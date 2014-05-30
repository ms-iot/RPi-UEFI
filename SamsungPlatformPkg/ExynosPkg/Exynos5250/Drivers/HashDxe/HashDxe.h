/** @file

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _CRYPTODXE_H_
#define _CRYPTODXE_H_

#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>

#define SSS_CMU_OFFSET		(0x8800)
#define CLK_SSS			(1 << 2)

#define SSS_FC_OFFSET		(0x0)
#define SSS_AES_OFFSET		(0x200)
#define SSS_HASH_OFFSET		(0x400)

/* Feed control registers */
#define SSS_FC_INTSTAT		(SSS_FC_OFFSET + 0x00)
#define SSS_FC_INTENSET		(SSS_FC_OFFSET + 0x04)
#define SSS_FC_INTENCLR		(SSS_FC_OFFSET + 0x08)
#define SSS_FC_INTPEND		(SSS_FC_OFFSET + 0x0C)
#define SSS_FC_FIFOSTAT		(SSS_FC_OFFSET + 0x10)
#define SSS_FC_FIFOCTRL		(SSS_FC_OFFSET + 0x14)
#define SSS_FC_GLOBAL		(SSS_FC_OFFSET + 0x18)
#define SSS_FC_BRDMAS		(SSS_FC_OFFSET + 0x20)
#define SSS_FC_BRDMAL		(SSS_FC_OFFSET + 0x24)
#define SSS_FC_BRDMAC		(SSS_FC_OFFSET + 0x28)
#define SSS_FC_BTDMAS		(SSS_FC_OFFSET + 0x30)
#define SSS_FC_BTDMAL		(SSS_FC_OFFSET + 0x34)
#define SSS_FC_BTDMAC		(SSS_FC_OFFSET + 0x38)
#define SSS_FC_HRDMAS		(SSS_FC_OFFSET + 0x40)
#define SSS_FC_HRDMAL		(SSS_FC_OFFSET + 0x44)
#define SSS_FC_HRDMAC		(SSS_FC_OFFSET + 0x48)
#define SSS_FC_PKDMAS		(SSS_FC_OFFSET + 0x50)
#define SSS_FC_PKDMAL		(SSS_FC_OFFSET + 0x54)
#define SSS_FC_PKDMAC		(SSS_FC_OFFSET + 0x58)
#define SSS_FC_PKDMAO		(SSS_FC_OFFSET + 0x5C)

/* AES control registers */
#define SSS_AES_CONTROL		(SSS_AES_OFFSET + 0x00)
#define SSS_AES_STATUS		(SSS_AES_OFFSET + 0x04)

#define SSS_AES_IN1		(SSS_AES_OFFSET + 0x10)
#define SSS_AES_IN2		(SSS_AES_OFFSET + 0x14)
#define SSS_AES_IN3		(SSS_AES_OFFSET + 0x18)
#define SSS_AES_IN4		(SSS_AES_OFFSET + 0x1C)

#define SSS_AES_OUT1		(SSS_AES_OFFSET + 0x20)
#define SSS_AES_OUT2		(SSS_AES_OFFSET + 0x24)
#define SSS_AES_OUT3		(SSS_AES_OFFSET + 0x28)
#define SSS_AES_OUT4		(SSS_AES_OFFSET + 0x2C)

#define SSS_AES_IV1		(SSS_AES_OFFSET + 0x30)
#define SSS_AES_IV2		(SSS_AES_OFFSET + 0x34)
#define SSS_AES_IV3		(SSS_AES_OFFSET + 0x38)
#define SSS_AES_IV4		(SSS_AES_OFFSET + 0x3C)

#define SSS_AES_CNT1		(SSS_AES_OFFSET + 0x40)
#define SSS_AES_CNT2		(SSS_AES_OFFSET + 0x44)
#define SSS_AES_CNT3		(SSS_AES_OFFSET + 0x48)
#define SSS_AES_CNT4		(SSS_AES_OFFSET + 0x4C)

#define SSS_AES_KEY1		(SSS_AES_OFFSET + 0x80)
#define SSS_AES_KEY2		(SSS_AES_OFFSET + 0x84)
#define SSS_AES_KEY3		(SSS_AES_OFFSET + 0x88)
#define SSS_AES_KEY4		(SSS_AES_OFFSET + 0x8C)
#define SSS_AES_KEY5		(SSS_AES_OFFSET + 0x90)
#define SSS_AES_KEY6		(SSS_AES_OFFSET + 0x94)
#define SSS_AES_KEY7		(SSS_AES_OFFSET + 0x98)
#define SSS_AES_KEY8		(SSS_AES_OFFSET + 0x9C)

