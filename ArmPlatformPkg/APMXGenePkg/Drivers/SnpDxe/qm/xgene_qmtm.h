/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager Header file
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
 * @file xgene_qmtm.h
 *
 */

#ifndef __XGENE_QMTM_H__
#define __XGENE_QMTM_H__

#include "../mustang.h"
/* QMTM return codes */
enum xgene_qmtm_rc {
	QMTM_OK = 0,
	QMTM_ERR = -1,
};

/* QMTM Slave Device Information */
struct xgene_qmtm_sdev {
	u8  slave;
	u8  slave_i;
	u8  qmtm_ip;	/* qmtm_ip see xgene_qmtm_ip */
	u8  slave_id;	/* slave id see xgene_qmtm_slave_id */
	u8  wq_pbn_start;
	u8  wq_pbn_count;
	u8  fq_pbn_start;
	u8  fq_pbn_count;
	u32 wq_pbn_pool;/* Bit mask indicates in use WQ PBN */
	u32 fq_pbn_pool;/* Bit mask indicates in use FP PBN */
	char *name;
} __attribute__ ((packed));

/* QMTM Queue types */
enum xgene_qmtm_qtype {
	QTYPE_DISABLED,	/* Queue Type is un-configured or disabled */
	QTYPE_PQ,	/* Queue Type is Physical Work Queue */
	QTYPE_FP,	/* Queue Type is Free Pool Queue */
	QTYPE_VQ,	/* Queue Type is Virtual Queue */
	QTYPE_MAX,
};

/* QMTM Queue possible sizes */
enum xgene_qmtm_qsize {
	QSIZE_512B,
	QSIZE_2KB,
	QSIZE_16KB,
	QSIZE_64KB,
	QSIZE_512KB,
	QSIZE_MAX,
};

/* QMTM Queue Access Method */
enum xgene_qmtm_qaccess {
	QACCESS_ALT,
	QACCESS_QMI,
	QACCESS_MBOX,
	QACCESS_MAX,
};

/* QMTM Buffer Length encoded as per QM message format */
enum xgene_qmtm_buf_len {
	BUF_LEN_256B = 0x7000,
	BUF_LEN_1K   = 0x6000,
	BUF_LEN_2K   = 0x5000,
	BUF_LEN_4K   = 0x4000,
	BUF_LEN_16K  = 0x0
};

/* QMTM messaging structures */
/*
 * @struct  xgene_qmtm_msg16
 * @brief   This structure represents 16 byte QMTM message format
 */
struct xgene_qmtm_msg16 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	/* memory word 0 (bit 31:0) */
	u32 UserInfo;

	/* memory word 1 (bit 63:32) */
	u32 HL:1;
	u32 LErr:3;
	u32 RType:4;
	u32 In:1;
#ifdef CONFIG_SHADOWCAT
	u32 AM:1;
#else
	u32 Rv:1;
#endif
	u32 HB:1;
	u32 PB:1;
	u32 LL:1;
	u32 NV:1;
	u32 LEI:2;
	u32 ELErr:2;
#ifdef CONFIG_SHADOWCAT
	u32 PType:2;
#else
	u32 Rv2:2;
#endif
	u32 FPQNum:12;

	/* memory word 2 (bit 95:64) */
	u32 DataAddrL;    /* split 10/32 */

	/* memory word 3 (bit 127:96) */
	u32 C:1;
	u32 BufDataLen:15;
#ifdef CONFIG_SHADOWCAT
	u32 VMid:6;
#else
	u32 Rv6:6;
#endif
	u32 DataAddrH:10; /* split 10/32 */
#else
	/* memory word 0 (bit 31:0) */
	u32 UserInfo;

	/* memory word 1 (bit 63:32) */
	u32 FPQNum:12;
#ifdef CONFIG_SHADOWCAT
	u32 PType:2;
#else
	u32 Rv2:2;
#endif
	u32 ELErr:2;
	u32 LEI:2;
	u32 NV:1;
	u32 LL:1;
	u32 PB:1;
	u32 HB:1;
