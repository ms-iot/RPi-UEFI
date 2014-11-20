/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager Message Source file
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * Author: Ravi Patel <rapatel@apm.com>
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
 * @file xgene_qmtm_msg.c
 *
 */

#ifndef APM_XGENE
#include <misc/xgene/qmtm/xgene_qmtm.h>
#else
#include "../mustang.h"
#include "xgene_qmtm.h"
#endif
#include "xgene_qmtm_core.h"

static struct xgene_qmtm_pdev *pdev = NULL;

void xgene_qmtm_msg_pdev(void *msg_pdev)
{
	pdev = (struct xgene_qmtm_pdev *)msg_pdev;
}

void xgene_qmtm_fp_dealloc_msg(u8 qmtm_ip, u16 queue_id,
		struct xgene_qmtm_msg16 *msg)
{
	struct xgene_qmtm_qinfo *qinfo = pdev->dev[qmtm_ip]->qinfo[queue_id];

	switch (qinfo->qaccess) {
	case QACCESS_ALT:
		{
			u32 qtail = qinfo->qtail;
			u32 count = qinfo->count;
			u8 *tailptr = (u8 *)&qinfo->msg16[qtail];

			memcpy(tailptr, msg, 16);

			if (++qtail == count)
				qtail = 0;

			xgene_qmtm_fab_wr32(qinfo->command, 1);

			qinfo->qtail = qtail;
			break;
		}
	case QACCESS_QMI:
		{
		}
	}
}

void xgene_qmtm_push_msg(u8 qmtm_ip, u16 queue_id, struct xgene_qmtm_msg64 *msg)
{
	struct xgene_qmtm_qinfo *qinfo = pdev->dev[qmtm_ip]->qinfo[queue_id];

	switch (qinfo->qaccess) {
	case QACCESS_ALT:
		{
			u32 qtail = qinfo->qtail;
			u32 count = qinfo->count;
			u8 *tailptr = (u8 *)&qinfo->msg32[qtail];

			memcpy(tailptr, msg, 32);

			if (++qtail == count)
				qtail = 0;

			if (!msg->msg32_1.msg16.NV) {
				xgene_qmtm_fab_wr32(qinfo->command, 1);
			} else {
				memcpy(tailptr + 32, (u8 *)msg + 32, 32);

				if (++qtail == count)
					qtail = 0;

				xgene_qmtm_fab_wr32(qinfo->command, 2);
			}

			qinfo->qtail = qtail;
			break;
		}
	case QACCESS_QMI:
		{
		}
	}
}

int xgene_qmtm_pull_msg(u8 qmtm_ip, u16 queue_id, struct xgene_qmtm_msg64 *msg)
{
	struct xgene_qmtm_qinfo *qinfo = pdev->dev[qmtm_ip]->qinfo[queue_id];

	switch (qinfo->qaccess) {
	case QACCESS_ALT:
		{
			u32 qhead = qinfo->qhead;
			u32 count = qinfo->count;
			u32 *headptr = (u32 *)&qinfo->msg32[qhead];

			if (headptr[EMPTY_SLOT_INDEX] == EMPTY_SLOT)
				return QMTM_ERR;

			memcpy(msg, headptr, 32);
			headptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;

			if (++qhead == count)
				qhead = 0;

			if (!msg->msg32_1.msg16.NV) {
				xgene_qmtm_fab_wr32(qinfo->command, 0xFFFFFFFF);
			} else {
				headptr += 8;

				if (headptr[EMPTY_SLOT_INDEX] == EMPTY_SLOT)
					return QMTM_ERR;

				memcpy((u8 *)msg + 32, headptr, 32);
				headptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;

				if (++qhead == count)
					qhead = 0;

				xgene_qmtm_fab_wr32(qinfo->command, 0xFFFFFFFE);
			}

			qinfo->qhead = qhead;
			break;
		}
	case QACCESS_QMI:
		{
		}
	}

	return QMTM_OK;
}