/* TDES control registers */
#define SSS_TDES_CONTROL	(SSS_TDES_OFFSET + 0x00)
#define SSS_TDES_STATUS		(SSS_TDES_OFFSET + 0x04)

#define SSS_TDES_KEY11		(SSS_TDES_OFFSET + 0x10)
#define SSS_TDES_KEY12		(SSS_TDES_OFFSET + 0x14)
#define SSS_TDES_KEY21		(SSS_TDES_OFFSET + 0x18)
#define SSS_TDES_KEY22		(SSS_TDES_OFFSET + 0x1C)
#define SSS_TDES_KEY31		(SSS_TDES_OFFSET + 0x20)
#define SSS_TDES_KEY32		(SSS_TDES_OFFSET + 0x24)

#define SSS_TDES_IV1		(SSS_TDES_OFFSET + 0x28)
#define SSS_TDES_IV2		(SSS_TDES_OFFSET + 0x2C)

#define SSS_TDES_IN1		(SSS_TDES_OFFSET + 0x30)
#define SSS_TDES_IN2		(SSS_TDES_OFFSET + 0x34)

#define SSS_TDES_OUT1		(SSS_TDES_OFFSET + 0x38)
#define SSS_TDES_OUT2		(SSS_TDES_OFFSET + 0x3C)

/* HASH control registers */
#define SSS_HASH_CONTROL	(SSS_HASH_OFFSET + 0x00)
#define SSS_HASH_CONTROL2	(SSS_HASH_OFFSET + 0x04)
#define SSS_HASH_FIFO_MODE	(SSS_HASH_OFFSET + 0x08)
#define SSS_HASH_BYTESWAP	(SSS_HASH_OFFSET + 0x0C)
#define SSS_HASH_STATUS		(SSS_HASH_OFFSET + 0x10)
#define SSS_HASH_MSGSIZE_LOW	(SSS_HASH_OFFSET + 0x20)
#define SSS_HASH_MSGSIZE_HIGH	(SSS_HASH_OFFSET + 0x24)
#define SSS_HASH_PRELEN_LOW	(SSS_HASH_OFFSET + 0x28)
#define SSS_HASH_PRELEN_HIGH	(SSS_HASH_OFFSET + 0x2C)

#define SSS_HASH_IN1		(SSS_HASH_OFFSET + 0x30)
#define SSS_HASH_IN2		(SSS_HASH_OFFSET + 0x34)
#define SSS_HASH_IN3		(SSS_HASH_OFFSET + 0x38)
#define SSS_HASH_IN4		(SSS_HASH_OFFSET + 0x3C)
#define SSS_HASH_IN5		(SSS_HASH_OFFSET + 0x40)
#define SSS_HASH_IN6		(SSS_HASH_OFFSET + 0x44)
#define SSS_HASH_IN7		(SSS_HASH_OFFSET + 0x48)
#define SSS_HASH_IN8		(SSS_HASH_OFFSET + 0x4C)
#define SSS_HASH_IN9		(SSS_HASH_OFFSET + 0x50)
#define SSS_HASH_IN10		(SSS_HASH_OFFSET + 0x54)
#define SSS_HASH_IN11		(SSS_HASH_OFFSET + 0x58)
#define SSS_HASH_IN12		(SSS_HASH_OFFSET + 0x5C)
#define SSS_HASH_IN13		(SSS_HASH_OFFSET + 0x60)
#define SSS_HASH_IN14		(SSS_HASH_OFFSET + 0x64)
#define SSS_HASH_IN15		(SSS_HASH_OFFSET + 0x68)
#define SSS_HASH_IN16		(SSS_HASH_OFFSET + 0x6C)

