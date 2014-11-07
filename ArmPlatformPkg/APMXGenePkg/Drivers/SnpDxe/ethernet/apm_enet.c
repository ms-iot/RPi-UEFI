/**
 * AppliedMicro X-Gene SOC Ethernet U-Boot Source file
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * Author: Keyur Chudgar <kchudgar@apm.com>
 *         Ravi Patel <rapatel@apm.com>
 *         Fushen Chen <fchen@apm.com>
 *         Iyappan Subramanian <isubramanian@apm.com>
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
 * @file apm_enet.c
 *
 */
#include "../mustang.h"
#include "../qm/xgene_qmtm.h"
#include "apm_enet_access.h"
#ifndef APM_XGENE
#include <asm/io.h>
#include <watchdog.h>
#endif

#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>
#include <Library/UefiLib.h>

#include "apm_enet_mac.h"
#include "apm_xgenet_mac.h"
#include "apm_enet_misc.h"
#include "apm_enet_csr.h"
#ifndef APM_XGENE
#include "../drivers/misc/xgene/qmtm/xgene_qmtm_core.h"
#include <misc/xgene/qmtm/xgene_qmtm.h>
#include <misc/xgene/cle/apm_preclass_data.h>
#else
#include "../qm/xgene_qmtm_core.h"
#include "../classifier/apm_preclass_data.h"
#define SPEED_10000           10000
#define SPEED_1000           1000
#endif
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
#include <miiphy.h>
#endif

#ifdef CONFIG_CMD_I2C
#include <i2c.h>
#ifdef CONFIG_STORM
#define SPFF_I2C_BUS    1
#else
#define SPFF_I2C_BUS    3
#endif
#define SPFF_I2C_CH_ADDR     0x71
#define SPFF_I2C_OUT0_ADDR   0x26 /* XG0, XG1 laser control */
#define SPFF_I2C_OUT1_ADDR   0x27 /* XG2, XG3 */
#define IN_OFFSET  0
#define OUT_OFFSET 1
#define CONFIG_OFFSET 3
u32 sfp_addr[4] = {SPFF_I2C_OUT0_ADDR, SPFF_I2C_OUT0_ADDR,
                   SPFF_I2C_OUT1_ADDR, SPFF_I2C_OUT1_ADDR};
u32 sfp_abs[4] = {0x20, 0x2, 0x20, 0x2};
u32 sfp_laser_on[4] = {0xef, 0xfe, 0xef, 0xfe};
u32 sfp_laser_off[4] = {0xff, 0xff, 0xff, 0xff};
#endif

#ifdef CONFIG_OCM_U_BOOT
#define QSIZE QSIZE_2KB
#else
#define QSIZE QSIZE_16KB
#endif

#undef PCM_LOOPBACK
#ifndef APM_XGENE
DECLARE_GLOBAL_DATA_PTR;
#endif

static struct apm_enet_dev *pdev[MAX_ENET_PORTS];
struct eth_device *emac_dev[MAX_ENET_PORTS];

static u8  phy_mode[MAX_ENET_PORTS];
static u32 phy_addr[MAX_ENET_PORTS];

/* Ethernet raw register write routine */
inline void apm_enet_wr32(void *addr, u32 data)
{
	ENET_REG_WR("Write addr 0x%p data 0x%08X\n", addr, data);
	writel(data, (u64)addr);
}

/* Ethernet raw register read routine */
inline void apm_enet_rd32(void *addr, u32 *data)
{
	ENET_REG_RD("Read addr 0x%p ", addr);
	*data = readl((u64)addr);
	ENET_REG_RD("data 0x%08X\n", *data);
}

#ifdef DEBUG_HEXDUMP
static int putshex(u8 *buf, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i == 0) {
			printf("%02X", buf[i]);
		} else {
			if ((i % 32) == 0)
				printf("\n%02X", buf[i]);
			else if ((i % 4) == 0)
				printf(" %02X", buf[i]);
			else
				printf("%02X", buf[i]);
		}
	}
	printf("\n");
	return 0;
}
#endif

