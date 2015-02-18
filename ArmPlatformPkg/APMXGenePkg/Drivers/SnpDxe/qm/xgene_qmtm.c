/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager Source file
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
 * @file xgene_qmtm.c
 *
 */


#include "xgene_qmtm.h"
#include "xgene_qmtm_core.h"
#ifdef CONFIG_SHADOWCAT
#include "xgene_qmtm_shadowcat_csr.h"
#else
#include "xgene_qmtm_csr.h"
#endif

#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>


#ifndef APM_XGENE
#include <misc/xgene/qmtm/xgene_qmtm.h>
#ifdef CONFIG_ARCH_MSLIM
#include <asm/hardware/mslim-iof-map.h>
#endif
#else
#define EIO	5
#define EAGAIN 11
#define ENOMEM 12 
#define ENODEV 19
#endif

static struct xgene_qmtm_pdev *pdev = NULL;

#ifdef CONFIG_SHADOWCAT
const struct xgene_qmtm_string slave_s[SLAVE_MAX] = {
	       [SLAVE_XGE0]        = { "SXGMII0" },
	       [SLAVE_XGE1]        = { "SXGMII1" },
	       [SLAVE_CPU_QMTM0]   = { "CPU_QMTM0" },
};
#else
const struct xgene_qmtm_string slave_s[SLAVE_MAX] = {
	[SLAVE_ETH0]        = { "SGMII0" },
	[SLAVE_ETH1]        = { "SGMII1" },
	[SLAVE_ETH2]        = { "SGMII2" },
	[SLAVE_ETH3]        = { "SGMII3" },
	[SLAVE_XGE0]        = { "SXGMII0" },
	[SLAVE_XGE1]        = { "SXGMII1" },
	[SLAVE_XGE2]        = { "SXGMII2" },
	[SLAVE_XGE3]        = { "SXGMII3" },
	[SLAVE_METH]        = { "RGMII" },
	[SLAVE_PKTDMA]      = { "PKTDMA" },
	[SLAVE_CTX_QMTM0]   = { "CTX_QMTM0" },
	[SLAVE_CTX_QMTM1]   = { "CTX_QMTM1" },
	[SLAVE_CTX_QMTM2]   = { "CTX_QMTM2" },
	[SLAVE_SEC]         = { "SEC" },
	[SLAVE_CLASS]       = { "LAC" },
	[SLAVE_MSLIM_QMTM0] = { "MSLIM_QMTM0" },
	[SLAVE_MSLIM_QMTM1] = { "MSLIM_QMTM1" },
	[SLAVE_MSLIM_QMTM2] = { "MSLIM_QMTM2" },
	[SLAVE_MSLIM_QMTM3] = { "MSLIM_QMTM3" },
	[SLAVE_PMPRO]       = { "PMPRO" },
	[SLAVE_SMPRO_QMTM0] = { "SMPRO_QMTM0" },
	[SLAVE_SMPRO_QMTM1] = { "SMPRO_QMTM1" },
	[SLAVE_SMPRO_QMTM2] = { "SMPRO_QMTM2" },
	[SLAVE_SMPRO_QMTM3] = { "SMPRO_QMTM3" },
	[SLAVE_CPU_QMTM0]   = { "CPU_QMTM0" },
	[SLAVE_CPU_QMTM1]   = { "CPU_QMTM1" },
	[SLAVE_CPU_QMTM2]   = { "CPU_QMTM2" },
	[SLAVE_CPU_QMTM3]   = { "CPU_QMTM3" },
};
#endif
const struct xgene_qmtm_string qtype_s[QTYPE_MAX] = {
	[QTYPE_DISABLED]      = { "--" },
	[QTYPE_PQ]            = { "PQ" },
	[QTYPE_FP]            = { "FP" },
	[QTYPE_VQ]            = { "VQ" },
};

const struct xgene_qmtm_string qsize_s[QSIZE_MAX] = {
	[QSIZE_512B]           = { "512B" },
	[QSIZE_2KB]            = { "2KB" },
	[QSIZE_16KB]           = { "16KB" },
	[QSIZE_64KB]           = { "64KB" },
	[QSIZE_512KB]          = { "512KB" },
};

const struct xgene_qmtm_string qaccess_s[QACCESS_MAX] = {
	[QACCESS_ALT]          = { "ALT" },
	[QACCESS_QMI]          = { "QMI" },
	[QACCESS_MBOX]         = { "MBOX" },
};

