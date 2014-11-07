/** @file
 *  
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *  
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *  
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *  
 **/
 
 #ifndef _APMXGENEAHBCCSR_H_
 #define _APMXGENEAHBCCSR_H_
 
 /*	Global Base Address	*/
#define AHBC_TOP_REG_BASE_ADDR			0x01f2a0000ULL

/*    Address AHBC_TOP_REG  Registers */
#define SDR_SDIO_AHB2AXI_CFG_ADDR                                    0x00000000
#define SDR_SDIO_AHB2AXI_CFG_DEFAULT                                 0x004481ff
#define SPI_CONFIG_ADDR                                              0x00000004
#define SPI_CONFIG_DEFAULT                                           0x00000003
#define SDHC_TAP_DELAY_ADDR                                          0x00000020
#define SDHC_TAP_DELAY_DEFAULT                                       0x00000000
#define SDHC_CAP_REG_LOW_S1_ADDR                                     0x00000024
#define SDHC_CAP_REG_LOW_S1_DEFAULT                                  0x00000000
#define SDHC_CAP_REG_HIGH_S1_ADDR                                    0x00000028
#define SDHC_CAP_REG_HIGH_S1_DEFAULT                                 0x00000000
#define SDHC_CAP_REG_LOW_S2_ADDR                                     0x0000002c
#define SDHC_CAP_REG_LOW_S2_DEFAULT                                  0x00000000
#define SDHC_CAP_REG_HIGH_S2_ADDR                                    0x00000030
#define SDHC_CAP_REG_HIGH_S2_DEFAULT                                 0x00000000
#define SDHC_INIT_PRESET_ADDR                                        0x00000034
#define SDHC_INIT_PRESET_DEFAULT                                     0x00000000
#define SDHC_DEFAULT_PRESET_ADDR                                     0x00000038
#define SDHC_DEFAULT_PRESET_DEFAULT                                  0x00000000
#define SDHC_HIGH_SPEED_PRESET_ADDR                                  0x0000003c
#define SDHC_HIGH_SPEED_PRESET_DEFAULT                               0x00000000
#define SDHC_SDR12_PRESET_ADDR                                       0x00000040
#define SDHC_SDR12_PRESET_DEFAULT                                    0x00000000
#define SDHC_SDR25_PRESET_ADDR                                       0x00000044
#define SDHC_SDR25_PRESET_DEFAULT                                    0x00000000
#define SDHC_SDR50_PRESET_ADDR                                       0x00000048
#define SDHC_SDR50_PRESET_DEFAULT                                    0x00000000
#define SDHC_SDR104_PRESET_ADDR                                      0x0000004c
#define SDHC_SDR104_PRESET_DEFAULT                                   0x00000000
#define SDHC_DDR50_PRESET_ADDR                                       0x00000050
#define SDHC_DDR50_PRESET_DEFAULT                                    0x00000000
#define SDHC_CONFIG_ADDR                                             0x00000054
#define SDHC_CONFIG_DEFAULT                                          0x00000000
#define SDHC_DATARAM_ADDR                                            0x00000058
#define SDHC_DATARAM_DEFAULT                                         0x00000000
#define CFG_X2H_BRIDGE_ADDR                                          0x00000060
#define CFG_X2H_BRIDGE_DEFAULT                                       0x00000002
#define UART_MODE_SEL_ADDR                                           0x00000064
#define UART_MODE_SEL_DEFAULT                                        0x00000000
#define AHB2AXI_BID_ADDR                                             0x00000070
#define AHB2AXI_BID_DEFAULT                                          0x00000020
#define AHBC_INTERRUPT_ADDR                                          0x00000074
#define AHBC_INTERRUPT_DEFAULT                                       0x00000000
#define AIM_0_AHB_ADDR                                               0x00000080
#define AIM_0_AHB_DEFAULT                                            0x00000000
#define AIM_0_SIZE_CTL_ADDR                                          0x00000084
#define AIM_0_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_0_AXI_LO_ADDR                                            0x00000088
#define AIM_0_AXI_LO_DEFAULT                                         0x00000000
#define AIM_0_AXI_HI_ADDR                                            0x00000090
#define AIM_0_AXI_HI_DEFAULT                                         0x00000000
#define AIM_1_AHB_ADDR                                               0x00000094
#define AIM_1_AHB_DEFAULT                                            0x00000000
#define AIM_1_SIZE_CTL_ADDR                                          0x00000098
#define AIM_1_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_1_AXI_LO_ADDR                                            0x0000009c
#define AIM_1_AXI_LO_DEFAULT                                         0x00000000
#define AIM_1_AXI_HI_ADDR                                            0x000000a0
#define AIM_1_AXI_HI_DEFAULT                                         0x00000000
#define AIM_2_AHB_ADDR                                               0x000000a4
#define AIM_2_AHB_DEFAULT                                            0x00000000
#define AIM_2_SIZE_CTL_ADDR                                          0x000000a8
#define AIM_2_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_2_AXI_LO_ADDR                                            0x000000ac
#define AIM_2_AXI_LO_DEFAULT                                         0x00000000
#define AIM_2_AXI_HI_ADDR                                            0x000000b0
#define AIM_2_AXI_HI_DEFAULT                                         0x00000000
#define AIM_3_AHB_ADDR                                               0x000000b4
#define AIM_3_AHB_DEFAULT                                            0x00000000
#define AIM_3_SIZE_CTL_ADDR                                          0x000000b8
#define AIM_3_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_3_AXI_LO_ADDR                                            0x000000bc
#define AIM_3_AXI_LO_DEFAULT                                         0x00000000
#define AIM_3_AXI_HI_ADDR                                            0x000000c0
#define AIM_3_AXI_HI_DEFAULT                                         0x00000000
#define AIM_4_AHB_ADDR                                               0x000000c4
#define AIM_4_AHB_DEFAULT                                            0x00000000
#define AIM_4_SIZE_CTL_ADDR                                          0x000000c8
#define AIM_4_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_4_AXI_LO_ADDR                                            0x000000cc
#define AIM_4_AXI_LO_DEFAULT                                         0x00000000
#define AIM_4_AXI_HI_ADDR                                            0x000000d0
#define AIM_4_AXI_HI_DEFAULT                                         0x00000000
#define AIM_5_AHB_ADDR                                               0x000000d4
#define AIM_5_AHB_DEFAULT                                            0x00000000
#define AIM_5_SIZE_CTL_ADDR                                          0x000000d8
#define AIM_5_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_5_AXI_LO_ADDR                                            0x000000dc
#define AIM_5_AXI_LO_DEFAULT                                         0x00000000
#define AIM_5_AXI_HI_ADDR                                            0x000000e0
#define AIM_5_AXI_HI_DEFAULT                                         0x00000000
#define AIM_6_AHB_ADDR                                               0x000000e4
#define AIM_6_AHB_DEFAULT                                            0x00000000
#define AIM_6_SIZE_CTL_ADDR                                          0x000000e8
#define AIM_6_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_6_AXI_LO_ADDR                                            0x000000ec
#define AIM_6_AXI_LO_DEFAULT                                         0x00000000
#define AIM_6_AXI_HI_ADDR                                            0x000000f0
#define AIM_6_AXI_HI_DEFAULT                                         0x00000000
#define AIM_7_AHB_ADDR                                               0x000000f4
#define AIM_7_AHB_DEFAULT                                            0x00000000
#define AIM_7_SIZE_CTL_ADDR                                          0x000000f8
#define AIM_7_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_7_AXI_LO_ADDR                                            0x000000fc
#define AIM_7_AXI_LO_DEFAULT                                         0x00000000
#define AIM_7_AXI_HI_ADDR                                            0x00000100
#define AIM_7_AXI_HI_DEFAULT                                         0x00000000
#define AIM_8_SIZE_CTL_ADDR                                          0x00000104
#define AIM_8_SIZE_CTL_DEFAULT                                       0x00000000
#define AIM_8_AXI_LO_ADDR                                            0x00000108
#define AIM_8_AXI_LO_DEFAULT                                         0x00000000
#define AIM_8_AXI_HI_ADDR                                            0x0000010c
#define AIM_8_AXI_HI_DEFAULT                                         0x00000000
#define AOM_0_AXI_LO_ADDR                                            0x00000110
#define AOM_0_AXI_LO_DEFAULT                                         0x00000000
#define AOM_0_AXI_HI_ADDR                                            0x00000114
#define AOM_0_AXI_HI_DEFAULT                                         0x00000000
#define AOM_0_SIZE_CTL_ADDR                                          0x00000118
#define AOM_0_SIZE_CTL_DEFAULT                                       0x00000000
#define AOM_0_AHB_ADDR                                               0x0000011c
#define AOM_0_AHB_DEFAULT                                            0x00000000
#define AOM_1_AXI_LO_ADDR                                            0x00000120
#define AOM_1_AXI_LO_DEFAULT                                         0x00000000
#define AOM_1_AXI_HI_ADDR                                            0x00000124
#define AOM_1_AXI_HI_DEFAULT                                         0x00000000
#define AOM_1_SIZE_CTL_ADDR                                          0x00000128
#define AOM_1_SIZE_CTL_DEFAULT                                       0x00000000
#define AOM_1_AHB_ADDR                                               0x0000012c
#define AOM_1_AHB_DEFAULT                                            0x00000000
#define AOM_2_AXI_LO_ADDR                                            0x00000130
#define AOM_2_AXI_LO_DEFAULT                                         0x00000000
#define AOM_2_AXI_HI_ADDR                                            0x00000134
#define AOM_2_AXI_HI_DEFAULT                                         0x00000000
#define AOM_2_SIZE_CTL_ADDR                                          0x00000138
#define AOM_2_SIZE_CTL_DEFAULT                                       0x00000000
#define AOM_2_AHB_ADDR                                               0x0000013c
#define AOM_2_AHB_DEFAULT                                            0x00000000
#define AOM_3_AXI_LO_ADDR                                            0x00000140
#define AOM_3_AXI_LO_DEFAULT                                         0x00000000
#define AOM_3_AXI_HI_ADDR                                            0x00000144
#define AOM_3_AXI_HI_DEFAULT                                         0x00000000
#define AOM_3_SIZE_CTL_ADDR                                          0x00000148
#define AOM_3_SIZE_CTL_DEFAULT                                       0x00000000
#define AOM_3_AHB_ADDR                                               0x0000014c
#define AOM_3_AHB_DEFAULT                                            0x00000000
#define AHB_RD_ERR_ADDR_ADDR                                         0x00000150
#define AHB_RD_ERR_ADDR_DEFAULT                                      0x00000000
#define AHB_RD_ERR_ATTRIBUTES_ADDR                                   0x00000154
#define AHB_RD_ERR_ATTRIBUTES_DEFAULT                                0x00000000
#define AHB_WR_ERR_ADDR_ADDR                                         0x00000158
#define AHB_WR_ERR_ADDR_DEFAULT                                      0x00000000
#define AHB_WR_ERR_DATA_ADDR                                         0x0000015c
#define AHB_WR_ERR_DATA_DEFAULT                                      0x00000000
#define AHB_WR_ERR_ATTRIBUTES_ADDR                                   0x00000160
#define AHB_WR_ERR_ATTRIBUTES_DEFAULT                                0x00000000
#define CFG_INTR_CTL_ADDR                                            0x00000164
#define CFG_INTR_CTL_DEFAULT                                         0x00000000
#define CFG_PIN_MUX_SEL_0_ADDR                                       0x00000168
#define CFG_PIN_MUX_SEL_0_DEFAULT                                    0x00000000
#define CFG_PIN_MUX_SEL_1_ADDR                                       0x0000016c
#define CFG_PIN_MUX_SEL_1_DEFAULT                                    0x00000000
#define CFG_PIN_MUX_SEL_2_ADDR                                       0x00000170
#define CFG_PIN_MUX_SEL_2_DEFAULT                                    0x00000000
#define CFG_USBH0_ADDR                                               0x00000174
#define CFG_USBH0_DEFAULT                                            0x00000037
#define CFG_USBH1_ADDR                                               0x00000178
#define CFG_USBH1_DEFAULT                                            0x00000037
#define CFG_PIN_OD_SEL_1_ADDR                                        0x0000017c
#define CFG_PIN_OD_SEL_1_DEFAULT                                     0x00000000
#define CFG_PIN_OD_SEL_2_ADDR                                        0x00000180
#define CFG_PIN_OD_SEL_2_DEFAULT                                     0x00000000
#define CFG_PIN_OD_SEL_3_ADDR                                        0x00000184
#define CFG_PIN_OD_SEL_3_DEFAULT                                     0x00000000

/*	Register SDR_SDIO_AHB2AXI_CFG	*/ 
/*	 Fields wr_coherent	 */
#define WR_COHERENT_WIDTH                                                     1
#define WR_COHERENT_SHIFT                                                    23
#define WR_COHERENT_MASK                                             0x00800000
#define WR_COHERENT_RD(src)                          (((src) & 0x00800000)>>23)
#define WR_COHERENT_WR(src)                     (((u32)(src)<<23) & 0x00800000)
#define WR_COHERENT_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields pw_axi_sideband_prio	 */
#define PW_AXI_SIDEBAND_PRIO_WIDTH                                            2
#define PW_AXI_SIDEBAND_PRIO_SHIFT                                           21
#define PW_AXI_SIDEBAND_PRIO_MASK                                    0x00600000
#define PW_AXI_SIDEBAND_PRIO_RD(src)                 (((src) & 0x00600000)>>21)
#define PW_AXI_SIDEBAND_PRIO_WR(src)            (((u32)(src)<<21) & 0x00600000)
#define PW_AXI_SIDEBAND_PRIO_SET(dst,src) \
                      (((dst) & ~0x00600000) | (((u32)(src)<<21) & 0x00600000))
/*	 Fields rd_coherent	 */
#define RD_COHERENT_WIDTH                                                     1
#define RD_COHERENT_SHIFT                                                    19
#define RD_COHERENT_MASK                                             0x00080000
#define RD_COHERENT_RD(src)                          (((src) & 0x00080000)>>19)
#define RD_COHERENT_WR(src)                     (((u32)(src)<<19) & 0x00080000)
#define RD_COHERENT_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields pr_axi_sideband_prio	 */
#define PR_AXI_SIDEBAND_PRIO_WIDTH                                            2
#define PR_AXI_SIDEBAND_PRIO_SHIFT                                           17
#define PR_AXI_SIDEBAND_PRIO_MASK                                    0x00060000
#define PR_AXI_SIDEBAND_PRIO_RD(src)                 (((src) & 0x00060000)>>17)
#define PR_AXI_SIDEBAND_PRIO_WR(src)            (((u32)(src)<<17) & 0x00060000)
#define PR_AXI_SIDEBAND_PRIO_SET(dst,src) \
                      (((dst) & ~0x00060000) | (((u32)(src)<<17) & 0x00060000))
/*	 Fields writes_block_reads	 */
#define WRITES_BLOCK_READS_WIDTH                                              1
#define WRITES_BLOCK_READS_SHIFT                                             15
#define WRITES_BLOCK_READS_MASK                                      0x00008000
#define WRITES_BLOCK_READS_RD(src)                   (((src) & 0x00008000)>>15)
#define WRITES_BLOCK_READS_WR(src)              (((u32)(src)<<15) & 0x00008000)
#define WRITES_BLOCK_READS_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields pw_max_outstanding	 */
#define PW_MAX_OUTSTANDING_WIDTH                                              4
#define PW_MAX_OUTSTANDING_SHIFT                                              8
#define PW_MAX_OUTSTANDING_MASK                                      0x00000f00
#define PW_MAX_OUTSTANDING_RD(src)                    (((src) & 0x00000f00)>>8)
#define PW_MAX_OUTSTANDING_WR(src)               (((u32)(src)<<8) & 0x00000f00)
#define PW_MAX_OUTSTANDING_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields tx_wrr_weight	 */
#define TX_WRR_WEIGHT_WIDTH                                                   4
#define TX_WRR_WEIGHT_SHIFT                                                   4
#define TX_WRR_WEIGHT_MASK                                           0x000000f0
#define TX_WRR_WEIGHT_RD(src)                         (((src) & 0x000000f0)>>4)
#define TX_WRR_WEIGHT_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define TX_WRR_WEIGHT_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields rx_wrr_weight	 */
#define RX_WRR_WEIGHT_WIDTH                                                   4
#define RX_WRR_WEIGHT_SHIFT                                                   0
#define RX_WRR_WEIGHT_MASK                                           0x0000000f
#define RX_WRR_WEIGHT_RD(src)                            (((src) & 0x0000000f))
#define RX_WRR_WEIGHT_WR(src)                       (((u32)(src)) & 0x0000000f)
#define RX_WRR_WEIGHT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SPI_CONFIG	*/ 
/*	 Fields spi_1_ss_in_n	 */
#define SPI_1_SS_IN_N_WIDTH                                                   1
#define SPI_1_SS_IN_N_SHIFT                                                   1
#define SPI_1_SS_IN_N_MASK                                           0x00000002
#define SPI_1_SS_IN_N_RD(src)                         (((src) & 0x00000002)>>1)
#define SPI_1_SS_IN_N_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define SPI_1_SS_IN_N_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields spi_0_ss_in_n	 */
#define SPI_0_SS_IN_N_WIDTH                                                   1
#define SPI_0_SS_IN_N_SHIFT                                                   0
#define SPI_0_SS_IN_N_MASK                                           0x00000001
#define SPI_0_SS_IN_N_RD(src)                            (((src) & 0x00000001))
#define SPI_0_SS_IN_N_WR(src)                       (((u32)(src)) & 0x00000001)
#define SPI_0_SS_IN_N_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SDHC_TAP_DELAY	*/ 
/*	 Fields CFG_OP_TAP_EN	 */
#define CFG_OP_TAP_EN_WIDTH                                                   1
#define CFG_OP_TAP_EN_SHIFT                                                  16
#define CFG_OP_TAP_EN_MASK                                           0x00010000
#define CFG_OP_TAP_EN_RD(src)                        (((src) & 0x00010000)>>16)
#define CFG_OP_TAP_EN_WR(src)                   (((u32)(src)<<16) & 0x00010000)
#define CFG_OP_TAP_EN_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields CFG_OP_TAP_DELAY	 */
#define CFG_OP_TAP_DELAY_WIDTH                                                4
#define CFG_OP_TAP_DELAY_SHIFT                                               12
#define CFG_OP_TAP_DELAY_MASK                                        0x0000f000
#define CFG_OP_TAP_DELAY_RD(src)                     (((src) & 0x0000f000)>>12)
#define CFG_OP_TAP_DELAY_WR(src)                (((u32)(src)<<12) & 0x0000f000)
#define CFG_OP_TAP_DELAY_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields CFG_OP_DLY_CTRL	 */
#define CFG_OP_DLY_CTRL_WIDTH                                                 2
#define CFG_OP_DLY_CTRL_SHIFT                                                10
#define CFG_OP_DLY_CTRL_MASK                                         0x00000c00
#define CFG_OP_DLY_CTRL_RD(src)                      (((src) & 0x00000c00)>>10)
#define CFG_OP_DLY_CTRL_WR(src)                 (((u32)(src)<<10) & 0x00000c00)
#define CFG_OP_DLY_CTRL_SET(dst,src) \
                      (((dst) & ~0x00000c00) | (((u32)(src)<<10) & 0x00000c00))
/*	 Fields CFG_IP_TAP_EN	 */
#define CFG_IP_TAP_EN_WIDTH                                                   1
#define CFG_IP_TAP_EN_SHIFT                                                   9
#define CFG_IP_TAP_EN_MASK                                           0x00000200
#define CFG_IP_TAP_EN_RD(src)                         (((src) & 0x00000200)>>9)
#define CFG_IP_TAP_EN_WR(src)                    (((u32)(src)<<9) & 0x00000200)
#define CFG_IP_TAP_EN_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields CFG_IP_TAP_DELAY	 */
#define CFG_IP_TAP_DELAY_WIDTH                                                6
#define CFG_IP_TAP_DELAY_SHIFT                                                3
#define CFG_IP_TAP_DELAY_MASK                                        0x000001f8
#define CFG_IP_TAP_DELAY_RD(src)                      (((src) & 0x000001f8)>>3)
#define CFG_IP_TAP_DELAY_WR(src)                 (((u32)(src)<<3) & 0x000001f8)
#define CFG_IP_TAP_DELAY_SET(dst,src) \
                       (((dst) & ~0x000001f8) | (((u32)(src)<<3) & 0x000001f8))
/*	 Fields CFG_IP_DLY_CTRL	 */
#define CFG_IP_DLY_CTRL_WIDTH                                                 2
#define CFG_IP_DLY_CTRL_SHIFT                                                 1
#define CFG_IP_DLY_CTRL_MASK                                         0x00000006
#define CFG_IP_DLY_CTRL_RD(src)                       (((src) & 0x00000006)>>1)
#define CFG_IP_DLY_CTRL_WR(src)                  (((u32)(src)<<1) & 0x00000006)
#define CFG_IP_DLY_CTRL_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields CFG_CMD_CONFLICT_DIS	 */
#define CFG_CMD_CONFLICT_DIS_WIDTH                                            1
#define CFG_CMD_CONFLICT_DIS_SHIFT                                            0
#define CFG_CMD_CONFLICT_DIS_MASK                                    0x00000001
#define CFG_CMD_CONFLICT_DIS_RD(src)                     (((src) & 0x00000001))
#define CFG_CMD_CONFLICT_DIS_WR(src)                (((u32)(src)) & 0x00000001)
#define CFG_CMD_CONFLICT_DIS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SDHC_CAP_REG_LOW_S1	*/ 
/*	 Fields SDHC_CAP_REG_LOW_S1	 */
#define SDHC_CAP_REG_LOW_S11_WIDTH                                           32
#define SDHC_CAP_REG_LOW_S11_SHIFT                                            0
#define SDHC_CAP_REG_LOW_S11_MASK                                    0xffffffff
#define SDHC_CAP_REG_LOW_S11_RD(src)                     (((src) & 0xffffffff))
#define SDHC_CAP_REG_LOW_S11_WR(src)                (((u32)(src)) & 0xffffffff)
#define SDHC_CAP_REG_LOW_S11_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SDHC_CAP_REG_HIGH_S1	*/ 
/*	 Fields SDHC_CAP_REG_HIGH_S1	 */
#define SDHC_CAP_REG_HIGH_S11_WIDTH                                          13
#define SDHC_CAP_REG_HIGH_S11_SHIFT                                           0
#define SDHC_CAP_REG_HIGH_S11_MASK                                   0x00001fff
#define SDHC_CAP_REG_HIGH_S11_RD(src)                    (((src) & 0x00001fff))
#define SDHC_CAP_REG_HIGH_S11_WR(src)               (((u32)(src)) & 0x00001fff)
#define SDHC_CAP_REG_HIGH_S11_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register SDHC_CAP_REG_LOW_S2	*/ 
/*	 Fields SDHC_CAP_REG_LOW_S2	 */
#define SDHC_CAP_REG_LOW_S22_WIDTH                                           32
#define SDHC_CAP_REG_LOW_S22_SHIFT                                            0
#define SDHC_CAP_REG_LOW_S22_MASK                                    0xffffffff
#define SDHC_CAP_REG_LOW_S22_RD(src)                     (((src) & 0xffffffff))
#define SDHC_CAP_REG_LOW_S22_WR(src)                (((u32)(src)) & 0xffffffff)
#define SDHC_CAP_REG_LOW_S22_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SDHC_CAP_REG_HIGH_S2	*/ 
/*	 Fields SDHC_CAP_REG_HIGH_S2	 */
#define SDHC_CAP_REG_HIGH_S22_WIDTH                                          13
#define SDHC_CAP_REG_HIGH_S22_SHIFT                                           0
#define SDHC_CAP_REG_HIGH_S22_MASK                                   0x00001fff
#define SDHC_CAP_REG_HIGH_S22_RD(src)                    (((src) & 0x00001fff))
#define SDHC_CAP_REG_HIGH_S22_WR(src)               (((u32)(src)) & 0x00001fff)
#define SDHC_CAP_REG_HIGH_S22_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register SDHC_INIT_PRESET	*/ 
/*	 Fields INIT_PRESET_S1	 */
#define INIT_PRESET_S1_WIDTH                                                 12
#define INIT_PRESET_S1_SHIFT                                                 12
#define INIT_PRESET_S1_MASK                                          0x00fff000
#define INIT_PRESET_S1_RD(src)                       (((src) & 0x00fff000)>>12)
#define INIT_PRESET_S1_WR(src)                  (((u32)(src)<<12) & 0x00fff000)
#define INIT_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields INIT_PRESET_S2	 */
#define INIT_PRESET_S2_WIDTH                                                 12
#define INIT_PRESET_S2_SHIFT                                                  0
#define INIT_PRESET_S2_MASK                                          0x00000fff
#define INIT_PRESET_S2_RD(src)                           (((src) & 0x00000fff))
#define INIT_PRESET_S2_WR(src)                      (((u32)(src)) & 0x00000fff)
#define INIT_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_DEFAULT_PRESET	*/ 
/*	 Fields DEFAULT_PRESET_S1	 */
#define DEFAULT_PRESET_S1_WIDTH                                              12
#define DEFAULT_PRESET_S1_SHIFT                                              12
#define DEFAULT_PRESET_S1_MASK                                       0x00fff000
#define DEFAULT_PRESET_S1_RD(src)                    (((src) & 0x00fff000)>>12)
#define DEFAULT_PRESET_S1_WR(src)               (((u32)(src)<<12) & 0x00fff000)
#define DEFAULT_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields DEFAULT_PRESET_S2	 */
#define DEFAULT_PRESET_S2_WIDTH                                              12
#define DEFAULT_PRESET_S2_SHIFT                                               0
#define DEFAULT_PRESET_S2_MASK                                       0x00000fff
#define DEFAULT_PRESET_S2_RD(src)                        (((src) & 0x00000fff))
#define DEFAULT_PRESET_S2_WR(src)                   (((u32)(src)) & 0x00000fff)
#define DEFAULT_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_HIGH_SPEED_PRESET	*/ 
/*	 Fields HIGH_SPEED_PRESET_S1	 */
#define HIGH_SPEED_PRESET_S1_WIDTH                                           12
#define HIGH_SPEED_PRESET_S1_SHIFT                                           12
#define HIGH_SPEED_PRESET_S1_MASK                                    0x00fff000
#define HIGH_SPEED_PRESET_S1_RD(src)                 (((src) & 0x00fff000)>>12)
#define HIGH_SPEED_PRESET_S1_WR(src)            (((u32)(src)<<12) & 0x00fff000)
#define HIGH_SPEED_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields HIGH_SPEED_PRESET_S2	 */
#define HIGH_SPEED_PRESET_S2_WIDTH                                           12
#define HIGH_SPEED_PRESET_S2_SHIFT                                            0
#define HIGH_SPEED_PRESET_S2_MASK                                    0x00000fff
#define HIGH_SPEED_PRESET_S2_RD(src)                     (((src) & 0x00000fff))
#define HIGH_SPEED_PRESET_S2_WR(src)                (((u32)(src)) & 0x00000fff)
#define HIGH_SPEED_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_SDR12_PRESET	*/ 
/*	 Fields SDR12_PRESET_S1	 */
#define SDR12_PRESET_S1_WIDTH                                                12
#define SDR12_PRESET_S1_SHIFT                                                12
#define SDR12_PRESET_S1_MASK                                         0x00fff000
#define SDR12_PRESET_S1_RD(src)                      (((src) & 0x00fff000)>>12)
#define SDR12_PRESET_S1_WR(src)                 (((u32)(src)<<12) & 0x00fff000)
#define SDR12_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields SDR12_PRESET_S2	 */
#define SDR12_PRESET_S2_WIDTH                                                12
#define SDR12_PRESET_S2_SHIFT                                                 0
#define SDR12_PRESET_S2_MASK                                         0x00000fff
#define SDR12_PRESET_S2_RD(src)                          (((src) & 0x00000fff))
#define SDR12_PRESET_S2_WR(src)                     (((u32)(src)) & 0x00000fff)
#define SDR12_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_SDR25_PRESET	*/ 
/*	 Fields SDR25_PRESET_S1	 */
#define SDR25_PRESET_S1_WIDTH                                                12
#define SDR25_PRESET_S1_SHIFT                                                12
#define SDR25_PRESET_S1_MASK                                         0x00fff000
#define SDR25_PRESET_S1_RD(src)                      (((src) & 0x00fff000)>>12)
#define SDR25_PRESET_S1_WR(src)                 (((u32)(src)<<12) & 0x00fff000)
#define SDR25_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields SDR25_PRESET_S2	 */
#define SDR25_PRESET_S2_WIDTH                                                12
#define SDR25_PRESET_S2_SHIFT                                                 0
#define SDR25_PRESET_S2_MASK                                         0x00000fff
#define SDR25_PRESET_S2_RD(src)                          (((src) & 0x00000fff))
#define SDR25_PRESET_S2_WR(src)                     (((u32)(src)) & 0x00000fff)
#define SDR25_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_SDR50_PRESET	*/ 
/*	 Fields SDR50_PRESET_S1	 */
#define SDR50_PRESET_S1_WIDTH                                                12
#define SDR50_PRESET_S1_SHIFT                                                12
#define SDR50_PRESET_S1_MASK                                         0x00fff000
#define SDR50_PRESET_S1_RD(src)                      (((src) & 0x00fff000)>>12)
#define SDR50_PRESET_S1_WR(src)                 (((u32)(src)<<12) & 0x00fff000)
#define SDR50_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields SDR50_PRESET_S2	 */
#define SDR50_PRESET_S2_WIDTH                                                12
#define SDR50_PRESET_S2_SHIFT                                                 0
#define SDR50_PRESET_S2_MASK                                         0x00000fff
#define SDR50_PRESET_S2_RD(src)                          (((src) & 0x00000fff))
#define SDR50_PRESET_S2_WR(src)                     (((u32)(src)) & 0x00000fff)
#define SDR50_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_SDR104_PRESET	*/ 
/*	 Fields SDR104_PRESET_S1	 */
#define SDR104_PRESET_S1_WIDTH                                               12
#define SDR104_PRESET_S1_SHIFT                                               12
#define SDR104_PRESET_S1_MASK                                        0x00fff000
#define SDR104_PRESET_S1_RD(src)                     (((src) & 0x00fff000)>>12)
#define SDR104_PRESET_S1_WR(src)                (((u32)(src)<<12) & 0x00fff000)
#define SDR104_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields SDR104_PRESET_S2	 */
#define SDR104_PRESET_S2_WIDTH                                               12
#define SDR104_PRESET_S2_SHIFT                                                0
#define SDR104_PRESET_S2_MASK                                        0x00000fff
#define SDR104_PRESET_S2_RD(src)                         (((src) & 0x00000fff))
#define SDR104_PRESET_S2_WR(src)                    (((u32)(src)) & 0x00000fff)
#define SDR104_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_DDR50_PRESET	*/ 
/*	 Fields DDR50_PRESET_S1	 */
#define DDR50_PRESET_S1_WIDTH                                                12
#define DDR50_PRESET_S1_SHIFT                                                12
#define DDR50_PRESET_S1_MASK                                         0x00fff000
#define DDR50_PRESET_S1_RD(src)                      (((src) & 0x00fff000)>>12)
#define DDR50_PRESET_S1_WR(src)                 (((u32)(src)<<12) & 0x00fff000)
#define DDR50_PRESET_S1_SET(dst,src) \
                      (((dst) & ~0x00fff000) | (((u32)(src)<<12) & 0x00fff000))