#ifdef CONFIG_SHADOWCAT
	u32 AM:1;
#else
	u32 Rv:1;
#endif
	u32 In:1;
	u32 RType:4;
	u32 LErr:3;
	u32 HL:1;

	/* memory word 2 (bit 95:64) */
	u32 DataAddrL;    /* split 10/32 */

	/* memory word 3 (bit 127:96) */
	u32 DataAddrH:10; /* split 10/32 */
#ifdef CONFIG_SHADOWCAT
	u32 VMid:6;
#else
	u32 Rv6:6;
#endif
	u32 BufDataLen:15;
	u32 C:1;
#endif
} __attribute__ ((packed));

/*
 * @struct  xgene_qmtm_msg_up16
 * @brief   This structure represents upper 16 byte portion of 32 byte of QMTM message format
 */
struct xgene_qmtm_msg_up16 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	/* memory word 4 (bit 159:128) */
	u32 H0Info_msbL;    /* split 16/32 */

	/* memory word 5 (bit 191:160) */
	u32 HR:1;
	u32 Rv0:1;
	u32 DR:1;
#ifdef CONFIG_SHADOWCAT
	HFPSel_msb:1;
#else
	u32 Rv1:1;
#endif
	u32 TotDataLengthLinkListLSBs:12;
	u16 H0Info_msbH; /* split 16/32 */

	/* memory word 6 (bit 223:192) */
	u32 H0Info_lsbL; /* split 16/32 */

	/* memory word 7 (bit 255:224) */
	u32 H0FPSel:4;
	u32 H0Enq_Num:12;
	u16 H0Info_lsbH; /* split 16/32 */
#else
	/* memory word 4 (bit 159:128) */
	u32 H0Info_msbL; /* split 16/32 */

	/* memory word 5 (bit 191:160) */
	u16 H0Info_msbH; /* split 16/32 */
	u32 TotDataLengthLinkListLSBs:12;
#ifdef CONFIG_SHADOWCAT
	u32 HFPSel_msb:1;
#else
	u32 Rv1:1;
#endif
	u32 DR:1;
	u32 Rv0:1;
	u32 HR:1;

	/* memory word 6 (bit 223:192) */
	u32 H0Info_lsbL; /* split 16/32 */

	/* memory word 7 (bit 255:224) */
	u16 H0Info_lsbH; /* split 16/32 */
	u32 H0Enq_Num:12;
	u32 H0FPSel:4;
#endif
} __attribute__ ((packed));

/*
 * @struct  xgene_qmtm_msg_ext8
 * @brief   This structure represents 8 byte portion of QMTM extended (64B)
 *          message format
 */
struct xgene_qmtm_msg_ext8 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	u32 NxtDataAddrL;
	u32 Rv1:1;
	u32 NxtBufDataLength:15;
	u32 NxtFPQNum:4;
	u32 Rv2:2;
	u32 NxtDataAddrH:10;
#else
	u32 NxtDataAddrL;
	u32 NxtDataAddrH:10;
	u32 Rv2:2;
	u32 NxtFPQNum:4;
	u32 NxtBufDataLength:15;
	u32 Rv1:1;
#endif
} __attribute__ ((packed));

/*
 * @struct  xgene_qmtm_msg_ll8
 * @brief   This structure represents 8 byte Link list portion of QMTM extended (64B)
 *          message format
 *
 */
struct xgene_qmtm_msg_ll8 {
#ifdef CONFIG_CPU_BIG_ENDIAN
	u32 NxtDataPtrL;
	u8  TotDataLengthLinkListMSBs;
	u8  NxtLinkListength;
	u32 NxtFPQNum:4;
	u32 Rv2:2;
	u32 NxtDataPtrH:10;
#else
	u32 NxtDataPtrL;
	u32 NxtDataPtrH:10;
	u32 Rv2:2;
	u32 NxtFPQNum:4;
	u8  NxtLinkListength;
	u8  TotDataLengthLinkListMSBs;
#endif
} __attribute__ ((packed));

/*
 * @struct  xgene_qmtm_msg32
 * @brief   This structure represents 32 byte QMTM message format
 */