static int xgene_qmtm_get_resource_id(u32 *resource, u32 start, u32 end)
{
	u32 index;

	for (index = start; index < end; index++) {
		if ((resource[RES_WORD(index)] & RES_MASK(index)) == 0) {
			resource[RES_WORD(index)] |= RES_MASK(index);
			return index;
		}
	}

	QMTM_PRINT("Out of Resource\n");

	return QMTM_ERR;
}

static void xgene_qmtm_put_resource_id(u32 *resource, u32 index)
{
	resource[RES_WORD(index)] &= ~(u32)RES_MASK(index);
}

static u32 xgene_qmtm_write_pbm(u32 qmtm_ip, u32 slave_id, u32 pbn, u32 val)
{

	u32 pbm_addr = OVERWRITE_WR(1) |
			SLVID_PBN_WR((slave_id << SLAVE_ID_SHIFT) | pbn);

	xgene_qmtm_wr32(qmtm_ip, CSR_PBM_ADDR, pbm_addr);

#ifndef CONFIG_SHADOWCAT
	if (qmtm_ip == QMTM0 || qmtm_ip == QMTM2)
		val |= PB_SIZE_WR(1);
#endif

	xgene_qmtm_wr32(qmtm_ip, CSR_PBM_BUF_WR_ADDR, val);
	QMTM_CORE_PRINT("PBM WR Addr: 0x%08X val: 0x%08X\n", pbm_addr, val);

	return val;
}

static u32 xgene_qmtm_read_pbm(u32 qmtm_ip, u32 slave_id, u32 pbn)
{
	u32 val = 0;
	u32 pbm_addr = SLVID_PBN_WR((slave_id << SLAVE_ID_SHIFT) | pbn);

	xgene_qmtm_wr32(qmtm_ip, CSR_PBM_ADDR, pbm_addr);
	xgene_qmtm_rd32(qmtm_ip, CSR_PBM_BUF_RD_ADDR, &val);
	QMTM_CORE_PRINT("PBM RD Addr: 0x%08X val: 0x%08X\n", pbm_addr, val);

	return val;
}

static void xgene_qmtm_set_pb(struct xgene_qmtm_qinfo *qinfo)
{
	u16 qmtm_ip = qinfo->qmtm_ip;
	u16 slave_id = qinfo->slave_id;
	u16 pbn = qinfo->pbn;
	u16 is_fp = qinfo->qtype == QTYPE_FP ? 1 : 0;
	u16 is_vq = qinfo->qtype == QTYPE_VQ ? 1 : 0;
	u16 queue_id = qinfo->queue_id;
	u32 val = 0;

	val = CORRESPONDING_QNUM_SET(val, queue_id);
	val = IS_FREE_POOL_SET(val, is_fp);
	val = TLVQ_SET(val, is_vq);
	val = PREFETCH_BUF_EN_SET(val, 1);
	val = xgene_qmtm_write_pbm(qmtm_ip, slave_id, pbn, val);
	QMTM_DEBUG_PRINT("SET: QMTM IP %d Slave ID %d PBN %d State: 0x%08X\n",
		qmtm_ip, slave_id, pbn, val);
}

static u32 xgene_qmtm_get_pb(struct xgene_qmtm_qinfo *qinfo)
{
	u16 qmtm_ip = qinfo->qmtm_ip;
	u16 slave_id = qinfo->slave_id;
	u16 pbn = qinfo->pbn;
	u32 val;

	val = xgene_qmtm_read_pbm(qmtm_ip, slave_id, pbn);
	QMTM_DEBUG_PRINT("GET: QMTM IP %d Slave ID %d PBN %d State: 0x%08X\n",
		qmtm_ip, slave_id, pbn, val);

	return val;
}

static void xgene_qmtm_clr_pb(struct xgene_qmtm_qinfo *qinfo)
{
	u16 qmtm_ip = qinfo->qmtm_ip;
	u16 slave_id = qinfo->slave_id;
	u16 pbn = qinfo->pbn;
	u32 val = 0;

	val = xgene_qmtm_write_pbm(qmtm_ip, slave_id, pbn, val);
	QMTM_DEBUG_PRINT("CLR: QMTM IP %d Slave ID %d PBN %d val: 0x%08X\n",
		qmtm_ip, slave_id, pbn, val);
}

static inline void xgene_qmtm_free_qinfo(struct xgene_qmtm_qinfo *qinfo)
{
	MEMFREE(qinfo->qstate);
	MEMFREE(qinfo);
}

