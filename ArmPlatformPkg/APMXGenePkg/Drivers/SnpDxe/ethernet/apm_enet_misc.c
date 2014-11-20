/**
 * AppliedMicro APM88xxxx Ethernet Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Mahesh Pujara <mpujara@apm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * @file apm_enet_misc.c
 *
 * This file implements driver for RGMII, MAC and statistics blocks of
 * APM88xxxx Ethernet subsystem
 *
 */

#include "apm_enet_access.h"
#include "apm_enet_csr.h"
#ifndef BOOTLOADER
#include <linux/of_irq.h>
#endif

int apm_enet_parse_error(u8 LErr, u8 HC, int qid)
{
	if (HC == 0) {
		/* Ethernet error */
		switch(LErr) {
		case ENET_AXI_WR_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: AXI write data error\n",
				LErr, qid);
			return 1;
		case ENET_ING_CRC_ERR:
			ENET_DEBUG(
				"LErr[%d] QID %d: Rx packet CRC Error\n",
				LErr, qid);
			return 1;
		case ENET_AXI_RD_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: AXI read data error\n",
				LErr, qid);
			return 0;
		case ENET_LL_RD_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: AXI Link List read error\n",
				LErr, qid);
			return 0;
		case ENET_CHKSUM_ERR:
			ENET_DEBUG(
				"LErr[%d] QID %d: Rx packet checksum error\n",
				LErr, qid);
			return 1;
		case ENET_BAD_MSG_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: bad QM message H0/H1 is 0 error\n",
				LErr, qid);
			return 0;
#if defined(CONFIG_APM862xx)
		case ENET_MISC_ERR:
			ENET_DEBUG_ERR("LErr[%d] QID %d: misc error\n",
				LErr, qid);
			return 1;
#else
		case ENET_MAC_TRUNC_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: Rx packet truncated error\n",
				LErr, qid);
			return 1;
		case ENET_MAC_LEN_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: Rx packet length field mismatch error\n",
				LErr, qid);
			return 1;
		case ENET_PKT_LESS64_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: Rx packet length lesser than 64B error\n",
				LErr, qid);
			return 1;
		case ENET_MAC_OVERRUN_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: Rx FIFO overrun error\n",
				LErr, qid);
			return 1;
		case ENET_UNISEC_CHKSUM_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: IPSec checksum error\n",
				LErr, qid);
			return 1;
		case ENET_UNISEC_LEN_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: IPSec length field error\n",
				LErr, qid);
			return 1;
		case ENET_UNISEC_ICV_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: IPSec ICV field mismatch error\n",
				LErr, qid);
			return 1;
		case ENET_UNISEC_PROTO_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: IPSec protocol field mismatch error\n",
				LErr, qid);
			return 1;
		case ENET_FP_TIMEOUT_ERR:
			ENET_DEBUG_ERR(
				"LErr[%d] QID %d: Unavailable free pool errro\n",
				LErr, qid);
			return 1;
#endif
		default:
			ENET_DEBUG_ERR("LErr[%d] QID %d: Unknown Error\n",
				LErr, qid);
			break;
		}
	}

	/* QM Error */
	switch(LErr) {
	case 1:
		ENET_DEBUG_ERR("LErr[%d] QID %d: QM msg size error\n",
			LErr, qid);
		return 0;
	case 2:
		ENET_DEBUG_ERR("LErr[%d] QID %d: QM msg hop count error\n",
			LErr, qid);
		return 0;
	case 3:
		ENET_DEBUG_ERR("LErr[%d] QID %d: enqueue to virtual queue error\n",
			LErr, qid);
		return 0;
	case 4:
		ENET_DEBUG_ERR("LErr[%d] QID %d: enqueue to disable queue error\n",
			LErr, qid);
		return 0;
	case 5:
		/* NOTE: From testing, it seems like this error is the
		         same as checksum error in APM867xx */
		ENET_DEBUG("LErr[%d] QID %d: queue overfill error\n",
			LErr, qid);
		return 1;
	case 6:
		ENET_DEBUG_ERR("LErr[%d] QID %d: QM enqueue error\n",
			LErr, qid);
		return 0;
	case 7:
		ENET_DEBUG_ERR("LErr[%d] QID %d: QM dequeue error\n",
			LErr, qid);
		return 0;
	}
	return 0;
}