struct xgene_qmtm_msg32 {
	struct xgene_qmtm_msg16 msg16;
	struct xgene_qmtm_msg_up16 msgup16;
} __attribute__ ((packed));

/*
 * @struct  xgene_qmtm_msg_ext32
 * @brief   This structure represents 32 byte of QMTM extended (64B)
 *          message format
 */
struct xgene_qmtm_msg_ext32 {
	struct xgene_qmtm_msg_ext8 msg8_2;
	struct xgene_qmtm_msg_ext8 msg8_1;
	union {
		struct xgene_qmtm_msg_ext8 msg8_4;
		struct xgene_qmtm_msg_ll8 msg8_ll;
	};
	struct xgene_qmtm_msg_ext8 msg8_3;
} __attribute__ ((packed));

/*
 * @struct  xgene_qmtm_msg64
 * @brief   This structure represents 64 byte QMTM message format
 */
struct xgene_qmtm_msg64 {
	struct xgene_qmtm_msg32 msg32_1;
	struct xgene_qmtm_msg_ext32 msg32_2;
} __attribute__ ((packed));

#ifdef CONFIG_CPU_BIG_ENDIAN
#define xgene_qmtm_msg_le32(word, words) \
	do { \
		int w; \
		for (w = 0; w < words; w++) \
			*(word + w) = cpu_to_le32(*(word + w)); \
	} while (0)
#else
#define xgene_qmtm_msg_le32(word, words) \
	do {} while (0)
#endif

/* Fabric format QID bit position */
#ifdef CONFIG_SHADOWCAT
#define Q_SHIFT 13
#else
#define Q_SHIFT 6
#endif
/* Empty Slot Soft Signature */
#define EMPTY_SLOT_INDEX 7
#define EMPTY_SLOT       0x22222222

/* Destination QM, 2 MSb in work queue, dstqid */
#define QMTM_QUEUE_ID(qm, qid) (((u16)(qm) << 10) | qid)

/* QMTM Queue Information structure */
/*
 * @struct  xgene_qmtm_qinfo
 * @brief   This structure represents per queue state database
 */
struct xgene_qmtm_qinfo {
	u8  slave;		/* arg, slave  see xgene_slave */
	u8  qtype;		/* arg, queue type see xgene_qmtm_qtype */
	u8  qsize;		/* arg, queue size see xgene_qmtm_qsize */
	u8  qaccess;		/* arg, qaccess method see xgene_qmtm_qaccess */
	u8  flags;		/* arg, flags */
	u8  qmtm_ip;		/* ret, qmtm_ip see xgene_qmtm_ip */
	u8  slave_id;		/* ret, slave id see xgene_qmtm_slave_id */
	u8  pbn;		/* ret, prefetch buffer number */
	u16 queue_id;		/* ret, queue id */
	u16 nummsgs;		/* ret, number of messages in the queue */
	u32 pbm_state;		/* ret, prefetch buffer manager state */
	u64 queue_paddr;	/* arg/ret, queue physical address */
	void *qfabric;		/* ret, queue fabric address */
	void *qstate;		/* ret, queue state */
	/* For Alt Enq/Deq Queue Access method */
	u16 qhead;		/* ret */
	u16 qtail;		/* ret */
	u16 count;		/* ret */
	u16 irq;		/* ret */
	void *command;		/* ret */
	union {			/* ret */
		void *queue_vaddr;	/* queue virtual address */
		/* For Alt Enq/Deq Queue Access method */
		struct xgene_qmtm_msg16 *msg16;
		struct xgene_qmtm_msg32 *msg32;
	};
} __attribute__ ((packed));

/* QMTM Queue Information flags */
#define XGENE_SLAVE_PB_CONFIGURE 0x01
#define XGENE_SLAVE_Q_ADDR_ALLOC 0x02
#define XGENE_SLAVE_DEFAULT_FLAGS (XGENE_SLAVE_PB_CONFIGURE | \
				XGENE_SLAVE_Q_ADDR_ALLOC)