void xgene_qmtm_read_qstate(u8 qmtm_ip, u16 queue_id, void *qstate)
{
	pdev->read_qstate(qmtm_ip, queue_id, qstate);
}

int xgene_qmtm_set_qinfo(struct xgene_qmtm_qinfo *set)
{
	struct xgene_qmtm_dev *dev;
	struct xgene_qmtm_sdev *sdev;
	struct xgene_qmtm_qinfo *qinfo;
	u32 *queue_resource = NULL, *pbn_resource = NULL;
	int rc = -ENODEV;
	u8 slave = set->slave;
	u8 qmtm_ip;
	u8 slave_id;
	u8 pbn = 0;
	u16 queue_id = 0;

	if (slave < 0 || slave >= SLAVE_MAX) {
		QMTM_PRINT("SETQ: Slave %d doesn't exist\n", slave);
		goto _ret_set_qinfo;
	}

	if (!pdev || !pdev->sdev[slave]) {
		QMTM_PRINT("SETQ: Slave %d not initialize\n", slave);
		goto _ret_set_qinfo;
	}


	if (set->qtype != QTYPE_PQ && set->qtype != QTYPE_FP) {
		QMTM_PRINT("SETQ: Queue Type %d not supported\n", set->qtype);
		goto _ret_set_qinfo;
	}

	if (set->qsize < QSIZE_512B || set->qsize > QSIZE_512KB) {
		QMTM_PRINT("SETQ: Queue Size %d not supported\n", set->qsize);
		goto _ret_set_qinfo;
	}

	sdev = pdev->sdev[slave];
	qmtm_ip = sdev->qmtm_ip;
	slave_id = sdev->slave_id;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("SETQ: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_set_qinfo;
	}

	if (!pdev->dev[qmtm_ip]) {
		QMTM_PRINT("SETQ: QMTM %d not initialize\n", qmtm_ip);
		goto _ret_set_qinfo;
	}

	if (set->flags & XGENE_SLAVE_PB_CONFIGURE) {
		u8 pbn_start, pbn_count;

		if (set->qtype == QTYPE_FP) {
			pbn_resource = &sdev->fq_pbn_pool;
			pbn_start = sdev->fq_pbn_start;
			pbn_count = sdev->fq_pbn_count;
		} else {
			pbn_resource = &sdev->wq_pbn_pool;
			pbn_start = sdev->wq_pbn_start;
			pbn_count = sdev->wq_pbn_count;
		}
		rc = xgene_qmtm_get_resource_id(pbn_resource, pbn_start,
			pbn_start + pbn_count);

		if (rc == QMTM_ERR) {
			QMTM_PRINT("SETQ: %a out of PBN\n",
				slave_s[slave].name);
			rc = -ENODEV;
			goto _ret_set_qinfo;
		}

		pbn = rc;
	}

	dev = pdev->dev[qmtm_ip];
	queue_resource = dev->queue_pool;
	rc = xgene_qmtm_get_resource_id(queue_resource, 0, dev->qmtm_max_queues);

	if (rc == QMTM_ERR) {
		QMTM_PRINT("SETQ: QMTM %d out of Queue ID\n", qmtm_ip);
		rc = -ENODEV;
		goto _put_pbn_resource;
	}

	queue_id = rc;
	qinfo = pdev->alloc_qinfo();

	if (qinfo == NULL) {
		QMTM_PRINT("SETQ: Unable to allocate qinfo\n");
		rc = -ENOMEM;
		goto _put_queue_resource;
	}

	qinfo->slave = slave;
	qinfo->qtype = set->qtype;
	qinfo->qsize = set->qsize;
	qinfo->qaccess = set->qaccess;
	qinfo->flags = set->flags;
	qinfo->qmtm_ip = qmtm_ip;
	qinfo->slave_id = slave_id;
	qinfo->pbn = (set->qtype == QTYPE_FP) ? (pbn | 0x20) : pbn;
	qinfo->queue_id = queue_id;
	qinfo->queue_paddr = set->queue_paddr;
	qinfo->qfabric = dev->qmtm_fabric_vaddr + (queue_id << Q_SHIFT);
	rc = pdev->set_qstate(qinfo);

	if (rc != QMTM_OK) {
		QMTM_PRINT("SETQ: Unable to configure qstate for %a "
			"Queue ID %d\n", slave_s[slave].name, queue_id);
		goto _del_qstate;
	}

	if (qinfo->qaccess == QACCESS_ALT)
		qinfo->command = qinfo->qfabric + 0x2C;

	if (set->flags & XGENE_SLAVE_PB_CONFIGURE) {
		xgene_qmtm_set_pb(qinfo);

		if (set->qaccess == QACCESS_ALT &&
				slave_id == QMTM_SLAVE_ID_CPU &&
				set->qtype == QTYPE_PQ) {
			u32 data;

			xgene_qmtm_rd32(qmtm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR,
				&data);
			data |= (u32)(1 << (31 - pbn));
			xgene_qmtm_wr32(qmtm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR,
				data);
		}

		if (set->qtype == QTYPE_PQ &&
				(slave_id == QMTM_SLAVE_ID_CPU ||
				slave_id == QMTM_SLAVE_ID_MSLIM)) {
			qinfo->irq = dev->dequeue_irq[pbn];
		}
	}

	dev->qinfo[queue_id] = qinfo;
	memcpy(set, qinfo, sizeof(struct xgene_qmtm_qinfo));
	set->qstate = NULL;
	return rc;

_del_qstate:
	pdev->clr_qstate(qinfo);
	xgene_qmtm_free_qinfo(qinfo);

_put_queue_resource:
	xgene_qmtm_put_resource_id(queue_resource, queue_id);

_put_pbn_resource:
	if (set->flags & XGENE_SLAVE_PB_CONFIGURE)
		xgene_qmtm_put_resource_id(pbn_resource, pbn);

_ret_set_qinfo:
	return rc;
}

