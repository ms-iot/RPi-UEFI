/**
 * AppliedMicro X-Gene SOC Queue Manager Traffic Manager CSR file
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
 * @file xgene_qmtm_csr.h
 *
 */

#ifndef __XGENE_QMTM_CSR_H__
#define __XGENE_QMTM_CSR_H__

/*    Address QM_CSR Registers */
#define CSR_QM_CONFIG_ADDR                                           0x00000004
#define CSR_PBM_ADDR                                                 0x00000008
#define CSR_PBM_BUF_WR_ADDR                                          0x0000000c
#define CSR_PBM_BUF_RD_ADDR                                          0x00000010
#define CSR_PBM_COAL_ADDR                                            0x00000014
#define CSR_PBM_CTICK0_ADDR                                          0x00000018
#define CSR_THRESHOLD0_SET1_ADDR                                     0x00000030
#define CSR_THRESHOLD1_SET1_ADDR                                     0x00000034
#define CSR_HYSTERESIS_ADDR                                          0x00000068
#define CSR_QSTATE_ADDR                                              0x0000006c
#define CSR_QSTATE_WR_0_ADDR                                         0x00000070
#define CSR_QSTATE_WR_1_ADDR                                         0x00000074
#define CSR_QSTATE_WR_2_ADDR                                         0x00000078
#define CSR_QSTATE_WR_3_ADDR                                         0x0000007c
#define CSR_QSTATE_WR_4_ADDR                                         0x00000080
#define CSR_QSTATE_RD_0_ADDR                                         0x00000084
#define CSR_QSTATE_RD_1_ADDR                                         0x00000088
#define CSR_QSTATE_RD_2_ADDR                                         0x0000008c
#define CSR_QSTATE_RD_3_ADDR                                         0x00000090
#define CSR_QSTATE_RD_4_ADDR                                         0x00000094
#define QM_INTERRUPT_ADDR                                            0x00000124
#define QM_INTERRUPTMASK_ADDR                                        0x00000128
#define CSR_PBM_ERRINF_ADDR                                          0x00000134
#define CSR_MSGRD_ERRINF_ADDR                                        0x00000138
#define CSR_QM_MBOX_NE_INT_MODE_ADDR                                 0x0000017c
#define CSR_QM_MBOX_NE_ADDR                                          0x00000180
#define CSR_QM_STATS_CFG_ADDR                                        0x00000204
#define CSR_ENQ_STATISTICS_ADDR                                      0x00000208
#define CSR_DEQ_STATISTICS_ADDR                                      0x0000020c
#define CSR_FIFO_STATUS_ADDR                                         0x00000210
#define CSR_ACR_FIFO_CTRL_ADDR                                       0x00000214
#define CSR_ERRQ_ADDR                                                0x00000218
#define CSR_QM_RAM_MARGIN_ADDR                                       0x0000021c
#define CSR_QM_TESTINT0_ADDR                                         0x00000220
#define CSR_QM_TESTINT1_ADDR                                         0x00000224
#define CSR_QMLITE_PBN_MAP_0_ADDR                                    0x00000228
#define CSR_QMLITE_PBN_MAP_1_ADDR                                    0x0000022c
#define CSR_RECOMB_CTRL_0_ADDR                                       0x00000230
#define CSR_RECOMB_CTRL_1_ADDR                                       0x00000234
#define CSR_RECOMB_CTRL_2_ADDR                                       0x00000238
#define CSR_QM_RECOMB_RAM_MARGIN_ADDR                                0x00000240
#define CSR_RECOMB_STS_0_ADDR                                        0x00000244
#define CSR_RECOMB_STS_1_ADDR                                        0x00000248
#define CSR_RECOMB_STS_2_ADDR                                        0x0000024c
#define RECOMB_INTERRUPT_ADDR                                        0x00000250
#define RECOMB_INTERRUPTMASK_ADDR                                    0x00000254
#define CSR_DEQ_CTRL_0_ADDR                                          0x00000258
#define CSR_MPIC_CTRL_0_ADDR                                         0x0000025c
#define CSR_MISC_CTRL_0_ADDR                                         0x00000260