/*	 Fields DDR50_PRESET_S2	 */
#define DDR50_PRESET_S2_WIDTH                                                12
#define DDR50_PRESET_S2_SHIFT                                                 0
#define DDR50_PRESET_S2_MASK                                         0x00000fff
#define DDR50_PRESET_S2_RD(src)                          (((src) & 0x00000fff))
#define DDR50_PRESET_S2_WR(src)                     (((u32)(src)) & 0x00000fff)
#define DDR50_PRESET_S2_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register SDHC_CONFIG	*/ 
/*	 Fields CFG_SDIO_RETUNE	 */
#define CFG_SDIO_RETUNE_WIDTH                                                 1
#define CFG_SDIO_RETUNE_SHIFT                                                30
#define CFG_SDIO_RETUNE_MASK                                         0x40000000
#define CFG_SDIO_RETUNE_RD(src)                      (((src) & 0x40000000)>>30)
#define CFG_SDIO_RETUNE_WR(src)                 (((u32)(src)<<30) & 0x40000000)
#define CFG_SDIO_RETUNE_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))

/*	Register SDHC_DATARAM	*/ 
/*	 Fields TEST1B	 */
#define TEST1B_WIDTH                                                          1
#define TEST1B_SHIFT                                                         12
#define TEST1B_MASK                                                  0x00001000
#define TEST1B_RD(src)                               (((src) & 0x00001000)>>12)
#define TEST1B_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define TEST1B_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields TEST1A	 */
#define TEST1A_WIDTH                                                          1
#define TEST1A_SHIFT                                                         11
#define TEST1A_MASK                                                  0x00000800
#define TEST1A_RD(src)                               (((src) & 0x00000800)>>11)
#define TEST1A_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define TEST1A_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields RMEB	 */
#define REGSPEC_RMEB_WIDTH_SDHC_DATARAM                                                    1
#define REGSPEC_RMEB_SHIFT_SDHC_DATARAM                                                   10
#define REGSPEC_RMEB_MASK_SDHC_DATARAM                                            0x00000400
#define REGSPEC_RMEB_RD_SDHC_DATARAM(src)                         (((src) & 0x00000400)>>10)
#define REGSPEC_RMEB_WR_SDHC_DATARAM(src)                    (((u32)(src)<<10) & 0x00000400)
#define REGSPEC_RMEB_SET_SDHC_DATARAM(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields RMEA	 */
#define REGSPEC_RMEA_WIDTH_SDHC_DATARAM                                                    1
#define REGSPEC_RMEA_SHIFT_SDHC_DATARAM                                                    9
#define REGSPEC_RMEA_MASK_SDHC_DATARAM                                            0x00000200
#define REGSPEC_RMEA_RD_SDHC_DATARAM(src)                          (((src) & 0x00000200)>>9)
#define REGSPEC_RMEA_WR_SDHC_DATARAM(src)                     (((u32)(src)<<9) & 0x00000200)
#define REGSPEC_RMEA_SET_SDHC_DATARAM(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields RMB	 */
#define REGSPEC_RMB_WIDTH_SDHC_DATARAM                                                     4
#define REGSPEC_RMB_SHIFT_SDHC_DATARAM                                                     5
#define REGSPEC_RMB_MASK_SDHC_DATARAM                                             0x000001e0
#define REGSPEC_RMB_RD_SDHC_DATARAM(src)                           (((src) & 0x000001e0)>>5)
#define REGSPEC_RMB_WR_SDHC_DATARAM(src)                      (((u32)(src)<<5) & 0x000001e0)
#define REGSPEC_RMB_SET_SDHC_DATARAM(dst,src) \
                       (((dst) & ~0x000001e0) | (((u32)(src)<<5) & 0x000001e0))
/*	 Fields RMA	 */
#define REGSPEC_RMA_WIDTH_SDHC_DATARAM                                                     4
#define REGSPEC_RMA_SHIFT_SDHC_DATARAM                                                     1
#define REGSPEC_RMA_MASK_SDHC_DATARAM                                             0x0000001e
#define REGSPEC_RMA_RD_SDHC_DATARAM(src)                           (((src) & 0x0000001e)>>1)
#define REGSPEC_RMA_WR_SDHC_DATARAM(src)                      (((u32)(src)<<1) & 0x0000001e)
#define REGSPEC_RMA_SET_SDHC_DATARAM(dst,src) \
                       (((dst) & ~0x0000001e) | (((u32)(src)<<1) & 0x0000001e))
/*	 Fields PWRDN_DIS	 */
#define PWRDN_DIS_WIDTH                                                       1
#define PWRDN_DIS_SHIFT                                                       0
#define PWRDN_DIS_MASK                                               0x00000001
#define PWRDN_DIS_RD(src)                                (((src) & 0x00000001))
#define PWRDN_DIS_WR(src)                           (((u32)(src)) & 0x00000001)
#define PWRDN_DIS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_X2H_BRIDGE	*/ 
/*	 Fields CFG_X2H_RD_USE_DEFINED_ONLY	 */
#define CFG_X2H_RD_USE_DEFINED_ONLY_WIDTH                                     1
#define CFG_X2H_RD_USE_DEFINED_ONLY_SHIFT                                     1
#define CFG_X2H_RD_USE_DEFINED_ONLY_MASK                             0x00000002
#define CFG_X2H_RD_USE_DEFINED_ONLY_RD(src)           (((src) & 0x00000002)>>1)
#define CFG_X2H_RD_USE_DEFINED_ONLY_WR(src)      (((u32)(src)<<1) & 0x00000002)
#define CFG_X2H_RD_USE_DEFINED_ONLY_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields CFG_X2H_USE_DEFINED_ONLY	 */
#define CFG_X2H_USE_DEFINED_ONLY_WIDTH                                        1
#define CFG_X2H_USE_DEFINED_ONLY_SHIFT                                        0
#define CFG_X2H_USE_DEFINED_ONLY_MASK                                0x00000001
#define CFG_X2H_USE_DEFINED_ONLY_RD(src)                 (((src) & 0x00000001))
#define CFG_X2H_USE_DEFINED_ONLY_WR(src)            (((u32)(src)) & 0x00000001)
#define CFG_X2H_USE_DEFINED_ONLY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_MODE_SEL	*/ 
/*	 Fields CFG_CTS_PAIR_1	 */
#define CFG_CTS_PAIR_1_WIDTH                                                  1
#define CFG_CTS_PAIR_1_SHIFT                                                  4
#define CFG_CTS_PAIR_1_MASK                                          0x00000010
#define CFG_CTS_PAIR_1_RD(src)                        (((src) & 0x00000010)>>4)
#define CFG_CTS_PAIR_1_WR(src)                   (((u32)(src)<<4) & 0x00000010)
#define CFG_CTS_PAIR_1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields CFG_CTS_PAIR_0	 */
#define CFG_CTS_PAIR_0_WIDTH                                                  1
#define CFG_CTS_PAIR_0_SHIFT                                                  3
#define CFG_CTS_PAIR_0_MASK                                          0x00000008
#define CFG_CTS_PAIR_0_RD(src)                        (((src) & 0x00000008)>>3)
#define CFG_CTS_PAIR_0_WR(src)                   (((u32)(src)<<3) & 0x00000008)
#define CFG_CTS_PAIR_0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields CFG_ENABLE_4BIT_UART_1	 */
#define CFG_ENABLE_4BIT_UART_1_WIDTH                                          1
#define CFG_ENABLE_4BIT_UART_1_SHIFT                                          2
#define CFG_ENABLE_4BIT_UART_1_MASK                                  0x00000004
#define CFG_ENABLE_4BIT_UART_1_RD(src)                (((src) & 0x00000004)>>2)
#define CFG_ENABLE_4BIT_UART_1_WR(src)           (((u32)(src)<<2) & 0x00000004)
#define CFG_ENABLE_4BIT_UART_1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields CFG_ENABLE_4BIT_UART_0	 */
#define CFG_ENABLE_4BIT_UART_0_WIDTH                                          1
#define CFG_ENABLE_4BIT_UART_0_SHIFT                                          1
#define CFG_ENABLE_4BIT_UART_0_MASK                                  0x00000002
#define CFG_ENABLE_4BIT_UART_0_RD(src)                (((src) & 0x00000002)>>1)
#define CFG_ENABLE_4BIT_UART_0_WR(src)           (((u32)(src)<<1) & 0x00000002)
#define CFG_ENABLE_4BIT_UART_0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields CFG_ENABLE_8BIT_UART_0	 */
#define CFG_ENABLE_8BIT_UART_0_WIDTH                                          1
#define CFG_ENABLE_8BIT_UART_0_SHIFT                                          0
#define CFG_ENABLE_8BIT_UART_0_MASK                                  0x00000001
#define CFG_ENABLE_8BIT_UART_0_RD(src)                   (((src) & 0x00000001))
#define CFG_ENABLE_8BIT_UART_0_WR(src)              (((u32)(src)) & 0x00000001)
#define CFG_ENABLE_8BIT_UART_0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ahb2axi_bid	*/ 
/*	 Fields revno	 */
#define REGSPEC_REVNO_WIDTH_AHB2AXI_BID                                                   2
#define REGSPEC_REVNO_SHIFT_AHB2AXI_BID                                                   8
#define REGSPEC_REVNO_MASK_AHB2AXI_BID                                           0x00000300
#define REGSPEC_REVNO_RD_AHB2AXI_BID(src)                         (((src) & 0x00000300)>>8)
#define REGSPEC_REVNO_SET_AHB2AXI_BID(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields busid	 */
#define REGSPEC_BUSID_WIDTH_AHB2AXI_BID                                                   3
#define REGSPEC_BUSID_SHIFT_AHB2AXI_BID                                                   5
#define REGSPEC_BUSID_MASK_AHB2AXI_BID                                           0x000000e0
#define REGSPEC_BUSID_RD_AHB2AXI_BID(src)                         (((src) & 0x000000e0)>>5)
#define REGSPEC_BUSID_SET_AHB2AXI_BID(dst,src) \
                       (((dst) & ~0x000000e0) | (((u32)(src)<<5) & 0x000000e0))
/*	 Fields deviceid	 */
#define REGSPEC_DEVICEID_WIDTH_AHB2AXI_BID                                                5
#define REGSPEC_DEVICEID_SHIFT_AHB2AXI_BID                                                0
#define REGSPEC_DEVICEID_MASK_AHB2AXI_BID                                        0x0000001f
#define REGSPEC_DEVICEID_RD_AHB2AXI_BID(src)                         (((src) & 0x0000001f))
#define REGSPEC_DEVICEID_SET_AHB2AXI_BID(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ahbc_INT	*/ 
/*	 Fields sdhc_wr_decerr_reported	 */
#define SDHC_WR_DECERR_REPORTED_WIDTH                                         1
#define SDHC_WR_DECERR_REPORTED_SHIFT                                         3
#define SDHC_WR_DECERR_REPORTED_MASK                                 0x00000008
#define SDHC_WR_DECERR_REPORTED_RD(src)               (((src) & 0x00000008)>>3)
#define SDHC_WR_DECERR_REPORTED_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields sdhc_wr_slverr_reported	 */
#define SDHC_WR_SLVERR_REPORTED_WIDTH                                         1
#define SDHC_WR_SLVERR_REPORTED_SHIFT                                         2
#define SDHC_WR_SLVERR_REPORTED_MASK                                 0x00000004
#define SDHC_WR_SLVERR_REPORTED_RD(src)               (((src) & 0x00000004)>>2)
#define SDHC_WR_SLVERR_REPORTED_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields sdhc_rd_decerr_reported	 */
#define SDHC_RD_DECERR_REPORTED_WIDTH                                         1
#define SDHC_RD_DECERR_REPORTED_SHIFT                                         1
#define SDHC_RD_DECERR_REPORTED_MASK                                 0x00000002
#define SDHC_RD_DECERR_REPORTED_RD(src)               (((src) & 0x00000002)>>1)
#define SDHC_RD_DECERR_REPORTED_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields sdhc_rd_slverr_reported	 */
#define SDHC_RD_SLVERR_REPORTED_WIDTH                                         1
#define SDHC_RD_SLVERR_REPORTED_SHIFT                                         0
#define SDHC_RD_SLVERR_REPORTED_MASK                                 0x00000001
#define SDHC_RD_SLVERR_REPORTED_RD(src)                  (((src) & 0x00000001))
#define SDHC_RD_SLVERR_REPORTED_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AIM_0_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_WIDTH                                              20
#define AIM_AHB_ADDRESS_N_SHIFT                                               0
#define AIM_AHB_ADDRESS_N_MASK                                       0x000fffff
#define AIM_AHB_ADDRESS_N_RD(src)                        (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_WR(src)                   (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_0_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_WIDTH                                                        1
#define AIM_EN_N_SHIFT                                                       31
#define AIM_EN_N_MASK                                                0x80000000
#define AIM_EN_N_RD(src)                             (((src) & 0x80000000)>>31)
#define AIM_EN_N_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_WIDTH                                                            3
#define ARSB_SHIFT                                                           23
#define ARSB_MASK                                                    0x03800000
#define ARSB_RD(src)                                 (((src) & 0x03800000)>>23)
#define ARSB_WR(src)                            (((u32)(src)<<23) & 0x03800000)
#define ARSB_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_WIDTH                                                            3
#define AWSB_SHIFT                                                           20
#define AWSB_MASK                                                    0x00700000
#define AWSB_RD(src)                                 (((src) & 0x00700000)>>20)
#define AWSB_WR(src)                            (((u32)(src)<<20) & 0x00700000)
#define AWSB_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_WIDTH                                                     20
#define AIM_MASK_N_SHIFT                                                      0
#define AIM_MASK_N_MASK                                              0x000fffff
#define AIM_MASK_N_RD(src)                               (((src) & 0x000fffff))
#define AIM_MASK_N_WR(src)                          (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_0_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_WIDTH                                           20
#define AIM_AXI_ADDRESS_LO_N_SHIFT                                            0
#define AIM_AXI_ADDRESS_LO_N_MASK                                    0x000fffff
#define AIM_AXI_ADDRESS_LO_N_RD(src)                     (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_0_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_WIDTH                                           12
#define AIM_AXI_ADDRESS_HI_N_SHIFT                                           20
#define AIM_AXI_ADDRESS_HI_N_MASK                                    0xfff00000
#define AIM_AXI_ADDRESS_HI_N_RD(src)                 (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_WR(src)            (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_1_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F1_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F1_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F1_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F1_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F1_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_1_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F1_WIDTH                                                     1
#define AIM_EN_N_F1_SHIFT                                                    31
#define AIM_EN_N_F1_MASK                                             0x80000000
#define AIM_EN_N_F1_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F1_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F1_WIDTH                                                         3
#define ARSB_F1_SHIFT                                                        23
#define ARSB_F1_MASK                                                 0x03800000
#define ARSB_F1_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F1_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F1_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F1_WIDTH                                                         3
#define AWSB_F1_SHIFT                                                        20
#define AWSB_F1_MASK                                                 0x00700000
#define AWSB_F1_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F1_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F1_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F1_WIDTH                                                  20
#define AIM_MASK_N_F1_SHIFT                                                   0
#define AIM_MASK_N_F1_MASK                                           0x000fffff
#define AIM_MASK_N_F1_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F1_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_1_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F1_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F1_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F1_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F1_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F1_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_1_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F1_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F1_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F1_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F1_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F1_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F1_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_2_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F2_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F2_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F2_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F2_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F2_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_2_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F2_WIDTH                                                     1
#define AIM_EN_N_F2_SHIFT                                                    31
#define AIM_EN_N_F2_MASK                                             0x80000000
#define AIM_EN_N_F2_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F2_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F2_WIDTH                                                         3
#define ARSB_F2_SHIFT                                                        23
#define ARSB_F2_MASK                                                 0x03800000
#define ARSB_F2_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F2_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F2_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F2_WIDTH                                                         3
#define AWSB_F2_SHIFT                                                        20
#define AWSB_F2_MASK                                                 0x00700000
#define AWSB_F2_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F2_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F2_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F2_WIDTH                                                  20
#define AIM_MASK_N_F2_SHIFT                                                   0
#define AIM_MASK_N_F2_MASK                                           0x000fffff
#define AIM_MASK_N_F2_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F2_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_2_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F2_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F2_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F2_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F2_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F2_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_2_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F2_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F2_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F2_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F2_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F2_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F2_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_3_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F3_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F3_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F3_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F3_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F3_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F3_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_3_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F3_WIDTH                                                     1
#define AIM_EN_N_F3_SHIFT                                                    31
#define AIM_EN_N_F3_MASK                                             0x80000000
#define AIM_EN_N_F3_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F3_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F3_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F3_WIDTH                                                         3
#define ARSB_F3_SHIFT                                                        23
#define ARSB_F3_MASK                                                 0x03800000
#define ARSB_F3_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F3_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F3_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F3_WIDTH                                                         3
#define AWSB_F3_SHIFT                                                        20
#define AWSB_F3_MASK                                                 0x00700000
#define AWSB_F3_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F3_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F3_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F3_WIDTH                                                  20
#define AIM_MASK_N_F3_SHIFT                                                   0
#define AIM_MASK_N_F3_MASK                                           0x000fffff
#define AIM_MASK_N_F3_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F3_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F3_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_3_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F3_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F3_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F3_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F3_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F3_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F3_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_3_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F3_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F3_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F3_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F3_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F3_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F3_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_4_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F4_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F4_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F4_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F4_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F4_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F4_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_4_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F4_WIDTH                                                     1
#define AIM_EN_N_F4_SHIFT                                                    31
#define AIM_EN_N_F4_MASK                                             0x80000000
#define AIM_EN_N_F4_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F4_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F4_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F4_WIDTH                                                         3
#define ARSB_F4_SHIFT                                                        23
#define ARSB_F4_MASK                                                 0x03800000
#define ARSB_F4_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F4_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F4_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F4_WIDTH                                                         3
#define AWSB_F4_SHIFT                                                        20
#define AWSB_F4_MASK                                                 0x00700000
#define AWSB_F4_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F4_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F4_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F4_WIDTH                                                  20
#define AIM_MASK_N_F4_SHIFT                                                   0
#define AIM_MASK_N_F4_MASK                                           0x000fffff
#define AIM_MASK_N_F4_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F4_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F4_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_4_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F4_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F4_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F4_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F4_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F4_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F4_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_4_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F4_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F4_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F4_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F4_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F4_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F4_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_5_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F5_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F5_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F5_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F5_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F5_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F5_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_5_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F5_WIDTH                                                     1
#define AIM_EN_N_F5_SHIFT                                                    31
#define AIM_EN_N_F5_MASK                                             0x80000000
#define AIM_EN_N_F5_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F5_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F5_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F5_WIDTH                                                         3
#define ARSB_F5_SHIFT                                                        23
#define ARSB_F5_MASK                                                 0x03800000
#define ARSB_F5_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F5_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F5_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F5_WIDTH                                                         3
#define AWSB_F5_SHIFT                                                        20
#define AWSB_F5_MASK                                                 0x00700000
#define AWSB_F5_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F5_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F5_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F5_WIDTH                                                  20
#define AIM_MASK_N_F5_SHIFT                                                   0
#define AIM_MASK_N_F5_MASK                                           0x000fffff
#define AIM_MASK_N_F5_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F5_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F5_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_5_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F5_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F5_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F5_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F5_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F5_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F5_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_5_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F5_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F5_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F5_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F5_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F5_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F5_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_6_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F6_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F6_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F6_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F6_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F6_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F6_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_6_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F6_WIDTH                                                     1
#define AIM_EN_N_F6_SHIFT                                                    31
#define AIM_EN_N_F6_MASK                                             0x80000000
#define AIM_EN_N_F6_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F6_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F6_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F6_WIDTH                                                         3
#define ARSB_F6_SHIFT                                                        23
#define ARSB_F6_MASK                                                 0x03800000
#define ARSB_F6_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F6_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F6_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F6_WIDTH                                                         3
#define AWSB_F6_SHIFT                                                        20
#define AWSB_F6_MASK                                                 0x00700000
#define AWSB_F6_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F6_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F6_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F6_WIDTH                                                  20
#define AIM_MASK_N_F6_SHIFT                                                   0
#define AIM_MASK_N_F6_MASK                                           0x000fffff
#define AIM_MASK_N_F6_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F6_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F6_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_6_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F6_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F6_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F6_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F6_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F6_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F6_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_6_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F6_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F6_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F6_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F6_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F6_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F6_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_7_AHB	*/ 
/*	 Fields aim_ahb_address_n	 */
#define AIM_AHB_ADDRESS_N_F7_WIDTH                                           20
#define AIM_AHB_ADDRESS_N_F7_SHIFT                                            0
#define AIM_AHB_ADDRESS_N_F7_MASK                                    0x000fffff
#define AIM_AHB_ADDRESS_N_F7_RD(src)                     (((src) & 0x000fffff))
#define AIM_AHB_ADDRESS_N_F7_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AHB_ADDRESS_N_F7_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_7_SIZE_CTL	*/ 
/*	 Fields aim_en_n	 */
#define AIM_EN_N_F7_WIDTH                                                     1
#define AIM_EN_N_F7_SHIFT                                                    31
#define AIM_EN_N_F7_MASK                                             0x80000000
#define AIM_EN_N_F7_RD(src)                          (((src) & 0x80000000)>>31)
#define AIM_EN_N_F7_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AIM_EN_N_F7_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields arsb	 */
#define ARSB_F7_WIDTH                                                         3
#define ARSB_F7_SHIFT                                                        23
#define ARSB_F7_MASK                                                 0x03800000
#define ARSB_F7_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F7_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F7_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F7_WIDTH                                                         3
#define AWSB_F7_SHIFT                                                        20
#define AWSB_F7_MASK                                                 0x00700000
#define AWSB_F7_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F7_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F7_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_mask_n	 */
#define AIM_MASK_N_F7_WIDTH                                                  20
#define AIM_MASK_N_F7_SHIFT                                                   0
#define AIM_MASK_N_F7_MASK                                           0x000fffff
#define AIM_MASK_N_F7_RD(src)                            (((src) & 0x000fffff))
#define AIM_MASK_N_F7_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AIM_MASK_N_F7_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_7_AXI_LO	*/ 
/*	 Fields aim_axi_address_LO_n	 */
#define AIM_AXI_ADDRESS_LO_N_F7_WIDTH                                        20
#define AIM_AXI_ADDRESS_LO_N_F7_SHIFT                                         0
#define AIM_AXI_ADDRESS_LO_N_F7_MASK                                 0x000fffff
#define AIM_AXI_ADDRESS_LO_N_F7_RD(src)                  (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_N_F7_WR(src)             (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_N_F7_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_7_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_n	 */
#define AIM_AXI_ADDRESS_HI_N_F7_WIDTH                                        12
#define AIM_AXI_ADDRESS_HI_N_F7_SHIFT                                        20
#define AIM_AXI_ADDRESS_HI_N_F7_MASK                                 0xfff00000
#define AIM_AXI_ADDRESS_HI_N_F7_RD(src)              (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_N_F7_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_N_F7_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AIM_8_SIZE_CTL	*/ 
/*	 Fields aim_mask_8	 */
#define AIM_MASK_8_WIDTH                                                     20
#define AIM_MASK_8_SHIFT                                                      0
#define AIM_MASK_8_MASK                                              0x000fffff
#define AIM_MASK_8_RD(src)                               (((src) & 0x000fffff))
#define AIM_MASK_8_WR(src)                          (((u32)(src)) & 0x000fffff)
#define AIM_MASK_8_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_8_AXI_LO	*/ 
/*	 Fields arsb	 */
#define ARSB_F8_WIDTH                                                         3
#define ARSB_F8_SHIFT                                                        23
#define ARSB_F8_MASK                                                 0x03800000
#define ARSB_F8_RD(src)                              (((src) & 0x03800000)>>23)
#define ARSB_F8_WR(src)                         (((u32)(src)<<23) & 0x03800000)
#define ARSB_F8_SET(dst,src) \
                      (((dst) & ~0x03800000) | (((u32)(src)<<23) & 0x03800000))