int xgene_qmtm_get_qinfo(struct xgene_qmtm_qinfo *get)
{
	int rc = -ENODEV;
	u8 qmtm_ip = get->qmtm_ip;
	u8 queue_id = get->queue_id;
	struct xgene_qmtm_qinfo *qinfo;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("GETQ: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_get_qinfo;
	}

	if (!pdev || !(pdev->dev[qmtm_ip])) {
		QMTM_PRINT("GETQ: QMTM %d not initialize\n", qmtm_ip);
		goto _ret_get_qinfo;
	}

	if (queue_id >= pdev->dev[qmtm_ip]->qmtm_max_queues) {
		QMTM_PRINT("GETQ: Queue ID %d out of range\n", queue_id);
		goto _ret_get_qinfo;
	}

	qinfo = pdev->dev[qmtm_ip]->qinfo[queue_id];

	if (qinfo == NULL) {
		QMTM_PRINT("GETQ: Queue ID %d does not exist\n", queue_id);
		goto _ret_get_qinfo;
	}

	pdev->get_qstate(qinfo);
	memcpy(get, qinfo, sizeof(struct xgene_qmtm_qinfo));
	get->qstate = NULL;

	if (qinfo->flags & XGENE_SLAVE_PB_CONFIGURE)
		get->pbm_state = xgene_qmtm_get_pb(qinfo);
	rc = QMTM_OK;

_ret_get_qinfo:
	return rc;
}

int xgene_qmtm_clr_qinfo(struct xgene_qmtm_qinfo *clr)
{
	int rc = -ENODEV;
	u8 qmtm_ip = clr->qmtm_ip;
	u8 queue_id = clr->queue_id;
	struct xgene_qmtm_qinfo *qinfo;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("CLRQ: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_clr_qinfo;
	}

	if (!pdev || !pdev->dev[qmtm_ip]) {
		QMTM_PRINT("CLRQ: QMTM %d not initialize\n", qmtm_ip);
		goto _ret_clr_qinfo;
	}

	if (queue_id >= pdev->dev[qmtm_ip]->qmtm_max_queues) {
		QMTM_PRINT("CLRQ: Queue ID %d out of range\n", queue_id);
		goto _ret_clr_qinfo;
	}

	qinfo = pdev->dev[qmtm_ip]->qinfo[queue_id];

	if (qinfo == NULL) {
		QMTM_PRINT("CLRQ: Queue ID %d does not exist\n", queue_id);
		goto _ret_clr_qinfo;
	}

	if (qinfo->flags & XGENE_SLAVE_PB_CONFIGURE) {
		u32 *pbn_resource;
		u8 slave = qinfo->slave;
		u8 qtype = qinfo->qtype;
		u8 pbn = (qtype == QTYPE_FP) ?
			(qinfo->pbn & ~(u8)0x20) :
			qinfo->pbn;

		if (qinfo->qaccess == QACCESS_ALT &&
				qinfo->slave_id == QMTM_SLAVE_ID_CPU &&
				qtype == QTYPE_PQ) {
			u32 data;

			xgene_qmtm_rd32(qmtm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR,
				&data);
			data &= ~(u32)(1 << (31 - pbn));
			xgene_qmtm_wr32(qmtm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR,
				data);
		}

		if (qinfo->qtype == QTYPE_FP)
			pbn_resource = &pdev->sdev[slave]->fq_pbn_pool;
		else
			pbn_resource = &pdev->sdev[slave]->wq_pbn_pool;

		xgene_qmtm_clr_pb(qinfo);
		xgene_qmtm_put_resource_id(pbn_resource, pbn);
	}

	pdev->clr_qstate(qinfo);
	xgene_qmtm_free_qinfo(qinfo);
	xgene_qmtm_put_resource_id(pdev->dev[qmtm_ip]->queue_pool, queue_id);
	pdev->dev[qmtm_ip]->qinfo[queue_id] = NULL;
	rc = QMTM_OK;

_ret_clr_qinfo:
	return rc;
}