static u64 PADDR(void *ptr)
{
	u64 paddress = 0x000000000ULL; /* Macro for DDR less than 4 GB */
	paddress |= (unsigned long) ptr;
	return paddress;
}

/* This will be called by application, not running in interrupt context */
int apm_eth_tx(struct eth_device *dev, volatile void *ptr, int len)
{
	struct enet_frame *ef_ptr;
	struct apm_enet_dev *priv_dev;
	struct xgene_qmtm_msg32 msg;
	struct xgene_qmtm_msg16 *msg16 = &(msg.msg16);
	struct xgene_qmtm_msg_up16 *msg_up16 = &msg.msgup16;
	u64 phy;
	int rc = APM_RC_ERROR;
	int poll = 0;
	u16 data_len;
	u8  qmtm_ip;

	memset(&msg, 0, sizeof(msg));
	priv_dev = dev->priv;
	qmtm_ip = priv_dev->sdev->qmtm_ip;

	ef_ptr = (struct enet_frame *) ptr;

	/* Copy mac address into frame buffer */
	memcpy(ef_ptr->source_addr, dev->enetaddr, ENET_ADDR_LENGTH);

	data_len = (len & TX_DATA_LEN_MASK);

	/* Prepare the Msg to send out the packet */
	ENET_DEBUG_TX("Tx Pkt VADDR 0x%p len %d qm=%d\n", ef_ptr, data_len, qmtm_ip);
	ENET_TXHEXDUMP((u8*) ef_ptr, data_len);

	msg16->BufDataLen = (data_len < 60) ? 60 : data_len;
	phy = PADDR(ef_ptr);
	msg16->DataAddrL = (u32)phy;
	msg16->DataAddrH = (u32)(phy >> 32);
	msg16->C = xgene_qmtm_coherent();

	/* For Receiving completion message */
	msg_up16->H0Enq_Num = QMTM_QUEUE_ID(qmtm_ip, priv_dev->queues.comp_qid);

	ENET_DEBUG_TX("Enqueue QM msg QID %d len %d\n",
		priv_dev->queues.tx_qid, msg16->BufDataLen);
        ENET_TXHEXDUMP((u8*) &msg, 32);

	xgene_qmtm_push_msg(qmtm_ip, priv_dev->queues.tx_qid,
			(struct xgene_qmtm_msg64 *)&msg);

	/* Check for completion message to make sure transmit succeeded */
	memset(&msg, 0, sizeof(msg));

	ENET_DEBUG_TX("Checking completion msg QID %d\n",
		priv_dev->queues.comp_qid);

	while (poll++ < 10) {
		rc = xgene_qmtm_pull_msg(qmtm_ip,
			priv_dev->queues.comp_qid,
			(struct xgene_qmtm_msg64 *)&msg);

		if (rc == APM_RC_OK)
			break;

		/* Wait a while so we receive completion msg */
		udelay(500);
	}

	if (poll >= 10) {
		printf("Time out completion msg QID %d\n",
				priv_dev->queues.comp_qid);
	} else {
		ENET_DEBUG_TX("Received completion msg QID %d\n",
				priv_dev->queues.comp_qid);
#ifdef DEBUG_HEXDUMP
		printf("Completion message dump:: \n");
		putshex((uchar*)&msg,  sizeof(struct xgene_qmtm_msg32));
#endif
	}

	return rc;
}

