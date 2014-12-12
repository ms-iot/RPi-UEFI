/**
 * AppliedMicro X-Gene Storm SOC Queue Manager Traffic Manager Source file
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * Author: Ravi Patel <rapatel@apm.com>
 *         Keyur Chudgar <kchudgar@apm.com>
 *         Fushen Chen <fchen@apm.com>
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
 * @file xgene_qmtm_storm.c
 *
 */
typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;

#include "../mustang.h"
#include "xgene_qmtm.h"
#include "xgene_qmtm_core.h"
#include "xgene_qmtm_storm.h"
#ifdef CONFIG_SHADOWCAT
#include "xgene_qmtm_shadowcat_csr.h"
#else
#include "xgene_qmtm_csr.h"
#endif
#ifndef APM_XGENE
#include <misc/xgene/qmtm/xgene_qmtm.h>
#ifdef CONFIG_ARCH_MSLIM
#include <asm/hardware/mslim-iof-map.h>
#endif
#endif

static struct xgene_qmtm_qinfo *storm_qmtm_alloc_qinfo(void)
{
	struct xgene_qmtm_qinfo *qinfo = MEMALLOC(sizeof(struct xgene_qmtm_qinfo), 8);

	if (qinfo == NULL)
		return NULL;

	memset(qinfo, 0, sizeof(struct xgene_qmtm_qinfo));
	qinfo->qstate = MEMALLOC(sizeof(union storm_qmtm_qstate), 8);

	if (qinfo->qstate == NULL) {
		MEMFREE(qinfo);
		return NULL;
	}

	memset(qinfo->qstate, 0, sizeof(union storm_qmtm_qstate));

	return qinfo;
}

static void storm_qmtm_write_qstate(u8 qmtm_ip, u16 queue_id, void *qstate)
{

	struct storm_qmtm_csr_qstate *csr_qstate =
		&((union storm_qmtm_qstate *)qstate)->csr;

#ifdef CONFIG_SHADOWCAT
        QMTM_QSTATE_PRINT("QState WR QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
	queue_id, csr_qstate->w0, csr_qstate->w1, csr_qstate->w2, csr_qstate->w3, 
	csr_qstate->w4, csr_qstate->w5);

#else
	QMTM_QSTATE_PRINT("QState WR QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
		queue_id, csr_qstate->w0, csr_qstate->w1, csr_qstate->w2,
	       	csr_qstate->w3, csr_qstate->w4);
#endif
	/* write queue number */
	queue_id = QNUMBER_WR(queue_id);
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_ADDR, (u32)queue_id);
	/* write queue state */
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_WR_0_ADDR, csr_qstate->w0);
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_WR_1_ADDR, csr_qstate->w1);
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_WR_2_ADDR, csr_qstate->w2);
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_WR_3_ADDR, csr_qstate->w3);
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_WR_4_ADDR, csr_qstate->w4);
#ifdef CONFIG_SHADOWCAT
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_WR_5_ADDR, csr_qstate->w5);
#endif
}

