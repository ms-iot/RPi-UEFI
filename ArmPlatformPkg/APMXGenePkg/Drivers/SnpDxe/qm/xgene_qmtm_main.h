/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager U-Boot Header file
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
 * @file xgene_qmtm_main.h
 *
 */

#ifndef __XGENE_QMTM_MAIN_H__
#define __XGENE_QMTM_MAIN_H__

#ifndef APM_XGENE
#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm-generic/errno.h>
#else
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;
//#define readl           MmioRead32
//#define writel(v, a)    MmioWrite32((a), (v))
#undef SIZE_2KB
#undef SIZE_16KB
#undef SIZE_64KB
#undef SIZE_512KB
#define QM_INFO
#ifdef QM_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif
#define printf          info
#endif

#define CONFIG_NOT_COHERENT_QMTM

/* Enabled debug macros put here */
#define QMTM_PRINT_ENABLE
#define QMTM_ERROR_PRINT_ENABLE
#undef  QMTM_CORE_PRINT_ENABLE
#undef  QMTM_QSTATE_PRINT_ENABLE
#undef  QMTM_WRITE_PRINT_ENABLE
#undef  QMTM_READ_PRINT_ENABLE
#undef  QMTM_DEBUG_PRINT_ENABLE

#ifdef QMTM_PRINT_ENABLE
#define QMTM_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_PRINT(x, ...)
#endif

#ifdef QMTM_ERROR_PRINT_ENABLE
#define QMTM_ERROR_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_ERROR_PRINT(x, ...)
#endif

#ifdef QMTM_CORE_PRINT_ENABLE
#define QMTM_CORE_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_CORE_PRINT(x, ...)
#endif

#ifdef QMTM_QSTATE_PRINT_ENABLE
#define QMTM_QSTATE_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_QSTATE_PRINT(x, ...)
#endif

#ifdef QMTM_WRITE_PRINT_ENABLE
#define QMTM_WRITE_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_WRITE_PRINT(x, ...)
#endif

#ifdef QMTM_READ_PRINT_ENABLE
#define QMTM_READ_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_READ_PRINT(x, ...)
#endif

#ifdef QMTM_DEBUG_PRINT_ENABLE
#define QMTM_DEBUG_PRINT(x, ...) printf(x, ##__VA_ARGS__)
#else
#define QMTM_DEBUG_PRINT(x, ...)
#endif

/* dummy virt to phys for u-boot */
#define virt_to_phys(x) 	((u64) (unsigned long) (x))
#define phys_to_virt(x) 	((void *) (unsigned long) (x))

#ifdef CONFIG_ARCH_MSLIM
#define CONFIG_NOT_COHERENT_QMTM
#define VIRT_TO_PHYS(x)	mslim_pa_to_iof_axi(virt_to_phys(x))
#define PHYS_TO_VIRT(x)	phys_to_virt(mslim_iof_axi_to_pa(x))
#else
#define VIRT_TO_PHYS(x) virt_to_phys(x)
#define PHYS_TO_VIRT(x) phys_to_virt(x)
#endif

#define BIT(nr)			(1UL << (nr))

void *MEMALLOC(u32 size, u32 align);
void MEMFREE(void *ptr);

/* QMTM raw register read/write routine */
int xgene_qmtm_wr32(u32 qmtm_ip, u32 offset, u32 data);
int xgene_qmtm_rd32(u32 qmtm_ip, u32 offset, u32 *data);

/* QMTM raw register read/write routine */
static inline void xgene_qmtm_fab_wr32(void *addr, u32 data)
{
	//writel(data, (u64)addr);
	MmioWrite32((u64)addr, data);
}

static inline u32 xgene_qmtm_fab_rd32(void *addr)
{
	//return readl((u64)addr);
	return MmioRead32((u64)addr);
}

int xgene_qmtm_main(u8 qmtm_ip);

#endif /* __XGENE_QMTM_MAIN_H__ */
