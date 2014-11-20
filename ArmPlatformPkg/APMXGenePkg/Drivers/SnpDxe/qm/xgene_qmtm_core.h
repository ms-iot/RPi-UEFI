/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager Core Header file
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
 * @file xgene_qmtm_core.h
 *
 */

#ifndef __XGENE_QMTM_CORE_H__
#define __XGENE_QMTM_CORE_H__

#ifdef APM_XGENE
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
//#define readl           MmioRead32
//#define writel(v, a)    MmioWrite32((a), (v))
#define udelay(x)          MicroSecondDelay((x))
#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define memcpy(dest,source,count)         CopyMem(dest,source,(UINTN)(count))
//#define printf          info
#define strcmp                            AsciiStrCmp
#define strcpy(strDest,strSource)         AsciiStrCpy(strDest,strSource)
#define strncpy(strDest,strSource,count)  AsciiStrnCpy(strDest,strSource,(UINTN)count)

#undef SIZE_2KB
#undef SIZE_16KB
#undef SIZE_64KB
#undef SIZE_512KB
#define memcpy(dest,source,count)         CopyMem(dest,source,(UINTN)(count))
#endif
#include "xgene_qmtm_main.h"

#define DST_QM_IP(n)		(n << 10)

/* QMTM Platform Information */
enum xgene_qmtm_pinfo {
	STORM_QMTM,
	SHADOWCAT_QMTM,
	MAX_PLATFORM,
};

/* QMTM IP Blocks */
#ifdef CONFIG_SHADOWCAT
enum xgene_qmtm_ip {
	QMTM0,
	QMTM_MAX,
};
/* Fake values to be able to compile shadowcat code */
#define QMTM1 0xFF
#define QMTM2 0xFE
#define QMTM3 0xFD
#else
enum xgene_qmtm_ip {
	QMTM0,
	QMTM1,
	QMTM2,
	QMTM3,
	QMTM_MAX,
};
#endif

/* QMTM Slave */
#ifdef CONFIG_SHADOWCAT
enum xgene_slave {
	SLAVE_XGE0,
	SLAVE_XGE1,
	SLAVE_CPU_QMTM0,
	SLAVE_MAX,
};
#else
enum xgene_slave {
	SLAVE_ETH0,
	SLAVE_ETH1,
	SLAVE_ETH2,
	SLAVE_ETH3,
	SLAVE_XGE0,
	SLAVE_XGE1,
	SLAVE_XGE2,
	SLAVE_XGE3,
	SLAVE_METH,
	SLAVE_PKTDMA,
	SLAVE_CTX_QMTM0,
	SLAVE_CTX_QMTM1,
	SLAVE_CTX_QMTM2,
	SLAVE_SEC,
	SLAVE_CLASS,
	SLAVE_MSLIM_QMTM0,
	SLAVE_MSLIM_QMTM1,
	SLAVE_MSLIM_QMTM2,
	SLAVE_MSLIM_QMTM3,
	SLAVE_PMPRO,
	SLAVE_SMPRO_QMTM0,
	SLAVE_SMPRO_QMTM1,
	SLAVE_SMPRO_QMTM2,
	SLAVE_SMPRO_QMTM3,
	SLAVE_CPU_QMTM0,
	SLAVE_CPU_QMTM1,
	SLAVE_CPU_QMTM2,
	SLAVE_CPU_QMTM3,
	SLAVE_MAX,
};
#endif

#define SLAVE_CTX(qmtm_ip)   (SLAVE_CTX_QMTM0 + qmtm_ip)
#define SLAVE_MSLIM(qmtm_ip) (SLAVE_MSLIM_QMTM0 + qmtm_ip)
#define SLAVE_SMPRO(qmtm_ip) (SLAVE_SMPRO_QMTM0 + qmtm_ip)
#define SLAVE_CPU(qmtm_ip)   (SLAVE_CPU_QMTM0 + qmtm_ip)

/* QMTM Slave Device Information */
struct xgene_qmtm_sdev;

#define QMTM_MIN_PBN_ID 0
#define QMTM_MAX_PBN_ID 31
#define QMTM_MAX_PBN    32
#define QMTM_PBN_MASK   0x1F
#define RES_MASK(nr)    (1UL << ((nr) % 32))
#define RES_WORD(nr)    ((nr) / 32)

/* QMTM Slave IDs */
enum xgene_qmtm_slave_id {
	QMTM_SLAVE_ID_ETH0,
	QMTM_SLAVE_ID_ETH1,
	QMTM_SLAVE_ID_RES2,
	QMTM_SLAVE_ID_PKTDMA,
	QMTM_SLAVE_ID_CTX,
	QMTM_SLAVE_ID_SEC,
	QMTM_SLAVE_ID_CLASS,
	QMTM_SLAVE_ID_MSLIM,
	QMTM_SLAVE_ID_RES8,
	QMTM_SLAVE_ID_RES9,
	QMTM_SLAVE_ID_RESA,
	QMTM_SLAVE_ID_RESB,
	QMTM_SLAVE_ID_RESC,
	QMTM_SLAVE_ID_PMPRO,
	QMTM_SLAVE_ID_SMPRO,
	QMTM_SLAVE_ID_CPU,
	QMTM_SLAVE_ID_MAX,
};