static void storm_qmtm_read_qstate(u8 qmtm_ip, u16 queue_id, void *qstate)
{
#ifdef QSTATE_READ_CSR
	struct storm_qmtm_csr_qstate *csr_qstate =
		&((union storm_qmtm_qstate *)qstate)->csr;

	/* write queue number */
	queue_id = QNUMBER_WR(queue_id);
	xgene_qmtm_wr32(qmtm_ip, CSR_QSTATE_ADDR, (u32)queue_id);
	/* read queue state */
	xgene_qmtm_rd32(qmtm_ip, CSR_QSTATE_RD_0_ADDR, &csr_qstate->w0);
	xgene_qmtm_rd32(qmtm_ip, CSR_QSTATE_RD_1_ADDR, &csr_qstate->w1);
	xgene_qmtm_rd32(qmtm_ip, CSR_QSTATE_RD_2_ADDR, &csr_qstate->w2);
	xgene_qmtm_rd32(qmtm_ip, CSR_QSTATE_RD_3_ADDR, &csr_qstate->w3);
	xgene_qmtm_rd32(qmtm_ip, CSR_QSTATE_RD_4_ADDR, &csr_qstate->w4);
#ifdef CONFIG_SHADOWCAT
	xgene_qmtm_rd32(qmtm_ip, CSR_QSTATE_RD_5_ADDR, &csr_qstate->w5);
        QMTM_QSTATE_PRINT("QState RD QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
	queue_id, csr_qstate->w0, csr_qstate->w1, csr_qstate->w2,
	csr_qstate->w3, csr_qstate->w4, csr_qstate->w5);

#else
	QMTM_QSTATE_PRINT("QState RD QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
		queue_id, csr_qstate->w0, csr_qstate->w1, csr_qstate->w2,
	       	csr_qstate->w3, csr_qstate->w4);
#endif
#else
	struct xgene_qmtm_dev *dev = xgene_qmtm_get_dev(qmtm_ip);
	struct storm_qmtm_csr_qstate *qfabric =
		(struct storm_qmtm_csr_qstate *)
		(dev->qmtm_fabric_vaddr + (queue_id << Q_SHIFT));
	struct storm_qmtm_csr_qstate *csr_qstate =
		&((union storm_qmtm_qstate *)qstate)->csr;

	/* read queue state */
	csr_qstate->w0 = xgene_qmtm_fab_rd32(&qfabric->w0);
	csr_qstate->w1 = xgene_qmtm_fab_rd32(&qfabric->w1);
	csr_qstate->w2 = xgene_qmtm_fab_rd32(&qfabric->w2);
	csr_qstate->w3 = xgene_qmtm_fab_rd32(&qfabric->w3);
	csr_qstate->w4 = xgene_qmtm_fab_rd32(&qfabric->w4);
#ifdef CONFIG_SHADOWCAT
	csr_qstate->w5 = xgene_qmtm_fab_rd32(&qfabric->w5);
        QMTM_QSTATE_PRINT("QState RD QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
	queue_id, csr_qstate->w0, csr_qstate->w1, csr_qstate->w2,
	csr_qstate->w3, csr_qstate->w4, csr_qstate->w5);

#else
	QMTM_QSTATE_PRINT("QState RD QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
		queue_id, csr_qstate->w0, csr_qstate->w1, csr_qstate->w2,
	       	csr_qstate->w3, csr_qstate->w4);
#endif
#endif
}

