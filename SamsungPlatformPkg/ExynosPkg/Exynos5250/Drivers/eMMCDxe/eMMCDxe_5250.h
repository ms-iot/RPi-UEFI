/** @file

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _MSHCDXE_5250_H_
#define _MSHCDXE_5250_H_


/*
 * Controller registers
 */
/*****************************************************/
/*      MSHC Internal Registers       */
/*****************************************************/

#define MSHCI_CTRL 	0x00	/* Control */
#define MSHCI_PWREN 	0x04   	/* Power-enable */
#define MSHCI_CLKDIV 	0x08   	/* Clock divider */
#define MSHCI_CLKSRC	0x0C   	/* Clock source */
#define MSHCI_CLKENA 	0x10	/* Clock enable */
#define MSHCI_TMOUT 	0x14	/* Timeout */
#define MSHCI_CTYPE 	0x18	/* Card type */
#define MSHCI_BLKSIZ 	0x1C	/* Block Size */
#define MSHCI_BYTCNT 	0x20	/* Byte count */
#define MSHCI_INTMSK 	0x24	/* Interrupt Mask */
#define MSHCI_CMDARG 	0x28	/* Command Argument */
#define MSHCI_CMD 	0x2C	/* Command */
#define MSHCI_RESP0 	0x30	/* Response 0 */
#define MSHCI_RESP1 	0x34	/* Response 1 */
#define MSHCI_RESP2 	0x38	/* Response 2 */
#define MSHCI_RESP3 	0x3C	/* Response 3 */
#define MSHCI_MINTSTS 	0x40	/* Masked interrupt status */
#define MSHCI_RINTSTS 	0x44	/* Raw interrupt status */
#define MSHCI_STATUS 	0x48	/* Status */
#define MSHCI_FIFOTH 	0x4C	/* FIFO threshold */
#define MSHCI_CDETECT 	0x50	/* Card detect */
#define MSHCI_WRTPRT 	0x54	/* Write protect */
#define MSHCI_GPIO 	0x58	/* General Purpose IO */
#define MSHCI_TCBCNT 	0x5C	/* Transferred CIU byte count */
#define MSHCI_TBBCNT 	0x60	/* Transferred host/DMA to/from byte count */
#define MSHCI_DEBNCE 	0x64	/* Card detect debounce */
#define MSHCI_USRID 	0x68	/* User ID */
#define MSHCI_VERID 	0x6C	/* Version ID */
#define MSHCI_HCON 	0x70	/* Hardware Configuration */
#define MSHCI_UHS_REG  	0x74	/* UHS and DDR setting */
#define MSHCI_BMOD      0x80    /* Bus mode register */
#define MSHCI_PLDMND    0x84    /* Poll demand */
#define MSHCI_DBADDR    0x88    /* Descriptor list base address */
#define MSHCI_IDSTS     0x8C    /* Internal DMAC status */
#define MSHCI_IDINTEN   0x90    /* Internal DMAC interrupt enable */
#define MSHCI_DSCADDR   0x94    /* Current host descriptor address */
#define MSHCI_BUFADDR   0x98    /* Current host buffer address */
#define MSHCI_CLKSEL	0x9C    /* Drv/sample clock selection register */
#define MSHCI_WAKEUPCON 0xA0    /* Wakeup control register */
#define MSHCI_CLOCKCON  0xA4    /* Clock (delay) control register */
#define MSHCI_FIFO          0x200
#define MSHCI_FIFODAT(x)	(x)	/* FIFO data read write */


/*****************************************************
 *  Control Register  Register
 *  MSHCI_CTRL - offset 0x00
 *****************************************************/

#define CTRL_RESET	(0x1<<0)	/* Reset DWC_mobile_storage controller */	
#define FIFO_RESET	(0x1<<1)	/* Reset FIFO */
#define DMA_RESET	(0x1<<2)	/* Reset DMA interface */
#define INT_ENABLE	(0x1<<4)	/* Global interrupt enable/disable bit */
#define DMA_ENABLE	(0x1<<5)	/* DMA transfer mode enable/disable bit */
#define READ_WAIT	(0x1<<6)	/* For sending read-wait to SDIO cards */
#define SEND_IRQ_RESP	(0x1<<7)	/* Send auto IRQ response */
#define ABRT_READ_DATA	(0x1<<8)	
#define SEND_CCSD	(0x1<<9)
#define SEND_AS_CCSD	(0x1<<10)
#define CEATA_INTSTAT	(0x1<<11)
#define CARD_VOLA	(0xF<<16)
#define CARD_VOLB	(0xF<<20)
#define ENABLE_OD_PULLUP	(0x1<<24)	
#define ENABLE_IDMAC    (0x1<<25)
#define MSHCI_RESET_ALL  (0x1)

/*****************************************************
 *  Power Enable Register
 *  MSHCI_PWREN - offset 0x04
 *****************************************************/
#define POWER_ENABLE	(0x1<<0)