/**
 * @brief   Determine whether QMTM is coherent
 * @param   None
 * @return  1 if QMTM is coherent else 0
 */
static inline int xgene_qmtm_coherent(void)
{
	return 1;
}

/**
 * @brief   Decode buffer length from BufDataLen
 * @param   bufdatalen Encoded buffer data length field
 * @return  Decoded value of buffer length
 */
static inline u16 xgene_qmtm_decode_buflen(u16 bufdatalen)
{
	switch (bufdatalen & 0x7000) {
		case 0x7000:
			return 0x100;
		case 0x6000:
			return 0x400;
		case 0x5000:
			return 0x800;
		case 0x4000:
			return 0x1000;
		default:
			return 0x4000;
	};
}

/**
 * @brief   Decode data length from BufDataLen
 * @param   bufdatalen Encoded buffer data length field
 * @return  Decoded value of data length
 */
static inline u32 xgene_qmtm_decode_datalen(u16 bufdatalen)
{
	switch (bufdatalen & 0x7000) {
		case 0x7000:
			return bufdatalen & 0xFF ? bufdatalen & 0xFF : 0x100;
		case 0x6000:
			return bufdatalen & 0x3FF ? bufdatalen & 0x3FF : 0x400;
		case 0x5000:
			return bufdatalen & 0x7FF ? bufdatalen & 0x7FF : 0x800;
		case 0x4000:
			return bufdatalen & 0xFFF ? bufdatalen & 0xFFF : 0x1000;
		default:
			return bufdatalen & 0x3FFF ? bufdatalen & 0x3FFF : 0x4000;
	};
}

/**
 * @brief   Decrement datalen in BufDataLen
 * @param   Encoded value of buffer data length field
 * @param   Less data from datalen
 * @param   Update datalen with original datalen
 * @return  Encoded value of buffer data length field
 */
static inline u16 xgene_qmtm_less_bufdatalen(u16 bufdatalen, u16 less, u32 *datalen)
{
	u16 mask;
	u16 final_datalen;

	switch ((bufdatalen >> 12) & 0x7) {
		case 7:
			mask = 0xFF;
			break;
		case 6:
			mask = 0x3FF;
			break;
		case 5:
			mask = 0x7FF;
			break;
		case 4:
			mask = 0xFFF;
			break;
		default:
			mask = 0x3FFF;
			break;
	};

	final_datalen = *datalen = (bufdatalen & mask) ? (bufdatalen & mask) : (mask + 1);
	final_datalen = (final_datalen > less) ? (final_datalen - less) : 0;
	bufdatalen = (bufdatalen & ~mask) | final_datalen;

	return bufdatalen;
}

/**
 * @brief   Encode buffer length and data length to BufDataLen
 * @param   len Data length or Buffer length
 * @return  Encoded value of buffer data length field
 */
static inline u16 xgene_qmtm_encode_bufdatalen(u32 len)
{
	if (len <= 0x100) {
		return (0x7 << 12) | (len & 0xFF);
	} else if (len <= 0x400) {
		return (0x6 << 12) | (len & 0x3FF);
	} else if (len <= 0x800) {
		return (0x5 << 12) | (len & 0x7FF);
	} else if (len <= 0x1000) {
		return (0x4 << 12) | (len & 0xFFF);
	} else if (len < 0x4000) {
		return len & 0x3FFF;
	} else {
		return 0;
	}
}

/**
 * @brief   Encode data length to BufDataLen assuming maximum buffer size
 * @param   len Data length
 * @return  Encoded value of buffer data length field
 */
static inline u16 xgene_qmtm_encode_datalen(u32 len)
{
	return len & 0x3FFF;
}

/**
 * @brief   Check if next buffer data length field is valid.
 * @param   nxtbufdatalen Next buffer data length field of a Extended Message
 * @return  0 - success or -1 - failure
 */
static inline int xgene_qmtm_nxtbufdatalen_is_valid(u16 nxtbufdatalen)
{
	return nxtbufdatalen == 0x7800 ? 0 : 1;
}