/*	 Fields awsb	 */
#define AWSB_F8_WIDTH                                                         3
#define AWSB_F8_SHIFT                                                        20
#define AWSB_F8_MASK                                                 0x00700000
#define AWSB_F8_RD(src)                              (((src) & 0x00700000)>>20)
#define AWSB_F8_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define AWSB_F8_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields aim_axi_address_LO_8	 */
#define AIM_AXI_ADDRESS_LO_8_WIDTH                                           20
#define AIM_AXI_ADDRESS_LO_8_SHIFT                                            0
#define AIM_AXI_ADDRESS_LO_8_MASK                                    0x000fffff
#define AIM_AXI_ADDRESS_LO_8_RD(src)                     (((src) & 0x000fffff))
#define AIM_AXI_ADDRESS_LO_8_WR(src)                (((u32)(src)) & 0x000fffff)
#define AIM_AXI_ADDRESS_LO_8_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AIM_8_AXI_HI	*/ 
/*	 Fields aim_axi_address_HI_8	 */
#define AIM_AXI_ADDRESS_HI_8_WIDTH                                           12
#define AIM_AXI_ADDRESS_HI_8_SHIFT                                           20
#define AIM_AXI_ADDRESS_HI_8_MASK                                    0xfff00000
#define AIM_AXI_ADDRESS_HI_8_RD(src)                 (((src) & 0xfff00000)>>20)
#define AIM_AXI_ADDRESS_HI_8_WR(src)            (((u32)(src)<<20) & 0xfff00000)
#define AIM_AXI_ADDRESS_HI_8_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AOM_0_AXI_LO	*/ 
/*	 Fields aom_axi_address_LO_n	 */
#define AOM_AXI_ADDRESS_LO_N_WIDTH                                           20
#define AOM_AXI_ADDRESS_LO_N_SHIFT                                            0
#define AOM_AXI_ADDRESS_LO_N_MASK                                    0x000fffff
#define AOM_AXI_ADDRESS_LO_N_RD(src)                     (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_LO_N_WR(src)                (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_LO_N_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_0_AXI_HI	*/ 
/*	 Fields aom_axi_address_HI_n	 */
#define AOM_AXI_ADDRESS_HI_N_WIDTH                                           12
#define AOM_AXI_ADDRESS_HI_N_SHIFT                                           20
#define AOM_AXI_ADDRESS_HI_N_MASK                                    0xfff00000
#define AOM_AXI_ADDRESS_HI_N_RD(src)                 (((src) & 0xfff00000)>>20)
#define AOM_AXI_ADDRESS_HI_N_WR(src)            (((u32)(src)<<20) & 0xfff00000)
#define AOM_AXI_ADDRESS_HI_N_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AOM_0_SIZE_CTL	*/ 
/*	 Fields aom_en_n	 */
#define AOM_EN_N_WIDTH                                                        1
#define AOM_EN_N_SHIFT                                                       31
#define AOM_EN_N_MASK                                                0x80000000
#define AOM_EN_N_RD(src)                             (((src) & 0x80000000)>>31)
#define AOM_EN_N_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define AOM_EN_N_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields aom_mask_n	 */
#define AOM_MASK_N_WIDTH                                                     20
#define AOM_MASK_N_SHIFT                                                      0
#define AOM_MASK_N_MASK                                              0x000fffff
#define AOM_MASK_N_RD(src)                               (((src) & 0x000fffff))
#define AOM_MASK_N_WR(src)                          (((u32)(src)) & 0x000fffff)
#define AOM_MASK_N_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_0_AHB	*/ 
/*	 Fields aom_axi_address_n	 */
#define AOM_AXI_ADDRESS_N_WIDTH                                              20
#define AOM_AXI_ADDRESS_N_SHIFT                                               0
#define AOM_AXI_ADDRESS_N_MASK                                       0x000fffff
#define AOM_AXI_ADDRESS_N_RD(src)                        (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_N_WR(src)                   (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_N_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_1_AXI_LO	*/ 
/*	 Fields aom_axi_address_LO_n	 */
#define AOM_AXI_ADDRESS_LO_N_F1_WIDTH                                        20
#define AOM_AXI_ADDRESS_LO_N_F1_SHIFT                                         0
#define AOM_AXI_ADDRESS_LO_N_F1_MASK                                 0x000fffff
#define AOM_AXI_ADDRESS_LO_N_F1_RD(src)                  (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_LO_N_F1_WR(src)             (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_LO_N_F1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_1_AXI_HI	*/ 
/*	 Fields aom_axi_address_HI_n	 */
#define AOM_AXI_ADDRESS_HI_N_F1_WIDTH                                        12
#define AOM_AXI_ADDRESS_HI_N_F1_SHIFT                                        20
#define AOM_AXI_ADDRESS_HI_N_F1_MASK                                 0xfff00000
#define AOM_AXI_ADDRESS_HI_N_F1_RD(src)              (((src) & 0xfff00000)>>20)
#define AOM_AXI_ADDRESS_HI_N_F1_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AOM_AXI_ADDRESS_HI_N_F1_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AOM_1_SIZE_CTL	*/ 
/*	 Fields aom_en_n	 */
#define AOM_EN_N_F1_WIDTH                                                     1
#define AOM_EN_N_F1_SHIFT                                                    31
#define AOM_EN_N_F1_MASK                                             0x80000000
#define AOM_EN_N_F1_RD(src)                          (((src) & 0x80000000)>>31)
#define AOM_EN_N_F1_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AOM_EN_N_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields aom_mask_n	 */
#define AOM_MASK_N_F1_WIDTH                                                  20
#define AOM_MASK_N_F1_SHIFT                                                   0
#define AOM_MASK_N_F1_MASK                                           0x000fffff
#define AOM_MASK_N_F1_RD(src)                            (((src) & 0x000fffff))
#define AOM_MASK_N_F1_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AOM_MASK_N_F1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_1_AHB	*/ 
/*	 Fields aom_axi_address_n	 */
#define AOM_AXI_ADDRESS_N_F1_WIDTH                                           20
#define AOM_AXI_ADDRESS_N_F1_SHIFT                                            0
#define AOM_AXI_ADDRESS_N_F1_MASK                                    0x000fffff
#define AOM_AXI_ADDRESS_N_F1_RD(src)                     (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_N_F1_WR(src)                (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_N_F1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_2_AXI_LO	*/ 
/*	 Fields aom_axi_address_LO_n	 */
#define AOM_AXI_ADDRESS_LO_N_F2_WIDTH                                        20
#define AOM_AXI_ADDRESS_LO_N_F2_SHIFT                                         0
#define AOM_AXI_ADDRESS_LO_N_F2_MASK                                 0x000fffff
#define AOM_AXI_ADDRESS_LO_N_F2_RD(src)                  (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_LO_N_F2_WR(src)             (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_LO_N_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_2_AXI_HI	*/ 
/*	 Fields aom_axi_address_HI_n	 */
#define AOM_AXI_ADDRESS_HI_N_F2_WIDTH                                        12
#define AOM_AXI_ADDRESS_HI_N_F2_SHIFT                                        20
#define AOM_AXI_ADDRESS_HI_N_F2_MASK                                 0xfff00000
#define AOM_AXI_ADDRESS_HI_N_F2_RD(src)              (((src) & 0xfff00000)>>20)
#define AOM_AXI_ADDRESS_HI_N_F2_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AOM_AXI_ADDRESS_HI_N_F2_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AOM_2_SIZE_CTL	*/ 
/*	 Fields aom_en_n	 */
#define AOM_EN_N_F2_WIDTH                                                     1
#define AOM_EN_N_F2_SHIFT                                                    31
#define AOM_EN_N_F2_MASK                                             0x80000000
#define AOM_EN_N_F2_RD(src)                          (((src) & 0x80000000)>>31)
#define AOM_EN_N_F2_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AOM_EN_N_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields aom_mask_n	 */
#define AOM_MASK_N_F2_WIDTH                                                  20
#define AOM_MASK_N_F2_SHIFT                                                   0
#define AOM_MASK_N_F2_MASK                                           0x000fffff
#define AOM_MASK_N_F2_RD(src)                            (((src) & 0x000fffff))
#define AOM_MASK_N_F2_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AOM_MASK_N_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_2_AHB	*/ 
/*	 Fields aom_axi_address_n	 */
#define AOM_AXI_ADDRESS_N_F2_WIDTH                                           20
#define AOM_AXI_ADDRESS_N_F2_SHIFT                                            0
#define AOM_AXI_ADDRESS_N_F2_MASK                                    0x000fffff
#define AOM_AXI_ADDRESS_N_F2_RD(src)                     (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_N_F2_WR(src)                (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_N_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_3_AXI_LO	*/ 
/*	 Fields aom_axi_address_LO_n	 */
#define AOM_AXI_ADDRESS_LO_N_F3_WIDTH                                        20
#define AOM_AXI_ADDRESS_LO_N_F3_SHIFT                                         0
#define AOM_AXI_ADDRESS_LO_N_F3_MASK                                 0x000fffff
#define AOM_AXI_ADDRESS_LO_N_F3_RD(src)                  (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_LO_N_F3_WR(src)             (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_LO_N_F3_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_3_AXI_HI	*/ 
/*	 Fields aom_axi_address_HI_n	 */
#define AOM_AXI_ADDRESS_HI_N_F3_WIDTH                                        12
#define AOM_AXI_ADDRESS_HI_N_F3_SHIFT                                        20
#define AOM_AXI_ADDRESS_HI_N_F3_MASK                                 0xfff00000
#define AOM_AXI_ADDRESS_HI_N_F3_RD(src)              (((src) & 0xfff00000)>>20)
#define AOM_AXI_ADDRESS_HI_N_F3_WR(src)         (((u32)(src)<<20) & 0xfff00000)
#define AOM_AXI_ADDRESS_HI_N_F3_SET(dst,src) \
                      (((dst) & ~0xfff00000) | (((u32)(src)<<20) & 0xfff00000))

/*	Register AOM_3_SIZE_CTL	*/ 
/*	 Fields aom_en_n	 */
#define AOM_EN_N_F3_WIDTH                                                     1
#define AOM_EN_N_F3_SHIFT                                                    31
#define AOM_EN_N_F3_MASK                                             0x80000000
#define AOM_EN_N_F3_RD(src)                          (((src) & 0x80000000)>>31)
#define AOM_EN_N_F3_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define AOM_EN_N_F3_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields aom_mask_n	 */
#define AOM_MASK_N_F3_WIDTH                                                  20
#define AOM_MASK_N_F3_SHIFT                                                   0
#define AOM_MASK_N_F3_MASK                                           0x000fffff
#define AOM_MASK_N_F3_RD(src)                            (((src) & 0x000fffff))
#define AOM_MASK_N_F3_WR(src)                       (((u32)(src)) & 0x000fffff)
#define AOM_MASK_N_F3_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register AOM_3_AHB	*/ 
/*	 Fields aom_axi_address_n	 */
#define AOM_AXI_ADDRESS_N_F3_WIDTH                                           20
#define AOM_AXI_ADDRESS_N_F3_SHIFT                                            0
#define AOM_AXI_ADDRESS_N_F3_MASK                                    0x000fffff
#define AOM_AXI_ADDRESS_N_F3_RD(src)                     (((src) & 0x000fffff))
#define AOM_AXI_ADDRESS_N_F3_WR(src)                (((u32)(src)) & 0x000fffff)
#define AOM_AXI_ADDRESS_N_F3_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register ahb_rd_err_addr	*/ 
/*	 Fields addr	 */
#define REGSPEC_ADDR_WIDTH                                                   32
#define REGSPEC_ADDR_SHIFT                                                    0
#define REGSPEC_ADDR_MASK                                            0xffffffff
#define REGSPEC_ADDR_RD(src)                             (((src) & 0xffffffff))
#define REGSPEC_ADDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ahb_rd_err_attributes	*/ 
/*	 Fields ahb_htrans	 */
#define AHB_HTRANS_WIDTH                                                      2
#define AHB_HTRANS_SHIFT                                                     11
#define AHB_HTRANS_MASK                                              0x00001800
#define AHB_HTRANS_RD(src)                           (((src) & 0x00001800)>>11)
#define AHB_HTRANS_SET(dst,src) \
                      (((dst) & ~0x00001800) | (((u32)(src)<<11) & 0x00001800))
/*	 Fields ahb_hsize	 */
#define AHB_HSIZE_WIDTH                                                       3
#define AHB_HSIZE_SHIFT                                                       8
#define AHB_HSIZE_MASK                                               0x00000700
#define AHB_HSIZE_RD(src)                             (((src) & 0x00000700)>>8)
#define AHB_HSIZE_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields ahb_hburst	 */
#define AHB_HBURST_WIDTH                                                      3
#define AHB_HBURST_SHIFT                                                      5
#define AHB_HBURST_MASK                                              0x000000e0
#define AHB_HBURST_RD(src)                            (((src) & 0x000000e0)>>5)
#define AHB_HBURST_SET(dst,src) \
                       (((dst) & ~0x000000e0) | (((u32)(src)<<5) & 0x000000e0))
/*	 Fields err_addr_decode	 */
#define ERR_ADDR_DECODE_WIDTH                                                 1
#define ERR_ADDR_DECODE_SHIFT                                                 4
#define ERR_ADDR_DECODE_MASK                                         0x00000010
#define ERR_ADDR_DECODE_RD(src)                       (((src) & 0x00000010)>>4)
#define ERR_ADDR_DECODE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ahb_rd_err	 */
#define AHB_RD_ERR_WIDTH                                                      1
#define AHB_RD_ERR_SHIFT                                                      0
#define AHB_RD_ERR_MASK                                              0x00000001
#define AHB_RD_ERR_RD(src)                               (((src) & 0x00000001))
#define AHB_RD_ERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ahb_wr_err_addr	*/ 
/*	 Fields addr	 */
#define REGSPEC_ADDR_F1_WIDTH                                                32
#define REGSPEC_ADDR_F1_SHIFT                                                 0
#define REGSPEC_ADDR_F1_MASK                                         0xffffffff
#define REGSPEC_ADDR_F1_RD(src)                          (((src) & 0xffffffff))
#define REGSPEC_ADDR_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ahb_wr_err_data	*/ 
/*	 Fields data	 */
#define DATA_WIDTH                                                           32
#define DATA_SHIFT                                                            0
#define DATA_MASK                                                    0xffffffff
#define DATA_RD(src)                                     (((src) & 0xffffffff))
#define DATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ahb_wr_err_attributes	*/ 
/*	 Fields ahb_htrans	 */
#define AHB_HTRANS_F1_WIDTH                                                   2
#define AHB_HTRANS_F1_SHIFT                                                  11
#define AHB_HTRANS_F1_MASK                                           0x00001800
#define AHB_HTRANS_F1_RD(src)                        (((src) & 0x00001800)>>11)
#define AHB_HTRANS_F1_SET(dst,src) \
                      (((dst) & ~0x00001800) | (((u32)(src)<<11) & 0x00001800))
/*	 Fields ahb_hsize	 */
#define AHB_HSIZE_F1_WIDTH                                                    3
#define AHB_HSIZE_F1_SHIFT                                                    8
#define AHB_HSIZE_F1_MASK                                            0x00000700
#define AHB_HSIZE_F1_RD(src)                          (((src) & 0x00000700)>>8)
#define AHB_HSIZE_F1_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields ahb_hburst	 */
#define AHB_HBURST_F1_WIDTH                                                   3
#define AHB_HBURST_F1_SHIFT                                                   5
#define AHB_HBURST_F1_MASK                                           0x000000e0
#define AHB_HBURST_F1_RD(src)                         (((src) & 0x000000e0)>>5)
#define AHB_HBURST_F1_SET(dst,src) \
                       (((dst) & ~0x000000e0) | (((u32)(src)<<5) & 0x000000e0))
/*	 Fields err_addr_decode	 */
#define ERR_ADDR_DECODE_F1_WIDTH                                              1
#define ERR_ADDR_DECODE_F1_SHIFT                                              4
#define ERR_ADDR_DECODE_F1_MASK                                      0x00000010
#define ERR_ADDR_DECODE_F1_RD(src)                    (((src) & 0x00000010)>>4)
#define ERR_ADDR_DECODE_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ahb_wr_err	 */
#define AHB_WR_ERR_WIDTH                                                      1
#define AHB_WR_ERR_SHIFT                                                      0
#define AHB_WR_ERR_MASK                                              0x00000001
#define AHB_WR_ERR_RD(src)                               (((src) & 0x00000001))
#define AHB_WR_ERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_INTR_CTL	*/ 
/*	 Fields sdhc_int	 */
#define SDHC_INT_WIDTH                                                        1
#define SDHC_INT_SHIFT                                                        6
#define SDHC_INT_MASK                                                0x00000040
#define SDHC_INT_RD(src)                              (((src) & 0x00000040)>>6)
#define SDHC_INT_WR(src)                         (((u32)(src)<<6) & 0x00000040)
#define SDHC_INT_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ahbc_spi_1_int	 */
#define AHBC_SPI_1_INT_WIDTH                                                  1
#define AHBC_SPI_1_INT_SHIFT                                                  5
#define AHBC_SPI_1_INT_MASK                                          0x00000020
#define AHBC_SPI_1_INT_RD(src)                        (((src) & 0x00000020)>>5)
#define AHBC_SPI_1_INT_WR(src)                   (((u32)(src)<<5) & 0x00000020)
#define AHBC_SPI_1_INT_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ahbc_spi_0_int	 */
#define AHBC_SPI_0_INT_WIDTH                                                  1
#define AHBC_SPI_0_INT_SHIFT                                                  4
#define AHBC_SPI_0_INT_MASK                                          0x00000010
#define AHBC_SPI_0_INT_RD(src)                        (((src) & 0x00000010)>>4)
#define AHBC_SPI_0_INT_WR(src)                   (((u32)(src)<<4) & 0x00000010)
#define AHBC_SPI_0_INT_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ahbc_uart_3_int	 */
#define AHBC_UART_3_INT_WIDTH                                                 1
#define AHBC_UART_3_INT_SHIFT                                                 3
#define AHBC_UART_3_INT_MASK                                         0x00000008
#define AHBC_UART_3_INT_RD(src)                       (((src) & 0x00000008)>>3)
#define AHBC_UART_3_INT_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define AHBC_UART_3_INT_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ahbc_uart_2_int	 */
#define AHBC_UART_2_INT_WIDTH                                                 1
#define AHBC_UART_2_INT_SHIFT                                                 2
#define AHBC_UART_2_INT_MASK                                         0x00000004
#define AHBC_UART_2_INT_RD(src)                       (((src) & 0x00000004)>>2)
#define AHBC_UART_2_INT_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define AHBC_UART_2_INT_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ahbc_uart_1_int	 */
#define AHBC_UART_1_INT_WIDTH                                                 1
#define AHBC_UART_1_INT_SHIFT                                                 1
#define AHBC_UART_1_INT_MASK                                         0x00000002
#define AHBC_UART_1_INT_RD(src)                       (((src) & 0x00000002)>>1)
#define AHBC_UART_1_INT_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define AHBC_UART_1_INT_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ahbc_uart_0_int	 */
#define AHBC_UART_0_INT_WIDTH                                                 1
#define AHBC_UART_0_INT_SHIFT                                                 0
#define AHBC_UART_0_INT_MASK                                         0x00000001
#define AHBC_UART_0_INT_RD(src)                          (((src) & 0x00000001))
#define AHBC_UART_0_INT_WR(src)                     (((u32)(src)) & 0x00000001)
#define AHBC_UART_0_INT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register cfg_pin_mux_sel_0	*/ 
/*	 Fields SEL	 */
#define REGSPEC_SEL0_WIDTH                                                   16
#define REGSPEC_SEL0_SHIFT                                                    0
#define REGSPEC_SEL0_MASK                                            0x0000ffff
#define REGSPEC_SEL0_RD(src)                             (((src) & 0x0000ffff))
#define REGSPEC_SEL0_WR(src)                        (((u32)(src)) & 0x0000ffff)
#define REGSPEC_SEL0_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register cfg_pin_mux_sel_1	*/ 
/*	 Fields SEL	 */
#define REGSPEC_SEL1_WIDTH                                                   32
#define REGSPEC_SEL1_SHIFT                                                    0
#define REGSPEC_SEL1_MASK                                            0xffffffff
#define REGSPEC_SEL1_RD(src)                             (((src) & 0xffffffff))
#define REGSPEC_SEL1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define REGSPEC_SEL1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register cfg_pin_mux_sel_2	*/ 
/*	 Fields SEL	 */
#define REGSPEC_SEL2_WIDTH                                                   16
#define REGSPEC_SEL2_SHIFT                                                    0
#define REGSPEC_SEL2_MASK                                            0x0000ffff
#define REGSPEC_SEL2_RD(src)                             (((src) & 0x0000ffff))
#define REGSPEC_SEL2_WR(src)                        (((u32)(src)) & 0x0000ffff)
#define REGSPEC_SEL2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_USBH0	*/ 
/*	 Fields pullup_n	 */
#define PULLUP_N0_WIDTH                                                       1
#define PULLUP_N0_SHIFT                                                       5
#define PULLUP_N0_MASK                                               0x00000020
#define PULLUP_N0_RD(src)                             (((src) & 0x00000020)>>5)
#define PULLUP_N0_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define PULLUP_N0_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields sre_n	 */
#define SRE_N0_WIDTH                                                          1
#define SRE_N0_SHIFT                                                          4
#define SRE_N0_MASK                                                  0x00000010
#define SRE_N0_RD(src)                                (((src) & 0x00000010)>>4)
#define SRE_N0_WR(src)                           (((u32)(src)<<4) & 0x00000010)
#define SRE_N0_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields pulldn_n	 */
#define PULLDN_N0_WIDTH                                                       1
#define PULLDN_N0_SHIFT                                                       2
#define PULLDN_N0_MASK                                               0x00000004
#define PULLDN_N0_RD(src)                             (((src) & 0x00000004)>>2)
#define PULLDN_N0_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define PULLDN_N0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields pdwn_n	 */
#define PDWN_N0_WIDTH                                                         1
#define PDWN_N0_SHIFT                                                         1
#define PDWN_N0_MASK                                                 0x00000002
#define PDWN_N0_RD(src)                               (((src) & 0x00000002)>>1)
#define PDWN_N0_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PDWN_N0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields hyst_n	 */
#define HYST_N0_WIDTH                                                         1
#define HYST_N0_SHIFT                                                         0
#define HYST_N0_MASK                                                 0x00000001
#define HYST_N0_RD(src)                                  (((src) & 0x00000001))
#define HYST_N0_WR(src)                             (((u32)(src)) & 0x00000001)
#define HYST_N0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_USBH1	*/ 
/*	 Fields pullup_n	 */
#define PULLUP_N1_WIDTH                                                       1
#define PULLUP_N1_SHIFT                                                       5
#define PULLUP_N1_MASK                                               0x00000020
#define PULLUP_N1_RD(src)                             (((src) & 0x00000020)>>5)
#define PULLUP_N1_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define PULLUP_N1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields sre_n	 */
#define SRE_N1_WIDTH                                                          1
#define SRE_N1_SHIFT                                                          4
#define SRE_N1_MASK                                                  0x00000010
#define SRE_N1_RD(src)                                (((src) & 0x00000010)>>4)
#define SRE_N1_WR(src)                           (((u32)(src)<<4) & 0x00000010)
#define SRE_N1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields pulldn_n	 */
#define PULLDN_N1_WIDTH                                                       1
#define PULLDN_N1_SHIFT                                                       2
#define PULLDN_N1_MASK                                               0x00000004
#define PULLDN_N1_RD(src)                             (((src) & 0x00000004)>>2)
#define PULLDN_N1_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define PULLDN_N1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields pdwn_n	 */
#define PDWN_N1_WIDTH                                                         1
#define PDWN_N1_SHIFT                                                         1
#define PDWN_N1_MASK                                                 0x00000002
#define PDWN_N1_RD(src)                               (((src) & 0x00000002)>>1)
#define PDWN_N1_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define PDWN_N1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields hyst_n	 */
#define HYST_N1_WIDTH                                                         1
#define HYST_N1_SHIFT                                                         0
#define HYST_N1_MASK                                                 0x00000001
#define HYST_N1_RD(src)                                  (((src) & 0x00000001))
#define HYST_N1_WR(src)                             (((u32)(src)) & 0x00000001)
#define HYST_N1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register cfg_pin_od_sel_1	*/ 
/*	 Fields OD_SEL	 */
#define OD_SEL1_WIDTH                                                         8
#define OD_SEL1_SHIFT                                                         0
#define OD_SEL1_MASK                                                 0x000000ff
#define OD_SEL1_RD(src)                                  (((src) & 0x000000ff))
#define OD_SEL1_WR(src)                             (((u32)(src)) & 0x000000ff)
#define OD_SEL1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register cfg_pin_od_sel_2	*/ 
/*	 Fields OD_SEL	 */
#define OD_SEL2_WIDTH                                                        16
#define OD_SEL2_SHIFT                                                         0
#define OD_SEL2_MASK                                                 0x0000ffff
#define OD_SEL2_RD(src)                                  (((src) & 0x0000ffff))
#define OD_SEL2_WR(src)                             (((u32)(src)) & 0x0000ffff)
#define OD_SEL2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register cfg_pin_od_sel_3	*/ 
/*	 Fields OD_SEL	 */
#define OD_SEL3_WIDTH                                                         8
#define OD_SEL3_SHIFT                                                         0
#define OD_SEL3_MASK                                                 0x000000ff
#define OD_SEL3_RD(src)                                  (((src) & 0x000000ff))
#define OD_SEL3_WR(src)                             (((u32)(src)) & 0x000000ff)
#define OD_SEL3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Global Base Address	*/
#define AHBC_CLKRST_REG_BASE_ADDR			0x01f2ac000ULL

/*    Address AHBC_CLKRST_REG  Registers */
#define AHBC_SRST_ADDR                                               0x00000000
#define AHBC_SRST_DEFAULT                                            0x000003ff
#define AHBC_CLKEN_ADDR                                              0x00000008
#define AHBC_CLKEN_DEFAULT                                           0x00000000
#define AHBC_CLK_CONFIG_ADDR                                         0x00000010
#define AHBC_CLK_CONFIG_DEFAULT                                      0x00000000