/*****************************************************
*  Clock Enable Register
*  MSHCI_CLKENA - offset 0x10
*****************************************************/
#define CLK_SDMMC_MAX	(48000000) /* 96Mhz. it SHOULDBE optimized */
#define CLK_ENABLE	(0x1<<0)
#define CLK_DISABLE	(0x0<<0)


/*****************************************************
 *  Interrupt Mask Register
 *  MSHCI_INTMSK - offset 0x24
 *****************************************************/
#define INT_MASK	(0xFFFF<<0)
#define	SDIO_INT_MASK	(0xFFFF<<16)
#define SDIO_INT_ENABLE (0x1<<16)

/* interrupt bits */
#define INTMSK_ALL	0xFFFFFFFF
#define INTMSK_CDETECT 	(0x1<<0) 
#define INTMSK_RE 	(0x1<<1)
#define INTMSK_CDONE 	(0x1<<2)
#define INTMSK_DTO 	(0x1<<3)
#define INTMSK_TXDR     (0x1<<4)
#define INTMSK_RXDR     (0x1<<5)
#define INTMSK_RCRC     (0x1<<6)
#define INTMSK_DCRC     (0x1<<7)
#define INTMSK_RTO      (0x1<<8)
#define INTMSK_DRTO    	(0x1<<9) 
#define INTMSK_HTO      (0x1<<10)
#define INTMSK_FRUN     (0x1<<11)
#define INTMSK_HLE      (0x1<<12)
#define INTMSK_SBE      (0x1<<13)
#define INTMSK_ACD      (0x1<<14)
#define INTMSK_EBE	(0x1<<15)
#define INTMSK_DMA	(INTMSK_ACD|INTMSK_RXDR|INTMSK_TXDR)

#define INT_SRC_IDMAC   (0x0)
#define INT_SRC_MINT    (0x1)


/*****************************************************
 *  Command Register
 *  MSHCI_CMD - offset 0x2C
 *****************************************************/

#define CMD_RESP_EXP_BIT	(0x1<<6)	
#define CMD_RESP_LENGTH_BIT	(0x1<<7)
#define CMD_CHECK_CRC_BIT	(0x1<<8)
#define CMD_DATA_EXP_BIT	(0x1<<9)
#define CMD_RW_BIT		(0x1<<10)
#define CMD_TRANSMODE_BIT	(0x1<<11)
#define CMD_SENT_AUTO_STOP_BIT	(0x1<<12)
#define CMD_WAIT_PRV_DAT_BIT	(0x1<<13)
#define CMD_ABRT_CMD_BIT	(0x1<<14)
#define CMD_SEND_INIT_BIT	(0x1<<15)
#define CMD_CARD_NUM_BITS	(0x1F<<16)
#define CMD_SEND_CLK_ONLY	(0x1<<21)
#define CMD_READ_CEATA		(0x1<<22)
#define CMD_CCS_EXPECTED	(0x1<<23)
#define CMD_USE_HOLD_REG	(0x1<<29)
#define CMD_STRT_BIT		(0x1<<31)
#define CMD_ONLY_CLK		(CMD_STRT_BIT | CMD_SEND_CLK_ONLY | \
						CMD_WAIT_PRV_DAT_BIT)

/*****************************************************
 *  Raw Interrupt Register
 *  MSHCI_RINTSTS - offset 0x44
 *****************************************************/
#define INT_STATUS	(0xFFFF<<0)
#define SDIO_INTR	(0xFFFF<<16)
#define DATA_ERR	(INTMSK_EBE|INTMSK_SBE|INTMSK_HLE|INTMSK_FRUN |\
					INTMSK_EBE |INTMSK_DCRC)
#define DATA_TOUT	(INTMSK_HTO|INTMSK_DRTO)
#define DATA_STATUS 	(DATA_ERR|DATA_TOUT|INTMSK_RXDR|INTMSK_TXDR|INTMSK_DTO)
#define CMD_STATUS	(INTMSK_RTO|INTMSK_RCRC|INTMSK_CDONE|INTMSK_RE)
#define CMD_ERROR       (INTMSK_RCRC|INTMSK_RTO|INTMSK_RE)


/*****************************************************
 *  Status Register
 *  MSHCI_STATUS - offset 0x48
 *****************************************************/
#define FIFO_RXWTRMARK	(0x1<<0)
#define FIFO_TXWTRMARK	(0x1<<1)
#define FIFO_EMPTY	(0x1<<2)
#define FIFO_FULL	(0x1<<3)
#define CMD_FSMSTAT	(0xF<<4)
#define	DATA_3STATUS	(0x1<<8)
#define DATA_BUSY	(0x1<<9)
#define DATA_MCBUSY	(0x1<<10)
#define RSP_INDEX	(0x3F<<11)
#define FIFO_COUNT	(0x1FFF<<17)
#define	DMA_ACK		(0x1<<30)
#define	DMA_REQ		(0x1<<31)
#define FIFO_WIDTH 	(0x4)
#define FIFO_DEPTH      (0x20)
#define FIFO_SIZE      (0x80)
#define GET_FIFO_COUNT(x)	(((x)&0x3ffe0000)>>17)



