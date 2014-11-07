/**
 * AppliedMicro APM88xxxx SoC Classifier Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Mahesh Pujara <mpujara@apm.com>
 *                      Ravi Patel <rapatel@apm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * @file apm_preclass_api.c
 *
 * This file iplements APIs for APM88xxxx SoC Classifier Parser module.
 *
 */
#ifndef APM_XGENE
#include <misc/xgene/cle/apm_preclass_data.h>
#include <misc/xgene/cle/apm_preclass_base.h>
#else
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#define readl           MmioRead32
#define writel(v, a)    MmioWrite32((a), (v))
#define swab16(x) \
	(u16)((((u16)(x) & 0x00ff) << 8) | \
	(((u16)(x) & 0xff00) >> 8))
#include "apm_preclass_data.h"
#include "apm_preclass_base.h"
#endif

#define APM_RET_IVP APM_RC_INVALID_PARM

/* global data */
/* apm_cle_system_id & apm_cle_systems used for CLE resource division for AMP */
u8 apm_cle_system_id;	/* Needs to be updated by BootLoader and OS */
u8 apm_cle_systems;	/* Needs to be updated by BootLoader and OS */
int apm_preclass_init_state[MAX_CLE_ENGINE] = {0};
#ifdef CLE_SHADOW
static int ptree_shadow_done[MAX_CLE_ENGINE] = {0};
static struct apm_ptree_node sys_ptree_node[MAX_CLE_ENGINE][MAX_NODE_ENTRIES];
static struct apm_cle_dbptr sys_cle_dbptr[MAX_CLE_ENGINE][MAX_DB_ENTRIES];
#endif
#ifdef PTREE_MANAGER
struct apm_preclass_state sys_preclass_state[MAX_CLE_ENGINE];
#endif
struct apm_ptree_config sys_ptree_config[MAX_CLE_PORTS];
#ifdef CLE_MANAGER
int apm_cle_mgr_init(u32 cid);
#endif

u32 PID2CID[MAX_CLE_PORTS] = {
	CLE_0,
	CLE_0,
	CLE_1,
	CLE_1,
	XGCLE_0,
	XGCLE_1,
	XGCLE_2,
	XGCLE_3,
	CLE_LITE,
	CLE_LAC,
};
#define INDEX 0
#define COUNT 1
u32 PORTPARSER[MAX_CLE_PORTS][2] = {
	{CLE_PARSER0, 1},
	{CLE_PARSER1, 1},
	{CLE_PARSER0, 1},
	{CLE_PARSER1, 1},
	{CLE_PARSER0, 3},
	{CLE_PARSER0, 3},
	{CLE_PARSER0, 3},
	{CLE_PARSER0, 3},
	{CLE_PARSER0, 1},
	{CLE_PARSER2, 1},
};
u32 CLEBASEPORTID[MAX_CLE_ENGINE] = {
	CLE_ENET_0,
	CLE_ENET_2,
	CLE_XGENET_0,
	CLE_XGENET_1,
	CLE_XGENET_2,
	CLE_XGENET_3,
	CLE_ENET_4,
	CLE_LA,
};
u32 CLEPARSERS[MAX_CLE_ENGINE] = {
	2,	/* one parser for CLE_ENET_0 & one parser for CLE_ENET_1 */
	2,	/* one parser for CLE_ENET_2 & one parser for CLE_ENET_3 */
	3,	/* three parsers for CLE_XGENET_0 */
	3,	/* three parsers for CLE_XGENET_1 */
	3,	/* three parsers for CLE_XGENET_2 */
	3,	/* three parsers for CLE_XGENET_3 */
	1,	/* one parser for CLE_ENET_4 */
	1,	/* one parser for CLE_LA */
};

#if 0
static void shift_left_be(u32 *data, u32 bit_index, u32 bit_length, u32 shift)
{
	while (shift > 0 && bit_index > 0) {
		u32 long_end = (bit_index + bit_length - 1) / 32;
		u32 long_index = (bit_index - 1) / 32;
		u32 long_bit_index = ((bit_index - 1) % 32);
		u32 long_bit_mask = 0xffffffff >> long_bit_index;
		u32 long_bit_end_index = ((bit_index + bit_length) % 32);
		u32 long_bit_end_mask = 0xffffffff <<
			(32 - (long_bit_end_index ? long_bit_end_index : 32));
		u32 i;

		if (long_index == long_end) {
			data[long_index] = (data[long_index] &
				~(long_bit_mask & long_bit_end_mask)) |
				((data[long_index] &
				(long_bit_mask & long_bit_end_mask)) << 1);
		} else {
			data[long_index] = (data[long_index] & ~long_bit_mask) |
				((data[long_index] << 1) & long_bit_mask);

			for (i = long_index; i < long_end; i++) {

				if (i > long_index)
					data[i] <<= 1;

				data[i] = (data[i] & ~1) | (data[i + 1] >> 31);
			}

			data[long_end] = (data[long_end] & ~long_bit_end_mask) |
				((data[long_end] << 1) & long_bit_end_mask);
		}

		bit_index--;
		shift--;
	}
}