/* QMTM Free Pool Queue modes */
enum xgene_qmtm_fp_mode {
	MSG_NO_CHANGE,
	ROUND_ADDR,
	REDUCE_LEN,
	CHANGE_LEN,
};

struct xgene_qmtm_string {
	char *name;
};

extern const struct xgene_qmtm_string slave_s[]; 
extern const struct xgene_qmtm_string qtype_s[]; 
extern const struct xgene_qmtm_string qsize_s[]; 
extern const struct xgene_qmtm_string qaccess_s[];

#define QMTM_MIN_QUEUE_ID  0
#define QMTM_MAX_QUEUE_ID  1023
#define QMTM_MAX_QUEUES    1024
#define QMTM_QID_MASK      0x3FF

/* QMTM structure */
struct xgene_qmtm_dev {
	/* QM/QML CSR address for all QMTM i.e. QMTM0, QMTM1, QMTM2, & QMTM3/QMLite */
	u64 qmtm_csr_paddr;
	void *qmtm_csr_vaddr;
	u64 qmtm_fabric_paddr;
	void *qmtm_fabric_vaddr;
	u16 qmtm_error_irq;
	u16 qmtm_max_queues;
	u32 qmtm_ip;		/* qmtm_ip, see xgene_qmtm_ip */
	u16 dequeue_irq[QMTM_MAX_PBN];
	char error_irq_s[16];
	char error_queue_irq_s[16];
	u32 *queue_pool;
	struct xgene_qmtm_qinfo * (*qinfo);
	struct xgene_qmtm_qinfo *error_qinfo;
	struct clk *clk;
}__attribute__ ((packed));

struct xgene_qmtm_pdev {
	struct xgene_qmtm_dev *dev[QMTM_MAX];
	struct xgene_qmtm_sdev *sdev[SLAVE_MAX];
	struct xgene_qmtm_qinfo* (*alloc_qinfo)(void);
	void (*write_qstate)(u8 qmtm_ip, u16 queue_id, void *qstate);
	void (*read_qstate)(u8 qmtm_ip, u16 queue_id, void *qstate);
	int (*set_qstate)(struct xgene_qmtm_qinfo *qinfo);
	void (*get_qstate)(struct xgene_qmtm_qinfo *qinfo);
	void (*clr_qstate)(struct xgene_qmtm_qinfo *qinfo);
};

#define MAX_COAL_TAP 0x7
#define MIN_COAL_TAP 0x0

/* API declarations */
void xgene_qmtm_read_qstate(u8 qmtm_ip, u16 queue_id, void *qstate);

int xgene_qmtm_dump_qinfo(struct xgene_qmtm_qinfo *qinfo);

/**
 * @brief   Enable and Initialize QMTM IP device
 * @param   qmtm_ip - QMTM0, QMTM1, QMTM2 or QMTM3
 *	    qmtm_max_queues - maximun number of queues to allow
 *	    qmtm_csr_paddr - QMTM IP CSR Physical Address
 *	    qmtm_csr_vaddr - QMTM IP CSR Virtual Address
 *	    qmtm_fabric_paddr - QMTM IP Fabric Physical Address
 *	    qmtm_fabric_vaddr - QMTM IP Fabric Virtual Address
 * @return  QMTM_OK on Success or QMTM_ERR on Failure
 */
int xgene_qmtm_dev_init(u8 qmtm_ip, u16 qmtm_max_queues,
		u64 qmtm_csr_paddr, void *qmtm_csr_vaddr,
		u64 qmtm_fabric_paddr, void *qmtm_fabric_vaddr);

/**
 * @brief   Disable QMTM IP device
 * @param   qmtm_ip - QMTM0, QMTM1, QMTM2 or QMTM3
 * @return  QMTM_OK on Success or QMTM_ERR on Failure
 */
int xgene_qmtm_dev_exit(u8 qmtm_ip);

/**
 * @brief   Enable and Initialize QMTM Platform device
 * @param   driver_data - information about platform i.e. Storm or ShadowCat
 * @return  QMTM Platform device structure
 */
struct xgene_qmtm_pdev *xgene_qmtm_pdev_init(u32 driver_data);

struct xgene_qmtm_dev *xgene_qmtm_get_dev(u8 qmtm_ip);

void storm_qmtm_pdev_init(struct xgene_qmtm_pdev *pdev);

void xgene_qmtm_msg_pdev(void *pdev);

#endif /* __XGENE_QMTM_CORE_H__ */