int apm_enet_get_pb_cnt(struct apm_enet_priv *priv, int pbn)
{
	u32 val;
	u32 reg_offset = ENET_STSSSQMIFPNUMENTRIES0_ADDR + ((pbn / 8) * 4);
	u32 pbn_offset = pbn % 8; 

	apm_enet_read(priv, BLOCK_ETH_QMI, reg_offset, &val);

	ENET_DEBUG("%a: %d: reg_offset 0x%08x pbn_offset 0x%08x val 0x%08x\n",
		__func__, __LINE__, reg_offset, pbn_offset, val);

	return (val >> (pbn_offset * 4)) & 0xf;
}

void apm_enet_qmi_read_pb_msg(struct apm_enet_priv *priv, u32 pbn,
				u32 addroffset, u32 last, u32 *msg)
{
	u32 data = 0;
	u32 count = 0;

	data = ENET_PBID_SET(data, pbn);
#ifdef CONFIG_APM862xx
	data = ENET_READ_SET(data, 1);
#else /* CONFIG_APM867xx || CONFIG_APM866xx */
	data = ENET_READ_F2_SET(data, 1);
#endif

	data = ENET_NACK_SET(data, 1);
	data = ENET_BUFFERADDR_SET(data, addroffset);
	data = ENET_LAST_SET(data, last);
	*msg = 0;

	apm_enet_write(priv, BLOCK_ETH_QMI,
			ENET_CFGSSQMIDBGCTRL_ADDR, data);

	/* wait for the request completion */
	do {
		apm_enet_read(priv, BLOCK_ETH_QMI,
				ENET_CFGSSQMIDBGCTRL_ADDR, &data);
	} while ((ENET_NACK_RD(data) != 0) && (count++ < 200000));

	if (count >= 200000) {
		ENET_DEBUG_ERR("Failed to read PB\n");
		return;
	}

	/* read the 32 bit data from STSSSQMIDBGDATA register */
	apm_enet_read(priv, BLOCK_ETH_QMI,
			ENET_STSSSQMIDBGDATA_ADDR, msg);
}

void apm_enet_qmi_pop_pb_msg(struct apm_enet_priv *priv, u32 pbn,
				u32 addroffset, u32 last, u32 *msg)
{
	u32 data = 0;
	u32 count = 0;

	data = ENET_PBID_SET(data, pbn);
	data = ENET_POP_SET(data, 1);
	data = ENET_NACK_SET(data, 1);
	data = ENET_BUFFERADDR_SET(data, addroffset);
	data = ENET_LAST_SET(data, last);
	*msg = 0;

	apm_enet_write(priv, BLOCK_ETH_QMI,
			ENET_CFGSSQMIDBGCTRL_ADDR, data);

	/* wait for the request completion */
	do {
		apm_enet_read(priv, BLOCK_ETH_QMI,
				ENET_CFGSSQMIDBGCTRL_ADDR, &data);
	} while ((ENET_NACK_RD(data) != 0) && (count++ < 200000));

	if (count >= 200000) {
		ENET_DEBUG_ERR("Failed to pop PB\n");
		return;
	}

	/* read the 32 bit data from STSSSQMIDBGDATA register */
	apm_enet_read(priv, BLOCK_ETH_QMI,
			ENET_STSSSQMIDBGDATA_ADDR, msg);
}