#ifndef CLE_SHADOW
static void shift_right_be(u32 *data, u32 data_length, u32 bit_index,
				u32 bit_length, u32 shift)
{
	bit_length = (bit_index + 1) < bit_length ? (bit_index + 1) : bit_length;

	while (shift > 0 && bit_index < ((data_length * 8) - 1)) {
		u32 long_end = (bit_index - bit_length + 1) / 32;
		u32 long_index = (bit_index + 1) / 32;
		u32 long_bit_index = ((bit_index + 1) % 32);
		u32 long_bit_mask = 0xffffffff << (31 - long_bit_index);
		u32 long_bit_end_index = ((bit_index - bit_length + 1) % 32);
		u32 long_bit_end_mask = 0xffffffff >> long_bit_end_index;
		u32 i;

		if (long_index == long_end) {
			data[long_index] = (data[long_index] &
				~(long_bit_mask & long_bit_end_mask)) |
				((data[long_index] &
				(long_bit_mask & long_bit_end_mask)) >> 1);
		} else {
			data[long_index] = (data[long_index] & ~long_bit_mask) |
				((data[long_index] >> 1) & long_bit_mask);

			for (i = long_index; i > long_end; i--) {

				if (i < long_index)
					data[i] >>= 1;

				data[i] = (data[i] & ~0x80000000) |
						(data[i - 1] << 31);
			}

			data[long_end] = (data[long_end] & ~long_bit_end_mask) |
				((data[long_end] & long_bit_end_mask) >> 1);
		}

		bit_index++;
		shift--;
	}
}
#endif

static void apm_ptree_node_struct_to_reg(void *data)
{
	u32 i;
	int shift;
	u32 *regs = (u32 *)data;
	struct apm_ptree_node *node = (struct apm_ptree_node *)data;

	switch (node->this.node_type) {
	case EIGHT_WAY_NODE:
#ifdef CONFIG_APM862xx
		shift = 5 - PAD_SIZE;
		shift_left_be(regs, 8, 17, shift);
		shift += 2;
#else
		shift = 6 - (PAD_SIZE / 5);
		shift_left_be(regs, 8 + ((PAD_SIZE * 4) / 5), 18, shift);
		shift += 1;
#endif
		for (i = 0; i < 8; i++) {
			shift += 5;
#ifdef CONFIG_APM862xx
			shift_left_be(regs, (64 * i) + 32, 59, shift);
#else
			shift_left_be(regs, (64 * i) + 32 + ((PAD_SIZE * 4) / 5), 59, shift);
#endif
		}
		break;

#ifdef CONFIG_APM862xx
	case FOUR_WAY_NODE1_ONLY:
	case FOUR_WAY_NODE2_ONLY:
	case FOUR_WAY_NODE_BOTH:
	{
		u32 j;
		shift = 0 - PAD_SIZE;
		for (j = 0; j < 2; j++) {
			shift += 5;
			shift_left_be(regs, (280 * j) + 8, 17, shift);
			shift += 2;
			for (i = 0; i < 4; i++) {
				shift += 5;
				shift_left_be(regs,
					((64 * i) + (280 * j) + 32), 59, shift);
			}
		}
		break;
	}
#endif

	case KEY_NODE:
#ifdef CONFIG_APM862xx
		shift = 2 - PAD_SIZE;
#else
		shift = 3 - (PAD_SIZE / 5);
#endif
		for (i = 0; i < 32; i++) {
			shift += 3;
#ifdef CONFIG_APM862xx
			shift_left_be(regs, (16 * i) + 8, 13, shift);
#else
			shift_left_be(regs, (16 * i) + 8 + ((PAD_SIZE * 4) / 5), 13, shift);
#endif
		}
	}
}

#ifndef CLE_SHADOW
static void apm_ptree_node_reg_to_struct(void *data)
{
	u32 i;
	int shift;
	u32 *regs = (u32 *)data;
	struct apm_ptree_node *node = (struct apm_ptree_node *)data;
	u32 size = SIZE_PER_PTREE_NODE_STRUCT;

	switch (node->this.node_type) {
	case EIGHT_WAY_NODE:
#ifdef CONFIG_APM862xx
		shift = 52 - PAD_SIZE;
#else
		shift = 52 - (PAD_SIZE / 5);
#endif
		for (i = 0; i < 8; i++) {
			shift -= 5;
			shift_right_be(regs, size, 491 + PAD_SIZE - (59 * i), 59, shift);
		}
#ifdef CONFIG_APM862xx
		shift -= 7;
		shift_right_be(regs, size, 19 + PAD_SIZE, 17, shift);
#else
		shift -= 6;
		shift_right_be(regs, size, 19 + PAD_SIZE, 18, shift);
#endif
		break;

#ifdef CONFIG_APM862xx
	case FOUR_WAY_NODE1_ONLY:
	case FOUR_WAY_NODE2_ONLY:
	case FOUR_WAY_NODE_BOTH:
	{
		u32 j;
		shift = 59 - PAD_SIZE;
		for (j = 0; j < 2; j++) {
			for (i = 0; i < 4; i++) {
				shift -= 5;
				shift_right_be(regs, size,
					(508 + PAD_SIZE - (59 * i) - (253 * j)), 59, shift);
			}
			shift -= 7;
			shift_right_be(regs, size, 272 + PAD_SIZE - (253 * j), 17, shift);
		}
		break;
	}
#endif

	case KEY_NODE:
#ifdef CONFIG_APM862xx
		shift = 101 - PAD_SIZE;
#else
		shift = 102 - (PAD_SIZE / 5);
#endif
		for (i = 0; i < 32; i++) {
			shift -= 3;
#ifdef CONFIG_APM862xx
			shift_right_be(regs, size, 418 + PAD_SIZE - (13 * i), 13, shift);
#else
			shift_right_be(regs, size, 417 + PAD_SIZE - (13 * i), 13, shift);
#endif
		}
	}
}
#endif
#endif