#define SSS_HASH_HMAC_KEY_IN1	(SSS_HASH_OFFSET + 0x70)
#define SSS_HASH_HMAC_KEY_IN2	(SSS_HASH_OFFSET + 0x74)
#define SSS_HASH_HMAC_KEY_IN3	(SSS_HASH_OFFSET + 0x78)
#define SSS_HASH_HMAC_KEY_IN4	(SSS_HASH_OFFSET + 0x7C)
#define SSS_HASH_HMAC_KEY_IN5	(SSS_HASH_OFFSET + 0x80)
#define SSS_HASH_HMAC_KEY_IN6	(SSS_HASH_OFFSET + 0x84)
#define SSS_HASH_HMAC_KEY_IN7	(SSS_HASH_OFFSET + 0x88)
#define SSS_HASH_HMAC_KEY_IN8	(SSS_HASH_OFFSET + 0x8C)
#define SSS_HASH_HMAC_KEY_IN9	(SSS_HASH_OFFSET + 0x90)
#define SSS_HASH_HMAC_KEY_IN10	(SSS_HASH_OFFSET + 0x94)
#define SSS_HASH_HMAC_KEY_IN11	(SSS_HASH_OFFSET + 0x98)
#define SSS_HASH_HMAC_KEY_IN12	(SSS_HASH_OFFSET + 0x9C)
#define SSS_HASH_HMAC_KEY_IN13	(SSS_HASH_OFFSET + 0xA0)
#define SSS_HASH_HMAC_KEY_IN14	(SSS_HASH_OFFSET + 0xA4)
#define SSS_HASH_HMAC_KEY_IN15	(SSS_HASH_OFFSET + 0xA8)
#define SSS_HASH_HMAC_KEY_IN16	(SSS_HASH_OFFSET + 0xAC)

#define SSS_HASH_IV1		(SSS_HASH_OFFSET + 0xB0)
#define SSS_HASH_IV2		(SSS_HASH_OFFSET + 0xB4)
#define SSS_HASH_IV3		(SSS_HASH_OFFSET + 0xB8)
#define SSS_HASH_IV4		(SSS_HASH_OFFSET + 0xBC)
#define SSS_HASH_IV5		(SSS_HASH_OFFSET + 0xC0)
#define SSS_HASH_IV6		(SSS_HASH_OFFSET + 0xC4)
#define SSS_HASH_IV7		(SSS_HASH_OFFSET + 0xC8)
#define SSS_HASH_IV8		(SSS_HASH_OFFSET + 0xCC)

#define SSS_HASH_RESULT1	(SSS_HASH_OFFSET + 0x100)
#define SSS_HASH_RESULT2	(SSS_HASH_OFFSET + 0x104)
#define SSS_HASH_RESULT3	(SSS_HASH_OFFSET + 0x108)
#define SSS_HASH_RESULT4	(SSS_HASH_OFFSET + 0x10C)
#define SSS_HASH_RESULT5	(SSS_HASH_OFFSET + 0x110)
#define SSS_HASH_RESULT6	(SSS_HASH_OFFSET + 0x114)
#define SSS_HASH_RESULT7	(SSS_HASH_OFFSET + 0x118)
#define SSS_HASH_RESULT8	(SSS_HASH_OFFSET + 0x11C)

#define SSS_HASH_SEED1		(SSS_HASH_OFFSET + 0x140)
#define SSS_HASH_SEED2		(SSS_HASH_OFFSET + 0x144)
#define SSS_HASH_SEED3		(SSS_HASH_OFFSET + 0x148)
#define SSS_HASH_SEED4		(SSS_HASH_OFFSET + 0x14C)
#define SSS_HASH_SEED5		(SSS_HASH_OFFSET + 0x150)

#define SSS_HASH_PRNG1		(SSS_HASH_OFFSET + 0x160)
#define SSS_HASH_PRNG2		(SSS_HASH_OFFSET + 0x164)
#define SSS_HASH_PRNG3		(SSS_HASH_OFFSET + 0x168)
#define SSS_HASH_PRNG4		(SSS_HASH_OFFSET + 0x16C)
#define SSS_HASH_PRNG5		(SSS_HASH_OFFSET + 0x170)

/* PKA control registers */
#define SSS_PKA_SFR0		(SSS_PKA_OFFSET + 0x00)
#define SSS_PKA_SFR1		(SSS_PKA_OFFSET + 0x04)
#define SSS_PKA_SFR2		(SSS_PKA_OFFSET + 0x08)
#define SSS_PKA_SFR3		(SSS_PKA_OFFSET + 0x0C)
#define SSS_PKA_SFR4		(SSS_PKA_OFFSET + 0x10)


/*****************************************************************
	OFFSET
*****************************************************************/