/**
 * @brief   Create and configure a queue
 * @param   qinfo->slave - slave see xgene_slave
 *	    qinfo->qtype - queue type (P_QUEUE or FP_QUEUE)
 *	    qinfo->qsize - queue size see xgene_qmtm_qsize
 *	    qinfo->qaccess - queue access method see xgene_qmtm_qaccess
 *	    qinfo->flags - Queue Information flags
 *	    qinfo->queue_paddr - If Desire Queue Physical Address to use
 * @return  QMTM_OK on Success or QMTM_ERR on Failure
 *	    On Success, updates following in qinfo
 *	    qinfo->qmtm_ip  - QMTM0, QMTM1, QMTM2 or QMTM3
 *	    qinfo->slave_id - Slave ID
 *	    qinfo->pbn - Slave ID's prefetch buffer number
 *	    qinfo->queue_id - Queue ID
 */
int xgene_qmtm_set_qinfo(struct xgene_qmtm_qinfo *qinfo);

/**
 * @brief   Get queue information structure for a queue
 * @param   qinfo->qmtm_ip  - QMTM0, QMTM1, QMTM2 or QMTM3
 *	    qinfo->queue_id - Queue ID
 * @return  QMTM_OK on Success or QMTM_ERR on Failure
 *	    On Success, returns following in qinfo
 *	    qinfo->slave - slave see xgene_slave
 *	    qinfo->qtype - queue type (P_QUEUE or FP_QUEUE)
 *	    qinfo->qsize - queue size see xgene_qmtm_qsize
 *	    qinfo->qaccess - queue access method see xgene_qmtm_qaccess
 *	    qinfo->flags - Queue Information flags
 *	    qinfo->queue_paddr - Queue Physical Address
 *	    qinfo->slave_id - Slave ID
 *	    qinfo->pbn - Slave's prefetch buffer number
 *	    qinfo->queue_vaddr - Queue Virtual Address
 *	    qinfo->nummsgs - Number of messages in the queue
 *	    qinfo->pbm_state - prefetch buffer managere state
 */
int xgene_qmtm_get_qinfo(struct xgene_qmtm_qinfo *qinfo);

/**
 * @brief   Unconfigure and delete a queue
 * @param   qinfo->qmtm_ip  - QMTM0, QMTM1, QMTM2 or QMTM3
 *	    qinfo->queue_id - Queue ID
 * @return  QMTM_OK on Success or QMTM_ERR on Failure
 */
int xgene_qmtm_clr_qinfo(struct xgene_qmtm_qinfo *qinfo);

/**
 * @brief   Configure slave properties
 * @param   name - name of slave see slave_s
 *	    qmtm_ip - slave belongs to QMTM0, QMTM1, QMTM2 or QMTM3
 *	    wq_pbn_start - slave's starting wq_pbn
 *	    wq_pbn_count - slave's wq_pbn count
 *	    fq_pbn_start - slave's starting fp_pbn
 *	    fq_pbn_count - slave's fp_pbn count
 * @return  slave structure on Success or NULL on Failure
 */

struct xgene_qmtm_sdev *xgene_qmtm_set_sdev(const char *name, u8 qmtm_ip,
		u8 wq_pbn_start, u8 wq_pbn_count,
		u8 fq_pbn_start, u8 fq_pbn_count);

/**
 * @brief   Delete slave properties
 * @param   slave structure
 * @return  QMTM_OK on Success or QMTM_ERR on Failure
 */
int xgene_qmtm_clr_sdev(struct xgene_qmtm_sdev *slave);

void xgene_qmtm_fp_dealloc_msg(u8 qmtm_ip, u16 queue_id, struct xgene_qmtm_msg16 *msg);

void xgene_qmtm_push_msg(u8 qmtm_ip, u16 queue_id, struct xgene_qmtm_msg64 *msg);

int xgene_qmtm_pull_msg(u8 qmtm_ip, u16 queue_id, struct xgene_qmtm_msg64 *msg);

int xgene_qmtm_intr_coalesce(u8 qmtm_ip, u8 pbn, u8 tap);

#endif /* __XGENE_QMTM_H__ */