int apm_preclassify_init(u32 cid)
{
	int rc = APM_RC_OK;
	int i;
	struct apm_cle_dbptr dbptr;

	if (apm_preclass_init_state[cid]) {
		PCLS_DBG("Pre-classifier global s/w "
			"config already done \n");
		rc = APM_RC_FATAL;
		goto _ret_preclassify_init;
	}

#ifdef PTREE_MANAGER
	memset(&sys_preclass_state[cid], 0, sizeof(sys_preclass_state[cid]));
#endif
	for (i = 0; i < CLEPARSERS[cid]; i++) {
#ifdef PTREE_MANAGER
		sys_preclass_state[cid].start_parser[i] = PARSER_HALT0_WR(1);
#endif
		memset(&sys_ptree_config[CLEBASEPORTID[cid] + i], 0,
			sizeof(sys_ptree_config[CLEBASEPORTID[cid] + i]));
		sys_ptree_config[i].start_parser = PARSER_HALT0_WR(1);
	}
	memset(&dbptr, 0, sizeof(dbptr));
	dbptr.index = START_DB_INDEX;
	dbptr.drop = 1;
	rc = apm_set_cle_dbptr(CLEBASEPORTID[cid], &dbptr);
#ifdef CLE_MANAGER
	rc |= apm_cle_mgr_init(cid);
#endif
	apm_preclass_init_state[cid] = 1;

_ret_preclassify_init:
	return rc;
}

#ifdef CLE_SHADOW
static inline void apm_ptree_shadow_init(u32 cid)
{
	if (!ptree_shadow_done[cid]) {
		memset(&sys_ptree_node[cid], 0,
			sizeof(sys_ptree_node[cid]));
		memset(&sys_cle_dbptr[cid], 0,
			sizeof(sys_cle_dbptr[cid]));
		ptree_shadow_done[cid] = 1;
	}
}

struct apm_ptree_node *get_shadow_ptree_nodes(u32 port)
{
	return &sys_ptree_node[PID2CID[port]][0];
}

struct apm_cle_dbptr *get_shadow_cle_dbptrs(u32 port)
{
	return &sys_cle_dbptr[PID2CID[port]][0];
}
#endif

int apm_set_ptree_node(u8 port, u8 node_index, struct apm_ptree_node *node)
{
	int rc;
	struct apm_ptree_node snode;

#ifdef CLE_SHADOW
	apm_ptree_shadow_init(PID2CID[port]);

	memcpy(&sys_ptree_node[PID2CID[port]][node_index], node,
		sizeof(struct apm_ptree_node));
#endif
	memset(&snode, 0, sizeof(snode));
	memcpy(&snode, node, sizeof(snode));

	if (snode.this.node_type == EIGHT_WAY_NODE) {
		int i;
		struct apm_ptree_ewdn *sewdn = &snode.ewdn;
		struct apm_ptree_branch empty_branch;
		u32 jump_bytes = (port >= CLE_XGENET_0 && port <= CLE_XGENET_3) ? 8 : 4;

		memset(&empty_branch, 0, sizeof(empty_branch));

		for (i = 0; i < 8; i++) {
			struct apm_ptree_branch *sbranch = &sewdn->branch[i];

			if (memcmp(sbranch, &empty_branch, sizeof(struct apm_ptree_branch))) {
				struct apm_ptree_branch branch;

				memcpy(&branch, sbranch, sizeof(struct apm_ptree_branch));
				sbranch->mask = swab16(branch.mask & DN_MASK_SIZE);
				sbranch->data = swab16(branch.data & DN_MASK_SIZE);
				if (branch.jump_rel == JMP_ABS)
					sbranch->next_packet_pointer =
						((branch.next_packet_pointer + jump_bytes) & DN_NBP_SIZE);
			}
		}
	}

	/*apm_ptree_node_struct_to_reg(node);*/
	rc = apm_preclass_ptram_write(port, node_index, (u32 *)&snode);

	return rc;
}

int apm_get_ptree_node(u8 port, u8 node_index, struct apm_ptree_node *node)
{
	int rc = APM_RC_OK;

#ifdef CLE_SHADOW
	apm_ptree_shadow_init(PID2CID[port]);

	memcpy(node, &sys_ptree_node[PID2CID[port]][node_index],
		sizeof(struct apm_ptree_node));
#else
	struct apm_ptree_node gnode;

	memset(&gnode, 0, sizeof(gnode));
	rc = apm_preclass_ptram_read(port, node_index, (u32 *)&gnode);
	/*apm_ptree_node_reg_to_struct(node);*/
	if (gnode.this.node_type == EIGHT_WAY_NODE) {
		int i;
		struct apm_ptree_ewdn *gewdn = (struct apm_ptree_ewdn *)&gnode;
		struct apm_ptree_branch empty_branch;
		u32 jump_bytes = (port >= CLE_XGENET_0 && port <= CLE_XGENET_3) ? 8 : 4;

		memset(&empty_branch, 0, sizeof(empty_branch));

		for (i = 0; i < 8; i++) {
			struct apm_ptree_branch *gbranch = &gewdn->branch[i];

			if (memcmp(gbranch, &empty_branch, sizeof(struct apm_ptree_branch))) {
				struct apm_ptree_branch branch;

				memcpy(&branch, gbranch, sizeof(struct apm_ptree_branch));
				gbranch->mask = swab16(branch.mask & DN_MASK_SIZE);
				gbranch->data = swab16(branch.data & DN_MASK_SIZE);
				if (branch.jump_rel == JMP_ABS)
					gbranch->next_packet_pointer =
						((branch.next_packet_pointer - jump_bytes) & DN_NBP_SIZE);
			}
		}
	}

	memcpy(node, &gnode, sizeof(gnode));
#endif

	return rc;
}