/* Deliver received packets to higher layers */
static int apm_eth_rx(struct eth_device *dev, VOID *Buffer, UINTN *BufferSize)
{
	int rc;
	struct apm_enet_dev *priv_dev;
	struct xgene_qmtm_msg32 msg;
	struct xgene_qmtm_msg16 fp_msg;
	struct xgene_qmtm_msg16 *msg16 = &msg.msg16;
	u64 pkt_ptr = 0UL;
	u16 data_len = 0;
	u8  qmtm_ip;
	u8  LErr;
	UINTN orig_size;

	priv_dev = dev->priv;
	qmtm_ip = priv_dev->sdev->qmtm_ip;
	orig_size = *BufferSize;
	memset(&msg, 0, sizeof(msg));

	/* Get the Pkts if any */
	rc = xgene_qmtm_pull_msg(qmtm_ip, priv_dev->queues.rx_qid,
			(struct xgene_qmtm_msg64 *)&msg);

	if (rc != APM_RC_OK) 
		return APM_RC_OK;

	if (msg16->LErr)
		ENET_DEBUG_RX("Rcvd LErr 0x%02x\n", msg16->LErr);

	if (msg16->ELErr)
		ENET_DEBUG_RX("Rcvd ELErr 0x%02x\n", msg16->ELErr);

	LErr = msg16->LErr;
	LErr |= (u8) msg16->ELErr << 3;

	if (LErr) {
#if defined(BYPASS_CLE)
		if (LErr == 0x10 || LErr == 0x11)
			goto process_pkt;
#endif
		ENET_DEBUG_ERR("Rcvd LErr 0x%02x ELErr 0x%02x qm %d qid %d\n",
			msg16->LErr, msg16->ELErr, qmtm_ip, priv_dev->queues.rx_qid);
		apm_enet_parse_error(LErr, 1, priv_dev->queues.rx_qid);
		if (msg16->FPQNum & 0x3ff) /* 10-bit */
			goto dealloc;

		return APM_RC_OK;
	}
#if defined(BYPASS_CLE)
process_pkt:
#endif
	/* Pass the Packet to Higher Layer for processing */
	data_len = msg16->BufDataLen & TX_DATA_LEN_MASK;
	pkt_ptr = ((u64)msg16->DataAddrH << 32) | msg16->DataAddrL;
	ENET_DEBUG_RX("Rcvd Pkt of Len[%d] Passing it to Higher UP\n", data_len);
#ifdef DEBUG_HEXDUMP
	printf("Message Dump:: \n");
	putshex((uchar*)&msg,  sizeof(struct xgene_qmtm_msg32));
	printf("Packet Dump:: \n");
	putshex((uchar*)pkt_ptr, data_len);
#endif
	*BufferSize = data_len;
	if (data_len > orig_size)
		return APM_RC_OK;
	memcpy(Buffer, (void*) pkt_ptr, data_len);
dealloc:
	/* Dealloc the Buff to FP */
	ENET_DEBUG_RX("Dealloc the Buff to FP \n");
	memset(&fp_msg, 0, sizeof(fp_msg));

	/* Common fields  */
	fp_msg.BufDataLen = BUF_LEN_2K;
	fp_msg.FPQNum = QMTM_QUEUE_ID(qmtm_ip, priv_dev->queues.rx_fp_qid);
	fp_msg.DataAddrL = msg16->DataAddrL;
	fp_msg.DataAddrH = msg16->DataAddrH;
	fp_msg.C = xgene_qmtm_coherent();
	xgene_qmtm_fp_dealloc_msg(qmtm_ip, priv_dev->queues.rx_fp_qid, &fp_msg);

	return data_len;
}

extern void apm_menet_clk_rst(struct apm_enet_priv *priv);

static void apm_eth_halt(struct eth_device *dev)
{
	struct apm_enet_dev *priv_dev;
	struct apm_enet_priv *priv;

	priv_dev = dev->priv;
	priv = &priv_dev->priv;
	ENET_DEBUG("%a port=%d, dev=0x%p priv=0x%p\n", __func__, dev->index, dev, priv);
#if defined(PCM_LOOPBACK)
	/* PCM Loopback is support for 1G */
	if (priv->port < XGENET_0 || priv->port > XGENET_3)
		return;
#endif
	/* Disable MAC */
	apm_enet_mac_rx_state(priv, 0);
	apm_enet_mac_tx_state(priv, 0);
	apm_menet_clk_rst(priv);
}

