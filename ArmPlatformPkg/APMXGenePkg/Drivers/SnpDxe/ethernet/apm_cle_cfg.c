/**
 * AppliedMicro X-Gene SOC Ethernet Classifier U-Boot Source file
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * Author: Ravi Patel <rapatel@apm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * @file apm_cle_cfg.c
 *
 */

#include "apm_enet_access.h"
#ifndef APM_XGENE
#include <misc/xgene/qmtm/xgene_qmtm.h>
#include <misc/xgene/cle/apm_preclass_data.h>
#include <misc/xgene/cle/apm_cle_mgr.h>
#else
#include "../qm/xgene_qmtm.h"
#include "../classifier/apm_preclass_data.h"
#include "../classifier/apm_cle_mgr.h"
#endif

#define CLE_DB_INDEX		0

static struct ptree_kn kn = {0, DBPTR_ALLOC(CLE_DB_INDEX)};
static struct apm_cle_dbptr dbptr;
static struct apm_ptree_config ptree[MAX_ENET_PORTS];
static u8 enet_macaddr[MAX_ENET_PORTS][8] = {{0}};

static struct ptree_branch branch[] = {
	{      0, 0xFFFF,  EQT, PTREE_ALLOC(0), EW_BRANCH(2),  2, 1, JMP_REL, JMP_FW },	/* Broadcast MACAddr byte [0:1] */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(1), EW_BRANCH(0),  0, 0, JMP_REL, JMP_BW },	/* Jump to check EthernetN MACAddr [0:1] */
	{      0, 0xFFFF,  EQT, PTREE_ALLOC(0), EW_BRANCH(4),  2, 1, JMP_REL, JMP_FW },	/* Broadcast MACAddr byte [2:3] */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(1), EW_BRANCH(0),  2, 0, JMP_REL, JMP_BW },	/* Jump to check EthernetN MACAddr [0:1] */
	{      0, 0xFFFF,  EQT, PTREE_ALLOC(0), EW_BRANCH(6),  8, 1, JMP_REL, JMP_FW },	/* Broadcast MACAddr byte [4:5] */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(1), EW_BRANCH(0),  4, 0, JMP_REL, JMP_BW },	/* Jump to check EthernetN MACAddr [0:1] */