/*	Register AHBC_SRST	*/ 
/*	 Fields cfg_ahbc_apb_peri_rst	 */
#define CFG_AHBC_APB_PERI_RST_WIDTH                                           1
#define CFG_AHBC_APB_PERI_RST_SHIFT                                           9
#define CFG_AHBC_APB_PERI_RST_MASK                                   0x00000200
#define CFG_AHBC_APB_PERI_RST_RD(src)                 (((src) & 0x00000200)>>9)
#define CFG_AHBC_APB_PERI_RST_WR(src)            (((u32)(src)<<9) & 0x00000200)
#define CFG_AHBC_APB_PERI_RST_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields cfg_spi0_rst	 */
#define CFG_SPI0_RST_WIDTH                                                    1
#define CFG_SPI0_RST_SHIFT                                                    8
#define CFG_SPI0_RST_MASK                                            0x00000100
#define CFG_SPI0_RST_RD(src)                          (((src) & 0x00000100)>>8)
#define CFG_SPI0_RST_WR(src)                     (((u32)(src)<<8) & 0x00000100)
#define CFG_SPI0_RST_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields cfg_spi1_rst	 */
#define CFG_SPI1_RST_WIDTH                                                    1
#define CFG_SPI1_RST_SHIFT                                                    7
#define CFG_SPI1_RST_MASK                                            0x00000080
#define CFG_SPI1_RST_RD(src)                          (((src) & 0x00000080)>>7)
#define CFG_SPI1_RST_WR(src)                     (((u32)(src)<<7) & 0x00000080)
#define CFG_SPI1_RST_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields cfg_uart3_rst	 */
#define CFG_UART3_RST_WIDTH                                                   1
#define CFG_UART3_RST_SHIFT                                                   6
#define CFG_UART3_RST_MASK                                           0x00000040
#define CFG_UART3_RST_RD(src)                         (((src) & 0x00000040)>>6)
#define CFG_UART3_RST_WR(src)                    (((u32)(src)<<6) & 0x00000040)
#define CFG_UART3_RST_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields cfg_uart2_rst	 */
#define CFG_UART2_RST_WIDTH                                                   1
#define CFG_UART2_RST_SHIFT                                                   5
#define CFG_UART2_RST_MASK                                           0x00000020
#define CFG_UART2_RST_RD(src)                         (((src) & 0x00000020)>>5)
#define CFG_UART2_RST_WR(src)                    (((u32)(src)<<5) & 0x00000020)
#define CFG_UART2_RST_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields cfg_uart1_rst	 */
#define CFG_UART1_RST_WIDTH                                                   1
#define CFG_UART1_RST_SHIFT                                                   4
#define CFG_UART1_RST_MASK                                           0x00000010
#define CFG_UART1_RST_RD(src)                         (((src) & 0x00000010)>>4)
#define CFG_UART1_RST_WR(src)                    (((u32)(src)<<4) & 0x00000010)
#define CFG_UART1_RST_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields cfg_uart0_rst	 */
#define CFG_UART0_RST_WIDTH                                                   1
#define CFG_UART0_RST_SHIFT                                                   3
#define CFG_UART0_RST_MASK                                           0x00000008
#define CFG_UART0_RST_RD(src)                         (((src) & 0x00000008)>>3)
#define CFG_UART0_RST_WR(src)                    (((u32)(src)<<3) & 0x00000008)
#define CFG_UART0_RST_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields cfg_gpio_rst	 */
#define CFG_GPIO_RST_WIDTH                                                    1
#define CFG_GPIO_RST_SHIFT                                                    2
#define CFG_GPIO_RST_MASK                                            0x00000004
#define CFG_GPIO_RST_RD(src)                          (((src) & 0x00000004)>>2)
#define CFG_GPIO_RST_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define CFG_GPIO_RST_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields cfg_sdio_rst	 */
#define CFG_SDIO_RST_WIDTH                                                    1
#define CFG_SDIO_RST_SHIFT                                                    1
#define CFG_SDIO_RST_MASK                                            0x00000002
#define CFG_SDIO_RST_RD(src)                          (((src) & 0x00000002)>>1)
#define CFG_SDIO_RST_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define CFG_SDIO_RST_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ahbc_csr_rst	 */
#define AHBC_CSR_RST_WIDTH                                                    1
#define AHBC_CSR_RST_SHIFT                                                    0
#define AHBC_CSR_RST_MASK                                            0x00000001
#define AHBC_CSR_RST_RD(src)                             (((src) & 0x00000001))
#define AHBC_CSR_RST_WR(src)                        (((u32)(src)) & 0x00000001)
#define AHBC_CSR_RST_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AHBC_CLKEN	*/ 
/*	 Fields cfg_clken_apb_peri	 */
#define CFG_CLKEN_APB_PERI_WIDTH                                              1
#define CFG_CLKEN_APB_PERI_SHIFT                                              9
#define CFG_CLKEN_APB_PERI_MASK                                      0x00000200
#define CFG_CLKEN_APB_PERI_RD(src)                    (((src) & 0x00000200)>>9)
#define CFG_CLKEN_APB_PERI_WR(src)               (((u32)(src)<<9) & 0x00000200)
#define CFG_CLKEN_APB_PERI_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields cfg_clken_spi_0	 */
#define CFG_CLKEN_SPI_0_WIDTH                                                 1
#define CFG_CLKEN_SPI_0_SHIFT                                                 8
#define CFG_CLKEN_SPI_0_MASK                                         0x00000100
#define CFG_CLKEN_SPI_0_RD(src)                       (((src) & 0x00000100)>>8)
#define CFG_CLKEN_SPI_0_WR(src)                  (((u32)(src)<<8) & 0x00000100)
#define CFG_CLKEN_SPI_0_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields cfg_clken_spi_1	 */
#define CFG_CLKEN_SPI_1_WIDTH                                                 1
#define CFG_CLKEN_SPI_1_SHIFT                                                 7
#define CFG_CLKEN_SPI_1_MASK                                         0x00000080
#define CFG_CLKEN_SPI_1_RD(src)                       (((src) & 0x00000080)>>7)
#define CFG_CLKEN_SPI_1_WR(src)                  (((u32)(src)<<7) & 0x00000080)
#define CFG_CLKEN_SPI_1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields cfg_clken_uart3	 */
#define CFG_CLKEN_UART3_WIDTH                                                 1
#define CFG_CLKEN_UART3_SHIFT                                                 6
#define CFG_CLKEN_UART3_MASK                                         0x00000040
#define CFG_CLKEN_UART3_RD(src)                       (((src) & 0x00000040)>>6)
#define CFG_CLKEN_UART3_WR(src)                  (((u32)(src)<<6) & 0x00000040)
#define CFG_CLKEN_UART3_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields cfg_clken_uart2	 */
#define CFG_CLKEN_UART2_WIDTH                                                 1
#define CFG_CLKEN_UART2_SHIFT                                                 5
#define CFG_CLKEN_UART2_MASK                                         0x00000020
#define CFG_CLKEN_UART2_RD(src)                       (((src) & 0x00000020)>>5)
#define CFG_CLKEN_UART2_WR(src)                  (((u32)(src)<<5) & 0x00000020)
#define CFG_CLKEN_UART2_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields cfg_clken_uart1	 */
#define CFG_CLKEN_UART1_WIDTH                                                 1
#define CFG_CLKEN_UART1_SHIFT                                                 4
#define CFG_CLKEN_UART1_MASK                                         0x00000010
#define CFG_CLKEN_UART1_RD(src)                       (((src) & 0x00000010)>>4)
#define CFG_CLKEN_UART1_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define CFG_CLKEN_UART1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields cfg_clken_uart0	 */
#define CFG_CLKEN_UART0_WIDTH                                                 1
#define CFG_CLKEN_UART0_SHIFT                                                 3
#define CFG_CLKEN_UART0_MASK                                         0x00000008
#define CFG_CLKEN_UART0_RD(src)                       (((src) & 0x00000008)>>3)
#define CFG_CLKEN_UART0_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define CFG_CLKEN_UART0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields cfg_clken_gpio	 */
#define CFG_CLKEN_GPIO_WIDTH                                                  1
#define CFG_CLKEN_GPIO_SHIFT                                                  2
#define CFG_CLKEN_GPIO_MASK                                          0x00000004
#define CFG_CLKEN_GPIO_RD(src)                        (((src) & 0x00000004)>>2)
#define CFG_CLKEN_GPIO_WR(src)                   (((u32)(src)<<2) & 0x00000004)
#define CFG_CLKEN_GPIO_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields cfg_clken_sdio	 */
#define CFG_CLKEN_SDIO_WIDTH                                                  1
#define CFG_CLKEN_SDIO_SHIFT                                                  1
#define CFG_CLKEN_SDIO_MASK                                          0x00000002
#define CFG_CLKEN_SDIO_RD(src)                        (((src) & 0x00000002)>>1)
#define CFG_CLKEN_SDIO_WR(src)                   (((u32)(src)<<1) & 0x00000002)
#define CFG_CLKEN_SDIO_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields cfg_clken_csr	 */
#define CFG_CLKEN_CSR_WIDTH                                                   1
#define CFG_CLKEN_CSR_SHIFT                                                   0
#define CFG_CLKEN_CSR_MASK                                           0x00000001
#define CFG_CLKEN_CSR_RD(src)                            (((src) & 0x00000001))
#define CFG_CLKEN_CSR_WR(src)                       (((u32)(src)) & 0x00000001)
#define CFG_CLKEN_CSR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AHBC_CLK_CONFIG	*/ 
/*	 Fields CFG_AHB_SCLK_RATIO	 */
#define CFG_AHB_SCLK_RATIO_WIDTH                                              7
#define CFG_AHB_SCLK_RATIO_SHIFT                                              4
#define CFG_AHB_SCLK_RATIO_MASK                                      0x000007f0
#define CFG_AHB_SCLK_RATIO_RD(src)                    (((src) & 0x000007f0)>>4)
#define CFG_AHB_SCLK_RATIO_WR(src)               (((u32)(src)<<4) & 0x000007f0)
#define CFG_AHB_SCLK_RATIO_SET(dst,src) \
                       (((dst) & ~0x000007f0) | (((u32)(src)<<4) & 0x000007f0))
/*	 Fields CFG_UART_INT_REFCLK	 */
#define CFG_UART_INT_REFCLK_WIDTH                                             1
#define CFG_UART_INT_REFCLK_SHIFT                                             3
#define CFG_UART_INT_REFCLK_MASK                                     0x00000008
#define CFG_UART_INT_REFCLK_RD(src)                   (((src) & 0x00000008)>>3)
#define CFG_UART_INT_REFCLK_WR(src)              (((u32)(src)<<3) & 0x00000008)
#define CFG_UART_INT_REFCLK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields CFG_UART_REFCLK	 */
#define CFG_UART_REFCLK_WIDTH                                                 1
#define CFG_UART_REFCLK_SHIFT                                                 2
#define CFG_UART_REFCLK_MASK                                         0x00000004
#define CFG_UART_REFCLK_RD(src)                       (((src) & 0x00000004)>>2)
#define CFG_UART_REFCLK_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define CFG_UART_REFCLK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields CFG_AHB_APB_CLK_RATIO	 */
#define CFG_AHB_APB_CLK_RATIO_WIDTH                                           2
#define CFG_AHB_APB_CLK_RATIO_SHIFT                                           0
#define CFG_AHB_APB_CLK_RATIO_MASK                                   0x00000003
#define CFG_AHB_APB_CLK_RATIO_RD(src)                    (((src) & 0x00000003))
#define CFG_AHB_APB_CLK_RATIO_WR(src)               (((u32)(src)) & 0x00000003)
#define CFG_AHB_APB_CLK_RATIO_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Global Base Address	*/
#define REGSPEC_AHBC_GLBL_DIAG_CSR_I_BASE_ADDR			0x01f2ad000ULL

/*    Address AHBC_GLBL_DIAG_CSR_I  Registers */
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
#define AHBC_SLAVE_SHIM_CSR_BASE_ADDR			0x01f2ae000ULL

/*    Address AHBC_SLAVE_SHIM_CSR  Registers */
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

/*	Global Base Address	*/
#define AHBC_MASTER_SHIM_CSR_BASE_ADDR			0x01f2af000ULL

/*    Address AHBC_MASTER_SHIM_CSR  Registers */
#define CFG_MST_IOB_SEL_ADDR                                         0x00000004
#define CFG_MST_IOB_SEL_DEFAULT                                      0x00000002
#define CFG_VC0_PREFETCH_ADDR                                        0x00000008
#define CFG_VC0_PREFETCH_DEFAULT                                     0x00000000
#define CFG_VC1_PREFETCH_ADDR                                        0x0000000c
#define CFG_VC1_PREFETCH_DEFAULT                                     0x00000000
#define CFG_VC2_PREFETCH_ADDR                                        0x00000010
#define CFG_VC2_PREFETCH_DEFAULT                                     0x00000000

/*	Register CFG_MST_IOB_SEL	*/ 
/*	 Fields CFG_VC_BYPASS	 */
#define CFG_VC_BYPASS_WIDTH                                                   1
#define CFG_VC_BYPASS_SHIFT                                                   1
#define CFG_VC_BYPASS_MASK                                           0x00000002
#define CFG_VC_BYPASS_RD(src)                         (((src) & 0x00000002)>>1)
#define CFG_VC_BYPASS_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define CFG_VC_BYPASS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields CFG_MST_IOB_SEL	 */
#define CFG_MST_IOB_SEL_WIDTH                                                 1
#define CFG_MST_IOB_SEL_SHIFT                                                 0
#define CFG_MST_IOB_SEL_MASK                                         0x00000001
#define CFG_MST_IOB_SEL_RD(src)                          (((src) & 0x00000001))
#define CFG_MST_IOB_SEL_WR(src)                     (((u32)(src)) & 0x00000001)
#define CFG_MST_IOB_SEL_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_VC0_PREFETCH	*/ 
/*	 Fields CFG_VC0_PREFETCH_CNT	 */
#define CFG_VC0_PREFETCH_CNT_WIDTH                                            4
#define CFG_VC0_PREFETCH_CNT_SHIFT                                            0
#define CFG_VC0_PREFETCH_CNT_MASK                                    0x0000000f
#define CFG_VC0_PREFETCH_CNT_RD(src)                     (((src) & 0x0000000f))
#define CFG_VC0_PREFETCH_CNT_WR(src)                (((u32)(src)) & 0x0000000f)
#define CFG_VC0_PREFETCH_CNT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register CFG_VC1_PREFETCH	*/ 
/*	 Fields CFG_VC1_PREFETCH_CNT	 */
#define CFG_VC1_PREFETCH_CNT_WIDTH                                            4
#define CFG_VC1_PREFETCH_CNT_SHIFT                                            0
#define CFG_VC1_PREFETCH_CNT_MASK                                    0x0000000f
#define CFG_VC1_PREFETCH_CNT_RD(src)                     (((src) & 0x0000000f))
#define CFG_VC1_PREFETCH_CNT_WR(src)                (((u32)(src)) & 0x0000000f)
#define CFG_VC1_PREFETCH_CNT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register CFG_VC2_PREFETCH	*/ 
/*	 Fields CFG_VC2_PREFETCH_CNT	 */
#define CFG_VC2_PREFETCH_CNT_WIDTH                                            4
#define CFG_VC2_PREFETCH_CNT_SHIFT                                            0
#define CFG_VC2_PREFETCH_CNT_MASK                                    0x0000000f
#define CFG_VC2_PREFETCH_CNT_RD(src)                     (((src) & 0x0000000f))
#define CFG_VC2_PREFETCH_CNT_WR(src)                (((u32)(src)) & 0x0000000f)
#define CFG_VC2_PREFETCH_CNT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Global Base Address	*/
#define UART3_REG_BASE_ADDR			0x01c023000ULL
#define UART2_REG_BASE_ADDR			0x01c022000ULL
#define UART1_REG_BASE_ADDR			0x01c021000ULL
#define UART0_REG_BASE_ADDR			0x01c020000ULL

/*    Address UART0_REG  Registers */
#define UART_RBR_ADDR                                                0x00000000
#define UART_RBR_DEFAULT                                             0x00000000
#define UART_DLH_ADDR                                                0x00000004
#define UART_DLH_DEFAULT                                             0x00000000
#define UART_IIR_ADDR                                                0x00000008
#define UART_IIR_DEFAULT                                             0x00000001
#define UART_LCR_ADDR                                                0x0000000c
#define UART_LCR_DEFAULT                                             0x00000000
#define UART_MCR_ADDR                                                0x00000010
#define UART_MCR_DEFAULT                                             0x00000000
#define UART_LSR_ADDR                                                0x00000014
#define UART_LSR_DEFAULT                                             0x00000060
#define UART_MSR_ADDR                                                0x00000018
#define UART_MSR_DEFAULT                                             0x00000000
#define UART_SCR_ADDR                                                0x0000001c
#define UART_SCR_DEFAULT                                             0x00000000
#define UART_LPDLL_ADDR                                              0x00000020
#define UART_LPDLL_DEFAULT                                           0x00000000
#define UART_LPDLH_ADDR                                              0x00000024
#define UART_LPDLH_DEFAULT                                           0x00000000
#define UART_SRBR_ADDR                                               0x00000030
#define UART_SRBR_DEFAULT                                            0x00000000
#define UART_FAR_ADDR                                                0x00000070
#define UART_FAR_DEFAULT                                             0x00000000
#define UART_TFR_ADDR                                                0x00000074
#define UART_TFR_DEFAULT                                             0x00000000
#define UART_RFW_ADDR                                                0x00000078
#define UART_RFW_DEFAULT                                             0x00000000
#define UART_USR_ADDR                                                0x0000007c
#define UART_USR_DEFAULT                                             0x00000006
#define UART_TFL_ADDR                                                0x00000080
#define UART_TFL_DEFAULT                                             0x00000000
#define UART_RFL_ADDR                                                0x00000084
#define UART_RFL_DEFAULT                                             0x00000000
#define UART_SRR_ADDR                                                0x00000088
#define UART_SRR_DEFAULT                                             0x00000000
#define UART_SRTS_ADDR                                               0x0000008c
#define UART_SRTS_DEFAULT                                            0x00000000
#define UART_SBCR_ADDR                                               0x00000090
#define UART_SBCR_DEFAULT                                            0x00000000
#define UART_SDMAM_ADDR                                              0x00000094
#define UART_SDMAM_DEFAULT                                           0x00000000
#define UART_SFE_ADDR                                                0x00000098
#define UART_SFE_DEFAULT                                             0x00000000
#define UART_SRT_ADDR                                                0x0000009c
#define UART_SRT_DEFAULT                                             0x00000000
#define UART_STET_ADDR                                               0x000000a0
#define UART_STET_DEFAULT                                            0x00000000
#define UART_HTX_ADDR                                                0x000000a4
#define UART_HTX_DEFAULT                                             0x00000000
#define UART_DMASA_ADDR                                              0x000000a8
#define UART_DMASA_DEFAULT                                           0x00000000
#define UART_CPR_ADDR                                                0x000000f4
#define UART_CPR_DEFAULT                                             0x00000000
#define UART_UCV_ADDR                                                0x000000f8
#define UART_UCV_DEFAULT                                             0x3331322a
#define UART_CTR_ADDR                                                0x000000fc
#define UART_CTR_DEFAULT                                             0x44570110

/*	Register UART_RBR	*/ 
/*	 Fields UART_RBR	 */
#define UART_RBR_WIDTH                                                        8
#define UART_RBR_SHIFT                                                        0
#define UART_RBR_MASK                                                0x000000ff
#define UART_RBR_RD(src)                                 (((src) & 0x000000ff))
#define UART_RBR_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register UART_DLH	*/ 
/*	 Fields UART_DLH	 */
#define UART_DLH_WIDTH                                                        8
#define UART_DLH_SHIFT                                                        0
#define UART_DLH_MASK                                                0x000000ff
#define UART_DLH_RD(src)                                 (((src) & 0x000000ff))
#define UART_DLH_WR(src)                            (((u32)(src)) & 0x000000ff)
#define UART_DLH_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register UART_IIR	*/ 
/*	 Fields FIFOSE	 */
#define FIFOSE_WIDTH                                                          2
#define FIFOSE_SHIFT                                                          6
#define FIFOSE_MASK                                                  0x000000c0
#define FIFOSE_RD(src)                                (((src) & 0x000000c0)>>6)
#define FIFOSE_SET(dst,src) \
                       (((dst) & ~0x000000c0) | (((u32)(src)<<6) & 0x000000c0))
/*	 Fields UART_IIR_Reserved	 */
#define UART_IIR_RESERVED_WIDTH                                               2
#define UART_IIR_RESERVED_SHIFT                                               4
#define UART_IIR_RESERVED_MASK                                       0x00000030
#define UART_IIR_RESERVED_RD(src)                     (((src) & 0x00000030)>>4)
#define UART_IIR_RESERVED_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields IID	 */
#define IID_WIDTH                                                             4
#define IID_SHIFT                                                             0
#define IID_MASK                                                     0x0000000f
#define IID_RD(src)                                      (((src) & 0x0000000f))
#define IID_SET(dst,src) (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register UART_LCR	*/ 
/*	 Fields DLAB	 */
#define DLAB_WIDTH                                                            1
#define DLAB_SHIFT                                                            7
#define DLAB_MASK                                                    0x00000080
#define DLAB_RD(src)                                  (((src) & 0x00000080)>>7)
#define DLAB_WR(src)                             (((u32)(src)<<7) & 0x00000080)
#define DLAB_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields BC	 */
#define BC_WIDTH                                                              1
#define BC_SHIFT                                                              6
#define BC_MASK                                                      0x00000040
#define BC_RD(src)                                    (((src) & 0x00000040)>>6)
#define BC_WR(src)                               (((u32)(src)<<6) & 0x00000040)
#define BC_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields Stick_Parity	 */
#define STICK_PARITY_WIDTH                                                    1
#define STICK_PARITY_SHIFT                                                    5
#define STICK_PARITY_MASK                                            0x00000020
#define STICK_PARITY_RD(src)                          (((src) & 0x00000020)>>5)
#define STICK_PARITY_WR(src)                     (((u32)(src)<<5) & 0x00000020)
#define STICK_PARITY_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields EPS	 */
#define EPS_WIDTH                                                             1
#define EPS_SHIFT                                                             4
#define EPS_MASK                                                     0x00000010
#define EPS_RD(src)                                   (((src) & 0x00000010)>>4)
#define EPS_WR(src)                              (((u32)(src)<<4) & 0x00000010)
#define EPS_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields PEN	 */
#define PEN_WIDTH                                                             1
#define PEN_SHIFT                                                             3
#define PEN_MASK                                                     0x00000008
#define PEN_RD(src)                                   (((src) & 0x00000008)>>3)
#define PEN_WR(src)                              (((u32)(src)<<3) & 0x00000008)
#define PEN_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields STOP	 */
#define STOP_WIDTH                                                            1
#define STOP_SHIFT                                                            2
#define STOP_MASK                                                    0x00000004
#define STOP_RD(src)                                  (((src) & 0x00000004)>>2)
#define STOP_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define STOP_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DLS	 */
#define DLS_WIDTH                                                             2
#define DLS_SHIFT                                                             0
#define DLS_MASK                                                     0x00000003
#define DLS_RD(src)                                      (((src) & 0x00000003))
#define DLS_WR(src)                                 (((u32)(src)) & 0x00000003)
#define DLS_SET(dst,src) (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register UART_MCR	*/ 
/*	 Fields SIRE	 */
#define SIRE_WIDTH                                                            1
#define SIRE_SHIFT                                                            6
#define SIRE_MASK                                                    0x00000040
#define SIRE_RD(src)                                  (((src) & 0x00000040)>>6)
#define SIRE_WR(src)                             (((u32)(src)<<6) & 0x00000040)
#define SIRE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields AFCE	 */
#define AFCE_WIDTH                                                            1
#define AFCE_SHIFT                                                            5
#define AFCE_MASK                                                    0x00000020
#define AFCE_RD(src)                                  (((src) & 0x00000020)>>5)
#define AFCE_WR(src)                             (((u32)(src)<<5) & 0x00000020)
#define AFCE_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields LB	 */
#define LB_WIDTH                                                              1
#define LB_SHIFT                                                              4
#define LB_MASK                                                      0x00000010
#define LB_RD(src)                                    (((src) & 0x00000010)>>4)
#define LB_WR(src)                               (((u32)(src)<<4) & 0x00000010)
#define LB_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields OUT2	 */
#define OUT2_WIDTH                                                            1
#define OUT2_SHIFT                                                            3
#define OUT2_MASK                                                    0x00000008
#define OUT2_RD(src)                                  (((src) & 0x00000008)>>3)
#define OUT2_WR(src)                             (((u32)(src)<<3) & 0x00000008)
#define OUT2_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields OUT1	 */
#define OUT1_WIDTH                                                            1
#define OUT1_SHIFT                                                            2
#define OUT1_MASK                                                    0x00000004
#define OUT1_RD(src)                                  (((src) & 0x00000004)>>2)
#define OUT1_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define OUT1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields RTS	 */
#define RTS_WIDTH                                                             1
#define RTS_SHIFT                                                             1
#define RTS_MASK                                                     0x00000002
#define RTS_RD(src)                                   (((src) & 0x00000002)>>1)
#define RTS_WR(src)                              (((u32)(src)<<1) & 0x00000002)
#define RTS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DTR	 */
#define DTR_WIDTH                                                             1
#define DTR_SHIFT                                                             0
#define DTR_MASK                                                     0x00000001
#define DTR_RD(src)                                      (((src) & 0x00000001))
#define DTR_WR(src)                                 (((u32)(src)) & 0x00000001)
#define DTR_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_LSR	*/ 
/*	 Fields RFE	 */
#define RFE_WIDTH                                                             1
#define RFE_SHIFT                                                             7
#define RFE_MASK                                                     0x00000080
#define RFE_RD(src)                                   (((src) & 0x00000080)>>7)
#define RFE_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields TEMT	 */
#define TEMT_WIDTH                                                            1
#define TEMT_SHIFT                                                            6
#define TEMT_MASK                                                    0x00000040
#define TEMT_RD(src)                                  (((src) & 0x00000040)>>6)
#define TEMT_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields THRE	 */
#define THRE_WIDTH                                                            1
#define THRE_SHIFT                                                            5
#define THRE_MASK                                                    0x00000020
#define THRE_RD(src)                                  (((src) & 0x00000020)>>5)
#define THRE_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields BI	 */
#define BI_WIDTH                                                              1
#define BI_SHIFT                                                              4
#define BI_MASK                                                      0x00000010
#define BI_RD(src)                                    (((src) & 0x00000010)>>4)
#define BI_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields FE	 */
#define FE_WIDTH                                                              1
#define FE_SHIFT                                                              3
#define FE_MASK                                                      0x00000008
#define FE_RD(src)                                    (((src) & 0x00000008)>>3)
#define FE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields PE	 */
#define PE_WIDTH                                                              1
#define PE_SHIFT                                                              2
#define PE_MASK                                                      0x00000004
#define PE_RD(src)                                    (((src) & 0x00000004)>>2)
#define PE_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields OE	 */
#define OE_WIDTH                                                              1
#define OE_SHIFT                                                              1
#define OE_MASK                                                      0x00000002
#define OE_RD(src)                                    (((src) & 0x00000002)>>1)
#define OE_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DR	 */
#define DR_WIDTH                                                              1
#define DR_SHIFT                                                              0
#define DR_MASK                                                      0x00000001
#define DR_RD(src)                                       (((src) & 0x00000001))
#define DR_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_MSR	*/ 
/*	 Fields DCD	 */
#define DCD_WIDTH                                                             1
#define DCD_SHIFT                                                             7
#define DCD_MASK                                                     0x00000080
#define DCD_RD(src)                                   (((src) & 0x00000080)>>7)
#define DCD_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields RI	 */
#define RI_WIDTH                                                              1
#define RI_SHIFT                                                              6
#define RI_MASK                                                      0x00000040
#define RI_RD(src)                                    (((src) & 0x00000040)>>6)
#define RI_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields DSR	 */
#define DSR_WIDTH                                                             1
#define DSR_SHIFT                                                             5
#define DSR_MASK                                                     0x00000020
#define DSR_RD(src)                                   (((src) & 0x00000020)>>5)
#define DSR_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields CTS	 */
#define CTS_WIDTH                                                             1
#define CTS_SHIFT                                                             4
#define CTS_MASK                                                     0x00000010
#define CTS_RD(src)                                   (((src) & 0x00000010)>>4)
#define CTS_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields DDCD	 */
#define DDCD_WIDTH                                                            1
#define DDCD_SHIFT                                                            3
#define DDCD_MASK                                                    0x00000008
#define DDCD_RD(src)                                  (((src) & 0x00000008)>>3)
#define DDCD_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields TERI	 */
#define TERI_WIDTH                                                            1
#define TERI_SHIFT                                                            2
#define TERI_MASK                                                    0x00000004
#define TERI_RD(src)                                  (((src) & 0x00000004)>>2)
#define TERI_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DDSR	 */
#define DDSR_WIDTH                                                            1
#define DDSR_SHIFT                                                            1
#define DDSR_MASK                                                    0x00000002
#define DDSR_RD(src)                                  (((src) & 0x00000002)>>1)
#define DDSR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DCTS	 */
#define DCTS_WIDTH                                                            1
#define DCTS_SHIFT                                                            0
#define DCTS_MASK                                                    0x00000001
#define DCTS_RD(src)                                     (((src) & 0x00000001))
#define DCTS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_SCR	*/ 
/*	 Fields Scratchpad	 */
#define SCRATCHPAD_WIDTH                                                      8
#define SCRATCHPAD_SHIFT                                                      0
#define SCRATCHPAD_MASK                                              0x000000ff
#define SCRATCHPAD_RD(src)                               (((src) & 0x000000ff))
#define SCRATCHPAD_WR(src)                          (((u32)(src)) & 0x000000ff)
#define SCRATCHPAD_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register UART_LPDLL	*/ 