static int apm_eth_fp_init(struct apm_enet_dev *priv_dev)
{
	int i, rc = APM_RC_OK;
	unsigned char *fp_buf_array;
	struct xgene_qmtm_msg16 msg;
	u8  qmtm_ip = priv_dev->sdev->qmtm_ip;

	ENET_DEBUG("Allocate memory for buffers \n" );
	fp_buf_array = MEMALLOC((NO_RX_BUFF * APM_ENET_FRAME_LEN), 16);

	if (fp_buf_array == NULL) {
		printf("Cannot allocate eth_rx_buf_list \n");
		rc = APM_RC_ERROR;
		goto _ret;
	}

	memset(fp_buf_array, 0, NO_RX_BUFF * APM_ENET_FRAME_LEN);
	memset(&msg, 0, sizeof(msg));

	/* Common fields */
	msg.BufDataLen = BUF_LEN_2K;
	msg.FPQNum = QMTM_QUEUE_ID(qmtm_ip, priv_dev->queues.rx_fp_qid);

	for (i = 0; i < NO_RX_BUFF; i++) {
		u64 paddr = PADDR(fp_buf_array + (i * APM_ENET_FRAME_LEN));
		/* Assign addresses as per configuration */
		msg.DataAddrL = (u32)paddr;
		msg.DataAddrH = (u32)(paddr >> 32);
		msg.C = xgene_qmtm_coherent();
		xgene_qmtm_fp_dealloc_msg(qmtm_ip, priv_dev->queues.rx_fp_qid,
			&msg);
	}

_ret:
	return rc;
}

static int apm_eth_qm_init(struct apm_enet_dev *priv_dev)
{
	struct xgene_qmtm_qinfo qinfo;
	int rc;
	u8 slave = priv_dev->sdev->slave;
	u8 slave_i = priv_dev->sdev->slave_i;
	u8 qmtm_ip = priv_dev->sdev->qmtm_ip;

	priv_dev->queues.qm_ip = qmtm_ip;

	/* Get completion queue info for Ethx to CPU */
	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.slave = slave_i;
	qinfo.qaccess = apm_enet_get_qacess();
	qinfo.qtype = QTYPE_PQ;
	qinfo.qsize = QSIZE;

	if (qmtm_ip == QMTM3)
		qinfo.flags = XGENE_SLAVE_Q_ADDR_ALLOC;
	else
		qinfo.flags = XGENE_SLAVE_DEFAULT_FLAGS;

	if ((rc = xgene_qmtm_set_qinfo(&qinfo)) != APM_RC_OK) {
		printf("Error allocating completion queue for ETH to CPU\n");
		goto _ret;
	}

	priv_dev->queues.comp_qid = qinfo.queue_id;

	/* Allocate egress work queue from CPU to ETHx */
	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.slave = slave;
	qinfo.qaccess = apm_enet_get_qacess();
	qinfo.qtype = QTYPE_PQ;
	qinfo.qsize = QSIZE;
	qinfo.flags = XGENE_SLAVE_DEFAULT_FLAGS;

	if ((rc = xgene_qmtm_set_qinfo(&qinfo)) != APM_RC_OK) {
		printf("Error allocating egress work queue for ETH\n");
		goto _ret;
	}

	priv_dev->queues.tx_qid = qinfo.queue_id;

	/* Allocate one ingress queue for Ethx to CPU normal work queue */
	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.slave = slave_i;
	qinfo.qaccess = apm_enet_get_qacess();
	qinfo.qtype = QTYPE_PQ;
	qinfo.qsize = QSIZE;

	if (qmtm_ip == QMTM3)
		qinfo.flags = XGENE_SLAVE_Q_ADDR_ALLOC;
	else
		qinfo.flags = XGENE_SLAVE_DEFAULT_FLAGS;

	if ((rc = xgene_qmtm_set_qinfo(&qinfo)) != APM_RC_OK) {
		printf("Error allocating ingress queue for ETH to CPU\n");
		goto _ret;
	}

	priv_dev->queues.rx_qid = qinfo.queue_id;

	/* Allocate free pool for ETHx from CPU */
	memset(&qinfo, 0, sizeof(qinfo));
	qinfo.slave = slave;
	qinfo.qaccess = apm_enet_get_qacess();
	qinfo.qtype = QTYPE_FP;
	qinfo.qsize = QSIZE;
	qinfo.flags = XGENE_SLAVE_DEFAULT_FLAGS;

	if ((rc = xgene_qmtm_set_qinfo(&qinfo)) != APM_RC_OK) {
		printf("Error allocating free pool for ETH\n");
		goto _ret;
	}

	priv_dev->queues.rx_fp_qid = qinfo.queue_id;
	priv_dev->queues.rx_fp_pbn = qinfo.pbn;

	ENET_DEBUG("RX QID %d TX QID %d CQID %d "
		"FP QID %d FP PBN %d\n",
		priv_dev->queues.rx_qid, priv_dev->queues.tx_qid,
		priv_dev->queues.comp_qid, priv_dev->queues.rx_fp_qid,
		priv_dev->queues.rx_fp_pbn);

_ret:
	return rc;
}

