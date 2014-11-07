/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager Utility Source file
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
 * @file xgene_qmtm_util.c
 *
 */

#ifndef MDEPKG_NDEBUG
#include "xgene_qmtm_util.h"
#define QMTM_DEBUG
#ifdef QMTM_DEBUG
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif
#undef QMTM_PRINT
#define QMTM_PRINT info
#undef QMCORE_PRINT
#define QMCORE_PRINT info

void xgene_qmtm_dump_qconfig(u8 qmtm_ip)
{
	int i;
	struct xgene_qmtm_dev *dev = xgene_qmtm_get_dev(qmtm_ip);

	if (dev == NULL)
		return;

	for (i = 0; i < dev->qmtm_max_queues && dev->qinfo[i]; i++) {
		struct xgene_qmtm_qinfo *qinfo = dev->qinfo[i];

		QMTM_PRINT("Q[%04d]: slave=%-11a pbn=0x%02x "
			"qtype=%a qsize=%-5a qaccess=%-4a\n",
			qinfo->queue_id, slave_s[qinfo->slave].name, qinfo->pbn,
			qtype_s[qinfo->qtype].name, qsize_s[qinfo->qsize].name,
			qaccess_s[qinfo->qaccess].name);
	}
}

int xgene_qmtm_dump_qinfo(struct xgene_qmtm_qinfo *dump)
{
	int rc;

	rc = xgene_qmtm_get_qinfo(dump);

	if (rc != QMTM_OK) {
		QMTM_PRINT("Error %d while dump qinfo for QMTM %d "
			"Queue ID %d\n", rc, dump->qmtm_ip, dump->queue_id);
		return rc;
	}

	QMTM_PRINT("\nThis queue belongs to: QMTM%d\n", dump->qmtm_ip);
	QMTM_PRINT("Queue ID: %d\n", dump->queue_id);
	QMTM_PRINT("Belongs to Slave ID: %d\n", dump->slave_id);
	QMTM_PRINT("Belongs to Prefetch Buffer: 0x%x\n", dump->pbn);
	QMTM_PRINT("This queue is: %a\n", qtype_s[dump->qtype].name);
	QMTM_PRINT("Queue size: %a\n", qsize_s[dump->qsize].name);
	QMTM_PRINT("Queue Physical start address: 0x%llx\n", (unsigned long long)(dump->queue_paddr));
	QMTM_PRINT("Queue Virtual  start address: 0x%p\n", dump->queue_vaddr);
	QMTM_PRINT("Number of message in queue: %d\n", dump->nummsgs);
	QMTM_PRINT("PBM STATE: 0x%08x\n\n", dump->pbm_state);

	return rc;
}

void xgene_qmtm_decode_message(struct xgene_qmtm_msg64 *msg)
{
	struct xgene_qmtm_msg16 *msg16 = &msg->msg32_1.msg16;
	struct xgene_qmtm_msg_up16 *msg_up16 = &msg->msg32_1.msgup16;

	QMTM_PRINT(" FPQNum=0x%x\n", msg16->FPQNum);
#ifdef CONFIG_SHADOWCAT
	QMTM_PRINT(" PType=0x%x\n", msg16->PType);
#else
	QMTM_PRINT(" Rv2=0x%x\n", msg16->Rv2);
#endif
	QMTM_PRINT(" ELErr=0x%x\n", msg16->ELErr);
	QMTM_PRINT(" LEI=0x%x\n", msg16->LEI);
	QMTM_PRINT(" NV=0x%x\n", msg16->NV);

	QMTM_PRINT(" LL=0x%x\n", msg16->LL);
	QMTM_PRINT(" PB=0x%x\n", msg16->PB);
	QMTM_PRINT(" HB=0x%x\n", msg16->HB);
#ifdef CONFIG_SHADOWCAT
	QMTM_PRINT(" AM=0x%x\n", msg16->AM);
#else
	QMTM_PRINT(" Rv=0x%x\n", msg16->Rv);
#endif
	QMTM_PRINT(" In=0x%x\n", msg16->In);
	QMTM_PRINT(" RType=0x%x\n", msg16->RType);
	QMTM_PRINT(" LErr=0x%x\n", msg16->LErr);
	QMTM_PRINT(" HL=0x%x\n", msg16->HL);
	QMTM_PRINT(" DataAddr=0x%04x%08x\n", msg16->DataAddrH, msg16->DataAddrL);
#ifdef CONFIG_SHADOWCAT
	QMTM_PRINT(" VMid=0x%x\n", msg16->VMid);
#else
	QMTM_PRINT(" Rv6=0x%x\n", msg16->Rv6);
#endif
	QMTM_PRINT(" BufDataLen=0x%x\n", msg16->BufDataLen);
	QMTM_PRINT(" C=0x%x\n", msg16->C);

	QMTM_PRINT(" H0Info_msb=0x%04x%08x\n", msg_up16->H0Info_msbH, msg_up16->H0Info_msbL);
	QMTM_PRINT(" TotDataLengthLinkListLSBs=0x%x\n", msg_up16->TotDataLengthLinkListLSBs);
#ifdef CONFIG_SHADOWCAT
	QMTM_PRINT(" HFPSel_msb=0x%x\n", msg_up16->HFPSel_msb);
#else
	QMTM_PRINT(" Rv1=0x%x\n", msg_up16->Rv1);
#endif
	QMTM_PRINT(" DR=0x%x\n", msg_up16->DR);
	QMTM_PRINT(" Rv0=0x%x\n", msg_up16->Rv0);
	QMTM_PRINT(" HR=0x%x\n", msg_up16->HR);
	QMTM_PRINT(" H0Info_lsb=0x%04x%08x\n", msg_up16->H0Info_lsbH, msg_up16->H0Info_lsbL);
	QMTM_PRINT(" H0Enq_Num=0x%x\n", msg_up16->H0Enq_Num);
	QMTM_PRINT(" H0FPSel=0x%x\n", msg_up16->H0FPSel);
}