int apm_set_cle_dbptr(u32 port, struct apm_cle_dbptr *dbptr)
{
	int rc;
	u32 index;

#ifdef CLE_DEBUG
	if (dbptr == NULL) {
		PCLS_DBG("Null dbptr pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif

	index = dbptr->index;
	/* Making sure RAM is not written with unintended value */
	dbptr->index = 0;
	rc = apm_preclass_cldb_write(port, index, (u32 *)dbptr);

#ifdef CLE_SHADOW
	apm_ptree_shadow_init(PID2CID[port]);

	/* index field Will be used for cle_dbptr validity by user */
	dbptr->index = 1;
	memcpy(&sys_cle_dbptr[PID2CID[port]][index], dbptr,
		sizeof(struct apm_cle_dbptr));
#endif

	/* Putting back the index vaule */
	dbptr->index = index;

	return rc;
}

#ifdef PTREE_MANAGER
int apm_get_cle_dbptr(u32 port, struct apm_cle_dbptr *dbptr)
{
	int rc = APM_RC_OK;
	u32 index;

#ifdef CLE_DEBUG
	if (dbptr == NULL) {
		PCLS_DBG("Null dbptr pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif

	index = dbptr->index;

#ifdef CLE_SHADOW
	apm_ptree_shadow_init(PID2CID[port]);

	memcpy(dbptr, &sys_cle_dbptr[PID2CID[port]][index],
		sizeof(struct apm_cle_dbptr));
#else
	dbptr->index = 0;
	rc = apm_preclass_cldb_read(port, index, (u32 *)dbptr);
#endif

	return rc;
}
#endif

#ifdef CLE_NODE_DEBUG
void apm_ptree_dump(const char *func, int line, struct apm_ptree_node *node)
{
	int i;
	struct apm_ptree_ewdn *ewdn;
	struct apm_ptree_branch empty_branch;
	struct apm_ptree_kn *kn;

	CLE_NODE_DBG("%a: %d:\n", func, line);
	switch(node->this.node_type) {
	case EIGHT_WAY_NODE:
		memset(&empty_branch, 0, sizeof(empty_branch));
		ewdn = (struct apm_ptree_ewdn *)node;
		CLE_NODE_DBG(" EW: Type %d "
				"RPtr %d SBSt %d BySt %d HdSt %d Last %d CorC %d"
				"\n", ewdn->node_type, ewdn->result_pointer,
				ewdn->search_byte_store, ewdn->byte_store,
				ewdn->header_length_store, ewdn->last_node,
				ewdn->extension);
		for (i = 0; i < 8; i++) {
			struct apm_ptree_branch *branch = &ewdn->branch[i];
			if (memcmp(branch, &empty_branch, sizeof(struct apm_ptree_branch))) {
				struct apm_ptree_branch dbranch;

				memcpy(&dbranch, branch, sizeof(struct apm_ptree_branch));
				CLE_NODE_DBG("  %d: VBit %d Mask %04x Data %04x OTyp %d "
					"%a %3d,%d JRel %d JBkw %d NPOf %d\n",
					i, dbranch.valid, dbranch.mask, dbranch.data,
					dbranch.operation,
					(ewdn->last_node ? "KNIn" : "NNBr"),
					dbranch.next_node_branch & DN_NN_SIZE,
					(ewdn->last_node ?
					((dbranch.next_node_branch & KN_NN_MASK) >> KN_NN_SHIFT) :
					((dbranch.next_node_branch & DN_NB_MASK) >> DN_NB_SHIFT)),
					dbranch.jump_rel, dbranch.jump_bw,
					dbranch.next_packet_pointer);
			}
		}
		break;

	case KEY_NODE:
		kn = (struct apm_ptree_kn *)node;
		CLE_NODE_DBG(" KN: Type %d\n", kn->node_type);
		for (i = 0; i < KEYNODE_COUNT; i++) {
			struct apm_ptree_key *key = &kn->key[i];
			if (key->result_pointer || key->priority) {
				CLE_NODE_DBG(" %2d: Prio %d RPtr %d\n",
					i, key->priority, key->result_pointer);
			}
		}
		break;
	}
}
#endif

void apm_ptree_set_data(u32 port, void *data,
		       struct ptree_node *pnode,
		       u8 set_type)
{
	u8 index = pnode->location;
	int i;
	struct apm_ptree_node *node;
	struct apm_ptree_ewdn *ewdn;
	struct apm_ptree_kn *kn;
	struct apm_ptree_key *key;
	struct ptree_dn *pdn;
	struct ptree_kn *pkn;

	node = (struct apm_ptree_node *)data;

	PCLS_DBG("pnode->type[%d] \n", pnode->type);

	if (!data) {
		PCLS_DBG("Invalid data pointer");
		return;
	}

#ifdef CLE_DEBUG
	for (i = 0; i < REGS_PER_PTREE_NODE; i++) {
		PCLS_DBG("data[%d] is 0X%08x \t", i, ((u32 *)data)[i]);
	}
	PCLS_DBG(" \n");
#endif

	switch(pnode->type) {
	case EWDN:
		if (set_type)
			node->this.node_type = set_type & DN_TYPE_SIZE;
		pdn = (struct ptree_dn *)pnode->data;
		ewdn = &node->ewdn;
		ewdn->result_pointer = pdn->result_pointer & DN_DEFPTR_SIZE;
		ewdn->search_byte_store = pdn->search_byte_store & DN_SEARCHB_SIZE;
		ewdn->byte_store = pdn->byte_store & DN_BYTE_SIZE;
		ewdn->header_length_store = pdn->header_length_store & DN_HDRL_SIZE;
		ewdn->last_node = pdn->node_position & DN_LN_SIZE;
		ewdn->extension = pdn->extension & DN_EXTENSION_SIZE;
		CLE_NODE_DBG(" EW: Type %d "
				"RPtr %d SBSt %d BySt %d HdSt %d Last %d CorC %d"
				"\n", ewdn->node_type, ewdn->result_pointer,
				ewdn->search_byte_store, ewdn->byte_store,
				ewdn->header_length_store, ewdn->last_node,
				ewdn->extension);
		for (i = 0; i < pdn->num; i++) {
			struct apm_ptree_branch *branch = &ewdn->branch[i];
			const struct ptree_branch *pbranch = &pdn->branch[i];
			branch->valid = pbranch->valid & DN_VALID_SIZE;
			branch->mask = pbranch->mask & DN_MASK_SIZE;
			branch->data = pbranch->data & DN_MASK_SIZE;
			branch->operation = pbranch->operation & DN_OP_SIZE;
			if (ewdn->last_node)
				branch->next_node_branch =
					((pbranch->next_node_index & DN_NN_SIZE) |
					((pbranch->next_node_loc & KN_NN_SIZE) << KN_NN_SHIFT)) & KN_NNP_SIZE;
			else
				branch->next_node_branch =
					((pbranch->next_node_index & DN_NN_SIZE) |
					((pbranch->next_node_loc & DN_NB_SIZE) << DN_NB_SHIFT)) & DN_NNP_SIZE;
			branch->jump_rel =
				pbranch->jump_rel & DN_JREL_SIZE;
			branch->jump_bw =
				pbranch->jump_bw & DN_JBW_SIZE;
			branch->next_packet_pointer =
				pbranch->next_packet_pointer & DN_NBP_SIZE;
			CLE_NODE_DBG("  %d: VBit %d Mask %04x Data %04x OTyp %d "
					"%a %3d%a,%d JRel %d JBkw %d NPOf %d\n",
					i, branch->valid, branch->mask, branch->data,
					branch->operation,
					(ewdn->last_node ? "KNIn" : "NNBr"),
					pbranch->next_node_index,
					"",
					pbranch->next_node_loc,
					branch->jump_rel, branch->jump_bw,
					branch->next_packet_pointer);
		}
		break;

	case KN:
		if (set_type)
			node->this.node_type = set_type & DN_TYPE_SIZE;
		pkn = (struct ptree_kn *)pnode->data;
		kn = &node->kn;
		key = &kn->key[index];
		key->priority = pkn->priority & KN_PRI_SIZE;
		key->result_pointer = pkn->result_pointer & KN_PTR_SIZE;

		CLE_NODE_DBG(" KN: Type %d\n", kn->node_type);
		CLE_NODE_DBG(" %2d: Prio %d RPtr %d\n",
				index, key->priority, key->result_pointer);
		break;
	}
}

int apm_ptree_node_config(u8 port, struct ptree_node *node)
{
	int rc = APM_RC_OK;
	u32 data[LONG_PER_PTREE_NODE_STRUCT];
	u32 node_index = node->index;
	u32 cid = PID2CID[port];
#ifdef PTREE_MANAGER
	struct apm_preclass_state *pcs = &sys_preclass_state[cid];
	struct apm_preclass_node_state *pns = &sys_preclass_state[cid].node_state[node_index];
#endif

	if (!apm_preclass_init_state[cid])
		apm_preclassify_init(cid);

#ifdef PTREE_MANAGER
	if (node->type == EWDN) { /* 8-way node */
		memset(data, 0, sizeof(data));

		/* check if this is the first config for this entry */
		if (!pns->type) {
			/* config + set type in hw */
			apm_ptree_set_data(port, data, node, EIGHT_WAY_NODE);
			/* set type */
			pns->type = EWDN;
			/* set location mask */
			pns->config_mask = 1;

			pcs->ewdn_count++;
		/* check if its the same type of node */
		} else if (pns->type == node->type) {
			/* check if the entry is already configured */
			if (pns->config_mask) {
				/* prompt for reconfig */
				PCLS_PRNT("8 way node entry %d reconfig "
					"detected !!\n", node_index);
			} else {
				/* set location mask */
				pns->config_mask = 1;
			}
			/* always write everything */
			apm_ptree_set_data(port, data, node, EIGHT_WAY_NODE);
		/* This is a reconfig of a different type
		   (can allow for EWDN only) */
		} else {
			/* prompt for new type config */
			PCLS_PRNT("Node entry %d reconfig with new "
				"type detected !!\n", node_index);
			apm_ptree_set_data(port, data, node, EIGHT_WAY_NODE);

			if (pns->type == KN)
				pcs->kn_count--;

			/* set type */
			pns->type = EWDN;
			/* set location mask */
			pns->config_mask = 1;

			pcs->ewdn_count++;
		}
	} else { /* Key node */
		/* check if this is the first config for this entry */
		if (!pns->type) {
			memset(data, 0, sizeof(data));
			/* config + set type in hw */
			apm_ptree_set_data(port, data, node, KEY_NODE);
			/* set type */
			pns->type = KN;
			/* set location mask */
			pns->config_mask |= 1 << node->location;

			pcs->kn_count++;
		} else if (pns->type == node->type) {
			/* check if its the same type of node */
			/* check if the entry is already configured */
			if ((pns->config_mask >> node->location) & 1) {
				/* prompt for reconfig */
				PCLS_PRNT("Key node entry %d "
					"location %d reconfig detected !!\n",
					node_index, node->location);
			} else {
				/* set location mask */
				pns->config_mask |= 1 << node->location;
			}

			/* needs read modify write */
			rc = apm_get_ptree_node(port, node_index,
				(struct apm_ptree_node *)data);

			/* config */
			apm_ptree_set_data(port, data, node, 0);

			pcs->kn_count++;
		}
	}
#else
	memset(data, 0, sizeof(data));
	if (node->type == EWDN) { /* 8-way node */
		apm_ptree_set_data(port, data, node, EIGHT_WAY_NODE);
	} else { /* Key node */
		apm_ptree_set_data(port, data, node, KEY_NODE);
	}
#endif

	rc |= apm_set_ptree_node(port, node_index,
			(struct apm_ptree_node *)data);

	return rc;
}

static void apm_set_ptree_node_branch_from_pbranch(
		struct apm_ptree_branch *branch,
		struct ptree_branch *pbranch,
		u32 set_branch_field, u32 last_node)
{
	if (set_branch_field & SET_BRANCH_VALID)
		branch->valid = pbranch->valid & DN_VALID_SIZE;
	if (set_branch_field & SET_BRANCH_MASK)
		branch->mask = pbranch->mask & DN_MASK_SIZE;
	if (set_branch_field & SET_BRANCH_DATA)
		branch->data = pbranch->data & DN_MASK_SIZE;
	if (set_branch_field & SET_BRANCH_OPERATION)
		branch->operation = pbranch->operation & DN_OP_SIZE;
	if (set_branch_field & SET_BRANCH_NNBR) {
		if (last_node)
			branch->next_node_branch =
				((pbranch->next_node_index & DN_NN_SIZE) |
				((pbranch->next_node_loc & KN_NN_SIZE) << KN_NN_SHIFT)) & KN_NNP_SIZE;
		else
			branch->next_node_branch =
				((pbranch->next_node_index & DN_NN_SIZE) |
				((pbranch->next_node_loc & DN_NB_SIZE) << DN_NB_SHIFT)) & DN_NNP_SIZE;
	}
	if (set_branch_field & SET_BRANCH_JUMP_REL)
		branch->jump_rel = pbranch->jump_rel & DN_JREL_SIZE;
	if (set_branch_field & SET_BRANCH_JUMP_BW)
		branch->jump_bw = pbranch->jump_bw & DN_JBW_SIZE;
	if (set_branch_field & SET_BRANCH_NPPTR)
		branch->next_packet_pointer = pbranch->next_packet_pointer & DN_NBP_SIZE;
}

int apm_set_ptree_node_branch(u8 port, u8 node_index,
			u8 sub_node, u8 branch_index,
			struct ptree_branch *pbranch,
			u32 set_branch_field)
{
	int rc = APM_RC_INVALID_PARM;
	struct apm_ptree_node node;

	if (apm_get_ptree_node(port, node_index, &node))
		goto _ret_ptree_node_branch;

	switch (node.this.node_type) {
	case EIGHT_WAY_NODE:
		if (branch_index < 8) {
			struct apm_ptree_branch *branch = &node.ewdn.branch[branch_index];

			apm_set_ptree_node_branch_from_pbranch(branch, pbranch,
				set_branch_field, node.ewdn.last_node);
			CLE_PTREE_DUMP(&node);
			rc |= apm_set_ptree_node(port, node_index, &node);
		} else {
			PCLS_PRNT("Invalid branch number for EWDN\n");
		}
		break;

	case KEY_NODE:
		PCLS_PRNT("Entry [%d] is a key node, cannot "
				"configure a branch \n", node_index);
		break;

	default:
		PCLS_PRNT("Node type unknown for entry [%d], "
			"configure it first \n", node_index);
	}

_ret_ptree_node_branch:
	return rc;
}

#ifdef PTREE_MANAGER
int apm_clear_ptree_node_type(u8 port, u8 node_index)
{
	int rc;
	struct apm_ptree_node node;

#ifdef CLE_DEBUG
	if (port > MAX_CLE_PORTS) {
		PCLS_DBG("Invalid port number \n");
		return APM_RC_INVALID_PARM;
	}
#endif
	/* read node */
	rc = apm_get_ptree_node(port, node_index, &node);
	/* clear node type in node */
	node.this.node_type = 0;
	/* write back */
	rc |= apm_set_ptree_node(port, node_index, &node);
	/* update state */
	sys_preclass_state[PID2CID[port]].node_state[node_index].type = 0;
	return rc;
}

int apm_get_preclass_state(u8 port, struct apm_preclass_state *preclass_state)
{
	int rc = APM_RC_OK;

#ifdef CLE_DEBUG
	if (preclass_state == NULL) {
		PCLS_DBG("Null preclass_state pointer \n");
		return APM_RC_INVALID_PARM;
	}
	if (port > MAX_CLE_PORTS) {
		PCLS_DBG("Invalid port number \n");
		return APM_RC_INVALID_PARM;
	}
#endif
	memcpy(preclass_state, &sys_preclass_state[PID2CID[port]],
		sizeof(struct apm_preclass_state));
	return rc;
}
#endif

int apm_set_sys_ptree_config(u8 port,
			struct apm_ptree_config *ptree_config)
{
	int i, rc = APM_RC_OK;
	u32 data;
	u32 snptr_addr = 0;
	u32 spptr_addr = 0;
	u32 dbptr_addr = 0;
	u32 parser_ctl_addr = 0;
	u32 maxhop_addr = 0;
	u32 cid = PID2CID[port];
	u32 control_bytes = (port >= CLE_XGENET_0 && port <= CLE_XGENET_3) ? 8 : 4;
#ifndef PTREE_MANAGER
	u32 update_parser = 1;
#endif

	if (!apm_preclass_init_state[cid])
		apm_preclassify_init(cid);

	if (ptree_config != NULL) {
		/* update default config */
		ptree_config->start_parser &= PARSER_HALT0_MASK;
#ifndef PTREE_MANAGER
		if (sys_ptree_config[port].start_parser == ptree_config->start_parser)
			update_parser = 0;
#endif
		memcpy(&sys_ptree_config[port], ptree_config,
			sizeof(struct apm_ptree_config));
	}

	for (i = PORTPARSER[port][INDEX]; i < PORTPARSER[port][INDEX] + PORTPARSER[port][COUNT]; i++) {
		switch (i) {
		case CLE_PARSER0:
			snptr_addr = SNPTR0_ADDR;
			spptr_addr = SPPTR0_ADDR;
			dbptr_addr = DFCLSRESDBPTR0_ADDR;
			parser_ctl_addr = PARSER_CTL0_ADDR;
			maxhop_addr = TMAXHOP0_ADDR;
			break;
		case CLE_PARSER1:
			snptr_addr = SNPTR1_ADDR;
			spptr_addr = SPPTR1_ADDR;
			dbptr_addr = DFCLSRESDBPTR1_ADDR;
			parser_ctl_addr = PARSER_CTL1_ADDR;
			maxhop_addr = TMAXHOP1_ADDR;
			break;
		case CLE_PARSER2:
			snptr_addr = SNPTR2_ADDR;
			spptr_addr = SPPTR2_ADDR;
			dbptr_addr = DFCLSRESDBPTR2_ADDR;
			parser_ctl_addr = PARSER_CTL2_ADDR;
			maxhop_addr = TMAXHOP2_ADDR;
			break;
		default:
			PCLS_ERR("Invalid port number %d\n", port);
			return APM_RC_INVALID_PARM;
		}

		PCLS_PRNT("Configuring start node ptr [%d] "
			"start packet ptr [%d] max hop [%d] "
			"start parser %d for port %d\n",
			sys_ptree_config[port].start_node_ptr,
			sys_ptree_config[port].start_pkt_ptr,
			sys_ptree_config[port].max_hop,
			sys_ptree_config[port].start_parser, port);

		/* snptr */
		data = SNPTR0_WR(sys_ptree_config[port].start_node_ptr);
		rc = apm_gbl_cle_wr32(cid, snptr_addr, data);

		/* spptr */
		data = SPPTR0_WR(sys_ptree_config[port].start_pkt_ptr + control_bytes);
		rc |= apm_gbl_cle_wr32(cid, spptr_addr, data);

		/* Assign Default Classification DB Ptr */
		data = (DFCLSRESDBPRIORITY0_MASK &
			sys_ptree_config[port].default_result) |
			(DFCLSRESDBPTR0_MASK &
			sys_ptree_config[port].default_result);
		rc |= apm_gbl_cle_wr32(cid, dbptr_addr, data);
		PCLS_PRNT("Assign Default Classification Priority %d DB Ptr %d\n",
			DFCLSRESDBPRIORITY0_RD(data), DFCLSRESDBPTR0_RD(data));

		/* set parser state */
#ifdef PTREE_MANAGER
		if (sys_preclass_state[cid].start_parser[i] !=
				sys_ptree_config[port].start_parser) {
			rc |= apm_gbl_cle_rd32(cid, parser_ctl_addr, &data);
			data = PARSER_HALT0_SET(data, PARSER_HALT0_WR(!sys_ptree_config[port].start_parser));
			rc |= apm_gbl_cle_wr32(cid, parser_ctl_addr, data);
			sys_preclass_state[cid].start_parser[i] =
				sys_ptree_config[port].start_parser;
			PCLS_PRNT("Parser Control 0x%08x\n", data);
		}
#else
		if (update_parser) {
			rc |= apm_gbl_cle_rd32(cid, parser_ctl_addr, &data);
			data = PARSER_HALT0_SET(data, PARSER_HALT0_WR(!sys_ptree_config[port].start_parser));
			rc |= apm_gbl_cle_wr32(cid, parser_ctl_addr, data);
			PCLS_PRNT("Parser Control 0x%08x\n", data);
		}
#endif

		/* Tree Max Hops */
		data = TMAXHOP0_WR(sys_ptree_config[port].max_hop);
		rc |= apm_gbl_cle_wr32(cid, maxhop_addr, data);
		PCLS_PRNT("Max Hop 0x%08x\n", data);
	}

	return rc;
}

#ifdef PTREE_MANAGER
int apm_get_sys_ptree_config(u8 port,
				struct apm_ptree_config *ptree_config)
{
	int rc = APM_RC_OK;

#ifdef CLE_DEBUG
	if (port > MAX_CLE_PORTS) {
		PCLS_DBG("Invalid port number \n");
		return APM_RC_INVALID_PARM;
	}
	if (ptree_config  == NULL) {
		PCLS_DBG("Null ptree_config pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif
	memcpy(ptree_config, &sys_ptree_config[port],
	       sizeof(struct apm_ptree_config));
	return rc;
}

int apm_preclass_start_stop(u8 port, u32 state)
{
	int i, rc = APM_RC_OK;
	u32 data;
	u32 parser_ctl_addr = 0;
	u32 cid = PID2CID[port];

	if (!apm_preclass_init_state[cid])
		apm_preclassify_init(cid);

	for (i = PORTPARSER[port][INDEX]; i < PORTPARSER[port][INDEX] + PORTPARSER[port][COUNT]; i++) {
		switch (i) {
		case CLE_PARSER0:
			parser_ctl_addr = PARSER_CTL0_ADDR;
			break;
		case CLE_PARSER1:
			parser_ctl_addr = PARSER_CTL1_ADDR;
			break;
		case CLE_PARSER2:
			parser_ctl_addr = PARSER_CTL2_ADDR;
			break;
		default:
			PCLS_ERR("Invalid port number %d\n", port);
			return APM_RC_INVALID_PARM;
		}

		/* set parser state */
		if (sys_preclass_state[cid].start_parser[i] !=
				PARSER_HALT0_WR(state)) {
			rc |= apm_gbl_cle_rd32(cid, parser_ctl_addr, &data);
			data = PARSER_HALT0_SET(data, PARSER_HALT0_WR(!state));
			rc |= apm_gbl_cle_wr32(cid, parser_ctl_addr, data);
			sys_preclass_state[cid].start_parser[i] =
				PARSER_HALT0_WR(state);
		}
	}

	PCLS_DBG("%a preclassification parser for port %d \n",
		(state ? "Starting" : "Stopping"), port);

	return rc;
}

int apm_get_preclass_trace(u8 port, struct apm_preclass_trace *preclass_trace)
{
	int i, rc = APM_RC_OK;
	u32 data = 0;
	u32 cid = PID2CID[port];

	switch (PORTPARSER[port][INDEX]) {
	case CLE_PARSER0:
		rc |= apm_gbl_cle_rd32(cid, LSTNVST0_ADDR, &data);
		preclass_trace->last_node_visited = LSTNVST0_RD(data);

		for (i = 0; i< MAX_LAST_NODES_TRACE; i++) {
			rc |= apm_gbl_cle_rd32(cid, LSTTRCNVST0_0_ADDR + (i<<2),
				       		&data);
			preclass_trace->last_visited_node_trace[i] =
							LTRCNVST0_RD(data);
		}
		for (i = 0; i< MAX_FIRST_NODES_TRACE; i++) {
			rc |= apm_gbl_cle_rd32(cid, FTRCNVST0_0_ADDR + (i<<2),
					      	&data);
			preclass_trace->first_visited_node_trace[i] =
							FTRCNVST0_RD(data);
		}
		break;

	case CLE_PARSER1:
		rc |= apm_gbl_cle_rd32(cid, LSTNVST1_ADDR, &data);
		preclass_trace->last_node_visited = LSTNVST1_RD(data);

		for (i = 0; i< MAX_LAST_NODES_TRACE; i++) {
			rc |= apm_gbl_cle_rd32(cid, LSTTRCNVST1_0_ADDR + (i<<2),
					       	&data);
			preclass_trace->last_visited_node_trace[i] =
							LTRCNVST1_RD(data);
		}
		for (i = 0; i< MAX_FIRST_NODES_TRACE; i++) {
			rc |= apm_gbl_cle_rd32(cid, FTRCNVST1_0_ADDR + (i<<2),
					       	&data);
			preclass_trace->first_visited_node_trace[i] =
							FTRCNVST1_RD(data);
		}
		break;

	case CLE_PARSER2:
		rc |= apm_gbl_cle_rd32(cid, LSTNVST2_ADDR, &data);
		preclass_trace->last_node_visited = LSTNVST2_RD(data);

		for (i = 0; i< MAX_LAST_NODES_TRACE; i++) {
			rc |= apm_gbl_cle_rd32 (cid, LSTTRCNVST2_0_ADDR + (i<<2),
					       &data);
			preclass_trace->last_visited_node_trace[i] =
							LTRCNVST2_RD(data);
		}
		for (i = 0; i< MAX_FIRST_NODES_TRACE; i++) {
			rc |= apm_gbl_cle_rd32 (cid, FTRCNVST2_0_ADDR + (i<<2),
					       &data);
			preclass_trace->first_visited_node_trace[i] =
							FTRCNVST2_RD(data);
		}
		break;

	default:
		break;
	}
	return rc;
}

int apm_preclass_wol_mode(int enable)
{
	int rc;
	u32 snptr;
	rc = apm_gbl_cle_rd32(0, SNPTR0_ADDR, &snptr);
	snptr = WOL_MODE0_SET(snptr, enable);
	rc |= apm_gbl_cle_wr32(0, SNPTR0_ADDR, snptr);
	return rc;
}
#endif