struct xgene_qmtm_sdev *xgene_qmtm_set_sdev(const char *name, u8 qmtm_ip,
		u8 wq_pbn_start, u8 wq_pbn_count,
		u8 fq_pbn_start, u8 fq_pbn_count)
{
	struct xgene_qmtm_sdev *sdev = NULL;
	u8 slave, slave_id;

	for (slave = 0; slave < SLAVE_MAX; slave++)
		if (strcmp(name, slave_s[slave].name) == 0)
			break;
	
	if (slave == SLAVE_MAX) {
		QMTM_PRINT("SETS: Slave %a doesn't exist\n", name);
		goto _ret_set_slave;
	}

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("SETS: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_set_slave;
	}

	if (!pdev || !pdev->dev[qmtm_ip]) {
		QMTM_PRINT("SETS: QMTM %d not initialize\n", qmtm_ip);
		goto _ret_set_slave;
	}

	if (pdev->sdev[slave]) {
		QMTM_PRINT("SETS: Slave %a already configured\n", name);
		goto _ret_set_slave;
	}

	if (wq_pbn_start > QMTM_MAX_PBN_ID ||
			(wq_pbn_start + wq_pbn_count) > QMTM_MAX_PBN) {
		QMTM_PRINT("SETS: Invalid wq_pbn_start %d or wq_pbn_count %d\n",
			wq_pbn_start, wq_pbn_count);
		goto _ret_set_slave;
	}

	if (fq_pbn_start > (QMTM_MAX_PBN_ID + 0x20) ||
			(fq_pbn_start + fq_pbn_count) >
			(QMTM_MAX_PBN + 0x20)) {
		QMTM_PRINT("SETS: Invalid fq_pbn_start %d or fq_pbn_count %d\n",
			fq_pbn_start, fq_pbn_count);
		goto _ret_set_slave;
	}

#ifdef CONFIG_SHADOWCAT
	switch (slave) {
	case SLAVE_XGE0:
		slave_id = QMTM_SLAVE_ID_ETH0;
		break;
	case SLAVE_XGE1:
		slave_id = QMTM_SLAVE_ID_ETH1;
		break;
	case SLAVE_CPU_QMTM0:
		slave_id = QMTM_SLAVE_ID_CPU;
		break;
	}
#else
	switch (slave) {
	case SLAVE_ETH0:
	case SLAVE_ETH1:
	case SLAVE_XGE0:
	case SLAVE_XGE2:
	case SLAVE_METH:
		slave_id = QMTM_SLAVE_ID_ETH0;
		break;
	case SLAVE_ETH2:
	case SLAVE_ETH3:
	case SLAVE_XGE1:
	case SLAVE_XGE3:
		slave_id = QMTM_SLAVE_ID_ETH1;
		break;
	case SLAVE_PKTDMA:
		slave_id = QMTM_SLAVE_ID_PKTDMA;
		break;
	case SLAVE_CTX_QMTM0:
	case SLAVE_CTX_QMTM1:
	case SLAVE_CTX_QMTM2:
		slave_id = QMTM_SLAVE_ID_CTX;
		break;
	case SLAVE_SEC:
		slave_id = QMTM_SLAVE_ID_SEC;
		break;
	case SLAVE_CLASS:
		slave_id = QMTM_SLAVE_ID_CLASS;
		break;
	case SLAVE_MSLIM_QMTM0:
	case SLAVE_MSLIM_QMTM1:
	case SLAVE_MSLIM_QMTM2:
	case SLAVE_MSLIM_QMTM3:
		slave_id = QMTM_SLAVE_ID_MSLIM;
		break;
	case SLAVE_PMPRO:
		slave_id = QMTM_SLAVE_ID_PMPRO;
		break;
	case SLAVE_SMPRO_QMTM0:
	case SLAVE_SMPRO_QMTM1:
	case SLAVE_SMPRO_QMTM2:
	case SLAVE_SMPRO_QMTM3:
		slave_id = QMTM_SLAVE_ID_SMPRO;
		break;
	case SLAVE_CPU_QMTM0:
	case SLAVE_CPU_QMTM1:
	case SLAVE_CPU_QMTM2:
	case SLAVE_CPU_QMTM3:
		slave_id = QMTM_SLAVE_ID_CPU;
		break;
	}
#endif

	sdev = MEMALLOC(sizeof(struct xgene_qmtm_sdev), 8);

	if (sdev == NULL)
		goto _ret_set_slave;

	pdev->sdev[slave] = sdev;
	memset(sdev, 0, sizeof(struct xgene_qmtm_sdev));
	sdev->slave = slave;
#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
	sdev->slave_i = SLAVE_MSLIM(qmtm_ip);
#else
	sdev->slave_i = SLAVE_CPU(qmtm_ip);
#endif
	sdev->qmtm_ip = qmtm_ip;
	sdev->slave_id = slave_id;
	sdev->wq_pbn_start = wq_pbn_start;
	sdev->wq_pbn_count = wq_pbn_count;
	sdev->fq_pbn_start = fq_pbn_start & ~0x20;
	sdev->fq_pbn_count = fq_pbn_count;
	sdev->name = slave_s[slave].name;

	QMTM_CORE_PRINT("%a: Slave %d QMTM %d Slave ID %d WQ_PBN 0x%02x "
		" WQ_Count %d FQ_PBN 0x%02x FQ_Count %d\n",
		name, slave, qmtm_ip, slave_id, wq_pbn_start,
		wq_pbn_count, fq_pbn_start, fq_pbn_count);

_ret_set_slave:
	return sdev;
}