#ifdef INT_SUPPORT
void apm_enet_unmask_int(struct apm_enet_priv *priv)
{
#if defined(INT_ENABLE)
	/* Unmask Enet Error Interrupts per port */
	apm_enet_write(priv, BLOCK_ETH_CSR, RSIF_INT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, RSIF_FINT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, TSIF_INT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, TSIF_FINT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, TSO_INT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, SPI2SAP_INT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR,
			RX_TX_BUF_CHKSM_INT_REG0MASK_ADDR, 0);

	/* Unmask all Enet MAC Error Interrupts */
	apm_enet_write(priv, BLOCK_MCX_MAC_CSR, MAC_INT_REG0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_MCX_MAC_CSR, MAC_INT_REG1MASK_ADDR, 0);

	/* Unmask all Enet MAC Error Interrupts */
	apm_enet_write(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT0MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT1MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT2MASK_ADDR, 0);
	apm_enet_write(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT4MASK_ADDR, 0);
#endif
}

irqreturn_t apm_enet_qmi_err_irq(int irq, void *dev_instance)
{
	struct apm_enet_priv *priv = get_priv(dev_instance);
	int rc;
	u32 data;
	u32 int_mask = 0;

	ENET_DEBUG_ERR("Received Ethernet QMI Error Interrupt\n");
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT0_ADDR, &data);
	if (data) {
		ENET_DEBUG_ERR("Received STSSSQMIINT0 Error Interrupt \n");
		if (ENET_FPOVERFLOW0_RD(data)) {
			ENET_DEBUG_ERR("FP PB overflow indication:0x%08X\n",
				       data);
			int_mask |= ENET_FPOVERFLOW0_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  ENET_STSSSQMIINT0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT1_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received STSSSQMIINT1 Error Interrupt\n");
		if (ENET_WQOVERFLOW1_RD(data)) {
			ENET_DEBUG_ERR("WQ PB overflow indication:0x%08X \n",
				       data);
			int_mask |= ENET_WQOVERFLOW1_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  ENET_STSSSQMIINT1_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT2_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received STSSSQMIINT2  Error Interrupt\n");
		if (ENET_FPUNDERRUN2_RD(data)) {
			ENET_DEBUG_ERR("FP PB underrun indication:0x%08X \n",
				       data);
			int_mask |= ENET_FPUNDERRUN2_MASK;
		}

		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  ENET_STSSSQMIINT2_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT3_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received STSSSQMIINT3 Error Interrupt\n");
		if (ENET_WQUNDERRUN3_RD(data)) {
			ENET_DEBUG_ERR("WQ PB underrun indication:0x%08X \n",
				       data);
			int_mask |= ENET_WQUNDERRUN3_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  ENET_STSSSQMIINT3_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, ENET_STSSSQMIINT4_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received STSSSQMIINT4 Error Interrupt\n");
		if (ENET_AXIWCMR_SLVERR4_RD(data)) {
			ENET_DEBUG_ERR("AXI slave error on write"
				       " master channel \n");
			int_mask |= ENET_AXIWCMR_SLVERR4_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  ENET_STSSSQMIINT4_ADDR, int_mask);
	}
	return IRQ_HANDLED;
}

irqreturn_t apm_enet_mac_err_irq(int irq, void *dev_instance)
{
	struct apm_enet_priv *priv = get_priv(dev_instance);
	int rc;
	u32 data;
	u32 int_mask = 0;

	ENET_DEBUG_ERR("Received Ethernet MAC Error Interrupt\n");

	rc = apm_enet_read(priv, BLOCK_MCX_MAC_CSR, MAC_INT_REG0_ADDR, &data);
	if (data) {
		ENET_DEBUG_ERR("Received MAC Error Interrupt\n");

		if (ICM_DATA_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 ICM Data fifo"
					"underflow interrupt \n");
			int_mask |= ICM_DATA_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if (ICM_DATA_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 ICM Data fifo"
					"overflow interrupt \n");
			int_mask |= ICM_DATA_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if (ICM_CTRL_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 ICM Ctrl fifo"
					"underflow Interrupt \n");
			int_mask |= ICM_CTRL_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if (ICM_CTRL_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 ICM Ctrl fifo"
					"overflow Interrupt \n");
			int_mask |= ICM_CTRL_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if (ECM_DATA_FIFO_UNDERN_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 ECM Data fifo"
					"underrun interrupt \n");
			int_mask |= ECM_DATA_FIFO_UNDERN_INTR_PRT10_MASK;
		}
		if ECM_DATA_FIFO_UNDERFL_INTR_PRT10_RD((data)) {
			ENET_DEBUG_ERR("TxPort1 ECM Data fifo"
					"underflow interrupt \n");
			int_mask |= ECM_DATA_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if ECM_DATA_FIFO_OVERFL_INTR_PRT10_RD((data)) {
			ENET_DEBUG_ERR("TxPort1 ECM Data fifo"
					"overflow interrupt \n");
			int_mask |= ECM_DATA_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if (MACIF_FIFO_UNDERFL_INTR_RXPRT10_F2_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 Mac i/f fifo"
					"underflow interrupt \n");
			int_mask |= MACIF_FIFO_UNDERFL_INTR_RXPRT10_F2_MASK;
		}
		if (MACIF_FIFO_OVERFL_INTR_RXPRT10_F2_RD(data)) {
			ENET_DEBUG_ERR("RxPort1 Mac i/f fifo"
					"overflow interrupt \n");
			int_mask |= MACIF_FIFO_OVERFL_INTR_RXPRT10_F2_MASK;
		}
		if (ICM_DATA_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 ICM Data fifo"
					"underflow interrupt \n");
			int_mask |= ICM_DATA_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if (ICM_DATA_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 ICM Data fifo"
					"overflow interrupt \n");
			int_mask |= ICM_DATA_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if (ICM_CTRL_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 ICM Ctrl fifo"
					"underflow Interrupt \n");
			int_mask |= ICM_CTRL_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if (ICM_CTRL_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 ICM Ctrl fifo"
					"overflow Interrupt \n");
			int_mask |= ICM_CTRL_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if (ECM_DATA_FIFO_UNDERN_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 ECM Data fifo"
					"underrun interrupt \n");
			int_mask |= ECM_DATA_FIFO_UNDERN_INTR_PRT00_MASK;
		}
		if ECM_DATA_FIFO_UNDERFL_INTR_PRT00_RD((data)) {
			ENET_DEBUG_ERR("TxPort0 ECM Data fifo"
					"underflow interrupt \n");
			int_mask |= ECM_DATA_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if ECM_DATA_FIFO_OVERFL_INTR_PRT00_RD((data)) {
			ENET_DEBUG_ERR("TxPort0 ECM Data fifo"
					"overflow interrupt \n");
			int_mask |= ECM_DATA_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if (MACIF_FIFO_UNDERFL_INTR_RXPRT00_F2_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 Mac i/f fifo"
					"underflow interrupt \n");
			int_mask |= MACIF_FIFO_UNDERFL_INTR_RXPRT00_F2_MASK;
		}
		if (MACIF_FIFO_OVERFL_INTR_RXPRT00_F2_RD(data)) {
			ENET_DEBUG_ERR("RxPort0 Mac i/f fifo"
					"overflow interrupt \n");
			int_mask |= MACIF_FIFO_OVERFL_INTR_RXPRT00_F2_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
				MAC_INT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_MCX_MAC_CSR, MAC_INT_REG1_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received MAC Error Interrupt1\n");
		if (LINKDOWN_PORT11_RD(data)) {
			ENET_DEBUG_ERR("Port1:Link Down Interrupt \n");
			int_mask |= LINKDOWN_PORT11_MASK;
		}
		if (CARRY_PORT11_RD(data)) {
			ENET_DEBUG_ERR("Carry Interrupt for Status"
					" Register Overflow for Port 1\n");
			int_mask |= CARRY_PORT11_MASK;
		}
		if (LINKDOWN_PORT01_RD(data)) {
			ENET_DEBUG_ERR("Port0:Link Down Interrupt \n");
			int_mask |= LINKDOWN_PORT01_MASK;
		}
		if (CARRY_PORT01_RD(data)) {
			ENET_DEBUG_ERR("Carry Interrupt for Status"
					" Register Overflow for Port 0\n");
			int_mask |= CARRY_PORT01_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
				MAC_INT_REG1_ADDR, int_mask);
	}
	return IRQ_HANDLED;
}

irqreturn_t apm_enet_err_irq(int irq, void *dev_instance)
{
	struct apm_enet_priv *priv = get_priv(dev_instance);
	int rc;
	u32 data;
	u32 int_mask = 0;

	rc = apm_enet_read(priv, BLOCK_ETH_CSR, RSIF_INT_REG0_ADDR, &data);
	if (data) {
		ENET_DEBUG_ERR("Received RSIF Error Interrupt\n");
		if (RSIF_LCL_RXBUF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 Local Rxbuff FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_LCL_RXBUF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if (RSIF_LCL_RXBUF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 Local Rxbuff FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_LCL_RXBUF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_CHKSUM_BUFF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 chksum buff FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_CHKSUM_BUFF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_CHKSUM_BUFF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 chksum buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
			      RSIF_CHKSUM_BUFF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_TIMESTAMP_BUFF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 timestamp buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
			     RSIF_TIMESTAMP_BUFF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_TIMESTAMP_BUFF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 timestamp FIFO"
					"underflow interrupt \n");
			int_mask |=
			    RSIF_TIMESTAMP_BUFF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_ERR_BUFF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 err buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_ERR_BUFF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_ERR_BUFF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 err buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_ERR_BUFF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_CLEBUFF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 classifier buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_CLEBUFF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_CLEBUFF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 classifier buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_CLEBUFF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_CTRLBUFF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 ctrl buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_CTRLBUFF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_CTRLBUFF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR(" Rx port1 ctrl buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_CTRLBUFF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_BUF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 buffer FIFO"
					"overflow interrupt \n");
			int_mask |= RSIF_BUF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(RSIF_BUF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 buffer FIFO"
					 "underflow interrupt \n");
			int_mask |= RSIF_BUF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(ENET_RSIF_PLC_CLEBUFF_FIFO_OVERFL_INTR0_RD(data)) {
			ENET_DEBUG_ERR("Policer CLE FIFO"
				       "overflow interrupt \n");
			int_mask |=
				ENET_RSIF_PLC_CLEBUFF_FIFO_OVERFL_INTR0_MASK;
		}
		if(ENET_RSIF_PLC_CLEBUFF_FIFO_UNDERFL_INTR0_RD(data)) {
			ENET_DEBUG_ERR("Policer CLE FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_LCL_RXBUF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_LCL_RXBUF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 Local Rx buffer FIFO"
					"overflow interrupt} \n");
			int_mask |=
				RSIF_LCL_RXBUF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_LCL_RXBUF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 Local Rx buffer FIFO"
					 "underflow interrupt \n");
			int_mask |=
				RSIF_LCL_RXBUF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_CHKSUM_BUFF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 chksum buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_CHKSUM_BUFF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_CHKSUM_BUFF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 chksum buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
			    RSIF_CHKSUM_BUFF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_TIMESTAMP_BUFF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 timestamp buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
			     RSIF_TIMESTAMP_BUFF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_TIMESTAMP_BUFF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 timestamp FIFO"
					"underflow interrupt \n");
			int_mask |=
			    RSIF_TIMESTAMP_BUFF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_ERR_BUFF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 err buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_ERR_BUFF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_ERR_BUFF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 err buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_ERR_BUFF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_CLEBUFF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 classifier buffer FIFO"
					"overflow interrupt \n");
			int_mask |= RSIF_CLEBUFF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}

		if(RSIF_CLEBUFF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 classifier buffer FIFO"
					"underflow interrupt \n");
			int_mask |=
				RSIF_CLEBUFF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_CTRLBUFF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 ctrl buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_CTRLBUFF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_CTRLBUFF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 ctrl buffer FIFO"
					"overflow interrupt \n");
			int_mask |=
				RSIF_CTRLBUFF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_BUF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 buffer FIFO"
					"overflow interrupt \n");
			int_mask |= RSIF_BUF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(RSIF_BUF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 buffer FIFO"
					"underflow interrupt \n");
			int_mask |= RSIF_BUF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				RSIF_INT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, RSIF_FINT_REG0_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received RSIF Error2 Interrupt\n");
		if(RSIF_SS_MIRRORERR_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Mirror buffer address offset/length do"
					"not match with normal xfr address"
					"offset/length in port1 \n");
			int_mask |= RSIF_SS_MIRRORERR_INTR_RXPRT10_MASK;
		}
		if(RSIF_SS_SPLIT_BOUNDARY_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Split boundary cannot be accomodated"
					"in the firt buffer in port1 \n");
			int_mask |= RSIF_SS_FPBUFF_TIMEOUT_INTR_RXPRT10_MASK;
		}
		if(RSIF_SS_FPBUFF_TIMEOUT_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Packet dropped by RSIF because "
					"freepool buffer was NOT available from"
					" QMI on port1 \n");
			int_mask |= RSIF_SS_FPBUFF_TIMEOUT_INTR_RXPRT10_MASK;
		}
		if(RSIF_SS_AXI_WRERR_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("AXI write error on port1 \n");
			int_mask |= RSIF_SS_AXI_WRERR_INTR_RXPRT10_MASK;
		}
		if(RSIF_SS_MIRRORERR_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Mirror buffer address offset/length"
					"do not match with normal xfr address"
					"offset/length in port0 \n");
			int_mask |= RSIF_SS_MIRRORERR_INTR_RXPRT00_MASK;
		}
		if(RSIF_SS_SPLIT_BOUNDARY_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Split boundary cannot be accomodated"
					"in the firt buffer in port0 \n");
			int_mask |= RSIF_SS_SPLIT_BOUNDARY_INTR_RXPRT00_MASK;
		}
		if(RSIF_SS_FPBUFF_TIMEOUT_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Packet dropped by RSIF because "
					"freepool buffer was NOT available from"
					" QMI on port0 \n");
			int_mask |= RSIF_SS_FPBUFF_TIMEOUT_INTR_RXPRT00_MASK;
		}
		if(RSIF_SS_AXI_WRERR_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("AXI write error on port0 \n");
			int_mask |= RSIF_SS_AXI_WRERR_INTR_RXPRT00_MASK;
		}
		if(STS_RSIF_PLC_DROP0_RD(data)) {
			ENET_DEBUG_ERR("Packet dropped by policer \n");
			int_mask |= STS_RSIF_PLC_DROP0_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				RSIF_FINT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, TSIF_INT_REG0_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received TSIF Error Interrupt\n");
		if(TSIF_RDMBUFF_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 RDM buffer FIFO"
					"overflow interrupt \n");
			int_mask |= TSIF_RDMBUFF_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if(TSIF_RDMBUFF_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 RDM buffer FIFO"
					"underflow interrupt \n");
			int_mask |= TSIF_RDMBUFF_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(TSIF_RRM_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 RRM buffer FIFO"
					"overflow interrupt \n");
			int_mask |= TSIF_RRM_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if(TSIF_RRM_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 RRM buffer FIFO"
					"underflow interrupt \n");
			int_mask |= TSIF_RRM_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(TSIF_AMABUF_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 AMA buffer FIFO"
					"overflow interrupt \n");
			int_mask |= TSIF_AMABUF_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if(TSIF_AMABUF_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 AMA buffer FIFO"
					"underflow interrupt \n");
			int_mask |= TSIF_AMABUF_FIFO_UNDERFL_INTR_PRT10_MASK;
		}

		if(TSIF_RDMBUFF_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 RDM buffer FIFO"
					"overflow interrupt \n");
			int_mask |= TSIF_RDMBUFF_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if(TSIF_RDMBUFF_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 RDM buffer FIFO"
					"underflow interrupt \n");
			int_mask |= TSIF_RDMBUFF_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if(TSIF_RRM_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 RRM buffer FIFO"
					"overflow interrupt \n");
			int_mask |= TSIF_RRM_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if(TSIF_RRM_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 RRM buffer FIFO"
					"underflow interrupt \n");
			int_mask |= TSIF_RRM_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if(TSIF_AMABUF_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 AMA buffer FIFO"
					"overflow interrupt \n");
			int_mask |= TSIF_AMABUF_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if(TSIF_AMABUF_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 AMA buffer FIFO"
					"underflow interrupt \n");
			int_mask |= TSIF_AMABUF_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  TSIF_INT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, TSIF_FINT_REG0_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received TSIF Error Interrupt\n");
		if(TSIF_SS_AXI_LLRDERR_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("AXI error when reading data"
					"from port1 \n");
			int_mask |= TSIF_SS_AXI_LLRDERR_INTR_PRT10_MASK;
		}
		if(TSIF_SS_AXI_RDERR_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("AXI error when reading data"
					"from port1 \n");
			int_mask |= TSIF_SS_AXI_RDERR_INTR_PRT10_MASK;
		}
		if(TSIF_SS_BAD_MSG_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Bad message received by TSIF"
					"on port1 \n");
			int_mask |= TSIF_SS_BAD_MSG_INTR_PRT10_MASK;
		}
		if(TSIF_SS_AXI_LLRDERR_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("AXI error when reading data"
					"from port0 \n");
			int_mask |= TSIF_SS_AXI_LLRDERR_INTR_PRT00_MASK;
		}
		if(TSIF_SS_AXI_RDERR_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("AXI error when reading data"
					"from port0 \n");
			int_mask |= TSIF_SS_AXI_RDERR_INTR_PRT00_MASK;
		}
		if(TSIF_SS_BAD_MSG_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Bad message received by TSIF"
					"on port0 \n");
			int_mask |= TSIF_SS_BAD_MSG_INTR_PRT00_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				TSIF_FINT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, TSO_INT_REG0_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received TSO Error Interrupt\n");
		if(MB_TTF_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 tso_txbuff FIFO"
					"overflow interrupt \n");
			int_mask |= MB_TTF_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if(MB_TTF_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 tso_txbuff FIFO"
					"underflow interrupt \n");
			int_mask |= MB_TTF_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(MH_DEALLOC_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Dealloc FIFO"
					"overflow interrupt \n");
			int_mask |= MH_DEALLOC_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if(MH_DEALLOC_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Dealloc FIFO"
					"underflow interrupt \n");
			int_mask |= MH_DEALLOC_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(MH_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Message Hold FIFO"
					"overflow interrupt \n");
			int_mask |= MH_FIFO_OVERFL_INTR_PRT10_MASK;
		}
		if(MH_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Message Hold FIFO"
					"underflow interrupt \n");
			int_mask |= MH_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(MB_TTF_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 tso_txbuff FIFO"
					"overflow interrupt \n");
			int_mask |= MB_TTF_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if(MB_TTF_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 tso_txbuff FIFO"
					"underflow interrupt \n");
			int_mask |= MB_TTF_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if(MH_DEALLOC_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 Dealloc FIFO"
					"overflow interrupt \n");
			int_mask |= MH_DEALLOC_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if(MH_DEALLOC_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Dealloc FIFO"
					"underflow interrupt \n");
			int_mask |= MH_DEALLOC_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if(MH_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Message Hold FIFO"
					"overflow interrupt \n");
			int_mask |= MH_FIFO_OVERFL_INTR_PRT00_MASK;
		}
		if(MH_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Message Hold FIFO"
					"underflow interrupt \n");
			int_mask |= MH_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				TSO_INT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR, SPI2SAP_INT_REG0_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received SPI2SAP Error Interrupt\n");
		if(MACIF_FIFO_OVERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 SAP FIFO overflow"
					"interrupt \n");
			int_mask |= MACIF_FIFO_OVERFL_INTR_RXPRT10_MASK;
		}
		if(MACIF_FIFO_UNDERFL_INTR_RXPRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 SAP FIFO underflow"
					"interrupt \n");
			int_mask |= MACIF_FIFO_UNDERFL_INTR_RXPRT10_MASK;
		}
		if(MACIF_FIFO_OVERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 SAP FIFO overflow"
					"interrupt \n");
			int_mask |= MACIF_FIFO_OVERFL_INTR_RXPRT00_MASK;
		}
		if(MACIF_FIFO_UNDERFL_INTR_RXPRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 SAP FIFO underflow"
					"interrupt \n");
			int_mask |= MACIF_FIFO_UNDERFL_INTR_RXPRT00_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  SPI2SAP_INT_REG0_ADDR, int_mask);
	}
	rc = apm_enet_read(priv, BLOCK_ETH_CSR,
			  RX_TX_BUF_CHKSM_INT_REG0_ADDR, &data);
	int_mask = 0;
	if (data) {
		ENET_DEBUG_ERR("Received RX/TX Buffer Checksum Error"
				"Interrupt\n");
		if(RXBUF_PAUSE_INTR_PORT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 Pause interrupt\n");
			int_mask |= RXBUF_PAUSE_INTR_PORT10_MASK ;
		}
		if(RX_CHKSUM_INTR_PORT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 Chksum Error interrupt \n");
			int_mask |= RX_CHKSUM_INTR_PORT10_MASK;
		}
		if(TX_CHKSUM_INTR_PORT10_RD(data)) {
			ENET_DEBUG_ERR("Tx port1 Chksum Error interrupt \n");
			int_mask |= TX_CHKSUM_INTR_PORT10_MASK;
		}
		if(RXBUF_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 rx buffer FIFO "
				       "overflow interrupt \n");
			int_mask |= RXBUF_FIFO_OVERFL_INTR_PRT10_MASK ;
		}
		if(RXBUF_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 rx buffer FIFO "
					"underflow interrupt \n");
			int_mask |= RXBUF_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(TXBUF_FIFO_OVERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 rx buffer FIFO "
					"overflow interrupt \n");
			int_mask |= RXBUF_FIFO_OVERFL_INTR_PRT10_MASK ;
		}
		if(TXBUF_FIFO_UNDERFL_INTR_PRT10_RD(data)) {
			ENET_DEBUG_ERR("Rx port1 rx buffer FIFO "
					"underflow interrupt \n");
			int_mask |= RXBUF_FIFO_UNDERFL_INTR_PRT10_MASK;
		}
		if(RXBUF_PAUSE_INTR_PORT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 Pause interrupt\n");
			int_mask |= RXBUF_PAUSE_INTR_PORT00_MASK ;
		}
		if(RX_CHKSUM_INTR_PORT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 Chksum Error interrupt \n");
			int_mask |= RX_CHKSUM_INTR_PORT00_MASK;
		}
		if(TX_CHKSUM_INTR_PORT00_RD(data)) {
			ENET_DEBUG_ERR("Tx port0 Chksum Error interrupt \n");
			int_mask |= TX_CHKSUM_INTR_PORT00_MASK;
		}
		if(RXBUF_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 rx buffer FIFO "
					"overflow interrupt \n");
			int_mask |= RXBUF_FIFO_OVERFL_INTR_PRT00_MASK ;
		}
		if(RXBUF_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 rx buffer FIFO "
					"underflow interrupt \n");
			int_mask |= RXBUF_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		if(TXBUF_FIFO_OVERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 rx buffer FIFO "
					"overflow interrupt \n");
			int_mask |= RXBUF_FIFO_OVERFL_INTR_PRT00_MASK ;
		}
		if(TXBUF_FIFO_UNDERFL_INTR_PRT00_RD(data)) {
			ENET_DEBUG_ERR("Rx port0 rx buffer FIFO "
					"underflow interrupt \n");
			int_mask |= RXBUF_FIFO_UNDERFL_INTR_PRT00_MASK;
		}
		/* Clear Interrupt status bits, its COW */
		rc = apm_enet_write(priv, BLOCK_ETH_CSR,
				  RX_TX_BUF_CHKSM_INT_REG0_ADDR, int_mask);
	}
	return IRQ_HANDLED;
}

#else
#define apm_enet_unmask_int 	NULL
#define apm_enet_qmi_err_irq   	NULL
#define apm_enet_mac_err_irq 	NULL
#define apm_enet_err_irq 	NULL
#endif