/*	Register UART_LPDLH	*/ 

/*	Register UART_SRBR	*/ 
/*	 Fields SRBR	 */
#define SRBR_WIDTH                                                            8
#define SRBR_SHIFT                                                            0
#define SRBR_MASK                                                    0x000000ff
#define SRBR_RD(src)                                     (((src) & 0x000000ff))
#define SRBR_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register UART_FAR	*/ 
/*	 Fields FAR	 */
#define FAR_WIDTH                                                             1
#define FAR_SHIFT                                                             0
#define FAR_MASK                                                     0x00000001
#define FAR_RD(src)                                      (((src) & 0x00000001))
#define FAR_WR(src)                                 (((u32)(src)) & 0x00000001)
#define FAR_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_TFR	*/ 
/*	 Fields TFR	 */
#define TFR_WIDTH                                                             8
#define TFR_SHIFT                                                             0
#define TFR_MASK                                                     0x000000ff
#define TFR_RD(src)                                      (((src) & 0x000000ff))
#define TFR_SET(dst,src) (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register UART_RFW	*/ 
/*	 Fields RFFE	 */
#define RFFE_WIDTH                                                            1
#define RFFE_SHIFT                                                            9
#define RFFE_MASK                                                    0x00000200
#define RFFE_RD(src)                                  (((src) & 0x00000200)>>9)
#define RFFE_WR(src)                             (((u32)(src)<<9) & 0x00000200)
#define RFFE_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields RFPE	 */
#define RFPE_WIDTH                                                            1
#define RFPE_SHIFT                                                            8
#define RFPE_MASK                                                    0x00000100
#define RFPE_RD(src)                                  (((src) & 0x00000100)>>8)
#define RFPE_WR(src)                             (((u32)(src)<<8) & 0x00000100)
#define RFPE_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields RFWD	 */
#define RFWD_WIDTH                                                            8
#define RFWD_SHIFT                                                            0
#define RFWD_MASK                                                    0x000000ff
#define RFWD_RD(src)                                     (((src) & 0x000000ff))
#define RFWD_WR(src)                                (((u32)(src)) & 0x000000ff)
#define RFWD_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register UART_USR	*/ 
/*	 Fields RFF	 */
#define RFF_WIDTH                                                             1
#define RFF_SHIFT                                                             4
#define RFF_MASK                                                     0x00000010
#define RFF_RD(src)                                   (((src) & 0x00000010)>>4)
#define RFF_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields RFNE	 */
#define RFNE_WIDTH                                                            1
#define RFNE_SHIFT                                                            3
#define RFNE_MASK                                                    0x00000008
#define RFNE_RD(src)                                  (((src) & 0x00000008)>>3)
#define RFNE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields TFE	 */
#define TFE_WIDTH                                                             1
#define TFE_SHIFT                                                             2
#define TFE_MASK                                                     0x00000004
#define TFE_RD(src)                                   (((src) & 0x00000004)>>2)
#define TFE_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TFNF	 */
#define TFNF_WIDTH                                                            1
#define TFNF_SHIFT                                                            1
#define TFNF_MASK                                                    0x00000002
#define TFNF_RD(src)                                  (((src) & 0x00000002)>>1)
#define TFNF_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields BUSY	 */
#define BUSY_WIDTH                                                            1
#define BUSY_SHIFT                                                            0
#define BUSY_MASK                                                    0x00000001
#define BUSY_RD(src)                                     (((src) & 0x00000001))
#define BUSY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_TFL	*/ 
/*	 Fields TFL	 */
#define TFL_WIDTH                                                             5
#define TFL_SHIFT                                                             0
#define TFL_MASK                                                     0x0000001f
#define TFL_RD(src)                                      (((src) & 0x0000001f))
#define TFL_SET(dst,src) (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register UART_RFL	*/ 
/*	 Fields RFL	 */
#define RFL_WIDTH                                                             5
#define RFL_SHIFT                                                             0
#define RFL_MASK                                                     0x0000001f
#define RFL_RD(src)                                      (((src) & 0x0000001f))
#define RFL_SET(dst,src) (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register UART_SRR	*/ 
/*	 Fields XFR	 */
#define XFR_WIDTH                                                             1
#define XFR_SHIFT                                                             2
#define XFR_MASK                                                     0x00000004
#define XFR_RD(src)                                   (((src) & 0x00000004)>>2)
#define XFR_WR(src)                              (((u32)(src)<<2) & 0x00000004)
#define XFR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields RFR	 */
#define RFR_WIDTH                                                             1
#define RFR_SHIFT                                                             1
#define RFR_MASK                                                     0x00000002
#define RFR_RD(src)                                   (((src) & 0x00000002)>>1)
#define RFR_WR(src)                              (((u32)(src)<<1) & 0x00000002)
#define RFR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields UR	 */
#define UR_WIDTH                                                              1
#define UR_SHIFT                                                              0
#define UR_MASK                                                      0x00000001
#define UR_RD(src)                                       (((src) & 0x00000001))
#define UR_WR(src)                                  (((u32)(src)) & 0x00000001)
#define UR_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_SRTS	*/ 
/*	 Fields SRTS	 */
#define SRTS_WIDTH                                                            1
#define SRTS_SHIFT                                                            0
#define SRTS_MASK                                                    0x00000001
#define SRTS_RD(src)                                     (((src) & 0x00000001))
#define SRTS_WR(src)                                (((u32)(src)) & 0x00000001)
#define SRTS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_SBCR	*/ 
/*	 Fields SBCR	 */
#define SBCR_WIDTH                                                            1
#define SBCR_SHIFT                                                            0
#define SBCR_MASK                                                    0x00000001
#define SBCR_RD(src)                                     (((src) & 0x00000001))
#define SBCR_WR(src)                                (((u32)(src)) & 0x00000001)
#define SBCR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_SDMAM	*/ 
/*	 Fields SDMAM	 */
#define SDMAM_WIDTH                                                           1
#define SDMAM_SHIFT                                                           0
#define SDMAM_MASK                                                   0x00000001
#define SDMAM_RD(src)                                    (((src) & 0x00000001))
#define SDMAM_WR(src)                               (((u32)(src)) & 0x00000001)
#define SDMAM_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_SFE	*/ 
/*	 Fields SFE	 */
#define SFE_WIDTH                                                             1
#define SFE_SHIFT                                                             0
#define SFE_MASK                                                     0x00000001
#define SFE_RD(src)                                      (((src) & 0x00000001))
#define SFE_WR(src)                                 (((u32)(src)) & 0x00000001)
#define SFE_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_SRT	*/ 
/*	 Fields SRT	 */
#define SRT_WIDTH                                                             2
#define SRT_SHIFT                                                             0
#define SRT_MASK                                                     0x00000003
#define SRT_RD(src)                                      (((src) & 0x00000003))
#define SRT_WR(src)                                 (((u32)(src)) & 0x00000003)
#define SRT_SET(dst,src) (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register UART_STET	*/ 
/*	 Fields STET	 */
#define STET_WIDTH                                                            2
#define STET_SHIFT                                                            0
#define STET_MASK                                                    0x00000003
#define STET_RD(src)                                     (((src) & 0x00000003))
#define STET_WR(src)                                (((u32)(src)) & 0x00000003)
#define STET_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register UART_HTX	*/ 
/*	 Fields HTX	 */
#define HTX_WIDTH                                                             1
#define HTX_SHIFT                                                             0
#define HTX_MASK                                                     0x00000001
#define HTX_RD(src)                                      (((src) & 0x00000001))
#define HTX_WR(src)                                 (((u32)(src)) & 0x00000001)
#define HTX_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_DMASA	*/ 
/*	 Fields DMASA	 */
#define DMASA_WIDTH                                                           1
#define DMASA_SHIFT                                                           0
#define DMASA_MASK                                                   0x00000001
#define DMASA_RD(src)                                    (((src) & 0x00000001))
#define DMASA_WR(src)                               (((u32)(src)) & 0x00000001)
#define DMASA_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register UART_CPR	*/ 
/*	 Fields FIFO_MODE	 */
#define REGSPEC_FIFO_MODE_WIDTH                                               8
#define REGSPEC_FIFO_MODE_SHIFT                                              16
#define REGSPEC_FIFO_MODE_MASK                                       0x00ff0000
#define REGSPEC_FIFO_MODE_RD(src)                    (((src) & 0x00ff0000)>>16)
#define REGSPEC_FIFO_MODE_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields DMA_EXTRA	 */
#define DMA_EXTRA_WIDTH                                                       1
#define DMA_EXTRA_SHIFT                                                      13
#define DMA_EXTRA_MASK                                               0x00002000
#define DMA_EXTRA_RD(src)                            (((src) & 0x00002000)>>13)
#define DMA_EXTRA_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields UART_ADD_ENCODED_PARAMS	 */
#define UART_ADD_ENCODED_PARAMS_WIDTH                                         1
#define UART_ADD_ENCODED_PARAMS_SHIFT                                        12
#define UART_ADD_ENCODED_PARAMS_MASK                                 0x00001000
#define UART_ADD_ENCODED_PARAMS_RD(src)              (((src) & 0x00001000)>>12)
#define UART_ADD_ENCODED_PARAMS_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SHADOW	 */
#define SHADOW_WIDTH                                                          1
#define SHADOW_SHIFT                                                         11
#define SHADOW_MASK                                                  0x00000800
#define SHADOW_RD(src)                               (((src) & 0x00000800)>>11)
#define SHADOW_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields FIFO_STAT	 */
#define FIFO_STAT_WIDTH                                                       1
#define FIFO_STAT_SHIFT                                                      10
#define FIFO_STAT_MASK                                               0x00000400
#define FIFO_STAT_RD(src)                            (((src) & 0x00000400)>>10)
#define FIFO_STAT_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields FIFO_ACCESS	 */
#define FIFO_ACCESS_WIDTH                                                     1
#define FIFO_ACCESS_SHIFT                                                     9
#define FIFO_ACCESS_MASK                                             0x00000200
#define FIFO_ACCESS_RD(src)                           (((src) & 0x00000200)>>9)
#define FIFO_ACCESS_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields NEW_FEAT	 */
#define NEW_FEAT_WIDTH                                                        1
#define NEW_FEAT_SHIFT                                                        8
#define NEW_FEAT_MASK                                                0x00000100
#define NEW_FEAT_RD(src)                              (((src) & 0x00000100)>>8)
#define NEW_FEAT_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SIR_LP_MODE	 */
#define REGSPEC_SIR_LP_MODE_WIDTH                                             1
#define REGSPEC_SIR_LP_MODE_SHIFT                                             7
#define REGSPEC_SIR_LP_MODE_MASK                                     0x00000080
#define REGSPEC_SIR_LP_MODE_RD(src)                   (((src) & 0x00000080)>>7)
#define REGSPEC_SIR_LP_MODE_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SIR_MODE	 */
#define REGSPEC_SIR_MODE_WIDTH                                                1
#define REGSPEC_SIR_MODE_SHIFT                                                6
#define REGSPEC_SIR_MODE_MASK                                        0x00000040
#define REGSPEC_SIR_MODE_RD(src)                      (((src) & 0x00000040)>>6)
#define REGSPEC_SIR_MODE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields THRE_MODE	 */
#define REGSPEC_THRE_MODE_WIDTH                                               1
#define REGSPEC_THRE_MODE_SHIFT                                               5
#define REGSPEC_THRE_MODE_MASK                                       0x00000020
#define REGSPEC_THRE_MODE_RD(src)                     (((src) & 0x00000020)>>5)
#define REGSPEC_THRE_MODE_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields AFCE_MODE	 */
#define REGSPEC_AFCE_MODE_WIDTH                                               1
#define REGSPEC_AFCE_MODE_SHIFT                                               4
#define REGSPEC_AFCE_MODE_MASK                                       0x00000010
#define REGSPEC_AFCE_MODE_RD(src)                     (((src) & 0x00000010)>>4)
#define REGSPEC_AFCE_MODE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields APB_DATA_WIDTH	 */
#define APB_DATA_WIDTH_WIDTH                                                  2
#define APB_DATA_WIDTH_SHIFT                                                  0
#define APB_DATA_WIDTH_MASK                                          0x00000003
#define APB_DATA_WIDTH_RD(src)                           (((src) & 0x00000003))
#define APB_DATA_WIDTH_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register UART_UCV	*/ 
/*	 Fields UCV	 */
#define UCV_WIDTH                                                            32
#define UCV_SHIFT                                                             0
#define UCV_MASK                                                     0xffffffff
#define UCV_RD(src)                                      (((src) & 0xffffffff))
#define UCV_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register UART_CTR	*/ 
/*	 Fields Peripheral_ID	 */
#define PERIPHERAL_ID_WIDTH                                                  32
#define PERIPHERAL_ID_SHIFT                                                   0
#define PERIPHERAL_ID_MASK                                           0xffffffff
#define PERIPHERAL_ID_RD(src)                            (((src) & 0xffffffff))
#define PERIPHERAL_ID_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*    Address UART1_REG  Registers */

/*    Address UART2_REG  Registers */

/*    Address UART3_REG  Registers */

/*	Global Base Address	*/
#define GPIO_REG_BASE_ADDR			0x01c024000ULL

/*    Address GPIO_REG  Registers */
#define GPIO_SWPORTA_DR_ADDR                                         0x00000000
#define GPIO_SWPORTA_DR_DEFAULT                                      0x00000000
#define GPIO_SWPORTA_DDR_ADDR                                        0x00000004
#define GPIO_SWPORTA_DDR_DEFAULT                                     0x00000000
#define GPIO_PORTA_CTL_ADDR                                          0x00000008
#define GPIO_PORTA_CTL_DEFAULT                                       0x00000000
#define GPIO_EXT_PORTA_ADDR                                          0x00000050
#define GPIO_EXT_PORTA_DEFAULT                                       0x00000000
#define GPIO_LS_SYNC_ADDR                                            0x00000060
#define GPIO_LS_SYNC_DEFAULT                                         0x00000000
#define GPIO_ID_CODE_ADDR                                            0x00000064
#define GPIO_ID_CODE_DEFAULT                                         0x00000000
#define GPIO_COMP_VERSION_ADDR                                       0x0000006c
#define GPIO_COMP_VERSION_DEFAULT                                    0x3230392a

/*	Register GPIO_SWPORTA_DR	*/ 
/*	 Fields GPIO_SWPORTA_DR	 */
#define GPIO_SWPORTA_DR_WIDTH                                                32
#define GPIO_SWPORTA_DR_SHIFT                                                 0
#define GPIO_SWPORTA_DR_MASK                                         0xffffffff
#define GPIO_SWPORTA_DR_RD(src)                          (((src) & 0xffffffff))
#define GPIO_SWPORTA_DR_WR(src)                     (((u32)(src)) & 0xffffffff)
#define GPIO_SWPORTA_DR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GPIO_SWPORTA_DDR	*/ 
/*	 Fields GPIO_SWPORTA_DDR	 */
#define GPIO_SWPORTA_DDR_WIDTH                                               32
#define GPIO_SWPORTA_DDR_SHIFT                                                0
#define GPIO_SWPORTA_DDR_MASK                                        0xffffffff
#define GPIO_SWPORTA_DDR_RD(src)                         (((src) & 0xffffffff))
#define GPIO_SWPORTA_DDR_WR(src)                    (((u32)(src)) & 0xffffffff)
#define GPIO_SWPORTA_DDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GPIO_PORTA_CTL	*/ 
/*	 Fields GPIO_PORTA_CTL	 */
#define GPIO_PORTA_CTL_WIDTH                                                  1
#define GPIO_PORTA_CTL_SHIFT                                                  0
#define GPIO_PORTA_CTL_MASK                                          0x00000001
#define GPIO_PORTA_CTL_RD(src)                           (((src) & 0x00000001))
#define GPIO_PORTA_CTL_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GPIO_EXT_PORTA	*/ 
/*	 Fields GPIO_EXT_PORTA	 */
#define GPIO_EXT_PORTA_WIDTH                                                 28
#define GPIO_EXT_PORTA_SHIFT                                                  0
#define GPIO_EXT_PORTA_MASK                                          0x0fffffff
#define GPIO_EXT_PORTA_RD(src)                           (((src) & 0x0fffffff))
#define GPIO_EXT_PORTA_SET(dst,src) \
                          (((dst) & ~0x0fffffff) | (((u32)(src)) & 0x0fffffff))

/*	Register GPIO_LS_SYNC	*/ 
/*	 Fields GPIO_LS_SYNC	 */
#define GPIO_LS_SYNC_WIDTH                                                    1
#define GPIO_LS_SYNC_SHIFT                                                    0
#define GPIO_LS_SYNC_MASK                                            0x00000001
#define GPIO_LS_SYNC_RD(src)                             (((src) & 0x00000001))
#define GPIO_LS_SYNC_WR(src)                        (((u32)(src)) & 0x00000001)
#define GPIO_LS_SYNC_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GPIO_ID_CODE	*/ 
/*	 Fields GPIO_ID_CODE	 */
#define GPIO_ID_CODE_WIDTH                                                   24
#define GPIO_ID_CODE_SHIFT                                                    0
#define GPIO_ID_CODE_MASK                                            0x00ffffff
#define GPIO_ID_CODE_RD(src)                             (((src) & 0x00ffffff))
#define GPIO_ID_CODE_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register GPIO_COMP_VERSION	*/ 
/*	 Fields GPIO_COMP_VERSION	 */
#define GPIO_COMP_VERSION_WIDTH                                              32
#define GPIO_COMP_VERSION_SHIFT                                               0
#define GPIO_COMP_VERSION_MASK                                       0xffffffff
#define GPIO_COMP_VERSION_RD(src)                        (((src) & 0xffffffff))
#define GPIO_COMP_VERSION_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define SPI1_REG_BASE_ADDR			0x01c026000ULL
#define SPI0_REG_BASE_ADDR			0x01c025000ULL

/*    Address SPI0_REG  Registers */
#define CTRLR0_ADDR                                                  0x00000000
#define CTRLR0_DEFAULT                                               0x00000007
#define CTRLR1_ADDR                                                  0x00000004
#define CTRLR1_DEFAULT                                               0x00000000
#define SSIENR_ADDR                                                  0x00000008
#define SSIENR_DEFAULT                                               0x00000000
#define MWCR_ADDR                                                    0x0000000c
#define MWCR_DEFAULT                                                 0x00000000
#define SER_ADDR                                                     0x00000010
#define SER_DEFAULT                                                  0x00000000
#define BAUDR_ADDR                                                   0x00000014
#define BAUDR_DEFAULT                                                0x00000000
#define TXFTLR_ADDR                                                  0x00000018
#define TXFTLR_DEFAULT                                               0x00000000
#define RXFTLR_ADDR                                                  0x0000001c
#define RXFTLR_DEFAULT                                               0x00000000
#define TXFLR_ADDR                                                   0x00000020
#define TXFLR_DEFAULT                                                0x00000000
#define RXFLR_ADDR                                                   0x00000024
#define RXFLR_DEFAULT                                                0x00000000
#define SR_ADDR                                                      0x00000028
#define SR_DEFAULT                                                   0x00000006
#define IMR_ADDR                                                     0x0000002c
#define IMR_DEFAULT                                                  0x0000003f
#define ISR_ADDR                                                     0x00000030
#define ISR_DEFAULT                                                  0x00000000
#define RISR_ADDR                                                    0x00000034
#define RISR_DEFAULT                                                 0x00000000
#define TXOICR_ADDR                                                  0x00000038
#define TXOICR_DEFAULT                                               0x00000000
#define RXOICR_ADDR                                                  0x0000003c
#define RXOICR_DEFAULT                                               0x00000000
#define RXUICR_ADDR                                                  0x00000040
#define RXUICR_DEFAULT                                               0x00000000
#define MSTICR_ADDR                                                  0x00000044
#define MSTICR_DEFAULT                                               0x00000000
#define ICR_ADDR                                                     0x00000048
#define ICR_DEFAULT                                                  0x00000000
#define IDR_ADDR                                                     0x00000058
#define IDR_DEFAULT                                                  0xffffffff
#define VIDR_ADDR                                                    0x0000005c
#define VIDR_DEFAULT                                                 0x3332312a
#define DR_LOW_ADDR                                                  0x00000060
#define DR_LOW_DEFAULT                                               0x00000000
#define RX_SAMPLE_DLY_ADDR                                           0x000000f0
#define RX_SAMPLE_DLY_DEFAULT                                        0x00000000

/*	Register CTRLR0	*/ 
/*	 Fields CFS	 */
#define CFS0_WIDTH                                                            4
#define CFS0_SHIFT                                                           12
#define CFS0_MASK                                                    0x0000f000
#define CFS0_RD(src)                                 (((src) & 0x0000f000)>>12)
#define CFS0_WR(src)                            (((u32)(src)<<12) & 0x0000f000)
#define CFS0_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields SRL	 */
#define SRL0_WIDTH                                                            1
#define SRL0_SHIFT                                                           11
#define SRL0_MASK                                                    0x00000800
#define SRL0_RD(src)                                 (((src) & 0x00000800)>>11)
#define SRL0_WR(src)                            (((u32)(src)<<11) & 0x00000800)
#define SRL0_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SLV_OE	 */
#define SLV_OE0_WIDTH                                                         1
#define SLV_OE0_SHIFT                                                        10
#define SLV_OE0_MASK                                                 0x00000400
#define SLV_OE0_RD(src)                              (((src) & 0x00000400)>>10)
#define SLV_OE0_WR(src)                         (((u32)(src)<<10) & 0x00000400)
#define SLV_OE0_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields TMOD	 */
#define TMOD0_WIDTH                                                           2
#define TMOD0_SHIFT                                                           8
#define TMOD0_MASK                                                   0x00000300
#define TMOD0_RD(src)                                 (((src) & 0x00000300)>>8)
#define TMOD0_WR(src)                            (((u32)(src)<<8) & 0x00000300)
#define TMOD0_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields SCPOL	 */
#define SCPOL0_WIDTH                                                          1
#define SCPOL0_SHIFT                                                          7
#define SCPOL0_MASK                                                  0x00000080
#define SCPOL0_RD(src)                                (((src) & 0x00000080)>>7)
#define SCPOL0_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define SCPOL0_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SCPH	 */
#define SCPH0_WIDTH                                                           1
#define SCPH0_SHIFT                                                           6
#define SCPH0_MASK                                                   0x00000040
#define SCPH0_RD(src)                                 (((src) & 0x00000040)>>6)
#define SCPH0_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define SCPH0_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields FRF	 */
#define FRF0_WIDTH                                                            2
#define FRF0_SHIFT                                                            4
#define FRF0_MASK                                                    0x00000030
#define FRF0_RD(src)                                  (((src) & 0x00000030)>>4)
#define FRF0_WR(src)                             (((u32)(src)<<4) & 0x00000030)
#define FRF0_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields DFS	 */
#define DFS0_WIDTH                                                            4
#define DFS0_SHIFT                                                            0
#define DFS0_MASK                                                    0x0000000f
#define DFS0_RD(src)                                     (((src) & 0x0000000f))
#define DFS0_WR(src)                                (((u32)(src)) & 0x0000000f)
#define DFS0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register CTRLR1	*/ 
/*	 Fields NDF	 */
#define NDF1_WIDTH                                                           16
#define NDF1_SHIFT                                                            0
#define NDF1_MASK                                                    0x0000ffff
#define NDF1_RD(src)                                     (((src) & 0x0000ffff))
#define NDF1_WR(src)                                (((u32)(src)) & 0x0000ffff)
#define NDF1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register SSIENR	*/ 
/*	 Fields SSI_EN	 */
#define SSI_EN_WIDTH                                                          1
#define SSI_EN_SHIFT                                                          0
#define SSI_EN_MASK                                                  0x00000001
#define SSI_EN_RD(src)                                   (((src) & 0x00000001))
#define SSI_EN_WR(src)                              (((u32)(src)) & 0x00000001)
#define SSI_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MWCR	*/ 
/*	 Fields MHS	 */
#define MHS_WIDTH                                                             1
#define MHS_SHIFT                                                             2
#define MHS_MASK                                                     0x00000004
#define MHS_RD(src)                                   (((src) & 0x00000004)>>2)
#define MHS_WR(src)                              (((u32)(src)<<2) & 0x00000004)
#define MHS_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MDD	 */
#define MDD_WIDTH                                                             1
#define MDD_SHIFT                                                             1
#define MDD_MASK                                                     0x00000002
#define MDD_RD(src)                                   (((src) & 0x00000002)>>1)
#define MDD_WR(src)                              (((u32)(src)<<1) & 0x00000002)
#define MDD_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MWMOD	 */
#define MWMOD_WIDTH                                                           1
#define MWMOD_SHIFT                                                           0
#define MWMOD_MASK                                                   0x00000001
#define MWMOD_RD(src)                                    (((src) & 0x00000001))
#define MWMOD_WR(src)                               (((u32)(src)) & 0x00000001)
#define MWMOD_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SER	*/ 
/*	 Fields SER	 */
#define SER_WIDTH                                                             3
#define SER_SHIFT                                                             0
#define SER_MASK                                                     0x00000007
#define SER_RD(src)                                      (((src) & 0x00000007))
#define SER_WR(src)                                 (((u32)(src)) & 0x00000007)
#define SER_SET(dst,src) (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register BAUDR	*/ 
/*	 Fields SCKDV	 */
#define SCKDV_WIDTH                                                          15
#define SCKDV_SHIFT                                                           1
#define SCKDV_MASK                                                   0x0000fffe
#define SCKDV_RD(src)                                 (((src) & 0x0000fffe)>>1)
#define SCKDV_WR(src)                            (((u32)(src)<<1) & 0x0000fffe)
#define SCKDV_SET(dst,src) \
                       (((dst) & ~0x0000fffe) | (((u32)(src)<<1) & 0x0000fffe))