/* SSS_FC_INT */
#define SSS_FC_PKDMA			(1 << 0)
#define SSS_FC_HRDMA			(1 << 1)
#define SSS_FC_BTDMA			(1 << 2)
#define SSS_FC_BRDMA			(1 << 3)
#define SSS_FC_PRNG_ERROR		(1 << 4)
#define SSS_FC_MSG_DONE			(1 << 5)
#define SSS_FC_PRNG_DONE		(1 << 6)
#define SSS_FC_PARTIAL_DONE		(1 << 7)

/* SSS_FC_FIFOSTAT */
#define SSS_FC_PKFIFO_EMPTY		(1 << 0)
#define SSS_FC_PKFIFO_FULL		(1 << 1)
#define SSS_FC_HRFIFO_EMPTY		(1 << 2)
#define SSS_FC_HRFIFO_FULL		(1 << 3)
#define SSS_FC_BTFIFO_EMPTY		(1 << 4)
#define SSS_FC_BTFIFO_FULL		(1 << 5)
#define SSS_FC_BRFIFO_EMPTY		(1 << 6)
#define SSS_FC_BRFIFO_FULL		(1 << 7)

/* SSS_FC_FIFOCTRL */
#define SSS_FC_SELHASH_MASK		(3 << 0)
#define SSS_FC_SELHASH_EXOUT		(0 << 0)
#define SSS_FC_SELHASH_BCIN		(1 << 0)
#define SSS_FC_SELHASH_BCOUT		(2 << 0)
#define SSS_FC_SELBC_MASK		(1 << 2)
#define SSS_FC_SELBC_AES		(0 << 2)
#define SSS_FC_SELBC_DES		(1 << 2)

/* SSS_FC_GLOBAL */
#define SSS_FC_SSS_RESET		(1 << 0)
#define SSS_FC_DMA_RESET		(1 << 1)
#define SSS_FC_AES_RESET		(1 << 2)
#define SSS_FC_DES_RESET		(1 << 3)
#define SSS_FC_HASH_RESET		(1 << 4)
#define SSS_FC_AXI_ENDIAN_MASK		(3 << 6)
#define SSS_FC_AXI_ENDIAN_LE		(0 << 6)
#define SSS_FC_AXI_ENDIAN_BIBE		(1 << 6)
#define SSS_FC_AXI_ENDIAN_WIBE		(2 << 6)

/* Feed control - BRDMA control */
#define SSS_FC_BRDMACFLUSH_OFF		(0 << 0)
#define SSS_FC_BRDMACFLUSH_ON		(1 << 0)
#define SSS_FC_BRDMACSWAP_ON		(1 << 1)
#define SSS_FC_BRDMACARPROT_MASK	(0x7 << 2)
#define SSS_FC_BRDMACARPROT_OFS		(2)
#define SSS_FC_BRDMACARCACHE_MASK	(0xF << 5)
#define SSS_FC_BRDMACARCACHE_OFS	(5)

/* Feed control - BTDMA control */
#define SSS_FC_BTDMACFLUSH_OFF		(0 << 0)
#define SSS_FC_BTDMACFLUSH_ON		(1 << 0)
#define SSS_FC_BTDMACSWAP_ON		(1 << 1)
#define SSS_FC_BTDMACAWPROT_MASK	(0x7 << 2)
#define SSS_FC_BTDMACAWPROT_OFS		(2)
#define SSS_FC_BTDMACAWCACHE_MASK	(0xF << 5)
#define SSS_FC_BTDMACAWCACHE_OFS	(5)

/* Feed control - HRDMA control */
#define SSS_FC_HRDMACFLUSH_OFF		(0 << 0)
#define SSS_FC_HRDMACFLUSH_ON		(1 << 0)
#define SSS_FC_HRDMACSWAP_ON		(1 << 1)

/* Feed control - PKDMA control */
#define SSS_FC_PKDMACBYTESWAP_ON	(1 << 3)
#define SSS_FC_PKDMACDESEND_ON		(1 << 2)
#define SSS_FC_PKDMACTRANSMIT_ON	(1 << 1)
#define SSS_FC_PKDMACFLUSH_ON		(1 << 0)

/* Feed control - PKDMA offset */
#define SSS_FC_SRAMOFFSET_MASK		(0xFFF)

/* AES control */
#define SSS_AES_MODE_MASK		(1 << 0)
#define SSS_AES_MODE_ENC		(0 << 0)
#define SSS_AES_MODE_DEC		(1 << 0)
#define SSS_AES_OPERMODE_MASK		(3 << 1)
#define SSS_AES_OPERMODE_ECB		(0 << 1)
#define SSS_AES_OPERMODE_CBC		(1 << 1)
#define SSS_AES_OPERMODE_CTR		(2 << 1)
/*
TODO
CTS MODE define
*/
#define SSS_AES_OPERMODE_CTS		(3 << 1)