#if defined(ALLOW_BROADCAST_ONLY_ARP)   /* (0x0806 == Ethernet Packet's EtherType field) */
	{      0, 0x0806,  EQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* Broadcast Ethertype ARP */
#elif defined(ALLOW_BROADCAST_UPTO_ARP) /* (0x0806 >= Ethernet Packet's EtherType field) */
	{      0, 0x0806,GTEQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* Broadcast Ethertype 0 to ARP (0x0806) */
#elif defined(ALLOW_BROADCAST_UPTO_VLAN)/* (0x8100 >= Ethernet Packet's EtherType field */
	{      0, 0x8100,GTEQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* Broadcast Ethertype 0 to VLAN (0x8100) */
#else /* ALLOW_BROADCAST_ANY_ETHERTYPE */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* No check for Ethertype */
#endif
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not a Broadcast Ethertype ARP so drop */


	{      0, 0x0000,  EQT, PTREE_ALLOC(1), EW_BRANCH(2),  2, 1, JMP_REL, JMP_FW },	/* EthernetN MACAddr byte [0:1] */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN MACAddr [0:1] so drop */
	{      0, 0x0000,  EQT, PTREE_ALLOC(1), EW_BRANCH(4),  2, 1, JMP_REL, JMP_FW },	/* EthernetN MACAddr byte [2:3] */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN MACAddr [2:3] so drop */
	{      0, 0x0000,  EQT, PTREE_ALLOC(1), EW_BRANCH(6),  8, 1, JMP_REL, JMP_FW },	/* EthernetN MACAddr byte [4:5] */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN MACAddr [4:5] so drop */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* No check for Ethertype */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN Ethertype so drop */

	{ 0xffff,      0,  EQT, PTREE_ALLOC(3), KEY_INDEX(0),  0, 0,       0,      0 },	/* Last Node allowing all of the above */
};

static struct ptree_dn dn[] = {
	{ START_NODE,	DBPTR_DROP(0), AVL_SEARCH(NO_BYTE), 0, 0, 0, 8, &branch[0] },	/* Allow BCast MAC with ARP */
	{ INTERIM_NODE,	DBPTR_DROP(0), AVL_SEARCH(NO_BYTE), 0, 0, 0, 8, &branch[8] },	/* Allow our EthernetN MACAddr */
	{ LAST_NODE,	DBPTR_DROP(0), AVL_SEARCH(NO_BYTE), 0, 0, 0, 1, &branch[16] },	/* Last Node */
};

static struct ptree_node node[] = {
	{ PTREE_ALLOC(0), EWDN, 0, (struct ptree_dn*)&dn[0] },
	{ PTREE_ALLOC(1), EWDN, 0, (struct ptree_dn*)&dn[1] },
	{ PTREE_ALLOC(2), EWDN, 0, (struct ptree_dn*)&dn[2] },
	{ PTREE_ALLOC(3),   KN, 0,    (struct ptree_kn*)&kn },
};

int apm_preclass_init(u8 port_id, struct eth_queue_ids *eth_q)
{
	int rc;
	struct apm_ptree_config *ptree_config = &ptree[port_id];
	u16 dstqid;

	memset(&enet_macaddr[port_id][0], 0, 8);
	memset(ptree_config, 0, sizeof(*ptree_config));

	ptree_config->default_result = DEFAULT_DBPTR;
	ptree_config->start_parser = 1;

	memset(&dbptr, 0, sizeof(dbptr));
	memset(&kn, 0, sizeof(kn));

	PCLS_DBG("Create Preclassifier DB entries for Ping Tree port %d\n",
		port_id);

	dstqid = QMTM_QUEUE_ID(eth_q->qm_ip, eth_q->rx_qid);
	dbptr.dstqidL = dstqid & 0x7f;
	dbptr.dstqidH = (dstqid >> 7) & 0x1f;
	dbptr.index = DBPTR_ALLOC(CLE_DB_INDEX);
	dbptr.fpsel  = eth_q->rx_fp_pbn - 0x20;

	kn.result_pointer = DBPTR_ALLOC(CLE_DB_INDEX);

	PCLS_DBG("Create Patricia Tree Nodes for Ping Tree with "
		"dstqid=0x%x, fpsel=0x%x\n", dbptr.dstqid, dbptr.fpsel);

	if ((rc = apm_ptree_alloc(port_id, ARRAY_SIZE(node),
			1, node, &dbptr, ptree_config)) !=
			APM_RC_OK) {
		PCLS_ERR("Preclass init error %d \n", rc);
		return rc;
	}

	PCLS_DBG("Switch Tree for port %d with default ptree\n", port_id);

	if ((rc = apm_set_sys_ptree_config(port_id, ptree_config)
			!= APM_RC_OK)) {
		PCLS_ERR("Preclass Switch port %d Tree error %d \n",
			port_id, rc);
		return rc;
	}

	return rc;
}

void apm_preclass_update_mac(u8 port_id, u8 *macaddr)
{
	int i;

	if (memcmp(&enet_macaddr[port_id][0], macaddr, 6) == 0)
		return;

	memcpy(&enet_macaddr[port_id][0], macaddr, 6);

	for (i = 0; i < 3; i++) {
		struct ptree_branch pbranch;

		memset(&pbranch, 0, sizeof(pbranch));
		pbranch.data = (macaddr[2 * i] << 8) | macaddr[(2 * i) + 1];
		pbranch.operation = EQT;
		apm_set_ptree_node_branch(port_id,
			ptree[port_id].start_node_ptr + 1,
			0, (i * 2), &pbranch, SET_BRANCH_MDO);
	}
}