/* Turn on laser for port */
static void apm_xg_laser_on(u32 port)
{
#ifdef CONFIG_CMD_I2C	/* TODO move this to XG */
	u32 p = port - XGENET_0;
	u8  i2c_data[1];
	u8  data;

	i2c_set_bus_num(SPFF_I2C_BUS);  /* Set to bus 1 */
	/* Select channel 1 */
	i2c_data[0] = 0x1;
	i2c_write(SPFF_I2C_CH_ADDR, OUT_OFFSET, 1, i2c_data, sizeof(i2c_data));
	/* Set config */
	i2c_data[0] = 0xee;
	i2c_write(sfp_addr[p], CONFIG_OFFSET, 1, i2c_data, sizeof(i2c_data));

	i2c_read(sfp_addr[p], IN_OFFSET, 1, i2c_data, sizeof(i2c_data));

	if (p & 1) {
		if (i2c_data[0] & sfp_abs[p])
			data = sfp_laser_off[p];
		else
			data = sfp_laser_on[p];

		if (i2c_data[0] & sfp_abs[p - 1])
			data &= sfp_laser_off[p - 1];
		else
			data &= sfp_laser_on[p - 1];
	} else {
		if (i2c_data[0] & sfp_abs[p])
			data = sfp_laser_off[p];
		else
			data = sfp_laser_on[p];

		if (i2c_data[0] & sfp_abs[p + 1])
			data &= sfp_laser_off[p + 1];
		else
			data &= sfp_laser_on[p + 1];
	}

	i2c_data[0] = data;
	i2c_write(sfp_addr[p], OUT_OFFSET, 1, i2c_data, sizeof(i2c_data));
#endif
}

#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
static struct apm_enet_dev *apm_eth_get_pdev(const char *devname)
{
	struct apm_enet_dev *priv_dev = NULL;
	int eth;

	for (eth = 0; eth < MAX_ENET_PORTS; eth++) {
		if (pdev[eth] &&
			(strcmp(devname, pdev[eth]->sdev->name) == 0)) {
			priv_dev = pdev[eth];
			break;
		}
	}

	return priv_dev;
}

static int apm_eth_miiphy_read(const char *devname, unsigned char addr, unsigned char reg,
			unsigned short *value)
{
	int ret;
	u32 data;
	struct apm_enet_dev *priv_dev = apm_eth_get_pdev(devname);

	if (!priv_dev)
		return -1;

	ret = apm_genericmiiphy_read(&priv_dev->priv, addr, reg, &data);
	if (ret == 0)
		*value = (unsigned short)(0x0000ffff & data);

	return ret;
}

static int apm_eth_miiphy_write(const char *devname, unsigned char addr, unsigned char reg,
			 unsigned short value)
{
	u32 data = (0x0000ffff & (u32)value);
	struct apm_enet_dev *priv_dev = apm_eth_get_pdev(devname);

	if (!priv_dev)
		return -1;

	return apm_genericmiiphy_write(&priv_dev->priv, addr, reg, data);
}
#endif