static int storm_qmtm_set_qstate(struct xgene_qmtm_qinfo *qinfo)
{
	int rc = QMTM_ERR;
	struct storm_qmtm_pq_fp_qstate *pq_fp =
		&((union storm_qmtm_qstate *)(qinfo->qstate))->pq;
	u64 cfgstartaddr;
	u32 qsize = 0;
	u8  qtype = qinfo->qtype;

	if (qtype != QTYPE_PQ && qtype != QTYPE_FP) {
		QMTM_PRINT("Queue type %d not supported\n", qinfo->qtype);
		goto _ret_set_qstate;
	}

	pq_fp->cfgqtype = qinfo->qtype;
#ifdef CONFIG_SHADOWCAT
	/* No address translation for queues and messages */
	pq_fp->QBase_AM = 1;
	pq_fp->Msg_AM = 1;
#endif

	/* if its a free queue, ask QMTM to set len to 0 when dealloc */
	if (qtype == QTYPE_FP)
		pq_fp->fp_mode = CHANGE_LEN;

#ifdef QMTM_RECOMBINATION_BUFFER
	if (qinfo->slave >= SLAVE_XGE0 &&
			qinfo->slave <= SLAVE_XGE3) {
		pq_fp->cfgRecombBuf = 1;
		pq_fp->cfgRecombBufTimeoutL = 0xf;
		pq_fp->cfgRecombBufTimeoutH = 0x7;
	}
#endif

	pq_fp->cfgselthrsh = 1;
	/*
	 *  Ethernet can generate LError (checksum error) for fragment packet,
	 *  we must allow the queue to accept message with non-zero LErr.
	 */
	pq_fp->cfgacceptlerr = 1;
	pq_fp->qcoherent = xgene_qmtm_coherent();

	switch (qinfo->qsize) {
	case QSIZE_512B:
		qsize = 512;
		break;
	case QSIZE_2KB:
		qsize = 2 * 1024;
		break;
	case QSIZE_16KB:
		qsize = 16 * 1024;
		break;
	case QSIZE_64KB:
		qsize = 64 * 1024;
		break;
	case QSIZE_512KB:
		qsize = 512 * 1024;
		break;
	default:
		QMTM_PRINT("Queue size %d is invalid\n", qinfo->qsize);
		goto _ret_set_qstate;
	}

	qinfo->count = (qtype == QTYPE_PQ) ? (qsize / 32) : (qsize / 16);

	if (qinfo->flags & XGENE_SLAVE_Q_ADDR_ALLOC) {
		qinfo->queue_vaddr = MEMALLOC(qsize, 256);

		if (qinfo->queue_vaddr == NULL) {
			QMTM_PRINT("Queue qsize 0x%x malloc failed\n", qsize);
			goto _ret_set_qstate;
		}

		qinfo->queue_paddr = (u64)VIRT_TO_PHYS(qinfo->queue_vaddr);
	} else {
		qinfo->queue_vaddr = PHYS_TO_VIRT(qinfo->queue_paddr);
	}

	memset(qinfo->queue_vaddr, 0, qsize);

	if ((qtype == QTYPE_PQ) && (qinfo->slave_id == QMTM_SLAVE_ID_CPU ||
			qinfo->slave_id == QMTM_SLAVE_ID_MSLIM)) {
		u32 i;

		for (i = 0; i < qinfo->count; i++) {
			u32 *slot = (u32 *)&qinfo->msg32[i];

			slot[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
		}
	}

	cfgstartaddr = qinfo->queue_paddr >> 8;
	pq_fp->cfgstartaddrL = (u32)(cfgstartaddr & (BIT(27) - 1));
	pq_fp->cfgstartaddrH = (u32)(cfgstartaddr >> 27);
	pq_fp->cfgqsize = qinfo->qsize;
#ifdef L3_STASHING
	pq_fp->stashing = 1;
#endif

	QMTM_CORE_PRINT("Queue PAddr 0x%llx VAddr 0x%p QAddr 0x%llx\n",
		(u64)qinfo->queue_paddr, qinfo->queue_vaddr, cfgstartaddr);
	QMTM_CORE_PRINT("QMTM_IP %d QID %d cfgqtype %d cfgselthrsh %d cfgqsize %d fp_mode %d\n",
		qinfo->qmtm_ip, qinfo->queue_id, pq_fp->cfgqtype, pq_fp->cfgselthrsh, pq_fp->cfgqsize, pq_fp->fp_mode);
	QMTM_CORE_PRINT("QMTM_IP %d QID %d cfgacceptlerr %d cfgstartaddr 0x%llx\n",
		qinfo->qmtm_ip, qinfo->queue_id, pq_fp->cfgacceptlerr, cfgstartaddr);
	QMTM_CORE_PRINT("QMTM_IP %d QID %d cfgsaben %d cfgtmvq %d cfgtmvqen %d\n",
		qinfo->qmtm_ip, qinfo->queue_id, pq_fp->cfgsaben, pq_fp->cfgtmvq, pq_fp->cfgtmvqen);

	QMTM_CORE_PRINT("PQ/FQueue configuration\n");
	QMTM_CORE_PRINT("QMTMIP blk: %d\n", qinfo->qmtm_ip);
	QMTM_CORE_PRINT("  Slave ID: %d\n", qinfo->slave_id);
	QMTM_CORE_PRINT("       PBN: %d\n", qinfo->pbn);
	QMTM_CORE_PRINT("  Queue ID: %d\n", qinfo->queue_id);
	QMTM_CORE_PRINT("Queue Type: %d\n", qinfo->qtype);
	storm_qmtm_write_qstate(qinfo->qmtm_ip, qinfo->queue_id, qinfo->qstate);
	rc = QMTM_OK;

_ret_set_qstate:
	return rc;
}

static void storm_qmtm_get_qstate(struct xgene_qmtm_qinfo *qinfo)
{
	struct storm_qmtm_pq_fp_qstate *pq_fp =
		&((union storm_qmtm_qstate *)(qinfo->qstate))->pq;

	storm_qmtm_read_qstate(qinfo->qmtm_ip, qinfo->queue_id, qinfo->qstate);
	qinfo->nummsgs = pq_fp->nummsg;
}

static void storm_qmtm_clr_qstate(struct xgene_qmtm_qinfo *qinfo)
{
	memset(qinfo->qstate, 0, sizeof(union storm_qmtm_qstate));
	storm_qmtm_write_qstate(qinfo->qmtm_ip, qinfo->queue_id,
		qinfo->qstate);

	if (qinfo->flags & XGENE_SLAVE_Q_ADDR_ALLOC &&
			qinfo->queue_vaddr) {
		MEMFREE(qinfo->queue_vaddr);
		qinfo->queue_vaddr = NULL;
	}
}

void storm_qmtm_pdev_init(struct xgene_qmtm_pdev *pdev)
{
	pdev->alloc_qinfo = storm_qmtm_alloc_qinfo;
	pdev->write_qstate = storm_qmtm_write_qstate;
	pdev->read_qstate = storm_qmtm_read_qstate;
	pdev->set_qstate = storm_qmtm_set_qstate;
	pdev->get_qstate = storm_qmtm_get_qstate;
	pdev->clr_qstate = storm_qmtm_clr_qstate;
}