/*	Register csr_qm_config	*/ 
/*	 Fields enable	 */
#define QM_ENABLE_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))

/*	Register csr_pbm	*/ 
/*	 Fields overwrite	 */
#define OVERWRITE_WR(src)                       (((u32)(src)<<31) & 0x80000000)
/*	 Fields slvid_pbn	 */
#define SLVID_PBN_WR(src)                           (((u32)(src)) & 0x000003ff)

/*	Register csr_pbm_buf_wr	*/ 
/*	 Fields pb_size	 */
#define PB_SIZE_WR(src)                         (((u32)(src)<<31) & 0x80000000)

/*	Register csr_pbm_buf_rd	*/ 
/*	 Fields prefetch_buf_en	 */
#define PREFETCH_BUF_EN_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields is_free_pool	 */
#define IS_FREE_POOL_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields tlvq	 */
#define TLVQ_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields corresponding_qnum	 */
#define CORRESPONDING_QNUM_SET(dst,src) \
                       (((dst) & ~0x0007fe00) | (((u32)(src)<<9) & 0x0007fe00))

/*	Register csr_qstate	*/ 
/*	 Fields qnumber	 */
#define QNUMBER_WR(src)                             (((u32)(src)) & 0x000003ff)

/*	Register qm_interruptMask	*/
/*    Mask Register Fields queue_not_emptyMask    */
#define QUEUE_NOT_EMPTYMASK_MASK                                     0x80000000
/*    Mask Register Fields acr_fifo_criticalMask    */
#define ACR_FIFO_CRITICALMASK_MASK                                   0x00000008
/*    Mask Register Fields qpcore_acr_errorMask    */
#define QPCORE_ACR_ERRORMASK_MASK                                    0x00000004
/*    Mask Register Fields deq_axi_errorMask    */
#define DEQ_AXI_ERRORMASK_MASK                                       0x00000002
/*    Mask Register Fields pbm_dec_errorMask    */
#define PBM_DEC_ERRORMASK_MASK                                       0x00000001

/*	Register csr_pbm_errinf	*/ 
/*	 Fields slave_id	 */
#define SLAVE_ID_SHIFT                                                        6
/*	 Fields acr_qid	 */
#define ACR_QID_RD(src)                              (((src) & 0x00ffc000)>>14)
/*	 Fields qid	 */
#define QID_RD(src)                                      (((src) & 0x000003ff))

/*	Register csr_errq	*/ 
/*	 Fields unexpected_en	 */
#define UNEXPECTED_EN_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields unexpected_qid	 */
#define UNEXPECTED_QID_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields expected_en	 */
#define EXPECTED_EN_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields expected_qid	 */
#define EXPECTED_QID_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register csr_recomb_ctrl_0	*/ 
/*	 Fields recomb_en	 */
#define RECOMB_EN0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Global Base Address	*/
#define QM_CLKRST_CSR_BASE_ADDR_OFFSET			0xc000

/*    Address QM_CLKRST_CSR  Registers */
#define QM_SRST_ADDR                                                 0x00000200
#define QM_CLKEN_ADDR                                                0x00000208

/*	Register qm_srst	*/ 
/*	 Fields qm_reset	 */
#define QM_RESET_WR(src)                         (((u32)(src)<<1) & 0x00000002)
/*	 Fields csr_reset	 */
#define CSR_RESET_WR(src)                           (((u32)(src)) & 0x00000001)

/*	Register qm_clken	*/ 
/*	 Fields qm_clken	 */
#define QM_CLKEN_WR(src)                         (((u32)(src)<<1) & 0x00000002)
/*	 Fields csr_clken	 */
#define CSR_CLKEN_WR(src)                           (((u32)(src)) & 0x00000001)

/*	Global Base Address	*/
#define QM_GLBL_DIAG_CSR_BASE_ADDR_OFFSET			0xd000

/*    Address GLBL_DIAG_CSR  Registers */
#define QM_CFG_MEM_RAM_SHUTDOWN_ADDR                            0x00000070
#define QM_CFG_MEM_RAM_SHUTDOWN_DEFAULT                         0xffffffff

#endif /* __XGENE_QMTM_CSR_H__ */
