/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager U-Boot Source file
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
 * @file xgene_qmtm_main.c
 *
 */

#ifndef APM_XGENE
#include <misc/xgene/qmtm/xgene_qmtm.h>
#include <malloc.h>
#else
#include "../mustang.h"
#include "xgene_qmtm.h"
#include "xgene_qmtm_core.h"
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>

#undef CONFIG_NOT_COHERENT_QM

#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define printf          info
#define malloc AllocateZeroPool
#define free FreePool

#endif

static struct xgene_qmtm_pdev *pdev = NULL;

void *MEMALLOC(u32 size, u32 align)
{
	u64 ptr = (u64)malloc(size + align);
	u64 mask = 0xFFFFFFFFFFFFFFFFULL - (align - 1);

	if (ptr & ~mask) {
		ptr &= mask;
		ptr += align;
	}

	return (void *)ptr;
}

void MEMFREE(void *ptr)
{
	free(ptr);
}

/* QM raw register read/write routine */
int xgene_qmtm_wr32(u32 qmtm_ip, u32 offset, u32 data)
{
	void *addr = (u8 *)pdev->dev[qmtm_ip]->qmtm_csr_vaddr + offset;

	QMTM_WRITE_PRINT("Write addr 0x%p data 0x%08x\n", addr, data);
	//writel(data, (u64)addr);
	MmioWrite32((u64)addr, data);

	return QMTM_OK;
}

int xgene_qmtm_rd32(u32 qmtm_ip, u32 offset, u32 *data)
{
	void *addr = (u8 *)pdev->dev[qmtm_ip]->qmtm_csr_vaddr + offset;

	//*data = readl((u64)addr);
	*data = MmioRead32((u64)addr);
	QMTM_READ_PRINT("Read addr 0x%p data %08X\n", addr, *data);

	return QMTM_OK;
}

int xgene_qmtm_main(u8 qmtm_ip)
{
	u64 qmtm_csr_paddr = 0, qmtm_fabric_paddr = 0;
	void *qmtm_csr_vaddr = NULL, *qmtm_fabric_vaddr = NULL;
	int rc = QMTM_OK;
	char name[16];
	u16 qmtm_max_queues = 0;
	u8 wq_pbn_start = 0, wq_pbn_count = 0;

	if (qmtm_ip < QMTM0 || qmtm_ip > QMTM3) {
		QMTM_PRINT("MAIN: QMTM %d doesn't exist\n", qmtm_ip);
		goto _ret_qmtm_main;
	}

	if (pdev == NULL)
		pdev = xgene_qmtm_pdev_init(STORM_QMTM);

	if (pdev == NULL) {
		QMTM_PRINT("MAIN: QMTM pdev error\n");
		rc = QMTM_ERR;
		goto _ret_qmtm_main;
	}

	if (pdev->dev[qmtm_ip])
		goto _ret_qmtm_main;

	switch (qmtm_ip) {
	case QMTM0:
		qmtm_csr_paddr = CONFIG_SYS_QM0_CSR_BASE;
		qmtm_csr_vaddr = (void *)CONFIG_SYS_QM0_CSR_BASE;
		qmtm_fabric_paddr = CONFIG_SYS_QM0_FABRIC_BASE;
		qmtm_fabric_vaddr = (void *)CONFIG_SYS_QM0_FABRIC_BASE;
#ifdef CONFIG_MSLIM
		wq_pbn_start = 0;
		wq_pbn_count = 5;
#else
		wq_pbn_start = 0;
		wq_pbn_count = 6;
#endif
		qmtm_max_queues = 10;
		break;
#ifndef CONFIG_SHADOWCAT
	case QMTM1:
		qmtm_csr_paddr = CONFIG_SYS_QM1_CSR_BASE;
		qmtm_csr_vaddr = (void *)CONFIG_SYS_QM1_CSR_BASE;
		qmtm_fabric_paddr = CONFIG_SYS_QM1_FABRIC_BASE;
		qmtm_fabric_vaddr = (void *)CONFIG_SYS_QM1_FABRIC_BASE;
#ifdef CONFIG_MSLIM
		wq_pbn_start = 5;
		wq_pbn_count = 5;
#else
		wq_pbn_start = 0;
		wq_pbn_count = 10;
#endif
		qmtm_max_queues = 18;
		break;
	case QMTM2:
		qmtm_csr_paddr = CONFIG_SYS_QM2_CSR_BASE;
		qmtm_csr_vaddr = (void *)CONFIG_SYS_QM2_CSR_BASE;
		qmtm_fabric_paddr = CONFIG_SYS_QM2_FABRIC_BASE;
		qmtm_fabric_vaddr = (void *)CONFIG_SYS_QM2_FABRIC_BASE;
#ifdef CONFIG_MSLIM
		wq_pbn_start = 10;
		wq_pbn_count = 5;
#else
		wq_pbn_start = 16;
		wq_pbn_count = 6;
#endif
		qmtm_max_queues = 10;
		break;
	case QMTM3:
		qmtm_csr_paddr = CONFIG_SYS_QML_CSR_BASE;
		qmtm_csr_vaddr = (void *)CONFIG_SYS_QML_CSR_BASE;
		qmtm_fabric_paddr = CONFIG_SYS_QML_FABRIC_BASE;
		qmtm_fabric_vaddr = (void *)CONFIG_SYS_QML_FABRIC_BASE;
#ifdef CONFIG_MSLIM
		wq_pbn_start = 15;
		wq_pbn_count = 1;
#else
		wq_pbn_start = 0;
		wq_pbn_count = 1;
#endif
		qmtm_max_queues = 6;
		break;
#endif
	}

	if (xgene_qmtm_dev_init(qmtm_ip, qmtm_max_queues,
			qmtm_csr_paddr, qmtm_csr_vaddr,
			qmtm_fabric_paddr, qmtm_fabric_vaddr) != QMTM_OK)
		goto _ret_qmtm_main;

#ifdef CONFIG_MSLIM
	snprintf(name, sizeof(name), "MSLIM_QMTM%d", qmtm_ip);
#else
	AsciiSPrint(name, sizeof(name),  "CPU_QMTM%d\n", qmtm_ip);
	name[AsciiStrLen(name) - 2] = 0;
#endif
	if (xgene_qmtm_set_sdev(name, qmtm_ip, wq_pbn_start, wq_pbn_count,
			0, 0) == NULL)
		rc = QMTM_ERR;

_ret_qmtm_main:
	return rc;
}