/*	Register TXFTLR	*/ 
/*	 Fields TFT	 */
#define TFT_WIDTH                                                             3
#define TFT_SHIFT                                                             0
#define TFT_MASK                                                     0x00000007
#define TFT_RD(src)                                      (((src) & 0x00000007))
#define TFT_WR(src)                                 (((u32)(src)) & 0x00000007)
#define TFT_SET(dst,src) (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register RXFTLR	*/ 
/*	 Fields RFT	 */
#define RFT_WIDTH                                                             3
#define RFT_SHIFT                                                             0
#define RFT_MASK                                                     0x00000007
#define RFT_RD(src)                                      (((src) & 0x00000007))
#define RFT_WR(src)                                 (((u32)(src)) & 0x00000007)
#define RFT_SET(dst,src) (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register TXFLR	*/ 
/*	 Fields TXTFL	 */
#define TXTFL_WIDTH                                                           4
#define TXTFL_SHIFT                                                           0
#define TXTFL_MASK                                                   0x0000000f
#define TXTFL_RD(src)                                    (((src) & 0x0000000f))
#define TXTFL_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register RXFLR	*/ 
/*	 Fields RXTFL	 */
#define RXTFL_WIDTH                                                           4
#define RXTFL_SHIFT                                                           0
#define RXTFL_MASK                                                   0x0000000f
#define RXTFL_RD(src)                                    (((src) & 0x0000000f))
#define RXTFL_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SR	*/ 
/*	 Fields DCOL	 */
#define DCOL_WIDTH                                                            1
#define DCOL_SHIFT                                                            6
#define DCOL_MASK                                                    0x00000040
#define DCOL_RD(src)                                  (((src) & 0x00000040)>>6)
#define DCOL_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields TXE	 */
#define TXE_WIDTH                                                             1
#define TXE_SHIFT                                                             5
#define TXE_MASK                                                     0x00000020
#define TXE_RD(src)                                   (((src) & 0x00000020)>>5)
#define TXE_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RFF	 */
#define RFF_F8_WIDTH                                                          1
#define RFF_F8_SHIFT                                                          4
#define RFF_F8_MASK                                                  0x00000010
#define RFF_F8_RD(src)                                (((src) & 0x00000010)>>4)
#define RFF_F8_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields RFNE	 */
#define RFNE_F8_WIDTH                                                         1
#define RFNE_F8_SHIFT                                                         3
#define RFNE_F8_MASK                                                 0x00000008
#define RFNE_F8_RD(src)                               (((src) & 0x00000008)>>3)
#define RFNE_F8_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields TFE	 */
#define TFE_F8_WIDTH                                                          1
#define TFE_F8_SHIFT                                                          2
#define TFE_F8_MASK                                                  0x00000004
#define TFE_F8_RD(src)                                (((src) & 0x00000004)>>2)
#define TFE_F8_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TFNF	 */
#define TFNF_F8_WIDTH                                                         1
#define TFNF_F8_SHIFT                                                         1
#define TFNF_F8_MASK                                                 0x00000002
#define TFNF_F8_RD(src)                               (((src) & 0x00000002)>>1)
#define TFNF_F8_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields BUSY	 */
#define BUSY_F8_WIDTH                                                         1
#define BUSY_F8_SHIFT                                                         0
#define BUSY_F8_MASK                                                 0x00000001
#define BUSY_F8_RD(src)                                  (((src) & 0x00000001))
#define BUSY_F8_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register IMR	*/ 
/*	 Fields MSTIM	 */
#define MSTIM_WIDTH                                                           1
#define MSTIM_SHIFT                                                           5
#define MSTIM_MASK                                                   0x00000020
#define MSTIM_RD(src)                                 (((src) & 0x00000020)>>5)
#define MSTIM_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define MSTIM_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RXFIM	 */
#define RXFIM_WIDTH                                                           1
#define RXFIM_SHIFT                                                           4
#define RXFIM_MASK                                                   0x00000010
#define RXFIM_RD(src)                                 (((src) & 0x00000010)>>4)
#define RXFIM_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define RXFIM_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields RXOIM	 */
#define RXOIM_WIDTH                                                           1
#define RXOIM_SHIFT                                                           3
#define RXOIM_MASK                                                   0x00000008
#define RXOIM_RD(src)                                 (((src) & 0x00000008)>>3)
#define RXOIM_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define RXOIM_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields RXUIM	 */
#define RXUIM_WIDTH                                                           1
#define RXUIM_SHIFT                                                           2
#define RXUIM_MASK                                                   0x00000004
#define RXUIM_RD(src)                                 (((src) & 0x00000004)>>2)
#define RXUIM_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define RXUIM_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TXOIM	 */
#define TXOIM_WIDTH                                                           1
#define TXOIM_SHIFT                                                           1
#define TXOIM_MASK                                                   0x00000002
#define TXOIM_RD(src)                                 (((src) & 0x00000002)>>1)
#define TXOIM_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define TXOIM_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields TXEIM	 */
#define TXEIM_WIDTH                                                           1
#define TXEIM_SHIFT                                                           0
#define TXEIM_MASK                                                   0x00000001
#define TXEIM_RD(src)                                    (((src) & 0x00000001))
#define TXEIM_WR(src)                               (((u32)(src)) & 0x00000001)
#define TXEIM_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ISR	*/ 
/*	 Fields MSTIS	 */
#define MSTIS_WIDTH                                                           1
#define MSTIS_SHIFT                                                           5
#define MSTIS_MASK                                                   0x00000020
#define MSTIS_RD(src)                                 (((src) & 0x00000020)>>5)
#define MSTIS_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RXFIS	 */
#define RXFIS_WIDTH                                                           1
#define RXFIS_SHIFT                                                           4
#define RXFIS_MASK                                                   0x00000010
#define RXFIS_RD(src)                                 (((src) & 0x00000010)>>4)
#define RXFIS_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields RXOIS	 */
#define RXOIS_WIDTH                                                           1
#define RXOIS_SHIFT                                                           3
#define RXOIS_MASK                                                   0x00000008
#define RXOIS_RD(src)                                 (((src) & 0x00000008)>>3)
#define RXOIS_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields RXUIS	 */
#define RXUIS_WIDTH                                                           1
#define RXUIS_SHIFT                                                           2
#define RXUIS_MASK                                                   0x00000004
#define RXUIS_RD(src)                                 (((src) & 0x00000004)>>2)
#define RXUIS_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TXOIS	 */
#define TXOIS_WIDTH                                                           1
#define TXOIS_SHIFT                                                           1
#define TXOIS_MASK                                                   0x00000002
#define TXOIS_RD(src)                                 (((src) & 0x00000002)>>1)
#define TXOIS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields TXEIS	 */
#define TXEIS_WIDTH                                                           1
#define TXEIS_SHIFT                                                           0
#define TXEIS_MASK                                                   0x00000001
#define TXEIS_RD(src)                                    (((src) & 0x00000001))
#define TXEIS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RISR	*/ 
/*	 Fields MSTIR	 */
#define MSTIR_WIDTH                                                           1
#define MSTIR_SHIFT                                                           5
#define MSTIR_MASK                                                   0x00000020
#define MSTIR_RD(src)                                 (((src) & 0x00000020)>>5)
#define MSTIR_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RXFIR	 */
#define RXFIR_WIDTH                                                           1
#define RXFIR_SHIFT                                                           4
#define RXFIR_MASK                                                   0x00000010
#define RXFIR_RD(src)                                 (((src) & 0x00000010)>>4)
#define RXFIR_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields RXOIR	 */
#define RXOIR_WIDTH                                                           1
#define RXOIR_SHIFT                                                           3
#define RXOIR_MASK                                                   0x00000008
#define RXOIR_RD(src)                                 (((src) & 0x00000008)>>3)
#define RXOIR_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields RXUIR	 */
#define RXUIR_WIDTH                                                           1
#define RXUIR_SHIFT                                                           2
#define RXUIR_MASK                                                   0x00000004
#define RXUIR_RD(src)                                 (((src) & 0x00000004)>>2)
#define RXUIR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TXOIR	 */
#define TXOIR_WIDTH                                                           1
#define TXOIR_SHIFT                                                           1
#define TXOIR_MASK                                                   0x00000002
#define TXOIR_RD(src)                                 (((src) & 0x00000002)>>1)
#define TXOIR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields TXEIR	 */
#define TXEIR_WIDTH                                                           1
#define TXEIR_SHIFT                                                           0
#define TXEIR_MASK                                                   0x00000001
#define TXEIR_RD(src)                                    (((src) & 0x00000001))
#define TXEIR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register TXOICR	*/ 
/*	 Fields TXOICR	 */
#define TXOICR_WIDTH                                                          1
#define TXOICR_SHIFT                                                          0
#define TXOICR_MASK                                                  0x00000001
#define TXOICR_RD(src)                                   (((src) & 0x00000001))
#define TXOICR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RXOICR	*/ 
/*	 Fields RXOICR	 */
#define RXOICR_WIDTH                                                          1
#define RXOICR_SHIFT                                                          0
#define RXOICR_MASK                                                  0x00000001
#define RXOICR_RD(src)                                   (((src) & 0x00000001))
#define RXOICR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RXUICR	*/ 
/*	 Fields RXUICR	 */
#define RXUICR_WIDTH                                                          1
#define RXUICR_SHIFT                                                          0
#define RXUICR_MASK                                                  0x00000001
#define RXUICR_RD(src)                                   (((src) & 0x00000001))
#define RXUICR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MSTICR	*/ 
/*	 Fields MSTICR	 */
#define MSTICR_WIDTH                                                          1
#define MSTICR_SHIFT                                                          0
#define MSTICR_MASK                                                  0x00000001
#define MSTICR_RD(src)                                   (((src) & 0x00000001))
#define MSTICR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ICR	*/ 
/*	 Fields ICR	 */
#define ICR_WIDTH                                                             1
#define ICR_SHIFT                                                             0
#define ICR_MASK                                                     0x00000001
#define ICR_RD(src)                                      (((src) & 0x00000001))
#define ICR_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register IDR	*/ 
/*	 Fields IDCODE	 */
#define IDCODE_WIDTH                                                         32
#define IDCODE_SHIFT                                                          0
#define IDCODE_MASK                                                  0xffffffff
#define IDCODE_RD(src)                                   (((src) & 0xffffffff))
#define IDCODE_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register VIDR	*/ 
/*	 Fields SSI_COMP_VERSION	 */
#define SSI_COMP_VERSION_WIDTH                                               32
#define SSI_COMP_VERSION_SHIFT                                                0
#define SSI_COMP_VERSION_MASK                                        0xffffffff
#define SSI_COMP_VERSION_RD(src)                         (((src) & 0xffffffff))
#define SSI_COMP_VERSION_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DR_LOW	*/ 
/*	 Fields DR_LOW	 */
#define DR_LOW_WIDTH                                                         16
#define DR_LOW_SHIFT                                                          0
#define DR_LOW_MASK                                                  0x0000ffff
#define DR_LOW_RD(src)                                   (((src) & 0x0000ffff))
#define DR_LOW_WR(src)                              (((u32)(src)) & 0x0000ffff)
#define DR_LOW_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RX_SAMPLE_DLY	*/ 
/*	 Fields RSD	 */
#define RSD_WIDTH                                                             8
#define RSD_SHIFT                                                             0
#define RSD_MASK                                                     0x000000ff
#define RSD_RD(src)                                      (((src) & 0x000000ff))
#define RSD_WR(src)                                 (((u32)(src)) & 0x000000ff)
#define RSD_SET(dst,src) (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*    Address SPI1_REG  Registers */

/*	Global Base Address	*/
#define SDHC_REG_BASE_ADDR			0x01c000000ULL

/*    Address SDHC_REG  Registers */
#define SDMA_SYSTEM_ADDRESS_ADDR                                     0x00000000
#define SDMA_SYSTEM_ADDRESS_DEFAULT                                  0x00000000
#define BLOCK_DEF_ADDR                                               0x00000004
#define BLOCK_DEF_DEFAULT                                            0x00000000
#define ARGUMENT_ADDR                                                0x00000008
#define ARGUMENT_DEFAULT                                             0x00000000
#define TRANSFERMODE_COMMAND_ADDR                                    0x0000000c
#define TRANSFERMODE_COMMAND_DEFAULT                                 0x00000000
#define RESPONSE_0_1_ADDR                                            0x00000010
#define RESPONSE_0_1_DEFAULT                                         0x00000000
#define RESPONSE_2_3_ADDR                                            0x00000014
#define RESPONSE_2_3_DEFAULT                                         0x00000000
#define RESPONSE_4_5_ADDR                                            0x00000018
#define RESPONSE_4_5_DEFAULT                                         0x00000000
#define RESPONSE_6_7_ADDR                                            0x0000001c
#define RESPONSE_6_7_DEFAULT                                         0x00000000
#define BUFFER_DATA_PORT_ADDR                                        0x00000020
#define BUFFER_DATA_PORT_DEFAULT                                     0x00000000
#define PRESENT_STATE_ADDR                                           0x00000024
#define PRESENT_STATE_DEFAULT                                        0x01f02000
#define GAP_WAKEUP_POWER_HOST_CONTROL_ADDR                           0x00000028
#define GAP_WAKEUP_POWER_HOST_CONTROL_DEFAULT                        0x00000000
#define SRESET_CLOCK_CONTROL_ADDR                                    0x0000002c
#define SRESET_CLOCK_CONTROL_DEFAULT                                 0x00000000
#define INTERRUPT_STATUS_ADDR                                        0x00000030
#define INTERRUPT_STATUS_DEFAULT                                     0x00000000
#define INTERRUPT_STATUS_ENABLE_ADDR                                 0x00000034
#define INTERRUPT_STATUS_ENABLE_DEFAULT                              0x00000000
#define INTERRUPT_SIGNAL_ENABLE_ADDR                                 0x00000038
#define INTERRUPT_SIGNAL_ENABLE_DEFAULT                              0x00000000
#define AUTO_CMD_ERROR_STATUS_ADDR                                   0x0000003c
#define AUTO_CMD_ERROR_STATUS_DEFAULT                                0x00000000
#define CAPABILITIES_0_ADDR                                          0x00000040
#define CAPABILITIES_0_DEFAULT                                       0x01ffe870
#define CAPABILITIES_1_ADDR                                          0x00000044
#define CAPABILITIES_1_DEFAULT                                       0x000807ff
#define MAX_CURRENT_CAPABILITIES_0_ADDR                              0x00000048
#define MAX_CURRENT_CAPABILITIES_0_DEFAULT                           0x00000000
#define MAX_CURRENT_CAPABILITIES_1_ADDR                              0x0000004c
#define MAX_CURRENT_CAPABILITIES_1_DEFAULT                           0x00000000
#define FORCE_EVENT_ADDR                                             0x00000050
#define FORCE_EVENT_DEFAULT                                          0x00000000
#define ADMA_ERROR_STATUS_ADDR                                       0x00000054
#define ADMA_ERROR_STATUS_DEFAULT                                    0x00000000
#define ADMA_ADDRESS_LOW_ADDR                                        0x00000058
#define ADMA_ADDRESS_LOW_DEFAULT                                     0x00000000
#define ADMA_ADDRESS_HIGH_ADDR                                       0x0000005c
#define ADMA_ADDRESS_HIGH_DEFAULT                                    0x00000000
#define PRESET_VALUE_0_ADDR                                          0x00000060
#define PRESET_VALUE_0_DEFAULT                                       0x00000000
#define PRESET_VALUE_1_ADDR                                          0x00000064
#define PRESET_VALUE_1_DEFAULT                                       0x00000000
#define PRESET_VALUE_2_ADDR                                          0x00000068
#define PRESET_VALUE_2_DEFAULT                                       0x00000000
#define PRESET_VALUE_3_ADDR                                          0x0000006c
#define PRESET_VALUE_3_DEFAULT                                       0x00000000
#define BOOT_TIMEOUT_CONTROL_ADDR                                    0x00000070
#define BOOT_TIMEOUT_CONTROL_DEFAULT                                 0x00000000
#define SHARED_BUS_CONTROL_ADDR                                      0x000000e0
#define SHARED_BUS_CONTROL_DEFAULT                                   0x00000000
#define SPI_INT_SUPPORT_ADDR                                         0x000000f0
#define SPI_INT_SUPPORT_DEFAULT                                      0x00000000
#define SLOT_INTR_STATUS_HOST_CONTROLLER_VERSION_ADDR                0x000000fc
#define SLOT_INTR_STATUS_HOST_CONTROLLER_VERSION_DEFAULT             0x48020000
#define SDMA_SYSTEM_ADDRESS_SLOT1_ADDR                               0x00000100
#define SDMA_SYSTEM_ADDRESS_SLOT1_DEFAULT                            0x00000000
#define BLOCK_DEF_SLOT1_ADDR                                         0x00000104
#define BLOCK_DEF_SLOT1_DEFAULT                                      0x00000000
#define ARGUMENT_SLOT1_ADDR                                          0x00000108
#define ARGUMENT_SLOT1_DEFAULT                                       0x00000000
#define TRANSFERMODE_COMMAND_SLOT1_ADDR                              0x0000010c
#define TRANSFERMODE_COMMAND_SLOT1_DEFAULT                           0x00000000
#define RESPONSE_0_1_SLOT1_ADDR                                      0x00000110
#define RESPONSE_0_1_SLOT1_DEFAULT                                   0x00000000
#define RESPONSE_2_3_SLOT1_ADDR                                      0x00000114
#define RESPONSE_2_3_SLOT1_DEFAULT                                   0x00000000
#define RESPONSE_4_5_SLOT1_ADDR                                      0x00000118
#define RESPONSE_4_5_SLOT1_DEFAULT                                   0x00000000
#define RESPONSE_6_7_SLOT1_ADDR                                      0x0000011c
#define RESPONSE_6_7_SLOT1_DEFAULT                                   0x00000000
#define BUFFER_DATA_PORT_SLOT1_ADDR                                  0x00000120
#define BUFFER_DATA_PORT_SLOT1_DEFAULT                               0x00000000
#define PRESENT_STATE_SLOT1_ADDR                                     0x00000124
#define PRESENT_STATE_SLOT1_DEFAULT                                  0x01f02000
#define GAP_WAKEUP_POWER_HOST_CONTROL_SLOT1_ADDR                     0x00000128
#define GAP_WAKEUP_POWER_HOST_CONTROL_SLOT1_DEFAULT                  0x00000000
#define SRESET_CLOCK_CONTROL_SLOT1_ADDR                              0x0000012c
#define SRESET_CLOCK_CONTROL_SLOT1_DEFAULT                           0x00000000
#define INTERRUPT_STATUS_SLOT1_ADDR                                  0x00000130
#define INTERRUPT_STATUS_SLOT1_DEFAULT                               0x00000000
#define INTERRUPT_STATUS_ENABLE_SLOT1_ADDR                           0x00000134
#define INTERRUPT_STATUS_ENABLE_SLOT1_DEFAULT                        0x00000000
#define INTERRUPT_SIGNAL_ENABLE_SLOT1_ADDR                           0x00000138
#define INTERRUPT_SIGNAL_ENABLE_SLOT1_DEFAULT                        0x00000000
#define AUTO_CMD_ERROR_STATUS_SLOT1_ADDR                             0x0000013c
#define AUTO_CMD_ERROR_STATUS_SLOT1_DEFAULT                          0x00000000
#define CAPABILITIES_0_SLOT1_ADDR                                    0x00000140
#define CAPABILITIES_0_SLOT1_DEFAULT                                 0x01ffe870
#define CAPABILITIES_1_SLOT1_ADDR                                    0x00000144
#define CAPABILITIES_1_SLOT1_DEFAULT                                 0x000807ff
#define MAX_CURRENT_CAPABILITIES_0_SLOT1_ADDR                        0x00000148
#define MAX_CURRENT_CAPABILITIES_0_SLOT1_DEFAULT                     0x00000000
#define MAX_CURRENT_CAPABILITIES_1_SLOT1_ADDR                        0x0000014c
#define MAX_CURRENT_CAPABILITIES_1_SLOT1_DEFAULT                     0x00000000
#define FORCE_EVENT_SLOT1_ADDR                                       0x00000150
#define FORCE_EVENT_SLOT1_DEFAULT                                    0x00000000
#define ADMA_ERROR_STATUS_SLOT1_ADDR                                 0x00000154
#define ADMA_ERROR_STATUS_SLOT1_DEFAULT                              0x00000000
#define ADMA_ADDRESS_LOW_SLOT1_ADDR                                  0x00000158
#define ADMA_ADDRESS_LOW_SLOT1_DEFAULT                               0x00000000
#define ADMA_ADDRESS_HIGH_SLOT1_ADDR                                 0x0000015c
#define ADMA_ADDRESS_HIGH_SLOT1_DEFAULT                              0x00000000
#define PRESET_VALUE_0_SLOT1_ADDR                                    0x00000160
#define PRESET_VALUE_0_SLOT1_DEFAULT                                 0x00000000
#define PRESET_VALUE_1_SLOT1_ADDR                                    0x00000164
#define PRESET_VALUE_1_SLOT1_DEFAULT                                 0x00000000
#define PRESET_VALUE_2_SLOT1_ADDR                                    0x00000168
#define PRESET_VALUE_2_SLOT1_DEFAULT                                 0x00000000
#define PRESET_VALUE_3_SLOT1_ADDR                                    0x0000016c
#define PRESET_VALUE_3_SLOT1_DEFAULT                                 0x00000000
#define BOOT_TIMEOUT_CONTROL_SLOT1_ADDR                              0x00000170
#define BOOT_TIMEOUT_CONTROL_SLOT1_DEFAULT                           0x00000000
#define SHARED_BUS_CONTROL_SLOT1_ADDR                                0x000001e0
#define SHARED_BUS_CONTROL_SLOT1_DEFAULT                             0x00000000
#define SPI_INT_SUPPORT_SLOT1_ADDR                                   0x000001f0
#define SPI_INT_SUPPORT_SLOT1_DEFAULT                                0x00000000

/*	Register SDMA_System_Address	*/ 
/*	 Fields SDMA_SYSTEM_ADDRESS_HIGH	 */
#define SDMA_SYSTEM_ADDRESS_HIGH_WIDTH                                       16
#define SDMA_SYSTEM_ADDRESS_HIGH_SHIFT                                       16
#define SDMA_SYSTEM_ADDRESS_HIGH_MASK                                0xffff0000
#define SDMA_SYSTEM_ADDRESS_HIGH_RD(src)             (((src) & 0xffff0000)>>16)
#define SDMA_SYSTEM_ADDRESS_HIGH_WR(src)        (((u32)(src)<<16) & 0xffff0000)
#define SDMA_SYSTEM_ADDRESS_HIGH_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields SDMA_SYSTEM_ADDRESS_LOW	 */
#define SDMA_SYSTEM_ADDRESS_LOW_WIDTH                                        16
#define SDMA_SYSTEM_ADDRESS_LOW_SHIFT                                         0
#define SDMA_SYSTEM_ADDRESS_LOW_MASK                                 0x0000ffff
#define SDMA_SYSTEM_ADDRESS_LOW_RD(src)                  (((src) & 0x0000ffff))
#define SDMA_SYSTEM_ADDRESS_LOW_WR(src)             (((u32)(src)) & 0x0000ffff)
#define SDMA_SYSTEM_ADDRESS_LOW_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register Block_DEF	*/ 
/*	 Fields BLOCK_SIZE	 */
#define BLOCK_SIZE_WIDTH                                                     16
#define BLOCK_SIZE_SHIFT                                                     16
#define BLOCK_SIZE_MASK                                              0xffff0000
#define BLOCK_SIZE_RD(src)                           (((src) & 0xffff0000)>>16)
#define BLOCK_SIZE_WR(src)                      (((u32)(src)<<16) & 0xffff0000)
#define BLOCK_SIZE_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields BLOCK_COUNT	 */
#define REGSPEC_BLOCK_COUNT_WIDTH_SDHC                                            16
#define REGSPEC_BLOCK_COUNT_SHIFT_SDHC                                             0
#define REGSPEC_BLOCK_COUNT_MASK_SDHC                                     0x0000ffff
#define REGSPEC_BLOCK_COUNT_RD_SDHC(src)                      (((src) & 0x0000ffff))
#define REGSPEC_BLOCK_COUNT_WR_SDHC(src)                 (((u32)(src)) & 0x0000ffff)
#define REGSPEC_BLOCK_COUNT_SET_SDHC(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register ARGUMENT	*/ 
/*	 Fields ARGUMENT_HIGH	 */
#define ARGUMENT_HIGH_WIDTH                                                  16
#define ARGUMENT_HIGH_SHIFT                                                  16
#define ARGUMENT_HIGH_MASK                                           0xffff0000
#define ARGUMENT_HIGH_RD(src)                        (((src) & 0xffff0000)>>16)
#define ARGUMENT_HIGH_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define ARGUMENT_HIGH_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields ARGUMENT_LOW	 */
#define ARGUMENT_LOW_WIDTH                                                   16
#define ARGUMENT_LOW_SHIFT                                                    0
#define ARGUMENT_LOW_MASK                                            0x0000ffff
#define ARGUMENT_LOW_RD(src)                             (((src) & 0x0000ffff))
#define ARGUMENT_LOW_WR(src)                        (((u32)(src)) & 0x0000ffff)
#define ARGUMENT_LOW_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register TRANSFERMODE_COMMAND	*/ 
/*	 Fields COMMAND_2	 */
#define COMMAND_2_WIDTH                                                      11
#define COMMAND_2_SHIFT                                                      19
#define COMMAND_2_MASK                                               0x3ff80000
#define COMMAND_2_RD(src)                            (((src) & 0x3ff80000)>>19)
#define COMMAND_2_WR(src)                       (((u32)(src)<<19) & 0x3ff80000)
#define COMMAND_2_SET(dst,src) \
                      (((dst) & ~0x3ff80000) | (((u32)(src)<<19) & 0x3ff80000))
