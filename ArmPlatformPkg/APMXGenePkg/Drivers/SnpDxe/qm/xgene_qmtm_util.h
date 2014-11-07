/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager Utility Header file
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
 * @file xgene_qmtm_util.h
 *
 */

#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>


#include "xgene_qmtm_core.h"
#ifndef APM_XGENE
#include <misc/xgene/qmtm/xgene_qmtm.h>
#else
#include "xgene_qmtm.h"
#endif

void xgene_qmtm_dump_qconfig(u8 qmtm_ip);

int xgene_qmtm_dump_qinfo(struct xgene_qmtm_qinfo *qinfo);

void xgene_qmtm_decode_message(struct xgene_qmtm_msg64 *msg);

int xgene_qmtm_fp_dealloc_msg_util(u32 qmtm_ip, u16 queue_id,
		struct xgene_qmtm_msg16 *msg);

int xgene_qmtm_push_msg_util(u8 qmtm_ip, u16 queue_id,
		struct xgene_qmtm_msg64 *msg);

int xgene_qmtm_pull_msg_util(u8 qmtm_ip, u16 queue_id);

int xgene_qmtm_create_lpq(struct xgene_qmtm_qinfo *qinfo);
