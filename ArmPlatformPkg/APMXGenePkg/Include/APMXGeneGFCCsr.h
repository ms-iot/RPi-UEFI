/** 
 * apm_gfc_csr.h - AppliedMicro GFC register header file
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 *  http://opensource.org/licenses/bsd-license.php
 *
 *THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#ifndef _APMXGENEGFCCSR_H__
#define _APMXGENEGFCCSR_H__

/*	Global Base Address	*/
#define GFC_CSR_BASE_ADDR			0x017010000ULL
#define GFC_CSR_SIZE          0x10000
/*    Address GFC_CSR  Registers */
#define GFC_IPREV_ADDR                                               0x00000004
#define GFC_SCRATCH_REG_ADDR                                         0x00000008
#define GFC_INTERRUPT_ADDR                                           0x0000000c
#define GFC_INTERRUPTMASK_ADDR                                       0x00000010
#define GFC_NAND_PIO_CTRL_ADDR                                       0x00000014
#define GFC_NAND_PIO_REG_CTRL0_ADDR                                  0x00000018
#define GFC_NAND_PIO_REG_CTRL1_ADDR                                  0x0000001c
#define GFC_NAND_PIO_REG_CTRL2_ADDR                                  0x00000020
#define GFC_NAND_PIO_REG0_ADDR                                       0x00000024
#define GFC_NAND_PIO_REG1_ADDR                                       0x00000028
#define GFC_NAND_PIO_REG2_ADDR                                       0x0000002c
#define GFC_NAND_PIO_REG3_ADDR                                       0x00000030
#define GFC_NAND_PIO_REG4_ADDR                                       0x00000034
#define GFC_NAND_PIO_REG5_ADDR                                       0x00000038
#define GFC_NAND_PIO_REG6_ADDR                                       0x0000003c
#define GFC_NAND_PIO_REG7_ADDR                                       0x00000040
#define GFC_NAND_PIO_REG8_ADDR                                       0x00000044
#define GFC_NAND_PIO_BUF_START_ADDR                                  0x00000048
#define GFC_NAND_PIO_BUF_END_ADDR                                    0x0000004c
#define GFC_NAND_PIO_FORCED_CMD_CTRL_ADDR                            0x00000050
#define GFC_NAND_PIO_READ_STATUS_STS_ADDR                            0x00000054
#define GFC_NAND_PIO_STATUS_ADDR                                     0x00000058
#define GFC_SPARE_ADDR                                               0x0000005c
#define GFC_NAND_ERR_CTRL_ADDR                                       0x00000060
#define GFC_NAND_TIMEOUT_ADDR                                        0x00000064
#define GFC_NAND_PIO_BUFFER_CTRL_ADDR                                0x00000068
#define GFC_NAND_PIO_BUFFER_THRESHOLD_ADDR                           0x0000006c
#define GFC_NAND_PIO_BUFFER_THRESHOLD1_ADDR                          0x00000070
#define GFC_GEN_CTRL_ADDR                                            0x00000074
#define GFC_GEN_STS0_ADDR                                            0x00000078
#define GFC_GEN_STS1_ADDR                                            0x0000007c
#define GFC_GEN_STS2_ADDR                                            0x00000080
#define GFC_GEN_STS3_ADDR                                            0x00000084
#define GFC_GEN_STS4_ADDR                                            0x00000088
#define GFC_NAND_PIO_ECC_ERR_ROW_ADDR                                0x0000008c
#define GFC_NAND_PIO_ECC_ERR_COL_ADDR                                0x00000090
#define GFC_ECC_RAM_CTRL_ADDR                                        0x00000094
#define GFC_FIFO0_ADDR                                               0x00000098
#define GFC_FIFO1_ADDR                                               0x0000009c
#define GFC_FIFO2_ADDR                                               0x000000a0
#define GFC_FIFO3_ADDR                                               0x000000a4
#define GFC_FIFO4_ADDR                                               0x000000a8
#define GFC_FIFO5_ADDR                                               0x000000ac
#define GFC_DA_ERR_ADDR                                              0x000000b0
#define GFC_ARB_CTRL_ADDR                                            0x000000b4
#define GFC_ARB_CTRL1_ADDR                                           0x000000b8
#define GFC_AXIM_CTRL_ADDR                                           0x000000bc
#define GFC_AXIWM_STS0_ADDR                                          0x000000c0
#define GFC_AXIWM_STS1_ADDR                                          0x000000c4
#define GFC_AXIRM_STS0_ADDR                                          0x000000c8
#define GFC_AXIRM_STS1_ADDR                                          0x000000cc
#define GFC_BANK0_CTRL0_ADDR                                         0x00002000
#define GFC_BANK0_START_ADD_ADDR                                     0x00002008
#define GFC_BANK0_END_ADD_ADDR                                       0x00002010
#define GFC_BANK0_BASE_ADD_ADDR                                      0x00002018
#define GFC_BANK0_DMA_CTRL0_ADDR                                     0x00002020
#define GFC_BANK0_DMA_START_ADD0_ADDR                                0x00002024
#define GFC_BANK0_DMA_START_ADD1_ADDR                                0x00002028
#define GFC_BANK0_DMA_DES_ADD0_ADDR                                  0x0000202c
#define GFC_BANK0_DMA_DES_ADD1_ADDR                                  0x00002030
#define GFC_BANK0_DMA_STATUS_ADDR                                    0x00002034
#define GFC_BANK0_DMA_ECCERR0_ADD_COL_ADDR                           0x00002038
#define GFC_BANK0_DMA_ECCERR0_ADD_ROW_ADDR                           0x0000203c
#define GFC_BANK0_DMA_ECCERR1_ADD_COL_ADDR                           0x00002040
#define GFC_BANK0_DMA_ECCERR1_ADD_ROW_ADDR                           0x00002044
#define GFC_BANK0_INTERRUPT_ADDR                                     0x00002050
#define GFC_BANK0_INTERRUPTMASK_ADDR                                 0x00002054
#define GFC_BANK0_SRAM_CTRL0_ADDR                                    0x00002100
#define GFC_BANK0_SRAM_NOR_CTRL1_ADDR                                0x00002104
#define GFC_BANK0_SRAM_NOR_CTRL2_ADDR                                0x00002108
#define GFC_BANK0_NAND_CTRL0_ADDR                                    0x00002200
#define GFC_BANK0_NAND_CTRL1_ADDR                                    0x00002204
#define GFC_BANK0_NAND_CTRL2_ADDR                                    0x00002208
#define GFC_BANK0_NAND_BCH_ADDR                                      0x0000220c
#define GFC_BANK0_DMA_CTRL1_ADDR                                     0x00002220
#define GFC_BANK0_NAND_CTRL3_ADDR                                    0x00002224
#define GFC_BANK0_NAND_CTRL4_ADDR                                    0x00002228
#define GFC_BANK0_NAND_TIMING0_ADDR                                  0x0000222c
#define GFC_BANK0_NAND_TIMING1_ADDR                                  0x00002230
#define GFC_BANK0_NAND_TIMING2_ADDR                                  0x00002234
#define GFC_BANK0_NAND_TIMING3_ADDR                                  0x00002238
#define GFC_BANK0_NAND_COR_ERR_ADDR                                  0x0000223c
#define GFC_BANK0_NAND_UNCOR_ERR_ADDR                                0x00002240
#define GFC_BANK1_CTRL0_ADDR                                         0x00003000
#define GFC_BANK1_START_ADD_ADDR                                     0x00003008
#define GFC_BANK1_END_ADD_ADDR                                       0x00003010
#define GFC_BANK1_BASE_ADD_ADDR                                      0x00003018
#define GFC_BANK1_DMA_CTRL0_ADDR                                     0x00003020
#define GFC_BANK1_DMA_START_ADD0_ADDR                                0x00003024
#define GFC_BANK1_DMA_START_ADD1_ADDR                                0x00003028
#define GFC_BANK1_DMA_DES_ADD0_ADDR                                  0x0000302c
#define GFC_BANK1_DMA_DES_ADD1_ADDR                                  0x00003030
#define GFC_BANK1_DMA_STATUS_ADDR                                    0x00003034
#define GFC_BANK1_DMA_ECCERR0_ADD_COL_ADDR                           0x00003038
#define GFC_BANK1_DMA_ECCERR0_ADD_ROW_ADDR                           0x0000303c
#define GFC_BANK1_DMA_ECCERR1_ADD_COL_ADDR                           0x00003040
#define GFC_BANK1_DMA_ECCERR1_ADD_ROW_ADDR                           0x00003044
#define GFC_BANK1_INTERRUPT_ADDR                                     0x00003050
#define GFC_BANK1_INTERRUPTMASK_ADDR                                 0x00003054
#define GFC_BANK1_SRAM_CTRL0_ADDR                                    0x00003100
#define GFC_BANK1_SRAM_NOR_CTRL1_ADDR                                0x00003104
#define GFC_BANK1_SRAM_NOR_CTRL2_ADDR                                0x00003108
#define GFC_BANK1_NAND_CTRL0_ADDR                                    0x00003200
#define GFC_BANK1_NAND_CTRL1_ADDR                                    0x00003204
#define GFC_BANK1_NAND_CTRL2_ADDR                                    0x00003208
#define GFC_BANK1_NAND_BCH_ADDR                                      0x0000320c
#define GFC_BANK1_DMA_CTRL1_ADDR                                     0x00003220
#define GFC_BANK1_NAND_CTRL3_ADDR                                    0x00003224
#define GFC_BANK1_NAND_CTRL4_ADDR                                    0x00003228
#define GFC_BANK1_NAND_TIMING0_ADDR                                  0x0000322c
#define GFC_BANK1_NAND_TIMING1_ADDR                                  0x00003230
#define GFC_BANK1_NAND_TIMING2_ADDR                                  0x00003234
#define GFC_BANK1_NAND_TIMING3_ADDR                                  0x00003238
#define GFC_BANK1_NAND_COR_ERR_ADDR                                  0x0000323c
#define GFC_BANK1_NAND_UNCOR_ERR_ADDR                                0x00003240
#define GFC_BANK2_CTRL0_ADDR                                         0x00004000
#define GFC_BANK2_START_ADD_ADDR                                     0x00004008
#define GFC_BANK2_END_ADD_ADDR                                       0x00004010
#define GFC_BANK2_BASE_ADD_ADDR                                      0x00004018
#define GFC_BANK2_DMA_CTRL0_ADDR                                     0x00004020
#define GFC_BANK2_DMA_START_ADD0_ADDR                                0x00004024
#define GFC_BANK2_DMA_START_ADD1_ADDR                                0x00004028
#define GFC_BANK2_DMA_DES_ADD0_ADDR                                  0x0000402c
#define GFC_BANK2_DMA_DES_ADD1_ADDR                                  0x00004030
#define GFC_BANK2_DMA_STATUS_ADDR                                    0x00004034
#define GFC_BANK2_DMA_ECCERR0_ADD_COL_ADDR                           0x00004038
#define GFC_BANK2_DMA_ECCERR0_ADD_ROW_ADDR                           0x0000403c
#define GFC_BANK2_DMA_ECCERR1_ADD_COL_ADDR                           0x00004040
#define GFC_BANK2_DMA_ECCERR1_ADD_ROW_ADDR                           0x00004044
#define GFC_BANK2_INTERRUPT_ADDR                                     0x00004050
#define GFC_BANK2_INTERRUPTMASK_ADDR                                 0x00004054
#define GFC_BANK2_SRAM_CTRL0_ADDR                                    0x00004100
#define GFC_BANK2_SRAM_NOR_CTRL1_ADDR                                0x00004104
#define GFC_BANK2_SRAM_NOR_CTRL2_ADDR                                0x00004108
#define GFC_BANK2_NAND_CTRL0_ADDR                                    0x00004200
#define GFC_BANK2_NAND_CTRL1_ADDR                                    0x00004204
#define GFC_BANK2_NAND_CTRL2_ADDR                                    0x00004208
#define GFC_BANK2_NAND_BCH_ADDR                                      0x0000420c
#define GFC_BANK2_DMA_CTRL1_ADDR                                     0x00004220
#define GFC_BANK2_NAND_CTRL3_ADDR                                    0x00004224
#define GFC_BANK2_NAND_CTRL4_ADDR                                    0x00004228
#define GFC_BANK2_NAND_TIMING0_ADDR                                  0x0000422c
#define GFC_BANK2_NAND_TIMING1_ADDR                                  0x00004230
#define GFC_BANK2_NAND_TIMING2_ADDR                                  0x00004234
#define GFC_BANK2_NAND_TIMING3_ADDR                                  0x00004238
#define GFC_BANK2_NAND_COR_ERR_ADDR                                  0x0000423c
#define GFC_BANK2_NAND_UNCOR_ERR_ADDR                                0x00004240
#define GFC_BANK3_CTRL0_ADDR                                         0x00005000
#define GFC_BANK3_START_ADD_ADDR                                     0x00005008
#define GFC_BANK3_END_ADD_ADDR                                       0x00005010
#define GFC_BANK3_BASE_ADD_ADDR                                      0x00005018
#define GFC_BANK3_DMA_CTRL0_ADDR                                     0x00005020
#define GFC_BANK3_DMA_START_ADD0_ADDR                                0x00005024
#define GFC_BANK3_DMA_START_ADD1_ADDR                                0x00005028
#define GFC_BANK3_DMA_DES_ADD0_ADDR                                  0x0000502c
#define GFC_BANK3_DMA_DES_ADD1_ADDR                                  0x00005030
#define GFC_BANK3_DMA_STATUS_ADDR                                    0x00005034
#define GFC_BANK3_DMA_ECCERR0_ADD_COL_ADDR                           0x00005038
#define GFC_BANK3_DMA_ECCERR0_ADD_ROW_ADDR                           0x0000503c
#define GFC_BANK3_DMA_ECCERR1_ADD_COL_ADDR                           0x00005040
#define GFC_BANK3_DMA_ECCERR1_ADD_ROW_ADDR                           0x00005044
#define GFC_BANK3_INTERRUPT_ADDR                                     0x00005050
#define GFC_BANK3_INTERRUPTMASK_ADDR                                 0x00005054
#define GFC_BANK3_SRAM_CTRL0_ADDR                                    0x00005100
#define GFC_BANK3_SRAM_NOR_CTRL1_ADDR                                0x00005104
#define GFC_BANK3_SRAM_NOR_CTRL2_ADDR                                0x00005108
#define GFC_BANK3_NAND_CTRL0_ADDR                                    0x00005200
#define GFC_BANK3_NAND_CTRL1_ADDR                                    0x00005204
#define GFC_BANK3_NAND_CTRL2_ADDR                                    0x00005208
#define GFC_BANK3_NAND_BCH_ADDR                                      0x0000520c
#define GFC_BANK3_DMA_CTRL1_ADDR                                     0x00005220
#define GFC_BANK3_NAND_CTRL3_ADDR                                    0x00005224
#define GFC_BANK3_NAND_CTRL4_ADDR                                    0x00005228
#define GFC_BANK3_NAND_TIMING0_ADDR                                  0x0000522c
#define GFC_BANK3_NAND_TIMING1_ADDR                                  0x00005230
#define GFC_BANK3_NAND_TIMING2_ADDR                                  0x00005234
#define GFC_BANK3_NAND_TIMING3_ADDR                                  0x00005238
#define GFC_BANK3_NAND_COR_ERR_ADDR                                  0x0000523c
#define GFC_BANK3_NAND_UNCOR_ERR_ADDR                                0x00005240
#define GFC_BANK4_CTRL0_ADDR                                         0x00006000
#define GFC_BANK4_START_ADD_ADDR                                     0x00006008
#define GFC_BANK4_END_ADD_ADDR                                       0x00006010
#define GFC_BANK4_BASE_ADD_ADDR                                      0x00006018
#define GFC_BANK4_DMA_CTRL0_ADDR                                     0x00006020
#define GFC_BANK4_DMA_START_ADD0_ADDR                                0x00006024
#define GFC_BANK4_DMA_START_ADD1_ADDR                                0x00006028
#define GFC_BANK4_DMA_DES_ADD0_ADDR                                  0x0000602c
#define GFC_BANK4_DMA_DES_ADD1_ADDR                                  0x00006030
#define GFC_BANK4_DMA_STATUS_ADDR                                    0x00006034
#define GFC_BANK4_DMA_ECCERR0_ADD_COL_ADDR                           0x00006038
#define GFC_BANK4_DMA_ECCERR0_ADD_ROW_ADDR                           0x0000603c
#define GFC_BANK4_DMA_ECCERR1_ADD_COL_ADDR                           0x00006040
#define GFC_BANK4_DMA_ECCERR1_ADD_ROW_ADDR                           0x00006044
#define GFC_BANK4_INTERRUPT_ADDR                                     0x00006050
#define GFC_BANK4_INTERRUPTMASK_ADDR                                 0x00006054
#define GFC_BANK4_SRAM_CTRL0_ADDR                                    0x00006100
#define GFC_BANK4_SRAM_NOR_CTRL1_ADDR                                0x00006104
#define GFC_BANK4_SRAM_NOR_CTRL2_ADDR                                0x00006108
#define GFC_BANK4_NAND_CTRL0_ADDR                                    0x00006200
#define GFC_BANK4_NAND_CTRL1_ADDR                                    0x00006204
#define GFC_BANK4_NAND_CTRL2_ADDR                                    0x00006208
#define GFC_BANK4_NAND_BCH_ADDR                                      0x0000620c
#define GFC_BANK4_DMA_CTRL1_ADDR                                     0x00006220
#define GFC_BANK4_NAND_CTRL3_ADDR                                    0x00006224
#define GFC_BANK4_NAND_CTRL4_ADDR                                    0x00006228
#define GFC_BANK4_NAND_TIMING0_ADDR                                  0x0000622c
#define GFC_BANK4_NAND_TIMING1_ADDR                                  0x00006230
#define GFC_BANK4_NAND_TIMING2_ADDR                                  0x00006234
#define GFC_BANK4_NAND_TIMING3_ADDR                                  0x00006238
#define GFC_BANK4_NAND_COR_ERR_ADDR                                  0x0000623c
#define GFC_BANK4_NAND_UNCOR_ERR_ADDR                                0x00006240
#define GFC_BANK5_CTRL0_ADDR                                         0x00007000
#define GFC_BANK5_START_ADD_ADDR                                     0x00007008
#define GFC_BANK5_END_ADD_ADDR                                       0x00007010
#define GFC_BANK5_BASE_ADD_ADDR                                      0x00007018
#define GFC_BANK5_DMA_CTRL0_ADDR                                     0x00007020
#define GFC_BANK5_DMA_START_ADD0_ADDR                                0x00007024
#define GFC_BANK5_DMA_START_ADD1_ADDR                                0x00007028
#define GFC_BANK5_DMA_DES_ADD0_ADDR                                  0x0000702c
#define GFC_BANK5_DMA_DES_ADD1_ADDR                                  0x00007030
#define GFC_BANK5_DMA_STATUS_ADDR                                    0x00007034
#define GFC_BANK5_DMA_ECCERR0_ADD_COL_ADDR                           0x00007038
#define GFC_BANK5_DMA_ECCERR0_ADD_ROW_ADDR                           0x0000703c
#define GFC_BANK5_DMA_ECCERR1_ADD_COL_ADDR                           0x00007040
#define GFC_BANK5_DMA_ECCERR1_ADD_ROW_ADDR                           0x00007044
#define GFC_BANK5_INTERRUPT_ADDR                                     0x00007050
#define GFC_BANK5_INTERRUPTMASK_ADDR                                 0x00007054
#define GFC_BANK5_SRAM_CTRL0_ADDR                                    0x00007100
#define GFC_BANK5_SRAM_NOR_CTRL1_ADDR                                0x00007104
#define GFC_BANK5_SRAM_NOR_CTRL2_ADDR                                0x00007108
#define GFC_BANK5_NAND_CTRL0_ADDR                                    0x00007200
#define GFC_BANK5_NAND_CTRL1_ADDR                                    0x00007204
#define GFC_BANK5_NAND_CTRL2_ADDR                                    0x00007208
#define GFC_BANK5_NAND_BCH_ADDR                                      0x0000720c
#define GFC_BANK5_DMA_CTRL1_ADDR                                     0x00007220
#define GFC_BANK5_NAND_CTRL3_ADDR                                    0x00007224
#define GFC_BANK5_NAND_CTRL4_ADDR                                    0x00007228
#define GFC_BANK5_NAND_TIMING0_ADDR                                  0x0000722c
#define GFC_BANK5_NAND_TIMING1_ADDR                                  0x00007230
#define GFC_BANK5_NAND_TIMING2_ADDR                                  0x00007234
#define GFC_BANK5_NAND_TIMING3_ADDR                                  0x00007238
#define GFC_BANK5_NAND_COR_ERR_ADDR                                  0x0000723c
#define GFC_BANK5_NAND_UNCOR_ERR_ADDR                                0x00007240

#define BANK0 0
#define BANK1 1
#define BANK2 2
#define BANK3 3
#define BANK4 4
#define BANK5 5

#define NAND     0
#define NOR      1
#define SRAM     2

#define READ_ONLY   1
#define WRITE_ONLY  2
#define READ_WRITE  3

#define BUS_WIDTH_8   0
#define BUS_WIDTH_16  1
#define BUS_WIDTH_32  2

#define BANKVALID 1
 
//NOR/SRAM timing parameters, device specific
#define twt 6 
#define fwt 6 
#define bwt 6
#define csn 1
#define oen 1
#define wbn 1
#define wbf 2
#define th  1
#define aln 4     
#define alh 2

#define burst_en 1
#define mux_en   1


int board_gfc_nor_init(void);



/*	Register gfc_iprev	*/
/*	 Fields gfc_rev	 */
#define GFC_REV_WIDTH                                                        32
#define GFC_REV_SHIFT                                                         0
#define GFC_REV_MASK                                                 0xffffffff
#define GFC_REV_RD(src)                                  (((src) & 0xffffffff))
#define GFC_REV_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_scratch_reg	*/
/*	 Fields gfc_scratch	 */
#define GFC_SCRATCH_WIDTH                                                    32
#define GFC_SCRATCH_SHIFT                                                     0
#define GFC_SCRATCH_MASK                                             0xffffffff
#define GFC_SCRATCH_RD(src)                              (((src) & 0xffffffff))
#define GFC_SCRATCH_WR(src)                         (((u32)(src)) & 0xffffffff)
#define GFC_SCRATCH_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_INT	*/
/*	 Fields nand_dma_wm_err	 */
#define NAND_DMA_WM_ERR_WIDTH                                                 1
#define NAND_DMA_WM_ERR_SHIFT                                                16
#define NAND_DMA_WM_ERR_MASK                                         0x00010000
#define NAND_DMA_WM_ERR_RD(src)                      (((src) & 0x00010000)>>16)
#define NAND_DMA_WM_ERR_WR(src)                 (((u32)(src)<<16) & 0x00010000)
#define NAND_DMA_WM_ERR_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields nand_dma_rm_err	 */
#define NAND_DMA_RM_ERR_WIDTH                                                 1
#define NAND_DMA_RM_ERR_SHIFT                                                15
#define NAND_DMA_RM_ERR_MASK                                         0x00008000
#define NAND_DMA_RM_ERR_RD(src)                      (((src) & 0x00008000)>>15)
#define NAND_DMA_RM_ERR_WR(src)                 (((u32)(src)<<15) & 0x00008000)
#define NAND_DMA_RM_ERR_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields nand_dma_timeout_abort	 */
#define NAND_DMA_TIMEOUT_ABORT_WIDTH                                          1
#define NAND_DMA_TIMEOUT_ABORT_SHIFT                                         14
#define NAND_DMA_TIMEOUT_ABORT_MASK                                  0x00004000
#define NAND_DMA_TIMEOUT_ABORT_RD(src)               (((src) & 0x00004000)>>14)
#define NAND_DMA_TIMEOUT_ABORT_WR(src)          (((u32)(src)<<14) & 0x00004000)
#define NAND_DMA_TIMEOUT_ABORT_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields rdybsyn_deassert	 */
#define RDYBSYN_DEASSERT_WIDTH                                                1
#define RDYBSYN_DEASSERT_SHIFT                                               13
#define RDYBSYN_DEASSERT_MASK                                        0x00002000
#define RDYBSYN_DEASSERT_RD(src)                     (((src) & 0x00002000)>>13)
#define RDYBSYN_DEASSERT_WR(src)                (((u32)(src)<<13) & 0x00002000)
#define RDYBSYN_DEASSERT_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields rdybsyn_assert	 */
#define RDYBSYN_ASSERT_WIDTH                                                  1
#define RDYBSYN_ASSERT_SHIFT                                                 12
#define RDYBSYN_ASSERT_MASK                                          0x00001000
#define RDYBSYN_ASSERT_RD(src)                       (((src) & 0x00001000)>>12)
#define RDYBSYN_ASSERT_WR(src)                  (((u32)(src)<<12) & 0x00001000)
#define RDYBSYN_ASSERT_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields ready_deassert	 */
#define READY_DEASSERT_WIDTH                                                  1
#define READY_DEASSERT_SHIFT                                                 11
#define READY_DEASSERT_MASK                                          0x00000800
#define READY_DEASSERT_RD(src)                       (((src) & 0x00000800)>>11)
#define READY_DEASSERT_WR(src)                  (((u32)(src)<<11) & 0x00000800)
#define READY_DEASSERT_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields ready_assert	 */
#define READY_ASSERT_WIDTH                                                    1
#define READY_ASSERT_SHIFT                                                   10
#define READY_ASSERT_MASK                                            0x00000400
#define READY_ASSERT_RD(src)                         (((src) & 0x00000400)>>10)
#define READY_ASSERT_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define READY_ASSERT_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields sram_dma_op_complete	 */
#define SRAM_DMA_OP_COMPLETE_WIDTH                                            1
#define SRAM_DMA_OP_COMPLETE_SHIFT                                            9
#define SRAM_DMA_OP_COMPLETE_MASK                                    0x00000200
#define SRAM_DMA_OP_COMPLETE_RD(src)                  (((src) & 0x00000200)>>9)
#define SRAM_DMA_OP_COMPLETE_WR(src)             (((u32)(src)<<9) & 0x00000200)
#define SRAM_DMA_OP_COMPLETE_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields nand_dma_op_complete	 */
#define NAND_DMA_OP_COMPLETE_WIDTH                                            1
#define NAND_DMA_OP_COMPLETE_SHIFT                                            8
#define NAND_DMA_OP_COMPLETE_MASK                                    0x00000100
#define NAND_DMA_OP_COMPLETE_RD(src)                  (((src) & 0x00000100)>>8)
#define NAND_DMA_OP_COMPLETE_WR(src)             (((u32)(src)<<8) & 0x00000100)
#define NAND_DMA_OP_COMPLETE_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields nand_timeout_abort	 */
#define NAND_TIMEOUT_ABORT_WIDTH                                              1
#define NAND_TIMEOUT_ABORT_SHIFT                                              7
#define NAND_TIMEOUT_ABORT_MASK                                      0x00000080
#define NAND_TIMEOUT_ABORT_RD(src)                    (((src) & 0x00000080)>>7)
#define NAND_TIMEOUT_ABORT_WR(src)               (((u32)(src)<<7) & 0x00000080)
#define NAND_TIMEOUT_ABORT_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields nand_pio_op_complete	 */
#define NAND_PIO_OP_COMPLETE_WIDTH                                            1
#define NAND_PIO_OP_COMPLETE_SHIFT                                            6
#define NAND_PIO_OP_COMPLETE_MASK                                    0x00000040
#define NAND_PIO_OP_COMPLETE_RD(src)                  (((src) & 0x00000040)>>6)
#define NAND_PIO_OP_COMPLETE_WR(src)             (((u32)(src)<<6) & 0x00000040)
#define NAND_PIO_OP_COMPLETE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields nand_pio_wbuf_full	 */
#define NAND_PIO_WBUF_FULL_WIDTH                                              1
#define NAND_PIO_WBUF_FULL_SHIFT                                              5
#define NAND_PIO_WBUF_FULL_MASK                                      0x00000020
#define NAND_PIO_WBUF_FULL_RD(src)                    (((src) & 0x00000020)>>5)
#define NAND_PIO_WBUF_FULL_WR(src)               (((u32)(src)<<5) & 0x00000020)
#define NAND_PIO_WBUF_FULL_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields nand_pio_wbuf_empty	 */
#define NAND_PIO_WBUF_EMPTY_WIDTH                                             1
#define NAND_PIO_WBUF_EMPTY_SHIFT                                             4
#define NAND_PIO_WBUF_EMPTY_MASK                                     0x00000010
#define NAND_PIO_WBUF_EMPTY_RD(src)                   (((src) & 0x00000010)>>4)
#define NAND_PIO_WBUF_EMPTY_WR(src)              (((u32)(src)<<4) & 0x00000010)
#define NAND_PIO_WBUF_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields nand_pio_rbuf_full	 */
#define NAND_PIO_RBUF_FULL_WIDTH                                              1
#define NAND_PIO_RBUF_FULL_SHIFT                                              3
#define NAND_PIO_RBUF_FULL_MASK                                      0x00000008
#define NAND_PIO_RBUF_FULL_RD(src)                    (((src) & 0x00000008)>>3)
#define NAND_PIO_RBUF_FULL_WR(src)               (((u32)(src)<<3) & 0x00000008)
#define NAND_PIO_RBUF_FULL_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields nand_pio_rbuf_nonempty	 */
#define NAND_PIO_RBUF_NONEMPTY_WIDTH                                          1
#define NAND_PIO_RBUF_NONEMPTY_SHIFT                                          2
#define NAND_PIO_RBUF_NONEMPTY_MASK                                  0x00000004
#define NAND_PIO_RBUF_NONEMPTY_RD(src)                (((src) & 0x00000004)>>2)
#define NAND_PIO_RBUF_NONEMPTY_WR(src)           (((u32)(src)<<2) & 0x00000004)
#define NAND_PIO_RBUF_NONEMPTY_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields nobank	 */
#define NOBANK_WIDTH                                                          1
#define NOBANK_SHIFT                                                          1
#define NOBANK_MASK                                                  0x00000002
#define NOBANK_RD(src)                                (((src) & 0x00000002)>>1)
#define NOBANK_WR(src)                           (((u32)(src)<<1) & 0x00000002)
#define NOBANK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields multiplebank	 */
#define MULTIPLEBANK_WIDTH                                                    1
#define MULTIPLEBANK_SHIFT                                                    0
#define MULTIPLEBANK_MASK                                            0x00000001
#define MULTIPLEBANK_RD(src)                             (((src) & 0x00000001))
#define MULTIPLEBANK_WR(src)                        (((u32)(src)) & 0x00000001)
#define MULTIPLEBANK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_interruptMask	*/
/*    Mask Register Fields nand_dma_wm_errMask    */
#define NAND_DMA_WM_ERRMASK_WIDTH                                             1
#define NAND_DMA_WM_ERRMASK_SHIFT                                            16
#define NAND_DMA_WM_ERRMASK_MASK                                     0x00010000
#define NAND_DMA_WM_ERRMASK_RD(src)                  (((src) & 0x00010000)>>16)
#define NAND_DMA_WM_ERRMASK_WR(src)             (((u32)(src)<<16) & 0x00010000)
#define NAND_DMA_WM_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields nand_dma_rm_errMask    */
#define NAND_DMA_RM_ERRMASK_WIDTH                                             1
#define NAND_DMA_RM_ERRMASK_SHIFT                                            15
#define NAND_DMA_RM_ERRMASK_MASK                                     0x00008000
#define NAND_DMA_RM_ERRMASK_RD(src)                  (((src) & 0x00008000)>>15)
#define NAND_DMA_RM_ERRMASK_WR(src)             (((u32)(src)<<15) & 0x00008000)
#define NAND_DMA_RM_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields nand_dma_timeout_abortMask    */
#define NAND_DMA_TIMEOUT_ABORTMASK_WIDTH                                      1
#define NAND_DMA_TIMEOUT_ABORTMASK_SHIFT                                     14
#define NAND_DMA_TIMEOUT_ABORTMASK_MASK                              0x00004000
#define NAND_DMA_TIMEOUT_ABORTMASK_RD(src)           (((src) & 0x00004000)>>14)
#define NAND_DMA_TIMEOUT_ABORTMASK_WR(src)      (((u32)(src)<<14) & 0x00004000)
#define NAND_DMA_TIMEOUT_ABORTMASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields rdybsyn_deassertMask    */
#define RDYBSYN_DEASSERTMASK_WIDTH                                            1
#define RDYBSYN_DEASSERTMASK_SHIFT                                           13
#define RDYBSYN_DEASSERTMASK_MASK                                    0x00002000
#define RDYBSYN_DEASSERTMASK_RD(src)                 (((src) & 0x00002000)>>13)
#define RDYBSYN_DEASSERTMASK_WR(src)            (((u32)(src)<<13) & 0x00002000)
#define RDYBSYN_DEASSERTMASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields rdybsyn_assertMask    */
#define RDYBSYN_ASSERTMASK_WIDTH                                              1
#define RDYBSYN_ASSERTMASK_SHIFT                                             12
#define RDYBSYN_ASSERTMASK_MASK                                      0x00001000
#define RDYBSYN_ASSERTMASK_RD(src)                   (((src) & 0x00001000)>>12)
#define RDYBSYN_ASSERTMASK_WR(src)              (((u32)(src)<<12) & 0x00001000)
#define RDYBSYN_ASSERTMASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields ready_deassertMask    */
#define READY_DEASSERTMASK_WIDTH                                              1
#define READY_DEASSERTMASK_SHIFT                                             11
#define READY_DEASSERTMASK_MASK                                      0x00000800
#define READY_DEASSERTMASK_RD(src)                   (((src) & 0x00000800)>>11)
#define READY_DEASSERTMASK_WR(src)              (((u32)(src)<<11) & 0x00000800)
#define READY_DEASSERTMASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields ready_assertMask    */
#define READY_ASSERTMASK_WIDTH                                                1
#define READY_ASSERTMASK_SHIFT                                               10
#define READY_ASSERTMASK_MASK                                        0x00000400
#define READY_ASSERTMASK_RD(src)                     (((src) & 0x00000400)>>10)
#define READY_ASSERTMASK_WR(src)                (((u32)(src)<<10) & 0x00000400)
#define READY_ASSERTMASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields sram_dma_op_completeMask    */
#define SRAM_DMA_OP_COMPLETEMASK_WIDTH                                        1
#define SRAM_DMA_OP_COMPLETEMASK_SHIFT                                        9
#define SRAM_DMA_OP_COMPLETEMASK_MASK                                0x00000200
#define SRAM_DMA_OP_COMPLETEMASK_RD(src)              (((src) & 0x00000200)>>9)
#define SRAM_DMA_OP_COMPLETEMASK_WR(src)         (((u32)(src)<<9) & 0x00000200)
#define SRAM_DMA_OP_COMPLETEMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields nand_dma_op_completeMask    */
#define NAND_DMA_OP_COMPLETEMASK_WIDTH                                        1
#define NAND_DMA_OP_COMPLETEMASK_SHIFT                                        8
#define NAND_DMA_OP_COMPLETEMASK_MASK                                0x00000100
#define NAND_DMA_OP_COMPLETEMASK_RD(src)              (((src) & 0x00000100)>>8)
#define NAND_DMA_OP_COMPLETEMASK_WR(src)         (((u32)(src)<<8) & 0x00000100)
#define NAND_DMA_OP_COMPLETEMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields nand_timeout_abortMask    */
#define NAND_TIMEOUT_ABORTMASK_WIDTH                                          1
#define NAND_TIMEOUT_ABORTMASK_SHIFT                                          7
#define NAND_TIMEOUT_ABORTMASK_MASK                                  0x00000080
#define NAND_TIMEOUT_ABORTMASK_RD(src)                (((src) & 0x00000080)>>7)
#define NAND_TIMEOUT_ABORTMASK_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define NAND_TIMEOUT_ABORTMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields nand_pio_op_completeMask    */
#define NAND_PIO_OP_COMPLETEMASK_WIDTH                                        1
#define NAND_PIO_OP_COMPLETEMASK_SHIFT                                        6
#define NAND_PIO_OP_COMPLETEMASK_MASK                                0x00000040
#define NAND_PIO_OP_COMPLETEMASK_RD(src)              (((src) & 0x00000040)>>6)
#define NAND_PIO_OP_COMPLETEMASK_WR(src)         (((u32)(src)<<6) & 0x00000040)
#define NAND_PIO_OP_COMPLETEMASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields nand_pio_wbuf_fullMask    */
#define NAND_PIO_WBUF_FULLMASK_WIDTH                                          1
#define NAND_PIO_WBUF_FULLMASK_SHIFT                                          5
#define NAND_PIO_WBUF_FULLMASK_MASK                                  0x00000020
#define NAND_PIO_WBUF_FULLMASK_RD(src)                (((src) & 0x00000020)>>5)
#define NAND_PIO_WBUF_FULLMASK_WR(src)           (((u32)(src)<<5) & 0x00000020)
#define NAND_PIO_WBUF_FULLMASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields nand_pio_wbuf_emptyMask    */
#define NAND_PIO_WBUF_EMPTYMASK_WIDTH                                         1
#define NAND_PIO_WBUF_EMPTYMASK_SHIFT                                         4
#define NAND_PIO_WBUF_EMPTYMASK_MASK                                 0x00000010
#define NAND_PIO_WBUF_EMPTYMASK_RD(src)               (((src) & 0x00000010)>>4)
#define NAND_PIO_WBUF_EMPTYMASK_WR(src)          (((u32)(src)<<4) & 0x00000010)
#define NAND_PIO_WBUF_EMPTYMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields nand_pio_rbuf_fullMask    */
#define NAND_PIO_RBUF_FULLMASK_WIDTH                                          1
#define NAND_PIO_RBUF_FULLMASK_SHIFT                                          3
#define NAND_PIO_RBUF_FULLMASK_MASK                                  0x00000008
#define NAND_PIO_RBUF_FULLMASK_RD(src)                (((src) & 0x00000008)>>3)
#define NAND_PIO_RBUF_FULLMASK_WR(src)           (((u32)(src)<<3) & 0x00000008)
#define NAND_PIO_RBUF_FULLMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields nand_pio_rbuf_nonemptyMask    */
#define NAND_PIO_RBUF_NONEMPTYMASK_WIDTH                                      1
#define NAND_PIO_RBUF_NONEMPTYMASK_SHIFT                                      2
#define NAND_PIO_RBUF_NONEMPTYMASK_MASK                              0x00000004
#define NAND_PIO_RBUF_NONEMPTYMASK_RD(src)            (((src) & 0x00000004)>>2)
#define NAND_PIO_RBUF_NONEMPTYMASK_WR(src)       (((u32)(src)<<2) & 0x00000004)
#define NAND_PIO_RBUF_NONEMPTYMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields nobankMask    */
#define NOBANKMASK_WIDTH                                                      1
#define NOBANKMASK_SHIFT                                                      1
#define NOBANKMASK_MASK                                              0x00000002
#define NOBANKMASK_RD(src)                            (((src) & 0x00000002)>>1)
#define NOBANKMASK_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define NOBANKMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields multiplebankMask    */
#define MULTIPLEBANKMASK_WIDTH                                                1
#define MULTIPLEBANKMASK_SHIFT                                                0
#define MULTIPLEBANKMASK_MASK                                        0x00000001
#define MULTIPLEBANKMASK_RD(src)                         (((src) & 0x00000001))
#define MULTIPLEBANKMASK_WR(src)                    (((u32)(src)) & 0x00000001)
#define MULTIPLEBANKMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_nand_pio_ctrl	*/
/*	 Fields size	 */
#define REGSPEC_SIZE_WIDTH                                                   24
#define REGSPEC_SIZE_SHIFT                                                    8
#define REGSPEC_SIZE_MASK                                            0xffffff00
#define REGSPEC_SIZE_RD(src)                          (((src) & 0xffffff00)>>8)
#define REGSPEC_SIZE_WR(src)                     (((u32)(src)<<8) & 0xffffff00)
#define REGSPEC_SIZE_SET(dst,src) \
                       (((dst) & ~0xffffff00) | (((u32)(src)<<8) & 0xffffff00))
/*	 Fields bypass_ecc	 */
#define BYPASS_ECC_WIDTH                                                      1
#define BYPASS_ECC_SHIFT                                                      7
#define BYPASS_ECC_MASK                                              0x00000080
#define BYPASS_ECC_RD(src)                            (((src) & 0x00000080)>>7)
#define BYPASS_ECC_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define BYPASS_ECC_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields write	 */
#define REGSPEC_GFC_WRITE_WIDTH                                                   1
#define REGSPEC_GFC_WRITE_SHIFT                                                   6
#define REGSPEC_GFC_WRITE_MASK                                           0x00000040
#define REGSPEC_GFC_WRITE_RD(src)                         (((src) & 0x00000040)>>6)
#define REGSPEC_GFC_WRITE_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define REGSPEC_GFC_WRITE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields read	 */
#define REGSPEC_GFC_READ_WIDTH                                                    1
#define REGSPEC_GFC_READ_SHIFT                                                    5
#define REGSPEC_GFC_READ_MASK                                            0x00000020
#define REGSPEC_GFC_READ_RD(src)                          (((src) & 0x00000020)>>5)
#define REGSPEC_GFC_READ_WR(src)                     (((u32)(src)<<5) & 0x00000020)
#define REGSPEC_GFC_READ_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields start	 */
#define START_GFC_WIDTH                                                           1
#define START_GFC_SHIFT                                                           4
#define START_GFC_MASK                                                   0x00000010
#define START_GFC_RD(src)                                 (((src) & 0x00000010)>>4)
#define START_GFC_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define START_GFC_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields device_addr	 */
#define DEVICE_ADDR_WIDTH                                                     3
#define DEVICE_ADDR_SHIFT                                                     1
#define DEVICE_ADDR_MASK                                             0x0000000e
#define DEVICE_ADDR_RD(src)                           (((src) & 0x0000000e)>>1)
#define DEVICE_ADDR_WR(src)                      (((u32)(src)<<1) & 0x0000000e)
#define DEVICE_ADDR_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields lock	 */
#define REGSPEC_LOCK_WIDTH                                                    1
#define REGSPEC_LOCK_SHIFT                                                    0
#define REGSPEC_LOCK_MASK                                            0x00000001
#define REGSPEC_LOCK_RD(src)                             (((src) & 0x00000001))
#define REGSPEC_LOCK_WR(src)                        (((u32)(src)) & 0x00000001)
#define REGSPEC_LOCK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_nand_pio_reg_ctrl0	*/
/*	 Fields r7_valid	 */
#define R7_VALID0_WIDTH                                                       1
#define R7_VALID0_SHIFT                                                      31
#define R7_VALID0_MASK                                               0x80000000
#define R7_VALID0_RD(src)                            (((src) & 0x80000000)>>31)
#define R7_VALID0_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define R7_VALID0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields r7_bus_ctrl	 */
#define R7_BUS_CTRL0_WIDTH                                                    3
#define R7_BUS_CTRL0_SHIFT                                                   28
#define R7_BUS_CTRL0_MASK                                            0x70000000
#define R7_BUS_CTRL0_RD(src)                         (((src) & 0x70000000)>>28)
#define R7_BUS_CTRL0_WR(src)                    (((u32)(src)<<28) & 0x70000000)
#define R7_BUS_CTRL0_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields r6_valid	 */
#define R6_VALID0_WIDTH                                                       1
#define R6_VALID0_SHIFT                                                      27
#define R6_VALID0_MASK                                               0x08000000
#define R6_VALID0_RD(src)                            (((src) & 0x08000000)>>27)
#define R6_VALID0_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define R6_VALID0_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields r6_bus_ctrl	 */
#define R6_BUS_CTRL0_WIDTH                                                    3
#define R6_BUS_CTRL0_SHIFT                                                   24
#define R6_BUS_CTRL0_MASK                                            0x07000000
#define R6_BUS_CTRL0_RD(src)                         (((src) & 0x07000000)>>24)
#define R6_BUS_CTRL0_WR(src)                    (((u32)(src)<<24) & 0x07000000)
#define R6_BUS_CTRL0_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields r5_valid	 */
#define R5_VALID0_WIDTH                                                       1
#define R5_VALID0_SHIFT                                                      23
#define R5_VALID0_MASK                                               0x00800000
#define R5_VALID0_RD(src)                            (((src) & 0x00800000)>>23)
#define R5_VALID0_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define R5_VALID0_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields r5_bus_ctrl	 */
#define R5_BUS_CTRL0_WIDTH                                                    3
#define R5_BUS_CTRL0_SHIFT                                                   20
#define R5_BUS_CTRL0_MASK                                            0x00700000
#define R5_BUS_CTRL0_RD(src)                         (((src) & 0x00700000)>>20)
#define R5_BUS_CTRL0_WR(src)                    (((u32)(src)<<20) & 0x00700000)
#define R5_BUS_CTRL0_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields r4_valid	 */
#define R4_VALID0_WIDTH                                                       1
#define R4_VALID0_SHIFT                                                      19
#define R4_VALID0_MASK                                               0x00080000
#define R4_VALID0_RD(src)                            (((src) & 0x00080000)>>19)
#define R4_VALID0_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define R4_VALID0_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields r4_bus_ctrl	 */
#define R4_BUS_CTRL0_WIDTH                                                    3
#define R4_BUS_CTRL0_SHIFT                                                   16
#define R4_BUS_CTRL0_MASK                                            0x00070000
#define R4_BUS_CTRL0_RD(src)                         (((src) & 0x00070000)>>16)
#define R4_BUS_CTRL0_WR(src)                    (((u32)(src)<<16) & 0x00070000)
#define R4_BUS_CTRL0_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields r3_valid	 */
#define R3_VALID0_WIDTH                                                       1
#define R3_VALID0_SHIFT                                                      15
#define R3_VALID0_MASK                                               0x00008000
#define R3_VALID0_RD(src)                            (((src) & 0x00008000)>>15)
#define R3_VALID0_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define R3_VALID0_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields r3_bus_ctrl	 */
#define R3_BUS_CTRL0_WIDTH                                                    3
#define R3_BUS_CTRL0_SHIFT                                                   12
#define R3_BUS_CTRL0_MASK                                            0x00007000
#define R3_BUS_CTRL0_RD(src)                         (((src) & 0x00007000)>>12)
#define R3_BUS_CTRL0_WR(src)                    (((u32)(src)<<12) & 0x00007000)
#define R3_BUS_CTRL0_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields r2_valid	 */
#define R2_VALID0_WIDTH                                                       1
#define R2_VALID0_SHIFT                                                      11
#define R2_VALID0_MASK                                               0x00000800
#define R2_VALID0_RD(src)                            (((src) & 0x00000800)>>11)
#define R2_VALID0_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define R2_VALID0_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields r2_bus_ctrl	 */
#define R2_BUS_CTRL0_WIDTH                                                    3
#define R2_BUS_CTRL0_SHIFT                                                    8
#define R2_BUS_CTRL0_MASK                                            0x00000700
#define R2_BUS_CTRL0_RD(src)                          (((src) & 0x00000700)>>8)
#define R2_BUS_CTRL0_WR(src)                     (((u32)(src)<<8) & 0x00000700)
#define R2_BUS_CTRL0_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields r1_valid	 */
#define R1_VALID0_WIDTH                                                       1
#define R1_VALID0_SHIFT                                                       7
#define R1_VALID0_MASK                                               0x00000080
#define R1_VALID0_RD(src)                             (((src) & 0x00000080)>>7)
#define R1_VALID0_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define R1_VALID0_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields r1_bus_ctrl	 */
#define R1_BUS_CTRL0_WIDTH                                                    3
#define R1_BUS_CTRL0_SHIFT                                                    4
#define R1_BUS_CTRL0_MASK                                            0x00000070
#define R1_BUS_CTRL0_RD(src)                          (((src) & 0x00000070)>>4)
#define R1_BUS_CTRL0_WR(src)                     (((u32)(src)<<4) & 0x00000070)
#define R1_BUS_CTRL0_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields r0_valid	 */
#define R0_VALID0_WIDTH                                                       1
#define R0_VALID0_SHIFT                                                       3
#define R0_VALID0_MASK                                               0x00000008
#define R0_VALID0_RD(src)                             (((src) & 0x00000008)>>3)
#define R0_VALID0_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define R0_VALID0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields r0_bus_ctrl	 */
#define R0_BUS_CTRL0_WIDTH                                                    3
#define R0_BUS_CTRL0_SHIFT                                                    0
#define R0_BUS_CTRL0_MASK                                            0x00000007
#define R0_BUS_CTRL0_RD(src)                             (((src) & 0x00000007))
#define R0_BUS_CTRL0_WR(src)                        (((u32)(src)) & 0x00000007)
#define R0_BUS_CTRL0_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register gfc_nand_pio_reg_ctrl1	*/
/*	 Fields r15_valid	 */
#define R15_VALID1_WIDTH                                                      1
#define R15_VALID1_SHIFT                                                     31
#define R15_VALID1_MASK                                              0x80000000
#define R15_VALID1_RD(src)                           (((src) & 0x80000000)>>31)
#define R15_VALID1_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define R15_VALID1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields r15_bus_ctrl	 */
#define R15_BUS_CTRL1_WIDTH                                                   3
#define R15_BUS_CTRL1_SHIFT                                                  28
#define R15_BUS_CTRL1_MASK                                           0x70000000
#define R15_BUS_CTRL1_RD(src)                        (((src) & 0x70000000)>>28)
#define R15_BUS_CTRL1_WR(src)                   (((u32)(src)<<28) & 0x70000000)
#define R15_BUS_CTRL1_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields r14_valid	 */
#define R14_VALID1_WIDTH                                                      1
#define R14_VALID1_SHIFT                                                     27
#define R14_VALID1_MASK                                              0x08000000
#define R14_VALID1_RD(src)                           (((src) & 0x08000000)>>27)
#define R14_VALID1_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define R14_VALID1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields r14_bus_ctrl	 */
#define R14_BUS_CTRL1_WIDTH                                                   3
#define R14_BUS_CTRL1_SHIFT                                                  24
#define R14_BUS_CTRL1_MASK                                           0x07000000
#define R14_BUS_CTRL1_RD(src)                        (((src) & 0x07000000)>>24)
#define R14_BUS_CTRL1_WR(src)                   (((u32)(src)<<24) & 0x07000000)
#define R14_BUS_CTRL1_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields r13_valid	 */
#define R13_VALID1_WIDTH                                                      1
#define R13_VALID1_SHIFT                                                     23
#define R13_VALID1_MASK                                              0x00800000
#define R13_VALID1_RD(src)                           (((src) & 0x00800000)>>23)
#define R13_VALID1_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define R13_VALID1_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields r13_bus_ctrl	 */
#define R13_BUS_CTRL1_WIDTH                                                   3
#define R13_BUS_CTRL1_SHIFT                                                  20
#define R13_BUS_CTRL1_MASK                                           0x00700000
#define R13_BUS_CTRL1_RD(src)                        (((src) & 0x00700000)>>20)
#define R13_BUS_CTRL1_WR(src)                   (((u32)(src)<<20) & 0x00700000)
#define R13_BUS_CTRL1_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields r12_valid	 */
#define R12_VALID1_WIDTH                                                      1
#define R12_VALID1_SHIFT                                                     19
#define R12_VALID1_MASK                                              0x00080000
#define R12_VALID1_RD(src)                           (((src) & 0x00080000)>>19)
#define R12_VALID1_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define R12_VALID1_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields r12_bus_ctrl	 */
#define R12_BUS_CTRL1_WIDTH                                                   3
#define R12_BUS_CTRL1_SHIFT                                                  16
#define R12_BUS_CTRL1_MASK                                           0x00070000
#define R12_BUS_CTRL1_RD(src)                        (((src) & 0x00070000)>>16)
#define R12_BUS_CTRL1_WR(src)                   (((u32)(src)<<16) & 0x00070000)
#define R12_BUS_CTRL1_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields r11_valid	 */
#define R11_VALID1_WIDTH                                                      1
#define R11_VALID1_SHIFT                                                     15
#define R11_VALID1_MASK                                              0x00008000
#define R11_VALID1_RD(src)                           (((src) & 0x00008000)>>15)
#define R11_VALID1_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define R11_VALID1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields r11_bus_ctrl	 */
#define R11_BUS_CTRL1_WIDTH                                                   3
#define R11_BUS_CTRL1_SHIFT                                                  12
#define R11_BUS_CTRL1_MASK                                           0x00007000
#define R11_BUS_CTRL1_RD(src)                        (((src) & 0x00007000)>>12)
#define R11_BUS_CTRL1_WR(src)                   (((u32)(src)<<12) & 0x00007000)
#define R11_BUS_CTRL1_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields r10_valid	 */
#define R10_VALID1_WIDTH                                                      1
#define R10_VALID1_SHIFT                                                     11
#define R10_VALID1_MASK                                              0x00000800
#define R10_VALID1_RD(src)                           (((src) & 0x00000800)>>11)
#define R10_VALID1_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define R10_VALID1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields r10_bus_ctrl	 */
#define R10_BUS_CTRL1_WIDTH                                                   3
#define R10_BUS_CTRL1_SHIFT                                                   8
#define R10_BUS_CTRL1_MASK                                           0x00000700
#define R10_BUS_CTRL1_RD(src)                         (((src) & 0x00000700)>>8)
#define R10_BUS_CTRL1_WR(src)                    (((u32)(src)<<8) & 0x00000700)
#define R10_BUS_CTRL1_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields r9_valid	 */
#define R9_VALID1_WIDTH                                                       1
#define R9_VALID1_SHIFT                                                       7
#define R9_VALID1_MASK                                               0x00000080
#define R9_VALID1_RD(src)                             (((src) & 0x00000080)>>7)
#define R9_VALID1_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define R9_VALID1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields r9_bus_ctrl	 */
#define R9_BUS_CTRL1_WIDTH                                                    3
#define R9_BUS_CTRL1_SHIFT                                                    4
#define R9_BUS_CTRL1_MASK                                            0x00000070
#define R9_BUS_CTRL1_RD(src)                          (((src) & 0x00000070)>>4)
#define R9_BUS_CTRL1_WR(src)                     (((u32)(src)<<4) & 0x00000070)
#define R9_BUS_CTRL1_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields r8_valid	 */
#define R8_VALID1_WIDTH                                                       1
#define R8_VALID1_SHIFT                                                       3
#define R8_VALID1_MASK                                               0x00000008
#define R8_VALID1_RD(src)                             (((src) & 0x00000008)>>3)
#define R8_VALID1_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define R8_VALID1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields r8_bus_ctrl	 */
#define R8_BUS_CTRL1_WIDTH                                                    3
#define R8_BUS_CTRL1_SHIFT                                                    0
#define R8_BUS_CTRL1_MASK                                            0x00000007
#define R8_BUS_CTRL1_RD(src)                             (((src) & 0x00000007))
#define R8_BUS_CTRL1_WR(src)                        (((u32)(src)) & 0x00000007)
#define R8_BUS_CTRL1_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register gfc_nand_pio_reg_ctrl2	*/
/*	 Fields ecc_buffer	 */
#define ECC_BUFFER2_WIDTH                                                     1
#define ECC_BUFFER2_SHIFT                                                     4
#define ECC_BUFFER2_MASK                                             0x00000010
#define ECC_BUFFER2_RD(src)                           (((src) & 0x00000010)>>4)
#define ECC_BUFFER2_WR(src)                      (((u32)(src)<<4) & 0x00000010)
#define ECC_BUFFER2_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields r16_valid	 */
#define R16_VALID2_WIDTH                                                      1
#define R16_VALID2_SHIFT                                                      3
#define R16_VALID2_MASK                                              0x00000008
#define R16_VALID2_RD(src)                            (((src) & 0x00000008)>>3)
#define R16_VALID2_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define R16_VALID2_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields r16_bus_ctrl	 */
#define R16_BUS_CTRL2_WIDTH                                                   3
#define R16_BUS_CTRL2_SHIFT                                                   0
#define R16_BUS_CTRL2_MASK                                           0x00000007
#define R16_BUS_CTRL2_RD(src)                            (((src) & 0x00000007))
#define R16_BUS_CTRL2_WR(src)                       (((u32)(src)) & 0x00000007)
#define R16_BUS_CTRL2_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register gfc_nand_pio_reg0	*/
/*	 Fields r1_bus_field	 */
#define R1_BUS_FIELD0_WIDTH                                                  16
#define R1_BUS_FIELD0_SHIFT                                                  16
#define R1_BUS_FIELD0_MASK                                           0xffff0000
#define R1_BUS_FIELD0_RD(src)                        (((src) & 0xffff0000)>>16)
#define R1_BUS_FIELD0_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define R1_BUS_FIELD0_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r0_bus_field	 */
#define R0_BUS_FIELD0_WIDTH                                                  16
#define R0_BUS_FIELD0_SHIFT                                                   0
#define R0_BUS_FIELD0_MASK                                           0x0000ffff
#define R0_BUS_FIELD0_RD(src)                            (((src) & 0x0000ffff))
#define R0_BUS_FIELD0_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define R0_BUS_FIELD0_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg1	*/
/*	 Fields r3_bus_field	 */
#define R3_BUS_FIELD1_WIDTH                                                  16
#define R3_BUS_FIELD1_SHIFT                                                  16
#define R3_BUS_FIELD1_MASK                                           0xffff0000
#define R3_BUS_FIELD1_RD(src)                        (((src) & 0xffff0000)>>16)
#define R3_BUS_FIELD1_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define R3_BUS_FIELD1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r2_bus_field	 */
#define R2_BUS_FIELD1_WIDTH                                                  16
#define R2_BUS_FIELD1_SHIFT                                                   0
#define R2_BUS_FIELD1_MASK                                           0x0000ffff
#define R2_BUS_FIELD1_RD(src)                            (((src) & 0x0000ffff))
#define R2_BUS_FIELD1_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define R2_BUS_FIELD1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg2	*/
/*	 Fields r5_bus_field	 */
#define R5_BUS_FIELD2_WIDTH                                                  16
#define R5_BUS_FIELD2_SHIFT                                                  16
#define R5_BUS_FIELD2_MASK                                           0xffff0000
#define R5_BUS_FIELD2_RD(src)                        (((src) & 0xffff0000)>>16)
#define R5_BUS_FIELD2_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define R5_BUS_FIELD2_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r4_bus_field	 */
#define R4_BUS_FIELD2_WIDTH                                                  16
#define R4_BUS_FIELD2_SHIFT                                                   0
#define R4_BUS_FIELD2_MASK                                           0x0000ffff
#define R4_BUS_FIELD2_RD(src)                            (((src) & 0x0000ffff))
#define R4_BUS_FIELD2_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define R4_BUS_FIELD2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg3	*/
/*	 Fields r7_bus_field	 */
#define R7_BUS_FIELD3_WIDTH                                                  16
#define R7_BUS_FIELD3_SHIFT                                                  16
#define R7_BUS_FIELD3_MASK                                           0xffff0000
#define R7_BUS_FIELD3_RD(src)                        (((src) & 0xffff0000)>>16)
#define R7_BUS_FIELD3_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define R7_BUS_FIELD3_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r6_bus_field	 */
#define R6_BUS_FIELD3_WIDTH                                                  16
#define R6_BUS_FIELD3_SHIFT                                                   0
#define R6_BUS_FIELD3_MASK                                           0x0000ffff
#define R6_BUS_FIELD3_RD(src)                            (((src) & 0x0000ffff))
#define R6_BUS_FIELD3_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define R6_BUS_FIELD3_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg4	*/
/*	 Fields r9_bus_field	 */
#define R9_BUS_FIELD4_WIDTH                                                  16
#define R9_BUS_FIELD4_SHIFT                                                  16
#define R9_BUS_FIELD4_MASK                                           0xffff0000
#define R9_BUS_FIELD4_RD(src)                        (((src) & 0xffff0000)>>16)
#define R9_BUS_FIELD4_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define R9_BUS_FIELD4_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r8_bus_field	 */
#define R8_BUS_FIELD4_WIDTH                                                  16
#define R8_BUS_FIELD4_SHIFT                                                   0
#define R8_BUS_FIELD4_MASK                                           0x0000ffff
#define R8_BUS_FIELD4_RD(src)                            (((src) & 0x0000ffff))
#define R8_BUS_FIELD4_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define R8_BUS_FIELD4_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg5	*/
/*	 Fields r11_bus_field	 */
#define R11_BUS_FIELD5_WIDTH                                                 16
#define R11_BUS_FIELD5_SHIFT                                                 16
#define R11_BUS_FIELD5_MASK                                          0xffff0000
#define R11_BUS_FIELD5_RD(src)                       (((src) & 0xffff0000)>>16)
#define R11_BUS_FIELD5_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define R11_BUS_FIELD5_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r10_bus_field	 */
#define R10_BUS_FIELD5_WIDTH                                                 16
#define R10_BUS_FIELD5_SHIFT                                                  0
#define R10_BUS_FIELD5_MASK                                          0x0000ffff
#define R10_BUS_FIELD5_RD(src)                           (((src) & 0x0000ffff))
#define R10_BUS_FIELD5_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define R10_BUS_FIELD5_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg6	*/
/*	 Fields r13_bus_field	 */
#define R13_BUS_FIELD6_WIDTH                                                 16
#define R13_BUS_FIELD6_SHIFT                                                 16
#define R13_BUS_FIELD6_MASK                                          0xffff0000
#define R13_BUS_FIELD6_RD(src)                       (((src) & 0xffff0000)>>16)
#define R13_BUS_FIELD6_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define R13_BUS_FIELD6_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r12_bus_field	 */
#define R12_BUS_FIELD6_WIDTH                                                 16
#define R12_BUS_FIELD6_SHIFT                                                  0
#define R12_BUS_FIELD6_MASK                                          0x0000ffff
#define R12_BUS_FIELD6_RD(src)                           (((src) & 0x0000ffff))
#define R12_BUS_FIELD6_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define R12_BUS_FIELD6_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg7	*/
/*	 Fields r15_bus_field	 */
#define R15_BUS_FIELD7_WIDTH                                                 16
#define R15_BUS_FIELD7_SHIFT                                                 16
#define R15_BUS_FIELD7_MASK                                          0xffff0000
#define R15_BUS_FIELD7_RD(src)                       (((src) & 0xffff0000)>>16)
#define R15_BUS_FIELD7_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define R15_BUS_FIELD7_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields r14_bus_field	 */
#define R14_BUS_FIELD7_WIDTH                                                 16
#define R14_BUS_FIELD7_SHIFT                                                  0
#define R14_BUS_FIELD7_MASK                                          0x0000ffff
#define R14_BUS_FIELD7_RD(src)                           (((src) & 0x0000ffff))
#define R14_BUS_FIELD7_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define R14_BUS_FIELD7_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_reg8	*/
/*	 Fields r16_bus_field	 */
#define R16_BUS_FIELD8_WIDTH                                                 16
#define R16_BUS_FIELD8_SHIFT                                                  0
#define R16_BUS_FIELD8_MASK                                          0x0000ffff
#define R16_BUS_FIELD8_RD(src)                           (((src) & 0x0000ffff))
#define R16_BUS_FIELD8_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define R16_BUS_FIELD8_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_buf_start	*/
/*	 Fields address	 */
#define ADDRESS_GFC_WIDTH                                                        32
#define ADDRESS_GFC_SHIFT                                                         0
#define ADDRESS_GFC_MASK                                                 0xffffffff
#define ADDRESS_GFC_RD(src)                                  (((src) & 0xffffffff))
#define ADDRESS_GFC_WR(src)                             (((u32)(src)) & 0xffffffff)
#define ADDRESS_GFC_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_nand_pio_buf_end	*/
/*	 Fields address	 */
#define ADDRESS_GFC_F1_WIDTH                                                     32
#define ADDRESS_GFC_F1_SHIFT                                                      0
#define ADDRESS_GFC_F1_MASK                                              0xffffffff
#define ADDRESS_GFC_F1_RD(src)                               (((src) & 0xffffffff))
#define ADDRESS_GFC_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define ADDRESS_GFC_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_nand_pio_forced_cmd_ctrl	*/
/*	 Fields read	 */
#define REGSPEC_READ_F1_WIDTH                                                 1
#define REGSPEC_READ_F1_SHIFT                                                26
#define REGSPEC_READ_F1_MASK                                         0x04000000
#define REGSPEC_READ_F1_RD(src)                      (((src) & 0x04000000)>>26)
#define REGSPEC_READ_F1_WR(src)                 (((u32)(src)<<26) & 0x04000000)
#define REGSPEC_READ_F1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields cs_n	 */
#define CS_N_WIDTH                                                            6
#define CS_N_SHIFT                                                           20
#define CS_N_MASK                                                    0x03f00000
#define CS_N_RD(src)                                 (((src) & 0x03f00000)>>20)
#define CS_N_WR(src)                            (((u32)(src)<<20) & 0x03f00000)
#define CS_N_SET(dst,src) \
                      (((dst) & ~0x03f00000) | (((u32)(src)<<20) & 0x03f00000))
/*	 Fields start	 */
#define START_GFC_F1_WIDTH                                                        1
#define START_GFC_F1_SHIFT                                                       19
#define START_GFC_F1_MASK                                                0x00080000
#define START_GFC_F1_RD(src)                             (((src) & 0x00080000)>>19)
#define START_GFC_F1_WR(src)                        (((u32)(src)<<19) & 0x00080000)
#define START_GFC_F1_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields bus_ctrl	 */
#define BUS_CTRL_WIDTH                                                        3
#define BUS_CTRL_SHIFT                                                       16
#define BUS_CTRL_MASK                                                0x00070000
#define BUS_CTRL_RD(src)                             (((src) & 0x00070000)>>16)
#define BUS_CTRL_WR(src)                        (((u32)(src)<<16) & 0x00070000)
#define BUS_CTRL_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields cmd	 */
#define CMD_WIDTH                                                            16
#define CMD_SHIFT                                                             0
#define CMD_MASK                                                     0x0000ffff
#define CMD_RD(src)                                      (((src) & 0x0000ffff))
#define CMD_WR(src)                                 (((u32)(src)) & 0x0000ffff)
#define CMD_SET(dst,src) (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_read_status_sts	*/
/*	 Fields data	 */
#define DATA_WIDTH_GFC                                                           16
#define DATA_SHIFT_GFC                                                            0
#define DATA_MASK_GFC                                                    0x0000ffff
#define DATA_RD_GFC(src)                                     (((src) & 0x0000ffff))
#define DATA_SET_GFC(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_nand_pio_status	*/
/*	 Fields wfifo_empty	 */
#define WFIFO_EMPTY_WIDTH                                                     1
#define WFIFO_EMPTY_SHIFT                                                    26
#define WFIFO_EMPTY_MASK                                             0x04000000
#define WFIFO_EMPTY_RD(src)                          (((src) & 0x04000000)>>26)
#define WFIFO_EMPTY_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields wfifo_full	 */
#define WFIFO_FULL_WIDTH                                                      1
#define WFIFO_FULL_SHIFT                                                     25
#define WFIFO_FULL_MASK                                              0x02000000
#define WFIFO_FULL_RD(src)                           (((src) & 0x02000000)>>25)
#define WFIFO_FULL_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields wfifo_data_avail	 */
#define WFIFO_DATA_AVAIL_WIDTH                                                1
#define WFIFO_DATA_AVAIL_SHIFT                                               24
#define WFIFO_DATA_AVAIL_MASK                                        0x01000000
#define WFIFO_DATA_AVAIL_RD(src)                     (((src) & 0x01000000)>>24)
#define WFIFO_DATA_AVAIL_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields wfifo_level	 */
#define WFIFO_LEVEL_WIDTH                                                     6
#define WFIFO_LEVEL_SHIFT                                                    16
#define WFIFO_LEVEL_MASK                                             0x003f0000
#define WFIFO_LEVEL_RD(src)                          (((src) & 0x003f0000)>>16)
#define WFIFO_LEVEL_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields rfifo_empty_raw	 */
#define RFIFO_EMPTY_RAW_WIDTH                                                 1
#define RFIFO_EMPTY_RAW_SHIFT                                                11
#define RFIFO_EMPTY_RAW_MASK                                         0x00000800
#define RFIFO_EMPTY_RAW_RD(src)                      (((src) & 0x00000800)>>11)
#define RFIFO_EMPTY_RAW_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields rfifo_empty	 */
#define RFIFO_EMPTY_WIDTH                                                     1
#define RFIFO_EMPTY_SHIFT                                                    10
#define RFIFO_EMPTY_MASK                                             0x00000400
#define RFIFO_EMPTY_RD(src)                          (((src) & 0x00000400)>>10)
#define RFIFO_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rfifo_full	 */
#define RFIFO_FULL_WIDTH                                                      1
#define RFIFO_FULL_SHIFT                                                      9
#define RFIFO_FULL_MASK                                              0x00000200
#define RFIFO_FULL_RD(src)                            (((src) & 0x00000200)>>9)
#define RFIFO_FULL_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields rfifo_data_avail	 */
#define RFIFO_DATA_AVAIL_WIDTH                                                1
#define RFIFO_DATA_AVAIL_SHIFT                                                8
#define RFIFO_DATA_AVAIL_MASK                                        0x00000100
#define RFIFO_DATA_AVAIL_RD(src)                      (((src) & 0x00000100)>>8)
#define RFIFO_DATA_AVAIL_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields rfifo_level	 */
#define RFIFO_LEVEL_WIDTH                                                     6
#define RFIFO_LEVEL_SHIFT                                                     0
#define RFIFO_LEVEL_MASK                                             0x0000003f
#define RFIFO_LEVEL_RD(src)                              (((src) & 0x0000003f))
#define RFIFO_LEVEL_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register gfc_spare	*/
/*	 Fields spare_config_bits	 */
#define SPARE_CONFIG_BITS_WIDTH                                              32
#define SPARE_CONFIG_BITS_SHIFT                                               0
#define SPARE_CONFIG_BITS_MASK                                       0xffffffff
#define SPARE_CONFIG_BITS_RD(src)                        (((src) & 0xffffffff))
#define SPARE_CONFIG_BITS_WR(src)                   (((u32)(src)) & 0xffffffff)
#define SPARE_CONFIG_BITS_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_nand_err_ctrl	*/
/*	 Fields dma_abort	 */
#define DMA_ABORT_WIDTH                                                       1
#define DMA_ABORT_SHIFT                                                       3
#define DMA_ABORT_MASK                                               0x00000008
#define DMA_ABORT_RD(src)                             (((src) & 0x00000008)>>3)
#define DMA_ABORT_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define DMA_ABORT_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields dma_timeout_en	 */
#define DMA_TIMEOUT_EN_WIDTH                                                  1
#define DMA_TIMEOUT_EN_SHIFT                                                  2
#define DMA_TIMEOUT_EN_MASK                                          0x00000004
#define DMA_TIMEOUT_EN_RD(src)                        (((src) & 0x00000004)>>2)
#define DMA_TIMEOUT_EN_WR(src)                   (((u32)(src)<<2) & 0x00000004)
#define DMA_TIMEOUT_EN_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields abort	 */
#define ABORT_WIDTH                                                           1
#define ABORT_SHIFT                                                           1
#define ABORT_MASK                                                   0x00000002
#define ABORT_RD(src)                                 (((src) & 0x00000002)>>1)
#define ABORT_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define ABORT_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields timeout_en	 */
#define TIMEOUT_EN_WIDTH                                                      1
#define TIMEOUT_EN_SHIFT                                                      0
#define TIMEOUT_EN_MASK                                              0x00000001
#define TIMEOUT_EN_RD(src)                               (((src) & 0x00000001))
#define TIMEOUT_EN_WR(src)                          (((u32)(src)) & 0x00000001)
#define TIMEOUT_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_nand_timeout	*/
/*	 Fields counter	 */
#define COUNTER_WIDTH                                                        32
#define COUNTER_SHIFT                                                         0
#define COUNTER_MASK                                                 0xffffffff
#define COUNTER_RD(src)                                  (((src) & 0xffffffff))
#define COUNTER_WR(src)                             (((u32)(src)) & 0xffffffff)
#define COUNTER_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_nand_pio_buffer_ctrl	*/
/*	 Fields rd_ecc_result_fifo	 */
#define RD_ECC_RESULT_FIFO_WIDTH                                              1
#define RD_ECC_RESULT_FIFO_SHIFT                                              2
#define RD_ECC_RESULT_FIFO_MASK                                      0x00000004
#define RD_ECC_RESULT_FIFO_RD(src)                    (((src) & 0x00000004)>>2)
#define RD_ECC_RESULT_FIFO_WR(src)               (((u32)(src)<<2) & 0x00000004)
#define RD_ECC_RESULT_FIFO_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields nand_auto_flush_rd_buf	 */
#define NAND_AUTO_FLUSH_RD_BUF_WIDTH                                          1
#define NAND_AUTO_FLUSH_RD_BUF_SHIFT                                          1
#define NAND_AUTO_FLUSH_RD_BUF_MASK                                  0x00000002
#define NAND_AUTO_FLUSH_RD_BUF_RD(src)                (((src) & 0x00000002)>>1)
#define NAND_AUTO_FLUSH_RD_BUF_WR(src)           (((u32)(src)<<1) & 0x00000002)
#define NAND_AUTO_FLUSH_RD_BUF_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields flush_rd_buffer	 */
#define FLUSH_RD_BUFFER_WIDTH                                                 1
#define FLUSH_RD_BUFFER_SHIFT                                                 0
#define FLUSH_RD_BUFFER_MASK                                         0x00000001
#define FLUSH_RD_BUFFER_RD(src)                          (((src) & 0x00000001))
#define FLUSH_RD_BUFFER_WR(src)                     (((u32)(src)) & 0x00000001)
#define FLUSH_RD_BUFFER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_nand_pio_buffer_threshold	*/
/*	 Fields rbuf_full	 */
#define RBUF_FULL_WIDTH                                                       6
#define RBUF_FULL_SHIFT                                                      24
#define RBUF_FULL_MASK                                               0x3f000000
#define RBUF_FULL_RD(src)                            (((src) & 0x3f000000)>>24)
#define RBUF_FULL_WR(src)                       (((u32)(src)<<24) & 0x3f000000)
#define RBUF_FULL_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*	 Fields wbuf_full	 */
#define WBUF_FULL_WIDTH                                                       6
#define WBUF_FULL_SHIFT                                                      16
#define WBUF_FULL_MASK                                               0x003f0000
#define WBUF_FULL_RD(src)                            (((src) & 0x003f0000)>>16)
#define WBUF_FULL_WR(src)                       (((u32)(src)<<16) & 0x003f0000)
#define WBUF_FULL_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields rbuf_afifo_full	 */
#define RBUF_AFIFO_FULL_WIDTH                                                 5
#define RBUF_AFIFO_FULL_SHIFT                                                 8
#define RBUF_AFIFO_FULL_MASK                                         0x00001f00
#define RBUF_AFIFO_FULL_RD(src)                       (((src) & 0x00001f00)>>8)
#define RBUF_AFIFO_FULL_WR(src)                  (((u32)(src)<<8) & 0x00001f00)
#define RBUF_AFIFO_FULL_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields wbuf_afifo_full	 */
#define WBUF_AFIFO_FULL_WIDTH                                                 4
#define WBUF_AFIFO_FULL_SHIFT                                                 0
#define WBUF_AFIFO_FULL_MASK                                         0x0000000f
#define WBUF_AFIFO_FULL_RD(src)                          (((src) & 0x0000000f))
#define WBUF_AFIFO_FULL_WR(src)                     (((u32)(src)) & 0x0000000f)
#define WBUF_AFIFO_FULL_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_nand_pio_buffer_threshold1	*/
/*	 Fields rbuf_axi_full	 */
#define RBUF_AXI_FULL1_WIDTH                                                  3
#define RBUF_AXI_FULL1_SHIFT                                                 16
#define RBUF_AXI_FULL1_MASK                                          0x00070000
#define RBUF_AXI_FULL1_RD(src)                       (((src) & 0x00070000)>>16)
#define RBUF_AXI_FULL1_WR(src)                  (((u32)(src)<<16) & 0x00070000)
#define RBUF_AXI_FULL1_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields rbuf_empty	 */
#define RBUF_EMPTY1_WIDTH                                                     6
#define RBUF_EMPTY1_SHIFT                                                     8
#define RBUF_EMPTY1_MASK                                             0x00003f00
#define RBUF_EMPTY1_RD(src)                           (((src) & 0x00003f00)>>8)
#define RBUF_EMPTY1_WR(src)                      (((u32)(src)<<8) & 0x00003f00)
#define RBUF_EMPTY1_SET(dst,src) \
                       (((dst) & ~0x00003f00) | (((u32)(src)<<8) & 0x00003f00))
/*	 Fields wbuf_empty	 */
#define WBUF_EMPTY1_WIDTH                                                     6
#define WBUF_EMPTY1_SHIFT                                                     0
#define WBUF_EMPTY1_MASK                                             0x0000003f
#define WBUF_EMPTY1_RD(src)                              (((src) & 0x0000003f))
#define WBUF_EMPTY1_WR(src)                         (((u32)(src)) & 0x0000003f)
#define WBUF_EMPTY1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register gfc_gen_ctrl	*/
/*	 Fields ctc	 */
#define CTC_WIDTH                                                             1
#define CTC_SHIFT                                                            31
#define CTC_MASK                                                     0x80000000
#define CTC_RD(src)                                  (((src) & 0x80000000)>>31)
#define CTC_WR(src)                             (((u32)(src)<<31) & 0x80000000)
#define CTC_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields dtc	 */
#define DTC_WIDTH                                                             1
#define DTC_SHIFT                                                            30
#define DTC_MASK                                                     0x40000000
#define DTC_RD(src)                                  (((src) & 0x40000000)>>30)
#define DTC_WR(src)                             (((u32)(src)<<30) & 0x40000000)
#define DTC_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields atc	 */
#define ATC_WIDTH                                                             1
#define ATC_SHIFT                                                            29
#define ATC_MASK                                                     0x20000000
#define ATC_RD(src)                                  (((src) & 0x20000000)>>29)
#define ATC_WR(src)                             (((u32)(src)<<29) & 0x20000000)
#define ATC_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields dma_word_swap_4byte	 */
#define DMA_WORD_SWAP_4BYTE_WIDTH                                             1
#define DMA_WORD_SWAP_4BYTE_SHIFT                                            28
#define DMA_WORD_SWAP_4BYTE_MASK                                     0x10000000
#define DMA_WORD_SWAP_4BYTE_RD(src)                  (((src) & 0x10000000)>>28)
#define DMA_WORD_SWAP_4BYTE_WR(src)             (((u32)(src)<<28) & 0x10000000)
#define DMA_WORD_SWAP_4BYTE_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields dma_swap_16byte	 */
#define DMA_SWAP_16BYTE_WIDTH                                                 1
#define DMA_SWAP_16BYTE_SHIFT                                                27
#define DMA_SWAP_16BYTE_MASK                                         0x08000000
#define DMA_SWAP_16BYTE_RD(src)                      (((src) & 0x08000000)>>27)
#define DMA_SWAP_16BYTE_WR(src)                 (((u32)(src)<<27) & 0x08000000)
#define DMA_SWAP_16BYTE_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields dma_swap_4byte	 */
#define DMA_SWAP_4BYTE_WIDTH                                                  1
#define DMA_SWAP_4BYTE_SHIFT                                                 26
#define DMA_SWAP_4BYTE_MASK                                          0x04000000
#define DMA_SWAP_4BYTE_RD(src)                       (((src) & 0x04000000)>>26)
#define DMA_SWAP_4BYTE_WR(src)                  (((u32)(src)<<26) & 0x04000000)
#define DMA_SWAP_4BYTE_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields dma_swap_2byte	 */
#define DMA_SWAP_2BYTE_WIDTH                                                  1
#define DMA_SWAP_2BYTE_SHIFT                                                 25
#define DMA_SWAP_2BYTE_MASK                                          0x02000000
#define DMA_SWAP_2BYTE_RD(src)                       (((src) & 0x02000000)>>25)
#define DMA_SWAP_2BYTE_WR(src)                  (((u32)(src)<<25) & 0x02000000)
#define DMA_SWAP_2BYTE_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields nand_word_swap_4byte	 */
#define NAND_WORD_SWAP_4BYTE_WIDTH                                            1
#define NAND_WORD_SWAP_4BYTE_SHIFT                                           24
#define NAND_WORD_SWAP_4BYTE_MASK                                    0x01000000
#define NAND_WORD_SWAP_4BYTE_RD(src)                 (((src) & 0x01000000)>>24)
#define NAND_WORD_SWAP_4BYTE_WR(src)            (((u32)(src)<<24) & 0x01000000)
#define NAND_WORD_SWAP_4BYTE_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields nand_ebus_swap_2byte	 */
#define NAND_EBUS_SWAP_2BYTE_WIDTH                                            1
#define NAND_EBUS_SWAP_2BYTE_SHIFT                                           23
#define NAND_EBUS_SWAP_2BYTE_MASK                                    0x00800000
#define NAND_EBUS_SWAP_2BYTE_RD(src)                 (((src) & 0x00800000)>>23)
#define NAND_EBUS_SWAP_2BYTE_WR(src)            (((u32)(src)<<23) & 0x00800000)
#define NAND_EBUS_SWAP_2BYTE_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields norsram_word_swap_4byte	 */
#define NORSRAM_WORD_SWAP_4BYTE_WIDTH                                         1
#define NORSRAM_WORD_SWAP_4BYTE_SHIFT                                        22
#define NORSRAM_WORD_SWAP_4BYTE_MASK                                 0x00400000
#define NORSRAM_WORD_SWAP_4BYTE_RD(src)              (((src) & 0x00400000)>>22)
#define NORSRAM_WORD_SWAP_4BYTE_WR(src)         (((u32)(src)<<22) & 0x00400000)
#define NORSRAM_WORD_SWAP_4BYTE_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields norsram_ebus_swap_2byte	 */
#define NORSRAM_EBUS_SWAP_2BYTE_WIDTH                                         1
#define NORSRAM_EBUS_SWAP_2BYTE_SHIFT                                        21
#define NORSRAM_EBUS_SWAP_2BYTE_MASK                                 0x00200000
#define NORSRAM_EBUS_SWAP_2BYTE_RD(src)              (((src) & 0x00200000)>>21)
#define NORSRAM_EBUS_SWAP_2BYTE_WR(src)         (((u32)(src)<<21) & 0x00200000)
#define NORSRAM_EBUS_SWAP_2BYTE_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields nand_rbuf_force_noslverr	 */
#define NAND_RBUF_FORCE_NOSLVERR_WIDTH                                        1
#define NAND_RBUF_FORCE_NOSLVERR_SHIFT                                       20
#define NAND_RBUF_FORCE_NOSLVERR_MASK                                0x00100000
#define NAND_RBUF_FORCE_NOSLVERR_RD(src)             (((src) & 0x00100000)>>20)
#define NAND_RBUF_FORCE_NOSLVERR_WR(src)        (((u32)(src)<<20) & 0x00100000)
#define NAND_RBUF_FORCE_NOSLVERR_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields nand_ecc_even_bound	 */
#define NAND_ECC_EVEN_BOUND_WIDTH                                             1
#define NAND_ECC_EVEN_BOUND_SHIFT                                            19
#define NAND_ECC_EVEN_BOUND_MASK                                     0x00080000
#define NAND_ECC_EVEN_BOUND_RD(src)                  (((src) & 0x00080000)>>19)
#define NAND_ECC_EVEN_BOUND_WR(src)             (((u32)(src)<<19) & 0x00080000)
#define NAND_ECC_EVEN_BOUND_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields nand_wp_n	 */
#define NAND_WP_N_WIDTH                                                       1
#define NAND_WP_N_SHIFT                                                      18
#define NAND_WP_N_MASK                                               0x00040000
#define NAND_WP_N_RD(src)                            (((src) & 0x00040000)>>18)
#define NAND_WP_N_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define NAND_WP_N_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields norsram_wp_n	 */
#define NORSRAM_WP_N_WIDTH                                                    1
#define NORSRAM_WP_N_SHIFT                                                   17
#define NORSRAM_WP_N_MASK                                            0x00020000
#define NORSRAM_WP_N_RD(src)                         (((src) & 0x00020000)>>17)
#define NORSRAM_WP_N_WR(src)                    (((u32)(src)<<17) & 0x00020000)
#define NORSRAM_WP_N_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields nand_bypass_ready	 */
#define NAND_BYPASS_READY_WIDTH                                               1
#define NAND_BYPASS_READY_SHIFT                                              16
#define NAND_BYPASS_READY_MASK                                       0x00010000
#define NAND_BYPASS_READY_RD(src)                    (((src) & 0x00010000)>>16)
#define NAND_BYPASS_READY_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define NAND_BYPASS_READY_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields nand_bypass_rdybsyn	 */
#define NAND_BYPASS_RDYBSYN_WIDTH                                             1
#define NAND_BYPASS_RDYBSYN_SHIFT                                            15
#define NAND_BYPASS_RDYBSYN_MASK                                     0x00008000
#define NAND_BYPASS_RDYBSYN_RD(src)                  (((src) & 0x00008000)>>15)
#define NAND_BYPASS_RDYBSYN_WR(src)             (((u32)(src)<<15) & 0x00008000)
#define NAND_BYPASS_RDYBSYN_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields nand_swap_16byte	 */
#define NAND_SWAP_16BYTE_WIDTH                                                1
#define NAND_SWAP_16BYTE_SHIFT                                               14
#define NAND_SWAP_16BYTE_MASK                                        0x00004000
#define NAND_SWAP_16BYTE_RD(src)                     (((src) & 0x00004000)>>14)
#define NAND_SWAP_16BYTE_WR(src)                (((u32)(src)<<14) & 0x00004000)
#define NAND_SWAP_16BYTE_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields nand_swap_4byte	 */
#define NAND_SWAP_4BYTE_WIDTH                                                 1
#define NAND_SWAP_4BYTE_SHIFT                                                13
#define NAND_SWAP_4BYTE_MASK                                         0x00002000
#define NAND_SWAP_4BYTE_RD(src)                      (((src) & 0x00002000)>>13)
#define NAND_SWAP_4BYTE_WR(src)                 (((u32)(src)<<13) & 0x00002000)
#define NAND_SWAP_4BYTE_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields nand_swap_2byte	 */
#define NAND_SWAP_2BYTE_WIDTH                                                 1
#define NAND_SWAP_2BYTE_SHIFT                                                12
#define NAND_SWAP_2BYTE_MASK                                         0x00001000
#define NAND_SWAP_2BYTE_RD(src)                      (((src) & 0x00001000)>>12)
#define NAND_SWAP_2BYTE_WR(src)                 (((u32)(src)<<12) & 0x00001000)
#define NAND_SWAP_2BYTE_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields nand_shift1_address	 */
#define NAND_SHIFT1_ADDRESS_WIDTH                                             1
#define NAND_SHIFT1_ADDRESS_SHIFT                                            11
#define NAND_SHIFT1_ADDRESS_MASK                                     0x00000800
#define NAND_SHIFT1_ADDRESS_RD(src)                  (((src) & 0x00000800)>>11)
#define NAND_SHIFT1_ADDRESS_WR(src)             (((u32)(src)<<11) & 0x00000800)
#define NAND_SHIFT1_ADDRESS_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields nand_reverse_address	 */
#define NAND_REVERSE_ADDRESS_WIDTH                                            1
#define NAND_REVERSE_ADDRESS_SHIFT                                           10
#define NAND_REVERSE_ADDRESS_MASK                                    0x00000400
#define NAND_REVERSE_ADDRESS_RD(src)                 (((src) & 0x00000400)>>10)
#define NAND_REVERSE_ADDRESS_WR(src)            (((u32)(src)<<10) & 0x00000400)
#define NAND_REVERSE_ADDRESS_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields nand_swap_rdy_rdbsyn	 */
#define NAND_SWAP_RDY_RDBSYN_WIDTH                                            1
#define NAND_SWAP_RDY_RDBSYN_SHIFT                                            9
#define NAND_SWAP_RDY_RDBSYN_MASK                                    0x00000200
#define NAND_SWAP_RDY_RDBSYN_RD(src)                  (((src) & 0x00000200)>>9)
#define NAND_SWAP_RDY_RDBSYN_WR(src)             (((u32)(src)<<9) & 0x00000200)
#define NAND_SWAP_RDY_RDBSYN_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields norsram_bypass_ready	 */
#define NORSRAM_BYPASS_READY_WIDTH                                            1
#define NORSRAM_BYPASS_READY_SHIFT                                            8
#define NORSRAM_BYPASS_READY_MASK                                    0x00000100
#define NORSRAM_BYPASS_READY_RD(src)                  (((src) & 0x00000100)>>8)
#define NORSRAM_BYPASS_READY_WR(src)             (((u32)(src)<<8) & 0x00000100)
#define NORSRAM_BYPASS_READY_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields norsram_bypass_rdybsyn	 */
#define NORSRAM_BYPASS_RDYBSYN_WIDTH                                          1
#define NORSRAM_BYPASS_RDYBSYN_SHIFT                                          7
#define NORSRAM_BYPASS_RDYBSYN_MASK                                  0x00000080
#define NORSRAM_BYPASS_RDYBSYN_RD(src)                (((src) & 0x00000080)>>7)
#define NORSRAM_BYPASS_RDYBSYN_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define NORSRAM_BYPASS_RDYBSYN_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields norsram_swap_16byte	 */
#define NORSRAM_SWAP_16BYTE_WIDTH                                             1
#define NORSRAM_SWAP_16BYTE_SHIFT                                             6
#define NORSRAM_SWAP_16BYTE_MASK                                     0x00000040
#define NORSRAM_SWAP_16BYTE_RD(src)                   (((src) & 0x00000040)>>6)
#define NORSRAM_SWAP_16BYTE_WR(src)              (((u32)(src)<<6) & 0x00000040)
#define NORSRAM_SWAP_16BYTE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields norsram_swap_4byte	 */
#define NORSRAM_SWAP_4BYTE_WIDTH                                              1
#define NORSRAM_SWAP_4BYTE_SHIFT                                              5
#define NORSRAM_SWAP_4BYTE_MASK                                      0x00000020
#define NORSRAM_SWAP_4BYTE_RD(src)                    (((src) & 0x00000020)>>5)
#define NORSRAM_SWAP_4BYTE_WR(src)               (((u32)(src)<<5) & 0x00000020)
#define NORSRAM_SWAP_4BYTE_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields norsram_swap_2byte	 */
#define NORSRAM_SWAP_2BYTE_WIDTH                                              1
#define NORSRAM_SWAP_2BYTE_SHIFT                                              4
#define NORSRAM_SWAP_2BYTE_MASK                                      0x00000010
#define NORSRAM_SWAP_2BYTE_RD(src)                    (((src) & 0x00000010)>>4)
#define NORSRAM_SWAP_2BYTE_WR(src)               (((u32)(src)<<4) & 0x00000010)
#define NORSRAM_SWAP_2BYTE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields norsram_shift1_address	 */
#define NORSRAM_SHIFT1_ADDRESS_WIDTH                                          1
#define NORSRAM_SHIFT1_ADDRESS_SHIFT                                          3
#define NORSRAM_SHIFT1_ADDRESS_MASK                                  0x00000008
#define NORSRAM_SHIFT1_ADDRESS_RD(src)                (((src) & 0x00000008)>>3)
#define NORSRAM_SHIFT1_ADDRESS_WR(src)           (((u32)(src)<<3) & 0x00000008)
#define NORSRAM_SHIFT1_ADDRESS_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields norsram_reverse_address	 */
#define NORSRAM_REVERSE_ADDRESS_WIDTH                                         1
#define NORSRAM_REVERSE_ADDRESS_SHIFT                                         2
#define NORSRAM_REVERSE_ADDRESS_MASK                                 0x00000004
#define NORSRAM_REVERSE_ADDRESS_RD(src)               (((src) & 0x00000004)>>2)
#define NORSRAM_REVERSE_ADDRESS_WR(src)          (((u32)(src)<<2) & 0x00000004)
#define NORSRAM_REVERSE_ADDRESS_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields norsram_swap_rdy_rdbsyn	 */
#define NORSRAM_SWAP_RDY_RDBSYN_WIDTH                                         1
#define NORSRAM_SWAP_RDY_RDBSYN_SHIFT                                         1
#define NORSRAM_SWAP_RDY_RDBSYN_MASK                                 0x00000002
#define NORSRAM_SWAP_RDY_RDBSYN_RD(src)               (((src) & 0x00000002)>>1)
#define NORSRAM_SWAP_RDY_RDBSYN_WR(src)          (((u32)(src)<<1) & 0x00000002)
#define NORSRAM_SWAP_RDY_RDBSYN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields bypass_pin_strap	 */
#define BYPASS_PIN_STRAP_WIDTH                                                1
#define BYPASS_PIN_STRAP_SHIFT                                                0
#define BYPASS_PIN_STRAP_MASK                                        0x00000001
#define BYPASS_PIN_STRAP_RD(src)                         (((src) & 0x00000001))
#define BYPASS_PIN_STRAP_WR(src)                    (((u32)(src)) & 0x00000001)
#define BYPASS_PIN_STRAP_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_gen_sts0	*/
/*	 Fields ebus_data_in	 */
#define EBUS_DATA_IN0_WIDTH                                                  32
#define EBUS_DATA_IN0_SHIFT                                                   0
#define EBUS_DATA_IN0_MASK                                           0xffffffff
#define EBUS_DATA_IN0_RD(src)                            (((src) & 0xffffffff))
#define EBUS_DATA_IN0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_gen_sts1	*/
/*	 Fields ebus_data_out	 */
#define EBUS_DATA_OUT1_WIDTH                                                 32
#define EBUS_DATA_OUT1_SHIFT                                                  0
#define EBUS_DATA_OUT1_MASK                                          0xffffffff
#define EBUS_DATA_OUT1_RD(src)                           (((src) & 0xffffffff))
#define EBUS_DATA_OUT1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_gen_sts2	*/
/*	 Fields ebus_addr_in	 */
#define EBUS_ADDR_IN2_WIDTH                                                  28
#define EBUS_ADDR_IN2_SHIFT                                                   0
#define EBUS_ADDR_IN2_MASK                                           0x0fffffff
#define EBUS_ADDR_IN2_RD(src)                            (((src) & 0x0fffffff))
#define EBUS_ADDR_IN2_SET(dst,src) \
                          (((dst) & ~0x0fffffff) | (((u32)(src)) & 0x0fffffff))

/*	Register gfc_gen_sts3	*/
/*	 Fields ebus_addr_out	 */
#define EBUS_ADDR_OUT3_WIDTH                                                 28
#define EBUS_ADDR_OUT3_SHIFT                                                  0
#define EBUS_ADDR_OUT3_MASK                                          0x0fffffff
#define EBUS_ADDR_OUT3_RD(src)                           (((src) & 0x0fffffff))
#define EBUS_ADDR_OUT3_SET(dst,src) \
                          (((dst) & ~0x0fffffff) | (((u32)(src)) & 0x0fffffff))

/*	Register gfc_gen_sts4	*/
/*	 Fields ebus_cs_n	 */
#define EBUS_CS_N4_WIDTH                                                      6
#define EBUS_CS_N4_SHIFT                                                     24
#define EBUS_CS_N4_MASK                                              0x3f000000
#define EBUS_CS_N4_RD(src)                           (((src) & 0x3f000000)>>24)
#define EBUS_CS_N4_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*	 Fields ebus_wbe_n	 */
#define EBUS_WBE_N4_WIDTH                                                     4
#define EBUS_WBE_N4_SHIFT                                                    20
#define EBUS_WBE_N4_MASK                                             0x00f00000
#define EBUS_WBE_N4_RD(src)                          (((src) & 0x00f00000)>>20)
#define EBUS_WBE_N4_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields ebus_parout	 */
#define EBUS_PAROUT4_WIDTH                                                    4
#define EBUS_PAROUT4_SHIFT                                                   16
#define EBUS_PAROUT4_MASK                                            0x000f0000
#define EBUS_PAROUT4_RD(src)                         (((src) & 0x000f0000)>>16)
#define EBUS_PAROUT4_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields ebus_parin	 */
#define EBUS_PARIN4_WIDTH                                                     4
#define EBUS_PARIN4_SHIFT                                                    12
#define EBUS_PARIN4_MASK                                             0x0000f000
#define EBUS_PARIN4_RD(src)                          (((src) & 0x0000f000)>>12)
#define EBUS_PARIN4_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields ebus_local_15_8_oe_n	 */
#define EBUS_LOCAL_15_8_OE_N4_WIDTH                                           1
#define EBUS_LOCAL_15_8_OE_N4_SHIFT                                          11
#define EBUS_LOCAL_15_8_OE_N4_MASK                                   0x00000800
#define EBUS_LOCAL_15_8_OE_N4_RD(src)                (((src) & 0x00000800)>>11)
#define EBUS_LOCAL_15_8_OE_N4_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields ebus_local_7_0_oe_n	 */
#define EBUS_LOCAL_7_0_OE_N4_WIDTH                                            1
#define EBUS_LOCAL_7_0_OE_N4_SHIFT                                           10
#define EBUS_LOCAL_7_0_OE_N4_MASK                                    0x00000400
#define EBUS_LOCAL_7_0_OE_N4_RD(src)                 (((src) & 0x00000400)>>10)
#define EBUS_LOCAL_7_0_OE_N4_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields ebus_local_addr_15_0_oe_n	 */
#define EBUS_LOCAL_ADDR_15_0_OE_N4_WIDTH                                      1
#define EBUS_LOCAL_ADDR_15_0_OE_N4_SHIFT                                      9
#define EBUS_LOCAL_ADDR_15_0_OE_N4_MASK                              0x00000200
#define EBUS_LOCAL_ADDR_15_0_OE_N4_RD(src)            (((src) & 0x00000200)>>9)
#define EBUS_LOCAL_ADDR_15_0_OE_N4_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ebus_local_addr_27_16_oe_n	 */
#define EBUS_LOCAL_ADDR_27_16_OE_N4_WIDTH                                     1
#define EBUS_LOCAL_ADDR_27_16_OE_N4_SHIFT                                     8
#define EBUS_LOCAL_ADDR_27_16_OE_N4_MASK                             0x00000100
#define EBUS_LOCAL_ADDR_27_16_OE_N4_RD(src)           (((src) & 0x00000100)>>8)
#define EBUS_LOCAL_ADDR_27_16_OE_N4_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ebus_cle	 */
#define EBUS_CLE4_WIDTH                                                       1
#define EBUS_CLE4_SHIFT                                                       7
#define EBUS_CLE4_MASK                                               0x00000080
#define EBUS_CLE4_RD(src)                             (((src) & 0x00000080)>>7)
#define EBUS_CLE4_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields ebus_wp_n	 */
#define EBUS_WP_N4_WIDTH                                                      1
#define EBUS_WP_N4_SHIFT                                                      6
#define EBUS_WP_N4_MASK                                              0x00000040
#define EBUS_WP_N4_RD(src)                            (((src) & 0x00000040)>>6)
#define EBUS_WP_N4_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ebus_ale	 */
#define EBUS_ALE4_WIDTH                                                       1
#define EBUS_ALE4_SHIFT                                                       5
#define EBUS_ALE4_MASK                                               0x00000020
#define EBUS_ALE4_RD(src)                             (((src) & 0x00000020)>>5)
#define EBUS_ALE4_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ebus_blast	 */
#define EBUS_BLAST4_WIDTH                                                     1
#define EBUS_BLAST4_SHIFT                                                     4
#define EBUS_BLAST4_MASK                                             0x00000010
#define EBUS_BLAST4_RD(src)                           (((src) & 0x00000010)>>4)
#define EBUS_BLAST4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ebus_oe_n	 */
#define EBUS_OE_N4_WIDTH                                                      1
#define EBUS_OE_N4_SHIFT                                                      3
#define EBUS_OE_N4_MASK                                              0x00000008
#define EBUS_OE_N4_RD(src)                            (((src) & 0x00000008)>>3)
#define EBUS_OE_N4_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ebus_rw	 */
#define EBUS_RW4_WIDTH                                                        1
#define EBUS_RW4_SHIFT                                                        2
#define EBUS_RW4_MASK                                                0x00000004
#define EBUS_RW4_RD(src)                              (((src) & 0x00000004)>>2)
#define EBUS_RW4_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ebus_ready	 */
#define EBUS_READY4_WIDTH                                                     1
#define EBUS_READY4_SHIFT                                                     1
#define EBUS_READY4_MASK                                             0x00000002
#define EBUS_READY4_RD(src)                           (((src) & 0x00000002)>>1)
#define EBUS_READY4_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ebus_rdybsyn	 */
#define EBUS_RDYBSYN4_WIDTH                                                   1
#define EBUS_RDYBSYN4_SHIFT                                                   0
#define EBUS_RDYBSYN4_MASK                                           0x00000001
#define EBUS_RDYBSYN4_RD(src)                            (((src) & 0x00000001))
#define EBUS_RDYBSYN4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_nand_pio_ecc_err_row	*/
/*	 Fields address	 */
#define ADDRESS_F2_WIDTH                                                     32
#define ADDRESS_F2_SHIFT                                                      0
#define ADDRESS_F2_MASK                                              0xffffffff
#define ADDRESS_F2_RD(src)                               (((src) & 0xffffffff))
#define ADDRESS_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_nand_pio_ecc_err_col	*/
/*	 Fields err_in_ecc	 */
#define ERR_IN_ECC_WIDTH                                                      1
#define ERR_IN_ECC_SHIFT                                                     20
#define ERR_IN_ECC_MASK                                              0x00100000
#define ERR_IN_ECC_RD(src)                           (((src) & 0x00100000)>>20)
#define ERR_IN_ECC_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields valid	 */
#define VALID_WIDTH                                                           1
#define VALID_SHIFT                                                          19
#define VALID_MASK                                                   0x00080000
#define VALID_RD(src)                                (((src) & 0x00080000)>>19)
#define VALID_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields bank	 */
#define BANK_WIDTH                                                            3
#define BANK_SHIFT                                                           16
#define BANK_MASK                                                    0x00070000
#define BANK_RD(src)                                 (((src) & 0x00070000)>>16)
#define BANK_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields address	 */
#define ADDRESS_F3_WIDTH                                                     16
#define ADDRESS_F3_SHIFT                                                      0
#define ADDRESS_F3_MASK                                              0x0000ffff
#define ADDRESS_F3_RD(src)                               (((src) & 0x0000ffff))
#define ADDRESS_F3_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_ecc_ram_ctrl	*/
/*	 Fields dma_rma	 */
#define DMA_RMA_WIDTH                                                         4
#define DMA_RMA_SHIFT                                                        20
#define DMA_RMA_MASK                                                 0x00f00000
#define DMA_RMA_RD(src)                              (((src) & 0x00f00000)>>20)
#define DMA_RMA_WR(src)                         (((u32)(src)<<20) & 0x00f00000)
#define DMA_RMA_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields dma_rmb	 */
#define DMA_RMB_WIDTH                                                         4
#define DMA_RMB_SHIFT                                                        16
#define DMA_RMB_MASK                                                 0x000f0000
#define DMA_RMB_RD(src)                              (((src) & 0x000f0000)>>16)
#define DMA_RMB_WR(src)                         (((u32)(src)<<16) & 0x000f0000)
#define DMA_RMB_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields dma_rmea	 */
#define DMA_RMEA_WIDTH                                                        1
#define DMA_RMEA_SHIFT                                                       15
#define DMA_RMEA_MASK                                                0x00008000
#define DMA_RMEA_RD(src)                             (((src) & 0x00008000)>>15)
#define DMA_RMEA_WR(src)                        (((u32)(src)<<15) & 0x00008000)
#define DMA_RMEA_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields dma_rmeb	 */
#define DMA_RMEB_WIDTH                                                        1
#define DMA_RMEB_SHIFT                                                       14
#define DMA_RMEB_MASK                                                0x00004000
#define DMA_RMEB_RD(src)                             (((src) & 0x00004000)>>14)
#define DMA_RMEB_WR(src)                        (((u32)(src)<<14) & 0x00004000)
#define DMA_RMEB_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields dma_test1a	 */
#define DMA_TEST1A_WIDTH                                                      1
#define DMA_TEST1A_SHIFT                                                     13
#define DMA_TEST1A_MASK                                              0x00002000
#define DMA_TEST1A_RD(src)                           (((src) & 0x00002000)>>13)
#define DMA_TEST1A_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define DMA_TEST1A_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields dma_test1b	 */
#define DMA_TEST1B_WIDTH                                                      1
#define DMA_TEST1B_SHIFT                                                     12
#define DMA_TEST1B_MASK                                              0x00001000
#define DMA_TEST1B_RD(src)                           (((src) & 0x00001000)>>12)
#define DMA_TEST1B_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define DMA_TEST1B_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields pio_rma	 */
#define PIO_RMA_WIDTH                                                         4
#define PIO_RMA_SHIFT                                                         8
#define PIO_RMA_MASK                                                 0x00000f00
#define PIO_RMA_RD(src)                               (((src) & 0x00000f00)>>8)
#define PIO_RMA_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define PIO_RMA_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields pio_rmb	 */
#define PIO_RMB_WIDTH                                                         4
#define PIO_RMB_SHIFT                                                         4
#define PIO_RMB_MASK                                                 0x000000f0
#define PIO_RMB_RD(src)                               (((src) & 0x000000f0)>>4)
#define PIO_RMB_WR(src)                          (((u32)(src)<<4) & 0x000000f0)
#define PIO_RMB_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields pio_rmea	 */
#define PIO_RMEA_WIDTH                                                        1
#define PIO_RMEA_SHIFT                                                        3
#define PIO_RMEA_MASK                                                0x00000008
#define PIO_RMEA_RD(src)                              (((src) & 0x00000008)>>3)
#define PIO_RMEA_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define PIO_RMEA_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields pio_rmeb	 */
#define PIO_RMEB_WIDTH                                                        1
#define PIO_RMEB_SHIFT                                                        2
#define PIO_RMEB_MASK                                                0x00000004
#define PIO_RMEB_RD(src)                              (((src) & 0x00000004)>>2)
#define PIO_RMEB_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define PIO_RMEB_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields pio_test1a	 */
#define PIO_TEST1A_WIDTH                                                      1
#define PIO_TEST1A_SHIFT                                                      1
#define PIO_TEST1A_MASK                                              0x00000002
#define PIO_TEST1A_RD(src)                            (((src) & 0x00000002)>>1)
#define PIO_TEST1A_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define PIO_TEST1A_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields pio_test1b	 */
#define PIO_TEST1B_WIDTH                                                      1
#define PIO_TEST1B_SHIFT                                                      0
#define PIO_TEST1B_MASK                                              0x00000001
#define PIO_TEST1B_RD(src)                               (((src) & 0x00000001))
#define PIO_TEST1B_WR(src)                          (((u32)(src)) & 0x00000001)
#define PIO_TEST1B_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_fifo0	*/
/*	 Fields eccr_full_th	 */
#define ECCR_FULL_TH0_WIDTH                                                   4
#define ECCR_FULL_TH0_SHIFT                                                  28
#define ECCR_FULL_TH0_MASK                                           0xf0000000
#define ECCR_FULL_TH0_RD(src)                        (((src) & 0xf0000000)>>28)
#define ECCR_FULL_TH0_WR(src)                   (((u32)(src)<<28) & 0xf0000000)
#define ECCR_FULL_TH0_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields eccw_full_th	 */
#define ECCW_FULL_TH0_WIDTH                                                   4
#define ECCW_FULL_TH0_SHIFT                                                  24
#define ECCW_FULL_TH0_MASK                                           0x0f000000
#define ECCW_FULL_TH0_RD(src)                        (((src) & 0x0f000000)>>24)
#define ECCW_FULL_TH0_WR(src)                   (((u32)(src)<<24) & 0x0f000000)
#define ECCW_FULL_TH0_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields ecc_buf_empty_th	 */
#define ECC_BUF_EMPTY_TH0_WIDTH                                               8
#define ECC_BUF_EMPTY_TH0_SHIFT                                              16
#define ECC_BUF_EMPTY_TH0_MASK                                       0x00ff0000
#define ECC_BUF_EMPTY_TH0_RD(src)                    (((src) & 0x00ff0000)>>16)
#define ECC_BUF_EMPTY_TH0_WR(src)               (((u32)(src)<<16) & 0x00ff0000)
#define ECC_BUF_EMPTY_TH0_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields ecc_buf_full_th	 */
#define ECC_BUF_FULL_TH0_WIDTH                                                8
#define ECC_BUF_FULL_TH0_SHIFT                                                8
#define ECC_BUF_FULL_TH0_MASK                                        0x0000ff00
#define ECC_BUF_FULL_TH0_RD(src)                      (((src) & 0x0000ff00)>>8)
#define ECC_BUF_FULL_TH0_WR(src)                 (((u32)(src)<<8) & 0x0000ff00)
#define ECC_BUF_FULL_TH0_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields bch_dec_full_th	 */
#define BCH_DEC_FULL_TH0_WIDTH                                                3
#define BCH_DEC_FULL_TH0_SHIFT                                                4
#define BCH_DEC_FULL_TH0_MASK                                        0x00000070
#define BCH_DEC_FULL_TH0_RD(src)                      (((src) & 0x00000070)>>4)
#define BCH_DEC_FULL_TH0_WR(src)                 (((u32)(src)<<4) & 0x00000070)
#define BCH_DEC_FULL_TH0_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields bch_enc_full_th	 */
#define BCH_ENC_FULL_TH0_WIDTH                                                3
#define BCH_ENC_FULL_TH0_SHIFT                                                0
#define BCH_ENC_FULL_TH0_MASK                                        0x00000007
#define BCH_ENC_FULL_TH0_RD(src)                         (((src) & 0x00000007))
#define BCH_ENC_FULL_TH0_WR(src)                    (((u32)(src)) & 0x00000007)
#define BCH_ENC_FULL_TH0_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register gfc_fifo1	*/
/*	 Fields dma_axir_buf_empty_th	 */
#define DMA_AXIR_BUF_EMPTY_TH1_WIDTH                                          6
#define DMA_AXIR_BUF_EMPTY_TH1_SHIFT                                         24
#define DMA_AXIR_BUF_EMPTY_TH1_MASK                                  0x3f000000
#define DMA_AXIR_BUF_EMPTY_TH1_RD(src)               (((src) & 0x3f000000)>>24)
#define DMA_AXIR_BUF_EMPTY_TH1_WR(src)          (((u32)(src)<<24) & 0x3f000000)
#define DMA_AXIR_BUF_EMPTY_TH1_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*	 Fields dma_axir_buf_full_th	 */
#define DMA_AXIR_BUF_FULL_TH1_WIDTH                                           6
#define DMA_AXIR_BUF_FULL_TH1_SHIFT                                          16
#define DMA_AXIR_BUF_FULL_TH1_MASK                                   0x003f0000
#define DMA_AXIR_BUF_FULL_TH1_RD(src)                (((src) & 0x003f0000)>>16)
#define DMA_AXIR_BUF_FULL_TH1_WR(src)           (((u32)(src)<<16) & 0x003f0000)
#define DMA_AXIR_BUF_FULL_TH1_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields bc_full_th	 */
#define BC_FULL_TH1_WIDTH                                                     4
#define BC_FULL_TH1_SHIFT                                                    12
#define BC_FULL_TH1_MASK                                             0x0000f000
#define BC_FULL_TH1_RD(src)                          (((src) & 0x0000f000)>>12)
#define BC_FULL_TH1_WR(src)                     (((u32)(src)<<12) & 0x0000f000)
#define BC_FULL_TH1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields bc_force_full_th	 */
#define BC_FORCE_FULL_TH1_WIDTH                                               3
#define BC_FORCE_FULL_TH1_SHIFT                                               8
#define BC_FORCE_FULL_TH1_MASK                                       0x00000700
#define BC_FORCE_FULL_TH1_RD(src)                     (((src) & 0x00000700)>>8)
#define BC_FORCE_FULL_TH1_WR(src)                (((u32)(src)<<8) & 0x00000700)
#define BC_FORCE_FULL_TH1_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields rowcol_full_th	 */
#define ROWCOL_FULL_TH1_WIDTH                                                 3
#define ROWCOL_FULL_TH1_SHIFT                                                 4
#define ROWCOL_FULL_TH1_MASK                                         0x00000070
#define ROWCOL_FULL_TH1_RD(src)                       (((src) & 0x00000070)>>4)
#define ROWCOL_FULL_TH1_WR(src)                  (((u32)(src)<<4) & 0x00000070)
#define ROWCOL_FULL_TH1_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields nandaddr_full_th	 */
#define NANDADDR_FULL_TH1_WIDTH                                               3
#define NANDADDR_FULL_TH1_SHIFT                                               0
#define NANDADDR_FULL_TH1_MASK                                       0x00000007
#define NANDADDR_FULL_TH1_RD(src)                        (((src) & 0x00000007))
#define NANDADDR_FULL_TH1_WR(src)                   (((u32)(src)) & 0x00000007)
#define NANDADDR_FULL_TH1_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register gfc_fifo2	*/
/*	 Fields dma_axiw_buf_empty_th	 */
#define DMA_AXIW_BUF_EMPTY_TH2_WIDTH                                          6
#define DMA_AXIW_BUF_EMPTY_TH2_SHIFT                                         24
#define DMA_AXIW_BUF_EMPTY_TH2_MASK                                  0x3f000000
#define DMA_AXIW_BUF_EMPTY_TH2_RD(src)               (((src) & 0x3f000000)>>24)
#define DMA_AXIW_BUF_EMPTY_TH2_WR(src)          (((u32)(src)<<24) & 0x3f000000)
#define DMA_AXIW_BUF_EMPTY_TH2_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*	 Fields dma_axiw_buf_full_th	 */
#define DMA_AXIW_BUF_FULL_TH2_WIDTH                                           6
#define DMA_AXIW_BUF_FULL_TH2_SHIFT                                          16
#define DMA_AXIW_BUF_FULL_TH2_MASK                                   0x003f0000
#define DMA_AXIW_BUF_FULL_TH2_RD(src)                (((src) & 0x003f0000)>>16)
#define DMA_AXIW_BUF_FULL_TH2_WR(src)           (((u32)(src)<<16) & 0x003f0000)
#define DMA_AXIW_BUF_FULL_TH2_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields dma_axiw_axif_full_th	 */
#define DMA_AXIW_AXIF_FULL_TH2_WIDTH                                          3
#define DMA_AXIW_AXIF_FULL_TH2_SHIFT                                         12
#define DMA_AXIW_AXIF_FULL_TH2_MASK                                  0x00007000
#define DMA_AXIW_AXIF_FULL_TH2_RD(src)               (((src) & 0x00007000)>>12)
#define DMA_AXIW_AXIF_FULL_TH2_WR(src)          (((u32)(src)<<12) & 0x00007000)
#define DMA_AXIW_AXIF_FULL_TH2_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields dma_axiw_asynchf_full_th	 */
#define DMA_AXIW_ASYNCHF_FULL_TH2_WIDTH                                       5
#define DMA_AXIW_ASYNCHF_FULL_TH2_SHIFT                                       4
#define DMA_AXIW_ASYNCHF_FULL_TH2_MASK                               0x000001f0
#define DMA_AXIW_ASYNCHF_FULL_TH2_RD(src)             (((src) & 0x000001f0)>>4)
#define DMA_AXIW_ASYNCHF_FULL_TH2_WR(src)        (((u32)(src)<<4) & 0x000001f0)
#define DMA_AXIW_ASYNCHF_FULL_TH2_SET(dst,src) \
                       (((dst) & ~0x000001f0) | (((u32)(src)<<4) & 0x000001f0))
/*	 Fields dma_axir_asynchf_full_th	 */
#define DMA_AXIR_ASYNCHF_FULL_TH2_WIDTH                                       4
#define DMA_AXIR_ASYNCHF_FULL_TH2_SHIFT                                       0
#define DMA_AXIR_ASYNCHF_FULL_TH2_MASK                               0x0000000f
#define DMA_AXIR_ASYNCHF_FULL_TH2_RD(src)                (((src) & 0x0000000f))
#define DMA_AXIR_ASYNCHF_FULL_TH2_WR(src)           (((u32)(src)) & 0x0000000f)
#define DMA_AXIR_ASYNCHF_FULL_TH2_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_fifo3	*/
/*	 Fields da_resp_sbuf_full_th	 */
#define DA_RESP_SBUF_FULL_TH3_WIDTH                                           4
#define DA_RESP_SBUF_FULL_TH3_SHIFT                                          28
#define DA_RESP_SBUF_FULL_TH3_MASK                                   0xf0000000
#define DA_RESP_SBUF_FULL_TH3_RD(src)                (((src) & 0xf0000000)>>28)
#define DA_RESP_SBUF_FULL_TH3_WR(src)           (((u32)(src)<<28) & 0xf0000000)
#define DA_RESP_SBUF_FULL_TH3_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields da_resp_dbuf_full_th	 */
#define DA_RESP_DBUF_FULL_TH3_WIDTH                                           4
#define DA_RESP_DBUF_FULL_TH3_SHIFT                                          24
#define DA_RESP_DBUF_FULL_TH3_MASK                                   0x0f000000
#define DA_RESP_DBUF_FULL_TH3_RD(src)                (((src) & 0x0f000000)>>24)
#define DA_RESP_DBUF_FULL_TH3_WR(src)           (((u32)(src)<<24) & 0x0f000000)
#define DA_RESP_DBUF_FULL_TH3_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields da_rreq_cff_full_th	 */
#define DA_RREQ_CFF_FULL_TH3_WIDTH                                            4
#define DA_RREQ_CFF_FULL_TH3_SHIFT                                           20
#define DA_RREQ_CFF_FULL_TH3_MASK                                    0x00f00000
#define DA_RREQ_CFF_FULL_TH3_RD(src)                 (((src) & 0x00f00000)>>20)
#define DA_RREQ_CFF_FULL_TH3_WR(src)            (((u32)(src)<<20) & 0x00f00000)
#define DA_RREQ_CFF_FULL_TH3_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields da_wreq_cff_full_th	 */
#define DA_WREQ_CFF_FULL_TH3_WIDTH                                            4
#define DA_WREQ_CFF_FULL_TH3_SHIFT                                           16
#define DA_WREQ_CFF_FULL_TH3_MASK                                    0x000f0000
#define DA_WREQ_CFF_FULL_TH3_RD(src)                 (((src) & 0x000f0000)>>16)
#define DA_WREQ_CFF_FULL_TH3_WR(src)            (((u32)(src)<<16) & 0x000f0000)
#define DA_WREQ_CFF_FULL_TH3_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields da_wreq_wff_full_th	 */
#define DA_WREQ_WFF_FULL_TH3_WIDTH                                            4
#define DA_WREQ_WFF_FULL_TH3_SHIFT                                           12
#define DA_WREQ_WFF_FULL_TH3_MASK                                    0x0000f000
#define DA_WREQ_WFF_FULL_TH3_RD(src)                 (((src) & 0x0000f000)>>12)
#define DA_WREQ_WFF_FULL_TH3_WR(src)            (((u32)(src)<<12) & 0x0000f000)
#define DA_WREQ_WFF_FULL_TH3_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields dma_cmdq_full_th	 */
#define DMA_CMDQ_FULL_TH3_WIDTH                                               6
#define DMA_CMDQ_FULL_TH3_SHIFT                                               4
#define DMA_CMDQ_FULL_TH3_MASK                                       0x000003f0
#define DMA_CMDQ_FULL_TH3_RD(src)                     (((src) & 0x000003f0)>>4)
#define DMA_CMDQ_FULL_TH3_WR(src)                (((u32)(src)<<4) & 0x000003f0)
#define DMA_CMDQ_FULL_TH3_SET(dst,src) \
                       (((dst) & ~0x000003f0) | (((u32)(src)<<4) & 0x000003f0))
/*	 Fields dma_cmdq_trac_full_th	 */
#define DMA_CMDQ_TRAC_FULL_TH3_WIDTH                                          3
#define DMA_CMDQ_TRAC_FULL_TH3_SHIFT                                          0
#define DMA_CMDQ_TRAC_FULL_TH3_MASK                                  0x00000007
#define DMA_CMDQ_TRAC_FULL_TH3_RD(src)                   (((src) & 0x00000007))
#define DMA_CMDQ_TRAC_FULL_TH3_WR(src)              (((u32)(src)) & 0x00000007)
#define DMA_CMDQ_TRAC_FULL_TH3_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register gfc_fifo4	*/
/*	 Fields da_pn_wbufc_empty_th	 */
#define DA_PN_WBUFC_EMPTY_TH4_WIDTH                                           5
#define DA_PN_WBUFC_EMPTY_TH4_SHIFT                                          24
#define DA_PN_WBUFC_EMPTY_TH4_MASK                                   0x1f000000
#define DA_PN_WBUFC_EMPTY_TH4_RD(src)                (((src) & 0x1f000000)>>24)
#define DA_PN_WBUFC_EMPTY_TH4_WR(src)           (((u32)(src)<<24) & 0x1f000000)
#define DA_PN_WBUFC_EMPTY_TH4_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields da_pn_wbufc_full_th	 */
#define DA_PN_WBUFC_FULL_TH4_WIDTH                                            5
#define DA_PN_WBUFC_FULL_TH4_SHIFT                                           16
#define DA_PN_WBUFC_FULL_TH4_MASK                                    0x001f0000
#define DA_PN_WBUFC_FULL_TH4_RD(src)                 (((src) & 0x001f0000)>>16)
#define DA_PN_WBUFC_FULL_TH4_WR(src)            (((u32)(src)<<16) & 0x001f0000)
#define DA_PN_WBUFC_FULL_TH4_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields da_pn_rbufc_empty_th	 */
#define DA_PN_RBUFC_EMPTY_TH4_WIDTH                                           5
#define DA_PN_RBUFC_EMPTY_TH4_SHIFT                                           8
#define DA_PN_RBUFC_EMPTY_TH4_MASK                                   0x00001f00
#define DA_PN_RBUFC_EMPTY_TH4_RD(src)                 (((src) & 0x00001f00)>>8)
#define DA_PN_RBUFC_EMPTY_TH4_WR(src)            (((u32)(src)<<8) & 0x00001f00)
#define DA_PN_RBUFC_EMPTY_TH4_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields da_pn_rbufc_full_th	 */
#define DA_PN_RBUFC_FULL_TH4_WIDTH                                            5
#define DA_PN_RBUFC_FULL_TH4_SHIFT                                            0
#define DA_PN_RBUFC_FULL_TH4_MASK                                    0x0000001f
#define DA_PN_RBUFC_FULL_TH4_RD(src)                     (((src) & 0x0000001f))
#define DA_PN_RBUFC_FULL_TH4_WR(src)                (((u32)(src)) & 0x0000001f)
#define DA_PN_RBUFC_FULL_TH4_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register gfc_fifo5	*/
/*	 Fields da_pn_wbufw_empty_th	 */
#define DA_PN_WBUFW_EMPTY_TH5_WIDTH                                           5
#define DA_PN_WBUFW_EMPTY_TH5_SHIFT                                           8
#define DA_PN_WBUFW_EMPTY_TH5_MASK                                   0x00001f00
#define DA_PN_WBUFW_EMPTY_TH5_RD(src)                 (((src) & 0x00001f00)>>8)
#define DA_PN_WBUFW_EMPTY_TH5_WR(src)            (((u32)(src)<<8) & 0x00001f00)
#define DA_PN_WBUFW_EMPTY_TH5_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields da_pn_wbufw_full_th	 */
#define DA_PN_WBUFW_FULL_TH5_WIDTH                                            5
#define DA_PN_WBUFW_FULL_TH5_SHIFT                                            0
#define DA_PN_WBUFW_FULL_TH5_MASK                                    0x0000001f
#define DA_PN_WBUFW_FULL_TH5_RD(src)                     (((src) & 0x0000001f))
#define DA_PN_WBUFW_FULL_TH5_WR(src)                (((u32)(src)) & 0x0000001f)
#define DA_PN_WBUFW_FULL_TH5_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register gfc_da_err	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_WIDTH                                                   32
#define REGSPEC_ADDR_SHIFT                                                    0
#define REGSPEC_ADDR_MASK                                            0xffffffff
#define REGSPEC_ADDR_RD(src)                             (((src) & 0xffffffff))
#define REGSPEC_ADDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_arb_ctrl	*/
/*	 Fields nandarb_pr1	 */
#define NANDARB_PR1_WIDTH                                                     2
#define NANDARB_PR1_SHIFT                                                    30
#define NANDARB_PR1_MASK                                             0xc0000000
#define NANDARB_PR1_RD(src)                          (((src) & 0xc0000000)>>30)
#define NANDARB_PR1_WR(src)                     (((u32)(src)<<30) & 0xc0000000)
#define NANDARB_PR1_SET(dst,src) \
                      (((dst) & ~0xc0000000) | (((u32)(src)<<30) & 0xc0000000))
/*	 Fields nandarb_pr0	 */
#define NANDARB_PR0_WIDTH                                                     2
#define NANDARB_PR0_SHIFT                                                    28
#define NANDARB_PR0_MASK                                             0x30000000
#define NANDARB_PR0_RD(src)                          (((src) & 0x30000000)>>28)
#define NANDARB_PR0_WR(src)                     (((u32)(src)<<28) & 0x30000000)
#define NANDARB_PR0_SET(dst,src) \
                      (((dst) & ~0x30000000) | (((u32)(src)<<28) & 0x30000000))
/*	 Fields nandarb_override	 */
#define NANDARB_OVERRIDE_WIDTH                                                1
#define NANDARB_OVERRIDE_SHIFT                                               27
#define NANDARB_OVERRIDE_MASK                                        0x08000000
#define NANDARB_OVERRIDE_RD(src)                     (((src) & 0x08000000)>>27)
#define NANDARB_OVERRIDE_WR(src)                (((u32)(src)<<27) & 0x08000000)
#define NANDARB_OVERRIDE_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields pnorarb_override	 */
#define PNORARB_OVERRIDE_WIDTH                                                1
#define PNORARB_OVERRIDE_SHIFT                                               24
#define PNORARB_OVERRIDE_MASK                                        0x01000000
#define PNORARB_OVERRIDE_RD(src)                     (((src) & 0x01000000)>>24)
#define PNORARB_OVERRIDE_WR(src)                (((u32)(src)<<24) & 0x01000000)
#define PNORARB_OVERRIDE_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields pnorarb_pr1	 */
#define PNORARB_PR1_WIDTH                                                     2
#define PNORARB_PR1_SHIFT                                                    22
#define PNORARB_PR1_MASK                                             0x00c00000
#define PNORARB_PR1_RD(src)                          (((src) & 0x00c00000)>>22)
#define PNORARB_PR1_WR(src)                     (((u32)(src)<<22) & 0x00c00000)
#define PNORARB_PR1_SET(dst,src) \
                      (((dst) & ~0x00c00000) | (((u32)(src)<<22) & 0x00c00000))
/*	 Fields pnorarb_pr0	 */
#define PNORARB_PR0_WIDTH                                                     2
#define PNORARB_PR0_SHIFT                                                    20
#define PNORARB_PR0_MASK                                             0x00300000
#define PNORARB_PR0_RD(src)                          (((src) & 0x00300000)>>20)
#define PNORARB_PR0_WR(src)                     (((u32)(src)<<20) & 0x00300000)
#define PNORARB_PR0_SET(dst,src) \
                      (((dst) & ~0x00300000) | (((u32)(src)<<20) & 0x00300000))
/*	 Fields ebusarb_override	 */
#define EBUSARB_OVERRIDE_WIDTH                                                1
#define EBUSARB_OVERRIDE_SHIFT                                               16
#define EBUSARB_OVERRIDE_MASK                                        0x00010000
#define EBUSARB_OVERRIDE_RD(src)                     (((src) & 0x00010000)>>16)
#define EBUSARB_OVERRIDE_WR(src)                (((u32)(src)<<16) & 0x00010000)
#define EBUSARB_OVERRIDE_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ebusarb_pr3	 */
#define EBUSARB_PR3_WIDTH                                                     4
#define EBUSARB_PR3_SHIFT                                                    12
#define EBUSARB_PR3_MASK                                             0x0000f000
#define EBUSARB_PR3_RD(src)                          (((src) & 0x0000f000)>>12)
#define EBUSARB_PR3_WR(src)                     (((u32)(src)<<12) & 0x0000f000)
#define EBUSARB_PR3_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields ebusarb_pr2	 */
#define EBUSARB_PR2_WIDTH                                                     4
#define EBUSARB_PR2_SHIFT                                                     8
#define EBUSARB_PR2_MASK                                             0x00000f00
#define EBUSARB_PR2_RD(src)                           (((src) & 0x00000f00)>>8)
#define EBUSARB_PR2_WR(src)                      (((u32)(src)<<8) & 0x00000f00)
#define EBUSARB_PR2_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields ebusarb_pr1	 */
#define EBUSARB_PR1_WIDTH                                                     4
#define EBUSARB_PR1_SHIFT                                                     4
#define EBUSARB_PR1_MASK                                             0x000000f0
#define EBUSARB_PR1_RD(src)                           (((src) & 0x000000f0)>>4)
#define EBUSARB_PR1_WR(src)                      (((u32)(src)<<4) & 0x000000f0)
#define EBUSARB_PR1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields ebusarb_pr0	 */
#define EBUSARB_PR0_WIDTH                                                     4
#define EBUSARB_PR0_SHIFT                                                     0
#define EBUSARB_PR0_MASK                                             0x0000000f
#define EBUSARB_PR0_RD(src)                              (((src) & 0x0000000f))
#define EBUSARB_PR0_WR(src)                         (((u32)(src)) & 0x0000000f)
#define EBUSARB_PR0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_arb_ctrl1	*/
/*	 Fields nand_dma_intl_en	 */
#define NAND_DMA_INTL_EN1_WIDTH                                               1
#define NAND_DMA_INTL_EN1_SHIFT                                              24
#define NAND_DMA_INTL_EN1_MASK                                       0x01000000
#define NAND_DMA_INTL_EN1_RD(src)                    (((src) & 0x01000000)>>24)
#define NAND_DMA_INTL_EN1_WR(src)               (((u32)(src)<<24) & 0x01000000)
#define NAND_DMA_INTL_EN1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields nand_dma_intl_th	 */
#define NAND_DMA_INTL_TH1_WIDTH                                              24
#define NAND_DMA_INTL_TH1_SHIFT                                               0
#define NAND_DMA_INTL_TH1_MASK                                       0x00ffffff
#define NAND_DMA_INTL_TH1_RD(src)                        (((src) & 0x00ffffff))
#define NAND_DMA_INTL_TH1_WR(src)                   (((u32)(src)) & 0x00ffffff)
#define NAND_DMA_INTL_TH1_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_axim_ctrl	*/
/*	 Fields wr_max_os_req	 */
#define WR_MAX_OS_REQ_WIDTH                                                   4
#define WR_MAX_OS_REQ_SHIFT                                                   4
#define WR_MAX_OS_REQ_MASK                                           0x000000f0
#define WR_MAX_OS_REQ_RD(src)                         (((src) & 0x000000f0)>>4)
#define WR_MAX_OS_REQ_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define WR_MAX_OS_REQ_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields rd_max_os_req	 */
#define RD_MAX_OS_REQ_WIDTH                                                   4
#define RD_MAX_OS_REQ_SHIFT                                                   0
#define RD_MAX_OS_REQ_MASK                                           0x0000000f
#define RD_MAX_OS_REQ_RD(src)                            (((src) & 0x0000000f))
#define RD_MAX_OS_REQ_WR(src)                       (((u32)(src)) & 0x0000000f)
#define RD_MAX_OS_REQ_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_axiwm_sts0	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR0_WIDTH                                                  32
#define REGSPEC_ADDR0_SHIFT                                                   0
#define REGSPEC_ADDR0_MASK                                           0xffffffff
#define REGSPEC_ADDR0_RD(src)                            (((src) & 0xffffffff))
#define REGSPEC_ADDR0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_axiwm_sts1	*/
/*	 Fields resp	 */
#define RESP1_WIDTH                                                           2
#define RESP1_SHIFT                                                          12
#define RESP1_MASK                                                   0x00003000
#define RESP1_RD(src)                                (((src) & 0x00003000)>>12)
#define RESP1_SET(dst,src) \
                      (((dst) & ~0x00003000) | (((u32)(src)<<12) & 0x00003000))
/*	 Fields addr	 */
#define REGSPEC_ADDR1_WIDTH                                                  10
#define REGSPEC_ADDR1_SHIFT                                                   0
#define REGSPEC_ADDR1_MASK                                           0x000003ff
#define REGSPEC_ADDR1_RD(src)                            (((src) & 0x000003ff))
#define REGSPEC_ADDR1_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_axirm_sts0	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR0_F1_WIDTH                                               32
#define REGSPEC_ADDR0_F1_SHIFT                                                0
#define REGSPEC_ADDR0_F1_MASK                                        0xffffffff
#define REGSPEC_ADDR0_F1_RD(src)                         (((src) & 0xffffffff))
#define REGSPEC_ADDR0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_axirm_sts1	*/
/*	 Fields resp	 */
#define RESP1_F1_WIDTH                                                        2
#define RESP1_F1_SHIFT                                                       12
#define RESP1_F1_MASK                                                0x00003000
#define RESP1_F1_RD(src)                             (((src) & 0x00003000)>>12)
#define RESP1_F1_SET(dst,src) \
                      (((dst) & ~0x00003000) | (((u32)(src)<<12) & 0x00003000))
/*	 Fields addr	 */
#define REGSPEC_ADDR1_F1_WIDTH                                               10
#define REGSPEC_ADDR1_F1_SHIFT                                                0
#define REGSPEC_ADDR1_F1_MASK                                        0x000003ff
#define REGSPEC_ADDR1_F1_RD(src)                         (((src) & 0x000003ff))
#define REGSPEC_ADDR1_F1_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank0_ctrl0	*/
/*	 Fields nand_wp_n	 */
#define NAND_WP_N0_WIDTH                                                      1
#define NAND_WP_N0_SHIFT                                                      8
#define NAND_WP_N0_MASK                                              0x00000100
#define NAND_WP_N0_RD(src)                            (((src) & 0x00000100)>>8)
#define NAND_WP_N0_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define NAND_WP_N0_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bus_width	 */
#define BUS_WIDTH0_WIDTH                                                      2
#define BUS_WIDTH0_SHIFT                                                      6
#define BUS_WIDTH0_MASK                                              0x000000c0
#define BUS_WIDTH0_RD(src)                            (((src) & 0x000000c0)>>6)
#define BUS_WIDTH0_WR(src)                       (((u32)(src)<<6) & 0x000000c0)
#define BUS_WIDTH0_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields bus_usage	 */
#define BUS_USAGE0_WIDTH                                                      2
#define BUS_USAGE0_SHIFT                                                      4
#define BUS_USAGE0_MASK                                              0x00000030
#define BUS_USAGE0_RD(src)                            (((src) & 0x00000030)>>4)
#define BUS_USAGE0_WR(src)                       (((u32)(src)<<4) & 0x00000030)
#define BUS_USAGE0_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields bank_type	 */
#define BANK_TYPE0_WIDTH                                                      3
#define BANK_TYPE0_SHIFT                                                      1
#define BANK_TYPE0_MASK                                              0x0000000e
#define BANK_TYPE0_RD(src)                            (((src) & 0x0000000e)>>1)
#define BANK_TYPE0_WR(src)                       (((u32)(src)<<1) & 0x0000000e)
#define BANK_TYPE0_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields bank_valid	 */
#define BANK_VALID0_WIDTH                                                     1
#define BANK_VALID0_SHIFT                                                     0
#define BANK_VALID0_MASK                                             0x00000001
#define BANK_VALID0_RD(src)                              (((src) & 0x00000001))
#define BANK_VALID0_WR(src)                         (((u32)(src)) & 0x00000001)
#define BANK_VALID0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank0_start_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F1_WIDTH_GFC                                                14
#define REGSPEC_ADDR_F1_SHIFT_GFC                                                 0
#define REGSPEC_ADDR_F1_MASK_GFC                                         0x00003fff
#define REGSPEC_ADDR_F1_RD_GFC(src)                          (((src) & 0x00003fff))
#define REGSPEC_ADDR_F1_WR_GFC(src)                     (((u32)(src)) & 0x00003fff)
#define REGSPEC_ADDR_F1_SET_GFC(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register gfc_bank0_end_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F2_WIDTH                                                15
#define REGSPEC_ADDR_F2_SHIFT                                                 0
#define REGSPEC_ADDR_F2_MASK                                         0x00007fff
#define REGSPEC_ADDR_F2_RD(src)                          (((src) & 0x00007fff))
#define REGSPEC_ADDR_F2_WR(src)                     (((u32)(src)) & 0x00007fff)
#define REGSPEC_ADDR_F2_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register gfc_bank0_base_add	*/
/*	 Fields bank_base_add	 */
#define BANK_BASE_ADD_WIDTH                                                  32
#define BANK_BASE_ADD_SHIFT                                                   0
#define BANK_BASE_ADD_MASK                                           0xffffffff
#define BANK_BASE_ADD_RD(src)                            (((src) & 0xffffffff))
#define BANK_BASE_ADD_WR(src)                       (((u32)(src)) & 0xffffffff)
#define BANK_BASE_ADD_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_dma_ctrl0	*/
/*	 Fields complNum_4_int	 */
#define COMPLNUM_4_INT0_WIDTH                                                 3
#define COMPLNUM_4_INT0_SHIFT                                                10
#define COMPLNUM_4_INT0_MASK                                         0x00001c00
#define COMPLNUM_4_INT0_RD(src)                      (((src) & 0x00001c00)>>10)
#define COMPLNUM_4_INT0_WR(src)                 (((u32)(src)<<10) & 0x00001c00)
#define COMPLNUM_4_INT0_SET(dst,src) \
                      (((dst) & ~0x00001c00) | (((u32)(src)<<10) & 0x00001c00))
/*	 Fields dma_cmd_code	 */
#define DMA_CMD_CODE0_WIDTH                                                   3
#define DMA_CMD_CODE0_SHIFT                                                   7
#define DMA_CMD_CODE0_MASK                                           0x00000380
#define DMA_CMD_CODE0_RD(src)                         (((src) & 0x00000380)>>7)
#define DMA_CMD_CODE0_WR(src)                    (((u32)(src)<<7) & 0x00000380)
#define DMA_CMD_CODE0_SET(dst,src) \
                       (((dst) & ~0x00000380) | (((u32)(src)<<7) & 0x00000380))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID0_WIDTH                                                     2
#define DMA_CMD_ID0_SHIFT                                                     3
#define DMA_CMD_ID0_MASK                                             0x00000018
#define DMA_CMD_ID0_RD(src)                           (((src) & 0x00000018)>>3)
#define DMA_CMD_ID0_WR(src)                      (((u32)(src)<<3) & 0x00000018)
#define DMA_CMD_ID0_SET(dst,src) \
                       (((dst) & ~0x00000018) | (((u32)(src)<<3) & 0x00000018))
/*	 Fields dma_cmd_pop	 */
#define DMA_CMD_POP0_WIDTH                                                    1
#define DMA_CMD_POP0_SHIFT                                                    2
#define DMA_CMD_POP0_MASK                                            0x00000004
#define DMA_CMD_POP0_RD(src)                          (((src) & 0x00000004)>>2)
#define DMA_CMD_POP0_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define DMA_CMD_POP0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dma_cmd_push	 */
#define DMA_CMD_PUSH0_WIDTH                                                   1
#define DMA_CMD_PUSH0_SHIFT                                                   1
#define DMA_CMD_PUSH0_MASK                                           0x00000002
#define DMA_CMD_PUSH0_RD(src)                         (((src) & 0x00000002)>>1)
#define DMA_CMD_PUSH0_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define DMA_CMD_PUSH0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dma_cmd_valid	 */
#define DMA_CMD_VALID0_WIDTH                                                  1
#define DMA_CMD_VALID0_SHIFT                                                  0
#define DMA_CMD_VALID0_MASK                                          0x00000001
#define DMA_CMD_VALID0_RD(src)                           (((src) & 0x00000001))
#define DMA_CMD_VALID0_WR(src)                      (((u32)(src)) & 0x00000001)
#define DMA_CMD_VALID0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank0_dma_start_add0	*/
/*	 Fields dma_start_add0	 */
#define DMA_START_ADD00_WIDTH                                                32
#define DMA_START_ADD00_SHIFT                                                 0
#define DMA_START_ADD00_MASK                                         0xffffffff
#define DMA_START_ADD00_RD(src)                          (((src) & 0xffffffff))
#define DMA_START_ADD00_WR(src)                     (((u32)(src)) & 0xffffffff)
#define DMA_START_ADD00_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_dma_start_add1	*/
/*	 Fields dma_start_add1	 */
#define DMA_START_ADD11_WIDTH                                                10
#define DMA_START_ADD11_SHIFT                                                 0
#define DMA_START_ADD11_MASK                                         0x000003ff
#define DMA_START_ADD11_RD(src)                          (((src) & 0x000003ff))
#define DMA_START_ADD11_WR(src)                     (((u32)(src)) & 0x000003ff)
#define DMA_START_ADD11_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank0_dma_des_add0	*/
/*	 Fields dma_des_add0	 */
#define DMA_DES_ADD00_WIDTH                                                  32
#define DMA_DES_ADD00_SHIFT                                                   0
#define DMA_DES_ADD00_MASK                                           0xffffffff
#define DMA_DES_ADD00_RD(src)                            (((src) & 0xffffffff))
#define DMA_DES_ADD00_WR(src)                       (((u32)(src)) & 0xffffffff)
#define DMA_DES_ADD00_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_dma_des_add1	*/
/*	 Fields dma_des_add1	 */
#define DMA_DES_ADD11_WIDTH                                                  10
#define DMA_DES_ADD11_SHIFT                                                   0
#define DMA_DES_ADD11_MASK                                           0x000003ff
#define DMA_DES_ADD11_RD(src)                            (((src) & 0x000003ff))
#define DMA_DES_ADD11_WR(src)                       (((u32)(src)) & 0x000003ff)
#define DMA_DES_ADD11_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank0_dma_status	*/
/*	 Fields bits_corrected_ecc	 */
#define BITS_CORRECTED_ECC_WIDTH                                              4
#define BITS_CORRECTED_ECC_SHIFT                                             14
#define BITS_CORRECTED_ECC_MASK                                      0x0003c000
#define BITS_CORRECTED_ECC_RD(src)                   (((src) & 0x0003c000)>>14)
#define BITS_CORRECTED_ECC_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields dma_err	 */
#define DMA_ERR_WIDTH                                                         3
#define DMA_ERR_SHIFT                                                         9
#define DMA_ERR_MASK                                                 0x00000e00
#define DMA_ERR_RD(src)                               (((src) & 0x00000e00)>>9)
#define DMA_ERR_SET(dst,src) \
                       (((dst) & ~0x00000e00) | (((u32)(src)<<9) & 0x00000e00))
/*	 Fields dma_cmpl_status	 */
#define DMA_CMPL_STATUS_WIDTH                                                 2
#define DMA_CMPL_STATUS_SHIFT                                                 6
#define DMA_CMPL_STATUS_MASK                                         0x000000c0
#define DMA_CMPL_STATUS_RD(src)                       (((src) & 0x000000c0)>>6)
#define DMA_CMPL_STATUS_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID_WIDTH                                                      2
#define DMA_CMD_ID_SHIFT                                                      1
#define DMA_CMD_ID_MASK                                              0x00000006
#define DMA_CMD_ID_RD(src)                            (((src) & 0x00000006)>>1)
#define DMA_CMD_ID_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields dma_cmpl_valid	 */
#define DMA_CMPL_VALID_WIDTH                                                  1
#define DMA_CMPL_VALID_SHIFT                                                  0
#define DMA_CMPL_VALID_MASK                                          0x00000001
#define DMA_CMPL_VALID_RD(src)                           (((src) & 0x00000001))
#define DMA_CMPL_VALID_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank0_dma_eccerr0_add_col	*/
/*	 Fields dma_eccerr0_add_col	 */
#define DMA_ECCERR0_ADD_COL_WIDTH                                            32
#define DMA_ECCERR0_ADD_COL_SHIFT                                             0
#define DMA_ECCERR0_ADD_COL_MASK                                     0xffffffff
#define DMA_ECCERR0_ADD_COL_RD(src)                      (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_COL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_dma_eccerr0_add_row	*/
/*	 Fields dma_eccerr0_add_row	 */
#define DMA_ECCERR0_ADD_ROW_WIDTH                                            32
#define DMA_ECCERR0_ADD_ROW_SHIFT                                             0
#define DMA_ECCERR0_ADD_ROW_MASK                                     0xffffffff
#define DMA_ECCERR0_ADD_ROW_RD(src)                      (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_ROW_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_dma_eccerr1_add_col	*/
/*	 Fields dma_eccerr1_add_col	 */
#define DMA_ECCERR1_ADD_COL_WIDTH                                            32
#define DMA_ECCERR1_ADD_COL_SHIFT                                             0
#define DMA_ECCERR1_ADD_COL_MASK                                     0xffffffff
#define DMA_ECCERR1_ADD_COL_RD(src)                      (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_COL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_dma_eccerr1_add_row	*/
/*	 Fields dma_eccerr1_add_row	 */
#define DMA_ECCERR1_ADD_ROW_WIDTH                                            32
#define DMA_ECCERR1_ADD_ROW_SHIFT                                             0
#define DMA_ECCERR1_ADD_ROW_MASK                                     0xffffffff
#define DMA_ECCERR1_ADD_ROW_RD(src)                      (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_ROW_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_INT	*/
/*	 Fields nandpio_device_protection_err	 */
#define NANDPIO_DEVICE_PROTECTION_ERR_WIDTH                                   1
#define NANDPIO_DEVICE_PROTECTION_ERR_SHIFT                                  11
#define NANDPIO_DEVICE_PROTECTION_ERR_MASK                           0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERR_RD(src)        (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERR_WR(src)   (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERR_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields norp_device_protection_err	 */
#define NORP_DEVICE_PROTECTION_ERR_WIDTH                                      1
#define NORP_DEVICE_PROTECTION_ERR_SHIFT                                     10
#define NORP_DEVICE_PROTECTION_ERR_MASK                              0x00000400
#define NORP_DEVICE_PROTECTION_ERR_RD(src)           (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERR_WR(src)      (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERR_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields dma_cmd_override_err	 */
#define DMA_CMD_OVERRIDE_ERR_WIDTH                                            1
#define DMA_CMD_OVERRIDE_ERR_SHIFT                                            9
#define DMA_CMD_OVERRIDE_ERR_MASK                                    0x00000200
#define DMA_CMD_OVERRIDE_ERR_RD(src)                  (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERR_WR(src)             (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERR_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields device_protection_err	 */
#define DEVICE_PROTECTION_ERR_WIDTH                                           1
#define DEVICE_PROTECTION_ERR_SHIFT                                           8
#define DEVICE_PROTECTION_ERR_MASK                                   0x00000100
#define DEVICE_PROTECTION_ERR_RD(src)                 (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERR_WR(src)            (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERR_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields transaction_timeout	 */
#define TRANSACTION_TIMEOUT_WIDTH                                             1
#define TRANSACTION_TIMEOUT_SHIFT                                             7
#define TRANSACTION_TIMEOUT_MASK                                     0x00000080
#define TRANSACTION_TIMEOUT_RD(src)                   (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUT_WR(src)              (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUT_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields parity_err	 */
#define PARITY_ERR_WIDTH                                                      1
#define PARITY_ERR_SHIFT                                                      6
#define PARITY_ERR_MASK                                              0x00000040
#define PARITY_ERR_RD(src)                            (((src) & 0x00000040)>>6)
#define PARITY_ERR_WR(src)                       (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERR_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ecc_err_single	 */
#define ECC_ERR_SINGLE_WIDTH                                                  1
#define ECC_ERR_SINGLE_SHIFT                                                  5
#define ECC_ERR_SINGLE_MASK                                          0x00000020
#define ECC_ERR_SINGLE_RD(src)                        (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLE_WR(src)                   (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLE_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ecc_err_multiple	 */
#define ECC_ERR_MULTIPLE_WIDTH                                                1
#define ECC_ERR_MULTIPLE_SHIFT                                                4
#define ECC_ERR_MULTIPLE_MASK                                        0x00000010
#define ECC_ERR_MULTIPLE_RD(src)                      (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLE_WR(src)                 (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields dma_done	 */
#define DMA_DONE_GFC_WIDTH                                                        1
#define DMA_DONE_GFC_SHIFT                                                        2
#define DMA_DONE_GFC_MASK                                                0x00000004
#define DMA_DONE_GFC_RD(src)                              (((src) & 0x00000004)>>2)
#define DMA_DONE_GFC_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define DMA_DONE_GFC_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank0_interruptMask	*/
/*    Mask Register Fields nandpio_device_protection_errMask    */
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_WIDTH                               1
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_SHIFT                              11
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_MASK                       0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_RD(src)    (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields norp_device_protection_errMask    */
#define NORP_DEVICE_PROTECTION_ERRMASK_WIDTH                                  1
#define NORP_DEVICE_PROTECTION_ERRMASK_SHIFT                                 10
#define NORP_DEVICE_PROTECTION_ERRMASK_MASK                          0x00000400
#define NORP_DEVICE_PROTECTION_ERRMASK_RD(src)       (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERRMASK_WR(src)  (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields dma_cmd_override_errMask    */
#define DMA_CMD_OVERRIDE_ERRMASK_WIDTH                                        1
#define DMA_CMD_OVERRIDE_ERRMASK_SHIFT                                        9
#define DMA_CMD_OVERRIDE_ERRMASK_MASK                                0x00000200
#define DMA_CMD_OVERRIDE_ERRMASK_RD(src)              (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERRMASK_WR(src)         (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields device_protection_errMask    */
#define DEVICE_PROTECTION_ERRMASK_WIDTH                                       1
#define DEVICE_PROTECTION_ERRMASK_SHIFT                                       8
#define DEVICE_PROTECTION_ERRMASK_MASK                               0x00000100
#define DEVICE_PROTECTION_ERRMASK_RD(src)             (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERRMASK_WR(src)        (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields transaction_timeoutMask    */
#define TRANSACTION_TIMEOUTMASK_WIDTH                                         1
#define TRANSACTION_TIMEOUTMASK_SHIFT                                         7
#define TRANSACTION_TIMEOUTMASK_MASK                                 0x00000080
#define TRANSACTION_TIMEOUTMASK_RD(src)               (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUTMASK_WR(src)          (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUTMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields parity_errMask    */
#define PARITY_ERRMASK_WIDTH                                                  1
#define PARITY_ERRMASK_SHIFT                                                  6
#define PARITY_ERRMASK_MASK                                          0x00000040
#define PARITY_ERRMASK_RD(src)                        (((src) & 0x00000040)>>6)
#define PARITY_ERRMASK_WR(src)                   (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ecc_err_singleMask    */
#define ECC_ERR_SINGLEMASK_WIDTH                                              1
#define ECC_ERR_SINGLEMASK_SHIFT                                              5
#define ECC_ERR_SINGLEMASK_MASK                                      0x00000020
#define ECC_ERR_SINGLEMASK_RD(src)                    (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLEMASK_WR(src)               (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLEMASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ecc_err_multipleMask    */
#define ECC_ERR_MULTIPLEMASK_WIDTH                                            1
#define ECC_ERR_MULTIPLEMASK_SHIFT                                            4
#define ECC_ERR_MULTIPLEMASK_MASK                                    0x00000010
#define ECC_ERR_MULTIPLEMASK_RD(src)                  (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLEMASK_WR(src)             (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLEMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields dma_doneMask    */
#define DMA_DONEMASK_WIDTH                                                    1
#define DMA_DONEMASK_SHIFT                                                    2
#define DMA_DONEMASK_MASK                                            0x00000004
#define DMA_DONEMASK_RD(src)                          (((src) & 0x00000004)>>2)
#define DMA_DONEMASK_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define DMA_DONEMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank0_sram_ctrl0	*/
/*	 Fields rtc	 */
#define REGSPEC_RTC0_WIDTH                                                    3
#define REGSPEC_RTC0_SHIFT                                                   12
#define REGSPEC_RTC0_MASK                                            0x00007000
#define REGSPEC_RTC0_RD(src)                         (((src) & 0x00007000)>>12)
#define REGSPEC_RTC0_WR(src)                    (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_RTC0_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields muxen	 */
#define MUXEN0_WIDTH                                                          1
#define MUXEN0_SHIFT                                                         10
#define MUXEN0_MASK                                                  0x00000400
#define MUXEN0_RD(src)                               (((src) & 0x00000400)>>10)
#define MUXEN0_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MUXEN0_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rdy_timeout_cnt	 */
#define RDY_TIMEOUT_CNT0_WIDTH                                                3
#define RDY_TIMEOUT_CNT0_SHIFT                                                2
#define RDY_TIMEOUT_CNT0_MASK                                        0x0000001c
#define RDY_TIMEOUT_CNT0_RD(src)                      (((src) & 0x0000001c)>>2)
#define RDY_TIMEOUT_CNT0_WR(src)                 (((u32)(src)<<2) & 0x0000001c)
#define RDY_TIMEOUT_CNT0_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields ptd	 */
#define PTD0_WIDTH                                                            1
#define PTD0_SHIFT                                                            1
#define PTD0_MASK                                                    0x00000002
#define PTD0_RD(src)                                  (((src) & 0x00000002)>>1)
#define PTD0_WR(src)                             (((u32)(src)<<1) & 0x00000002)
#define PTD0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields le	 */
#define LE0_WIDTH                                                             1
#define LE0_SHIFT                                                             0
#define LE0_MASK                                                     0x00000001
#define LE0_RD(src)                                      (((src) & 0x00000001))
#define LE0_WR(src)                                 (((u32)(src)) & 0x00000001)
#define LE0_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank0_sram_nor_ctrl1	*/
/*	 Fields BME	 */
#define BME1_WIDTH                                                            1
#define BME1_SHIFT                                                           31
#define BME1_MASK                                                    0x80000000
#define BME1_RD(src)                                 (((src) & 0x80000000)>>31)
#define BME1_WR(src)                            (((u32)(src)<<31) & 0x80000000)
#define BME1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields OEO	 */
#define OEO1_WIDTH                                                            1
#define OEO1_SHIFT                                                           30
#define OEO1_MASK                                                    0x40000000
#define OEO1_RD(src)                                 (((src) & 0x40000000)>>30)
#define OEO1_WR(src)                            (((u32)(src)<<30) & 0x40000000)
#define OEO1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields BWT	 */
#define BWT1_WIDTH                                                            5
#define BWT1_SHIFT                                                           20
#define BWT1_MASK                                                    0x01f00000
#define BWT1_RD(src)                                 (((src) & 0x01f00000)>>20)
#define BWT1_WR(src)                            (((u32)(src)<<20) & 0x01f00000)
#define BWT1_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields FWT	 */
#define FWT1_WIDTH                                                            7
#define FWT1_SHIFT                                                           12
#define FWT1_MASK                                                    0x0007f000
#define FWT1_RD(src)                                 (((src) & 0x0007f000)>>12)
#define FWT1_WR(src)                            (((u32)(src)<<12) & 0x0007f000)
#define FWT1_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields TWT	 */
#define TWT1_WIDTH                                                           10
#define TWT1_SHIFT                                                            0
#define TWT1_MASK                                                    0x000003ff
#define TWT1_RD(src)                                     (((src) & 0x000003ff))
#define TWT1_WR(src)                                (((u32)(src)) & 0x000003ff)
#define TWT1_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank0_sram_nor_ctrl2	*/
/*	 Fields ALN	 */
#define ALN2_WIDTH                                                            4
#define ALN2_SHIFT                                                           28
#define ALN2_MASK                                                    0xf0000000
#define ALN2_RD(src)                                 (((src) & 0xf0000000)>>28)
#define ALN2_WR(src)                            (((u32)(src)<<28) & 0xf0000000)
#define ALN2_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields PEN	 */
#define PEN2_WIDTH                                                            1
#define PEN2_SHIFT                                                           27
#define PEN2_MASK                                                    0x08000000
#define PEN2_RD(src)                                 (((src) & 0x08000000)>>27)
#define PEN2_WR(src)                            (((u32)(src)<<27) & 0x08000000)
#define PEN2_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields BEM	 */
#define BEM2_WIDTH                                                            1
#define BEM2_SHIFT                                                           26
#define BEM2_MASK                                                    0x04000000
#define BEM2_RD(src)                                 (((src) & 0x04000000)>>26)
#define BEM2_WR(src)                            (((u32)(src)<<26) & 0x04000000)
#define BEM2_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SOR	 */
#define SOR2_WIDTH                                                            1
#define SOR2_SHIFT                                                           25
#define SOR2_MASK                                                    0x02000000
#define SOR2_RD(src)                                 (((src) & 0x02000000)>>25)
#define SOR2_WR(src)                            (((u32)(src)<<25) & 0x02000000)
#define SOR2_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RE	 */
#define RE2_WIDTH                                                             1
#define RE2_SHIFT                                                            24
#define RE2_MASK                                                     0x01000000
#define RE2_RD(src)                                  (((src) & 0x01000000)>>24)
#define RE2_WR(src)                             (((u32)(src)<<24) & 0x01000000)
#define RE2_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields TH	 */
#define TH2_WIDTH                                                             5
#define TH2_SHIFT                                                            16
#define TH2_MASK                                                     0x001f0000
#define TH2_RD(src)                                  (((src) & 0x001f0000)>>16)
#define TH2_WR(src)                             (((u32)(src)<<16) & 0x001f0000)
#define TH2_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WBF	 */
#define WBF2_WIDTH                                                            4
#define WBF2_SHIFT                                                           12
#define WBF2_MASK                                                    0x0000f000
#define WBF2_RD(src)                                 (((src) & 0x0000f000)>>12)
#define WBF2_WR(src)                            (((u32)(src)<<12) & 0x0000f000)
#define WBF2_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WBN	 */
#define WBN2_WIDTH                                                            4
#define WBN2_SHIFT                                                            8
#define WBN2_MASK                                                    0x00000f00
#define WBN2_RD(src)                                  (((src) & 0x00000f00)>>8)
#define WBN2_WR(src)                             (((u32)(src)<<8) & 0x00000f00)
#define WBN2_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields OEN	 */
#define OEN2_WIDTH                                                            4
#define OEN2_SHIFT                                                            4
#define OEN2_MASK                                                    0x000000f0
#define OEN2_RD(src)                                  (((src) & 0x000000f0)>>4)
#define OEN2_WR(src)                             (((u32)(src)<<4) & 0x000000f0)
#define OEN2_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields CSN	 */
#define CSN2_WIDTH                                                            4
#define CSN2_SHIFT                                                            0
#define CSN2_MASK                                                    0x0000000f
#define CSN2_RD(src)                                     (((src) & 0x0000000f))
#define CSN2_WR(src)                                (((u32)(src)) & 0x0000000f)
#define CSN2_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_bank0_nand_ctrl0	*/
/*	 Fields SPARE_OFFSET	 */
#define SPARE_OFFSET0_WIDTH                                                  16
#define SPARE_OFFSET0_SHIFT                                                  16
#define SPARE_OFFSET0_MASK                                           0xffff0000
#define SPARE_OFFSET0_RD(src)                        (((src) & 0xffff0000)>>16)
#define SPARE_OFFSET0_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define SPARE_OFFSET0_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields FORCE_SPARE_OFFSET	 */
#define FORCE_SPARE_OFFSET0_WIDTH                                             1
#define FORCE_SPARE_OFFSET0_SHIFT                                             9
#define FORCE_SPARE_OFFSET0_MASK                                     0x00000200
#define FORCE_SPARE_OFFSET0_RD(src)                   (((src) & 0x00000200)>>9)
#define FORCE_SPARE_OFFSET0_WR(src)              (((u32)(src)<<9) & 0x00000200)
#define FORCE_SPARE_OFFSET0_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ECC_Algorithm	 */
#define ECC_ALGORITHM0_WIDTH                                                  1
#define ECC_ALGORITHM0_SHIFT                                                  8
#define ECC_ALGORITHM0_MASK                                          0x00000100
#define ECC_ALGORITHM0_RD(src)                        (((src) & 0x00000100)>>8)
#define ECC_ALGORITHM0_WR(src)                   (((u32)(src)<<8) & 0x00000100)
#define ECC_ALGORITHM0_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ECC_ON_OFF	 */
#define ECC_ON_OFF0_WIDTH                                                     1
#define ECC_ON_OFF0_SHIFT                                                     7
#define ECC_ON_OFF0_MASK                                             0x00000080
#define ECC_ON_OFF0_RD(src)                           (((src) & 0x00000080)>>7)
#define ECC_ON_OFF0_WR(src)                      (((u32)(src)<<7) & 0x00000080)
#define ECC_ON_OFF0_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))

/*	Register gfc_bank0_nand_ctrl1	*/

/*	Register gfc_bank0_nand_ctrl2	*/

/*	Register gfc_bank0_nand_bch	*/
/*	 Fields bch_k	 */
#define BCH_K_WIDTH                                                           3
#define BCH_K_SHIFT                                                          20
#define BCH_K_MASK                                                   0x00700000
#define BCH_K_RD(src)                                (((src) & 0x00700000)>>20)
#define BCH_K_WR(src)                           (((u32)(src)<<20) & 0x00700000)
#define BCH_K_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields bch_t	 */
#define BCH_T_WIDTH                                                           4
#define BCH_T_SHIFT                                                          16
#define BCH_T_MASK                                                   0x000f0000
#define BCH_T_RD(src)                                (((src) & 0x000f0000)>>16)
#define BCH_T_WR(src)                           (((u32)(src)<<16) & 0x000f0000)
#define BCH_T_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields bch_n	 */
#define BCH_N_WIDTH                                                          16
#define BCH_N_SHIFT                                                           0
#define BCH_N_MASK                                                   0x0000ffff
#define BCH_N_RD(src)                                    (((src) & 0x0000ffff))
#define BCH_N_WR(src)                               (((u32)(src)) & 0x0000ffff)
#define BCH_N_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank0_dma_ctrl1	*/
/*	 Fields dma_data_size	 */
#define DMA_DATA_SIZE1_WIDTH                                                 24
#define DMA_DATA_SIZE1_SHIFT                                                  0
#define DMA_DATA_SIZE1_MASK                                          0x00ffffff
#define DMA_DATA_SIZE1_RD(src)                           (((src) & 0x00ffffff))
#define DMA_DATA_SIZE1_WR(src)                      (((u32)(src)) & 0x00ffffff)
#define DMA_DATA_SIZE1_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_bank0_nand_ctrl3	*/
/*	 Fields page_size	 */
#define PAGE_SIZE3_WIDTH                                                     16
#define PAGE_SIZE3_SHIFT                                                      0
#define PAGE_SIZE3_MASK                                              0x0000ffff
#define PAGE_SIZE3_RD(src)                               (((src) & 0x0000ffff))
#define PAGE_SIZE3_WR(src)                          (((u32)(src)) & 0x0000ffff)
#define PAGE_SIZE3_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank0_nand_ctrl4	*/
/*	 Fields device_size	 */
#define DEVICE_SIZE4_WIDTH                                                   16
#define DEVICE_SIZE4_SHIFT                                                   16
#define DEVICE_SIZE4_MASK                                            0xffff0000
#define DEVICE_SIZE4_RD(src)                         (((src) & 0xffff0000)>>16)
#define DEVICE_SIZE4_WR(src)                    (((u32)(src)<<16) & 0xffff0000)
#define DEVICE_SIZE4_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields block_size	 */
#define BLOCK_SIZE4_WIDTH                                                    16
#define BLOCK_SIZE4_SHIFT                                                     0
#define BLOCK_SIZE4_MASK                                             0x0000ffff
#define BLOCK_SIZE4_RD(src)                              (((src) & 0x0000ffff))
#define BLOCK_SIZE4_WR(src)                         (((u32)(src)) & 0x0000ffff)
#define BLOCK_SIZE4_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank0_nand_timing0	*/
/*	 Fields t_adl	 */
#define T_ADL0_WIDTH                                                          8
#define T_ADL0_SHIFT                                                         24
#define T_ADL0_MASK                                                  0xff000000
#define T_ADL0_RD(src)                               (((src) & 0xff000000)>>24)
#define T_ADL0_WR(src)                          (((u32)(src)<<24) & 0xff000000)
#define T_ADL0_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_wb	 */
#define T_WB0_WIDTH                                                           8
#define T_WB0_SHIFT                                                          16
#define T_WB0_MASK                                                   0x00ff0000
#define T_WB0_RD(src)                                (((src) & 0x00ff0000)>>16)
#define T_WB0_WR(src)                           (((u32)(src)<<16) & 0x00ff0000)
#define T_WB0_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_rhw	 */
#define T_RHW0_WIDTH                                                          8
#define T_RHW0_SHIFT                                                          8
#define T_RHW0_MASK                                                  0x0000ff00
#define T_RHW0_RD(src)                                (((src) & 0x0000ff00)>>8)
#define T_RHW0_WR(src)                           (((u32)(src)<<8) & 0x0000ff00)
#define T_RHW0_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_ccs	 */
#define T_CCS0_WIDTH                                                          8
#define T_CCS0_SHIFT                                                          0
#define T_CCS0_MASK                                                  0x000000ff
#define T_CCS0_RD(src)                                   (((src) & 0x000000ff))
#define T_CCS0_WR(src)                              (((u32)(src)) & 0x000000ff)
#define T_CCS0_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank0_nand_timing1	*/
/*	 Fields t_alh_clh_ch	 */
#define T_ALH_CLH_CH1_WIDTH                                                   8
#define T_ALH_CLH_CH1_SHIFT                                                  24
#define T_ALH_CLH_CH1_MASK                                           0xff000000
#define T_ALH_CLH_CH1_RD(src)                        (((src) & 0xff000000)>>24)
#define T_ALH_CLH_CH1_WR(src)                   (((u32)(src)<<24) & 0xff000000)
#define T_ALH_CLH_CH1_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_als_cls_cs	 */
#define T_ALS_CLS_CS1_WIDTH                                                   8
#define T_ALS_CLS_CS1_SHIFT                                                  16
#define T_ALS_CLS_CS1_MASK                                           0x00ff0000
#define T_ALS_CLS_CS1_RD(src)                        (((src) & 0x00ff0000)>>16)
#define T_ALS_CLS_CS1_WR(src)                   (((u32)(src)<<16) & 0x00ff0000)
#define T_ALS_CLS_CS1_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_ds_wp	 */
#define T_DS_WP1_WIDTH                                                        8
#define T_DS_WP1_SHIFT                                                        8
#define T_DS_WP1_MASK                                                0x0000ff00
#define T_DS_WP1_RD(src)                              (((src) & 0x0000ff00)>>8)
#define T_DS_WP1_WR(src)                         (((u32)(src)<<8) & 0x0000ff00)
#define T_DS_WP1_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_dh_wh	 */
#define T_DH_WH1_WIDTH                                                        8
#define T_DH_WH1_SHIFT                                                        0
#define T_DH_WH1_MASK                                                0x000000ff
#define T_DH_WH1_RD(src)                                 (((src) & 0x000000ff))
#define T_DH_WH1_WR(src)                            (((u32)(src)) & 0x000000ff)
#define T_DH_WH1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank0_nand_timing2	*/
/*	 Fields t_ar_clr_whr_ir	 */
#define T_AR_CLR_WHR_IR2_WIDTH                                                8
#define T_AR_CLR_WHR_IR2_SHIFT                                               24
#define T_AR_CLR_WHR_IR2_MASK                                        0xff000000
#define T_AR_CLR_WHR_IR2_RD(src)                     (((src) & 0xff000000)>>24)
#define T_AR_CLR_WHR_IR2_WR(src)                (((u32)(src)<<24) & 0xff000000)
#define T_AR_CLR_WHR_IR2_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_rr	 */
#define T_RR2_WIDTH                                                           8
#define T_RR2_SHIFT                                                          16
#define T_RR2_MASK                                                   0x00ff0000
#define T_RR2_RD(src)                                (((src) & 0x00ff0000)>>16)
#define T_RR2_WR(src)                           (((u32)(src)<<16) & 0x00ff0000)
#define T_RR2_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_reh	 */
#define T_REH2_WIDTH                                                          8
#define T_REH2_SHIFT                                                          8
#define T_REH2_MASK                                                  0x0000ff00
#define T_REH2_RD(src)                                (((src) & 0x0000ff00)>>8)
#define T_REH2_WR(src)                           (((u32)(src)<<8) & 0x0000ff00)
#define T_REH2_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_rp	 */
#define T_RP2_WIDTH                                                           8
#define T_RP2_SHIFT                                                           0
#define T_RP2_MASK                                                   0x000000ff
#define T_RP2_RD(src)                                    (((src) & 0x000000ff))
#define T_RP2_WR(src)                               (((u32)(src)) & 0x000000ff)
#define T_RP2_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank0_nand_timing3	*/
/*	 Fields t_ww	 */
#define T_WW3_WIDTH                                                           8
#define T_WW3_SHIFT                                                          16
#define T_WW3_MASK                                                   0x00ff0000
#define T_WW3_RD(src)                                (((src) & 0x00ff0000)>>16)
#define T_WW3_WR(src)                           (((u32)(src)<<16) & 0x00ff0000)
#define T_WW3_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_chz	 */
#define T_CHZ3_WIDTH                                                          8
#define T_CHZ3_SHIFT                                                          8
#define T_CHZ3_MASK                                                  0x0000ff00
#define T_CHZ3_RD(src)                                (((src) & 0x0000ff00)>>8)
#define T_CHZ3_WR(src)                           (((u32)(src)<<8) & 0x0000ff00)
#define T_CHZ3_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_cea	 */
#define T_CEA3_WIDTH                                                          8
#define T_CEA3_SHIFT                                                          0
#define T_CEA3_MASK                                                  0x000000ff
#define T_CEA3_RD(src)                                   (((src) & 0x000000ff))
#define T_CEA3_WR(src)                              (((u32)(src)) & 0x000000ff)
#define T_CEA3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank0_nand_cor_err	*/
/*	 Fields counter	 */
#define COUNTER_F1_WIDTH                                                     32
#define COUNTER_F1_SHIFT                                                      0
#define COUNTER_F1_MASK                                              0xffffffff
#define COUNTER_F1_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank0_nand_uncor_err	*/
/*	 Fields counter	 */
#define COUNTER_F2_WIDTH                                                     32
#define COUNTER_F2_SHIFT                                                      0
#define COUNTER_F2_MASK                                              0xffffffff
#define COUNTER_F2_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_ctrl0	*/
/*	 Fields nand_wp_n	 */
#define NAND_WP_N0_F1_WIDTH                                                   1
#define NAND_WP_N0_F1_SHIFT                                                   8
#define NAND_WP_N0_F1_MASK                                           0x00000100
#define NAND_WP_N0_F1_RD(src)                         (((src) & 0x00000100)>>8)
#define NAND_WP_N0_F1_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define NAND_WP_N0_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bus_width	 */
#define BUS_WIDTH0_F1_WIDTH                                                   2
#define BUS_WIDTH0_F1_SHIFT                                                   6
#define BUS_WIDTH0_F1_MASK                                           0x000000c0
#define BUS_WIDTH0_F1_RD(src)                         (((src) & 0x000000c0)>>6)
#define BUS_WIDTH0_F1_WR(src)                    (((u32)(src)<<6) & 0x000000c0)
#define BUS_WIDTH0_F1_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields bus_usage	 */
#define BUS_USAGE0_F1_WIDTH                                                   2
#define BUS_USAGE0_F1_SHIFT                                                   4
#define BUS_USAGE0_F1_MASK                                           0x00000030
#define BUS_USAGE0_F1_RD(src)                         (((src) & 0x00000030)>>4)
#define BUS_USAGE0_F1_WR(src)                    (((u32)(src)<<4) & 0x00000030)
#define BUS_USAGE0_F1_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields bank_type	 */
#define BANK_TYPE0_F1_WIDTH                                                   3
#define BANK_TYPE0_F1_SHIFT                                                   1
#define BANK_TYPE0_F1_MASK                                           0x0000000e
#define BANK_TYPE0_F1_RD(src)                         (((src) & 0x0000000e)>>1)
#define BANK_TYPE0_F1_WR(src)                    (((u32)(src)<<1) & 0x0000000e)
#define BANK_TYPE0_F1_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields bank_valid	 */
#define BANK_VALID0_F1_WIDTH                                                  1
#define BANK_VALID0_F1_SHIFT                                                  0
#define BANK_VALID0_F1_MASK                                          0x00000001
#define BANK_VALID0_F1_RD(src)                           (((src) & 0x00000001))
#define BANK_VALID0_F1_WR(src)                      (((u32)(src)) & 0x00000001)
#define BANK_VALID0_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank1_start_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F3_WIDTH                                                14
#define REGSPEC_ADDR_F3_SHIFT                                                 0
#define REGSPEC_ADDR_F3_MASK                                         0x00003fff
#define REGSPEC_ADDR_F3_RD(src)                          (((src) & 0x00003fff))
#define REGSPEC_ADDR_F3_WR(src)                     (((u32)(src)) & 0x00003fff)
#define REGSPEC_ADDR_F3_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register gfc_bank1_end_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F4_WIDTH                                                15
#define REGSPEC_ADDR_F4_SHIFT                                                 0
#define REGSPEC_ADDR_F4_MASK                                         0x00007fff
#define REGSPEC_ADDR_F4_RD(src)                          (((src) & 0x00007fff))
#define REGSPEC_ADDR_F4_WR(src)                     (((u32)(src)) & 0x00007fff)
#define REGSPEC_ADDR_F4_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register gfc_bank1_base_add	*/
/*	 Fields bank_base_add	 */
#define BANK_BASE_ADD_F1_WIDTH                                               32
#define BANK_BASE_ADD_F1_SHIFT                                                0
#define BANK_BASE_ADD_F1_MASK                                        0xffffffff
#define BANK_BASE_ADD_F1_RD(src)                         (((src) & 0xffffffff))
#define BANK_BASE_ADD_F1_WR(src)                    (((u32)(src)) & 0xffffffff)
#define BANK_BASE_ADD_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_dma_ctrl0	*/
/*	 Fields complNum_4_int	 */
#define COMPLNUM_4_INT0_F1_WIDTH                                              3
#define COMPLNUM_4_INT0_F1_SHIFT                                             10
#define COMPLNUM_4_INT0_F1_MASK                                      0x00001c00
#define COMPLNUM_4_INT0_F1_RD(src)                   (((src) & 0x00001c00)>>10)
#define COMPLNUM_4_INT0_F1_WR(src)              (((u32)(src)<<10) & 0x00001c00)
#define COMPLNUM_4_INT0_F1_SET(dst,src) \
                      (((dst) & ~0x00001c00) | (((u32)(src)<<10) & 0x00001c00))
/*	 Fields dma_cmd_code	 */
#define DMA_CMD_CODE0_F1_WIDTH                                                3
#define DMA_CMD_CODE0_F1_SHIFT                                                7
#define DMA_CMD_CODE0_F1_MASK                                        0x00000380
#define DMA_CMD_CODE0_F1_RD(src)                      (((src) & 0x00000380)>>7)
#define DMA_CMD_CODE0_F1_WR(src)                 (((u32)(src)<<7) & 0x00000380)
#define DMA_CMD_CODE0_F1_SET(dst,src) \
                       (((dst) & ~0x00000380) | (((u32)(src)<<7) & 0x00000380))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID0_F1_WIDTH                                                  2
#define DMA_CMD_ID0_F1_SHIFT                                                  3
#define DMA_CMD_ID0_F1_MASK                                          0x00000018
#define DMA_CMD_ID0_F1_RD(src)                        (((src) & 0x00000018)>>3)
#define DMA_CMD_ID0_F1_WR(src)                   (((u32)(src)<<3) & 0x00000018)
#define DMA_CMD_ID0_F1_SET(dst,src) \
                       (((dst) & ~0x00000018) | (((u32)(src)<<3) & 0x00000018))
/*	 Fields dma_cmd_pop	 */
#define DMA_CMD_POP0_F1_WIDTH                                                 1
#define DMA_CMD_POP0_F1_SHIFT                                                 2
#define DMA_CMD_POP0_F1_MASK                                         0x00000004
#define DMA_CMD_POP0_F1_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_CMD_POP0_F1_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_CMD_POP0_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dma_cmd_push	 */
#define DMA_CMD_PUSH0_F1_WIDTH                                                1
#define DMA_CMD_PUSH0_F1_SHIFT                                                1
#define DMA_CMD_PUSH0_F1_MASK                                        0x00000002
#define DMA_CMD_PUSH0_F1_RD(src)                      (((src) & 0x00000002)>>1)
#define DMA_CMD_PUSH0_F1_WR(src)                 (((u32)(src)<<1) & 0x00000002)
#define DMA_CMD_PUSH0_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dma_cmd_valid	 */
#define DMA_CMD_VALID0_F1_WIDTH                                               1
#define DMA_CMD_VALID0_F1_SHIFT                                               0
#define DMA_CMD_VALID0_F1_MASK                                       0x00000001
#define DMA_CMD_VALID0_F1_RD(src)                        (((src) & 0x00000001))
#define DMA_CMD_VALID0_F1_WR(src)                   (((u32)(src)) & 0x00000001)
#define DMA_CMD_VALID0_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank1_dma_start_add0	*/
/*	 Fields dma_start_add0	 */
#define DMA_START_ADD00_F1_WIDTH                                             32
#define DMA_START_ADD00_F1_SHIFT                                              0
#define DMA_START_ADD00_F1_MASK                                      0xffffffff
#define DMA_START_ADD00_F1_RD(src)                       (((src) & 0xffffffff))
#define DMA_START_ADD00_F1_WR(src)                  (((u32)(src)) & 0xffffffff)
#define DMA_START_ADD00_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_dma_start_add1	*/
/*	 Fields dma_start_add1	 */
#define DMA_START_ADD11_F1_WIDTH                                             10
#define DMA_START_ADD11_F1_SHIFT                                              0
#define DMA_START_ADD11_F1_MASK                                      0x000003ff
#define DMA_START_ADD11_F1_RD(src)                       (((src) & 0x000003ff))
#define DMA_START_ADD11_F1_WR(src)                  (((u32)(src)) & 0x000003ff)
#define DMA_START_ADD11_F1_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank1_dma_des_add0	*/
/*	 Fields dma_des_add0	 */
#define DMA_DES_ADD00_F1_WIDTH                                               32
#define DMA_DES_ADD00_F1_SHIFT                                                0
#define DMA_DES_ADD00_F1_MASK                                        0xffffffff
#define DMA_DES_ADD00_F1_RD(src)                         (((src) & 0xffffffff))
#define DMA_DES_ADD00_F1_WR(src)                    (((u32)(src)) & 0xffffffff)
#define DMA_DES_ADD00_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_dma_des_add1	*/
/*	 Fields dma_des_add1	 */
#define DMA_DES_ADD11_F1_WIDTH                                               10
#define DMA_DES_ADD11_F1_SHIFT                                                0
#define DMA_DES_ADD11_F1_MASK                                        0x000003ff
#define DMA_DES_ADD11_F1_RD(src)                         (((src) & 0x000003ff))
#define DMA_DES_ADD11_F1_WR(src)                    (((u32)(src)) & 0x000003ff)
#define DMA_DES_ADD11_F1_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank1_dma_status	*/
/*	 Fields bits_corrected_ecc	 */
#define BITS_CORRECTED_ECC_F1_WIDTH                                           4
#define BITS_CORRECTED_ECC_F1_SHIFT                                          14
#define BITS_CORRECTED_ECC_F1_MASK                                   0x0003c000
#define BITS_CORRECTED_ECC_F1_RD(src)                (((src) & 0x0003c000)>>14)
#define BITS_CORRECTED_ECC_F1_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields dma_err	 */
#define DMA_ERR_F1_WIDTH                                                      3
#define DMA_ERR_F1_SHIFT                                                      9
#define DMA_ERR_F1_MASK                                              0x00000e00
#define DMA_ERR_F1_RD(src)                            (((src) & 0x00000e00)>>9)
#define DMA_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000e00) | (((u32)(src)<<9) & 0x00000e00))
/*	 Fields dma_cmpl_status	 */
#define DMA_CMPL_STATUS_F1_WIDTH                                              2
#define DMA_CMPL_STATUS_F1_SHIFT                                              6
#define DMA_CMPL_STATUS_F1_MASK                                      0x000000c0
#define DMA_CMPL_STATUS_F1_RD(src)                    (((src) & 0x000000c0)>>6)
#define DMA_CMPL_STATUS_F1_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID_F1_WIDTH                                                   2
#define DMA_CMD_ID_F1_SHIFT                                                   1
#define DMA_CMD_ID_F1_MASK                                           0x00000006
#define DMA_CMD_ID_F1_RD(src)                         (((src) & 0x00000006)>>1)
#define DMA_CMD_ID_F1_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields dma_cmpl_valid	 */
#define DMA_CMPL_VALID_F1_WIDTH                                               1
#define DMA_CMPL_VALID_F1_SHIFT                                               0
#define DMA_CMPL_VALID_F1_MASK                                       0x00000001
#define DMA_CMPL_VALID_F1_RD(src)                        (((src) & 0x00000001))
#define DMA_CMPL_VALID_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank1_dma_eccerr0_add_col	*/
/*	 Fields dma_eccerr0_add_col	 */
#define DMA_ECCERR0_ADD_COL_F1_WIDTH                                         32
#define DMA_ECCERR0_ADD_COL_F1_SHIFT                                          0
#define DMA_ECCERR0_ADD_COL_F1_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_COL_F1_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_COL_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_dma_eccerr0_add_row	*/
/*	 Fields dma_eccerr0_add_row	 */
#define DMA_ECCERR0_ADD_ROW_F1_WIDTH                                         32
#define DMA_ECCERR0_ADD_ROW_F1_SHIFT                                          0
#define DMA_ECCERR0_ADD_ROW_F1_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_ROW_F1_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_ROW_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_dma_eccerr1_add_col	*/
/*	 Fields dma_eccerr1_add_col	 */
#define DMA_ECCERR1_ADD_COL_F1_WIDTH                                         32
#define DMA_ECCERR1_ADD_COL_F1_SHIFT                                          0
#define DMA_ECCERR1_ADD_COL_F1_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_COL_F1_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_COL_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_dma_eccerr1_add_row	*/
/*	 Fields dma_eccerr1_add_row	 */
#define DMA_ECCERR1_ADD_ROW_F1_WIDTH                                         32
#define DMA_ECCERR1_ADD_ROW_F1_SHIFT                                          0
#define DMA_ECCERR1_ADD_ROW_F1_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_ROW_F1_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_ROW_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_INT	*/
/*	 Fields nandpio_device_protection_err	 */
#define NANDPIO_DEVICE_PROTECTION_ERR_F1_WIDTH                                1
#define NANDPIO_DEVICE_PROTECTION_ERR_F1_SHIFT                               11
#define NANDPIO_DEVICE_PROTECTION_ERR_F1_MASK                        0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERR_F1_RD(src)     (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERR_F1_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields norp_device_protection_err	 */
#define NORP_DEVICE_PROTECTION_ERR_F1_WIDTH                                   1
#define NORP_DEVICE_PROTECTION_ERR_F1_SHIFT                                  10
#define NORP_DEVICE_PROTECTION_ERR_F1_MASK                           0x00000400
#define NORP_DEVICE_PROTECTION_ERR_F1_RD(src)        (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERR_F1_WR(src)   (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields dma_cmd_override_err	 */
#define DMA_CMD_OVERRIDE_ERR_F1_WIDTH                                         1
#define DMA_CMD_OVERRIDE_ERR_F1_SHIFT                                         9
#define DMA_CMD_OVERRIDE_ERR_F1_MASK                                 0x00000200
#define DMA_CMD_OVERRIDE_ERR_F1_RD(src)               (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERR_F1_WR(src)          (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields device_protection_err	 */
#define DEVICE_PROTECTION_ERR_F1_WIDTH                                        1
#define DEVICE_PROTECTION_ERR_F1_SHIFT                                        8
#define DEVICE_PROTECTION_ERR_F1_MASK                                0x00000100
#define DEVICE_PROTECTION_ERR_F1_RD(src)              (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERR_F1_WR(src)         (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields transaction_timeout	 */
#define TRANSACTION_TIMEOUT_F1_WIDTH                                          1
#define TRANSACTION_TIMEOUT_F1_SHIFT                                          7
#define TRANSACTION_TIMEOUT_F1_MASK                                  0x00000080
#define TRANSACTION_TIMEOUT_F1_RD(src)                (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUT_F1_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUT_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields parity_err	 */
#define PARITY_ERR_F1_WIDTH                                                   1
#define PARITY_ERR_F1_SHIFT                                                   6
#define PARITY_ERR_F1_MASK                                           0x00000040
#define PARITY_ERR_F1_RD(src)                         (((src) & 0x00000040)>>6)
#define PARITY_ERR_F1_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ecc_err_single	 */
#define ECC_ERR_SINGLE_F1_WIDTH                                               1
#define ECC_ERR_SINGLE_F1_SHIFT                                               5
#define ECC_ERR_SINGLE_F1_MASK                                       0x00000020
#define ECC_ERR_SINGLE_F1_RD(src)                     (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLE_F1_WR(src)                (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLE_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ecc_err_multiple	 */
#define ECC_ERR_MULTIPLE_F1_WIDTH                                             1
#define ECC_ERR_MULTIPLE_F1_SHIFT                                             4
#define ECC_ERR_MULTIPLE_F1_MASK                                     0x00000010
#define ECC_ERR_MULTIPLE_F1_RD(src)                   (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLE_F1_WR(src)              (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLE_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields dma_done	 */
#define DMA_DONE_F1_WIDTH                                                     1
#define DMA_DONE_F1_SHIFT                                                     2
#define DMA_DONE_F1_MASK                                             0x00000004
#define DMA_DONE_F1_RD(src)                           (((src) & 0x00000004)>>2)
#define DMA_DONE_F1_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define DMA_DONE_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank1_interruptMask	*/
/*    Mask Register Fields nandpio_device_protection_errMask    */
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F1_WIDTH                            1
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F1_SHIFT                           11
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F1_MASK                    0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F1_RD(src) \
                                                    (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F1_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields norp_device_protection_errMask    */
#define NORP_DEVICE_PROTECTION_ERRMASK_F1_WIDTH                               1
#define NORP_DEVICE_PROTECTION_ERRMASK_F1_SHIFT                              10
#define NORP_DEVICE_PROTECTION_ERRMASK_F1_MASK                       0x00000400
#define NORP_DEVICE_PROTECTION_ERRMASK_F1_RD(src)    (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERRMASK_F1_WR(src) \
                                                (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERRMASK_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields dma_cmd_override_errMask    */
#define DMA_CMD_OVERRIDE_ERRMASK_F1_WIDTH                                     1
#define DMA_CMD_OVERRIDE_ERRMASK_F1_SHIFT                                     9
#define DMA_CMD_OVERRIDE_ERRMASK_F1_MASK                             0x00000200
#define DMA_CMD_OVERRIDE_ERRMASK_F1_RD(src)           (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERRMASK_F1_WR(src)      (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERRMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields device_protection_errMask    */
#define DEVICE_PROTECTION_ERRMASK_F1_WIDTH                                    1
#define DEVICE_PROTECTION_ERRMASK_F1_SHIFT                                    8
#define DEVICE_PROTECTION_ERRMASK_F1_MASK                            0x00000100
#define DEVICE_PROTECTION_ERRMASK_F1_RD(src)          (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERRMASK_F1_WR(src)     (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERRMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields transaction_timeoutMask    */
#define TRANSACTION_TIMEOUTMASK_F1_WIDTH                                      1
#define TRANSACTION_TIMEOUTMASK_F1_SHIFT                                      7
#define TRANSACTION_TIMEOUTMASK_F1_MASK                              0x00000080
#define TRANSACTION_TIMEOUTMASK_F1_RD(src)            (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUTMASK_F1_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUTMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields parity_errMask    */
#define PARITY_ERRMASK_F1_WIDTH                                               1
#define PARITY_ERRMASK_F1_SHIFT                                               6
#define PARITY_ERRMASK_F1_MASK                                       0x00000040
#define PARITY_ERRMASK_F1_RD(src)                     (((src) & 0x00000040)>>6)
#define PARITY_ERRMASK_F1_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERRMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ecc_err_singleMask    */
#define ECC_ERR_SINGLEMASK_F1_WIDTH                                           1
#define ECC_ERR_SINGLEMASK_F1_SHIFT                                           5
#define ECC_ERR_SINGLEMASK_F1_MASK                                   0x00000020
#define ECC_ERR_SINGLEMASK_F1_RD(src)                 (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLEMASK_F1_WR(src)            (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLEMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ecc_err_multipleMask    */
#define ECC_ERR_MULTIPLEMASK_F1_WIDTH                                         1
#define ECC_ERR_MULTIPLEMASK_F1_SHIFT                                         4
#define ECC_ERR_MULTIPLEMASK_F1_MASK                                 0x00000010
#define ECC_ERR_MULTIPLEMASK_F1_RD(src)               (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLEMASK_F1_WR(src)          (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLEMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields dma_doneMask    */
#define DMA_DONEMASK_F1_WIDTH                                                 1
#define DMA_DONEMASK_F1_SHIFT                                                 2
#define DMA_DONEMASK_F1_MASK                                         0x00000004
#define DMA_DONEMASK_F1_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_DONEMASK_F1_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_DONEMASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank1_sram_ctrl0	*/
/*	 Fields rtc	 */
#define REGSPEC_RTC0_F1_WIDTH                                                 3
#define REGSPEC_RTC0_F1_SHIFT                                                12
#define REGSPEC_RTC0_F1_MASK                                         0x00007000
#define REGSPEC_RTC0_F1_RD(src)                      (((src) & 0x00007000)>>12)
#define REGSPEC_RTC0_F1_WR(src)                 (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_RTC0_F1_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields muxen	 */
#define MUXEN0_F1_WIDTH                                                       1
#define MUXEN0_F1_SHIFT                                                      10
#define MUXEN0_F1_MASK                                               0x00000400
#define MUXEN0_F1_RD(src)                            (((src) & 0x00000400)>>10)
#define MUXEN0_F1_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define MUXEN0_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rdy_timeout_cnt	 */
#define RDY_TIMEOUT_CNT0_F1_WIDTH                                             3
#define RDY_TIMEOUT_CNT0_F1_SHIFT                                             2
#define RDY_TIMEOUT_CNT0_F1_MASK                                     0x0000001c
#define RDY_TIMEOUT_CNT0_F1_RD(src)                   (((src) & 0x0000001c)>>2)
#define RDY_TIMEOUT_CNT0_F1_WR(src)              (((u32)(src)<<2) & 0x0000001c)
#define RDY_TIMEOUT_CNT0_F1_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields ptd	 */
#define PTD0_F1_WIDTH                                                         1
#define PTD0_F1_SHIFT                                                         1
#define PTD0_F1_MASK                                                 0x00000002
#define PTD0_F1_RD(src)                               (((src) & 0x00000002)>>1)
#define PTD0_F1_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PTD0_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields le	 */
#define LE0_F1_WIDTH                                                          1
#define LE0_F1_SHIFT                                                          0
#define LE0_F1_MASK                                                  0x00000001
#define LE0_F1_RD(src)                                   (((src) & 0x00000001))
#define LE0_F1_WR(src)                              (((u32)(src)) & 0x00000001)
#define LE0_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank1_sram_nor_ctrl1	*/
/*	 Fields BME	 */
#define BME1_F1_WIDTH                                                         1
#define BME1_F1_SHIFT                                                        31
#define BME1_F1_MASK                                                 0x80000000
#define BME1_F1_RD(src)                              (((src) & 0x80000000)>>31)
#define BME1_F1_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define BME1_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields OEO	 */
#define OEO1_F1_WIDTH                                                         1
#define OEO1_F1_SHIFT                                                        30
#define OEO1_F1_MASK                                                 0x40000000
#define OEO1_F1_RD(src)                              (((src) & 0x40000000)>>30)
#define OEO1_F1_WR(src)                         (((u32)(src)<<30) & 0x40000000)
#define OEO1_F1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields BWT	 */
#define BWT1_F1_WIDTH                                                         5
#define BWT1_F1_SHIFT                                                        20
#define BWT1_F1_MASK                                                 0x01f00000
#define BWT1_F1_RD(src)                              (((src) & 0x01f00000)>>20)
#define BWT1_F1_WR(src)                         (((u32)(src)<<20) & 0x01f00000)
#define BWT1_F1_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields FWT	 */
#define FWT1_F1_WIDTH                                                         7
#define FWT1_F1_SHIFT                                                        12
#define FWT1_F1_MASK                                                 0x0007f000
#define FWT1_F1_RD(src)                              (((src) & 0x0007f000)>>12)
#define FWT1_F1_WR(src)                         (((u32)(src)<<12) & 0x0007f000)
#define FWT1_F1_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields TWT	 */
#define TWT1_F1_WIDTH                                                        10
#define TWT1_F1_SHIFT                                                         0
#define TWT1_F1_MASK                                                 0x000003ff
#define TWT1_F1_RD(src)                                  (((src) & 0x000003ff))
#define TWT1_F1_WR(src)                             (((u32)(src)) & 0x000003ff)
#define TWT1_F1_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank1_sram_nor_ctrl2	*/
/*	 Fields ALN	 */
#define ALN2_F1_WIDTH                                                         4
#define ALN2_F1_SHIFT                                                        28
#define ALN2_F1_MASK                                                 0xf0000000
#define ALN2_F1_RD(src)                              (((src) & 0xf0000000)>>28)
#define ALN2_F1_WR(src)                         (((u32)(src)<<28) & 0xf0000000)
#define ALN2_F1_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields PEN	 */
#define PEN2_F1_WIDTH                                                         1
#define PEN2_F1_SHIFT                                                        27
#define PEN2_F1_MASK                                                 0x08000000
#define PEN2_F1_RD(src)                              (((src) & 0x08000000)>>27)
#define PEN2_F1_WR(src)                         (((u32)(src)<<27) & 0x08000000)
#define PEN2_F1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields BEM	 */
#define BEM2_F1_WIDTH                                                         1
#define BEM2_F1_SHIFT                                                        26
#define BEM2_F1_MASK                                                 0x04000000
#define BEM2_F1_RD(src)                              (((src) & 0x04000000)>>26)
#define BEM2_F1_WR(src)                         (((u32)(src)<<26) & 0x04000000)
#define BEM2_F1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SOR	 */
#define SOR2_F1_WIDTH                                                         1
#define SOR2_F1_SHIFT                                                        25
#define SOR2_F1_MASK                                                 0x02000000
#define SOR2_F1_RD(src)                              (((src) & 0x02000000)>>25)
#define SOR2_F1_WR(src)                         (((u32)(src)<<25) & 0x02000000)
#define SOR2_F1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RE	 */
#define RE2_F1_WIDTH                                                          1
#define RE2_F1_SHIFT                                                         24
#define RE2_F1_MASK                                                  0x01000000
#define RE2_F1_RD(src)                               (((src) & 0x01000000)>>24)
#define RE2_F1_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define RE2_F1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields TH	 */
#define TH2_F1_WIDTH                                                          5
#define TH2_F1_SHIFT                                                         16
#define TH2_F1_MASK                                                  0x001f0000
#define TH2_F1_RD(src)                               (((src) & 0x001f0000)>>16)
#define TH2_F1_WR(src)                          (((u32)(src)<<16) & 0x001f0000)
#define TH2_F1_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WBF	 */
#define WBF2_F1_WIDTH                                                         4
#define WBF2_F1_SHIFT                                                        12
#define WBF2_F1_MASK                                                 0x0000f000
#define WBF2_F1_RD(src)                              (((src) & 0x0000f000)>>12)
#define WBF2_F1_WR(src)                         (((u32)(src)<<12) & 0x0000f000)
#define WBF2_F1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WBN	 */
#define WBN2_F1_WIDTH                                                         4
#define WBN2_F1_SHIFT                                                         8
#define WBN2_F1_MASK                                                 0x00000f00
#define WBN2_F1_RD(src)                               (((src) & 0x00000f00)>>8)
#define WBN2_F1_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define WBN2_F1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields OEN	 */
#define OEN2_F1_WIDTH                                                         4
#define OEN2_F1_SHIFT                                                         4
#define OEN2_F1_MASK                                                 0x000000f0
#define OEN2_F1_RD(src)                               (((src) & 0x000000f0)>>4)
#define OEN2_F1_WR(src)                          (((u32)(src)<<4) & 0x000000f0)
#define OEN2_F1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields CSN	 */
#define CSN2_F1_WIDTH                                                         4
#define CSN2_F1_SHIFT                                                         0
#define CSN2_F1_MASK                                                 0x0000000f
#define CSN2_F1_RD(src)                                  (((src) & 0x0000000f))
#define CSN2_F1_WR(src)                             (((u32)(src)) & 0x0000000f)
#define CSN2_F1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_bank1_nand_ctrl0	*/
/*	 Fields SPARE_OFFSET	 */
#define SPARE_OFFSET0_F1_WIDTH                                               16
#define SPARE_OFFSET0_F1_SHIFT                                               16
#define SPARE_OFFSET0_F1_MASK                                        0xffff0000
#define SPARE_OFFSET0_F1_RD(src)                     (((src) & 0xffff0000)>>16)
#define SPARE_OFFSET0_F1_WR(src)                (((u32)(src)<<16) & 0xffff0000)
#define SPARE_OFFSET0_F1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields FORCE_SPARE_OFFSET	 */
#define FORCE_SPARE_OFFSET0_F1_WIDTH                                          1
#define FORCE_SPARE_OFFSET0_F1_SHIFT                                          9
#define FORCE_SPARE_OFFSET0_F1_MASK                                  0x00000200
#define FORCE_SPARE_OFFSET0_F1_RD(src)                (((src) & 0x00000200)>>9)
#define FORCE_SPARE_OFFSET0_F1_WR(src)           (((u32)(src)<<9) & 0x00000200)
#define FORCE_SPARE_OFFSET0_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ECC_Algorithm	 */
#define ECC_ALGORITHM0_F1_WIDTH                                               1
#define ECC_ALGORITHM0_F1_SHIFT                                               8
#define ECC_ALGORITHM0_F1_MASK                                       0x00000100
#define ECC_ALGORITHM0_F1_RD(src)                     (((src) & 0x00000100)>>8)
#define ECC_ALGORITHM0_F1_WR(src)                (((u32)(src)<<8) & 0x00000100)
#define ECC_ALGORITHM0_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ECC_ON_OFF	 */
#define ECC_ON_OFF0_F1_WIDTH                                                  1
#define ECC_ON_OFF0_F1_SHIFT                                                  7
#define ECC_ON_OFF0_F1_MASK                                          0x00000080
#define ECC_ON_OFF0_F1_RD(src)                        (((src) & 0x00000080)>>7)
#define ECC_ON_OFF0_F1_WR(src)                   (((u32)(src)<<7) & 0x00000080)
#define ECC_ON_OFF0_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))

/*	Register gfc_bank1_nand_ctrl1	*/

/*	Register gfc_bank1_nand_ctrl2	*/

/*	Register gfc_bank1_nand_bch	*/
/*	 Fields bch_k	 */
#define BCH_K_F1_WIDTH                                                        3
#define BCH_K_F1_SHIFT                                                       20
#define BCH_K_F1_MASK                                                0x00700000
#define BCH_K_F1_RD(src)                             (((src) & 0x00700000)>>20)
#define BCH_K_F1_WR(src)                        (((u32)(src)<<20) & 0x00700000)
#define BCH_K_F1_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields bch_t	 */
#define BCH_T_F1_WIDTH                                                        4
#define BCH_T_F1_SHIFT                                                       16
#define BCH_T_F1_MASK                                                0x000f0000
#define BCH_T_F1_RD(src)                             (((src) & 0x000f0000)>>16)
#define BCH_T_F1_WR(src)                        (((u32)(src)<<16) & 0x000f0000)
#define BCH_T_F1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields bch_n	 */
#define BCH_N_F1_WIDTH                                                       16
#define BCH_N_F1_SHIFT                                                        0
#define BCH_N_F1_MASK                                                0x0000ffff
#define BCH_N_F1_RD(src)                                 (((src) & 0x0000ffff))
#define BCH_N_F1_WR(src)                            (((u32)(src)) & 0x0000ffff)
#define BCH_N_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank1_dma_ctrl1	*/
/*	 Fields dma_data_size	 */
#define DMA_DATA_SIZE1_F1_WIDTH                                              24
#define DMA_DATA_SIZE1_F1_SHIFT                                               0
#define DMA_DATA_SIZE1_F1_MASK                                       0x00ffffff
#define DMA_DATA_SIZE1_F1_RD(src)                        (((src) & 0x00ffffff))
#define DMA_DATA_SIZE1_F1_WR(src)                   (((u32)(src)) & 0x00ffffff)
#define DMA_DATA_SIZE1_F1_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_bank1_nand_ctrl3	*/
/*	 Fields page_size	 */
#define PAGE_SIZE3_F1_WIDTH                                                  16
#define PAGE_SIZE3_F1_SHIFT                                                   0
#define PAGE_SIZE3_F1_MASK                                           0x0000ffff
#define PAGE_SIZE3_F1_RD(src)                            (((src) & 0x0000ffff))
#define PAGE_SIZE3_F1_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define PAGE_SIZE3_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank1_nand_ctrl4	*/
/*	 Fields device_size	 */
#define DEVICE_SIZE4_F1_WIDTH                                                16
#define DEVICE_SIZE4_F1_SHIFT                                                16
#define DEVICE_SIZE4_F1_MASK                                         0xffff0000
#define DEVICE_SIZE4_F1_RD(src)                      (((src) & 0xffff0000)>>16)
#define DEVICE_SIZE4_F1_WR(src)                 (((u32)(src)<<16) & 0xffff0000)
#define DEVICE_SIZE4_F1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields block_size	 */
#define BLOCK_SIZE4_F1_WIDTH                                                 16
#define BLOCK_SIZE4_F1_SHIFT                                                  0
#define BLOCK_SIZE4_F1_MASK                                          0x0000ffff
#define BLOCK_SIZE4_F1_RD(src)                           (((src) & 0x0000ffff))
#define BLOCK_SIZE4_F1_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define BLOCK_SIZE4_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank1_nand_timing0	*/
/*	 Fields t_adl	 */
#define T_ADL0_F1_WIDTH                                                       8
#define T_ADL0_F1_SHIFT                                                      24
#define T_ADL0_F1_MASK                                               0xff000000
#define T_ADL0_F1_RD(src)                            (((src) & 0xff000000)>>24)
#define T_ADL0_F1_WR(src)                       (((u32)(src)<<24) & 0xff000000)
#define T_ADL0_F1_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_wb	 */
#define T_WB0_F1_WIDTH                                                        8
#define T_WB0_F1_SHIFT                                                       16
#define T_WB0_F1_MASK                                                0x00ff0000
#define T_WB0_F1_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WB0_F1_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WB0_F1_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_rhw	 */
#define T_RHW0_F1_WIDTH                                                       8
#define T_RHW0_F1_SHIFT                                                       8
#define T_RHW0_F1_MASK                                               0x0000ff00
#define T_RHW0_F1_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_RHW0_F1_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_RHW0_F1_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_ccs	 */
#define T_CCS0_F1_WIDTH                                                       8
#define T_CCS0_F1_SHIFT                                                       0
#define T_CCS0_F1_MASK                                               0x000000ff
#define T_CCS0_F1_RD(src)                                (((src) & 0x000000ff))
#define T_CCS0_F1_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CCS0_F1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank1_nand_timing1	*/
/*	 Fields t_alh_clh_ch	 */
#define T_ALH_CLH_CH1_F1_WIDTH                                                8
#define T_ALH_CLH_CH1_F1_SHIFT                                               24
#define T_ALH_CLH_CH1_F1_MASK                                        0xff000000
#define T_ALH_CLH_CH1_F1_RD(src)                     (((src) & 0xff000000)>>24)
#define T_ALH_CLH_CH1_F1_WR(src)                (((u32)(src)<<24) & 0xff000000)
#define T_ALH_CLH_CH1_F1_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_als_cls_cs	 */
#define T_ALS_CLS_CS1_F1_WIDTH                                                8
#define T_ALS_CLS_CS1_F1_SHIFT                                               16
#define T_ALS_CLS_CS1_F1_MASK                                        0x00ff0000
#define T_ALS_CLS_CS1_F1_RD(src)                     (((src) & 0x00ff0000)>>16)
#define T_ALS_CLS_CS1_F1_WR(src)                (((u32)(src)<<16) & 0x00ff0000)
#define T_ALS_CLS_CS1_F1_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_ds_wp	 */
#define T_DS_WP1_F1_WIDTH                                                     8
#define T_DS_WP1_F1_SHIFT                                                     8
#define T_DS_WP1_F1_MASK                                             0x0000ff00
#define T_DS_WP1_F1_RD(src)                           (((src) & 0x0000ff00)>>8)
#define T_DS_WP1_F1_WR(src)                      (((u32)(src)<<8) & 0x0000ff00)
#define T_DS_WP1_F1_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_dh_wh	 */
#define T_DH_WH1_F1_WIDTH                                                     8
#define T_DH_WH1_F1_SHIFT                                                     0
#define T_DH_WH1_F1_MASK                                             0x000000ff
#define T_DH_WH1_F1_RD(src)                              (((src) & 0x000000ff))
#define T_DH_WH1_F1_WR(src)                         (((u32)(src)) & 0x000000ff)
#define T_DH_WH1_F1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank1_nand_timing2	*/
/*	 Fields t_ar_clr_whr_ir	 */
#define T_AR_CLR_WHR_IR2_F1_WIDTH                                             8
#define T_AR_CLR_WHR_IR2_F1_SHIFT                                            24
#define T_AR_CLR_WHR_IR2_F1_MASK                                     0xff000000
#define T_AR_CLR_WHR_IR2_F1_RD(src)                  (((src) & 0xff000000)>>24)
#define T_AR_CLR_WHR_IR2_F1_WR(src)             (((u32)(src)<<24) & 0xff000000)
#define T_AR_CLR_WHR_IR2_F1_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_rr	 */
#define T_RR2_F1_WIDTH                                                        8
#define T_RR2_F1_SHIFT                                                       16
#define T_RR2_F1_MASK                                                0x00ff0000
#define T_RR2_F1_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_RR2_F1_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_RR2_F1_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_reh	 */
#define T_REH2_F1_WIDTH                                                       8
#define T_REH2_F1_SHIFT                                                       8
#define T_REH2_F1_MASK                                               0x0000ff00
#define T_REH2_F1_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_REH2_F1_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_REH2_F1_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_rp	 */
#define T_RP2_F1_WIDTH                                                        8
#define T_RP2_F1_SHIFT                                                        0
#define T_RP2_F1_MASK                                                0x000000ff
#define T_RP2_F1_RD(src)                                 (((src) & 0x000000ff))
#define T_RP2_F1_WR(src)                            (((u32)(src)) & 0x000000ff)
#define T_RP2_F1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank1_nand_timing3	*/
/*	 Fields t_ww	 */
#define T_WW3_F1_WIDTH                                                        8
#define T_WW3_F1_SHIFT                                                       16
#define T_WW3_F1_MASK                                                0x00ff0000
#define T_WW3_F1_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WW3_F1_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WW3_F1_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_chz	 */
#define T_CHZ3_F1_WIDTH                                                       8
#define T_CHZ3_F1_SHIFT                                                       8
#define T_CHZ3_F1_MASK                                               0x0000ff00
#define T_CHZ3_F1_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_CHZ3_F1_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_CHZ3_F1_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_cea	 */
#define T_CEA3_F1_WIDTH                                                       8
#define T_CEA3_F1_SHIFT                                                       0
#define T_CEA3_F1_MASK                                               0x000000ff
#define T_CEA3_F1_RD(src)                                (((src) & 0x000000ff))
#define T_CEA3_F1_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CEA3_F1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank1_nand_cor_err	*/
/*	 Fields counter	 */
#define COUNTER_F3_WIDTH                                                     32
#define COUNTER_F3_SHIFT                                                      0
#define COUNTER_F3_MASK                                              0xffffffff
#define COUNTER_F3_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank1_nand_uncor_err	*/
/*	 Fields counter	 */
#define COUNTER_F4_WIDTH                                                     32
#define COUNTER_F4_SHIFT                                                      0
#define COUNTER_F4_MASK                                              0xffffffff
#define COUNTER_F4_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_ctrl0	*/
/*	 Fields nand_wp_n	 */
#define NAND_WP_N0_F2_WIDTH                                                   1
#define NAND_WP_N0_F2_SHIFT                                                   8
#define NAND_WP_N0_F2_MASK                                           0x00000100
#define NAND_WP_N0_F2_RD(src)                         (((src) & 0x00000100)>>8)
#define NAND_WP_N0_F2_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define NAND_WP_N0_F2_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bus_width	 */
#define BUS_WIDTH0_F2_WIDTH                                                   2
#define BUS_WIDTH0_F2_SHIFT                                                   6
#define BUS_WIDTH0_F2_MASK                                           0x000000c0
#define BUS_WIDTH0_F2_RD(src)                         (((src) & 0x000000c0)>>6)
#define BUS_WIDTH0_F2_WR(src)                    (((u32)(src)<<6) & 0x000000c0)
#define BUS_WIDTH0_F2_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields bus_usage	 */
#define BUS_USAGE0_F2_WIDTH                                                   2
#define BUS_USAGE0_F2_SHIFT                                                   4
#define BUS_USAGE0_F2_MASK                                           0x00000030
#define BUS_USAGE0_F2_RD(src)                         (((src) & 0x00000030)>>4)
#define BUS_USAGE0_F2_WR(src)                    (((u32)(src)<<4) & 0x00000030)
#define BUS_USAGE0_F2_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields bank_type	 */
#define BANK_TYPE0_F2_WIDTH                                                   3
#define BANK_TYPE0_F2_SHIFT                                                   1
#define BANK_TYPE0_F2_MASK                                           0x0000000e
#define BANK_TYPE0_F2_RD(src)                         (((src) & 0x0000000e)>>1)
#define BANK_TYPE0_F2_WR(src)                    (((u32)(src)<<1) & 0x0000000e)
#define BANK_TYPE0_F2_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields bank_valid	 */
#define BANK_VALID0_F2_WIDTH                                                  1
#define BANK_VALID0_F2_SHIFT                                                  0
#define BANK_VALID0_F2_MASK                                          0x00000001
#define BANK_VALID0_F2_RD(src)                           (((src) & 0x00000001))
#define BANK_VALID0_F2_WR(src)                      (((u32)(src)) & 0x00000001)
#define BANK_VALID0_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank2_start_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F5_WIDTH                                                14
#define REGSPEC_ADDR_F5_SHIFT                                                 0
#define REGSPEC_ADDR_F5_MASK                                         0x00003fff
#define REGSPEC_ADDR_F5_RD(src)                          (((src) & 0x00003fff))
#define REGSPEC_ADDR_F5_WR(src)                     (((u32)(src)) & 0x00003fff)
#define REGSPEC_ADDR_F5_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register gfc_bank2_end_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F6_WIDTH                                                15
#define REGSPEC_ADDR_F6_SHIFT                                                 0
#define REGSPEC_ADDR_F6_MASK                                         0x00007fff
#define REGSPEC_ADDR_F6_RD(src)                          (((src) & 0x00007fff))
#define REGSPEC_ADDR_F6_WR(src)                     (((u32)(src)) & 0x00007fff)
#define REGSPEC_ADDR_F6_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register gfc_bank2_base_add	*/
/*	 Fields bank_base_add	 */
#define BANK_BASE_ADD_F2_WIDTH                                               32
#define BANK_BASE_ADD_F2_SHIFT                                                0
#define BANK_BASE_ADD_F2_MASK                                        0xffffffff
#define BANK_BASE_ADD_F2_RD(src)                         (((src) & 0xffffffff))
#define BANK_BASE_ADD_F2_WR(src)                    (((u32)(src)) & 0xffffffff)
#define BANK_BASE_ADD_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_dma_ctrl0	*/
/*	 Fields complNum_4_int	 */
#define COMPLNUM_4_INT0_F2_WIDTH                                              3
#define COMPLNUM_4_INT0_F2_SHIFT                                             10
#define COMPLNUM_4_INT0_F2_MASK                                      0x00001c00
#define COMPLNUM_4_INT0_F2_RD(src)                   (((src) & 0x00001c00)>>10)
#define COMPLNUM_4_INT0_F2_WR(src)              (((u32)(src)<<10) & 0x00001c00)
#define COMPLNUM_4_INT0_F2_SET(dst,src) \
                      (((dst) & ~0x00001c00) | (((u32)(src)<<10) & 0x00001c00))
/*	 Fields dma_cmd_code	 */
#define DMA_CMD_CODE0_F2_WIDTH                                                3
#define DMA_CMD_CODE0_F2_SHIFT                                                7
#define DMA_CMD_CODE0_F2_MASK                                        0x00000380
#define DMA_CMD_CODE0_F2_RD(src)                      (((src) & 0x00000380)>>7)
#define DMA_CMD_CODE0_F2_WR(src)                 (((u32)(src)<<7) & 0x00000380)
#define DMA_CMD_CODE0_F2_SET(dst,src) \
                       (((dst) & ~0x00000380) | (((u32)(src)<<7) & 0x00000380))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID0_F2_WIDTH                                                  2
#define DMA_CMD_ID0_F2_SHIFT                                                  3
#define DMA_CMD_ID0_F2_MASK                                          0x00000018
#define DMA_CMD_ID0_F2_RD(src)                        (((src) & 0x00000018)>>3)
#define DMA_CMD_ID0_F2_WR(src)                   (((u32)(src)<<3) & 0x00000018)
#define DMA_CMD_ID0_F2_SET(dst,src) \
                       (((dst) & ~0x00000018) | (((u32)(src)<<3) & 0x00000018))
/*	 Fields dma_cmd_pop	 */
#define DMA_CMD_POP0_F2_WIDTH                                                 1
#define DMA_CMD_POP0_F2_SHIFT                                                 2
#define DMA_CMD_POP0_F2_MASK                                         0x00000004
#define DMA_CMD_POP0_F2_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_CMD_POP0_F2_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_CMD_POP0_F2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dma_cmd_push	 */
#define DMA_CMD_PUSH0_F2_WIDTH                                                1
#define DMA_CMD_PUSH0_F2_SHIFT                                                1
#define DMA_CMD_PUSH0_F2_MASK                                        0x00000002
#define DMA_CMD_PUSH0_F2_RD(src)                      (((src) & 0x00000002)>>1)
#define DMA_CMD_PUSH0_F2_WR(src)                 (((u32)(src)<<1) & 0x00000002)
#define DMA_CMD_PUSH0_F2_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dma_cmd_valid	 */
#define DMA_CMD_VALID0_F2_WIDTH                                               1
#define DMA_CMD_VALID0_F2_SHIFT                                               0
#define DMA_CMD_VALID0_F2_MASK                                       0x00000001
#define DMA_CMD_VALID0_F2_RD(src)                        (((src) & 0x00000001))
#define DMA_CMD_VALID0_F2_WR(src)                   (((u32)(src)) & 0x00000001)
#define DMA_CMD_VALID0_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank2_dma_start_add0	*/
/*	 Fields dma_start_add0	 */
#define DMA_START_ADD00_F2_WIDTH                                             32
#define DMA_START_ADD00_F2_SHIFT                                              0
#define DMA_START_ADD00_F2_MASK                                      0xffffffff
#define DMA_START_ADD00_F2_RD(src)                       (((src) & 0xffffffff))
#define DMA_START_ADD00_F2_WR(src)                  (((u32)(src)) & 0xffffffff)
#define DMA_START_ADD00_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_dma_start_add1	*/
/*	 Fields dma_start_add1	 */
#define DMA_START_ADD11_F2_WIDTH                                             10
#define DMA_START_ADD11_F2_SHIFT                                              0
#define DMA_START_ADD11_F2_MASK                                      0x000003ff
#define DMA_START_ADD11_F2_RD(src)                       (((src) & 0x000003ff))
#define DMA_START_ADD11_F2_WR(src)                  (((u32)(src)) & 0x000003ff)
#define DMA_START_ADD11_F2_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank2_dma_des_add0	*/
/*	 Fields dma_des_add0	 */
#define DMA_DES_ADD00_F2_WIDTH                                               32
#define DMA_DES_ADD00_F2_SHIFT                                                0
#define DMA_DES_ADD00_F2_MASK                                        0xffffffff
#define DMA_DES_ADD00_F2_RD(src)                         (((src) & 0xffffffff))
#define DMA_DES_ADD00_F2_WR(src)                    (((u32)(src)) & 0xffffffff)
#define DMA_DES_ADD00_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_dma_des_add1	*/
/*	 Fields dma_des_add1	 */
#define DMA_DES_ADD11_F2_WIDTH                                               10
#define DMA_DES_ADD11_F2_SHIFT                                                0
#define DMA_DES_ADD11_F2_MASK                                        0x000003ff
#define DMA_DES_ADD11_F2_RD(src)                         (((src) & 0x000003ff))
#define DMA_DES_ADD11_F2_WR(src)                    (((u32)(src)) & 0x000003ff)
#define DMA_DES_ADD11_F2_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank2_dma_status	*/
/*	 Fields bits_corrected_ecc	 */
#define BITS_CORRECTED_ECC_F2_WIDTH                                           4
#define BITS_CORRECTED_ECC_F2_SHIFT                                          14
#define BITS_CORRECTED_ECC_F2_MASK                                   0x0003c000
#define BITS_CORRECTED_ECC_F2_RD(src)                (((src) & 0x0003c000)>>14)
#define BITS_CORRECTED_ECC_F2_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields dma_err	 */
#define DMA_ERR_F2_WIDTH                                                      3
#define DMA_ERR_F2_SHIFT                                                      9
#define DMA_ERR_F2_MASK                                              0x00000e00
#define DMA_ERR_F2_RD(src)                            (((src) & 0x00000e00)>>9)
#define DMA_ERR_F2_SET(dst,src) \
                       (((dst) & ~0x00000e00) | (((u32)(src)<<9) & 0x00000e00))
/*	 Fields dma_cmpl_status	 */
#define DMA_CMPL_STATUS_F2_WIDTH                                              2
#define DMA_CMPL_STATUS_F2_SHIFT                                              6
#define DMA_CMPL_STATUS_F2_MASK                                      0x000000c0
#define DMA_CMPL_STATUS_F2_RD(src)                    (((src) & 0x000000c0)>>6)
#define DMA_CMPL_STATUS_F2_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID_F2_WIDTH                                                   2
#define DMA_CMD_ID_F2_SHIFT                                                   1
#define DMA_CMD_ID_F2_MASK                                           0x00000006
#define DMA_CMD_ID_F2_RD(src)                         (((src) & 0x00000006)>>1)
#define DMA_CMD_ID_F2_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields dma_cmpl_valid	 */
#define DMA_CMPL_VALID_F2_WIDTH                                               1
#define DMA_CMPL_VALID_F2_SHIFT                                               0
#define DMA_CMPL_VALID_F2_MASK                                       0x00000001
#define DMA_CMPL_VALID_F2_RD(src)                        (((src) & 0x00000001))
#define DMA_CMPL_VALID_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank2_dma_eccerr0_add_col	*/
/*	 Fields dma_eccerr0_add_col	 */
#define DMA_ECCERR0_ADD_COL_F2_WIDTH                                         32
#define DMA_ECCERR0_ADD_COL_F2_SHIFT                                          0
#define DMA_ECCERR0_ADD_COL_F2_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_COL_F2_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_COL_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_dma_eccerr0_add_row	*/
/*	 Fields dma_eccerr0_add_row	 */
#define DMA_ECCERR0_ADD_ROW_F2_WIDTH                                         32
#define DMA_ECCERR0_ADD_ROW_F2_SHIFT                                          0
#define DMA_ECCERR0_ADD_ROW_F2_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_ROW_F2_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_ROW_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_dma_eccerr1_add_col	*/
/*	 Fields dma_eccerr1_add_col	 */
#define DMA_ECCERR1_ADD_COL_F2_WIDTH                                         32
#define DMA_ECCERR1_ADD_COL_F2_SHIFT                                          0
#define DMA_ECCERR1_ADD_COL_F2_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_COL_F2_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_COL_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_dma_eccerr1_add_row	*/
/*	 Fields dma_eccerr1_add_row	 */
#define DMA_ECCERR1_ADD_ROW_F2_WIDTH                                         32
#define DMA_ECCERR1_ADD_ROW_F2_SHIFT                                          0
#define DMA_ECCERR1_ADD_ROW_F2_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_ROW_F2_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_ROW_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_INT	*/
/*	 Fields nandpio_device_protection_err	 */
#define NANDPIO_DEVICE_PROTECTION_ERR_F2_WIDTH                                1
#define NANDPIO_DEVICE_PROTECTION_ERR_F2_SHIFT                               11
#define NANDPIO_DEVICE_PROTECTION_ERR_F2_MASK                        0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERR_F2_RD(src)     (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERR_F2_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERR_F2_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields norp_device_protection_err	 */
#define NORP_DEVICE_PROTECTION_ERR_F2_WIDTH                                   1
#define NORP_DEVICE_PROTECTION_ERR_F2_SHIFT                                  10
#define NORP_DEVICE_PROTECTION_ERR_F2_MASK                           0x00000400
#define NORP_DEVICE_PROTECTION_ERR_F2_RD(src)        (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERR_F2_WR(src)   (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERR_F2_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields dma_cmd_override_err	 */
#define DMA_CMD_OVERRIDE_ERR_F2_WIDTH                                         1
#define DMA_CMD_OVERRIDE_ERR_F2_SHIFT                                         9
#define DMA_CMD_OVERRIDE_ERR_F2_MASK                                 0x00000200
#define DMA_CMD_OVERRIDE_ERR_F2_RD(src)               (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERR_F2_WR(src)          (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERR_F2_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields device_protection_err	 */
#define DEVICE_PROTECTION_ERR_F2_WIDTH                                        1
#define DEVICE_PROTECTION_ERR_F2_SHIFT                                        8
#define DEVICE_PROTECTION_ERR_F2_MASK                                0x00000100
#define DEVICE_PROTECTION_ERR_F2_RD(src)              (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERR_F2_WR(src)         (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERR_F2_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields transaction_timeout	 */
#define TRANSACTION_TIMEOUT_F2_WIDTH                                          1
#define TRANSACTION_TIMEOUT_F2_SHIFT                                          7
#define TRANSACTION_TIMEOUT_F2_MASK                                  0x00000080
#define TRANSACTION_TIMEOUT_F2_RD(src)                (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUT_F2_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUT_F2_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields parity_err	 */
#define PARITY_ERR_F2_WIDTH                                                   1
#define PARITY_ERR_F2_SHIFT                                                   6
#define PARITY_ERR_F2_MASK                                           0x00000040
#define PARITY_ERR_F2_RD(src)                         (((src) & 0x00000040)>>6)
#define PARITY_ERR_F2_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERR_F2_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ecc_err_single	 */
#define ECC_ERR_SINGLE_F2_WIDTH                                               1
#define ECC_ERR_SINGLE_F2_SHIFT                                               5
#define ECC_ERR_SINGLE_F2_MASK                                       0x00000020
#define ECC_ERR_SINGLE_F2_RD(src)                     (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLE_F2_WR(src)                (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLE_F2_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ecc_err_multiple	 */
#define ECC_ERR_MULTIPLE_F2_WIDTH                                             1
#define ECC_ERR_MULTIPLE_F2_SHIFT                                             4
#define ECC_ERR_MULTIPLE_F2_MASK                                     0x00000010
#define ECC_ERR_MULTIPLE_F2_RD(src)                   (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLE_F2_WR(src)              (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLE_F2_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields dma_done	 */
#define DMA_DONE_F2_WIDTH                                                     1
#define DMA_DONE_F2_SHIFT                                                     2
#define DMA_DONE_F2_MASK                                             0x00000004
#define DMA_DONE_F2_RD(src)                           (((src) & 0x00000004)>>2)
#define DMA_DONE_F2_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define DMA_DONE_F2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank2_interruptMask	*/
/*    Mask Register Fields nandpio_device_protection_errMask    */
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F2_WIDTH                            1
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F2_SHIFT                           11
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F2_MASK                    0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F2_RD(src) \
                                                    (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F2_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F2_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields norp_device_protection_errMask    */
#define NORP_DEVICE_PROTECTION_ERRMASK_F2_WIDTH                               1
#define NORP_DEVICE_PROTECTION_ERRMASK_F2_SHIFT                              10
#define NORP_DEVICE_PROTECTION_ERRMASK_F2_MASK                       0x00000400
#define NORP_DEVICE_PROTECTION_ERRMASK_F2_RD(src)    (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERRMASK_F2_WR(src) \
                                                (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERRMASK_F2_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields dma_cmd_override_errMask    */
#define DMA_CMD_OVERRIDE_ERRMASK_F2_WIDTH                                     1
#define DMA_CMD_OVERRIDE_ERRMASK_F2_SHIFT                                     9
#define DMA_CMD_OVERRIDE_ERRMASK_F2_MASK                             0x00000200
#define DMA_CMD_OVERRIDE_ERRMASK_F2_RD(src)           (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERRMASK_F2_WR(src)      (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERRMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields device_protection_errMask    */
#define DEVICE_PROTECTION_ERRMASK_F2_WIDTH                                    1
#define DEVICE_PROTECTION_ERRMASK_F2_SHIFT                                    8
#define DEVICE_PROTECTION_ERRMASK_F2_MASK                            0x00000100
#define DEVICE_PROTECTION_ERRMASK_F2_RD(src)          (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERRMASK_F2_WR(src)     (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERRMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields transaction_timeoutMask    */
#define TRANSACTION_TIMEOUTMASK_F2_WIDTH                                      1
#define TRANSACTION_TIMEOUTMASK_F2_SHIFT                                      7
#define TRANSACTION_TIMEOUTMASK_F2_MASK                              0x00000080
#define TRANSACTION_TIMEOUTMASK_F2_RD(src)            (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUTMASK_F2_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUTMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields parity_errMask    */
#define PARITY_ERRMASK_F2_WIDTH                                               1
#define PARITY_ERRMASK_F2_SHIFT                                               6
#define PARITY_ERRMASK_F2_MASK                                       0x00000040
#define PARITY_ERRMASK_F2_RD(src)                     (((src) & 0x00000040)>>6)
#define PARITY_ERRMASK_F2_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERRMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ecc_err_singleMask    */
#define ECC_ERR_SINGLEMASK_F2_WIDTH                                           1
#define ECC_ERR_SINGLEMASK_F2_SHIFT                                           5
#define ECC_ERR_SINGLEMASK_F2_MASK                                   0x00000020
#define ECC_ERR_SINGLEMASK_F2_RD(src)                 (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLEMASK_F2_WR(src)            (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLEMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ecc_err_multipleMask    */
#define ECC_ERR_MULTIPLEMASK_F2_WIDTH                                         1
#define ECC_ERR_MULTIPLEMASK_F2_SHIFT                                         4
#define ECC_ERR_MULTIPLEMASK_F2_MASK                                 0x00000010
#define ECC_ERR_MULTIPLEMASK_F2_RD(src)               (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLEMASK_F2_WR(src)          (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLEMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields dma_doneMask    */
#define DMA_DONEMASK_F2_WIDTH                                                 1
#define DMA_DONEMASK_F2_SHIFT                                                 2
#define DMA_DONEMASK_F2_MASK                                         0x00000004
#define DMA_DONEMASK_F2_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_DONEMASK_F2_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_DONEMASK_F2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank2_sram_ctrl0	*/
/*	 Fields rtc	 */
#define REGSPEC_RTC0_F2_WIDTH                                                 3
#define REGSPEC_RTC0_F2_SHIFT                                                12
#define REGSPEC_RTC0_F2_MASK                                         0x00007000
#define REGSPEC_RTC0_F2_RD(src)                      (((src) & 0x00007000)>>12)
#define REGSPEC_RTC0_F2_WR(src)                 (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_RTC0_F2_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields muxen	 */
#define MUXEN0_F2_WIDTH                                                       1
#define MUXEN0_F2_SHIFT                                                      10
#define MUXEN0_F2_MASK                                               0x00000400
#define MUXEN0_F2_RD(src)                            (((src) & 0x00000400)>>10)
#define MUXEN0_F2_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define MUXEN0_F2_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rdy_timeout_cnt	 */
#define RDY_TIMEOUT_CNT0_F2_WIDTH                                             3
#define RDY_TIMEOUT_CNT0_F2_SHIFT                                             2
#define RDY_TIMEOUT_CNT0_F2_MASK                                     0x0000001c
#define RDY_TIMEOUT_CNT0_F2_RD(src)                   (((src) & 0x0000001c)>>2)
#define RDY_TIMEOUT_CNT0_F2_WR(src)              (((u32)(src)<<2) & 0x0000001c)
#define RDY_TIMEOUT_CNT0_F2_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields ptd	 */
#define PTD0_F2_WIDTH                                                         1
#define PTD0_F2_SHIFT                                                         1
#define PTD0_F2_MASK                                                 0x00000002
#define PTD0_F2_RD(src)                               (((src) & 0x00000002)>>1)
#define PTD0_F2_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PTD0_F2_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields le	 */
#define LE0_F2_WIDTH                                                          1
#define LE0_F2_SHIFT                                                          0
#define LE0_F2_MASK                                                  0x00000001
#define LE0_F2_RD(src)                                   (((src) & 0x00000001))
#define LE0_F2_WR(src)                              (((u32)(src)) & 0x00000001)
#define LE0_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank2_sram_nor_ctrl1	*/
/*	 Fields BME	 */
#define BME1_F2_WIDTH                                                         1
#define BME1_F2_SHIFT                                                        31
#define BME1_F2_MASK                                                 0x80000000
#define BME1_F2_RD(src)                              (((src) & 0x80000000)>>31)
#define BME1_F2_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define BME1_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields OEO	 */
#define OEO1_F2_WIDTH                                                         1
#define OEO1_F2_SHIFT                                                        30
#define OEO1_F2_MASK                                                 0x40000000
#define OEO1_F2_RD(src)                              (((src) & 0x40000000)>>30)
#define OEO1_F2_WR(src)                         (((u32)(src)<<30) & 0x40000000)
#define OEO1_F2_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields BWT	 */
#define BWT1_F2_WIDTH                                                         5
#define BWT1_F2_SHIFT                                                        20
#define BWT1_F2_MASK                                                 0x01f00000
#define BWT1_F2_RD(src)                              (((src) & 0x01f00000)>>20)
#define BWT1_F2_WR(src)                         (((u32)(src)<<20) & 0x01f00000)
#define BWT1_F2_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields FWT	 */
#define FWT1_F2_WIDTH                                                         7
#define FWT1_F2_SHIFT                                                        12
#define FWT1_F2_MASK                                                 0x0007f000
#define FWT1_F2_RD(src)                              (((src) & 0x0007f000)>>12)
#define FWT1_F2_WR(src)                         (((u32)(src)<<12) & 0x0007f000)
#define FWT1_F2_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields TWT	 */
#define TWT1_F2_WIDTH                                                        10
#define TWT1_F2_SHIFT                                                         0
#define TWT1_F2_MASK                                                 0x000003ff
#define TWT1_F2_RD(src)                                  (((src) & 0x000003ff))
#define TWT1_F2_WR(src)                             (((u32)(src)) & 0x000003ff)
#define TWT1_F2_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank2_sram_nor_ctrl2	*/
/*	 Fields ALN	 */
#define ALN2_F2_WIDTH                                                         4
#define ALN2_F2_SHIFT                                                        28
#define ALN2_F2_MASK                                                 0xf0000000
#define ALN2_F2_RD(src)                              (((src) & 0xf0000000)>>28)
#define ALN2_F2_WR(src)                         (((u32)(src)<<28) & 0xf0000000)
#define ALN2_F2_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields PEN	 */
#define PEN2_F2_WIDTH                                                         1
#define PEN2_F2_SHIFT                                                        27
#define PEN2_F2_MASK                                                 0x08000000
#define PEN2_F2_RD(src)                              (((src) & 0x08000000)>>27)
#define PEN2_F2_WR(src)                         (((u32)(src)<<27) & 0x08000000)
#define PEN2_F2_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields BEM	 */
#define BEM2_F2_WIDTH                                                         1
#define BEM2_F2_SHIFT                                                        26
#define BEM2_F2_MASK                                                 0x04000000
#define BEM2_F2_RD(src)                              (((src) & 0x04000000)>>26)
#define BEM2_F2_WR(src)                         (((u32)(src)<<26) & 0x04000000)
#define BEM2_F2_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SOR	 */
#define SOR2_F2_WIDTH                                                         1
#define SOR2_F2_SHIFT                                                        25
#define SOR2_F2_MASK                                                 0x02000000
#define SOR2_F2_RD(src)                              (((src) & 0x02000000)>>25)
#define SOR2_F2_WR(src)                         (((u32)(src)<<25) & 0x02000000)
#define SOR2_F2_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RE	 */
#define RE2_F2_WIDTH                                                          1
#define RE2_F2_SHIFT                                                         24
#define RE2_F2_MASK                                                  0x01000000
#define RE2_F2_RD(src)                               (((src) & 0x01000000)>>24)
#define RE2_F2_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define RE2_F2_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields TH	 */
#define TH2_F2_WIDTH                                                          5
#define TH2_F2_SHIFT                                                         16
#define TH2_F2_MASK                                                  0x001f0000
#define TH2_F2_RD(src)                               (((src) & 0x001f0000)>>16)
#define TH2_F2_WR(src)                          (((u32)(src)<<16) & 0x001f0000)
#define TH2_F2_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WBF	 */
#define WBF2_F2_WIDTH                                                         4
#define WBF2_F2_SHIFT                                                        12
#define WBF2_F2_MASK                                                 0x0000f000
#define WBF2_F2_RD(src)                              (((src) & 0x0000f000)>>12)
#define WBF2_F2_WR(src)                         (((u32)(src)<<12) & 0x0000f000)
#define WBF2_F2_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WBN	 */
#define WBN2_F2_WIDTH                                                         4
#define WBN2_F2_SHIFT                                                         8
#define WBN2_F2_MASK                                                 0x00000f00
#define WBN2_F2_RD(src)                               (((src) & 0x00000f00)>>8)
#define WBN2_F2_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define WBN2_F2_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields OEN	 */
#define OEN2_F2_WIDTH                                                         4
#define OEN2_F2_SHIFT                                                         4
#define OEN2_F2_MASK                                                 0x000000f0
#define OEN2_F2_RD(src)                               (((src) & 0x000000f0)>>4)
#define OEN2_F2_WR(src)                          (((u32)(src)<<4) & 0x000000f0)
#define OEN2_F2_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields CSN	 */
#define CSN2_F2_WIDTH                                                         4
#define CSN2_F2_SHIFT                                                         0
#define CSN2_F2_MASK                                                 0x0000000f
#define CSN2_F2_RD(src)                                  (((src) & 0x0000000f))
#define CSN2_F2_WR(src)                             (((u32)(src)) & 0x0000000f)
#define CSN2_F2_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_bank2_nand_ctrl0	*/
/*	 Fields SPARE_OFFSET	 */
#define SPARE_OFFSET0_F2_WIDTH                                               16
#define SPARE_OFFSET0_F2_SHIFT                                               16
#define SPARE_OFFSET0_F2_MASK                                        0xffff0000
#define SPARE_OFFSET0_F2_RD(src)                     (((src) & 0xffff0000)>>16)
#define SPARE_OFFSET0_F2_WR(src)                (((u32)(src)<<16) & 0xffff0000)
#define SPARE_OFFSET0_F2_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields FORCE_SPARE_OFFSET	 */
#define FORCE_SPARE_OFFSET0_F2_WIDTH                                          1
#define FORCE_SPARE_OFFSET0_F2_SHIFT                                          9
#define FORCE_SPARE_OFFSET0_F2_MASK                                  0x00000200
#define FORCE_SPARE_OFFSET0_F2_RD(src)                (((src) & 0x00000200)>>9)
#define FORCE_SPARE_OFFSET0_F2_WR(src)           (((u32)(src)<<9) & 0x00000200)
#define FORCE_SPARE_OFFSET0_F2_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ECC_Algorithm	 */
#define ECC_ALGORITHM0_F2_WIDTH                                               1
#define ECC_ALGORITHM0_F2_SHIFT                                               8
#define ECC_ALGORITHM0_F2_MASK                                       0x00000100
#define ECC_ALGORITHM0_F2_RD(src)                     (((src) & 0x00000100)>>8)
#define ECC_ALGORITHM0_F2_WR(src)                (((u32)(src)<<8) & 0x00000100)
#define ECC_ALGORITHM0_F2_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ECC_ON_OFF	 */
#define ECC_ON_OFF0_F2_WIDTH                                                  1
#define ECC_ON_OFF0_F2_SHIFT                                                  7
#define ECC_ON_OFF0_F2_MASK                                          0x00000080
#define ECC_ON_OFF0_F2_RD(src)                        (((src) & 0x00000080)>>7)
#define ECC_ON_OFF0_F2_WR(src)                   (((u32)(src)<<7) & 0x00000080)
#define ECC_ON_OFF0_F2_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))

/*	Register gfc_bank2_nand_ctrl1	*/

/*	Register gfc_bank2_nand_ctrl2	*/

/*	Register gfc_bank2_nand_bch	*/
/*	 Fields bch_k	 */
#define BCH_K_F2_WIDTH                                                        3
#define BCH_K_F2_SHIFT                                                       20
#define BCH_K_F2_MASK                                                0x00700000
#define BCH_K_F2_RD(src)                             (((src) & 0x00700000)>>20)
#define BCH_K_F2_WR(src)                        (((u32)(src)<<20) & 0x00700000)
#define BCH_K_F2_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields bch_t	 */
#define BCH_T_F2_WIDTH                                                        4
#define BCH_T_F2_SHIFT                                                       16
#define BCH_T_F2_MASK                                                0x000f0000
#define BCH_T_F2_RD(src)                             (((src) & 0x000f0000)>>16)
#define BCH_T_F2_WR(src)                        (((u32)(src)<<16) & 0x000f0000)
#define BCH_T_F2_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields bch_n	 */
#define BCH_N_F2_WIDTH                                                       16
#define BCH_N_F2_SHIFT                                                        0
#define BCH_N_F2_MASK                                                0x0000ffff
#define BCH_N_F2_RD(src)                                 (((src) & 0x0000ffff))
#define BCH_N_F2_WR(src)                            (((u32)(src)) & 0x0000ffff)
#define BCH_N_F2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank2_dma_ctrl1	*/
/*	 Fields dma_data_size	 */
#define DMA_DATA_SIZE1_F2_WIDTH                                              24
#define DMA_DATA_SIZE1_F2_SHIFT                                               0
#define DMA_DATA_SIZE1_F2_MASK                                       0x00ffffff
#define DMA_DATA_SIZE1_F2_RD(src)                        (((src) & 0x00ffffff))
#define DMA_DATA_SIZE1_F2_WR(src)                   (((u32)(src)) & 0x00ffffff)
#define DMA_DATA_SIZE1_F2_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_bank2_nand_ctrl3	*/
/*	 Fields page_size	 */
#define PAGE_SIZE3_F2_WIDTH                                                  16
#define PAGE_SIZE3_F2_SHIFT                                                   0
#define PAGE_SIZE3_F2_MASK                                           0x0000ffff
#define PAGE_SIZE3_F2_RD(src)                            (((src) & 0x0000ffff))
#define PAGE_SIZE3_F2_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define PAGE_SIZE3_F2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank2_nand_ctrl4	*/
/*	 Fields device_size	 */
#define DEVICE_SIZE4_F2_WIDTH                                                16
#define DEVICE_SIZE4_F2_SHIFT                                                16
#define DEVICE_SIZE4_F2_MASK                                         0xffff0000
#define DEVICE_SIZE4_F2_RD(src)                      (((src) & 0xffff0000)>>16)
#define DEVICE_SIZE4_F2_WR(src)                 (((u32)(src)<<16) & 0xffff0000)
#define DEVICE_SIZE4_F2_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields block_size	 */
#define BLOCK_SIZE4_F2_WIDTH                                                 16
#define BLOCK_SIZE4_F2_SHIFT                                                  0
#define BLOCK_SIZE4_F2_MASK                                          0x0000ffff
#define BLOCK_SIZE4_F2_RD(src)                           (((src) & 0x0000ffff))
#define BLOCK_SIZE4_F2_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define BLOCK_SIZE4_F2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank2_nand_timing0	*/
/*	 Fields t_adl	 */
#define T_ADL0_F2_WIDTH                                                       8
#define T_ADL0_F2_SHIFT                                                      24
#define T_ADL0_F2_MASK                                               0xff000000
#define T_ADL0_F2_RD(src)                            (((src) & 0xff000000)>>24)
#define T_ADL0_F2_WR(src)                       (((u32)(src)<<24) & 0xff000000)
#define T_ADL0_F2_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_wb	 */
#define T_WB0_F2_WIDTH                                                        8
#define T_WB0_F2_SHIFT                                                       16
#define T_WB0_F2_MASK                                                0x00ff0000
#define T_WB0_F2_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WB0_F2_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WB0_F2_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_rhw	 */
#define T_RHW0_F2_WIDTH                                                       8
#define T_RHW0_F2_SHIFT                                                       8
#define T_RHW0_F2_MASK                                               0x0000ff00
#define T_RHW0_F2_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_RHW0_F2_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_RHW0_F2_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_ccs	 */
#define T_CCS0_F2_WIDTH                                                       8
#define T_CCS0_F2_SHIFT                                                       0
#define T_CCS0_F2_MASK                                               0x000000ff
#define T_CCS0_F2_RD(src)                                (((src) & 0x000000ff))
#define T_CCS0_F2_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CCS0_F2_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank2_nand_timing1	*/
/*	 Fields t_alh_clh_ch	 */
#define T_ALH_CLH_CH1_F2_WIDTH                                                8
#define T_ALH_CLH_CH1_F2_SHIFT                                               24
#define T_ALH_CLH_CH1_F2_MASK                                        0xff000000
#define T_ALH_CLH_CH1_F2_RD(src)                     (((src) & 0xff000000)>>24)
#define T_ALH_CLH_CH1_F2_WR(src)                (((u32)(src)<<24) & 0xff000000)
#define T_ALH_CLH_CH1_F2_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_als_cls_cs	 */
#define T_ALS_CLS_CS1_F2_WIDTH                                                8
#define T_ALS_CLS_CS1_F2_SHIFT                                               16
#define T_ALS_CLS_CS1_F2_MASK                                        0x00ff0000
#define T_ALS_CLS_CS1_F2_RD(src)                     (((src) & 0x00ff0000)>>16)
#define T_ALS_CLS_CS1_F2_WR(src)                (((u32)(src)<<16) & 0x00ff0000)
#define T_ALS_CLS_CS1_F2_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_ds_wp	 */
#define T_DS_WP1_F2_WIDTH                                                     8
#define T_DS_WP1_F2_SHIFT                                                     8
#define T_DS_WP1_F2_MASK                                             0x0000ff00
#define T_DS_WP1_F2_RD(src)                           (((src) & 0x0000ff00)>>8)
#define T_DS_WP1_F2_WR(src)                      (((u32)(src)<<8) & 0x0000ff00)
#define T_DS_WP1_F2_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_dh_wh	 */
#define T_DH_WH1_F2_WIDTH                                                     8
#define T_DH_WH1_F2_SHIFT                                                     0
#define T_DH_WH1_F2_MASK                                             0x000000ff
#define T_DH_WH1_F2_RD(src)                              (((src) & 0x000000ff))
#define T_DH_WH1_F2_WR(src)                         (((u32)(src)) & 0x000000ff)
#define T_DH_WH1_F2_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank2_nand_timing2	*/
/*	 Fields t_ar_clr_whr_ir	 */
#define T_AR_CLR_WHR_IR2_F2_WIDTH                                             8
#define T_AR_CLR_WHR_IR2_F2_SHIFT                                            24
#define T_AR_CLR_WHR_IR2_F2_MASK                                     0xff000000
#define T_AR_CLR_WHR_IR2_F2_RD(src)                  (((src) & 0xff000000)>>24)
#define T_AR_CLR_WHR_IR2_F2_WR(src)             (((u32)(src)<<24) & 0xff000000)
#define T_AR_CLR_WHR_IR2_F2_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_rr	 */
#define T_RR2_F2_WIDTH                                                        8
#define T_RR2_F2_SHIFT                                                       16
#define T_RR2_F2_MASK                                                0x00ff0000
#define T_RR2_F2_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_RR2_F2_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_RR2_F2_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_reh	 */
#define T_REH2_F2_WIDTH                                                       8
#define T_REH2_F2_SHIFT                                                       8
#define T_REH2_F2_MASK                                               0x0000ff00
#define T_REH2_F2_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_REH2_F2_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_REH2_F2_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_rp	 */
#define T_RP2_F2_WIDTH                                                        8
#define T_RP2_F2_SHIFT                                                        0
#define T_RP2_F2_MASK                                                0x000000ff
#define T_RP2_F2_RD(src)                                 (((src) & 0x000000ff))
#define T_RP2_F2_WR(src)                            (((u32)(src)) & 0x000000ff)
#define T_RP2_F2_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank2_nand_timing3	*/
/*	 Fields t_ww	 */
#define T_WW3_F2_WIDTH                                                        8
#define T_WW3_F2_SHIFT                                                       16
#define T_WW3_F2_MASK                                                0x00ff0000
#define T_WW3_F2_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WW3_F2_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WW3_F2_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_chz	 */
#define T_CHZ3_F2_WIDTH                                                       8
#define T_CHZ3_F2_SHIFT                                                       8
#define T_CHZ3_F2_MASK                                               0x0000ff00
#define T_CHZ3_F2_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_CHZ3_F2_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_CHZ3_F2_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_cea	 */
#define T_CEA3_F2_WIDTH                                                       8
#define T_CEA3_F2_SHIFT                                                       0
#define T_CEA3_F2_MASK                                               0x000000ff
#define T_CEA3_F2_RD(src)                                (((src) & 0x000000ff))
#define T_CEA3_F2_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CEA3_F2_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank2_nand_cor_err	*/
/*	 Fields counter	 */
#define COUNTER_F5_WIDTH                                                     32
#define COUNTER_F5_SHIFT                                                      0
#define COUNTER_F5_MASK                                              0xffffffff
#define COUNTER_F5_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank2_nand_uncor_err	*/
/*	 Fields counter	 */
#define COUNTER_F6_WIDTH                                                     32
#define COUNTER_F6_SHIFT                                                      0
#define COUNTER_F6_MASK                                              0xffffffff
#define COUNTER_F6_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_ctrl0	*/
/*	 Fields nand_wp_n	 */
#define NAND_WP_N0_F3_WIDTH                                                   1
#define NAND_WP_N0_F3_SHIFT                                                   8
#define NAND_WP_N0_F3_MASK                                           0x00000100
#define NAND_WP_N0_F3_RD(src)                         (((src) & 0x00000100)>>8)
#define NAND_WP_N0_F3_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define NAND_WP_N0_F3_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bus_width	 */
#define BUS_WIDTH0_F3_WIDTH                                                   2
#define BUS_WIDTH0_F3_SHIFT                                                   6
#define BUS_WIDTH0_F3_MASK                                           0x000000c0
#define BUS_WIDTH0_F3_RD(src)                         (((src) & 0x000000c0)>>6)
#define BUS_WIDTH0_F3_WR(src)                    (((u32)(src)<<6) & 0x000000c0)
#define BUS_WIDTH0_F3_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields bus_usage	 */
#define BUS_USAGE0_F3_WIDTH                                                   2
#define BUS_USAGE0_F3_SHIFT                                                   4
#define BUS_USAGE0_F3_MASK                                           0x00000030
#define BUS_USAGE0_F3_RD(src)                         (((src) & 0x00000030)>>4)
#define BUS_USAGE0_F3_WR(src)                    (((u32)(src)<<4) & 0x00000030)
#define BUS_USAGE0_F3_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields bank_type	 */
#define BANK_TYPE0_F3_WIDTH                                                   3
#define BANK_TYPE0_F3_SHIFT                                                   1
#define BANK_TYPE0_F3_MASK                                           0x0000000e
#define BANK_TYPE0_F3_RD(src)                         (((src) & 0x0000000e)>>1)
#define BANK_TYPE0_F3_WR(src)                    (((u32)(src)<<1) & 0x0000000e)
#define BANK_TYPE0_F3_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields bank_valid	 */
#define BANK_VALID0_F3_WIDTH                                                  1
#define BANK_VALID0_F3_SHIFT                                                  0
#define BANK_VALID0_F3_MASK                                          0x00000001
#define BANK_VALID0_F3_RD(src)                           (((src) & 0x00000001))
#define BANK_VALID0_F3_WR(src)                      (((u32)(src)) & 0x00000001)
#define BANK_VALID0_F3_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank3_start_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F7_WIDTH                                                14
#define REGSPEC_ADDR_F7_SHIFT                                                 0
#define REGSPEC_ADDR_F7_MASK                                         0x00003fff
#define REGSPEC_ADDR_F7_RD(src)                          (((src) & 0x00003fff))
#define REGSPEC_ADDR_F7_WR(src)                     (((u32)(src)) & 0x00003fff)
#define REGSPEC_ADDR_F7_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register gfc_bank3_end_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F8_WIDTH                                                15
#define REGSPEC_ADDR_F8_SHIFT                                                 0
#define REGSPEC_ADDR_F8_MASK                                         0x00007fff
#define REGSPEC_ADDR_F8_RD(src)                          (((src) & 0x00007fff))
#define REGSPEC_ADDR_F8_WR(src)                     (((u32)(src)) & 0x00007fff)
#define REGSPEC_ADDR_F8_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register gfc_bank3_base_add	*/
/*	 Fields bank_base_add	 */
#define BANK_BASE_ADD_F3_WIDTH                                               32
#define BANK_BASE_ADD_F3_SHIFT                                                0
#define BANK_BASE_ADD_F3_MASK                                        0xffffffff
#define BANK_BASE_ADD_F3_RD(src)                         (((src) & 0xffffffff))
#define BANK_BASE_ADD_F3_WR(src)                    (((u32)(src)) & 0xffffffff)
#define BANK_BASE_ADD_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_dma_ctrl0	*/
/*	 Fields complNum_4_int	 */
#define COMPLNUM_4_INT0_F3_WIDTH                                              3
#define COMPLNUM_4_INT0_F3_SHIFT                                             10
#define COMPLNUM_4_INT0_F3_MASK                                      0x00001c00
#define COMPLNUM_4_INT0_F3_RD(src)                   (((src) & 0x00001c00)>>10)
#define COMPLNUM_4_INT0_F3_WR(src)              (((u32)(src)<<10) & 0x00001c00)
#define COMPLNUM_4_INT0_F3_SET(dst,src) \
                      (((dst) & ~0x00001c00) | (((u32)(src)<<10) & 0x00001c00))
/*	 Fields dma_cmd_code	 */
#define DMA_CMD_CODE0_F3_WIDTH                                                3
#define DMA_CMD_CODE0_F3_SHIFT                                                7
#define DMA_CMD_CODE0_F3_MASK                                        0x00000380
#define DMA_CMD_CODE0_F3_RD(src)                      (((src) & 0x00000380)>>7)
#define DMA_CMD_CODE0_F3_WR(src)                 (((u32)(src)<<7) & 0x00000380)
#define DMA_CMD_CODE0_F3_SET(dst,src) \
                       (((dst) & ~0x00000380) | (((u32)(src)<<7) & 0x00000380))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID0_F3_WIDTH                                                  2
#define DMA_CMD_ID0_F3_SHIFT                                                  3
#define DMA_CMD_ID0_F3_MASK                                          0x00000018
#define DMA_CMD_ID0_F3_RD(src)                        (((src) & 0x00000018)>>3)
#define DMA_CMD_ID0_F3_WR(src)                   (((u32)(src)<<3) & 0x00000018)
#define DMA_CMD_ID0_F3_SET(dst,src) \
                       (((dst) & ~0x00000018) | (((u32)(src)<<3) & 0x00000018))
/*	 Fields dma_cmd_pop	 */
#define DMA_CMD_POP0_F3_WIDTH                                                 1
#define DMA_CMD_POP0_F3_SHIFT                                                 2
#define DMA_CMD_POP0_F3_MASK                                         0x00000004
#define DMA_CMD_POP0_F3_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_CMD_POP0_F3_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_CMD_POP0_F3_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dma_cmd_push	 */
#define DMA_CMD_PUSH0_F3_WIDTH                                                1
#define DMA_CMD_PUSH0_F3_SHIFT                                                1
#define DMA_CMD_PUSH0_F3_MASK                                        0x00000002
#define DMA_CMD_PUSH0_F3_RD(src)                      (((src) & 0x00000002)>>1)
#define DMA_CMD_PUSH0_F3_WR(src)                 (((u32)(src)<<1) & 0x00000002)
#define DMA_CMD_PUSH0_F3_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dma_cmd_valid	 */
#define DMA_CMD_VALID0_F3_WIDTH                                               1
#define DMA_CMD_VALID0_F3_SHIFT                                               0
#define DMA_CMD_VALID0_F3_MASK                                       0x00000001
#define DMA_CMD_VALID0_F3_RD(src)                        (((src) & 0x00000001))
#define DMA_CMD_VALID0_F3_WR(src)                   (((u32)(src)) & 0x00000001)
#define DMA_CMD_VALID0_F3_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank3_dma_start_add0	*/
/*	 Fields dma_start_add0	 */
#define DMA_START_ADD00_F3_WIDTH                                             32
#define DMA_START_ADD00_F3_SHIFT                                              0
#define DMA_START_ADD00_F3_MASK                                      0xffffffff
#define DMA_START_ADD00_F3_RD(src)                       (((src) & 0xffffffff))
#define DMA_START_ADD00_F3_WR(src)                  (((u32)(src)) & 0xffffffff)
#define DMA_START_ADD00_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_dma_start_add1	*/
/*	 Fields dma_start_add1	 */
#define DMA_START_ADD11_F3_WIDTH                                             10
#define DMA_START_ADD11_F3_SHIFT                                              0
#define DMA_START_ADD11_F3_MASK                                      0x000003ff
#define DMA_START_ADD11_F3_RD(src)                       (((src) & 0x000003ff))
#define DMA_START_ADD11_F3_WR(src)                  (((u32)(src)) & 0x000003ff)
#define DMA_START_ADD11_F3_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank3_dma_des_add0	*/
/*	 Fields dma_des_add0	 */
#define DMA_DES_ADD00_F3_WIDTH                                               32
#define DMA_DES_ADD00_F3_SHIFT                                                0
#define DMA_DES_ADD00_F3_MASK                                        0xffffffff
#define DMA_DES_ADD00_F3_RD(src)                         (((src) & 0xffffffff))
#define DMA_DES_ADD00_F3_WR(src)                    (((u32)(src)) & 0xffffffff)
#define DMA_DES_ADD00_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_dma_des_add1	*/
/*	 Fields dma_des_add1	 */
#define DMA_DES_ADD11_F3_WIDTH                                               10
#define DMA_DES_ADD11_F3_SHIFT                                                0
#define DMA_DES_ADD11_F3_MASK                                        0x000003ff
#define DMA_DES_ADD11_F3_RD(src)                         (((src) & 0x000003ff))
#define DMA_DES_ADD11_F3_WR(src)                    (((u32)(src)) & 0x000003ff)
#define DMA_DES_ADD11_F3_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank3_dma_status	*/
/*	 Fields bits_corrected_ecc	 */
#define BITS_CORRECTED_ECC_F3_WIDTH                                           4
#define BITS_CORRECTED_ECC_F3_SHIFT                                          14
#define BITS_CORRECTED_ECC_F3_MASK                                   0x0003c000
#define BITS_CORRECTED_ECC_F3_RD(src)                (((src) & 0x0003c000)>>14)
#define BITS_CORRECTED_ECC_F3_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields dma_err	 */
#define DMA_ERR_F3_WIDTH                                                      3
#define DMA_ERR_F3_SHIFT                                                      9
#define DMA_ERR_F3_MASK                                              0x00000e00
#define DMA_ERR_F3_RD(src)                            (((src) & 0x00000e00)>>9)
#define DMA_ERR_F3_SET(dst,src) \
                       (((dst) & ~0x00000e00) | (((u32)(src)<<9) & 0x00000e00))
/*	 Fields dma_cmpl_status	 */
#define DMA_CMPL_STATUS_F3_WIDTH                                              2
#define DMA_CMPL_STATUS_F3_SHIFT                                              6
#define DMA_CMPL_STATUS_F3_MASK                                      0x000000c0
#define DMA_CMPL_STATUS_F3_RD(src)                    (((src) & 0x000000c0)>>6)
#define DMA_CMPL_STATUS_F3_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID_F3_WIDTH                                                   2
#define DMA_CMD_ID_F3_SHIFT                                                   1
#define DMA_CMD_ID_F3_MASK                                           0x00000006
#define DMA_CMD_ID_F3_RD(src)                         (((src) & 0x00000006)>>1)
#define DMA_CMD_ID_F3_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields dma_cmpl_valid	 */
#define DMA_CMPL_VALID_F3_WIDTH                                               1
#define DMA_CMPL_VALID_F3_SHIFT                                               0
#define DMA_CMPL_VALID_F3_MASK                                       0x00000001
#define DMA_CMPL_VALID_F3_RD(src)                        (((src) & 0x00000001))
#define DMA_CMPL_VALID_F3_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank3_dma_eccerr0_add_col	*/
/*	 Fields dma_eccerr0_add_col	 */
#define DMA_ECCERR0_ADD_COL_F3_WIDTH                                         32
#define DMA_ECCERR0_ADD_COL_F3_SHIFT                                          0
#define DMA_ECCERR0_ADD_COL_F3_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_COL_F3_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_COL_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_dma_eccerr0_add_row	*/
/*	 Fields dma_eccerr0_add_row	 */
#define DMA_ECCERR0_ADD_ROW_F3_WIDTH                                         32
#define DMA_ECCERR0_ADD_ROW_F3_SHIFT                                          0
#define DMA_ECCERR0_ADD_ROW_F3_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_ROW_F3_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_ROW_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_dma_eccerr1_add_col	*/
/*	 Fields dma_eccerr1_add_col	 */
#define DMA_ECCERR1_ADD_COL_F3_WIDTH                                         32
#define DMA_ECCERR1_ADD_COL_F3_SHIFT                                          0
#define DMA_ECCERR1_ADD_COL_F3_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_COL_F3_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_COL_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_dma_eccerr1_add_row	*/
/*	 Fields dma_eccerr1_add_row	 */
#define DMA_ECCERR1_ADD_ROW_F3_WIDTH                                         32
#define DMA_ECCERR1_ADD_ROW_F3_SHIFT                                          0
#define DMA_ECCERR1_ADD_ROW_F3_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_ROW_F3_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_ROW_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_INT	*/
/*	 Fields nandpio_device_protection_err	 */
#define NANDPIO_DEVICE_PROTECTION_ERR_F3_WIDTH                                1
#define NANDPIO_DEVICE_PROTECTION_ERR_F3_SHIFT                               11
#define NANDPIO_DEVICE_PROTECTION_ERR_F3_MASK                        0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERR_F3_RD(src)     (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERR_F3_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERR_F3_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields norp_device_protection_err	 */
#define NORP_DEVICE_PROTECTION_ERR_F3_WIDTH                                   1
#define NORP_DEVICE_PROTECTION_ERR_F3_SHIFT                                  10
#define NORP_DEVICE_PROTECTION_ERR_F3_MASK                           0x00000400
#define NORP_DEVICE_PROTECTION_ERR_F3_RD(src)        (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERR_F3_WR(src)   (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERR_F3_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields dma_cmd_override_err	 */
#define DMA_CMD_OVERRIDE_ERR_F3_WIDTH                                         1
#define DMA_CMD_OVERRIDE_ERR_F3_SHIFT                                         9
#define DMA_CMD_OVERRIDE_ERR_F3_MASK                                 0x00000200
#define DMA_CMD_OVERRIDE_ERR_F3_RD(src)               (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERR_F3_WR(src)          (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERR_F3_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields device_protection_err	 */
#define DEVICE_PROTECTION_ERR_F3_WIDTH                                        1
#define DEVICE_PROTECTION_ERR_F3_SHIFT                                        8
#define DEVICE_PROTECTION_ERR_F3_MASK                                0x00000100
#define DEVICE_PROTECTION_ERR_F3_RD(src)              (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERR_F3_WR(src)         (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERR_F3_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields transaction_timeout	 */
#define TRANSACTION_TIMEOUT_F3_WIDTH                                          1
#define TRANSACTION_TIMEOUT_F3_SHIFT                                          7
#define TRANSACTION_TIMEOUT_F3_MASK                                  0x00000080
#define TRANSACTION_TIMEOUT_F3_RD(src)                (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUT_F3_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUT_F3_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields parity_err	 */
#define PARITY_ERR_F3_WIDTH                                                   1
#define PARITY_ERR_F3_SHIFT                                                   6
#define PARITY_ERR_F3_MASK                                           0x00000040
#define PARITY_ERR_F3_RD(src)                         (((src) & 0x00000040)>>6)
#define PARITY_ERR_F3_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERR_F3_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ecc_err_single	 */
#define ECC_ERR_SINGLE_F3_WIDTH                                               1
#define ECC_ERR_SINGLE_F3_SHIFT                                               5
#define ECC_ERR_SINGLE_F3_MASK                                       0x00000020
#define ECC_ERR_SINGLE_F3_RD(src)                     (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLE_F3_WR(src)                (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLE_F3_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ecc_err_multiple	 */
#define ECC_ERR_MULTIPLE_F3_WIDTH                                             1
#define ECC_ERR_MULTIPLE_F3_SHIFT                                             4
#define ECC_ERR_MULTIPLE_F3_MASK                                     0x00000010
#define ECC_ERR_MULTIPLE_F3_RD(src)                   (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLE_F3_WR(src)              (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLE_F3_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields dma_done	 */
#define DMA_DONE_F3_WIDTH                                                     1
#define DMA_DONE_F3_SHIFT                                                     2
#define DMA_DONE_F3_MASK                                             0x00000004
#define DMA_DONE_F3_RD(src)                           (((src) & 0x00000004)>>2)
#define DMA_DONE_F3_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define DMA_DONE_F3_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank3_interruptMask	*/
/*    Mask Register Fields nandpio_device_protection_errMask    */
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F3_WIDTH                            1
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F3_SHIFT                           11
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F3_MASK                    0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F3_RD(src) \
                                                    (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F3_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F3_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields norp_device_protection_errMask    */
#define NORP_DEVICE_PROTECTION_ERRMASK_F3_WIDTH                               1
#define NORP_DEVICE_PROTECTION_ERRMASK_F3_SHIFT                              10
#define NORP_DEVICE_PROTECTION_ERRMASK_F3_MASK                       0x00000400
#define NORP_DEVICE_PROTECTION_ERRMASK_F3_RD(src)    (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERRMASK_F3_WR(src) \
                                                (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERRMASK_F3_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields dma_cmd_override_errMask    */
#define DMA_CMD_OVERRIDE_ERRMASK_F3_WIDTH                                     1
#define DMA_CMD_OVERRIDE_ERRMASK_F3_SHIFT                                     9
#define DMA_CMD_OVERRIDE_ERRMASK_F3_MASK                             0x00000200
#define DMA_CMD_OVERRIDE_ERRMASK_F3_RD(src)           (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERRMASK_F3_WR(src)      (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERRMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields device_protection_errMask    */
#define DEVICE_PROTECTION_ERRMASK_F3_WIDTH                                    1
#define DEVICE_PROTECTION_ERRMASK_F3_SHIFT                                    8
#define DEVICE_PROTECTION_ERRMASK_F3_MASK                            0x00000100
#define DEVICE_PROTECTION_ERRMASK_F3_RD(src)          (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERRMASK_F3_WR(src)     (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERRMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields transaction_timeoutMask    */
#define TRANSACTION_TIMEOUTMASK_F3_WIDTH                                      1
#define TRANSACTION_TIMEOUTMASK_F3_SHIFT                                      7
#define TRANSACTION_TIMEOUTMASK_F3_MASK                              0x00000080
#define TRANSACTION_TIMEOUTMASK_F3_RD(src)            (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUTMASK_F3_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUTMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields parity_errMask    */
#define PARITY_ERRMASK_F3_WIDTH                                               1
#define PARITY_ERRMASK_F3_SHIFT                                               6
#define PARITY_ERRMASK_F3_MASK                                       0x00000040
#define PARITY_ERRMASK_F3_RD(src)                     (((src) & 0x00000040)>>6)
#define PARITY_ERRMASK_F3_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERRMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ecc_err_singleMask    */
#define ECC_ERR_SINGLEMASK_F3_WIDTH                                           1
#define ECC_ERR_SINGLEMASK_F3_SHIFT                                           5
#define ECC_ERR_SINGLEMASK_F3_MASK                                   0x00000020
#define ECC_ERR_SINGLEMASK_F3_RD(src)                 (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLEMASK_F3_WR(src)            (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLEMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ecc_err_multipleMask    */
#define ECC_ERR_MULTIPLEMASK_F3_WIDTH                                         1
#define ECC_ERR_MULTIPLEMASK_F3_SHIFT                                         4
#define ECC_ERR_MULTIPLEMASK_F3_MASK                                 0x00000010
#define ECC_ERR_MULTIPLEMASK_F3_RD(src)               (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLEMASK_F3_WR(src)          (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLEMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields dma_doneMask    */
#define DMA_DONEMASK_F3_WIDTH                                                 1
#define DMA_DONEMASK_F3_SHIFT                                                 2
#define DMA_DONEMASK_F3_MASK                                         0x00000004
#define DMA_DONEMASK_F3_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_DONEMASK_F3_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_DONEMASK_F3_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank3_sram_ctrl0	*/
/*	 Fields rtc	 */
#define REGSPEC_RTC0_F3_WIDTH                                                 3
#define REGSPEC_RTC0_F3_SHIFT                                                12
#define REGSPEC_RTC0_F3_MASK                                         0x00007000
#define REGSPEC_RTC0_F3_RD(src)                      (((src) & 0x00007000)>>12)
#define REGSPEC_RTC0_F3_WR(src)                 (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_RTC0_F3_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields muxen	 */
#define MUXEN0_F3_WIDTH                                                       1
#define MUXEN0_F3_SHIFT                                                      10
#define MUXEN0_F3_MASK                                               0x00000400
#define MUXEN0_F3_RD(src)                            (((src) & 0x00000400)>>10)
#define MUXEN0_F3_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define MUXEN0_F3_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rdy_timeout_cnt	 */
#define RDY_TIMEOUT_CNT0_F3_WIDTH                                             3
#define RDY_TIMEOUT_CNT0_F3_SHIFT                                             2
#define RDY_TIMEOUT_CNT0_F3_MASK                                     0x0000001c
#define RDY_TIMEOUT_CNT0_F3_RD(src)                   (((src) & 0x0000001c)>>2)
#define RDY_TIMEOUT_CNT0_F3_WR(src)              (((u32)(src)<<2) & 0x0000001c)
#define RDY_TIMEOUT_CNT0_F3_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields ptd	 */
#define PTD0_F3_WIDTH                                                         1
#define PTD0_F3_SHIFT                                                         1
#define PTD0_F3_MASK                                                 0x00000002
#define PTD0_F3_RD(src)                               (((src) & 0x00000002)>>1)
#define PTD0_F3_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PTD0_F3_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields le	 */
#define LE0_F3_WIDTH                                                          1
#define LE0_F3_SHIFT                                                          0
#define LE0_F3_MASK                                                  0x00000001
#define LE0_F3_RD(src)                                   (((src) & 0x00000001))
#define LE0_F3_WR(src)                              (((u32)(src)) & 0x00000001)
#define LE0_F3_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank3_sram_nor_ctrl1	*/
/*	 Fields BME	 */
#define BME1_F3_WIDTH                                                         1
#define BME1_F3_SHIFT                                                        31
#define BME1_F3_MASK                                                 0x80000000
#define BME1_F3_RD(src)                              (((src) & 0x80000000)>>31)
#define BME1_F3_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define BME1_F3_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields OEO	 */
#define OEO1_F3_WIDTH                                                         1
#define OEO1_F3_SHIFT                                                        30
#define OEO1_F3_MASK                                                 0x40000000
#define OEO1_F3_RD(src)                              (((src) & 0x40000000)>>30)
#define OEO1_F3_WR(src)                         (((u32)(src)<<30) & 0x40000000)
#define OEO1_F3_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields BWT	 */
#define BWT1_F3_WIDTH                                                         5
#define BWT1_F3_SHIFT                                                        20
#define BWT1_F3_MASK                                                 0x01f00000
#define BWT1_F3_RD(src)                              (((src) & 0x01f00000)>>20)
#define BWT1_F3_WR(src)                         (((u32)(src)<<20) & 0x01f00000)
#define BWT1_F3_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields FWT	 */
#define FWT1_F3_WIDTH                                                         7
#define FWT1_F3_SHIFT                                                        12
#define FWT1_F3_MASK                                                 0x0007f000
#define FWT1_F3_RD(src)                              (((src) & 0x0007f000)>>12)
#define FWT1_F3_WR(src)                         (((u32)(src)<<12) & 0x0007f000)
#define FWT1_F3_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields TWT	 */
#define TWT1_F3_WIDTH                                                        10
#define TWT1_F3_SHIFT                                                         0
#define TWT1_F3_MASK                                                 0x000003ff
#define TWT1_F3_RD(src)                                  (((src) & 0x000003ff))
#define TWT1_F3_WR(src)                             (((u32)(src)) & 0x000003ff)
#define TWT1_F3_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank3_sram_nor_ctrl2	*/
/*	 Fields ALN	 */
#define ALN2_F3_WIDTH                                                         4
#define ALN2_F3_SHIFT                                                        28
#define ALN2_F3_MASK                                                 0xf0000000
#define ALN2_F3_RD(src)                              (((src) & 0xf0000000)>>28)
#define ALN2_F3_WR(src)                         (((u32)(src)<<28) & 0xf0000000)
#define ALN2_F3_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields PEN	 */
#define PEN2_F3_WIDTH                                                         1
#define PEN2_F3_SHIFT                                                        27
#define PEN2_F3_MASK                                                 0x08000000
#define PEN2_F3_RD(src)                              (((src) & 0x08000000)>>27)
#define PEN2_F3_WR(src)                         (((u32)(src)<<27) & 0x08000000)
#define PEN2_F3_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields BEM	 */
#define BEM2_F3_WIDTH                                                         1
#define BEM2_F3_SHIFT                                                        26
#define BEM2_F3_MASK                                                 0x04000000
#define BEM2_F3_RD(src)                              (((src) & 0x04000000)>>26)
#define BEM2_F3_WR(src)                         (((u32)(src)<<26) & 0x04000000)
#define BEM2_F3_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SOR	 */
#define SOR2_F3_WIDTH                                                         1
#define SOR2_F3_SHIFT                                                        25
#define SOR2_F3_MASK                                                 0x02000000
#define SOR2_F3_RD(src)                              (((src) & 0x02000000)>>25)
#define SOR2_F3_WR(src)                         (((u32)(src)<<25) & 0x02000000)
#define SOR2_F3_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RE	 */
#define RE2_F3_WIDTH                                                          1
#define RE2_F3_SHIFT                                                         24
#define RE2_F3_MASK                                                  0x01000000
#define RE2_F3_RD(src)                               (((src) & 0x01000000)>>24)
#define RE2_F3_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define RE2_F3_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields TH	 */
#define TH2_F3_WIDTH                                                          5
#define TH2_F3_SHIFT                                                         16
#define TH2_F3_MASK                                                  0x001f0000
#define TH2_F3_RD(src)                               (((src) & 0x001f0000)>>16)
#define TH2_F3_WR(src)                          (((u32)(src)<<16) & 0x001f0000)
#define TH2_F3_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WBF	 */
#define WBF2_F3_WIDTH                                                         4
#define WBF2_F3_SHIFT                                                        12
#define WBF2_F3_MASK                                                 0x0000f000
#define WBF2_F3_RD(src)                              (((src) & 0x0000f000)>>12)
#define WBF2_F3_WR(src)                         (((u32)(src)<<12) & 0x0000f000)
#define WBF2_F3_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WBN	 */
#define WBN2_F3_WIDTH                                                         4
#define WBN2_F3_SHIFT                                                         8
#define WBN2_F3_MASK                                                 0x00000f00
#define WBN2_F3_RD(src)                               (((src) & 0x00000f00)>>8)
#define WBN2_F3_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define WBN2_F3_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields OEN	 */
#define OEN2_F3_WIDTH                                                         4
#define OEN2_F3_SHIFT                                                         4
#define OEN2_F3_MASK                                                 0x000000f0
#define OEN2_F3_RD(src)                               (((src) & 0x000000f0)>>4)
#define OEN2_F3_WR(src)                          (((u32)(src)<<4) & 0x000000f0)
#define OEN2_F3_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields CSN	 */
#define CSN2_F3_WIDTH                                                         4
#define CSN2_F3_SHIFT                                                         0
#define CSN2_F3_MASK                                                 0x0000000f
#define CSN2_F3_RD(src)                                  (((src) & 0x0000000f))
#define CSN2_F3_WR(src)                             (((u32)(src)) & 0x0000000f)
#define CSN2_F3_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_bank3_nand_ctrl0	*/
/*	 Fields SPARE_OFFSET	 */
#define SPARE_OFFSET0_F3_WIDTH                                               16
#define SPARE_OFFSET0_F3_SHIFT                                               16
#define SPARE_OFFSET0_F3_MASK                                        0xffff0000
#define SPARE_OFFSET0_F3_RD(src)                     (((src) & 0xffff0000)>>16)
#define SPARE_OFFSET0_F3_WR(src)                (((u32)(src)<<16) & 0xffff0000)
#define SPARE_OFFSET0_F3_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields FORCE_SPARE_OFFSET	 */
#define FORCE_SPARE_OFFSET0_F3_WIDTH                                          1
#define FORCE_SPARE_OFFSET0_F3_SHIFT                                          9
#define FORCE_SPARE_OFFSET0_F3_MASK                                  0x00000200
#define FORCE_SPARE_OFFSET0_F3_RD(src)                (((src) & 0x00000200)>>9)
#define FORCE_SPARE_OFFSET0_F3_WR(src)           (((u32)(src)<<9) & 0x00000200)
#define FORCE_SPARE_OFFSET0_F3_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ECC_Algorithm	 */
#define ECC_ALGORITHM0_F3_WIDTH                                               1
#define ECC_ALGORITHM0_F3_SHIFT                                               8
#define ECC_ALGORITHM0_F3_MASK                                       0x00000100
#define ECC_ALGORITHM0_F3_RD(src)                     (((src) & 0x00000100)>>8)
#define ECC_ALGORITHM0_F3_WR(src)                (((u32)(src)<<8) & 0x00000100)
#define ECC_ALGORITHM0_F3_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ECC_ON_OFF	 */
#define ECC_ON_OFF0_F3_WIDTH                                                  1
#define ECC_ON_OFF0_F3_SHIFT                                                  7
#define ECC_ON_OFF0_F3_MASK                                          0x00000080
#define ECC_ON_OFF0_F3_RD(src)                        (((src) & 0x00000080)>>7)
#define ECC_ON_OFF0_F3_WR(src)                   (((u32)(src)<<7) & 0x00000080)
#define ECC_ON_OFF0_F3_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))

/*	Register gfc_bank3_nand_ctrl1	*/

/*	Register gfc_bank3_nand_ctrl2	*/

/*	Register gfc_bank3_nand_bch	*/
/*	 Fields bch_k	 */
#define BCH_K_F3_WIDTH                                                        3
#define BCH_K_F3_SHIFT                                                       20
#define BCH_K_F3_MASK                                                0x00700000
#define BCH_K_F3_RD(src)                             (((src) & 0x00700000)>>20)
#define BCH_K_F3_WR(src)                        (((u32)(src)<<20) & 0x00700000)
#define BCH_K_F3_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields bch_t	 */
#define BCH_T_F3_WIDTH                                                        4
#define BCH_T_F3_SHIFT                                                       16
#define BCH_T_F3_MASK                                                0x000f0000
#define BCH_T_F3_RD(src)                             (((src) & 0x000f0000)>>16)
#define BCH_T_F3_WR(src)                        (((u32)(src)<<16) & 0x000f0000)
#define BCH_T_F3_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields bch_n	 */
#define BCH_N_F3_WIDTH                                                       16
#define BCH_N_F3_SHIFT                                                        0
#define BCH_N_F3_MASK                                                0x0000ffff
#define BCH_N_F3_RD(src)                                 (((src) & 0x0000ffff))
#define BCH_N_F3_WR(src)                            (((u32)(src)) & 0x0000ffff)
#define BCH_N_F3_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank3_dma_ctrl1	*/
/*	 Fields dma_data_size	 */
#define DMA_DATA_SIZE1_F3_WIDTH                                              24
#define DMA_DATA_SIZE1_F3_SHIFT                                               0
#define DMA_DATA_SIZE1_F3_MASK                                       0x00ffffff
#define DMA_DATA_SIZE1_F3_RD(src)                        (((src) & 0x00ffffff))
#define DMA_DATA_SIZE1_F3_WR(src)                   (((u32)(src)) & 0x00ffffff)
#define DMA_DATA_SIZE1_F3_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_bank3_nand_ctrl3	*/
/*	 Fields page_size	 */
#define PAGE_SIZE3_F3_WIDTH                                                  16
#define PAGE_SIZE3_F3_SHIFT                                                   0
#define PAGE_SIZE3_F3_MASK                                           0x0000ffff
#define PAGE_SIZE3_F3_RD(src)                            (((src) & 0x0000ffff))
#define PAGE_SIZE3_F3_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define PAGE_SIZE3_F3_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank3_nand_ctrl4	*/
/*	 Fields device_size	 */
#define DEVICE_SIZE4_F3_WIDTH                                                16
#define DEVICE_SIZE4_F3_SHIFT                                                16
#define DEVICE_SIZE4_F3_MASK                                         0xffff0000
#define DEVICE_SIZE4_F3_RD(src)                      (((src) & 0xffff0000)>>16)
#define DEVICE_SIZE4_F3_WR(src)                 (((u32)(src)<<16) & 0xffff0000)
#define DEVICE_SIZE4_F3_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields block_size	 */
#define BLOCK_SIZE4_F3_WIDTH                                                 16
#define BLOCK_SIZE4_F3_SHIFT                                                  0
#define BLOCK_SIZE4_F3_MASK                                          0x0000ffff
#define BLOCK_SIZE4_F3_RD(src)                           (((src) & 0x0000ffff))
#define BLOCK_SIZE4_F3_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define BLOCK_SIZE4_F3_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank3_nand_timing0	*/
/*	 Fields t_adl	 */
#define T_ADL0_F3_WIDTH                                                       8
#define T_ADL0_F3_SHIFT                                                      24
#define T_ADL0_F3_MASK                                               0xff000000
#define T_ADL0_F3_RD(src)                            (((src) & 0xff000000)>>24)
#define T_ADL0_F3_WR(src)                       (((u32)(src)<<24) & 0xff000000)
#define T_ADL0_F3_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_wb	 */
#define T_WB0_F3_WIDTH                                                        8
#define T_WB0_F3_SHIFT                                                       16
#define T_WB0_F3_MASK                                                0x00ff0000
#define T_WB0_F3_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WB0_F3_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WB0_F3_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_rhw	 */
#define T_RHW0_F3_WIDTH                                                       8
#define T_RHW0_F3_SHIFT                                                       8
#define T_RHW0_F3_MASK                                               0x0000ff00
#define T_RHW0_F3_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_RHW0_F3_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_RHW0_F3_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_ccs	 */
#define T_CCS0_F3_WIDTH                                                       8
#define T_CCS0_F3_SHIFT                                                       0
#define T_CCS0_F3_MASK                                               0x000000ff
#define T_CCS0_F3_RD(src)                                (((src) & 0x000000ff))
#define T_CCS0_F3_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CCS0_F3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank3_nand_timing1	*/
/*	 Fields t_alh_clh_ch	 */
#define T_ALH_CLH_CH1_F3_WIDTH                                                8
#define T_ALH_CLH_CH1_F3_SHIFT                                               24
#define T_ALH_CLH_CH1_F3_MASK                                        0xff000000
#define T_ALH_CLH_CH1_F3_RD(src)                     (((src) & 0xff000000)>>24)
#define T_ALH_CLH_CH1_F3_WR(src)                (((u32)(src)<<24) & 0xff000000)
#define T_ALH_CLH_CH1_F3_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_als_cls_cs	 */
#define T_ALS_CLS_CS1_F3_WIDTH                                                8
#define T_ALS_CLS_CS1_F3_SHIFT                                               16
#define T_ALS_CLS_CS1_F3_MASK                                        0x00ff0000
#define T_ALS_CLS_CS1_F3_RD(src)                     (((src) & 0x00ff0000)>>16)
#define T_ALS_CLS_CS1_F3_WR(src)                (((u32)(src)<<16) & 0x00ff0000)
#define T_ALS_CLS_CS1_F3_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_ds_wp	 */
#define T_DS_WP1_F3_WIDTH                                                     8
#define T_DS_WP1_F3_SHIFT                                                     8
#define T_DS_WP1_F3_MASK                                             0x0000ff00
#define T_DS_WP1_F3_RD(src)                           (((src) & 0x0000ff00)>>8)
#define T_DS_WP1_F3_WR(src)                      (((u32)(src)<<8) & 0x0000ff00)
#define T_DS_WP1_F3_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_dh_wh	 */
#define T_DH_WH1_F3_WIDTH                                                     8
#define T_DH_WH1_F3_SHIFT                                                     0
#define T_DH_WH1_F3_MASK                                             0x000000ff
#define T_DH_WH1_F3_RD(src)                              (((src) & 0x000000ff))
#define T_DH_WH1_F3_WR(src)                         (((u32)(src)) & 0x000000ff)
#define T_DH_WH1_F3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank3_nand_timing2	*/
/*	 Fields t_ar_clr_whr_ir	 */
#define T_AR_CLR_WHR_IR2_F3_WIDTH                                             8
#define T_AR_CLR_WHR_IR2_F3_SHIFT                                            24
#define T_AR_CLR_WHR_IR2_F3_MASK                                     0xff000000
#define T_AR_CLR_WHR_IR2_F3_RD(src)                  (((src) & 0xff000000)>>24)
#define T_AR_CLR_WHR_IR2_F3_WR(src)             (((u32)(src)<<24) & 0xff000000)
#define T_AR_CLR_WHR_IR2_F3_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_rr	 */
#define T_RR2_F3_WIDTH                                                        8
#define T_RR2_F3_SHIFT                                                       16
#define T_RR2_F3_MASK                                                0x00ff0000
#define T_RR2_F3_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_RR2_F3_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_RR2_F3_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_reh	 */
#define T_REH2_F3_WIDTH                                                       8
#define T_REH2_F3_SHIFT                                                       8
#define T_REH2_F3_MASK                                               0x0000ff00
#define T_REH2_F3_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_REH2_F3_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_REH2_F3_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_rp	 */
#define T_RP2_F3_WIDTH                                                        8
#define T_RP2_F3_SHIFT                                                        0
#define T_RP2_F3_MASK                                                0x000000ff
#define T_RP2_F3_RD(src)                                 (((src) & 0x000000ff))
#define T_RP2_F3_WR(src)                            (((u32)(src)) & 0x000000ff)
#define T_RP2_F3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank3_nand_timing3	*/
/*	 Fields t_ww	 */
#define T_WW3_F3_WIDTH                                                        8
#define T_WW3_F3_SHIFT                                                       16
#define T_WW3_F3_MASK                                                0x00ff0000
#define T_WW3_F3_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WW3_F3_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WW3_F3_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_chz	 */
#define T_CHZ3_F3_WIDTH                                                       8
#define T_CHZ3_F3_SHIFT                                                       8
#define T_CHZ3_F3_MASK                                               0x0000ff00
#define T_CHZ3_F3_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_CHZ3_F3_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_CHZ3_F3_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_cea	 */
#define T_CEA3_F3_WIDTH                                                       8
#define T_CEA3_F3_SHIFT                                                       0
#define T_CEA3_F3_MASK                                               0x000000ff
#define T_CEA3_F3_RD(src)                                (((src) & 0x000000ff))
#define T_CEA3_F3_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CEA3_F3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank3_nand_cor_err	*/
/*	 Fields counter	 */
#define COUNTER_F7_WIDTH                                                     32
#define COUNTER_F7_SHIFT                                                      0
#define COUNTER_F7_MASK                                              0xffffffff
#define COUNTER_F7_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank3_nand_uncor_err	*/
/*	 Fields counter	 */
#define COUNTER_F8_WIDTH                                                     32
#define COUNTER_F8_SHIFT                                                      0
#define COUNTER_F8_MASK                                              0xffffffff
#define COUNTER_F8_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_ctrl0	*/
/*	 Fields nand_wp_n	 */
#define NAND_WP_N0_F4_WIDTH                                                   1
#define NAND_WP_N0_F4_SHIFT                                                   8
#define NAND_WP_N0_F4_MASK                                           0x00000100
#define NAND_WP_N0_F4_RD(src)                         (((src) & 0x00000100)>>8)
#define NAND_WP_N0_F4_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define NAND_WP_N0_F4_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bus_width	 */
#define BUS_WIDTH0_F4_WIDTH                                                   2
#define BUS_WIDTH0_F4_SHIFT                                                   6
#define BUS_WIDTH0_F4_MASK                                           0x000000c0
#define BUS_WIDTH0_F4_RD(src)                         (((src) & 0x000000c0)>>6)
#define BUS_WIDTH0_F4_WR(src)                    (((u32)(src)<<6) & 0x000000c0)
#define BUS_WIDTH0_F4_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields bus_usage	 */
#define BUS_USAGE0_F4_WIDTH                                                   2
#define BUS_USAGE0_F4_SHIFT                                                   4
#define BUS_USAGE0_F4_MASK                                           0x00000030
#define BUS_USAGE0_F4_RD(src)                         (((src) & 0x00000030)>>4)
#define BUS_USAGE0_F4_WR(src)                    (((u32)(src)<<4) & 0x00000030)
#define BUS_USAGE0_F4_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields bank_type	 */
#define BANK_TYPE0_F4_WIDTH                                                   3
#define BANK_TYPE0_F4_SHIFT                                                   1
#define BANK_TYPE0_F4_MASK                                           0x0000000e
#define BANK_TYPE0_F4_RD(src)                         (((src) & 0x0000000e)>>1)
#define BANK_TYPE0_F4_WR(src)                    (((u32)(src)<<1) & 0x0000000e)
#define BANK_TYPE0_F4_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields bank_valid	 */
#define BANK_VALID0_F4_WIDTH                                                  1
#define BANK_VALID0_F4_SHIFT                                                  0
#define BANK_VALID0_F4_MASK                                          0x00000001
#define BANK_VALID0_F4_RD(src)                           (((src) & 0x00000001))
#define BANK_VALID0_F4_WR(src)                      (((u32)(src)) & 0x00000001)
#define BANK_VALID0_F4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank4_start_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F9_WIDTH                                                14
#define REGSPEC_ADDR_F9_SHIFT                                                 0
#define REGSPEC_ADDR_F9_MASK                                         0x00003fff
#define REGSPEC_ADDR_F9_RD(src)                          (((src) & 0x00003fff))
#define REGSPEC_ADDR_F9_WR(src)                     (((u32)(src)) & 0x00003fff)
#define REGSPEC_ADDR_F9_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register gfc_bank4_end_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F10_WIDTH                                               15
#define REGSPEC_ADDR_F10_SHIFT                                                0
#define REGSPEC_ADDR_F10_MASK                                        0x00007fff
#define REGSPEC_ADDR_F10_RD(src)                         (((src) & 0x00007fff))
#define REGSPEC_ADDR_F10_WR(src)                    (((u32)(src)) & 0x00007fff)
#define REGSPEC_ADDR_F10_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register gfc_bank4_base_add	*/
/*	 Fields bank_base_add	 */
#define BANK_BASE_ADD_F4_WIDTH                                               32
#define BANK_BASE_ADD_F4_SHIFT                                                0
#define BANK_BASE_ADD_F4_MASK                                        0xffffffff
#define BANK_BASE_ADD_F4_RD(src)                         (((src) & 0xffffffff))
#define BANK_BASE_ADD_F4_WR(src)                    (((u32)(src)) & 0xffffffff)
#define BANK_BASE_ADD_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_dma_ctrl0	*/
/*	 Fields complNum_4_int	 */
#define COMPLNUM_4_INT0_F4_WIDTH                                              3
#define COMPLNUM_4_INT0_F4_SHIFT                                             10
#define COMPLNUM_4_INT0_F4_MASK                                      0x00001c00
#define COMPLNUM_4_INT0_F4_RD(src)                   (((src) & 0x00001c00)>>10)
#define COMPLNUM_4_INT0_F4_WR(src)              (((u32)(src)<<10) & 0x00001c00)
#define COMPLNUM_4_INT0_F4_SET(dst,src) \
                      (((dst) & ~0x00001c00) | (((u32)(src)<<10) & 0x00001c00))
/*	 Fields dma_cmd_code	 */
#define DMA_CMD_CODE0_F4_WIDTH                                                3
#define DMA_CMD_CODE0_F4_SHIFT                                                7
#define DMA_CMD_CODE0_F4_MASK                                        0x00000380
#define DMA_CMD_CODE0_F4_RD(src)                      (((src) & 0x00000380)>>7)
#define DMA_CMD_CODE0_F4_WR(src)                 (((u32)(src)<<7) & 0x00000380)
#define DMA_CMD_CODE0_F4_SET(dst,src) \
                       (((dst) & ~0x00000380) | (((u32)(src)<<7) & 0x00000380))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID0_F4_WIDTH                                                  2
#define DMA_CMD_ID0_F4_SHIFT                                                  3
#define DMA_CMD_ID0_F4_MASK                                          0x00000018
#define DMA_CMD_ID0_F4_RD(src)                        (((src) & 0x00000018)>>3)
#define DMA_CMD_ID0_F4_WR(src)                   (((u32)(src)<<3) & 0x00000018)
#define DMA_CMD_ID0_F4_SET(dst,src) \
                       (((dst) & ~0x00000018) | (((u32)(src)<<3) & 0x00000018))
/*	 Fields dma_cmd_pop	 */
#define DMA_CMD_POP0_F4_WIDTH                                                 1
#define DMA_CMD_POP0_F4_SHIFT                                                 2
#define DMA_CMD_POP0_F4_MASK                                         0x00000004
#define DMA_CMD_POP0_F4_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_CMD_POP0_F4_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_CMD_POP0_F4_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dma_cmd_push	 */
#define DMA_CMD_PUSH0_F4_WIDTH                                                1
#define DMA_CMD_PUSH0_F4_SHIFT                                                1
#define DMA_CMD_PUSH0_F4_MASK                                        0x00000002
#define DMA_CMD_PUSH0_F4_RD(src)                      (((src) & 0x00000002)>>1)
#define DMA_CMD_PUSH0_F4_WR(src)                 (((u32)(src)<<1) & 0x00000002)
#define DMA_CMD_PUSH0_F4_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dma_cmd_valid	 */
#define DMA_CMD_VALID0_F4_WIDTH                                               1
#define DMA_CMD_VALID0_F4_SHIFT                                               0
#define DMA_CMD_VALID0_F4_MASK                                       0x00000001
#define DMA_CMD_VALID0_F4_RD(src)                        (((src) & 0x00000001))
#define DMA_CMD_VALID0_F4_WR(src)                   (((u32)(src)) & 0x00000001)
#define DMA_CMD_VALID0_F4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank4_dma_start_add0	*/
/*	 Fields dma_start_add0	 */
#define DMA_START_ADD00_F4_WIDTH                                             32
#define DMA_START_ADD00_F4_SHIFT                                              0
#define DMA_START_ADD00_F4_MASK                                      0xffffffff
#define DMA_START_ADD00_F4_RD(src)                       (((src) & 0xffffffff))
#define DMA_START_ADD00_F4_WR(src)                  (((u32)(src)) & 0xffffffff)
#define DMA_START_ADD00_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_dma_start_add1	*/
/*	 Fields dma_start_add1	 */
#define DMA_START_ADD11_F4_WIDTH                                             10
#define DMA_START_ADD11_F4_SHIFT                                              0
#define DMA_START_ADD11_F4_MASK                                      0x000003ff
#define DMA_START_ADD11_F4_RD(src)                       (((src) & 0x000003ff))
#define DMA_START_ADD11_F4_WR(src)                  (((u32)(src)) & 0x000003ff)
#define DMA_START_ADD11_F4_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank4_dma_des_add0	*/
/*	 Fields dma_des_add0	 */
#define DMA_DES_ADD00_F4_WIDTH                                               32
#define DMA_DES_ADD00_F4_SHIFT                                                0
#define DMA_DES_ADD00_F4_MASK                                        0xffffffff
#define DMA_DES_ADD00_F4_RD(src)                         (((src) & 0xffffffff))
#define DMA_DES_ADD00_F4_WR(src)                    (((u32)(src)) & 0xffffffff)
#define DMA_DES_ADD00_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_dma_des_add1	*/
/*	 Fields dma_des_add1	 */
#define DMA_DES_ADD11_F4_WIDTH                                               10
#define DMA_DES_ADD11_F4_SHIFT                                                0
#define DMA_DES_ADD11_F4_MASK                                        0x000003ff
#define DMA_DES_ADD11_F4_RD(src)                         (((src) & 0x000003ff))
#define DMA_DES_ADD11_F4_WR(src)                    (((u32)(src)) & 0x000003ff)
#define DMA_DES_ADD11_F4_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank4_dma_status	*/
/*	 Fields bits_corrected_ecc	 */
#define BITS_CORRECTED_ECC_F4_WIDTH                                           4
#define BITS_CORRECTED_ECC_F4_SHIFT                                          14
#define BITS_CORRECTED_ECC_F4_MASK                                   0x0003c000
#define BITS_CORRECTED_ECC_F4_RD(src)                (((src) & 0x0003c000)>>14)
#define BITS_CORRECTED_ECC_F4_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields dma_err	 */
#define DMA_ERR_F4_WIDTH                                                      3
#define DMA_ERR_F4_SHIFT                                                      9
#define DMA_ERR_F4_MASK                                              0x00000e00
#define DMA_ERR_F4_RD(src)                            (((src) & 0x00000e00)>>9)
#define DMA_ERR_F4_SET(dst,src) \
                       (((dst) & ~0x00000e00) | (((u32)(src)<<9) & 0x00000e00))
/*	 Fields dma_cmpl_status	 */
#define DMA_CMPL_STATUS_F4_WIDTH                                              2
#define DMA_CMPL_STATUS_F4_SHIFT                                              6
#define DMA_CMPL_STATUS_F4_MASK                                      0x000000c0
#define DMA_CMPL_STATUS_F4_RD(src)                    (((src) & 0x000000c0)>>6)
#define DMA_CMPL_STATUS_F4_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID_F4_WIDTH                                                   2
#define DMA_CMD_ID_F4_SHIFT                                                   1
#define DMA_CMD_ID_F4_MASK                                           0x00000006
#define DMA_CMD_ID_F4_RD(src)                         (((src) & 0x00000006)>>1)
#define DMA_CMD_ID_F4_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields dma_cmpl_valid	 */
#define DMA_CMPL_VALID_F4_WIDTH                                               1
#define DMA_CMPL_VALID_F4_SHIFT                                               0
#define DMA_CMPL_VALID_F4_MASK                                       0x00000001
#define DMA_CMPL_VALID_F4_RD(src)                        (((src) & 0x00000001))
#define DMA_CMPL_VALID_F4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank4_dma_eccerr0_add_col	*/
/*	 Fields dma_eccerr0_add_col	 */
#define DMA_ECCERR0_ADD_COL_F4_WIDTH                                         32
#define DMA_ECCERR0_ADD_COL_F4_SHIFT                                          0
#define DMA_ECCERR0_ADD_COL_F4_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_COL_F4_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_COL_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_dma_eccerr0_add_row	*/
/*	 Fields dma_eccerr0_add_row	 */
#define DMA_ECCERR0_ADD_ROW_F4_WIDTH                                         32
#define DMA_ECCERR0_ADD_ROW_F4_SHIFT                                          0
#define DMA_ECCERR0_ADD_ROW_F4_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_ROW_F4_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_ROW_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_dma_eccerr1_add_col	*/
/*	 Fields dma_eccerr1_add_col	 */
#define DMA_ECCERR1_ADD_COL_F4_WIDTH                                         32
#define DMA_ECCERR1_ADD_COL_F4_SHIFT                                          0
#define DMA_ECCERR1_ADD_COL_F4_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_COL_F4_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_COL_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_dma_eccerr1_add_row	*/
/*	 Fields dma_eccerr1_add_row	 */
#define DMA_ECCERR1_ADD_ROW_F4_WIDTH                                         32
#define DMA_ECCERR1_ADD_ROW_F4_SHIFT                                          0
#define DMA_ECCERR1_ADD_ROW_F4_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_ROW_F4_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_ROW_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_INT	*/
/*	 Fields nandpio_device_protection_err	 */
#define NANDPIO_DEVICE_PROTECTION_ERR_F4_WIDTH                                1
#define NANDPIO_DEVICE_PROTECTION_ERR_F4_SHIFT                               11
#define NANDPIO_DEVICE_PROTECTION_ERR_F4_MASK                        0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERR_F4_RD(src)     (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERR_F4_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERR_F4_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields norp_device_protection_err	 */
#define NORP_DEVICE_PROTECTION_ERR_F4_WIDTH                                   1
#define NORP_DEVICE_PROTECTION_ERR_F4_SHIFT                                  10
#define NORP_DEVICE_PROTECTION_ERR_F4_MASK                           0x00000400
#define NORP_DEVICE_PROTECTION_ERR_F4_RD(src)        (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERR_F4_WR(src)   (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERR_F4_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields dma_cmd_override_err	 */
#define DMA_CMD_OVERRIDE_ERR_F4_WIDTH                                         1
#define DMA_CMD_OVERRIDE_ERR_F4_SHIFT                                         9
#define DMA_CMD_OVERRIDE_ERR_F4_MASK                                 0x00000200
#define DMA_CMD_OVERRIDE_ERR_F4_RD(src)               (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERR_F4_WR(src)          (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERR_F4_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields device_protection_err	 */
#define DEVICE_PROTECTION_ERR_F4_WIDTH                                        1
#define DEVICE_PROTECTION_ERR_F4_SHIFT                                        8
#define DEVICE_PROTECTION_ERR_F4_MASK                                0x00000100
#define DEVICE_PROTECTION_ERR_F4_RD(src)              (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERR_F4_WR(src)         (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERR_F4_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields transaction_timeout	 */
#define TRANSACTION_TIMEOUT_F4_WIDTH                                          1
#define TRANSACTION_TIMEOUT_F4_SHIFT                                          7
#define TRANSACTION_TIMEOUT_F4_MASK                                  0x00000080
#define TRANSACTION_TIMEOUT_F4_RD(src)                (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUT_F4_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUT_F4_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields parity_err	 */
#define PARITY_ERR_F4_WIDTH                                                   1
#define PARITY_ERR_F4_SHIFT                                                   6
#define PARITY_ERR_F4_MASK                                           0x00000040
#define PARITY_ERR_F4_RD(src)                         (((src) & 0x00000040)>>6)
#define PARITY_ERR_F4_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERR_F4_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ecc_err_single	 */
#define ECC_ERR_SINGLE_F4_WIDTH                                               1
#define ECC_ERR_SINGLE_F4_SHIFT                                               5
#define ECC_ERR_SINGLE_F4_MASK                                       0x00000020
#define ECC_ERR_SINGLE_F4_RD(src)                     (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLE_F4_WR(src)                (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLE_F4_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ecc_err_multiple	 */
#define ECC_ERR_MULTIPLE_F4_WIDTH                                             1
#define ECC_ERR_MULTIPLE_F4_SHIFT                                             4
#define ECC_ERR_MULTIPLE_F4_MASK                                     0x00000010
#define ECC_ERR_MULTIPLE_F4_RD(src)                   (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLE_F4_WR(src)              (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLE_F4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields dma_done	 */
#define DMA_DONE_F4_WIDTH                                                     1
#define DMA_DONE_F4_SHIFT                                                     2
#define DMA_DONE_F4_MASK                                             0x00000004
#define DMA_DONE_F4_RD(src)                           (((src) & 0x00000004)>>2)
#define DMA_DONE_F4_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define DMA_DONE_F4_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank4_interruptMask	*/
/*    Mask Register Fields nandpio_device_protection_errMask    */
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F4_WIDTH                            1
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F4_SHIFT                           11
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F4_MASK                    0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F4_RD(src) \
                                                    (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F4_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F4_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields norp_device_protection_errMask    */
#define NORP_DEVICE_PROTECTION_ERRMASK_F4_WIDTH                               1
#define NORP_DEVICE_PROTECTION_ERRMASK_F4_SHIFT                              10
#define NORP_DEVICE_PROTECTION_ERRMASK_F4_MASK                       0x00000400
#define NORP_DEVICE_PROTECTION_ERRMASK_F4_RD(src)    (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERRMASK_F4_WR(src) \
                                                (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERRMASK_F4_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields dma_cmd_override_errMask    */
#define DMA_CMD_OVERRIDE_ERRMASK_F4_WIDTH                                     1
#define DMA_CMD_OVERRIDE_ERRMASK_F4_SHIFT                                     9
#define DMA_CMD_OVERRIDE_ERRMASK_F4_MASK                             0x00000200
#define DMA_CMD_OVERRIDE_ERRMASK_F4_RD(src)           (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERRMASK_F4_WR(src)      (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERRMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields device_protection_errMask    */
#define DEVICE_PROTECTION_ERRMASK_F4_WIDTH                                    1
#define DEVICE_PROTECTION_ERRMASK_F4_SHIFT                                    8
#define DEVICE_PROTECTION_ERRMASK_F4_MASK                            0x00000100
#define DEVICE_PROTECTION_ERRMASK_F4_RD(src)          (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERRMASK_F4_WR(src)     (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERRMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields transaction_timeoutMask    */
#define TRANSACTION_TIMEOUTMASK_F4_WIDTH                                      1
#define TRANSACTION_TIMEOUTMASK_F4_SHIFT                                      7
#define TRANSACTION_TIMEOUTMASK_F4_MASK                              0x00000080
#define TRANSACTION_TIMEOUTMASK_F4_RD(src)            (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUTMASK_F4_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUTMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields parity_errMask    */
#define PARITY_ERRMASK_F4_WIDTH                                               1
#define PARITY_ERRMASK_F4_SHIFT                                               6
#define PARITY_ERRMASK_F4_MASK                                       0x00000040
#define PARITY_ERRMASK_F4_RD(src)                     (((src) & 0x00000040)>>6)
#define PARITY_ERRMASK_F4_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERRMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ecc_err_singleMask    */
#define ECC_ERR_SINGLEMASK_F4_WIDTH                                           1
#define ECC_ERR_SINGLEMASK_F4_SHIFT                                           5
#define ECC_ERR_SINGLEMASK_F4_MASK                                   0x00000020
#define ECC_ERR_SINGLEMASK_F4_RD(src)                 (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLEMASK_F4_WR(src)            (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLEMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ecc_err_multipleMask    */
#define ECC_ERR_MULTIPLEMASK_F4_WIDTH                                         1
#define ECC_ERR_MULTIPLEMASK_F4_SHIFT                                         4
#define ECC_ERR_MULTIPLEMASK_F4_MASK                                 0x00000010
#define ECC_ERR_MULTIPLEMASK_F4_RD(src)               (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLEMASK_F4_WR(src)          (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLEMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields dma_doneMask    */
#define DMA_DONEMASK_F4_WIDTH                                                 1
#define DMA_DONEMASK_F4_SHIFT                                                 2
#define DMA_DONEMASK_F4_MASK                                         0x00000004
#define DMA_DONEMASK_F4_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_DONEMASK_F4_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_DONEMASK_F4_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank4_sram_ctrl0	*/
/*	 Fields rtc	 */
#define REGSPEC_RTC0_F4_WIDTH                                                 3
#define REGSPEC_RTC0_F4_SHIFT                                                12
#define REGSPEC_RTC0_F4_MASK                                         0x00007000
#define REGSPEC_RTC0_F4_RD(src)                      (((src) & 0x00007000)>>12)
#define REGSPEC_RTC0_F4_WR(src)                 (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_RTC0_F4_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields muxen	 */
#define MUXEN0_F4_WIDTH                                                       1
#define MUXEN0_F4_SHIFT                                                      10
#define MUXEN0_F4_MASK                                               0x00000400
#define MUXEN0_F4_RD(src)                            (((src) & 0x00000400)>>10)
#define MUXEN0_F4_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define MUXEN0_F4_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rdy_timeout_cnt	 */
#define RDY_TIMEOUT_CNT0_F4_WIDTH                                             3
#define RDY_TIMEOUT_CNT0_F4_SHIFT                                             2
#define RDY_TIMEOUT_CNT0_F4_MASK                                     0x0000001c
#define RDY_TIMEOUT_CNT0_F4_RD(src)                   (((src) & 0x0000001c)>>2)
#define RDY_TIMEOUT_CNT0_F4_WR(src)              (((u32)(src)<<2) & 0x0000001c)
#define RDY_TIMEOUT_CNT0_F4_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields ptd	 */
#define PTD0_F4_WIDTH                                                         1
#define PTD0_F4_SHIFT                                                         1
#define PTD0_F4_MASK                                                 0x00000002
#define PTD0_F4_RD(src)                               (((src) & 0x00000002)>>1)
#define PTD0_F4_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PTD0_F4_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields le	 */
#define LE0_F4_WIDTH                                                          1
#define LE0_F4_SHIFT                                                          0
#define LE0_F4_MASK                                                  0x00000001
#define LE0_F4_RD(src)                                   (((src) & 0x00000001))
#define LE0_F4_WR(src)                              (((u32)(src)) & 0x00000001)
#define LE0_F4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank4_sram_nor_ctrl1	*/
/*	 Fields BME	 */
#define BME1_F4_WIDTH                                                         1
#define BME1_F4_SHIFT                                                        31
#define BME1_F4_MASK                                                 0x80000000
#define BME1_F4_RD(src)                              (((src) & 0x80000000)>>31)
#define BME1_F4_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define BME1_F4_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields OEO	 */
#define OEO1_F4_WIDTH                                                         1
#define OEO1_F4_SHIFT                                                        30
#define OEO1_F4_MASK                                                 0x40000000
#define OEO1_F4_RD(src)                              (((src) & 0x40000000)>>30)
#define OEO1_F4_WR(src)                         (((u32)(src)<<30) & 0x40000000)
#define OEO1_F4_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields BWT	 */
#define BWT1_F4_WIDTH                                                         5
#define BWT1_F4_SHIFT                                                        20
#define BWT1_F4_MASK                                                 0x01f00000
#define BWT1_F4_RD(src)                              (((src) & 0x01f00000)>>20)
#define BWT1_F4_WR(src)                         (((u32)(src)<<20) & 0x01f00000)
#define BWT1_F4_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields FWT	 */
#define FWT1_F4_WIDTH                                                         7
#define FWT1_F4_SHIFT                                                        12
#define FWT1_F4_MASK                                                 0x0007f000
#define FWT1_F4_RD(src)                              (((src) & 0x0007f000)>>12)
#define FWT1_F4_WR(src)                         (((u32)(src)<<12) & 0x0007f000)
#define FWT1_F4_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields TWT	 */
#define TWT1_F4_WIDTH                                                        10
#define TWT1_F4_SHIFT                                                         0
#define TWT1_F4_MASK                                                 0x000003ff
#define TWT1_F4_RD(src)                                  (((src) & 0x000003ff))
#define TWT1_F4_WR(src)                             (((u32)(src)) & 0x000003ff)
#define TWT1_F4_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank4_sram_nor_ctrl2	*/
/*	 Fields ALN	 */
#define ALN2_F4_WIDTH                                                         4
#define ALN2_F4_SHIFT                                                        28
#define ALN2_F4_MASK                                                 0xf0000000
#define ALN2_F4_RD(src)                              (((src) & 0xf0000000)>>28)
#define ALN2_F4_WR(src)                         (((u32)(src)<<28) & 0xf0000000)
#define ALN2_F4_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields PEN	 */
#define PEN2_F4_WIDTH                                                         1
#define PEN2_F4_SHIFT                                                        27
#define PEN2_F4_MASK                                                 0x08000000
#define PEN2_F4_RD(src)                              (((src) & 0x08000000)>>27)
#define PEN2_F4_WR(src)                         (((u32)(src)<<27) & 0x08000000)
#define PEN2_F4_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields BEM	 */
#define BEM2_F4_WIDTH                                                         1
#define BEM2_F4_SHIFT                                                        26
#define BEM2_F4_MASK                                                 0x04000000
#define BEM2_F4_RD(src)                              (((src) & 0x04000000)>>26)
#define BEM2_F4_WR(src)                         (((u32)(src)<<26) & 0x04000000)
#define BEM2_F4_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SOR	 */
#define SOR2_F4_WIDTH                                                         1
#define SOR2_F4_SHIFT                                                        25
#define SOR2_F4_MASK                                                 0x02000000
#define SOR2_F4_RD(src)                              (((src) & 0x02000000)>>25)
#define SOR2_F4_WR(src)                         (((u32)(src)<<25) & 0x02000000)
#define SOR2_F4_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RE	 */
#define RE2_F4_WIDTH                                                          1
#define RE2_F4_SHIFT                                                         24
#define RE2_F4_MASK                                                  0x01000000
#define RE2_F4_RD(src)                               (((src) & 0x01000000)>>24)
#define RE2_F4_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define RE2_F4_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields TH	 */
#define TH2_F4_WIDTH                                                          5
#define TH2_F4_SHIFT                                                         16
#define TH2_F4_MASK                                                  0x001f0000
#define TH2_F4_RD(src)                               (((src) & 0x001f0000)>>16)
#define TH2_F4_WR(src)                          (((u32)(src)<<16) & 0x001f0000)
#define TH2_F4_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WBF	 */
#define WBF2_F4_WIDTH                                                         4
#define WBF2_F4_SHIFT                                                        12
#define WBF2_F4_MASK                                                 0x0000f000
#define WBF2_F4_RD(src)                              (((src) & 0x0000f000)>>12)
#define WBF2_F4_WR(src)                         (((u32)(src)<<12) & 0x0000f000)
#define WBF2_F4_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WBN	 */
#define WBN2_F4_WIDTH                                                         4
#define WBN2_F4_SHIFT                                                         8
#define WBN2_F4_MASK                                                 0x00000f00
#define WBN2_F4_RD(src)                               (((src) & 0x00000f00)>>8)
#define WBN2_F4_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define WBN2_F4_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields OEN	 */
#define OEN2_F4_WIDTH                                                         4
#define OEN2_F4_SHIFT                                                         4
#define OEN2_F4_MASK                                                 0x000000f0
#define OEN2_F4_RD(src)                               (((src) & 0x000000f0)>>4)
#define OEN2_F4_WR(src)                          (((u32)(src)<<4) & 0x000000f0)
#define OEN2_F4_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields CSN	 */
#define CSN2_F4_WIDTH                                                         4
#define CSN2_F4_SHIFT                                                         0
#define CSN2_F4_MASK                                                 0x0000000f
#define CSN2_F4_RD(src)                                  (((src) & 0x0000000f))
#define CSN2_F4_WR(src)                             (((u32)(src)) & 0x0000000f)
#define CSN2_F4_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_bank4_nand_ctrl0	*/
/*	 Fields SPARE_OFFSET	 */
#define SPARE_OFFSET0_F4_WIDTH                                               16
#define SPARE_OFFSET0_F4_SHIFT                                               16
#define SPARE_OFFSET0_F4_MASK                                        0xffff0000
#define SPARE_OFFSET0_F4_RD(src)                     (((src) & 0xffff0000)>>16)
#define SPARE_OFFSET0_F4_WR(src)                (((u32)(src)<<16) & 0xffff0000)
#define SPARE_OFFSET0_F4_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields FORCE_SPARE_OFFSET	 */
#define FORCE_SPARE_OFFSET0_F4_WIDTH                                          1
#define FORCE_SPARE_OFFSET0_F4_SHIFT                                          9
#define FORCE_SPARE_OFFSET0_F4_MASK                                  0x00000200
#define FORCE_SPARE_OFFSET0_F4_RD(src)                (((src) & 0x00000200)>>9)
#define FORCE_SPARE_OFFSET0_F4_WR(src)           (((u32)(src)<<9) & 0x00000200)
#define FORCE_SPARE_OFFSET0_F4_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ECC_Algorithm	 */
#define ECC_ALGORITHM0_F4_WIDTH                                               1
#define ECC_ALGORITHM0_F4_SHIFT                                               8
#define ECC_ALGORITHM0_F4_MASK                                       0x00000100
#define ECC_ALGORITHM0_F4_RD(src)                     (((src) & 0x00000100)>>8)
#define ECC_ALGORITHM0_F4_WR(src)                (((u32)(src)<<8) & 0x00000100)
#define ECC_ALGORITHM0_F4_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ECC_ON_OFF	 */
#define ECC_ON_OFF0_F4_WIDTH                                                  1
#define ECC_ON_OFF0_F4_SHIFT                                                  7
#define ECC_ON_OFF0_F4_MASK                                          0x00000080
#define ECC_ON_OFF0_F4_RD(src)                        (((src) & 0x00000080)>>7)
#define ECC_ON_OFF0_F4_WR(src)                   (((u32)(src)<<7) & 0x00000080)
#define ECC_ON_OFF0_F4_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))

/*	Register gfc_bank4_nand_ctrl1	*/

/*	Register gfc_bank4_nand_ctrl2	*/

/*	Register gfc_bank4_nand_bch	*/
/*	 Fields bch_k	 */
#define BCH_K_F4_WIDTH                                                        3
#define BCH_K_F4_SHIFT                                                       20
#define BCH_K_F4_MASK                                                0x00700000
#define BCH_K_F4_RD(src)                             (((src) & 0x00700000)>>20)
#define BCH_K_F4_WR(src)                        (((u32)(src)<<20) & 0x00700000)
#define BCH_K_F4_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields bch_t	 */
#define BCH_T_F4_WIDTH                                                        4
#define BCH_T_F4_SHIFT                                                       16
#define BCH_T_F4_MASK                                                0x000f0000
#define BCH_T_F4_RD(src)                             (((src) & 0x000f0000)>>16)
#define BCH_T_F4_WR(src)                        (((u32)(src)<<16) & 0x000f0000)
#define BCH_T_F4_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields bch_n	 */
#define BCH_N_F4_WIDTH                                                       16
#define BCH_N_F4_SHIFT                                                        0
#define BCH_N_F4_MASK                                                0x0000ffff
#define BCH_N_F4_RD(src)                                 (((src) & 0x0000ffff))
#define BCH_N_F4_WR(src)                            (((u32)(src)) & 0x0000ffff)
#define BCH_N_F4_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank4_dma_ctrl1	*/
/*	 Fields dma_data_size	 */
#define DMA_DATA_SIZE1_F4_WIDTH                                              24
#define DMA_DATA_SIZE1_F4_SHIFT                                               0
#define DMA_DATA_SIZE1_F4_MASK                                       0x00ffffff
#define DMA_DATA_SIZE1_F4_RD(src)                        (((src) & 0x00ffffff))
#define DMA_DATA_SIZE1_F4_WR(src)                   (((u32)(src)) & 0x00ffffff)
#define DMA_DATA_SIZE1_F4_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_bank4_nand_ctrl3	*/
/*	 Fields page_size	 */
#define PAGE_SIZE3_F4_WIDTH                                                  16
#define PAGE_SIZE3_F4_SHIFT                                                   0
#define PAGE_SIZE3_F4_MASK                                           0x0000ffff
#define PAGE_SIZE3_F4_RD(src)                            (((src) & 0x0000ffff))
#define PAGE_SIZE3_F4_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define PAGE_SIZE3_F4_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank4_nand_ctrl4	*/
/*	 Fields device_size	 */
#define DEVICE_SIZE4_F4_WIDTH                                                16
#define DEVICE_SIZE4_F4_SHIFT                                                16
#define DEVICE_SIZE4_F4_MASK                                         0xffff0000
#define DEVICE_SIZE4_F4_RD(src)                      (((src) & 0xffff0000)>>16)
#define DEVICE_SIZE4_F4_WR(src)                 (((u32)(src)<<16) & 0xffff0000)
#define DEVICE_SIZE4_F4_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields block_size	 */
#define BLOCK_SIZE4_F4_WIDTH                                                 16
#define BLOCK_SIZE4_F4_SHIFT                                                  0
#define BLOCK_SIZE4_F4_MASK                                          0x0000ffff
#define BLOCK_SIZE4_F4_RD(src)                           (((src) & 0x0000ffff))
#define BLOCK_SIZE4_F4_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define BLOCK_SIZE4_F4_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank4_nand_timing0	*/
/*	 Fields t_adl	 */
#define T_ADL0_F4_WIDTH                                                       8
#define T_ADL0_F4_SHIFT                                                      24
#define T_ADL0_F4_MASK                                               0xff000000
#define T_ADL0_F4_RD(src)                            (((src) & 0xff000000)>>24)
#define T_ADL0_F4_WR(src)                       (((u32)(src)<<24) & 0xff000000)
#define T_ADL0_F4_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_wb	 */
#define T_WB0_F4_WIDTH                                                        8
#define T_WB0_F4_SHIFT                                                       16
#define T_WB0_F4_MASK                                                0x00ff0000
#define T_WB0_F4_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WB0_F4_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WB0_F4_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_rhw	 */
#define T_RHW0_F4_WIDTH                                                       8
#define T_RHW0_F4_SHIFT                                                       8
#define T_RHW0_F4_MASK                                               0x0000ff00
#define T_RHW0_F4_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_RHW0_F4_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_RHW0_F4_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_ccs	 */
#define T_CCS0_F4_WIDTH                                                       8
#define T_CCS0_F4_SHIFT                                                       0
#define T_CCS0_F4_MASK                                               0x000000ff
#define T_CCS0_F4_RD(src)                                (((src) & 0x000000ff))
#define T_CCS0_F4_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CCS0_F4_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank4_nand_timing1	*/
/*	 Fields t_alh_clh_ch	 */
#define T_ALH_CLH_CH1_F4_WIDTH                                                8
#define T_ALH_CLH_CH1_F4_SHIFT                                               24
#define T_ALH_CLH_CH1_F4_MASK                                        0xff000000
#define T_ALH_CLH_CH1_F4_RD(src)                     (((src) & 0xff000000)>>24)
#define T_ALH_CLH_CH1_F4_WR(src)                (((u32)(src)<<24) & 0xff000000)
#define T_ALH_CLH_CH1_F4_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_als_cls_cs	 */
#define T_ALS_CLS_CS1_F4_WIDTH                                                8
#define T_ALS_CLS_CS1_F4_SHIFT                                               16
#define T_ALS_CLS_CS1_F4_MASK                                        0x00ff0000
#define T_ALS_CLS_CS1_F4_RD(src)                     (((src) & 0x00ff0000)>>16)
#define T_ALS_CLS_CS1_F4_WR(src)                (((u32)(src)<<16) & 0x00ff0000)
#define T_ALS_CLS_CS1_F4_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_ds_wp	 */
#define T_DS_WP1_F4_WIDTH                                                     8
#define T_DS_WP1_F4_SHIFT                                                     8
#define T_DS_WP1_F4_MASK                                             0x0000ff00
#define T_DS_WP1_F4_RD(src)                           (((src) & 0x0000ff00)>>8)
#define T_DS_WP1_F4_WR(src)                      (((u32)(src)<<8) & 0x0000ff00)
#define T_DS_WP1_F4_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_dh_wh	 */
#define T_DH_WH1_F4_WIDTH                                                     8
#define T_DH_WH1_F4_SHIFT                                                     0
#define T_DH_WH1_F4_MASK                                             0x000000ff
#define T_DH_WH1_F4_RD(src)                              (((src) & 0x000000ff))
#define T_DH_WH1_F4_WR(src)                         (((u32)(src)) & 0x000000ff)
#define T_DH_WH1_F4_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank4_nand_timing2	*/
/*	 Fields t_ar_clr_whr_ir	 */
#define T_AR_CLR_WHR_IR2_F4_WIDTH                                             8
#define T_AR_CLR_WHR_IR2_F4_SHIFT                                            24
#define T_AR_CLR_WHR_IR2_F4_MASK                                     0xff000000
#define T_AR_CLR_WHR_IR2_F4_RD(src)                  (((src) & 0xff000000)>>24)
#define T_AR_CLR_WHR_IR2_F4_WR(src)             (((u32)(src)<<24) & 0xff000000)
#define T_AR_CLR_WHR_IR2_F4_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_rr	 */
#define T_RR2_F4_WIDTH                                                        8
#define T_RR2_F4_SHIFT                                                       16
#define T_RR2_F4_MASK                                                0x00ff0000
#define T_RR2_F4_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_RR2_F4_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_RR2_F4_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_reh	 */
#define T_REH2_F4_WIDTH                                                       8
#define T_REH2_F4_SHIFT                                                       8
#define T_REH2_F4_MASK                                               0x0000ff00
#define T_REH2_F4_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_REH2_F4_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_REH2_F4_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_rp	 */
#define T_RP2_F4_WIDTH                                                        8
#define T_RP2_F4_SHIFT                                                        0
#define T_RP2_F4_MASK                                                0x000000ff
#define T_RP2_F4_RD(src)                                 (((src) & 0x000000ff))
#define T_RP2_F4_WR(src)                            (((u32)(src)) & 0x000000ff)
#define T_RP2_F4_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank4_nand_timing3	*/
/*	 Fields t_ww	 */
#define T_WW3_F4_WIDTH                                                        8
#define T_WW3_F4_SHIFT                                                       16
#define T_WW3_F4_MASK                                                0x00ff0000
#define T_WW3_F4_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WW3_F4_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WW3_F4_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_chz	 */
#define T_CHZ3_F4_WIDTH                                                       8
#define T_CHZ3_F4_SHIFT                                                       8
#define T_CHZ3_F4_MASK                                               0x0000ff00
#define T_CHZ3_F4_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_CHZ3_F4_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_CHZ3_F4_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_cea	 */
#define T_CEA3_F4_WIDTH                                                       8
#define T_CEA3_F4_SHIFT                                                       0
#define T_CEA3_F4_MASK                                               0x000000ff
#define T_CEA3_F4_RD(src)                                (((src) & 0x000000ff))
#define T_CEA3_F4_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CEA3_F4_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank4_nand_cor_err	*/
/*	 Fields counter	 */
#define COUNTER_F9_WIDTH                                                     32
#define COUNTER_F9_SHIFT                                                      0
#define COUNTER_F9_MASK                                              0xffffffff
#define COUNTER_F9_RD(src)                               (((src) & 0xffffffff))
#define COUNTER_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank4_nand_uncor_err	*/
/*	 Fields counter	 */
#define COUNTER_F10_WIDTH                                                    32
#define COUNTER_F10_SHIFT                                                     0
#define COUNTER_F10_MASK                                             0xffffffff
#define COUNTER_F10_RD(src)                              (((src) & 0xffffffff))
#define COUNTER_F10_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_ctrl0	*/
/*	 Fields nand_wp_n	 */
#define NAND_WP_N0_F5_WIDTH                                                   1
#define NAND_WP_N0_F5_SHIFT                                                   8
#define NAND_WP_N0_F5_MASK                                           0x00000100
#define NAND_WP_N0_F5_RD(src)                         (((src) & 0x00000100)>>8)
#define NAND_WP_N0_F5_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define NAND_WP_N0_F5_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bus_width	 */
#define BUS_WIDTH0_F5_WIDTH                                                   2
#define BUS_WIDTH0_F5_SHIFT                                                   6
#define BUS_WIDTH0_F5_MASK                                           0x000000c0
#define BUS_WIDTH0_F5_RD(src)                         (((src) & 0x000000c0)>>6)
#define BUS_WIDTH0_F5_WR(src)                    (((u32)(src)<<6) & 0x000000c0)
#define BUS_WIDTH0_F5_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields bus_usage	 */
#define BUS_USAGE0_F5_WIDTH                                                   2
#define BUS_USAGE0_F5_SHIFT                                                   4
#define BUS_USAGE0_F5_MASK                                           0x00000030
#define BUS_USAGE0_F5_RD(src)                         (((src) & 0x00000030)>>4)
#define BUS_USAGE0_F5_WR(src)                    (((u32)(src)<<4) & 0x00000030)
#define BUS_USAGE0_F5_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields bank_type	 */
#define BANK_TYPE0_F5_WIDTH                                                   3
#define BANK_TYPE0_F5_SHIFT                                                   1
#define BANK_TYPE0_F5_MASK                                           0x0000000e
#define BANK_TYPE0_F5_RD(src)                         (((src) & 0x0000000e)>>1)
#define BANK_TYPE0_F5_WR(src)                    (((u32)(src)<<1) & 0x0000000e)
#define BANK_TYPE0_F5_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields bank_valid	 */
#define BANK_VALID0_F5_WIDTH                                                  1
#define BANK_VALID0_F5_SHIFT                                                  0
#define BANK_VALID0_F5_MASK                                          0x00000001
#define BANK_VALID0_F5_RD(src)                           (((src) & 0x00000001))
#define BANK_VALID0_F5_WR(src)                      (((u32)(src)) & 0x00000001)
#define BANK_VALID0_F5_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank5_start_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F11_WIDTH                                               14
#define REGSPEC_ADDR_F11_SHIFT                                                0
#define REGSPEC_ADDR_F11_MASK                                        0x00003fff
#define REGSPEC_ADDR_F11_RD(src)                         (((src) & 0x00003fff))
#define REGSPEC_ADDR_F11_WR(src)                    (((u32)(src)) & 0x00003fff)
#define REGSPEC_ADDR_F11_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register gfc_bank5_end_add	*/
/*	 Fields addr	 */
#define REGSPEC_ADDR_F12_WIDTH                                               15
#define REGSPEC_ADDR_F12_SHIFT                                                0
#define REGSPEC_ADDR_F12_MASK                                        0x00007fff
#define REGSPEC_ADDR_F12_RD(src)                         (((src) & 0x00007fff))
#define REGSPEC_ADDR_F12_WR(src)                    (((u32)(src)) & 0x00007fff)
#define REGSPEC_ADDR_F12_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register gfc_bank5_base_add	*/
/*	 Fields bank_base_add	 */
#define BANK_BASE_ADD_F5_WIDTH                                               32
#define BANK_BASE_ADD_F5_SHIFT                                                0
#define BANK_BASE_ADD_F5_MASK                                        0xffffffff
#define BANK_BASE_ADD_F5_RD(src)                         (((src) & 0xffffffff))
#define BANK_BASE_ADD_F5_WR(src)                    (((u32)(src)) & 0xffffffff)
#define BANK_BASE_ADD_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_dma_ctrl0	*/
/*	 Fields complNum_4_int	 */
#define COMPLNUM_4_INT0_F5_WIDTH                                              3
#define COMPLNUM_4_INT0_F5_SHIFT                                             10
#define COMPLNUM_4_INT0_F5_MASK                                      0x00001c00
#define COMPLNUM_4_INT0_F5_RD(src)                   (((src) & 0x00001c00)>>10)
#define COMPLNUM_4_INT0_F5_WR(src)              (((u32)(src)<<10) & 0x00001c00)
#define COMPLNUM_4_INT0_F5_SET(dst,src) \
                      (((dst) & ~0x00001c00) | (((u32)(src)<<10) & 0x00001c00))
/*	 Fields dma_cmd_code	 */
#define DMA_CMD_CODE0_F5_WIDTH                                                3
#define DMA_CMD_CODE0_F5_SHIFT                                                7
#define DMA_CMD_CODE0_F5_MASK                                        0x00000380
#define DMA_CMD_CODE0_F5_RD(src)                      (((src) & 0x00000380)>>7)
#define DMA_CMD_CODE0_F5_WR(src)                 (((u32)(src)<<7) & 0x00000380)
#define DMA_CMD_CODE0_F5_SET(dst,src) \
                       (((dst) & ~0x00000380) | (((u32)(src)<<7) & 0x00000380))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID0_F5_WIDTH                                                  2
#define DMA_CMD_ID0_F5_SHIFT                                                  3
#define DMA_CMD_ID0_F5_MASK                                          0x00000018
#define DMA_CMD_ID0_F5_RD(src)                        (((src) & 0x00000018)>>3)
#define DMA_CMD_ID0_F5_WR(src)                   (((u32)(src)<<3) & 0x00000018)
#define DMA_CMD_ID0_F5_SET(dst,src) \
                       (((dst) & ~0x00000018) | (((u32)(src)<<3) & 0x00000018))
/*	 Fields dma_cmd_pop	 */
#define DMA_CMD_POP0_F5_WIDTH                                                 1
#define DMA_CMD_POP0_F5_SHIFT                                                 2
#define DMA_CMD_POP0_F5_MASK                                         0x00000004
#define DMA_CMD_POP0_F5_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_CMD_POP0_F5_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_CMD_POP0_F5_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dma_cmd_push	 */
#define DMA_CMD_PUSH0_F5_WIDTH                                                1
#define DMA_CMD_PUSH0_F5_SHIFT                                                1
#define DMA_CMD_PUSH0_F5_MASK                                        0x00000002
#define DMA_CMD_PUSH0_F5_RD(src)                      (((src) & 0x00000002)>>1)
#define DMA_CMD_PUSH0_F5_WR(src)                 (((u32)(src)<<1) & 0x00000002)
#define DMA_CMD_PUSH0_F5_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dma_cmd_valid	 */
#define DMA_CMD_VALID0_F5_WIDTH                                               1
#define DMA_CMD_VALID0_F5_SHIFT                                               0
#define DMA_CMD_VALID0_F5_MASK                                       0x00000001
#define DMA_CMD_VALID0_F5_RD(src)                        (((src) & 0x00000001))
#define DMA_CMD_VALID0_F5_WR(src)                   (((u32)(src)) & 0x00000001)
#define DMA_CMD_VALID0_F5_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank5_dma_start_add0	*/
/*	 Fields dma_start_add0	 */
#define DMA_START_ADD00_F5_WIDTH                                             32
#define DMA_START_ADD00_F5_SHIFT                                              0
#define DMA_START_ADD00_F5_MASK                                      0xffffffff
#define DMA_START_ADD00_F5_RD(src)                       (((src) & 0xffffffff))
#define DMA_START_ADD00_F5_WR(src)                  (((u32)(src)) & 0xffffffff)
#define DMA_START_ADD00_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_dma_start_add1	*/
/*	 Fields dma_start_add1	 */
#define DMA_START_ADD11_F5_WIDTH                                             10
#define DMA_START_ADD11_F5_SHIFT                                              0
#define DMA_START_ADD11_F5_MASK                                      0x000003ff
#define DMA_START_ADD11_F5_RD(src)                       (((src) & 0x000003ff))
#define DMA_START_ADD11_F5_WR(src)                  (((u32)(src)) & 0x000003ff)
#define DMA_START_ADD11_F5_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank5_dma_des_add0	*/
/*	 Fields dma_des_add0	 */
#define DMA_DES_ADD00_F5_WIDTH                                               32
#define DMA_DES_ADD00_F5_SHIFT                                                0
#define DMA_DES_ADD00_F5_MASK                                        0xffffffff
#define DMA_DES_ADD00_F5_RD(src)                         (((src) & 0xffffffff))
#define DMA_DES_ADD00_F5_WR(src)                    (((u32)(src)) & 0xffffffff)
#define DMA_DES_ADD00_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_dma_des_add1	*/
/*	 Fields dma_des_add1	 */
#define DMA_DES_ADD11_F5_WIDTH                                               10
#define DMA_DES_ADD11_F5_SHIFT                                                0
#define DMA_DES_ADD11_F5_MASK                                        0x000003ff
#define DMA_DES_ADD11_F5_RD(src)                         (((src) & 0x000003ff))
#define DMA_DES_ADD11_F5_WR(src)                    (((u32)(src)) & 0x000003ff)
#define DMA_DES_ADD11_F5_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank5_dma_status	*/
/*	 Fields bits_corrected_ecc	 */
#define BITS_CORRECTED_ECC_F5_WIDTH                                           4
#define BITS_CORRECTED_ECC_F5_SHIFT                                          14
#define BITS_CORRECTED_ECC_F5_MASK                                   0x0003c000
#define BITS_CORRECTED_ECC_F5_RD(src)                (((src) & 0x0003c000)>>14)
#define BITS_CORRECTED_ECC_F5_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields dma_err	 */
#define DMA_ERR_F5_WIDTH                                                      3
#define DMA_ERR_F5_SHIFT                                                      9
#define DMA_ERR_F5_MASK                                              0x00000e00
#define DMA_ERR_F5_RD(src)                            (((src) & 0x00000e00)>>9)
#define DMA_ERR_F5_SET(dst,src) \
                       (((dst) & ~0x00000e00) | (((u32)(src)<<9) & 0x00000e00))
/*	 Fields dma_cmpl_status	 */
#define DMA_CMPL_STATUS_F5_WIDTH                                              2
#define DMA_CMPL_STATUS_F5_SHIFT                                              6
#define DMA_CMPL_STATUS_F5_MASK                                      0x000000c0
#define DMA_CMPL_STATUS_F5_RD(src)                    (((src) & 0x000000c0)>>6)
#define DMA_CMPL_STATUS_F5_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields dma_cmd_id	 */
#define DMA_CMD_ID_F5_WIDTH                                                   2
#define DMA_CMD_ID_F5_SHIFT                                                   1
#define DMA_CMD_ID_F5_MASK                                           0x00000006
#define DMA_CMD_ID_F5_RD(src)                         (((src) & 0x00000006)>>1)
#define DMA_CMD_ID_F5_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields dma_cmpl_valid	 */
#define DMA_CMPL_VALID_F5_WIDTH                                               1
#define DMA_CMPL_VALID_F5_SHIFT                                               0
#define DMA_CMPL_VALID_F5_MASK                                       0x00000001
#define DMA_CMPL_VALID_F5_RD(src)                        (((src) & 0x00000001))
#define DMA_CMPL_VALID_F5_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank5_dma_eccerr0_add_col	*/
/*	 Fields dma_eccerr0_add_col	 */
#define DMA_ECCERR0_ADD_COL_F5_WIDTH                                         32
#define DMA_ECCERR0_ADD_COL_F5_SHIFT                                          0
#define DMA_ECCERR0_ADD_COL_F5_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_COL_F5_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_COL_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_dma_eccerr0_add_row	*/
/*	 Fields dma_eccerr0_add_row	 */
#define DMA_ECCERR0_ADD_ROW_F5_WIDTH                                         32
#define DMA_ECCERR0_ADD_ROW_F5_SHIFT                                          0
#define DMA_ECCERR0_ADD_ROW_F5_MASK                                  0xffffffff
#define DMA_ECCERR0_ADD_ROW_F5_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR0_ADD_ROW_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_dma_eccerr1_add_col	*/
/*	 Fields dma_eccerr1_add_col	 */
#define DMA_ECCERR1_ADD_COL_F5_WIDTH                                         32
#define DMA_ECCERR1_ADD_COL_F5_SHIFT                                          0
#define DMA_ECCERR1_ADD_COL_F5_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_COL_F5_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_COL_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_dma_eccerr1_add_row	*/
/*	 Fields dma_eccerr1_add_row	 */
#define DMA_ECCERR1_ADD_ROW_F5_WIDTH                                         32
#define DMA_ECCERR1_ADD_ROW_F5_SHIFT                                          0
#define DMA_ECCERR1_ADD_ROW_F5_MASK                                  0xffffffff
#define DMA_ECCERR1_ADD_ROW_F5_RD(src)                   (((src) & 0xffffffff))
#define DMA_ECCERR1_ADD_ROW_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_INT	*/
/*	 Fields nandpio_device_protection_err	 */
#define NANDPIO_DEVICE_PROTECTION_ERR_F5_WIDTH                                1
#define NANDPIO_DEVICE_PROTECTION_ERR_F5_SHIFT                               11
#define NANDPIO_DEVICE_PROTECTION_ERR_F5_MASK                        0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERR_F5_RD(src)     (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERR_F5_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERR_F5_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields norp_device_protection_err	 */
#define NORP_DEVICE_PROTECTION_ERR_F5_WIDTH                                   1
#define NORP_DEVICE_PROTECTION_ERR_F5_SHIFT                                  10
#define NORP_DEVICE_PROTECTION_ERR_F5_MASK                           0x00000400
#define NORP_DEVICE_PROTECTION_ERR_F5_RD(src)        (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERR_F5_WR(src)   (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERR_F5_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields dma_cmd_override_err	 */
#define DMA_CMD_OVERRIDE_ERR_F5_WIDTH                                         1
#define DMA_CMD_OVERRIDE_ERR_F5_SHIFT                                         9
#define DMA_CMD_OVERRIDE_ERR_F5_MASK                                 0x00000200
#define DMA_CMD_OVERRIDE_ERR_F5_RD(src)               (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERR_F5_WR(src)          (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERR_F5_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields device_protection_err	 */
#define DEVICE_PROTECTION_ERR_F5_WIDTH                                        1
#define DEVICE_PROTECTION_ERR_F5_SHIFT                                        8
#define DEVICE_PROTECTION_ERR_F5_MASK                                0x00000100
#define DEVICE_PROTECTION_ERR_F5_RD(src)              (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERR_F5_WR(src)         (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERR_F5_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields transaction_timeout	 */
#define TRANSACTION_TIMEOUT_F5_WIDTH                                          1
#define TRANSACTION_TIMEOUT_F5_SHIFT                                          7
#define TRANSACTION_TIMEOUT_F5_MASK                                  0x00000080
#define TRANSACTION_TIMEOUT_F5_RD(src)                (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUT_F5_WR(src)           (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUT_F5_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields parity_err	 */
#define PARITY_ERR_F5_WIDTH                                                   1
#define PARITY_ERR_F5_SHIFT                                                   6
#define PARITY_ERR_F5_MASK                                           0x00000040
#define PARITY_ERR_F5_RD(src)                         (((src) & 0x00000040)>>6)
#define PARITY_ERR_F5_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERR_F5_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ecc_err_single	 */
#define ECC_ERR_SINGLE_F5_WIDTH                                               1
#define ECC_ERR_SINGLE_F5_SHIFT                                               5
#define ECC_ERR_SINGLE_F5_MASK                                       0x00000020
#define ECC_ERR_SINGLE_F5_RD(src)                     (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLE_F5_WR(src)                (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLE_F5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ecc_err_multiple	 */
#define ECC_ERR_MULTIPLE_F5_WIDTH                                             1
#define ECC_ERR_MULTIPLE_F5_SHIFT                                             4
#define ECC_ERR_MULTIPLE_F5_MASK                                     0x00000010
#define ECC_ERR_MULTIPLE_F5_RD(src)                   (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLE_F5_WR(src)              (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLE_F5_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields dma_done	 */
#define DMA_DONE_F5_WIDTH                                                     1
#define DMA_DONE_F5_SHIFT                                                     2
#define DMA_DONE_F5_MASK                                             0x00000004
#define DMA_DONE_F5_RD(src)                           (((src) & 0x00000004)>>2)
#define DMA_DONE_F5_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define DMA_DONE_F5_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank5_interruptMask	*/
/*    Mask Register Fields nandpio_device_protection_errMask    */
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F5_WIDTH                            1
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F5_SHIFT                           11
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F5_MASK                    0x00000800
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F5_RD(src) \
                                                    (((src) & 0x00000800)>>11)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F5_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define NANDPIO_DEVICE_PROTECTION_ERRMASK_F5_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields norp_device_protection_errMask    */
#define NORP_DEVICE_PROTECTION_ERRMASK_F5_WIDTH                               1
#define NORP_DEVICE_PROTECTION_ERRMASK_F5_SHIFT                              10
#define NORP_DEVICE_PROTECTION_ERRMASK_F5_MASK                       0x00000400
#define NORP_DEVICE_PROTECTION_ERRMASK_F5_RD(src)    (((src) & 0x00000400)>>10)
#define NORP_DEVICE_PROTECTION_ERRMASK_F5_WR(src) \
                                                (((u32)(src)<<10) & 0x00000400)
#define NORP_DEVICE_PROTECTION_ERRMASK_F5_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields dma_cmd_override_errMask    */
#define DMA_CMD_OVERRIDE_ERRMASK_F5_WIDTH                                     1
#define DMA_CMD_OVERRIDE_ERRMASK_F5_SHIFT                                     9
#define DMA_CMD_OVERRIDE_ERRMASK_F5_MASK                             0x00000200
#define DMA_CMD_OVERRIDE_ERRMASK_F5_RD(src)           (((src) & 0x00000200)>>9)
#define DMA_CMD_OVERRIDE_ERRMASK_F5_WR(src)      (((u32)(src)<<9) & 0x00000200)
#define DMA_CMD_OVERRIDE_ERRMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields device_protection_errMask    */
#define DEVICE_PROTECTION_ERRMASK_F5_WIDTH                                    1
#define DEVICE_PROTECTION_ERRMASK_F5_SHIFT                                    8
#define DEVICE_PROTECTION_ERRMASK_F5_MASK                            0x00000100
#define DEVICE_PROTECTION_ERRMASK_F5_RD(src)          (((src) & 0x00000100)>>8)
#define DEVICE_PROTECTION_ERRMASK_F5_WR(src)     (((u32)(src)<<8) & 0x00000100)
#define DEVICE_PROTECTION_ERRMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields transaction_timeoutMask    */
#define TRANSACTION_TIMEOUTMASK_F5_WIDTH                                      1
#define TRANSACTION_TIMEOUTMASK_F5_SHIFT                                      7
#define TRANSACTION_TIMEOUTMASK_F5_MASK                              0x00000080
#define TRANSACTION_TIMEOUTMASK_F5_RD(src)            (((src) & 0x00000080)>>7)
#define TRANSACTION_TIMEOUTMASK_F5_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define TRANSACTION_TIMEOUTMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields parity_errMask    */
#define PARITY_ERRMASK_F5_WIDTH                                               1
#define PARITY_ERRMASK_F5_SHIFT                                               6
#define PARITY_ERRMASK_F5_MASK                                       0x00000040
#define PARITY_ERRMASK_F5_RD(src)                     (((src) & 0x00000040)>>6)
#define PARITY_ERRMASK_F5_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define PARITY_ERRMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ecc_err_singleMask    */
#define ECC_ERR_SINGLEMASK_F5_WIDTH                                           1
#define ECC_ERR_SINGLEMASK_F5_SHIFT                                           5
#define ECC_ERR_SINGLEMASK_F5_MASK                                   0x00000020
#define ECC_ERR_SINGLEMASK_F5_RD(src)                 (((src) & 0x00000020)>>5)
#define ECC_ERR_SINGLEMASK_F5_WR(src)            (((u32)(src)<<5) & 0x00000020)
#define ECC_ERR_SINGLEMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ecc_err_multipleMask    */
#define ECC_ERR_MULTIPLEMASK_F5_WIDTH                                         1
#define ECC_ERR_MULTIPLEMASK_F5_SHIFT                                         4
#define ECC_ERR_MULTIPLEMASK_F5_MASK                                 0x00000010
#define ECC_ERR_MULTIPLEMASK_F5_RD(src)               (((src) & 0x00000010)>>4)
#define ECC_ERR_MULTIPLEMASK_F5_WR(src)          (((u32)(src)<<4) & 0x00000010)
#define ECC_ERR_MULTIPLEMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields dma_doneMask    */
#define DMA_DONEMASK_F5_WIDTH                                                 1
#define DMA_DONEMASK_F5_SHIFT                                                 2
#define DMA_DONEMASK_F5_MASK                                         0x00000004
#define DMA_DONEMASK_F5_RD(src)                       (((src) & 0x00000004)>>2)
#define DMA_DONEMASK_F5_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DMA_DONEMASK_F5_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))

/*	Register gfc_bank5_sram_ctrl0	*/
/*	 Fields rtc	 */
#define REGSPEC_RTC0_F5_WIDTH                                                 3
#define REGSPEC_RTC0_F5_SHIFT                                                12
#define REGSPEC_RTC0_F5_MASK                                         0x00007000
#define REGSPEC_RTC0_F5_RD(src)                      (((src) & 0x00007000)>>12)
#define REGSPEC_RTC0_F5_WR(src)                 (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_RTC0_F5_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields muxen	 */
#define MUXEN0_F5_WIDTH                                                       1
#define MUXEN0_F5_SHIFT                                                      10
#define MUXEN0_F5_MASK                                               0x00000400
#define MUXEN0_F5_RD(src)                            (((src) & 0x00000400)>>10)
#define MUXEN0_F5_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define MUXEN0_F5_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields rdy_timeout_cnt	 */
#define RDY_TIMEOUT_CNT0_F5_WIDTH                                             3
#define RDY_TIMEOUT_CNT0_F5_SHIFT                                             2
#define RDY_TIMEOUT_CNT0_F5_MASK                                     0x0000001c
#define RDY_TIMEOUT_CNT0_F5_RD(src)                   (((src) & 0x0000001c)>>2)
#define RDY_TIMEOUT_CNT0_F5_WR(src)              (((u32)(src)<<2) & 0x0000001c)
#define RDY_TIMEOUT_CNT0_F5_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields ptd	 */
#define PTD0_F5_WIDTH                                                         1
#define PTD0_F5_SHIFT                                                         1
#define PTD0_F5_MASK                                                 0x00000002
#define PTD0_F5_RD(src)                               (((src) & 0x00000002)>>1)
#define PTD0_F5_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PTD0_F5_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields le	 */
#define LE0_F5_WIDTH                                                          1
#define LE0_F5_SHIFT                                                          0
#define LE0_F5_MASK                                                  0x00000001
#define LE0_F5_RD(src)                                   (((src) & 0x00000001))
#define LE0_F5_WR(src)                              (((u32)(src)) & 0x00000001)
#define LE0_F5_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_bank5_sram_nor_ctrl1	*/
/*	 Fields BME	 */
#define BME1_F5_WIDTH                                                         1
#define BME1_F5_SHIFT                                                        31
#define BME1_F5_MASK                                                 0x80000000
#define BME1_F5_RD(src)                              (((src) & 0x80000000)>>31)
#define BME1_F5_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define BME1_F5_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields OEO	 */
#define OEO1_F5_WIDTH                                                         1
#define OEO1_F5_SHIFT                                                        30
#define OEO1_F5_MASK                                                 0x40000000
#define OEO1_F5_RD(src)                              (((src) & 0x40000000)>>30)
#define OEO1_F5_WR(src)                         (((u32)(src)<<30) & 0x40000000)
#define OEO1_F5_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields BWT	 */
#define BWT1_F5_WIDTH                                                         5
#define BWT1_F5_SHIFT                                                        20
#define BWT1_F5_MASK                                                 0x01f00000
#define BWT1_F5_RD(src)                              (((src) & 0x01f00000)>>20)
#define BWT1_F5_WR(src)                         (((u32)(src)<<20) & 0x01f00000)
#define BWT1_F5_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields FWT	 */
#define FWT1_F5_WIDTH                                                         7
#define FWT1_F5_SHIFT                                                        12
#define FWT1_F5_MASK                                                 0x0007f000
#define FWT1_F5_RD(src)                              (((src) & 0x0007f000)>>12)
#define FWT1_F5_WR(src)                         (((u32)(src)<<12) & 0x0007f000)
#define FWT1_F5_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields TWT	 */
#define TWT1_F5_WIDTH                                                        10
#define TWT1_F5_SHIFT                                                         0
#define TWT1_F5_MASK                                                 0x000003ff
#define TWT1_F5_RD(src)                                  (((src) & 0x000003ff))
#define TWT1_F5_WR(src)                             (((u32)(src)) & 0x000003ff)
#define TWT1_F5_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register gfc_bank5_sram_nor_ctrl2	*/
/*	 Fields ALN	 */
#define ALN2_F5_WIDTH                                                         4
#define ALN2_F5_SHIFT                                                        28
#define ALN2_F5_MASK                                                 0xf0000000
#define ALN2_F5_RD(src)                              (((src) & 0xf0000000)>>28)
#define ALN2_F5_WR(src)                         (((u32)(src)<<28) & 0xf0000000)
#define ALN2_F5_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields PEN	 */
#define PEN2_F5_WIDTH                                                         1
#define PEN2_F5_SHIFT                                                        27
#define PEN2_F5_MASK                                                 0x08000000
#define PEN2_F5_RD(src)                              (((src) & 0x08000000)>>27)
#define PEN2_F5_WR(src)                         (((u32)(src)<<27) & 0x08000000)
#define PEN2_F5_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields BEM	 */
#define BEM2_F5_WIDTH                                                         1
#define BEM2_F5_SHIFT                                                        26
#define BEM2_F5_MASK                                                 0x04000000
#define BEM2_F5_RD(src)                              (((src) & 0x04000000)>>26)
#define BEM2_F5_WR(src)                         (((u32)(src)<<26) & 0x04000000)
#define BEM2_F5_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SOR	 */
#define SOR2_F5_WIDTH                                                         1
#define SOR2_F5_SHIFT                                                        25
#define SOR2_F5_MASK                                                 0x02000000
#define SOR2_F5_RD(src)                              (((src) & 0x02000000)>>25)
#define SOR2_F5_WR(src)                         (((u32)(src)<<25) & 0x02000000)
#define SOR2_F5_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RE	 */
#define RE2_F5_WIDTH                                                          1
#define RE2_F5_SHIFT                                                         24
#define RE2_F5_MASK                                                  0x01000000
#define RE2_F5_RD(src)                               (((src) & 0x01000000)>>24)
#define RE2_F5_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define RE2_F5_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields TH	 */
#define TH2_F5_WIDTH                                                          5
#define TH2_F5_SHIFT                                                         16
#define TH2_F5_MASK                                                  0x001f0000
#define TH2_F5_RD(src)                               (((src) & 0x001f0000)>>16)
#define TH2_F5_WR(src)                          (((u32)(src)<<16) & 0x001f0000)
#define TH2_F5_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WBF	 */
#define WBF2_F5_WIDTH                                                         4
#define WBF2_F5_SHIFT                                                        12
#define WBF2_F5_MASK                                                 0x0000f000
#define WBF2_F5_RD(src)                              (((src) & 0x0000f000)>>12)
#define WBF2_F5_WR(src)                         (((u32)(src)<<12) & 0x0000f000)
#define WBF2_F5_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WBN	 */
#define WBN2_F5_WIDTH                                                         4
#define WBN2_F5_SHIFT                                                         8
#define WBN2_F5_MASK                                                 0x00000f00
#define WBN2_F5_RD(src)                               (((src) & 0x00000f00)>>8)
#define WBN2_F5_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define WBN2_F5_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields OEN	 */
#define OEN2_F5_WIDTH                                                         4
#define OEN2_F5_SHIFT                                                         4
#define OEN2_F5_MASK                                                 0x000000f0
#define OEN2_F5_RD(src)                               (((src) & 0x000000f0)>>4)
#define OEN2_F5_WR(src)                          (((u32)(src)<<4) & 0x000000f0)
#define OEN2_F5_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields CSN	 */
#define CSN2_F5_WIDTH                                                         4
#define CSN2_F5_SHIFT                                                         0
#define CSN2_F5_MASK                                                 0x0000000f
#define CSN2_F5_RD(src)                                  (((src) & 0x0000000f))
#define CSN2_F5_WR(src)                             (((u32)(src)) & 0x0000000f)
#define CSN2_F5_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register gfc_bank5_nand_ctrl0	*/
/*	 Fields SPARE_OFFSET	 */
#define SPARE_OFFSET0_F5_WIDTH                                               16
#define SPARE_OFFSET0_F5_SHIFT                                               16
#define SPARE_OFFSET0_F5_MASK                                        0xffff0000
#define SPARE_OFFSET0_F5_RD(src)                     (((src) & 0xffff0000)>>16)
#define SPARE_OFFSET0_F5_WR(src)                (((u32)(src)<<16) & 0xffff0000)
#define SPARE_OFFSET0_F5_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields FORCE_SPARE_OFFSET	 */
#define FORCE_SPARE_OFFSET0_F5_WIDTH                                          1
#define FORCE_SPARE_OFFSET0_F5_SHIFT                                          9
#define FORCE_SPARE_OFFSET0_F5_MASK                                  0x00000200
#define FORCE_SPARE_OFFSET0_F5_RD(src)                (((src) & 0x00000200)>>9)
#define FORCE_SPARE_OFFSET0_F5_WR(src)           (((u32)(src)<<9) & 0x00000200)
#define FORCE_SPARE_OFFSET0_F5_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ECC_Algorithm	 */
#define ECC_ALGORITHM0_F5_WIDTH                                               1
#define ECC_ALGORITHM0_F5_SHIFT                                               8
#define ECC_ALGORITHM0_F5_MASK                                       0x00000100
#define ECC_ALGORITHM0_F5_RD(src)                     (((src) & 0x00000100)>>8)
#define ECC_ALGORITHM0_F5_WR(src)                (((u32)(src)<<8) & 0x00000100)
#define ECC_ALGORITHM0_F5_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ECC_ON_OFF	 */
#define ECC_ON_OFF0_F5_WIDTH                                                  1
#define ECC_ON_OFF0_F5_SHIFT                                                  7
#define ECC_ON_OFF0_F5_MASK                                          0x00000080
#define ECC_ON_OFF0_F5_RD(src)                        (((src) & 0x00000080)>>7)
#define ECC_ON_OFF0_F5_WR(src)                   (((u32)(src)<<7) & 0x00000080)
#define ECC_ON_OFF0_F5_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))

/*	Register gfc_bank5_nand_ctrl1	*/

/*	Register gfc_bank5_nand_ctrl2	*/

/*	Register gfc_bank5_nand_bch	*/
/*	 Fields bch_k	 */
#define BCH_K_F5_WIDTH                                                        3
#define BCH_K_F5_SHIFT                                                       20
#define BCH_K_F5_MASK                                                0x00700000
#define BCH_K_F5_RD(src)                             (((src) & 0x00700000)>>20)
#define BCH_K_F5_WR(src)                        (((u32)(src)<<20) & 0x00700000)
#define BCH_K_F5_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields bch_t	 */
#define BCH_T_F5_WIDTH                                                        4
#define BCH_T_F5_SHIFT                                                       16
#define BCH_T_F5_MASK                                                0x000f0000
#define BCH_T_F5_RD(src)                             (((src) & 0x000f0000)>>16)
#define BCH_T_F5_WR(src)                        (((u32)(src)<<16) & 0x000f0000)
#define BCH_T_F5_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields bch_n	 */
#define BCH_N_F5_WIDTH                                                       16
#define BCH_N_F5_SHIFT                                                        0
#define BCH_N_F5_MASK                                                0x0000ffff
#define BCH_N_F5_RD(src)                                 (((src) & 0x0000ffff))
#define BCH_N_F5_WR(src)                            (((u32)(src)) & 0x0000ffff)
#define BCH_N_F5_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank5_dma_ctrl1	*/
/*	 Fields dma_data_size	 */
#define DMA_DATA_SIZE1_F5_WIDTH                                              24
#define DMA_DATA_SIZE1_F5_SHIFT                                               0
#define DMA_DATA_SIZE1_F5_MASK                                       0x00ffffff
#define DMA_DATA_SIZE1_F5_RD(src)                        (((src) & 0x00ffffff))
#define DMA_DATA_SIZE1_F5_WR(src)                   (((u32)(src)) & 0x00ffffff)
#define DMA_DATA_SIZE1_F5_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register gfc_bank5_nand_ctrl3	*/
/*	 Fields page_size	 */
#define PAGE_SIZE3_F5_WIDTH                                                  16
#define PAGE_SIZE3_F5_SHIFT                                                   0
#define PAGE_SIZE3_F5_MASK                                           0x0000ffff
#define PAGE_SIZE3_F5_RD(src)                            (((src) & 0x0000ffff))
#define PAGE_SIZE3_F5_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define PAGE_SIZE3_F5_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank5_nand_ctrl4	*/
/*	 Fields device_size	 */
#define DEVICE_SIZE4_F5_WIDTH                                                16
#define DEVICE_SIZE4_F5_SHIFT                                                16
#define DEVICE_SIZE4_F5_MASK                                         0xffff0000
#define DEVICE_SIZE4_F5_RD(src)                      (((src) & 0xffff0000)>>16)
#define DEVICE_SIZE4_F5_WR(src)                 (((u32)(src)<<16) & 0xffff0000)
#define DEVICE_SIZE4_F5_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields block_size	 */
#define BLOCK_SIZE4_F5_WIDTH                                                 16
#define BLOCK_SIZE4_F5_SHIFT                                                  0
#define BLOCK_SIZE4_F5_MASK                                          0x0000ffff
#define BLOCK_SIZE4_F5_RD(src)                           (((src) & 0x0000ffff))
#define BLOCK_SIZE4_F5_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define BLOCK_SIZE4_F5_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_bank5_nand_timing0	*/
/*	 Fields t_adl	 */
#define T_ADL0_F5_WIDTH                                                       8
#define T_ADL0_F5_SHIFT                                                      24
#define T_ADL0_F5_MASK                                               0xff000000
#define T_ADL0_F5_RD(src)                            (((src) & 0xff000000)>>24)
#define T_ADL0_F5_WR(src)                       (((u32)(src)<<24) & 0xff000000)
#define T_ADL0_F5_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_wb	 */
#define T_WB0_F5_WIDTH                                                        8
#define T_WB0_F5_SHIFT                                                       16
#define T_WB0_F5_MASK                                                0x00ff0000
#define T_WB0_F5_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WB0_F5_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WB0_F5_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_rhw	 */
#define T_RHW0_F5_WIDTH                                                       8
#define T_RHW0_F5_SHIFT                                                       8
#define T_RHW0_F5_MASK                                               0x0000ff00
#define T_RHW0_F5_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_RHW0_F5_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_RHW0_F5_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_ccs	 */
#define T_CCS0_F5_WIDTH                                                       8
#define T_CCS0_F5_SHIFT                                                       0
#define T_CCS0_F5_MASK                                               0x000000ff
#define T_CCS0_F5_RD(src)                                (((src) & 0x000000ff))
#define T_CCS0_F5_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CCS0_F5_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank5_nand_timing1	*/
/*	 Fields t_alh_clh_ch	 */
#define T_ALH_CLH_CH1_F5_WIDTH                                                8
#define T_ALH_CLH_CH1_F5_SHIFT                                               24
#define T_ALH_CLH_CH1_F5_MASK                                        0xff000000
#define T_ALH_CLH_CH1_F5_RD(src)                     (((src) & 0xff000000)>>24)
#define T_ALH_CLH_CH1_F5_WR(src)                (((u32)(src)<<24) & 0xff000000)
#define T_ALH_CLH_CH1_F5_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_als_cls_cs	 */
#define T_ALS_CLS_CS1_F5_WIDTH                                                8
#define T_ALS_CLS_CS1_F5_SHIFT                                               16
#define T_ALS_CLS_CS1_F5_MASK                                        0x00ff0000
#define T_ALS_CLS_CS1_F5_RD(src)                     (((src) & 0x00ff0000)>>16)
#define T_ALS_CLS_CS1_F5_WR(src)                (((u32)(src)<<16) & 0x00ff0000)
#define T_ALS_CLS_CS1_F5_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_ds_wp	 */
#define T_DS_WP1_F5_WIDTH                                                     8
#define T_DS_WP1_F5_SHIFT                                                     8
#define T_DS_WP1_F5_MASK                                             0x0000ff00
#define T_DS_WP1_F5_RD(src)                           (((src) & 0x0000ff00)>>8)
#define T_DS_WP1_F5_WR(src)                      (((u32)(src)<<8) & 0x0000ff00)
#define T_DS_WP1_F5_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_dh_wh	 */
#define T_DH_WH1_F5_WIDTH                                                     8
#define T_DH_WH1_F5_SHIFT                                                     0
#define T_DH_WH1_F5_MASK                                             0x000000ff
#define T_DH_WH1_F5_RD(src)                              (((src) & 0x000000ff))
#define T_DH_WH1_F5_WR(src)                         (((u32)(src)) & 0x000000ff)
#define T_DH_WH1_F5_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank5_nand_timing2	*/
/*	 Fields t_ar_clr_whr_ir	 */
#define T_AR_CLR_WHR_IR2_F5_WIDTH                                             8
#define T_AR_CLR_WHR_IR2_F5_SHIFT                                            24
#define T_AR_CLR_WHR_IR2_F5_MASK                                     0xff000000
#define T_AR_CLR_WHR_IR2_F5_RD(src)                  (((src) & 0xff000000)>>24)
#define T_AR_CLR_WHR_IR2_F5_WR(src)             (((u32)(src)<<24) & 0xff000000)
#define T_AR_CLR_WHR_IR2_F5_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields t_rr	 */
#define T_RR2_F5_WIDTH                                                        8
#define T_RR2_F5_SHIFT                                                       16
#define T_RR2_F5_MASK                                                0x00ff0000
#define T_RR2_F5_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_RR2_F5_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_RR2_F5_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_reh	 */
#define T_REH2_F5_WIDTH                                                       8
#define T_REH2_F5_SHIFT                                                       8
#define T_REH2_F5_MASK                                               0x0000ff00
#define T_REH2_F5_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_REH2_F5_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_REH2_F5_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_rp	 */
#define T_RP2_F5_WIDTH                                                        8
#define T_RP2_F5_SHIFT                                                        0
#define T_RP2_F5_MASK                                                0x000000ff
#define T_RP2_F5_RD(src)                                 (((src) & 0x000000ff))
#define T_RP2_F5_WR(src)                            (((u32)(src)) & 0x000000ff)
#define T_RP2_F5_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank5_nand_timing3	*/
/*	 Fields t_ww	 */
#define T_WW3_F5_WIDTH                                                        8
#define T_WW3_F5_SHIFT                                                       16
#define T_WW3_F5_MASK                                                0x00ff0000
#define T_WW3_F5_RD(src)                             (((src) & 0x00ff0000)>>16)
#define T_WW3_F5_WR(src)                        (((u32)(src)<<16) & 0x00ff0000)
#define T_WW3_F5_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields t_chz	 */
#define T_CHZ3_F5_WIDTH                                                       8
#define T_CHZ3_F5_SHIFT                                                       8
#define T_CHZ3_F5_MASK                                               0x0000ff00
#define T_CHZ3_F5_RD(src)                             (((src) & 0x0000ff00)>>8)
#define T_CHZ3_F5_WR(src)                        (((u32)(src)<<8) & 0x0000ff00)
#define T_CHZ3_F5_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields t_cea	 */
#define T_CEA3_F5_WIDTH                                                       8
#define T_CEA3_F5_SHIFT                                                       0
#define T_CEA3_F5_MASK                                               0x000000ff
#define T_CEA3_F5_RD(src)                                (((src) & 0x000000ff))
#define T_CEA3_F5_WR(src)                           (((u32)(src)) & 0x000000ff)
#define T_CEA3_F5_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register gfc_bank5_nand_cor_err	*/
/*	 Fields counter	 */
#define COUNTER_F11_WIDTH                                                    32
#define COUNTER_F11_SHIFT                                                     0
#define COUNTER_F11_MASK                                             0xffffffff
#define COUNTER_F11_RD(src)                              (((src) & 0xffffffff))
#define COUNTER_F11_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_bank5_nand_uncor_err	*/
/*	 Fields counter	 */
#define COUNTER_F12_WIDTH                                                    32
#define COUNTER_F12_SHIFT                                                     0
#define COUNTER_F12_MASK                                             0xffffffff
#define COUNTER_F12_RD(src)                              (((src) & 0xffffffff))
#define COUNTER_F12_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define GFC_CLKRST_CSR_BASE_ADDR			0x01701c000ULL

/*    Address GFC_CLKRST_CSR  Registers */
#define GFC_SRST_ADDR                                                0x00000000
#define GFC_SRST_DEFAULT                                             0x00000000
#define GFC_CLKEN_ADDR                                               0x00000008
#define GFC_CLKEN_DEFAULT                                            0x00000007
#define GFC_GPIO_FL0_ADDR                                            0x0000000c
#define GFC_GPIO_FL0_DEFAULT                                         0xffffffff
#define GFC_GPIO_FL0_MUX_ADDR                                        0x00000010
#define GFC_GPIO_FL0_MUX_DEFAULT                                     0x00000000
#define GFC_GPI_FL0_ADDR                                             0x00000014
#define GFC_GPI_FL0_DEFAULT                                          0x00000000
#define GFC_GPIO_FL1_ADDR                                            0x00000018
#define GFC_GPIO_FL1_DEFAULT                                         0xffffffff
#define GFC_GPIO_FL1_MUX_ADDR                                        0x0000001c
#define GFC_GPIO_FL1_MUX_DEFAULT                                     0x00000000
#define GFC_GPI_FL1_ADDR                                             0x00000020
#define GFC_GPI_FL1_DEFAULT                                          0x00000000
#define GFC_GPIO_FL2_ADDR                                            0x00000024
#define GFC_GPIO_FL2_DEFAULT                                         0xffffffff
#define GFC_GPIO_FL2_MUX_ADDR                                        0x00000028
#define GFC_GPIO_FL2_MUX_DEFAULT                                     0x00000000
#define GFC_GPI_FL2_ADDR                                             0x0000002c
#define GFC_GPI_FL2_DEFAULT                                          0x00000000
#define GFC_GPIO_FL0_OD_ADDR                                         0x00000030
#define GFC_GPIO_FL0_OD_DEFAULT                                      0x00000000
#define GFC_GPIO_FL1_OD_ADDR                                         0x00000034
#define GFC_GPIO_FL1_OD_DEFAULT                                      0x00000000
#define GFC_GPIO_FL2_OD_ADDR                                         0x00000038
#define GFC_GPIO_FL2_OD_DEFAULT                                      0x00000000

/*	Register gfc_srst	*/
/*	 Fields axi_reset	 */
#define AXI_RESET_WIDTH                                                       1
#define AXI_RESET_SHIFT                                                       2
#define AXI_RESET_MASK                                               0x00000004
#define AXI_RESET_RD(src)                             (((src) & 0x00000004)>>2)
#define AXI_RESET_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define AXI_RESET_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields gfc_reset	 */
#define GFC_RESET_WIDTH                                                       1
#define GFC_RESET_SHIFT                                                       1
#define GFC_RESET_MASK                                               0x00000002
#define GFC_RESET_RD(src)                             (((src) & 0x00000002)>>1)
#define GFC_RESET_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define GFC_RESET_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields csr_reset	 */
#define CSR_RESET_WIDTH                                                       1
#define CSR_RESET_SHIFT                                                       0
#define CSR_RESET_MASK                                               0x00000001
#define CSR_RESET_RD(src)                                (((src) & 0x00000001))
#define CSR_RESET_WR(src)                           (((u32)(src)) & 0x00000001)
#define CSR_RESET_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_clken	*/
/*	 Fields axi_clken	 */
#define AXI_CLKEN_WIDTH                                                       1
#define AXI_CLKEN_SHIFT                                                       2
#define AXI_CLKEN_MASK                                               0x00000004
#define AXI_CLKEN_RD(src)                             (((src) & 0x00000004)>>2)
#define AXI_CLKEN_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define AXI_CLKEN_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields gfc_clken	 */
#define GFC_CLKEN_WIDTH                                                       1
#define GFC_CLKEN_SHIFT                                                       1
#define GFC_CLKEN_MASK                                               0x00000002
#define GFC_CLKEN_RD(src)                             (((src) & 0x00000002)>>1)
#define GFC_CLKEN_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define GFC_CLKEN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields csr_clken	 */
#define CSR_CLKEN_WIDTH                                                       1
#define CSR_CLKEN_SHIFT                                                       0
#define CSR_CLKEN_MASK                                               0x00000001
#define CSR_CLKEN_RD(src)                                (((src) & 0x00000001))
#define CSR_CLKEN_WR(src)                           (((u32)(src)) & 0x00000001)
#define CSR_CLKEN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register gfc_gpio_fl0	*/
/*	 Fields data	 */
#define DATA0_WIDTH                                                          16
#define DATA0_SHIFT                                                          16
#define DATA0_MASK                                                   0xffff0000
#define DATA0_RD(src)                                (((src) & 0xffff0000)>>16)
#define DATA0_WR(src)                           (((u32)(src)<<16) & 0xffff0000)
#define DATA0_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields oe_n	 */
#define OE_N0_WIDTH                                                          16
#define OE_N0_SHIFT                                                           0
#define OE_N0_MASK                                                   0x0000ffff
#define OE_N0_RD(src)                                    (((src) & 0x0000ffff))
#define OE_N0_WR(src)                               (((u32)(src)) & 0x0000ffff)
#define OE_N0_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl0_mux	*/
/*	 Fields sel	 */
#define REGSPEC_SEL_WIDTH                                                    32
#define REGSPEC_SEL_SHIFT                                                     0
#define REGSPEC_SEL_MASK                                             0xffffffff
#define REGSPEC_SEL_RD(src)                              (((src) & 0xffffffff))
#define REGSPEC_SEL_WR(src)                         (((u32)(src)) & 0xffffffff)
#define REGSPEC_SEL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_gpi_fl0	*/
/*	 Fields data	 */
#define DATA0_F1_WIDTH                                                       16
#define DATA0_F1_SHIFT                                                        0
#define DATA0_F1_MASK                                                0x0000ffff
#define DATA0_F1_RD(src)                                 (((src) & 0x0000ffff))
#define DATA0_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl1	*/
/*	 Fields data	 */
#define DATA1_WIDTH                                                          16
#define DATA1_SHIFT                                                          16
#define DATA1_MASK                                                   0xffff0000
#define DATA1_RD(src)                                (((src) & 0xffff0000)>>16)
#define DATA1_WR(src)                           (((u32)(src)<<16) & 0xffff0000)
#define DATA1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields oe_n	 */
#define OE_N1_WIDTH                                                          16
#define OE_N1_SHIFT                                                           0
#define OE_N1_MASK                                                   0x0000ffff
#define OE_N1_RD(src)                                    (((src) & 0x0000ffff))
#define OE_N1_WR(src)                               (((u32)(src)) & 0x0000ffff)
#define OE_N1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl1_mux	*/
/*	 Fields sel	 */
#define REGSPEC_SEL_F1_WIDTH                                                 32
#define REGSPEC_SEL_F1_SHIFT                                                  0
#define REGSPEC_SEL_F1_MASK                                          0xffffffff
#define REGSPEC_SEL_F1_RD(src)                           (((src) & 0xffffffff))
#define REGSPEC_SEL_F1_WR(src)                      (((u32)(src)) & 0xffffffff)
#define REGSPEC_SEL_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_gpi_fl1	*/
/*	 Fields data	 */
#define DATA1_F1_WIDTH                                                       16
#define DATA1_F1_SHIFT                                                        0
#define DATA1_F1_MASK                                                0x0000ffff
#define DATA1_F1_RD(src)                                 (((src) & 0x0000ffff))
#define DATA1_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl2	*/
/*	 Fields data	 */
#define DATA2_WIDTH                                                          16
#define DATA2_SHIFT                                                          16
#define DATA2_MASK                                                   0xffff0000
#define DATA2_RD(src)                                (((src) & 0xffff0000)>>16)
#define DATA2_WR(src)                           (((u32)(src)<<16) & 0xffff0000)
#define DATA2_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields oe_n	 */
#define OE_N2_WIDTH                                                          16
#define OE_N2_SHIFT                                                           0
#define OE_N2_MASK                                                   0x0000ffff
#define OE_N2_RD(src)                                    (((src) & 0x0000ffff))
#define OE_N2_WR(src)                               (((u32)(src)) & 0x0000ffff)
#define OE_N2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl2_mux	*/
/*	 Fields sel	 */
#define REGSPEC_SEL_F2_WIDTH                                                 32
#define REGSPEC_SEL_F2_SHIFT                                                  0
#define REGSPEC_SEL_F2_MASK                                          0xffffffff
#define REGSPEC_SEL_F2_RD(src)                           (((src) & 0xffffffff))
#define REGSPEC_SEL_F2_WR(src)                      (((u32)(src)) & 0xffffffff)
#define REGSPEC_SEL_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register gfc_gpi_fl2	*/
/*	 Fields data	 */
#define DATA2_F1_WIDTH                                                       16
#define DATA2_F1_SHIFT                                                        0
#define DATA2_F1_MASK                                                0x0000ffff
#define DATA2_F1_RD(src)                                 (((src) & 0x0000ffff))
#define DATA2_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl0_od	*/
/*	 Fields od	 */
#define OD_WIDTH                                                             16
#define OD_SHIFT                                                              0
#define OD_MASK                                                      0x0000ffff
#define OD_RD(src)                                       (((src) & 0x0000ffff))
#define OD_WR(src)                                  (((u32)(src)) & 0x0000ffff)
#define OD_SET(dst,src) (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl1_od	*/
/*	 Fields od	 */
#define OD_F1_WIDTH                                                          16
#define OD_F1_SHIFT                                                           0
#define OD_F1_MASK                                                   0x0000ffff
#define OD_F1_RD(src)                                    (((src) & 0x0000ffff))
#define OD_F1_WR(src)                               (((u32)(src)) & 0x0000ffff)
#define OD_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register gfc_gpio_fl2_od	*/
/*	 Fields od	 */
#define OD_F2_WIDTH                                                          16
#define OD_F2_SHIFT                                                           0
#define OD_F2_MASK                                                   0x0000ffff
#define OD_F2_RD(src)                                    (((src) & 0x0000ffff))
#define OD_F2_WR(src)                               (((u32)(src)) & 0x0000ffff)
#define OD_F2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Global Base Address	*/
#define REGSPEC_GLBL_DIAG_CSR_BASE_ADDR			0x01701d000ULL

/*    Address GLBL_DIAG_CSR  Registers */
#define REGSPEC_CFG_DIAG_SEL_ADDR                                    0x00000000
#define REGSPEC_CFG_DIAG_SEL_DEFAULT                                 0x00000000
#define REGSPEC_CFG_READ_BW_LAT_ADDR_MASK_ADDR                       0x00000004
#define REGSPEC_CFG_READ_BW_LAT_ADDR_MASK_DEFAULT                    0x00000000
#define REGSPEC_CFG_READ_BW_LAT_ADDR_PAT_ADDR                        0x00000008
#define REGSPEC_CFG_READ_BW_LAT_ADDR_PAT_DEFAULT                     0xffffffff
#define REGSPEC_CFG_WRITE_BW_LAT_ADDR_MASK_ADDR                      0x0000000c
#define REGSPEC_CFG_WRITE_BW_LAT_ADDR_MASK_DEFAULT                   0x00000000
#define REGSPEC_CFG_WRITE_BW_LAT_ADDR_PAT_ADDR                       0x00000010
#define REGSPEC_CFG_WRITE_BW_LAT_ADDR_PAT_DEFAULT                    0xffffffff
#define REGSPEC_CFG_DIAG_START_STOP_ADDR                             0x00000014
#define REGSPEC_CFG_DIAG_START_STOP_DEFAULT                          0x0000001f
#define REGSPEC_CFG_BW_MSTR_STOP_CNT_ADDR                            0x00000018
#define REGSPEC_CFG_BW_MSTR_STOP_CNT_DEFAULT                         0x00040004
#define REGSPEC_CFG_BW_SLV_STOP_CNT_ADDR                             0x0000001c
#define REGSPEC_CFG_BW_SLV_STOP_CNT_DEFAULT                          0x00040004
#define REGSPEC_STS_READ_LATENCY_OUTPUT_ADDR                         0x00000020
#define REGSPEC_STS_READ_LATENCY_OUTPUT_DEFAULT                      0x00000000
#define REGSPEC_STS_AXI_MRD_BW_CLK_CNT_ADDR                          0x00000024
#define REGSPEC_STS_AXI_MRD_BW_CLK_CNT_DEFAULT                       0x00000000
#define REGSPEC_STS_AXI_MRD_BW_BYTE_CNT_ADDR                         0x00000028
#define REGSPEC_STS_AXI_MRD_BW_BYTE_CNT_DEFAULT                      0x00000000
#define REGSPEC_STS_AXI_MWR_BW_CLK_CNT_ADDR                          0x0000002c
#define REGSPEC_STS_AXI_MWR_BW_CLK_CNT_DEFAULT                       0x00000000
#define REGSPEC_STS_AXI_MWR_BW_BYTE_CNT_ADDR                         0x00000030
#define REGSPEC_STS_AXI_MWR_BW_BYTE_CNT_DEFAULT                      0x00000000
#define REGSPEC_STS_AXI_SRD_BW_CLK_CNT_ADDR                          0x00000034
#define REGSPEC_STS_AXI_SRD_BW_CLK_CNT_DEFAULT                       0x00000000
#define REGSPEC_STS_AXI_SRD_BW_BYTE_CNT_ADDR                         0x00000038
#define REGSPEC_STS_AXI_SRD_BW_BYTE_CNT_DEFAULT                      0x00000000
#define REGSPEC_STS_AXI_SWR_BW_CLK_CNT_ADDR                          0x0000003c
#define REGSPEC_STS_AXI_SWR_BW_CLK_CNT_DEFAULT                       0x00000000
#define REGSPEC_STS_AXI_SWR_BW_BYTE_CNT_ADDR                         0x00000040
#define REGSPEC_STS_AXI_SWR_BW_BYTE_CNT_DEFAULT                      0x00000000
#define REGSPEC_CFG_DBG_TRIG_CTRL_ADDR                               0x00000044
#define REGSPEC_CFG_DBG_TRIG_CTRL_DEFAULT                            0x00000000
#define REGSPEC_CFG_DBG_PAT_REG_0_ADDR                               0x00000048
#define REGSPEC_CFG_DBG_PAT_REG_0_DEFAULT                            0x00000000
#define REGSPEC_CFG_DBG_PAT_MASK_REG_0_ADDR                          0x0000004c
#define REGSPEC_CFG_DBG_PAT_MASK_REG_0_DEFAULT                       0x00000000
#define REGSPEC_CFG_DBG_PAT_REG_1_ADDR                               0x00000050
#define REGSPEC_CFG_DBG_PAT_REG_1_DEFAULT                            0x00000000
#define REGSPEC_CFG_DBG_PAT_MASK_REG_1_ADDR                          0x00000054
#define REGSPEC_CFG_DBG_PAT_MASK_REG_1_DEFAULT                       0x00000000
#define REGSPEC_DBG_TRIG_OUT_ADDR                                    0x00000058
#define REGSPEC_DBG_TRIG_OUT_DEFAULT                                 0x00000000
#define REGSPEC_DBG_TRIG_INT_ADDR                                    0x0000005c
#define REGSPEC_DBG_TRIG_INT_DEFAULT                                 0x00000000
#define REGSPEC_DBG_TRIG_INTMASK_ADDR                                0x00000060
#define REGSPEC_CFG_MEM_ECC_BYPASS_ADDR                              0x00000068
#define REGSPEC_CFG_MEM_ECC_BYPASS_DEFAULT                           0x00000000
#define REGSPEC_CFG_MEM_PWRDN_DIS_ADDR                               0x0000006c
#define REGSPEC_CFG_MEM_PWRDN_DIS_DEFAULT                            0x00000000
#define REGSPEC_CFG_MEM_RAM_SHUTDOWN_ADDR                            0x00000070
#define REGSPEC_CFG_MEM_RAM_SHUTDOWN_DEFAULT                         0xffffffff
#define REGSPEC_BLOCK_MEM_RDY_ADDR                                   0x00000074
#define REGSPEC_BLOCK_MEM_RDY_DEFAULT                                0xffffffff
#define REGSPEC_STS_READ_LATENCY_TOT_READ_REQS_ADDR                  0x0000008c
#define REGSPEC_STS_READ_LATENCY_TOT_READ_REQS_DEFAULT               0x00000000

/*	Register CFG_DIAG_SEL	*/
/*	 Fields CFG_SHIM_BLK_DBUS_MUX_SELECT	 */
#define REGSPEC_CFG_SHIM_BLK_DBUS_MUX_SELECT_WIDTH                            1
#define REGSPEC_CFG_SHIM_BLK_DBUS_MUX_SELECT_SHIFT                           12
#define REGSPEC_CFG_SHIM_BLK_DBUS_MUX_SELECT_MASK                    0x00001000
#define REGSPEC_CFG_SHIM_BLK_DBUS_MUX_SELECT_RD(src) \
                                                    (((src) & 0x00001000)>>12)
#define REGSPEC_CFG_SHIM_BLK_DBUS_MUX_SELECT_WR(src) \
                                                (((u32)(src)<<12) & 0x00001000)
#define REGSPEC_CFG_SHIM_BLK_DBUS_MUX_SELECT_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields CFG_AXI_NON_AXI_MUX_SELECT	 */
#define REGSPEC_CFG_AXI_NON_AXI_MUX_SELECT_WIDTH                              1
#define REGSPEC_CFG_AXI_NON_AXI_MUX_SELECT_SHIFT                             11
#define REGSPEC_CFG_AXI_NON_AXI_MUX_SELECT_MASK                      0x00000800
#define REGSPEC_CFG_AXI_NON_AXI_MUX_SELECT_RD(src)   (((src) & 0x00000800)>>11)
#define REGSPEC_CFG_AXI_NON_AXI_MUX_SELECT_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define REGSPEC_CFG_AXI_NON_AXI_MUX_SELECT_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields CFG_MUX_SELECTOR	 */
#define REGSPEC_CFG_MUX_SELECTOR_WIDTH                                       11
#define REGSPEC_CFG_MUX_SELECTOR_SHIFT                                        0
#define REGSPEC_CFG_MUX_SELECTOR_MASK                                0x000007ff
#define REGSPEC_CFG_MUX_SELECTOR_RD(src)                 (((src) & 0x000007ff))
#define REGSPEC_CFG_MUX_SELECTOR_WR(src)            (((u32)(src)) & 0x000007ff)
#define REGSPEC_CFG_MUX_SELECTOR_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register CFG_READ_BW_LAT_ADDR_MASK	*/
/*	 Fields READ_ADDR_MASK	 */
#define REGSPEC_READ_ADDR_MASK_WIDTH                                         32
#define REGSPEC_READ_ADDR_MASK_SHIFT                                          0
#define REGSPEC_READ_ADDR_MASK_MASK                                  0xffffffff
#define REGSPEC_READ_ADDR_MASK_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_READ_ADDR_MASK_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_READ_ADDR_MASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_READ_BW_LAT_ADDR_PAT	*/
/*	 Fields READ_ADDR_PAT	 */
#define REGSPEC_READ_ADDR_PAT_WIDTH                                          32
#define REGSPEC_READ_ADDR_PAT_SHIFT                                           0
#define REGSPEC_READ_ADDR_PAT_MASK                                   0xffffffff
#define REGSPEC_READ_ADDR_PAT_RD(src)                    (((src) & 0xffffffff))
#define REGSPEC_READ_ADDR_PAT_WR(src)               (((u32)(src)) & 0xffffffff)
#define REGSPEC_READ_ADDR_PAT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_WRITE_BW_LAT_ADDR_MASK	*/
/*	 Fields WRITE_ADDR_MASK	 */
#define REGSPEC_WRITE_ADDR_MASK_WIDTH                                        32
#define REGSPEC_WRITE_ADDR_MASK_SHIFT                                         0
#define REGSPEC_WRITE_ADDR_MASK_MASK                                 0xffffffff
#define REGSPEC_WRITE_ADDR_MASK_RD(src)                  (((src) & 0xffffffff))
#define REGSPEC_WRITE_ADDR_MASK_WR(src)             (((u32)(src)) & 0xffffffff)
#define REGSPEC_WRITE_ADDR_MASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_WRITE_BW_LAT_ADDR_PAT	*/
/*	 Fields WRITE_ADDR_PAT	 */
#define REGSPEC_WRITE_ADDR_PAT_WIDTH                                         32
#define REGSPEC_WRITE_ADDR_PAT_SHIFT                                          0
#define REGSPEC_WRITE_ADDR_PAT_MASK                                  0xffffffff
#define REGSPEC_WRITE_ADDR_PAT_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_WRITE_ADDR_PAT_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_WRITE_ADDR_PAT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DIAG_START_STOP	*/
/*	 Fields START_RD_LATENCY	 */
#define REGSPEC_START_RD_LATENCY_WIDTH                                        1
#define REGSPEC_START_RD_LATENCY_SHIFT                                        4
#define REGSPEC_START_RD_LATENCY_MASK                                0x00000010
#define REGSPEC_START_RD_LATENCY_RD(src)              (((src) & 0x00000010)>>4)
#define REGSPEC_START_RD_LATENCY_WR(src)         (((u32)(src)<<4) & 0x00000010)
#define REGSPEC_START_RD_LATENCY_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields START_SRD_BW	 */
#define REGSPEC_START_SRD_BW_WIDTH                                            1
#define REGSPEC_START_SRD_BW_SHIFT                                            3
#define REGSPEC_START_SRD_BW_MASK                                    0x00000008
#define REGSPEC_START_SRD_BW_RD(src)                  (((src) & 0x00000008)>>3)
#define REGSPEC_START_SRD_BW_WR(src)             (((u32)(src)<<3) & 0x00000008)
#define REGSPEC_START_SRD_BW_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields START_MRD_BW	 */
#define REGSPEC_START_MRD_BW_WIDTH                                            1
#define REGSPEC_START_MRD_BW_SHIFT                                            2
#define REGSPEC_START_MRD_BW_MASK                                    0x00000004
#define REGSPEC_START_MRD_BW_RD(src)                  (((src) & 0x00000004)>>2)
#define REGSPEC_START_MRD_BW_WR(src)             (((u32)(src)<<2) & 0x00000004)
#define REGSPEC_START_MRD_BW_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields START_SWR_BW	 */
#define REGSPEC_START_SWR_BW_WIDTH                                            1
#define REGSPEC_START_SWR_BW_SHIFT                                            1
#define REGSPEC_START_SWR_BW_MASK                                    0x00000002
#define REGSPEC_START_SWR_BW_RD(src)                  (((src) & 0x00000002)>>1)
#define REGSPEC_START_SWR_BW_WR(src)             (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_START_SWR_BW_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields START_MWR_BW	 */
#define REGSPEC_START_MWR_BW_WIDTH                                            1
#define REGSPEC_START_MWR_BW_SHIFT                                            0
#define REGSPEC_START_MWR_BW_MASK                                    0x00000001
#define REGSPEC_START_MWR_BW_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_START_MWR_BW_WR(src)                (((u32)(src)) & 0x00000001)
#define REGSPEC_START_MWR_BW_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_BW_MSTR_STOP_CNT	*/
/*	 Fields MSTR_STOP_RD_CNT	 */
#define REGSPEC_MSTR_STOP_RD_CNT_WIDTH                                       16
#define REGSPEC_MSTR_STOP_RD_CNT_SHIFT                                       16
#define REGSPEC_MSTR_STOP_RD_CNT_MASK                                0xffff0000
#define REGSPEC_MSTR_STOP_RD_CNT_RD(src)             (((src) & 0xffff0000)>>16)
#define REGSPEC_MSTR_STOP_RD_CNT_WR(src)        (((u32)(src)<<16) & 0xffff0000)
#define REGSPEC_MSTR_STOP_RD_CNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields MSTR_STOP_WR_CNT	 */
#define REGSPEC_MSTR_STOP_WR_CNT_WIDTH                                       16
#define REGSPEC_MSTR_STOP_WR_CNT_SHIFT                                        0
#define REGSPEC_MSTR_STOP_WR_CNT_MASK                                0x0000ffff
#define REGSPEC_MSTR_STOP_WR_CNT_RD(src)                 (((src) & 0x0000ffff))
#define REGSPEC_MSTR_STOP_WR_CNT_WR(src)            (((u32)(src)) & 0x0000ffff)
#define REGSPEC_MSTR_STOP_WR_CNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_BW_SLV_STOP_CNT	*/
/*	 Fields SLV_STOP_RD_CNT	 */
#define REGSPEC_SLV_STOP_RD_CNT_WIDTH                                        16
#define REGSPEC_SLV_STOP_RD_CNT_SHIFT                                        16
#define REGSPEC_SLV_STOP_RD_CNT_MASK                                 0xffff0000
#define REGSPEC_SLV_STOP_RD_CNT_RD(src)              (((src) & 0xffff0000)>>16)
#define REGSPEC_SLV_STOP_RD_CNT_WR(src)         (((u32)(src)<<16) & 0xffff0000)
#define REGSPEC_SLV_STOP_RD_CNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields SLV_STOP_WR_CNT	 */
#define REGSPEC_SLV_STOP_WR_CNT_WIDTH                                        16
#define REGSPEC_SLV_STOP_WR_CNT_SHIFT                                         0
#define REGSPEC_SLV_STOP_WR_CNT_MASK                                 0x0000ffff
#define REGSPEC_SLV_STOP_WR_CNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_SLV_STOP_WR_CNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_SLV_STOP_WR_CNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register STS_READ_LATENCY_OUTPUT	*/
/*	 Fields READ_MAX	 */
#define REGSPEC_READ_MAX_WIDTH                                               10
#define REGSPEC_READ_MAX_SHIFT                                               22
#define REGSPEC_READ_MAX_MASK                                        0xffc00000
#define REGSPEC_READ_MAX_RD(src)                     (((src) & 0xffc00000)>>22)
#define REGSPEC_READ_MAX_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields READ_TOT	 */
#define REGSPEC_READ_TOT_WIDTH                                               22
#define REGSPEC_READ_TOT_SHIFT                                                0
#define REGSPEC_READ_TOT_MASK                                        0x003fffff
#define REGSPEC_READ_TOT_RD(src)                         (((src) & 0x003fffff))
#define REGSPEC_READ_TOT_SET(dst,src) \
                          (((dst) & ~0x003fffff) | (((u32)(src)) & 0x003fffff))

/*	Register STS_AXI_MRD_BW_CLK_CNT	*/
/*	 Fields MSTR_READ_BW_CLK_CNT	 */
#define REGSPEC_MSTR_READ_BW_CLK_CNT_WIDTH                                   32
#define REGSPEC_MSTR_READ_BW_CLK_CNT_SHIFT                                    0
#define REGSPEC_MSTR_READ_BW_CLK_CNT_MASK                            0xffffffff
#define REGSPEC_MSTR_READ_BW_CLK_CNT_RD(src)             (((src) & 0xffffffff))
#define REGSPEC_MSTR_READ_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_MRD_BW_BYTE_CNT	*/
/*	 Fields MSTR_READ_BW_BYTE_CNT	 */
#define REGSPEC_MSTR_READ_BW_BYTE_CNT_WIDTH                                  32
#define REGSPEC_MSTR_READ_BW_BYTE_CNT_SHIFT                                   0
#define REGSPEC_MSTR_READ_BW_BYTE_CNT_MASK                           0xffffffff
#define REGSPEC_MSTR_READ_BW_BYTE_CNT_RD(src)            (((src) & 0xffffffff))
#define REGSPEC_MSTR_READ_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_MWR_BW_CLK_CNT	*/
/*	 Fields MSTR_WRITE_BW_CLK_CNT	 */
#define REGSPEC_MSTR_WRITE_BW_CLK_CNT_WIDTH                                  32
#define REGSPEC_MSTR_WRITE_BW_CLK_CNT_SHIFT                                   0
#define REGSPEC_MSTR_WRITE_BW_CLK_CNT_MASK                           0xffffffff
#define REGSPEC_MSTR_WRITE_BW_CLK_CNT_RD(src)            (((src) & 0xffffffff))
#define REGSPEC_MSTR_WRITE_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_MWR_BW_BYTE_CNT	*/
/*	 Fields MSTR_WRITE_BW_BYTE_CNT	 */
#define REGSPEC_MSTR_WRITE_BW_BYTE_CNT_WIDTH                                 32
#define REGSPEC_MSTR_WRITE_BW_BYTE_CNT_SHIFT                                  0
#define REGSPEC_MSTR_WRITE_BW_BYTE_CNT_MASK                          0xffffffff
#define REGSPEC_MSTR_WRITE_BW_BYTE_CNT_RD(src)           (((src) & 0xffffffff))
#define REGSPEC_MSTR_WRITE_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SRD_BW_CLK_CNT	*/
/*	 Fields SLV_READ_BW_CLK_CNT	 */
#define REGSPEC_SLV_READ_BW_CLK_CNT_WIDTH                                    32
#define REGSPEC_SLV_READ_BW_CLK_CNT_SHIFT                                     0
#define REGSPEC_SLV_READ_BW_CLK_CNT_MASK                             0xffffffff
#define REGSPEC_SLV_READ_BW_CLK_CNT_RD(src)              (((src) & 0xffffffff))
#define REGSPEC_SLV_READ_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SRD_BW_BYTE_CNT	*/
/*	 Fields SLV_READ_BW_BYTE_CNT	 */
#define REGSPEC_SLV_READ_BW_BYTE_CNT_WIDTH                                   32
#define REGSPEC_SLV_READ_BW_BYTE_CNT_SHIFT                                    0
#define REGSPEC_SLV_READ_BW_BYTE_CNT_MASK                            0xffffffff
#define REGSPEC_SLV_READ_BW_BYTE_CNT_RD(src)             (((src) & 0xffffffff))
#define REGSPEC_SLV_READ_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SWR_BW_CLK_CNT	*/
/*	 Fields SLV_WRITE_BW_CLK_CNT	 */
#define REGSPEC_SLV_WRITE_BW_CLK_CNT_WIDTH                                   32
#define REGSPEC_SLV_WRITE_BW_CLK_CNT_SHIFT                                    0
#define REGSPEC_SLV_WRITE_BW_CLK_CNT_MASK                            0xffffffff
#define REGSPEC_SLV_WRITE_BW_CLK_CNT_RD(src)             (((src) & 0xffffffff))
#define REGSPEC_SLV_WRITE_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SWR_BW_BYTE_CNT	*/
/*	 Fields SLV_WRITE_BW_BYTE_CNT	 */
#define REGSPEC_SLV_WRITE_BW_BYTE_CNT_WIDTH                                  32
#define REGSPEC_SLV_WRITE_BW_BYTE_CNT_SHIFT                                   0
#define REGSPEC_SLV_WRITE_BW_BYTE_CNT_MASK                           0xffffffff
#define REGSPEC_SLV_WRITE_BW_BYTE_CNT_RD(src)            (((src) & 0xffffffff))
#define REGSPEC_SLV_WRITE_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_TRIG_CTRL	*/
/*	 Fields TRIG_EN	 */
#define REGSPEC_TRIG_EN_WIDTH                                                 1
#define REGSPEC_TRIG_EN_SHIFT                                                 4
#define REGSPEC_TRIG_EN_MASK                                         0x00000010
#define REGSPEC_TRIG_EN_RD(src)                       (((src) & 0x00000010)>>4)
#define REGSPEC_TRIG_EN_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define REGSPEC_TRIG_EN_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields AND_E	 */
#define REGSPEC_AND_E_WIDTH                                                   2
#define REGSPEC_AND_E_SHIFT                                                   2
#define REGSPEC_AND_E_MASK                                           0x0000000c
#define REGSPEC_AND_E_RD(src)                         (((src) & 0x0000000c)>>2)
#define REGSPEC_AND_E_WR(src)                    (((u32)(src)<<2) & 0x0000000c)
#define REGSPEC_AND_E_SET(dst,src) \
                       (((dst) & ~0x0000000c) | (((u32)(src)<<2) & 0x0000000c))
/*	 Fields OR_E	 */
#define REGSPEC_OR_E_WIDTH                                                    2
#define REGSPEC_OR_E_SHIFT                                                    0
#define REGSPEC_OR_E_MASK                                            0x00000003
#define REGSPEC_OR_E_RD(src)                             (((src) & 0x00000003))
#define REGSPEC_OR_E_WR(src)                        (((u32)(src)) & 0x00000003)
#define REGSPEC_OR_E_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register CFG_DBG_PAT_REG_0	*/
/*	 Fields PATTERN	 */
#define REGSPEC_PATTERN0_WIDTH                                               32
#define REGSPEC_PATTERN0_SHIFT                                                0
#define REGSPEC_PATTERN0_MASK                                        0xffffffff
#define REGSPEC_PATTERN0_RD(src)                         (((src) & 0xffffffff))
#define REGSPEC_PATTERN0_WR(src)                    (((u32)(src)) & 0xffffffff)
#define REGSPEC_PATTERN0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_PAT_MASK_REG_0	*/
/*	 Fields PAT_MASK	 */
#define REGSPEC_PAT_MASK0_WIDTH                                              32
#define REGSPEC_PAT_MASK0_SHIFT                                               0
#define REGSPEC_PAT_MASK0_MASK                                       0xffffffff
#define REGSPEC_PAT_MASK0_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_PAT_MASK0_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_PAT_MASK0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_PAT_REG_1	*/
/*	 Fields PATTERN	 */
#define REGSPEC_PATTERN1_WIDTH                                               32
#define REGSPEC_PATTERN1_SHIFT                                                0
#define REGSPEC_PATTERN1_MASK                                        0xffffffff
#define REGSPEC_PATTERN1_RD(src)                         (((src) & 0xffffffff))
#define REGSPEC_PATTERN1_WR(src)                    (((u32)(src)) & 0xffffffff)
#define REGSPEC_PATTERN1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_PAT_MASK_REG_1	*/
/*	 Fields PAT_MASK	 */
#define REGSPEC_PAT_MASK1_WIDTH                                              32
#define REGSPEC_PAT_MASK1_SHIFT                                               0
#define REGSPEC_PAT_MASK1_MASK                                       0xffffffff
#define REGSPEC_PAT_MASK1_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_PAT_MASK1_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_PAT_MASK1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_TRIG_OUT	*/
/*	 Fields DBG_OUT	 */
#define REGSPEC_DBG_OUT_WIDTH                                                32
#define REGSPEC_DBG_OUT_SHIFT                                                 0
#define REGSPEC_DBG_OUT_MASK                                         0xffffffff
#define REGSPEC_DBG_OUT_RD(src)                          (((src) & 0xffffffff))
#define REGSPEC_DBG_OUT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_TRIG_INT	*/
/*	 Fields DBG_INT	 */
#define REGSPEC_DBG_INT_WIDTH                                                 1
#define REGSPEC_DBG_INT_SHIFT                                                 0
#define REGSPEC_DBG_INT_MASK                                         0x00000001
#define REGSPEC_DBG_INT_RD(src)                          (((src) & 0x00000001))
#define REGSPEC_DBG_INT_WR(src)                     (((u32)(src)) & 0x00000001)
#define REGSPEC_DBG_INT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register DBG_TRIG_INTMask	*/
/*    Mask Register Fields DBG_INTMask    */
#define REGSPEC_DBG_INTMASK_WIDTH                                             1
#define REGSPEC_DBG_INTMASK_SHIFT                                             0
#define REGSPEC_DBG_INTMASK_MASK                                     0x00000001
#define REGSPEC_DBG_INTMASK_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_DBG_INTMASK_WR(src)                 (((u32)(src)) & 0x00000001)
#define REGSPEC_DBG_INTMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_MEM_ECC_BYPASS	*/
/*	 Fields CFG_ECC_BYPASS	 */
#define REGSPEC_CFG_ECC_BYPASS_WIDTH                                         16
#define REGSPEC_CFG_ECC_BYPASS_SHIFT                                          0
#define REGSPEC_CFG_ECC_BYPASS_MASK                                  0x0000ffff
#define REGSPEC_CFG_ECC_BYPASS_RD(src)                   (((src) & 0x0000ffff))
#define REGSPEC_CFG_ECC_BYPASS_WR(src)              (((u32)(src)) & 0x0000ffff)
#define REGSPEC_CFG_ECC_BYPASS_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_MEM_PWRDN_DIS	*/
/*	 Fields CFG_ECC_PWRDN_DIS	 */
#define REGSPEC_CFG_ECC_PWRDN_DIS_WIDTH                                      16
#define REGSPEC_CFG_ECC_PWRDN_DIS_SHIFT                                      16
#define REGSPEC_CFG_ECC_PWRDN_DIS_MASK                               0xffff0000
#define REGSPEC_CFG_ECC_PWRDN_DIS_RD(src)            (((src) & 0xffff0000)>>16)
#define REGSPEC_CFG_ECC_PWRDN_DIS_WR(src)       (((u32)(src)<<16) & 0xffff0000)
#define REGSPEC_CFG_ECC_PWRDN_DIS_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields CFG_PWRDN_DIS	 */
#define REGSPEC_CFG_PWRDN_DIS_WIDTH                                          16
#define REGSPEC_CFG_PWRDN_DIS_SHIFT                                           0
#define REGSPEC_CFG_PWRDN_DIS_MASK                                   0x0000ffff
#define REGSPEC_CFG_PWRDN_DIS_RD(src)                    (((src) & 0x0000ffff))
#define REGSPEC_CFG_PWRDN_DIS_WR(src)               (((u32)(src)) & 0x0000ffff)
#define REGSPEC_CFG_PWRDN_DIS_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_MEM_RAM_SHUTDOWN	*/
/*	 Fields CFG_RAM_SHUTDOWN_EN	 */
#define REGSPEC_CFG_RAM_SHUTDOWN_EN_WIDTH                                    32
#define REGSPEC_CFG_RAM_SHUTDOWN_EN_SHIFT                                     0
#define REGSPEC_CFG_RAM_SHUTDOWN_EN_MASK                             0xffffffff
#define REGSPEC_CFG_RAM_SHUTDOWN_EN_RD(src)              (((src) & 0xffffffff))
#define REGSPEC_CFG_RAM_SHUTDOWN_EN_WR(src)         (((u32)(src)) & 0xffffffff)
#define REGSPEC_CFG_RAM_SHUTDOWN_EN_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register BLOCK_MEM_RDY	*/
/*	 Fields MEM_RDY	 */
#define REGSPEC_MEM_RDY_WIDTH                                                32
#define REGSPEC_MEM_RDY_SHIFT                                                 0
#define REGSPEC_MEM_RDY_MASK                                         0xffffffff
#define REGSPEC_MEM_RDY_RD(src)                          (((src) & 0xffffffff))
#define REGSPEC_MEM_RDY_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_READ_LATENCY_TOT_READ_REQS	*/
/*	 Fields TOT_READS	 */
#define REGSPEC_TOT_READS_WIDTH                                              16
#define REGSPEC_TOT_READS_SHIFT                                              16
#define REGSPEC_TOT_READS_MASK                                       0xffff0000
#define REGSPEC_TOT_READS_RD(src)                    (((src) & 0xffff0000)>>16)
#define REGSPEC_TOT_READS_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))

/*	Global Base Address	*/
#define GLBL_ERR_CSR_BASE_ADDR			0x01701d000ULL

/*    Address GLBL_ERR_CSR  Registers */
#define GLBL_ERR_STS_ADDR                                            0x00000800
#define GLBL_ERR_STS_DEFAULT                                         0x00000000
#define GLBL_SEC_ERRL_ADDR                                           0x00000810
#define GLBL_SEC_ERRL_DEFAULT                                        0x00000000
#define GLBL_SEC_ERRLMASK_ADDR                                       0x00000814
#define GLBL_SEC_ERRH_ADDR                                           0x00000818
#define GLBL_SEC_ERRH_DEFAULT                                        0x00000000
#define GLBL_SEC_ERRHMASK_ADDR                                       0x0000081c
#define GLBL_MSEC_ERRL_ADDR                                          0x00000820
#define GLBL_MSEC_ERRL_DEFAULT                                       0x00000000
#define GLBL_MSEC_ERRLMASK_ADDR                                      0x00000824
#define GLBL_MSEC_ERRH_ADDR                                          0x00000828
#define GLBL_MSEC_ERRH_DEFAULT                                       0x00000000
#define GLBL_MSEC_ERRHMASK_ADDR                                      0x0000082c
#define GLBL_DED_ERRL_ADDR                                           0x00000830
#define GLBL_DED_ERRL_DEFAULT                                        0x00000000
#define GLBL_DED_ERRLMASK_ADDR                                       0x00000834
#define GLBL_DED_ERRH_ADDR                                           0x00000838
#define GLBL_DED_ERRH_DEFAULT                                        0x00000000
#define GLBL_DED_ERRHMASK_ADDR                                       0x0000083c
#define GLBL_MDED_ERRL_ADDR                                          0x00000840
#define GLBL_MDED_ERRL_DEFAULT                                       0x00000000
#define GLBL_MDED_ERRLMASK_ADDR                                      0x00000844
#define GLBL_MDED_ERRH_ADDR                                          0x00000848
#define GLBL_MDED_ERRH_DEFAULT                                       0x00000000
#define GLBL_MDED_ERRHMASK_ADDR                                      0x0000084c
#define GLBL_MERR_ADDR_ADDR                                          0x00000850
#define GLBL_MERR_ADDR_DEFAULT                                       0x00000000
#define GLBL_MERR_REQINFO_ADDR                                       0x00000854
#define GLBL_MERR_REQINFO_DEFAULT                                    0x00000000
#define GLBL_TRANS_ERR_ADDR                                          0x00000860
#define GLBL_TRANS_ERR_DEFAULT                                       0x00000000
#define GLBL_TRANS_ERRMASK_ADDR                                      0x00000864
#define GLBL_WDERR_ADDR_ADDR                                         0x00000870
#define GLBL_WDERR_ADDR_DEFAULT                                      0x00000000
#define GLBL_WDERR_REQINFO_ADDR                                      0x00000874
#define GLBL_WDERR_REQINFO_DEFAULT                                   0x00000000
#define GLBL_DEVERR_ADDR_ADDR                                        0x00000878
#define GLBL_DEVERR_ADDR_DEFAULT                                     0x00000000
#define GLBL_DEVERR_REQINFO_ADDR                                     0x0000087c
#define GLBL_DEVERR_REQINFO_DEFAULT                                  0x00000000
#define GLBL_SEC_ERRL_ALS_ADDR                                       0x00000880
#define GLBL_SEC_ERRL_ALS_DEFAULT                                    0x00000000
#define GLBL_SEC_ERRH_ALS_ADDR                                       0x00000884
#define GLBL_SEC_ERRH_ALS_DEFAULT                                    0x00000000
#define GLBL_DED_ERRL_ALS_ADDR                                       0x00000888
#define GLBL_DED_ERRL_ALS_DEFAULT                                    0x00000000
#define GLBL_DED_ERRH_ALS_ADDR                                       0x0000088c
#define GLBL_DED_ERRH_ALS_DEFAULT                                    0x00000000
#define GLBL_TRANS_ERR_ALS_ADDR                                      0x00000890
#define GLBL_TRANS_ERR_ALS_DEFAULT                                   0x00000000

/*	Register GLBL_ERR_STS	*/
/*	 Fields SHIM_ERR	 */
#define SHIM_ERR_WIDTH                                                        1
#define SHIM_ERR_SHIFT                                                        5
#define SHIM_ERR_MASK                                                0x00000020
#define SHIM_ERR_RD(src)                              (((src) & 0x00000020)>>5)
#define SHIM_ERR_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields TRANS_ERR	 */
#define TRANS_ERR_WIDTH                                                       1
#define TRANS_ERR_SHIFT                                                       4
#define TRANS_ERR_MASK                                               0x00000010
#define TRANS_ERR_RD(src)                             (((src) & 0x00000010)>>4)
#define TRANS_ERR_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MDED_ERR	 */
#define MDED_ERR_WIDTH                                                        1
#define MDED_ERR_SHIFT                                                        3
#define MDED_ERR_MASK                                                0x00000008
#define MDED_ERR_RD(src)                              (((src) & 0x00000008)>>3)
#define MDED_ERR_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DED_ERR	 */
#define DED_ERR_WIDTH                                                         1
#define DED_ERR_SHIFT                                                         2
#define DED_ERR_MASK                                                 0x00000004
#define DED_ERR_RD(src)                               (((src) & 0x00000004)>>2)
#define DED_ERR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSEC_ERR	 */
#define MSEC_ERR_WIDTH                                                        1
#define MSEC_ERR_SHIFT                                                        1
#define MSEC_ERR_MASK                                                0x00000002
#define MSEC_ERR_RD(src)                              (((src) & 0x00000002)>>1)
#define MSEC_ERR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SEC_ERR	 */
#define SEC_ERR_WIDTH                                                         1
#define SEC_ERR_SHIFT                                                         0
#define SEC_ERR_MASK                                                 0x00000001
#define SEC_ERR_RD(src)                                  (((src) & 0x00000001))
#define SEC_ERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRL	*/
/*	 Fields SEC31	 */
#define SEC31_WIDTH                                                           1
#define SEC31_SHIFT                                                          31
#define SEC31_MASK                                                   0x80000000
#define SEC31_RD(src)                                (((src) & 0x80000000)>>31)
#define SEC31_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define SEC31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SEC30	 */
#define SEC30_WIDTH                                                           1
#define SEC30_SHIFT                                                          30
#define SEC30_MASK                                                   0x40000000
#define SEC30_RD(src)                                (((src) & 0x40000000)>>30)
#define SEC30_WR(src)                           (((u32)(src)<<30) & 0x40000000)
#define SEC30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields SEC29	 */
#define SEC29_WIDTH                                                           1
#define SEC29_SHIFT                                                          29
#define SEC29_MASK                                                   0x20000000
#define SEC29_RD(src)                                (((src) & 0x20000000)>>29)
#define SEC29_WR(src)                           (((u32)(src)<<29) & 0x20000000)
#define SEC29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields SEC28	 */
#define SEC28_WIDTH                                                           1
#define SEC28_SHIFT                                                          28
#define SEC28_MASK                                                   0x10000000
#define SEC28_RD(src)                                (((src) & 0x10000000)>>28)
#define SEC28_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define SEC28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SEC27	 */
#define SEC27_WIDTH                                                           1
#define SEC27_SHIFT                                                          27
#define SEC27_MASK                                                   0x08000000
#define SEC27_RD(src)                                (((src) & 0x08000000)>>27)
#define SEC27_WR(src)                           (((u32)(src)<<27) & 0x08000000)
#define SEC27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields SEC26	 */
#define SEC26_WIDTH                                                           1
#define SEC26_SHIFT                                                          26
#define SEC26_MASK                                                   0x04000000
#define SEC26_RD(src)                                (((src) & 0x04000000)>>26)
#define SEC26_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define SEC26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SEC25	 */
#define SEC25_WIDTH                                                           1
#define SEC25_SHIFT                                                          25
#define SEC25_MASK                                                   0x02000000
#define SEC25_RD(src)                                (((src) & 0x02000000)>>25)
#define SEC25_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define SEC25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SEC24	 */
#define SEC24_WIDTH                                                           1
#define SEC24_SHIFT                                                          24
#define SEC24_MASK                                                   0x01000000
#define SEC24_RD(src)                                (((src) & 0x01000000)>>24)
#define SEC24_WR(src)                           (((u32)(src)<<24) & 0x01000000)
#define SEC24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields SEC23	 */
#define SEC23_WIDTH                                                           1
#define SEC23_SHIFT                                                          23
#define SEC23_MASK                                                   0x00800000
#define SEC23_RD(src)                                (((src) & 0x00800000)>>23)
#define SEC23_WR(src)                           (((u32)(src)<<23) & 0x00800000)
#define SEC23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields SEC22	 */
#define SEC22_WIDTH                                                           1
#define SEC22_SHIFT                                                          22
#define SEC22_MASK                                                   0x00400000
#define SEC22_RD(src)                                (((src) & 0x00400000)>>22)
#define SEC22_WR(src)                           (((u32)(src)<<22) & 0x00400000)
#define SEC22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields SEC21	 */
#define SEC21_WIDTH                                                           1
#define SEC21_SHIFT                                                          21
#define SEC21_MASK                                                   0x00200000
#define SEC21_RD(src)                                (((src) & 0x00200000)>>21)
#define SEC21_WR(src)                           (((u32)(src)<<21) & 0x00200000)
#define SEC21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields SEC20	 */
#define SEC20_WIDTH                                                           1
#define SEC20_SHIFT                                                          20
#define SEC20_MASK                                                   0x00100000
#define SEC20_RD(src)                                (((src) & 0x00100000)>>20)
#define SEC20_WR(src)                           (((u32)(src)<<20) & 0x00100000)
#define SEC20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields SEC19	 */
#define SEC19_WIDTH                                                           1
#define SEC19_SHIFT                                                          19
#define SEC19_MASK                                                   0x00080000
#define SEC19_RD(src)                                (((src) & 0x00080000)>>19)
#define SEC19_WR(src)                           (((u32)(src)<<19) & 0x00080000)
#define SEC19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC18	 */
#define SEC18_WIDTH                                                           1
#define SEC18_SHIFT                                                          18
#define SEC18_MASK                                                   0x00040000
#define SEC18_RD(src)                                (((src) & 0x00040000)>>18)
#define SEC18_WR(src)                           (((u32)(src)<<18) & 0x00040000)
#define SEC18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields SEC17	 */
#define SEC17_WIDTH                                                           1
#define SEC17_SHIFT                                                          17
#define SEC17_MASK                                                   0x00020000
#define SEC17_RD(src)                                (((src) & 0x00020000)>>17)
#define SEC17_WR(src)                           (((u32)(src)<<17) & 0x00020000)
#define SEC17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields SEC16	 */
#define SEC16_WIDTH                                                           1
#define SEC16_SHIFT                                                          16
#define SEC16_MASK                                                   0x00010000
#define SEC16_RD(src)                                (((src) & 0x00010000)>>16)
#define SEC16_WR(src)                           (((u32)(src)<<16) & 0x00010000)
#define SEC16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields SEC15	 */
#define SEC15_WIDTH                                                           1
#define SEC15_SHIFT                                                          15
#define SEC15_MASK                                                   0x00008000
#define SEC15_RD(src)                                (((src) & 0x00008000)>>15)
#define SEC15_WR(src)                           (((u32)(src)<<15) & 0x00008000)
#define SEC15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields SEC14	 */
#define SEC14_WIDTH                                                           1
#define SEC14_SHIFT                                                          14
#define SEC14_MASK                                                   0x00004000
#define SEC14_RD(src)                                (((src) & 0x00004000)>>14)
#define SEC14_WR(src)                           (((u32)(src)<<14) & 0x00004000)
#define SEC14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields SEC13	 */
#define SEC13_WIDTH                                                           1
#define SEC13_SHIFT                                                          13
#define SEC13_MASK                                                   0x00002000
#define SEC13_RD(src)                                (((src) & 0x00002000)>>13)
#define SEC13_WR(src)                           (((u32)(src)<<13) & 0x00002000)
#define SEC13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields SEC12	 */
#define SEC12_WIDTH                                                           1
#define SEC12_SHIFT                                                          12
#define SEC12_MASK                                                   0x00001000
#define SEC12_RD(src)                                (((src) & 0x00001000)>>12)
#define SEC12_WR(src)                           (((u32)(src)<<12) & 0x00001000)
#define SEC12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SEC11	 */
#define SEC11_WIDTH                                                           1
#define SEC11_SHIFT                                                          11
#define SEC11_MASK                                                   0x00000800
#define SEC11_RD(src)                                (((src) & 0x00000800)>>11)
#define SEC11_WR(src)                           (((u32)(src)<<11) & 0x00000800)
#define SEC11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SEC10	 */
#define SEC10_WIDTH                                                           1
#define SEC10_SHIFT                                                          10
#define SEC10_MASK                                                   0x00000400
#define SEC10_RD(src)                                (((src) & 0x00000400)>>10)
#define SEC10_WR(src)                           (((u32)(src)<<10) & 0x00000400)
#define SEC10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SEC9	 */
#define SEC9_WIDTH                                                            1
#define SEC9_SHIFT                                                            9
#define SEC9_MASK                                                    0x00000200
#define SEC9_RD(src)                                  (((src) & 0x00000200)>>9)
#define SEC9_WR(src)                             (((u32)(src)<<9) & 0x00000200)
#define SEC9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SEC8	 */
#define SEC8_WIDTH                                                            1
#define SEC8_SHIFT                                                            8
#define SEC8_MASK                                                    0x00000100
#define SEC8_RD(src)                                  (((src) & 0x00000100)>>8)
#define SEC8_WR(src)                             (((u32)(src)<<8) & 0x00000100)
#define SEC8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SEC7	 */
#define SEC7_WIDTH                                                            1
#define SEC7_SHIFT                                                            7
#define SEC7_MASK                                                    0x00000080
#define SEC7_RD(src)                                  (((src) & 0x00000080)>>7)
#define SEC7_WR(src)                             (((u32)(src)<<7) & 0x00000080)
#define SEC7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SEC6	 */
#define SEC6_WIDTH                                                            1
#define SEC6_SHIFT                                                            6
#define SEC6_MASK                                                    0x00000040
#define SEC6_RD(src)                                  (((src) & 0x00000040)>>6)
#define SEC6_WR(src)                             (((u32)(src)<<6) & 0x00000040)
#define SEC6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields SEC5	 */
#define SEC5_WIDTH                                                            1
#define SEC5_SHIFT                                                            5
#define SEC5_MASK                                                    0x00000020
#define SEC5_RD(src)                                  (((src) & 0x00000020)>>5)
#define SEC5_WR(src)                             (((u32)(src)<<5) & 0x00000020)
#define SEC5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields SEC4	 */
#define SEC4_WIDTH                                                            1
#define SEC4_SHIFT                                                            4
#define SEC4_MASK                                                    0x00000010
#define SEC4_RD(src)                                  (((src) & 0x00000010)>>4)
#define SEC4_WR(src)                             (((u32)(src)<<4) & 0x00000010)
#define SEC4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields SEC3	 */
#define SEC3_WIDTH                                                            1
#define SEC3_SHIFT                                                            3
#define SEC3_MASK                                                    0x00000008
#define SEC3_RD(src)                                  (((src) & 0x00000008)>>3)
#define SEC3_WR(src)                             (((u32)(src)<<3) & 0x00000008)
#define SEC3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SEC2	 */
#define SEC2_WIDTH                                                            1
#define SEC2_SHIFT                                                            2
#define SEC2_MASK                                                    0x00000004
#define SEC2_RD(src)                                  (((src) & 0x00000004)>>2)
#define SEC2_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define SEC2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SEC1	 */
#define SEC1_WIDTH                                                            1
#define SEC1_SHIFT                                                            1
#define SEC1_MASK                                                    0x00000002
#define SEC1_RD(src)                                  (((src) & 0x00000002)>>1)
#define SEC1_WR(src)                             (((u32)(src)<<1) & 0x00000002)
#define SEC1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SEC0	 */
#define SEC0_WIDTH                                                            1
#define SEC0_SHIFT                                                            0
#define SEC0_MASK                                                    0x00000001
#define SEC0_RD(src)                                     (((src) & 0x00000001))
#define SEC0_WR(src)                                (((u32)(src)) & 0x00000001)
#define SEC0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRLMask	*/
/*    Mask Register Fields SEC31Mask    */
#define SEC31MASK_WIDTH                                                       1
#define SEC31MASK_SHIFT                                                      31
#define SEC31MASK_MASK                                               0x80000000
#define SEC31MASK_RD(src)                            (((src) & 0x80000000)>>31)
#define SEC31MASK_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define SEC31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields SEC30Mask    */
#define SEC30MASK_WIDTH                                                       1
#define SEC30MASK_SHIFT                                                      30
#define SEC30MASK_MASK                                               0x40000000
#define SEC30MASK_RD(src)                            (((src) & 0x40000000)>>30)
#define SEC30MASK_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define SEC30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields SEC29Mask    */
#define SEC29MASK_WIDTH                                                       1
#define SEC29MASK_SHIFT                                                      29
#define SEC29MASK_MASK                                               0x20000000
#define SEC29MASK_RD(src)                            (((src) & 0x20000000)>>29)
#define SEC29MASK_WR(src)                       (((u32)(src)<<29) & 0x20000000)
#define SEC29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields SEC28Mask    */
#define SEC28MASK_WIDTH                                                       1
#define SEC28MASK_SHIFT                                                      28
#define SEC28MASK_MASK                                               0x10000000
#define SEC28MASK_RD(src)                            (((src) & 0x10000000)>>28)
#define SEC28MASK_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define SEC28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields SEC27Mask    */
#define SEC27MASK_WIDTH                                                       1
#define SEC27MASK_SHIFT                                                      27
#define SEC27MASK_MASK                                               0x08000000
#define SEC27MASK_RD(src)                            (((src) & 0x08000000)>>27)
#define SEC27MASK_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define SEC27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields SEC26Mask    */
#define SEC26MASK_WIDTH                                                       1
#define SEC26MASK_SHIFT                                                      26
#define SEC26MASK_MASK                                               0x04000000
#define SEC26MASK_RD(src)                            (((src) & 0x04000000)>>26)
#define SEC26MASK_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define SEC26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields SEC25Mask    */
#define SEC25MASK_WIDTH                                                       1
#define SEC25MASK_SHIFT                                                      25
#define SEC25MASK_MASK                                               0x02000000
#define SEC25MASK_RD(src)                            (((src) & 0x02000000)>>25)
#define SEC25MASK_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define SEC25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields SEC24Mask    */
#define SEC24MASK_WIDTH                                                       1
#define SEC24MASK_SHIFT                                                      24
#define SEC24MASK_MASK                                               0x01000000
#define SEC24MASK_RD(src)                            (((src) & 0x01000000)>>24)
#define SEC24MASK_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define SEC24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields SEC23Mask    */
#define SEC23MASK_WIDTH                                                       1
#define SEC23MASK_SHIFT                                                      23
#define SEC23MASK_MASK                                               0x00800000
#define SEC23MASK_RD(src)                            (((src) & 0x00800000)>>23)
#define SEC23MASK_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define SEC23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields SEC22Mask    */
#define SEC22MASK_WIDTH                                                       1
#define SEC22MASK_SHIFT                                                      22
#define SEC22MASK_MASK                                               0x00400000
#define SEC22MASK_RD(src)                            (((src) & 0x00400000)>>22)
#define SEC22MASK_WR(src)                       (((u32)(src)<<22) & 0x00400000)
#define SEC22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields SEC21Mask    */
#define SEC21MASK_WIDTH                                                       1
#define SEC21MASK_SHIFT                                                      21
#define SEC21MASK_MASK                                               0x00200000
#define SEC21MASK_RD(src)                            (((src) & 0x00200000)>>21)
#define SEC21MASK_WR(src)                       (((u32)(src)<<21) & 0x00200000)
#define SEC21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields SEC20Mask    */
#define SEC20MASK_WIDTH                                                       1
#define SEC20MASK_SHIFT                                                      20
#define SEC20MASK_MASK                                               0x00100000
#define SEC20MASK_RD(src)                            (((src) & 0x00100000)>>20)
#define SEC20MASK_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define SEC20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields SEC19Mask    */
#define SEC19MASK_WIDTH                                                       1
#define SEC19MASK_SHIFT                                                      19
#define SEC19MASK_MASK                                               0x00080000
#define SEC19MASK_RD(src)                            (((src) & 0x00080000)>>19)
#define SEC19MASK_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define SEC19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields SEC18Mask    */
#define SEC18MASK_WIDTH                                                       1
#define SEC18MASK_SHIFT                                                      18
#define SEC18MASK_MASK                                               0x00040000
#define SEC18MASK_RD(src)                            (((src) & 0x00040000)>>18)
#define SEC18MASK_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define SEC18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields SEC17Mask    */
#define SEC17MASK_WIDTH                                                       1
#define SEC17MASK_SHIFT                                                      17
#define SEC17MASK_MASK                                               0x00020000
#define SEC17MASK_RD(src)                            (((src) & 0x00020000)>>17)
#define SEC17MASK_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define SEC17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields SEC16Mask    */
#define SEC16MASK_WIDTH                                                       1
#define SEC16MASK_SHIFT                                                      16
#define SEC16MASK_MASK                                               0x00010000
#define SEC16MASK_RD(src)                            (((src) & 0x00010000)>>16)
#define SEC16MASK_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define SEC16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields SEC15Mask    */
#define SEC15MASK_WIDTH                                                       1
#define SEC15MASK_SHIFT                                                      15
#define SEC15MASK_MASK                                               0x00008000
#define SEC15MASK_RD(src)                            (((src) & 0x00008000)>>15)
#define SEC15MASK_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define SEC15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields SEC14Mask    */
#define SEC14MASK_WIDTH                                                       1
#define SEC14MASK_SHIFT                                                      14
#define SEC14MASK_MASK                                               0x00004000
#define SEC14MASK_RD(src)                            (((src) & 0x00004000)>>14)
#define SEC14MASK_WR(src)                       (((u32)(src)<<14) & 0x00004000)
#define SEC14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields SEC13Mask    */
#define SEC13MASK_WIDTH                                                       1
#define SEC13MASK_SHIFT                                                      13
#define SEC13MASK_MASK                                               0x00002000
#define SEC13MASK_RD(src)                            (((src) & 0x00002000)>>13)
#define SEC13MASK_WR(src)                       (((u32)(src)<<13) & 0x00002000)
#define SEC13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields SEC12Mask    */
#define SEC12MASK_WIDTH                                                       1
#define SEC12MASK_SHIFT                                                      12
#define SEC12MASK_MASK                                               0x00001000
#define SEC12MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define SEC12MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define SEC12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SEC11Mask    */
#define SEC11MASK_WIDTH                                                       1
#define SEC11MASK_SHIFT                                                      11
#define SEC11MASK_MASK                                               0x00000800
#define SEC11MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define SEC11MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define SEC11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SEC10Mask    */
#define SEC10MASK_WIDTH                                                       1
#define SEC10MASK_SHIFT                                                      10
#define SEC10MASK_MASK                                               0x00000400
#define SEC10MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define SEC10MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define SEC10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SEC9Mask    */
#define SEC9MASK_WIDTH                                                        1
#define SEC9MASK_SHIFT                                                        9
#define SEC9MASK_MASK                                                0x00000200
#define SEC9MASK_RD(src)                              (((src) & 0x00000200)>>9)
#define SEC9MASK_WR(src)                         (((u32)(src)<<9) & 0x00000200)
#define SEC9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields SEC8Mask    */
#define SEC8MASK_WIDTH                                                        1
#define SEC8MASK_SHIFT                                                        8
#define SEC8MASK_MASK                                                0x00000100
#define SEC8MASK_RD(src)                              (((src) & 0x00000100)>>8)
#define SEC8MASK_WR(src)                         (((u32)(src)<<8) & 0x00000100)
#define SEC8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields SEC7Mask    */
#define SEC7MASK_WIDTH                                                        1
#define SEC7MASK_SHIFT                                                        7
#define SEC7MASK_MASK                                                0x00000080
#define SEC7MASK_RD(src)                              (((src) & 0x00000080)>>7)
#define SEC7MASK_WR(src)                         (((u32)(src)<<7) & 0x00000080)
#define SEC7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields SEC6Mask    */
#define SEC6MASK_WIDTH                                                        1
#define SEC6MASK_SHIFT                                                        6
#define SEC6MASK_MASK                                                0x00000040
#define SEC6MASK_RD(src)                              (((src) & 0x00000040)>>6)
#define SEC6MASK_WR(src)                         (((u32)(src)<<6) & 0x00000040)
#define SEC6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields SEC5Mask    */
#define SEC5MASK_WIDTH                                                        1
#define SEC5MASK_SHIFT                                                        5
#define SEC5MASK_MASK                                                0x00000020
#define SEC5MASK_RD(src)                              (((src) & 0x00000020)>>5)
#define SEC5MASK_WR(src)                         (((u32)(src)<<5) & 0x00000020)
#define SEC5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields SEC4Mask    */
#define SEC4MASK_WIDTH                                                        1
#define SEC4MASK_SHIFT                                                        4
#define SEC4MASK_MASK                                                0x00000010
#define SEC4MASK_RD(src)                              (((src) & 0x00000010)>>4)
#define SEC4MASK_WR(src)                         (((u32)(src)<<4) & 0x00000010)
#define SEC4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields SEC3Mask    */
#define SEC3MASK_WIDTH                                                        1
#define SEC3MASK_SHIFT                                                        3
#define SEC3MASK_MASK                                                0x00000008
#define SEC3MASK_RD(src)                              (((src) & 0x00000008)>>3)
#define SEC3MASK_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define SEC3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields SEC2Mask    */
#define SEC2MASK_WIDTH                                                        1
#define SEC2MASK_SHIFT                                                        2
#define SEC2MASK_MASK                                                0x00000004
#define SEC2MASK_RD(src)                              (((src) & 0x00000004)>>2)
#define SEC2MASK_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define SEC2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields SEC1Mask    */
#define SEC1MASK_WIDTH                                                        1
#define SEC1MASK_SHIFT                                                        1
#define SEC1MASK_MASK                                                0x00000002
#define SEC1MASK_RD(src)                              (((src) & 0x00000002)>>1)
#define SEC1MASK_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define SEC1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SEC0Mask    */
#define SEC0MASK_WIDTH                                                        1
#define SEC0MASK_SHIFT                                                        0
#define SEC0MASK_MASK                                                0x00000001
#define SEC0MASK_RD(src)                                 (((src) & 0x00000001))
#define SEC0MASK_WR(src)                            (((u32)(src)) & 0x00000001)
#define SEC0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRH	*/
/*	 Fields SEC31	 */
#define SEC31_F1_WIDTH                                                        1
#define SEC31_F1_SHIFT                                                       31
#define SEC31_F1_MASK                                                0x80000000
#define SEC31_F1_RD(src)                             (((src) & 0x80000000)>>31)
#define SEC31_F1_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define SEC31_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SEC30	 */
#define SEC30_F1_WIDTH                                                        1
#define SEC30_F1_SHIFT                                                       30
#define SEC30_F1_MASK                                                0x40000000
#define SEC30_F1_RD(src)                             (((src) & 0x40000000)>>30)
#define SEC30_F1_WR(src)                        (((u32)(src)<<30) & 0x40000000)
#define SEC30_F1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields SEC29	 */
#define SEC29_F1_WIDTH                                                        1
#define SEC29_F1_SHIFT                                                       29
#define SEC29_F1_MASK                                                0x20000000
#define SEC29_F1_RD(src)                             (((src) & 0x20000000)>>29)
#define SEC29_F1_WR(src)                        (((u32)(src)<<29) & 0x20000000)
#define SEC29_F1_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields SEC28	 */
#define SEC28_F1_WIDTH                                                        1
#define SEC28_F1_SHIFT                                                       28
#define SEC28_F1_MASK                                                0x10000000
#define SEC28_F1_RD(src)                             (((src) & 0x10000000)>>28)
#define SEC28_F1_WR(src)                        (((u32)(src)<<28) & 0x10000000)
#define SEC28_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SEC27	 */
#define SEC27_F1_WIDTH                                                        1
#define SEC27_F1_SHIFT                                                       27
#define SEC27_F1_MASK                                                0x08000000
#define SEC27_F1_RD(src)                             (((src) & 0x08000000)>>27)
#define SEC27_F1_WR(src)                        (((u32)(src)<<27) & 0x08000000)
#define SEC27_F1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields SEC26	 */
#define SEC26_F1_WIDTH                                                        1
#define SEC26_F1_SHIFT                                                       26
#define SEC26_F1_MASK                                                0x04000000
#define SEC26_F1_RD(src)                             (((src) & 0x04000000)>>26)
#define SEC26_F1_WR(src)                        (((u32)(src)<<26) & 0x04000000)
#define SEC26_F1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SEC25	 */
#define SEC25_F1_WIDTH                                                        1
#define SEC25_F1_SHIFT                                                       25
#define SEC25_F1_MASK                                                0x02000000
#define SEC25_F1_RD(src)                             (((src) & 0x02000000)>>25)
#define SEC25_F1_WR(src)                        (((u32)(src)<<25) & 0x02000000)
#define SEC25_F1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SEC24	 */
#define SEC24_F1_WIDTH                                                        1
#define SEC24_F1_SHIFT                                                       24
#define SEC24_F1_MASK                                                0x01000000
#define SEC24_F1_RD(src)                             (((src) & 0x01000000)>>24)
#define SEC24_F1_WR(src)                        (((u32)(src)<<24) & 0x01000000)
#define SEC24_F1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields SEC23	 */
#define SEC23_F1_WIDTH                                                        1
#define SEC23_F1_SHIFT                                                       23
#define SEC23_F1_MASK                                                0x00800000
#define SEC23_F1_RD(src)                             (((src) & 0x00800000)>>23)
#define SEC23_F1_WR(src)                        (((u32)(src)<<23) & 0x00800000)
#define SEC23_F1_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields SEC22	 */
#define SEC22_F1_WIDTH                                                        1
#define SEC22_F1_SHIFT                                                       22
#define SEC22_F1_MASK                                                0x00400000
#define SEC22_F1_RD(src)                             (((src) & 0x00400000)>>22)
#define SEC22_F1_WR(src)                        (((u32)(src)<<22) & 0x00400000)
#define SEC22_F1_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields SEC21	 */
#define SEC21_F1_WIDTH                                                        1
#define SEC21_F1_SHIFT                                                       21
#define SEC21_F1_MASK                                                0x00200000
#define SEC21_F1_RD(src)                             (((src) & 0x00200000)>>21)
#define SEC21_F1_WR(src)                        (((u32)(src)<<21) & 0x00200000)
#define SEC21_F1_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields SEC20	 */
#define SEC20_F1_WIDTH                                                        1
#define SEC20_F1_SHIFT                                                       20
#define SEC20_F1_MASK                                                0x00100000
#define SEC20_F1_RD(src)                             (((src) & 0x00100000)>>20)
#define SEC20_F1_WR(src)                        (((u32)(src)<<20) & 0x00100000)
#define SEC20_F1_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields SEC19	 */
#define SEC19_F1_WIDTH                                                        1
#define SEC19_F1_SHIFT                                                       19
#define SEC19_F1_MASK                                                0x00080000
#define SEC19_F1_RD(src)                             (((src) & 0x00080000)>>19)
#define SEC19_F1_WR(src)                        (((u32)(src)<<19) & 0x00080000)
#define SEC19_F1_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC18	 */
#define SEC18_F1_WIDTH                                                        1
#define SEC18_F1_SHIFT                                                       18
#define SEC18_F1_MASK                                                0x00040000
#define SEC18_F1_RD(src)                             (((src) & 0x00040000)>>18)
#define SEC18_F1_WR(src)                        (((u32)(src)<<18) & 0x00040000)
#define SEC18_F1_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields SEC17	 */
#define SEC17_F1_WIDTH                                                        1
#define SEC17_F1_SHIFT                                                       17
#define SEC17_F1_MASK                                                0x00020000
#define SEC17_F1_RD(src)                             (((src) & 0x00020000)>>17)
#define SEC17_F1_WR(src)                        (((u32)(src)<<17) & 0x00020000)
#define SEC17_F1_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields SEC16	 */
#define SEC16_F1_WIDTH                                                        1
#define SEC16_F1_SHIFT                                                       16
#define SEC16_F1_MASK                                                0x00010000
#define SEC16_F1_RD(src)                             (((src) & 0x00010000)>>16)
#define SEC16_F1_WR(src)                        (((u32)(src)<<16) & 0x00010000)
#define SEC16_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields SEC15	 */
#define SEC15_F1_WIDTH                                                        1
#define SEC15_F1_SHIFT                                                       15
#define SEC15_F1_MASK                                                0x00008000
#define SEC15_F1_RD(src)                             (((src) & 0x00008000)>>15)
#define SEC15_F1_WR(src)                        (((u32)(src)<<15) & 0x00008000)
#define SEC15_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields SEC14	 */
#define SEC14_F1_WIDTH                                                        1
#define SEC14_F1_SHIFT                                                       14
#define SEC14_F1_MASK                                                0x00004000
#define SEC14_F1_RD(src)                             (((src) & 0x00004000)>>14)
#define SEC14_F1_WR(src)                        (((u32)(src)<<14) & 0x00004000)
#define SEC14_F1_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields SEC13	 */
#define SEC13_F1_WIDTH                                                        1
#define SEC13_F1_SHIFT                                                       13
#define SEC13_F1_MASK                                                0x00002000
#define SEC13_F1_RD(src)                             (((src) & 0x00002000)>>13)
#define SEC13_F1_WR(src)                        (((u32)(src)<<13) & 0x00002000)
#define SEC13_F1_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields SEC12	 */
#define SEC12_F1_WIDTH                                                        1
#define SEC12_F1_SHIFT                                                       12
#define SEC12_F1_MASK                                                0x00001000
#define SEC12_F1_RD(src)                             (((src) & 0x00001000)>>12)
#define SEC12_F1_WR(src)                        (((u32)(src)<<12) & 0x00001000)
#define SEC12_F1_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SEC11	 */
#define SEC11_F1_WIDTH                                                        1
#define SEC11_F1_SHIFT                                                       11
#define SEC11_F1_MASK                                                0x00000800
#define SEC11_F1_RD(src)                             (((src) & 0x00000800)>>11)
#define SEC11_F1_WR(src)                        (((u32)(src)<<11) & 0x00000800)
#define SEC11_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SEC10	 */
#define SEC10_F1_WIDTH                                                        1
#define SEC10_F1_SHIFT                                                       10
#define SEC10_F1_MASK                                                0x00000400
#define SEC10_F1_RD(src)                             (((src) & 0x00000400)>>10)
#define SEC10_F1_WR(src)                        (((u32)(src)<<10) & 0x00000400)
#define SEC10_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SEC9	 */
#define SEC9_F1_WIDTH                                                         1
#define SEC9_F1_SHIFT                                                         9
#define SEC9_F1_MASK                                                 0x00000200
#define SEC9_F1_RD(src)                               (((src) & 0x00000200)>>9)
#define SEC9_F1_WR(src)                          (((u32)(src)<<9) & 0x00000200)
#define SEC9_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SEC8	 */
#define SEC8_F1_WIDTH                                                         1
#define SEC8_F1_SHIFT                                                         8
#define SEC8_F1_MASK                                                 0x00000100
#define SEC8_F1_RD(src)                               (((src) & 0x00000100)>>8)
#define SEC8_F1_WR(src)                          (((u32)(src)<<8) & 0x00000100)
#define SEC8_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SEC7	 */
#define SEC7_F1_WIDTH                                                         1
#define SEC7_F1_SHIFT                                                         7
#define SEC7_F1_MASK                                                 0x00000080
#define SEC7_F1_RD(src)                               (((src) & 0x00000080)>>7)
#define SEC7_F1_WR(src)                          (((u32)(src)<<7) & 0x00000080)
#define SEC7_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SEC6	 */
#define SEC6_F1_WIDTH                                                         1
#define SEC6_F1_SHIFT                                                         6
#define SEC6_F1_MASK                                                 0x00000040
#define SEC6_F1_RD(src)                               (((src) & 0x00000040)>>6)
#define SEC6_F1_WR(src)                          (((u32)(src)<<6) & 0x00000040)
#define SEC6_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields SEC5	 */
#define SEC5_F1_WIDTH                                                         1
#define SEC5_F1_SHIFT                                                         5
#define SEC5_F1_MASK                                                 0x00000020
#define SEC5_F1_RD(src)                               (((src) & 0x00000020)>>5)
#define SEC5_F1_WR(src)                          (((u32)(src)<<5) & 0x00000020)
#define SEC5_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields SEC4	 */
#define SEC4_F1_WIDTH                                                         1
#define SEC4_F1_SHIFT                                                         4
#define SEC4_F1_MASK                                                 0x00000010
#define SEC4_F1_RD(src)                               (((src) & 0x00000010)>>4)
#define SEC4_F1_WR(src)                          (((u32)(src)<<4) & 0x00000010)
#define SEC4_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields SEC3	 */
#define SEC3_F1_WIDTH                                                         1
#define SEC3_F1_SHIFT                                                         3
#define SEC3_F1_MASK                                                 0x00000008
#define SEC3_F1_RD(src)                               (((src) & 0x00000008)>>3)
#define SEC3_F1_WR(src)                          (((u32)(src)<<3) & 0x00000008)
#define SEC3_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SEC2	 */
#define SEC2_F1_WIDTH                                                         1
#define SEC2_F1_SHIFT                                                         2
#define SEC2_F1_MASK                                                 0x00000004
#define SEC2_F1_RD(src)                               (((src) & 0x00000004)>>2)
#define SEC2_F1_WR(src)                          (((u32)(src)<<2) & 0x00000004)
#define SEC2_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SEC1	 */
#define SEC1_F1_WIDTH                                                         1
#define SEC1_F1_SHIFT                                                         1
#define SEC1_F1_MASK                                                 0x00000002
#define SEC1_F1_RD(src)                               (((src) & 0x00000002)>>1)
#define SEC1_F1_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define SEC1_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SEC0	 */
#define SEC0_F1_WIDTH                                                         1
#define SEC0_F1_SHIFT                                                         0
#define SEC0_F1_MASK                                                 0x00000001
#define SEC0_F1_RD(src)                                  (((src) & 0x00000001))
#define SEC0_F1_WR(src)                             (((u32)(src)) & 0x00000001)
#define SEC0_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRHMask	*/
/*    Mask Register Fields SEC31Mask    */
#define SEC31MASK_F1_WIDTH                                                    1
#define SEC31MASK_F1_SHIFT                                                   31
#define SEC31MASK_F1_MASK                                            0x80000000
#define SEC31MASK_F1_RD(src)                         (((src) & 0x80000000)>>31)
#define SEC31MASK_F1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define SEC31MASK_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields SEC30Mask    */
#define SEC30MASK_F1_WIDTH                                                    1
#define SEC30MASK_F1_SHIFT                                                   30
#define SEC30MASK_F1_MASK                                            0x40000000
#define SEC30MASK_F1_RD(src)                         (((src) & 0x40000000)>>30)
#define SEC30MASK_F1_WR(src)                    (((u32)(src)<<30) & 0x40000000)
#define SEC30MASK_F1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields SEC29Mask    */
#define SEC29MASK_F1_WIDTH                                                    1
#define SEC29MASK_F1_SHIFT                                                   29
#define SEC29MASK_F1_MASK                                            0x20000000
#define SEC29MASK_F1_RD(src)                         (((src) & 0x20000000)>>29)
#define SEC29MASK_F1_WR(src)                    (((u32)(src)<<29) & 0x20000000)
#define SEC29MASK_F1_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields SEC28Mask    */
#define SEC28MASK_F1_WIDTH                                                    1
#define SEC28MASK_F1_SHIFT                                                   28
#define SEC28MASK_F1_MASK                                            0x10000000
#define SEC28MASK_F1_RD(src)                         (((src) & 0x10000000)>>28)
#define SEC28MASK_F1_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define SEC28MASK_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields SEC27Mask    */
#define SEC27MASK_F1_WIDTH                                                    1
#define SEC27MASK_F1_SHIFT                                                   27
#define SEC27MASK_F1_MASK                                            0x08000000
#define SEC27MASK_F1_RD(src)                         (((src) & 0x08000000)>>27)
#define SEC27MASK_F1_WR(src)                    (((u32)(src)<<27) & 0x08000000)
#define SEC27MASK_F1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields SEC26Mask    */
#define SEC26MASK_F1_WIDTH                                                    1
#define SEC26MASK_F1_SHIFT                                                   26
#define SEC26MASK_F1_MASK                                            0x04000000
#define SEC26MASK_F1_RD(src)                         (((src) & 0x04000000)>>26)
#define SEC26MASK_F1_WR(src)                    (((u32)(src)<<26) & 0x04000000)
#define SEC26MASK_F1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields SEC25Mask    */
#define SEC25MASK_F1_WIDTH                                                    1
#define SEC25MASK_F1_SHIFT                                                   25
#define SEC25MASK_F1_MASK                                            0x02000000
#define SEC25MASK_F1_RD(src)                         (((src) & 0x02000000)>>25)
#define SEC25MASK_F1_WR(src)                    (((u32)(src)<<25) & 0x02000000)
#define SEC25MASK_F1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields SEC24Mask    */
#define SEC24MASK_F1_WIDTH                                                    1
#define SEC24MASK_F1_SHIFT                                                   24
#define SEC24MASK_F1_MASK                                            0x01000000
#define SEC24MASK_F1_RD(src)                         (((src) & 0x01000000)>>24)
#define SEC24MASK_F1_WR(src)                    (((u32)(src)<<24) & 0x01000000)
#define SEC24MASK_F1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields SEC23Mask    */
#define SEC23MASK_F1_WIDTH                                                    1
#define SEC23MASK_F1_SHIFT                                                   23
#define SEC23MASK_F1_MASK                                            0x00800000
#define SEC23MASK_F1_RD(src)                         (((src) & 0x00800000)>>23)
#define SEC23MASK_F1_WR(src)                    (((u32)(src)<<23) & 0x00800000)
#define SEC23MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields SEC22Mask    */
#define SEC22MASK_F1_WIDTH                                                    1
#define SEC22MASK_F1_SHIFT                                                   22
#define SEC22MASK_F1_MASK                                            0x00400000
#define SEC22MASK_F1_RD(src)                         (((src) & 0x00400000)>>22)
#define SEC22MASK_F1_WR(src)                    (((u32)(src)<<22) & 0x00400000)
#define SEC22MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields SEC21Mask    */
#define SEC21MASK_F1_WIDTH                                                    1
#define SEC21MASK_F1_SHIFT                                                   21
#define SEC21MASK_F1_MASK                                            0x00200000
#define SEC21MASK_F1_RD(src)                         (((src) & 0x00200000)>>21)
#define SEC21MASK_F1_WR(src)                    (((u32)(src)<<21) & 0x00200000)
#define SEC21MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields SEC20Mask    */
#define SEC20MASK_F1_WIDTH                                                    1
#define SEC20MASK_F1_SHIFT                                                   20
#define SEC20MASK_F1_MASK                                            0x00100000
#define SEC20MASK_F1_RD(src)                         (((src) & 0x00100000)>>20)
#define SEC20MASK_F1_WR(src)                    (((u32)(src)<<20) & 0x00100000)
#define SEC20MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields SEC19Mask    */
#define SEC19MASK_F1_WIDTH                                                    1
#define SEC19MASK_F1_SHIFT                                                   19
#define SEC19MASK_F1_MASK                                            0x00080000
#define SEC19MASK_F1_RD(src)                         (((src) & 0x00080000)>>19)
#define SEC19MASK_F1_WR(src)                    (((u32)(src)<<19) & 0x00080000)
#define SEC19MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields SEC18Mask    */
#define SEC18MASK_F1_WIDTH                                                    1
#define SEC18MASK_F1_SHIFT                                                   18
#define SEC18MASK_F1_MASK                                            0x00040000
#define SEC18MASK_F1_RD(src)                         (((src) & 0x00040000)>>18)
#define SEC18MASK_F1_WR(src)                    (((u32)(src)<<18) & 0x00040000)
#define SEC18MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields SEC17Mask    */
#define SEC17MASK_F1_WIDTH                                                    1
#define SEC17MASK_F1_SHIFT                                                   17
#define SEC17MASK_F1_MASK                                            0x00020000
#define SEC17MASK_F1_RD(src)                         (((src) & 0x00020000)>>17)
#define SEC17MASK_F1_WR(src)                    (((u32)(src)<<17) & 0x00020000)
#define SEC17MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields SEC16Mask    */
#define SEC16MASK_F1_WIDTH                                                    1
#define SEC16MASK_F1_SHIFT                                                   16
#define SEC16MASK_F1_MASK                                            0x00010000
#define SEC16MASK_F1_RD(src)                         (((src) & 0x00010000)>>16)
#define SEC16MASK_F1_WR(src)                    (((u32)(src)<<16) & 0x00010000)
#define SEC16MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields SEC15Mask    */
#define SEC15MASK_F1_WIDTH                                                    1
#define SEC15MASK_F1_SHIFT                                                   15
#define SEC15MASK_F1_MASK                                            0x00008000
#define SEC15MASK_F1_RD(src)                         (((src) & 0x00008000)>>15)
#define SEC15MASK_F1_WR(src)                    (((u32)(src)<<15) & 0x00008000)
#define SEC15MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields SEC14Mask    */
#define SEC14MASK_F1_WIDTH                                                    1
#define SEC14MASK_F1_SHIFT                                                   14
#define SEC14MASK_F1_MASK                                            0x00004000
#define SEC14MASK_F1_RD(src)                         (((src) & 0x00004000)>>14)
#define SEC14MASK_F1_WR(src)                    (((u32)(src)<<14) & 0x00004000)
#define SEC14MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields SEC13Mask    */
#define SEC13MASK_F1_WIDTH                                                    1
#define SEC13MASK_F1_SHIFT                                                   13
#define SEC13MASK_F1_MASK                                            0x00002000
#define SEC13MASK_F1_RD(src)                         (((src) & 0x00002000)>>13)
#define SEC13MASK_F1_WR(src)                    (((u32)(src)<<13) & 0x00002000)
#define SEC13MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields SEC12Mask    */
#define SEC12MASK_F1_WIDTH                                                    1
#define SEC12MASK_F1_SHIFT                                                   12
#define SEC12MASK_F1_MASK                                            0x00001000
#define SEC12MASK_F1_RD(src)                         (((src) & 0x00001000)>>12)
#define SEC12MASK_F1_WR(src)                    (((u32)(src)<<12) & 0x00001000)
#define SEC12MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SEC11Mask    */
#define SEC11MASK_F1_WIDTH                                                    1
#define SEC11MASK_F1_SHIFT                                                   11
#define SEC11MASK_F1_MASK                                            0x00000800
#define SEC11MASK_F1_RD(src)                         (((src) & 0x00000800)>>11)
#define SEC11MASK_F1_WR(src)                    (((u32)(src)<<11) & 0x00000800)
#define SEC11MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SEC10Mask    */
#define SEC10MASK_F1_WIDTH                                                    1
#define SEC10MASK_F1_SHIFT                                                   10
#define SEC10MASK_F1_MASK                                            0x00000400
#define SEC10MASK_F1_RD(src)                         (((src) & 0x00000400)>>10)
#define SEC10MASK_F1_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define SEC10MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SEC9Mask    */
#define SEC9MASK_F1_WIDTH                                                     1
#define SEC9MASK_F1_SHIFT                                                     9
#define SEC9MASK_F1_MASK                                             0x00000200
#define SEC9MASK_F1_RD(src)                           (((src) & 0x00000200)>>9)
#define SEC9MASK_F1_WR(src)                      (((u32)(src)<<9) & 0x00000200)
#define SEC9MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields SEC8Mask    */
#define SEC8MASK_F1_WIDTH                                                     1
#define SEC8MASK_F1_SHIFT                                                     8
#define SEC8MASK_F1_MASK                                             0x00000100
#define SEC8MASK_F1_RD(src)                           (((src) & 0x00000100)>>8)
#define SEC8MASK_F1_WR(src)                      (((u32)(src)<<8) & 0x00000100)
#define SEC8MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields SEC7Mask    */
#define SEC7MASK_F1_WIDTH                                                     1
#define SEC7MASK_F1_SHIFT                                                     7
#define SEC7MASK_F1_MASK                                             0x00000080
#define SEC7MASK_F1_RD(src)                           (((src) & 0x00000080)>>7)
#define SEC7MASK_F1_WR(src)                      (((u32)(src)<<7) & 0x00000080)
#define SEC7MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields SEC6Mask    */
#define SEC6MASK_F1_WIDTH                                                     1
#define SEC6MASK_F1_SHIFT                                                     6
#define SEC6MASK_F1_MASK                                             0x00000040
#define SEC6MASK_F1_RD(src)                           (((src) & 0x00000040)>>6)
#define SEC6MASK_F1_WR(src)                      (((u32)(src)<<6) & 0x00000040)
#define SEC6MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields SEC5Mask    */
#define SEC5MASK_F1_WIDTH                                                     1
#define SEC5MASK_F1_SHIFT                                                     5
#define SEC5MASK_F1_MASK                                             0x00000020
#define SEC5MASK_F1_RD(src)                           (((src) & 0x00000020)>>5)
#define SEC5MASK_F1_WR(src)                      (((u32)(src)<<5) & 0x00000020)
#define SEC5MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields SEC4Mask    */
#define SEC4MASK_F1_WIDTH                                                     1
#define SEC4MASK_F1_SHIFT                                                     4
#define SEC4MASK_F1_MASK                                             0x00000010
#define SEC4MASK_F1_RD(src)                           (((src) & 0x00000010)>>4)
#define SEC4MASK_F1_WR(src)                      (((u32)(src)<<4) & 0x00000010)
#define SEC4MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields SEC3Mask    */
#define SEC3MASK_F1_WIDTH                                                     1
#define SEC3MASK_F1_SHIFT                                                     3
#define SEC3MASK_F1_MASK                                             0x00000008
#define SEC3MASK_F1_RD(src)                           (((src) & 0x00000008)>>3)
#define SEC3MASK_F1_WR(src)                      (((u32)(src)<<3) & 0x00000008)
#define SEC3MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields SEC2Mask    */
#define SEC2MASK_F1_WIDTH                                                     1
#define SEC2MASK_F1_SHIFT                                                     2
#define SEC2MASK_F1_MASK                                             0x00000004
#define SEC2MASK_F1_RD(src)                           (((src) & 0x00000004)>>2)
#define SEC2MASK_F1_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define SEC2MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields SEC1Mask    */
#define SEC1MASK_F1_WIDTH                                                     1
#define SEC1MASK_F1_SHIFT                                                     1
#define SEC1MASK_F1_MASK                                             0x00000002
#define SEC1MASK_F1_RD(src)                           (((src) & 0x00000002)>>1)
#define SEC1MASK_F1_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define SEC1MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SEC0Mask    */
#define SEC0MASK_F1_WIDTH                                                     1
#define SEC0MASK_F1_SHIFT                                                     0
#define SEC0MASK_F1_MASK                                             0x00000001
#define SEC0MASK_F1_RD(src)                              (((src) & 0x00000001))
#define SEC0MASK_F1_WR(src)                         (((u32)(src)) & 0x00000001)
#define SEC0MASK_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRL	*/
/*	 Fields MSEC31	 */
#define MSEC31_WIDTH                                                          1
#define MSEC31_SHIFT                                                         31
#define MSEC31_MASK                                                  0x80000000
#define MSEC31_RD(src)                               (((src) & 0x80000000)>>31)
#define MSEC31_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MSEC31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MSEC30	 */
#define MSEC30_WIDTH                                                          1
#define MSEC30_SHIFT                                                         30
#define MSEC30_MASK                                                  0x40000000
#define MSEC30_RD(src)                               (((src) & 0x40000000)>>30)
#define MSEC30_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MSEC30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MSEC29	 */
#define MSEC29_WIDTH                                                          1
#define MSEC29_SHIFT                                                         29
#define MSEC29_MASK                                                  0x20000000
#define MSEC29_RD(src)                               (((src) & 0x20000000)>>29)
#define MSEC29_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MSEC29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MSEC28	 */
#define MSEC28_WIDTH                                                          1
#define MSEC28_SHIFT                                                         28
#define MSEC28_MASK                                                  0x10000000
#define MSEC28_RD(src)                               (((src) & 0x10000000)>>28)
#define MSEC28_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MSEC28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MSEC27	 */
#define MSEC27_WIDTH                                                          1
#define MSEC27_SHIFT                                                         27
#define MSEC27_MASK                                                  0x08000000
#define MSEC27_RD(src)                               (((src) & 0x08000000)>>27)
#define MSEC27_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MSEC27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MSEC26	 */
#define MSEC26_WIDTH                                                          1
#define MSEC26_SHIFT                                                         26
#define MSEC26_MASK                                                  0x04000000
#define MSEC26_RD(src)                               (((src) & 0x04000000)>>26)
#define MSEC26_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MSEC26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MSEC25	 */
#define MSEC25_WIDTH                                                          1
#define MSEC25_SHIFT                                                         25
#define MSEC25_MASK                                                  0x02000000
#define MSEC25_RD(src)                               (((src) & 0x02000000)>>25)
#define MSEC25_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MSEC25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MSEC24	 */
#define MSEC24_WIDTH                                                          1
#define MSEC24_SHIFT                                                         24
#define MSEC24_MASK                                                  0x01000000
#define MSEC24_RD(src)                               (((src) & 0x01000000)>>24)
#define MSEC24_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MSEC24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MSEC23	 */
#define MSEC23_WIDTH                                                          1
#define MSEC23_SHIFT                                                         23
#define MSEC23_MASK                                                  0x00800000
#define MSEC23_RD(src)                               (((src) & 0x00800000)>>23)
#define MSEC23_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MSEC23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MSEC22	 */
#define MSEC22_WIDTH                                                          1
#define MSEC22_SHIFT                                                         22
#define MSEC22_MASK                                                  0x00400000
#define MSEC22_RD(src)                               (((src) & 0x00400000)>>22)
#define MSEC22_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MSEC22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MSEC21	 */
#define MSEC21_WIDTH                                                          1
#define MSEC21_SHIFT                                                         21
#define MSEC21_MASK                                                  0x00200000
#define MSEC21_RD(src)                               (((src) & 0x00200000)>>21)
#define MSEC21_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MSEC21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MSEC20	 */
#define MSEC20_WIDTH                                                          1
#define MSEC20_SHIFT                                                         20
#define MSEC20_MASK                                                  0x00100000
#define MSEC20_RD(src)                               (((src) & 0x00100000)>>20)
#define MSEC20_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MSEC20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MSEC19	 */
#define MSEC19_WIDTH                                                          1
#define MSEC19_SHIFT                                                         19
#define MSEC19_MASK                                                  0x00080000
#define MSEC19_RD(src)                               (((src) & 0x00080000)>>19)
#define MSEC19_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MSEC19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MSEC18	 */
#define MSEC18_WIDTH                                                          1
#define MSEC18_SHIFT                                                         18
#define MSEC18_MASK                                                  0x00040000
#define MSEC18_RD(src)                               (((src) & 0x00040000)>>18)
#define MSEC18_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MSEC18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MSEC17	 */
#define MSEC17_WIDTH                                                          1
#define MSEC17_SHIFT                                                         17
#define MSEC17_MASK                                                  0x00020000
#define MSEC17_RD(src)                               (((src) & 0x00020000)>>17)
#define MSEC17_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MSEC17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MSEC16	 */
#define MSEC16_WIDTH                                                          1
#define MSEC16_SHIFT                                                         16
#define MSEC16_MASK                                                  0x00010000
#define MSEC16_RD(src)                               (((src) & 0x00010000)>>16)
#define MSEC16_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MSEC16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MSEC15	 */
#define MSEC15_WIDTH                                                          1
#define MSEC15_SHIFT                                                         15
#define MSEC15_MASK                                                  0x00008000
#define MSEC15_RD(src)                               (((src) & 0x00008000)>>15)
#define MSEC15_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MSEC15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MSEC14	 */
#define MSEC14_WIDTH                                                          1
#define MSEC14_SHIFT                                                         14
#define MSEC14_MASK                                                  0x00004000
#define MSEC14_RD(src)                               (((src) & 0x00004000)>>14)
#define MSEC14_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MSEC14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MSEC13	 */
#define MSEC13_WIDTH                                                          1
#define MSEC13_SHIFT                                                         13
#define MSEC13_MASK                                                  0x00002000
#define MSEC13_RD(src)                               (((src) & 0x00002000)>>13)
#define MSEC13_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MSEC13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MSEC12	 */
#define MSEC12_WIDTH                                                          1
#define MSEC12_SHIFT                                                         12
#define MSEC12_MASK                                                  0x00001000
#define MSEC12_RD(src)                               (((src) & 0x00001000)>>12)
#define MSEC12_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MSEC12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MSEC11	 */
#define MSEC11_WIDTH                                                          1
#define MSEC11_SHIFT                                                         11
#define MSEC11_MASK                                                  0x00000800
#define MSEC11_RD(src)                               (((src) & 0x00000800)>>11)
#define MSEC11_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MSEC11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MSEC10	 */
#define MSEC10_WIDTH                                                          1
#define MSEC10_SHIFT                                                         10
#define MSEC10_MASK                                                  0x00000400
#define MSEC10_RD(src)                               (((src) & 0x00000400)>>10)
#define MSEC10_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MSEC10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MSEC9	 */
#define MSEC9_WIDTH                                                           1
#define MSEC9_SHIFT                                                           9
#define MSEC9_MASK                                                   0x00000200
#define MSEC9_RD(src)                                 (((src) & 0x00000200)>>9)
#define MSEC9_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define MSEC9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MSEC8	 */
#define MSEC8_WIDTH                                                           1
#define MSEC8_SHIFT                                                           8
#define MSEC8_MASK                                                   0x00000100
#define MSEC8_RD(src)                                 (((src) & 0x00000100)>>8)
#define MSEC8_WR(src)                            (((u32)(src)<<8) & 0x00000100)
#define MSEC8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MSEC7	 */
#define MSEC7_WIDTH                                                           1
#define MSEC7_SHIFT                                                           7
#define MSEC7_MASK                                                   0x00000080
#define MSEC7_RD(src)                                 (((src) & 0x00000080)>>7)
#define MSEC7_WR(src)                            (((u32)(src)<<7) & 0x00000080)
#define MSEC7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MSEC6	 */
#define MSEC6_WIDTH                                                           1
#define MSEC6_SHIFT                                                           6
#define MSEC6_MASK                                                   0x00000040
#define MSEC6_RD(src)                                 (((src) & 0x00000040)>>6)
#define MSEC6_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define MSEC6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MSEC5	 */
#define MSEC5_WIDTH                                                           1
#define MSEC5_SHIFT                                                           5
#define MSEC5_MASK                                                   0x00000020
#define MSEC5_RD(src)                                 (((src) & 0x00000020)>>5)
#define MSEC5_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define MSEC5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MSEC4	 */
#define MSEC4_WIDTH                                                           1
#define MSEC4_SHIFT                                                           4
#define MSEC4_MASK                                                   0x00000010
#define MSEC4_RD(src)                                 (((src) & 0x00000010)>>4)
#define MSEC4_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define MSEC4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MSEC3	 */
#define MSEC3_WIDTH                                                           1
#define MSEC3_SHIFT                                                           3
#define MSEC3_MASK                                                   0x00000008
#define MSEC3_RD(src)                                 (((src) & 0x00000008)>>3)
#define MSEC3_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define MSEC3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MSEC2	 */
#define MSEC2_WIDTH                                                           1
#define MSEC2_SHIFT                                                           2
#define MSEC2_MASK                                                   0x00000004
#define MSEC2_RD(src)                                 (((src) & 0x00000004)>>2)
#define MSEC2_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define MSEC2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSEC1	 */
#define MSEC1_WIDTH                                                           1
#define MSEC1_SHIFT                                                           1
#define MSEC1_MASK                                                   0x00000002
#define MSEC1_RD(src)                                 (((src) & 0x00000002)>>1)
#define MSEC1_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define MSEC1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MSEC0	 */
#define MSEC0_WIDTH                                                           1
#define MSEC0_SHIFT                                                           0
#define MSEC0_MASK                                                   0x00000001
#define MSEC0_RD(src)                                    (((src) & 0x00000001))
#define MSEC0_WR(src)                               (((u32)(src)) & 0x00000001)
#define MSEC0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRLMask	*/
/*    Mask Register Fields MSEC31Mask    */
#define MSEC31MASK_WIDTH                                                      1
#define MSEC31MASK_SHIFT                                                     31
#define MSEC31MASK_MASK                                              0x80000000
#define MSEC31MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MSEC31MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MSEC31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MSEC30Mask    */
#define MSEC30MASK_WIDTH                                                      1
#define MSEC30MASK_SHIFT                                                     30
#define MSEC30MASK_MASK                                              0x40000000
#define MSEC30MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MSEC30MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MSEC30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MSEC29Mask    */
#define MSEC29MASK_WIDTH                                                      1
#define MSEC29MASK_SHIFT                                                     29
#define MSEC29MASK_MASK                                              0x20000000
#define MSEC29MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MSEC29MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MSEC29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MSEC28Mask    */
#define MSEC28MASK_WIDTH                                                      1
#define MSEC28MASK_SHIFT                                                     28
#define MSEC28MASK_MASK                                              0x10000000
#define MSEC28MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MSEC28MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MSEC28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MSEC27Mask    */
#define MSEC27MASK_WIDTH                                                      1
#define MSEC27MASK_SHIFT                                                     27
#define MSEC27MASK_MASK                                              0x08000000
#define MSEC27MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MSEC27MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MSEC27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MSEC26Mask    */
#define MSEC26MASK_WIDTH                                                      1
#define MSEC26MASK_SHIFT                                                     26
#define MSEC26MASK_MASK                                              0x04000000
#define MSEC26MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MSEC26MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MSEC26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MSEC25Mask    */
#define MSEC25MASK_WIDTH                                                      1
#define MSEC25MASK_SHIFT                                                     25
#define MSEC25MASK_MASK                                              0x02000000
#define MSEC25MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MSEC25MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MSEC25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MSEC24Mask    */
#define MSEC24MASK_WIDTH                                                      1
#define MSEC24MASK_SHIFT                                                     24
#define MSEC24MASK_MASK                                              0x01000000
#define MSEC24MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MSEC24MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MSEC24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MSEC23Mask    */
#define MSEC23MASK_WIDTH                                                      1
#define MSEC23MASK_SHIFT                                                     23
#define MSEC23MASK_MASK                                              0x00800000
#define MSEC23MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MSEC23MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MSEC23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MSEC22Mask    */
#define MSEC22MASK_WIDTH                                                      1
#define MSEC22MASK_SHIFT                                                     22
#define MSEC22MASK_MASK                                              0x00400000
#define MSEC22MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MSEC22MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MSEC22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MSEC21Mask    */
#define MSEC21MASK_WIDTH                                                      1
#define MSEC21MASK_SHIFT                                                     21
#define MSEC21MASK_MASK                                              0x00200000
#define MSEC21MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MSEC21MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MSEC21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MSEC20Mask    */
#define MSEC20MASK_WIDTH                                                      1
#define MSEC20MASK_SHIFT                                                     20
#define MSEC20MASK_MASK                                              0x00100000
#define MSEC20MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MSEC20MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MSEC20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MSEC19Mask    */
#define MSEC19MASK_WIDTH                                                      1
#define MSEC19MASK_SHIFT                                                     19
#define MSEC19MASK_MASK                                              0x00080000
#define MSEC19MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MSEC19MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MSEC19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MSEC18Mask    */
#define MSEC18MASK_WIDTH                                                      1
#define MSEC18MASK_SHIFT                                                     18
#define MSEC18MASK_MASK                                              0x00040000
#define MSEC18MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MSEC18MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MSEC18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MSEC17Mask    */
#define MSEC17MASK_WIDTH                                                      1
#define MSEC17MASK_SHIFT                                                     17
#define MSEC17MASK_MASK                                              0x00020000
#define MSEC17MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MSEC17MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MSEC17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MSEC16Mask    */
#define MSEC16MASK_WIDTH                                                      1
#define MSEC16MASK_SHIFT                                                     16
#define MSEC16MASK_MASK                                              0x00010000
#define MSEC16MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MSEC16MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MSEC16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MSEC15Mask    */
#define MSEC15MASK_WIDTH                                                      1
#define MSEC15MASK_SHIFT                                                     15
#define MSEC15MASK_MASK                                              0x00008000
#define MSEC15MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MSEC15MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MSEC15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MSEC14Mask    */
#define MSEC14MASK_WIDTH                                                      1
#define MSEC14MASK_SHIFT                                                     14
#define MSEC14MASK_MASK                                              0x00004000
#define MSEC14MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MSEC14MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MSEC14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MSEC13Mask    */
#define MSEC13MASK_WIDTH                                                      1
#define MSEC13MASK_SHIFT                                                     13
#define MSEC13MASK_MASK                                              0x00002000
#define MSEC13MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MSEC13MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MSEC13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MSEC12Mask    */
#define MSEC12MASK_WIDTH                                                      1
#define MSEC12MASK_SHIFT                                                     12
#define MSEC12MASK_MASK                                              0x00001000
#define MSEC12MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MSEC12MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MSEC12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MSEC11Mask    */
#define MSEC11MASK_WIDTH                                                      1
#define MSEC11MASK_SHIFT                                                     11
#define MSEC11MASK_MASK                                              0x00000800
#define MSEC11MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MSEC11MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MSEC11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MSEC10Mask    */
#define MSEC10MASK_WIDTH                                                      1
#define MSEC10MASK_SHIFT                                                     10
#define MSEC10MASK_MASK                                              0x00000400
#define MSEC10MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MSEC10MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MSEC10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MSEC9Mask    */
#define MSEC9MASK_WIDTH                                                       1
#define MSEC9MASK_SHIFT                                                       9
#define MSEC9MASK_MASK                                               0x00000200
#define MSEC9MASK_RD(src)                             (((src) & 0x00000200)>>9)
#define MSEC9MASK_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define MSEC9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MSEC8Mask    */
#define MSEC8MASK_WIDTH                                                       1
#define MSEC8MASK_SHIFT                                                       8
#define MSEC8MASK_MASK                                               0x00000100
#define MSEC8MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define MSEC8MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define MSEC8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MSEC7Mask    */
#define MSEC7MASK_WIDTH                                                       1
#define MSEC7MASK_SHIFT                                                       7
#define MSEC7MASK_MASK                                               0x00000080
#define MSEC7MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define MSEC7MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define MSEC7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MSEC6Mask    */
#define MSEC6MASK_WIDTH                                                       1
#define MSEC6MASK_SHIFT                                                       6
#define MSEC6MASK_MASK                                               0x00000040
#define MSEC6MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define MSEC6MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define MSEC6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MSEC5Mask    */
#define MSEC5MASK_WIDTH                                                       1
#define MSEC5MASK_SHIFT                                                       5
#define MSEC5MASK_MASK                                               0x00000020
#define MSEC5MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define MSEC5MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define MSEC5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MSEC4Mask    */
#define MSEC4MASK_WIDTH                                                       1
#define MSEC4MASK_SHIFT                                                       4
#define MSEC4MASK_MASK                                               0x00000010
#define MSEC4MASK_RD(src)                             (((src) & 0x00000010)>>4)
#define MSEC4MASK_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define MSEC4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MSEC3Mask    */
#define MSEC3MASK_WIDTH                                                       1
#define MSEC3MASK_SHIFT                                                       3
#define MSEC3MASK_MASK                                               0x00000008
#define MSEC3MASK_RD(src)                             (((src) & 0x00000008)>>3)
#define MSEC3MASK_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define MSEC3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MSEC2Mask    */
#define MSEC2MASK_WIDTH                                                       1
#define MSEC2MASK_SHIFT                                                       2
#define MSEC2MASK_MASK                                               0x00000004
#define MSEC2MASK_RD(src)                             (((src) & 0x00000004)>>2)
#define MSEC2MASK_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define MSEC2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MSEC1Mask    */
#define MSEC1MASK_WIDTH                                                       1
#define MSEC1MASK_SHIFT                                                       1
#define MSEC1MASK_MASK                                               0x00000002
#define MSEC1MASK_RD(src)                             (((src) & 0x00000002)>>1)
#define MSEC1MASK_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define MSEC1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MSEC0Mask    */
#define MSEC0MASK_WIDTH                                                       1
#define MSEC0MASK_SHIFT                                                       0
#define MSEC0MASK_MASK                                               0x00000001
#define MSEC0MASK_RD(src)                                (((src) & 0x00000001))
#define MSEC0MASK_WR(src)                           (((u32)(src)) & 0x00000001)
#define MSEC0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRH	*/
/*	 Fields MSEC63	 */
#define MSEC63_WIDTH                                                          1
#define MSEC63_SHIFT                                                         31
#define MSEC63_MASK                                                  0x80000000
#define MSEC63_RD(src)                               (((src) & 0x80000000)>>31)
#define MSEC63_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MSEC63_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MSEC62	 */
#define MSEC62_WIDTH                                                          1
#define MSEC62_SHIFT                                                         30
#define MSEC62_MASK                                                  0x40000000
#define MSEC62_RD(src)                               (((src) & 0x40000000)>>30)
#define MSEC62_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MSEC62_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MSEC61	 */
#define MSEC61_WIDTH                                                          1
#define MSEC61_SHIFT                                                         29
#define MSEC61_MASK                                                  0x20000000
#define MSEC61_RD(src)                               (((src) & 0x20000000)>>29)
#define MSEC61_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MSEC61_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MSEC60	 */
#define MSEC60_WIDTH                                                          1
#define MSEC60_SHIFT                                                         28
#define MSEC60_MASK                                                  0x10000000
#define MSEC60_RD(src)                               (((src) & 0x10000000)>>28)
#define MSEC60_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MSEC60_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MSEC59	 */
#define MSEC59_WIDTH                                                          1
#define MSEC59_SHIFT                                                         27
#define MSEC59_MASK                                                  0x08000000
#define MSEC59_RD(src)                               (((src) & 0x08000000)>>27)
#define MSEC59_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MSEC59_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MSEC58	 */
#define MSEC58_WIDTH                                                          1
#define MSEC58_SHIFT                                                         26
#define MSEC58_MASK                                                  0x04000000
#define MSEC58_RD(src)                               (((src) & 0x04000000)>>26)
#define MSEC58_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MSEC58_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MSEC57	 */
#define MSEC57_WIDTH                                                          1
#define MSEC57_SHIFT                                                         25
#define MSEC57_MASK                                                  0x02000000
#define MSEC57_RD(src)                               (((src) & 0x02000000)>>25)
#define MSEC57_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MSEC57_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MSEC56	 */
#define MSEC56_WIDTH                                                          1
#define MSEC56_SHIFT                                                         24
#define MSEC56_MASK                                                  0x01000000
#define MSEC56_RD(src)                               (((src) & 0x01000000)>>24)
#define MSEC56_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MSEC56_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MSEC55	 */
#define MSEC55_WIDTH                                                          1
#define MSEC55_SHIFT                                                         23
#define MSEC55_MASK                                                  0x00800000
#define MSEC55_RD(src)                               (((src) & 0x00800000)>>23)
#define MSEC55_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MSEC55_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MSEC54	 */
#define MSEC54_WIDTH                                                          1
#define MSEC54_SHIFT                                                         22
#define MSEC54_MASK                                                  0x00400000
#define MSEC54_RD(src)                               (((src) & 0x00400000)>>22)
#define MSEC54_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MSEC54_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MSEC53	 */
#define MSEC53_WIDTH                                                          1
#define MSEC53_SHIFT                                                         21
#define MSEC53_MASK                                                  0x00200000
#define MSEC53_RD(src)                               (((src) & 0x00200000)>>21)
#define MSEC53_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MSEC53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MSEC52	 */
#define MSEC52_WIDTH                                                          1
#define MSEC52_SHIFT                                                         20
#define MSEC52_MASK                                                  0x00100000
#define MSEC52_RD(src)                               (((src) & 0x00100000)>>20)
#define MSEC52_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MSEC52_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MSEC51	 */
#define MSEC51_WIDTH                                                          1
#define MSEC51_SHIFT                                                         19
#define MSEC51_MASK                                                  0x00080000
#define MSEC51_RD(src)                               (((src) & 0x00080000)>>19)
#define MSEC51_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MSEC51_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MSEC50	 */
#define MSEC50_WIDTH                                                          1
#define MSEC50_SHIFT                                                         18
#define MSEC50_MASK                                                  0x00040000
#define MSEC50_RD(src)                               (((src) & 0x00040000)>>18)
#define MSEC50_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MSEC50_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MSEC49	 */
#define MSEC49_WIDTH                                                          1
#define MSEC49_SHIFT                                                         17
#define MSEC49_MASK                                                  0x00020000
#define MSEC49_RD(src)                               (((src) & 0x00020000)>>17)
#define MSEC49_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MSEC49_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MSEC48	 */
#define MSEC48_WIDTH                                                          1
#define MSEC48_SHIFT                                                         16
#define MSEC48_MASK                                                  0x00010000
#define MSEC48_RD(src)                               (((src) & 0x00010000)>>16)
#define MSEC48_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MSEC48_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MSEC47	 */
#define MSEC47_WIDTH                                                          1
#define MSEC47_SHIFT                                                         15
#define MSEC47_MASK                                                  0x00008000
#define MSEC47_RD(src)                               (((src) & 0x00008000)>>15)
#define MSEC47_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MSEC47_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MSEC46	 */
#define MSEC46_WIDTH                                                          1
#define MSEC46_SHIFT                                                         14
#define MSEC46_MASK                                                  0x00004000
#define MSEC46_RD(src)                               (((src) & 0x00004000)>>14)
#define MSEC46_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MSEC46_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MSEC45	 */
#define MSEC45_WIDTH                                                          1
#define MSEC45_SHIFT                                                         13
#define MSEC45_MASK                                                  0x00002000
#define MSEC45_RD(src)                               (((src) & 0x00002000)>>13)
#define MSEC45_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MSEC45_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MSEC44	 */
#define MSEC44_WIDTH                                                          1
#define MSEC44_SHIFT                                                         12
#define MSEC44_MASK                                                  0x00001000
#define MSEC44_RD(src)                               (((src) & 0x00001000)>>12)
#define MSEC44_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MSEC44_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MSEC43	 */
#define MSEC43_WIDTH                                                          1
#define MSEC43_SHIFT                                                         11
#define MSEC43_MASK                                                  0x00000800
#define MSEC43_RD(src)                               (((src) & 0x00000800)>>11)
#define MSEC43_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MSEC43_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MSEC42	 */
#define MSEC42_WIDTH                                                          1
#define MSEC42_SHIFT                                                         10
#define MSEC42_MASK                                                  0x00000400
#define MSEC42_RD(src)                               (((src) & 0x00000400)>>10)
#define MSEC42_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MSEC42_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MSEC41	 */
#define MSEC41_WIDTH                                                          1
#define MSEC41_SHIFT                                                          9
#define MSEC41_MASK                                                  0x00000200
#define MSEC41_RD(src)                                (((src) & 0x00000200)>>9)
#define MSEC41_WR(src)                           (((u32)(src)<<9) & 0x00000200)
#define MSEC41_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MSEC40	 */
#define MSEC40_WIDTH                                                          1
#define MSEC40_SHIFT                                                          8
#define MSEC40_MASK                                                  0x00000100
#define MSEC40_RD(src)                                (((src) & 0x00000100)>>8)
#define MSEC40_WR(src)                           (((u32)(src)<<8) & 0x00000100)
#define MSEC40_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MSEC39	 */
#define MSEC39_WIDTH                                                          1
#define MSEC39_SHIFT                                                          7
#define MSEC39_MASK                                                  0x00000080
#define MSEC39_RD(src)                                (((src) & 0x00000080)>>7)
#define MSEC39_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define MSEC39_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MSEC38	 */
#define MSEC38_WIDTH                                                          1
#define MSEC38_SHIFT                                                          6
#define MSEC38_MASK                                                  0x00000040
#define MSEC38_RD(src)                                (((src) & 0x00000040)>>6)
#define MSEC38_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define MSEC38_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MSEC37	 */
#define MSEC37_WIDTH                                                          1
#define MSEC37_SHIFT                                                          5
#define MSEC37_MASK                                                  0x00000020
#define MSEC37_RD(src)                                (((src) & 0x00000020)>>5)
#define MSEC37_WR(src)                           (((u32)(src)<<5) & 0x00000020)
#define MSEC37_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MSEC36	 */
#define MSEC36_WIDTH                                                          1
#define MSEC36_SHIFT                                                          4
#define MSEC36_MASK                                                  0x00000010
#define MSEC36_RD(src)                                (((src) & 0x00000010)>>4)
#define MSEC36_WR(src)                           (((u32)(src)<<4) & 0x00000010)
#define MSEC36_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MSEC35	 */
#define MSEC35_WIDTH                                                          1
#define MSEC35_SHIFT                                                          3
#define MSEC35_MASK                                                  0x00000008
#define MSEC35_RD(src)                                (((src) & 0x00000008)>>3)
#define MSEC35_WR(src)                           (((u32)(src)<<3) & 0x00000008)
#define MSEC35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MSEC34	 */
#define MSEC34_WIDTH                                                          1
#define MSEC34_SHIFT                                                          2
#define MSEC34_MASK                                                  0x00000004
#define MSEC34_RD(src)                                (((src) & 0x00000004)>>2)
#define MSEC34_WR(src)                           (((u32)(src)<<2) & 0x00000004)
#define MSEC34_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSEC33	 */
#define MSEC33_WIDTH                                                          1
#define MSEC33_SHIFT                                                          1
#define MSEC33_MASK                                                  0x00000002
#define MSEC33_RD(src)                                (((src) & 0x00000002)>>1)
#define MSEC33_WR(src)                           (((u32)(src)<<1) & 0x00000002)
#define MSEC33_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MSEC32	 */
#define MSEC32_WIDTH                                                          1
#define MSEC32_SHIFT                                                          0
#define MSEC32_MASK                                                  0x00000001
#define MSEC32_RD(src)                                   (((src) & 0x00000001))
#define MSEC32_WR(src)                              (((u32)(src)) & 0x00000001)
#define MSEC32_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRHMask	*/
/*    Mask Register Fields MSEC63Mask    */
#define MSEC63MASK_WIDTH                                                      1
#define MSEC63MASK_SHIFT                                                     31
#define MSEC63MASK_MASK                                              0x80000000
#define MSEC63MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MSEC63MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MSEC63MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MSEC62Mask    */
#define MSEC62MASK_WIDTH                                                      1
#define MSEC62MASK_SHIFT                                                     30
#define MSEC62MASK_MASK                                              0x40000000
#define MSEC62MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MSEC62MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MSEC62MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MSEC61Mask    */
#define MSEC61MASK_WIDTH                                                      1
#define MSEC61MASK_SHIFT                                                     29
#define MSEC61MASK_MASK                                              0x20000000
#define MSEC61MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MSEC61MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MSEC61MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MSEC60Mask    */
#define MSEC60MASK_WIDTH                                                      1
#define MSEC60MASK_SHIFT                                                     28
#define MSEC60MASK_MASK                                              0x10000000
#define MSEC60MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MSEC60MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MSEC60MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MSEC59Mask    */
#define MSEC59MASK_WIDTH                                                      1
#define MSEC59MASK_SHIFT                                                     27
#define MSEC59MASK_MASK                                              0x08000000
#define MSEC59MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MSEC59MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MSEC59MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MSEC58Mask    */
#define MSEC58MASK_WIDTH                                                      1
#define MSEC58MASK_SHIFT                                                     26
#define MSEC58MASK_MASK                                              0x04000000
#define MSEC58MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MSEC58MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MSEC58MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MSEC57Mask    */
#define MSEC57MASK_WIDTH                                                      1
#define MSEC57MASK_SHIFT                                                     25
#define MSEC57MASK_MASK                                              0x02000000
#define MSEC57MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MSEC57MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MSEC57MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MSEC56Mask    */
#define MSEC56MASK_WIDTH                                                      1
#define MSEC56MASK_SHIFT                                                     24
#define MSEC56MASK_MASK                                              0x01000000
#define MSEC56MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MSEC56MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MSEC56MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MSEC55Mask    */
#define MSEC55MASK_WIDTH                                                      1
#define MSEC55MASK_SHIFT                                                     23
#define MSEC55MASK_MASK                                              0x00800000
#define MSEC55MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MSEC55MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MSEC55MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MSEC54Mask    */
#define MSEC54MASK_WIDTH                                                      1
#define MSEC54MASK_SHIFT                                                     22
#define MSEC54MASK_MASK                                              0x00400000
#define MSEC54MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MSEC54MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MSEC54MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MSEC53Mask    */
#define MSEC53MASK_WIDTH                                                      1
#define MSEC53MASK_SHIFT                                                     21
#define MSEC53MASK_MASK                                              0x00200000
#define MSEC53MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MSEC53MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MSEC53MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MSEC52Mask    */
#define MSEC52MASK_WIDTH                                                      1
#define MSEC52MASK_SHIFT                                                     20
#define MSEC52MASK_MASK                                              0x00100000
#define MSEC52MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MSEC52MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MSEC52MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MSEC51Mask    */
#define MSEC51MASK_WIDTH                                                      1
#define MSEC51MASK_SHIFT                                                     19
#define MSEC51MASK_MASK                                              0x00080000
#define MSEC51MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MSEC51MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MSEC51MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MSEC50Mask    */
#define MSEC50MASK_WIDTH                                                      1
#define MSEC50MASK_SHIFT                                                     18
#define MSEC50MASK_MASK                                              0x00040000
#define MSEC50MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MSEC50MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MSEC50MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MSEC49Mask    */
#define MSEC49MASK_WIDTH                                                      1
#define MSEC49MASK_SHIFT                                                     17
#define MSEC49MASK_MASK                                              0x00020000
#define MSEC49MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MSEC49MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MSEC49MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MSEC48Mask    */
#define MSEC48MASK_WIDTH                                                      1
#define MSEC48MASK_SHIFT                                                     16
#define MSEC48MASK_MASK                                              0x00010000
#define MSEC48MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MSEC48MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MSEC48MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MSEC47Mask    */
#define MSEC47MASK_WIDTH                                                      1
#define MSEC47MASK_SHIFT                                                     15
#define MSEC47MASK_MASK                                              0x00008000
#define MSEC47MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MSEC47MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MSEC47MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MSEC46Mask    */
#define MSEC46MASK_WIDTH                                                      1
#define MSEC46MASK_SHIFT                                                     14
#define MSEC46MASK_MASK                                              0x00004000
#define MSEC46MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MSEC46MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MSEC46MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MSEC45Mask    */
#define MSEC45MASK_WIDTH                                                      1
#define MSEC45MASK_SHIFT                                                     13
#define MSEC45MASK_MASK                                              0x00002000
#define MSEC45MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MSEC45MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MSEC45MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MSEC44Mask    */
#define MSEC44MASK_WIDTH                                                      1
#define MSEC44MASK_SHIFT                                                     12
#define MSEC44MASK_MASK                                              0x00001000
#define MSEC44MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MSEC44MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MSEC44MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MSEC43Mask    */
#define MSEC43MASK_WIDTH                                                      1
#define MSEC43MASK_SHIFT                                                     11
#define MSEC43MASK_MASK                                              0x00000800
#define MSEC43MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MSEC43MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MSEC43MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MSEC42Mask    */
#define MSEC42MASK_WIDTH                                                      1
#define MSEC42MASK_SHIFT                                                     10
#define MSEC42MASK_MASK                                              0x00000400
#define MSEC42MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MSEC42MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MSEC42MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MSEC41Mask    */
#define MSEC41MASK_WIDTH                                                      1
#define MSEC41MASK_SHIFT                                                      9
#define MSEC41MASK_MASK                                              0x00000200
#define MSEC41MASK_RD(src)                            (((src) & 0x00000200)>>9)
#define MSEC41MASK_WR(src)                       (((u32)(src)<<9) & 0x00000200)
#define MSEC41MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MSEC40Mask    */
#define MSEC40MASK_WIDTH                                                      1
#define MSEC40MASK_SHIFT                                                      8
#define MSEC40MASK_MASK                                              0x00000100
#define MSEC40MASK_RD(src)                            (((src) & 0x00000100)>>8)
#define MSEC40MASK_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define MSEC40MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MSEC39Mask    */
#define MSEC39MASK_WIDTH                                                      1
#define MSEC39MASK_SHIFT                                                      7
#define MSEC39MASK_MASK                                              0x00000080
#define MSEC39MASK_RD(src)                            (((src) & 0x00000080)>>7)
#define MSEC39MASK_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define MSEC39MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MSEC38Mask    */
#define MSEC38MASK_WIDTH                                                      1
#define MSEC38MASK_SHIFT                                                      6
#define MSEC38MASK_MASK                                              0x00000040
#define MSEC38MASK_RD(src)                            (((src) & 0x00000040)>>6)
#define MSEC38MASK_WR(src)                       (((u32)(src)<<6) & 0x00000040)
#define MSEC38MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MSEC37Mask    */
#define MSEC37MASK_WIDTH                                                      1
#define MSEC37MASK_SHIFT                                                      5
#define MSEC37MASK_MASK                                              0x00000020
#define MSEC37MASK_RD(src)                            (((src) & 0x00000020)>>5)
#define MSEC37MASK_WR(src)                       (((u32)(src)<<5) & 0x00000020)
#define MSEC37MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MSEC36Mask    */
#define MSEC36MASK_WIDTH                                                      1
#define MSEC36MASK_SHIFT                                                      4
#define MSEC36MASK_MASK                                              0x00000010
#define MSEC36MASK_RD(src)                            (((src) & 0x00000010)>>4)
#define MSEC36MASK_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define MSEC36MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MSEC35Mask    */
#define MSEC35MASK_WIDTH                                                      1
#define MSEC35MASK_SHIFT                                                      3
#define MSEC35MASK_MASK                                              0x00000008
#define MSEC35MASK_RD(src)                            (((src) & 0x00000008)>>3)
#define MSEC35MASK_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define MSEC35MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MSEC34Mask    */
#define MSEC34MASK_WIDTH                                                      1
#define MSEC34MASK_SHIFT                                                      2
#define MSEC34MASK_MASK                                              0x00000004
#define MSEC34MASK_RD(src)                            (((src) & 0x00000004)>>2)
#define MSEC34MASK_WR(src)                       (((u32)(src)<<2) & 0x00000004)
#define MSEC34MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MSEC33Mask    */
#define MSEC33MASK_WIDTH                                                      1
#define MSEC33MASK_SHIFT                                                      1
#define MSEC33MASK_MASK                                              0x00000002
#define MSEC33MASK_RD(src)                            (((src) & 0x00000002)>>1)
#define MSEC33MASK_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define MSEC33MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MSEC32Mask    */
#define MSEC32MASK_WIDTH                                                      1
#define MSEC32MASK_SHIFT                                                      0
#define MSEC32MASK_MASK                                              0x00000001
#define MSEC32MASK_RD(src)                               (((src) & 0x00000001))
#define MSEC32MASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define MSEC32MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRL	*/
/*	 Fields DED31	 */
#define DED31_WIDTH                                                           1
#define DED31_SHIFT                                                          31
#define DED31_MASK                                                   0x80000000
#define DED31_RD(src)                                (((src) & 0x80000000)>>31)
#define DED31_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define DED31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields DED30	 */
#define DED30_WIDTH                                                           1
#define DED30_SHIFT                                                          30
#define DED30_MASK                                                   0x40000000
#define DED30_RD(src)                                (((src) & 0x40000000)>>30)
#define DED30_WR(src)                           (((u32)(src)<<30) & 0x40000000)
#define DED30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields DED29	 */
#define DED29_WIDTH                                                           1
#define DED29_SHIFT                                                          29
#define DED29_MASK                                                   0x20000000
#define DED29_RD(src)                                (((src) & 0x20000000)>>29)
#define DED29_WR(src)                           (((u32)(src)<<29) & 0x20000000)
#define DED29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields DED28	 */
#define DED28_WIDTH                                                           1
#define DED28_SHIFT                                                          28
#define DED28_MASK                                                   0x10000000
#define DED28_RD(src)                                (((src) & 0x10000000)>>28)
#define DED28_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define DED28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields DED27	 */
#define DED27_WIDTH                                                           1
#define DED27_SHIFT                                                          27
#define DED27_MASK                                                   0x08000000
#define DED27_RD(src)                                (((src) & 0x08000000)>>27)
#define DED27_WR(src)                           (((u32)(src)<<27) & 0x08000000)
#define DED27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields DED26	 */
#define DED26_WIDTH                                                           1
#define DED26_SHIFT                                                          26
#define DED26_MASK                                                   0x04000000
#define DED26_RD(src)                                (((src) & 0x04000000)>>26)
#define DED26_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define DED26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields DED25	 */
#define DED25_WIDTH                                                           1
#define DED25_SHIFT                                                          25
#define DED25_MASK                                                   0x02000000
#define DED25_RD(src)                                (((src) & 0x02000000)>>25)
#define DED25_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define DED25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields DED24	 */
#define DED24_WIDTH                                                           1
#define DED24_SHIFT                                                          24
#define DED24_MASK                                                   0x01000000
#define DED24_RD(src)                                (((src) & 0x01000000)>>24)
#define DED24_WR(src)                           (((u32)(src)<<24) & 0x01000000)
#define DED24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields DED23	 */
#define DED23_WIDTH                                                           1
#define DED23_SHIFT                                                          23
#define DED23_MASK                                                   0x00800000
#define DED23_RD(src)                                (((src) & 0x00800000)>>23)
#define DED23_WR(src)                           (((u32)(src)<<23) & 0x00800000)
#define DED23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields DED22	 */
#define DED22_WIDTH                                                           1
#define DED22_SHIFT                                                          22
#define DED22_MASK                                                   0x00400000
#define DED22_RD(src)                                (((src) & 0x00400000)>>22)
#define DED22_WR(src)                           (((u32)(src)<<22) & 0x00400000)
#define DED22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields DED21	 */
#define DED21_WIDTH                                                           1
#define DED21_SHIFT                                                          21
#define DED21_MASK                                                   0x00200000
#define DED21_RD(src)                                (((src) & 0x00200000)>>21)
#define DED21_WR(src)                           (((u32)(src)<<21) & 0x00200000)
#define DED21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields DED20	 */
#define DED20_WIDTH                                                           1
#define DED20_SHIFT                                                          20
#define DED20_MASK                                                   0x00100000
#define DED20_RD(src)                                (((src) & 0x00100000)>>20)
#define DED20_WR(src)                           (((u32)(src)<<20) & 0x00100000)
#define DED20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields DED19	 */
#define DED19_WIDTH                                                           1
#define DED19_SHIFT                                                          19
#define DED19_MASK                                                   0x00080000
#define DED19_RD(src)                                (((src) & 0x00080000)>>19)
#define DED19_WR(src)                           (((u32)(src)<<19) & 0x00080000)
#define DED19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields DED18	 */
#define DED18_WIDTH                                                           1
#define DED18_SHIFT                                                          18
#define DED18_MASK                                                   0x00040000
#define DED18_RD(src)                                (((src) & 0x00040000)>>18)
#define DED18_WR(src)                           (((u32)(src)<<18) & 0x00040000)
#define DED18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields DED17	 */
#define DED17_WIDTH                                                           1
#define DED17_SHIFT                                                          17
#define DED17_MASK                                                   0x00020000
#define DED17_RD(src)                                (((src) & 0x00020000)>>17)
#define DED17_WR(src)                           (((u32)(src)<<17) & 0x00020000)
#define DED17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields DED16	 */
#define DED16_WIDTH                                                           1
#define DED16_SHIFT                                                          16
#define DED16_MASK                                                   0x00010000
#define DED16_RD(src)                                (((src) & 0x00010000)>>16)
#define DED16_WR(src)                           (((u32)(src)<<16) & 0x00010000)
#define DED16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields DED15	 */
#define DED15_WIDTH                                                           1
#define DED15_SHIFT                                                          15
#define DED15_MASK                                                   0x00008000
#define DED15_RD(src)                                (((src) & 0x00008000)>>15)
#define DED15_WR(src)                           (((u32)(src)<<15) & 0x00008000)
#define DED15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields DED14	 */
#define DED14_WIDTH                                                           1
#define DED14_SHIFT                                                          14
#define DED14_MASK                                                   0x00004000
#define DED14_RD(src)                                (((src) & 0x00004000)>>14)
#define DED14_WR(src)                           (((u32)(src)<<14) & 0x00004000)
#define DED14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields DED13	 */
#define DED13_WIDTH                                                           1
#define DED13_SHIFT                                                          13
#define DED13_MASK                                                   0x00002000
#define DED13_RD(src)                                (((src) & 0x00002000)>>13)
#define DED13_WR(src)                           (((u32)(src)<<13) & 0x00002000)
#define DED13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields DED12	 */
#define DED12_WIDTH                                                           1
#define DED12_SHIFT                                                          12
#define DED12_MASK                                                   0x00001000
#define DED12_RD(src)                                (((src) & 0x00001000)>>12)
#define DED12_WR(src)                           (((u32)(src)<<12) & 0x00001000)
#define DED12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields DED11	 */
#define DED11_WIDTH                                                           1
#define DED11_SHIFT                                                          11
#define DED11_MASK                                                   0x00000800
#define DED11_RD(src)                                (((src) & 0x00000800)>>11)
#define DED11_WR(src)                           (((u32)(src)<<11) & 0x00000800)
#define DED11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields DED10	 */
#define DED10_WIDTH                                                           1
#define DED10_SHIFT                                                          10
#define DED10_MASK                                                   0x00000400
#define DED10_RD(src)                                (((src) & 0x00000400)>>10)
#define DED10_WR(src)                           (((u32)(src)<<10) & 0x00000400)
#define DED10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields DED9	 */
#define DED9_WIDTH                                                            1
#define DED9_SHIFT                                                            9
#define DED9_MASK                                                    0x00000200
#define DED9_RD(src)                                  (((src) & 0x00000200)>>9)
#define DED9_WR(src)                             (((u32)(src)<<9) & 0x00000200)
#define DED9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields DED8	 */
#define DED8_WIDTH                                                            1
#define DED8_SHIFT                                                            8
#define DED8_MASK                                                    0x00000100
#define DED8_RD(src)                                  (((src) & 0x00000100)>>8)
#define DED8_WR(src)                             (((u32)(src)<<8) & 0x00000100)
#define DED8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields DED7	 */
#define DED7_WIDTH                                                            1
#define DED7_SHIFT                                                            7
#define DED7_MASK                                                    0x00000080
#define DED7_RD(src)                                  (((src) & 0x00000080)>>7)
#define DED7_WR(src)                             (((u32)(src)<<7) & 0x00000080)
#define DED7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields DED6	 */
#define DED6_WIDTH                                                            1
#define DED6_SHIFT                                                            6
#define DED6_MASK                                                    0x00000040
#define DED6_RD(src)                                  (((src) & 0x00000040)>>6)
#define DED6_WR(src)                             (((u32)(src)<<6) & 0x00000040)
#define DED6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields DED5	 */
#define DED5_WIDTH                                                            1
#define DED5_SHIFT                                                            5
#define DED5_MASK                                                    0x00000020
#define DED5_RD(src)                                  (((src) & 0x00000020)>>5)
#define DED5_WR(src)                             (((u32)(src)<<5) & 0x00000020)
#define DED5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields DED4	 */
#define DED4_WIDTH                                                            1
#define DED4_SHIFT                                                            4
#define DED4_MASK                                                    0x00000010
#define DED4_RD(src)                                  (((src) & 0x00000010)>>4)
#define DED4_WR(src)                             (((u32)(src)<<4) & 0x00000010)
#define DED4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields DED3	 */
#define DED3_WIDTH                                                            1
#define DED3_SHIFT                                                            3
#define DED3_MASK                                                    0x00000008
#define DED3_RD(src)                                  (((src) & 0x00000008)>>3)
#define DED3_WR(src)                             (((u32)(src)<<3) & 0x00000008)
#define DED3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DED2	 */
#define DED2_WIDTH                                                            1
#define DED2_SHIFT                                                            2
#define DED2_MASK                                                    0x00000004
#define DED2_RD(src)                                  (((src) & 0x00000004)>>2)
#define DED2_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define DED2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DED1	 */
#define DED1_WIDTH                                                            1
#define DED1_SHIFT                                                            1
#define DED1_MASK                                                    0x00000002
#define DED1_RD(src)                                  (((src) & 0x00000002)>>1)
#define DED1_WR(src)                             (((u32)(src)<<1) & 0x00000002)
#define DED1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DED0	 */
#define DED0_WIDTH                                                            1
#define DED0_SHIFT                                                            0
#define DED0_MASK                                                    0x00000001
#define DED0_RD(src)                                     (((src) & 0x00000001))
#define DED0_WR(src)                                (((u32)(src)) & 0x00000001)
#define DED0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRLMask	*/
/*    Mask Register Fields DED31Mask    */
#define DED31MASK_WIDTH                                                       1
#define DED31MASK_SHIFT                                                      31
#define DED31MASK_MASK                                               0x80000000
#define DED31MASK_RD(src)                            (((src) & 0x80000000)>>31)
#define DED31MASK_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define DED31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields DED30Mask    */
#define DED30MASK_WIDTH                                                       1
#define DED30MASK_SHIFT                                                      30
#define DED30MASK_MASK                                               0x40000000
#define DED30MASK_RD(src)                            (((src) & 0x40000000)>>30)
#define DED30MASK_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define DED30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields DED29Mask    */
#define DED29MASK_WIDTH                                                       1
#define DED29MASK_SHIFT                                                      29
#define DED29MASK_MASK                                               0x20000000
#define DED29MASK_RD(src)                            (((src) & 0x20000000)>>29)
#define DED29MASK_WR(src)                       (((u32)(src)<<29) & 0x20000000)
#define DED29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields DED28Mask    */
#define DED28MASK_WIDTH                                                       1
#define DED28MASK_SHIFT                                                      28
#define DED28MASK_MASK                                               0x10000000
#define DED28MASK_RD(src)                            (((src) & 0x10000000)>>28)
#define DED28MASK_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define DED28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields DED27Mask    */
#define DED27MASK_WIDTH                                                       1
#define DED27MASK_SHIFT                                                      27
#define DED27MASK_MASK                                               0x08000000
#define DED27MASK_RD(src)                            (((src) & 0x08000000)>>27)
#define DED27MASK_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define DED27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields DED26Mask    */
#define DED26MASK_WIDTH                                                       1
#define DED26MASK_SHIFT                                                      26
#define DED26MASK_MASK                                               0x04000000
#define DED26MASK_RD(src)                            (((src) & 0x04000000)>>26)
#define DED26MASK_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define DED26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields DED25Mask    */
#define DED25MASK_WIDTH                                                       1
#define DED25MASK_SHIFT                                                      25
#define DED25MASK_MASK                                               0x02000000
#define DED25MASK_RD(src)                            (((src) & 0x02000000)>>25)
#define DED25MASK_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define DED25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields DED24Mask    */
#define DED24MASK_WIDTH                                                       1
#define DED24MASK_SHIFT                                                      24
#define DED24MASK_MASK                                               0x01000000
#define DED24MASK_RD(src)                            (((src) & 0x01000000)>>24)
#define DED24MASK_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define DED24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields DED23Mask    */
#define DED23MASK_WIDTH                                                       1
#define DED23MASK_SHIFT                                                      23
#define DED23MASK_MASK                                               0x00800000
#define DED23MASK_RD(src)                            (((src) & 0x00800000)>>23)
#define DED23MASK_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define DED23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields DED22Mask    */
#define DED22MASK_WIDTH                                                       1
#define DED22MASK_SHIFT                                                      22
#define DED22MASK_MASK                                               0x00400000
#define DED22MASK_RD(src)                            (((src) & 0x00400000)>>22)
#define DED22MASK_WR(src)                       (((u32)(src)<<22) & 0x00400000)
#define DED22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields DED21Mask    */
#define DED21MASK_WIDTH                                                       1
#define DED21MASK_SHIFT                                                      21
#define DED21MASK_MASK                                               0x00200000
#define DED21MASK_RD(src)                            (((src) & 0x00200000)>>21)
#define DED21MASK_WR(src)                       (((u32)(src)<<21) & 0x00200000)
#define DED21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields DED20Mask    */
#define DED20MASK_WIDTH                                                       1
#define DED20MASK_SHIFT                                                      20
#define DED20MASK_MASK                                               0x00100000
#define DED20MASK_RD(src)                            (((src) & 0x00100000)>>20)
#define DED20MASK_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define DED20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields DED19Mask    */
#define DED19MASK_WIDTH                                                       1
#define DED19MASK_SHIFT                                                      19
#define DED19MASK_MASK                                               0x00080000
#define DED19MASK_RD(src)                            (((src) & 0x00080000)>>19)
#define DED19MASK_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define DED19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields DED18Mask    */
#define DED18MASK_WIDTH                                                       1
#define DED18MASK_SHIFT                                                      18
#define DED18MASK_MASK                                               0x00040000
#define DED18MASK_RD(src)                            (((src) & 0x00040000)>>18)
#define DED18MASK_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define DED18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields DED17Mask    */
#define DED17MASK_WIDTH                                                       1
#define DED17MASK_SHIFT                                                      17
#define DED17MASK_MASK                                               0x00020000
#define DED17MASK_RD(src)                            (((src) & 0x00020000)>>17)
#define DED17MASK_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define DED17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields DED16Mask    */
#define DED16MASK_WIDTH                                                       1
#define DED16MASK_SHIFT                                                      16
#define DED16MASK_MASK                                               0x00010000
#define DED16MASK_RD(src)                            (((src) & 0x00010000)>>16)
#define DED16MASK_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define DED16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields DED15Mask    */
#define DED15MASK_WIDTH                                                       1
#define DED15MASK_SHIFT                                                      15
#define DED15MASK_MASK                                               0x00008000
#define DED15MASK_RD(src)                            (((src) & 0x00008000)>>15)
#define DED15MASK_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define DED15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields DED14Mask    */
#define DED14MASK_WIDTH                                                       1
#define DED14MASK_SHIFT                                                      14
#define DED14MASK_MASK                                               0x00004000
#define DED14MASK_RD(src)                            (((src) & 0x00004000)>>14)
#define DED14MASK_WR(src)                       (((u32)(src)<<14) & 0x00004000)
#define DED14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields DED13Mask    */
#define DED13MASK_WIDTH                                                       1
#define DED13MASK_SHIFT                                                      13
#define DED13MASK_MASK                                               0x00002000
#define DED13MASK_RD(src)                            (((src) & 0x00002000)>>13)
#define DED13MASK_WR(src)                       (((u32)(src)<<13) & 0x00002000)
#define DED13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields DED12Mask    */
#define DED12MASK_WIDTH                                                       1
#define DED12MASK_SHIFT                                                      12
#define DED12MASK_MASK                                               0x00001000
#define DED12MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define DED12MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define DED12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields DED11Mask    */
#define DED11MASK_WIDTH                                                       1
#define DED11MASK_SHIFT                                                      11
#define DED11MASK_MASK                                               0x00000800
#define DED11MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define DED11MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define DED11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields DED10Mask    */
#define DED10MASK_WIDTH                                                       1
#define DED10MASK_SHIFT                                                      10
#define DED10MASK_MASK                                               0x00000400
#define DED10MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define DED10MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define DED10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields DED9Mask    */
#define DED9MASK_WIDTH                                                        1
#define DED9MASK_SHIFT                                                        9
#define DED9MASK_MASK                                                0x00000200
#define DED9MASK_RD(src)                              (((src) & 0x00000200)>>9)
#define DED9MASK_WR(src)                         (((u32)(src)<<9) & 0x00000200)
#define DED9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields DED8Mask    */
#define DED8MASK_WIDTH                                                        1
#define DED8MASK_SHIFT                                                        8
#define DED8MASK_MASK                                                0x00000100
#define DED8MASK_RD(src)                              (((src) & 0x00000100)>>8)
#define DED8MASK_WR(src)                         (((u32)(src)<<8) & 0x00000100)
#define DED8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields DED7Mask    */
#define DED7MASK_WIDTH                                                        1
#define DED7MASK_SHIFT                                                        7
#define DED7MASK_MASK                                                0x00000080
#define DED7MASK_RD(src)                              (((src) & 0x00000080)>>7)
#define DED7MASK_WR(src)                         (((u32)(src)<<7) & 0x00000080)
#define DED7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields DED6Mask    */
#define DED6MASK_WIDTH                                                        1
#define DED6MASK_SHIFT                                                        6
#define DED6MASK_MASK                                                0x00000040
#define DED6MASK_RD(src)                              (((src) & 0x00000040)>>6)
#define DED6MASK_WR(src)                         (((u32)(src)<<6) & 0x00000040)
#define DED6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields DED5Mask    */
#define DED5MASK_WIDTH                                                        1
#define DED5MASK_SHIFT                                                        5
#define DED5MASK_MASK                                                0x00000020
#define DED5MASK_RD(src)                              (((src) & 0x00000020)>>5)
#define DED5MASK_WR(src)                         (((u32)(src)<<5) & 0x00000020)
#define DED5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields DED4Mask    */
#define DED4MASK_WIDTH                                                        1
#define DED4MASK_SHIFT                                                        4
#define DED4MASK_MASK                                                0x00000010
#define DED4MASK_RD(src)                              (((src) & 0x00000010)>>4)
#define DED4MASK_WR(src)                         (((u32)(src)<<4) & 0x00000010)
#define DED4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields DED3Mask    */
#define DED3MASK_WIDTH                                                        1
#define DED3MASK_SHIFT                                                        3
#define DED3MASK_MASK                                                0x00000008
#define DED3MASK_RD(src)                              (((src) & 0x00000008)>>3)
#define DED3MASK_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define DED3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields DED2Mask    */
#define DED2MASK_WIDTH                                                        1
#define DED2MASK_SHIFT                                                        2
#define DED2MASK_MASK                                                0x00000004
#define DED2MASK_RD(src)                              (((src) & 0x00000004)>>2)
#define DED2MASK_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define DED2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields DED1Mask    */
#define DED1MASK_WIDTH                                                        1
#define DED1MASK_SHIFT                                                        1
#define DED1MASK_MASK                                                0x00000002
#define DED1MASK_RD(src)                              (((src) & 0x00000002)>>1)
#define DED1MASK_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define DED1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields DED0Mask    */
#define DED0MASK_WIDTH                                                        1
#define DED0MASK_SHIFT                                                        0
#define DED0MASK_MASK                                                0x00000001
#define DED0MASK_RD(src)                                 (((src) & 0x00000001))
#define DED0MASK_WR(src)                            (((u32)(src)) & 0x00000001)
#define DED0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRH	*/
/*	 Fields DED63	 */
#define DED63_WIDTH                                                           1
#define DED63_SHIFT                                                          31
#define DED63_MASK                                                   0x80000000
#define DED63_RD(src)                                (((src) & 0x80000000)>>31)
#define DED63_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define DED63_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields DED62	 */
#define DED62_WIDTH                                                           1
#define DED62_SHIFT                                                          30
#define DED62_MASK                                                   0x40000000
#define DED62_RD(src)                                (((src) & 0x40000000)>>30)
#define DED62_WR(src)                           (((u32)(src)<<30) & 0x40000000)
#define DED62_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields DED61	 */
#define DED61_WIDTH                                                           1
#define DED61_SHIFT                                                          29
#define DED61_MASK                                                   0x20000000
#define DED61_RD(src)                                (((src) & 0x20000000)>>29)
#define DED61_WR(src)                           (((u32)(src)<<29) & 0x20000000)
#define DED61_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields DED60	 */
#define DED60_WIDTH                                                           1
#define DED60_SHIFT                                                          28
#define DED60_MASK                                                   0x10000000
#define DED60_RD(src)                                (((src) & 0x10000000)>>28)
#define DED60_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define DED60_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields DED59	 */
#define DED59_WIDTH                                                           1
#define DED59_SHIFT                                                          27
#define DED59_MASK                                                   0x08000000
#define DED59_RD(src)                                (((src) & 0x08000000)>>27)
#define DED59_WR(src)                           (((u32)(src)<<27) & 0x08000000)
#define DED59_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields DED58	 */
#define DED58_WIDTH                                                           1
#define DED58_SHIFT                                                          26
#define DED58_MASK                                                   0x04000000
#define DED58_RD(src)                                (((src) & 0x04000000)>>26)
#define DED58_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define DED58_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields DED57	 */
#define DED57_WIDTH                                                           1
#define DED57_SHIFT                                                          25
#define DED57_MASK                                                   0x02000000
#define DED57_RD(src)                                (((src) & 0x02000000)>>25)
#define DED57_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define DED57_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields DED56	 */
#define DED56_WIDTH                                                           1
#define DED56_SHIFT                                                          24
#define DED56_MASK                                                   0x01000000
#define DED56_RD(src)                                (((src) & 0x01000000)>>24)
#define DED56_WR(src)                           (((u32)(src)<<24) & 0x01000000)
#define DED56_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields DED55	 */
#define DED55_WIDTH                                                           1
#define DED55_SHIFT                                                          23
#define DED55_MASK                                                   0x00800000
#define DED55_RD(src)                                (((src) & 0x00800000)>>23)
#define DED55_WR(src)                           (((u32)(src)<<23) & 0x00800000)
#define DED55_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields DED54	 */
#define DED54_WIDTH                                                           1
#define DED54_SHIFT                                                          22
#define DED54_MASK                                                   0x00400000
#define DED54_RD(src)                                (((src) & 0x00400000)>>22)
#define DED54_WR(src)                           (((u32)(src)<<22) & 0x00400000)
#define DED54_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields DED53	 */
#define DED53_WIDTH                                                           1
#define DED53_SHIFT                                                          21
#define DED53_MASK                                                   0x00200000
#define DED53_RD(src)                                (((src) & 0x00200000)>>21)
#define DED53_WR(src)                           (((u32)(src)<<21) & 0x00200000)
#define DED53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields DED52	 */
#define DED52_WIDTH                                                           1
#define DED52_SHIFT                                                          20
#define DED52_MASK                                                   0x00100000
#define DED52_RD(src)                                (((src) & 0x00100000)>>20)
#define DED52_WR(src)                           (((u32)(src)<<20) & 0x00100000)
#define DED52_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields DED51	 */
#define DED51_WIDTH                                                           1
#define DED51_SHIFT                                                          19
#define DED51_MASK                                                   0x00080000
#define DED51_RD(src)                                (((src) & 0x00080000)>>19)
#define DED51_WR(src)                           (((u32)(src)<<19) & 0x00080000)
#define DED51_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields DED50	 */
#define DED50_WIDTH                                                           1
#define DED50_SHIFT                                                          18
#define DED50_MASK                                                   0x00040000
#define DED50_RD(src)                                (((src) & 0x00040000)>>18)
#define DED50_WR(src)                           (((u32)(src)<<18) & 0x00040000)
#define DED50_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields DED49	 */
#define DED49_WIDTH                                                           1
#define DED49_SHIFT                                                          17
#define DED49_MASK                                                   0x00020000
#define DED49_RD(src)                                (((src) & 0x00020000)>>17)
#define DED49_WR(src)                           (((u32)(src)<<17) & 0x00020000)
#define DED49_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields DED48	 */
#define DED48_WIDTH                                                           1
#define DED48_SHIFT                                                          16
#define DED48_MASK                                                   0x00010000
#define DED48_RD(src)                                (((src) & 0x00010000)>>16)
#define DED48_WR(src)                           (((u32)(src)<<16) & 0x00010000)
#define DED48_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields DED47	 */
#define DED47_WIDTH                                                           1
#define DED47_SHIFT                                                          15
#define DED47_MASK                                                   0x00008000
#define DED47_RD(src)                                (((src) & 0x00008000)>>15)
#define DED47_WR(src)                           (((u32)(src)<<15) & 0x00008000)
#define DED47_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields DED46	 */
#define DED46_WIDTH                                                           1
#define DED46_SHIFT                                                          14
#define DED46_MASK                                                   0x00004000
#define DED46_RD(src)                                (((src) & 0x00004000)>>14)
#define DED46_WR(src)                           (((u32)(src)<<14) & 0x00004000)
#define DED46_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields DED45	 */
#define DED45_WIDTH                                                           1
#define DED45_SHIFT                                                          13
#define DED45_MASK                                                   0x00002000
#define DED45_RD(src)                                (((src) & 0x00002000)>>13)
#define DED45_WR(src)                           (((u32)(src)<<13) & 0x00002000)
#define DED45_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields DED44	 */
#define DED44_WIDTH                                                           1
#define DED44_SHIFT                                                          12
#define DED44_MASK                                                   0x00001000
#define DED44_RD(src)                                (((src) & 0x00001000)>>12)
#define DED44_WR(src)                           (((u32)(src)<<12) & 0x00001000)
#define DED44_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields DED43	 */
#define DED43_WIDTH                                                           1
#define DED43_SHIFT                                                          11
#define DED43_MASK                                                   0x00000800
#define DED43_RD(src)                                (((src) & 0x00000800)>>11)
#define DED43_WR(src)                           (((u32)(src)<<11) & 0x00000800)
#define DED43_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields DED42	 */
#define DED42_WIDTH                                                           1
#define DED42_SHIFT                                                          10
#define DED42_MASK                                                   0x00000400
#define DED42_RD(src)                                (((src) & 0x00000400)>>10)
#define DED42_WR(src)                           (((u32)(src)<<10) & 0x00000400)
#define DED42_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields DED41	 */
#define DED41_WIDTH                                                           1
#define DED41_SHIFT                                                           9
#define DED41_MASK                                                   0x00000200
#define DED41_RD(src)                                 (((src) & 0x00000200)>>9)
#define DED41_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define DED41_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields DED40	 */
#define DED40_WIDTH                                                           1
#define DED40_SHIFT                                                           8
#define DED40_MASK                                                   0x00000100
#define DED40_RD(src)                                 (((src) & 0x00000100)>>8)
#define DED40_WR(src)                            (((u32)(src)<<8) & 0x00000100)
#define DED40_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields DED39	 */
#define DED39_WIDTH                                                           1
#define DED39_SHIFT                                                           7
#define DED39_MASK                                                   0x00000080
#define DED39_RD(src)                                 (((src) & 0x00000080)>>7)
#define DED39_WR(src)                            (((u32)(src)<<7) & 0x00000080)
#define DED39_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields DED38	 */
#define DED38_WIDTH                                                           1
#define DED38_SHIFT                                                           6
#define DED38_MASK                                                   0x00000040
#define DED38_RD(src)                                 (((src) & 0x00000040)>>6)
#define DED38_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define DED38_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields DED37	 */
#define DED37_WIDTH                                                           1
#define DED37_SHIFT                                                           5
#define DED37_MASK                                                   0x00000020
#define DED37_RD(src)                                 (((src) & 0x00000020)>>5)
#define DED37_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define DED37_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields DED36	 */
#define DED36_WIDTH                                                           1
#define DED36_SHIFT                                                           4
#define DED36_MASK                                                   0x00000010
#define DED36_RD(src)                                 (((src) & 0x00000010)>>4)
#define DED36_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define DED36_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields DED35	 */
#define DED35_WIDTH                                                           1
#define DED35_SHIFT                                                           3
#define DED35_MASK                                                   0x00000008
#define DED35_RD(src)                                 (((src) & 0x00000008)>>3)
#define DED35_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define DED35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DED34	 */
#define DED34_WIDTH                                                           1
#define DED34_SHIFT                                                           2
#define DED34_MASK                                                   0x00000004
#define DED34_RD(src)                                 (((src) & 0x00000004)>>2)
#define DED34_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define DED34_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DED33	 */
#define DED33_WIDTH                                                           1
#define DED33_SHIFT                                                           1
#define DED33_MASK                                                   0x00000002
#define DED33_RD(src)                                 (((src) & 0x00000002)>>1)
#define DED33_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define DED33_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DED32	 */
#define DED32_WIDTH                                                           1
#define DED32_SHIFT                                                           0
#define DED32_MASK                                                   0x00000001
#define DED32_RD(src)                                    (((src) & 0x00000001))
#define DED32_WR(src)                               (((u32)(src)) & 0x00000001)
#define DED32_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRHMask	*/
/*    Mask Register Fields DED63Mask    */
#define DED63MASK_WIDTH                                                       1
#define DED63MASK_SHIFT                                                      31
#define DED63MASK_MASK                                               0x80000000
#define DED63MASK_RD(src)                            (((src) & 0x80000000)>>31)
#define DED63MASK_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define DED63MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields DED62Mask    */
#define DED62MASK_WIDTH                                                       1
#define DED62MASK_SHIFT                                                      30
#define DED62MASK_MASK                                               0x40000000
#define DED62MASK_RD(src)                            (((src) & 0x40000000)>>30)
#define DED62MASK_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define DED62MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields DED61Mask    */
#define DED61MASK_WIDTH                                                       1
#define DED61MASK_SHIFT                                                      29
#define DED61MASK_MASK                                               0x20000000
#define DED61MASK_RD(src)                            (((src) & 0x20000000)>>29)
#define DED61MASK_WR(src)                       (((u32)(src)<<29) & 0x20000000)
#define DED61MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields DED60Mask    */
#define DED60MASK_WIDTH                                                       1
#define DED60MASK_SHIFT                                                      28
#define DED60MASK_MASK                                               0x10000000
#define DED60MASK_RD(src)                            (((src) & 0x10000000)>>28)
#define DED60MASK_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define DED60MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields DED59Mask    */
#define DED59MASK_WIDTH                                                       1
#define DED59MASK_SHIFT                                                      27
#define DED59MASK_MASK                                               0x08000000
#define DED59MASK_RD(src)                            (((src) & 0x08000000)>>27)
#define DED59MASK_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define DED59MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields DED58Mask    */
#define DED58MASK_WIDTH                                                       1
#define DED58MASK_SHIFT                                                      26
#define DED58MASK_MASK                                               0x04000000
#define DED58MASK_RD(src)                            (((src) & 0x04000000)>>26)
#define DED58MASK_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define DED58MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields DED57Mask    */
#define DED57MASK_WIDTH                                                       1
#define DED57MASK_SHIFT                                                      25
#define DED57MASK_MASK                                               0x02000000
#define DED57MASK_RD(src)                            (((src) & 0x02000000)>>25)
#define DED57MASK_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define DED57MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields DED56Mask    */
#define DED56MASK_WIDTH                                                       1
#define DED56MASK_SHIFT                                                      24
#define DED56MASK_MASK                                               0x01000000
#define DED56MASK_RD(src)                            (((src) & 0x01000000)>>24)
#define DED56MASK_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define DED56MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields DED55Mask    */
#define DED55MASK_WIDTH                                                       1
#define DED55MASK_SHIFT                                                      23
#define DED55MASK_MASK                                               0x00800000
#define DED55MASK_RD(src)                            (((src) & 0x00800000)>>23)
#define DED55MASK_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define DED55MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields DED54Mask    */
#define DED54MASK_WIDTH                                                       1
#define DED54MASK_SHIFT                                                      22
#define DED54MASK_MASK                                               0x00400000
#define DED54MASK_RD(src)                            (((src) & 0x00400000)>>22)
#define DED54MASK_WR(src)                       (((u32)(src)<<22) & 0x00400000)
#define DED54MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields DED53Mask    */
#define DED53MASK_WIDTH                                                       1
#define DED53MASK_SHIFT                                                      21
#define DED53MASK_MASK                                               0x00200000
#define DED53MASK_RD(src)                            (((src) & 0x00200000)>>21)
#define DED53MASK_WR(src)                       (((u32)(src)<<21) & 0x00200000)
#define DED53MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields DED52Mask    */
#define DED52MASK_WIDTH                                                       1
#define DED52MASK_SHIFT                                                      20
#define DED52MASK_MASK                                               0x00100000
#define DED52MASK_RD(src)                            (((src) & 0x00100000)>>20)
#define DED52MASK_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define DED52MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields DED51Mask    */
#define DED51MASK_WIDTH                                                       1
#define DED51MASK_SHIFT                                                      19
#define DED51MASK_MASK                                               0x00080000
#define DED51MASK_RD(src)                            (((src) & 0x00080000)>>19)
#define DED51MASK_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define DED51MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields DED50Mask    */
#define DED50MASK_WIDTH                                                       1
#define DED50MASK_SHIFT                                                      18
#define DED50MASK_MASK                                               0x00040000
#define DED50MASK_RD(src)                            (((src) & 0x00040000)>>18)
#define DED50MASK_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define DED50MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields DED49Mask    */
#define DED49MASK_WIDTH                                                       1
#define DED49MASK_SHIFT                                                      17
#define DED49MASK_MASK                                               0x00020000
#define DED49MASK_RD(src)                            (((src) & 0x00020000)>>17)
#define DED49MASK_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define DED49MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields DED48Mask    */
#define DED48MASK_WIDTH                                                       1
#define DED48MASK_SHIFT                                                      16
#define DED48MASK_MASK                                               0x00010000
#define DED48MASK_RD(src)                            (((src) & 0x00010000)>>16)
#define DED48MASK_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define DED48MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields DED47Mask    */
#define DED47MASK_WIDTH                                                       1
#define DED47MASK_SHIFT                                                      15
#define DED47MASK_MASK                                               0x00008000
#define DED47MASK_RD(src)                            (((src) & 0x00008000)>>15)
#define DED47MASK_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define DED47MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields DED46Mask    */
#define DED46MASK_WIDTH                                                       1
#define DED46MASK_SHIFT                                                      14
#define DED46MASK_MASK                                               0x00004000
#define DED46MASK_RD(src)                            (((src) & 0x00004000)>>14)
#define DED46MASK_WR(src)                       (((u32)(src)<<14) & 0x00004000)
#define DED46MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields DED45Mask    */
#define DED45MASK_WIDTH                                                       1
#define DED45MASK_SHIFT                                                      13
#define DED45MASK_MASK                                               0x00002000
#define DED45MASK_RD(src)                            (((src) & 0x00002000)>>13)
#define DED45MASK_WR(src)                       (((u32)(src)<<13) & 0x00002000)
#define DED45MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields DED44Mask    */
#define DED44MASK_WIDTH                                                       1
#define DED44MASK_SHIFT                                                      12
#define DED44MASK_MASK                                               0x00001000
#define DED44MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define DED44MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define DED44MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields DED43Mask    */
#define DED43MASK_WIDTH                                                       1
#define DED43MASK_SHIFT                                                      11
#define DED43MASK_MASK                                               0x00000800
#define DED43MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define DED43MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define DED43MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields DED42Mask    */
#define DED42MASK_WIDTH                                                       1
#define DED42MASK_SHIFT                                                      10
#define DED42MASK_MASK                                               0x00000400
#define DED42MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define DED42MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define DED42MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields DED41Mask    */
#define DED41MASK_WIDTH                                                       1
#define DED41MASK_SHIFT                                                       9
#define DED41MASK_MASK                                               0x00000200
#define DED41MASK_RD(src)                             (((src) & 0x00000200)>>9)
#define DED41MASK_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define DED41MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields DED40Mask    */
#define DED40MASK_WIDTH                                                       1
#define DED40MASK_SHIFT                                                       8
#define DED40MASK_MASK                                               0x00000100
#define DED40MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define DED40MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define DED40MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields DED39Mask    */
#define DED39MASK_WIDTH                                                       1
#define DED39MASK_SHIFT                                                       7
#define DED39MASK_MASK                                               0x00000080
#define DED39MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define DED39MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define DED39MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields DED38Mask    */
#define DED38MASK_WIDTH                                                       1
#define DED38MASK_SHIFT                                                       6
#define DED38MASK_MASK                                               0x00000040
#define DED38MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define DED38MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define DED38MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields DED37Mask    */
#define DED37MASK_WIDTH                                                       1
#define DED37MASK_SHIFT                                                       5
#define DED37MASK_MASK                                               0x00000020
#define DED37MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define DED37MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define DED37MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields DED36Mask    */
#define DED36MASK_WIDTH                                                       1
#define DED36MASK_SHIFT                                                       4
#define DED36MASK_MASK                                               0x00000010
#define DED36MASK_RD(src)                             (((src) & 0x00000010)>>4)
#define DED36MASK_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define DED36MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields DED35Mask    */
#define DED35MASK_WIDTH                                                       1
#define DED35MASK_SHIFT                                                       3
#define DED35MASK_MASK                                               0x00000008
#define DED35MASK_RD(src)                             (((src) & 0x00000008)>>3)
#define DED35MASK_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define DED35MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields DED34Mask    */
#define DED34MASK_WIDTH                                                       1
#define DED34MASK_SHIFT                                                       2
#define DED34MASK_MASK                                               0x00000004
#define DED34MASK_RD(src)                             (((src) & 0x00000004)>>2)
#define DED34MASK_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define DED34MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields DED33Mask    */
#define DED33MASK_WIDTH                                                       1
#define DED33MASK_SHIFT                                                       1
#define DED33MASK_MASK                                               0x00000002
#define DED33MASK_RD(src)                             (((src) & 0x00000002)>>1)
#define DED33MASK_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define DED33MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields DED32Mask    */
#define DED32MASK_WIDTH                                                       1
#define DED32MASK_SHIFT                                                       0
#define DED32MASK_MASK                                               0x00000001
#define DED32MASK_RD(src)                                (((src) & 0x00000001))
#define DED32MASK_WR(src)                           (((u32)(src)) & 0x00000001)
#define DED32MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRL	*/
/*	 Fields MDED31	 */
#define MDED31_WIDTH                                                          1
#define MDED31_SHIFT                                                         31
#define MDED31_MASK                                                  0x80000000
#define MDED31_RD(src)                               (((src) & 0x80000000)>>31)
#define MDED31_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MDED31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MDED30	 */
#define MDED30_WIDTH                                                          1
#define MDED30_SHIFT                                                         30
#define MDED30_MASK                                                  0x40000000
#define MDED30_RD(src)                               (((src) & 0x40000000)>>30)
#define MDED30_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MDED30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MDED29	 */
#define MDED29_WIDTH                                                          1
#define MDED29_SHIFT                                                         29
#define MDED29_MASK                                                  0x20000000
#define MDED29_RD(src)                               (((src) & 0x20000000)>>29)
#define MDED29_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MDED29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MDED28	 */
#define MDED28_WIDTH                                                          1
#define MDED28_SHIFT                                                         28
#define MDED28_MASK                                                  0x10000000
#define MDED28_RD(src)                               (((src) & 0x10000000)>>28)
#define MDED28_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MDED28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MDED27	 */
#define MDED27_WIDTH                                                          1
#define MDED27_SHIFT                                                         27
#define MDED27_MASK                                                  0x08000000
#define MDED27_RD(src)                               (((src) & 0x08000000)>>27)
#define MDED27_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MDED27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MDED26	 */
#define MDED26_WIDTH                                                          1
#define MDED26_SHIFT                                                         26
#define MDED26_MASK                                                  0x04000000
#define MDED26_RD(src)                               (((src) & 0x04000000)>>26)
#define MDED26_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MDED26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MDED25	 */
#define MDED25_WIDTH                                                          1
#define MDED25_SHIFT                                                         25
#define MDED25_MASK                                                  0x02000000
#define MDED25_RD(src)                               (((src) & 0x02000000)>>25)
#define MDED25_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MDED25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MDED24	 */
#define MDED24_WIDTH                                                          1
#define MDED24_SHIFT                                                         24
#define MDED24_MASK                                                  0x01000000
#define MDED24_RD(src)                               (((src) & 0x01000000)>>24)
#define MDED24_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MDED24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MDED23	 */
#define MDED23_WIDTH                                                          1
#define MDED23_SHIFT                                                         23
#define MDED23_MASK                                                  0x00800000
#define MDED23_RD(src)                               (((src) & 0x00800000)>>23)
#define MDED23_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MDED23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MDED22	 */
#define MDED22_WIDTH                                                          1
#define MDED22_SHIFT                                                         22
#define MDED22_MASK                                                  0x00400000
#define MDED22_RD(src)                               (((src) & 0x00400000)>>22)
#define MDED22_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MDED22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MDED21	 */
#define MDED21_WIDTH                                                          1
#define MDED21_SHIFT                                                         21
#define MDED21_MASK                                                  0x00200000
#define MDED21_RD(src)                               (((src) & 0x00200000)>>21)
#define MDED21_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MDED21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MDED20	 */
#define MDED20_WIDTH                                                          1
#define MDED20_SHIFT                                                         20
#define MDED20_MASK                                                  0x00100000
#define MDED20_RD(src)                               (((src) & 0x00100000)>>20)
#define MDED20_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MDED20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MDED19	 */
#define MDED19_WIDTH                                                          1
#define MDED19_SHIFT                                                         19
#define MDED19_MASK                                                  0x00080000
#define MDED19_RD(src)                               (((src) & 0x00080000)>>19)
#define MDED19_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MDED19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MDED18	 */
#define MDED18_WIDTH                                                          1
#define MDED18_SHIFT                                                         18
#define MDED18_MASK                                                  0x00040000
#define MDED18_RD(src)                               (((src) & 0x00040000)>>18)
#define MDED18_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MDED18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MDED17	 */
#define MDED17_WIDTH                                                          1
#define MDED17_SHIFT                                                         17
#define MDED17_MASK                                                  0x00020000
#define MDED17_RD(src)                               (((src) & 0x00020000)>>17)
#define MDED17_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MDED17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MDED16	 */
#define MDED16_WIDTH                                                          1
#define MDED16_SHIFT                                                         16
#define MDED16_MASK                                                  0x00010000
#define MDED16_RD(src)                               (((src) & 0x00010000)>>16)
#define MDED16_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MDED16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MDED15	 */
#define MDED15_WIDTH                                                          1
#define MDED15_SHIFT                                                         15
#define MDED15_MASK                                                  0x00008000
#define MDED15_RD(src)                               (((src) & 0x00008000)>>15)
#define MDED15_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MDED15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MDED14	 */
#define MDED14_WIDTH                                                          1
#define MDED14_SHIFT                                                         14
#define MDED14_MASK                                                  0x00004000
#define MDED14_RD(src)                               (((src) & 0x00004000)>>14)
#define MDED14_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MDED14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MDED13	 */
#define MDED13_WIDTH                                                          1
#define MDED13_SHIFT                                                         13
#define MDED13_MASK                                                  0x00002000
#define MDED13_RD(src)                               (((src) & 0x00002000)>>13)
#define MDED13_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MDED13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MDED12	 */
#define MDED12_WIDTH                                                          1
#define MDED12_SHIFT                                                         12
#define MDED12_MASK                                                  0x00001000
#define MDED12_RD(src)                               (((src) & 0x00001000)>>12)
#define MDED12_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MDED12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MDED11	 */
#define MDED11_WIDTH                                                          1
#define MDED11_SHIFT                                                         11
#define MDED11_MASK                                                  0x00000800
#define MDED11_RD(src)                               (((src) & 0x00000800)>>11)
#define MDED11_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MDED11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MDED10	 */
#define MDED10_WIDTH                                                          1
#define MDED10_SHIFT                                                         10
#define MDED10_MASK                                                  0x00000400
#define MDED10_RD(src)                               (((src) & 0x00000400)>>10)
#define MDED10_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MDED10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MDED9	 */
#define MDED9_WIDTH                                                           1
#define MDED9_SHIFT                                                           9
#define MDED9_MASK                                                   0x00000200
#define MDED9_RD(src)                                 (((src) & 0x00000200)>>9)
#define MDED9_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define MDED9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MDED8	 */
#define MDED8_WIDTH                                                           1
#define MDED8_SHIFT                                                           8
#define MDED8_MASK                                                   0x00000100
#define MDED8_RD(src)                                 (((src) & 0x00000100)>>8)
#define MDED8_WR(src)                            (((u32)(src)<<8) & 0x00000100)
#define MDED8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MDED7	 */
#define MDED7_WIDTH                                                           1
#define MDED7_SHIFT                                                           7
#define MDED7_MASK                                                   0x00000080
#define MDED7_RD(src)                                 (((src) & 0x00000080)>>7)
#define MDED7_WR(src)                            (((u32)(src)<<7) & 0x00000080)
#define MDED7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MDED6	 */
#define MDED6_WIDTH                                                           1
#define MDED6_SHIFT                                                           6
#define MDED6_MASK                                                   0x00000040
#define MDED6_RD(src)                                 (((src) & 0x00000040)>>6)
#define MDED6_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define MDED6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MDED5	 */
#define MDED5_WIDTH                                                           1
#define MDED5_SHIFT                                                           5
#define MDED5_MASK                                                   0x00000020
#define MDED5_RD(src)                                 (((src) & 0x00000020)>>5)
#define MDED5_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define MDED5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MDED4	 */
#define MDED4_WIDTH                                                           1
#define MDED4_SHIFT                                                           4
#define MDED4_MASK                                                   0x00000010
#define MDED4_RD(src)                                 (((src) & 0x00000010)>>4)
#define MDED4_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define MDED4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MDED3	 */
#define MDED3_WIDTH                                                           1
#define MDED3_SHIFT                                                           3
#define MDED3_MASK                                                   0x00000008
#define MDED3_RD(src)                                 (((src) & 0x00000008)>>3)
#define MDED3_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define MDED3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MDED2	 */
#define MDED2_WIDTH                                                           1
#define MDED2_SHIFT                                                           2
#define MDED2_MASK                                                   0x00000004
#define MDED2_RD(src)                                 (((src) & 0x00000004)>>2)
#define MDED2_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define MDED2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MDED1	 */
#define MDED1_WIDTH                                                           1
#define MDED1_SHIFT                                                           1
#define MDED1_MASK                                                   0x00000002
#define MDED1_RD(src)                                 (((src) & 0x00000002)>>1)
#define MDED1_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define MDED1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MDED0	 */
#define MDED0_WIDTH                                                           1
#define MDED0_SHIFT                                                           0
#define MDED0_MASK                                                   0x00000001
#define MDED0_RD(src)                                    (((src) & 0x00000001))
#define MDED0_WR(src)                               (((u32)(src)) & 0x00000001)
#define MDED0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRLMask	*/
/*    Mask Register Fields MDED31Mask    */
#define MDED31MASK_WIDTH                                                      1
#define MDED31MASK_SHIFT                                                     31
#define MDED31MASK_MASK                                              0x80000000
#define MDED31MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MDED31MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MDED31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MDED30Mask    */
#define MDED30MASK_WIDTH                                                      1
#define MDED30MASK_SHIFT                                                     30
#define MDED30MASK_MASK                                              0x40000000
#define MDED30MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MDED30MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MDED30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MDED29Mask    */
#define MDED29MASK_WIDTH                                                      1
#define MDED29MASK_SHIFT                                                     29
#define MDED29MASK_MASK                                              0x20000000
#define MDED29MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MDED29MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MDED29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MDED28Mask    */
#define MDED28MASK_WIDTH                                                      1
#define MDED28MASK_SHIFT                                                     28
#define MDED28MASK_MASK                                              0x10000000
#define MDED28MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MDED28MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MDED28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MDED27Mask    */
#define MDED27MASK_WIDTH                                                      1
#define MDED27MASK_SHIFT                                                     27
#define MDED27MASK_MASK                                              0x08000000
#define MDED27MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MDED27MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MDED27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MDED26Mask    */
#define MDED26MASK_WIDTH                                                      1
#define MDED26MASK_SHIFT                                                     26
#define MDED26MASK_MASK                                              0x04000000
#define MDED26MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MDED26MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MDED26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MDED25Mask    */
#define MDED25MASK_WIDTH                                                      1
#define MDED25MASK_SHIFT                                                     25
#define MDED25MASK_MASK                                              0x02000000
#define MDED25MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MDED25MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MDED25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MDED24Mask    */
#define MDED24MASK_WIDTH                                                      1
#define MDED24MASK_SHIFT                                                     24
#define MDED24MASK_MASK                                              0x01000000
#define MDED24MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MDED24MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MDED24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MDED23Mask    */
#define MDED23MASK_WIDTH                                                      1
#define MDED23MASK_SHIFT                                                     23
#define MDED23MASK_MASK                                              0x00800000
#define MDED23MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MDED23MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MDED23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MDED22Mask    */
#define MDED22MASK_WIDTH                                                      1
#define MDED22MASK_SHIFT                                                     22
#define MDED22MASK_MASK                                              0x00400000
#define MDED22MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MDED22MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MDED22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MDED21Mask    */
#define MDED21MASK_WIDTH                                                      1
#define MDED21MASK_SHIFT                                                     21
#define MDED21MASK_MASK                                              0x00200000
#define MDED21MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MDED21MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MDED21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MDED20Mask    */
#define MDED20MASK_WIDTH                                                      1
#define MDED20MASK_SHIFT                                                     20
#define MDED20MASK_MASK                                              0x00100000
#define MDED20MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MDED20MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MDED20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MDED19Mask    */
#define MDED19MASK_WIDTH                                                      1
#define MDED19MASK_SHIFT                                                     19
#define MDED19MASK_MASK                                              0x00080000
#define MDED19MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MDED19MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MDED19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MDED18Mask    */
#define MDED18MASK_WIDTH                                                      1
#define MDED18MASK_SHIFT                                                     18
#define MDED18MASK_MASK                                              0x00040000
#define MDED18MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MDED18MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MDED18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MDED17Mask    */
#define MDED17MASK_WIDTH                                                      1
#define MDED17MASK_SHIFT                                                     17
#define MDED17MASK_MASK                                              0x00020000
#define MDED17MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MDED17MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MDED17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MDED16Mask    */
#define MDED16MASK_WIDTH                                                      1
#define MDED16MASK_SHIFT                                                     16
#define MDED16MASK_MASK                                              0x00010000
#define MDED16MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MDED16MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MDED16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MDED15Mask    */
#define MDED15MASK_WIDTH                                                      1
#define MDED15MASK_SHIFT                                                     15
#define MDED15MASK_MASK                                              0x00008000
#define MDED15MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MDED15MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MDED15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MDED14Mask    */
#define MDED14MASK_WIDTH                                                      1
#define MDED14MASK_SHIFT                                                     14
#define MDED14MASK_MASK                                              0x00004000
#define MDED14MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MDED14MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MDED14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MDED13Mask    */
#define MDED13MASK_WIDTH                                                      1
#define MDED13MASK_SHIFT                                                     13
#define MDED13MASK_MASK                                              0x00002000
#define MDED13MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MDED13MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MDED13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MDED12Mask    */
#define MDED12MASK_WIDTH                                                      1
#define MDED12MASK_SHIFT                                                     12
#define MDED12MASK_MASK                                              0x00001000
#define MDED12MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MDED12MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MDED12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MDED11Mask    */
#define MDED11MASK_WIDTH                                                      1
#define MDED11MASK_SHIFT                                                     11
#define MDED11MASK_MASK                                              0x00000800
#define MDED11MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MDED11MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MDED11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MDED10Mask    */
#define MDED10MASK_WIDTH                                                      1
#define MDED10MASK_SHIFT                                                     10
#define MDED10MASK_MASK                                              0x00000400
#define MDED10MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MDED10MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MDED10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MDED9Mask    */
#define MDED9MASK_WIDTH                                                       1
#define MDED9MASK_SHIFT                                                       9
#define MDED9MASK_MASK                                               0x00000200
#define MDED9MASK_RD(src)                             (((src) & 0x00000200)>>9)
#define MDED9MASK_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define MDED9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MDED8Mask    */
#define MDED8MASK_WIDTH                                                       1
#define MDED8MASK_SHIFT                                                       8
#define MDED8MASK_MASK                                               0x00000100
#define MDED8MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define MDED8MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define MDED8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MDED7Mask    */
#define MDED7MASK_WIDTH                                                       1
#define MDED7MASK_SHIFT                                                       7
#define MDED7MASK_MASK                                               0x00000080
#define MDED7MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define MDED7MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define MDED7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MDED6Mask    */
#define MDED6MASK_WIDTH                                                       1
#define MDED6MASK_SHIFT                                                       6
#define MDED6MASK_MASK                                               0x00000040
#define MDED6MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define MDED6MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define MDED6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MDED5Mask    */
#define MDED5MASK_WIDTH                                                       1
#define MDED5MASK_SHIFT                                                       5
#define MDED5MASK_MASK                                               0x00000020
#define MDED5MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define MDED5MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define MDED5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MDED4Mask    */
#define MDED4MASK_WIDTH                                                       1
#define MDED4MASK_SHIFT                                                       4
#define MDED4MASK_MASK                                               0x00000010
#define MDED4MASK_RD(src)                             (((src) & 0x00000010)>>4)
#define MDED4MASK_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define MDED4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MDED3Mask    */
#define MDED3MASK_WIDTH                                                       1
#define MDED3MASK_SHIFT                                                       3
#define MDED3MASK_MASK                                               0x00000008
#define MDED3MASK_RD(src)                             (((src) & 0x00000008)>>3)
#define MDED3MASK_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define MDED3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MDED2Mask    */
#define MDED2MASK_WIDTH                                                       1
#define MDED2MASK_SHIFT                                                       2
#define MDED2MASK_MASK                                               0x00000004
#define MDED2MASK_RD(src)                             (((src) & 0x00000004)>>2)
#define MDED2MASK_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define MDED2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MDED1Mask    */
#define MDED1MASK_WIDTH                                                       1
#define MDED1MASK_SHIFT                                                       1
#define MDED1MASK_MASK                                               0x00000002
#define MDED1MASK_RD(src)                             (((src) & 0x00000002)>>1)
#define MDED1MASK_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define MDED1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MDED0Mask    */
#define MDED0MASK_WIDTH                                                       1
#define MDED0MASK_SHIFT                                                       0
#define MDED0MASK_MASK                                               0x00000001
#define MDED0MASK_RD(src)                                (((src) & 0x00000001))
#define MDED0MASK_WR(src)                           (((u32)(src)) & 0x00000001)
#define MDED0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRH	*/
/*	 Fields MDED63	 */
#define MDED63_WIDTH                                                          1
#define MDED63_SHIFT                                                         31
#define MDED63_MASK                                                  0x80000000
#define MDED63_RD(src)                               (((src) & 0x80000000)>>31)
#define MDED63_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MDED63_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MDED62	 */
#define MDED62_WIDTH                                                          1
#define MDED62_SHIFT                                                         30
#define MDED62_MASK                                                  0x40000000
#define MDED62_RD(src)                               (((src) & 0x40000000)>>30)
#define MDED62_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MDED62_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MDED61	 */
#define MDED61_WIDTH                                                          1
#define MDED61_SHIFT                                                         29
#define MDED61_MASK                                                  0x20000000
#define MDED61_RD(src)                               (((src) & 0x20000000)>>29)
#define MDED61_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MDED61_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MDED60	 */
#define MDED60_WIDTH                                                          1
#define MDED60_SHIFT                                                         28
#define MDED60_MASK                                                  0x10000000
#define MDED60_RD(src)                               (((src) & 0x10000000)>>28)
#define MDED60_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MDED60_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MDED59	 */
#define MDED59_WIDTH                                                          1
#define MDED59_SHIFT                                                         27
#define MDED59_MASK                                                  0x08000000
#define MDED59_RD(src)                               (((src) & 0x08000000)>>27)
#define MDED59_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MDED59_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MDED58	 */
#define MDED58_WIDTH                                                          1
#define MDED58_SHIFT                                                         26
#define MDED58_MASK                                                  0x04000000
#define MDED58_RD(src)                               (((src) & 0x04000000)>>26)
#define MDED58_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MDED58_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MDED57	 */
#define MDED57_WIDTH                                                          1
#define MDED57_SHIFT                                                         25
#define MDED57_MASK                                                  0x02000000
#define MDED57_RD(src)                               (((src) & 0x02000000)>>25)
#define MDED57_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MDED57_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MDED56	 */
#define MDED56_WIDTH                                                          1
#define MDED56_SHIFT                                                         24
#define MDED56_MASK                                                  0x01000000
#define MDED56_RD(src)                               (((src) & 0x01000000)>>24)
#define MDED56_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MDED56_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MDED55	 */
#define MDED55_WIDTH                                                          1
#define MDED55_SHIFT                                                         23
#define MDED55_MASK                                                  0x00800000
#define MDED55_RD(src)                               (((src) & 0x00800000)>>23)
#define MDED55_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MDED55_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MDED54	 */
#define MDED54_WIDTH                                                          1
#define MDED54_SHIFT                                                         22
#define MDED54_MASK                                                  0x00400000
#define MDED54_RD(src)                               (((src) & 0x00400000)>>22)
#define MDED54_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MDED54_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MDED53	 */
#define MDED53_WIDTH                                                          1
#define MDED53_SHIFT                                                         21
#define MDED53_MASK                                                  0x00200000
#define MDED53_RD(src)                               (((src) & 0x00200000)>>21)
#define MDED53_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MDED53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MDED52	 */
#define MDED52_WIDTH                                                          1
#define MDED52_SHIFT                                                         20
#define MDED52_MASK                                                  0x00100000
#define MDED52_RD(src)                               (((src) & 0x00100000)>>20)
#define MDED52_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MDED52_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MDED51	 */
#define MDED51_WIDTH                                                          1
#define MDED51_SHIFT                                                         19
#define MDED51_MASK                                                  0x00080000
#define MDED51_RD(src)                               (((src) & 0x00080000)>>19)
#define MDED51_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MDED51_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MDED50	 */
#define MDED50_WIDTH                                                          1
#define MDED50_SHIFT                                                         18
#define MDED50_MASK                                                  0x00040000
#define MDED50_RD(src)                               (((src) & 0x00040000)>>18)
#define MDED50_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MDED50_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MDED49	 */
#define MDED49_WIDTH                                                          1
#define MDED49_SHIFT                                                         17
#define MDED49_MASK                                                  0x00020000
#define MDED49_RD(src)                               (((src) & 0x00020000)>>17)
#define MDED49_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MDED49_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MDED48	 */
#define MDED48_WIDTH                                                          1
#define MDED48_SHIFT                                                         16
#define MDED48_MASK                                                  0x00010000
#define MDED48_RD(src)                               (((src) & 0x00010000)>>16)
#define MDED48_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MDED48_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MDED47	 */
#define MDED47_WIDTH                                                          1
#define MDED47_SHIFT                                                         15
#define MDED47_MASK                                                  0x00008000
#define MDED47_RD(src)                               (((src) & 0x00008000)>>15)
#define MDED47_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MDED47_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MDED46	 */
#define MDED46_WIDTH                                                          1
#define MDED46_SHIFT                                                         14
#define MDED46_MASK                                                  0x00004000
#define MDED46_RD(src)                               (((src) & 0x00004000)>>14)
#define MDED46_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MDED46_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MDED45	 */
#define MDED45_WIDTH                                                          1
#define MDED45_SHIFT                                                         13
#define MDED45_MASK                                                  0x00002000
#define MDED45_RD(src)                               (((src) & 0x00002000)>>13)
#define MDED45_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MDED45_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MDED44	 */
#define MDED44_WIDTH                                                          1
#define MDED44_SHIFT                                                         12
#define MDED44_MASK                                                  0x00001000
#define MDED44_RD(src)                               (((src) & 0x00001000)>>12)
#define MDED44_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MDED44_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MDED43	 */
#define MDED43_WIDTH                                                          1
#define MDED43_SHIFT                                                         11
#define MDED43_MASK                                                  0x00000800
#define MDED43_RD(src)                               (((src) & 0x00000800)>>11)
#define MDED43_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MDED43_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MDED42	 */
#define MDED42_WIDTH                                                          1
#define MDED42_SHIFT                                                         10
#define MDED42_MASK                                                  0x00000400
#define MDED42_RD(src)                               (((src) & 0x00000400)>>10)
#define MDED42_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MDED42_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MDED41	 */
#define MDED41_WIDTH                                                          1
#define MDED41_SHIFT                                                          9
#define MDED41_MASK                                                  0x00000200
#define MDED41_RD(src)                                (((src) & 0x00000200)>>9)
#define MDED41_WR(src)                           (((u32)(src)<<9) & 0x00000200)
#define MDED41_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MDED40	 */
#define MDED40_WIDTH                                                          1
#define MDED40_SHIFT                                                          8
#define MDED40_MASK                                                  0x00000100
#define MDED40_RD(src)                                (((src) & 0x00000100)>>8)
#define MDED40_WR(src)                           (((u32)(src)<<8) & 0x00000100)
#define MDED40_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MDED39	 */
#define MDED39_WIDTH                                                          1
#define MDED39_SHIFT                                                          7
#define MDED39_MASK                                                  0x00000080
#define MDED39_RD(src)                                (((src) & 0x00000080)>>7)
#define MDED39_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define MDED39_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MDED38	 */
#define MDED38_WIDTH                                                          1
#define MDED38_SHIFT                                                          6
#define MDED38_MASK                                                  0x00000040
#define MDED38_RD(src)                                (((src) & 0x00000040)>>6)
#define MDED38_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define MDED38_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MDED37	 */
#define MDED37_WIDTH                                                          1
#define MDED37_SHIFT                                                          5
#define MDED37_MASK                                                  0x00000020
#define MDED37_RD(src)                                (((src) & 0x00000020)>>5)
#define MDED37_WR(src)                           (((u32)(src)<<5) & 0x00000020)
#define MDED37_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MDED36	 */
#define MDED36_WIDTH                                                          1
#define MDED36_SHIFT                                                          4
#define MDED36_MASK                                                  0x00000010
#define MDED36_RD(src)                                (((src) & 0x00000010)>>4)
#define MDED36_WR(src)                           (((u32)(src)<<4) & 0x00000010)
#define MDED36_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MDED35	 */
#define MDED35_WIDTH                                                          1
#define MDED35_SHIFT                                                          3
#define MDED35_MASK                                                  0x00000008
#define MDED35_RD(src)                                (((src) & 0x00000008)>>3)
#define MDED35_WR(src)                           (((u32)(src)<<3) & 0x00000008)
#define MDED35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MDED34	 */
#define MDED34_WIDTH                                                          1
#define MDED34_SHIFT                                                          2
#define MDED34_MASK                                                  0x00000004
#define MDED34_RD(src)                                (((src) & 0x00000004)>>2)
#define MDED34_WR(src)                           (((u32)(src)<<2) & 0x00000004)
#define MDED34_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MDED33	 */
#define MDED33_WIDTH                                                          1
#define MDED33_SHIFT                                                          1
#define MDED33_MASK                                                  0x00000002
#define MDED33_RD(src)                                (((src) & 0x00000002)>>1)
#define MDED33_WR(src)                           (((u32)(src)<<1) & 0x00000002)
#define MDED33_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MDED32	 */
#define MDED32_WIDTH                                                          1
#define MDED32_SHIFT                                                          0
#define MDED32_MASK                                                  0x00000001
#define MDED32_RD(src)                                   (((src) & 0x00000001))
#define MDED32_WR(src)                              (((u32)(src)) & 0x00000001)
#define MDED32_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRHMask	*/
/*    Mask Register Fields MDED63Mask    */
#define MDED63MASK_WIDTH                                                      1
#define MDED63MASK_SHIFT                                                     31
#define MDED63MASK_MASK                                              0x80000000
#define MDED63MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MDED63MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MDED63MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MDED62Mask    */
#define MDED62MASK_WIDTH                                                      1
#define MDED62MASK_SHIFT                                                     30
#define MDED62MASK_MASK                                              0x40000000
#define MDED62MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MDED62MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MDED62MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MDED61Mask    */
#define MDED61MASK_WIDTH                                                      1
#define MDED61MASK_SHIFT                                                     29
#define MDED61MASK_MASK                                              0x20000000
#define MDED61MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MDED61MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MDED61MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MDED60Mask    */
#define MDED60MASK_WIDTH                                                      1
#define MDED60MASK_SHIFT                                                     28
#define MDED60MASK_MASK                                              0x10000000
#define MDED60MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MDED60MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MDED60MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MDED59Mask    */
#define MDED59MASK_WIDTH                                                      1
#define MDED59MASK_SHIFT                                                     27
#define MDED59MASK_MASK                                              0x08000000
#define MDED59MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MDED59MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MDED59MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MDED58Mask    */
#define MDED58MASK_WIDTH                                                      1
#define MDED58MASK_SHIFT                                                     26
#define MDED58MASK_MASK                                              0x04000000
#define MDED58MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MDED58MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MDED58MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MDED57Mask    */
#define MDED57MASK_WIDTH                                                      1
#define MDED57MASK_SHIFT                                                     25
#define MDED57MASK_MASK                                              0x02000000
#define MDED57MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MDED57MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MDED57MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MDED56Mask    */
#define MDED56MASK_WIDTH                                                      1
#define MDED56MASK_SHIFT                                                     24
#define MDED56MASK_MASK                                              0x01000000
#define MDED56MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MDED56MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MDED56MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MDED55Mask    */
#define MDED55MASK_WIDTH                                                      1
#define MDED55MASK_SHIFT                                                     23
#define MDED55MASK_MASK                                              0x00800000
#define MDED55MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MDED55MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MDED55MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MDED54Mask    */
#define MDED54MASK_WIDTH                                                      1
#define MDED54MASK_SHIFT                                                     22
#define MDED54MASK_MASK                                              0x00400000
#define MDED54MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MDED54MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MDED54MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MDED53Mask    */
#define MDED53MASK_WIDTH                                                      1
#define MDED53MASK_SHIFT                                                     21
#define MDED53MASK_MASK                                              0x00200000
#define MDED53MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MDED53MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MDED53MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MDED52Mask    */
#define MDED52MASK_WIDTH                                                      1
#define MDED52MASK_SHIFT                                                     20
#define MDED52MASK_MASK                                              0x00100000
#define MDED52MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MDED52MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MDED52MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MDED51Mask    */
#define MDED51MASK_WIDTH                                                      1
#define MDED51MASK_SHIFT                                                     19
#define MDED51MASK_MASK                                              0x00080000
#define MDED51MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MDED51MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MDED51MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MDED50Mask    */
#define MDED50MASK_WIDTH                                                      1
#define MDED50MASK_SHIFT                                                     18
#define MDED50MASK_MASK                                              0x00040000
#define MDED50MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MDED50MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MDED50MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MDED49Mask    */
#define MDED49MASK_WIDTH                                                      1
#define MDED49MASK_SHIFT                                                     17
#define MDED49MASK_MASK                                              0x00020000
#define MDED49MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MDED49MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MDED49MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MDED48Mask    */
#define MDED48MASK_WIDTH                                                      1
#define MDED48MASK_SHIFT                                                     16
#define MDED48MASK_MASK                                              0x00010000
#define MDED48MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MDED48MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MDED48MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MDED47Mask    */
#define MDED47MASK_WIDTH                                                      1
#define MDED47MASK_SHIFT                                                     15
#define MDED47MASK_MASK                                              0x00008000
#define MDED47MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MDED47MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MDED47MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MDED46Mask    */
#define MDED46MASK_WIDTH                                                      1
#define MDED46MASK_SHIFT                                                     14
#define MDED46MASK_MASK                                              0x00004000
#define MDED46MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MDED46MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MDED46MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MDED45Mask    */
#define MDED45MASK_WIDTH                                                      1
#define MDED45MASK_SHIFT                                                     13
#define MDED45MASK_MASK                                              0x00002000
#define MDED45MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MDED45MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MDED45MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MDED44Mask    */
#define MDED44MASK_WIDTH                                                      1
#define MDED44MASK_SHIFT                                                     12
#define MDED44MASK_MASK                                              0x00001000
#define MDED44MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MDED44MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MDED44MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MDED43Mask    */
#define MDED43MASK_WIDTH                                                      1
#define MDED43MASK_SHIFT                                                     11
#define MDED43MASK_MASK                                              0x00000800
#define MDED43MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MDED43MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MDED43MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MDED42Mask    */
#define MDED42MASK_WIDTH                                                      1
#define MDED42MASK_SHIFT                                                     10
#define MDED42MASK_MASK                                              0x00000400
#define MDED42MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MDED42MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MDED42MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MDED41Mask    */
#define MDED41MASK_WIDTH                                                      1
#define MDED41MASK_SHIFT                                                      9
#define MDED41MASK_MASK                                              0x00000200
#define MDED41MASK_RD(src)                            (((src) & 0x00000200)>>9)
#define MDED41MASK_WR(src)                       (((u32)(src)<<9) & 0x00000200)
#define MDED41MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MDED40Mask    */
#define MDED40MASK_WIDTH                                                      1
#define MDED40MASK_SHIFT                                                      8
#define MDED40MASK_MASK                                              0x00000100
#define MDED40MASK_RD(src)                            (((src) & 0x00000100)>>8)
#define MDED40MASK_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define MDED40MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MDED39Mask    */
#define MDED39MASK_WIDTH                                                      1
#define MDED39MASK_SHIFT                                                      7
#define MDED39MASK_MASK                                              0x00000080
#define MDED39MASK_RD(src)                            (((src) & 0x00000080)>>7)
#define MDED39MASK_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define MDED39MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MDED38Mask    */
#define MDED38MASK_WIDTH                                                      1
#define MDED38MASK_SHIFT                                                      6
#define MDED38MASK_MASK                                              0x00000040
#define MDED38MASK_RD(src)                            (((src) & 0x00000040)>>6)
#define MDED38MASK_WR(src)                       (((u32)(src)<<6) & 0x00000040)
#define MDED38MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MDED37Mask    */
#define MDED37MASK_WIDTH                                                      1
#define MDED37MASK_SHIFT                                                      5
#define MDED37MASK_MASK                                              0x00000020
#define MDED37MASK_RD(src)                            (((src) & 0x00000020)>>5)
#define MDED37MASK_WR(src)                       (((u32)(src)<<5) & 0x00000020)
#define MDED37MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MDED36Mask    */
#define MDED36MASK_WIDTH                                                      1
#define MDED36MASK_SHIFT                                                      4
#define MDED36MASK_MASK                                              0x00000010
#define MDED36MASK_RD(src)                            (((src) & 0x00000010)>>4)
#define MDED36MASK_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define MDED36MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MDED35Mask    */
#define MDED35MASK_WIDTH                                                      1
#define MDED35MASK_SHIFT                                                      3
#define MDED35MASK_MASK                                              0x00000008
#define MDED35MASK_RD(src)                            (((src) & 0x00000008)>>3)
#define MDED35MASK_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define MDED35MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MDED34Mask    */
#define MDED34MASK_WIDTH                                                      1
#define MDED34MASK_SHIFT                                                      2
#define MDED34MASK_MASK                                              0x00000004
#define MDED34MASK_RD(src)                            (((src) & 0x00000004)>>2)
#define MDED34MASK_WR(src)                       (((u32)(src)<<2) & 0x00000004)
#define MDED34MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MDED33Mask    */
#define MDED33MASK_WIDTH                                                      1
#define MDED33MASK_SHIFT                                                      1
#define MDED33MASK_MASK                                              0x00000002
#define MDED33MASK_RD(src)                            (((src) & 0x00000002)>>1)
#define MDED33MASK_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define MDED33MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MDED32Mask    */
#define MDED32MASK_WIDTH                                                      1
#define MDED32MASK_SHIFT                                                      0
#define MDED32MASK_MASK                                              0x00000001
#define MDED32MASK_RD(src)                               (((src) & 0x00000001))
#define MDED32MASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define MDED32MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MERR_ADDR	*/
/*	 Fields ERRADDRL	 */
#define ERRADDRL_WIDTH                                                       32
#define ERRADDRL_SHIFT                                                        0
#define ERRADDRL_MASK                                                0xffffffff
#define ERRADDRL_RD(src)                                 (((src) & 0xffffffff))
#define ERRADDRL_WR(src)                            (((u32)(src)) & 0xffffffff)
#define ERRADDRL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_MERR_REQINFO	*/
/*	 Fields ERRADDRH	 */
#define ERRADDRH_WIDTH                                                       10
#define ERRADDRH_SHIFT                                                       22
#define ERRADDRH_MASK                                                0xffc00000
#define ERRADDRH_RD(src)                             (((src) & 0xffc00000)>>22)
#define ERRADDRH_WR(src)                        (((u32)(src)<<22) & 0xffc00000)
#define ERRADDRH_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields MSTRID	 */
#define MSTRID_WIDTH                                                          6
#define MSTRID_SHIFT                                                         16
#define MSTRID_MASK                                                  0x003f0000
#define MSTRID_RD(src)                               (((src) & 0x003f0000)>>16)
#define MSTRID_WR(src)                          (((u32)(src)<<16) & 0x003f0000)
#define MSTRID_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields AUXINFO	 */
#define AUXINFO_WIDTH                                                         6
#define AUXINFO_SHIFT                                                        10
#define AUXINFO_MASK                                                 0x0000fc00
#define AUXINFO_RD(src)                              (((src) & 0x0000fc00)>>10)
#define AUXINFO_WR(src)                         (((u32)(src)<<10) & 0x0000fc00)
#define AUXINFO_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields REQLEN	 */
#define REQLEN_WIDTH                                                          2
#define REQLEN_SHIFT                                                          4
#define REQLEN_MASK                                                  0x00000030
#define REQLEN_RD(src)                                (((src) & 0x00000030)>>4)
#define REQLEN_WR(src)                           (((u32)(src)<<4) & 0x00000030)
#define REQLEN_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields REQSIZE	 */
#define REQSIZE_WIDTH                                                         3
#define REQSIZE_SHIFT                                                         1
#define REQSIZE_MASK                                                 0x0000000e
#define REQSIZE_RD(src)                               (((src) & 0x0000000e)>>1)
#define REQSIZE_WR(src)                          (((u32)(src)<<1) & 0x0000000e)
#define REQSIZE_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields REQTYPE	 */
#define REQTYPE_WIDTH                                                         1
#define REQTYPE_SHIFT                                                         0
#define REQTYPE_MASK                                                 0x00000001
#define REQTYPE_RD(src)                                  (((src) & 0x00000001))
#define REQTYPE_WR(src)                             (((u32)(src)) & 0x00000001)
#define REQTYPE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_TRANS_ERR	*/
/*	 Fields MSWRPOISON	 */
#define MSWRPOISON_WIDTH                                                      1
#define MSWRPOISON_SHIFT                                                     12
#define MSWRPOISON_MASK                                              0x00001000
#define MSWRPOISON_RD(src)                           (((src) & 0x00001000)>>12)
#define MSWRPOISON_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MSWRPOISON_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SWRPOISON	 */
#define SWRPOISON_WIDTH                                                       1
#define SWRPOISON_SHIFT                                                      11
#define SWRPOISON_MASK                                               0x00000800
#define SWRPOISON_RD(src)                            (((src) & 0x00000800)>>11)
#define SWRPOISON_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define SWRPOISON_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SWRDYTMO	 */
#define SWRDYTMO_WIDTH                                                        1
#define SWRDYTMO_SHIFT                                                       10
#define SWRDYTMO_MASK                                                0x00000400
#define SWRDYTMO_RD(src)                             (((src) & 0x00000400)>>10)
#define SWRDYTMO_WR(src)                        (((u32)(src)<<10) & 0x00000400)
#define SWRDYTMO_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SWRESPTMO	 */
#define SWRESPTMO_WIDTH                                                       1
#define SWRESPTMO_SHIFT                                                       9
#define SWRESPTMO_MASK                                               0x00000200
#define SWRESPTMO_RD(src)                             (((src) & 0x00000200)>>9)
#define SWRESPTMO_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define SWRESPTMO_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MSWRERR	 */
#define MSWRERR_WIDTH                                                         1
#define MSWRERR_SHIFT                                                         8
#define MSWRERR_MASK                                                 0x00000100
#define MSWRERR_RD(src)                               (((src) & 0x00000100)>>8)
#define MSWRERR_WR(src)                          (((u32)(src)<<8) & 0x00000100)
#define MSWRERR_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SWRERR	 */
#define SWRERR_WIDTH                                                          1
#define SWRERR_SHIFT                                                          7
#define SWRERR_MASK                                                  0x00000080
#define SWRERR_RD(src)                                (((src) & 0x00000080)>>7)
#define SWRERR_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define SWRERR_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SRRDYTMO	 */
#define SRRDYTMO_WIDTH                                                        1
#define SRRDYTMO_SHIFT                                                        3
#define SRRDYTMO_MASK                                                0x00000008
#define SRRDYTMO_RD(src)                              (((src) & 0x00000008)>>3)
#define SRRDYTMO_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define SRRDYTMO_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SRRESPTMO	 */
#define SRRESPTMO_WIDTH                                                       1
#define SRRESPTMO_SHIFT                                                       2
#define SRRESPTMO_MASK                                               0x00000004
#define SRRESPTMO_RD(src)                             (((src) & 0x00000004)>>2)
#define SRRESPTMO_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define SRRESPTMO_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSRDERR	 */
#define MSRDERR_WIDTH                                                         1
#define MSRDERR_SHIFT                                                         1
#define MSRDERR_MASK                                                 0x00000002
#define MSRDERR_RD(src)                               (((src) & 0x00000002)>>1)
#define MSRDERR_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define MSRDERR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SRDERR	 */
#define SRDERR_WIDTH                                                          1
#define SRDERR_SHIFT                                                          0
#define SRDERR_MASK                                                  0x00000001
#define SRDERR_RD(src)                                   (((src) & 0x00000001))
#define SRDERR_WR(src)                              (((u32)(src)) & 0x00000001)
#define SRDERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_TRANS_ERRMask	*/
/*    Mask Register Fields MSWRPOISONMask    */
#define MSWRPOISONMASK_WIDTH                                                  1
#define MSWRPOISONMASK_SHIFT                                                 12
#define MSWRPOISONMASK_MASK                                          0x00001000
#define MSWRPOISONMASK_RD(src)                       (((src) & 0x00001000)>>12)
#define MSWRPOISONMASK_WR(src)                  (((u32)(src)<<12) & 0x00001000)
#define MSWRPOISONMASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SWRPOISONMask    */
#define SWRPOISONMASK_WIDTH                                                   1
#define SWRPOISONMASK_SHIFT                                                  11
#define SWRPOISONMASK_MASK                                           0x00000800
#define SWRPOISONMASK_RD(src)                        (((src) & 0x00000800)>>11)
#define SWRPOISONMASK_WR(src)                   (((u32)(src)<<11) & 0x00000800)
#define SWRPOISONMASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SWRDYTMOMask    */
#define SWRDYTMOMASK_WIDTH                                                    1
#define SWRDYTMOMASK_SHIFT                                                   10
#define SWRDYTMOMASK_MASK                                            0x00000400
#define SWRDYTMOMASK_RD(src)                         (((src) & 0x00000400)>>10)
#define SWRDYTMOMASK_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define SWRDYTMOMASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SWRESPTMOMask    */
#define SWRESPTMOMASK_WIDTH                                                   1
#define SWRESPTMOMASK_SHIFT                                                   9
#define SWRESPTMOMASK_MASK                                           0x00000200
#define SWRESPTMOMASK_RD(src)                         (((src) & 0x00000200)>>9)
#define SWRESPTMOMASK_WR(src)                    (((u32)(src)<<9) & 0x00000200)
#define SWRESPTMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MSWRERRMask    */
#define MSWRERRMASK_WIDTH                                                     1
#define MSWRERRMASK_SHIFT                                                     8
#define MSWRERRMASK_MASK                                             0x00000100
#define MSWRERRMASK_RD(src)                           (((src) & 0x00000100)>>8)
#define MSWRERRMASK_WR(src)                      (((u32)(src)<<8) & 0x00000100)
#define MSWRERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields SWRERRMask    */
#define SWRERRMASK_WIDTH                                                      1
#define SWRERRMASK_SHIFT                                                      7
#define SWRERRMASK_MASK                                              0x00000080
#define SWRERRMASK_RD(src)                            (((src) & 0x00000080)>>7)
#define SWRERRMASK_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define SWRERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields SRRDYTMOMask    */
#define SRRDYTMOMASK_WIDTH                                                    1
#define SRRDYTMOMASK_SHIFT                                                    3
#define SRRDYTMOMASK_MASK                                            0x00000008
#define SRRDYTMOMASK_RD(src)                          (((src) & 0x00000008)>>3)
#define SRRDYTMOMASK_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define SRRDYTMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields SRRESPTMOMask    */
#define SRRESPTMOMASK_WIDTH                                                   1
#define SRRESPTMOMASK_SHIFT                                                   2
#define SRRESPTMOMASK_MASK                                           0x00000004
#define SRRESPTMOMASK_RD(src)                         (((src) & 0x00000004)>>2)
#define SRRESPTMOMASK_WR(src)                    (((u32)(src)<<2) & 0x00000004)
#define SRRESPTMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MSRDERRMask    */
#define MSRDERRMASK_WIDTH                                                     1
#define MSRDERRMASK_SHIFT                                                     1
#define MSRDERRMASK_MASK                                             0x00000002
#define MSRDERRMASK_RD(src)                           (((src) & 0x00000002)>>1)
#define MSRDERRMASK_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define MSRDERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SRDERRMask    */
#define SRDERRMASK_WIDTH                                                      1
#define SRDERRMASK_SHIFT                                                      0
#define SRDERRMASK_MASK                                              0x00000001
#define SRDERRMASK_RD(src)                               (((src) & 0x00000001))
#define SRDERRMASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define SRDERRMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_WDERR_ADDR	*/
/*	 Fields ERRADDRL	 */
#define ERRADDRL_F1_WIDTH                                                    32
#define ERRADDRL_F1_SHIFT                                                     0
#define ERRADDRL_F1_MASK                                             0xffffffff
#define ERRADDRL_F1_RD(src)                              (((src) & 0xffffffff))
#define ERRADDRL_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define ERRADDRL_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_WDERR_REQINFO	*/
/*	 Fields ERRADDRH	 */
#define ERRADDRH_F1_WIDTH                                                    10
#define ERRADDRH_F1_SHIFT                                                    22
#define ERRADDRH_F1_MASK                                             0xffc00000
#define ERRADDRH_F1_RD(src)                          (((src) & 0xffc00000)>>22)
#define ERRADDRH_F1_WR(src)                     (((u32)(src)<<22) & 0xffc00000)
#define ERRADDRH_F1_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields MSTRID	 */
#define MSTRID_F1_WIDTH                                                       6
#define MSTRID_F1_SHIFT                                                      16
#define MSTRID_F1_MASK                                               0x003f0000
#define MSTRID_F1_RD(src)                            (((src) & 0x003f0000)>>16)
#define MSTRID_F1_WR(src)                       (((u32)(src)<<16) & 0x003f0000)
#define MSTRID_F1_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields AUXINFO	 */
#define AUXINFO_F1_WIDTH                                                      6
#define AUXINFO_F1_SHIFT                                                     10
#define AUXINFO_F1_MASK                                              0x0000fc00
#define AUXINFO_F1_RD(src)                           (((src) & 0x0000fc00)>>10)
#define AUXINFO_F1_WR(src)                      (((u32)(src)<<10) & 0x0000fc00)
#define AUXINFO_F1_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields REQLEN	 */
#define REQLEN_F1_WIDTH                                                       2
#define REQLEN_F1_SHIFT                                                       4
#define REQLEN_F1_MASK                                               0x00000030
#define REQLEN_F1_RD(src)                             (((src) & 0x00000030)>>4)
#define REQLEN_F1_WR(src)                        (((u32)(src)<<4) & 0x00000030)
#define REQLEN_F1_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields REQSIZE	 */
#define REQSIZE_F1_WIDTH                                                      3
#define REQSIZE_F1_SHIFT                                                      1
#define REQSIZE_F1_MASK                                              0x0000000e
#define REQSIZE_F1_RD(src)                            (((src) & 0x0000000e)>>1)
#define REQSIZE_F1_WR(src)                       (((u32)(src)<<1) & 0x0000000e)
#define REQSIZE_F1_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))

/*	Register GLBL_DEVERR_ADDR	*/
/*	 Fields ERRADDRL	 */
#define ERRADDRL_F2_WIDTH                                                    32
#define ERRADDRL_F2_SHIFT                                                     0
#define ERRADDRL_F2_MASK                                             0xffffffff
#define ERRADDRL_F2_RD(src)                              (((src) & 0xffffffff))
#define ERRADDRL_F2_WR(src)                         (((u32)(src)) & 0xffffffff)
#define ERRADDRL_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_DEVERR_REQINFO	*/
/*	 Fields ERRADDRH	 */
#define ERRADDRH_F2_WIDTH                                                    10
#define ERRADDRH_F2_SHIFT                                                    22
#define ERRADDRH_F2_MASK                                             0xffc00000
#define ERRADDRH_F2_RD(src)                          (((src) & 0xffc00000)>>22)
#define ERRADDRH_F2_WR(src)                     (((u32)(src)<<22) & 0xffc00000)
#define ERRADDRH_F2_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields MSTRID	 */
#define MSTRID_F2_WIDTH                                                       6
#define MSTRID_F2_SHIFT                                                      16
#define MSTRID_F2_MASK                                               0x003f0000
#define MSTRID_F2_RD(src)                            (((src) & 0x003f0000)>>16)
#define MSTRID_F2_WR(src)                       (((u32)(src)<<16) & 0x003f0000)
#define MSTRID_F2_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields AUXINFO	 */
#define AUXINFO_F2_WIDTH                                                      6
#define AUXINFO_F2_SHIFT                                                     10
#define AUXINFO_F2_MASK                                              0x0000fc00
#define AUXINFO_F2_RD(src)                           (((src) & 0x0000fc00)>>10)
#define AUXINFO_F2_WR(src)                      (((u32)(src)<<10) & 0x0000fc00)
#define AUXINFO_F2_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields REQLEN	 */
#define REQLEN_F2_WIDTH                                                       2
#define REQLEN_F2_SHIFT                                                       4
#define REQLEN_F2_MASK                                               0x00000030
#define REQLEN_F2_RD(src)                             (((src) & 0x00000030)>>4)
#define REQLEN_F2_WR(src)                        (((u32)(src)<<4) & 0x00000030)
#define REQLEN_F2_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields REQSIZE	 */
#define REQSIZE_F2_WIDTH                                                      3
#define REQSIZE_F2_SHIFT                                                      1
#define REQSIZE_F2_MASK                                              0x0000000e
#define REQSIZE_F2_RD(src)                            (((src) & 0x0000000e)>>1)
#define REQSIZE_F2_WR(src)                       (((u32)(src)<<1) & 0x0000000e)
#define REQSIZE_F2_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields REQTYPE	 */
#define REQTYPE_F1_WIDTH                                                      1
#define REQTYPE_F1_SHIFT                                                      0
#define REQTYPE_F1_MASK                                              0x00000001
#define REQTYPE_F1_RD(src)                               (((src) & 0x00000001))
#define REQTYPE_F1_WR(src)                          (((u32)(src)) & 0x00000001)
#define REQTYPE_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRL_ALS	*/
/*	 Fields SEC	 */
#define SEC_WIDTH                                                            32
#define SEC_SHIFT                                                             0
#define SEC_MASK                                                     0xffffffff
#define SEC_RD(src)                                      (((src) & 0xffffffff))
#define SEC_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define SEC_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_SEC_ERRH_ALS	*/
/*	 Fields SEC	 */
#define SEC_F1_WIDTH                                                         32
#define SEC_F1_SHIFT                                                          0
#define SEC_F1_MASK                                                  0xffffffff
#define SEC_F1_RD(src)                                   (((src) & 0xffffffff))
#define SEC_F1_WR(src)                              (((u32)(src)) & 0xffffffff)
#define SEC_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_DED_ERRL_ALS	*/
/*	 Fields DED	 */
#define DED_WIDTH                                                            32
#define DED_SHIFT                                                             0
#define DED_MASK                                                     0xffffffff
#define DED_RD(src)                                      (((src) & 0xffffffff))
#define DED_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define DED_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_DED_ERRH_ALS	*/
/*	 Fields DED	 */
#define DED_F1_WIDTH                                                         32
#define DED_F1_SHIFT                                                          0
#define DED_F1_MASK                                                  0xffffffff
#define DED_F1_RD(src)                                   (((src) & 0xffffffff))
#define DED_F1_WR(src)                              (((u32)(src)) & 0xffffffff)
#define DED_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_TRANS_ERR_ALS	*/
/*	 Fields SWRPOISON	 */
#define SWRPOISON_F1_WIDTH                                                    1
#define SWRPOISON_F1_SHIFT                                                   11
#define SWRPOISON_F1_MASK                                            0x00000800
#define SWRPOISON_F1_RD(src)                         (((src) & 0x00000800)>>11)
#define SWRPOISON_F1_WR(src)                    (((u32)(src)<<11) & 0x00000800)
#define SWRPOISON_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SWRDYTMO	 */
#define SWRDYTMO_F1_WIDTH                                                     1
#define SWRDYTMO_F1_SHIFT                                                    10
#define SWRDYTMO_F1_MASK                                             0x00000400
#define SWRDYTMO_F1_RD(src)                          (((src) & 0x00000400)>>10)
#define SWRDYTMO_F1_WR(src)                     (((u32)(src)<<10) & 0x00000400)
#define SWRDYTMO_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SWRESPTMO	 */
#define SWRESPTMO_F1_WIDTH                                                    1
#define SWRESPTMO_F1_SHIFT                                                    9
#define SWRESPTMO_F1_MASK                                            0x00000200
#define SWRESPTMO_F1_RD(src)                          (((src) & 0x00000200)>>9)
#define SWRESPTMO_F1_WR(src)                     (((u32)(src)<<9) & 0x00000200)
#define SWRESPTMO_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SWRERR	 */
#define SWRERR_F1_WIDTH                                                       1
#define SWRERR_F1_SHIFT                                                       7
#define SWRERR_F1_MASK                                               0x00000080
#define SWRERR_F1_RD(src)                             (((src) & 0x00000080)>>7)
#define SWRERR_F1_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define SWRERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SRRDYTMO	 */
#define SRRDYTMO_F1_WIDTH                                                     1
#define SRRDYTMO_F1_SHIFT                                                     3
#define SRRDYTMO_F1_MASK                                             0x00000008
#define SRRDYTMO_F1_RD(src)                           (((src) & 0x00000008)>>3)
#define SRRDYTMO_F1_WR(src)                      (((u32)(src)<<3) & 0x00000008)
#define SRRDYTMO_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SRRESPTMO	 */
#define SRRESPTMO_F1_WIDTH                                                    1
#define SRRESPTMO_F1_SHIFT                                                    2
#define SRRESPTMO_F1_MASK                                            0x00000004
#define SRRESPTMO_F1_RD(src)                          (((src) & 0x00000004)>>2)
#define SRRESPTMO_F1_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define SRRESPTMO_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SRDERR	 */
#define SRDERR_F1_WIDTH                                                       1
#define SRDERR_F1_SHIFT                                                       0
#define SRDERR_F1_MASK                                               0x00000001
#define SRDERR_F1_RD(src)                                (((src) & 0x00000001))
#define SRDERR_F1_WR(src)                           (((u32)(src)) & 0x00000001)
#define SRDERR_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Global Base Address	*/
#define SLAVE_SHIM_CSR_BASE_ADDR			0x01701e000ULL

/*    Address SLAVE_SHIM_CSR  Registers */
#define CFG_SLV_RESP_TMO_CNTR_ADDR                                   0x00000004
#define CFG_SLV_RESP_TMO_CNTR_DEFAULT                                0x0000ffff
#define CFG_SLV_READY_TMO_CNTR_ADDR                                  0x00000008
#define CFG_SLV_READY_TMO_CNTR_DEFAULT                               0x0000ffff
#define INT_SLV_TMO_ADDR                                             0x0000000c
#define INT_SLV_TMO_DEFAULT                                          0x00000000
#define INT_SLV_TMOMASK_ADDR                                         0x00000010
#define CFG_AMA_MODE_ADDR                                            0x00000014
#define CFG_AMA_MODE_DEFAULT                                         0x00000000

/*	Register CFG_SLV_RESP_TMO_CNTR	*/
/*	 Fields CFG_CSR_POISON	 */
#define CFG_CSR_POISON_WIDTH                                                  1
#define CFG_CSR_POISON_SHIFT                                                 17
#define CFG_CSR_POISON_MASK                                          0x00020000
#define CFG_CSR_POISON_RD(src)                       (((src) & 0x00020000)>>17)
#define CFG_CSR_POISON_WR(src)                  (((u32)(src)<<17) & 0x00020000)
#define CFG_CSR_POISON_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields CSR_ERR_RESP_EN	 */
#define CSR_ERR_RESP_EN_WIDTH                                                 1
#define CSR_ERR_RESP_EN_SHIFT                                                16
#define CSR_ERR_RESP_EN_MASK                                         0x00010000
#define CSR_ERR_RESP_EN_RD(src)                      (((src) & 0x00010000)>>16)
#define CSR_ERR_RESP_EN_WR(src)                 (((u32)(src)<<16) & 0x00010000)
#define CSR_ERR_RESP_EN_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields CFG_CSR_RESP_TMO	 */
#define CFG_CSR_RESP_TMO_WIDTH                                               16
#define CFG_CSR_RESP_TMO_SHIFT                                                0
#define CFG_CSR_RESP_TMO_MASK                                        0x0000ffff
#define CFG_CSR_RESP_TMO_RD(src)                         (((src) & 0x0000ffff))
#define CFG_CSR_RESP_TMO_WR(src)                    (((u32)(src)) & 0x0000ffff)
#define CFG_CSR_RESP_TMO_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_SLV_READY_TMO_CNTR	*/
/*	 Fields CFG_CSR_READY_TMO	 */
#define CFG_CSR_READY_TMO_WIDTH                                              32
#define CFG_CSR_READY_TMO_SHIFT                                               0
#define CFG_CSR_READY_TMO_MASK                                       0xffffffff
#define CFG_CSR_READY_TMO_RD(src)                        (((src) & 0xffffffff))
#define CFG_CSR_READY_TMO_WR(src)                   (((u32)(src)) & 0xffffffff)
#define CFG_CSR_READY_TMO_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register INT_SLV_TMO	*/
/*	 Fields STS_CSR_TMO	 */
#define STS_CSR_TMO_WIDTH                                                     1
#define STS_CSR_TMO_SHIFT                                                     4
#define STS_CSR_TMO_MASK                                             0x00000010
#define STS_CSR_TMO_RD(src)                           (((src) & 0x00000010)>>4)
#define STS_CSR_TMO_WR(src)                      (((u32)(src)<<4) & 0x00000010)
#define STS_CSR_TMO_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields STS_ARREADY_TMO	 */
#define STS_ARREADY_TMO_WIDTH                                                 1
#define STS_ARREADY_TMO_SHIFT                                                 3
#define STS_ARREADY_TMO_MASK                                         0x00000008
#define STS_ARREADY_TMO_RD(src)                       (((src) & 0x00000008)>>3)
#define STS_ARREADY_TMO_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define STS_ARREADY_TMO_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields STS_RVALID_TMO	 */
#define STS_RVALID_TMO_WIDTH                                                  1
#define STS_RVALID_TMO_SHIFT                                                  2
#define STS_RVALID_TMO_MASK                                          0x00000004
#define STS_RVALID_TMO_RD(src)                        (((src) & 0x00000004)>>2)
#define STS_RVALID_TMO_WR(src)                   (((u32)(src)<<2) & 0x00000004)
#define STS_RVALID_TMO_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields STS_AWREADY_TMO	 */
#define STS_AWREADY_TMO_WIDTH                                                 1
#define STS_AWREADY_TMO_SHIFT                                                 1
#define STS_AWREADY_TMO_MASK                                         0x00000002
#define STS_AWREADY_TMO_RD(src)                       (((src) & 0x00000002)>>1)
#define STS_AWREADY_TMO_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define STS_AWREADY_TMO_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields STS_BVALID_TMO	 */
#define STS_BVALID_TMO_WIDTH                                                  1
#define STS_BVALID_TMO_SHIFT                                                  0
#define STS_BVALID_TMO_MASK                                          0x00000001
#define STS_BVALID_TMO_RD(src)                           (((src) & 0x00000001))
#define STS_BVALID_TMO_WR(src)                      (((u32)(src)) & 0x00000001)
#define STS_BVALID_TMO_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register INT_SLV_TMOMask	*/
/*    Mask Register Fields STS_CSR_TMOMask    */
#define STS_CSR_TMOMASK_WIDTH                                                 1
#define STS_CSR_TMOMASK_SHIFT                                                 4
#define STS_CSR_TMOMASK_MASK                                         0x00000010
#define STS_CSR_TMOMASK_RD(src)                       (((src) & 0x00000010)>>4)
#define STS_CSR_TMOMASK_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define STS_CSR_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields STS_ARREADY_TMOMask    */
#define STS_ARREADY_TMOMASK_WIDTH                                             1
#define STS_ARREADY_TMOMASK_SHIFT                                             3
#define STS_ARREADY_TMOMASK_MASK                                     0x00000008
#define STS_ARREADY_TMOMASK_RD(src)                   (((src) & 0x00000008)>>3)
#define STS_ARREADY_TMOMASK_WR(src)              (((u32)(src)<<3) & 0x00000008)
#define STS_ARREADY_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields STS_RVALID_TMOMask    */
#define STS_RVALID_TMOMASK_WIDTH                                              1
#define STS_RVALID_TMOMASK_SHIFT                                              2
#define STS_RVALID_TMOMASK_MASK                                      0x00000004
#define STS_RVALID_TMOMASK_RD(src)                    (((src) & 0x00000004)>>2)
#define STS_RVALID_TMOMASK_WR(src)               (((u32)(src)<<2) & 0x00000004)
#define STS_RVALID_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields STS_AWREADY_TMOMask    */
#define STS_AWREADY_TMOMASK_WIDTH                                             1
#define STS_AWREADY_TMOMASK_SHIFT                                             1
#define STS_AWREADY_TMOMASK_MASK                                     0x00000002
#define STS_AWREADY_TMOMASK_RD(src)                   (((src) & 0x00000002)>>1)
#define STS_AWREADY_TMOMASK_WR(src)              (((u32)(src)<<1) & 0x00000002)
#define STS_AWREADY_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields STS_BVALID_TMOMask    */
#define STS_BVALID_TMOMASK_WIDTH                                              1
#define STS_BVALID_TMOMASK_SHIFT                                              0
#define STS_BVALID_TMOMASK_MASK                                      0x00000001
#define STS_BVALID_TMOMASK_RD(src)                       (((src) & 0x00000001))
#define STS_BVALID_TMOMASK_WR(src)                  (((u32)(src)) & 0x00000001)
#define STS_BVALID_TMOMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_AMA_MODE	*/
/*	 Fields CFG_AMA_MODE	 */
#define REGSPEC_CFG_AMA_MODE_WIDTH                                            1
#define REGSPEC_CFG_AMA_MODE_SHIFT                                            0
#define REGSPEC_CFG_AMA_MODE_MASK                                    0x00000001
#define REGSPEC_CFG_AMA_MODE_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_CFG_AMA_MODE_WR(src)                (((u32)(src)) & 0x00000001)
#define REGSPEC_CFG_AMA_MODE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))


#endif /*_APMXGENEGFCCSR_H__*/
