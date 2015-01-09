/**
 * AppliedMicro X-Gene SOC Ethernet U-Boot Header file
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * Author: Keyur Chudgar <kchudgar@apm.com>
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
 * @file apm_enet_access.h
 *
 */

#ifndef __APM_ENET_ACCESS_H__
#define __APM_ENET_ACCESS_H__

#ifndef APM_XGENE
#include <config.h>
#include <common.h>
#include <net.h>
#else
#include "../mustang.h"
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;

struct eth_device {
	char name[16];
	unsigned char enetaddr[6];
	int iobase;
	int state;

	int  (*init) (struct eth_device * /*TODO , bd_t * */);
	int  (*send) (struct eth_device*, volatile void* packet, int length);
	int  (*recv) (struct eth_device *, VOID *Buffer, UINTN *BufferSize);
	void (*halt) (struct eth_device *);
#ifdef CONFIG_MCAST_TFTP
	int (*mcast) (struct eth_device *, u32 ip, u8 set);
#endif
	int  (*write_hwaddr) (struct eth_device *);
	struct eth_device *next;
	int index;
	void *priv;
};

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)   sizeof(x)/sizeof(x[0])
#endif

//#define readl           MmioRead32
//#define writel(v, a)    MmioWrite32((a), (v))
#define udelay(x)          MicroSecondDelay((x))
#define mdelay(x)   MicroSecondDelay((x*1000))
#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define memcpy(dest,source,count)         CopyMem(dest,source,(UINTN)(count))
#define printf          info
#define strcmp                            AsciiStrCmp
#define strcpy(strDest,strSource)         AsciiStrCpy(strDest,strSource)
#define strncpy(strDest,strSource,count)  AsciiStrnCpy(strDest,strSource,(UINTN)count)
#define strncmp(string1,string2,count)    (int)(AsciiStrnCmp(string1,string2,(UINTN)(count)))


#define DDR_INFO
#undef DDR_DBG
#ifdef DDR_DBG
#define debug(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define debug(arg...)
#endif

#ifdef DDR_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif

#include "apm_enet_common.h"
#endif

#define BOOTLOADER
#undef BYPASS_CLE

#ifdef DEBUG_ENET
#define ENET_DBG_ERR
#define ENET_PRINT_ENABLE
#define ENET_DBG        //fscz
#define DEBUG_TX        //fscz
#else
#undef ENET_DBG_ERR
#undef ENET_PRINT_ENABLE
#undef ENET_DBG        //fscz
#undef DEBUG_TX        //fscz
#endif

#undef PHY_DEBUG
#undef FAM_UBOOT
#undef DEBUG_HEXDUMP
#undef DEBUG_RD   
#undef DEBUG_WR   
#undef DEBUG_RX 
#undef ENET_REGISTER_READ
#undef ENET_REGISTER_WRITE

#define STORM_FPGA_CLS_BYPASS

#ifdef ENET_PRINT_ENABLE
#define ENET_PRINT(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_PRINT(x, ...)
#endif

#ifdef PHY_DEBUG
#define PHY_PRINT(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define PHY_PRINT(x, ...)
#endif

#ifdef ENET_DBG
#define ENET_DEBUG(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG(x, ...)	
#endif

#ifdef ENET_DBG_ERR
#define ENET_DEBUG_ERR(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_ERR(x, ...)	    
#endif

#ifdef DEBUG_RD
#define ENET_DEBUG_RD(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_RD(x, ...)		
#endif

#ifdef DEBUG_WR
#define ENET_DEBUG_WR(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_WR(x, ...)		
#endif

#ifdef ENET_REGISTER_READ
#define ENET_REG_RD(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_REG_RD(x, ...)
#endif

#ifdef ENET_REGISTER_WRITE
#define ENET_REG_WR(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_REG_WR(x, ...)
#endif

#ifdef DEBUG_HEXDUMP
#define ENET_RXHEXDUMP(b, l)		putshex(b, l)
#define ENET_TXHEXDUMP(b, l)		putshex(b, l)
#else
#define ENET_RXHEXDUMP(b, l)
#define ENET_TXHEXDUMP(b, l)
#endif

#ifdef DEBUG_RX
#define ENET_DEBUG_RX(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_RX(x, ...)		
#endif

#ifdef DEBUG_TX
#define ENET_DEBUG_TX(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_TX(x, ...)		
#endif

#define physical_addr(x) 	((unsigned int) (x))
#define virtual_addr(x)	 	((void *) (x))

#define NO_RX_BUFF		16

#define ENET_ADDR_LENGTH	6
#define EMAC_NUM_DEV		1

#define TX_DATA_LEN_MASK	0XFFF
#define APM_ENET_FRAME_LEN	1536 //PKTSIZE_ALIGN

#ifndef CONFIG_STORM_VHP
#define PBN_CLEAR_SUPPORT
#endif

#undef APM_ENET_SERDES_LOOPBACK

#ifdef APM_ENET_SERDES_LOOPBACK
#define NON_AUTO_NEGOTIATION	1
#endif

#if defined(CONFIG_STORM)
#define invalidate_dcache_range(x, y)
#define flush_dcache_range(x, y)
#endif

// FIXME: do we need mailbox related variables ?
// FIXME: do we need pbn ?  can we have qinfo instead of qid etc ?
/* Queues related parameters per Enet port */
struct eth_queue_ids {
	u32 rx_qid;
	u32 rx_mbid; 	/* mailbox id for receive queue */
	u32 rx_fp_qid;
	u32 rx_fp_mbid;
	u32 rx_fp_pbn;
	u32 tx_qid;		/* Endque q id	      */
	u32 comp_qid;		/* completion q id    */
	u32 comp_mb;		/* completion mailbox */
	u32 qm_ip;
};

struct enet_frame {
	unsigned char dest_addr[ENET_ADDR_LENGTH];
	unsigned char source_addr[ENET_ADDR_LENGTH];
	unsigned short type;
	unsigned char enet_data[1];
};

/* private information regarding device */
struct apm_enet_dev {
	struct apm_enet_priv priv;
	struct eth_device *ndev;
	u32 port_id;
	struct apm_emac_error_stats estats;
	struct eth_queue_ids queues;
	struct xgene_qmtm_sdev *sdev;
};

#ifdef inline
#undef inline
#endif
/* Ethernet raw register write routine */
inline void apm_enet_wr32(void *addr, u32 data);


/* Ethernet raw register read routine */
inline void apm_enet_rd32(void *addr, u32 *data);

/**
 * @brief   This function performs preclassifier engine Initialization
 * 	    and node configurations.  
 * @param   port_id - GE Port number
 * @param   *eth_q  - Pointer to queue configurations used by Ethernet 
 * @return  0 - success or -1 - failure
 */
int apm_preclass_init(u8 port_id, struct eth_queue_ids *eth_q);

/**
 * @brief   This function updates preclassifier rule of allowing incoming
 *          Ethernet packets dstmac address which are same as macaddr
 * @param   port_id - GE Port number
 * @param   macaddr - Ethenet MAC Address
 */
void apm_preclass_update_mac(u8 port_id, u8 *macaddr);

#endif	/* __APM_ENET_ACCESS_H__ */