int xgene_qmtm_fp_dealloc_msg_util(u32 qmtm_ip, u16 queue_id,
		struct xgene_qmtm_msg16 *msg)
{
	struct xgene_qmtm_msg16 msg16;
	u32 *word_msg = (u32 *)msg ?: (u32 *)&msg16;
	static u32 UserInfo = 0;

	if (msg == NULL) {
		msg16.BufDataLen = 3;
		msg16.DataAddrL = 0x0d00ffff;
		msg16.UserInfo = ++UserInfo;
		msg16.FPQNum = queue_id;
	}

	xgene_qmtm_fp_dealloc_msg(qmtm_ip, queue_id, (struct xgene_qmtm_msg16 *)word_msg);

	return QMTM_OK;
}

int xgene_qmtm_push_msg_util(u8 qmtm_ip, u16 queue_id,
		struct xgene_qmtm_msg64 *msg)
{
	struct xgene_qmtm_msg32 msg32;
	u32 *word_msg = (u32 *)msg ?: (u32 *)&msg32;
	static u32 UserInfo = 0;

	if (msg == NULL) {
		msg32.msg16.BufDataLen = 3;
		msg32.msg16.DataAddrL = 0x0d00ffff;
		msg32.msg16.UserInfo = ++UserInfo;
	}

	xgene_qmtm_push_msg(qmtm_ip, queue_id, (struct xgene_qmtm_msg64 *)word_msg);

	return QMTM_OK;
}

int xgene_qmtm_pull_msg_util(u8 qmtm_ip, u16 queue_id)
{
	struct xgene_qmtm_msg32 msg;
	u32 *word_msg = (u32 *)&msg;
	int i;

	if (xgene_qmtm_pull_msg(qmtm_ip, queue_id,
			(struct xgene_qmtm_msg64 *)&msg))
		return QMTM_OK;

	for (i = 0; i < 4; i++)
		QMTM_PRINT("READ MSG: %x\n", *word_msg++);

	xgene_qmtm_decode_message((struct xgene_qmtm_msg64 *)&msg);

	return QMTM_OK;
}

int xgene_qmtm_create_lpq(struct xgene_qmtm_qinfo *qinfo)
{
	int rc;
	u8  qmtm_ip = qinfo->qmtm_ip;

#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
	qinfo->slave = SLAVE_MSLIM(qmtm_ip);
	qinfo->qaccess = QACCESS_QMI;
#else
	qinfo->slave = SLAVE_CPU(qmtm_ip);
	qinfo->qaccess = QACCESS_ALT;
#endif
	qinfo->qtype = QTYPE_PQ;
	qinfo->qsize = QSIZE_512B;

	if (qmtm_ip == QMTM3)
		qinfo->flags = XGENE_SLAVE_Q_ADDR_ALLOC;
	else
		qinfo->flags = XGENE_SLAVE_DEFAULT_FLAGS;

	if ((rc = xgene_qmtm_set_qinfo(qinfo)) != QMTM_OK)
		QMTM_PRINT("Error allocating LoopBack queue\n");
	else
		QMTM_PRINT("Created LoopBack queue id: %d\n", qinfo->queue_id);

	return rc;
}
#endif