/*	 Fields COMMAND_1	 */
#define COMMAND_1_WIDTH                                                       2
#define COMMAND_1_SHIFT                                                      16
#define COMMAND_1_MASK                                               0x00030000
#define COMMAND_1_RD(src)                            (((src) & 0x00030000)>>16)
#define COMMAND_1_WR(src)                       (((u32)(src)<<16) & 0x00030000)
#define COMMAND_1_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields TRANSFERMODE	 */
#define REGSPEC_TRANSFERMODE_WIDTH                                            6
#define REGSPEC_TRANSFERMODE_SHIFT                                            0
#define REGSPEC_TRANSFERMODE_MASK                                    0x0000003f
#define REGSPEC_TRANSFERMODE_RD(src)                     (((src) & 0x0000003f))
#define REGSPEC_TRANSFERMODE_WR(src)                (((u32)(src)) & 0x0000003f)
#define REGSPEC_TRANSFERMODE_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register RESPONSE_0_1	*/ 
/*	 Fields RESPONSE_1	 */
#define RESPONSE_11_WIDTH                                                    16
#define RESPONSE_11_SHIFT                                                    16
#define RESPONSE_11_MASK                                             0xffff0000
#define RESPONSE_11_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_11_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_0	 */
#define RESPONSE_01_WIDTH                                                    16
#define RESPONSE_01_SHIFT                                                     0
#define RESPONSE_01_MASK                                             0x0000ffff
#define RESPONSE_01_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_01_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RESPONSE_2_3	*/ 
/*	 Fields RESPONSE_3	 */
#define RESPONSE_33_WIDTH                                                    16
#define RESPONSE_33_SHIFT                                                    16
#define RESPONSE_33_MASK                                             0xffff0000
#define RESPONSE_33_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_33_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_2	 */
#define RESPONSE_23_WIDTH                                                    16
#define RESPONSE_23_SHIFT                                                     0
#define RESPONSE_23_MASK                                             0x0000ffff
#define RESPONSE_23_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_23_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RESPONSE_4_5	*/ 
/*	 Fields RESPONSE_5	 */
#define RESPONSE_55_WIDTH                                                    16
#define RESPONSE_55_SHIFT                                                    16
#define RESPONSE_55_MASK                                             0xffff0000
#define RESPONSE_55_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_55_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_4	 */
#define RESPONSE_45_WIDTH                                                    16
#define RESPONSE_45_SHIFT                                                     0
#define RESPONSE_45_MASK                                             0x0000ffff
#define RESPONSE_45_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_45_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RESPONSE_6_7	*/ 
/*	 Fields RESPONSE_7	 */
#define RESPONSE_77_WIDTH                                                    16
#define RESPONSE_77_SHIFT                                                    16
#define RESPONSE_77_MASK                                             0xffff0000
#define RESPONSE_77_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_77_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_6	 */
#define RESPONSE_67_WIDTH                                                    16
#define RESPONSE_67_SHIFT                                                     0
#define RESPONSE_67_MASK                                             0x0000ffff
#define RESPONSE_67_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_67_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register BUFFER_DATA_PORT	*/ 
/*	 Fields BUFFER_DATA_PORT_1	 */
#define BUFFER_DATA_PORT_1_WIDTH                                             16
#define BUFFER_DATA_PORT_1_SHIFT                                             16
#define BUFFER_DATA_PORT_1_MASK                                      0xffff0000
#define BUFFER_DATA_PORT_1_RD(src)                   (((src) & 0xffff0000)>>16)
#define BUFFER_DATA_PORT_1_WR(src)              (((u32)(src)<<16) & 0xffff0000)
#define BUFFER_DATA_PORT_1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields BUFFER_DATA_PORT_0	 */
#define BUFFER_DATA_PORT_0_WIDTH                                             16
#define BUFFER_DATA_PORT_0_SHIFT                                              0
#define BUFFER_DATA_PORT_0_MASK                                      0x0000ffff
#define BUFFER_DATA_PORT_0_RD(src)                       (((src) & 0x0000ffff))
#define BUFFER_DATA_PORT_0_WR(src)                  (((u32)(src)) & 0x0000ffff)
#define BUFFER_DATA_PORT_0_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register PRESENT_STATE	*/ 
/*	 Fields PRESENT_STATUS	 */
#define PRESENT_STATUS_WIDTH                                                 17
#define PRESENT_STATUS_SHIFT                                                  0
#define PRESENT_STATUS_MASK                                          0x0001ffff
#define PRESENT_STATUS_RD(src)                           (((src) & 0x0001ffff))
#define PRESENT_STATUS_SET(dst,src) \
                          (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register GAP_WAKEUP_POWER_HOST_CONTROL	*/ 
/*	 Fields WAKEUP_CONTROL	 */
#define WAKEUP_CONTROL_WIDTH                                                  3
#define WAKEUP_CONTROL_SHIFT                                                 24
#define WAKEUP_CONTROL_MASK                                          0x07000000
#define WAKEUP_CONTROL_RD(src)                       (((src) & 0x07000000)>>24)
#define WAKEUP_CONTROL_WR(src)                  (((u32)(src)<<24) & 0x07000000)
#define WAKEUP_CONTROL_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields BLOCK_GAP_CONTROL	 */
#define BLOCK_GAP_CONTROL_WIDTH                                               7
#define BLOCK_GAP_CONTROL_SHIFT                                              16
#define BLOCK_GAP_CONTROL_MASK                                       0x007f0000
#define BLOCK_GAP_CONTROL_RD(src)                    (((src) & 0x007f0000)>>16)
#define BLOCK_GAP_CONTROL_WR(src)               (((u32)(src)<<16) & 0x007f0000)
#define BLOCK_GAP_CONTROL_SET(dst,src) \
                      (((dst) & ~0x007f0000) | (((u32)(src)<<16) & 0x007f0000))
/*	 Fields POWER_CONTROL	 */
#define POWER_CONTROL_WIDTH                                                   5
#define POWER_CONTROL_SHIFT                                                   8
#define POWER_CONTROL_MASK                                           0x00001f00
#define POWER_CONTROL_RD(src)                         (((src) & 0x00001f00)>>8)
#define POWER_CONTROL_WR(src)                    (((u32)(src)<<8) & 0x00001f00)
#define POWER_CONTROL_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields HOST_CONTROL	 */
#define HOST_CONTROL_WIDTH                                                    8
#define HOST_CONTROL_SHIFT                                                    0
#define HOST_CONTROL_MASK                                            0x000000ff
#define HOST_CONTROL_RD(src)                             (((src) & 0x000000ff))
#define HOST_CONTROL_WR(src)                        (((u32)(src)) & 0x000000ff)
#define HOST_CONTROL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register SRESET_CLOCK_CONTROL	*/ 
/*	 Fields SOFTWARE_RESET_CONTROL	 */
#define SOFTWARE_RESET_CONTROL_WIDTH                                          3
#define SOFTWARE_RESET_CONTROL_SHIFT                                         24
#define SOFTWARE_RESET_CONTROL_MASK                                  0x07000000
#define SOFTWARE_RESET_CONTROL_RD(src)               (((src) & 0x07000000)>>24)
#define SOFTWARE_RESET_CONTROL_WR(src)          (((u32)(src)<<24) & 0x07000000)
#define SOFTWARE_RESET_CONTROL_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields TIMEOUT_CONTROL	 */
#define TIMEOUT_CONTROL_WIDTH                                                 4
#define TIMEOUT_CONTROL_SHIFT                                                16
#define TIMEOUT_CONTROL_MASK                                         0x000f0000
#define TIMEOUT_CONTROL_RD(src)                      (((src) & 0x000f0000)>>16)
#define TIMEOUT_CONTROL_WR(src)                 (((u32)(src)<<16) & 0x000f0000)
#define TIMEOUT_CONTROL_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields CLOCK_CONTROL	 */
#define CLOCK_CONTROL_WIDTH                                                  14
#define CLOCK_CONTROL_SHIFT                                                   0
#define CLOCK_CONTROL_MASK                                           0x00003fff
#define CLOCK_CONTROL_RD(src)                            (((src) & 0x00003fff))
#define CLOCK_CONTROL_WR(src)                       (((u32)(src)) & 0x00003fff)
#define CLOCK_CONTROL_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register INT_STATUS	*/ 
/*	 Fields ERROR_INTERRUPT_STATUS	 */
#define ERROR_INTERRUPT_STATUS_WIDTH                                         12
#define ERROR_INTERRUPT_STATUS_SHIFT                                         16
#define ERROR_INTERRUPT_STATUS_MASK                                  0x0fff0000
#define ERROR_INTERRUPT_STATUS_RD(src)               (((src) & 0x0fff0000)>>16)
#define ERROR_INTERRUPT_STATUS_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields NORMAL_INTERRUPT_STATUS	 */
#define NORMAL_INTERRUPT_STATUS_WIDTH                                        16
#define NORMAL_INTERRUPT_STATUS_SHIFT                                         0
#define NORMAL_INTERRUPT_STATUS_MASK                                 0x0000ffff
#define NORMAL_INTERRUPT_STATUS_RD(src)                  (((src) & 0x0000ffff))
#define NORMAL_INTERRUPT_STATUS_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register INT_STATUS_ENABLE	*/ 
/*	 Fields ERROR_INTERRUPT_STATUS_ENABLE	 */
#define ERROR_INTERRUPT_STATUS_ENABLE_WIDTH                                  12
#define ERROR_INTERRUPT_STATUS_ENABLE_SHIFT                                  16
#define ERROR_INTERRUPT_STATUS_ENABLE_MASK                           0x0fff0000
#define ERROR_INTERRUPT_STATUS_ENABLE_RD(src)        (((src) & 0x0fff0000)>>16)
#define ERROR_INTERRUPT_STATUS_ENABLE_WR(src)   (((u32)(src)<<16) & 0x0fff0000)
#define ERROR_INTERRUPT_STATUS_ENABLE_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields NORMAL_INTERRUPT_STATUS_ENABLE	 */
#define NORMAL_INTERRUPT_STATUS_ENABLE_WIDTH                                 16
#define NORMAL_INTERRUPT_STATUS_ENABLE_SHIFT                                  0
#define NORMAL_INTERRUPT_STATUS_ENABLE_MASK                          0x0000ffff
#define NORMAL_INTERRUPT_STATUS_ENABLE_RD(src)           (((src) & 0x0000ffff))
#define NORMAL_INTERRUPT_STATUS_ENABLE_WR(src)      (((u32)(src)) & 0x0000ffff)
#define NORMAL_INTERRUPT_STATUS_ENABLE_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register INT_SIGNAL_ENABLE	*/ 
/*	 Fields ERROR_INTERRUPT_SIGNAL_ENABLE	 */
#define ERROR_INTERRUPT_SIGNAL_ENABLE_WIDTH                                  12
#define ERROR_INTERRUPT_SIGNAL_ENABLE_SHIFT                                  16
#define ERROR_INTERRUPT_SIGNAL_ENABLE_MASK                           0x0fff0000
#define ERROR_INTERRUPT_SIGNAL_ENABLE_RD(src)        (((src) & 0x0fff0000)>>16)
#define ERROR_INTERRUPT_SIGNAL_ENABLE_WR(src)   (((u32)(src)<<16) & 0x0fff0000)
#define ERROR_INTERRUPT_SIGNAL_ENABLE_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields NORMAL_INTERRUPT_SIGNAL_ENABLE	 */
#define NORMAL_INTERRUPT_SIGNAL_ENABLE_WIDTH                                 16
#define NORMAL_INTERRUPT_SIGNAL_ENABLE_SHIFT                                  0
#define NORMAL_INTERRUPT_SIGNAL_ENABLE_MASK                          0x0000ffff
#define NORMAL_INTERRUPT_SIGNAL_ENABLE_RD(src)           (((src) & 0x0000ffff))
#define NORMAL_INTERRUPT_SIGNAL_ENABLE_WR(src)      (((u32)(src)) & 0x0000ffff)
#define NORMAL_INTERRUPT_SIGNAL_ENABLE_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register AUTO_CMD_ERROR_STATUS	*/ 
/*	 Fields HOST_CONTROL_2	 */
#define HOST_CONTROL_2_WIDTH                                                 10
#define HOST_CONTROL_2_SHIFT                                                 16
#define HOST_CONTROL_2_MASK                                          0x03ff0000
#define HOST_CONTROL_2_RD(src)                       (((src) & 0x03ff0000)>>16)
#define HOST_CONTROL_2_WR(src)                  (((u32)(src)<<16) & 0x03ff0000)
#define HOST_CONTROL_2_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields AUTO_CMD_ERROR_STATUS	 */
#define AUTO_CMD_ERROR_STATUS_WIDTH                                           6
#define AUTO_CMD_ERROR_STATUS_SHIFT                                           0
#define AUTO_CMD_ERROR_STATUS_MASK                                   0x0000003f
#define AUTO_CMD_ERROR_STATUS_RD(src)                    (((src) & 0x0000003f))
#define AUTO_CMD_ERROR_STATUS_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register CAPABILITIES_0	*/ 
/*	 Fields CAPABILITIES_0	 */
#define CAPABILITIES_00_WIDTH                                                30
#define CAPABILITIES_00_SHIFT                                                 0
#define CAPABILITIES_00_MASK                                         0x3fffffff
#define CAPABILITIES_00_RD(src)                          (((src) & 0x3fffffff))
#define CAPABILITIES_00_SET(dst,src) \
                          (((dst) & ~0x3fffffff) | (((u32)(src)) & 0x3fffffff))

/*	Register CAPABILITIES_1	*/ 
/*	 Fields CAPABILITIES_1	 */
#define CAPABILITIES_11_WIDTH                                                21
#define CAPABILITIES_11_SHIFT                                                 0
#define CAPABILITIES_11_MASK                                         0x001fffff
#define CAPABILITIES_11_RD(src)                          (((src) & 0x001fffff))
#define CAPABILITIES_11_SET(dst,src) \
                          (((dst) & ~0x001fffff) | (((u32)(src)) & 0x001fffff))

/*	Register MAX_CURRENT_CAPABILITIES_0	*/ 
/*	 Fields MAX_CURRENT_CAPABILITIES_0	 */
#define MAX_CURRENT_CAPABILITIES_00_WIDTH                                    24
#define MAX_CURRENT_CAPABILITIES_00_SHIFT                                     0
#define MAX_CURRENT_CAPABILITIES_00_MASK                             0x00ffffff
#define MAX_CURRENT_CAPABILITIES_00_RD(src)              (((src) & 0x00ffffff))
#define MAX_CURRENT_CAPABILITIES_00_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register MAX_CURRENT_CAPABILITIES_1	*/ 

/*	Register FORCE_EVENT	*/ 
/*	 Fields FORCE_EVENT_FOR_ERROR_INT_STATUS	 */
#define FORCE_EVENT_FOR_ERROR_INT_STATUS_WIDTH                               10
#define FORCE_EVENT_FOR_ERROR_INT_STATUS_SHIFT                               16
#define FORCE_EVENT_FOR_ERROR_INT_STATUS_MASK                        0x03ff0000
#define FORCE_EVENT_FOR_ERROR_INT_STATUS_RD(src)     (((src) & 0x03ff0000)>>16)
#define FORCE_EVENT_FOR_ERROR_INT_STATUS_WR(src) \
                                                (((u32)(src)<<16) & 0x03ff0000)
#define FORCE_EVENT_FOR_ERROR_INT_STATUS_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields FORCE_EVENT_FOR_AUTO_CMD_ERROR	 */
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR_WIDTH                                  6
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR_SHIFT                                  0
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR_MASK                          0x0000003f
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR_RD(src)           (((src) & 0x0000003f))
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR_WR(src)      (((u32)(src)) & 0x0000003f)
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register ADMA_ERROR_STATUS	*/ 
/*	 Fields ADMA_ERROR_STATUS	 */
#define ADMA_ERROR_STATUS_WIDTH                                               3
#define ADMA_ERROR_STATUS_SHIFT                                               0
#define ADMA_ERROR_STATUS_MASK                                       0x00000007
#define ADMA_ERROR_STATUS_RD(src)                        (((src) & 0x00000007))
#define ADMA_ERROR_STATUS_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register ADMA_ADDRESS_LOW	*/ 
/*	 Fields ADMA_ADDRESS_LOW	 */
#define ADMA_ADDRESS_LOW_WIDTH                                               32
#define ADMA_ADDRESS_LOW_SHIFT                                                0
#define ADMA_ADDRESS_LOW_MASK                                        0xffffffff
#define ADMA_ADDRESS_LOW_RD(src)                         (((src) & 0xffffffff))
#define ADMA_ADDRESS_LOW_WR(src)                    (((u32)(src)) & 0xffffffff)
#define ADMA_ADDRESS_LOW_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ADMA_ADDRESS_HIGH	*/ 

/*	Register PRESET_VALUE_0	*/ 
/*	 Fields PRESET_VALUE_0_2	 */
#define PRESET_VALUE_0_20_WIDTH                                              14
#define PRESET_VALUE_0_20_SHIFT                                              16
#define PRESET_VALUE_0_20_MASK                                       0x3fff0000
#define PRESET_VALUE_0_20_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_0_20_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_0_20_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_0_1	 */
#define PRESET_VALUE_0_10_WIDTH                                              14
#define PRESET_VALUE_0_10_SHIFT                                               0
#define PRESET_VALUE_0_10_MASK                                       0x00003fff
#define PRESET_VALUE_0_10_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_0_10_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_0_10_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register PRESET_VALUE_1	*/ 
/*	 Fields PRESET_VALUE_1_2	 */
#define PRESET_VALUE_1_21_WIDTH                                              14
#define PRESET_VALUE_1_21_SHIFT                                              16
#define PRESET_VALUE_1_21_MASK                                       0x3fff0000
#define PRESET_VALUE_1_21_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_1_21_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_1_21_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_1_1	 */
#define PRESET_VALUE_1_11_WIDTH                                              14
#define PRESET_VALUE_1_11_SHIFT                                               0
#define PRESET_VALUE_1_11_MASK                                       0x00003fff
#define PRESET_VALUE_1_11_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_1_11_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_1_11_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register PRESET_VALUE_2	*/ 
/*	 Fields PRESET_VALUE_2_2	 */
#define PRESET_VALUE_2_22_WIDTH                                              14
#define PRESET_VALUE_2_22_SHIFT                                              16
#define PRESET_VALUE_2_22_MASK                                       0x3fff0000
#define PRESET_VALUE_2_22_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_2_22_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_2_22_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_2_1	 */
#define PRESET_VALUE_2_12_WIDTH                                              14
#define PRESET_VALUE_2_12_SHIFT                                               0
#define PRESET_VALUE_2_12_MASK                                       0x00003fff
#define PRESET_VALUE_2_12_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_2_12_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_2_12_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register PRESET_VALUE_3	*/ 
/*	 Fields PRESET_VALUE_3_2	 */
#define PRESET_VALUE_3_23_WIDTH                                              14
#define PRESET_VALUE_3_23_SHIFT                                              16
#define PRESET_VALUE_3_23_MASK                                       0x3fff0000
#define PRESET_VALUE_3_23_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_3_23_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_3_23_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_3_1	 */
#define PRESET_VALUE_3_13_WIDTH                                              14
#define PRESET_VALUE_3_13_SHIFT                                               0
#define PRESET_VALUE_3_13_MASK                                       0x00003fff
#define PRESET_VALUE_3_13_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_3_13_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_3_13_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register BOOT_TIMEOUT_CONTROL	*/ 
/*	 Fields BOOT_TIMEOUT_CONTROL	 */
#define BOOT_TIMEOUT_CONTROL_WIDTH                                           32
#define BOOT_TIMEOUT_CONTROL_SHIFT                                            0
#define BOOT_TIMEOUT_CONTROL_MASK                                    0xffffffff
#define BOOT_TIMEOUT_CONTROL_RD(src)                     (((src) & 0xffffffff))
#define BOOT_TIMEOUT_CONTROL_WR(src)                (((u32)(src)) & 0xffffffff)
#define BOOT_TIMEOUT_CONTROL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SHARED_BUS_CONTROL	*/ 
/*	 Fields SHARED_BUS_CONTROL_6	 */
#define SHARED_BUS_CONTROL_6_WIDTH                                            7
#define SHARED_BUS_CONTROL_6_SHIFT                                           24
#define SHARED_BUS_CONTROL_6_MASK                                    0x7f000000
#define SHARED_BUS_CONTROL_6_RD(src)                 (((src) & 0x7f000000)>>24)
#define SHARED_BUS_CONTROL_6_WR(src)            (((u32)(src)<<24) & 0x7f000000)
#define SHARED_BUS_CONTROL_6_SET(dst,src) \
                      (((dst) & ~0x7f000000) | (((u32)(src)<<24) & 0x7f000000))
/*	 Fields SHARED_BUS_CONTROL_5	 */
#define SHARED_BUS_CONTROL_5_WIDTH                                            3
#define SHARED_BUS_CONTROL_5_SHIFT                                           20
#define SHARED_BUS_CONTROL_5_MASK                                    0x00700000
#define SHARED_BUS_CONTROL_5_RD(src)                 (((src) & 0x00700000)>>20)
#define SHARED_BUS_CONTROL_5_WR(src)            (((u32)(src)<<20) & 0x00700000)
#define SHARED_BUS_CONTROL_5_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields SHARED_BUS_CONTROL_4	 */
#define SHARED_BUS_CONTROL_4_WIDTH                                            3
#define SHARED_BUS_CONTROL_4_SHIFT                                           16
#define SHARED_BUS_CONTROL_4_MASK                                    0x00070000
#define SHARED_BUS_CONTROL_4_RD(src)                 (((src) & 0x00070000)>>16)
#define SHARED_BUS_CONTROL_4_WR(src)            (((u32)(src)<<16) & 0x00070000)
#define SHARED_BUS_CONTROL_4_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields SHARED_BUS_CONTROL_3	 */
#define SHARED_BUS_CONTROL_3_WIDTH                                            7
#define SHARED_BUS_CONTROL_3_SHIFT                                            8
#define SHARED_BUS_CONTROL_3_MASK                                    0x00007f00
#define SHARED_BUS_CONTROL_3_RD(src)                  (((src) & 0x00007f00)>>8)
#define SHARED_BUS_CONTROL_3_SET(dst,src) \
                       (((dst) & ~0x00007f00) | (((u32)(src)<<8) & 0x00007f00))
/*	 Fields SHARED_BUS_CONTROL_2	 */
#define SHARED_BUS_CONTROL_2_WIDTH                                            2
#define SHARED_BUS_CONTROL_2_SHIFT                                            4
#define SHARED_BUS_CONTROL_2_MASK                                    0x00000030
#define SHARED_BUS_CONTROL_2_RD(src)                  (((src) & 0x00000030)>>4)
#define SHARED_BUS_CONTROL_2_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields SHARED_BUS_CONTROL_1	 */
#define SHARED_BUS_CONTROL_1_WIDTH                                            3
#define SHARED_BUS_CONTROL_1_SHIFT                                            0
#define SHARED_BUS_CONTROL_1_MASK                                    0x00000007
#define SHARED_BUS_CONTROL_1_RD(src)                     (((src) & 0x00000007))
#define SHARED_BUS_CONTROL_1_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register SPI_INT_SUPPORT	*/ 
/*	 Fields SPI_INT_SUPPORT	 */
#define SPI_INT_SUPPORT_WIDTH                                                 8
#define SPI_INT_SUPPORT_SHIFT                                                 0
#define SPI_INT_SUPPORT_MASK                                         0x000000ff
#define SPI_INT_SUPPORT_RD(src)                          (((src) & 0x000000ff))
#define SPI_INT_SUPPORT_WR(src)                     (((u32)(src)) & 0x000000ff)
#define SPI_INT_SUPPORT_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register SLOT_INTR_STATUS_HOST_CONTROLLER_VERSION	*/ 
/*	 Fields HOST_CONTROLLER_VERSION	 */
#define HOST_CONTROLLER_VERSION_WIDTH                                        16
#define HOST_CONTROLLER_VERSION_SHIFT                                        16
#define HOST_CONTROLLER_VERSION_MASK                                 0xffff0000
#define HOST_CONTROLLER_VERSION_RD(src)              (((src) & 0xffff0000)>>16)
#define HOST_CONTROLLER_VERSION_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields SLOT_INTR_STATUS	 */
#define SLOT_INTR_STATUS_WIDTH                                                8
#define SLOT_INTR_STATUS_SHIFT                                                0
#define SLOT_INTR_STATUS_MASK                                        0x000000ff
#define SLOT_INTR_STATUS_RD(src)                         (((src) & 0x000000ff))
#define SLOT_INTR_STATUS_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register SDMA_System_Address_Slot1	*/ 
/*	 Fields SDMA_SYSTEM_ADDRESS_HIGH	 */
#define SDMA_SYSTEM_ADDRESS_HIGH1_WIDTH                                      16
#define SDMA_SYSTEM_ADDRESS_HIGH1_SHIFT                                      16
#define SDMA_SYSTEM_ADDRESS_HIGH1_MASK                               0xffff0000
#define SDMA_SYSTEM_ADDRESS_HIGH1_RD(src)            (((src) & 0xffff0000)>>16)
#define SDMA_SYSTEM_ADDRESS_HIGH1_WR(src)       (((u32)(src)<<16) & 0xffff0000)
#define SDMA_SYSTEM_ADDRESS_HIGH1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields SDMA_SYSTEM_ADDRESS_LOW	 */
#define SDMA_SYSTEM_ADDRESS_LOW1_WIDTH                                       16
#define SDMA_SYSTEM_ADDRESS_LOW1_SHIFT                                        0
#define SDMA_SYSTEM_ADDRESS_LOW1_MASK                                0x0000ffff
#define SDMA_SYSTEM_ADDRESS_LOW1_RD(src)                 (((src) & 0x0000ffff))
#define SDMA_SYSTEM_ADDRESS_LOW1_WR(src)            (((u32)(src)) & 0x0000ffff)
#define SDMA_SYSTEM_ADDRESS_LOW1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register Block_DEF_Slot1	*/ 
/*	 Fields BLOCK_SIZE	 */
#define BLOCK_SIZE1_WIDTH                                                    16
#define BLOCK_SIZE1_SHIFT                                                    16
#define BLOCK_SIZE1_MASK                                             0xffff0000
#define BLOCK_SIZE1_RD(src)                          (((src) & 0xffff0000)>>16)
#define BLOCK_SIZE1_WR(src)                     (((u32)(src)<<16) & 0xffff0000)
#define BLOCK_SIZE1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields BLOCK_COUNT	 */
#define REGSPEC_BLOCK_COUNT1_WIDTH                                           16
#define REGSPEC_BLOCK_COUNT1_SHIFT                                            0
#define REGSPEC_BLOCK_COUNT1_MASK                                    0x0000ffff
#define REGSPEC_BLOCK_COUNT1_RD(src)                     (((src) & 0x0000ffff))
#define REGSPEC_BLOCK_COUNT1_WR(src)                (((u32)(src)) & 0x0000ffff)
#define REGSPEC_BLOCK_COUNT1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register ARGUMENT_Slot1	*/ 
/*	 Fields ARGUMENT_HIGH	 */
#define ARGUMENT_HIGH1_WIDTH                                                 16
#define ARGUMENT_HIGH1_SHIFT                                                 16
#define ARGUMENT_HIGH1_MASK                                          0xffff0000
#define ARGUMENT_HIGH1_RD(src)                       (((src) & 0xffff0000)>>16)
#define ARGUMENT_HIGH1_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define ARGUMENT_HIGH1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields ARGUMENT_LOW	 */
#define ARGUMENT_LOW1_WIDTH                                                  16
#define ARGUMENT_LOW1_SHIFT                                                   0
#define ARGUMENT_LOW1_MASK                                           0x0000ffff
#define ARGUMENT_LOW1_RD(src)                            (((src) & 0x0000ffff))
#define ARGUMENT_LOW1_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define ARGUMENT_LOW1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register TRANSFERMODE_COMMAND_Slot1	*/ 
/*	 Fields COMMAND_2	 */
#define COMMAND_21_WIDTH                                                     11
#define COMMAND_21_SHIFT                                                     19
#define COMMAND_21_MASK                                              0x3ff80000
#define COMMAND_21_RD(src)                           (((src) & 0x3ff80000)>>19)
#define COMMAND_21_WR(src)                      (((u32)(src)<<19) & 0x3ff80000)
#define COMMAND_21_SET(dst,src) \
                      (((dst) & ~0x3ff80000) | (((u32)(src)<<19) & 0x3ff80000))
/*	 Fields COMMAND_1	 */
#define COMMAND_11_WIDTH                                                      2
#define COMMAND_11_SHIFT                                                     16
#define COMMAND_11_MASK                                              0x00030000
#define COMMAND_11_RD(src)                           (((src) & 0x00030000)>>16)
#define COMMAND_11_WR(src)                      (((u32)(src)<<16) & 0x00030000)
#define COMMAND_11_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields TRANSFERMODE	 */
#define REGSPEC_TRANSFERMODE1_WIDTH                                           6
#define REGSPEC_TRANSFERMODE1_SHIFT                                           0
#define REGSPEC_TRANSFERMODE1_MASK                                   0x0000003f
#define REGSPEC_TRANSFERMODE1_RD(src)                    (((src) & 0x0000003f))
#define REGSPEC_TRANSFERMODE1_WR(src)               (((u32)(src)) & 0x0000003f)
#define REGSPEC_TRANSFERMODE1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register RESPONSE_0_1_Slot1	*/ 
/*	 Fields RESPONSE_1	 */
#define RESPONSE_11_F1_WIDTH                                                 16
#define RESPONSE_11_F1_SHIFT                                                 16
#define RESPONSE_11_F1_MASK                                          0xffff0000
#define RESPONSE_11_F1_RD(src)                       (((src) & 0xffff0000)>>16)
#define RESPONSE_11_F1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_0	 */
#define RESPONSE_01_F1_WIDTH                                                 16
#define RESPONSE_01_F1_SHIFT                                                  0
#define RESPONSE_01_F1_MASK                                          0x0000ffff
#define RESPONSE_01_F1_RD(src)                           (((src) & 0x0000ffff))
#define RESPONSE_01_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RESPONSE_2_3_Slot1	*/ 
/*	 Fields RESPONSE_3	 */
#define RESPONSE_31_WIDTH                                                    16
#define RESPONSE_31_SHIFT                                                    16
#define RESPONSE_31_MASK                                             0xffff0000
#define RESPONSE_31_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_31_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_2	 */
#define RESPONSE_21_WIDTH                                                    16
#define RESPONSE_21_SHIFT                                                     0
#define RESPONSE_21_MASK                                             0x0000ffff
#define RESPONSE_21_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_21_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RESPONSE_4_5_Slot1	*/ 
/*	 Fields RESPONSE_5	 */
#define RESPONSE_51_WIDTH                                                    16
#define RESPONSE_51_SHIFT                                                    16
#define RESPONSE_51_MASK                                             0xffff0000
#define RESPONSE_51_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_51_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_4	 */
#define RESPONSE_41_WIDTH                                                    16
#define RESPONSE_41_SHIFT                                                     0
#define RESPONSE_41_MASK                                             0x0000ffff
#define RESPONSE_41_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_41_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register RESPONSE_6_7_Slot1	*/ 
/*	 Fields RESPONSE_7	 */
#define RESPONSE_71_WIDTH                                                    16
#define RESPONSE_71_SHIFT                                                    16
#define RESPONSE_71_MASK                                             0xffff0000
#define RESPONSE_71_RD(src)                          (((src) & 0xffff0000)>>16)
#define RESPONSE_71_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESPONSE_6	 */
#define RESPONSE_61_WIDTH                                                    16
#define RESPONSE_61_SHIFT                                                     0
#define RESPONSE_61_MASK                                             0x0000ffff
#define RESPONSE_61_RD(src)                              (((src) & 0x0000ffff))
#define RESPONSE_61_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register BUFFER_DATA_PORT_Slot1	*/ 
/*	 Fields BUFFER_DATA_PORT_1	 */
#define BUFFER_DATA_PORT_11_WIDTH                                            16
#define BUFFER_DATA_PORT_11_SHIFT                                            16
#define BUFFER_DATA_PORT_11_MASK                                     0xffff0000
#define BUFFER_DATA_PORT_11_RD(src)                  (((src) & 0xffff0000)>>16)
#define BUFFER_DATA_PORT_11_WR(src)             (((u32)(src)<<16) & 0xffff0000)
#define BUFFER_DATA_PORT_11_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields BUFFER_DATA_PORT_0	 */
#define BUFFER_DATA_PORT_01_WIDTH                                            16
#define BUFFER_DATA_PORT_01_SHIFT                                             0
#define BUFFER_DATA_PORT_01_MASK                                     0x0000ffff
#define BUFFER_DATA_PORT_01_RD(src)                      (((src) & 0x0000ffff))
#define BUFFER_DATA_PORT_01_WR(src)                 (((u32)(src)) & 0x0000ffff)
#define BUFFER_DATA_PORT_01_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register PRESENT_STATE_Slot1	*/ 
/*	 Fields PRESENT_STATUS	 */
#define PRESENT_STATUS1_WIDTH                                                17
#define PRESENT_STATUS1_SHIFT                                                 0
#define PRESENT_STATUS1_MASK                                         0x0001ffff
#define PRESENT_STATUS1_RD(src)                          (((src) & 0x0001ffff))
#define PRESENT_STATUS1_SET(dst,src) \
                          (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register GAP_WAKEUP_POWER_HOST_CONTROL_Slot1	*/ 
/*	 Fields WAKEUP_CONTROL	 */
#define WAKEUP_CONTROL1_WIDTH                                                 3
#define WAKEUP_CONTROL1_SHIFT                                                24
#define WAKEUP_CONTROL1_MASK                                         0x07000000
#define WAKEUP_CONTROL1_RD(src)                      (((src) & 0x07000000)>>24)
#define WAKEUP_CONTROL1_WR(src)                 (((u32)(src)<<24) & 0x07000000)
#define WAKEUP_CONTROL1_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields BLOCK_GAP_CONTROL	 */
#define BLOCK_GAP_CONTROL1_WIDTH                                              7
#define BLOCK_GAP_CONTROL1_SHIFT                                             16
#define BLOCK_GAP_CONTROL1_MASK                                      0x007f0000
#define BLOCK_GAP_CONTROL1_RD(src)                   (((src) & 0x007f0000)>>16)
#define BLOCK_GAP_CONTROL1_WR(src)              (((u32)(src)<<16) & 0x007f0000)
#define BLOCK_GAP_CONTROL1_SET(dst,src) \
                      (((dst) & ~0x007f0000) | (((u32)(src)<<16) & 0x007f0000))
/*	 Fields POWER_CONTROL	 */
#define POWER_CONTROL1_WIDTH                                                  5
#define POWER_CONTROL1_SHIFT                                                  8
#define POWER_CONTROL1_MASK                                          0x00001f00
#define POWER_CONTROL1_RD(src)                        (((src) & 0x00001f00)>>8)
#define POWER_CONTROL1_WR(src)                   (((u32)(src)<<8) & 0x00001f00)
#define POWER_CONTROL1_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields HOST_CONTROL	 */
#define HOST_CONTROL1_WIDTH                                                   8
#define HOST_CONTROL1_SHIFT                                                   0
#define HOST_CONTROL1_MASK                                           0x000000ff
#define HOST_CONTROL1_RD(src)                            (((src) & 0x000000ff))
#define HOST_CONTROL1_WR(src)                       (((u32)(src)) & 0x000000ff)
#define HOST_CONTROL1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register SRESET_CLOCK_CONTROL_Slot1	*/ 
/*	 Fields SOFTWARE_RESET_CONTROL	 */
#define SOFTWARE_RESET_CONTROL1_WIDTH                                         3
#define SOFTWARE_RESET_CONTROL1_SHIFT                                        24
#define SOFTWARE_RESET_CONTROL1_MASK                                 0x07000000
#define SOFTWARE_RESET_CONTROL1_RD(src)              (((src) & 0x07000000)>>24)
#define SOFTWARE_RESET_CONTROL1_WR(src)         (((u32)(src)<<24) & 0x07000000)
#define SOFTWARE_RESET_CONTROL1_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields TIMEOUT_CONTROL	 */
#define TIMEOUT_CONTROL1_WIDTH                                                4
#define TIMEOUT_CONTROL1_SHIFT                                               16
#define TIMEOUT_CONTROL1_MASK                                        0x000f0000
#define TIMEOUT_CONTROL1_RD(src)                     (((src) & 0x000f0000)>>16)
#define TIMEOUT_CONTROL1_WR(src)                (((u32)(src)<<16) & 0x000f0000)
#define TIMEOUT_CONTROL1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields CLOCK_CONTROL	 */
#define CLOCK_CONTROL1_WIDTH                                                 14
#define CLOCK_CONTROL1_SHIFT                                                  0
#define CLOCK_CONTROL1_MASK                                          0x00003fff
#define CLOCK_CONTROL1_RD(src)                           (((src) & 0x00003fff))
#define CLOCK_CONTROL1_WR(src)                      (((u32)(src)) & 0x00003fff)
#define CLOCK_CONTROL1_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register INT_STATUS_Slot1	*/ 
/*	 Fields ERROR_INTERRUPT_STATUS	 */
#define ERROR_INTERRUPT_STATUS1_WIDTH                                        12
#define ERROR_INTERRUPT_STATUS1_SHIFT                                        16
#define ERROR_INTERRUPT_STATUS1_MASK                                 0x0fff0000
#define ERROR_INTERRUPT_STATUS1_RD(src)              (((src) & 0x0fff0000)>>16)
#define ERROR_INTERRUPT_STATUS1_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields NORMAL_INTERRUPT_STATUS	 */
#define NORMAL_INTERRUPT_STATUS1_WIDTH                                       16
#define NORMAL_INTERRUPT_STATUS1_SHIFT                                        0
#define NORMAL_INTERRUPT_STATUS1_MASK                                0x0000ffff
#define NORMAL_INTERRUPT_STATUS1_RD(src)                 (((src) & 0x0000ffff))
#define NORMAL_INTERRUPT_STATUS1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register INT_STATUS_ENABLE_Slot1	*/ 
/*	 Fields ERROR_INTERRUPT_STATUS_ENABLE	 */
#define ERROR_INTERRUPT_STATUS_ENABLE1_WIDTH                                 12
#define ERROR_INTERRUPT_STATUS_ENABLE1_SHIFT                                 16
#define ERROR_INTERRUPT_STATUS_ENABLE1_MASK                          0x0fff0000
#define ERROR_INTERRUPT_STATUS_ENABLE1_RD(src)       (((src) & 0x0fff0000)>>16)
#define ERROR_INTERRUPT_STATUS_ENABLE1_WR(src)  (((u32)(src)<<16) & 0x0fff0000)
#define ERROR_INTERRUPT_STATUS_ENABLE1_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields NORMAL_INTERRUPT_STATUS_ENABLE	 */
#define NORMAL_INTERRUPT_STATUS_ENABLE1_WIDTH                                16
#define NORMAL_INTERRUPT_STATUS_ENABLE1_SHIFT                                 0
#define NORMAL_INTERRUPT_STATUS_ENABLE1_MASK                         0x0000ffff
#define NORMAL_INTERRUPT_STATUS_ENABLE1_RD(src)          (((src) & 0x0000ffff))
#define NORMAL_INTERRUPT_STATUS_ENABLE1_WR(src)     (((u32)(src)) & 0x0000ffff)
#define NORMAL_INTERRUPT_STATUS_ENABLE1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register INT_SIGNAL_ENABLE_Slot1	*/ 
/*	 Fields ERROR_INTERRUPT_SIGNAL_ENABLE	 */
#define ERROR_INTERRUPT_SIGNAL_ENABLE1_WIDTH                                 12
#define ERROR_INTERRUPT_SIGNAL_ENABLE1_SHIFT                                 16
#define ERROR_INTERRUPT_SIGNAL_ENABLE1_MASK                          0x0fff0000
#define ERROR_INTERRUPT_SIGNAL_ENABLE1_RD(src)       (((src) & 0x0fff0000)>>16)
#define ERROR_INTERRUPT_SIGNAL_ENABLE1_WR(src)  (((u32)(src)<<16) & 0x0fff0000)
#define ERROR_INTERRUPT_SIGNAL_ENABLE1_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields NORMAL_INTERRUPT_SIGNAL_ENABLE	 */
#define NORMAL_INTERRUPT_SIGNAL_ENABLE1_WIDTH                                16
#define NORMAL_INTERRUPT_SIGNAL_ENABLE1_SHIFT                                 0
#define NORMAL_INTERRUPT_SIGNAL_ENABLE1_MASK                         0x0000ffff
#define NORMAL_INTERRUPT_SIGNAL_ENABLE1_RD(src)          (((src) & 0x0000ffff))
#define NORMAL_INTERRUPT_SIGNAL_ENABLE1_WR(src)     (((u32)(src)) & 0x0000ffff)
#define NORMAL_INTERRUPT_SIGNAL_ENABLE1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register AUTO_CMD_ERROR_STATUS_Slot1	*/ 
/*	 Fields HOST_CONTROL_2	 */
#define HOST_CONTROL_21_WIDTH                                                10
#define HOST_CONTROL_21_SHIFT                                                16
#define HOST_CONTROL_21_MASK                                         0x03ff0000
#define HOST_CONTROL_21_RD(src)                      (((src) & 0x03ff0000)>>16)
#define HOST_CONTROL_21_WR(src)                 (((u32)(src)<<16) & 0x03ff0000)
#define HOST_CONTROL_21_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields AUTO_CMD_ERROR_STATUS	 */
#define AUTO_CMD_ERROR_STATUS1_WIDTH                                          6
#define AUTO_CMD_ERROR_STATUS1_SHIFT                                          0
#define AUTO_CMD_ERROR_STATUS1_MASK                                  0x0000003f
#define AUTO_CMD_ERROR_STATUS1_RD(src)                   (((src) & 0x0000003f))
#define AUTO_CMD_ERROR_STATUS1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register CAPABILITIES_0_Slot1	*/ 
/*	 Fields CAPABILITIES_0	 */
#define CAPABILITIES_01_WIDTH                                                30
#define CAPABILITIES_01_SHIFT                                                 0
#define CAPABILITIES_01_MASK                                         0x3fffffff
#define CAPABILITIES_01_RD(src)                          (((src) & 0x3fffffff))
#define CAPABILITIES_01_SET(dst,src) \
                          (((dst) & ~0x3fffffff) | (((u32)(src)) & 0x3fffffff))

/*	Register CAPABILITIES_1_Slot1	*/ 
/*	 Fields CAPABILITIES_1	 */
#define CAPABILITIES_11_F1_WIDTH                                             21
#define CAPABILITIES_11_F1_SHIFT                                              0
#define CAPABILITIES_11_F1_MASK                                      0x001fffff
#define CAPABILITIES_11_F1_RD(src)                       (((src) & 0x001fffff))
#define CAPABILITIES_11_F1_SET(dst,src) \
                          (((dst) & ~0x001fffff) | (((u32)(src)) & 0x001fffff))

/*	Register MAX_CURRENT_CAPABILITIES_0_Slot1	*/ 
/*	 Fields MAX_CURRENT_CAPABILITIES_0	 */
#define MAX_CURRENT_CAPABILITIES_01_WIDTH                                    24
#define MAX_CURRENT_CAPABILITIES_01_SHIFT                                     0
#define MAX_CURRENT_CAPABILITIES_01_MASK                             0x00ffffff
#define MAX_CURRENT_CAPABILITIES_01_RD(src)              (((src) & 0x00ffffff))
#define MAX_CURRENT_CAPABILITIES_01_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register MAX_CURRENT_CAPABILITIES_1_Slot1	*/ 

/*	Register FORCE_EVENT_Slot1	*/ 
/*	 Fields FORCE_EVENT_FOR_ERROR_INT_STATUS	 */
#define FORCE_EVENT_FOR_ERROR_INT_STATUS1_WIDTH                              10
#define FORCE_EVENT_FOR_ERROR_INT_STATUS1_SHIFT                              16
#define FORCE_EVENT_FOR_ERROR_INT_STATUS1_MASK                       0x03ff0000
#define FORCE_EVENT_FOR_ERROR_INT_STATUS1_RD(src)    (((src) & 0x03ff0000)>>16)
#define FORCE_EVENT_FOR_ERROR_INT_STATUS1_WR(src) \
                                                (((u32)(src)<<16) & 0x03ff0000)
#define FORCE_EVENT_FOR_ERROR_INT_STATUS1_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields FORCE_EVENT_FOR_AUTO_CMD_ERROR	 */
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR1_WIDTH                                 6
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR1_SHIFT                                 0
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR1_MASK                         0x0000003f
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR1_RD(src)          (((src) & 0x0000003f))
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR1_WR(src)     (((u32)(src)) & 0x0000003f)
#define FORCE_EVENT_FOR_AUTO_CMD_ERROR1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register ADMA_ERROR_STATUS_Slot1	*/ 
/*	 Fields ADMA_ERROR_STATUS	 */
#define ADMA_ERROR_STATUS1_WIDTH                                              3
#define ADMA_ERROR_STATUS1_SHIFT                                              0
#define ADMA_ERROR_STATUS1_MASK                                      0x00000007
#define ADMA_ERROR_STATUS1_RD(src)                       (((src) & 0x00000007))
#define ADMA_ERROR_STATUS1_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register ADMA_ADDRESS_LOW_Slot1	*/ 
/*	 Fields ADMA_ADDRESS_LOW	 */
#define ADMA_ADDRESS_LOW1_WIDTH                                              32
#define ADMA_ADDRESS_LOW1_SHIFT                                               0
#define ADMA_ADDRESS_LOW1_MASK                                       0xffffffff
#define ADMA_ADDRESS_LOW1_RD(src)                        (((src) & 0xffffffff))
#define ADMA_ADDRESS_LOW1_WR(src)                   (((u32)(src)) & 0xffffffff)
#define ADMA_ADDRESS_LOW1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ADMA_ADDRESS_HIGH_Slot1	*/ 

/*	Register PRESET_VALUE_0_Slot1	*/ 
/*	 Fields PRESET_VALUE_0_2	 */
#define PRESET_VALUE_0_21_WIDTH                                              14
#define PRESET_VALUE_0_21_SHIFT                                              16
#define PRESET_VALUE_0_21_MASK                                       0x3fff0000
#define PRESET_VALUE_0_21_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_0_21_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_0_21_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_0_1	 */
#define PRESET_VALUE_0_11_WIDTH                                              14
#define PRESET_VALUE_0_11_SHIFT                                               0
#define PRESET_VALUE_0_11_MASK                                       0x00003fff
#define PRESET_VALUE_0_11_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_0_11_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_0_11_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register PRESET_VALUE_1_Slot1	*/ 
/*	 Fields PRESET_VALUE_1_2	 */
#define PRESET_VALUE_1_21_F1_WIDTH                                           14
#define PRESET_VALUE_1_21_F1_SHIFT                                           16
#define PRESET_VALUE_1_21_F1_MASK                                    0x3fff0000
#define PRESET_VALUE_1_21_F1_RD(src)                 (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_1_21_F1_WR(src)            (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_1_21_F1_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_1_1	 */
#define PRESET_VALUE_1_11_F1_WIDTH                                           14
#define PRESET_VALUE_1_11_F1_SHIFT                                            0
#define PRESET_VALUE_1_11_F1_MASK                                    0x00003fff
#define PRESET_VALUE_1_11_F1_RD(src)                     (((src) & 0x00003fff))
#define PRESET_VALUE_1_11_F1_WR(src)                (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_1_11_F1_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register PRESET_VALUE_2_Slot1	*/ 
/*	 Fields PRESET_VALUE_2_2	 */
#define PRESET_VALUE_2_21_WIDTH                                              14
#define PRESET_VALUE_2_21_SHIFT                                              16
#define PRESET_VALUE_2_21_MASK                                       0x3fff0000
#define PRESET_VALUE_2_21_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_2_21_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_2_21_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_2_1	 */
#define PRESET_VALUE_2_11_WIDTH                                              14
#define PRESET_VALUE_2_11_SHIFT                                               0
#define PRESET_VALUE_2_11_MASK                                       0x00003fff
#define PRESET_VALUE_2_11_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_2_11_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_2_11_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register PRESET_VALUE_3_Slot1	*/ 
/*	 Fields PRESET_VALUE_3_2	 */
#define PRESET_VALUE_3_21_WIDTH                                              14
#define PRESET_VALUE_3_21_SHIFT                                              16
#define PRESET_VALUE_3_21_MASK                                       0x3fff0000
#define PRESET_VALUE_3_21_RD(src)                    (((src) & 0x3fff0000)>>16)
#define PRESET_VALUE_3_21_WR(src)               (((u32)(src)<<16) & 0x3fff0000)
#define PRESET_VALUE_3_21_SET(dst,src) \
                      (((dst) & ~0x3fff0000) | (((u32)(src)<<16) & 0x3fff0000))
/*	 Fields PRESET_VALUE_3_1	 */
#define PRESET_VALUE_3_11_WIDTH                                              14
#define PRESET_VALUE_3_11_SHIFT                                               0
#define PRESET_VALUE_3_11_MASK                                       0x00003fff
#define PRESET_VALUE_3_11_RD(src)                        (((src) & 0x00003fff))
#define PRESET_VALUE_3_11_WR(src)                   (((u32)(src)) & 0x00003fff)
#define PRESET_VALUE_3_11_SET(dst,src) \
                          (((dst) & ~0x00003fff) | (((u32)(src)) & 0x00003fff))

/*	Register BOOT_TIMEOUT_CONTROL_Slot1	*/ 
/*	 Fields BOOT_TIMEOUT_CONTROL	 */
#define BOOT_TIMEOUT_CONTROL1_WIDTH                                          32
#define BOOT_TIMEOUT_CONTROL1_SHIFT                                           0
#define BOOT_TIMEOUT_CONTROL1_MASK                                   0xffffffff
#define BOOT_TIMEOUT_CONTROL1_RD(src)                    (((src) & 0xffffffff))
#define BOOT_TIMEOUT_CONTROL1_WR(src)               (((u32)(src)) & 0xffffffff)
#define BOOT_TIMEOUT_CONTROL1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SHARED_BUS_CONTROL_Slot1	*/ 
/*	 Fields SHARED_BUS_CONTROL_6	 */
#define SHARED_BUS_CONTROL_61_WIDTH                                           7
#define SHARED_BUS_CONTROL_61_SHIFT                                          24
#define SHARED_BUS_CONTROL_61_MASK                                   0x7f000000
#define SHARED_BUS_CONTROL_61_RD(src)                (((src) & 0x7f000000)>>24)
#define SHARED_BUS_CONTROL_61_WR(src)           (((u32)(src)<<24) & 0x7f000000)
#define SHARED_BUS_CONTROL_61_SET(dst,src) \
                      (((dst) & ~0x7f000000) | (((u32)(src)<<24) & 0x7f000000))
/*	 Fields SHARED_BUS_CONTROL_5	 */
#define SHARED_BUS_CONTROL_51_WIDTH                                           3
#define SHARED_BUS_CONTROL_51_SHIFT                                          20
#define SHARED_BUS_CONTROL_51_MASK                                   0x00700000
#define SHARED_BUS_CONTROL_51_RD(src)                (((src) & 0x00700000)>>20)
#define SHARED_BUS_CONTROL_51_WR(src)           (((u32)(src)<<20) & 0x00700000)
#define SHARED_BUS_CONTROL_51_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields SHARED_BUS_CONTROL_4	 */
#define SHARED_BUS_CONTROL_41_WIDTH                                           3
#define SHARED_BUS_CONTROL_41_SHIFT                                          16
#define SHARED_BUS_CONTROL_41_MASK                                   0x00070000
#define SHARED_BUS_CONTROL_41_RD(src)                (((src) & 0x00070000)>>16)
#define SHARED_BUS_CONTROL_41_WR(src)           (((u32)(src)<<16) & 0x00070000)
#define SHARED_BUS_CONTROL_41_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields SHARED_BUS_CONTROL_3	 */
#define SHARED_BUS_CONTROL_31_WIDTH                                           7
#define SHARED_BUS_CONTROL_31_SHIFT                                           8
#define SHARED_BUS_CONTROL_31_MASK                                   0x00007f00
#define SHARED_BUS_CONTROL_31_RD(src)                 (((src) & 0x00007f00)>>8)
#define SHARED_BUS_CONTROL_31_SET(dst,src) \
                       (((dst) & ~0x00007f00) | (((u32)(src)<<8) & 0x00007f00))
/*	 Fields SHARED_BUS_CONTROL_2	 */
#define SHARED_BUS_CONTROL_21_WIDTH                                           2
#define SHARED_BUS_CONTROL_21_SHIFT                                           4
#define SHARED_BUS_CONTROL_21_MASK                                   0x00000030
#define SHARED_BUS_CONTROL_21_RD(src)                 (((src) & 0x00000030)>>4)
#define SHARED_BUS_CONTROL_21_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields SHARED_BUS_CONTROL_1	 */
#define SHARED_BUS_CONTROL_11_WIDTH                                           3
#define SHARED_BUS_CONTROL_11_SHIFT                                           0
#define SHARED_BUS_CONTROL_11_MASK                                   0x00000007
#define SHARED_BUS_CONTROL_11_RD(src)                    (((src) & 0x00000007))
#define SHARED_BUS_CONTROL_11_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register SPI_INT_SUPPORT_slot1	*/ 
/*	 Fields SPI_INT_SUPPORT	 */
#define SPI_INT_SUPPORT1_WIDTH                                                8
#define SPI_INT_SUPPORT1_SHIFT                                                0
#define SPI_INT_SUPPORT1_MASK                                        0x000000ff
#define SPI_INT_SUPPORT1_RD(src)                         (((src) & 0x000000ff))
#define SPI_INT_SUPPORT1_WR(src)                    (((u32)(src)) & 0x000000ff)
#define SPI_INT_SUPPORT1_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

#endif /* _APMXGENEAHBCCSR_H_ */