int xgene_qmtm_clr_sdev(struct xgene_qmtm_sdev *sdev)
{
	int rc = QMTM_ERR;

	if (!pdev) {
		QMTM_PRINT("CLRS: QMTM pdev not initialize\n");
		goto _ret_clr_slave;
	} else if (!sdev) {
		QMTM_PRINT("CLRS: Slave arg is null\n");
		goto _ret_clr_slave;
	} else {
		u8 slave = sdev->slave;
		u8 qmtm_ip = sdev->qmtm_ip;

		if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
			QMTM_PRINT("CLRS: QMTM %d doesn't exist\n", qmtm_ip);
			goto _ret_clr_slave;
		}
		if (!pdev->dev[qmtm_ip]) {
			QMTM_PRINT("CLRS: QMTM %d not initialize\n", qmtm_ip);
			goto _ret_clr_slave;
		}

		if (slave < 0 || slave >= SLAVE_MAX) {
			QMTM_PRINT("CLRS: Slave %d doesn't exist\n", slave);
			goto _ret_clr_slave;
		}

		if (!pdev->sdev[qmtm_ip]) {
			QMTM_PRINT("CLRS: Slave %d not initialize\n", slave);
			goto _ret_clr_slave;
		}

		if (sdev != pdev->sdev[slave]) {
			QMTM_PRINT("CLRS: Invalid Slave arg\n");
			goto _ret_clr_slave;
		}
	}

	memset(sdev, 0, sizeof(struct xgene_qmtm_sdev));
	MEMFREE(pdev->sdev[sdev->slave]);
	pdev->sdev[sdev->slave] = NULL;
	rc = QMTM_OK;

_ret_clr_slave:
	return rc;
}