#define SSS_AES_FIFO_MASK		(1 << 3)
#define SSS_AES_FIFO_OFF		(0 << 3)
#define SSS_AES_FIFO_ON			(1 << 3)
#define SSS_AES_KEYSIZE_MASK		(3 << 4)
#define SSS_AES_KEYSIZE_128		(0 << 4)
#define SSS_AES_KEYSIZE_192		(1 << 4)
#define SSS_AES_KEYSIZE_256		(2 << 4)
#define SSS_AES_KEYCNGMODE_MASK		(1 << 6)
#define SSS_AES_KEYCNGMODE_OFF		(0 << 6)
#define SSS_AES_KEYCNGMODE_ON		(1 << 6)
#define SSS_AES_SWAP_MASK		(0x1F << 7)
#define SSS_AES_SWAPKEY_OFF		(0 << 7)
#define SSS_AES_SWAPKEY_ON		(1 << 7)
#define SSS_AES_SWAPCNT_OFF		(0 << 8)
#define SSS_AES_SWAPCNT_ON		(1 << 8)
#define SSS_AES_SWAPIV_OFF		(0 << 9)
#define SSS_AES_SWAPIV_ON		(1 << 9)
#define SSS_AES_SWAPDO_OFF		(0 << 10)
#define SSS_AES_SWAPDO_ON		(1 << 10)
#define SSS_AES_SWAPDI_OFF		(0 << 11)
#define SSS_AES_SWAPDI_ON		(1 << 11)
#define SSS_AES_COUNTERSIZE_MASK	(3 << 12)
#define SSS_AES_COUNTERSIZE_128		(0 << 12)
#define SSS_AES_COUNTERSIZE_64		(1 << 12)
#define SSS_AES_COUNTERSIZE_32		(2 << 12)
#define SSS_AES_COUNTERSIZE_16		(3 << 12)

/* AES status */
#define SSS_AES_OUTRDY_MASK		(1 << 0)
#define SSS_AES_OUTRDY_OFF		(0 << 0)
#define SSS_AES_OUTRDY_ON		(1 << 0)
#define SSS_AES_INRDY_MASK		(1 << 1)
#define SSS_AES_INRDY_OFF		(0 << 1)
#define SSS_AES_INRDY_ON		(1 << 1)
#define SSS_AES_BUSY_MASK		(1 << 2)
#define SSS_AES_BUSY_OFF		(0 << 2)
#define SSS_AES_BUSY_ON			(1 << 2)

/* TDES control */
#define SSS_TDES_MODE_MASK		(1 << 0)
#define SSS_TDES_MODE_ENC		(0 << 0)
#define SSS_TDES_MODE_DEC		(1 << 0)
#define SSS_TDES_OPERMODE_MASK		(1 << 1)
#define SSS_TDES_OPERMODE_ECB		(0 << 1)
#define SSS_TDES_OPERMODE_CBC		(1 << 1)
#define SSS_TDES_SEL_MASK		(3 << 3)
#define SSS_TDES_SEL_DES		(0 << 3)
#define SSS_TDES_SEL_TDESEDE		(1 << 3)
#define SSS_TDES_SEL_TDESEEE		(3 << 3)
#define SSS_TDES_FIFO_MASK		(1 << 5)
#define SSS_TDES_FIFO_OFF		(0 << 5)
#define SSS_TDES_FIFO_ON		(1 << 5)
#define SSS_TDES_SWAP_MASK		(0xF << 6)
#define SSS_TDES_SWAPKEY_OFF		(0 << 6)
#define SSS_TDES_SWAPKEY_ON		(1 << 6)
#define SSS_TDES_SWAPIV_OFF		(0 << 7)
#define SSS_TDES_SWAPIV_ON		(1 << 7)
#define SSS_TDES_SWAPDO_OFF		(0 << 8)
#define SSS_TDES_SWAPDO_ON		(1 << 8)
#define SSS_TDES_SWAPDI_OFF		(0 << 9)
#define SSS_TDES_SWAPDI_ON		(1 << 9)