static void rgmii_speed_set(u32 speed)
{
	switch (speed) {
	case APM_ENET_SPEED_1000:
		apm_enet_wr32((void *)CONFIG_SYS_ETH4_SCU_ETHDIV, 0x8);
		break;
	case APM_ENET_SPEED_100:
		apm_enet_wr32((void *)CONFIG_SYS_ETH4_SCU_ETHDIV, 0x28);
		break;
	case APM_ENET_SPEED_10:
		apm_enet_wr32((void *)CONFIG_SYS_ETH4_SCU_ETHDIV, 0x190);
	break;
	}
}

static int apm_eth_init(struct eth_device *dev /*, bd_t *bis*/)
{
	struct apm_enet_dev *priv_dev;
	struct apm_enet_priv *priv;
	int port, rc = -1;

	port = dev->index;
	priv_dev = pdev[port];
	priv = &priv_dev->priv;
	priv->phy_mode = phy_mode[dev->index];
	dev->priv = priv_dev;
	printf("%a dev=0x%p port=%d priv_dev=0x%p priv=0x%p priv_dev=0x%p enter\n",
		__func__, dev, port, priv_dev, priv, priv_dev);

#ifndef BYPASS_CLE
	apm_preclass_update_mac(priv->port, dev->enetaddr);
#endif
	/* Check link mode */
	if (phy_mode[port] == PHY_MODE_XGMII)
		priv->speed = SPEED_10000;
	else
		apm_enet_get_link_status(priv);

	/* Initialize MAC */
	rc = apm_enet_mac_init(priv, dev->enetaddr, priv->speed, 1);
	if (priv->phy_mode == PHY_MODE_RGMII)
		rgmii_speed_set(priv->speed);

	/* Enable MAC */
	apm_enet_mac_rx_state(priv, 1);
	apm_enet_mac_tx_state(priv, 1);
	printf("%a dev=0x%p priv=0x%p pdev=0x%p exit\n", __func__, dev, priv, pdev[port]);
	return rc;
}