/*****************************************************
 *  FIFO Threshold Watermark Register
 *  MSHCI_FIFOTH - offset 0x4C
 *****************************************************/
#define TX_WMARK	(0xFFF<<0)
#define RX_WMARK	(0xFFF<<16)
#define MSIZE_MASK	(0x7<<28)

/* DW DMA Mutiple Transaction Size */
#define MSIZE_1		(0<<28)
#define MSIZE_4		(1<<28)
#define MSIZE_8		(2<<28)
#define MSIZE_16	(3<<28)
#define MSIZE_32	(4<<28)
#define MSIZE_64	(5<<28)		
#define MSIZE_128	(6<<28)
#define MSIZE_256	(7<<28)

#define TX_WMARK_DEFAULT    (0x10<<0)
#define RX_WMARK_DEFAULT    (0x10<<16)

//#define TX_WMARK_DEFAULT    (0x40<<0)
//#define RX_WMARK_DEFAULT    (0x3F<<16)


/*****************************************************
 *  Bus Mode Register
 *  MSHCI_UHS_REG - offset 0x74
 *****************************************************/
#define UHS_DDR                 (0x1<<16)
#define UHS_NON_DDR           (0x0<<16)
#define BUSMODE_DDR     1
#define BUSMODE_NON_DDR     0

/*****************************************************
 *  Bus Mode Register
 *  MSHCI_BMOD - offset 0x80
 *****************************************************/
#define BMOD_IDMAC_RESET        (0x1<<0)
#define BMOD_IDMAC_FB           (0x1<<1)
#define BMOD_IDMAC_ENABLE       (0x1<<7)

/*****************************************************
 *  Hardware Configuration  Register
 *  MSHCI_IDSTS - offset 0x8c
 *****************************************************/
#define IDSTS_FSM               (0xf<<13)
#define IDSTS_EB                (0x7<<10)
#define IDSTS_AIS               (0x1<<9)
#define IDSTS_NIS               (0x1<<8)
#define IDSTS_CES               (0x1<<5)
#define IDSTS_DU                (0x1<<4)
#define IDSTS_FBE               (0x1<<2)
#define IDSTS_RI                (0x1<<1)
#define IDSTS_TI                (0x1<<0)


/*****************************************************
 *  Card Type Register
 *  MSHCI_CTYPE - offset 0x18
 *****************************************************/
#define CARD_WIDTH14	(0xFFFF<<0)
#define CARD_WIDTH8	(0xFFFF<<16)

struct mshci_idmac {
        UINT32     des0;
        UINT32     des1;
        UINT32     des2;
        UINT32     des3;
#define MSHCI_IDMAC_OWN         (1<<31)
#define MSHCI_IDMAC_ER          (1<<5)
#define MSHCI_IDMAC_CH          (1<<4)
#define MSHCI_IDMAC_FS          (1<<3)
#define MSHCI_IDMAC_LD          (1<<2)
#define MSHCI_IDMAC_DIC         (1<<1)
#define INTMSK_IDMAC_ALL        (0x337)
#define INTMSK_IDMAC_ERROR      (0x214)        
};

typedef enum {
  READ,
  WRITE
} OPERATION_TYPE;


/*****************************************************
 *  DMA Buffer structure
 *  
 * CH0 for eMMC 0x40300000--0x40380000
 * CH2 for SD Card 0x40380000--0x40400000


 *****************************************************/
#define EMMC_DMA_PHYSICAL_BUFFER_BASE 0x40300000
#define EMMC_DMA_PHYSICAL_BUFFER_SIZE   0x00100000 //1MB
#define PHY_BUF_OFFSET  0x1000 //4K
#define PHY_BUF_SIZE  0x1000 //4K

#define MAX_MSHC_TRANSFER_SIZE  0x40000   //512blocks, 256KB



/*****************************************************
 * External Functions
 *****************************************************/


EFI_STATUS InitializeMSHC (VOID);
VOID UpdateMSHCClkFrequency (UINTN NewCLK);
void MSHC_reset_fifo(void);
extern void MSHC_reset_all(void);
extern VOID PrepareTransfer (IN OUT VOID *Buffer, UINTN ByteCount, IN OPERATION_TYPE OperationType);
extern EFI_STATUS MSHC_ReadFIFO(IN UINTN Size32, OUT VOID *Buffer);
extern EFI_STATUS MSHC_WriteFIFO(IN UINTN Size32, IN VOID *Buffer);
void mshci_set_mdma_desc(UINT8 *desc_vir, UINT8 *desc_phy, 
				UINT32 des0, UINT32 des1, UINT32 des2);
EFI_STATUS MSHC_ReadDMA(OUT VOID *Buffer, IN UINTN BlockCount);
EFI_STATUS MSHC_WriteDMA(IN VOID *Buffer, IN UINTN BlockCount);



#endif