static int xgene_qmtm_enable(u32 qmtm_ip)
{
	u32 val;
	int mwait = 0;

	xgene_qmtm_wr32(qmtm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET +
		QM_CLKEN_ADDR, 0x3);
	xgene_qmtm_wr32(qmtm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET +
		QM_SRST_ADDR, 3);
	udelay(1000);
	xgene_qmtm_wr32(qmtm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET +
		QM_SRST_ADDR, 0);
	xgene_qmtm_wr32(qmtm_ip, QM_GLBL_DIAG_CSR_BASE_ADDR_OFFSET +
		QM_CFG_MEM_RAM_SHUTDOWN_ADDR, 0);

	do {
		xgene_qmtm_rd32(qmtm_ip, QM_GLBL_DIAG_CSR_BASE_ADDR_OFFSET +
			QM_CFG_MEM_RAM_SHUTDOWN_ADDR, &val);

		if (mwait++ >= 1000)
			return QMTM_ERR;
	} while (val == QM_CFG_MEM_RAM_SHUTDOWN_DEFAULT);

	switch (qmtm_ip) {
	case QMTM0:
	case QMTM2:
#ifdef QMTM_RECOMBINATION_BUFFER
		xgene_qmtm_rd32(qmtm_ip, CSR_RECOMB_CTRL_0_ADDR, &val);
		val = RECOMB_EN0_SET(val, 1);
		xgene_qmtm_wr32(qmtm_ip, CSR_RECOMB_CTRL_0_ADDR, val);
#endif
		break;
	case QMTM3:
		xgene_qmtm_wr32(QMTM3, CSR_QMLITE_PBN_MAP_0_ADDR, 0x00000000);
		break;
	}

	/* program threshold set 1 and all hysteresis */
	xgene_qmtm_wr32(qmtm_ip, CSR_THRESHOLD0_SET1_ADDR, 100);
	xgene_qmtm_wr32(qmtm_ip, CSR_THRESHOLD1_SET1_ADDR, 200);
	xgene_qmtm_wr32(qmtm_ip, CSR_HYSTERESIS_ADDR, 0xFFFFFFFF);

	/* Enable QPcore and assign error queue */
	val = 0;
	val = QM_ENABLE_SET(val, 1);
	xgene_qmtm_wr32(qmtm_ip, CSR_QM_CONFIG_ADDR, val);

	return QMTM_OK;
}

static void xgene_qmtm_disable(u32 qmtm_ip)
{
	u32 val;

	/* Disable QPcore */
	xgene_qmtm_wr32(qmtm_ip, CSR_QM_CONFIG_ADDR, 0);

	val = QM_RESET_WR(1) | CSR_RESET_WR(1);
	xgene_qmtm_wr32(qmtm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET + QM_SRST_ADDR,
		val);
	val = QM_CLKEN_WR(0) | CSR_CLKEN_WR(0);
	xgene_qmtm_wr32(qmtm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET + QM_CLKEN_ADDR,
		val);
}

int xgene_qmtm_dev_init(u8 qmtm_ip, u16 qmtm_max_queues,
		u64 qmtm_csr_paddr, void *qmtm_csr_vaddr,
		u64 qmtm_fabric_paddr, void *qmtm_fabric_vaddr)
{
	int rc = -ENODEV;
	struct xgene_qmtm_dev *dev;
	u32 malloc_size = (sizeof(struct xgene_qmtm_info *)) * qmtm_max_queues;
	u32 queue_id;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("INIT: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_dev_init;
	}

	if (!pdev) {
		QMTM_PRINT("INIT: QMTM pdev not initialize\n");
		goto _ret_dev_init;
	}

	if (qmtm_max_queues > QMTM_MAX_QUEUES) {
		QMTM_PRINT("INIT: qmtm_max_queues %d out of range\n",
			qmtm_max_queues);
		goto _ret_dev_init;
	}

	if (pdev->dev[qmtm_ip]) {
		QMTM_PRINT("INIT: QMTM %d already configured\n", qmtm_ip);
		goto _ret_dev_init;
	}

	dev = MEMALLOC(sizeof(struct xgene_qmtm_dev), 8);

	if (dev == NULL) {
		rc = -ENOMEM;
		goto _ret_dev_init;
	}

	pdev->dev[qmtm_ip] = dev;
	memset(dev, 0, sizeof(struct xgene_qmtm_dev));
	dev->qmtm_csr_paddr = qmtm_csr_paddr;
	dev->qmtm_csr_vaddr = qmtm_csr_vaddr;
	dev->qmtm_fabric_paddr = qmtm_fabric_paddr;
	dev->qmtm_fabric_vaddr = qmtm_fabric_vaddr;
	dev->qinfo = MEMALLOC(malloc_size, 8);

	if (dev->qinfo == NULL) {
		rc = -ENOMEM;
		goto _free_dev;
	}

	memset(dev->qinfo, 0, malloc_size);
	malloc_size = (((qmtm_max_queues + 31) / 32) * 4);
	dev->queue_pool = MEMALLOC(malloc_size, 8);

	if (dev->queue_pool == NULL) {
		rc = -ENOMEM;
		goto _free_qinfo;
	}

	memset(dev->queue_pool, 0, malloc_size);

	dev->qmtm_ip = qmtm_ip;

	if (xgene_qmtm_enable(qmtm_ip) == QMTM_ERR) {
		rc = -EIO;
		goto _free_queue_pool;
	}

	/* Clear all HW queue state in case they were not de-activated */
	for (queue_id = 0; queue_id < qmtm_max_queues; queue_id++)
		pdev->write_qstate(qmtm_ip, queue_id, dev->qinfo);

	dev->qmtm_max_queues = qmtm_max_queues;

	return QMTM_OK;

_free_queue_pool:
	MEMFREE(dev->queue_pool);

_free_qinfo:
	MEMFREE(dev->qinfo);

	dev->queue_pool = NULL;
	dev->qinfo = NULL;

_free_dev:
	MEMFREE(pdev->dev[qmtm_ip]);
	pdev->dev[qmtm_ip] = NULL;

_ret_dev_init:
	return rc;
}