static int apm_eth_device_setup(int port, u8 *apm_mac_addr)
{
	struct apm_enet_dev *priv_dev;
	struct apm_enet_priv *priv;
	struct xgene_qmtm_sdev *sdev;
	u32 base = 0, qmtm = 0;
	u64 cle_addr = 0, enet_addr;
	char name[8];
	u8 dev_addr[8];
	u8 wq_pbn_start = 0, wq_pbn_count = 0, fq_pbn_start = 0, fq_pbn_count = 0;
	void *port_vaddr = NULL, *gbl_vaddr = NULL, *mii_vaddr = NULL;
	int rc = 0;
	struct eth_device *dev;

	printf("%a port=%d enter\n", __func__, port);
	memset(dev_addr, 0xff, sizeof(dev_addr));
	memcpy(dev_addr, apm_mac_addr, 6);
	memset(name, 0, sizeof(name));

	switch (port) {
	case ENET_0:
	case ENET_1:
	case ENET_2:
	case ENET_3:
		qmtm = QMTM1;
		base = port / 2;
		enet_addr = CONFIG_SYS_ETH01_CSR_BASE + (base * 0x10000);
		cle_addr = CONFIG_SYS_CLE01_CSR_BASE + (base * 0x10000);
		AsciiSPrint(name, sizeof(name), "SGMII%d", port);
		wq_pbn_start = 0x00 + ((port % 2) * 8);
		wq_pbn_count = 0x08;
		fq_pbn_start = 0x20 + ((port % 2) * 8);
		fq_pbn_count = 0x08;
		port_vaddr = (void *)(enet_addr + ((port % 2) * 0x30));
		gbl_vaddr = (void *)enet_addr;
		mii_vaddr = (void *)CONFIG_SYS_ETH4_CSR_BASE;
		break;
	case XGENET_0:
	case XGENET_1:
	case XGENET_2:
	case XGENET_3:
		base = (port - XGENET_0) / 2;
		qmtm = QMTM0 + (2 * base);
		enet_addr = CONFIG_SYS_XGE0_CSR_BASE +
			(base * 0x100000) +
			((port % 2) * 0x10000);
		cle_addr = CONFIG_SYS_XGC0_CSR_BASE +
			(base * 0x100000) +
			((port % 2) * 0x10000);
		AsciiSPrint(name, sizeof(name), "SXGMII%d", port - XGENET_0);
		wq_pbn_start = 0x00;
		wq_pbn_count = 0x08;
		fq_pbn_start = 0x20;
		fq_pbn_count = 0x08;
		port_vaddr = (void *)enet_addr;
		gbl_vaddr = (void *)enet_addr;
		mii_vaddr = (void *)CONFIG_SYS_ETH4_CSR_BASE;
		base = port - 2;
		break;
	case MENET:
		qmtm = QMTM3;
		base = CLE_LITE;
		cle_addr = CONFIG_SYS_CLE4_CSR_BASE;
		strcpy(name, "RGMII");
		wq_pbn_start = 0x00;
		wq_pbn_count = 0x04;
		fq_pbn_start = 0x20;
		fq_pbn_count = 0x04;
		port_vaddr = (void *)CONFIG_SYS_ETH4_CSR_BASE;
		gbl_vaddr = (void *)CONFIG_SYS_ETH4_CSR_BASE;
		mii_vaddr = (void *)CONFIG_SYS_ETH4_CSR_BASE;
		break;
	}

	/* Initialize Queue Mgr for Ethernet */
	if ((rc = xgene_qmtm_main(qmtm)) != 0) {
		printf("QMTM%d error %d\n", qmtm, rc);
		goto _ret;
	}

	apm_class_base_addr[base] = (void *)cle_addr;

	if ((sdev = xgene_qmtm_set_sdev(name, qmtm, wq_pbn_start, wq_pbn_count,
			fq_pbn_start, fq_pbn_count)) == NULL) {
		printf("xgene_qmtm_set_sdev error for port %d\n", port);
		rc = -1;
		goto _ret;
	}

	/* Allocate device private structure */
	priv_dev = MEMALLOC(sizeof(struct apm_enet_dev), 8);
	if (!priv_dev) {
		printf("Error: Failed to allocate apm_enet_dev %d\n", port);
		rc = -1;
		goto _ret;
	}


	memset(priv_dev, 0, sizeof(*priv_dev));
	priv_dev->sdev = sdev;
	priv = &priv_dev->priv;
	priv->port = port;
	printf("%a priv->port=%d\n", __func__, port);

	/* Allocate device structure */
	dev = (struct eth_device *) MEMALLOC(sizeof(struct eth_device), 8);
	if (!dev) {
		printf("Error: Failed to allocate eth_device %d\n", (int)port);
		rc = -1;
		goto _ret;
	}
	memset(dev, 0, sizeof(*dev));
	/* Initialize device function pointers */
	dev->priv = (void *) priv_dev;
	dev->send = apm_eth_tx;
	dev->recv = apm_eth_rx;
	dev->halt = apm_eth_halt;
	dev->next = NULL;
	dev->index = port;
	dev->init = apm_eth_init;
	memcpy(dev->enetaddr, apm_mac_addr, 6);
	AsciiSPrint(dev->name, 4, "eth%d", port);

	/* Initialize device function pointers */
	switch (port) {
	case XGENET_0:
	case XGENET_1:
	case XGENET_2:
	case XGENET_3:
		/* 10G interface is used */
		apm_xgenet_init_priv(priv, port_vaddr, gbl_vaddr, mii_vaddr);
		//phy_mode[port] = PHY_MODE_SGMII;
		break;
	default:
		/* 1G interface is used */
		apm_enet_init_priv(priv, port_vaddr, gbl_vaddr, mii_vaddr);
		break;
	}

	priv->phy_addr = phy_addr[port];
	priv->phy_mode = phy_mode[port];
	apm_enet_port_reset(priv, phy_mode[port]);

	/* QM queue configuration */
	if ((rc = apm_eth_qm_init(priv_dev)) != 0) {
		printf("Error in QM configuration\n");
		goto _ret;
	}

	/* Allocate buffers in free pool */
	if ((rc = apm_eth_fp_init(priv_dev)) != APM_RC_OK) {
		printf("Error in Free Pool Configure\n");
		goto _ret;
	}

	/* Configure classifier */
#ifdef BYPASS_CLE
	apm_enet_cle_bypass(priv,
		(priv_dev->queues.rx_qid | DST_QM_IP(priv_dev->sdev->qmtm_ip)),
		priv_dev->queues.rx_fp_pbn-0x20, 0);
#else
	/* Initialize preclass tree */
	if ((rc = apm_preclass_init(port, &priv_dev->queues)) != APM_RC_OK) {
		printf("Error in CLE configuration\n");
		goto _ret;
	}
#endif
	/* Initialize MAC */
	if (phy_mode[port] == PHY_MODE_XGMII) {
		/* Wait for Power On */
		mdelay(100);
		rc = apm_enet_mac_init(priv, dev_addr, SPEED_10000, 1);
		/* Wait for MAC to be up */
		mdelay(100);
		apm_xg_laser_on(port);
	} else {
		rc = apm_enet_mac_init(priv, dev_addr, SPEED_1000, 1);
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
		/* Register MII PHY read/write operations */
		miiphy_register(name, apm_eth_miiphy_read, apm_eth_miiphy_write);
#endif
	}
	pdev[port] = priv_dev;
#ifdef CONFIG_STORM
	if (port == MENET)
		emac_dev[0] = dev;
	else if (port == ENET_0)
		emac_dev[1] = dev;
	else if (port == ENET_1)
		emac_dev[2] = dev;
	else if (port == XGENET_0)
		emac_dev[3] = dev;
#else
	if (port == XGENET_0)
		emac_dev[0] = dev;
	else if (port == XGENET_1)
		emac_dev[1] = dev;
#endif
	dev->index = port;
	dev->priv = priv_dev;
	printf("%a port=%d dev->index=%d priv=0x%p priv->port=%d dev=0x%p, pdev=0x%p\n",
		__func__, port, dev->index, priv, priv->port, dev, pdev[port]);
_ret:
	return rc;
}