/* TDES status */
#define SSS_TDES_OUTRDY_MASK		(1 << 0)
#define SSS_TDES_OUTRDY_OFF		(0 << 0)
#define SSS_TDES_OUTRDY_ON		(1 << 0)
#define SSS_TDES_INRDY_MASK		(1 << 1)
#define SSS_TDES_INRDY_OFF		(0 << 1)
#define SSS_TDES_INRDY_ON		(1 << 1)
#define SSS_TDES_BUSY_MASK		(1 << 2)
#define SSS_TDES_BUSY_OFF		(0 << 2)
#define SSS_TDES_BUSY_ON		(1 << 2)

/* Hash control */
#define SSS_HASH_ENGSEL_MASK		(0xF << 0)
#define SSS_HASH_ENGSEL_SHA1HASH	(0x0 << 0)
#define SSS_HASH_ENGSEL_SHA1HMAC	(0x1 << 0)
#define SSS_HASH_ENGSEL_SHA1HMACIN	(0x1 << 0)
#define SSS_HASH_ENGSEL_SHA1HMACOUT	(0x9 << 0)
#define SSS_HASH_ENGSEL_MD5HASH		(0x2 << 0)
#define SSS_HASH_ENGSEL_MD5HMAC		(0x3 << 0)
#define SSS_HASH_ENGSEL_MD5HMACIN	(0x3 << 0)
#define SSS_HASH_ENGSEL_MD5HMACOUT	(0xB << 0)
#define SSS_HASH_ENGSEL_SHA256HASH	(0x4 << 0)
#define SSS_HASH_ENGSEL_SHA256HMAC	(0x5 << 0)
#define SSS_HASH_ENGSEL_PRNG		(0x8 << 0)
#define SSS_HASH_STARTBIT_ON		(1 << 4)
#define SSS_HASH_USERIV_EN		(1 << 5)

/* Hash control 2 */
#define SSS_HASH_PAUSE_ON		(1 << 0)

/* Hash control - FIFO mode */
#define SSS_HASH_FIFO_MASK		(1 << 0)
#define SSS_HASH_FIFO_OFF		(0 << 0)
#define SSS_HASH_FIFO_ON		(1 << 0)

/* Hash control - byte swap */
#define SSS_HASH_SWAP_MASK		(0xF << 0)
#define SSS_HASH_SWAPKEY_OFF		(0 << 0)
#define	SSS_HASH_SWAPKEY_ON		(1 << 0)
#define SSS_HASH_SWAPIV_OFF		(0 << 1)
#define	SSS_HASH_SWAPIV_ON		(1 << 1)
#define SSS_HASH_SWAPDO_OFF		(0 << 2)
#define SSS_HASH_SWAPDO_ON		(1 << 2)
#define SSS_HASH_SWAPDI_OFF		(0 << 3)
#define SSS_HASH_SWAPDI_ON		(1 << 3)

/* Hash status */
#define SSS_HASH_BUFRDY_MASK		(1 << 0)
#define SSS_HASH_BUFRDY_OFF		(0 << 0)
#define SSS_HASH_BUFRDY_ON		(1 << 0)
#define SSS_HASH_SEEDSETTING_MASK	(1 << 1)
#define SSS_HASH_SEEDSETTING_OFF	(0 << 1)
#define SSS_HASH_SEEDSETTING_ON		(1 << 1)
#define SSS_HASH_PRNGBUSY_MASK		(1 << 2)
#define SSS_HASH_PRNGBUSY_OFF		(0 << 2)
#define SSS_HASH_PRNGBUSY_ON		(1 << 2)
#define SSS_HASH_PARTIALDONE_MASK	(1 << 4)
#define SSS_HASH_PARTIALDONE_OFF	(0 << 4)
#define SSS_HASH_PARTIALDONE_ON		(1 << 4)
#define SSS_HASH_PRNGDONE_MASK		(1 << 5)
#define SSS_HASH_PRNGDONE_OFF		(0 << 5)
#define SSS_HASH_PRNGDONE_ON		(1 << 5)
#define SSS_HASH_MSGDONE_MASK		(1 << 6)
#define SSS_HASH_MSGDONE_OFF		(0 << 6)
#define SSS_HASH_MSGDONE_ON		(1 << 6)
#define SSS_HASH_PRNGERROR_MASK		(1 << 7)
#define SSS_HASH_PRNGERROR_OFF		(0 << 7)
#define SSS_HASH_PRNGERROR_ON		(1 << 7)

#endif /* __CRYPTODXE_H__ */