int xgene_qmtm_dev_exit(u8 qmtm_ip)
{
	int rc = -ENODEV;
	struct xgene_qmtm_dev *dev;
	u16 queue_id;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("EXIT: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_dev_exit;
	}

	if (!pdev || !pdev->dev[qmtm_ip]) {
		QMTM_PRINT("EXIT: QMTM %d not initialize\n", qmtm_ip);
		goto _ret_dev_exit;
	}

	dev = pdev->dev[qmtm_ip];

	for (queue_id = 0; queue_id < dev->qmtm_max_queues; queue_id++) {
		if (dev->qinfo[queue_id]) {
			QMTM_PRINT("QMTM %d Queue ID %d Resource in use\n",
				qmtm_ip, queue_id);
			rc = -EAGAIN;
			goto _ret_dev_exit;
		}
	}

	xgene_qmtm_disable(qmtm_ip);
	dev->qmtm_max_queues = 0;
	MEMFREE(dev->queue_pool);
	MEMFREE(dev->qinfo);
	dev->queue_pool = NULL;
	dev->qinfo = NULL;
	MEMFREE(pdev->dev[qmtm_ip]);
	pdev->dev[qmtm_ip] = NULL;
	rc = QMTM_OK;

_ret_dev_exit:
	return rc;
}

struct xgene_qmtm_pdev *xgene_qmtm_pdev_init(u32 driver_data)
{
	/* QMTM INIT */
	pdev = MEMALLOC(sizeof(struct xgene_qmtm_pdev), 8);

	if (pdev == NULL)
		return NULL;

	memset(pdev, 0, sizeof(struct xgene_qmtm_pdev));

	switch (driver_data) {
	case STORM_QMTM:
	case SHADOWCAT_QMTM:
		storm_qmtm_pdev_init(pdev);
		break;
	default:
		MEMFREE(pdev);
		pdev = NULL;
	}

	xgene_qmtm_msg_pdev(pdev);
	return pdev;
}

struct xgene_qmtm_dev *xgene_qmtm_get_dev(u8 qmtm_ip)
{
	struct xgene_qmtm_dev *dev = NULL;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("GETD: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_get_dev_exit;
	}

	if (!pdev || !pdev->dev[qmtm_ip]) {
		QMTM_PRINT("GETD: QMTM %d not initialize\n", qmtm_ip);
		goto _ret_get_dev_exit;
	}

	dev = pdev->dev[qmtm_ip];

_ret_get_dev_exit:
	return dev;
}

/* If tap is zero then coalescence is off */
int xgene_qmtm_intr_coalesce(u8 qmtm_ip, u8 pbn, u8 tap)
{
	u32 val, offset, mask, shift;

	if (tap < MIN_COAL_TAP || tap > MAX_COAL_TAP)
		return QMTM_ERR;

	if (pbn < QMTM_MIN_PBN_ID || pbn > QMTM_MAX_PBN_ID)
		return QMTM_ERR;

	offset = 4 * (pbn / 8);
	shift = 4 * (7 - (pbn % 8));
	mask = 7 << shift;

	xgene_qmtm_rd32(qmtm_ip, CSR_PBM_CTICK0_ADDR + offset, &val);
	val = (val & ~(u32)mask) | (((u32)tap << shift) & mask);
	xgene_qmtm_wr32(qmtm_ip, CSR_PBM_CTICK0_ADDR + offset, val);

	return QMTM_OK;
}