/* Ethernet Subsystem Initialization */
#ifdef APM_XGENE 
int apm_eth_initialize(int index, u8 *mac_addr)
#else
int apm_eth_initialize(bd_t *bis)
#endif
{
	int ret = 0;

	ENET_DEBUG("%a index=%d\n", __func__, index);
	/* Setup classifier */
	apm_cle_system_id = CORE_0;
	apm_cle_systems = 1;

#ifdef CONFIG_SHADOWCAT
	if (index == 0) {
		phy_mode[XGENET_0] = PHY_MODE_SGMII;
		ret = apm_eth_device_setup(XGENET_0, mac_addr);
	} else if (index == 1) {
                phy_mode[ENET_0] = PHY_MODE_XGMII;
                ret = apm_eth_device_setup(XGENET_1, mac_addr);
        }
#else
	if (index == 0) {
		phy_mode[MENET] = PHY_MODE_RGMII;
		ret = apm_eth_device_setup(MENET, mac_addr);
	}
	else if (index == 1) {
		phy_mode[ENET_0] = PHY_MODE_SGMII;
		ret = apm_eth_device_setup(ENET_0, mac_addr);
	}
	else if (index == 2) {
		phy_mode[ENET_1] = PHY_MODE_SGMII;
		ret = apm_eth_device_setup(ENET_1, mac_addr);
	}
	else if (index == 3) {
		phy_mode[XGENET_0] = PHY_MODE_XGMII;
		ret = apm_eth_device_setup(XGENET_0, mac_addr);
	}
#endif
	if (ret != 0)
		return ret;

	printf("%a index=%d emac_dev=0x%p exit\n", __func__, index, emac_dev[index] );
	return ret;
}
