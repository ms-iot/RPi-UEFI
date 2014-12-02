/**
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

#ifndef _APM_IPP_CSR_H__
#define _APM_IPP_CSR_H__

/*	Global Base Address	*/
#define MPA_SCU_CSR_I_BASE_ADDR			0x050000000ULL

/*    Address MPA_SCU_CSR_I  Registers */
#define SCU_BID_ADDR                                                 0x00000000
#define SCU_BID_DEFAULT                                              0x00000067
#define SCU_JTAG0_ADDR                                               0x00000004
#define SCU_JTAG0_DEFAULT                                            0x146501e1
#define SCU_JTAG1_ADDR                                               0x00000008
#define SCU_JTAG1_DEFAULT                                            0x00001000
#define SCU_SRST_ADDR                                                0x0000000c
#define SCU_SRST_DEFAULT                                             0x00000040
#define SCU_CLKEN_ADDR                                               0x00000010
#define SCU_CLKEN_DEFAULT                                            0x0000001f
#define SCU_RSTREQ_ADDR                                              0x00000014
#define SCU_RSTREQ_DEFAULT                                           0x00000000
#define SCU_STAT_ADDR                                                0x00000018
#define SCU_STAT_DEFAULT                                             0x00000000
#define SCU_SOC_EFUSE_ADDR                                           0x0000001c
#define SCU_SOC_EFUSE_DEFAULT                                        0x00000000
#define SCU_PINSTRAP_ADDR                                            0x00000020
#define SCU_PINSTRAP_DEFAULT                                         0x00000000
#define SCU_BOOTSTRAP_ADDR                                           0x0000002c
#define SCU_BOOTSTRAP_DEFAULT                                        0x00000000
#define SCU_PCPBOOTDEV_ADDR                                          0x00000034
#define SCU_PCPBOOTDEV_DEFAULT                                       0x00000000
#define SCU_IOBRCR_ADDR                                              0x00000040
#define SCU_IOBRCR_DEFAULT                                           0x00000003
#define SCU_IOBCCR_ADDR                                              0x00000044
#define SCU_IOBCCR_DEFAULT                                           0x00008820
#define SCU_IOBMCR_ADDR                                              0x00000050
#define SCU_IOBMCR_DEFAULT                                           0x00000004
#define SCU_IOBMSR_ADDR                                              0x00000054
#define SCU_IOBMSR_DEFAULT                                           0x00000000
#define SCU_SOC_PWR_CTL_ADDR                                         0x00000070
#define SCU_SOC_PWR_CTL_DEFAULT                                      0x0000001f
#define SCU_SOC_PWR_STAT_ADDR                                        0x00000074
#define SCU_SOC_PWR_STAT_DEFAULT                                     0x00000001
#define SCU_PWRGOOD_ADDR                                             0x00000078
#define SCU_PWRGOOD_DEFAULT                                          0x00000000
#define SCU_PS_CTL_ADDR                                              0x0000007c
#define SCU_PS_CTL_DEFAULT                                           0x00000000
#define SCU_ECID0_ADDR                                               0x00000080
#define SCU_ECID0_DEFAULT                                            0x00000000
#define SCU_ECID1_ADDR                                               0x00000084
#define SCU_ECID1_DEFAULT                                            0x00000000
#define SCU_ECID2_ADDR                                               0x00000088
#define SCU_ECID2_DEFAULT                                            0x00000000
#define SCU_ECID3_ADDR                                               0x0000008c
#define SCU_ECID3_DEFAULT                                            0x00000000
#define SCU_RAMRWM0_ADDR                                             0x00000090
#define SCU_RAMRWM0_DEFAULT                                          0x11111111
#define SCU_RAMRWM1_ADDR                                             0x00000094
#define SCU_RAMRWM1_DEFAULT                                          0x11111111
#define SCU_RAMRWM2_ADDR                                             0x00000098
#define SCU_RAMRWM2_DEFAULT                                          0x00111111
#define SCU_RAMRWM3_ADDR                                             0x0000009c
#define SCU_RAMRWM3_DEFAULT                                          0x00000011
#define SCU_ROMRM_ADDR                                               0x000000a0
#define SCU_ROMRM_DEFAULT                                            0x00000011
#define SCU_MRDY_ADDR                                                0x000000b0
#define SCU_MRDY_DEFAULT                                             0x00000000
#define SCU_SOC_TS_CTL_ADDR                                          0x000000b4
#define SCU_SOC_TS_CTL_DEFAULT                                       0x0000003f
#define SCU_SOC_SMS_CTL_ADDR                                         0x000000d4
#define SCU_SOC_SMS_CTL_DEFAULT                                      0x00000000
#define SCU_SOC_SMS_RST_ADDR                                         0x000000d8
#define SCU_SOC_SMS_RST_DEFAULT                                      0x00000000
#define SCU_SOC_SMS_RSTRDY_ADDR                                      0x000000dc
#define SCU_SOC_SMS_RSTRDY_DEFAULT                                   0x00000000
#define SCU_PCPPLL_ADDR                                              0x00000100
#define SCU_PCPPLL_DEFAULT                                           0x8001002e
#define SCU_PCPPLLADJ_ADDR                                           0x00000104
#define SCU_PCPPLLADJ_DEFAULT                                        0x003fb000
#define SCU_PCPPLLTEST_ADDR                                          0x00000108
#define SCU_PCPPLLTEST_DEFAULT                                       0x00000000
#define SCU_PCPPLLSTAT_ADDR                                          0x0000010c
#define SCU_PCPPLLSTAT_DEFAULT                                       0x00000000
#define SCU_PCPPLLDLY_ADDR                                           0x00000110
#define SCU_PCPPLLDLY_DEFAULT                                        0x02000200
#define SCU_PCPPLLINIT_ADDR                                          0x00000114
#define SCU_PCPPLLINIT_DEFAULT                                       0x00000000
#define SCU_SOCPLL_ADDR                                              0x00000120
#define SCU_SOCPLL_DEFAULT                                           0x03000050
#define SCU_SOCPLLSTAT_ADDR                                          0x00000128
#define SCU_SOCPLLSTAT_DEFAULT                                       0x00000000
#define SCU_PLLDLY_ADDR                                              0x0000012c
#define SCU_PLLDLY_DEFAULT                                           0x01000100
#define SCU_RAMRWM4_ADDR                                             0x00000130
#define SCU_RAMRWM4_DEFAULT                                          0x11111111
#define SCU_RAMRWM5_ADDR                                             0x00000134
#define SCU_RAMRWM5_DEFAULT                                          0x11111111
#define SCU_SOC_EFUSE1_ADDR                                          0x00000138
#define SCU_SOC_EFUSE1_DEFAULT                                       0x00000000
#define SCU_SOCCOP0DIV_ADDR                                          0x00000140
#define SCU_SOCCOP0DIV_DEFAULT                                       0x00000004
#define SCU_SOCPTPDIV_ADDR                                           0x00000148
#define SCU_SOCPTPDIV_DEFAULT                                        0x00000004
#define SCU_SOCTRACEDIV_ADDR                                         0x0000014c
#define SCU_SOCTRACEDIV_DEFAULT                                      0x00000004
#define SCU_SOCIOBAXIDIV_ADDR                                        0x00000150
#define SCU_SOCIOBAXIDIV_DEFAULT                                     0x00000005
#define SCU_ARMTRCLKINDIV_ADDR                                       0x00000154
#define SCU_ARMTRCLKINDIV_DEFAULT                                    0x00000005
#define SCU_SOCAXIDIV_ADDR                                           0x00000160
#define SCU_SOCAXIDIV_DEFAULT                                        0x00000004
#define SCU_SOCAHBDIV_ADDR                                           0x00000164
#define SCU_SOCAHBDIV_DEFAULT                                        0x00000005
#define SCU_INTAHBDIV_ADDR                                           0x00000168
#define SCU_INTAHBDIV_DEFAULT                                        0x00000004
#define SCU_SOCCRYPTODIV_ADDR                                        0x0000016c
#define SCU_SOCCRYPTODIV_DEFAULT                                     0x00000003
#define SCU_SOCGFCDIV_ADDR                                           0x00000170
#define SCU_SOCGFCDIV_DEFAULT                                        0x00000014
#define SCU_SOCSDIODIV_ADDR                                          0x00000178
#define SCU_SOCSDIODIV_DEFAULT                                       0x00000014
#define SCU_GCCLKDIV_ADDR                                            0x0000017c
#define SCU_GCCLKDIV_DEFAULT                                         0x00000004
#define SCU_RESUME0_ADDR                                             0x00000190
#define SCU_RESUME0_DEFAULT                                          0x00000000
#define SCU_RESUME1_ADDR                                             0x00000194
#define SCU_RESUME1_DEFAULT                                          0x00000000
#define SCU_RESUME2_ADDR                                             0x00000198
#define SCU_RESUME2_DEFAULT                                          0x00000000
#define SCU_RESUME3_ADDR                                             0x0000019c
#define SCU_RESUME3_DEFAULT                                          0x00000000
#define SCU_RESUME4_ADDR                                             0x000001a0
#define SCU_RESUME4_DEFAULT                                          0x00000000
#define SCU_RESUME5_ADDR                                             0x000001a4
#define SCU_RESUME5_DEFAULT                                          0x00000000
#define SCU_RESUME6_ADDR                                             0x000001a8
#define SCU_RESUME6_DEFAULT                                          0x00000000
#define SCU_RESUME7_ADDR                                             0x000001ac
#define SCU_RESUME7_DEFAULT                                          0x00000000
#define SCU_RESUME8_ADDR                                             0x000001b0
#define SCU_RESUME8_DEFAULT                                          0x00000000
#define SCU_RESUME9_ADDR                                             0x000001b4
#define SCU_RESUME9_DEFAULT                                          0x00000000
#define SCU_SPMODE_ADDR                                              0x000001b8
#define SCU_SPMODE_DEFAULT                                           0x00000000
#define SCU_SOC_DBGEN_ADDR                                           0x000001c0
#define SCU_SOC_DBGEN_DEFAULT                                        0x00000001
#define SCU_ETHDIV_ADDR                                              0x00000238
#define SCU_ETHDIV_DEFAULT                                           0x00000008
#define I2C_BOOT_CFG_ADDR                                            0x00000300
#define I2C_BOOT_CFG_DEFAULT                                         0x05000029
#define I2C_BOOT_RST_ADDR                                            0x00000304
#define I2C_BOOT_RST_DEFAULT                                         0x00000000
#define I2C_BOOT_HS_CNT_ADDR                                         0x00000308
#define I2C_BOOT_HS_CNT_DEFAULT                                      0x05000500
#define I2C_BOOT_FS_CNT_ADDR                                         0x0000030c
#define I2C_BOOT_FS_CNT_DEFAULT                                      0x05000500
#define IDRAM_SD_ADDR                                                0x00000340
#define IDRAM_SD_DEFAULT                                             0x00000000

/*	Register SCU_BID	*/ 
/*	 Fields REVNO	 */
#define REGSPEC_REVNO_WIDTH                                                   2
#define REGSPEC_REVNO_SHIFT                                                   9
#define REGSPEC_REVNO_MASK                                           0x00000600
#define REGSPEC_REVNO_RD(src)                         (((src) & 0x00000600)>>9)
#define REGSPEC_REVNO_SET(dst,src) \
                       (((dst) & ~0x00000600) | (((u32)(src)<<9) & 0x00000600))
/*	 Fields BUSID	 */
#define REGSPEC_BUSID_WIDTH                                                   3
#define REGSPEC_BUSID_SHIFT                                                   6
#define REGSPEC_BUSID_MASK                                           0x000001c0
#define REGSPEC_BUSID_RD(src)                         (((src) & 0x000001c0)>>6)
#define REGSPEC_BUSID_SET(dst,src) \
                       (((dst) & ~0x000001c0) | (((u32)(src)<<6) & 0x000001c0))
/*	 Fields DEVICEID	 */
#define REGSPEC_DEVICEID_WIDTH                                                6
#define REGSPEC_DEVICEID_SHIFT                                                0
#define REGSPEC_DEVICEID_MASK                                        0x0000003f
#define REGSPEC_DEVICEID_RD(src)                         (((src) & 0x0000003f))
#define REGSPEC_DEVICEID_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register SCU_JTAG0	*/ 
/*	 Fields Version	 */
#define VERSION0_WIDTH                                                        4
#define VERSION0_SHIFT                                                       28
#define VERSION0_MASK                                                0xf0000000
#define VERSION0_RD(src)                             (((src) & 0xf0000000)>>28)
#define VERSION0_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields Part	 */
#define PART0_WIDTH                                                          16
#define PART0_SHIFT                                                          12
#define PART0_MASK                                                   0x0ffff000
#define PART0_RD(src)                                (((src) & 0x0ffff000)>>12)
#define PART0_SET(dst,src) \
                      (((dst) & ~0x0ffff000) | (((u32)(src)<<12) & 0x0ffff000))
/*	 Fields MID	 */
#define MID0_WIDTH                                                           11
#define MID0_SHIFT                                                            1
#define MID0_MASK                                                    0x00000ffe
#define MID0_RD(src)                                  (((src) & 0x00000ffe)>>1)
#define MID0_SET(dst,src) \
                       (((dst) & ~0x00000ffe) | (((u32)(src)<<1) & 0x00000ffe))
/*	 Fields LSB	 */
#define LSB0_WIDTH                                                            1
#define LSB0_SHIFT                                                            0
#define LSB0_MASK                                                    0x00000001
#define LSB0_RD(src)                                     (((src) & 0x00000001))
#define LSB0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_JTAG1	*/ 
/*	 Fields UserCode	 */
#define USERCODE1_WIDTH                                                      32
#define USERCODE1_SHIFT                                                       0
#define USERCODE1_MASK                                               0xffffffff
#define USERCODE1_RD(src)                                (((src) & 0xffffffff))
#define USERCODE1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_SRST	*/ 
/*	 Fields EXT_RESETN	 */
#define EXT_RESETN_WIDTH                                                      1
#define EXT_RESETN_SHIFT                                                     11
#define EXT_RESETN_MASK                                              0x00000800
#define EXT_RESETN_RD(src)                           (((src) & 0x00000800)>>11)
#define EXT_RESETN_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define EXT_RESETN_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields EXT_SB_RESETN	 */
#define EXT_SB_RESETN_WIDTH                                                   1
#define EXT_SB_RESETN_SHIFT                                                   8
#define EXT_SB_RESETN_MASK                                           0x00000100
#define EXT_SB_RESETN_RD(src)                         (((src) & 0x00000100)>>8)
#define EXT_SB_RESETN_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define EXT_SB_RESETN_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields CORE	 */
#define CORE_WIDTH                                                            1
#define CORE_SHIFT                                                            6
#define CORE_MASK                                                    0x00000040
#define CORE_RD(src)                                  (((src) & 0x00000040)>>6)
#define CORE_WR(src)                             (((u32)(src)<<6) & 0x00000040)
#define CORE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields SBFAXI	 */
#define SBFAXI_WIDTH                                                          1
#define SBFAXI_SHIFT                                                          5
#define SBFAXI_MASK                                                  0x00000020
#define SBFAXI_RD(src)                                (((src) & 0x00000020)>>5)
#define SBFAXI_WR(src)                           (((u32)(src)<<5) & 0x00000020)
#define SBFAXI_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MPA_PKP	 */
#define MPA_PKP_WIDTH                                                         1
#define MPA_PKP_SHIFT                                                         4
#define MPA_PKP_MASK                                                 0x00000010
#define MPA_PKP_RD(src)                               (((src) & 0x00000010)>>4)
#define MPA_PKP_WR(src)                          (((u32)(src)<<4) & 0x00000010)
#define MPA_PKP_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MPA_CRDMA	 */
#define MPA_CRDMA_WIDTH                                                       1
#define MPA_CRDMA_SHIFT                                                       3
#define MPA_CRDMA_MASK                                               0x00000008
#define MPA_CRDMA_RD(src)                             (((src) & 0x00000008)>>3)
#define MPA_CRDMA_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define MPA_CRDMA_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MPA_IIC1	 */
#define MPA_IIC1_WIDTH                                                        1
#define MPA_IIC1_SHIFT                                                        2
#define MPA_IIC1_MASK                                                0x00000004
#define MPA_IIC1_RD(src)                              (((src) & 0x00000004)>>2)
#define MPA_IIC1_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define MPA_IIC1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields RTC	 */
#define REGSPEC_RTC_WIDTH                                                     1
#define REGSPEC_RTC_SHIFT                                                     1
#define REGSPEC_RTC_MASK                                             0x00000002
#define REGSPEC_RTC_RD(src)                           (((src) & 0x00000002)>>1)
#define REGSPEC_RTC_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_RTC_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MPA_APB	 */
#define MPA_APB_WIDTH                                                         1
#define MPA_APB_SHIFT                                                         0
#define MPA_APB_MASK                                                 0x00000001
#define MPA_APB_RD(src)                                  (((src) & 0x00000001))
#define MPA_APB_WR(src)                             (((u32)(src)) & 0x00000001)
#define MPA_APB_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_CLKEN	*/ 
/*	 Fields MPA_PKP	 */
#define MPA_PKP_F1_WIDTH                                                      1
#define MPA_PKP_F1_SHIFT                                                      4
#define MPA_PKP_F1_MASK                                              0x00000010
#define MPA_PKP_F1_RD(src)                            (((src) & 0x00000010)>>4)
#define MPA_PKP_F1_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define MPA_PKP_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MPA_CRDMA	 */
#define MPA_CRDMA_F1_WIDTH                                                    1
#define MPA_CRDMA_F1_SHIFT                                                    3
#define MPA_CRDMA_F1_MASK                                            0x00000008
#define MPA_CRDMA_F1_RD(src)                          (((src) & 0x00000008)>>3)
#define MPA_CRDMA_F1_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define MPA_CRDMA_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MPA_IIC1	 */
#define MPA_IIC1_F1_WIDTH                                                     1
#define MPA_IIC1_F1_SHIFT                                                     2
#define MPA_IIC1_F1_MASK                                             0x00000004
#define MPA_IIC1_F1_RD(src)                           (((src) & 0x00000004)>>2)
#define MPA_IIC1_F1_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define MPA_IIC1_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields RTC	 */
#define REGSPEC_RTC_F1_WIDTH                                                  1
#define REGSPEC_RTC_F1_SHIFT                                                  1
#define REGSPEC_RTC_F1_MASK                                          0x00000002
#define REGSPEC_RTC_F1_RD(src)                        (((src) & 0x00000002)>>1)
#define REGSPEC_RTC_F1_WR(src)                   (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_RTC_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MPA_APB	 */
#define MPA_APB_F1_WIDTH                                                      1
#define MPA_APB_F1_SHIFT                                                      0
#define MPA_APB_F1_MASK                                              0x00000001
#define MPA_APB_F1_RD(src)                               (((src) & 0x00000001))
#define MPA_APB_F1_WR(src)                          (((u32)(src)) & 0x00000001)
#define MPA_APB_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_RSTREQ	*/ 
/*	 Fields WARM_RESET	 */
#define WARM_RESET_WIDTH                                                      1
#define WARM_RESET_SHIFT                                                      1
#define WARM_RESET_MASK                                              0x00000002
#define WARM_RESET_RD(src)                            (((src) & 0x00000002)>>1)
#define WARM_RESET_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define WARM_RESET_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields COLD_RESET	 */
#define COLD_RESET_WIDTH                                                      1
#define COLD_RESET_SHIFT                                                      0
#define COLD_RESET_MASK                                              0x00000001
#define COLD_RESET_RD(src)                               (((src) & 0x00000001))
#define COLD_RESET_WR(src)                          (((u32)(src)) & 0x00000001)
#define COLD_RESET_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_STAT	*/ 
/*	 Fields TS1_READY	 */
#define TS1_READY_WIDTH                                                       1
#define TS1_READY_SHIFT                                                      23
#define TS1_READY_MASK                                               0x00800000
#define TS1_READY_RD(src)                            (((src) & 0x00800000)>>23)
#define TS1_READY_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields TS1_TEMP	 */
#define TS1_TEMP_WIDTH                                                        6
#define TS1_TEMP_SHIFT                                                       16
#define TS1_TEMP_MASK                                                0x003f0000
#define TS1_TEMP_RD(src)                             (((src) & 0x003f0000)>>16)
#define TS1_TEMP_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields TS0_READY	 */
#define TS0_READY_WIDTH                                                       1
#define TS0_READY_SHIFT                                                      15
#define TS0_READY_MASK                                               0x00008000
#define TS0_READY_RD(src)                            (((src) & 0x00008000)>>15)
#define TS0_READY_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields TS0_TEMP	 */
#define TS0_TEMP_WIDTH                                                        6
#define TS0_TEMP_SHIFT                                                        8
#define TS0_TEMP_MASK                                                0x00003f00
#define TS0_TEMP_RD(src)                              (((src) & 0x00003f00)>>8)
#define TS0_TEMP_SET(dst,src) \
                       (((dst) & ~0x00003f00) | (((u32)(src)<<8) & 0x00003f00))
/*	 Fields IIC1_NO_DEV	 */
#define IIC1_NO_DEV_WIDTH                                                     1
#define IIC1_NO_DEV_SHIFT                                                     3
#define IIC1_NO_DEV_MASK                                             0x00000008
#define IIC1_NO_DEV_RD(src)                           (((src) & 0x00000008)>>3)
#define IIC1_NO_DEV_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SMS_FAIL	 */
#define SMS_FAIL_WIDTH                                                        1
#define SMS_FAIL_SHIFT                                                        2
#define SMS_FAIL_MASK                                                0x00000004
#define SMS_FAIL_RD(src)                              (((src) & 0x00000004)>>2)
#define SMS_FAIL_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SMS_DONE	 */
#define SMS_DONE_WIDTH                                                        1
#define SMS_DONE_SHIFT                                                        1
#define SMS_DONE_MASK                                                0x00000002
#define SMS_DONE_RD(src)                              (((src) & 0x00000002)>>1)
#define SMS_DONE_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields EFUSE_RD_SHIFT_DONE	 */
#define EFUSE_RD_SHIFT_DONE_WIDTH                                             1
#define EFUSE_RD_SHIFT_DONE_SHIFT                                             0
#define EFUSE_RD_SHIFT_DONE_MASK                                     0x00000001
#define EFUSE_RD_SHIFT_DONE_RD(src)                      (((src) & 0x00000001))
#define EFUSE_RD_SHIFT_DONE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_SOC_EFUSE	*/ 
/*	 Fields EFUSE31_0	 */
#define EFUSE31_0_WIDTH                                                      32
#define EFUSE31_0_SHIFT                                                       0
#define EFUSE31_0_MASK                                               0xffffffff
#define EFUSE31_0_RD(src)                                (((src) & 0xffffffff))
#define EFUSE31_0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_PINSTRAP	*/ 
/*	 Fields BSC_DIS	 */
#define BSC_DIS_WIDTH                                                         1
#define BSC_DIS_SHIFT                                                        31
#define BSC_DIS_MASK                                                 0x80000000
#define BSC_DIS_RD(src)                              (((src) & 0x80000000)>>31)
#define BSC_DIS_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields IIC_CODE	 */
#define IIC_CODE_WIDTH                                                        1
#define IIC_CODE_SHIFT                                                       26
#define IIC_CODE_MASK                                                0x04000000
#define IIC_CODE_RD(src)                             (((src) & 0x04000000)>>26)
#define IIC_CODE_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields IO_CLKCFG	 */
#define IO_CLKCFG_WIDTH                                                       2
#define IO_CLKCFG_SHIFT                                                      24
#define IO_CLKCFG_MASK                                               0x03000000
#define IO_CLKCFG_RD(src)                            (((src) & 0x03000000)>>24)
#define IO_CLKCFG_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields CPU_CLKCFG	 */
#define CPU_CLKCFG_WIDTH                                                      3
#define CPU_CLKCFG_SHIFT                                                     20
#define CPU_CLKCFG_MASK                                              0x00700000
#define CPU_CLKCFG_RD(src)                           (((src) & 0x00700000)>>20)
#define CPU_CLKCFG_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields MPA_IRAM_SIZE	 */
#define MPA_IRAM_SIZE_WIDTH                                                   2
#define MPA_IRAM_SIZE_SHIFT                                                  16
#define MPA_IRAM_SIZE_MASK                                           0x00030000
#define MPA_IRAM_SIZE_RD(src)                        (((src) & 0x00030000)>>16)
#define MPA_IRAM_SIZE_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields MPA_IROM_1WS	 */
#define MPA_IROM_1WS_WIDTH                                                    1
#define MPA_IROM_1WS_SHIFT                                                   15
#define MPA_IROM_1WS_MASK                                            0x00008000
#define MPA_IROM_1WS_RD(src)                         (((src) & 0x00008000)>>15)
#define MPA_IROM_1WS_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields TEST_TPM_ENABLE	 */
#define TEST_TPM_ENABLE_WIDTH                                                 1
#define TEST_TPM_ENABLE_SHIFT                                                14
#define TEST_TPM_ENABLE_MASK                                         0x00004000
#define TEST_TPM_ENABLE_RD(src)                      (((src) & 0x00004000)>>14)
#define TEST_TPM_ENABLE_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields COP_DOMAIN_DIS	 */
#define COP_DOMAIN_DIS_WIDTH                                                  1
#define COP_DOMAIN_DIS_SHIFT                                                 12
#define COP_DOMAIN_DIS_MASK                                          0x00001000
#define COP_DOMAIN_DIS_RD(src)                       (((src) & 0x00001000)>>12)
#define COP_DOMAIN_DIS_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields XGE_DOMAIN_DIS	 */
#define XGE_DOMAIN_DIS_WIDTH                                                  1
#define XGE_DOMAIN_DIS_SHIFT                                                 11
#define XGE_DOMAIN_DIS_MASK                                          0x00000800
#define XGE_DOMAIN_DIS_RD(src)                       (((src) & 0x00000800)>>11)
#define XGE_DOMAIN_DIS_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields PCI_DOMAIN_DIS	 */
#define PCI_DOMAIN_DIS_WIDTH                                                  1
#define PCI_DOMAIN_DIS_SHIFT                                                 10
#define PCI_DOMAIN_DIS_MASK                                          0x00000400
#define PCI_DOMAIN_DIS_RD(src)                       (((src) & 0x00000400)>>10)
#define PCI_DOMAIN_DIS_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields ROM_TYP	 */
#define ROM_TYP_WIDTH                                                         4
#define ROM_TYP_SHIFT                                                         0
#define ROM_TYP_MASK                                                 0x0000000f
#define ROM_TYP_RD(src)                                  (((src) & 0x0000000f))
#define ROM_TYP_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_BOOTSTRAP	*/ 
/*	 Fields BSC_DIS	 */
#define BSC_DIS_F1_WIDTH                                                      1
#define BSC_DIS_F1_SHIFT                                                     31
#define BSC_DIS_F1_MASK                                              0x80000000
#define BSC_DIS_F1_RD(src)                           (((src) & 0x80000000)>>31)
#define BSC_DIS_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ROM_WIDTH	 */
#define ROM_WIDTH_WIDTH                                                       1
#define ROM_WIDTH_SHIFT                                                      27
#define ROM_WIDTH_MASK                                               0x08000000
#define ROM_WIDTH_RD(src)                            (((src) & 0x08000000)>>27)
#define ROM_WIDTH_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MPA_IRAM_SIZE	 */
#define MPA_IRAM_SIZE_F1_WIDTH                                                2
#define MPA_IRAM_SIZE_F1_SHIFT                                               16
#define MPA_IRAM_SIZE_F1_MASK                                        0x00030000
#define MPA_IRAM_SIZE_F1_RD(src)                     (((src) & 0x00030000)>>16)
#define MPA_IRAM_SIZE_F1_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields MPA_IROM_1WS	 */
#define MPA_IROM_1WS_F1_WIDTH                                                 1
#define MPA_IROM_1WS_F1_SHIFT                                                15
#define MPA_IROM_1WS_F1_MASK                                         0x00008000
#define MPA_IROM_1WS_F1_RD(src)                      (((src) & 0x00008000)>>15)
#define MPA_IROM_1WS_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields BOOT_DEV	 */
#define BOOT_DEV_WIDTH                                                        4
#define BOOT_DEV_SHIFT                                                        0
#define BOOT_DEV_MASK                                                0x0000000f
#define BOOT_DEV_RD(src)                                 (((src) & 0x0000000f))
#define BOOT_DEV_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_PCPBOOTDEV	*/ 
/*	 Fields BOOT_DEV	 */
#define BOOT_DEV_F1_WIDTH                                                     4
#define BOOT_DEV_F1_SHIFT                                                     0
#define BOOT_DEV_F1_MASK                                             0x0000000f
#define BOOT_DEV_F1_RD(src)                              (((src) & 0x0000000f))
#define BOOT_DEV_F1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_IOBRCR	*/ 
/*	 Fields ResetCsw	 */
#define RESETCSW_WIDTH_IPP                                                        1
#define RESETCSW_SHIFT_IPP                                                        1
#define RESETCSW_MASK_IPP                                                0x00000002
#define RESETCSW_RD_IPP(src)                              (((src) & 0x00000002)>>1)
#define RESETCSW_WR_IPP(src)                         (((u32)(src)<<1) & 0x00000002)
#define RESETCSW_SET_IPP(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ResetIob	 */
#define RESETIOB_WIDTH                                                        1
#define RESETIOB_SHIFT                                                        0
#define RESETIOB_MASK                                                0x00000001
#define RESETIOB_RD(src)                                 (((src) & 0x00000001))
#define RESETIOB_WR(src)                            (((u32)(src)) & 0x00000001)
#define RESETIOB_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_IOBCCR	*/ 
/*	 Fields IobClkMacRst	 */
#define IOBCLKMACRST_WIDTH                                                    1
#define IOBCLKMACRST_SHIFT                                                   15
#define IOBCLKMACRST_MASK                                            0x00008000
#define IOBCLKMACRST_RD(src)                         (((src) & 0x00008000)>>15)
#define IOBCLKMACRST_WR(src)                    (((u32)(src)<<15) & 0x00008000)
#define IOBCLKMACRST_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields IobClkMacPd	 */
#define IOBCLKMACPD_WIDTH                                                     1
#define IOBCLKMACPD_SHIFT                                                    14
#define IOBCLKMACPD_MASK                                             0x00004000
#define IOBCLKMACPD_RD(src)                          (((src) & 0x00004000)>>14)
#define IOBCLKMACPD_WR(src)                     (((u32)(src)<<14) & 0x00004000)
#define IOBCLKMACPD_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields IobClkEn	 */
#define IOBCLKEN_WIDTH                                                        1
#define IOBCLKEN_SHIFT                                                       11
#define IOBCLKEN_MASK                                                0x00000800
#define IOBCLKEN_RD(src)                             (((src) & 0x00000800)>>11)
#define IOBCLKEN_WR(src)                        (((u32)(src)<<11) & 0x00000800)
#define IOBCLKEN_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields CmlNsCorrEn	 */
#define CMLNSCORREN_WIDTH                                                     1
#define CMLNSCORREN_SHIFT                                                     5
#define CMLNSCORREN_MASK                                             0x00000020
#define CMLNSCORREN_RD(src)                           (((src) & 0x00000020)>>5)
#define CMLNSCORREN_WR(src)                      (((u32)(src)<<5) & 0x00000020)
#define CMLNSCORREN_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))

/*	Register SCU_IOBMCR	*/ 
/*	 Fields IobMemSd	 */
#define IOBMEMSD_WIDTH                                                        1
#define IOBMEMSD_SHIFT                                                        2
#define IOBMEMSD_MASK                                                0x00000004
#define IOBMEMSD_RD(src)                              (((src) & 0x00000004)>>2)
#define IOBMEMSD_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define IOBMEMSD_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields IobPwrdnDis	 */
#define IOBPWRDNDIS_WIDTH                                                     1
#define IOBPWRDNDIS_SHIFT                                                     1
#define IOBPWRDNDIS_MASK                                             0x00000002
#define IOBPWRDNDIS_RD(src)                           (((src) & 0x00000002)>>1)
#define IOBPWRDNDIS_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define IOBPWRDNDIS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields IobEccBypass	 */
#define IOBECCBYPASS_WIDTH                                                    1
#define IOBECCBYPASS_SHIFT                                                    0
#define IOBECCBYPASS_MASK                                            0x00000001
#define IOBECCBYPASS_RD(src)                             (((src) & 0x00000001))
#define IOBECCBYPASS_WR(src)                        (((u32)(src)) & 0x00000001)
#define IOBECCBYPASS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_IOBMSR	*/ 
/*	 Fields IobMemRdy	 */
#define IOBMEMRDY_WIDTH                                                       1
#define IOBMEMRDY_SHIFT                                                       0
#define IOBMEMRDY_MASK                                               0x00000001
#define IOBMEMRDY_RD(src)                                (((src) & 0x00000001))
#define IOBMEMRDY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_SOC_PWR_CTL	*/ 
/*	 Fields MCU3_Isolate	 */
#define MCU3_ISOLATE_WIDTH                                                    1
#define MCU3_ISOLATE_SHIFT                                                    4
#define MCU3_ISOLATE_MASK                                            0x00000010
#define MCU3_ISOLATE_RD(src)                          (((src) & 0x00000010)>>4)
#define MCU3_ISOLATE_WR(src)                     (((u32)(src)<<4) & 0x00000010)
#define MCU3_ISOLATE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MCU2_Isolate	 */
#define MCU2_ISOLATE_WIDTH                                                    1
#define MCU2_ISOLATE_SHIFT                                                    3
#define MCU2_ISOLATE_MASK                                            0x00000008
#define MCU2_ISOLATE_RD(src)                          (((src) & 0x00000008)>>3)
#define MCU2_ISOLATE_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define MCU2_ISOLATE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MCU1_Isolate	 */
#define MCU1_ISOLATE_WIDTH                                                    1
#define MCU1_ISOLATE_SHIFT                                                    2
#define MCU1_ISOLATE_MASK                                            0x00000004
#define MCU1_ISOLATE_RD(src)                          (((src) & 0x00000004)>>2)
#define MCU1_ISOLATE_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define MCU1_ISOLATE_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MCU0_Isolate	 */
#define MCU0_ISOLATE_WIDTH                                                    1
#define MCU0_ISOLATE_SHIFT                                                    1
#define MCU0_ISOLATE_MASK                                            0x00000002
#define MCU0_ISOLATE_RD(src)                          (((src) & 0x00000002)>>1)
#define MCU0_ISOLATE_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define MCU0_ISOLATE_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SOC_Isolate	 */
#define SOC_ISOLATE_WIDTH                                                     1
#define SOC_ISOLATE_SHIFT                                                     0
#define SOC_ISOLATE_MASK                                             0x00000001
#define SOC_ISOLATE_RD(src)                              (((src) & 0x00000001))
#define SOC_ISOLATE_WR(src)                         (((u32)(src)) & 0x00000001)
#define SOC_ISOLATE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_SOC_PWR_STAT	*/ 
/*	 Fields SOC_PWR_SM_RDY	 */
#define SOC_PWR_SM_RDY_WIDTH                                                  1
#define SOC_PWR_SM_RDY_SHIFT                                                  0
#define SOC_PWR_SM_RDY_MASK                                          0x00000001
#define SOC_PWR_SM_RDY_RD(src)                           (((src) & 0x00000001))
#define SOC_PWR_SM_RDY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_PWRGOOD	*/ 
/*	 Fields PWRGOOD	 */
#define PWRGOOD_WIDTH                                                         6
#define PWRGOOD_SHIFT                                                         0
#define PWRGOOD_MASK                                                 0x0000003f
#define PWRGOOD_RD(src)                                  (((src) & 0x0000003f))
#define PWRGOOD_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register SCU_PS_CTL	*/ 
/*	 Fields VSCALE	 */
#define VSCALE_WIDTH                                                          1
#define VSCALE_SHIFT                                                          6
#define VSCALE_MASK                                                  0x00000040
#define VSCALE_RD(src)                                (((src) & 0x00000040)>>6)
#define VSCALE_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define VSCALE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields PS_CTL	 */
#define PS_CTL_WIDTH                                                          6
#define PS_CTL_SHIFT                                                          0
#define PS_CTL_MASK                                                  0x0000003f
#define PS_CTL_RD(src)                                   (((src) & 0x0000003f))
#define PS_CTL_WR(src)                              (((u32)(src)) & 0x0000003f)
#define PS_CTL_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register SCU_ECID0	*/ 
/*	 Fields SYS_VER_UPPER	 */
#define SYS_VER_UPPER0_WIDTH                                                 16
#define SYS_VER_UPPER0_SHIFT                                                 16
#define SYS_VER_UPPER0_MASK                                          0xffff0000
#define SYS_VER_UPPER0_RD(src)                       (((src) & 0xffff0000)>>16)
#define SYS_VER_UPPER0_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))

/*	Register SCU_ECID1	*/ 
/*	 Fields SYS_VER_LOWER	 */
#define SYS_VER_LOWER1_WIDTH                                                 16
#define SYS_VER_LOWER1_SHIFT                                                 16
#define SYS_VER_LOWER1_MASK                                          0xffff0000
#define SYS_VER_LOWER1_RD(src)                       (((src) & 0xffff0000)>>16)
#define SYS_VER_LOWER1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))

/*	Register SCU_ECID2	*/ 
/*	 Fields ECID2	 */
#define ECID22_WIDTH                                                         32
#define ECID22_SHIFT                                                          0
#define ECID22_MASK                                                  0xffffffff
#define ECID22_RD(src)                                   (((src) & 0xffffffff))
#define ECID22_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_ECID3	*/ 
/*	 Fields ECID3	 */
#define ECID33_WIDTH                                                         32
#define ECID33_SHIFT                                                          0
#define ECID33_MASK                                                  0xffffffff
#define ECID33_RD(src)                                   (((src) & 0xffffffff))
#define ECID33_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RAMRWM0	*/ 
/*	 Fields RWMB_MPA_RD	 */
#define RWMB_MPA_RD0_WIDTH                                                    4
#define RWMB_MPA_RD0_SHIFT                                                   28
#define RWMB_MPA_RD0_MASK                                            0xf0000000
#define RWMB_MPA_RD0_RD(src)                         (((src) & 0xf0000000)>>28)
#define RWMB_MPA_RD0_WR(src)                    (((u32)(src)<<28) & 0xf0000000)
#define RWMB_MPA_RD0_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields RWMB_MPA_RC	 */
#define RWMB_MPA_RC0_WIDTH                                                    4
#define RWMB_MPA_RC0_SHIFT                                                   24
#define RWMB_MPA_RC0_MASK                                            0x0f000000
#define RWMB_MPA_RC0_RD(src)                         (((src) & 0x0f000000)>>24)
#define RWMB_MPA_RC0_WR(src)                    (((u32)(src)<<24) & 0x0f000000)
#define RWMB_MPA_RC0_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields RWMB_MPA_RB	 */
#define RWMB_MPA_RB0_WIDTH                                                    4
#define RWMB_MPA_RB0_SHIFT                                                   20
#define RWMB_MPA_RB0_MASK                                            0x00f00000
#define RWMB_MPA_RB0_RD(src)                         (((src) & 0x00f00000)>>20)
#define RWMB_MPA_RB0_WR(src)                    (((u32)(src)<<20) & 0x00f00000)
#define RWMB_MPA_RB0_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields RWMB_MPA_RA	 */
#define RWMB_MPA_RA0_WIDTH                                                    4
#define RWMB_MPA_RA0_SHIFT                                                   16
#define RWMB_MPA_RA0_MASK                                            0x000f0000
#define RWMB_MPA_RA0_RD(src)                         (((src) & 0x000f0000)>>16)
#define RWMB_MPA_RA0_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define RWMB_MPA_RA0_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields RWMA_MPA_RD	 */
#define RWMA_MPA_RD0_WIDTH                                                    4
#define RWMA_MPA_RD0_SHIFT                                                   12
#define RWMA_MPA_RD0_MASK                                            0x0000f000
#define RWMA_MPA_RD0_RD(src)                         (((src) & 0x0000f000)>>12)
#define RWMA_MPA_RD0_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define RWMA_MPA_RD0_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields RWMA_MPA_RC	 */
#define RWMA_MPA_RC0_WIDTH                                                    4
#define RWMA_MPA_RC0_SHIFT                                                    8
#define RWMA_MPA_RC0_MASK                                            0x00000f00
#define RWMA_MPA_RC0_RD(src)                          (((src) & 0x00000f00)>>8)
#define RWMA_MPA_RC0_WR(src)                     (((u32)(src)<<8) & 0x00000f00)
#define RWMA_MPA_RC0_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields RWMA_MPA_RB	 */
#define RWMA_MPA_RB0_WIDTH                                                    4
#define RWMA_MPA_RB0_SHIFT                                                    4
#define RWMA_MPA_RB0_MASK                                            0x000000f0
#define RWMA_MPA_RB0_RD(src)                          (((src) & 0x000000f0)>>4)
#define RWMA_MPA_RB0_WR(src)                     (((u32)(src)<<4) & 0x000000f0)
#define RWMA_MPA_RB0_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RWMA_MPA_RA	 */
#define RWMA_MPA_RA0_WIDTH                                                    4
#define RWMA_MPA_RA0_SHIFT                                                    0
#define RWMA_MPA_RA0_MASK                                            0x0000000f
#define RWMA_MPA_RA0_RD(src)                             (((src) & 0x0000000f))
#define RWMA_MPA_RA0_WR(src)                        (((u32)(src)) & 0x0000000f)
#define RWMA_MPA_RA0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_RAMRWM1	*/ 
/*	 Fields RWMB_MPA_RD	 */
#define RWMB_MPA_RD1_WIDTH                                                    4
#define RWMB_MPA_RD1_SHIFT                                                   28
#define RWMB_MPA_RD1_MASK                                            0xf0000000
#define RWMB_MPA_RD1_RD(src)                         (((src) & 0xf0000000)>>28)
#define RWMB_MPA_RD1_WR(src)                    (((u32)(src)<<28) & 0xf0000000)
#define RWMB_MPA_RD1_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields RWMB_MPA_RC	 */
#define RWMB_MPA_RC1_WIDTH                                                    4
#define RWMB_MPA_RC1_SHIFT                                                   24
#define RWMB_MPA_RC1_MASK                                            0x0f000000
#define RWMB_MPA_RC1_RD(src)                         (((src) & 0x0f000000)>>24)
#define RWMB_MPA_RC1_WR(src)                    (((u32)(src)<<24) & 0x0f000000)
#define RWMB_MPA_RC1_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields RWMB_MPA_RB	 */
#define RWMB_MPA_RB1_WIDTH                                                    4
#define RWMB_MPA_RB1_SHIFT                                                   20
#define RWMB_MPA_RB1_MASK                                            0x00f00000
#define RWMB_MPA_RB1_RD(src)                         (((src) & 0x00f00000)>>20)
#define RWMB_MPA_RB1_WR(src)                    (((u32)(src)<<20) & 0x00f00000)
#define RWMB_MPA_RB1_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields RWMB_MPA_RA	 */
#define RWMB_MPA_RA1_WIDTH                                                    4
#define RWMB_MPA_RA1_SHIFT                                                   16
#define RWMB_MPA_RA1_MASK                                            0x000f0000
#define RWMB_MPA_RA1_RD(src)                         (((src) & 0x000f0000)>>16)
#define RWMB_MPA_RA1_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define RWMB_MPA_RA1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields RWMA_MPA_RD	 */
#define RWMA_MPA_RD1_WIDTH                                                    4
#define RWMA_MPA_RD1_SHIFT                                                   12
#define RWMA_MPA_RD1_MASK                                            0x0000f000
#define RWMA_MPA_RD1_RD(src)                         (((src) & 0x0000f000)>>12)
#define RWMA_MPA_RD1_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define RWMA_MPA_RD1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields RWMA_MPA_RC	 */
#define RWMA_MPA_RC1_WIDTH                                                    4
#define RWMA_MPA_RC1_SHIFT                                                    8
#define RWMA_MPA_RC1_MASK                                            0x00000f00
#define RWMA_MPA_RC1_RD(src)                          (((src) & 0x00000f00)>>8)
#define RWMA_MPA_RC1_WR(src)                     (((u32)(src)<<8) & 0x00000f00)
#define RWMA_MPA_RC1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields RWMA_MPA_RB	 */
#define RWMA_MPA_RB1_WIDTH                                                    4
#define RWMA_MPA_RB1_SHIFT                                                    4
#define RWMA_MPA_RB1_MASK                                            0x000000f0
#define RWMA_MPA_RB1_RD(src)                          (((src) & 0x000000f0)>>4)
#define RWMA_MPA_RB1_WR(src)                     (((u32)(src)<<4) & 0x000000f0)
#define RWMA_MPA_RB1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RWMA_MPA_RA	 */
#define RWMA_MPA_RA1_WIDTH                                                    4
#define RWMA_MPA_RA1_SHIFT                                                    0
#define RWMA_MPA_RA1_MASK                                            0x0000000f
#define RWMA_MPA_RA1_RD(src)                             (((src) & 0x0000000f))
#define RWMA_MPA_RA1_WR(src)                        (((u32)(src)) & 0x0000000f)
#define RWMA_MPA_RA1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_RAMRWM2	*/ 
/*	 Fields RWMB_PKA_LNME	 */
#define RWMB_PKA_LNME2_WIDTH                                                  4
#define RWMB_PKA_LNME2_SHIFT                                                 20
#define RWMB_PKA_LNME2_MASK                                          0x00f00000
#define RWMB_PKA_LNME2_RD(src)                       (((src) & 0x00f00000)>>20)
#define RWMB_PKA_LNME2_WR(src)                  (((u32)(src)<<20) & 0x00f00000)
#define RWMB_PKA_LNME2_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields RWMB_PKA_R	 */
#define RWMB_PKA_R2_WIDTH                                                     4
#define RWMB_PKA_R2_SHIFT                                                    16
#define RWMB_PKA_R2_MASK                                             0x000f0000
#define RWMB_PKA_R2_RD(src)                          (((src) & 0x000f0000)>>16)
#define RWMB_PKA_R2_WR(src)                     (((u32)(src)<<16) & 0x000f0000)
#define RWMB_PKA_R2_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields RWMB_PKA_PR	 */
#define RWMB_PKA_PR2_WIDTH                                                    4
#define RWMB_PKA_PR2_SHIFT                                                   12
#define RWMB_PKA_PR2_MASK                                            0x0000f000
#define RWMB_PKA_PR2_RD(src)                         (((src) & 0x0000f000)>>12)
#define RWMB_PKA_PR2_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define RWMB_PKA_PR2_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields RWMA_PKA_LNME	 */
#define RWMA_PKA_LNME2_WIDTH                                                  4
#define RWMA_PKA_LNME2_SHIFT                                                  8
#define RWMA_PKA_LNME2_MASK                                          0x00000f00
#define RWMA_PKA_LNME2_RD(src)                        (((src) & 0x00000f00)>>8)
#define RWMA_PKA_LNME2_WR(src)                   (((u32)(src)<<8) & 0x00000f00)
#define RWMA_PKA_LNME2_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields RWMA_PKA_R	 */
#define RWMA_PKA_R2_WIDTH                                                     4
#define RWMA_PKA_R2_SHIFT                                                     4
#define RWMA_PKA_R2_MASK                                             0x000000f0
#define RWMA_PKA_R2_RD(src)                           (((src) & 0x000000f0)>>4)
#define RWMA_PKA_R2_WR(src)                      (((u32)(src)<<4) & 0x000000f0)
#define RWMA_PKA_R2_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RWMA_PKA_PR	 */
#define RWMA_PKA_PR2_WIDTH                                                    4
#define RWMA_PKA_PR2_SHIFT                                                    0
#define RWMA_PKA_PR2_MASK                                            0x0000000f
#define RWMA_PKA_PR2_RD(src)                             (((src) & 0x0000000f))
#define RWMA_PKA_PR2_WR(src)                        (((u32)(src)) & 0x0000000f)
#define RWMA_PKA_PR2_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_RAMRWM3	*/ 
/*	 Fields TEST_DMA	 */
#define TEST_DMA3_WIDTH                                                       4
#define TEST_DMA3_SHIFT                                                       8
#define TEST_DMA3_MASK                                               0x00000f00
#define TEST_DMA3_RD(src)                             (((src) & 0x00000f00)>>8)
#define TEST_DMA3_WR(src)                        (((u32)(src)<<8) & 0x00000f00)
#define TEST_DMA3_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields RWMB_DMA	 */
#define RWMB_DMA3_WIDTH                                                       4
#define RWMB_DMA3_SHIFT                                                       4
#define RWMB_DMA3_MASK                                               0x000000f0
#define RWMB_DMA3_RD(src)                             (((src) & 0x000000f0)>>4)
#define RWMB_DMA3_WR(src)                        (((u32)(src)<<4) & 0x000000f0)
#define RWMB_DMA3_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RWMA_DMA	 */
#define RWMA_DMA3_WIDTH                                                       4
#define RWMA_DMA3_SHIFT                                                       0
#define RWMA_DMA3_MASK                                               0x0000000f
#define RWMA_DMA3_RD(src)                                (((src) & 0x0000000f))
#define RWMA_DMA3_WR(src)                           (((u32)(src)) & 0x0000000f)
#define RWMA_DMA3_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_ROMRM	*/ 
/*	 Fields RM_MPA_ROMB	 */
#define RM_MPA_ROMB_WIDTH                                                     4
#define RM_MPA_ROMB_SHIFT                                                     4
#define RM_MPA_ROMB_MASK                                             0x000000f0
#define RM_MPA_ROMB_RD(src)                           (((src) & 0x000000f0)>>4)
#define RM_MPA_ROMB_WR(src)                      (((u32)(src)<<4) & 0x000000f0)
#define RM_MPA_ROMB_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RM_MPA_ROMA	 */
#define RM_MPA_ROMA_WIDTH                                                     4
#define RM_MPA_ROMA_SHIFT                                                     0
#define RM_MPA_ROMA_MASK                                             0x0000000f
#define RM_MPA_ROMA_RD(src)                              (((src) & 0x0000000f))
#define RM_MPA_ROMA_WR(src)                         (((u32)(src)) & 0x0000000f)
#define RM_MPA_ROMA_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_MRDY	*/ 
/*	 Fields AHBC	 */
#define AHBC_WIDTH                                                            1
#define AHBC_SHIFT                                                           31
#define AHBC_MASK                                                    0x80000000
#define AHBC_RD(src)                                 (((src) & 0x80000000)>>31)
#define AHBC_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SATA0	 */
#define SATA0_WIDTH                                                           1
#define SATA0_SHIFT                                                          30
#define SATA0_MASK                                                   0x40000000
#define SATA0_RD(src)                                (((src) & 0x40000000)>>30)
#define SATA0_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields SATA1	 */
#define SATA1_WIDTH                                                           1
#define SATA1_SHIFT                                                          29
#define SATA1_MASK                                                   0x20000000
#define SATA1_RD(src)                                (((src) & 0x20000000)>>29)
#define SATA1_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields SATA2	 */
#define SATA2_WIDTH                                                           1
#define SATA2_SHIFT                                                          28
#define SATA2_MASK                                                   0x10000000
#define SATA2_RD(src)                                (((src) & 0x10000000)>>28)
#define SATA2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields PCIE0	 */
#define PCIE0_WIDTH                                                           1
#define PCIE0_SHIFT                                                          27
#define PCIE0_MASK                                                   0x08000000
#define PCIE0_RD(src)                                (((src) & 0x08000000)>>27)
#define PCIE0_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields PCIE1	 */
#define PCIE1_WIDTH                                                           1
#define PCIE1_SHIFT                                                          26
#define PCIE1_MASK                                                   0x04000000
#define PCIE1_RD(src)                                (((src) & 0x04000000)>>26)
#define PCIE1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields PCIE2	 */
#define PCIE2_WIDTH                                                           1
#define PCIE2_SHIFT                                                          25
#define PCIE2_MASK                                                   0x02000000
#define PCIE2_RD(src)                                (((src) & 0x02000000)>>25)
#define PCIE2_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields PCIE3	 */
#define PCIE3_WIDTH                                                           1
#define PCIE3_SHIFT                                                          24
#define PCIE3_MASK                                                   0x01000000
#define PCIE3_RD(src)                                (((src) & 0x01000000)>>24)
#define PCIE3_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields PCIE4	 */
#define PCIE4_WIDTH                                                           1
#define PCIE4_SHIFT                                                          23
#define PCIE4_MASK                                                   0x00800000
#define PCIE4_RD(src)                                (((src) & 0x00800000)>>23)
#define PCIE4_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields ENET0	 */
#define ENET0_WIDTH                                                           1
#define ENET0_SHIFT                                                          21
#define ENET0_MASK                                                   0x00200000
#define ENET0_RD(src)                                (((src) & 0x00200000)>>21)
#define ENET0_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields ENET2	 */
#define ENET2_WIDTH                                                           1
#define ENET2_SHIFT                                                          20
#define ENET2_MASK                                                   0x00100000
#define ENET2_RD(src)                                (((src) & 0x00100000)>>20)
#define ENET2_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields ENET4	 */
#define ENET4_WIDTH                                                           1
#define ENET4_SHIFT                                                          19
#define ENET4_MASK                                                   0x00080000
#define ENET4_RD(src)                                (((src) & 0x00080000)>>19)
#define ENET4_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC_EIP96	 */
#define SEC_EIP96_WIDTH                                                       1
#define SEC_EIP96_SHIFT                                                      18
#define SEC_EIP96_MASK                                               0x00040000
#define SEC_EIP96_RD(src)                            (((src) & 0x00040000)>>18)
#define SEC_EIP96_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields USB0	 */
#define USB0_WIDTH                                                            1
#define USB0_SHIFT                                                           16
#define USB0_MASK                                                    0x00010000
#define USB0_RD(src)                                 (((src) & 0x00010000)>>16)
#define USB0_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields USB1	 */
#define USB1_WIDTH                                                            1
#define USB1_SHIFT                                                           15
#define USB1_MASK                                                    0x00008000
#define USB1_RD(src)                                 (((src) & 0x00008000)>>15)
#define USB1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields OCM	 */
#define OCM_WIDTH                                                             1
#define OCM_SHIFT                                                            12
#define OCM_MASK                                                     0x00001000
#define OCM_RD(src)                                  (((src) & 0x00001000)>>12)
#define OCM_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields QMLite	 */
#define QMLITE_WIDTH                                                          1
#define QMLITE_SHIFT                                                         11
#define QMLITE_MASK                                                  0x00000800
#define QMLITE_RD(src)                               (((src) & 0x00000800)>>11)
#define QMLITE_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields QMTM0	 */
#define QMTM0_WIDTH                                                           1
#define QMTM0_SHIFT                                                          10
#define QMTM0_MASK                                                   0x00000400
#define QMTM0_RD(src)                                (((src) & 0x00000400)>>10)
#define QMTM0_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields QMTM1	 */
#define QMTM1_WIDTH                                                           1
#define QMTM1_SHIFT                                                           9
#define QMTM1_MASK                                                   0x00000200
#define QMTM1_RD(src)                                 (((src) & 0x00000200)>>9)
#define QMTM1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields GFC	 */
#define GFC_WIDTH                                                             1
#define GFC_SHIFT                                                             8
#define GFC_MASK                                                     0x00000100
#define GFC_RD(src)                                   (((src) & 0x00000100)>>8)
#define GFC_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields CLE	 */
#define CLE_WIDTH                                                             1
#define CLE_SHIFT                                                             7
#define CLE_MASK                                                     0x00000080
#define CLE_RD(src)                                   (((src) & 0x00000080)>>7)
#define CLE_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields COP	 */
#define COP_WIDTH                                                             1
#define COP_SHIFT                                                             6
#define COP_MASK                                                     0x00000040
#define COP_RD(src)                                   (((src) & 0x00000040)>>6)
#define COP_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields PDMA	 */
#define PDMA_WIDTH                                                            1
#define PDMA_SHIFT                                                            5
#define PDMA_MASK                                                    0x00000020
#define PDMA_RD(src)                                  (((src) & 0x00000020)>>5)
#define PDMA_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields XGE0	 */
#define XGE0_WIDTH                                                            1
#define XGE0_SHIFT                                                            4
#define XGE0_MASK                                                    0x00000010
#define XGE0_RD(src)                                  (((src) & 0x00000010)>>4)
#define XGE0_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields XGE1	 */
#define XGE1_WIDTH                                                            1
#define XGE1_SHIFT                                                            3
#define XGE1_MASK                                                    0x00000008
#define XGE1_RD(src)                                  (((src) & 0x00000008)>>3)
#define XGE1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields CTXMGR	 */
#define CTXMGR_WIDTH                                                          1
#define CTXMGR_SHIFT                                                          2
#define CTXMGR_MASK                                                  0x00000004
#define CTXMGR_RD(src)                                (((src) & 0x00000004)>>2)
#define CTXMGR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SLIMpro	 */
#define SLIMPRO_WIDTH                                                         1
#define SLIMPRO_SHIFT                                                         0
#define SLIMPRO_MASK                                                 0x00000001
#define SLIMPRO_RD(src)                                  (((src) & 0x00000001))
#define SLIMPRO_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_SOC_TS_CTL	*/ 
/*	 Fields START	 */
#define START_WIDTH                                                           1
#define START_SHIFT                                                          31
#define START_MASK                                                   0x80000000
#define START_RD(src)                                (((src) & 0x80000000)>>31)
#define START_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define START_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields TS_SEL	 */
#define TS_SEL_WIDTH                                                          1
#define TS_SEL_SHIFT                                                         30
#define TS_SEL_MASK                                                  0x40000000
#define TS_SEL_RD(src)                               (((src) & 0x40000000)>>30)
#define TS_SEL_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define TS_SEL_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields TS1_PWRDN	 */
#define TS1_PWRDN_WIDTH                                                       1
#define TS1_PWRDN_SHIFT                                                      17
#define TS1_PWRDN_MASK                                               0x00020000
#define TS1_PWRDN_RD(src)                            (((src) & 0x00020000)>>17)
#define TS1_PWRDN_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define TS1_PWRDN_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields TS0_PWRDN	 */
#define TS0_PWRDN_WIDTH                                                       1
#define TS0_PWRDN_SHIFT                                                      16
#define TS0_PWRDN_MASK                                               0x00010000
#define TS0_PWRDN_RD(src)                            (((src) & 0x00010000)>>16)
#define TS0_PWRDN_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define TS0_PWRDN_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields PERIOD	 */
#define PERIOD_WIDTH                                                          2
#define PERIOD_SHIFT                                                          9
#define PERIOD_MASK                                                  0x00000600
#define PERIOD_RD(src)                                (((src) & 0x00000600)>>9)
#define PERIOD_WR(src)                           (((u32)(src)<<9) & 0x00000600)
#define PERIOD_SET(dst,src) \
                       (((dst) & ~0x00000600) | (((u32)(src)<<9) & 0x00000600))
/*	 Fields MODE	 */
#define REGSPEC_MODE_WIDTH                                                    1
#define REGSPEC_MODE_SHIFT                                                    8
#define REGSPEC_MODE_MASK                                            0x00000100
#define REGSPEC_MODE_RD(src)                          (((src) & 0x00000100)>>8)
#define REGSPEC_MODE_WR(src)                     (((u32)(src)<<8) & 0x00000100)
#define REGSPEC_MODE_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields THRESHOLD	 */
#define THRESHOLD_WIDTH                                                       6
#define THRESHOLD_SHIFT                                                       0
#define THRESHOLD_MASK                                               0x0000003f
#define THRESHOLD_RD(src)                                (((src) & 0x0000003f))
#define THRESHOLD_WR(src)                           (((u32)(src)) & 0x0000003f)
#define THRESHOLD_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register SCU_SOC_SMS_CTL	*/ 
/*	 Fields START	 */
#define START_F1_WIDTH                                                        1
#define START_F1_SHIFT                                                       31
#define START_F1_MASK                                                0x80000000
#define START_F1_RD(src)                             (((src) & 0x80000000)>>31)
#define START_F1_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define START_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))

/*	Register SCU_SOC_SMS_RST	*/ 
/*	 Fields SMS_RST_N	 */
#define SMS_RST_N_WIDTH                                                       1
#define SMS_RST_N_SHIFT                                                       0
#define SMS_RST_N_MASK                                               0x00000001
#define SMS_RST_N_RD(src)                                (((src) & 0x00000001))
#define SMS_RST_N_WR(src)                           (((u32)(src)) & 0x00000001)
#define SMS_RST_N_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_SOC_SMS_RSTRDY	*/ 
/*	 Fields SMS_RSTRDY	 */
#define SMS_RSTRDY_WIDTH                                                      1
#define SMS_RSTRDY_SHIFT                                                      0
#define SMS_RSTRDY_MASK                                              0x00000001
#define SMS_RSTRDY_RD(src)                               (((src) & 0x00000001))
#define SMS_RSTRDY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_PCPPLL	*/ 
/*	 Fields PWRDN	 */
#define PWRDN_WIDTH                                                           1
#define PWRDN_SHIFT                                                          31
#define PWRDN_MASK                                                   0x80000000
#define PWRDN_RD(src)                                (((src) & 0x80000000)>>31)
#define PWRDN_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define PWRDN_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields BYPASS	 */
#define BYPASS_WIDTH                                                          1
#define BYPASS_SHIFT                                                         30
#define BYPASS_MASK                                                  0x40000000
#define BYPASS_RD(src)                               (((src) & 0x40000000)>>30)
#define BYPASS_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define BYPASS_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields RESET	 */
#define REGSPEC_RESET_WIDTH                                                   1
#define REGSPEC_RESET_SHIFT                                                  16
#define REGSPEC_RESET_MASK                                           0x00010000
#define REGSPEC_RESET_RD(src)                        (((src) & 0x00010000)>>16)
#define REGSPEC_RESET_WR(src)                   (((u32)(src)<<16) & 0x00010000)
#define REGSPEC_RESET_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields REFCLK_SEL	 */
#define REFCLK_SEL_WIDTH                                                      1
#define REFCLK_SEL_SHIFT                                                     15
#define REFCLK_SEL_MASK                                              0x00008000
#define REFCLK_SEL_RD(src)                           (((src) & 0x00008000)>>15)
#define REFCLK_SEL_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define REFCLK_SEL_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields N_DIV	 */
#define N_DIV_WIDTH                                                           9
#define N_DIV_SHIFT                                                           0
#define N_DIV_MASK                                                   0x000001ff
#define N_DIV_RD(src)                                    (((src) & 0x000001ff))
#define N_DIV_WR(src)                               (((u32)(src)) & 0x000001ff)
#define N_DIV_SET(dst,src) \
                          (((dst) & ~0x000001ff) | (((u32)(src)) & 0x000001ff))

/*	Register SCU_PCPPLLADJ	*/ 
/*	 Fields WRP_PD	 */
#define WRP_PD_WIDTH                                                          1
#define WRP_PD_SHIFT                                                         21
#define WRP_PD_MASK                                                  0x00200000
#define WRP_PD_RD(src)                               (((src) & 0x00200000)>>21)
#define WRP_PD_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define WRP_PD_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields WRP_CLK_BYPASS	 */
#define WRP_CLK_BYPASS_WIDTH                                                  1
#define WRP_CLK_BYPASS_SHIFT                                                 20
#define WRP_CLK_BYPASS_MASK                                          0x00100000
#define WRP_CLK_BYPASS_RD(src)                       (((src) & 0x00100000)>>20)
#define WRP_CLK_BYPASS_WR(src)                  (((u32)(src)<<20) & 0x00100000)
#define WRP_CLK_BYPASS_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields WRP_RESET	 */
#define WRP_RESET_WIDTH                                                       1
#define WRP_RESET_SHIFT                                                      19
#define WRP_RESET_MASK                                               0x00080000
#define WRP_RESET_RD(src)                            (((src) & 0x00080000)>>19)
#define WRP_RESET_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define WRP_RESET_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields WRP_STOP_DLY_SEL	 */
#define WRP_STOP_DLY_SEL_WIDTH                                                3
#define WRP_STOP_DLY_SEL_SHIFT                                               16
#define WRP_STOP_DLY_SEL_MASK                                        0x00070000
#define WRP_STOP_DLY_SEL_RD(src)                     (((src) & 0x00070000)>>16)
#define WRP_STOP_DLY_SEL_WR(src)                (((u32)(src)<<16) & 0x00070000)
#define WRP_STOP_DLY_SEL_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields WRP_CLK_STOP	 */
#define WRP_CLK_STOP_WIDTH                                                    1
#define WRP_CLK_STOP_SHIFT                                                   15
#define WRP_CLK_STOP_MASK                                            0x00008000
#define WRP_CLK_STOP_RD(src)                         (((src) & 0x00008000)>>15)
#define WRP_CLK_STOP_WR(src)                    (((u32)(src)<<15) & 0x00008000)
#define WRP_CLK_STOP_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields WRP_FORCE_FSWING	 */
#define WRP_FORCE_FSWING_WIDTH                                                1
#define WRP_FORCE_FSWING_SHIFT                                               14
#define WRP_FORCE_FSWING_MASK                                        0x00004000
#define WRP_FORCE_FSWING_RD(src)                     (((src) & 0x00004000)>>14)
#define WRP_FORCE_FSWING_WR(src)                (((u32)(src)<<14) & 0x00004000)
#define WRP_FORCE_FSWING_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields WRP_NOISE_REDUCE	 */
#define WRP_NOISE_REDUCE_WIDTH                                                1
#define WRP_NOISE_REDUCE_SHIFT                                               13
#define WRP_NOISE_REDUCE_MASK                                        0x00002000
#define WRP_NOISE_REDUCE_RD(src)                     (((src) & 0x00002000)>>13)
#define WRP_NOISE_REDUCE_WR(src)                (((u32)(src)<<13) & 0x00002000)
#define WRP_NOISE_REDUCE_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields REF100M	 */
#define REF100M_WIDTH                                                         1
#define REF100M_SHIFT                                                        12
#define REF100M_MASK                                                 0x00001000
#define REF100M_RD(src)                              (((src) & 0x00001000)>>12)
#define REF100M_WR(src)                         (((u32)(src)<<12) & 0x00001000)
#define REF100M_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields CP_TRIM	 */
#define CP_TRIM_WIDTH                                                         4
#define CP_TRIM_SHIFT                                                         8
#define CP_TRIM_MASK                                                 0x00000f00
#define CP_TRIM_RD(src)                               (((src) & 0x00000f00)>>8)
#define CP_TRIM_WR(src)                          (((u32)(src)<<8) & 0x00000f00)
#define CP_TRIM_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields BG12_TRIM	 */
#define BG12_TRIM_WIDTH                                                       4
#define BG12_TRIM_SHIFT                                                       4
#define BG12_TRIM_MASK                                               0x000000f0
#define BG12_TRIM_RD(src)                             (((src) & 0x000000f0)>>4)
#define BG12_TRIM_WR(src)                        (((u32)(src)<<4) & 0x000000f0)
#define BG12_TRIM_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields BG09_TRIM	 */
#define BG09_TRIM_WIDTH                                                       4
#define BG09_TRIM_SHIFT                                                       0
#define BG09_TRIM_MASK                                               0x0000000f
#define BG09_TRIM_RD(src)                                (((src) & 0x0000000f))
#define BG09_TRIM_WR(src)                           (((u32)(src)) & 0x0000000f)
#define BG09_TRIM_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_PCPPLLTEST	*/ 
/*	 Fields AB_CTRL	 */
#define AB_CTRL_WIDTH                                                         7
#define AB_CTRL_SHIFT                                                         0
#define AB_CTRL_MASK                                                 0x0000007f
#define AB_CTRL_RD(src)                                  (((src) & 0x0000007f))
#define AB_CTRL_WR(src)                             (((u32)(src)) & 0x0000007f)
#define AB_CTRL_SET(dst,src) \
                          (((dst) & ~0x0000007f) | (((u32)(src)) & 0x0000007f))

/*	Register SCU_PCPPLLSTAT	*/ 
/*	 Fields LOCK	 */
#define REGSPEC_LOCK_WIDTH                                                    1
#define REGSPEC_LOCK_SHIFT                                                    0
#define REGSPEC_LOCK_MASK                                            0x00000001
#define REGSPEC_LOCK_RD(src)                             (((src) & 0x00000001))
#define REGSPEC_LOCK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_PCPPLLDLY	*/ 
/*	 Fields PllStartDelay	 */
#define PLLSTARTDELAY_WIDTH                                                  16
#define PLLSTARTDELAY_SHIFT                                                  16
#define PLLSTARTDELAY_MASK                                           0xffff0000
#define PLLSTARTDELAY_RD(src)                        (((src) & 0xffff0000)>>16)
#define PLLSTARTDELAY_WR(src)                   (((u32)(src)<<16) & 0xffff0000)
#define PLLSTARTDELAY_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields PllLockDelay	 */
#define PLLLOCKDELAY_WIDTH                                                   16
#define PLLLOCKDELAY_SHIFT                                                    0
#define PLLLOCKDELAY_MASK                                            0x0000ffff
#define PLLLOCKDELAY_RD(src)                             (((src) & 0x0000ffff))
#define PLLLOCKDELAY_WR(src)                        (((u32)(src)) & 0x0000ffff)
#define PLLLOCKDELAY_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register SCU_PCPPLLINIT	*/ 
/*	 Fields PllStart	 */
#define PLLSTART_WIDTH                                                        1
#define PLLSTART_SHIFT                                                        1
#define PLLSTART_MASK                                                0x00000002
#define PLLSTART_RD(src)                              (((src) & 0x00000002)>>1)
#define PLLSTART_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define PLLSTART_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields StartDelayMet	 */
#define STARTDELAYMET_WIDTH                                                   1
#define STARTDELAYMET_SHIFT                                                   0
#define STARTDELAYMET_MASK                                           0x00000001
#define STARTDELAYMET_RD(src)                            (((src) & 0x00000001))
#define STARTDELAYMET_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_SOCPLL	*/ 
/*	 Fields BYPASS	 */
#define BYPASS_F1_WIDTH                                                       1
#define BYPASS_F1_SHIFT                                                      30
#define BYPASS_F1_MASK                                               0x40000000
#define BYPASS_F1_RD(src)                            (((src) & 0x40000000)>>30)
#define BYPASS_F1_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define BYPASS_F1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields CLKR	 */
#define CLKR_WIDTH                                                            3
#define CLKR_SHIFT                                                           24
#define CLKR_MASK                                                    0x07000000
#define CLKR_RD(src)                                 (((src) & 0x07000000)>>24)
#define CLKR_WR(src)                            (((u32)(src)<<24) & 0x07000000)
#define CLKR_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields CLKOD	 */
#define CLKOD_WIDTH                                                           2
#define CLKOD_SHIFT                                                          20
#define CLKOD_MASK                                                   0x00300000
#define CLKOD_RD(src)                                (((src) & 0x00300000)>>20)
#define CLKOD_WR(src)                           (((u32)(src)<<20) & 0x00300000)
#define CLKOD_SET(dst,src) \
                      (((dst) & ~0x00300000) | (((u32)(src)<<20) & 0x00300000))
/*	 Fields RESET	 */
#define REGSPEC_RESET_F1_WIDTH                                                1
#define REGSPEC_RESET_F1_SHIFT                                               16
#define REGSPEC_RESET_F1_MASK                                        0x00010000
#define REGSPEC_RESET_F1_RD(src)                     (((src) & 0x00010000)>>16)
#define REGSPEC_RESET_F1_WR(src)                (((u32)(src)<<16) & 0x00010000)
#define REGSPEC_RESET_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields CLKF	 */
#define CLKF_WIDTH                                                            9
#define CLKF_SHIFT                                                            0
#define CLKF_MASK                                                    0x000001ff
#define CLKF_RD(src)                                     (((src) & 0x000001ff))
#define CLKF_WR(src)                                (((u32)(src)) & 0x000001ff)
#define CLKF_SET(dst,src) \
                          (((dst) & ~0x000001ff) | (((u32)(src)) & 0x000001ff))

/*	Register SCU_SOCPLLSTAT	*/ 
/*	 Fields LOCK	 */
#define REGSPEC_LOCK_F1_WIDTH                                                 1
#define REGSPEC_LOCK_F1_SHIFT                                                 0
#define REGSPEC_LOCK_F1_MASK                                         0x00000001
#define REGSPEC_LOCK_F1_RD(src)                          (((src) & 0x00000001))
#define REGSPEC_LOCK_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_PLLDLY	*/ 
/*	 Fields PllStartDelay	 */
#define PLLSTARTDELAY_F1_WIDTH                                               16
#define PLLSTARTDELAY_F1_SHIFT                                               16
#define PLLSTARTDELAY_F1_MASK                                        0xffff0000
#define PLLSTARTDELAY_F1_RD(src)                     (((src) & 0xffff0000)>>16)
#define PLLSTARTDELAY_F1_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields PllLockDelay	 */
#define PLLLOCKDELAY_F1_WIDTH                                                16
#define PLLLOCKDELAY_F1_SHIFT                                                 0
#define PLLLOCKDELAY_F1_MASK                                         0x0000ffff
#define PLLLOCKDELAY_F1_RD(src)                          (((src) & 0x0000ffff))
#define PLLLOCKDELAY_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register SCU_RAMRWM4	*/ 
/*	 Fields RWMB_MPA_RD	 */
#define RWMB_MPA_RD4_WIDTH                                                    4
#define RWMB_MPA_RD4_SHIFT                                                   28
#define RWMB_MPA_RD4_MASK                                            0xf0000000
#define RWMB_MPA_RD4_RD(src)                         (((src) & 0xf0000000)>>28)
#define RWMB_MPA_RD4_WR(src)                    (((u32)(src)<<28) & 0xf0000000)
#define RWMB_MPA_RD4_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields RWMB_MPA_RC	 */
#define RWMB_MPA_RC4_WIDTH                                                    4
#define RWMB_MPA_RC4_SHIFT                                                   24
#define RWMB_MPA_RC4_MASK                                            0x0f000000
#define RWMB_MPA_RC4_RD(src)                         (((src) & 0x0f000000)>>24)
#define RWMB_MPA_RC4_WR(src)                    (((u32)(src)<<24) & 0x0f000000)
#define RWMB_MPA_RC4_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields RWMB_MPA_RB	 */
#define RWMB_MPA_RB4_WIDTH                                                    4
#define RWMB_MPA_RB4_SHIFT                                                   20
#define RWMB_MPA_RB4_MASK                                            0x00f00000
#define RWMB_MPA_RB4_RD(src)                         (((src) & 0x00f00000)>>20)
#define RWMB_MPA_RB4_WR(src)                    (((u32)(src)<<20) & 0x00f00000)
#define RWMB_MPA_RB4_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields RWMB_MPA_RA	 */
#define RWMB_MPA_RA4_WIDTH                                                    4
#define RWMB_MPA_RA4_SHIFT                                                   16
#define RWMB_MPA_RA4_MASK                                            0x000f0000
#define RWMB_MPA_RA4_RD(src)                         (((src) & 0x000f0000)>>16)
#define RWMB_MPA_RA4_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define RWMB_MPA_RA4_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields RWMA_MPA_RD	 */
#define RWMA_MPA_RD4_WIDTH                                                    4
#define RWMA_MPA_RD4_SHIFT                                                   12
#define RWMA_MPA_RD4_MASK                                            0x0000f000
#define RWMA_MPA_RD4_RD(src)                         (((src) & 0x0000f000)>>12)
#define RWMA_MPA_RD4_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define RWMA_MPA_RD4_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields RWMA_MPA_RC	 */
#define RWMA_MPA_RC4_WIDTH                                                    4
#define RWMA_MPA_RC4_SHIFT                                                    8
#define RWMA_MPA_RC4_MASK                                            0x00000f00
#define RWMA_MPA_RC4_RD(src)                          (((src) & 0x00000f00)>>8)
#define RWMA_MPA_RC4_WR(src)                     (((u32)(src)<<8) & 0x00000f00)
#define RWMA_MPA_RC4_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields RWMA_MPA_RB	 */
#define RWMA_MPA_RB4_WIDTH                                                    4
#define RWMA_MPA_RB4_SHIFT                                                    4
#define RWMA_MPA_RB4_MASK                                            0x000000f0
#define RWMA_MPA_RB4_RD(src)                          (((src) & 0x000000f0)>>4)
#define RWMA_MPA_RB4_WR(src)                     (((u32)(src)<<4) & 0x000000f0)
#define RWMA_MPA_RB4_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RWMA_MPA_RA	 */
#define RWMA_MPA_RA4_WIDTH                                                    4
#define RWMA_MPA_RA4_SHIFT                                                    0
#define RWMA_MPA_RA4_MASK                                            0x0000000f
#define RWMA_MPA_RA4_RD(src)                             (((src) & 0x0000000f))
#define RWMA_MPA_RA4_WR(src)                        (((u32)(src)) & 0x0000000f)
#define RWMA_MPA_RA4_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_RAMRWM5	*/ 
/*	 Fields RWMB_MPA_RD	 */
#define RWMB_MPA_RD5_WIDTH                                                    4
#define RWMB_MPA_RD5_SHIFT                                                   28
#define RWMB_MPA_RD5_MASK                                            0xf0000000
#define RWMB_MPA_RD5_RD(src)                         (((src) & 0xf0000000)>>28)
#define RWMB_MPA_RD5_WR(src)                    (((u32)(src)<<28) & 0xf0000000)
#define RWMB_MPA_RD5_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields RWMB_MPA_RC	 */
#define RWMB_MPA_RC5_WIDTH                                                    4
#define RWMB_MPA_RC5_SHIFT                                                   24
#define RWMB_MPA_RC5_MASK                                            0x0f000000
#define RWMB_MPA_RC5_RD(src)                         (((src) & 0x0f000000)>>24)
#define RWMB_MPA_RC5_WR(src)                    (((u32)(src)<<24) & 0x0f000000)
#define RWMB_MPA_RC5_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields RWMB_MPA_RB	 */
#define RWMB_MPA_RB5_WIDTH                                                    4
#define RWMB_MPA_RB5_SHIFT                                                   20
#define RWMB_MPA_RB5_MASK                                            0x00f00000
#define RWMB_MPA_RB5_RD(src)                         (((src) & 0x00f00000)>>20)
#define RWMB_MPA_RB5_WR(src)                    (((u32)(src)<<20) & 0x00f00000)
#define RWMB_MPA_RB5_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields RWMB_MPA_RA	 */
#define RWMB_MPA_RA5_WIDTH                                                    4
#define RWMB_MPA_RA5_SHIFT                                                   16
#define RWMB_MPA_RA5_MASK                                            0x000f0000
#define RWMB_MPA_RA5_RD(src)                         (((src) & 0x000f0000)>>16)
#define RWMB_MPA_RA5_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define RWMB_MPA_RA5_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields RWMA_MPA_RD	 */
#define RWMA_MPA_RD5_WIDTH                                                    4
#define RWMA_MPA_RD5_SHIFT                                                   12
#define RWMA_MPA_RD5_MASK                                            0x0000f000
#define RWMA_MPA_RD5_RD(src)                         (((src) & 0x0000f000)>>12)
#define RWMA_MPA_RD5_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define RWMA_MPA_RD5_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields RWMA_MPA_RC	 */
#define RWMA_MPA_RC5_WIDTH                                                    4
#define RWMA_MPA_RC5_SHIFT                                                    8
#define RWMA_MPA_RC5_MASK                                            0x00000f00
#define RWMA_MPA_RC5_RD(src)                          (((src) & 0x00000f00)>>8)
#define RWMA_MPA_RC5_WR(src)                     (((u32)(src)<<8) & 0x00000f00)
#define RWMA_MPA_RC5_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields RWMA_MPA_RB	 */
#define RWMA_MPA_RB5_WIDTH                                                    4
#define RWMA_MPA_RB5_SHIFT                                                    4
#define RWMA_MPA_RB5_MASK                                            0x000000f0
#define RWMA_MPA_RB5_RD(src)                          (((src) & 0x000000f0)>>4)
#define RWMA_MPA_RB5_WR(src)                     (((u32)(src)<<4) & 0x000000f0)
#define RWMA_MPA_RB5_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields RWMA_MPA_RA	 */
#define RWMA_MPA_RA5_WIDTH                                                    4
#define RWMA_MPA_RA5_SHIFT                                                    0
#define RWMA_MPA_RA5_MASK                                            0x0000000f
#define RWMA_MPA_RA5_RD(src)                             (((src) & 0x0000000f))
#define RWMA_MPA_RA5_WR(src)                        (((u32)(src)) & 0x0000000f)
#define RWMA_MPA_RA5_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register SCU_SOC_EFUSE1	*/ 
/*	 Fields EFUSE63_32	 */
#define EFUSE63_321_WIDTH                                                     3
#define EFUSE63_321_SHIFT                                                    29
#define EFUSE63_321_MASK                                             0xe0000000
#define EFUSE63_321_RD(src)                          (((src) & 0xe0000000)>>29)
#define EFUSE63_321_SET(dst,src) \
                      (((dst) & ~0xe0000000) | (((u32)(src)<<29) & 0xe0000000))

/*	Register SCU_SOCCOP0DIV	*/ 
/*	 Fields COP0_FREQ_SEL	 */
#define COP0_FREQ_SEL_WIDTH                                                   5
#define COP0_FREQ_SEL_SHIFT                                                   0
#define COP0_FREQ_SEL_MASK                                           0x0000001f
#define COP0_FREQ_SEL_RD(src)                            (((src) & 0x0000001f))
#define COP0_FREQ_SEL_WR(src)                       (((u32)(src)) & 0x0000001f)
#define COP0_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCPTPDIV	*/ 
/*	 Fields PTP_FREQ_SEL	 */
#define PTP_FREQ_SEL_WIDTH                                                    5
#define PTP_FREQ_SEL_SHIFT                                                    0
#define PTP_FREQ_SEL_MASK                                            0x0000001f
#define PTP_FREQ_SEL_RD(src)                             (((src) & 0x0000001f))
#define PTP_FREQ_SEL_WR(src)                        (((u32)(src)) & 0x0000001f)
#define PTP_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCTRACEDIV	*/ 
/*	 Fields TRACE_FREQ_SEL	 */
#define TRACE_FREQ_SEL_WIDTH                                                  5
#define TRACE_FREQ_SEL_SHIFT                                                  0
#define TRACE_FREQ_SEL_MASK                                          0x0000001f
#define TRACE_FREQ_SEL_RD(src)                           (((src) & 0x0000001f))
#define TRACE_FREQ_SEL_WR(src)                      (((u32)(src)) & 0x0000001f)
#define TRACE_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCIOBAXIDIV	*/ 
/*	 Fields IOB_AXI_FREQ_SEL	 */
#define IOB_AXI_FREQ_SEL_WIDTH                                                5
#define IOB_AXI_FREQ_SEL_SHIFT                                                0
#define IOB_AXI_FREQ_SEL_MASK                                        0x0000001f
#define IOB_AXI_FREQ_SEL_RD(src)                         (((src) & 0x0000001f))
#define IOB_AXI_FREQ_SEL_WR(src)                    (((u32)(src)) & 0x0000001f)
#define IOB_AXI_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_ARMTRCLKINDIV	*/ 
/*	 Fields TRCLKIN_FREQ_SEL	 */
#define TRCLKIN_FREQ_SEL_WIDTH                                                5
#define TRCLKIN_FREQ_SEL_SHIFT                                                0
#define TRCLKIN_FREQ_SEL_MASK                                        0x0000001f
#define TRCLKIN_FREQ_SEL_RD(src)                         (((src) & 0x0000001f))
#define TRCLKIN_FREQ_SEL_WR(src)                    (((u32)(src)) & 0x0000001f)
#define TRCLKIN_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCAXIDIV	*/ 
/*	 Fields AXI_FREQ_SEL	 */
#define AXI_FREQ_SEL_WIDTH                                                    5
#define AXI_FREQ_SEL_SHIFT                                                    0
#define AXI_FREQ_SEL_MASK                                            0x0000001f
#define AXI_FREQ_SEL_RD(src)                             (((src) & 0x0000001f))
#define AXI_FREQ_SEL_WR(src)                        (((u32)(src)) & 0x0000001f)
#define AXI_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCAHBDIV	*/ 
/*	 Fields AHB_FREQ_SEL	 */
#define AHB_FREQ_SEL_WIDTH                                                    5
#define AHB_FREQ_SEL_SHIFT                                                    0
#define AHB_FREQ_SEL_MASK                                            0x0000001f
#define AHB_FREQ_SEL_RD(src)                             (((src) & 0x0000001f))
#define AHB_FREQ_SEL_WR(src)                        (((u32)(src)) & 0x0000001f)
#define AHB_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_INTAHBDIV	*/ 
/*	 Fields AHB_FREQ_SEL	 */
#define AHB_FREQ_SEL_F1_WIDTH                                                 5
#define AHB_FREQ_SEL_F1_SHIFT                                                 0
#define AHB_FREQ_SEL_F1_MASK                                         0x0000001f
#define AHB_FREQ_SEL_F1_RD(src)                          (((src) & 0x0000001f))
#define AHB_FREQ_SEL_F1_WR(src)                     (((u32)(src)) & 0x0000001f)
#define AHB_FREQ_SEL_F1_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCCRYPTODIV	*/ 
/*	 Fields CRYPTO_FREQ_SEL	 */
#define CRYPTO_FREQ_SEL_WIDTH                                                 5
#define CRYPTO_FREQ_SEL_SHIFT                                                 0
#define CRYPTO_FREQ_SEL_MASK                                         0x0000001f
#define CRYPTO_FREQ_SEL_RD(src)                          (((src) & 0x0000001f))
#define CRYPTO_FREQ_SEL_WR(src)                     (((u32)(src)) & 0x0000001f)
#define CRYPTO_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_SOCGFCDIV	*/ 
/*	 Fields GFC_FREQ_SEL	 */
#define GFC_FREQ_SEL_WIDTH                                                    8
#define GFC_FREQ_SEL_SHIFT                                                    0
#define GFC_FREQ_SEL_MASK                                            0x000000ff
#define GFC_FREQ_SEL_RD(src)                             (((src) & 0x000000ff))
#define GFC_FREQ_SEL_WR(src)                        (((u32)(src)) & 0x000000ff)
#define GFC_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register SCU_SOCSDIODIV	*/ 
/*	 Fields SDIO_FREQ_SEL	 */
#define SDIO_FREQ_SEL_WIDTH                                                   8
#define SDIO_FREQ_SEL_SHIFT                                                   0
#define SDIO_FREQ_SEL_MASK                                           0x000000ff
#define SDIO_FREQ_SEL_RD(src)                            (((src) & 0x000000ff))
#define SDIO_FREQ_SEL_WR(src)                       (((u32)(src)) & 0x000000ff)
#define SDIO_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register SCU_GCCLKDIV	*/ 
/*	 Fields GC_FREQ_SEL	 */
#define GC_FREQ_SEL_WIDTH                                                     5
#define GC_FREQ_SEL_SHIFT                                                     0
#define GC_FREQ_SEL_MASK                                             0x0000001f
#define GC_FREQ_SEL_RD(src)                              (((src) & 0x0000001f))
#define GC_FREQ_SEL_WR(src)                         (((u32)(src)) & 0x0000001f)
#define GC_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SCU_RESUME0	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS0_WIDTH                                                     32
#define RESUME_DS0_SHIFT                                                      0
#define RESUME_DS0_MASK                                              0xffffffff
#define RESUME_DS0_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS0_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME1	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS1_WIDTH                                                     32
#define RESUME_DS1_SHIFT                                                      0
#define RESUME_DS1_MASK                                              0xffffffff
#define RESUME_DS1_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME2	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS2_WIDTH                                                     32
#define RESUME_DS2_SHIFT                                                      0
#define RESUME_DS2_MASK                                              0xffffffff
#define RESUME_DS2_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS2_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME3	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS3_WIDTH                                                     32
#define RESUME_DS3_SHIFT                                                      0
#define RESUME_DS3_MASK                                              0xffffffff
#define RESUME_DS3_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS3_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME4	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS4_WIDTH                                                     32
#define RESUME_DS4_SHIFT                                                      0
#define RESUME_DS4_MASK                                              0xffffffff
#define RESUME_DS4_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS4_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME5	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS5_WIDTH                                                     32
#define RESUME_DS5_SHIFT                                                      0
#define RESUME_DS5_MASK                                              0xffffffff
#define RESUME_DS5_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS5_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME6	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS6_WIDTH                                                     32
#define RESUME_DS6_SHIFT                                                      0
#define RESUME_DS6_MASK                                              0xffffffff
#define RESUME_DS6_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS6_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME7	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS7_WIDTH                                                     32
#define RESUME_DS7_SHIFT                                                      0
#define RESUME_DS7_MASK                                              0xffffffff
#define RESUME_DS7_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS7_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME8	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS8_WIDTH                                                     32
#define RESUME_DS8_SHIFT                                                      0
#define RESUME_DS8_MASK                                              0xffffffff
#define RESUME_DS8_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS8_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_RESUME9	*/ 
/*	 Fields RESUME_DS	 */
#define RESUME_DS9_WIDTH                                                     32
#define RESUME_DS9_SHIFT                                                      0
#define RESUME_DS9_MASK                                              0xffffffff
#define RESUME_DS9_RD(src)                               (((src) & 0xffffffff))
#define RESUME_DS9_WR(src)                          (((u32)(src)) & 0xffffffff)
#define RESUME_DS9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_SPMODE	*/ 
/*	 Fields MODE	 */
#define REGSPEC_MODE_F1_WIDTH                                                32
#define REGSPEC_MODE_F1_SHIFT                                                 0
#define REGSPEC_MODE_F1_MASK                                         0xffffffff
#define REGSPEC_MODE_F1_RD(src)                          (((src) & 0xffffffff))
#define REGSPEC_MODE_F1_WR(src)                     (((u32)(src)) & 0xffffffff)
#define REGSPEC_MODE_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SCU_SOC_DBGEN	*/ 
/*	 Fields PCPPLL_DBGEN	 */
#define PCPPLL_DBGEN_WIDTH                                                    1
#define PCPPLL_DBGEN_SHIFT                                                    1
#define PCPPLL_DBGEN_MASK                                            0x00000002
#define PCPPLL_DBGEN_RD(src)                          (((src) & 0x00000002)>>1)
#define PCPPLL_DBGEN_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define PCPPLL_DBGEN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SOC_DBGEN	 */
#define SOC_DBGEN_WIDTH                                                       1
#define SOC_DBGEN_SHIFT                                                       0
#define SOC_DBGEN_MASK                                               0x00000001
#define SOC_DBGEN_RD(src)                                (((src) & 0x00000001))
#define SOC_DBGEN_WR(src)                           (((u32)(src)) & 0x00000001)
#define SOC_DBGEN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SCU_ETHDIV	*/ 
/*	 Fields ETH_FREQ_SEL	 */
#define ETH_FREQ_SEL_WIDTH                                                    9
#define ETH_FREQ_SEL_SHIFT                                                    0
#define ETH_FREQ_SEL_MASK                                            0x000001ff
#define ETH_FREQ_SEL_RD(src)                             (((src) & 0x000001ff))
#define ETH_FREQ_SEL_WR(src)                        (((u32)(src)) & 0x000001ff)
#define ETH_FREQ_SEL_SET(dst,src) \
                          (((dst) & ~0x000001ff) | (((u32)(src)) & 0x000001ff))

/*	Register I2C_BOOT_Cfg	*/ 
/*	 Fields CFG_ic_ss_hcnt	 */
#define CFG_IC_SS_HCNT_WIDTH                                                 16
#define CFG_IC_SS_HCNT_SHIFT                                                 16
#define CFG_IC_SS_HCNT_MASK                                          0xffff0000
#define CFG_IC_SS_HCNT_RD(src)                       (((src) & 0xffff0000)>>16)
#define CFG_IC_SS_HCNT_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define CFG_IC_SS_HCNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields CFG_hs_sync	 */
#define CFG_HS_SYNC_WIDTH                                                     1
#define CFG_HS_SYNC_SHIFT                                                     7
#define CFG_HS_SYNC_MASK                                             0x00000080
#define CFG_HS_SYNC_RD(src)                           (((src) & 0x00000080)>>7)
#define CFG_HS_SYNC_WR(src)                      (((u32)(src)<<7) & 0x00000080)
#define CFG_HS_SYNC_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields CFG_fs_sync	 */
#define CFG_FS_SYNC_WIDTH                                                     1
#define CFG_FS_SYNC_SHIFT                                                     6
#define CFG_FS_SYNC_MASK                                             0x00000040
#define CFG_FS_SYNC_RD(src)                           (((src) & 0x00000040)>>6)
#define CFG_FS_SYNC_WR(src)                      (((u32)(src)<<6) & 0x00000040)
#define CFG_FS_SYNC_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields CFG_ss_sync	 */
#define CFG_SS_SYNC_WIDTH                                                     1
#define CFG_SS_SYNC_SHIFT                                                     5
#define CFG_SS_SYNC_MASK                                             0x00000020
#define CFG_SS_SYNC_RD(src)                           (((src) & 0x00000020)>>5)
#define CFG_SS_SYNC_WR(src)                      (((u32)(src)<<5) & 0x00000020)
#define CFG_SS_SYNC_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields CFG_10bit_mst_sync	 */
#define CFG_10BIT_MST_SYNC_WIDTH                                              1
#define CFG_10BIT_MST_SYNC_SHIFT                                              4
#define CFG_10BIT_MST_SYNC_MASK                                      0x00000010
#define CFG_10BIT_MST_SYNC_RD(src)                    (((src) & 0x00000010)>>4)
#define CFG_10BIT_MST_SYNC_WR(src)               (((u32)(src)<<4) & 0x00000010)
#define CFG_10BIT_MST_SYNC_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields CFG_rstrt_en_sync	 */
#define CFG_RSTRT_EN_SYNC_WIDTH                                               1
#define CFG_RSTRT_EN_SYNC_SHIFT                                               3
#define CFG_RSTRT_EN_SYNC_MASK                                       0x00000008
#define CFG_RSTRT_EN_SYNC_RD(src)                     (((src) & 0x00000008)>>3)
#define CFG_RSTRT_EN_SYNC_WR(src)                (((u32)(src)<<3) & 0x00000008)
#define CFG_RSTRT_EN_SYNC_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields CFG_ic_hs_maddr	 */
#define CFG_IC_HS_MADDR_WIDTH                                                 3
#define CFG_IC_HS_MADDR_SHIFT                                                 0
#define CFG_IC_HS_MADDR_MASK                                         0x00000007
#define CFG_IC_HS_MADDR_RD(src)                          (((src) & 0x00000007))
#define CFG_IC_HS_MADDR_WR(src)                     (((u32)(src)) & 0x00000007)
#define CFG_IC_HS_MADDR_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register I2C_BOOT_Rst	*/ 
/*	 Fields CFG_fifo_rst	 */
#define CFG_FIFO_RST_WIDTH                                                    1
#define CFG_FIFO_RST_SHIFT                                                    3
#define CFG_FIFO_RST_MASK                                            0x00000008
#define CFG_FIFO_RST_RD(src)                          (((src) & 0x00000008)>>3)
#define CFG_FIFO_RST_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define CFG_FIFO_RST_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields CFG_tx_fifo_rst	 */
#define CFG_TX_FIFO_RST_WIDTH                                                 1
#define CFG_TX_FIFO_RST_SHIFT                                                 2
#define CFG_TX_FIFO_RST_MASK                                         0x00000004
#define CFG_TX_FIFO_RST_RD(src)                       (((src) & 0x00000004)>>2)
#define CFG_TX_FIFO_RST_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define CFG_TX_FIFO_RST_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields CFG_master_srst_sync	 */
#define CFG_MASTER_SRST_SYNC_WIDTH                                            1
#define CFG_MASTER_SRST_SYNC_SHIFT                                            1
#define CFG_MASTER_SRST_SYNC_MASK                                    0x00000002
#define CFG_MASTER_SRST_SYNC_RD(src)                  (((src) & 0x00000002)>>1)
#define CFG_MASTER_SRST_SYNC_WR(src)             (((u32)(src)<<1) & 0x00000002)
#define CFG_MASTER_SRST_SYNC_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields CFG_srst_sync	 */
#define CFG_SRST_SYNC_WIDTH                                                   1
#define CFG_SRST_SYNC_SHIFT                                                   0
#define CFG_SRST_SYNC_MASK                                           0x00000001
#define CFG_SRST_SYNC_RD(src)                            (((src) & 0x00000001))
#define CFG_SRST_SYNC_WR(src)                       (((u32)(src)) & 0x00000001)
#define CFG_SRST_SYNC_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_BOOT_HS_Cnt	*/ 
/*	 Fields CFG_ic_hcnt	 */
#define CFG_IC_HCNT_WIDTH                                                    16
#define CFG_IC_HCNT_SHIFT                                                    16
#define CFG_IC_HCNT_MASK                                             0xffff0000
#define CFG_IC_HCNT_RD(src)                          (((src) & 0xffff0000)>>16)
#define CFG_IC_HCNT_WR(src)                     (((u32)(src)<<16) & 0xffff0000)
#define CFG_IC_HCNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields CFG_ic_lcnt	 */
#define CFG_IC_LCNT_WIDTH                                                    16
#define CFG_IC_LCNT_SHIFT                                                     0
#define CFG_IC_LCNT_MASK                                             0x0000ffff
#define CFG_IC_LCNT_RD(src)                              (((src) & 0x0000ffff))
#define CFG_IC_LCNT_WR(src)                         (((u32)(src)) & 0x0000ffff)
#define CFG_IC_LCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_BOOT_FS_Cnt	*/ 
/*	 Fields CFG_ic_fs_hcnt	 */
#define CFG_IC_FS_HCNT_WIDTH                                                 16
#define CFG_IC_FS_HCNT_SHIFT                                                 16
#define CFG_IC_FS_HCNT_MASK                                          0xffff0000
#define CFG_IC_FS_HCNT_RD(src)                       (((src) & 0xffff0000)>>16)
#define CFG_IC_FS_HCNT_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define CFG_IC_FS_HCNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields CFG_ic_fs_lcnt	 */
#define CFG_IC_FS_LCNT_WIDTH                                                 16
#define CFG_IC_FS_LCNT_SHIFT                                                  0
#define CFG_IC_FS_LCNT_MASK                                          0x0000ffff
#define CFG_IC_FS_LCNT_RD(src)                           (((src) & 0x0000ffff))
#define CFG_IC_FS_LCNT_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define CFG_IC_FS_LCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register IDRAM_SD	*/ 
/*	 Fields SD	 */
#define SD_WIDTH                                                              8
#define SD_SHIFT                                                              4
#define SD_MASK                                                      0x00000ff0
#define SD_RD(src)                                    (((src) & 0x00000ff0)>>4)
#define SD_WR(src)                               (((u32)(src)<<4) & 0x00000ff0)
#define SD_SET(dst,src) \
                       (((dst) & ~0x00000ff0) | (((u32)(src)<<4) & 0x00000ff0))

/*	Global Base Address	*/
#define MPA_REG_CSR_I_BASE_ADDR			0x050001000ULL

/*    Address MPA_REG_CSR_I  Registers */
#define MPA_SPARE_DSF_ADDR                                           0x00000100
#define MPA_SPARE_DSF_DEFAULT                                        0x00000000
#define MPA_SPARE_SERDES_ADDR                                        0x00000104
#define MPA_SPARE_SERDES_DEFAULT                                     0x00000000
#define MPA_SPARE_GLBL_ADDR                                          0x00000108
#define MPA_SPARE_GLBL_DEFAULT                                       0x00000000
#define MPA_SPARE_STAT_ADDR                                          0x0000010c
#define MPA_SPARE_STAT_DEFAULT                                       0x00000000
#define MPA_ARM_INPUT0_ADDR                                          0x00000110
#define MPA_ARM_INPUT0_DEFAULT                                       0xe003d090
#define MPA_ARM_INPUT1_ADDR                                          0x00000114
#define MPA_ARM_INPUT1_DEFAULT                                       0x00000000
#define MPA_ARM_INPUT2_ADDR                                          0x00000118
#define MPA_ARM_INPUT2_DEFAULT                                       0x08000000
#define MPA_ARM_OUTPUT0_ADDR                                         0x0000011c
#define MPA_ARM_OUTPUT0_DEFAULT                                      0x00000000
#define MPA_DWIP_INPUT0_ADDR                                         0x00000120
#define MPA_DWIP_INPUT0_DEFAULT                                      0x00000001
#define MPA_DWIP_OUTPUT0_ADDR                                        0x00000124
#define MPA_DWIP_OUTPUT0_DEFAULT                                     0x00000000
#define MPA_SCRATCH3_ADDR                                            0x00000180
#define MPA_SCRATCH3_DEFAULT                                         0x00000000
#define MPA_SCRATCH4_ADDR                                            0x00000184
#define MPA_SCRATCH4_DEFAULT                                         0x00000000
#define MPA_SCRATCH5_ADDR                                            0x00000188
#define MPA_SCRATCH5_DEFAULT                                         0x00000000
#define MPA_SCRATCH6_ADDR                                            0x0000018c
#define MPA_SCRATCH6_DEFAULT                                         0x00000000
#define MPA_SCRATCH7_ADDR                                            0x00000190
#define MPA_SCRATCH7_DEFAULT                                         0x00000000
#define MPA_SCRATCH8_ADDR                                            0x00000194
#define MPA_SCRATCH8_DEFAULT                                         0x00000000
#define MPA_SCRATCH9_ADDR                                            0x00000198
#define MPA_SCRATCH9_DEFAULT                                         0x00000000
#define MPA_SCRATCH10_ADDR                                           0x0000019c
#define MPA_SCRATCH10_DEFAULT                                        0x00000000
#define MPA_SCRATCH11_ADDR                                           0x000001a0
#define MPA_SCRATCH11_DEFAULT                                        0x00000000
#define MPA_SCRATCH12_ADDR                                           0x000001a4
#define MPA_SCRATCH12_DEFAULT                                        0x00000000
#define MPA_SCRATCH13_ADDR                                           0x000001a8
#define MPA_SCRATCH13_DEFAULT                                        0x00000000
#define MPA_SCRATCH14_ADDR                                           0x000001ac
#define MPA_SCRATCH14_DEFAULT                                        0x00000000
#define MPA_SCRATCH15_ADDR                                           0x000001b0
#define MPA_SCRATCH15_DEFAULT                                        0x00000000
#define MPA_TA_BYPASS_ADDR                                           0x00000200
#define MPA_TA_BYPASS_DEFAULT                                        0x00000001
#define MPA_IRAM_ADDR_ADDR                                           0x00000220
#define MPA_IRAM_ADDR_DEFAULT                                        0x00000000
#define MPA_IRAM_DATA_ADDR                                           0x00000224
#define MPA_IRAM_DATA_DEFAULT                                        0x00000000
#define MPA_IRAM_RDATA_ADDR                                          0x00000228
#define MPA_IRAM_RDATA_DEFAULT                                       0x00000000
#define MPA_ARM_INTSTAT0_ADDR                                        0x00000260
#define MPA_ARM_INTSTAT0_DEFAULT                                     0x00000000
#define MPA_ARM_INTSTAT0MASK_ADDR                                    0x00000264
#define MPA_ARM_INTSTAT1_ADDR                                        0x00000268
#define MPA_ARM_INTSTAT1_DEFAULT                                     0x00000000
#define MPA_ARM_INTSTAT1MASK_ADDR                                    0x0000026c
#define MPA_ARM_INTSTAT2_ADDR                                        0x00000270
#define MPA_ARM_INTSTAT2_DEFAULT                                     0x00000000
#define MPA_ARM_INTSTAT2MASK_ADDR                                    0x00000274
#define MPA_ARM_INTSTAT3_ADDR                                        0x00000278
#define MPA_ARM_INTSTAT3_DEFAULT                                     0x00000000
#define MPA_ARM_INTSTAT3MASK_ADDR                                    0x0000027c
#define MPA_WOL_STAT_ADDR                                            0x00000284
#define MPA_WOL_STAT_DEFAULT                                         0x00000000
#define PKP_DEBUG_ADDR                                               0x00000288
#define PKP_DEBUG_DEFAULT                                            0x00000002
#define MPA_GPIO_INT_LVL_ADDR                                        0x00000290
#define MPA_GPIO_INT_LVL_DEFAULT                                     0x00000000
#define MPA_GPIO_SEL_LO_ADDR                                         0x00000294
#define MPA_GPIO_SEL_LO_DEFAULT                                      0x00000000
#define MPA_GPIO_SEL_HI_ADDR                                         0x00000298
#define MPA_GPIO_SEL_HI_DEFAULT                                      0x00000000
#define MPA_GPIO_OE_ADDR                                             0x0000029c
#define MPA_GPIO_OE_DEFAULT                                          0x00000000
#define MPA_GPIO_OUT_ADDR                                            0x000002a0
#define MPA_GPIO_OUT_DEFAULT                                         0x00000000
#define MPA_GPIO_IN_ADDR                                             0x000002a4
#define MPA_GPIO_IN_DEFAULT                                          0x00000000
#define MPA_GPIO_OD_ADDR                                             0x000002a8
#define MPA_GPIO_OD_DEFAULT                                          0x00000000
#define MPA_ATMR0_ADDR                                               0x000002b0
#define MPA_ATMR0_DEFAULT                                            0x00000000
#define MPA_ATMR1_ADDR                                               0x000002b4
#define MPA_ATMR1_DEFAULT                                            0x00000000
#define MPA_ATMR2_ADDR                                               0x000002b8
#define MPA_ATMR2_DEFAULT                                            0x00000000
#define MPA_IIDMA_CTL_ADDR                                           0x000002e0
#define MPA_IIDMA_CTL_DEFAULT                                        0x00000000
#define MPA_IIDMA_CNT_ADDR                                           0x000002e4
#define MPA_IIDMA_CNT_DEFAULT                                        0x00001000
#define MPA_IIDMA_IRAMADDR_ADDR                                      0x000002e8
#define MPA_IIDMA_IRAMADDR_DEFAULT                                   0x00000000
#define MPA_IIDMA_IICADDR_ADDR                                       0x000002ec
#define MPA_IIDMA_IICADDR_DEFAULT                                    0x00000000
#define MPA_IIDMA_STAT_ADDR                                          0x000002f0
#define MPA_IIDMA_STAT_DEFAULT                                       0x00000000
#define MPA_DIAG_ADDR                                                0x00000320
#define MPA_DIAG_DEFAULT                                             0x00000000
#define MPA_LED_ADDR                                                 0x00000324
#define MPA_LED_DEFAULT                                              0x00000000
#define MPA_INTDBG0_ADDR                                             0x00000328
#define MPA_INTDBG0_DEFAULT                                          0x00000000
#define MPA_INTDBG1_ADDR                                             0x0000032c
#define MPA_INTDBG1_DEFAULT                                          0x00000000
#define MPA_ERR_ADDR0_ADDR                                           0x00000330
#define MPA_ERR_ADDR0_DEFAULT                                        0x00000000
#define MPA_ERR_ADDR1_ADDR                                           0x00000334
#define MPA_ERR_ADDR1_DEFAULT                                        0x00000000
#define MPA_ERR_ADDR                                                 0x00000340
#define MPA_ERR_DEFAULT                                              0x00000000
#define MPA_ERRMASK_ADDR                                             0x00000344
#define MPA_ERR_INT_MASK_ADDR                                        0x00000348
#define MPA_ERR_INT_MASK_DEFAULT                                     0x0fffffff
#define MPA_QMI_INTSTAT_ADDR                                         0x00000350
#define MPA_QMI_INTSTAT_DEFAULT                                      0x00000000
#define MPA_QMI_INTSTATMASK_ADDR                                     0x00000354
#define MPA_SAB_INTSTAT_ADDR                                         0x00000358
#define MPA_SAB_INTSTAT_DEFAULT                                      0x00000000
#define MPA_SAB_INTSTATMASK_ADDR                                     0x0000035c
#define MPA_SCRATCH_ADDR                                             0x00000360
#define MPA_SCRATCH_DEFAULT                                          0x00000000
#define MPA_SCRATCH1_ADDR                                            0x00000364
#define MPA_SCRATCH1_DEFAULT                                         0x00000000
#define MPA_SCRATCH2_ADDR                                            0x00000368
#define MPA_SCRATCH2_DEFAULT                                         0x00000000
#define MPA_SLP_TMR_ADDR                                             0x0000036c
#define MPA_SLP_TMR_DEFAULT                                          0x00000100
#define MPA_GPIO_DS_IOCTL0_ADDR                                      0x00000370
#define MPA_GPIO_DS_IOCTL0_DEFAULT                                   0x000ffff0
#define MPA_GPIO_DS_IOCTL1_ADDR                                      0x00000374
#define MPA_GPIO_DS_IOCTL1_DEFAULT                                   0x000ffff0
#define MPA_GPIO_DS_IOCTL2_ADDR                                      0x00000378
#define MPA_GPIO_DS_IOCTL2_DEFAULT                                   0x000ffff0
#define MPA_GPIO_DS_IOCTL3_ADDR                                      0x0000037c
#define MPA_GPIO_DS_IOCTL3_DEFAULT                                   0x000ffff0
#define MPA_GPIO_DS_IOCTL4_ADDR                                      0x00000380
#define MPA_GPIO_DS_IOCTL4_DEFAULT                                   0x000ffff0
#define MPA_GPIO_DS_IOCTL5_ADDR                                      0x00000384
#define MPA_GPIO_DS_IOCTL5_DEFAULT                                   0x000ffff0
#define MPA_ENET4_PWRGD_IOCTL_ADDR                                   0x00000388
#define MPA_ENET4_PWRGD_IOCTL_DEFAULT                                0x1e1e1e1e
#define MPA_IIC_SPI_IOCTL_ADDR                                       0x0000038c
#define MPA_IIC_SPI_IOCTL_DEFAULT                                    0x1e1e0000
#define MPA_SDIO_EBUS_IOCTL_ADDR                                     0x00000390
#define MPA_SDIO_EBUS_IOCTL_DEFAULT                                  0x00001e00
#define MPA_UART_SPARE_IOCTL_ADDR                                    0x00000394
#define MPA_UART_SPARE_IOCTL_DEFAULT                                 0x00003e1e
#define MPA_MDIO_IOCTL_ADDR                                          0x00000398
#define MPA_MDIO_IOCTL_DEFAULT                                       0x00001e1e
#define MPA_MISC1_IOCTL0_ADDR                                        0x0000039c
#define MPA_MISC1_IOCTL0_DEFAULT                                     0x1e1e1e1e
#define MPA_CH0_PWM_CTL_ADDR                                         0x00000400
#define MPA_CH0_PWM_CTL_DEFAULT                                      0x00000000
#define MPA_CH0_PWM_PERIOD_ADDR                                      0x00000404
#define MPA_CH0_PWM_PERIOD_DEFAULT                                   0x00000000
#define MPA_CH0_PWM_HIGH_ADDR                                        0x00000408
#define MPA_CH0_PWM_HIGH_DEFAULT                                     0x00000000
#define MPA_CH1_PWM_CTL_ADDR                                         0x00000410
#define MPA_CH1_PWM_CTL_DEFAULT                                      0x00000000
#define MPA_CH1_PWM_PERIOD_ADDR                                      0x00000414
#define MPA_CH1_PWM_PERIOD_DEFAULT                                   0x00000000
#define MPA_CH1_PWM_HIGH_ADDR                                        0x00000418
#define MPA_CH1_PWM_HIGH_DEFAULT                                     0x00000000
#define MPA_TMM_WRERR_STAT0_ADDR                                     0x00000420
#define MPA_TMM_WRERR_STAT0_DEFAULT                                  0x00000000
#define MPA_TMM_WRERR_STAT1_ADDR                                     0x00000424
#define MPA_TMM_WRERR_STAT1_DEFAULT                                  0x00000000
#define MPA_TMM_RDERR_STAT0_ADDR                                     0x00000428
#define MPA_TMM_RDERR_STAT0_DEFAULT                                  0x00000000
#define MPA_TMM_RDERR_STAT1_ADDR                                     0x0000042c
#define MPA_TMM_RDERR_STAT1_DEFAULT                                  0x00000000
#define MPA_TMM_CSR_ERR_STAT_ADDR                                    0x00000430
#define MPA_TMM_CSR_ERR_STAT_DEFAULT                                 0x00000000
#define MPA_CH2_PWM_CTL_ADDR                                         0x00000434
#define MPA_CH2_PWM_CTL_DEFAULT                                      0x00000000
#define MPA_CH2_PWM_PERIOD_ADDR                                      0x00000438
#define MPA_CH2_PWM_PERIOD_DEFAULT                                   0x00000000
#define MPA_CH2_PWM_HIGH_ADDR                                        0x0000043c
#define MPA_CH2_PWM_HIGH_DEFAULT                                     0x00000000
#define MPA_CH3_PWM_CTL_ADDR                                         0x00000440
#define MPA_CH3_PWM_CTL_DEFAULT                                      0x00000000
#define MPA_CH3_PWM_PERIOD_ADDR                                      0x00000444
#define MPA_CH3_PWM_PERIOD_DEFAULT                                   0x00000000
#define MPA_CH3_PWM_HIGH_ADDR                                        0x00000448
#define MPA_CH3_PWM_HIGH_DEFAULT                                     0x00000000
#define MPA_CLKMON_SEL_ADDR                                          0x00000450
#define MPA_CLKMON_SEL_DEFAULT                                       0x00000000
#define PKA_DEBUG0_ADDR                                              0x00000500
#define PKA_DEBUG0_DEFAULT                                           0x00000000
#define PKA_DEBUG1_ADDR                                              0x00000504
#define PKA_DEBUG1_DEFAULT                                           0x00000000
#define PKA_DEBUG2_ADDR                                              0x00000508
#define PKA_DEBUG2_DEFAULT                                           0x00000000

/*	Register MPA_SPARE_DSF	*/ 
/*	 Fields DSF	 */
#define DSF_WIDTH                                                            32
#define DSF_SHIFT                                                             0
#define DSF_MASK                                                     0xffffffff
#define DSF_RD(src)                                      (((src) & 0xffffffff))
#define DSF_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define DSF_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SPARE_SERDES	*/ 
/*	 Fields SERDES	 */
#define SERDES_WIDTH                                                         32
#define SERDES_SHIFT                                                          0
#define SERDES_MASK                                                  0xffffffff
#define SERDES_RD(src)                                   (((src) & 0xffffffff))
#define SERDES_WR(src)                              (((u32)(src)) & 0xffffffff)
#define SERDES_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SPARE_GLBL	*/ 
/*	 Fields GLBL	 */
#define GLBL_WIDTH                                                           32
#define GLBL_SHIFT                                                            0
#define GLBL_MASK                                                    0xffffffff
#define GLBL_RD(src)                                     (((src) & 0xffffffff))
#define GLBL_WR(src)                                (((u32)(src)) & 0xffffffff)
#define GLBL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SPARE_STAT	*/ 
/*	 Fields STATUS	 */
#define STATUS_WIDTH                                                         32
#define STATUS_SHIFT                                                          0
#define STATUS_MASK                                                  0xffffffff
#define STATUS_RD(src)                                   (((src) & 0xffffffff))
#define STATUS_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ARM_INPUT0	*/ 
/*	 Fields PWRUP	 */
#define PWRUP0_WIDTH                                                          1
#define PWRUP0_SHIFT                                                         31
#define PWRUP0_MASK                                                  0x80000000
#define PWRUP0_RD(src)                               (((src) & 0x80000000)>>31)
#define PWRUP0_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define PWRUP0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ISOLATEn	 */
#define ISOLATEN0_WIDTH                                                       1
#define ISOLATEN0_SHIFT                                                      30
#define ISOLATEN0_MASK                                               0x40000000
#define ISOLATEN0_RD(src)                            (((src) & 0x40000000)>>30)
#define ISOLATEN0_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define ISOLATEN0_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields RETAINn	 */
#define RETAINN0_WIDTH                                                        1
#define RETAINN0_SHIFT                                                       29
#define RETAINN0_MASK                                                0x20000000
#define RETAINN0_RD(src)                             (((src) & 0x20000000)>>29)
#define RETAINN0_WR(src)                        (((u32)(src)<<29) & 0x20000000)
#define RETAINN0_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields STCALIB	 */
#define STCALIB0_WIDTH                                                       26
#define STCALIB0_SHIFT                                                        0
#define STCALIB0_MASK                                                0x03ffffff
#define STCALIB0_RD(src)                                 (((src) & 0x03ffffff))
#define STCALIB0_WR(src)                            (((u32)(src)) & 0x03ffffff)
#define STCALIB0_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register MPA_ARM_INPUT1	*/ 
/*	 Fields AUXFAULT	 */
#define AUXFAULT1_WIDTH                                                      32
#define AUXFAULT1_SHIFT                                                       0
#define AUXFAULT1_MASK                                               0xffffffff
#define AUXFAULT1_RD(src)                                (((src) & 0xffffffff))
#define AUXFAULT1_WR(src)                           (((u32)(src)) & 0xffffffff)
#define AUXFAULT1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ARM_INPUT2	*/ 
/*	 Fields BIGEND	 */
#define BIGEND2_WIDTH                                                         1
#define BIGEND2_SHIFT                                                        31
#define BIGEND2_MASK                                                 0x80000000
#define BIGEND2_RD(src)                              (((src) & 0x80000000)>>31)
#define BIGEND2_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define BIGEND2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields EDBGRQ	 */
#define EDBGRQ2_WIDTH                                                         1
#define EDBGRQ2_SHIFT                                                        30
#define EDBGRQ2_MASK                                                 0x40000000
#define EDBGRQ2_RD(src)                              (((src) & 0x40000000)>>30)
#define EDBGRQ2_WR(src)                         (((u32)(src)<<30) & 0x40000000)
#define EDBGRQ2_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields DBGRESTART	 */
#define DBGRESTART2_WIDTH                                                     1
#define DBGRESTART2_SHIFT                                                    29
#define DBGRESTART2_MASK                                             0x20000000
#define DBGRESTART2_RD(src)                          (((src) & 0x20000000)>>29)
#define DBGRESTART2_WR(src)                     (((u32)(src)<<29) & 0x20000000)
#define DBGRESTART2_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields RXEV	 */
#define RXEV2_WIDTH                                                           1
#define RXEV2_SHIFT                                                          28
#define RXEV2_MASK                                                   0x10000000
#define RXEV2_RD(src)                                (((src) & 0x10000000)>>28)
#define RXEV2_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define RXEV2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SLEEPHOLDREQn	 */
#define SLEEPHOLDREQN2_WIDTH                                                  1
#define SLEEPHOLDREQN2_SHIFT                                                 27
#define SLEEPHOLDREQN2_MASK                                          0x08000000
#define SLEEPHOLDREQN2_RD(src)                       (((src) & 0x08000000)>>27)
#define SLEEPHOLDREQN2_WR(src)                  (((u32)(src)<<27) & 0x08000000)
#define SLEEPHOLDREQN2_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields WICENREQ	 */
#define WICENREQ2_WIDTH                                                       1
#define WICENREQ2_SHIFT                                                      26
#define WICENREQ2_MASK                                               0x04000000
#define WICENREQ2_RD(src)                            (((src) & 0x04000000)>>26)
#define WICENREQ2_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define WICENREQ2_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields FIXMASTERTYPE	 */
#define FIXMASTERTYPE2_WIDTH                                                  1
#define FIXMASTERTYPE2_SHIFT                                                 25
#define FIXMASTERTYPE2_MASK                                          0x02000000
#define FIXMASTERTYPE2_RD(src)                       (((src) & 0x02000000)>>25)
#define FIXMASTERTYPE2_WR(src)                  (((u32)(src)<<25) & 0x02000000)
#define FIXMASTERTYPE2_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))

/*	Register MPA_ARM_OUTPUT0	*/ 
/*	 Fields SWDOEN	 */
#define SWDOEN0_WIDTH                                                         1
#define SWDOEN0_SHIFT                                                        31
#define SWDOEN0_MASK                                                 0x80000000
#define SWDOEN0_RD(src)                              (((src) & 0x80000000)>>31)
#define SWDOEN0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SWDO	 */
#define SWDO0_WIDTH                                                           1
#define SWDO0_SHIFT                                                          30
#define SWDO0_MASK                                                   0x40000000
#define SWDO0_RD(src)                                (((src) & 0x40000000)>>30)
#define SWDO0_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields SWV	 */
#define SWV0_WIDTH                                                            1
#define SWV0_SHIFT                                                           29
#define SWV0_MASK                                                    0x20000000
#define SWV0_RD(src)                                 (((src) & 0x20000000)>>29)
#define SWV0_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields JTAGNSW	 */
#define JTAGNSW0_WIDTH                                                        1
#define JTAGNSW0_SHIFT                                                       28
#define JTAGNSW0_MASK                                                0x10000000
#define JTAGNSW0_RD(src)                             (((src) & 0x10000000)>>28)
#define JTAGNSW0_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields WICENACK	 */
#define WICENACK0_WIDTH                                                       1
#define WICENACK0_SHIFT                                                      27
#define WICENACK0_MASK                                               0x08000000
#define WICENACK0_RD(src)                            (((src) & 0x08000000)>>27)
#define WICENACK0_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields WAKEUP	 */
#define WAKEUP0_WIDTH                                                         1
#define WAKEUP0_SHIFT                                                        26
#define WAKEUP0_MASK                                                 0x04000000
#define WAKEUP0_RD(src)                              (((src) & 0x04000000)>>26)
#define WAKEUP0_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields PWRUPREADY	 */
#define PWRUPREADY0_WIDTH                                                     1
#define PWRUPREADY0_SHIFT                                                    25
#define PWRUPREADY0_MASK                                             0x02000000
#define PWRUPREADY0_RD(src)                          (((src) & 0x02000000)>>25)
#define PWRUPREADY0_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))

/*	Register MPA_DWIP_INPUT0	*/ 
/*	 Fields eh2h_shsel_reg	 */
#define EH2H_SHSEL_REG0_WIDTH                                                 1
#define EH2H_SHSEL_REG0_SHIFT                                                31
#define EH2H_SHSEL_REG0_MASK                                         0x80000000
#define EH2H_SHSEL_REG0_RD(src)                      (((src) & 0x80000000)>>31)
#define EH2H_SHSEL_REG0_WR(src)                 (((u32)(src)<<31) & 0x80000000)
#define EH2H_SHSEL_REG0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields eh2h_shsel_p	 */
#define EH2H_SHSEL_P0_WIDTH                                                   1
#define EH2H_SHSEL_P0_SHIFT                                                  30
#define EH2H_SHSEL_P0_MASK                                           0x40000000
#define EH2H_SHSEL_P0_RD(src)                        (((src) & 0x40000000)>>30)
#define EH2H_SHSEL_P0_WR(src)                   (((u32)(src)<<30) & 0x40000000)
#define EH2H_SHSEL_P0_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields x2h_awlock	 */
#define X2H_AWLOCK0_WIDTH                                                     2
#define X2H_AWLOCK0_SHIFT                                                    26
#define X2H_AWLOCK0_MASK                                             0x0c000000
#define X2H_AWLOCK0_RD(src)                          (((src) & 0x0c000000)>>26)
#define X2H_AWLOCK0_WR(src)                     (((u32)(src)<<26) & 0x0c000000)
#define X2H_AWLOCK0_SET(dst,src) \
                      (((dst) & ~0x0c000000) | (((u32)(src)<<26) & 0x0c000000))
/*	 Fields x2h_arlock	 */
#define X2H_ARLOCK0_WIDTH                                                     2
#define X2H_ARLOCK0_SHIFT                                                    24
#define X2H_ARLOCK0_MASK                                             0x03000000
#define X2H_ARLOCK0_RD(src)                          (((src) & 0x03000000)>>24)
#define X2H_ARLOCK0_WR(src)                     (((u32)(src)<<24) & 0x03000000)
#define X2H_ARLOCK0_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields x2h_awprot	 */
#define X2H_AWPROT0_WIDTH                                                     3
#define X2H_AWPROT0_SHIFT                                                    20
#define X2H_AWPROT0_MASK                                             0x00700000
#define X2H_AWPROT0_RD(src)                          (((src) & 0x00700000)>>20)
#define X2H_AWPROT0_WR(src)                     (((u32)(src)<<20) & 0x00700000)
#define X2H_AWPROT0_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields x2h_arprot	 */
#define X2H_ARPROT0_WIDTH                                                     3
#define X2H_ARPROT0_SHIFT                                                    16
#define X2H_ARPROT0_MASK                                             0x00070000
#define X2H_ARPROT0_RD(src)                          (((src) & 0x00070000)>>16)
#define X2H_ARPROT0_WR(src)                     (((u32)(src)<<16) & 0x00070000)
#define X2H_ARPROT0_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields x2h_awcache	 */
#define X2H_AWCACHE0_WIDTH                                                    4
#define X2H_AWCACHE0_SHIFT                                                   12
#define X2H_AWCACHE0_MASK                                            0x0000f000
#define X2H_AWCACHE0_RD(src)                         (((src) & 0x0000f000)>>12)
#define X2H_AWCACHE0_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define X2H_AWCACHE0_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields x2h_arcache	 */
#define X2H_ARCACHE0_WIDTH                                                    4
#define X2H_ARCACHE0_SHIFT                                                    8
#define X2H_ARCACHE0_MASK                                            0x00000f00
#define X2H_ARCACHE0_RD(src)                          (((src) & 0x00000f00)>>8)
#define X2H_ARCACHE0_WR(src)                     (((u32)(src)<<8) & 0x00000f00)
#define X2H_ARCACHE0_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields apb_pclk_en	 */
#define APB_PCLK_EN0_WIDTH                                                    1
#define APB_PCLK_EN0_SHIFT                                                    0
#define APB_PCLK_EN0_MASK                                            0x00000001
#define APB_PCLK_EN0_RD(src)                             (((src) & 0x00000001))
#define APB_PCLK_EN0_WR(src)                        (((u32)(src)) & 0x00000001)
#define APB_PCLK_EN0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_DWIP_OUTPUT0	*/ 
/*	 Fields debug_s_gen	 */
#define DEBUG_S_GEN0_WIDTH                                                    1
#define DEBUG_S_GEN0_SHIFT                                                   31
#define DEBUG_S_GEN0_MASK                                            0x80000000
#define DEBUG_S_GEN0_RD(src)                         (((src) & 0x80000000)>>31)
#define DEBUG_S_GEN0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields debug_p_gen	 */
#define DEBUG_P_GEN0_WIDTH                                                    1
#define DEBUG_P_GEN0_SHIFT                                                   30
#define DEBUG_P_GEN0_MASK                                            0x40000000
#define DEBUG_P_GEN0_RD(src)                         (((src) & 0x40000000)>>30)
#define DEBUG_P_GEN0_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields debug_data	 */
#define DEBUG_DATA0_WIDTH                                                     1
#define DEBUG_DATA0_SHIFT                                                    29
#define DEBUG_DATA0_MASK                                             0x20000000
#define DEBUG_DATA0_RD(src)                          (((src) & 0x20000000)>>29)
#define DEBUG_DATA0_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields debug_addr	 */
#define DEBUG_ADDR0_WIDTH                                                     1
#define DEBUG_ADDR0_SHIFT                                                    28
#define DEBUG_ADDR0_MASK                                             0x10000000
#define DEBUG_ADDR0_RD(src)                          (((src) & 0x10000000)>>28)
#define DEBUG_ADDR0_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields debug_rd	 */
#define DEBUG_RD0_WIDTH                                                       1
#define DEBUG_RD0_SHIFT                                                      27
#define DEBUG_RD0_MASK                                               0x08000000
#define DEBUG_RD0_RD(src)                            (((src) & 0x08000000)>>27)
#define DEBUG_RD0_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields debug_wr	 */
#define DEBUG_WR0_WIDTH                                                       1
#define DEBUG_WR0_SHIFT                                                      26
#define DEBUG_WR0_MASK                                               0x04000000
#define DEBUG_WR0_RD(src)                            (((src) & 0x04000000)>>26)
#define DEBUG_WR0_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields debug_hs	 */
#define DEBUG_HS0_WIDTH                                                       1
#define DEBUG_HS0_SHIFT                                                      25
#define DEBUG_HS0_MASK                                               0x02000000
#define DEBUG_HS0_RD(src)                            (((src) & 0x02000000)>>25)
#define DEBUG_HS0_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields debug_master_act	 */
#define DEBUG_MASTER_ACT0_WIDTH                                               1
#define DEBUG_MASTER_ACT0_SHIFT                                              24
#define DEBUG_MASTER_ACT0_MASK                                       0x01000000
#define DEBUG_MASTER_ACT0_RD(src)                    (((src) & 0x01000000)>>24)
#define DEBUG_MASTER_ACT0_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields debug_slave_act	 */
#define DEBUG_SLAVE_ACT0_WIDTH                                                1
#define DEBUG_SLAVE_ACT0_SHIFT                                               23
#define DEBUG_SLAVE_ACT0_MASK                                        0x00800000
#define DEBUG_SLAVE_ACT0_RD(src)                     (((src) & 0x00800000)>>23)
#define DEBUG_SLAVE_ACT0_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields debug_addr_10bit	 */
#define DEBUG_ADDR_10BIT0_WIDTH                                               1
#define DEBUG_ADDR_10BIT0_SHIFT                                              22
#define DEBUG_ADDR_10BIT0_MASK                                       0x00400000
#define DEBUG_ADDR_10BIT0_RD(src)                    (((src) & 0x00400000)>>22)
#define DEBUG_ADDR_10BIT0_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields ic_en	 */
#define IC_EN0_WIDTH                                                          1
#define IC_EN0_SHIFT                                                         21
#define IC_EN0_MASK                                                  0x00200000
#define IC_EN0_RD(src)                               (((src) & 0x00200000)>>21)
#define IC_EN0_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields debug_mst_cstate	 */
#define DEBUG_MST_CSTATE0_WIDTH                                               5
#define DEBUG_MST_CSTATE0_SHIFT                                               8
#define DEBUG_MST_CSTATE0_MASK                                       0x00001f00
#define DEBUG_MST_CSTATE0_RD(src)                     (((src) & 0x00001f00)>>8)
#define DEBUG_MST_CSTATE0_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields debug_slv_cstate	 */
#define DEBUG_SLV_CSTATE0_WIDTH                                               4
#define DEBUG_SLV_CSTATE0_SHIFT                                               0
#define DEBUG_SLV_CSTATE0_MASK                                       0x0000000f
#define DEBUG_SLV_CSTATE0_RD(src)                        (((src) & 0x0000000f))
#define DEBUG_SLV_CSTATE0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_SCRATCH3	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH3_WIDTH                                                       32
#define SCRATCH3_SHIFT                                                        0
#define SCRATCH3_MASK                                                0xffffffff
#define SCRATCH3_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH3_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH4	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH4_WIDTH                                                       32
#define SCRATCH4_SHIFT                                                        0
#define SCRATCH4_MASK                                                0xffffffff
#define SCRATCH4_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH4_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH5	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH5_WIDTH                                                       32
#define SCRATCH5_SHIFT                                                        0
#define SCRATCH5_MASK                                                0xffffffff
#define SCRATCH5_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH5_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH6	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH6_WIDTH                                                       32
#define SCRATCH6_SHIFT                                                        0
#define SCRATCH6_MASK                                                0xffffffff
#define SCRATCH6_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH6_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH7	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH7_WIDTH                                                       32
#define SCRATCH7_SHIFT                                                        0
#define SCRATCH7_MASK                                                0xffffffff
#define SCRATCH7_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH7_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH8	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH8_WIDTH                                                       32
#define SCRATCH8_SHIFT                                                        0
#define SCRATCH8_MASK                                                0xffffffff
#define SCRATCH8_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH8_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH9	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH9_WIDTH                                                       32
#define SCRATCH9_SHIFT                                                        0
#define SCRATCH9_MASK                                                0xffffffff
#define SCRATCH9_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH9_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH10	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH0_WIDTH                                                       32
#define SCRATCH0_SHIFT                                                        0
#define SCRATCH0_MASK                                                0xffffffff
#define SCRATCH0_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH0_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH11	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH1_WIDTH                                                       32
#define SCRATCH1_SHIFT                                                        0
#define SCRATCH1_MASK                                                0xffffffff
#define SCRATCH1_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH12	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH2_WIDTH                                                       32
#define SCRATCH2_SHIFT                                                        0
#define SCRATCH2_MASK                                                0xffffffff
#define SCRATCH2_RD(src)                                 (((src) & 0xffffffff))
#define SCRATCH2_WR(src)                            (((u32)(src)) & 0xffffffff)
#define SCRATCH2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH13	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH3_F1_WIDTH                                                    32
#define SCRATCH3_F1_SHIFT                                                     0
#define SCRATCH3_F1_MASK                                             0xffffffff
#define SCRATCH3_F1_RD(src)                              (((src) & 0xffffffff))
#define SCRATCH3_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define SCRATCH3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH14	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH4_F1_WIDTH                                                    32
#define SCRATCH4_F1_SHIFT                                                     0
#define SCRATCH4_F1_MASK                                             0xffffffff
#define SCRATCH4_F1_RD(src)                              (((src) & 0xffffffff))
#define SCRATCH4_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define SCRATCH4_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH15	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH5_F1_WIDTH                                                    32
#define SCRATCH5_F1_SHIFT                                                     0
#define SCRATCH5_F1_MASK                                             0xffffffff
#define SCRATCH5_F1_RD(src)                              (((src) & 0xffffffff))
#define SCRATCH5_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define SCRATCH5_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_TA_BYPASS	*/ 
/*	 Fields BYPASS	 */
#define BYPASS_F4_WIDTH                                                       1
#define BYPASS_F4_SHIFT                                                       0
#define BYPASS_F4_MASK                                               0x00000001
#define BYPASS_F4_RD(src)                                (((src) & 0x00000001))
#define BYPASS_F4_WR(src)                           (((u32)(src)) & 0x00000001)
#define BYPASS_F4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_IRAM_ADDR	*/ 
/*	 Fields IRAM_ADDR	 */
#define IRAM_ADDR_WIDTH                                                      16
#define IRAM_ADDR_SHIFT                                                       0
#define IRAM_ADDR_MASK                                               0x0000ffff
#define IRAM_ADDR_RD(src)                                (((src) & 0x0000ffff))
#define IRAM_ADDR_WR(src)                           (((u32)(src)) & 0x0000ffff)
#define IRAM_ADDR_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_IRAM_DATA	*/ 
/*	 Fields IRAM_DATA	 */
#define IRAM_DATA_WIDTH                                                      32
#define IRAM_DATA_SHIFT                                                       0
#define IRAM_DATA_MASK                                               0xffffffff
#define IRAM_DATA_RD(src)                                (((src) & 0xffffffff))
#define IRAM_DATA_WR(src)                           (((u32)(src)) & 0xffffffff)
#define IRAM_DATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_IRAM_RDATA	*/ 
/*	 Fields IRAM_RDATA	 */
#define IRAM_RDATA_WIDTH                                                     32
#define IRAM_RDATA_SHIFT                                                      0
#define IRAM_RDATA_MASK                                              0xffffffff
#define IRAM_RDATA_RD(src)                               (((src) & 0xffffffff))
#define IRAM_RDATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ARM_INTSTAT0	*/ 
/*	 Fields DBOUT9_ACK	 */
#define DBOUT9_ACK0_WIDTH                                                     1
#define DBOUT9_ACK0_SHIFT                                                    25
#define DBOUT9_ACK0_MASK                                             0x02000000
#define DBOUT9_ACK0_RD(src)                          (((src) & 0x02000000)>>25)
#define DBOUT9_ACK0_WR(src)                     (((u32)(src)<<25) & 0x02000000)
#define DBOUT9_ACK0_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields DBOUT8_ACK	 */
#define DBOUT8_ACK0_WIDTH                                                     1
#define DBOUT8_ACK0_SHIFT                                                    24
#define DBOUT8_ACK0_MASK                                             0x01000000
#define DBOUT8_ACK0_RD(src)                          (((src) & 0x01000000)>>24)
#define DBOUT8_ACK0_WR(src)                     (((u32)(src)<<24) & 0x01000000)
#define DBOUT8_ACK0_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields DBOUT7_ACK	 */
#define DBOUT7_ACK0_WIDTH                                                     1
#define DBOUT7_ACK0_SHIFT                                                    23
#define DBOUT7_ACK0_MASK                                             0x00800000
#define DBOUT7_ACK0_RD(src)                          (((src) & 0x00800000)>>23)
#define DBOUT7_ACK0_WR(src)                     (((u32)(src)<<23) & 0x00800000)
#define DBOUT7_ACK0_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields DBOUT6_ACK	 */
#define DBOUT6_ACK0_WIDTH                                                     1
#define DBOUT6_ACK0_SHIFT                                                    22
#define DBOUT6_ACK0_MASK                                             0x00400000
#define DBOUT6_ACK0_RD(src)                          (((src) & 0x00400000)>>22)
#define DBOUT6_ACK0_WR(src)                     (((u32)(src)<<22) & 0x00400000)
#define DBOUT6_ACK0_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields DBOUT5_ACK	 */
#define DBOUT5_ACK0_WIDTH                                                     1
#define DBOUT5_ACK0_SHIFT                                                    21
#define DBOUT5_ACK0_MASK                                             0x00200000
#define DBOUT5_ACK0_RD(src)                          (((src) & 0x00200000)>>21)
#define DBOUT5_ACK0_WR(src)                     (((u32)(src)<<21) & 0x00200000)
#define DBOUT5_ACK0_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields DBOUT4_ACK	 */
#define DBOUT4_ACK0_WIDTH                                                     1
#define DBOUT4_ACK0_SHIFT                                                    20
#define DBOUT4_ACK0_MASK                                             0x00100000
#define DBOUT4_ACK0_RD(src)                          (((src) & 0x00100000)>>20)
#define DBOUT4_ACK0_WR(src)                     (((u32)(src)<<20) & 0x00100000)
#define DBOUT4_ACK0_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields DBOUT3_ACK	 */
#define DBOUT3_ACK0_WIDTH                                                     1
#define DBOUT3_ACK0_SHIFT                                                    19
#define DBOUT3_ACK0_MASK                                             0x00080000
#define DBOUT3_ACK0_RD(src)                          (((src) & 0x00080000)>>19)
#define DBOUT3_ACK0_WR(src)                     (((u32)(src)<<19) & 0x00080000)
#define DBOUT3_ACK0_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields DBOUT2_ACK	 */
#define DBOUT2_ACK0_WIDTH                                                     1
#define DBOUT2_ACK0_SHIFT                                                    18
#define DBOUT2_ACK0_MASK                                             0x00040000
#define DBOUT2_ACK0_RD(src)                          (((src) & 0x00040000)>>18)
#define DBOUT2_ACK0_WR(src)                     (((u32)(src)<<18) & 0x00040000)
#define DBOUT2_ACK0_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields DBOUT1_ACK	 */
#define DBOUT1_ACK0_WIDTH                                                     1
#define DBOUT1_ACK0_SHIFT                                                    17
#define DBOUT1_ACK0_MASK                                             0x00020000
#define DBOUT1_ACK0_RD(src)                          (((src) & 0x00020000)>>17)
#define DBOUT1_ACK0_WR(src)                     (((u32)(src)<<17) & 0x00020000)
#define DBOUT1_ACK0_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields DBOUT0_ACK	 */
#define DBOUT0_ACK0_WIDTH                                                     1
#define DBOUT0_ACK0_SHIFT                                                    16
#define DBOUT0_ACK0_MASK                                             0x00010000
#define DBOUT0_ACK0_RD(src)                          (((src) & 0x00010000)>>16)
#define DBOUT0_ACK0_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define DBOUT0_ACK0_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields DBIN9_AVAIL	 */
#define DBIN9_AVAIL0_WIDTH                                                    1
#define DBIN9_AVAIL0_SHIFT                                                    9
#define DBIN9_AVAIL0_MASK                                            0x00000200
#define DBIN9_AVAIL0_RD(src)                          (((src) & 0x00000200)>>9)
#define DBIN9_AVAIL0_WR(src)                     (((u32)(src)<<9) & 0x00000200)
#define DBIN9_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields DBIN8_AVAIL	 */
#define DBIN8_AVAIL0_WIDTH                                                    1
#define DBIN8_AVAIL0_SHIFT                                                    8
#define DBIN8_AVAIL0_MASK                                            0x00000100
#define DBIN8_AVAIL0_RD(src)                          (((src) & 0x00000100)>>8)
#define DBIN8_AVAIL0_WR(src)                     (((u32)(src)<<8) & 0x00000100)
#define DBIN8_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields DBIN7_AVAIL	 */
#define DBIN7_AVAIL0_WIDTH                                                    1
#define DBIN7_AVAIL0_SHIFT                                                    7
#define DBIN7_AVAIL0_MASK                                            0x00000080
#define DBIN7_AVAIL0_RD(src)                          (((src) & 0x00000080)>>7)
#define DBIN7_AVAIL0_WR(src)                     (((u32)(src)<<7) & 0x00000080)
#define DBIN7_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields DBIN6_AVAIL	 */
#define DBIN6_AVAIL0_WIDTH                                                    1
#define DBIN6_AVAIL0_SHIFT                                                    6
#define DBIN6_AVAIL0_MASK                                            0x00000040
#define DBIN6_AVAIL0_RD(src)                          (((src) & 0x00000040)>>6)
#define DBIN6_AVAIL0_WR(src)                     (((u32)(src)<<6) & 0x00000040)
#define DBIN6_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields DBIN5_AVAIL	 */
#define DBIN5_AVAIL0_WIDTH                                                    1
#define DBIN5_AVAIL0_SHIFT                                                    5
#define DBIN5_AVAIL0_MASK                                            0x00000020
#define DBIN5_AVAIL0_RD(src)                          (((src) & 0x00000020)>>5)
#define DBIN5_AVAIL0_WR(src)                     (((u32)(src)<<5) & 0x00000020)
#define DBIN5_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields DBIN4_AVAIL	 */
#define DBIN4_AVAIL0_WIDTH                                                    1
#define DBIN4_AVAIL0_SHIFT                                                    4
#define DBIN4_AVAIL0_MASK                                            0x00000010
#define DBIN4_AVAIL0_RD(src)                          (((src) & 0x00000010)>>4)
#define DBIN4_AVAIL0_WR(src)                     (((u32)(src)<<4) & 0x00000010)
#define DBIN4_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields DBIN3_AVAIL	 */
#define DBIN3_AVAIL0_WIDTH                                                    1
#define DBIN3_AVAIL0_SHIFT                                                    3
#define DBIN3_AVAIL0_MASK                                            0x00000008
#define DBIN3_AVAIL0_RD(src)                          (((src) & 0x00000008)>>3)
#define DBIN3_AVAIL0_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define DBIN3_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DBIN2_AVAIL	 */
#define DBIN2_AVAIL0_WIDTH                                                    1
#define DBIN2_AVAIL0_SHIFT                                                    2
#define DBIN2_AVAIL0_MASK                                            0x00000004
#define DBIN2_AVAIL0_RD(src)                          (((src) & 0x00000004)>>2)
#define DBIN2_AVAIL0_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define DBIN2_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DBIN1_AVAIL	 */
#define DBIN1_AVAIL0_WIDTH                                                    1
#define DBIN1_AVAIL0_SHIFT                                                    1
#define DBIN1_AVAIL0_MASK                                            0x00000002
#define DBIN1_AVAIL0_RD(src)                          (((src) & 0x00000002)>>1)
#define DBIN1_AVAIL0_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define DBIN1_AVAIL0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DBIN0_AVAIL	 */
#define DBIN0_AVAIL0_WIDTH                                                    1
#define DBIN0_AVAIL0_SHIFT                                                    0
#define DBIN0_AVAIL0_MASK                                            0x00000001
#define DBIN0_AVAIL0_RD(src)                             (((src) & 0x00000001))
#define DBIN0_AVAIL0_WR(src)                        (((u32)(src)) & 0x00000001)
#define DBIN0_AVAIL0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ARM_INTSTAT0Mask	*/
/*    Mask Register Fields DBOUT9_ACKMask    */
#define DBOUT9_ACKMASK_WIDTH                                                  1
#define DBOUT9_ACKMASK_SHIFT                                                 25
#define DBOUT9_ACKMASK_MASK                                          0x02000000
#define DBOUT9_ACKMASK_RD(src)                       (((src) & 0x02000000)>>25)
#define DBOUT9_ACKMASK_WR(src)                  (((u32)(src)<<25) & 0x02000000)
#define DBOUT9_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields DBOUT8_ACKMask    */
#define DBOUT8_ACKMASK_WIDTH                                                  1
#define DBOUT8_ACKMASK_SHIFT                                                 24
#define DBOUT8_ACKMASK_MASK                                          0x01000000
#define DBOUT8_ACKMASK_RD(src)                       (((src) & 0x01000000)>>24)
#define DBOUT8_ACKMASK_WR(src)                  (((u32)(src)<<24) & 0x01000000)
#define DBOUT8_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields DBOUT7_ACKMask    */
#define DBOUT7_ACKMASK_WIDTH                                                  1
#define DBOUT7_ACKMASK_SHIFT                                                 23
#define DBOUT7_ACKMASK_MASK                                          0x00800000
#define DBOUT7_ACKMASK_RD(src)                       (((src) & 0x00800000)>>23)
#define DBOUT7_ACKMASK_WR(src)                  (((u32)(src)<<23) & 0x00800000)
#define DBOUT7_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields DBOUT6_ACKMask    */
#define DBOUT6_ACKMASK_WIDTH                                                  1
#define DBOUT6_ACKMASK_SHIFT                                                 22
#define DBOUT6_ACKMASK_MASK                                          0x00400000
#define DBOUT6_ACKMASK_RD(src)                       (((src) & 0x00400000)>>22)
#define DBOUT6_ACKMASK_WR(src)                  (((u32)(src)<<22) & 0x00400000)
#define DBOUT6_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields DBOUT5_ACKMask    */
#define DBOUT5_ACKMASK_WIDTH                                                  1
#define DBOUT5_ACKMASK_SHIFT                                                 21
#define DBOUT5_ACKMASK_MASK                                          0x00200000
#define DBOUT5_ACKMASK_RD(src)                       (((src) & 0x00200000)>>21)
#define DBOUT5_ACKMASK_WR(src)                  (((u32)(src)<<21) & 0x00200000)
#define DBOUT5_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields DBOUT4_ACKMask    */
#define DBOUT4_ACKMASK_WIDTH                                                  1
#define DBOUT4_ACKMASK_SHIFT                                                 20
#define DBOUT4_ACKMASK_MASK                                          0x00100000
#define DBOUT4_ACKMASK_RD(src)                       (((src) & 0x00100000)>>20)
#define DBOUT4_ACKMASK_WR(src)                  (((u32)(src)<<20) & 0x00100000)
#define DBOUT4_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields DBOUT3_ACKMask    */
#define DBOUT3_ACKMASK_WIDTH                                                  1
#define DBOUT3_ACKMASK_SHIFT                                                 19
#define DBOUT3_ACKMASK_MASK                                          0x00080000
#define DBOUT3_ACKMASK_RD(src)                       (((src) & 0x00080000)>>19)
#define DBOUT3_ACKMASK_WR(src)                  (((u32)(src)<<19) & 0x00080000)
#define DBOUT3_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields DBOUT2_ACKMask    */
#define DBOUT2_ACKMASK_WIDTH                                                  1
#define DBOUT2_ACKMASK_SHIFT                                                 18
#define DBOUT2_ACKMASK_MASK                                          0x00040000
#define DBOUT2_ACKMASK_RD(src)                       (((src) & 0x00040000)>>18)
#define DBOUT2_ACKMASK_WR(src)                  (((u32)(src)<<18) & 0x00040000)
#define DBOUT2_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields DBOUT1_ACKMask    */
#define DBOUT1_ACKMASK_WIDTH                                                  1
#define DBOUT1_ACKMASK_SHIFT                                                 17
#define DBOUT1_ACKMASK_MASK                                          0x00020000
#define DBOUT1_ACKMASK_RD(src)                       (((src) & 0x00020000)>>17)
#define DBOUT1_ACKMASK_WR(src)                  (((u32)(src)<<17) & 0x00020000)
#define DBOUT1_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields DBOUT0_ACKMask    */
#define DBOUT0_ACKMASK_WIDTH                                                  1
#define DBOUT0_ACKMASK_SHIFT                                                 16
#define DBOUT0_ACKMASK_MASK                                          0x00010000
#define DBOUT0_ACKMASK_RD(src)                       (((src) & 0x00010000)>>16)
#define DBOUT0_ACKMASK_WR(src)                  (((u32)(src)<<16) & 0x00010000)
#define DBOUT0_ACKMASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields DBIN9_AVAILMask    */
#define DBIN9_AVAILMASK_WIDTH                                                 1
#define DBIN9_AVAILMASK_SHIFT                                                 9
#define DBIN9_AVAILMASK_MASK                                         0x00000200
#define DBIN9_AVAILMASK_RD(src)                       (((src) & 0x00000200)>>9)
#define DBIN9_AVAILMASK_WR(src)                  (((u32)(src)<<9) & 0x00000200)
#define DBIN9_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields DBIN8_AVAILMask    */
#define DBIN8_AVAILMASK_WIDTH                                                 1
#define DBIN8_AVAILMASK_SHIFT                                                 8
#define DBIN8_AVAILMASK_MASK                                         0x00000100
#define DBIN8_AVAILMASK_RD(src)                       (((src) & 0x00000100)>>8)
#define DBIN8_AVAILMASK_WR(src)                  (((u32)(src)<<8) & 0x00000100)
#define DBIN8_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields DBIN7_AVAILMask    */
#define DBIN7_AVAILMASK_WIDTH                                                 1
#define DBIN7_AVAILMASK_SHIFT                                                 7
#define DBIN7_AVAILMASK_MASK                                         0x00000080
#define DBIN7_AVAILMASK_RD(src)                       (((src) & 0x00000080)>>7)
#define DBIN7_AVAILMASK_WR(src)                  (((u32)(src)<<7) & 0x00000080)
#define DBIN7_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields DBIN6_AVAILMask    */
#define DBIN6_AVAILMASK_WIDTH                                                 1
#define DBIN6_AVAILMASK_SHIFT                                                 6
#define DBIN6_AVAILMASK_MASK                                         0x00000040
#define DBIN6_AVAILMASK_RD(src)                       (((src) & 0x00000040)>>6)
#define DBIN6_AVAILMASK_WR(src)                  (((u32)(src)<<6) & 0x00000040)
#define DBIN6_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields DBIN5_AVAILMask    */
#define DBIN5_AVAILMASK_WIDTH                                                 1
#define DBIN5_AVAILMASK_SHIFT                                                 5
#define DBIN5_AVAILMASK_MASK                                         0x00000020
#define DBIN5_AVAILMASK_RD(src)                       (((src) & 0x00000020)>>5)
#define DBIN5_AVAILMASK_WR(src)                  (((u32)(src)<<5) & 0x00000020)
#define DBIN5_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields DBIN4_AVAILMask    */
#define DBIN4_AVAILMASK_WIDTH                                                 1
#define DBIN4_AVAILMASK_SHIFT                                                 4
#define DBIN4_AVAILMASK_MASK                                         0x00000010
#define DBIN4_AVAILMASK_RD(src)                       (((src) & 0x00000010)>>4)
#define DBIN4_AVAILMASK_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define DBIN4_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields DBIN3_AVAILMask    */
#define DBIN3_AVAILMASK_WIDTH                                                 1
#define DBIN3_AVAILMASK_SHIFT                                                 3
#define DBIN3_AVAILMASK_MASK                                         0x00000008
#define DBIN3_AVAILMASK_RD(src)                       (((src) & 0x00000008)>>3)
#define DBIN3_AVAILMASK_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define DBIN3_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields DBIN2_AVAILMask    */
#define DBIN2_AVAILMASK_WIDTH                                                 1
#define DBIN2_AVAILMASK_SHIFT                                                 2
#define DBIN2_AVAILMASK_MASK                                         0x00000004
#define DBIN2_AVAILMASK_RD(src)                       (((src) & 0x00000004)>>2)
#define DBIN2_AVAILMASK_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define DBIN2_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields DBIN1_AVAILMask    */
#define DBIN1_AVAILMASK_WIDTH                                                 1
#define DBIN1_AVAILMASK_SHIFT                                                 1
#define DBIN1_AVAILMASK_MASK                                         0x00000002
#define DBIN1_AVAILMASK_RD(src)                       (((src) & 0x00000002)>>1)
#define DBIN1_AVAILMASK_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define DBIN1_AVAILMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields DBIN0_AVAILMask    */
#define DBIN0_AVAILMASK_WIDTH                                                 1
#define DBIN0_AVAILMASK_SHIFT                                                 0
#define DBIN0_AVAILMASK_MASK                                         0x00000001
#define DBIN0_AVAILMASK_RD(src)                          (((src) & 0x00000001))
#define DBIN0_AVAILMASK_WR(src)                     (((u32)(src)) & 0x00000001)
#define DBIN0_AVAILMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ARM_INTSTAT1	*/ 
/*	 Fields SLEEPMODE	 */
#define REGSPEC_SLEEPMODE1_WIDTH                                              1
#define REGSPEC_SLEEPMODE1_SHIFT                                             28
#define REGSPEC_SLEEPMODE1_MASK                                      0x10000000
#define REGSPEC_SLEEPMODE1_RD(src)                   (((src) & 0x10000000)>>28)
#define REGSPEC_SLEEPMODE1_WR(src)              (((u32)(src)<<28) & 0x10000000)
#define REGSPEC_SLEEPMODE1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields QMLITE_ERR	 */
#define QMLITE_ERR1_WIDTH                                                     1
#define QMLITE_ERR1_SHIFT                                                    27
#define QMLITE_ERR1_MASK                                             0x08000000
#define QMLITE_ERR1_RD(src)                          (((src) & 0x08000000)>>27)
#define QMLITE_ERR1_WR(src)                     (((u32)(src)<<27) & 0x08000000)
#define QMLITE_ERR1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MDIO	 */
#define MDIO1_WIDTH                                                           1
#define MDIO1_SHIFT                                                          26
#define MDIO1_MASK                                                   0x04000000
#define MDIO1_RD(src)                                (((src) & 0x04000000)>>26)
#define MDIO1_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define MDIO1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields ENET4_CLE	 */
#define ENET4_CLE1_WIDTH                                                      1
#define ENET4_CLE1_SHIFT                                                     25
#define ENET4_CLE1_MASK                                              0x02000000
#define ENET4_CLE1_RD(src)                           (((src) & 0x02000000)>>25)
#define ENET4_CLE1_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define ENET4_CLE1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields ENET4_QMI	 */
#define ENET4_QMI1_WIDTH                                                      1
#define ENET4_QMI1_SHIFT                                                     24
#define ENET4_QMI1_MASK                                              0x01000000
#define ENET4_QMI1_RD(src)                           (((src) & 0x01000000)>>24)
#define ENET4_QMI1_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define ENET4_QMI1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields ENET4_MAC	 */
#define ENET4_MAC1_WIDTH                                                      1
#define ENET4_MAC1_SHIFT                                                     23
#define ENET4_MAC1_MASK                                              0x00800000
#define ENET4_MAC1_RD(src)                           (((src) & 0x00800000)>>23)
#define ENET4_MAC1_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define ENET4_MAC1_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields ENET4_CSR	 */
#define ENET4_CSR1_WIDTH                                                      1
#define ENET4_CSR1_SHIFT                                                     22
#define ENET4_CSR1_MASK                                              0x00400000
#define ENET4_CSR1_RD(src)                           (((src) & 0x00400000)>>22)
#define ENET4_CSR1_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define ENET4_CSR1_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields PTP	 */
#define PTP1_WIDTH                                                            1
#define PTP1_SHIFT                                                           21
#define PTP1_MASK                                                    0x00200000
#define PTP1_RD(src)                                 (((src) & 0x00200000)>>21)
#define PTP1_WR(src)                            (((u32)(src)<<21) & 0x00200000)
#define PTP1_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields WAKEON_GPIO	 */
#define WAKEON_GPIO1_WIDTH                                                    8
#define WAKEON_GPIO1_SHIFT                                                   13
#define WAKEON_GPIO1_MASK                                            0x001fe000
#define WAKEON_GPIO1_RD(src)                         (((src) & 0x001fe000)>>13)
#define WAKEON_GPIO1_WR(src)                    (((u32)(src)<<13) & 0x001fe000)
#define WAKEON_GPIO1_SET(dst,src) \
                      (((dst) & ~0x001fe000) | (((u32)(src)<<13) & 0x001fe000))
/*	 Fields SATA2	 */
#define SATA21_WIDTH                                                          1
#define SATA21_SHIFT                                                         12
#define SATA21_MASK                                                  0x00001000
#define SATA21_RD(src)                               (((src) & 0x00001000)>>12)
#define SATA21_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define SATA21_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SATA1	 */
#define SATA11_WIDTH                                                          1
#define SATA11_SHIFT                                                         11
#define SATA11_MASK                                                  0x00000800
#define SATA11_RD(src)                               (((src) & 0x00000800)>>11)
#define SATA11_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define SATA11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SATA0	 */
#define SATA01_WIDTH                                                          1
#define SATA01_SHIFT                                                         10
#define SATA01_MASK                                                  0x00000400
#define SATA01_RD(src)                               (((src) & 0x00000400)>>10)
#define SATA01_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define SATA01_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SDIO	 */
#define SDIO1_WIDTH                                                           1
#define SDIO1_SHIFT                                                           9
#define SDIO1_MASK                                                   0x00000200
#define SDIO1_RD(src)                                 (((src) & 0x00000200)>>9)
#define SDIO1_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define SDIO1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields UART3	 */
#define UART31_WIDTH                                                          1
#define UART31_SHIFT                                                          8
#define UART31_MASK                                                  0x00000100
#define UART31_RD(src)                                (((src) & 0x00000100)>>8)
#define UART31_WR(src)                           (((u32)(src)<<8) & 0x00000100)
#define UART31_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields UART2	 */
#define UART21_WIDTH                                                          1
#define UART21_SHIFT                                                          7
#define UART21_MASK                                                  0x00000080
#define UART21_RD(src)                                (((src) & 0x00000080)>>7)
#define UART21_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define UART21_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields UART1	 */
#define UART11_WIDTH                                                          1
#define UART11_SHIFT                                                          6
#define UART11_MASK                                                  0x00000040
#define UART11_RD(src)                                (((src) & 0x00000040)>>6)
#define UART11_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define UART11_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields UART0	 */
#define UART01_WIDTH                                                          1
#define UART01_SHIFT                                                          5
#define UART01_MASK                                                  0x00000020
#define UART01_RD(src)                                (((src) & 0x00000020)>>5)
#define UART01_WR(src)                           (((u32)(src)<<5) & 0x00000020)
#define UART01_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields USB1	 */
#define USB11_WIDTH                                                           1
#define USB11_SHIFT                                                           4
#define USB11_MASK                                                   0x00000010
#define USB11_RD(src)                                 (((src) & 0x00000010)>>4)
#define USB11_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define USB11_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields USB0	 */
#define USB01_WIDTH                                                           1
#define USB01_SHIFT                                                           3
#define USB01_MASK                                                   0x00000008
#define USB01_RD(src)                                 (((src) & 0x00000008)>>3)
#define USB01_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define USB01_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields GFC	 */
#define GFC1_WIDTH                                                            1
#define GFC1_SHIFT                                                            2
#define GFC1_MASK                                                    0x00000004
#define GFC1_RD(src)                                  (((src) & 0x00000004)>>2)
#define GFC1_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define GFC1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SPI1	 */
#define SPI11_WIDTH                                                           1
#define SPI11_SHIFT                                                           1
#define SPI11_MASK                                                   0x00000002
#define SPI11_RD(src)                                 (((src) & 0x00000002)>>1)
#define SPI11_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define SPI11_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SPI0	 */
#define SPI01_WIDTH                                                           1
#define SPI01_SHIFT                                                           0
#define SPI01_MASK                                                   0x00000001
#define SPI01_RD(src)                                    (((src) & 0x00000001))
#define SPI01_WR(src)                               (((u32)(src)) & 0x00000001)
#define SPI01_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ARM_INTSTAT1Mask	*/
/*    Mask Register Fields SLEEPMODEMask    */
#define REGSPEC_SLEEPMODEMASK_WIDTH                                           1
#define REGSPEC_SLEEPMODEMASK_SHIFT                                          28
#define REGSPEC_SLEEPMODEMASK_MASK                                   0x10000000
#define REGSPEC_SLEEPMODEMASK_RD(src)                (((src) & 0x10000000)>>28)
#define REGSPEC_SLEEPMODEMASK_WR(src)           (((u32)(src)<<28) & 0x10000000)
#define REGSPEC_SLEEPMODEMASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields QMLITE_ERRMask    */
#define QMLITE_ERRMASK_WIDTH                                                  1
#define QMLITE_ERRMASK_SHIFT                                                 27
#define QMLITE_ERRMASK_MASK                                          0x08000000
#define QMLITE_ERRMASK_RD(src)                       (((src) & 0x08000000)>>27)
#define QMLITE_ERRMASK_WR(src)                  (((u32)(src)<<27) & 0x08000000)
#define QMLITE_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MDIOMask    */
#define MDIOMASK_WIDTH                                                        1
#define MDIOMASK_SHIFT                                                       26
#define MDIOMASK_MASK                                                0x04000000
#define MDIOMASK_RD(src)                             (((src) & 0x04000000)>>26)
#define MDIOMASK_WR(src)                        (((u32)(src)<<26) & 0x04000000)
#define MDIOMASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields ENET4_CLEMask    */
#define ENET4_CLEMASK_WIDTH                                                   1
#define ENET4_CLEMASK_SHIFT                                                  25
#define ENET4_CLEMASK_MASK                                           0x02000000
#define ENET4_CLEMASK_RD(src)                        (((src) & 0x02000000)>>25)
#define ENET4_CLEMASK_WR(src)                   (((u32)(src)<<25) & 0x02000000)
#define ENET4_CLEMASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields ENET4_QMIMask    */
#define ENET4_QMIMASK_WIDTH                                                   1
#define ENET4_QMIMASK_SHIFT                                                  24
#define ENET4_QMIMASK_MASK                                           0x01000000
#define ENET4_QMIMASK_RD(src)                        (((src) & 0x01000000)>>24)
#define ENET4_QMIMASK_WR(src)                   (((u32)(src)<<24) & 0x01000000)
#define ENET4_QMIMASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields ENET4_MACMask    */
#define ENET4_MACMASK_WIDTH                                                   1
#define ENET4_MACMASK_SHIFT                                                  23
#define ENET4_MACMASK_MASK                                           0x00800000
#define ENET4_MACMASK_RD(src)                        (((src) & 0x00800000)>>23)
#define ENET4_MACMASK_WR(src)                   (((u32)(src)<<23) & 0x00800000)
#define ENET4_MACMASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields ENET4_CSRMask    */
#define ENET4_CSRMASK_WIDTH                                                   1
#define ENET4_CSRMASK_SHIFT                                                  22
#define ENET4_CSRMASK_MASK                                           0x00400000
#define ENET4_CSRMASK_RD(src)                        (((src) & 0x00400000)>>22)
#define ENET4_CSRMASK_WR(src)                   (((u32)(src)<<22) & 0x00400000)
#define ENET4_CSRMASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields PTPMask    */
#define PTPMASK_WIDTH                                                         1
#define PTPMASK_SHIFT                                                        21
#define PTPMASK_MASK                                                 0x00200000
#define PTPMASK_RD(src)                              (((src) & 0x00200000)>>21)
#define PTPMASK_WR(src)                         (((u32)(src)<<21) & 0x00200000)
#define PTPMASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields WAKEON_GPIOMask    */
#define WAKEON_GPIOMASK_WIDTH                                                 8
#define WAKEON_GPIOMASK_SHIFT                                                13
#define WAKEON_GPIOMASK_MASK                                         0x001fe000
#define WAKEON_GPIOMASK_RD(src)                      (((src) & 0x001fe000)>>13)
#define WAKEON_GPIOMASK_WR(src)                 (((u32)(src)<<13) & 0x001fe000)
#define WAKEON_GPIOMASK_SET(dst,src) \
                      (((dst) & ~0x001fe000) | (((u32)(src)<<13) & 0x001fe000))
/*    Mask Register Fields SATA2Mask    */
#define SATA2MASK_WIDTH                                                       1
#define SATA2MASK_SHIFT                                                      12
#define SATA2MASK_MASK                                               0x00001000
#define SATA2MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define SATA2MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define SATA2MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SATA1Mask    */
#define SATA1MASK_WIDTH                                                       1
#define SATA1MASK_SHIFT                                                      11
#define SATA1MASK_MASK                                               0x00000800
#define SATA1MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define SATA1MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define SATA1MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SATA0Mask    */
#define SATA0MASK_WIDTH                                                       1
#define SATA0MASK_SHIFT                                                      10
#define SATA0MASK_MASK                                               0x00000400
#define SATA0MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define SATA0MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define SATA0MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SDIOMask    */
#define SDIOMASK_WIDTH                                                        1
#define SDIOMASK_SHIFT                                                        9
#define SDIOMASK_MASK                                                0x00000200
#define SDIOMASK_RD(src)                              (((src) & 0x00000200)>>9)
#define SDIOMASK_WR(src)                         (((u32)(src)<<9) & 0x00000200)
#define SDIOMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields UART3Mask    */
#define UART3MASK_WIDTH                                                       1
#define UART3MASK_SHIFT                                                       8
#define UART3MASK_MASK                                               0x00000100
#define UART3MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define UART3MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define UART3MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields UART2Mask    */
#define UART2MASK_WIDTH                                                       1
#define UART2MASK_SHIFT                                                       7
#define UART2MASK_MASK                                               0x00000080
#define UART2MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define UART2MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define UART2MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields UART1Mask    */
#define UART1MASK_WIDTH                                                       1
#define UART1MASK_SHIFT                                                       6
#define UART1MASK_MASK                                               0x00000040
#define UART1MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define UART1MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define UART1MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields UART0Mask    */
#define UART0MASK_WIDTH                                                       1
#define UART0MASK_SHIFT                                                       5
#define UART0MASK_MASK                                               0x00000020
#define UART0MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define UART0MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define UART0MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields USB1Mask    */
#define USB1MASK_WIDTH                                                        1
#define USB1MASK_SHIFT                                                        4
#define USB1MASK_MASK                                                0x00000010
#define USB1MASK_RD(src)                              (((src) & 0x00000010)>>4)
#define USB1MASK_WR(src)                         (((u32)(src)<<4) & 0x00000010)
#define USB1MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields USB0Mask    */
#define USB0MASK_WIDTH                                                        1
#define USB0MASK_SHIFT                                                        3
#define USB0MASK_MASK                                                0x00000008
#define USB0MASK_RD(src)                              (((src) & 0x00000008)>>3)
#define USB0MASK_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define USB0MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields GFCMask    */
#define GFCMASK_WIDTH                                                         1
#define GFCMASK_SHIFT                                                         2
#define GFCMASK_MASK                                                 0x00000004
#define GFCMASK_RD(src)                               (((src) & 0x00000004)>>2)
#define GFCMASK_WR(src)                          (((u32)(src)<<2) & 0x00000004)
#define GFCMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields SPI1Mask    */
#define SPI1MASK_WIDTH                                                        1
#define SPI1MASK_SHIFT                                                        1
#define SPI1MASK_MASK                                                0x00000002
#define SPI1MASK_RD(src)                              (((src) & 0x00000002)>>1)
#define SPI1MASK_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define SPI1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SPI0Mask    */
#define SPI0MASK_WIDTH                                                        1
#define SPI0MASK_SHIFT                                                        0
#define SPI0MASK_MASK                                                0x00000001
#define SPI0MASK_RD(src)                                 (((src) & 0x00000001))
#define SPI0MASK_WR(src)                            (((u32)(src)) & 0x00000001)
#define SPI0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ARM_INTSTAT2	*/ 
/*	 Fields TS_EVENT	 */
#define TS_EVENT2_WIDTH                                                       1
#define TS_EVENT2_SHIFT                                                       8
#define TS_EVENT2_MASK                                               0x00000100
#define TS_EVENT2_RD(src)                             (((src) & 0x00000100)>>8)
#define TS_EVENT2_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define TS_EVENT2_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ATMR2_EVENT	 */
#define ATMR2_EVENT2_WIDTH                                                    1
#define ATMR2_EVENT2_SHIFT                                                    2
#define ATMR2_EVENT2_MASK                                            0x00000004
#define ATMR2_EVENT2_RD(src)                          (((src) & 0x00000004)>>2)
#define ATMR2_EVENT2_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define ATMR2_EVENT2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ATMR1_EVENT	 */
#define ATMR1_EVENT2_WIDTH                                                    1
#define ATMR1_EVENT2_SHIFT                                                    1
#define ATMR1_EVENT2_MASK                                            0x00000002
#define ATMR1_EVENT2_RD(src)                          (((src) & 0x00000002)>>1)
#define ATMR1_EVENT2_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define ATMR1_EVENT2_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ATMR0_EVENT	 */
#define ATMR0_EVENT2_WIDTH                                                    1
#define ATMR0_EVENT2_SHIFT                                                    0
#define ATMR0_EVENT2_MASK                                            0x00000001
#define ATMR0_EVENT2_RD(src)                             (((src) & 0x00000001))
#define ATMR0_EVENT2_WR(src)                        (((u32)(src)) & 0x00000001)
#define ATMR0_EVENT2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ARM_INTSTAT2Mask	*/
/*    Mask Register Fields TS_EVENTMask    */
#define TS_EVENTMASK_WIDTH                                                    1
#define TS_EVENTMASK_SHIFT                                                    8
#define TS_EVENTMASK_MASK                                            0x00000100
#define TS_EVENTMASK_RD(src)                          (((src) & 0x00000100)>>8)
#define TS_EVENTMASK_WR(src)                     (((u32)(src)<<8) & 0x00000100)
#define TS_EVENTMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields ATMR2_EVENTMask    */
#define ATMR2_EVENTMASK_WIDTH                                                 1
#define ATMR2_EVENTMASK_SHIFT                                                 2
#define ATMR2_EVENTMASK_MASK                                         0x00000004
#define ATMR2_EVENTMASK_RD(src)                       (((src) & 0x00000004)>>2)
#define ATMR2_EVENTMASK_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define ATMR2_EVENTMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields ATMR1_EVENTMask    */
#define ATMR1_EVENTMASK_WIDTH                                                 1
#define ATMR1_EVENTMASK_SHIFT                                                 1
#define ATMR1_EVENTMASK_MASK                                         0x00000002
#define ATMR1_EVENTMASK_RD(src)                       (((src) & 0x00000002)>>1)
#define ATMR1_EVENTMASK_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define ATMR1_EVENTMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields ATMR0_EVENTMask    */
#define ATMR0_EVENTMASK_WIDTH                                                 1
#define ATMR0_EVENTMASK_SHIFT                                                 0
#define ATMR0_EVENTMASK_MASK                                         0x00000001
#define ATMR0_EVENTMASK_RD(src)                          (((src) & 0x00000001))
#define ATMR0_EVENTMASK_WR(src)                     (((u32)(src)) & 0x00000001)
#define ATMR0_EVENTMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ARM_INTSTAT3	*/ 
/*	 Fields GIC_WAKE_FIQ	 */
#define GIC_WAKE_FIQ3_WIDTH                                                   8
#define GIC_WAKE_FIQ3_SHIFT                                                   8
#define GIC_WAKE_FIQ3_MASK                                           0x0000ff00
#define GIC_WAKE_FIQ3_RD(src)                         (((src) & 0x0000ff00)>>8)
#define GIC_WAKE_FIQ3_WR(src)                    (((u32)(src)<<8) & 0x0000ff00)
#define GIC_WAKE_FIQ3_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields GIC_WAKE_IRQ	 */
#define GIC_WAKE_IRQ3_WIDTH                                                   8
#define GIC_WAKE_IRQ3_SHIFT                                                   0
#define GIC_WAKE_IRQ3_MASK                                           0x000000ff
#define GIC_WAKE_IRQ3_RD(src)                            (((src) & 0x000000ff))
#define GIC_WAKE_IRQ3_WR(src)                       (((u32)(src)) & 0x000000ff)
#define GIC_WAKE_IRQ3_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register MPA_ARM_INTSTAT3Mask	*/
/*    Mask Register Fields GIC_WAKE_FIQMask    */
#define GIC_WAKE_FIQMASK_WIDTH                                                8
#define GIC_WAKE_FIQMASK_SHIFT                                                8
#define GIC_WAKE_FIQMASK_MASK                                        0x0000ff00
#define GIC_WAKE_FIQMASK_RD(src)                      (((src) & 0x0000ff00)>>8)
#define GIC_WAKE_FIQMASK_WR(src)                 (((u32)(src)<<8) & 0x0000ff00)
#define GIC_WAKE_FIQMASK_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*    Mask Register Fields GIC_WAKE_IRQMask    */
#define GIC_WAKE_IRQMASK_WIDTH                                                8
#define GIC_WAKE_IRQMASK_SHIFT                                                0
#define GIC_WAKE_IRQMASK_MASK                                        0x000000ff
#define GIC_WAKE_IRQMASK_RD(src)                         (((src) & 0x000000ff))
#define GIC_WAKE_IRQMASK_WR(src)                    (((u32)(src)) & 0x000000ff)
#define GIC_WAKE_IRQMASK_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register MPA_WOL_STAT	*/ 
/*	 Fields CLE_WOL_MODE	 */
#define REGSPEC_CLE_WOL_MODE_WIDTH                                            1
#define REGSPEC_CLE_WOL_MODE_SHIFT                                            0
#define REGSPEC_CLE_WOL_MODE_MASK                                    0x00000001
#define REGSPEC_CLE_WOL_MODE_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_CLE_WOL_MODE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register PKP_DEBUG	*/ 
/*	 Fields PKA_FIFO_SIZE_SEL	 */
#define PKA_FIFO_SIZE_SEL_WIDTH                                               1
#define PKA_FIFO_SIZE_SEL_SHIFT                                               1
#define PKA_FIFO_SIZE_SEL_MASK                                       0x00000002
#define PKA_FIFO_SIZE_SEL_RD(src)                     (((src) & 0x00000002)>>1)
#define PKA_FIFO_SIZE_SEL_WR(src)                (((u32)(src)<<1) & 0x00000002)
#define PKA_FIFO_SIZE_SEL_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ZEROIZE_RST	 */
#define ZEROIZE_RST_WIDTH                                                     1
#define ZEROIZE_RST_SHIFT                                                     0
#define ZEROIZE_RST_MASK                                             0x00000001
#define ZEROIZE_RST_RD(src)                              (((src) & 0x00000001))
#define ZEROIZE_RST_WR(src)                         (((u32)(src)) & 0x00000001)
#define ZEROIZE_RST_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_GPIO_INT_LVL	*/ 
/*	 Fields GPIO_INT_LVL	 */
#define GPIO_INT_LVL_WIDTH                                                    8
#define GPIO_INT_LVL_SHIFT                                                    0
#define GPIO_INT_LVL_MASK                                            0x000000ff
#define GPIO_INT_LVL_RD(src)                             (((src) & 0x000000ff))
#define GPIO_INT_LVL_WR(src)                        (((u32)(src)) & 0x000000ff)
#define GPIO_INT_LVL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register MPA_GPIO_SEL_LO	*/ 
/*	 Fields GPIO_SEL	 */
#define GPIO_SEL_WIDTH                                                       32
#define GPIO_SEL_SHIFT                                                        0
#define GPIO_SEL_MASK                                                0xffffffff
#define GPIO_SEL_RD(src)                                 (((src) & 0xffffffff))
#define GPIO_SEL_WR(src)                            (((u32)(src)) & 0xffffffff)
#define GPIO_SEL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_GPIO_SEL_HI	*/ 
/*	 Fields GPIO_SEL	 */
#define GPIO_SEL_F1_WIDTH                                                    16
#define GPIO_SEL_F1_SHIFT                                                     0
#define GPIO_SEL_F1_MASK                                             0x0000ffff
#define GPIO_SEL_F1_RD(src)                              (((src) & 0x0000ffff))
#define GPIO_SEL_F1_WR(src)                         (((u32)(src)) & 0x0000ffff)
#define GPIO_SEL_F1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_GPIO_OE	*/ 
/*	 Fields GPIO_OE	 */
#define GPIO_OE_WIDTH                                                        24
#define GPIO_OE_SHIFT                                                         0
#define GPIO_OE_MASK                                                 0x00ffffff
#define GPIO_OE_RD(src)                                  (((src) & 0x00ffffff))
#define GPIO_OE_WR(src)                             (((u32)(src)) & 0x00ffffff)
#define GPIO_OE_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register MPA_GPIO_OUT	*/ 
/*	 Fields GPIO_OUT	 */
#define GPIO_OUT_WIDTH                                                       24
#define GPIO_OUT_SHIFT                                                        0
#define GPIO_OUT_MASK                                                0x00ffffff
#define GPIO_OUT_RD(src)                                 (((src) & 0x00ffffff))
#define GPIO_OUT_WR(src)                            (((u32)(src)) & 0x00ffffff)
#define GPIO_OUT_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register MPA_GPIO_IN	*/ 
/*	 Fields GPIO_IN	 */
#define GPIO_IN_WIDTH                                                        24
#define GPIO_IN_SHIFT                                                         0
#define GPIO_IN_MASK                                                 0x00ffffff
#define GPIO_IN_RD(src)                                  (((src) & 0x00ffffff))
#define GPIO_IN_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register MPA_GPIO_OD	*/ 
/*	 Fields GPIO_OD	 */
#define GPIO_OD_WIDTH                                                        24
#define GPIO_OD_SHIFT                                                         0
#define GPIO_OD_MASK                                                 0x00ffffff
#define GPIO_OD_RD(src)                                  (((src) & 0x00ffffff))
#define GPIO_OD_WR(src)                             (((u32)(src)) & 0x00ffffff)
#define GPIO_OD_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register MPA_ATMR0	*/ 
/*	 Fields ATMR0_START	 */
#define ATMR0_START0_WIDTH                                                    1
#define ATMR0_START0_SHIFT                                                   31
#define ATMR0_START0_MASK                                            0x80000000
#define ATMR0_START0_RD(src)                         (((src) & 0x80000000)>>31)
#define ATMR0_START0_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define ATMR0_START0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ATMR0_RES	 */
#define ATMR0_RES0_WIDTH                                                      4
#define ATMR0_RES0_SHIFT                                                     16
#define ATMR0_RES0_MASK                                              0x000f0000
#define ATMR0_RES0_RD(src)                           (((src) & 0x000f0000)>>16)
#define ATMR0_RES0_WR(src)                      (((u32)(src)<<16) & 0x000f0000)
#define ATMR0_RES0_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields ATMR0_PER	 */
#define ATMR0_PER0_WIDTH                                                     16
#define ATMR0_PER0_SHIFT                                                      0
#define ATMR0_PER0_MASK                                              0x0000ffff
#define ATMR0_PER0_RD(src)                               (((src) & 0x0000ffff))
#define ATMR0_PER0_WR(src)                          (((u32)(src)) & 0x0000ffff)
#define ATMR0_PER0_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_ATMR1	*/ 
/*	 Fields ATMR1_START	 */
#define ATMR1_START1_WIDTH                                                    1
#define ATMR1_START1_SHIFT                                                   31
#define ATMR1_START1_MASK                                            0x80000000
#define ATMR1_START1_RD(src)                         (((src) & 0x80000000)>>31)
#define ATMR1_START1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define ATMR1_START1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ATMR1_RES	 */
#define ATMR1_RES1_WIDTH                                                      4
#define ATMR1_RES1_SHIFT                                                     16
#define ATMR1_RES1_MASK                                              0x000f0000
#define ATMR1_RES1_RD(src)                           (((src) & 0x000f0000)>>16)
#define ATMR1_RES1_WR(src)                      (((u32)(src)<<16) & 0x000f0000)
#define ATMR1_RES1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields ATMR1_PER	 */
#define ATMR1_PER1_WIDTH                                                     16
#define ATMR1_PER1_SHIFT                                                      0
#define ATMR1_PER1_MASK                                              0x0000ffff
#define ATMR1_PER1_RD(src)                               (((src) & 0x0000ffff))
#define ATMR1_PER1_WR(src)                          (((u32)(src)) & 0x0000ffff)
#define ATMR1_PER1_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_ATMR2	*/ 
/*	 Fields ATMR2_START	 */
#define ATMR2_START2_WIDTH                                                    1
#define ATMR2_START2_SHIFT                                                   31
#define ATMR2_START2_MASK                                            0x80000000
#define ATMR2_START2_RD(src)                         (((src) & 0x80000000)>>31)
#define ATMR2_START2_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define ATMR2_START2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ATMR2_RES	 */
#define ATMR2_RES2_WIDTH                                                      4
#define ATMR2_RES2_SHIFT                                                     16
#define ATMR2_RES2_MASK                                              0x000f0000
#define ATMR2_RES2_RD(src)                           (((src) & 0x000f0000)>>16)
#define ATMR2_RES2_WR(src)                      (((u32)(src)<<16) & 0x000f0000)
#define ATMR2_RES2_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields ATMR2_PER	 */
#define ATMR2_PER2_WIDTH                                                     16
#define ATMR2_PER2_SHIFT                                                      0
#define ATMR2_PER2_MASK                                              0x0000ffff
#define ATMR2_PER2_RD(src)                               (((src) & 0x0000ffff))
#define ATMR2_PER2_WR(src)                          (((u32)(src)) & 0x0000ffff)
#define ATMR2_PER2_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_IIDMA_CTL	*/ 
/*	 Fields IIDMA_EN	 */
#define IIDMA_EN_WIDTH                                                        1
#define IIDMA_EN_SHIFT                                                        0
#define IIDMA_EN_MASK                                                0x00000001
#define IIDMA_EN_RD(src)                                 (((src) & 0x00000001))
#define IIDMA_EN_WR(src)                            (((u32)(src)) & 0x00000001)
#define IIDMA_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_IIDMA_CNT	*/ 
/*	 Fields IIDMA_CNT	 */
#define IIDMA_CNT_WIDTH                                                      13
#define IIDMA_CNT_SHIFT                                                       0
#define IIDMA_CNT_MASK                                               0x00001fff
#define IIDMA_CNT_RD(src)                                (((src) & 0x00001fff))
#define IIDMA_CNT_WR(src)                           (((u32)(src)) & 0x00001fff)
#define IIDMA_CNT_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register MPA_IIDMA_IRAMADDR	*/ 
/*	 Fields IIDMA_IRAMADDR	 */
#define IIDMA_IRAMADDR_WIDTH                                                 16
#define IIDMA_IRAMADDR_SHIFT                                                  0
#define IIDMA_IRAMADDR_MASK                                          0x0000ffff
#define IIDMA_IRAMADDR_RD(src)                           (((src) & 0x0000ffff))
#define IIDMA_IRAMADDR_WR(src)                      (((u32)(src)) & 0x0000ffff)
#define IIDMA_IRAMADDR_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_IIDMA_IICADDR	*/ 
/*	 Fields IIDMA_IICADDR	 */
#define IIDMA_IICADDR_WIDTH                                                  17
#define IIDMA_IICADDR_SHIFT                                                   0
#define IIDMA_IICADDR_MASK                                           0x0001ffff
#define IIDMA_IICADDR_RD(src)                            (((src) & 0x0001ffff))
#define IIDMA_IICADDR_WR(src)                       (((u32)(src)) & 0x0001ffff)
#define IIDMA_IICADDR_SET(dst,src) \
                          (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register MPA_IIDMA_STAT	*/ 
/*	 Fields IIDMA_PENDING	 */
#define IIDMA_PENDING_WIDTH                                                   1
#define IIDMA_PENDING_SHIFT                                                   0
#define IIDMA_PENDING_MASK                                           0x00000001
#define IIDMA_PENDING_RD(src)                            (((src) & 0x00000001))
#define IIDMA_PENDING_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_DIAG	*/ 
/*	 Fields SBF_DIAG_SEL	 */
#define SBF_DIAG_SEL_WIDTH                                                    5
#define SBF_DIAG_SEL_SHIFT                                                   24
#define SBF_DIAG_SEL_MASK                                            0x1f000000
#define SBF_DIAG_SEL_RD(src)                         (((src) & 0x1f000000)>>24)
#define SBF_DIAG_SEL_WR(src)                    (((u32)(src)<<24) & 0x1f000000)
#define SBF_DIAG_SEL_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields XGE0134_DIAG_SEL	 */
#define XGE0134_DIAG_SEL_WIDTH                                                2
#define XGE0134_DIAG_SEL_SHIFT                                               22
#define XGE0134_DIAG_SEL_MASK                                        0x00c00000
#define XGE0134_DIAG_SEL_RD(src)                     (((src) & 0x00c00000)>>22)
#define XGE0134_DIAG_SEL_WR(src)                (((u32)(src)<<22) & 0x00c00000)
#define XGE0134_DIAG_SEL_SET(dst,src) \
                      (((dst) & ~0x00c00000) | (((u32)(src)<<22) & 0x00c00000))
/*	 Fields AHBC_DMA_DIAG_SEL	 */
#define AHBC_DMA_DIAG_SEL_WIDTH                                               2
#define AHBC_DMA_DIAG_SEL_SHIFT                                              20
#define AHBC_DMA_DIAG_SEL_MASK                                       0x00300000
#define AHBC_DMA_DIAG_SEL_RD(src)                    (((src) & 0x00300000)>>20)
#define AHBC_DMA_DIAG_SEL_WR(src)               (((u32)(src)<<20) & 0x00300000)
#define AHBC_DMA_DIAG_SEL_SET(dst,src) \
                      (((dst) & ~0x00300000) | (((u32)(src)<<20) & 0x00300000))
/*	 Fields CTM_OCM_DIAG_SEL	 */
#define CTM_OCM_DIAG_SEL_WIDTH                                                3
#define CTM_OCM_DIAG_SEL_SHIFT                                               16
#define CTM_OCM_DIAG_SEL_MASK                                        0x00070000
#define CTM_OCM_DIAG_SEL_RD(src)                     (((src) & 0x00070000)>>16)
#define CTM_OCM_DIAG_SEL_WR(src)                (((u32)(src)<<16) & 0x00070000)
#define CTM_OCM_DIAG_SEL_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields SATA_TRC_DIAG_SEL	 */
#define SATA_TRC_DIAG_SEL_WIDTH                                               3
#define SATA_TRC_DIAG_SEL_SHIFT                                              12
#define SATA_TRC_DIAG_SEL_MASK                                       0x00007000
#define SATA_TRC_DIAG_SEL_RD(src)                    (((src) & 0x00007000)>>12)
#define SATA_TRC_DIAG_SEL_WR(src)               (((u32)(src)<<12) & 0x00007000)
#define SATA_TRC_DIAG_SEL_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields PCIE0134_DIAG_SEL	 */
#define PCIE0134_DIAG_SEL_WIDTH                                               2
#define PCIE0134_DIAG_SEL_SHIFT                                              10
#define PCIE0134_DIAG_SEL_MASK                                       0x00000c00
#define PCIE0134_DIAG_SEL_RD(src)                    (((src) & 0x00000c00)>>10)
#define PCIE0134_DIAG_SEL_WR(src)               (((u32)(src)<<10) & 0x00000c00)
#define PCIE0134_DIAG_SEL_SET(dst,src) \
                      (((dst) & ~0x00000c00) | (((u32)(src)<<10) & 0x00000c00))
/*	 Fields SATA_ENET_QM_DIAG_SEL	 */
#define SATA_ENET_QM_DIAG_SEL_WIDTH                                           2
#define SATA_ENET_QM_DIAG_SEL_SHIFT                                           8
#define SATA_ENET_QM_DIAG_SEL_MASK                                   0x00000300
#define SATA_ENET_QM_DIAG_SEL_RD(src)                 (((src) & 0x00000300)>>8)
#define SATA_ENET_QM_DIAG_SEL_WR(src)            (((u32)(src)<<8) & 0x00000300)
#define SATA_ENET_QM_DIAG_SEL_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields STORM_DIAG_SEL	 */
#define STORM_DIAG_SEL_WIDTH                                                  6
#define STORM_DIAG_SEL_SHIFT                                                  0
#define STORM_DIAG_SEL_MASK                                          0x0000003f
#define STORM_DIAG_SEL_RD(src)                           (((src) & 0x0000003f))
#define STORM_DIAG_SEL_WR(src)                      (((u32)(src)) & 0x0000003f)
#define STORM_DIAG_SEL_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register MPA_LED	*/ 
/*	 Fields LED	 */
#define LED_WIDTH                                                             5
#define LED_SHIFT                                                             0
#define LED_MASK                                                     0x0000001f
#define LED_RD(src)                                      (((src) & 0x0000001f))
#define LED_WR(src)                                 (((u32)(src)) & 0x0000001f)
#define LED_SET(dst,src) (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register MPA_INTDBG0	*/ 
/*	 Fields ARM_NMI	 */
#define ARM_NMI0_WIDTH                                                        1
#define ARM_NMI0_SHIFT                                                       31
#define ARM_NMI0_MASK                                                0x80000000
#define ARM_NMI0_RD(src)                             (((src) & 0x80000000)>>31)
#define ARM_NMI0_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define ARM_NMI0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ARM_INT	 */
#define ARM_INT0_WIDTH                                                       13
#define ARM_INT0_SHIFT                                                        0
#define ARM_INT0_MASK                                                0x00001fff
#define ARM_INT0_RD(src)                                 (((src) & 0x00001fff))
#define ARM_INT0_WR(src)                            (((u32)(src)) & 0x00001fff)
#define ARM_INT0_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register MPA_INTDBG1	*/ 
/*	 Fields GIC_INT	 */
#define GIC_INT1_WIDTH                                                       17
#define GIC_INT1_SHIFT                                                        0
#define GIC_INT1_MASK                                                0x0001ffff
#define GIC_INT1_RD(src)                                 (((src) & 0x0001ffff))
#define GIC_INT1_WR(src)                            (((u32)(src)) & 0x0001ffff)
#define GIC_INT1_SET(dst,src) \
                          (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register MPA_ERR_ADDR0	*/ 
/*	 Fields ADDR0	 */
#define ADDR00_WIDTH                                                         32
#define ADDR00_SHIFT                                                          0
#define ADDR00_MASK                                                  0xffffffff
#define ADDR00_RD(src)                                   (((src) & 0xffffffff))
#define ADDR00_WR(src)                              (((u32)(src)) & 0xffffffff)
#define ADDR00_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ERR_ADDR1	*/ 
/*	 Fields ERR_WRITE	 */
#define ERR_WRITE1_WIDTH                                                      1
#define ERR_WRITE1_SHIFT                                                     31
#define ERR_WRITE1_MASK                                              0x80000000
#define ERR_WRITE1_RD(src)                           (((src) & 0x80000000)>>31)
#define ERR_WRITE1_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define ERR_WRITE1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields ADDR1	 */
#define ADDR11_WIDTH                                                         10
#define ADDR11_SHIFT                                                          0
#define ADDR11_MASK                                                  0x000003ff
#define ADDR11_RD(src)                                   (((src) & 0x000003ff))
#define ADDR11_WR(src)                              (((u32)(src)) & 0x000003ff)
#define ADDR11_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register MPA_ERR	*/ 
/*	 Fields PROH_FACC	 */
#define PROH_FACC_WIDTH                                                       1
#define PROH_FACC_SHIFT                                                      31
#define PROH_FACC_MASK                                               0x80000000
#define PROH_FACC_RD(src)                            (((src) & 0x80000000)>>31)
#define PROH_FACC_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define PROH_FACC_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields AXI_SLVERR	 */
#define AXI_SLVERR_WIDTH                                                      1
#define AXI_SLVERR_SHIFT                                                     17
#define AXI_SLVERR_MASK                                              0x00020000
#define AXI_SLVERR_RD(src)                           (((src) & 0x00020000)>>17)
#define AXI_SLVERR_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define AXI_SLVERR_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields PKA_PROG_RAM_ERR	 */
#define PKA_PROG_RAM_ERR_WIDTH                                                1
#define PKA_PROG_RAM_ERR_SHIFT                                               16
#define PKA_PROG_RAM_ERR_MASK                                        0x00010000
#define PKA_PROG_RAM_ERR_RD(src)                     (((src) & 0x00010000)>>16)
#define PKA_PROG_RAM_ERR_WR(src)                (((u32)(src)<<16) & 0x00010000)
#define PKA_PROG_RAM_ERR_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ARM_RAM15_ERR	 */
#define ARM_RAM15_ERR_WIDTH                                                   1
#define ARM_RAM15_ERR_SHIFT                                                  15
#define ARM_RAM15_ERR_MASK                                           0x00008000
#define ARM_RAM15_ERR_RD(src)                        (((src) & 0x00008000)>>15)
#define ARM_RAM15_ERR_WR(src)                   (((u32)(src)<<15) & 0x00008000)
#define ARM_RAM15_ERR_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields ARM_RAM14_ERR	 */
#define ARM_RAM14_ERR_WIDTH                                                   1
#define ARM_RAM14_ERR_SHIFT                                                  14
#define ARM_RAM14_ERR_MASK                                           0x00004000
#define ARM_RAM14_ERR_RD(src)                        (((src) & 0x00004000)>>14)
#define ARM_RAM14_ERR_WR(src)                   (((u32)(src)<<14) & 0x00004000)
#define ARM_RAM14_ERR_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields ARM_RAM13_ERR	 */
#define ARM_RAM13_ERR_WIDTH                                                   1
#define ARM_RAM13_ERR_SHIFT                                                  13
#define ARM_RAM13_ERR_MASK                                           0x00002000
#define ARM_RAM13_ERR_RD(src)                        (((src) & 0x00002000)>>13)
#define ARM_RAM13_ERR_WR(src)                   (((u32)(src)<<13) & 0x00002000)
#define ARM_RAM13_ERR_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields ARM_RAM12_ERR	 */
#define ARM_RAM12_ERR_WIDTH                                                   1
#define ARM_RAM12_ERR_SHIFT                                                  12
#define ARM_RAM12_ERR_MASK                                           0x00001000
#define ARM_RAM12_ERR_RD(src)                        (((src) & 0x00001000)>>12)
#define ARM_RAM12_ERR_WR(src)                   (((u32)(src)<<12) & 0x00001000)
#define ARM_RAM12_ERR_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields ARM_RAM11_ERR	 */
#define ARM_RAM11_ERR_WIDTH                                                   1
#define ARM_RAM11_ERR_SHIFT                                                  11
#define ARM_RAM11_ERR_MASK                                           0x00000800
#define ARM_RAM11_ERR_RD(src)                        (((src) & 0x00000800)>>11)
#define ARM_RAM11_ERR_WR(src)                   (((u32)(src)<<11) & 0x00000800)
#define ARM_RAM11_ERR_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields ARM_RAM10_ERR	 */
#define ARM_RAM10_ERR_WIDTH                                                   1
#define ARM_RAM10_ERR_SHIFT                                                  10
#define ARM_RAM10_ERR_MASK                                           0x00000400
#define ARM_RAM10_ERR_RD(src)                        (((src) & 0x00000400)>>10)
#define ARM_RAM10_ERR_WR(src)                   (((u32)(src)<<10) & 0x00000400)
#define ARM_RAM10_ERR_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields ARM_RAM9_ERR	 */
#define ARM_RAM9_ERR_WIDTH                                                    1
#define ARM_RAM9_ERR_SHIFT                                                    9
#define ARM_RAM9_ERR_MASK                                            0x00000200
#define ARM_RAM9_ERR_RD(src)                          (((src) & 0x00000200)>>9)
#define ARM_RAM9_ERR_WR(src)                     (((u32)(src)<<9) & 0x00000200)
#define ARM_RAM9_ERR_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ARM_RAM8_ERR	 */
#define ARM_RAM8_ERR_WIDTH                                                    1
#define ARM_RAM8_ERR_SHIFT                                                    8
#define ARM_RAM8_ERR_MASK                                            0x00000100
#define ARM_RAM8_ERR_RD(src)                          (((src) & 0x00000100)>>8)
#define ARM_RAM8_ERR_WR(src)                     (((u32)(src)<<8) & 0x00000100)
#define ARM_RAM8_ERR_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ARM_RAM7_ERR	 */
#define ARM_RAM7_ERR_WIDTH                                                    1
#define ARM_RAM7_ERR_SHIFT                                                    7
#define ARM_RAM7_ERR_MASK                                            0x00000080
#define ARM_RAM7_ERR_RD(src)                          (((src) & 0x00000080)>>7)
#define ARM_RAM7_ERR_WR(src)                     (((u32)(src)<<7) & 0x00000080)
#define ARM_RAM7_ERR_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields ARM_RAM6_ERR	 */
#define ARM_RAM6_ERR_WIDTH                                                    1
#define ARM_RAM6_ERR_SHIFT                                                    6
#define ARM_RAM6_ERR_MASK                                            0x00000040
#define ARM_RAM6_ERR_RD(src)                          (((src) & 0x00000040)>>6)
#define ARM_RAM6_ERR_WR(src)                     (((u32)(src)<<6) & 0x00000040)
#define ARM_RAM6_ERR_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ARM_RAM5_ERR	 */
#define ARM_RAM5_ERR_WIDTH                                                    1
#define ARM_RAM5_ERR_SHIFT                                                    5
#define ARM_RAM5_ERR_MASK                                            0x00000020
#define ARM_RAM5_ERR_RD(src)                          (((src) & 0x00000020)>>5)
#define ARM_RAM5_ERR_WR(src)                     (((u32)(src)<<5) & 0x00000020)
#define ARM_RAM5_ERR_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ARM_RAM4_ERR	 */
#define ARM_RAM4_ERR_WIDTH                                                    1
#define ARM_RAM4_ERR_SHIFT                                                    4
#define ARM_RAM4_ERR_MASK                                            0x00000010
#define ARM_RAM4_ERR_RD(src)                          (((src) & 0x00000010)>>4)
#define ARM_RAM4_ERR_WR(src)                     (((u32)(src)<<4) & 0x00000010)
#define ARM_RAM4_ERR_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ARM_RAM3_ERR	 */
#define ARM_RAM3_ERR_WIDTH                                                    1
#define ARM_RAM3_ERR_SHIFT                                                    3
#define ARM_RAM3_ERR_MASK                                            0x00000008
#define ARM_RAM3_ERR_RD(src)                          (((src) & 0x00000008)>>3)
#define ARM_RAM3_ERR_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define ARM_RAM3_ERR_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ARM_RAM2_ERR	 */
#define ARM_RAM2_ERR_WIDTH                                                    1
#define ARM_RAM2_ERR_SHIFT                                                    2
#define ARM_RAM2_ERR_MASK                                            0x00000004
#define ARM_RAM2_ERR_RD(src)                          (((src) & 0x00000004)>>2)
#define ARM_RAM2_ERR_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define ARM_RAM2_ERR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ARM_RAM1_ERR	 */
#define ARM_RAM1_ERR_WIDTH                                                    1
#define ARM_RAM1_ERR_SHIFT                                                    1
#define ARM_RAM1_ERR_MASK                                            0x00000002
#define ARM_RAM1_ERR_RD(src)                          (((src) & 0x00000002)>>1)
#define ARM_RAM1_ERR_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define ARM_RAM1_ERR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ARM_RAM0_ERR	 */
#define ARM_RAM0_ERR_WIDTH                                                    1
#define ARM_RAM0_ERR_SHIFT                                                    0
#define ARM_RAM0_ERR_MASK                                            0x00000001
#define ARM_RAM0_ERR_RD(src)                             (((src) & 0x00000001))
#define ARM_RAM0_ERR_WR(src)                        (((u32)(src)) & 0x00000001)
#define ARM_RAM0_ERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ERRMask	*/
/*    Mask Register Fields PROH_FACCMask    */
#define PROH_FACCMASK_WIDTH                                                   1
#define PROH_FACCMASK_SHIFT                                                  31
#define PROH_FACCMASK_MASK                                           0x80000000
#define PROH_FACCMASK_RD(src)                        (((src) & 0x80000000)>>31)
#define PROH_FACCMASK_WR(src)                   (((u32)(src)<<31) & 0x80000000)
#define PROH_FACCMASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields AXI_SLVERRMask    */
#define AXI_SLVERRMASK_WIDTH                                                  1
#define AXI_SLVERRMASK_SHIFT                                                 17
#define AXI_SLVERRMASK_MASK                                          0x00020000
#define AXI_SLVERRMASK_RD(src)                       (((src) & 0x00020000)>>17)
#define AXI_SLVERRMASK_WR(src)                  (((u32)(src)<<17) & 0x00020000)
#define AXI_SLVERRMASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields PKA_PROG_RAM_ERRMask    */
#define PKA_PROG_RAM_ERRMASK_WIDTH                                            1
#define PKA_PROG_RAM_ERRMASK_SHIFT                                           16
#define PKA_PROG_RAM_ERRMASK_MASK                                    0x00010000
#define PKA_PROG_RAM_ERRMASK_RD(src)                 (((src) & 0x00010000)>>16)
#define PKA_PROG_RAM_ERRMASK_WR(src)            (((u32)(src)<<16) & 0x00010000)
#define PKA_PROG_RAM_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ARM_RAM15_ERRMask    */
#define ARM_RAM15_ERRMASK_WIDTH                                               1
#define ARM_RAM15_ERRMASK_SHIFT                                              15
#define ARM_RAM15_ERRMASK_MASK                                       0x00008000
#define ARM_RAM15_ERRMASK_RD(src)                    (((src) & 0x00008000)>>15)
#define ARM_RAM15_ERRMASK_WR(src)               (((u32)(src)<<15) & 0x00008000)
#define ARM_RAM15_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields ARM_RAM14_ERRMask    */
#define ARM_RAM14_ERRMASK_WIDTH                                               1
#define ARM_RAM14_ERRMASK_SHIFT                                              14
#define ARM_RAM14_ERRMASK_MASK                                       0x00004000
#define ARM_RAM14_ERRMASK_RD(src)                    (((src) & 0x00004000)>>14)
#define ARM_RAM14_ERRMASK_WR(src)               (((u32)(src)<<14) & 0x00004000)
#define ARM_RAM14_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields ARM_RAM13_ERRMask    */
#define ARM_RAM13_ERRMASK_WIDTH                                               1
#define ARM_RAM13_ERRMASK_SHIFT                                              13
#define ARM_RAM13_ERRMASK_MASK                                       0x00002000
#define ARM_RAM13_ERRMASK_RD(src)                    (((src) & 0x00002000)>>13)
#define ARM_RAM13_ERRMASK_WR(src)               (((u32)(src)<<13) & 0x00002000)
#define ARM_RAM13_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields ARM_RAM12_ERRMask    */
#define ARM_RAM12_ERRMASK_WIDTH                                               1
#define ARM_RAM12_ERRMASK_SHIFT                                              12
#define ARM_RAM12_ERRMASK_MASK                                       0x00001000
#define ARM_RAM12_ERRMASK_RD(src)                    (((src) & 0x00001000)>>12)
#define ARM_RAM12_ERRMASK_WR(src)               (((u32)(src)<<12) & 0x00001000)
#define ARM_RAM12_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields ARM_RAM11_ERRMask    */
#define ARM_RAM11_ERRMASK_WIDTH                                               1
#define ARM_RAM11_ERRMASK_SHIFT                                              11
#define ARM_RAM11_ERRMASK_MASK                                       0x00000800
#define ARM_RAM11_ERRMASK_RD(src)                    (((src) & 0x00000800)>>11)
#define ARM_RAM11_ERRMASK_WR(src)               (((u32)(src)<<11) & 0x00000800)
#define ARM_RAM11_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields ARM_RAM10_ERRMask    */
#define ARM_RAM10_ERRMASK_WIDTH                                               1
#define ARM_RAM10_ERRMASK_SHIFT                                              10
#define ARM_RAM10_ERRMASK_MASK                                       0x00000400
#define ARM_RAM10_ERRMASK_RD(src)                    (((src) & 0x00000400)>>10)
#define ARM_RAM10_ERRMASK_WR(src)               (((u32)(src)<<10) & 0x00000400)
#define ARM_RAM10_ERRMASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields ARM_RAM9_ERRMask    */
#define ARM_RAM9_ERRMASK_WIDTH                                                1
#define ARM_RAM9_ERRMASK_SHIFT                                                9
#define ARM_RAM9_ERRMASK_MASK                                        0x00000200
#define ARM_RAM9_ERRMASK_RD(src)                      (((src) & 0x00000200)>>9)
#define ARM_RAM9_ERRMASK_WR(src)                 (((u32)(src)<<9) & 0x00000200)
#define ARM_RAM9_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields ARM_RAM8_ERRMask    */
#define ARM_RAM8_ERRMASK_WIDTH                                                1
#define ARM_RAM8_ERRMASK_SHIFT                                                8
#define ARM_RAM8_ERRMASK_MASK                                        0x00000100
#define ARM_RAM8_ERRMASK_RD(src)                      (((src) & 0x00000100)>>8)
#define ARM_RAM8_ERRMASK_WR(src)                 (((u32)(src)<<8) & 0x00000100)
#define ARM_RAM8_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields ARM_RAM7_ERRMask    */
#define ARM_RAM7_ERRMASK_WIDTH                                                1
#define ARM_RAM7_ERRMASK_SHIFT                                                7
#define ARM_RAM7_ERRMASK_MASK                                        0x00000080
#define ARM_RAM7_ERRMASK_RD(src)                      (((src) & 0x00000080)>>7)
#define ARM_RAM7_ERRMASK_WR(src)                 (((u32)(src)<<7) & 0x00000080)
#define ARM_RAM7_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields ARM_RAM6_ERRMask    */
#define ARM_RAM6_ERRMASK_WIDTH                                                1
#define ARM_RAM6_ERRMASK_SHIFT                                                6
#define ARM_RAM6_ERRMASK_MASK                                        0x00000040
#define ARM_RAM6_ERRMASK_RD(src)                      (((src) & 0x00000040)>>6)
#define ARM_RAM6_ERRMASK_WR(src)                 (((u32)(src)<<6) & 0x00000040)
#define ARM_RAM6_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields ARM_RAM5_ERRMask    */
#define ARM_RAM5_ERRMASK_WIDTH                                                1
#define ARM_RAM5_ERRMASK_SHIFT                                                5
#define ARM_RAM5_ERRMASK_MASK                                        0x00000020
#define ARM_RAM5_ERRMASK_RD(src)                      (((src) & 0x00000020)>>5)
#define ARM_RAM5_ERRMASK_WR(src)                 (((u32)(src)<<5) & 0x00000020)
#define ARM_RAM5_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields ARM_RAM4_ERRMask    */
#define ARM_RAM4_ERRMASK_WIDTH                                                1
#define ARM_RAM4_ERRMASK_SHIFT                                                4
#define ARM_RAM4_ERRMASK_MASK                                        0x00000010
#define ARM_RAM4_ERRMASK_RD(src)                      (((src) & 0x00000010)>>4)
#define ARM_RAM4_ERRMASK_WR(src)                 (((u32)(src)<<4) & 0x00000010)
#define ARM_RAM4_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields ARM_RAM3_ERRMask    */
#define ARM_RAM3_ERRMASK_WIDTH                                                1
#define ARM_RAM3_ERRMASK_SHIFT                                                3
#define ARM_RAM3_ERRMASK_MASK                                        0x00000008
#define ARM_RAM3_ERRMASK_RD(src)                      (((src) & 0x00000008)>>3)
#define ARM_RAM3_ERRMASK_WR(src)                 (((u32)(src)<<3) & 0x00000008)
#define ARM_RAM3_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields ARM_RAM2_ERRMask    */
#define ARM_RAM2_ERRMASK_WIDTH                                                1
#define ARM_RAM2_ERRMASK_SHIFT                                                2
#define ARM_RAM2_ERRMASK_MASK                                        0x00000004
#define ARM_RAM2_ERRMASK_RD(src)                      (((src) & 0x00000004)>>2)
#define ARM_RAM2_ERRMASK_WR(src)                 (((u32)(src)<<2) & 0x00000004)
#define ARM_RAM2_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields ARM_RAM1_ERRMask    */
#define ARM_RAM1_ERRMASK_WIDTH                                                1
#define ARM_RAM1_ERRMASK_SHIFT                                                1
#define ARM_RAM1_ERRMASK_MASK                                        0x00000002
#define ARM_RAM1_ERRMASK_RD(src)                      (((src) & 0x00000002)>>1)
#define ARM_RAM1_ERRMASK_WR(src)                 (((u32)(src)<<1) & 0x00000002)
#define ARM_RAM1_ERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields ARM_RAM0_ERRMask    */
#define ARM_RAM0_ERRMASK_WIDTH                                                1
#define ARM_RAM0_ERRMASK_SHIFT                                                0
#define ARM_RAM0_ERRMASK_MASK                                        0x00000001
#define ARM_RAM0_ERRMASK_RD(src)                         (((src) & 0x00000001))
#define ARM_RAM0_ERRMASK_WR(src)                    (((u32)(src)) & 0x00000001)
#define ARM_RAM0_ERRMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_ERR_INT_MASK	*/ 
/*	 Fields IIC0	 */
#define IIC0_WIDTH                                                            1
#define IIC0_SHIFT                                                           27
#define IIC0_MASK                                                    0x08000000
#define IIC0_RD(src)                                 (((src) & 0x08000000)>>27)
#define IIC0_WR(src)                            (((u32)(src)<<27) & 0x08000000)
#define IIC0_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields IIC1	 */
#define IIC1_WIDTH                                                            1
#define IIC1_SHIFT                                                           26
#define IIC1_MASK                                                    0x04000000
#define IIC1_RD(src)                                 (((src) & 0x04000000)>>26)
#define IIC1_WR(src)                            (((u32)(src)<<26) & 0x04000000)
#define IIC1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields CRDMA	 */
#define CRDMA_WIDTH                                                           1
#define CRDMA_SHIFT                                                          25
#define CRDMA_MASK                                                   0x02000000
#define CRDMA_RD(src)                                (((src) & 0x02000000)>>25)
#define CRDMA_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define CRDMA_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields RTC	 */
#define REGSPEC_RTC_F4_WIDTH                                                  1
#define REGSPEC_RTC_F4_SHIFT                                                 24
#define REGSPEC_RTC_F4_MASK                                          0x01000000
#define REGSPEC_RTC_F4_RD(src)                       (((src) & 0x01000000)>>24)
#define REGSPEC_RTC_F4_WR(src)                  (((u32)(src)<<24) & 0x01000000)
#define REGSPEC_RTC_F4_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields PKP_SLVERR	 */
#define PKP_SLVERR_WIDTH                                                      1
#define PKP_SLVERR_SHIFT                                                     23
#define PKP_SLVERR_MASK                                              0x00800000
#define PKP_SLVERR_RD(src)                           (((src) & 0x00800000)>>23)
#define PKP_SLVERR_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define PKP_SLVERR_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields TRNG_ALARM	 */
#define TRNG_ALARM_WIDTH                                                      1
#define TRNG_ALARM_SHIFT                                                     22
#define TRNG_ALARM_MASK                                              0x00400000
#define TRNG_ALARM_RD(src)                           (((src) & 0x00400000)>>22)
#define TRNG_ALARM_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define TRNG_ALARM_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields TRNG	 */
#define TRNG_WIDTH                                                            1
#define TRNG_SHIFT                                                           21
#define TRNG_MASK                                                    0x00200000
#define TRNG_RD(src)                                 (((src) & 0x00200000)>>21)
#define TRNG_WR(src)                            (((u32)(src)<<21) & 0x00200000)
#define TRNG_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields PKA	 */
#define PKA_WIDTH                                                             3
#define PKA_SHIFT                                                            18
#define PKA_MASK                                                     0x001c0000
#define PKA_RD(src)                                  (((src) & 0x001c0000)>>18)
#define PKA_WR(src)                             (((u32)(src)<<18) & 0x001c0000)
#define PKA_SET(dst,src) \
                      (((dst) & ~0x001c0000) | (((u32)(src)<<18) & 0x001c0000))
/*	 Fields AXI_SLVERR	 */
#define AXI_SLVERR_F1_WIDTH                                                   1
#define AXI_SLVERR_F1_SHIFT                                                  17
#define AXI_SLVERR_F1_MASK                                           0x00020000
#define AXI_SLVERR_F1_RD(src)                        (((src) & 0x00020000)>>17)
#define AXI_SLVERR_F1_WR(src)                   (((u32)(src)<<17) & 0x00020000)
#define AXI_SLVERR_F1_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields PKA_PROG_RAM_ERR	 */
#define PKA_PROG_RAM_ERR_F1_WIDTH                                             1
#define PKA_PROG_RAM_ERR_F1_SHIFT                                            16
#define PKA_PROG_RAM_ERR_F1_MASK                                     0x00010000
#define PKA_PROG_RAM_ERR_F1_RD(src)                  (((src) & 0x00010000)>>16)
#define PKA_PROG_RAM_ERR_F1_WR(src)             (((u32)(src)<<16) & 0x00010000)
#define PKA_PROG_RAM_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ARM_RAM15_ERR	 */
#define ARM_RAM15_ERR_F1_WIDTH                                                1
#define ARM_RAM15_ERR_F1_SHIFT                                               15
#define ARM_RAM15_ERR_F1_MASK                                        0x00008000
#define ARM_RAM15_ERR_F1_RD(src)                     (((src) & 0x00008000)>>15)
#define ARM_RAM15_ERR_F1_WR(src)                (((u32)(src)<<15) & 0x00008000)
#define ARM_RAM15_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields ARM_RAM14_ERR	 */
#define ARM_RAM14_ERR_F1_WIDTH                                                1
#define ARM_RAM14_ERR_F1_SHIFT                                               14
#define ARM_RAM14_ERR_F1_MASK                                        0x00004000
#define ARM_RAM14_ERR_F1_RD(src)                     (((src) & 0x00004000)>>14)
#define ARM_RAM14_ERR_F1_WR(src)                (((u32)(src)<<14) & 0x00004000)
#define ARM_RAM14_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields ARM_RAM13_ERR	 */
#define ARM_RAM13_ERR_F1_WIDTH                                                1
#define ARM_RAM13_ERR_F1_SHIFT                                               13
#define ARM_RAM13_ERR_F1_MASK                                        0x00002000
#define ARM_RAM13_ERR_F1_RD(src)                     (((src) & 0x00002000)>>13)
#define ARM_RAM13_ERR_F1_WR(src)                (((u32)(src)<<13) & 0x00002000)
#define ARM_RAM13_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields ARM_RAM12_ERR	 */
#define ARM_RAM12_ERR_F1_WIDTH                                                1
#define ARM_RAM12_ERR_F1_SHIFT                                               12
#define ARM_RAM12_ERR_F1_MASK                                        0x00001000
#define ARM_RAM12_ERR_F1_RD(src)                     (((src) & 0x00001000)>>12)
#define ARM_RAM12_ERR_F1_WR(src)                (((u32)(src)<<12) & 0x00001000)
#define ARM_RAM12_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields ARM_RAM11_ERR	 */
#define ARM_RAM11_ERR_F1_WIDTH                                                1
#define ARM_RAM11_ERR_F1_SHIFT                                               11
#define ARM_RAM11_ERR_F1_MASK                                        0x00000800
#define ARM_RAM11_ERR_F1_RD(src)                     (((src) & 0x00000800)>>11)
#define ARM_RAM11_ERR_F1_WR(src)                (((u32)(src)<<11) & 0x00000800)
#define ARM_RAM11_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields ARM_RAM10_ERR	 */
#define ARM_RAM10_ERR_F1_WIDTH                                                1
#define ARM_RAM10_ERR_F1_SHIFT                                               10
#define ARM_RAM10_ERR_F1_MASK                                        0x00000400
#define ARM_RAM10_ERR_F1_RD(src)                     (((src) & 0x00000400)>>10)
#define ARM_RAM10_ERR_F1_WR(src)                (((u32)(src)<<10) & 0x00000400)
#define ARM_RAM10_ERR_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields ARM_RAM9_ERR	 */
#define ARM_RAM9_ERR_F1_WIDTH                                                 1
#define ARM_RAM9_ERR_F1_SHIFT                                                 9
#define ARM_RAM9_ERR_F1_MASK                                         0x00000200
#define ARM_RAM9_ERR_F1_RD(src)                       (((src) & 0x00000200)>>9)
#define ARM_RAM9_ERR_F1_WR(src)                  (((u32)(src)<<9) & 0x00000200)
#define ARM_RAM9_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ARM_RAM8_ERR	 */
#define ARM_RAM8_ERR_F1_WIDTH                                                 1
#define ARM_RAM8_ERR_F1_SHIFT                                                 8
#define ARM_RAM8_ERR_F1_MASK                                         0x00000100
#define ARM_RAM8_ERR_F1_RD(src)                       (((src) & 0x00000100)>>8)
#define ARM_RAM8_ERR_F1_WR(src)                  (((u32)(src)<<8) & 0x00000100)
#define ARM_RAM8_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ARM_RAM7_ERR	 */
#define ARM_RAM7_ERR_F1_WIDTH                                                 1
#define ARM_RAM7_ERR_F1_SHIFT                                                 7
#define ARM_RAM7_ERR_F1_MASK                                         0x00000080
#define ARM_RAM7_ERR_F1_RD(src)                       (((src) & 0x00000080)>>7)
#define ARM_RAM7_ERR_F1_WR(src)                  (((u32)(src)<<7) & 0x00000080)
#define ARM_RAM7_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields ARM_RAM6_ERR	 */
#define ARM_RAM6_ERR_F1_WIDTH                                                 1
#define ARM_RAM6_ERR_F1_SHIFT                                                 6
#define ARM_RAM6_ERR_F1_MASK                                         0x00000040
#define ARM_RAM6_ERR_F1_RD(src)                       (((src) & 0x00000040)>>6)
#define ARM_RAM6_ERR_F1_WR(src)                  (((u32)(src)<<6) & 0x00000040)
#define ARM_RAM6_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ARM_RAM5_ERR	 */
#define ARM_RAM5_ERR_F1_WIDTH                                                 1
#define ARM_RAM5_ERR_F1_SHIFT                                                 5
#define ARM_RAM5_ERR_F1_MASK                                         0x00000020
#define ARM_RAM5_ERR_F1_RD(src)                       (((src) & 0x00000020)>>5)
#define ARM_RAM5_ERR_F1_WR(src)                  (((u32)(src)<<5) & 0x00000020)
#define ARM_RAM5_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ARM_RAM4_ERR	 */
#define ARM_RAM4_ERR_F1_WIDTH                                                 1
#define ARM_RAM4_ERR_F1_SHIFT                                                 4
#define ARM_RAM4_ERR_F1_MASK                                         0x00000010
#define ARM_RAM4_ERR_F1_RD(src)                       (((src) & 0x00000010)>>4)
#define ARM_RAM4_ERR_F1_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define ARM_RAM4_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ARM_RAM3_ERR	 */
#define ARM_RAM3_ERR_F1_WIDTH                                                 1
#define ARM_RAM3_ERR_F1_SHIFT                                                 3
#define ARM_RAM3_ERR_F1_MASK                                         0x00000008
#define ARM_RAM3_ERR_F1_RD(src)                       (((src) & 0x00000008)>>3)
#define ARM_RAM3_ERR_F1_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define ARM_RAM3_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ARM_RAM2_ERR	 */
#define ARM_RAM2_ERR_F1_WIDTH                                                 1
#define ARM_RAM2_ERR_F1_SHIFT                                                 2
#define ARM_RAM2_ERR_F1_MASK                                         0x00000004
#define ARM_RAM2_ERR_F1_RD(src)                       (((src) & 0x00000004)>>2)
#define ARM_RAM2_ERR_F1_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define ARM_RAM2_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ARM_RAM1_ERR	 */
#define ARM_RAM1_ERR_F1_WIDTH                                                 1
#define ARM_RAM1_ERR_F1_SHIFT                                                 1
#define ARM_RAM1_ERR_F1_MASK                                         0x00000002
#define ARM_RAM1_ERR_F1_RD(src)                       (((src) & 0x00000002)>>1)
#define ARM_RAM1_ERR_F1_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define ARM_RAM1_ERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ARM_RAM0_ERR	 */
#define ARM_RAM0_ERR_F1_WIDTH                                                 1
#define ARM_RAM0_ERR_F1_SHIFT                                                 0
#define ARM_RAM0_ERR_F1_MASK                                         0x00000001
#define ARM_RAM0_ERR_F1_RD(src)                          (((src) & 0x00000001))
#define ARM_RAM0_ERR_F1_WR(src)                     (((u32)(src)) & 0x00000001)
#define ARM_RAM0_ERR_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_QMI_INTSTAT	*/ 
/*	 Fields QMI	 */
#define QMI_WIDTH                                                             1
#define QMI_SHIFT                                                            31
#define QMI_MASK                                                     0x80000000
#define QMI_RD(src)                                  (((src) & 0x80000000)>>31)
#define QMI_WR(src)                             (((u32)(src)<<31) & 0x80000000)
#define QMI_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields WQ_AVAIL	 */
#define WQ_AVAIL_WIDTH                                                        6
#define WQ_AVAIL_SHIFT                                                       24
#define WQ_AVAIL_MASK                                                0x3f000000
#define WQ_AVAIL_RD(src)                             (((src) & 0x3f000000)>>24)
#define WQ_AVAIL_WR(src)                        (((u32)(src)<<24) & 0x3f000000)
#define WQ_AVAIL_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*	 Fields FP_AVAIL	 */
#define FP_AVAIL_WIDTH                                                       20
#define FP_AVAIL_SHIFT                                                        0
#define FP_AVAIL_MASK                                                0x000fffff
#define FP_AVAIL_RD(src)                                 (((src) & 0x000fffff))
#define FP_AVAIL_WR(src)                            (((u32)(src)) & 0x000fffff)
#define FP_AVAIL_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register MPA_QMI_INTSTATMask	*/
/*    Mask Register Fields QMIMask    */
#define QMIMASK_WIDTH                                                         1
#define QMIMASK_SHIFT                                                        31
#define QMIMASK_MASK                                                 0x80000000
#define QMIMASK_RD(src)                              (((src) & 0x80000000)>>31)
#define QMIMASK_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define QMIMASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields WQ_AVAILMask    */
#define WQ_AVAILMASK_WIDTH                                                    6
#define WQ_AVAILMASK_SHIFT                                                   24
#define WQ_AVAILMASK_MASK                                            0x3f000000
#define WQ_AVAILMASK_RD(src)                         (((src) & 0x3f000000)>>24)
#define WQ_AVAILMASK_WR(src)                    (((u32)(src)<<24) & 0x3f000000)
#define WQ_AVAILMASK_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*    Mask Register Fields FP_AVAILMask    */
#define FP_AVAILMASK_WIDTH                                                   20
#define FP_AVAILMASK_SHIFT                                                    0
#define FP_AVAILMASK_MASK                                            0x000fffff
#define FP_AVAILMASK_RD(src)                             (((src) & 0x000fffff))
#define FP_AVAILMASK_WR(src)                        (((u32)(src)) & 0x000fffff)
#define FP_AVAILMASK_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register MPA_SAB_INTSTAT	*/ 
/*	 Fields RID	 */
#define RID_WIDTH                                                            17
#define RID_SHIFT                                                             0
#define RID_MASK                                                     0x0001ffff
#define RID_RD(src)                                      (((src) & 0x0001ffff))
#define RID_WR(src)                                 (((u32)(src)) & 0x0001ffff)
#define RID_SET(dst,src) (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register MPA_SAB_INTSTATMask	*/
/*    Mask Register Fields RIDMask    */
#define RIDMASK_WIDTH                                                        17
#define RIDMASK_SHIFT                                                         0
#define RIDMASK_MASK                                                 0x0001ffff
#define RIDMASK_RD(src)                                  (((src) & 0x0001ffff))
#define RIDMASK_WR(src)                             (((u32)(src)) & 0x0001ffff)
#define RIDMASK_SET(dst,src) \
                          (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register MPA_SCRATCH	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH_WIDTH                                                        32
#define SCRATCH_SHIFT                                                         0
#define SCRATCH_MASK                                                 0xffffffff
#define SCRATCH_RD(src)                                  (((src) & 0xffffffff))
#define SCRATCH_WR(src)                             (((u32)(src)) & 0xffffffff)
#define SCRATCH_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH1	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH1_F1_WIDTH                                                    32
#define SCRATCH1_F1_SHIFT                                                     0
#define SCRATCH1_F1_MASK                                             0xffffffff
#define SCRATCH1_F1_RD(src)                              (((src) & 0xffffffff))
#define SCRATCH1_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define SCRATCH1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SCRATCH2	*/ 
/*	 Fields SCRATCH	 */
#define SCRATCH2_F1_WIDTH                                                    32
#define SCRATCH2_F1_SHIFT                                                     0
#define SCRATCH2_F1_MASK                                             0xffffffff
#define SCRATCH2_F1_RD(src)                              (((src) & 0xffffffff))
#define SCRATCH2_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define SCRATCH2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_SLP_TMR	*/ 
/*	 Fields DS_DEACT	 */
#define DS_DEACT_WIDTH                                                        1
#define DS_DEACT_SHIFT                                                       31
#define DS_DEACT_MASK                                                0x80000000
#define DS_DEACT_RD(src)                             (((src) & 0x80000000)>>31)
#define DS_DEACT_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define DS_DEACT_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SLP_TMR	 */
#define SLP_TMR_WIDTH                                                        16
#define SLP_TMR_SHIFT                                                         0
#define SLP_TMR_MASK                                                 0x0000ffff
#define SLP_TMR_RD(src)                                  (((src) & 0x0000ffff))
#define SLP_TMR_WR(src)                             (((u32)(src)) & 0x0000ffff)
#define SLP_TMR_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_GPIO_DS_IOCTL0	*/ 
/*	 Fields GPIO_DS_SRE	 */
#define GPIO_DS_SRE0_WIDTH                                                    4
#define GPIO_DS_SRE0_SHIFT                                                   16
#define GPIO_DS_SRE0_MASK                                            0x000f0000
#define GPIO_DS_SRE0_RD(src)                         (((src) & 0x000f0000)>>16)
#define GPIO_DS_SRE0_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define GPIO_DS_SRE0_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields GPIO_DS_HYTS	 */
#define GPIO_DS_HYTS0_WIDTH                                                   4
#define GPIO_DS_HYTS0_SHIFT                                                  12
#define GPIO_DS_HYTS0_MASK                                           0x0000f000
#define GPIO_DS_HYTS0_RD(src)                        (((src) & 0x0000f000)>>12)
#define GPIO_DS_HYTS0_WR(src)                   (((u32)(src)<<12) & 0x0000f000)
#define GPIO_DS_HYTS0_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields GPIO_DS_PULLUP	 */
#define GPIO_DS_PULLUP0_WIDTH                                                 4
#define GPIO_DS_PULLUP0_SHIFT                                                 8
#define GPIO_DS_PULLUP0_MASK                                         0x00000f00
#define GPIO_DS_PULLUP0_RD(src)                       (((src) & 0x00000f00)>>8)
#define GPIO_DS_PULLUP0_WR(src)                  (((u32)(src)<<8) & 0x00000f00)
#define GPIO_DS_PULLUP0_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields GPIO_DS_PDWN	 */
#define GPIO_DS_PDWN0_WIDTH                                                   4
#define GPIO_DS_PDWN0_SHIFT                                                   4
#define GPIO_DS_PDWN0_MASK                                           0x000000f0
#define GPIO_DS_PDWN0_RD(src)                         (((src) & 0x000000f0)>>4)
#define GPIO_DS_PDWN0_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define GPIO_DS_PDWN0_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields GPIO_DS_PWROK	 */
#define GPIO_DS_PWROK0_WIDTH                                                  4
#define GPIO_DS_PWROK0_SHIFT                                                  0
#define GPIO_DS_PWROK0_MASK                                          0x0000000f
#define GPIO_DS_PWROK0_RD(src)                           (((src) & 0x0000000f))
#define GPIO_DS_PWROK0_WR(src)                      (((u32)(src)) & 0x0000000f)
#define GPIO_DS_PWROK0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_GPIO_DS_IOCTL1	*/ 
/*	 Fields GPIO_DS_SRE	 */
#define GPIO_DS_SRE1_WIDTH                                                    4
#define GPIO_DS_SRE1_SHIFT                                                   16
#define GPIO_DS_SRE1_MASK                                            0x000f0000
#define GPIO_DS_SRE1_RD(src)                         (((src) & 0x000f0000)>>16)
#define GPIO_DS_SRE1_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define GPIO_DS_SRE1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields GPIO_DS_HYTS	 */
#define GPIO_DS_HYTS1_WIDTH                                                   4
#define GPIO_DS_HYTS1_SHIFT                                                  12
#define GPIO_DS_HYTS1_MASK                                           0x0000f000
#define GPIO_DS_HYTS1_RD(src)                        (((src) & 0x0000f000)>>12)
#define GPIO_DS_HYTS1_WR(src)                   (((u32)(src)<<12) & 0x0000f000)
#define GPIO_DS_HYTS1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields GPIO_DS_PULLUP	 */
#define GPIO_DS_PULLUP1_WIDTH                                                 4
#define GPIO_DS_PULLUP1_SHIFT                                                 8
#define GPIO_DS_PULLUP1_MASK                                         0x00000f00
#define GPIO_DS_PULLUP1_RD(src)                       (((src) & 0x00000f00)>>8)
#define GPIO_DS_PULLUP1_WR(src)                  (((u32)(src)<<8) & 0x00000f00)
#define GPIO_DS_PULLUP1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields GPIO_DS_PDWN	 */
#define GPIO_DS_PDWN1_WIDTH                                                   4
#define GPIO_DS_PDWN1_SHIFT                                                   4
#define GPIO_DS_PDWN1_MASK                                           0x000000f0
#define GPIO_DS_PDWN1_RD(src)                         (((src) & 0x000000f0)>>4)
#define GPIO_DS_PDWN1_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define GPIO_DS_PDWN1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields GPIO_DS_PWROK	 */
#define GPIO_DS_PWROK1_WIDTH                                                  4
#define GPIO_DS_PWROK1_SHIFT                                                  0
#define GPIO_DS_PWROK1_MASK                                          0x0000000f
#define GPIO_DS_PWROK1_RD(src)                           (((src) & 0x0000000f))
#define GPIO_DS_PWROK1_WR(src)                      (((u32)(src)) & 0x0000000f)
#define GPIO_DS_PWROK1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_GPIO_DS_IOCTL2	*/ 
/*	 Fields GPIO_DS_SRE	 */
#define GPIO_DS_SRE2_WIDTH                                                    4
#define GPIO_DS_SRE2_SHIFT                                                   16
#define GPIO_DS_SRE2_MASK                                            0x000f0000
#define GPIO_DS_SRE2_RD(src)                         (((src) & 0x000f0000)>>16)
#define GPIO_DS_SRE2_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define GPIO_DS_SRE2_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields GPIO_DS_HYTS	 */
#define GPIO_DS_HYTS2_WIDTH                                                   4
#define GPIO_DS_HYTS2_SHIFT                                                  12
#define GPIO_DS_HYTS2_MASK                                           0x0000f000
#define GPIO_DS_HYTS2_RD(src)                        (((src) & 0x0000f000)>>12)
#define GPIO_DS_HYTS2_WR(src)                   (((u32)(src)<<12) & 0x0000f000)
#define GPIO_DS_HYTS2_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields GPIO_DS_PULLUP	 */
#define GPIO_DS_PULLUP2_WIDTH                                                 4
#define GPIO_DS_PULLUP2_SHIFT                                                 8
#define GPIO_DS_PULLUP2_MASK                                         0x00000f00
#define GPIO_DS_PULLUP2_RD(src)                       (((src) & 0x00000f00)>>8)
#define GPIO_DS_PULLUP2_WR(src)                  (((u32)(src)<<8) & 0x00000f00)
#define GPIO_DS_PULLUP2_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields GPIO_DS_PDWN	 */
#define GPIO_DS_PDWN2_WIDTH                                                   4
#define GPIO_DS_PDWN2_SHIFT                                                   4
#define GPIO_DS_PDWN2_MASK                                           0x000000f0
#define GPIO_DS_PDWN2_RD(src)                         (((src) & 0x000000f0)>>4)
#define GPIO_DS_PDWN2_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define GPIO_DS_PDWN2_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields GPIO_DS_PWROK	 */
#define GPIO_DS_PWROK2_WIDTH                                                  4
#define GPIO_DS_PWROK2_SHIFT                                                  0
#define GPIO_DS_PWROK2_MASK                                          0x0000000f
#define GPIO_DS_PWROK2_RD(src)                           (((src) & 0x0000000f))
#define GPIO_DS_PWROK2_WR(src)                      (((u32)(src)) & 0x0000000f)
#define GPIO_DS_PWROK2_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_GPIO_DS_IOCTL3	*/ 
/*	 Fields GPIO_DS_SRE	 */
#define GPIO_DS_SRE3_WIDTH                                                    4
#define GPIO_DS_SRE3_SHIFT                                                   16
#define GPIO_DS_SRE3_MASK                                            0x000f0000
#define GPIO_DS_SRE3_RD(src)                         (((src) & 0x000f0000)>>16)
#define GPIO_DS_SRE3_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define GPIO_DS_SRE3_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields GPIO_DS_HYTS	 */
#define GPIO_DS_HYTS3_WIDTH                                                   4
#define GPIO_DS_HYTS3_SHIFT                                                  12
#define GPIO_DS_HYTS3_MASK                                           0x0000f000
#define GPIO_DS_HYTS3_RD(src)                        (((src) & 0x0000f000)>>12)
#define GPIO_DS_HYTS3_WR(src)                   (((u32)(src)<<12) & 0x0000f000)
#define GPIO_DS_HYTS3_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields GPIO_DS_PULLUP	 */
#define GPIO_DS_PULLUP3_WIDTH                                                 4
#define GPIO_DS_PULLUP3_SHIFT                                                 8
#define GPIO_DS_PULLUP3_MASK                                         0x00000f00
#define GPIO_DS_PULLUP3_RD(src)                       (((src) & 0x00000f00)>>8)
#define GPIO_DS_PULLUP3_WR(src)                  (((u32)(src)<<8) & 0x00000f00)
#define GPIO_DS_PULLUP3_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields GPIO_DS_PDWN	 */
#define GPIO_DS_PDWN3_WIDTH                                                   4
#define GPIO_DS_PDWN3_SHIFT                                                   4
#define GPIO_DS_PDWN3_MASK                                           0x000000f0
#define GPIO_DS_PDWN3_RD(src)                         (((src) & 0x000000f0)>>4)
#define GPIO_DS_PDWN3_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define GPIO_DS_PDWN3_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields GPIO_DS_PWROK	 */
#define GPIO_DS_PWROK3_WIDTH                                                  4
#define GPIO_DS_PWROK3_SHIFT                                                  0
#define GPIO_DS_PWROK3_MASK                                          0x0000000f
#define GPIO_DS_PWROK3_RD(src)                           (((src) & 0x0000000f))
#define GPIO_DS_PWROK3_WR(src)                      (((u32)(src)) & 0x0000000f)
#define GPIO_DS_PWROK3_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_GPIO_DS_IOCTL4	*/ 
/*	 Fields GPIO_DS_SRE	 */
#define GPIO_DS_SRE4_WIDTH                                                    4
#define GPIO_DS_SRE4_SHIFT                                                   16
#define GPIO_DS_SRE4_MASK                                            0x000f0000
#define GPIO_DS_SRE4_RD(src)                         (((src) & 0x000f0000)>>16)
#define GPIO_DS_SRE4_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define GPIO_DS_SRE4_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields GPIO_DS_HYTS	 */
#define GPIO_DS_HYTS4_WIDTH                                                   4
#define GPIO_DS_HYTS4_SHIFT                                                  12
#define GPIO_DS_HYTS4_MASK                                           0x0000f000
#define GPIO_DS_HYTS4_RD(src)                        (((src) & 0x0000f000)>>12)
#define GPIO_DS_HYTS4_WR(src)                   (((u32)(src)<<12) & 0x0000f000)
#define GPIO_DS_HYTS4_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields GPIO_DS_PULLUP	 */
#define GPIO_DS_PULLUP4_WIDTH                                                 4
#define GPIO_DS_PULLUP4_SHIFT                                                 8
#define GPIO_DS_PULLUP4_MASK                                         0x00000f00
#define GPIO_DS_PULLUP4_RD(src)                       (((src) & 0x00000f00)>>8)
#define GPIO_DS_PULLUP4_WR(src)                  (((u32)(src)<<8) & 0x00000f00)
#define GPIO_DS_PULLUP4_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields GPIO_DS_PDWN	 */
#define GPIO_DS_PDWN4_WIDTH                                                   4
#define GPIO_DS_PDWN4_SHIFT                                                   4
#define GPIO_DS_PDWN4_MASK                                           0x000000f0
#define GPIO_DS_PDWN4_RD(src)                         (((src) & 0x000000f0)>>4)
#define GPIO_DS_PDWN4_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define GPIO_DS_PDWN4_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields GPIO_DS_PWROK	 */
#define GPIO_DS_PWROK4_WIDTH                                                  4
#define GPIO_DS_PWROK4_SHIFT                                                  0
#define GPIO_DS_PWROK4_MASK                                          0x0000000f
#define GPIO_DS_PWROK4_RD(src)                           (((src) & 0x0000000f))
#define GPIO_DS_PWROK4_WR(src)                      (((u32)(src)) & 0x0000000f)
#define GPIO_DS_PWROK4_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_GPIO_DS_IOCTL5	*/ 
/*	 Fields GPIO_DS_SRE	 */
#define GPIO_DS_SRE5_WIDTH                                                    4
#define GPIO_DS_SRE5_SHIFT                                                   16
#define GPIO_DS_SRE5_MASK                                            0x000f0000
#define GPIO_DS_SRE5_RD(src)                         (((src) & 0x000f0000)>>16)
#define GPIO_DS_SRE5_WR(src)                    (((u32)(src)<<16) & 0x000f0000)
#define GPIO_DS_SRE5_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields GPIO_DS_HYTS	 */
#define GPIO_DS_HYTS5_WIDTH                                                   4
#define GPIO_DS_HYTS5_SHIFT                                                  12
#define GPIO_DS_HYTS5_MASK                                           0x0000f000
#define GPIO_DS_HYTS5_RD(src)                        (((src) & 0x0000f000)>>12)
#define GPIO_DS_HYTS5_WR(src)                   (((u32)(src)<<12) & 0x0000f000)
#define GPIO_DS_HYTS5_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields GPIO_DS_PULLUP	 */
#define GPIO_DS_PULLUP5_WIDTH                                                 4
#define GPIO_DS_PULLUP5_SHIFT                                                 8
#define GPIO_DS_PULLUP5_MASK                                         0x00000f00
#define GPIO_DS_PULLUP5_RD(src)                       (((src) & 0x00000f00)>>8)
#define GPIO_DS_PULLUP5_WR(src)                  (((u32)(src)<<8) & 0x00000f00)
#define GPIO_DS_PULLUP5_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields GPIO_DS_PDWN	 */
#define GPIO_DS_PDWN5_WIDTH                                                   4
#define GPIO_DS_PDWN5_SHIFT                                                   4
#define GPIO_DS_PDWN5_MASK                                           0x000000f0
#define GPIO_DS_PDWN5_RD(src)                         (((src) & 0x000000f0)>>4)
#define GPIO_DS_PDWN5_WR(src)                    (((u32)(src)<<4) & 0x000000f0)
#define GPIO_DS_PDWN5_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields GPIO_DS_PWROK	 */
#define GPIO_DS_PWROK5_WIDTH                                                  4
#define GPIO_DS_PWROK5_SHIFT                                                  0
#define GPIO_DS_PWROK5_MASK                                          0x0000000f
#define GPIO_DS_PWROK5_RD(src)                           (((src) & 0x0000000f))
#define GPIO_DS_PWROK5_WR(src)                      (((u32)(src)) & 0x0000000f)
#define GPIO_DS_PWROK5_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_ENET4_PWRGD_IOCTL	*/ 
/*	 Fields PMTMR_SRE	 */
#define PMTMR_SRE_WIDTH                                                       1
#define PMTMR_SRE_SHIFT                                                      28
#define PMTMR_SRE_MASK                                               0x10000000
#define PMTMR_SRE_RD(src)                            (((src) & 0x10000000)>>28)
#define PMTMR_SRE_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define PMTMR_SRE_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields PMTMR_HYTS	 */
#define PMTMR_HYTS_WIDTH                                                      1
#define PMTMR_HYTS_SHIFT                                                     27
#define PMTMR_HYTS_MASK                                              0x08000000
#define PMTMR_HYTS_RD(src)                           (((src) & 0x08000000)>>27)
#define PMTMR_HYTS_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define PMTMR_HYTS_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields PMTMR_PULLUP	 */
#define PMTMR_PULLUP_WIDTH                                                    1
#define PMTMR_PULLUP_SHIFT                                                   26
#define PMTMR_PULLUP_MASK                                            0x04000000
#define PMTMR_PULLUP_RD(src)                         (((src) & 0x04000000)>>26)
#define PMTMR_PULLUP_WR(src)                    (((u32)(src)<<26) & 0x04000000)
#define PMTMR_PULLUP_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields PMTMR_PDWN	 */
#define PMTMR_PDWN_WIDTH                                                      1
#define PMTMR_PDWN_SHIFT                                                     25
#define PMTMR_PDWN_MASK                                              0x02000000
#define PMTMR_PDWN_RD(src)                           (((src) & 0x02000000)>>25)
#define PMTMR_PDWN_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define PMTMR_PDWN_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields PMTMR_PWROK	 */
#define PMTMR_PWROK_WIDTH                                                     1
#define PMTMR_PWROK_SHIFT                                                    24
#define PMTMR_PWROK_MASK                                             0x01000000
#define PMTMR_PWROK_RD(src)                          (((src) & 0x01000000)>>24)
#define PMTMR_PWROK_WR(src)                     (((u32)(src)<<24) & 0x01000000)
#define PMTMR_PWROK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields ENET4_SRE	 */
#define ENET4_SRE_WIDTH                                                       1
#define ENET4_SRE_SHIFT                                                      20
#define ENET4_SRE_MASK                                               0x00100000
#define ENET4_SRE_RD(src)                            (((src) & 0x00100000)>>20)
#define ENET4_SRE_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define ENET4_SRE_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields ENET4_HYTS	 */
#define ENET4_HYTS_WIDTH                                                      1
#define ENET4_HYTS_SHIFT                                                     19
#define ENET4_HYTS_MASK                                              0x00080000
#define ENET4_HYTS_RD(src)                           (((src) & 0x00080000)>>19)
#define ENET4_HYTS_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define ENET4_HYTS_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields ENET4_PULLUP	 */
#define ENET4_PULLUP_WIDTH                                                    1
#define ENET4_PULLUP_SHIFT                                                   18
#define ENET4_PULLUP_MASK                                            0x00040000
#define ENET4_PULLUP_RD(src)                         (((src) & 0x00040000)>>18)
#define ENET4_PULLUP_WR(src)                    (((u32)(src)<<18) & 0x00040000)
#define ENET4_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields ENET4_PDWN	 */
#define ENET4_PDWN_WIDTH                                                      1
#define ENET4_PDWN_SHIFT                                                     17
#define ENET4_PDWN_MASK                                              0x00020000
#define ENET4_PDWN_RD(src)                           (((src) & 0x00020000)>>17)
#define ENET4_PDWN_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define ENET4_PDWN_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields ENET4_PWROK	 */
#define ENET4_PWROK_WIDTH                                                     1
#define ENET4_PWROK_SHIFT                                                    16
#define ENET4_PWROK_MASK                                             0x00010000
#define ENET4_PWROK_RD(src)                          (((src) & 0x00010000)>>16)
#define ENET4_PWROK_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ENET4_PWROK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields PSCTL_SRE	 */
#define PSCTL_SRE_WIDTH                                                       1
#define PSCTL_SRE_SHIFT                                                      12
#define PSCTL_SRE_MASK                                               0x00001000
#define PSCTL_SRE_RD(src)                            (((src) & 0x00001000)>>12)
#define PSCTL_SRE_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define PSCTL_SRE_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields PSCTL_HYTS	 */
#define PSCTL_HYTS_WIDTH                                                      1
#define PSCTL_HYTS_SHIFT                                                     11
#define PSCTL_HYTS_MASK                                              0x00000800
#define PSCTL_HYTS_RD(src)                           (((src) & 0x00000800)>>11)
#define PSCTL_HYTS_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define PSCTL_HYTS_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields PSCTL_PULLUP	 */
#define PSCTL_PULLUP_WIDTH                                                    1
#define PSCTL_PULLUP_SHIFT                                                   10
#define PSCTL_PULLUP_MASK                                            0x00000400
#define PSCTL_PULLUP_RD(src)                         (((src) & 0x00000400)>>10)
#define PSCTL_PULLUP_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define PSCTL_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields PSCTL_PDWN	 */
#define PSCTL_PDWN_WIDTH                                                      1
#define PSCTL_PDWN_SHIFT                                                      9
#define PSCTL_PDWN_MASK                                              0x00000200
#define PSCTL_PDWN_RD(src)                            (((src) & 0x00000200)>>9)
#define PSCTL_PDWN_WR(src)                       (((u32)(src)<<9) & 0x00000200)
#define PSCTL_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields PSCTL_PWROK	 */
#define PSCTL_PWROK_WIDTH                                                     1
#define PSCTL_PWROK_SHIFT                                                     8
#define PSCTL_PWROK_MASK                                             0x00000100
#define PSCTL_PWROK_RD(src)                           (((src) & 0x00000100)>>8)
#define PSCTL_PWROK_WR(src)                      (((u32)(src)<<8) & 0x00000100)
#define PSCTL_PWROK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields PWRGD_SRE	 */
#define PWRGD_SRE_WIDTH                                                       1
#define PWRGD_SRE_SHIFT                                                       4
#define PWRGD_SRE_MASK                                               0x00000010
#define PWRGD_SRE_RD(src)                             (((src) & 0x00000010)>>4)
#define PWRGD_SRE_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define PWRGD_SRE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields PWRGD_HYTS	 */
#define PWRGD_HYTS_WIDTH                                                      1
#define PWRGD_HYTS_SHIFT                                                      3
#define PWRGD_HYTS_MASK                                              0x00000008
#define PWRGD_HYTS_RD(src)                            (((src) & 0x00000008)>>3)
#define PWRGD_HYTS_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define PWRGD_HYTS_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields PWRGD_PULLUP	 */
#define PWRGD_PULLUP_WIDTH                                                    1
#define PWRGD_PULLUP_SHIFT                                                    2
#define PWRGD_PULLUP_MASK                                            0x00000004
#define PWRGD_PULLUP_RD(src)                          (((src) & 0x00000004)>>2)
#define PWRGD_PULLUP_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define PWRGD_PULLUP_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields PWRGD_PDWN	 */
#define PWRGD_PDWN_WIDTH                                                      1
#define PWRGD_PDWN_SHIFT                                                      1
#define PWRGD_PDWN_MASK                                              0x00000002
#define PWRGD_PDWN_RD(src)                            (((src) & 0x00000002)>>1)
#define PWRGD_PDWN_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define PWRGD_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PWRGD_PWROK	 */
#define PWRGD_PWROK_WIDTH                                                     1
#define PWRGD_PWROK_SHIFT                                                     0
#define PWRGD_PWROK_MASK                                             0x00000001
#define PWRGD_PWROK_RD(src)                              (((src) & 0x00000001))
#define PWRGD_PWROK_WR(src)                         (((u32)(src)) & 0x00000001)
#define PWRGD_PWROK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_IIC_SPI_IOCTL	*/ 
/*	 Fields SPI1_SRE	 */
#define SPI1_SRE_WIDTH                                                        1
#define SPI1_SRE_SHIFT                                                       28
#define SPI1_SRE_MASK                                                0x10000000
#define SPI1_SRE_RD(src)                             (((src) & 0x10000000)>>28)
#define SPI1_SRE_WR(src)                        (((u32)(src)<<28) & 0x10000000)
#define SPI1_SRE_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SPI1_HYTS	 */
#define SPI1_HYTS_WIDTH                                                       1
#define SPI1_HYTS_SHIFT                                                      27
#define SPI1_HYTS_MASK                                               0x08000000
#define SPI1_HYTS_RD(src)                            (((src) & 0x08000000)>>27)
#define SPI1_HYTS_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define SPI1_HYTS_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields SPI1_PULLUP	 */
#define SPI1_PULLUP_WIDTH                                                     1
#define SPI1_PULLUP_SHIFT                                                    26
#define SPI1_PULLUP_MASK                                             0x04000000
#define SPI1_PULLUP_RD(src)                          (((src) & 0x04000000)>>26)
#define SPI1_PULLUP_WR(src)                     (((u32)(src)<<26) & 0x04000000)
#define SPI1_PULLUP_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SPI1_PDWN	 */
#define SPI1_PDWN_WIDTH                                                       1
#define SPI1_PDWN_SHIFT                                                      25
#define SPI1_PDWN_MASK                                               0x02000000
#define SPI1_PDWN_RD(src)                            (((src) & 0x02000000)>>25)
#define SPI1_PDWN_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define SPI1_PDWN_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SPI1_PWROK	 */
#define SPI1_PWROK_WIDTH                                                      1
#define SPI1_PWROK_SHIFT                                                     24
#define SPI1_PWROK_MASK                                              0x01000000
#define SPI1_PWROK_RD(src)                           (((src) & 0x01000000)>>24)
#define SPI1_PWROK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define SPI1_PWROK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields SPI0_SRE	 */
#define SPI0_SRE_WIDTH                                                        1
#define SPI0_SRE_SHIFT                                                       20
#define SPI0_SRE_MASK                                                0x00100000
#define SPI0_SRE_RD(src)                             (((src) & 0x00100000)>>20)
#define SPI0_SRE_WR(src)                        (((u32)(src)<<20) & 0x00100000)
#define SPI0_SRE_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields SPI0_HYTS	 */
#define SPI0_HYTS_WIDTH                                                       1
#define SPI0_HYTS_SHIFT                                                      19
#define SPI0_HYTS_MASK                                               0x00080000
#define SPI0_HYTS_RD(src)                            (((src) & 0x00080000)>>19)
#define SPI0_HYTS_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define SPI0_HYTS_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SPI0_PULLUP	 */
#define SPI0_PULLUP_WIDTH                                                     1
#define SPI0_PULLUP_SHIFT                                                    18
#define SPI0_PULLUP_MASK                                             0x00040000
#define SPI0_PULLUP_RD(src)                          (((src) & 0x00040000)>>18)
#define SPI0_PULLUP_WR(src)                     (((u32)(src)<<18) & 0x00040000)
#define SPI0_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields SPI0_PDWN	 */
#define SPI0_PDWN_WIDTH                                                       1
#define SPI0_PDWN_SHIFT                                                      17
#define SPI0_PDWN_MASK                                               0x00020000
#define SPI0_PDWN_RD(src)                            (((src) & 0x00020000)>>17)
#define SPI0_PDWN_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define SPI0_PDWN_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields SPI0_PWROK	 */
#define SPI0_PWROK_WIDTH                                                      1
#define SPI0_PWROK_SHIFT                                                     16
#define SPI0_PWROK_MASK                                              0x00010000
#define SPI0_PWROK_RD(src)                           (((src) & 0x00010000)>>16)
#define SPI0_PWROK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define SPI0_PWROK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))

/*	Register MPA_SDIO_EBUS_IOCTL	*/ 
/*	 Fields SDIO_SRE	 */
#define SDIO_SRE_WIDTH                                                        1
#define SDIO_SRE_SHIFT                                                       12
#define SDIO_SRE_MASK                                                0x00001000
#define SDIO_SRE_RD(src)                             (((src) & 0x00001000)>>12)
#define SDIO_SRE_WR(src)                        (((u32)(src)<<12) & 0x00001000)
#define SDIO_SRE_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SDIO_HYTS	 */
#define SDIO_HYTS_WIDTH                                                       1
#define SDIO_HYTS_SHIFT                                                      11
#define SDIO_HYTS_MASK                                               0x00000800
#define SDIO_HYTS_RD(src)                            (((src) & 0x00000800)>>11)
#define SDIO_HYTS_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define SDIO_HYTS_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SDIO_PULLUP	 */
#define SDIO_PULLUP_WIDTH                                                     1
#define SDIO_PULLUP_SHIFT                                                    10
#define SDIO_PULLUP_MASK                                             0x00000400
#define SDIO_PULLUP_RD(src)                          (((src) & 0x00000400)>>10)
#define SDIO_PULLUP_WR(src)                     (((u32)(src)<<10) & 0x00000400)
#define SDIO_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SDIO_PDWN	 */
#define SDIO_PDWN_WIDTH                                                       1
#define SDIO_PDWN_SHIFT                                                       9
#define SDIO_PDWN_MASK                                               0x00000200
#define SDIO_PDWN_RD(src)                             (((src) & 0x00000200)>>9)
#define SDIO_PDWN_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define SDIO_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SDIO_PWROK	 */
#define SDIO_PWROK_WIDTH                                                      1
#define SDIO_PWROK_SHIFT                                                      8
#define SDIO_PWROK_MASK                                              0x00000100
#define SDIO_PWROK_RD(src)                            (((src) & 0x00000100)>>8)
#define SDIO_PWROK_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define SDIO_PWROK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))

/*	Register MPA_UART_SPARE_IOCTL	*/ 
/*	 Fields UART_SRE	 */
#define UART_SRE_WIDTH                                                        1
#define UART_SRE_SHIFT                                                       13
#define UART_SRE_MASK                                                0x00002000
#define UART_SRE_RD(src)                             (((src) & 0x00002000)>>13)
#define UART_SRE_WR(src)                        (((u32)(src)<<13) & 0x00002000)
#define UART_SRE_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields UART_HYTS	 */
#define UART_HYTS_WIDTH                                                       1
#define UART_HYTS_SHIFT                                                      12
#define UART_HYTS_MASK                                               0x00001000
#define UART_HYTS_RD(src)                            (((src) & 0x00001000)>>12)
#define UART_HYTS_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define UART_HYTS_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields UART_PULLUP	 */
#define UART_PULLUP_WIDTH                                                     1
#define UART_PULLUP_SHIFT                                                    11
#define UART_PULLUP_MASK                                             0x00000800
#define UART_PULLUP_RD(src)                          (((src) & 0x00000800)>>11)
#define UART_PULLUP_WR(src)                     (((u32)(src)<<11) & 0x00000800)
#define UART_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields UART_PULLDN	 */
#define UART_PULLDN_WIDTH                                                     1
#define UART_PULLDN_SHIFT                                                    10
#define UART_PULLDN_MASK                                             0x00000400
#define UART_PULLDN_RD(src)                          (((src) & 0x00000400)>>10)
#define UART_PULLDN_WR(src)                     (((u32)(src)<<10) & 0x00000400)
#define UART_PULLDN_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields UART_PDWN	 */
#define UART_PDWN_WIDTH                                                       1
#define UART_PDWN_SHIFT                                                       9
#define UART_PDWN_MASK                                               0x00000200
#define UART_PDWN_RD(src)                             (((src) & 0x00000200)>>9)
#define UART_PDWN_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define UART_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields UART_PWROK	 */
#define UART_PWROK_WIDTH                                                      1
#define UART_PWROK_SHIFT                                                      8
#define UART_PWROK_MASK                                              0x00000100
#define UART_PWROK_RD(src)                            (((src) & 0x00000100)>>8)
#define UART_PWROK_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define UART_PWROK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SPARE_SRE	 */
#define SPARE_SRE_WIDTH                                                       1
#define SPARE_SRE_SHIFT                                                       4
#define SPARE_SRE_MASK                                               0x00000010
#define SPARE_SRE_RD(src)                             (((src) & 0x00000010)>>4)
#define SPARE_SRE_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define SPARE_SRE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields SPARE_HYTS	 */
#define SPARE_HYTS_WIDTH                                                      1
#define SPARE_HYTS_SHIFT                                                      3
#define SPARE_HYTS_MASK                                              0x00000008
#define SPARE_HYTS_RD(src)                            (((src) & 0x00000008)>>3)
#define SPARE_HYTS_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define SPARE_HYTS_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SPARE_PULLUP	 */
#define SPARE_PULLUP_WIDTH                                                    1
#define SPARE_PULLUP_SHIFT                                                    2
#define SPARE_PULLUP_MASK                                            0x00000004
#define SPARE_PULLUP_RD(src)                          (((src) & 0x00000004)>>2)
#define SPARE_PULLUP_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define SPARE_PULLUP_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SPARE_PDWN	 */
#define SPARE_PDWN_WIDTH                                                      1
#define SPARE_PDWN_SHIFT                                                      1
#define SPARE_PDWN_MASK                                              0x00000002
#define SPARE_PDWN_RD(src)                            (((src) & 0x00000002)>>1)
#define SPARE_PDWN_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define SPARE_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SPARE_PWROK	 */
#define SPARE_PWROK_WIDTH                                                     1
#define SPARE_PWROK_SHIFT                                                     0
#define SPARE_PWROK_MASK                                             0x00000001
#define SPARE_PWROK_RD(src)                              (((src) & 0x00000001))
#define SPARE_PWROK_WR(src)                         (((u32)(src)) & 0x00000001)
#define SPARE_PWROK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_MDIO_IOCTL	*/ 
/*	 Fields TST_MDIO_SRE	 */
#define TST_MDIO_SRE_WIDTH                                                    1
#define TST_MDIO_SRE_SHIFT                                                   20
#define TST_MDIO_SRE_MASK                                            0x00100000
#define TST_MDIO_SRE_RD(src)                         (((src) & 0x00100000)>>20)
#define TST_MDIO_SRE_WR(src)                    (((u32)(src)<<20) & 0x00100000)
#define TST_MDIO_SRE_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields TST_MDIO_HYTS	 */
#define TST_MDIO_HYTS_WIDTH                                                   1
#define TST_MDIO_HYTS_SHIFT                                                  19
#define TST_MDIO_HYTS_MASK                                           0x00080000
#define TST_MDIO_HYTS_RD(src)                        (((src) & 0x00080000)>>19)
#define TST_MDIO_HYTS_WR(src)                   (((u32)(src)<<19) & 0x00080000)
#define TST_MDIO_HYTS_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields TST_MDIO_PULLUP	 */
#define TST_MDIO_PULLUP_WIDTH                                                 1
#define TST_MDIO_PULLUP_SHIFT                                                18
#define TST_MDIO_PULLUP_MASK                                         0x00040000
#define TST_MDIO_PULLUP_RD(src)                      (((src) & 0x00040000)>>18)
#define TST_MDIO_PULLUP_WR(src)                 (((u32)(src)<<18) & 0x00040000)
#define TST_MDIO_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields TST_MDIO_PDWN	 */
#define TST_MDIO_PDWN_WIDTH                                                   1
#define TST_MDIO_PDWN_SHIFT                                                  17
#define TST_MDIO_PDWN_MASK                                           0x00020000
#define TST_MDIO_PDWN_RD(src)                        (((src) & 0x00020000)>>17)
#define TST_MDIO_PDWN_WR(src)                   (((u32)(src)<<17) & 0x00020000)
#define TST_MDIO_PDWN_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields TST_MDIO_PWROK	 */
#define TST_MDIO_PWROK_WIDTH                                                  1
#define TST_MDIO_PWROK_SHIFT                                                 16
#define TST_MDIO_PWROK_MASK                                          0x00010000
#define TST_MDIO_PWROK_RD(src)                       (((src) & 0x00010000)>>16)
#define TST_MDIO_PWROK_WR(src)                  (((u32)(src)<<16) & 0x00010000)
#define TST_MDIO_PWROK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields GE_MDIO_SRE	 */
#define GE_MDIO_SRE_WIDTH                                                     1
#define GE_MDIO_SRE_SHIFT                                                    12
#define GE_MDIO_SRE_MASK                                             0x00001000
#define GE_MDIO_SRE_RD(src)                          (((src) & 0x00001000)>>12)
#define GE_MDIO_SRE_WR(src)                     (((u32)(src)<<12) & 0x00001000)
#define GE_MDIO_SRE_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields GE_MDIO_HYTS	 */
#define GE_MDIO_HYTS_WIDTH                                                    1
#define GE_MDIO_HYTS_SHIFT                                                   11
#define GE_MDIO_HYTS_MASK                                            0x00000800
#define GE_MDIO_HYTS_RD(src)                         (((src) & 0x00000800)>>11)
#define GE_MDIO_HYTS_WR(src)                    (((u32)(src)<<11) & 0x00000800)
#define GE_MDIO_HYTS_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields GE_MDIO_PULLUP	 */
#define GE_MDIO_PULLUP_WIDTH                                                  1
#define GE_MDIO_PULLUP_SHIFT                                                 10
#define GE_MDIO_PULLUP_MASK                                          0x00000400
#define GE_MDIO_PULLUP_RD(src)                       (((src) & 0x00000400)>>10)
#define GE_MDIO_PULLUP_WR(src)                  (((u32)(src)<<10) & 0x00000400)
#define GE_MDIO_PULLUP_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields GE_MDIO_PDWN	 */
#define GE_MDIO_PDWN_WIDTH                                                    1
#define GE_MDIO_PDWN_SHIFT                                                    9
#define GE_MDIO_PDWN_MASK                                            0x00000200
#define GE_MDIO_PDWN_RD(src)                          (((src) & 0x00000200)>>9)
#define GE_MDIO_PDWN_WR(src)                     (((u32)(src)<<9) & 0x00000200)
#define GE_MDIO_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields GE_MDIO_PWROK	 */
#define GE_MDIO_PWROK_WIDTH                                                   1
#define GE_MDIO_PWROK_SHIFT                                                   8
#define GE_MDIO_PWROK_MASK                                           0x00000100
#define GE_MDIO_PWROK_RD(src)                         (((src) & 0x00000100)>>8)
#define GE_MDIO_PWROK_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define GE_MDIO_PWROK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields XGE_MDIO_SRE	 */
#define XGE_MDIO_SRE_WIDTH                                                    1
#define XGE_MDIO_SRE_SHIFT                                                    4
#define XGE_MDIO_SRE_MASK                                            0x00000010
#define XGE_MDIO_SRE_RD(src)                          (((src) & 0x00000010)>>4)
#define XGE_MDIO_SRE_WR(src)                     (((u32)(src)<<4) & 0x00000010)
#define XGE_MDIO_SRE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields XGE_MDIO_HYTS	 */
#define XGE_MDIO_HYTS_WIDTH                                                   1
#define XGE_MDIO_HYTS_SHIFT                                                   3
#define XGE_MDIO_HYTS_MASK                                           0x00000008
#define XGE_MDIO_HYTS_RD(src)                         (((src) & 0x00000008)>>3)
#define XGE_MDIO_HYTS_WR(src)                    (((u32)(src)<<3) & 0x00000008)
#define XGE_MDIO_HYTS_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields XGE_MDIO_PULLUP	 */
#define XGE_MDIO_PULLUP_WIDTH                                                 1
#define XGE_MDIO_PULLUP_SHIFT                                                 2
#define XGE_MDIO_PULLUP_MASK                                         0x00000004
#define XGE_MDIO_PULLUP_RD(src)                       (((src) & 0x00000004)>>2)
#define XGE_MDIO_PULLUP_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define XGE_MDIO_PULLUP_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields XGE_MDIO_PDWN	 */
#define XGE_MDIO_PDWN_WIDTH                                                   1
#define XGE_MDIO_PDWN_SHIFT                                                   1
#define XGE_MDIO_PDWN_MASK                                           0x00000002
#define XGE_MDIO_PDWN_RD(src)                         (((src) & 0x00000002)>>1)
#define XGE_MDIO_PDWN_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define XGE_MDIO_PDWN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields XGE_MDIO_PWROK	 */
#define XGE_MDIO_PWROK_WIDTH                                                  1
#define XGE_MDIO_PWROK_SHIFT                                                  0
#define XGE_MDIO_PWROK_MASK                                          0x00000001
#define XGE_MDIO_PWROK_RD(src)                           (((src) & 0x00000001))
#define XGE_MDIO_PWROK_WR(src)                      (((u32)(src)) & 0x00000001)
#define XGE_MDIO_PWROK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_MISC1_IOCTL0	*/ 
/*	 Fields TRC_SRE	 */
#define TRC_SRE0_WIDTH                                                        1
#define TRC_SRE0_SHIFT                                                       28
#define TRC_SRE0_MASK                                                0x10000000
#define TRC_SRE0_RD(src)                             (((src) & 0x10000000)>>28)
#define TRC_SRE0_WR(src)                        (((u32)(src)<<28) & 0x10000000)
#define TRC_SRE0_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields TRC_HYTS	 */
#define TRC_HYTS0_WIDTH                                                       1
#define TRC_HYTS0_SHIFT                                                      27
#define TRC_HYTS0_MASK                                               0x08000000
#define TRC_HYTS0_RD(src)                            (((src) & 0x08000000)>>27)
#define TRC_HYTS0_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define TRC_HYTS0_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields TRC_PULLUP	 */
#define TRC_PULLUP0_WIDTH                                                     1
#define TRC_PULLUP0_SHIFT                                                    26
#define TRC_PULLUP0_MASK                                             0x04000000
#define TRC_PULLUP0_RD(src)                          (((src) & 0x04000000)>>26)
#define TRC_PULLUP0_WR(src)                     (((u32)(src)<<26) & 0x04000000)
#define TRC_PULLUP0_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields TRC_PDWN	 */
#define TRC_PDWN0_WIDTH                                                       1
#define TRC_PDWN0_SHIFT                                                      25
#define TRC_PDWN0_MASK                                               0x02000000
#define TRC_PDWN0_RD(src)                            (((src) & 0x02000000)>>25)
#define TRC_PDWN0_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define TRC_PDWN0_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields TRC_PWROK	 */
#define TRC_PWROK0_WIDTH                                                      1
#define TRC_PWROK0_SHIFT                                                     24
#define TRC_PWROK0_MASK                                              0x01000000
#define TRC_PWROK0_RD(src)                           (((src) & 0x01000000)>>24)
#define TRC_PWROK0_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define TRC_PWROK0_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields ETH_REFCLK_SRE	 */
#define ETH_REFCLK_SRE0_WIDTH                                                 1
#define ETH_REFCLK_SRE0_SHIFT                                                20
#define ETH_REFCLK_SRE0_MASK                                         0x00100000
#define ETH_REFCLK_SRE0_RD(src)                      (((src) & 0x00100000)>>20)
#define ETH_REFCLK_SRE0_WR(src)                 (((u32)(src)<<20) & 0x00100000)
#define ETH_REFCLK_SRE0_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields ETH_REFCLK_HYTS	 */
#define ETH_REFCLK_HYTS0_WIDTH                                                1
#define ETH_REFCLK_HYTS0_SHIFT                                               19
#define ETH_REFCLK_HYTS0_MASK                                        0x00080000
#define ETH_REFCLK_HYTS0_RD(src)                     (((src) & 0x00080000)>>19)
#define ETH_REFCLK_HYTS0_WR(src)                (((u32)(src)<<19) & 0x00080000)
#define ETH_REFCLK_HYTS0_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields ETH_REFCLK_PULLUP	 */
#define ETH_REFCLK_PULLUP0_WIDTH                                              1
#define ETH_REFCLK_PULLUP0_SHIFT                                             18
#define ETH_REFCLK_PULLUP0_MASK                                      0x00040000
#define ETH_REFCLK_PULLUP0_RD(src)                   (((src) & 0x00040000)>>18)
#define ETH_REFCLK_PULLUP0_WR(src)              (((u32)(src)<<18) & 0x00040000)
#define ETH_REFCLK_PULLUP0_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields ETH_REFCLK_PDWN	 */
#define ETH_REFCLK_PDWN0_WIDTH                                                1
#define ETH_REFCLK_PDWN0_SHIFT                                               17
#define ETH_REFCLK_PDWN0_MASK                                        0x00020000
#define ETH_REFCLK_PDWN0_RD(src)                     (((src) & 0x00020000)>>17)
#define ETH_REFCLK_PDWN0_WR(src)                (((u32)(src)<<17) & 0x00020000)
#define ETH_REFCLK_PDWN0_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields ETH_REFCLK_PWROK	 */
#define ETH_REFCLK_PWROK0_WIDTH                                               1
#define ETH_REFCLK_PWROK0_SHIFT                                              16
#define ETH_REFCLK_PWROK0_MASK                                       0x00010000
#define ETH_REFCLK_PWROK0_RD(src)                    (((src) & 0x00010000)>>16)
#define ETH_REFCLK_PWROK0_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ETH_REFCLK_PWROK0_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields CLK_MON_SRE	 */
#define CLK_MON_SRE0_WIDTH                                                    1
#define CLK_MON_SRE0_SHIFT                                                   12
#define CLK_MON_SRE0_MASK                                            0x00001000
#define CLK_MON_SRE0_RD(src)                         (((src) & 0x00001000)>>12)
#define CLK_MON_SRE0_WR(src)                    (((u32)(src)<<12) & 0x00001000)
#define CLK_MON_SRE0_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields CLK_MON_HYTS	 */
#define CLK_MON_HYTS0_WIDTH                                                   1
#define CLK_MON_HYTS0_SHIFT                                                  11
#define CLK_MON_HYTS0_MASK                                           0x00000800
#define CLK_MON_HYTS0_RD(src)                        (((src) & 0x00000800)>>11)
#define CLK_MON_HYTS0_WR(src)                   (((u32)(src)<<11) & 0x00000800)
#define CLK_MON_HYTS0_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields CLK_MON_PULLUP	 */
#define CLK_MON_PULLUP0_WIDTH                                                 1
#define CLK_MON_PULLUP0_SHIFT                                                10
#define CLK_MON_PULLUP0_MASK                                         0x00000400
#define CLK_MON_PULLUP0_RD(src)                      (((src) & 0x00000400)>>10)
#define CLK_MON_PULLUP0_WR(src)                 (((u32)(src)<<10) & 0x00000400)
#define CLK_MON_PULLUP0_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields CLK_MON_PDWN	 */
#define CLK_MON_PDWN0_WIDTH                                                   1
#define CLK_MON_PDWN0_SHIFT                                                   9
#define CLK_MON_PDWN0_MASK                                           0x00000200
#define CLK_MON_PDWN0_RD(src)                         (((src) & 0x00000200)>>9)
#define CLK_MON_PDWN0_WR(src)                    (((u32)(src)<<9) & 0x00000200)
#define CLK_MON_PDWN0_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields CLK_MON_PWROK	 */
#define CLK_MON_PWROK0_WIDTH                                                  1
#define CLK_MON_PWROK0_SHIFT                                                  8
#define CLK_MON_PWROK0_MASK                                          0x00000100
#define CLK_MON_PWROK0_RD(src)                        (((src) & 0x00000100)>>8)
#define CLK_MON_PWROK0_WR(src)                   (((u32)(src)<<8) & 0x00000100)
#define CLK_MON_PWROK0_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields FAULT_SRE	 */
#define FAULT_SRE0_WIDTH                                                      1
#define FAULT_SRE0_SHIFT                                                      4
#define FAULT_SRE0_MASK                                              0x00000010
#define FAULT_SRE0_RD(src)                            (((src) & 0x00000010)>>4)
#define FAULT_SRE0_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define FAULT_SRE0_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields FAULT_HYTS	 */
#define FAULT_HYTS0_WIDTH                                                     1
#define FAULT_HYTS0_SHIFT                                                     3
#define FAULT_HYTS0_MASK                                             0x00000008
#define FAULT_HYTS0_RD(src)                           (((src) & 0x00000008)>>3)
#define FAULT_HYTS0_WR(src)                      (((u32)(src)<<3) & 0x00000008)
#define FAULT_HYTS0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields FAULT_PULLUP	 */
#define FAULT_PULLUP0_WIDTH                                                   1
#define FAULT_PULLUP0_SHIFT                                                   2
#define FAULT_PULLUP0_MASK                                           0x00000004
#define FAULT_PULLUP0_RD(src)                         (((src) & 0x00000004)>>2)
#define FAULT_PULLUP0_WR(src)                    (((u32)(src)<<2) & 0x00000004)
#define FAULT_PULLUP0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields FAULT_PDWN	 */
#define FAULT_PDWN0_WIDTH                                                     1
#define FAULT_PDWN0_SHIFT                                                     1
#define FAULT_PDWN0_MASK                                             0x00000002
#define FAULT_PDWN0_RD(src)                           (((src) & 0x00000002)>>1)
#define FAULT_PDWN0_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define FAULT_PDWN0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields FAULT_PWROK	 */
#define FAULT_PWROK0_WIDTH                                                    1
#define FAULT_PWROK0_SHIFT                                                    0
#define FAULT_PWROK0_MASK                                            0x00000001
#define FAULT_PWROK0_RD(src)                             (((src) & 0x00000001))
#define FAULT_PWROK0_WR(src)                        (((u32)(src)) & 0x00000001)
#define FAULT_PWROK0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_CH0_PWM_CTL	*/ 
/*	 Fields PWM_POLARITY	 */
#define PWM_POLARITY_WIDTH                                                    1
#define PWM_POLARITY_SHIFT                                                    1
#define PWM_POLARITY_MASK                                            0x00000002
#define PWM_POLARITY_RD(src)                          (((src) & 0x00000002)>>1)
#define PWM_POLARITY_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define PWM_POLARITY_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PWM_ENABLE	 */
#define PWM_ENABLE_WIDTH                                                      1
#define PWM_ENABLE_SHIFT                                                      0
#define PWM_ENABLE_MASK                                              0x00000001
#define PWM_ENABLE_RD(src)                               (((src) & 0x00000001))
#define PWM_ENABLE_WR(src)                          (((u32)(src)) & 0x00000001)
#define PWM_ENABLE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_CH0_PWM_PERIOD	*/ 
/*	 Fields PWM_PERIOD	 */
#define PWM_PERIOD_WIDTH                                                     32
#define PWM_PERIOD_SHIFT                                                      0
#define PWM_PERIOD_MASK                                              0xffffffff
#define PWM_PERIOD_RD(src)                               (((src) & 0xffffffff))
#define PWM_PERIOD_WR(src)                          (((u32)(src)) & 0xffffffff)
#define PWM_PERIOD_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CH0_PWM_HIGH	*/ 
/*	 Fields PWM_HIGH	 */
#define PWM_HIGH_WIDTH                                                       32
#define PWM_HIGH_SHIFT                                                        0
#define PWM_HIGH_MASK                                                0xffffffff
#define PWM_HIGH_RD(src)                                 (((src) & 0xffffffff))
#define PWM_HIGH_WR(src)                            (((u32)(src)) & 0xffffffff)
#define PWM_HIGH_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CH1_PWM_CTL	*/ 
/*	 Fields PWM_POLARITY	 */
#define PWM_POLARITY_F1_WIDTH                                                 1
#define PWM_POLARITY_F1_SHIFT                                                 1
#define PWM_POLARITY_F1_MASK                                         0x00000002
#define PWM_POLARITY_F1_RD(src)                       (((src) & 0x00000002)>>1)
#define PWM_POLARITY_F1_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define PWM_POLARITY_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PWM_ENABLE	 */
#define PWM_ENABLE_F1_WIDTH                                                   1
#define PWM_ENABLE_F1_SHIFT                                                   0
#define PWM_ENABLE_F1_MASK                                           0x00000001
#define PWM_ENABLE_F1_RD(src)                            (((src) & 0x00000001))
#define PWM_ENABLE_F1_WR(src)                       (((u32)(src)) & 0x00000001)
#define PWM_ENABLE_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_CH1_PWM_PERIOD	*/ 
/*	 Fields PWM_PERIOD	 */
#define PWM_PERIOD_F1_WIDTH                                                  32
#define PWM_PERIOD_F1_SHIFT                                                   0
#define PWM_PERIOD_F1_MASK                                           0xffffffff
#define PWM_PERIOD_F1_RD(src)                            (((src) & 0xffffffff))
#define PWM_PERIOD_F1_WR(src)                       (((u32)(src)) & 0xffffffff)
#define PWM_PERIOD_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CH1_PWM_HIGH	*/ 
/*	 Fields PWM_HIGH	 */
#define PWM_HIGH_F1_WIDTH                                                    32
#define PWM_HIGH_F1_SHIFT                                                     0
#define PWM_HIGH_F1_MASK                                             0xffffffff
#define PWM_HIGH_F1_RD(src)                              (((src) & 0xffffffff))
#define PWM_HIGH_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define PWM_HIGH_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_TMM_WRERR_STAT0	*/ 
/*	 Fields ADDR	 */
#define REGSPEC_ADDR0_WIDTH                                                  32
#define REGSPEC_ADDR0_SHIFT                                                   0
#define REGSPEC_ADDR0_MASK                                           0xffffffff
#define REGSPEC_ADDR0_RD(src)                            (((src) & 0xffffffff))
#define REGSPEC_ADDR0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_TMM_WRERR_STAT1	*/ 
/*	 Fields ERROR	 */
#define REGSPEC_ERROR1_WIDTH                                                  1
#define REGSPEC_ERROR1_SHIFT                                                 31
#define REGSPEC_ERROR1_MASK                                          0x80000000
#define REGSPEC_ERROR1_RD(src)                       (((src) & 0x80000000)>>31)
#define REGSPEC_ERROR1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields AXI_LEN	 */
#define AXI_LEN1_WIDTH                                                        4
#define AXI_LEN1_SHIFT                                                       12
#define AXI_LEN1_MASK                                                0x0000f000
#define AXI_LEN1_RD(src)                             (((src) & 0x0000f000)>>12)
#define AXI_LEN1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields AXI_ID	 */
#define AXI_ID1_WIDTH                                                         6
#define AXI_ID1_SHIFT                                                         0
#define AXI_ID1_MASK                                                 0x0000003f
#define AXI_ID1_RD(src)                                  (((src) & 0x0000003f))
#define AXI_ID1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register MPA_TMM_RDERR_STAT0	*/ 
/*	 Fields ADDR	 */
#define REGSPEC_ADDR0_F1_WIDTH                                               32
#define REGSPEC_ADDR0_F1_SHIFT                                                0
#define REGSPEC_ADDR0_F1_MASK                                        0xffffffff
#define REGSPEC_ADDR0_F1_RD(src)                         (((src) & 0xffffffff))
#define REGSPEC_ADDR0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_TMM_RDERR_STAT1	*/ 
/*	 Fields ERROR	 */
#define REGSPEC_ERROR1_F1_WIDTH                                               1
#define REGSPEC_ERROR1_F1_SHIFT                                              31
#define REGSPEC_ERROR1_F1_MASK                                       0x80000000
#define REGSPEC_ERROR1_F1_RD(src)                    (((src) & 0x80000000)>>31)
#define REGSPEC_ERROR1_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields AXI_LEN	 */
#define AXI_LEN1_F1_WIDTH                                                     4
#define AXI_LEN1_F1_SHIFT                                                    12
#define AXI_LEN1_F1_MASK                                             0x0000f000
#define AXI_LEN1_F1_RD(src)                          (((src) & 0x0000f000)>>12)
#define AXI_LEN1_F1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields AXI_ID	 */
#define AXI_ID1_F1_WIDTH                                                      6
#define AXI_ID1_F1_SHIFT                                                      0
#define AXI_ID1_F1_MASK                                              0x0000003f
#define AXI_ID1_F1_RD(src)                               (((src) & 0x0000003f))
#define AXI_ID1_F1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register MPA_TMM_CSR_ERR_STAT	*/ 
/*	 Fields ERROR	 */
#define REGSPEC_ERROR_WIDTH                                                   1
#define REGSPEC_ERROR_SHIFT                                                  31
#define REGSPEC_ERROR_MASK                                           0x80000000
#define REGSPEC_ERROR_RD(src)                        (((src) & 0x80000000)>>31)
#define REGSPEC_ERROR_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields CSR_WR	 */
#define CSR_WR_WIDTH                                                          1
#define CSR_WR_SHIFT                                                         16
#define CSR_WR_MASK                                                  0x00010000
#define CSR_WR_RD(src)                               (((src) & 0x00010000)>>16)
#define CSR_WR_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields CSR_ADDR	 */
#define CSR_ADDR_WIDTH                                                       15
#define CSR_ADDR_SHIFT                                                        0
#define CSR_ADDR_MASK                                                0x00007fff
#define CSR_ADDR_RD(src)                                 (((src) & 0x00007fff))
#define CSR_ADDR_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register MPA_CH2_PWM_CTL	*/ 
/*	 Fields PWM_POLARITY	 */
#define PWM_POLARITY_F2_WIDTH                                                 1
#define PWM_POLARITY_F2_SHIFT                                                 1
#define PWM_POLARITY_F2_MASK                                         0x00000002
#define PWM_POLARITY_F2_RD(src)                       (((src) & 0x00000002)>>1)
#define PWM_POLARITY_F2_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define PWM_POLARITY_F2_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PWM_ENABLE	 */
#define PWM_ENABLE_F2_WIDTH                                                   1
#define PWM_ENABLE_F2_SHIFT                                                   0
#define PWM_ENABLE_F2_MASK                                           0x00000001
#define PWM_ENABLE_F2_RD(src)                            (((src) & 0x00000001))
#define PWM_ENABLE_F2_WR(src)                       (((u32)(src)) & 0x00000001)
#define PWM_ENABLE_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_CH2_PWM_PERIOD	*/ 
/*	 Fields PWM_PERIOD	 */
#define PWM_PERIOD_F2_WIDTH                                                  32
#define PWM_PERIOD_F2_SHIFT                                                   0
#define PWM_PERIOD_F2_MASK                                           0xffffffff
#define PWM_PERIOD_F2_RD(src)                            (((src) & 0xffffffff))
#define PWM_PERIOD_F2_WR(src)                       (((u32)(src)) & 0xffffffff)
#define PWM_PERIOD_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CH2_PWM_HIGH	*/ 
/*	 Fields PWM_HIGH	 */
#define PWM_HIGH_F2_WIDTH                                                    32
#define PWM_HIGH_F2_SHIFT                                                     0
#define PWM_HIGH_F2_MASK                                             0xffffffff
#define PWM_HIGH_F2_RD(src)                              (((src) & 0xffffffff))
#define PWM_HIGH_F2_WR(src)                         (((u32)(src)) & 0xffffffff)
#define PWM_HIGH_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CH3_PWM_CTL	*/ 
/*	 Fields PWM_POLARITY	 */
#define PWM_POLARITY_F3_WIDTH                                                 1
#define PWM_POLARITY_F3_SHIFT                                                 1
#define PWM_POLARITY_F3_MASK                                         0x00000002
#define PWM_POLARITY_F3_RD(src)                       (((src) & 0x00000002)>>1)
#define PWM_POLARITY_F3_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define PWM_POLARITY_F3_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PWM_ENABLE	 */
#define PWM_ENABLE_F3_WIDTH                                                   1
#define PWM_ENABLE_F3_SHIFT                                                   0
#define PWM_ENABLE_F3_MASK                                           0x00000001
#define PWM_ENABLE_F3_RD(src)                            (((src) & 0x00000001))
#define PWM_ENABLE_F3_WR(src)                       (((u32)(src)) & 0x00000001)
#define PWM_ENABLE_F3_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_CH3_PWM_PERIOD	*/ 
/*	 Fields PWM_PERIOD	 */
#define PWM_PERIOD_F3_WIDTH                                                  32
#define PWM_PERIOD_F3_SHIFT                                                   0
#define PWM_PERIOD_F3_MASK                                           0xffffffff
#define PWM_PERIOD_F3_RD(src)                            (((src) & 0xffffffff))
#define PWM_PERIOD_F3_WR(src)                       (((u32)(src)) & 0xffffffff)
#define PWM_PERIOD_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CH3_PWM_HIGH	*/ 
/*	 Fields PWM_HIGH	 */
#define PWM_HIGH_F3_WIDTH                                                    32
#define PWM_HIGH_F3_SHIFT                                                     0
#define PWM_HIGH_F3_MASK                                             0xffffffff
#define PWM_HIGH_F3_RD(src)                              (((src) & 0xffffffff))
#define PWM_HIGH_F3_WR(src)                         (((u32)(src)) & 0xffffffff)
#define PWM_HIGH_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_CLKMON_SEL	*/ 
/*	 Fields CLKMON_FREQ_SEL	 */
#define CLKMON_FREQ_SEL_WIDTH                                                 5
#define CLKMON_FREQ_SEL_SHIFT                                                 8
#define CLKMON_FREQ_SEL_MASK                                         0x00001f00
#define CLKMON_FREQ_SEL_RD(src)                       (((src) & 0x00001f00)>>8)
#define CLKMON_FREQ_SEL_WR(src)                  (((u32)(src)<<8) & 0x00001f00)
#define CLKMON_FREQ_SEL_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields DSF_CLKMON_SEL	 */
#define DSF_CLKMON_SEL_WIDTH                                                  6
#define DSF_CLKMON_SEL_SHIFT                                                  0
#define DSF_CLKMON_SEL_MASK                                          0x0000003f
#define DSF_CLKMON_SEL_RD(src)                           (((src) & 0x0000003f))
#define DSF_CLKMON_SEL_WR(src)                      (((u32)(src)) & 0x0000003f)
#define DSF_CLKMON_SEL_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register PKA_DEBUG0	*/ 
/*	 Fields DEBUG0	 */
#define DEBUG00_WIDTH                                                        16
#define DEBUG00_SHIFT                                                         0
#define DEBUG00_MASK                                                 0x0000ffff
#define DEBUG00_RD(src)                                  (((src) & 0x0000ffff))
#define DEBUG00_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register PKA_DEBUG1	*/ 
/*	 Fields DEBUG1	 */
#define DEBUG11_WIDTH                                                        16
#define DEBUG11_SHIFT                                                         0
#define DEBUG11_MASK                                                 0x0000ffff
#define DEBUG11_RD(src)                                  (((src) & 0x0000ffff))
#define DEBUG11_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register PKA_DEBUG2	*/ 
/*	 Fields DEBUG2	 */
#define DEBUG22_WIDTH                                                         4
#define DEBUG22_SHIFT                                                         0
#define DEBUG22_MASK                                                 0x0000000f
#define DEBUG22_RD(src)                                  (((src) & 0x0000000f))
#define DEBUG22_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Global Base Address	*/
#define MPA_AHB_CSR_I_BASE_ADDR			0x050002000ULL

/*    Address MPA_AHB_CSR_I  Registers */
#define MPA_DMA_STAT_ADDR                                            0x00000000
#define MPA_DMA_STAT_DEFAULT                                         0x00000000
#define MPA_PG_MAP0_ADDR                                             0x00000010
#define MPA_PG_MAP0_DEFAULT                                          0x00000000
#define MPA_PG_MAP1_ADDR                                             0x00000014
#define MPA_PG_MAP1_DEFAULT                                          0x00000000
#define MPA_PG_MAP2_ADDR                                             0x00000018
#define MPA_PG_MAP2_DEFAULT                                          0x00000000
#define MPA_PG_MAP3_ADDR                                             0x0000001c
#define MPA_PG_MAP3_DEFAULT                                          0x00000000
#define MPA_VC_ADDR                                                  0x00000020
#define MPA_VC_DEFAULT                                               0x00000002
#define MPA_OCM_CTL_ADDR                                             0x00000024
#define MPA_OCM_CTL_DEFAULT                                          0x00000000
#define FORCE_SPDUP_ADDR                                             0x00000040
#define FORCE_SPDUP_DEFAULT                                          0x00000000
#define MPA_QMI_INTSTAT_RO_ADDR                                      0x00000100
#define MPA_QMI_INTSTAT_RO_DEFAULT                                   0x00000000
#define MPA_QMI_STAT_ADDR                                            0x00000108
#define MPA_QMI_STAT_DEFAULT                                         0x00000000
#define MPA_QMI_FP_CTL_ADDR                                          0x00000120
#define MPA_QMI_FP_CTL_DEFAULT                                       0x00000000
#define MPA_QMI_WQ_CTL_ADDR                                          0x00000124
#define MPA_QMI_WQ_CTL_DEFAULT                                       0x00000000
#define MPA_QMI_FPDE_CTL_ADDR                                        0x00000128
#define MPA_QMI_FPDE_CTL_DEFAULT                                     0x00000000
#define MPA_QMI_CM_CTL_ADDR                                          0x0000012c
#define MPA_QMI_CM_CTL_DEFAULT                                       0x00000000
#define MPA_QMI_FP_MSG0_ADDR                                         0x00000130
#define MPA_QMI_FP_MSG0_DEFAULT                                      0x00000000
#define MPA_QMI_FP_MSG1_ADDR                                         0x00000134
#define MPA_QMI_FP_MSG1_DEFAULT                                      0x00000000
#define MPA_QMI_FP_MSG2_ADDR                                         0x00000138
#define MPA_QMI_FP_MSG2_DEFAULT                                      0x00000000
#define MPA_QMI_FP_MSG3_ADDR                                         0x0000013c
#define MPA_QMI_FP_MSG3_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG0_ADDR                                         0x00000140
#define MPA_QMI_WQ_MSG0_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG1_ADDR                                         0x00000144
#define MPA_QMI_WQ_MSG1_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG2_ADDR                                         0x00000148
#define MPA_QMI_WQ_MSG2_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG3_ADDR                                         0x0000014c
#define MPA_QMI_WQ_MSG3_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG4_ADDR                                         0x00000150
#define MPA_QMI_WQ_MSG4_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG5_ADDR                                         0x00000154
#define MPA_QMI_WQ_MSG5_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG6_ADDR                                         0x00000158
#define MPA_QMI_WQ_MSG6_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG7_ADDR                                         0x0000015c
#define MPA_QMI_WQ_MSG7_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG8_ADDR                                         0x00000160
#define MPA_QMI_WQ_MSG8_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG9_ADDR                                         0x00000164
#define MPA_QMI_WQ_MSG9_DEFAULT                                      0x00000000
#define MPA_QMI_WQ_MSG10_ADDR                                        0x00000168
#define MPA_QMI_WQ_MSG10_DEFAULT                                     0x00000000
#define MPA_QMI_WQ_MSG11_ADDR                                        0x0000016c
#define MPA_QMI_WQ_MSG11_DEFAULT                                     0x00000000
#define MPA_QMI_WQ_MSG12_ADDR                                        0x00000170
#define MPA_QMI_WQ_MSG12_DEFAULT                                     0x00000000
#define MPA_QMI_WQ_MSG13_ADDR                                        0x00000174
#define MPA_QMI_WQ_MSG13_DEFAULT                                     0x00000000
#define MPA_QMI_WQ_MSG14_ADDR                                        0x00000178
#define MPA_QMI_WQ_MSG14_DEFAULT                                     0x00000000
#define MPA_QMI_WQ_MSG15_ADDR                                        0x0000017c
#define MPA_QMI_WQ_MSG15_DEFAULT                                     0x00000000
#define MPA_QMI_FPDE_MSG0_ADDR                                       0x00000180
#define MPA_QMI_FPDE_MSG0_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG1_ADDR                                       0x00000184
#define MPA_QMI_FPDE_MSG1_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG2_ADDR                                       0x00000188
#define MPA_QMI_FPDE_MSG2_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG3_ADDR                                       0x0000018c
#define MPA_QMI_FPDE_MSG3_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG4_ADDR                                       0x00000190
#define MPA_QMI_FPDE_MSG4_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG5_ADDR                                       0x00000194
#define MPA_QMI_FPDE_MSG5_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG6_ADDR                                       0x00000198
#define MPA_QMI_FPDE_MSG6_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG7_ADDR                                       0x0000019c
#define MPA_QMI_FPDE_MSG7_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG8_ADDR                                       0x000001a0
#define MPA_QMI_FPDE_MSG8_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG9_ADDR                                       0x000001a4
#define MPA_QMI_FPDE_MSG9_DEFAULT                                    0x00000000
#define MPA_QMI_FPDE_MSG10_ADDR                                      0x000001a8
#define MPA_QMI_FPDE_MSG10_DEFAULT                                   0x00000000
#define MPA_QMI_FPDE_MSG11_ADDR                                      0x000001ac
#define MPA_QMI_FPDE_MSG11_DEFAULT                                   0x00000000
#define MPA_QMI_FPDE_MSG12_ADDR                                      0x000001b0
#define MPA_QMI_FPDE_MSG12_DEFAULT                                   0x00000000
#define MPA_QMI_FPDE_MSG13_ADDR                                      0x000001b4
#define MPA_QMI_FPDE_MSG13_DEFAULT                                   0x00000000
#define MPA_QMI_FPDE_MSG14_ADDR                                      0x000001b8
#define MPA_QMI_FPDE_MSG14_DEFAULT                                   0x00000000
#define MPA_QMI_FPDE_MSG15_ADDR                                      0x000001bc
#define MPA_QMI_FPDE_MSG15_DEFAULT                                   0x00000000
#define MPA_QMI_RIDA_ADDR                                            0x000001e0
#define MPA_QMI_RIDA_DEFAULT                                         0x00000000
#define MPA_QMI_RIDB_ADDR                                            0x000001e4
#define MPA_QMI_RIDB_DEFAULT                                         0x00000000
#define MPA_QMI_RIDC_ADDR                                            0x000001e8
#define MPA_QMI_RIDC_DEFAULT                                         0x00000000
#define MPA_QMI_RID_IENA_ADDR                                        0x000001f0
#define MPA_QMI_RID_IENA_DEFAULT                                     0x00000000
#define MPA_QMI_RID_IENB_ADDR                                        0x000001f4
#define MPA_QMI_RID_IENB_DEFAULT                                     0x00000000
#define MPA_QMI_RID_IENC_ADDR                                        0x000001f8
#define MPA_QMI_RID_IENC_DEFAULT                                     0x00000000
#define MPA_QMI_CM_MSG0_ADDR                                         0x00000200
#define MPA_QMI_CM_MSG0_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG1_ADDR                                         0x00000204
#define MPA_QMI_CM_MSG1_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG2_ADDR                                         0x00000208
#define MPA_QMI_CM_MSG2_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG3_ADDR                                         0x0000020c
#define MPA_QMI_CM_MSG3_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG4_ADDR                                         0x00000210
#define MPA_QMI_CM_MSG4_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG5_ADDR                                         0x00000214
#define MPA_QMI_CM_MSG5_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG6_ADDR                                         0x00000218
#define MPA_QMI_CM_MSG6_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG7_ADDR                                         0x0000021c
#define MPA_QMI_CM_MSG7_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG8_ADDR                                         0x00000220
#define MPA_QMI_CM_MSG8_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG9_ADDR                                         0x00000224
#define MPA_QMI_CM_MSG9_DEFAULT                                      0x00000000
#define MPA_QMI_CM_MSG10_ADDR                                        0x00000228
#define MPA_QMI_CM_MSG10_DEFAULT                                     0x00000000
#define MPA_QMI_CM_MSG11_ADDR                                        0x0000022c
#define MPA_QMI_CM_MSG11_DEFAULT                                     0x00000000
#define MPA_QMI_CM_MSG12_ADDR                                        0x00000230
#define MPA_QMI_CM_MSG12_DEFAULT                                     0x00000000
#define MPA_QMI_CM_MSG13_ADDR                                        0x00000234
#define MPA_QMI_CM_MSG13_DEFAULT                                     0x00000000
#define MPA_QMI_CM_MSG14_ADDR                                        0x00000238
#define MPA_QMI_CM_MSG14_DEFAULT                                     0x00000000
#define MPA_QMI_CM_MSG15_ADDR                                        0x0000023c
#define MPA_QMI_CM_MSG15_DEFAULT                                     0x00000000
#define MPA_DRAM_CTL_ADDR                                            0x00000240
#define MPA_DRAM_CTL_DEFAULT                                         0x80000001
#define AHB_SOC_EFUSE_ADDR                                           0x00000244
#define AHB_SOC_EFUSE_DEFAULT                                        0x00000000
#define AHB_SOC_EFUSE1_ADDR                                          0x00000248
#define AHB_SOC_EFUSE1_DEFAULT                                       0x00000000
#define MPA_DMA_CTL_ADDR                                             0x00000300
#define MPA_DMA_CTL_DEFAULT                                          0x00000000
#define MPA_DMA_CNT_ADDR                                             0x00000304
#define MPA_DMA_CNT_DEFAULT                                          0x00000000
#define MPA_DMA_LADDR_ADDR                                           0x00000308
#define MPA_DMA_LADDR_DEFAULT                                        0x00000000
#define MPA_DMA_HADDR_ADDR                                           0x0000030c
#define MPA_DMA_HADDR_DEFAULT                                        0x00000000
#define MPA_DMA_MADDR_ADDR                                           0x00000310
#define MPA_DMA_MADDR_DEFAULT                                        0x00000000
#define EFUSE_CTL_ADDR                                               0x00000400
#define EFUSE_CTL_DEFAULT                                            0x00000000
#define EFUSE_STAT_ADDR                                              0x00000404
#define EFUSE_STAT_DEFAULT                                           0x00000000
#define EFUSE_RDDATA_ADDR                                            0x0000040c
#define EFUSE_RDDATA_DEFAULT                                         0x00000000
#define TPM_CTL_ADDR                                                 0x00000410
#define TPM_CTL_DEFAULT                                              0x00000000
#define AHB_PINSTRAP_ADDR                                            0x00000414
#define AHB_PINSTRAP_DEFAULT                                         0x00000000
#define MPA_AHB_IRAM_ADDR_ADDR                                       0x00000430
#define MPA_AHB_IRAM_ADDR_DEFAULT                                    0x00000000
#define MPA_AHB_IRAM_DATA_ADDR                                       0x00000434
#define MPA_AHB_IRAM_DATA_DEFAULT                                    0x00000000
#define MPA_AHB_IRAM_RDATA_ADDR                                      0x00000438
#define MPA_AHB_IRAM_RDATA_DEFAULT                                   0x00000000
#define MPA_GC_CLK_MODE_ADDR                                         0x00000440
#define MPA_GC_CLK_MODE_DEFAULT                                      0x00000000
#define DB0_IN_ADDR                                                  0x00000500
#define DB0_IN_DEFAULT                                               0x00000000
#define DB0_DIN0_ADDR                                                0x00000504
#define DB0_DIN0_DEFAULT                                             0x00000000
#define DB0_DIN1_ADDR                                                0x00000508
#define DB0_DIN1_DEFAULT                                             0x00000000
#define DB0_OUT_ADDR                                                 0x00000510
#define DB0_OUT_DEFAULT                                              0x00000000
#define DB0_DOUT0_ADDR                                               0x00000514
#define DB0_DOUT0_DEFAULT                                            0x00000000
#define DB0_DOUT1_ADDR                                               0x00000518
#define DB0_DOUT1_DEFAULT                                            0x00000000
#define DB1_IN_ADDR                                                  0x00000520
#define DB1_IN_DEFAULT                                               0x00000000
#define DB1_DIN0_ADDR                                                0x00000524
#define DB1_DIN0_DEFAULT                                             0x00000000
#define DB1_DIN1_ADDR                                                0x00000528
#define DB1_DIN1_DEFAULT                                             0x00000000
#define DB1_OUT_ADDR                                                 0x00000530
#define DB1_OUT_DEFAULT                                              0x00000000
#define DB1_DOUT0_ADDR                                               0x00000534
#define DB1_DOUT0_DEFAULT                                            0x00000000
#define DB1_DOUT1_ADDR                                               0x00000538
#define DB1_DOUT1_DEFAULT                                            0x00000000
#define DB2_IN_ADDR                                                  0x00000540
#define DB2_IN_DEFAULT                                               0x00000000
#define DB2_DIN0_ADDR                                                0x00000544
#define DB2_DIN0_DEFAULT                                             0x00000000
#define DB2_DIN1_ADDR                                                0x00000548
#define DB2_DIN1_DEFAULT                                             0x00000000
#define DB2_OUT_ADDR                                                 0x00000550
#define DB2_OUT_DEFAULT                                              0x00000000
#define DB2_DOUT0_ADDR                                               0x00000554
#define DB2_DOUT0_DEFAULT                                            0x00000000
#define DB2_DOUT1_ADDR                                               0x00000558
#define DB2_DOUT1_DEFAULT                                            0x00000000
#define DB3_IN_ADDR                                                  0x00000560
#define DB3_IN_DEFAULT                                               0x00000000
#define DB3_DIN0_ADDR                                                0x00000564
#define DB3_DIN0_DEFAULT                                             0x00000000
#define DB3_DIN1_ADDR                                                0x00000568
#define DB3_DIN1_DEFAULT                                             0x00000000
#define DB3_OUT_ADDR                                                 0x00000570
#define DB3_OUT_DEFAULT                                              0x00000000
#define DB3_DOUT0_ADDR                                               0x00000574
#define DB3_DOUT0_DEFAULT                                            0x00000000
#define DB3_DOUT1_ADDR                                               0x00000578
#define DB3_DOUT1_DEFAULT                                            0x00000000
#define DB4_IN_ADDR                                                  0x00000580
#define DB4_IN_DEFAULT                                               0x00000000
#define DB4_DIN0_ADDR                                                0x00000584
#define DB4_DIN0_DEFAULT                                             0x00000000
#define DB4_DIN1_ADDR                                                0x00000588
#define DB4_DIN1_DEFAULT                                             0x00000000
#define DB4_OUT_ADDR                                                 0x00000590
#define DB4_OUT_DEFAULT                                              0x00000000
#define DB4_DOUT0_ADDR                                               0x00000594
#define DB4_DOUT0_DEFAULT                                            0x00000000
#define DB4_DOUT1_ADDR                                               0x00000598
#define DB4_DOUT1_DEFAULT                                            0x00000000
#define DB5_IN_ADDR                                                  0x000005a0
#define DB5_IN_DEFAULT                                               0x00000000
#define DB5_DIN0_ADDR                                                0x000005a4
#define DB5_DIN0_DEFAULT                                             0x00000000
#define DB5_DIN1_ADDR                                                0x000005a8
#define DB5_DIN1_DEFAULT                                             0x00000000
#define DB5_OUT_ADDR                                                 0x000005b0
#define DB5_OUT_DEFAULT                                              0x00000000
#define DB5_DOUT0_ADDR                                               0x000005b4
#define DB5_DOUT0_DEFAULT                                            0x00000000
#define DB5_DOUT1_ADDR                                               0x000005b8
#define DB5_DOUT1_DEFAULT                                            0x00000000
#define DB6_IN_ADDR                                                  0x000005c0
#define DB6_IN_DEFAULT                                               0x00000000
#define DB6_DIN0_ADDR                                                0x000005c4
#define DB6_DIN0_DEFAULT                                             0x00000000
#define DB6_DIN1_ADDR                                                0x000005c8
#define DB6_DIN1_DEFAULT                                             0x00000000
#define DB6_OUT_ADDR                                                 0x000005d0
#define DB6_OUT_DEFAULT                                              0x00000000
#define DB6_DOUT0_ADDR                                               0x000005d4
#define DB6_DOUT0_DEFAULT                                            0x00000000
#define DB6_DOUT1_ADDR                                               0x000005d8
#define DB6_DOUT1_DEFAULT                                            0x00000000
#define DB7_IN_ADDR                                                  0x000005e0
#define DB7_IN_DEFAULT                                               0x00000000
#define DB7_DIN0_ADDR                                                0x000005e4
#define DB7_DIN0_DEFAULT                                             0x00000000
#define DB7_DIN1_ADDR                                                0x000005e8
#define DB7_DIN1_DEFAULT                                             0x00000000
#define DB7_OUT_ADDR                                                 0x000005f0
#define DB7_OUT_DEFAULT                                              0x00000000
#define DB7_DOUT0_ADDR                                               0x000005f4
#define DB7_DOUT0_DEFAULT                                            0x00000000
#define DB7_DOUT1_ADDR                                               0x000005f8
#define DB7_DOUT1_DEFAULT                                            0x00000000
#define DB8_IN_ADDR                                                  0x00000600
#define DB8_IN_DEFAULT                                               0x00000000
#define DB8_DIN0_ADDR                                                0x00000604
#define DB8_DIN0_DEFAULT                                             0x00000000
#define DB8_DIN1_ADDR                                                0x00000608
#define DB8_DIN1_DEFAULT                                             0x00000000
#define DB8_OUT_ADDR                                                 0x00000610
#define DB8_OUT_DEFAULT                                              0x00000000
#define DB8_DOUT0_ADDR                                               0x00000614
#define DB8_DOUT0_DEFAULT                                            0x00000000
#define DB8_DOUT1_ADDR                                               0x00000618
#define DB8_DOUT1_DEFAULT                                            0x00000000
#define DB9_IN_ADDR                                                  0x00000620
#define DB9_IN_DEFAULT                                               0x00000000
#define DB9_DIN0_ADDR                                                0x00000624
#define DB9_DIN0_DEFAULT                                             0x00000000
#define DB9_DIN1_ADDR                                                0x00000628
#define DB9_DIN1_DEFAULT                                             0x00000000
#define DB9_OUT_ADDR                                                 0x00000630
#define DB9_OUT_DEFAULT                                              0x00000000
#define DB9_DOUT0_ADDR                                               0x00000634
#define DB9_DOUT0_DEFAULT                                            0x00000000
#define DB9_DOUT1_ADDR                                               0x00000638
#define DB9_DOUT1_DEFAULT                                            0x00000000
#define MPA_EFUSE0_SHADOW_ENABLE_ADDR                                0x00000640
#define MPA_EFUSE0_SHADOW_ENABLE_DEFAULT                             0x00000000
#define MPA_EFUSE1_SHADOW_ENABLE_ADDR                                0x00000644
#define MPA_EFUSE1_SHADOW_ENABLE_DEFAULT                             0x00000000
#define MPA_ECID0_SHADOW_ENABLE_ADDR                                 0x00000648
#define MPA_ECID0_SHADOW_ENABLE_DEFAULT                              0x00000000
#define MPA_ECID1_SHADOW_ENABLE_ADDR                                 0x0000064c
#define MPA_ECID1_SHADOW_ENABLE_DEFAULT                              0x00000000
#define MPA_ECID2_SHADOW_ENABLE_ADDR                                 0x00000650
#define MPA_ECID2_SHADOW_ENABLE_DEFAULT                              0x00000000
#define MPA_ECID3_SHADOW_ENABLE_ADDR                                 0x00000654
#define MPA_ECID3_SHADOW_ENABLE_DEFAULT                              0x00000000
#define MPA_JTAG1_SHADOW_ENABLE_ADDR                                 0x00000658
#define MPA_JTAG1_SHADOW_ENABLE_DEFAULT                              0x00000000
#define ACPI_STS_ADDR                                                0x00000660
#define ACPI_STS_DEFAULT                                             0x00000000
#define ACPI_W1C_WR_ADDR                                             0x00000664
#define ACPI_W1C_WR_DEFAULT                                          0x00000000
#define ACPI_W1C_RD_ADDR                                             0x00000668
#define ACPI_W1C_RD_DEFAULT                                          0x00000000
#define ACPI_EN_RD_ADDR                                              0x00000670
#define ACPI_EN_RD_DEFAULT                                           0x00000000
#define ACPI_CNT_RD_ADDR                                             0x00000674
#define ACPI_CNT_RD_DEFAULT                                          0x00000000
#define ACPI_CTL0_ADDR                                               0x00000680
#define ACPI_CTL0_DEFAULT                                            0x00000000
#define ACPI_STS0_ADDR                                               0x00000684
#define ACPI_STS0_DEFAULT                                            0x00000000
#define ACPI_CTL1_ADDR                                               0x00000688
#define ACPI_CTL1_DEFAULT                                            0x00000000
#define ACPI_STS1_ADDR                                               0x0000068c
#define ACPI_STS1_DEFAULT                                            0x00000000
#define ACPI_CTL2_ADDR                                               0x00000690
#define ACPI_CTL2_DEFAULT                                            0x00000000
#define ACPI_STS2_ADDR                                               0x00000694
#define ACPI_STS2_DEFAULT                                            0x00000000
#define ACPI_CTL3_ADDR                                               0x00000698
#define ACPI_CTL3_DEFAULT                                            0x00000000
#define ACPI_STS3_ADDR                                               0x0000069c
#define ACPI_STS3_DEFAULT                                            0x00000000
#define ACPI_CTL4_ADDR                                               0x000006a0
#define ACPI_CTL4_DEFAULT                                            0x00000000
#define ACPI_STS4_ADDR                                               0x000006a4
#define ACPI_STS4_DEFAULT                                            0x00000000
#define ACPI_CTL5_ADDR                                               0x000006a8
#define ACPI_CTL5_DEFAULT                                            0x00000000
#define ACPI_STS5_ADDR                                               0x000006ac
#define ACPI_STS5_DEFAULT                                            0x00000000
#define ACPI_CTL6_ADDR                                               0x000006b0
#define ACPI_CTL6_DEFAULT                                            0x00000000
#define ACPI_STS6_ADDR                                               0x000006b4
#define ACPI_STS6_DEFAULT                                            0x00000000
#define ACPI_CTL7_ADDR                                               0x000006b8
#define ACPI_CTL7_DEFAULT                                            0x00000000
#define ACPI_STS7_ADDR                                               0x000006bc
#define ACPI_STS7_DEFAULT                                            0x00000000
#define ACPI_W1C_INTR_STS_ADDR                                       0x00000700
#define ACPI_W1C_INTR_STS_DEFAULT                                    0x00000000
#define ACPI_W1C_INTR_STSMASK_ADDR                                   0x00000704
#define ACPI_RW_INTR_STS0_ADDR                                       0x00000720
#define ACPI_RW_INTR_STS0_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS0MASK_ADDR                                   0x00000724
#define ACPI_RW_INTR_STS1_ADDR                                       0x00000728
#define ACPI_RW_INTR_STS1_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS1MASK_ADDR                                   0x0000072c
#define ACPI_RW_INTR_STS2_ADDR                                       0x00000730
#define ACPI_RW_INTR_STS2_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS2MASK_ADDR                                   0x00000734
#define ACPI_RW_INTR_STS3_ADDR                                       0x00000738
#define ACPI_RW_INTR_STS3_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS3MASK_ADDR                                   0x0000073c
#define ACPI_RW_INTR_STS4_ADDR                                       0x00000740
#define ACPI_RW_INTR_STS4_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS4MASK_ADDR                                   0x00000744
#define ACPI_RW_INTR_STS5_ADDR                                       0x00000748
#define ACPI_RW_INTR_STS5_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS5MASK_ADDR                                   0x0000074c
#define ACPI_RW_INTR_STS6_ADDR                                       0x00000750
#define ACPI_RW_INTR_STS6_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS6MASK_ADDR                                   0x00000754
#define ACPI_RW_INTR_STS7_ADDR                                       0x00000758
#define ACPI_RW_INTR_STS7_DEFAULT                                    0x00000000
#define ACPI_RW_INTR_STS7MASK_ADDR                                   0x0000075c
#define MPA_I2C_OVERRIDE_ADDR                                        0x00000760
#define MPA_I2C_OVERRIDE_DEFAULT                                     0x00000000
#define DBG_COLDRST_STEP_ADDR                                        0x00000800
#define DBG_COLDRST_STEP_DEFAULT                                     0x00000000
#define DBG_WARMRST_STEP_ADDR                                        0x00000804
#define DBG_WARMRST_STEP_DEFAULT                                     0x00000000
#define DBG_RSTSM_STS_ADDR                                           0x00000808
#define DBG_RSTSM_STS_DEFAULT                                        0x00000000
#define DBG_RSTSM_FORCE_ADDR                                         0x0000080c
#define DBG_RSTSM_FORCE_DEFAULT                                      0x00000000
#define DBG_BSC_DATA7_ADDR                                           0x00000810
#define DBG_BSC_DATA7_DEFAULT                                        0x00000000
#define DBG_BSC_DATA6_ADDR                                           0x00000814
#define DBG_BSC_DATA6_DEFAULT                                        0x00000000
#define DBG_BSC_DATA5_ADDR                                           0x00000818
#define DBG_BSC_DATA5_DEFAULT                                        0x00000000
#define DBG_BSC_DATA4_ADDR                                           0x0000081c
#define DBG_BSC_DATA4_DEFAULT                                        0x00000000
#define DBG_BSC_DATA3_ADDR                                           0x00000820
#define DBG_BSC_DATA3_DEFAULT                                        0x00000000
#define DBG_BSC_DATA2_ADDR                                           0x00000824
#define DBG_BSC_DATA2_DEFAULT                                        0x00000000
#define DBG_BSC_DATA1_ADDR                                           0x00000828
#define DBG_BSC_DATA1_DEFAULT                                        0x00000000
#define DBG_BSC_DATA0_ADDR                                           0x0000082c
#define DBG_BSC_DATA0_DEFAULT                                        0x00000000

/*	Register MPA_DMA_STAT	*/ 
/*	 Fields DMA_PENDING	 */
#define DMA_PENDING_WIDTH                                                     1
#define DMA_PENDING_SHIFT                                                     1
#define DMA_PENDING_MASK                                             0x00000002
#define DMA_PENDING_RD(src)                           (((src) & 0x00000002)>>1)
#define DMA_PENDING_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DMA_DONE	 */
#define DMA_DONE_WIDTH                                                        1
#define DMA_DONE_SHIFT                                                        0
#define DMA_DONE_MASK                                                0x00000001
#define DMA_DONE_RD(src)                                 (((src) & 0x00000001))
#define DMA_DONE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_PG_MAP0	*/ 
/*	 Fields COHERENT	 */
#define COHERENT0_WIDTH                                                       1
#define COHERENT0_SHIFT                                                      16
#define COHERENT0_MASK                                               0x00010000
#define COHERENT0_RD(src)                            (((src) & 0x00010000)>>16)
#define COHERENT0_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define COHERENT0_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields STASH	 */
#define STASH0_WIDTH                                                          1
#define STASH0_SHIFT                                                         15
#define STASH0_MASK                                                  0x00008000
#define STASH0_RD(src)                               (((src) & 0x00008000)>>15)
#define STASH0_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define STASH0_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MAPPER	 */
#define MAPPER0_WIDTH                                                        13
#define MAPPER0_SHIFT                                                         0
#define MAPPER0_MASK                                                 0x00001fff
#define MAPPER0_RD(src)                                  (((src) & 0x00001fff))
#define MAPPER0_WR(src)                             (((u32)(src)) & 0x00001fff)
#define MAPPER0_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register MPA_PG_MAP1	*/ 
/*	 Fields COHERENT	 */
#define COHERENT1_WIDTH                                                       1
#define COHERENT1_SHIFT                                                      16
#define COHERENT1_MASK                                               0x00010000
#define COHERENT1_RD(src)                            (((src) & 0x00010000)>>16)
#define COHERENT1_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define COHERENT1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields STASH	 */
#define STASH1_WIDTH                                                          1
#define STASH1_SHIFT                                                         15
#define STASH1_MASK                                                  0x00008000
#define STASH1_RD(src)                               (((src) & 0x00008000)>>15)
#define STASH1_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define STASH1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MAPPER	 */
#define MAPPER1_WIDTH                                                        13
#define MAPPER1_SHIFT                                                         0
#define MAPPER1_MASK                                                 0x00001fff
#define MAPPER1_RD(src)                                  (((src) & 0x00001fff))
#define MAPPER1_WR(src)                             (((u32)(src)) & 0x00001fff)
#define MAPPER1_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register MPA_PG_MAP2	*/ 
/*	 Fields COHERENT	 */
#define COHERENT2_WIDTH                                                       1
#define COHERENT2_SHIFT                                                      16
#define COHERENT2_MASK                                               0x00010000
#define COHERENT2_RD(src)                            (((src) & 0x00010000)>>16)
#define COHERENT2_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define COHERENT2_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields STASH	 */
#define STASH2_WIDTH                                                          1
#define STASH2_SHIFT                                                         15
#define STASH2_MASK                                                  0x00008000
#define STASH2_RD(src)                               (((src) & 0x00008000)>>15)
#define STASH2_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define STASH2_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MAPPER	 */
#define MAPPER2_WIDTH                                                        13
#define MAPPER2_SHIFT                                                         0
#define MAPPER2_MASK                                                 0x00001fff
#define MAPPER2_RD(src)                                  (((src) & 0x00001fff))
#define MAPPER2_WR(src)                             (((u32)(src)) & 0x00001fff)
#define MAPPER2_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register MPA_PG_MAP3	*/ 
/*	 Fields COHERENT	 */
#define COHERENT3_WIDTH                                                       1
#define COHERENT3_SHIFT                                                      16
#define COHERENT3_MASK                                               0x00010000
#define COHERENT3_RD(src)                            (((src) & 0x00010000)>>16)
#define COHERENT3_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define COHERENT3_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields STASH	 */
#define STASH3_WIDTH                                                          1
#define STASH3_SHIFT                                                         15
#define STASH3_MASK                                                  0x00008000
#define STASH3_RD(src)                               (((src) & 0x00008000)>>15)
#define STASH3_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define STASH3_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MAPPER	 */
#define MAPPER3_WIDTH                                                        13
#define MAPPER3_SHIFT                                                         0
#define MAPPER3_MASK                                                 0x00001fff
#define MAPPER3_RD(src)                                  (((src) & 0x00001fff))
#define MAPPER3_WR(src)                             (((u32)(src)) & 0x00001fff)
#define MAPPER3_SET(dst,src) \
                          (((dst) & ~0x00001fff) | (((u32)(src)) & 0x00001fff))

/*	Register MPA_VC	*/ 
/*	 Fields VC	 */
#define VC_WIDTH                                                              2
#define VC_SHIFT                                                              0
#define VC_MASK                                                      0x00000003
#define VC_RD(src)                                       (((src) & 0x00000003))
#define VC_WR(src)                                  (((u32)(src)) & 0x00000003)
#define VC_SET(dst,src) (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register MPA_OCM_CTL	*/ 
/*	 Fields OCM_WP	 */
#define OCM_WP_WIDTH                                                          1
#define OCM_WP_SHIFT                                                          0
#define OCM_WP_MASK                                                  0x00000001
#define OCM_WP_RD(src)                                   (((src) & 0x00000001))
#define OCM_WP_WR(src)                              (((u32)(src)) & 0x00000001)
#define OCM_WP_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register FORCE_SPDUP	*/ 
/*	 Fields SPDUP	 */
#define SPDUP_WIDTH                                                           1
#define SPDUP_SHIFT                                                           0
#define SPDUP_MASK                                                   0x00000001
#define SPDUP_RD(src)                                    (((src) & 0x00000001))
#define SPDUP_WR(src)                               (((u32)(src)) & 0x00000001)
#define SPDUP_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_QMI_INTSTAT_RO	*/ 
/*	 Fields QMI	 */
#define QMI_F2_WIDTH                                                          1
#define QMI_F2_SHIFT                                                         31
#define QMI_F2_MASK                                                  0x80000000
#define QMI_F2_RD(src)                               (((src) & 0x80000000)>>31)
#define QMI_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields WQ_AVAIL	 */
#define WQ_AVAIL_F2_WIDTH                                                     6
#define WQ_AVAIL_F2_SHIFT                                                    24
#define WQ_AVAIL_F2_MASK                                             0x3f000000
#define WQ_AVAIL_F2_RD(src)                          (((src) & 0x3f000000)>>24)
#define WQ_AVAIL_F2_SET(dst,src) \
                      (((dst) & ~0x3f000000) | (((u32)(src)<<24) & 0x3f000000))
/*	 Fields FP_AVAIL	 */
#define FP_AVAIL_F2_WIDTH                                                    20
#define FP_AVAIL_F2_SHIFT                                                     0
#define FP_AVAIL_F2_MASK                                             0x000fffff
#define FP_AVAIL_F2_RD(src)                              (((src) & 0x000fffff))
#define FP_AVAIL_F2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register MPA_QMI_STAT	*/ 
/*	 Fields FPDE_FULL64	 */
#define FPDE_FULL64_WIDTH                                                     1
#define FPDE_FULL64_SHIFT                                                     1
#define FPDE_FULL64_MASK                                             0x00000002
#define FPDE_FULL64_RD(src)                           (((src) & 0x00000002)>>1)
#define FPDE_FULL64_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields FPDE_FULL16	 */
#define FPDE_FULL16_WIDTH                                                     1
#define FPDE_FULL16_SHIFT                                                     0
#define FPDE_FULL16_MASK                                             0x00000001
#define FPDE_FULL16_RD(src)                              (((src) & 0x00000001))
#define FPDE_FULL16_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_QMI_FP_CTL	*/ 
/*	 Fields FP_FETCH	 */
#define FP_FETCH_WIDTH                                                        1
#define FP_FETCH_SHIFT                                                       31
#define FP_FETCH_MASK                                                0x80000000
#define FP_FETCH_RD(src)                             (((src) & 0x80000000)>>31)
#define FP_FETCH_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define FP_FETCH_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields FP_BID	 */
#define FP_BID_WIDTH                                                          5
#define FP_BID_SHIFT                                                          0
#define FP_BID_MASK                                                  0x0000001f
#define FP_BID_RD(src)                                   (((src) & 0x0000001f))
#define FP_BID_WR(src)                              (((u32)(src)) & 0x0000001f)
#define FP_BID_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register MPA_QMI_WQ_CTL	*/ 
/*	 Fields WQ_FETCH	 */
#define WQ_FETCH_WIDTH                                                        1
#define WQ_FETCH_SHIFT                                                       31
#define WQ_FETCH_MASK                                                0x80000000
#define WQ_FETCH_RD(src)                             (((src) & 0x80000000)>>31)
#define WQ_FETCH_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define WQ_FETCH_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields WQ_MSG_SIZE	 */
#define WQ_MSG_SIZE_WIDTH                                                     2
#define WQ_MSG_SIZE_SHIFT                                                     4
#define WQ_MSG_SIZE_MASK                                             0x00000030
#define WQ_MSG_SIZE_RD(src)                           (((src) & 0x00000030)>>4)
#define WQ_MSG_SIZE_WR(src)                      (((u32)(src)<<4) & 0x00000030)
#define WQ_MSG_SIZE_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields WQ_BID	 */
#define WQ_BID_WIDTH                                                          3
#define WQ_BID_SHIFT                                                          0
#define WQ_BID_MASK                                                  0x00000007
#define WQ_BID_RD(src)                                   (((src) & 0x00000007))
#define WQ_BID_WR(src)                              (((u32)(src)) & 0x00000007)
#define WQ_BID_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register MPA_QMI_FPDE_CTL	*/ 
/*	 Fields FP_DEALLOC	 */
#define FP_DEALLOC_WIDTH                                                      1
#define FP_DEALLOC_SHIFT                                                     31
#define FP_DEALLOC_MASK                                              0x80000000
#define FP_DEALLOC_RD(src)                           (((src) & 0x80000000)>>31)
#define FP_DEALLOC_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define FP_DEALLOC_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields FPDE_SIZE	 */
#define FPDE_SIZE_WIDTH                                                       2
#define FPDE_SIZE_SHIFT                                                       0
#define FPDE_SIZE_MASK                                               0x00000003
#define FPDE_SIZE_RD(src)                                (((src) & 0x00000003))
#define FPDE_SIZE_WR(src)                           (((u32)(src)) & 0x00000003)
#define FPDE_SIZE_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register MPA_QMI_CM_CTL	*/ 
/*	 Fields CM_SEND	 */
#define CM_SEND_WIDTH                                                         1
#define CM_SEND_SHIFT                                                        31
#define CM_SEND_MASK                                                 0x80000000
#define CM_SEND_RD(src)                              (((src) & 0x80000000)>>31)
#define CM_SEND_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define CM_SEND_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields CM_VC	 */
#define CM_VC_WIDTH                                                           2
#define CM_VC_SHIFT                                                          24
#define CM_VC_MASK                                                   0x03000000
#define CM_VC_RD(src)                                (((src) & 0x03000000)>>24)
#define CM_VC_WR(src)                           (((u32)(src)<<24) & 0x03000000)
#define CM_VC_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields CM_LERR	 */
#define CM_LERR_WIDTH                                                         5
#define CM_LERR_SHIFT                                                        19
#define CM_LERR_MASK                                                 0x00f80000
#define CM_LERR_RD(src)                              (((src) & 0x00f80000)>>19)
#define CM_LERR_WR(src)                         (((u32)(src)<<19) & 0x00f80000)
#define CM_LERR_SET(dst,src) \
                      (((dst) & ~0x00f80000) | (((u32)(src)<<19) & 0x00f80000))
/*	 Fields CM_LAST	 */
#define CM_LAST_WIDTH                                                         3
#define CM_LAST_SHIFT                                                        16
#define CM_LAST_MASK                                                 0x00070000
#define CM_LAST_RD(src)                              (((src) & 0x00070000)>>16)
#define CM_LAST_WR(src)                         (((u32)(src)<<16) & 0x00070000)
#define CM_LAST_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields CM_COHERENT	 */
#define CM_COHERENT_WIDTH                                                     1
#define CM_COHERENT_SHIFT                                                    14
#define CM_COHERENT_MASK                                             0x00004000
#define CM_COHERENT_RD(src)                          (((src) & 0x00004000)>>14)
#define CM_COHERENT_WR(src)                     (((u32)(src)<<14) & 0x00004000)
#define CM_COHERENT_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields CM_SIZE	 */
#define CM_SIZE_WIDTH                                                         2
#define CM_SIZE_SHIFT                                                        12
#define CM_SIZE_MASK                                                 0x00003000
#define CM_SIZE_RD(src)                              (((src) & 0x00003000)>>12)
#define CM_SIZE_WR(src)                         (((u32)(src)<<12) & 0x00003000)
#define CM_SIZE_SET(dst,src) \
                      (((dst) & ~0x00003000) | (((u32)(src)<<12) & 0x00003000))
/*	 Fields CM_QID	 */
#define CM_QID_WIDTH                                                         12
#define CM_QID_SHIFT                                                          0
#define CM_QID_MASK                                                  0x00000fff
#define CM_QID_RD(src)                                   (((src) & 0x00000fff))
#define CM_QID_WR(src)                              (((u32)(src)) & 0x00000fff)
#define CM_QID_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register MPA_QMI_FP_MSG0	*/ 
/*	 Fields FP_MSG	 */
#define FP_MSG0_WIDTH                                                        32
#define FP_MSG0_SHIFT                                                         0
#define FP_MSG0_MASK                                                 0xffffffff
#define FP_MSG0_RD(src)                                  (((src) & 0xffffffff))
#define FP_MSG0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FP_MSG1	*/ 
/*	 Fields FP_MSG	 */
#define FP_MSG1_WIDTH                                                        32
#define FP_MSG1_SHIFT                                                         0
#define FP_MSG1_MASK                                                 0xffffffff
#define FP_MSG1_RD(src)                                  (((src) & 0xffffffff))
#define FP_MSG1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FP_MSG2	*/ 
/*	 Fields FP_MSG	 */
#define FP_MSG2_WIDTH                                                        32
#define FP_MSG2_SHIFT                                                         0
#define FP_MSG2_MASK                                                 0xffffffff
#define FP_MSG2_RD(src)                                  (((src) & 0xffffffff))
#define FP_MSG2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FP_MSG3	*/ 
/*	 Fields FP_MSG	 */
#define FP_MSG3_WIDTH                                                        32
#define FP_MSG3_SHIFT                                                         0
#define FP_MSG3_MASK                                                 0xffffffff
#define FP_MSG3_RD(src)                                  (((src) & 0xffffffff))
#define FP_MSG3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG0	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG0_WIDTH                                                        32
#define WQ_MSG0_SHIFT                                                         0
#define WQ_MSG0_MASK                                                 0xffffffff
#define WQ_MSG0_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG1	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG1_WIDTH                                                        32
#define WQ_MSG1_SHIFT                                                         0
#define WQ_MSG1_MASK                                                 0xffffffff
#define WQ_MSG1_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG2	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG2_WIDTH                                                        32
#define WQ_MSG2_SHIFT                                                         0
#define WQ_MSG2_MASK                                                 0xffffffff
#define WQ_MSG2_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG3	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG3_WIDTH                                                        32
#define WQ_MSG3_SHIFT                                                         0
#define WQ_MSG3_MASK                                                 0xffffffff
#define WQ_MSG3_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG4	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG4_WIDTH                                                        32
#define WQ_MSG4_SHIFT                                                         0
#define WQ_MSG4_MASK                                                 0xffffffff
#define WQ_MSG4_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG5	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG5_WIDTH                                                        32
#define WQ_MSG5_SHIFT                                                         0
#define WQ_MSG5_MASK                                                 0xffffffff
#define WQ_MSG5_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG6	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG6_WIDTH                                                        32
#define WQ_MSG6_SHIFT                                                         0
#define WQ_MSG6_MASK                                                 0xffffffff
#define WQ_MSG6_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG7	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG7_WIDTH                                                        32
#define WQ_MSG7_SHIFT                                                         0
#define WQ_MSG7_MASK                                                 0xffffffff
#define WQ_MSG7_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG8	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG8_WIDTH                                                        32
#define WQ_MSG8_SHIFT                                                         0
#define WQ_MSG8_MASK                                                 0xffffffff
#define WQ_MSG8_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG9	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG9_WIDTH                                                        32
#define WQ_MSG9_SHIFT                                                         0
#define WQ_MSG9_MASK                                                 0xffffffff
#define WQ_MSG9_RD(src)                                  (((src) & 0xffffffff))
#define WQ_MSG9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG10	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG0_F1_WIDTH                                                     32
#define WQ_MSG0_F1_SHIFT                                                      0
#define WQ_MSG0_F1_MASK                                              0xffffffff
#define WQ_MSG0_F1_RD(src)                               (((src) & 0xffffffff))
#define WQ_MSG0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG11	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG1_F1_WIDTH                                                     32
#define WQ_MSG1_F1_SHIFT                                                      0
#define WQ_MSG1_F1_MASK                                              0xffffffff
#define WQ_MSG1_F1_RD(src)                               (((src) & 0xffffffff))
#define WQ_MSG1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG12	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG2_F1_WIDTH                                                     32
#define WQ_MSG2_F1_SHIFT                                                      0
#define WQ_MSG2_F1_MASK                                              0xffffffff
#define WQ_MSG2_F1_RD(src)                               (((src) & 0xffffffff))
#define WQ_MSG2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG13	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG3_F1_WIDTH                                                     32
#define WQ_MSG3_F1_SHIFT                                                      0
#define WQ_MSG3_F1_MASK                                              0xffffffff
#define WQ_MSG3_F1_RD(src)                               (((src) & 0xffffffff))
#define WQ_MSG3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG14	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG4_F1_WIDTH                                                     32
#define WQ_MSG4_F1_SHIFT                                                      0
#define WQ_MSG4_F1_MASK                                              0xffffffff
#define WQ_MSG4_F1_RD(src)                               (((src) & 0xffffffff))
#define WQ_MSG4_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_WQ_MSG15	*/ 
/*	 Fields WQ_MSG	 */
#define WQ_MSG5_F1_WIDTH                                                     32
#define WQ_MSG5_F1_SHIFT                                                      0
#define WQ_MSG5_F1_MASK                                              0xffffffff
#define WQ_MSG5_F1_RD(src)                               (((src) & 0xffffffff))
#define WQ_MSG5_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG0	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG0_WIDTH                                                      32
#define FPDE_MSG0_SHIFT                                                       0
#define FPDE_MSG0_MASK                                               0xffffffff
#define FPDE_MSG0_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG0_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG1	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG1_WIDTH                                                      32
#define FPDE_MSG1_SHIFT                                                       0
#define FPDE_MSG1_MASK                                               0xffffffff
#define FPDE_MSG1_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG1_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG2	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG2_WIDTH                                                      32
#define FPDE_MSG2_SHIFT                                                       0
#define FPDE_MSG2_MASK                                               0xffffffff
#define FPDE_MSG2_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG2_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG3	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG3_WIDTH                                                      32
#define FPDE_MSG3_SHIFT                                                       0
#define FPDE_MSG3_MASK                                               0xffffffff
#define FPDE_MSG3_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG3_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG4	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG4_WIDTH                                                      32
#define FPDE_MSG4_SHIFT                                                       0
#define FPDE_MSG4_MASK                                               0xffffffff
#define FPDE_MSG4_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG4_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG5	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG5_WIDTH                                                      32
#define FPDE_MSG5_SHIFT                                                       0
#define FPDE_MSG5_MASK                                               0xffffffff
#define FPDE_MSG5_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG5_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG6	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG6_WIDTH                                                      32
#define FPDE_MSG6_SHIFT                                                       0
#define FPDE_MSG6_MASK                                               0xffffffff
#define FPDE_MSG6_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG6_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG7	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG7_WIDTH                                                      32
#define FPDE_MSG7_SHIFT                                                       0
#define FPDE_MSG7_MASK                                               0xffffffff
#define FPDE_MSG7_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG7_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG8	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG8_WIDTH                                                      32
#define FPDE_MSG8_SHIFT                                                       0
#define FPDE_MSG8_MASK                                               0xffffffff
#define FPDE_MSG8_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG8_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG9	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG9_WIDTH                                                      32
#define FPDE_MSG9_SHIFT                                                       0
#define FPDE_MSG9_MASK                                               0xffffffff
#define FPDE_MSG9_RD(src)                                (((src) & 0xffffffff))
#define FPDE_MSG9_WR(src)                           (((u32)(src)) & 0xffffffff)
#define FPDE_MSG9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG10	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG0_F1_WIDTH                                                   32
#define FPDE_MSG0_F1_SHIFT                                                    0
#define FPDE_MSG0_F1_MASK                                            0xffffffff
#define FPDE_MSG0_F1_RD(src)                             (((src) & 0xffffffff))
#define FPDE_MSG0_F1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define FPDE_MSG0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG11	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG1_F1_WIDTH                                                   32
#define FPDE_MSG1_F1_SHIFT                                                    0
#define FPDE_MSG1_F1_MASK                                            0xffffffff
#define FPDE_MSG1_F1_RD(src)                             (((src) & 0xffffffff))
#define FPDE_MSG1_F1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define FPDE_MSG1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG12	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG2_F1_WIDTH                                                   32
#define FPDE_MSG2_F1_SHIFT                                                    0
#define FPDE_MSG2_F1_MASK                                            0xffffffff
#define FPDE_MSG2_F1_RD(src)                             (((src) & 0xffffffff))
#define FPDE_MSG2_F1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define FPDE_MSG2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG13	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG3_F1_WIDTH                                                   32
#define FPDE_MSG3_F1_SHIFT                                                    0
#define FPDE_MSG3_F1_MASK                                            0xffffffff
#define FPDE_MSG3_F1_RD(src)                             (((src) & 0xffffffff))
#define FPDE_MSG3_F1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define FPDE_MSG3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG14	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG4_F1_WIDTH                                                   32
#define FPDE_MSG4_F1_SHIFT                                                    0
#define FPDE_MSG4_F1_MASK                                            0xffffffff
#define FPDE_MSG4_F1_RD(src)                             (((src) & 0xffffffff))
#define FPDE_MSG4_F1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define FPDE_MSG4_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_FPDE_MSG15	*/ 
/*	 Fields FPDE_MSG	 */
#define FPDE_MSG5_F1_WIDTH                                                   32
#define FPDE_MSG5_F1_SHIFT                                                    0
#define FPDE_MSG5_F1_MASK                                            0xffffffff
#define FPDE_MSG5_F1_RD(src)                             (((src) & 0xffffffff))
#define FPDE_MSG5_F1_WR(src)                        (((u32)(src)) & 0xffffffff)
#define FPDE_MSG5_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_RIDA	*/ 
/*	 Fields QMI_RID7_VALID	 */
#define QMI_RID7_VALID_WIDTH                                                  1
#define QMI_RID7_VALID_SHIFT                                                 31
#define QMI_RID7_VALID_MASK                                          0x80000000
#define QMI_RID7_VALID_RD(src)                       (((src) & 0x80000000)>>31)
#define QMI_RID7_VALID_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields QMI_RID7_STAT	 */
#define QMI_RID7_STAT_WIDTH                                                   3
#define QMI_RID7_STAT_SHIFT                                                  28
#define QMI_RID7_STAT_MASK                                           0x70000000
#define QMI_RID7_STAT_RD(src)                        (((src) & 0x70000000)>>28)
#define QMI_RID7_STAT_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields QMI_RID6_VALID	 */
#define QMI_RID6_VALID_WIDTH                                                  1
#define QMI_RID6_VALID_SHIFT                                                 27
#define QMI_RID6_VALID_MASK                                          0x08000000
#define QMI_RID6_VALID_RD(src)                       (((src) & 0x08000000)>>27)
#define QMI_RID6_VALID_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields QMI_RID6_STAT	 */
#define QMI_RID6_STAT_WIDTH                                                   3
#define QMI_RID6_STAT_SHIFT                                                  24
#define QMI_RID6_STAT_MASK                                           0x07000000
#define QMI_RID6_STAT_RD(src)                        (((src) & 0x07000000)>>24)
#define QMI_RID6_STAT_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields QMI_RID5_VALID	 */
#define QMI_RID5_VALID_WIDTH                                                  1
#define QMI_RID5_VALID_SHIFT                                                 23
#define QMI_RID5_VALID_MASK                                          0x00800000
#define QMI_RID5_VALID_RD(src)                       (((src) & 0x00800000)>>23)
#define QMI_RID5_VALID_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields QMI_RID5_STAT	 */
#define QMI_RID5_STAT_WIDTH                                                   3
#define QMI_RID5_STAT_SHIFT                                                  20
#define QMI_RID5_STAT_MASK                                           0x00700000
#define QMI_RID5_STAT_RD(src)                        (((src) & 0x00700000)>>20)
#define QMI_RID5_STAT_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields QMI_RID4_VALID	 */
#define QMI_RID4_VALID_WIDTH                                                  1
#define QMI_RID4_VALID_SHIFT                                                 19
#define QMI_RID4_VALID_MASK                                          0x00080000
#define QMI_RID4_VALID_RD(src)                       (((src) & 0x00080000)>>19)
#define QMI_RID4_VALID_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields QMI_RID4_STAT	 */
#define QMI_RID4_STAT_WIDTH                                                   3
#define QMI_RID4_STAT_SHIFT                                                  16
#define QMI_RID4_STAT_MASK                                           0x00070000
#define QMI_RID4_STAT_RD(src)                        (((src) & 0x00070000)>>16)
#define QMI_RID4_STAT_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields QMI_RID3_VALID	 */
#define QMI_RID3_VALID_WIDTH                                                  1
#define QMI_RID3_VALID_SHIFT                                                 15
#define QMI_RID3_VALID_MASK                                          0x00008000
#define QMI_RID3_VALID_RD(src)                       (((src) & 0x00008000)>>15)
#define QMI_RID3_VALID_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields QMI_RID3_STAT	 */
#define QMI_RID3_STAT_WIDTH                                                   3
#define QMI_RID3_STAT_SHIFT                                                  12
#define QMI_RID3_STAT_MASK                                           0x00007000
#define QMI_RID3_STAT_RD(src)                        (((src) & 0x00007000)>>12)
#define QMI_RID3_STAT_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields QMI_RID2_VALID	 */
#define QMI_RID2_VALID_WIDTH                                                  1
#define QMI_RID2_VALID_SHIFT                                                 11
#define QMI_RID2_VALID_MASK                                          0x00000800
#define QMI_RID2_VALID_RD(src)                       (((src) & 0x00000800)>>11)
#define QMI_RID2_VALID_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields QMI_RID2_STAT	 */
#define QMI_RID2_STAT_WIDTH                                                   3
#define QMI_RID2_STAT_SHIFT                                                   8
#define QMI_RID2_STAT_MASK                                           0x00000700
#define QMI_RID2_STAT_RD(src)                         (((src) & 0x00000700)>>8)
#define QMI_RID2_STAT_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields QMI_RID1_VALID	 */
#define QMI_RID1_VALID_WIDTH                                                  1
#define QMI_RID1_VALID_SHIFT                                                  7
#define QMI_RID1_VALID_MASK                                          0x00000080
#define QMI_RID1_VALID_RD(src)                        (((src) & 0x00000080)>>7)
#define QMI_RID1_VALID_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields QMI_RID1_STAT	 */
#define QMI_RID1_STAT_WIDTH                                                   3
#define QMI_RID1_STAT_SHIFT                                                   4
#define QMI_RID1_STAT_MASK                                           0x00000070
#define QMI_RID1_STAT_RD(src)                         (((src) & 0x00000070)>>4)
#define QMI_RID1_STAT_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields QMI_RID0_VALID	 */
#define QMI_RID0_VALID_WIDTH                                                  1
#define QMI_RID0_VALID_SHIFT                                                  3
#define QMI_RID0_VALID_MASK                                          0x00000008
#define QMI_RID0_VALID_RD(src)                        (((src) & 0x00000008)>>3)
#define QMI_RID0_VALID_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields QMI_RID0_STAT	 */
#define QMI_RID0_STAT_WIDTH                                                   3
#define QMI_RID0_STAT_SHIFT                                                   0
#define QMI_RID0_STAT_MASK                                           0x00000007
#define QMI_RID0_STAT_RD(src)                            (((src) & 0x00000007))
#define QMI_RID0_STAT_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register MPA_QMI_RIDB	*/ 
/*	 Fields QMI_RID15_VALID	 */
#define QMI_RID15_VALID_WIDTH                                                 1
#define QMI_RID15_VALID_SHIFT                                                31
#define QMI_RID15_VALID_MASK                                         0x80000000
#define QMI_RID15_VALID_RD(src)                      (((src) & 0x80000000)>>31)
#define QMI_RID15_VALID_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields QMI_RID15_STAT	 */
#define QMI_RID15_STAT_WIDTH                                                  3
#define QMI_RID15_STAT_SHIFT                                                 28
#define QMI_RID15_STAT_MASK                                          0x70000000
#define QMI_RID15_STAT_RD(src)                       (((src) & 0x70000000)>>28)
#define QMI_RID15_STAT_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields QMI_RID14_VALID	 */
#define QMI_RID14_VALID_WIDTH                                                 1
#define QMI_RID14_VALID_SHIFT                                                27
#define QMI_RID14_VALID_MASK                                         0x08000000
#define QMI_RID14_VALID_RD(src)                      (((src) & 0x08000000)>>27)
#define QMI_RID14_VALID_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields QMI_RID14_STAT	 */
#define QMI_RID14_STAT_WIDTH                                                  3
#define QMI_RID14_STAT_SHIFT                                                 24
#define QMI_RID14_STAT_MASK                                          0x07000000
#define QMI_RID14_STAT_RD(src)                       (((src) & 0x07000000)>>24)
#define QMI_RID14_STAT_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields QMI_RID13_VALID	 */
#define QMI_RID13_VALID_WIDTH                                                 1
#define QMI_RID13_VALID_SHIFT                                                23
#define QMI_RID13_VALID_MASK                                         0x00800000
#define QMI_RID13_VALID_RD(src)                      (((src) & 0x00800000)>>23)
#define QMI_RID13_VALID_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields QMI_RID13_STAT	 */
#define QMI_RID13_STAT_WIDTH                                                  3
#define QMI_RID13_STAT_SHIFT                                                 20
#define QMI_RID13_STAT_MASK                                          0x00700000
#define QMI_RID13_STAT_RD(src)                       (((src) & 0x00700000)>>20)
#define QMI_RID13_STAT_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields QMI_RID12_VALID	 */
#define QMI_RID12_VALID_WIDTH                                                 1
#define QMI_RID12_VALID_SHIFT                                                19
#define QMI_RID12_VALID_MASK                                         0x00080000
#define QMI_RID12_VALID_RD(src)                      (((src) & 0x00080000)>>19)
#define QMI_RID12_VALID_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields QMI_RID12_STAT	 */
#define QMI_RID12_STAT_WIDTH                                                  3
#define QMI_RID12_STAT_SHIFT                                                 16
#define QMI_RID12_STAT_MASK                                          0x00070000
#define QMI_RID12_STAT_RD(src)                       (((src) & 0x00070000)>>16)
#define QMI_RID12_STAT_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields QMI_RID11_VALID	 */
#define QMI_RID11_VALID_WIDTH                                                 1
#define QMI_RID11_VALID_SHIFT                                                15
#define QMI_RID11_VALID_MASK                                         0x00008000
#define QMI_RID11_VALID_RD(src)                      (((src) & 0x00008000)>>15)
#define QMI_RID11_VALID_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields QMI_RID11_STAT	 */
#define QMI_RID11_STAT_WIDTH                                                  3
#define QMI_RID11_STAT_SHIFT                                                 12
#define QMI_RID11_STAT_MASK                                          0x00007000
#define QMI_RID11_STAT_RD(src)                       (((src) & 0x00007000)>>12)
#define QMI_RID11_STAT_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields QMI_RID10_VALID	 */
#define QMI_RID10_VALID_WIDTH                                                 1
#define QMI_RID10_VALID_SHIFT                                                11
#define QMI_RID10_VALID_MASK                                         0x00000800
#define QMI_RID10_VALID_RD(src)                      (((src) & 0x00000800)>>11)
#define QMI_RID10_VALID_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields QMI_RID10_STAT	 */
#define QMI_RID10_STAT_WIDTH                                                  3
#define QMI_RID10_STAT_SHIFT                                                  8
#define QMI_RID10_STAT_MASK                                          0x00000700
#define QMI_RID10_STAT_RD(src)                        (((src) & 0x00000700)>>8)
#define QMI_RID10_STAT_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields QMI_RID9_VALID	 */
#define QMI_RID9_VALID_WIDTH                                                  1
#define QMI_RID9_VALID_SHIFT                                                  7
#define QMI_RID9_VALID_MASK                                          0x00000080
#define QMI_RID9_VALID_RD(src)                        (((src) & 0x00000080)>>7)
#define QMI_RID9_VALID_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields QMI_RID9_STAT	 */
#define QMI_RID9_STAT_WIDTH                                                   3
#define QMI_RID9_STAT_SHIFT                                                   4
#define QMI_RID9_STAT_MASK                                           0x00000070
#define QMI_RID9_STAT_RD(src)                         (((src) & 0x00000070)>>4)
#define QMI_RID9_STAT_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields QMI_RID8_VALID	 */
#define QMI_RID8_VALID_WIDTH                                                  1
#define QMI_RID8_VALID_SHIFT                                                  3
#define QMI_RID8_VALID_MASK                                          0x00000008
#define QMI_RID8_VALID_RD(src)                        (((src) & 0x00000008)>>3)
#define QMI_RID8_VALID_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields QMI_RID8_STAT	 */
#define QMI_RID8_STAT_WIDTH                                                   3
#define QMI_RID8_STAT_SHIFT                                                   0
#define QMI_RID8_STAT_MASK                                           0x00000007
#define QMI_RID8_STAT_RD(src)                            (((src) & 0x00000007))
#define QMI_RID8_STAT_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register MPA_QMI_RIDC	*/ 
/*	 Fields QMI_ERRQ_VALID	 */
#define QMI_ERRQ_VALID_WIDTH                                                  1
#define QMI_ERRQ_VALID_SHIFT                                                  3
#define QMI_ERRQ_VALID_MASK                                          0x00000008
#define QMI_ERRQ_VALID_RD(src)                        (((src) & 0x00000008)>>3)
#define QMI_ERRQ_VALID_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields QMI_ERRQ_STAT	 */
#define QMI_ERRQ_STAT_WIDTH                                                   3
#define QMI_ERRQ_STAT_SHIFT                                                   0
#define QMI_ERRQ_STAT_MASK                                           0x00000007
#define QMI_ERRQ_STAT_RD(src)                            (((src) & 0x00000007))
#define QMI_ERRQ_STAT_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register MPA_QMI_RID_IENA	*/ 
/*	 Fields QMI_RID7_IEN	 */
#define QMI_RID7_IEN_WIDTH                                                    2
#define QMI_RID7_IEN_SHIFT                                                   28
#define QMI_RID7_IEN_MASK                                            0x30000000
#define QMI_RID7_IEN_RD(src)                         (((src) & 0x30000000)>>28)
#define QMI_RID7_IEN_WR(src)                    (((u32)(src)<<28) & 0x30000000)
#define QMI_RID7_IEN_SET(dst,src) \
                      (((dst) & ~0x30000000) | (((u32)(src)<<28) & 0x30000000))
/*	 Fields QMI_RID6_IEN	 */
#define QMI_RID6_IEN_WIDTH                                                    2
#define QMI_RID6_IEN_SHIFT                                                   24
#define QMI_RID6_IEN_MASK                                            0x03000000
#define QMI_RID6_IEN_RD(src)                         (((src) & 0x03000000)>>24)
#define QMI_RID6_IEN_WR(src)                    (((u32)(src)<<24) & 0x03000000)
#define QMI_RID6_IEN_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields QMI_RID5_IEN	 */
#define QMI_RID5_IEN_WIDTH                                                    2
#define QMI_RID5_IEN_SHIFT                                                   20
#define QMI_RID5_IEN_MASK                                            0x00300000
#define QMI_RID5_IEN_RD(src)                         (((src) & 0x00300000)>>20)
#define QMI_RID5_IEN_WR(src)                    (((u32)(src)<<20) & 0x00300000)
#define QMI_RID5_IEN_SET(dst,src) \
                      (((dst) & ~0x00300000) | (((u32)(src)<<20) & 0x00300000))
/*	 Fields QMI_RID4_IEN	 */
#define QMI_RID4_IEN_WIDTH                                                    2
#define QMI_RID4_IEN_SHIFT                                                   16
#define QMI_RID4_IEN_MASK                                            0x00030000
#define QMI_RID4_IEN_RD(src)                         (((src) & 0x00030000)>>16)
#define QMI_RID4_IEN_WR(src)                    (((u32)(src)<<16) & 0x00030000)
#define QMI_RID4_IEN_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields QMI_RID3_IEN	 */
#define QMI_RID3_IEN_WIDTH                                                    2
#define QMI_RID3_IEN_SHIFT                                                   12
#define QMI_RID3_IEN_MASK                                            0x00003000
#define QMI_RID3_IEN_RD(src)                         (((src) & 0x00003000)>>12)
#define QMI_RID3_IEN_WR(src)                    (((u32)(src)<<12) & 0x00003000)
#define QMI_RID3_IEN_SET(dst,src) \
                      (((dst) & ~0x00003000) | (((u32)(src)<<12) & 0x00003000))
/*	 Fields QMI_RID2_IEN	 */
#define QMI_RID2_IEN_WIDTH                                                    2
#define QMI_RID2_IEN_SHIFT                                                    8
#define QMI_RID2_IEN_MASK                                            0x00000300
#define QMI_RID2_IEN_RD(src)                          (((src) & 0x00000300)>>8)
#define QMI_RID2_IEN_WR(src)                     (((u32)(src)<<8) & 0x00000300)
#define QMI_RID2_IEN_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields QMI_RID1_IEN	 */
#define QMI_RID1_IEN_WIDTH                                                    2
#define QMI_RID1_IEN_SHIFT                                                    4
#define QMI_RID1_IEN_MASK                                            0x00000030
#define QMI_RID1_IEN_RD(src)                          (((src) & 0x00000030)>>4)
#define QMI_RID1_IEN_WR(src)                     (((u32)(src)<<4) & 0x00000030)
#define QMI_RID1_IEN_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields QMI_RID0_IEN	 */
#define QMI_RID0_IEN_WIDTH                                                    2
#define QMI_RID0_IEN_SHIFT                                                    0
#define QMI_RID0_IEN_MASK                                            0x00000003
#define QMI_RID0_IEN_RD(src)                             (((src) & 0x00000003))
#define QMI_RID0_IEN_WR(src)                        (((u32)(src)) & 0x00000003)
#define QMI_RID0_IEN_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register MPA_QMI_RID_IENB	*/ 
/*	 Fields QMI_RID15_IEN	 */
#define QMI_RID15_IEN_WIDTH                                                   2
#define QMI_RID15_IEN_SHIFT                                                  28
#define QMI_RID15_IEN_MASK                                           0x30000000
#define QMI_RID15_IEN_RD(src)                        (((src) & 0x30000000)>>28)
#define QMI_RID15_IEN_WR(src)                   (((u32)(src)<<28) & 0x30000000)
#define QMI_RID15_IEN_SET(dst,src) \
                      (((dst) & ~0x30000000) | (((u32)(src)<<28) & 0x30000000))
/*	 Fields QMI_RID14_IEN	 */
#define QMI_RID14_IEN_WIDTH                                                   2
#define QMI_RID14_IEN_SHIFT                                                  24
#define QMI_RID14_IEN_MASK                                           0x03000000
#define QMI_RID14_IEN_RD(src)                        (((src) & 0x03000000)>>24)
#define QMI_RID14_IEN_WR(src)                   (((u32)(src)<<24) & 0x03000000)
#define QMI_RID14_IEN_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields QMI_RID13_IEN	 */
#define QMI_RID13_IEN_WIDTH                                                   2
#define QMI_RID13_IEN_SHIFT                                                  20
#define QMI_RID13_IEN_MASK                                           0x00300000
#define QMI_RID13_IEN_RD(src)                        (((src) & 0x00300000)>>20)
#define QMI_RID13_IEN_WR(src)                   (((u32)(src)<<20) & 0x00300000)
#define QMI_RID13_IEN_SET(dst,src) \
                      (((dst) & ~0x00300000) | (((u32)(src)<<20) & 0x00300000))
/*	 Fields QMI_RID12_IEN	 */
#define QMI_RID12_IEN_WIDTH                                                   2
#define QMI_RID12_IEN_SHIFT                                                  16
#define QMI_RID12_IEN_MASK                                           0x00030000
#define QMI_RID12_IEN_RD(src)                        (((src) & 0x00030000)>>16)
#define QMI_RID12_IEN_WR(src)                   (((u32)(src)<<16) & 0x00030000)
#define QMI_RID12_IEN_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields QMI_RID11_IEN	 */
#define QMI_RID11_IEN_WIDTH                                                   2
#define QMI_RID11_IEN_SHIFT                                                  12
#define QMI_RID11_IEN_MASK                                           0x00003000
#define QMI_RID11_IEN_RD(src)                        (((src) & 0x00003000)>>12)
#define QMI_RID11_IEN_WR(src)                   (((u32)(src)<<12) & 0x00003000)
#define QMI_RID11_IEN_SET(dst,src) \
                      (((dst) & ~0x00003000) | (((u32)(src)<<12) & 0x00003000))
/*	 Fields QMI_RID10_IEN	 */
#define QMI_RID10_IEN_WIDTH                                                   2
#define QMI_RID10_IEN_SHIFT                                                   8
#define QMI_RID10_IEN_MASK                                           0x00000300
#define QMI_RID10_IEN_RD(src)                         (((src) & 0x00000300)>>8)
#define QMI_RID10_IEN_WR(src)                    (((u32)(src)<<8) & 0x00000300)
#define QMI_RID10_IEN_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields QMI_RID9_IEN	 */
#define QMI_RID9_IEN_WIDTH                                                    2
#define QMI_RID9_IEN_SHIFT                                                    4
#define QMI_RID9_IEN_MASK                                            0x00000030
#define QMI_RID9_IEN_RD(src)                          (((src) & 0x00000030)>>4)
#define QMI_RID9_IEN_WR(src)                     (((u32)(src)<<4) & 0x00000030)
#define QMI_RID9_IEN_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields QMI_RID8_IEN	 */
#define QMI_RID8_IEN_WIDTH                                                    2
#define QMI_RID8_IEN_SHIFT                                                    0
#define QMI_RID8_IEN_MASK                                            0x00000003
#define QMI_RID8_IEN_RD(src)                             (((src) & 0x00000003))
#define QMI_RID8_IEN_WR(src)                        (((u32)(src)) & 0x00000003)
#define QMI_RID8_IEN_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register MPA_QMI_RID_IENC	*/ 
/*	 Fields QMI_ERRQ_IEN	 */
#define QMI_ERRQ_IEN_WIDTH                                                    2
#define QMI_ERRQ_IEN_SHIFT                                                    0
#define QMI_ERRQ_IEN_MASK                                            0x00000003
#define QMI_ERRQ_IEN_RD(src)                             (((src) & 0x00000003))
#define QMI_ERRQ_IEN_WR(src)                        (((u32)(src)) & 0x00000003)
#define QMI_ERRQ_IEN_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register MPA_QMI_CM_MSG0	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG0_WIDTH                                                        32
#define CM_MSG0_SHIFT                                                         0
#define CM_MSG0_MASK                                                 0xffffffff
#define CM_MSG0_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG0_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG1	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG1_WIDTH                                                        32
#define CM_MSG1_SHIFT                                                         0
#define CM_MSG1_MASK                                                 0xffffffff
#define CM_MSG1_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG1_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG2	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG2_WIDTH                                                        32
#define CM_MSG2_SHIFT                                                         0
#define CM_MSG2_MASK                                                 0xffffffff
#define CM_MSG2_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG2_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG3	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG3_WIDTH                                                        32
#define CM_MSG3_SHIFT                                                         0
#define CM_MSG3_MASK                                                 0xffffffff
#define CM_MSG3_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG3_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG4	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG4_WIDTH                                                        32
#define CM_MSG4_SHIFT                                                         0
#define CM_MSG4_MASK                                                 0xffffffff
#define CM_MSG4_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG4_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG5	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG5_WIDTH                                                        32
#define CM_MSG5_SHIFT                                                         0
#define CM_MSG5_MASK                                                 0xffffffff
#define CM_MSG5_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG5_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG6	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG6_WIDTH                                                        32
#define CM_MSG6_SHIFT                                                         0
#define CM_MSG6_MASK                                                 0xffffffff
#define CM_MSG6_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG6_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG7	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG7_WIDTH                                                        32
#define CM_MSG7_SHIFT                                                         0
#define CM_MSG7_MASK                                                 0xffffffff
#define CM_MSG7_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG7_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG8	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG8_WIDTH                                                        32
#define CM_MSG8_SHIFT                                                         0
#define CM_MSG8_MASK                                                 0xffffffff
#define CM_MSG8_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG8_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG9	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG9_WIDTH                                                        32
#define CM_MSG9_SHIFT                                                         0
#define CM_MSG9_MASK                                                 0xffffffff
#define CM_MSG9_RD(src)                                  (((src) & 0xffffffff))
#define CM_MSG9_WR(src)                             (((u32)(src)) & 0xffffffff)
#define CM_MSG9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG10	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG0_F1_WIDTH                                                     32
#define CM_MSG0_F1_SHIFT                                                      0
#define CM_MSG0_F1_MASK                                              0xffffffff
#define CM_MSG0_F1_RD(src)                               (((src) & 0xffffffff))
#define CM_MSG0_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define CM_MSG0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG11	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG1_F1_WIDTH                                                     32
#define CM_MSG1_F1_SHIFT                                                      0
#define CM_MSG1_F1_MASK                                              0xffffffff
#define CM_MSG1_F1_RD(src)                               (((src) & 0xffffffff))
#define CM_MSG1_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define CM_MSG1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG12	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG2_F1_WIDTH                                                     32
#define CM_MSG2_F1_SHIFT                                                      0
#define CM_MSG2_F1_MASK                                              0xffffffff
#define CM_MSG2_F1_RD(src)                               (((src) & 0xffffffff))
#define CM_MSG2_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define CM_MSG2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG13	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG3_F1_WIDTH                                                     32
#define CM_MSG3_F1_SHIFT                                                      0
#define CM_MSG3_F1_MASK                                              0xffffffff
#define CM_MSG3_F1_RD(src)                               (((src) & 0xffffffff))
#define CM_MSG3_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define CM_MSG3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG14	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG4_F1_WIDTH                                                     32
#define CM_MSG4_F1_SHIFT                                                      0
#define CM_MSG4_F1_MASK                                              0xffffffff
#define CM_MSG4_F1_RD(src)                               (((src) & 0xffffffff))
#define CM_MSG4_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define CM_MSG4_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_QMI_CM_MSG15	*/ 
/*	 Fields CM_MSG	 */
#define CM_MSG5_F1_WIDTH                                                     32
#define CM_MSG5_F1_SHIFT                                                      0
#define CM_MSG5_F1_MASK                                              0xffffffff
#define CM_MSG5_F1_RD(src)                               (((src) & 0xffffffff))
#define CM_MSG5_F1_WR(src)                          (((u32)(src)) & 0xffffffff)
#define CM_MSG5_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_DRAM_CTL	*/ 
/*	 Fields LS_dis	 */
#define LS_DIS_WIDTH                                                          1
#define LS_DIS_SHIFT                                                         31
#define LS_DIS_MASK                                                  0x80000000
#define LS_DIS_RD(src)                               (((src) & 0x80000000)>>31)
#define LS_DIS_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define LS_DIS_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields DRAM_ALIAS	 */
#define DRAM_ALIAS_WIDTH                                                      1
#define DRAM_ALIAS_SHIFT                                                      1
#define DRAM_ALIAS_MASK                                              0x00000002
#define DRAM_ALIAS_RD(src)                            (((src) & 0x00000002)>>1)
#define DRAM_ALIAS_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define DRAM_ALIAS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DRAM_1WS	 */
#define DRAM_1WS_WIDTH                                                        1
#define DRAM_1WS_SHIFT                                                        0
#define DRAM_1WS_MASK                                                0x00000001
#define DRAM_1WS_RD(src)                                 (((src) & 0x00000001))
#define DRAM_1WS_WR(src)                            (((u32)(src)) & 0x00000001)
#define DRAM_1WS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AHB_SOC_EFUSE	*/ 
/*	 Fields SW_VERSION	 */
#define SW_VERSION_WIDTH                                                      8
#define SW_VERSION_SHIFT                                                     24
#define SW_VERSION_MASK                                              0xff000000
#define SW_VERSION_RD(src)                           (((src) & 0xff000000)>>24)
#define SW_VERSION_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields EFUSE23_21	 */
#define EFUSE23_21_WIDTH                                                      2
#define EFUSE23_21_SHIFT                                                     22
#define EFUSE23_21_MASK                                              0x00c00000
#define EFUSE23_21_RD(src)                           (((src) & 0x00c00000)>>22)
#define EFUSE23_21_SET(dst,src) \
                      (((dst) & ~0x00c00000) | (((u32)(src)<<22) & 0x00c00000))
/*	 Fields MPA_SEC_DISABLE	 */
#define MPA_SEC_DISABLE_WIDTH                                                 1
#define MPA_SEC_DISABLE_SHIFT                                                21
#define MPA_SEC_DISABLE_MASK                                         0x00200000
#define MPA_SEC_DISABLE_RD(src)                      (((src) & 0x00200000)>>21)
#define MPA_SEC_DISABLE_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields SATA_BYPASS	 */
#define SATA_BYPASS_WIDTH                                                     1
#define SATA_BYPASS_SHIFT                                                    20
#define SATA_BYPASS_MASK                                             0x00100000
#define SATA_BYPASS_RD(src)                          (((src) & 0x00100000)>>20)
#define SATA_BYPASS_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields OTP_DISABLE	 */
#define OTP_DISABLE_WIDTH                                                     1
#define OTP_DISABLE_SHIFT                                                    19
#define OTP_DISABLE_MASK                                             0x00080000
#define OTP_DISABLE_RD(src)                          (((src) & 0x00080000)>>19)
#define OTP_DISABLE_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC_DISABLE	 */
#define SEC_DISABLE_WIDTH                                                     1
#define SEC_DISABLE_SHIFT                                                    18
#define SEC_DISABLE_MASK                                             0x00040000
#define SEC_DISABLE_RD(src)                          (((src) & 0x00040000)>>18)
#define SEC_DISABLE_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields TPM_CFG	 */
#define TPM_CFG_WIDTH                                                         2
#define TPM_CFG_SHIFT                                                        16
#define TPM_CFG_MASK                                                 0x00030000
#define TPM_CFG_RD(src)                              (((src) & 0x00030000)>>16)
#define TPM_CFG_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields EFUSE15_4	 */
#define EFUSE15_4_WIDTH                                                      12
#define EFUSE15_4_SHIFT                                                       4
#define EFUSE15_4_MASK                                               0x0000fff0
#define EFUSE15_4_RD(src)                             (((src) & 0x0000fff0)>>4)
#define EFUSE15_4_SET(dst,src) \
                       (((dst) & ~0x0000fff0) | (((u32)(src)<<4) & 0x0000fff0))
/*	 Fields PMD3_DISABLE	 */
#define PMD3_DISABLE_WIDTH                                                    1
#define PMD3_DISABLE_SHIFT                                                    3
#define PMD3_DISABLE_MASK                                            0x00000008
#define PMD3_DISABLE_RD(src)                          (((src) & 0x00000008)>>3)
#define PMD3_DISABLE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields PMD2_DISABLE	 */
#define PMD2_DISABLE_WIDTH                                                    1
#define PMD2_DISABLE_SHIFT                                                    2
#define PMD2_DISABLE_MASK                                            0x00000004
#define PMD2_DISABLE_RD(src)                          (((src) & 0x00000004)>>2)
#define PMD2_DISABLE_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields PMD1_DISABLE	 */
#define PMD1_DISABLE_WIDTH                                                    1
#define PMD1_DISABLE_SHIFT                                                    1
#define PMD1_DISABLE_MASK                                            0x00000002
#define PMD1_DISABLE_RD(src)                          (((src) & 0x00000002)>>1)
#define PMD1_DISABLE_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PMD0_DISABLE	 */
#define PMD0_DISABLE_WIDTH                                                    1
#define PMD0_DISABLE_SHIFT                                                    0
#define PMD0_DISABLE_MASK                                            0x00000001
#define PMD0_DISABLE_RD(src)                             (((src) & 0x00000001))
#define PMD0_DISABLE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AHB_SOC_EFUSE1	*/ 
/*	 Fields EFUSE63_61	 */
#define EFUSE63_611_WIDTH                                                     3
#define EFUSE63_611_SHIFT                                                    29
#define EFUSE63_611_MASK                                             0xe0000000
#define EFUSE63_611_RD(src)                          (((src) & 0xe0000000)>>29)
#define EFUSE63_611_SET(dst,src) \
                      (((dst) & ~0xe0000000) | (((u32)(src)<<29) & 0xe0000000))
/*	 Fields SOC_DBG_DIS_PREAUTH	 */
#define SOC_DBG_DIS_PREAUTH1_WIDTH                                            1
#define SOC_DBG_DIS_PREAUTH1_SHIFT                                           28
#define SOC_DBG_DIS_PREAUTH1_MASK                                    0x10000000
#define SOC_DBG_DIS_PREAUTH1_RD(src)                 (((src) & 0x10000000)>>28)
#define SOC_DBG_DIS_PREAUTH1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SOC_DBG_DIS_PERM	 */
#define SOC_DBG_DIS_PERM1_WIDTH                                               1
#define SOC_DBG_DIS_PERM1_SHIFT                                              27
#define SOC_DBG_DIS_PERM1_MASK                                       0x08000000
#define SOC_DBG_DIS_PERM1_RD(src)                    (((src) & 0x08000000)>>27)
#define SOC_DBG_DIS_PERM1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields TMM_DBG_DIS_PREAUTH	 */
#define TMM_DBG_DIS_PREAUTH1_WIDTH                                            1
#define TMM_DBG_DIS_PREAUTH1_SHIFT                                           26
#define TMM_DBG_DIS_PREAUTH1_MASK                                    0x04000000
#define TMM_DBG_DIS_PREAUTH1_RD(src)                 (((src) & 0x04000000)>>26)
#define TMM_DBG_DIS_PREAUTH1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields TMM_DBG_DIS_PERM	 */
#define TMM_DBG_DIS_PERM1_WIDTH                                               1
#define TMM_DBG_DIS_PERM1_SHIFT                                              25
#define TMM_DBG_DIS_PERM1_MASK                                       0x02000000
#define TMM_DBG_DIS_PERM1_RD(src)                    (((src) & 0x02000000)>>25)
#define TMM_DBG_DIS_PERM1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SW_TMM	 */
#define SW_TMM1_WIDTH                                                        20
#define SW_TMM1_SHIFT                                                         5
#define SW_TMM1_MASK                                                 0x01ffffe0
#define SW_TMM1_RD(src)                               (((src) & 0x01ffffe0)>>5)
#define SW_TMM1_SET(dst,src) \
                       (((dst) & ~0x01ffffe0) | (((u32)(src)<<5) & 0x01ffffe0))
/*	 Fields EFUSE36_32	 */
#define EFUSE36_321_WIDTH                                                     5
#define EFUSE36_321_SHIFT                                                     0
#define EFUSE36_321_MASK                                             0x0000001f
#define EFUSE36_321_RD(src)                              (((src) & 0x0000001f))
#define EFUSE36_321_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register MPA_DMA_CTL	*/ 
/*	 Fields DMA_COHERENT	 */
#define DMA_COHERENT_WIDTH                                                    1
#define DMA_COHERENT_SHIFT                                                    3
#define DMA_COHERENT_MASK                                            0x00000008
#define DMA_COHERENT_RD(src)                          (((src) & 0x00000008)>>3)
#define DMA_COHERENT_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define DMA_COHERENT_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DMA_DIR	 */
#define DMA_DIR_WIDTH                                                         1
#define DMA_DIR_SHIFT                                                         1
#define DMA_DIR_MASK                                                 0x00000002
#define DMA_DIR_RD(src)                               (((src) & 0x00000002)>>1)
#define DMA_DIR_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define DMA_DIR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DMA_EN	 */
#define DMA_EN_WIDTH                                                          1
#define DMA_EN_SHIFT                                                          0
#define DMA_EN_MASK                                                  0x00000001
#define DMA_EN_RD(src)                                   (((src) & 0x00000001))
#define DMA_EN_WR(src)                              (((u32)(src)) & 0x00000001)
#define DMA_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register MPA_DMA_CNT	*/ 
/*	 Fields DMA_CNT	 */
#define DMA_CNT_WIDTH                                                        11
#define DMA_CNT_SHIFT                                                         0
#define DMA_CNT_MASK                                                 0x000007ff
#define DMA_CNT_RD(src)                                  (((src) & 0x000007ff))
#define DMA_CNT_WR(src)                             (((u32)(src)) & 0x000007ff)
#define DMA_CNT_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register MPA_DMA_LADDR	*/ 
/*	 Fields DMA_LADDR	 */
#define DMA_LADDR_WIDTH                                                      32
#define DMA_LADDR_SHIFT                                                       0
#define DMA_LADDR_MASK                                               0xffffffff
#define DMA_LADDR_RD(src)                                (((src) & 0xffffffff))
#define DMA_LADDR_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DMA_LADDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_DMA_HADDR	*/ 
/*	 Fields DMA_HADDR	 */
#define DMA_HADDR_WIDTH                                                      10
#define DMA_HADDR_SHIFT                                                       0
#define DMA_HADDR_MASK                                               0x000003ff
#define DMA_HADDR_RD(src)                                (((src) & 0x000003ff))
#define DMA_HADDR_WR(src)                           (((u32)(src)) & 0x000003ff)
#define DMA_HADDR_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register MPA_DMA_MADDR	*/ 
/*	 Fields DMA_MADDR	 */
#define DMA_MADDR_WIDTH                                                      32
#define DMA_MADDR_SHIFT                                                       0
#define DMA_MADDR_MASK                                               0xffffffff
#define DMA_MADDR_RD(src)                                (((src) & 0xffffffff))
#define DMA_MADDR_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DMA_MADDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register EFUSE_CTL	*/ 
/*	 Fields EFUSE_FETCH	 */
#define EFUSE_FETCH_WIDTH                                                     1
#define EFUSE_FETCH_SHIFT                                                    31
#define EFUSE_FETCH_MASK                                             0x80000000
#define EFUSE_FETCH_RD(src)                          (((src) & 0x80000000)>>31)
#define EFUSE_FETCH_WR(src)                     (((u32)(src)<<31) & 0x80000000)
#define EFUSE_FETCH_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields EFUSE_ADDR	 */
#define EFUSE_ADDR_WIDTH                                                      8
#define EFUSE_ADDR_SHIFT                                                      0
#define EFUSE_ADDR_MASK                                              0x000000ff
#define EFUSE_ADDR_RD(src)                               (((src) & 0x000000ff))
#define EFUSE_ADDR_WR(src)                          (((u32)(src)) & 0x000000ff)
#define EFUSE_ADDR_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register EFUSE_STAT	*/ 
/*	 Fields EFUSEFetchIP	 */
#define EFUSEFETCHIP_WIDTH                                                    1
#define EFUSEFETCHIP_SHIFT                                                    0
#define EFUSEFETCHIP_MASK                                            0x00000001
#define EFUSEFETCHIP_RD(src)                             (((src) & 0x00000001))
#define EFUSEFETCHIP_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register EFUSE_RDDATA	*/ 
/*	 Fields EFUSE_RDDATA	 */
#define EFUSE_RDDATA_WIDTH                                                   32
#define EFUSE_RDDATA_SHIFT                                                    0
#define EFUSE_RDDATA_MASK                                            0xffffffff
#define EFUSE_RDDATA_RD(src)                             (((src) & 0xffffffff))
#define EFUSE_RDDATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TPM_CTL	*/ 
/*	 Fields DRAM_FACC	 */
#define DRAM_FACC_WIDTH                                                       1
#define DRAM_FACC_SHIFT                                                       1
#define DRAM_FACC_MASK                                               0x00000002
#define DRAM_FACC_RD(src)                             (((src) & 0x00000002)>>1)
#define DRAM_FACC_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define DRAM_FACC_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields RUNTIME_AUTH	 */
#define RUNTIME_AUTH_WIDTH                                                    1
#define RUNTIME_AUTH_SHIFT                                                    0
#define RUNTIME_AUTH_MASK                                            0x00000001
#define RUNTIME_AUTH_RD(src)                             (((src) & 0x00000001))
#define RUNTIME_AUTH_WR(src)                        (((u32)(src)) & 0x00000001)
#define RUNTIME_AUTH_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AHB_PINSTRAP	*/ 
/*	 Fields BSC_DIS	 */
#define BSC_DIS_F4_WIDTH                                                      1
#define BSC_DIS_F4_SHIFT                                                     31
#define BSC_DIS_F4_MASK                                              0x80000000
#define BSC_DIS_F4_RD(src)                           (((src) & 0x80000000)>>31)
#define BSC_DIS_F4_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields IIC_CODE	 */
#define IIC_CODE_F2_WIDTH                                                     1
#define IIC_CODE_F2_SHIFT                                                    26
#define IIC_CODE_F2_MASK                                             0x04000000
#define IIC_CODE_F2_RD(src)                          (((src) & 0x04000000)>>26)
#define IIC_CODE_F2_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields IO_CLKCFG	 */
#define IO_CLKCFG_F2_WIDTH                                                    2
#define IO_CLKCFG_F2_SHIFT                                                   24
#define IO_CLKCFG_F2_MASK                                            0x03000000
#define IO_CLKCFG_F2_RD(src)                         (((src) & 0x03000000)>>24)
#define IO_CLKCFG_F2_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields CPU_CLKCFG	 */
#define CPU_CLKCFG_F2_WIDTH                                                   3
#define CPU_CLKCFG_F2_SHIFT                                                  20
#define CPU_CLKCFG_F2_MASK                                           0x00700000
#define CPU_CLKCFG_F2_RD(src)                        (((src) & 0x00700000)>>20)
#define CPU_CLKCFG_F2_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields MPA_IRAM_SIZE	 */
#define MPA_IRAM_SIZE_F4_WIDTH                                                2
#define MPA_IRAM_SIZE_F4_SHIFT                                               16
#define MPA_IRAM_SIZE_F4_MASK                                        0x00030000
#define MPA_IRAM_SIZE_F4_RD(src)                     (((src) & 0x00030000)>>16)
#define MPA_IRAM_SIZE_F4_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields MPA_IROM_1WS	 */
#define MPA_IROM_1WS_F4_WIDTH                                                 1
#define MPA_IROM_1WS_F4_SHIFT                                                15
#define MPA_IROM_1WS_F4_MASK                                         0x00008000
#define MPA_IROM_1WS_F4_RD(src)                      (((src) & 0x00008000)>>15)
#define MPA_IROM_1WS_F4_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields TEST_TPM_ENABLE	 */
#define TEST_TPM_ENABLE_F2_WIDTH                                              1
#define TEST_TPM_ENABLE_F2_SHIFT                                             14
#define TEST_TPM_ENABLE_F2_MASK                                      0x00004000
#define TEST_TPM_ENABLE_F2_RD(src)                   (((src) & 0x00004000)>>14)
#define TEST_TPM_ENABLE_F2_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields COP_DOMAIN_DIS	 */
#define COP_DOMAIN_DIS_F2_WIDTH                                               1
#define COP_DOMAIN_DIS_F2_SHIFT                                              12
#define COP_DOMAIN_DIS_F2_MASK                                       0x00001000
#define COP_DOMAIN_DIS_F2_RD(src)                    (((src) & 0x00001000)>>12)
#define COP_DOMAIN_DIS_F2_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields XGE_DOMAIN_DIS	 */
#define XGE_DOMAIN_DIS_F2_WIDTH                                               1
#define XGE_DOMAIN_DIS_F2_SHIFT                                              11
#define XGE_DOMAIN_DIS_F2_MASK                                       0x00000800
#define XGE_DOMAIN_DIS_F2_RD(src)                    (((src) & 0x00000800)>>11)
#define XGE_DOMAIN_DIS_F2_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields PCI_DOMAIN_DIS	 */
#define PCI_DOMAIN_DIS_F2_WIDTH                                               1
#define PCI_DOMAIN_DIS_F2_SHIFT                                              10
#define PCI_DOMAIN_DIS_F2_MASK                                       0x00000400
#define PCI_DOMAIN_DIS_F2_RD(src)                    (((src) & 0x00000400)>>10)
#define PCI_DOMAIN_DIS_F2_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields ROM_TYP	 */
#define ROM_TYP_F2_WIDTH                                                      4
#define ROM_TYP_F2_SHIFT                                                      0
#define ROM_TYP_F2_MASK                                              0x0000000f
#define ROM_TYP_F2_RD(src)                               (((src) & 0x0000000f))
#define ROM_TYP_F2_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register MPA_AHB_IRAM_ADDR	*/ 
/*	 Fields AHB_IRAM_ADDR	 */
#define AHB_IRAM_ADDR_WIDTH                                                  16
#define AHB_IRAM_ADDR_SHIFT                                                   0
#define AHB_IRAM_ADDR_MASK                                           0x0000ffff
#define AHB_IRAM_ADDR_RD(src)                            (((src) & 0x0000ffff))
#define AHB_IRAM_ADDR_WR(src)                       (((u32)(src)) & 0x0000ffff)
#define AHB_IRAM_ADDR_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register MPA_AHB_IRAM_DATA	*/ 
/*	 Fields AHB_IRAM_DATA	 */
#define AHB_IRAM_DATA_WIDTH                                                  32
#define AHB_IRAM_DATA_SHIFT                                                   0
#define AHB_IRAM_DATA_MASK                                           0xffffffff
#define AHB_IRAM_DATA_RD(src)                            (((src) & 0xffffffff))
#define AHB_IRAM_DATA_WR(src)                       (((u32)(src)) & 0xffffffff)
#define AHB_IRAM_DATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_AHB_IRAM_RDATA	*/ 
/*	 Fields AHB_IRAM_RDATA	 */
#define AHB_IRAM_RDATA_WIDTH                                                 32
#define AHB_IRAM_RDATA_SHIFT                                                  0
#define AHB_IRAM_RDATA_MASK                                          0xffffffff
#define AHB_IRAM_RDATA_RD(src)                           (((src) & 0xffffffff))
#define AHB_IRAM_RDATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_GC_CLK_MODE	*/ 
/*	 Fields CLK_MODE	 */
#define REGSPEC_CLK_MODE_WIDTH                                                1
#define REGSPEC_CLK_MODE_SHIFT                                                0
#define REGSPEC_CLK_MODE_MASK                                        0x00000001
#define REGSPEC_CLK_MODE_RD(src)                         (((src) & 0x00000001))
#define REGSPEC_CLK_MODE_WR(src)                    (((u32)(src)) & 0x00000001)
#define REGSPEC_CLK_MODE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register DB0_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_WIDTH                                                          32
#define DB_IN_SHIFT                                                           0
#define DB_IN_MASK                                                   0xffffffff
#define DB_IN_RD(src)                                    (((src) & 0xffffffff))
#define DB_IN_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB0_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_WIDTH                                                        32
#define DB_DIN0_SHIFT                                                         0
#define DB_DIN0_MASK                                                 0xffffffff
#define DB_DIN0_RD(src)                                  (((src) & 0xffffffff))
#define DB_DIN0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB0_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_WIDTH                                                        32
#define DB_DIN1_SHIFT                                                         0
#define DB_DIN1_MASK                                                 0xffffffff
#define DB_DIN1_RD(src)                                  (((src) & 0xffffffff))
#define DB_DIN1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB0_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_WIDTH                                                         32
#define DB_OUT_SHIFT                                                          0
#define DB_OUT_MASK                                                  0xffffffff
#define DB_OUT_RD(src)                                   (((src) & 0xffffffff))
#define DB_OUT_WR(src)                              (((u32)(src)) & 0xffffffff)
#define DB_OUT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB0_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_WIDTH                                                       32
#define DB_DOUT0_SHIFT                                                        0
#define DB_DOUT0_MASK                                                0xffffffff
#define DB_DOUT0_RD(src)                                 (((src) & 0xffffffff))
#define DB_DOUT0_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB0_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_WIDTH                                                       32
#define DB_DOUT1_SHIFT                                                        0
#define DB_DOUT1_MASK                                                0xffffffff
#define DB_DOUT1_RD(src)                                 (((src) & 0xffffffff))
#define DB_DOUT1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB1_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F1_WIDTH                                                       32
#define DB_IN_F1_SHIFT                                                        0
#define DB_IN_F1_MASK                                                0xffffffff
#define DB_IN_F1_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB1_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F1_WIDTH                                                     32
#define DB_DIN0_F1_SHIFT                                                      0
#define DB_DIN0_F1_MASK                                              0xffffffff
#define DB_DIN0_F1_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB1_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F1_WIDTH                                                     32
#define DB_DIN1_F1_SHIFT                                                      0
#define DB_DIN1_F1_MASK                                              0xffffffff
#define DB_DIN1_F1_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB1_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F1_WIDTH                                                      32
#define DB_OUT_F1_SHIFT                                                       0
#define DB_OUT_F1_MASK                                               0xffffffff
#define DB_OUT_F1_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F1_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB1_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F1_WIDTH                                                    32
#define DB_DOUT0_F1_SHIFT                                                     0
#define DB_DOUT0_F1_MASK                                             0xffffffff
#define DB_DOUT0_F1_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB1_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F1_WIDTH                                                    32
#define DB_DOUT1_F1_SHIFT                                                     0
#define DB_DOUT1_F1_MASK                                             0xffffffff
#define DB_DOUT1_F1_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB2_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F2_WIDTH                                                       32
#define DB_IN_F2_SHIFT                                                        0
#define DB_IN_F2_MASK                                                0xffffffff
#define DB_IN_F2_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB2_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F2_WIDTH                                                     32
#define DB_DIN0_F2_SHIFT                                                      0
#define DB_DIN0_F2_MASK                                              0xffffffff
#define DB_DIN0_F2_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB2_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F2_WIDTH                                                     32
#define DB_DIN1_F2_SHIFT                                                      0
#define DB_DIN1_F2_MASK                                              0xffffffff
#define DB_DIN1_F2_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB2_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F2_WIDTH                                                      32
#define DB_OUT_F2_SHIFT                                                       0
#define DB_OUT_F2_MASK                                               0xffffffff
#define DB_OUT_F2_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F2_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB2_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F2_WIDTH                                                    32
#define DB_DOUT0_F2_SHIFT                                                     0
#define DB_DOUT0_F2_MASK                                             0xffffffff
#define DB_DOUT0_F2_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F2_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB2_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F2_WIDTH                                                    32
#define DB_DOUT1_F2_SHIFT                                                     0
#define DB_DOUT1_F2_MASK                                             0xffffffff
#define DB_DOUT1_F2_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F2_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB3_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F3_WIDTH                                                       32
#define DB_IN_F3_SHIFT                                                        0
#define DB_IN_F3_MASK                                                0xffffffff
#define DB_IN_F3_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB3_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F3_WIDTH                                                     32
#define DB_DIN0_F3_SHIFT                                                      0
#define DB_DIN0_F3_MASK                                              0xffffffff
#define DB_DIN0_F3_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB3_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F3_WIDTH                                                     32
#define DB_DIN1_F3_SHIFT                                                      0
#define DB_DIN1_F3_MASK                                              0xffffffff
#define DB_DIN1_F3_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB3_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F3_WIDTH                                                      32
#define DB_OUT_F3_SHIFT                                                       0
#define DB_OUT_F3_MASK                                               0xffffffff
#define DB_OUT_F3_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F3_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB3_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F3_WIDTH                                                    32
#define DB_DOUT0_F3_SHIFT                                                     0
#define DB_DOUT0_F3_MASK                                             0xffffffff
#define DB_DOUT0_F3_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F3_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB3_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F3_WIDTH                                                    32
#define DB_DOUT1_F3_SHIFT                                                     0
#define DB_DOUT1_F3_MASK                                             0xffffffff
#define DB_DOUT1_F3_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F3_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB4_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F4_WIDTH                                                       32
#define DB_IN_F4_SHIFT                                                        0
#define DB_IN_F4_MASK                                                0xffffffff
#define DB_IN_F4_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB4_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F4_WIDTH                                                     32
#define DB_DIN0_F4_SHIFT                                                      0
#define DB_DIN0_F4_MASK                                              0xffffffff
#define DB_DIN0_F4_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB4_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F4_WIDTH                                                     32
#define DB_DIN1_F4_SHIFT                                                      0
#define DB_DIN1_F4_MASK                                              0xffffffff
#define DB_DIN1_F4_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB4_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F4_WIDTH                                                      32
#define DB_OUT_F4_SHIFT                                                       0
#define DB_OUT_F4_MASK                                               0xffffffff
#define DB_OUT_F4_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F4_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB4_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F4_WIDTH                                                    32
#define DB_DOUT0_F4_SHIFT                                                     0
#define DB_DOUT0_F4_MASK                                             0xffffffff
#define DB_DOUT0_F4_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F4_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB4_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F4_WIDTH                                                    32
#define DB_DOUT1_F4_SHIFT                                                     0
#define DB_DOUT1_F4_MASK                                             0xffffffff
#define DB_DOUT1_F4_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F4_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB5_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F5_WIDTH                                                       32
#define DB_IN_F5_SHIFT                                                        0
#define DB_IN_F5_MASK                                                0xffffffff
#define DB_IN_F5_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB5_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F5_WIDTH                                                     32
#define DB_DIN0_F5_SHIFT                                                      0
#define DB_DIN0_F5_MASK                                              0xffffffff
#define DB_DIN0_F5_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB5_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F5_WIDTH                                                     32
#define DB_DIN1_F5_SHIFT                                                      0
#define DB_DIN1_F5_MASK                                              0xffffffff
#define DB_DIN1_F5_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB5_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F5_WIDTH                                                      32
#define DB_OUT_F5_SHIFT                                                       0
#define DB_OUT_F5_MASK                                               0xffffffff
#define DB_OUT_F5_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F5_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB5_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F5_WIDTH                                                    32
#define DB_DOUT0_F5_SHIFT                                                     0
#define DB_DOUT0_F5_MASK                                             0xffffffff
#define DB_DOUT0_F5_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F5_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB5_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F5_WIDTH                                                    32
#define DB_DOUT1_F5_SHIFT                                                     0
#define DB_DOUT1_F5_MASK                                             0xffffffff
#define DB_DOUT1_F5_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F5_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB6_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F6_WIDTH                                                       32
#define DB_IN_F6_SHIFT                                                        0
#define DB_IN_F6_MASK                                                0xffffffff
#define DB_IN_F6_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB6_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F6_WIDTH                                                     32
#define DB_DIN0_F6_SHIFT                                                      0
#define DB_DIN0_F6_MASK                                              0xffffffff
#define DB_DIN0_F6_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB6_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F6_WIDTH                                                     32
#define DB_DIN1_F6_SHIFT                                                      0
#define DB_DIN1_F6_MASK                                              0xffffffff
#define DB_DIN1_F6_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB6_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F6_WIDTH                                                      32
#define DB_OUT_F6_SHIFT                                                       0
#define DB_OUT_F6_MASK                                               0xffffffff
#define DB_OUT_F6_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F6_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB6_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F6_WIDTH                                                    32
#define DB_DOUT0_F6_SHIFT                                                     0
#define DB_DOUT0_F6_MASK                                             0xffffffff
#define DB_DOUT0_F6_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F6_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB6_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F6_WIDTH                                                    32
#define DB_DOUT1_F6_SHIFT                                                     0
#define DB_DOUT1_F6_MASK                                             0xffffffff
#define DB_DOUT1_F6_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F6_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB7_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F7_WIDTH                                                       32
#define DB_IN_F7_SHIFT                                                        0
#define DB_IN_F7_MASK                                                0xffffffff
#define DB_IN_F7_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB7_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F7_WIDTH                                                     32
#define DB_DIN0_F7_SHIFT                                                      0
#define DB_DIN0_F7_MASK                                              0xffffffff
#define DB_DIN0_F7_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB7_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F7_WIDTH                                                     32
#define DB_DIN1_F7_SHIFT                                                      0
#define DB_DIN1_F7_MASK                                              0xffffffff
#define DB_DIN1_F7_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB7_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F7_WIDTH                                                      32
#define DB_OUT_F7_SHIFT                                                       0
#define DB_OUT_F7_MASK                                               0xffffffff
#define DB_OUT_F7_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F7_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB7_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F7_WIDTH                                                    32
#define DB_DOUT0_F7_SHIFT                                                     0
#define DB_DOUT0_F7_MASK                                             0xffffffff
#define DB_DOUT0_F7_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F7_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB7_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F7_WIDTH                                                    32
#define DB_DOUT1_F7_SHIFT                                                     0
#define DB_DOUT1_F7_MASK                                             0xffffffff
#define DB_DOUT1_F7_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F7_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB8_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F8_WIDTH                                                       32
#define DB_IN_F8_SHIFT                                                        0
#define DB_IN_F8_MASK                                                0xffffffff
#define DB_IN_F8_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB8_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F8_WIDTH                                                     32
#define DB_DIN0_F8_SHIFT                                                      0
#define DB_DIN0_F8_MASK                                              0xffffffff
#define DB_DIN0_F8_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB8_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F8_WIDTH                                                     32
#define DB_DIN1_F8_SHIFT                                                      0
#define DB_DIN1_F8_MASK                                              0xffffffff
#define DB_DIN1_F8_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB8_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F8_WIDTH                                                      32
#define DB_OUT_F8_SHIFT                                                       0
#define DB_OUT_F8_MASK                                               0xffffffff
#define DB_OUT_F8_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F8_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB8_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F8_WIDTH                                                    32
#define DB_DOUT0_F8_SHIFT                                                     0
#define DB_DOUT0_F8_MASK                                             0xffffffff
#define DB_DOUT0_F8_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F8_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB8_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F8_WIDTH                                                    32
#define DB_DOUT1_F8_SHIFT                                                     0
#define DB_DOUT1_F8_MASK                                             0xffffffff
#define DB_DOUT1_F8_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F8_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB9_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F9_WIDTH                                                       32
#define DB_IN_F9_SHIFT                                                        0
#define DB_IN_F9_MASK                                                0xffffffff
#define DB_IN_F9_RD(src)                                 (((src) & 0xffffffff))
#define DB_IN_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB9_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F9_WIDTH                                                     32
#define DB_DIN0_F9_SHIFT                                                      0
#define DB_DIN0_F9_MASK                                              0xffffffff
#define DB_DIN0_F9_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN0_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB9_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F9_WIDTH                                                     32
#define DB_DIN1_F9_SHIFT                                                      0
#define DB_DIN1_F9_MASK                                              0xffffffff
#define DB_DIN1_F9_RD(src)                               (((src) & 0xffffffff))
#define DB_DIN1_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB9_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F9_WIDTH                                                      32
#define DB_OUT_F9_SHIFT                                                       0
#define DB_OUT_F9_MASK                                               0xffffffff
#define DB_OUT_F9_RD(src)                                (((src) & 0xffffffff))
#define DB_OUT_F9_WR(src)                           (((u32)(src)) & 0xffffffff)
#define DB_OUT_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB9_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F9_WIDTH                                                    32
#define DB_DOUT0_F9_SHIFT                                                     0
#define DB_DOUT0_F9_MASK                                             0xffffffff
#define DB_DOUT0_F9_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT0_F9_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DB9_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F9_WIDTH                                                    32
#define DB_DOUT1_F9_SHIFT                                                     0
#define DB_DOUT1_F9_MASK                                             0xffffffff
#define DB_DOUT1_F9_RD(src)                              (((src) & 0xffffffff))
#define DB_DOUT1_F9_WR(src)                         (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_EFUSE0_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_WIDTH                                                 32
#define REGSPEC_ENABLE_SHIFT                                                  0
#define REGSPEC_ENABLE_MASK                                          0xffffffff
#define REGSPEC_ENABLE_RD(src)                           (((src) & 0xffffffff))
#define REGSPEC_ENABLE_WR(src)                      (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_EFUSE1_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F1_WIDTH                                              32
#define REGSPEC_ENABLE_F1_SHIFT                                               0
#define REGSPEC_ENABLE_F1_MASK                                       0xffffffff
#define REGSPEC_ENABLE_F1_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_ENABLE_F1_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ECID0_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F2_WIDTH                                              32
#define REGSPEC_ENABLE_F2_SHIFT                                               0
#define REGSPEC_ENABLE_F2_MASK                                       0xffffffff
#define REGSPEC_ENABLE_F2_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_ENABLE_F2_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ECID1_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F3_WIDTH                                              32
#define REGSPEC_ENABLE_F3_SHIFT                                               0
#define REGSPEC_ENABLE_F3_MASK                                       0xffffffff
#define REGSPEC_ENABLE_F3_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_ENABLE_F3_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ECID2_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F4_WIDTH                                              32
#define REGSPEC_ENABLE_F4_SHIFT                                               0
#define REGSPEC_ENABLE_F4_MASK                                       0xffffffff
#define REGSPEC_ENABLE_F4_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_ENABLE_F4_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_ECID3_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F5_WIDTH                                              32
#define REGSPEC_ENABLE_F5_SHIFT                                               0
#define REGSPEC_ENABLE_F5_MASK                                       0xffffffff
#define REGSPEC_ENABLE_F5_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_ENABLE_F5_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register MPA_JTAG1_SHADOW_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F6_WIDTH                                              32
#define REGSPEC_ENABLE_F6_SHIFT                                               0
#define REGSPEC_ENABLE_F6_MASK                                       0xffffffff
#define REGSPEC_ENABLE_F6_RD(src)                        (((src) & 0xffffffff))
#define REGSPEC_ENABLE_F6_WR(src)                   (((u32)(src)) & 0xffffffff)
#define REGSPEC_ENABLE_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS	*/ 
/*	 Fields ACPI_W1C_STS	 */
#define ACPI_W1C_STS_WIDTH                                                    1
#define ACPI_W1C_STS_SHIFT                                                    8
#define ACPI_W1C_STS_MASK                                            0x00000100
#define ACPI_W1C_STS_RD(src)                          (((src) & 0x00000100)>>8)
#define ACPI_W1C_STS_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ACPI_7_STS	 */
#define ACPI_7_STS_WIDTH                                                      1
#define ACPI_7_STS_SHIFT                                                      7
#define ACPI_7_STS_MASK                                              0x00000080
#define ACPI_7_STS_RD(src)                            (((src) & 0x00000080)>>7)
#define ACPI_7_STS_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields ACPI_6_STS	 */
#define ACPI_6_STS_WIDTH                                                      1
#define ACPI_6_STS_SHIFT                                                      6
#define ACPI_6_STS_MASK                                              0x00000040
#define ACPI_6_STS_RD(src)                            (((src) & 0x00000040)>>6)
#define ACPI_6_STS_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ACPI_5_STS	 */
#define ACPI_5_STS_WIDTH                                                      1
#define ACPI_5_STS_SHIFT                                                      5
#define ACPI_5_STS_MASK                                              0x00000020
#define ACPI_5_STS_RD(src)                            (((src) & 0x00000020)>>5)
#define ACPI_5_STS_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ACPI_4_STS	 */
#define ACPI_4_STS_WIDTH                                                      1
#define ACPI_4_STS_SHIFT                                                      4
#define ACPI_4_STS_MASK                                              0x00000010
#define ACPI_4_STS_RD(src)                            (((src) & 0x00000010)>>4)
#define ACPI_4_STS_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ACPI_3_STS	 */
#define ACPI_3_STS_WIDTH                                                      1
#define ACPI_3_STS_SHIFT                                                      3
#define ACPI_3_STS_MASK                                              0x00000008
#define ACPI_3_STS_RD(src)                            (((src) & 0x00000008)>>3)
#define ACPI_3_STS_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ACPI_2_STS	 */
#define ACPI_2_STS_WIDTH                                                      1
#define ACPI_2_STS_SHIFT                                                      2
#define ACPI_2_STS_MASK                                              0x00000004
#define ACPI_2_STS_RD(src)                            (((src) & 0x00000004)>>2)
#define ACPI_2_STS_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ACPI_1_STS	 */
#define ACPI_1_STS_WIDTH                                                      1
#define ACPI_1_STS_SHIFT                                                      1
#define ACPI_1_STS_MASK                                              0x00000002
#define ACPI_1_STS_RD(src)                            (((src) & 0x00000002)>>1)
#define ACPI_1_STS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ACPI_0_STS	 */
#define ACPI_0_STS_WIDTH                                                      1
#define ACPI_0_STS_SHIFT                                                      0
#define ACPI_0_STS_MASK                                              0x00000001
#define ACPI_0_STS_RD(src)                               (((src) & 0x00000001))
#define ACPI_0_STS_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ACPI_W1C_WR	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA_WIDTH                                                           16
#define ACPI_DATA_SHIFT                                                            0
#define ACPI_DATA_MASK                                                    0x0000ffff
#define ACPI_DATA_RD(src)                                     (((src) & 0x0000ffff))
#define ACPI_DATA_WR(src)                                (((u32)(src)) & 0x0000ffff)
#define ACPI_DATA_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register ACPI_W1C_RD	*/ 
/*	 Fields DATA	 */
#define DATA_F1_WIDTH                                                        32
#define DATA_F1_SHIFT                                                         0
#define DATA_F1_MASK                                                 0xffffffff
#define DATA_F1_RD(src)                                  (((src) & 0xffffffff))
#define DATA_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_EN_RD	*/ 
/*	 Fields DATA	 */
#define DATA_F2_WIDTH                                                        32
#define DATA_F2_SHIFT                                                         0
#define DATA_F2_MASK                                                 0xffffffff
#define DATA_F2_RD(src)                                  (((src) & 0xffffffff))
#define DATA_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CNT_RD	*/ 
/*	 Fields DATA	 */
#define DATA_F3_WIDTH                                                        32
#define DATA_F3_SHIFT                                                         0
#define DATA_F3_MASK                                                 0xffffffff
#define DATA_F3_RD(src)                                  (((src) & 0xffffffff))
#define DATA_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL0	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA0_WIDTH                                                          32
#define ACPI_DATA0_SHIFT                                                           0
#define ACPI_DATA0_MASK                                                   0xffffffff
#define ACPI_DATA0_RD(src)                                    (((src) & 0xffffffff))
#define ACPI_DATA0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS0	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA0_F1_WIDTH                                                       32
#define ACPI_DATA0_F1_SHIFT                                                        0
#define ACPI_DATA0_F1_MASK                                                0xffffffff
#define ACPI_DATA0_F1_RD(src)                                 (((src) & 0xffffffff))
#define ACPI_DATA0_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define ACPI_DATA0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL1	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA1_WIDTH                                                          32
#define ACPI_DATA1_SHIFT                                                           0
#define ACPI_DATA1_MASK                                                   0xffffffff
#define ACPI_DATA1_RD(src)                                    (((src) & 0xffffffff))
#define ACPI_DATA1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS1	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA1_F1_WIDTH                                                       32
#define ACPI_DATA1_F1_SHIFT                                                        0
#define ACPI_DATA1_F1_MASK                                                0xffffffff
#define ACPI_DATA1_F1_RD(src)                                 (((src) & 0xffffffff))
#define ACPI_DATA1_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define ACPI_DATA1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL2	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA2_WIDTH                                                          32
#define ACPI_DATA2_SHIFT                                                           0
#define ACPI_DATA2_MASK                                                   0xffffffff
#define ACPI_DATA2_RD(src)                                    (((src) & 0xffffffff))
#define ACPI_DATA2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS2	*/ 
/*	 Fields DATA	 */
#define ACPI_DATA2_F1_WIDTH                                                       32
#define ACPI_DATA2_F1_SHIFT                                                        0
#define ACPI_DATA2_F1_MASK                                                0xffffffff
#define ACPI_DATA2_F1_RD(src)                                 (((src) & 0xffffffff))
#define ACPI_DATA2_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define ACPI_DATA2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL3	*/ 
/*	 Fields DATA	 */
#define DATA3_WIDTH                                                          32
#define DATA3_SHIFT                                                           0
#define DATA3_MASK                                                   0xffffffff
#define DATA3_RD(src)                                    (((src) & 0xffffffff))
#define DATA3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS3	*/ 
/*	 Fields DATA	 */
#define DATA3_F1_WIDTH                                                       32
#define DATA3_F1_SHIFT                                                        0
#define DATA3_F1_MASK                                                0xffffffff
#define DATA3_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA3_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DATA3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL4	*/ 
/*	 Fields DATA	 */
#define DATA4_WIDTH                                                          32
#define DATA4_SHIFT                                                           0
#define DATA4_MASK                                                   0xffffffff
#define DATA4_RD(src)                                    (((src) & 0xffffffff))
#define DATA4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS4	*/ 
/*	 Fields DATA	 */
#define DATA4_F1_WIDTH                                                       32
#define DATA4_F1_SHIFT                                                        0
#define DATA4_F1_MASK                                                0xffffffff
#define DATA4_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA4_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DATA4_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL5	*/ 
/*	 Fields DATA	 */
#define DATA5_WIDTH                                                          32
#define DATA5_SHIFT                                                           0
#define DATA5_MASK                                                   0xffffffff
#define DATA5_RD(src)                                    (((src) & 0xffffffff))
#define DATA5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS5	*/ 
/*	 Fields DATA	 */
#define DATA5_F1_WIDTH                                                       32
#define DATA5_F1_SHIFT                                                        0
#define DATA5_F1_MASK                                                0xffffffff
#define DATA5_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA5_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DATA5_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL6	*/ 
/*	 Fields DATA	 */
#define DATA6_WIDTH                                                          32
#define DATA6_SHIFT                                                           0
#define DATA6_MASK                                                   0xffffffff
#define DATA6_RD(src)                                    (((src) & 0xffffffff))
#define DATA6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS6	*/ 
/*	 Fields DATA	 */
#define DATA6_F1_WIDTH                                                       32
#define DATA6_F1_SHIFT                                                        0
#define DATA6_F1_MASK                                                0xffffffff
#define DATA6_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA6_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DATA6_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CTL7	*/ 
/*	 Fields DATA	 */
#define DATA7_WIDTH                                                          32
#define DATA7_SHIFT                                                           0
#define DATA7_MASK                                                   0xffffffff
#define DATA7_RD(src)                                    (((src) & 0xffffffff))
#define DATA7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS7	*/ 
/*	 Fields DATA	 */
#define DATA7_F1_WIDTH                                                       32
#define DATA7_F1_SHIFT                                                        0
#define DATA7_F1_MASK                                                0xffffffff
#define DATA7_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA7_F1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DATA7_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_W1C_INTR_STS	*/ 
/*	 Fields ACPI_TMR	 */
#define ACPI_TMR_WIDTH                                                        1
#define ACPI_TMR_SHIFT                                                        3
#define ACPI_TMR_MASK                                                0x00000008
#define ACPI_TMR_RD(src)                              (((src) & 0x00000008)>>3)
#define ACPI_TMR_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define ACPI_TMR_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ACPI_CNT	 */
#define ACPI_CNT_WIDTH                                                        1
#define ACPI_CNT_SHIFT                                                        2
#define ACPI_CNT_MASK                                                0x00000004
#define ACPI_CNT_RD(src)                              (((src) & 0x00000004)>>2)
#define ACPI_CNT_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define ACPI_CNT_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ACPI_EN	 */
#define ACPI_EN_WIDTH                                                         1
#define ACPI_EN_SHIFT                                                         1
#define ACPI_EN_MASK                                                 0x00000002
#define ACPI_EN_RD(src)                               (((src) & 0x00000002)>>1)
#define ACPI_EN_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define ACPI_EN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ACPI_W1C	 */
#define ACPI_W1C_WIDTH                                                        1
#define ACPI_W1C_SHIFT                                                        0
#define ACPI_W1C_MASK                                                0x00000001
#define ACPI_W1C_RD(src)                                 (((src) & 0x00000001))
#define ACPI_W1C_WR(src)                            (((u32)(src)) & 0x00000001)
#define ACPI_W1C_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ACPI_W1C_INTR_STSMask	*/
/*    Mask Register Fields ACPI_TMRMask    */
#define ACPI_TMRMASK_WIDTH                                                    1
#define ACPI_TMRMASK_SHIFT                                                    3
#define ACPI_TMRMASK_MASK                                            0x00000008
#define ACPI_TMRMASK_RD(src)                          (((src) & 0x00000008)>>3)
#define ACPI_TMRMASK_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define ACPI_TMRMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields ACPI_CNTMask    */
#define ACPI_CNTMASK_WIDTH                                                    1
#define ACPI_CNTMASK_SHIFT                                                    2
#define ACPI_CNTMASK_MASK                                            0x00000004
#define ACPI_CNTMASK_RD(src)                          (((src) & 0x00000004)>>2)
#define ACPI_CNTMASK_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define ACPI_CNTMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields ACPI_ENMask    */
#define ACPI_ENMASK_WIDTH                                                     1
#define ACPI_ENMASK_SHIFT                                                     1
#define ACPI_ENMASK_MASK                                             0x00000002
#define ACPI_ENMASK_RD(src)                           (((src) & 0x00000002)>>1)
#define ACPI_ENMASK_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define ACPI_ENMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields ACPI_W1CMask    */
#define ACPI_W1CMASK_WIDTH                                                    1
#define ACPI_W1CMASK_SHIFT                                                    0
#define ACPI_W1CMASK_MASK                                            0x00000001
#define ACPI_W1CMASK_RD(src)                             (((src) & 0x00000001))
#define ACPI_W1CMASK_WR(src)                        (((u32)(src)) & 0x00000001)
#define ACPI_W1CMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register ACPI_RW_INTR_STS0	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR0_WIDTH                                                     1
#define ACPI_RW_WR0_SHIFT                                                    16
#define ACPI_RW_WR0_MASK                                             0x00010000
#define ACPI_RW_WR0_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR0_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR0_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD0_WIDTH                                                     5
#define ACPI_RO_RD0_SHIFT                                                     0
#define ACPI_RO_RD0_MASK                                             0x0000001f
#define ACPI_RO_RD0_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD0_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD0_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS0Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_WIDTH                                                  1
#define ACPI_RW_WRMASK_SHIFT                                                 16
#define ACPI_RW_WRMASK_MASK                                          0x00010000
#define ACPI_RW_WRMASK_RD(src)                       (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_WR(src)                  (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_WIDTH                                                  5
#define ACPI_RO_RDMASK_SHIFT                                                  0
#define ACPI_RO_RDMASK_MASK                                          0x0000001f
#define ACPI_RO_RDMASK_RD(src)                           (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_WR(src)                      (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS1	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR1_WIDTH                                                     1
#define ACPI_RW_WR1_SHIFT                                                    16
#define ACPI_RW_WR1_MASK                                             0x00010000
#define ACPI_RW_WR1_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR1_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD1_WIDTH                                                     5
#define ACPI_RO_RD1_SHIFT                                                     0
#define ACPI_RO_RD1_MASK                                             0x0000001f
#define ACPI_RO_RD1_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD1_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD1_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS1Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F1_WIDTH                                               1
#define ACPI_RW_WRMASK_F1_SHIFT                                              16
#define ACPI_RW_WRMASK_F1_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F1_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F1_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F1_WIDTH                                               5
#define ACPI_RO_RDMASK_F1_SHIFT                                               0
#define ACPI_RO_RDMASK_F1_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F1_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F1_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F1_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS2	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR2_WIDTH                                                     1
#define ACPI_RW_WR2_SHIFT                                                    16
#define ACPI_RW_WR2_MASK                                             0x00010000
#define ACPI_RW_WR2_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR2_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR2_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD2_WIDTH                                                     5
#define ACPI_RO_RD2_SHIFT                                                     0
#define ACPI_RO_RD2_MASK                                             0x0000001f
#define ACPI_RO_RD2_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD2_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD2_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS2Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F2_WIDTH                                               1
#define ACPI_RW_WRMASK_F2_SHIFT                                              16
#define ACPI_RW_WRMASK_F2_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F2_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F2_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F2_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F2_WIDTH                                               5
#define ACPI_RO_RDMASK_F2_SHIFT                                               0
#define ACPI_RO_RDMASK_F2_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F2_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F2_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F2_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS3	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR3_WIDTH                                                     1
#define ACPI_RW_WR3_SHIFT                                                    16
#define ACPI_RW_WR3_MASK                                             0x00010000
#define ACPI_RW_WR3_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR3_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR3_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD3_WIDTH                                                     5
#define ACPI_RO_RD3_SHIFT                                                     0
#define ACPI_RO_RD3_MASK                                             0x0000001f
#define ACPI_RO_RD3_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD3_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD3_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS3Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F3_WIDTH                                               1
#define ACPI_RW_WRMASK_F3_SHIFT                                              16
#define ACPI_RW_WRMASK_F3_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F3_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F3_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F3_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F3_WIDTH                                               5
#define ACPI_RO_RDMASK_F3_SHIFT                                               0
#define ACPI_RO_RDMASK_F3_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F3_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F3_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F3_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS4	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR4_WIDTH                                                     1
#define ACPI_RW_WR4_SHIFT                                                    16
#define ACPI_RW_WR4_MASK                                             0x00010000
#define ACPI_RW_WR4_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR4_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR4_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD4_WIDTH                                                     5
#define ACPI_RO_RD4_SHIFT                                                     0
#define ACPI_RO_RD4_MASK                                             0x0000001f
#define ACPI_RO_RD4_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD4_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD4_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS4Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F4_WIDTH                                               1
#define ACPI_RW_WRMASK_F4_SHIFT                                              16
#define ACPI_RW_WRMASK_F4_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F4_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F4_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F4_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F4_WIDTH                                               5
#define ACPI_RO_RDMASK_F4_SHIFT                                               0
#define ACPI_RO_RDMASK_F4_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F4_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F4_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F4_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS5	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR5_WIDTH                                                     1
#define ACPI_RW_WR5_SHIFT                                                    16
#define ACPI_RW_WR5_MASK                                             0x00010000
#define ACPI_RW_WR5_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR5_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR5_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD5_WIDTH                                                     5
#define ACPI_RO_RD5_SHIFT                                                     0
#define ACPI_RO_RD5_MASK                                             0x0000001f
#define ACPI_RO_RD5_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD5_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD5_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS5Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F5_WIDTH                                               1
#define ACPI_RW_WRMASK_F5_SHIFT                                              16
#define ACPI_RW_WRMASK_F5_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F5_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F5_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F5_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F5_WIDTH                                               5
#define ACPI_RO_RDMASK_F5_SHIFT                                               0
#define ACPI_RO_RDMASK_F5_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F5_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F5_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F5_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS6	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR6_WIDTH                                                     1
#define ACPI_RW_WR6_SHIFT                                                    16
#define ACPI_RW_WR6_MASK                                             0x00010000
#define ACPI_RW_WR6_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR6_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR6_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD6_WIDTH                                                     5
#define ACPI_RO_RD6_SHIFT                                                     0
#define ACPI_RO_RD6_MASK                                             0x0000001f
#define ACPI_RO_RD6_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD6_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD6_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS6Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F6_WIDTH                                               1
#define ACPI_RW_WRMASK_F6_SHIFT                                              16
#define ACPI_RW_WRMASK_F6_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F6_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F6_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F6_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F6_WIDTH                                               5
#define ACPI_RO_RDMASK_F6_SHIFT                                               0
#define ACPI_RO_RDMASK_F6_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F6_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F6_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F6_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS7	*/ 
/*	 Fields ACPI_RW_WR	 */
#define ACPI_RW_WR7_WIDTH                                                     1
#define ACPI_RW_WR7_SHIFT                                                    16
#define ACPI_RW_WR7_MASK                                             0x00010000
#define ACPI_RW_WR7_RD(src)                          (((src) & 0x00010000)>>16)
#define ACPI_RW_WR7_WR(src)                     (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WR7_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields ACPI_RO_RD	 */
#define ACPI_RO_RD7_WIDTH                                                     5
#define ACPI_RO_RD7_SHIFT                                                     0
#define ACPI_RO_RD7_MASK                                             0x0000001f
#define ACPI_RO_RD7_RD(src)                              (((src) & 0x0000001f))
#define ACPI_RO_RD7_WR(src)                         (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RD7_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register ACPI_RW_INTR_STS7Mask	*/
/*    Mask Register Fields ACPI_RW_WRMask    */
#define ACPI_RW_WRMASK_F7_WIDTH                                               1
#define ACPI_RW_WRMASK_F7_SHIFT                                              16
#define ACPI_RW_WRMASK_F7_MASK                                       0x00010000
#define ACPI_RW_WRMASK_F7_RD(src)                    (((src) & 0x00010000)>>16)
#define ACPI_RW_WRMASK_F7_WR(src)               (((u32)(src)<<16) & 0x00010000)
#define ACPI_RW_WRMASK_F7_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields ACPI_RO_RDMask    */
#define ACPI_RO_RDMASK_F7_WIDTH                                               5
#define ACPI_RO_RDMASK_F7_SHIFT                                               0
#define ACPI_RO_RDMASK_F7_MASK                                       0x0000001f
#define ACPI_RO_RDMASK_F7_RD(src)                        (((src) & 0x0000001f))
#define ACPI_RO_RDMASK_F7_WR(src)                   (((u32)(src)) & 0x0000001f)
#define ACPI_RO_RDMASK_F7_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register MPA_I2C_OVERRIDE	*/ 
/*	 Fields I2C1_SDA_OE	 */
#define I2C1_SDA_OE_WIDTH                                                     1
#define I2C1_SDA_OE_SHIFT                                                     3
#define I2C1_SDA_OE_MASK                                             0x00000008
#define I2C1_SDA_OE_RD(src)                           (((src) & 0x00000008)>>3)
#define I2C1_SDA_OE_WR(src)                      (((u32)(src)<<3) & 0x00000008)
#define I2C1_SDA_OE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields I2C1_SCL_OE	 */
#define I2C1_SCL_OE_WIDTH                                                     1
#define I2C1_SCL_OE_SHIFT                                                     2
#define I2C1_SCL_OE_MASK                                             0x00000004
#define I2C1_SCL_OE_RD(src)                           (((src) & 0x00000004)>>2)
#define I2C1_SCL_OE_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define I2C1_SCL_OE_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields I2C0_SDA_OE	 */
#define I2C0_SDA_OE_WIDTH                                                     1
#define I2C0_SDA_OE_SHIFT                                                     1
#define I2C0_SDA_OE_MASK                                             0x00000002
#define I2C0_SDA_OE_RD(src)                           (((src) & 0x00000002)>>1)
#define I2C0_SDA_OE_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define I2C0_SDA_OE_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields I2C0_SCL_OE	 */
#define I2C0_SCL_OE_WIDTH                                                     1
#define I2C0_SCL_OE_SHIFT                                                     0
#define I2C0_SCL_OE_MASK                                             0x00000001
#define I2C0_SCL_OE_RD(src)                              (((src) & 0x00000001))
#define I2C0_SCL_OE_WR(src)                         (((u32)(src)) & 0x00000001)
#define I2C0_SCL_OE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register DBG_COLDRST_STEP	*/ 
/*	 Fields DATA	 */
#define DATA_F4_WIDTH                                                         1
#define DATA_F4_SHIFT                                                         0
#define DATA_F4_MASK                                                 0x00000001
#define DATA_F4_RD(src)                                  (((src) & 0x00000001))
#define DATA_F4_WR(src)                             (((u32)(src)) & 0x00000001)
#define DATA_F4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register DBG_WARMRST_STEP	*/ 
/*	 Fields DATA	 */
#define DATA_F5_WIDTH                                                         1
#define DATA_F5_SHIFT                                                         0
#define DATA_F5_MASK                                                 0x00000001
#define DATA_F5_RD(src)                                  (((src) & 0x00000001))
#define DATA_F5_WR(src)                             (((u32)(src)) & 0x00000001)
#define DATA_F5_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register DBG_RSTSM_STS	*/ 
/*	 Fields DATA	 */
#define DATA_F6_WIDTH                                                        32
#define DATA_F6_SHIFT                                                         0
#define DATA_F6_MASK                                                 0xffffffff
#define DATA_F6_RD(src)                                  (((src) & 0xffffffff))
#define DATA_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_RSTSM_FORCE	*/ 
/*	 Fields DATA	 */
#define DATA_F7_WIDTH                                                        32
#define DATA_F7_SHIFT                                                         0
#define DATA_F7_MASK                                                 0xffffffff
#define DATA_F7_RD(src)                                  (((src) & 0xffffffff))
#define DATA_F7_WR(src)                             (((u32)(src)) & 0xffffffff)
#define DATA_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA7	*/ 
/*	 Fields DATA	 */
#define DATA7_F2_WIDTH                                                       32
#define DATA7_F2_SHIFT                                                        0
#define DATA7_F2_MASK                                                0xffffffff
#define DATA7_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA7_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA6	*/ 
/*	 Fields DATA	 */
#define DATA6_F2_WIDTH                                                       32
#define DATA6_F2_SHIFT                                                        0
#define DATA6_F2_MASK                                                0xffffffff
#define DATA6_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA6_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA5	*/ 
/*	 Fields DATA	 */
#define DATA5_F2_WIDTH                                                       32
#define DATA5_F2_SHIFT                                                        0
#define DATA5_F2_MASK                                                0xffffffff
#define DATA5_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA5_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA4	*/ 
/*	 Fields DATA	 */
#define DATA4_F2_WIDTH                                                       32
#define DATA4_F2_SHIFT                                                        0
#define DATA4_F2_MASK                                                0xffffffff
#define DATA4_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA4_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA3	*/ 
/*	 Fields DATA	 */
#define DATA3_F2_WIDTH                                                       32
#define DATA3_F2_SHIFT                                                        0
#define DATA3_F2_MASK                                                0xffffffff
#define DATA3_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA3_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA2	*/ 
/*	 Fields DATA	 */
#define DATA2_F2_WIDTH                                                       32
#define DATA2_F2_SHIFT                                                        0
#define DATA2_F2_MASK                                                0xffffffff
#define DATA2_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA2_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA1	*/ 
/*	 Fields DATA	 */
#define DATA1_F2_WIDTH                                                       32
#define DATA1_F2_SHIFT                                                        0
#define DATA1_F2_MASK                                                0xffffffff
#define DATA1_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA1_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BSC_DATA0	*/ 
/*	 Fields DATA	 */
#define DATA0_F2_WIDTH                                                       32
#define DATA0_F2_SHIFT                                                        0
#define DATA0_F2_MASK                                                0xffffffff
#define DATA0_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA0_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define REGSPEC_QMI_SLAVE_I_BASE_ADDR			0x050009000ULL

/*    Address QMI_SLAVE_I  Registers */
#define REGSPEC_CFGSSQMI0_ADDR                                       0x00000000
#define REGSPEC_CFGSSQMI0_DEFAULT                                    0x804c4041
#define REGSPEC_CFGSSQMI1_ADDR                                       0x00000004
#define REGSPEC_CFGSSQMI1_DEFAULT                                    0x0000b7a2
#define REGSPEC_CFGSSQMIQM0_ADDR                                     0x00000008
#define REGSPEC_CFGSSQMIQM0_DEFAULT                                  0x00000060
#define REGSPEC_CFGSSQMIQM1_ADDR                                     0x0000000c
#define REGSPEC_CFGSSQMIQM1_DEFAULT                                  0x0000006c
#define REGSPEC_CFGSSQMIFPDISABLE_ADDR                               0x00000010
#define REGSPEC_CFGSSQMIFPDISABLE_DEFAULT                            0x00000000
#define REGSPEC_CFGSSQMIFPRESET_ADDR                                 0x00000014
#define REGSPEC_CFGSSQMIFPRESET_DEFAULT                              0x00000000
#define REGSPEC_CFGSSQMIWQDISABLE_ADDR                               0x00000018
#define REGSPEC_CFGSSQMIWQDISABLE_DEFAULT                            0x00000000
#define REGSPEC_CFGSSQMIWQRESET_ADDR                                 0x0000001c
#define REGSPEC_CFGSSQMIWQRESET_DEFAULT                              0x00000000
#define REGSPEC_STSSSQMIFPPTR0_ADDR                                  0x00000020
#define REGSPEC_STSSSQMIFPPTR0_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIFPPTR1_ADDR                                  0x00000024
#define REGSPEC_STSSSQMIFPPTR1_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIFPPTR2_ADDR                                  0x00000028
#define REGSPEC_STSSSQMIFPPTR2_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIFPPTR3_ADDR                                  0x0000002c
#define REGSPEC_STSSSQMIFPPTR3_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIFPNUMENTRIES0_ADDR                           0x00000030
#define REGSPEC_STSSSQMIFPNUMENTRIES0_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIFPNUMENTRIES1_ADDR                           0x00000034
#define REGSPEC_STSSSQMIFPNUMENTRIES1_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIFPNUMENTRIES2_ADDR                           0x00000038
#define REGSPEC_STSSSQMIFPNUMENTRIES2_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIFPNUMENTRIES3_ADDR                           0x0000003c
#define REGSPEC_STSSSQMIFPNUMENTRIES3_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQPTR0_ADDR                                  0x00000040
#define REGSPEC_STSSSQMIWQPTR0_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIWQPTR1_ADDR                                  0x00000044
#define REGSPEC_STSSSQMIWQPTR1_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIWQPTR2_ADDR                                  0x00000048
#define REGSPEC_STSSSQMIWQPTR2_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIWQPTR3_ADDR                                  0x0000004c
#define REGSPEC_STSSSQMIWQPTR3_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES0_ADDR                           0x00000050
#define REGSPEC_STSSSQMIWQNUMENTRIES0_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES1_ADDR                           0x00000054
#define REGSPEC_STSSSQMIWQNUMENTRIES1_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES2_ADDR                           0x00000058
#define REGSPEC_STSSSQMIWQNUMENTRIES2_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES3_ADDR                           0x0000005c
#define REGSPEC_STSSSQMIWQNUMENTRIES3_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES4_ADDR                           0x00000060
#define REGSPEC_STSSSQMIWQNUMENTRIES4_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES5_ADDR                           0x00000064
#define REGSPEC_STSSSQMIWQNUMENTRIES5_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES6_ADDR                           0x00000068
#define REGSPEC_STSSSQMIWQNUMENTRIES6_DEFAULT                        0x00000000
#define REGSPEC_STSSSQMIWQNUMENTRIES7_ADDR                           0x0000006c
#define REGSPEC_STSSSQMIWQNUMENTRIES7_DEFAULT                        0x00000000
#define REGSPEC_CFGSSQMISABENABLE_ADDR                               0x00000070
#define REGSPEC_CFGSSQMISABENABLE_DEFAULT                            0x00000000
#define REGSPEC_CFGSSQMISAB0_ADDR                                    0x00000074
#define REGSPEC_CFGSSQMISAB0_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB1_ADDR                                    0x00000078
#define REGSPEC_CFGSSQMISAB1_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB2_ADDR                                    0x0000007c
#define REGSPEC_CFGSSQMISAB2_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB3_ADDR                                    0x00000080
#define REGSPEC_CFGSSQMISAB3_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB4_ADDR                                    0x00000084
#define REGSPEC_CFGSSQMISAB4_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB5_ADDR                                    0x00000088
#define REGSPEC_CFGSSQMISAB5_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB6_ADDR                                    0x0000008c
#define REGSPEC_CFGSSQMISAB6_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB7_ADDR                                    0x00000090
#define REGSPEC_CFGSSQMISAB7_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB8_ADDR                                    0x00000094
#define REGSPEC_CFGSSQMISAB8_DEFAULT                                 0x00000000
#define REGSPEC_CFGSSQMISAB9_ADDR                                    0x00000098
#define REGSPEC_CFGSSQMISAB9_DEFAULT                                 0x00000000
#define REGSPEC_STSSSQMIINT0_ADDR                                    0x0000009c
#define REGSPEC_STSSSQMIINT0_DEFAULT                                 0x00000000
#define REGSPEC_STSSSQMIINT0MASK_ADDR                                0x000000a0
#define REGSPEC_STSSSQMIINT1_ADDR                                    0x000000a4
#define REGSPEC_STSSSQMIINT1_DEFAULT                                 0x00000000
#define REGSPEC_STSSSQMIINT1MASK_ADDR                                0x000000a8
#define REGSPEC_STSSSQMIINT2_ADDR                                    0x000000ac
#define REGSPEC_STSSSQMIINT2_DEFAULT                                 0x00000000
#define REGSPEC_STSSSQMIINT2MASK_ADDR                                0x000000b0
#define REGSPEC_STSSSQMIINT3_ADDR                                    0x000000b4
#define REGSPEC_STSSSQMIINT3_DEFAULT                                 0x00000000
#define REGSPEC_STSSSQMIINT3MASK_ADDR                                0x000000b8
#define REGSPEC_STSSSQMIINT4_ADDR                                    0x000000bc
#define REGSPEC_STSSSQMIINT4_DEFAULT                                 0x00000000
#define REGSPEC_STSSSQMIINT4MASK_ADDR                                0x000000c0
#define REGSPEC_CFGSSQMIDBGCTRL_ADDR                                 0x000000c4
#define REGSPEC_CFGSSQMIDBGCTRL_DEFAULT                              0x00000000
#define REGSPEC_CFGSSQMIDBGDATA0_ADDR                                0x000000c8
#define REGSPEC_CFGSSQMIDBGDATA0_DEFAULT                             0x00000000
#define REGSPEC_CFGSSQMIDBGDATA1_ADDR                                0x000000cc
#define REGSPEC_CFGSSQMIDBGDATA1_DEFAULT                             0x00000000
#define REGSPEC_CFGSSQMIDBGDATA2_ADDR                                0x000000d0
#define REGSPEC_CFGSSQMIDBGDATA2_DEFAULT                             0x00000000
#define REGSPEC_CFGSSQMIDBGDATA3_ADDR                                0x000000d4
#define REGSPEC_CFGSSQMIDBGDATA3_DEFAULT                             0x00000000
#define REGSPEC_STSSSQMIDBGDATA_ADDR                                 0x000000d8
#define REGSPEC_STSSSQMIDBGDATA_DEFAULT                              0x00000000
#define REGSPEC_CFGSSQMIFPQASSOC_ADDR                                0x000000dc
#define REGSPEC_CFGSSQMIFPQASSOC_DEFAULT                             0x00000000
#define REGSPEC_CFGSSQMIWQASSOC_ADDR                                 0x000000e0
#define REGSPEC_CFGSSQMIWQASSOC_DEFAULT                              0x00000000
#define REGSPEC_CFGSSQMIMEMORY_ADDR                                  0x000000e4
#define REGSPEC_CFGSSQMIMEMORY_DEFAULT                               0x00000000
#define REGSPEC_STSSSQMIFIFO_ADDR                                    0x000000e8
#define REGSPEC_STSSSQMIFIFO_DEFAULT                                 0x07ffffff
#define REGSPEC_CFGSSQMIQMLITE_ADDR                                  0x000000ec
#define REGSPEC_CFGSSQMIQMLITE_DEFAULT                               0x00000040
#define REGSPEC_CFGSSQMIQMLITEFPQASSOC_ADDR                          0x000000f0
#define REGSPEC_CFGSSQMIQMLITEFPQASSOC_DEFAULT                       0x00000000
#define REGSPEC_CFGSSQMIQMLITEWQASSOC_ADDR                           0x000000f4
#define REGSPEC_CFGSSQMIQMLITEWQASSOC_DEFAULT                        0x00000000
#define REGSPEC_CFGSSQMIQMHOLD_ADDR                                  0x000000f8
#define REGSPEC_CFGSSQMIQMHOLD_DEFAULT                               0x80000003
#define REGSPEC_STSSSQMIQMHOLD_ADDR                                  0x000000fc
#define REGSPEC_STSSSQMIQMHOLD_DEFAULT                               0x00000000
#define REGSPEC_CFGSSQMIFPQVCASSOC0_ADDR                             0x00000100
#define REGSPEC_CFGSSQMIFPQVCASSOC0_DEFAULT                          0x00000000
#define REGSPEC_CFGSSQMIFPQVCASSOC1_ADDR                             0x00000104
#define REGSPEC_CFGSSQMIFPQVCASSOC1_DEFAULT                          0x00000000
#define REGSPEC_CFGSSQMIWQVCASSOC0_ADDR                              0x00000108
#define REGSPEC_CFGSSQMIWQVCASSOC0_DEFAULT                           0x00000000
#define REGSPEC_CFGSSQMIWQVCASSOC1_ADDR                              0x0000010c
#define REGSPEC_CFGSSQMIWQVCASSOC1_DEFAULT                           0x00000000
#define REGSPEC_CFGSSQMIQM2_ADDR                                     0x00000110
#define REGSPEC_CFGSSQMIQM2_DEFAULT                                  0x00000078

/*	Register CfgSsQmi0	*/ 
/*	 Fields WQBavailFMWait	 */
#define REGSPEC_WQBAVAILFMWAIT0_WIDTH                                         1
#define REGSPEC_WQBAVAILFMWAIT0_SHIFT                                        31
#define REGSPEC_WQBAVAILFMWAIT0_MASK                                 0x80000000
#define REGSPEC_WQBAVAILFMWAIT0_RD(src)              (((src) & 0x80000000)>>31)
#define REGSPEC_WQBAVAILFMWAIT0_WR(src)         (((u32)(src)<<31) & 0x80000000)
#define REGSPEC_WQBAVAILFMWAIT0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields FPDecDiffThreshold	 */
#define REGSPEC_FPDECDIFFTHRESHOLD0_WIDTH                                     4
#define REGSPEC_FPDECDIFFTHRESHOLD0_SHIFT                                    27
#define REGSPEC_FPDECDIFFTHRESHOLD0_MASK                             0x78000000
#define REGSPEC_FPDECDIFFTHRESHOLD0_RD(src)          (((src) & 0x78000000)>>27)
#define REGSPEC_FPDECDIFFTHRESHOLD0_WR(src)     (((u32)(src)<<27) & 0x78000000)
#define REGSPEC_FPDECDIFFTHRESHOLD0_SET(dst,src) \
                      (((dst) & ~0x78000000) | (((u32)(src)<<27) & 0x78000000))
/*	 Fields WQDecDiffThreshold	 */
#define REGSPEC_WQDECDIFFTHRESHOLD0_WIDTH                                     5
#define REGSPEC_WQDECDIFFTHRESHOLD0_SHIFT                                    22
#define REGSPEC_WQDECDIFFTHRESHOLD0_MASK                             0x07c00000
#define REGSPEC_WQDECDIFFTHRESHOLD0_RD(src)          (((src) & 0x07c00000)>>22)
#define REGSPEC_WQDECDIFFTHRESHOLD0_WR(src)     (((u32)(src)<<22) & 0x07c00000)
#define REGSPEC_WQDECDIFFTHRESHOLD0_SET(dst,src) \
                      (((dst) & ~0x07c00000) | (((u32)(src)<<22) & 0x07c00000))
/*	 Fields DeallocThreshold	 */
#define REGSPEC_DEALLOCTHRESHOLD0_WIDTH                                       4
#define REGSPEC_DEALLOCTHRESHOLD0_SHIFT                                      18
#define REGSPEC_DEALLOCTHRESHOLD0_MASK                               0x003c0000
#define REGSPEC_DEALLOCTHRESHOLD0_RD(src)            (((src) & 0x003c0000)>>18)
#define REGSPEC_DEALLOCTHRESHOLD0_WR(src)       (((u32)(src)<<18) & 0x003c0000)
#define REGSPEC_DEALLOCTHRESHOLD0_SET(dst,src) \
                      (((dst) & ~0x003c0000) | (((u32)(src)<<18) & 0x003c0000))
/*	 Fields FPDecThreshold	 */
#define REGSPEC_FPDECTHRESHOLD0_WIDTH                                         4
#define REGSPEC_FPDECTHRESHOLD0_SHIFT                                        14
#define REGSPEC_FPDECTHRESHOLD0_MASK                                 0x0003c000
#define REGSPEC_FPDECTHRESHOLD0_RD(src)              (((src) & 0x0003c000)>>14)
#define REGSPEC_FPDECTHRESHOLD0_WR(src)         (((u32)(src)<<14) & 0x0003c000)
#define REGSPEC_FPDECTHRESHOLD0_SET(dst,src) \
                      (((dst) & ~0x0003c000) | (((u32)(src)<<14) & 0x0003c000))
/*	 Fields FPBAvlThreshold	 */
#define REGSPEC_FPBAVLTHRESHOLD0_WIDTH                                        4
#define REGSPEC_FPBAVLTHRESHOLD0_SHIFT                                       10
#define REGSPEC_FPBAVLTHRESHOLD0_MASK                                0x00003c00
#define REGSPEC_FPBAVLTHRESHOLD0_RD(src)             (((src) & 0x00003c00)>>10)
#define REGSPEC_FPBAVLTHRESHOLD0_WR(src)        (((u32)(src)<<10) & 0x00003c00)
#define REGSPEC_FPBAVLTHRESHOLD0_SET(dst,src) \
                      (((dst) & ~0x00003c00) | (((u32)(src)<<10) & 0x00003c00))
/*	 Fields WQDecThreshold	 */
#define REGSPEC_WQDECTHRESHOLD0_WIDTH                                         5
#define REGSPEC_WQDECTHRESHOLD0_SHIFT                                         5
#define REGSPEC_WQDECTHRESHOLD0_MASK                                 0x000003e0
#define REGSPEC_WQDECTHRESHOLD0_RD(src)               (((src) & 0x000003e0)>>5)
#define REGSPEC_WQDECTHRESHOLD0_WR(src)          (((u32)(src)<<5) & 0x000003e0)
#define REGSPEC_WQDECTHRESHOLD0_SET(dst,src) \
                       (((dst) & ~0x000003e0) | (((u32)(src)<<5) & 0x000003e0))
/*	 Fields WQBAvlThreshold	 */
#define REGSPEC_WQBAVLTHRESHOLD0_WIDTH                                        5
#define REGSPEC_WQBAVLTHRESHOLD0_SHIFT                                        0
#define REGSPEC_WQBAVLTHRESHOLD0_MASK                                0x0000001f
#define REGSPEC_WQBAVLTHRESHOLD0_RD(src)                 (((src) & 0x0000001f))
#define REGSPEC_WQBAVLTHRESHOLD0_WR(src)            (((u32)(src)) & 0x0000001f)
#define REGSPEC_WQBAVLTHRESHOLD0_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register CfgSsQmi1	*/ 
/*	 Fields CmOverrideLLFields	 */
#define REGSPEC_CMOVERRIDELLFIELDS1_WIDTH                                     1
#define REGSPEC_CMOVERRIDELLFIELDS1_SHIFT                                    15
#define REGSPEC_CMOVERRIDELLFIELDS1_MASK                             0x00008000
#define REGSPEC_CMOVERRIDELLFIELDS1_RD(src)          (((src) & 0x00008000)>>15)
#define REGSPEC_CMOVERRIDELLFIELDS1_WR(src)     (((u32)(src)<<15) & 0x00008000)
#define REGSPEC_CMOVERRIDELLFIELDS1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields CmCtrlbuffThreshold	 */
#define REGSPEC_CMCTRLBUFFTHRESHOLD1_WIDTH                                    3
#define REGSPEC_CMCTRLBUFFTHRESHOLD1_SHIFT                                   12
#define REGSPEC_CMCTRLBUFFTHRESHOLD1_MASK                            0x00007000
#define REGSPEC_CMCTRLBUFFTHRESHOLD1_RD(src)         (((src) & 0x00007000)>>12)
#define REGSPEC_CMCTRLBUFFTHRESHOLD1_WR(src)    (((u32)(src)<<12) & 0x00007000)
#define REGSPEC_CMCTRLBUFFTHRESHOLD1_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields CmDatabuffThreshold	 */
#define REGSPEC_CMDATABUFFTHRESHOLD1_WIDTH                                    5
#define REGSPEC_CMDATABUFFTHRESHOLD1_SHIFT                                    7
#define REGSPEC_CMDATABUFFTHRESHOLD1_MASK                            0x00000f80
#define REGSPEC_CMDATABUFFTHRESHOLD1_RD(src)          (((src) & 0x00000f80)>>7)
#define REGSPEC_CMDATABUFFTHRESHOLD1_WR(src)     (((u32)(src)<<7) & 0x00000f80)
#define REGSPEC_CMDATABUFFTHRESHOLD1_SET(dst,src) \
                       (((dst) & ~0x00000f80) | (((u32)(src)<<7) & 0x00000f80))
/*	 Fields CmMsgfThreshold	 */
#define REGSPEC_CMMSGFTHRESHOLD1_WIDTH                                        4
#define REGSPEC_CMMSGFTHRESHOLD1_SHIFT                                        3
#define REGSPEC_CMMSGFTHRESHOLD1_MASK                                0x00000078
#define REGSPEC_CMMSGFTHRESHOLD1_RD(src)              (((src) & 0x00000078)>>3)
#define REGSPEC_CMMSGFTHRESHOLD1_WR(src)         (((u32)(src)<<3) & 0x00000078)
#define REGSPEC_CMMSGFTHRESHOLD1_SET(dst,src) \
                       (((dst) & ~0x00000078) | (((u32)(src)<<3) & 0x00000078))
/*	 Fields CmRegfThreshold	 */
#define REGSPEC_CMREGFTHRESHOLD1_WIDTH                                        3
#define REGSPEC_CMREGFTHRESHOLD1_SHIFT                                        0
#define REGSPEC_CMREGFTHRESHOLD1_MASK                                0x00000007
#define REGSPEC_CMREGFTHRESHOLD1_RD(src)                 (((src) & 0x00000007))
#define REGSPEC_CMREGFTHRESHOLD1_WR(src)            (((u32)(src)) & 0x00000007)
#define REGSPEC_CMREGFTHRESHOLD1_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register CfgSsQmiQM0	*/ 
/*	 Fields Address	 */
#define REGSPEC_ADDRESS0_WIDTH                                               20
#define REGSPEC_ADDRESS0_SHIFT                                                0
#define REGSPEC_ADDRESS0_MASK                                        0x000fffff
#define REGSPEC_ADDRESS0_RD(src)                         (((src) & 0x000fffff))
#define REGSPEC_ADDRESS0_WR(src)                    (((u32)(src)) & 0x000fffff)
#define REGSPEC_ADDRESS0_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register CfgSsQmiQM1	*/ 
/*	 Fields Address	 */
#define REGSPEC_ADDRESS1_WIDTH                                               20
#define REGSPEC_ADDRESS1_SHIFT                                                0
#define REGSPEC_ADDRESS1_MASK                                        0x000fffff
#define REGSPEC_ADDRESS1_RD(src)                         (((src) & 0x000fffff))
#define REGSPEC_ADDRESS1_WR(src)                    (((u32)(src)) & 0x000fffff)
#define REGSPEC_ADDRESS1_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register CfgSsQmiFPDisable	*/ 
/*	 Fields Disable	 */
#define REGSPEC_DISABLE_WIDTH                                                32
#define REGSPEC_DISABLE_SHIFT                                                 0
#define REGSPEC_DISABLE_MASK                                         0xffffffff
#define REGSPEC_DISABLE_RD(src)                          (((src) & 0xffffffff))
#define REGSPEC_DISABLE_WR(src)                     (((u32)(src)) & 0xffffffff)
#define REGSPEC_DISABLE_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiFPReset	*/ 
/*	 Fields Reset	 */
#define REGSPEC_RESET_F4_WIDTH                                               32
#define REGSPEC_RESET_F4_SHIFT                                                0
#define REGSPEC_RESET_F4_MASK                                        0xffffffff
#define REGSPEC_RESET_F4_RD(src)                         (((src) & 0xffffffff))
#define REGSPEC_RESET_F4_WR(src)                    (((u32)(src)) & 0xffffffff)
#define REGSPEC_RESET_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiWQDisable	*/ 
/*	 Fields Disable	 */
#define REGSPEC_DISABLE_F1_WIDTH                                             32
#define REGSPEC_DISABLE_F1_SHIFT                                              0
#define REGSPEC_DISABLE_F1_MASK                                      0xffffffff
#define REGSPEC_DISABLE_F1_RD(src)                       (((src) & 0xffffffff))
#define REGSPEC_DISABLE_F1_WR(src)                  (((u32)(src)) & 0xffffffff)
#define REGSPEC_DISABLE_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiWQReset	*/ 
/*	 Fields Reset	 */
#define REGSPEC_RESET_F5_WIDTH                                               32
#define REGSPEC_RESET_F5_SHIFT                                                0
#define REGSPEC_RESET_F5_MASK                                        0xffffffff
#define REGSPEC_RESET_F5_RD(src)                         (((src) & 0xffffffff))
#define REGSPEC_RESET_F5_WR(src)                    (((u32)(src)) & 0xffffffff)
#define REGSPEC_RESET_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiFPPtr0	*/ 
/*	 Fields FP7	 */
#define REGSPEC_FP70_WIDTH                                                    3
#define REGSPEC_FP70_SHIFT                                                   28
#define REGSPEC_FP70_MASK                                            0x70000000
#define REGSPEC_FP70_RD(src)                         (((src) & 0x70000000)>>28)
#define REGSPEC_FP70_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields FP6	 */
#define REGSPEC_FP60_WIDTH                                                    3
#define REGSPEC_FP60_SHIFT                                                   24
#define REGSPEC_FP60_MASK                                            0x07000000
#define REGSPEC_FP60_RD(src)                         (((src) & 0x07000000)>>24)
#define REGSPEC_FP60_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields FP5	 */
#define REGSPEC_FP50_WIDTH                                                    3
#define REGSPEC_FP50_SHIFT                                                   20
#define REGSPEC_FP50_MASK                                            0x00700000
#define REGSPEC_FP50_RD(src)                         (((src) & 0x00700000)>>20)
#define REGSPEC_FP50_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields FP4	 */
#define REGSPEC_FP40_WIDTH                                                    3
#define REGSPEC_FP40_SHIFT                                                   16
#define REGSPEC_FP40_MASK                                            0x00070000
#define REGSPEC_FP40_RD(src)                         (((src) & 0x00070000)>>16)
#define REGSPEC_FP40_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields FP3	 */
#define REGSPEC_FP30_WIDTH                                                    3
#define REGSPEC_FP30_SHIFT                                                   12
#define REGSPEC_FP30_MASK                                            0x00007000
#define REGSPEC_FP30_RD(src)                         (((src) & 0x00007000)>>12)
#define REGSPEC_FP30_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields FP2	 */
#define REGSPEC_FP20_WIDTH                                                    3
#define REGSPEC_FP20_SHIFT                                                    8
#define REGSPEC_FP20_MASK                                            0x00000700
#define REGSPEC_FP20_RD(src)                          (((src) & 0x00000700)>>8)
#define REGSPEC_FP20_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields FP1	 */
#define REGSPEC_FP10_WIDTH                                                    3
#define REGSPEC_FP10_SHIFT                                                    4
#define REGSPEC_FP10_MASK                                            0x00000070
#define REGSPEC_FP10_RD(src)                          (((src) & 0x00000070)>>4)
#define REGSPEC_FP10_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields FP0	 */
#define REGSPEC_FP00_WIDTH                                                    3
#define REGSPEC_FP00_SHIFT                                                    0
#define REGSPEC_FP00_MASK                                            0x00000007
#define REGSPEC_FP00_RD(src)                             (((src) & 0x00000007))
#define REGSPEC_FP00_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register StsSsQmiFPPtr1	*/ 
/*	 Fields FP15	 */
#define REGSPEC_FP151_WIDTH                                                   3
#define REGSPEC_FP151_SHIFT                                                  28
#define REGSPEC_FP151_MASK                                           0x70000000
#define REGSPEC_FP151_RD(src)                        (((src) & 0x70000000)>>28)
#define REGSPEC_FP151_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields FP14	 */
#define REGSPEC_FP141_WIDTH                                                   3
#define REGSPEC_FP141_SHIFT                                                  24
#define REGSPEC_FP141_MASK                                           0x07000000
#define REGSPEC_FP141_RD(src)                        (((src) & 0x07000000)>>24)
#define REGSPEC_FP141_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields FP13	 */
#define REGSPEC_FP131_WIDTH                                                   3
#define REGSPEC_FP131_SHIFT                                                  20
#define REGSPEC_FP131_MASK                                           0x00700000
#define REGSPEC_FP131_RD(src)                        (((src) & 0x00700000)>>20)
#define REGSPEC_FP131_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields FP12	 */
#define REGSPEC_FP121_WIDTH                                                   3
#define REGSPEC_FP121_SHIFT                                                  16
#define REGSPEC_FP121_MASK                                           0x00070000
#define REGSPEC_FP121_RD(src)                        (((src) & 0x00070000)>>16)
#define REGSPEC_FP121_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields FP11	 */
#define REGSPEC_FP111_WIDTH                                                   3
#define REGSPEC_FP111_SHIFT                                                  12
#define REGSPEC_FP111_MASK                                           0x00007000
#define REGSPEC_FP111_RD(src)                        (((src) & 0x00007000)>>12)
#define REGSPEC_FP111_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields FP10	 */
#define REGSPEC_FP101_WIDTH                                                   3
#define REGSPEC_FP101_SHIFT                                                   8
#define REGSPEC_FP101_MASK                                           0x00000700
#define REGSPEC_FP101_RD(src)                         (((src) & 0x00000700)>>8)
#define REGSPEC_FP101_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields FP9	 */
#define REGSPEC_FP91_WIDTH                                                    3
#define REGSPEC_FP91_SHIFT                                                    4
#define REGSPEC_FP91_MASK                                            0x00000070
#define REGSPEC_FP91_RD(src)                          (((src) & 0x00000070)>>4)
#define REGSPEC_FP91_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields FP8	 */
#define REGSPEC_FP81_WIDTH                                                    3
#define REGSPEC_FP81_SHIFT                                                    0
#define REGSPEC_FP81_MASK                                            0x00000007
#define REGSPEC_FP81_RD(src)                             (((src) & 0x00000007))
#define REGSPEC_FP81_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register StsSsQmiFPPtr2	*/ 
/*	 Fields FP23	 */
#define REGSPEC_FP232_WIDTH                                                   3
#define REGSPEC_FP232_SHIFT                                                  28
#define REGSPEC_FP232_MASK                                           0x70000000
#define REGSPEC_FP232_RD(src)                        (((src) & 0x70000000)>>28)
#define REGSPEC_FP232_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields FP22	 */
#define REGSPEC_FP222_WIDTH                                                   3
#define REGSPEC_FP222_SHIFT                                                  24
#define REGSPEC_FP222_MASK                                           0x07000000
#define REGSPEC_FP222_RD(src)                        (((src) & 0x07000000)>>24)
#define REGSPEC_FP222_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields FP21	 */
#define REGSPEC_FP212_WIDTH                                                   3
#define REGSPEC_FP212_SHIFT                                                  20
#define REGSPEC_FP212_MASK                                           0x00700000
#define REGSPEC_FP212_RD(src)                        (((src) & 0x00700000)>>20)
#define REGSPEC_FP212_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields FP20	 */
#define REGSPEC_FP202_WIDTH                                                   3
#define REGSPEC_FP202_SHIFT                                                  16
#define REGSPEC_FP202_MASK                                           0x00070000
#define REGSPEC_FP202_RD(src)                        (((src) & 0x00070000)>>16)
#define REGSPEC_FP202_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields FP19	 */
#define REGSPEC_FP192_WIDTH                                                   3
#define REGSPEC_FP192_SHIFT                                                  12
#define REGSPEC_FP192_MASK                                           0x00007000
#define REGSPEC_FP192_RD(src)                        (((src) & 0x00007000)>>12)
#define REGSPEC_FP192_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields FP18	 */
#define REGSPEC_FP182_WIDTH                                                   3
#define REGSPEC_FP182_SHIFT                                                   8
#define REGSPEC_FP182_MASK                                           0x00000700
#define REGSPEC_FP182_RD(src)                         (((src) & 0x00000700)>>8)
#define REGSPEC_FP182_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields FP17	 */
#define REGSPEC_FP172_WIDTH                                                   3
#define REGSPEC_FP172_SHIFT                                                   4
#define REGSPEC_FP172_MASK                                           0x00000070
#define REGSPEC_FP172_RD(src)                         (((src) & 0x00000070)>>4)
#define REGSPEC_FP172_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields FP16	 */
#define REGSPEC_FP162_WIDTH                                                   3
#define REGSPEC_FP162_SHIFT                                                   0
#define REGSPEC_FP162_MASK                                           0x00000007
#define REGSPEC_FP162_RD(src)                            (((src) & 0x00000007))
#define REGSPEC_FP162_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register StsSsQmiFPPtr3	*/ 
/*	 Fields FP31	 */
#define REGSPEC_FP313_WIDTH                                                   3
#define REGSPEC_FP313_SHIFT                                                  28
#define REGSPEC_FP313_MASK                                           0x70000000
#define REGSPEC_FP313_RD(src)                        (((src) & 0x70000000)>>28)
#define REGSPEC_FP313_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields FP30	 */
#define REGSPEC_FP303_WIDTH                                                   3
#define REGSPEC_FP303_SHIFT                                                  24
#define REGSPEC_FP303_MASK                                           0x07000000
#define REGSPEC_FP303_RD(src)                        (((src) & 0x07000000)>>24)
#define REGSPEC_FP303_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields FP29	 */
#define REGSPEC_FP293_WIDTH                                                   3
#define REGSPEC_FP293_SHIFT                                                  20
#define REGSPEC_FP293_MASK                                           0x00700000
#define REGSPEC_FP293_RD(src)                        (((src) & 0x00700000)>>20)
#define REGSPEC_FP293_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields FP28	 */
#define REGSPEC_FP283_WIDTH                                                   3
#define REGSPEC_FP283_SHIFT                                                  16
#define REGSPEC_FP283_MASK                                           0x00070000
#define REGSPEC_FP283_RD(src)                        (((src) & 0x00070000)>>16)
#define REGSPEC_FP283_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields FP27	 */
#define REGSPEC_FP273_WIDTH                                                   3
#define REGSPEC_FP273_SHIFT                                                  12
#define REGSPEC_FP273_MASK                                           0x00007000
#define REGSPEC_FP273_RD(src)                        (((src) & 0x00007000)>>12)
#define REGSPEC_FP273_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields FP26	 */
#define REGSPEC_FP263_WIDTH                                                   3
#define REGSPEC_FP263_SHIFT                                                   8
#define REGSPEC_FP263_MASK                                           0x00000700
#define REGSPEC_FP263_RD(src)                         (((src) & 0x00000700)>>8)
#define REGSPEC_FP263_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields FP25	 */
#define REGSPEC_FP253_WIDTH                                                   3
#define REGSPEC_FP253_SHIFT                                                   4
#define REGSPEC_FP253_MASK                                           0x00000070
#define REGSPEC_FP253_RD(src)                         (((src) & 0x00000070)>>4)
#define REGSPEC_FP253_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields FP24	 */
#define REGSPEC_FP243_WIDTH                                                   3
#define REGSPEC_FP243_SHIFT                                                   0
#define REGSPEC_FP243_MASK                                           0x00000007
#define REGSPEC_FP243_RD(src)                            (((src) & 0x00000007))
#define REGSPEC_FP243_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register StsSsQmiFPNumEntries0	*/ 
/*	 Fields FP7	 */
#define REGSPEC_FP70_F1_WIDTH                                                 4
#define REGSPEC_FP70_F1_SHIFT                                                28
#define REGSPEC_FP70_F1_MASK                                         0xf0000000
#define REGSPEC_FP70_F1_RD(src)                      (((src) & 0xf0000000)>>28)
#define REGSPEC_FP70_F1_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields FP6	 */
#define REGSPEC_FP60_F1_WIDTH                                                 4
#define REGSPEC_FP60_F1_SHIFT                                                24
#define REGSPEC_FP60_F1_MASK                                         0x0f000000
#define REGSPEC_FP60_F1_RD(src)                      (((src) & 0x0f000000)>>24)
#define REGSPEC_FP60_F1_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields FP5	 */
#define REGSPEC_FP50_F1_WIDTH                                                 4
#define REGSPEC_FP50_F1_SHIFT                                                20
#define REGSPEC_FP50_F1_MASK                                         0x00f00000
#define REGSPEC_FP50_F1_RD(src)                      (((src) & 0x00f00000)>>20)
#define REGSPEC_FP50_F1_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields FP4	 */
#define REGSPEC_FP40_F1_WIDTH                                                 4
#define REGSPEC_FP40_F1_SHIFT                                                16
#define REGSPEC_FP40_F1_MASK                                         0x000f0000
#define REGSPEC_FP40_F1_RD(src)                      (((src) & 0x000f0000)>>16)
#define REGSPEC_FP40_F1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields FP3	 */
#define REGSPEC_FP30_F1_WIDTH                                                 4
#define REGSPEC_FP30_F1_SHIFT                                                12
#define REGSPEC_FP30_F1_MASK                                         0x0000f000
#define REGSPEC_FP30_F1_RD(src)                      (((src) & 0x0000f000)>>12)
#define REGSPEC_FP30_F1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields FP2	 */
#define REGSPEC_FP20_F1_WIDTH                                                 4
#define REGSPEC_FP20_F1_SHIFT                                                 8
#define REGSPEC_FP20_F1_MASK                                         0x00000f00
#define REGSPEC_FP20_F1_RD(src)                       (((src) & 0x00000f00)>>8)
#define REGSPEC_FP20_F1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields FP1	 */
#define REGSPEC_FP10_F1_WIDTH                                                 4
#define REGSPEC_FP10_F1_SHIFT                                                 4
#define REGSPEC_FP10_F1_MASK                                         0x000000f0
#define REGSPEC_FP10_F1_RD(src)                       (((src) & 0x000000f0)>>4)
#define REGSPEC_FP10_F1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields FP0	 */
#define REGSPEC_FP00_F1_WIDTH                                                 4
#define REGSPEC_FP00_F1_SHIFT                                                 0
#define REGSPEC_FP00_F1_MASK                                         0x0000000f
#define REGSPEC_FP00_F1_RD(src)                          (((src) & 0x0000000f))
#define REGSPEC_FP00_F1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiFPNumEntries1	*/ 
/*	 Fields FP15	 */
#define REGSPEC_FP151_F1_WIDTH                                                4
#define REGSPEC_FP151_F1_SHIFT                                               28
#define REGSPEC_FP151_F1_MASK                                        0xf0000000
#define REGSPEC_FP151_F1_RD(src)                     (((src) & 0xf0000000)>>28)
#define REGSPEC_FP151_F1_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields FP14	 */
#define REGSPEC_FP141_F1_WIDTH                                                4
#define REGSPEC_FP141_F1_SHIFT                                               24
#define REGSPEC_FP141_F1_MASK                                        0x0f000000
#define REGSPEC_FP141_F1_RD(src)                     (((src) & 0x0f000000)>>24)
#define REGSPEC_FP141_F1_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields FP13	 */
#define REGSPEC_FP131_F1_WIDTH                                                4
#define REGSPEC_FP131_F1_SHIFT                                               20
#define REGSPEC_FP131_F1_MASK                                        0x00f00000
#define REGSPEC_FP131_F1_RD(src)                     (((src) & 0x00f00000)>>20)
#define REGSPEC_FP131_F1_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields FP12	 */
#define REGSPEC_FP121_F1_WIDTH                                                4
#define REGSPEC_FP121_F1_SHIFT                                               16
#define REGSPEC_FP121_F1_MASK                                        0x000f0000
#define REGSPEC_FP121_F1_RD(src)                     (((src) & 0x000f0000)>>16)
#define REGSPEC_FP121_F1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields FP11	 */
#define REGSPEC_FP111_F1_WIDTH                                                4
#define REGSPEC_FP111_F1_SHIFT                                               12
#define REGSPEC_FP111_F1_MASK                                        0x0000f000
#define REGSPEC_FP111_F1_RD(src)                     (((src) & 0x0000f000)>>12)
#define REGSPEC_FP111_F1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields FP10	 */
#define REGSPEC_FP101_F1_WIDTH                                                4
#define REGSPEC_FP101_F1_SHIFT                                                8
#define REGSPEC_FP101_F1_MASK                                        0x00000f00
#define REGSPEC_FP101_F1_RD(src)                      (((src) & 0x00000f00)>>8)
#define REGSPEC_FP101_F1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields FP9	 */
#define REGSPEC_FP91_F1_WIDTH                                                 4
#define REGSPEC_FP91_F1_SHIFT                                                 4
#define REGSPEC_FP91_F1_MASK                                         0x000000f0
#define REGSPEC_FP91_F1_RD(src)                       (((src) & 0x000000f0)>>4)
#define REGSPEC_FP91_F1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields FP8	 */
#define REGSPEC_FP81_F1_WIDTH                                                 4
#define REGSPEC_FP81_F1_SHIFT                                                 0
#define REGSPEC_FP81_F1_MASK                                         0x0000000f
#define REGSPEC_FP81_F1_RD(src)                          (((src) & 0x0000000f))
#define REGSPEC_FP81_F1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiFPNumEntries2	*/ 
/*	 Fields FP23	 */
#define REGSPEC_FP232_F1_WIDTH                                                4
#define REGSPEC_FP232_F1_SHIFT                                               28
#define REGSPEC_FP232_F1_MASK                                        0xf0000000
#define REGSPEC_FP232_F1_RD(src)                     (((src) & 0xf0000000)>>28)
#define REGSPEC_FP232_F1_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields FP22	 */
#define REGSPEC_FP222_F1_WIDTH                                                4
#define REGSPEC_FP222_F1_SHIFT                                               24
#define REGSPEC_FP222_F1_MASK                                        0x0f000000
#define REGSPEC_FP222_F1_RD(src)                     (((src) & 0x0f000000)>>24)
#define REGSPEC_FP222_F1_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields FP21	 */
#define REGSPEC_FP212_F1_WIDTH                                                4
#define REGSPEC_FP212_F1_SHIFT                                               20
#define REGSPEC_FP212_F1_MASK                                        0x00f00000
#define REGSPEC_FP212_F1_RD(src)                     (((src) & 0x00f00000)>>20)
#define REGSPEC_FP212_F1_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields FP20	 */
#define REGSPEC_FP202_F1_WIDTH                                                4
#define REGSPEC_FP202_F1_SHIFT                                               16
#define REGSPEC_FP202_F1_MASK                                        0x000f0000
#define REGSPEC_FP202_F1_RD(src)                     (((src) & 0x000f0000)>>16)
#define REGSPEC_FP202_F1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields FP19	 */
#define REGSPEC_FP192_F1_WIDTH                                                4
#define REGSPEC_FP192_F1_SHIFT                                               12
#define REGSPEC_FP192_F1_MASK                                        0x0000f000
#define REGSPEC_FP192_F1_RD(src)                     (((src) & 0x0000f000)>>12)
#define REGSPEC_FP192_F1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields FP18	 */
#define REGSPEC_FP182_F1_WIDTH                                                4
#define REGSPEC_FP182_F1_SHIFT                                                8
#define REGSPEC_FP182_F1_MASK                                        0x00000f00
#define REGSPEC_FP182_F1_RD(src)                      (((src) & 0x00000f00)>>8)
#define REGSPEC_FP182_F1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields FP17	 */
#define REGSPEC_FP172_F1_WIDTH                                                4
#define REGSPEC_FP172_F1_SHIFT                                                4
#define REGSPEC_FP172_F1_MASK                                        0x000000f0
#define REGSPEC_FP172_F1_RD(src)                      (((src) & 0x000000f0)>>4)
#define REGSPEC_FP172_F1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields FP16	 */
#define REGSPEC_FP162_F1_WIDTH                                                4
#define REGSPEC_FP162_F1_SHIFT                                                0
#define REGSPEC_FP162_F1_MASK                                        0x0000000f
#define REGSPEC_FP162_F1_RD(src)                         (((src) & 0x0000000f))
#define REGSPEC_FP162_F1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiFPNumEntries3	*/ 
/*	 Fields FP31	 */
#define REGSPEC_FP313_F1_WIDTH                                                4
#define REGSPEC_FP313_F1_SHIFT                                               28
#define REGSPEC_FP313_F1_MASK                                        0xf0000000
#define REGSPEC_FP313_F1_RD(src)                     (((src) & 0xf0000000)>>28)
#define REGSPEC_FP313_F1_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields FP30	 */
#define REGSPEC_FP303_F1_WIDTH                                                4
#define REGSPEC_FP303_F1_SHIFT                                               24
#define REGSPEC_FP303_F1_MASK                                        0x0f000000
#define REGSPEC_FP303_F1_RD(src)                     (((src) & 0x0f000000)>>24)
#define REGSPEC_FP303_F1_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields FP29	 */
#define REGSPEC_FP293_F1_WIDTH                                                4
#define REGSPEC_FP293_F1_SHIFT                                               20
#define REGSPEC_FP293_F1_MASK                                        0x00f00000
#define REGSPEC_FP293_F1_RD(src)                     (((src) & 0x00f00000)>>20)
#define REGSPEC_FP293_F1_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields FP28	 */
#define REGSPEC_FP283_F1_WIDTH                                                4
#define REGSPEC_FP283_F1_SHIFT                                               16
#define REGSPEC_FP283_F1_MASK                                        0x000f0000
#define REGSPEC_FP283_F1_RD(src)                     (((src) & 0x000f0000)>>16)
#define REGSPEC_FP283_F1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields FP27	 */
#define REGSPEC_FP273_F1_WIDTH                                                4
#define REGSPEC_FP273_F1_SHIFT                                               12
#define REGSPEC_FP273_F1_MASK                                        0x0000f000
#define REGSPEC_FP273_F1_RD(src)                     (((src) & 0x0000f000)>>12)
#define REGSPEC_FP273_F1_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields FP26	 */
#define REGSPEC_FP263_F1_WIDTH                                                4
#define REGSPEC_FP263_F1_SHIFT                                                8
#define REGSPEC_FP263_F1_MASK                                        0x00000f00
#define REGSPEC_FP263_F1_RD(src)                      (((src) & 0x00000f00)>>8)
#define REGSPEC_FP263_F1_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields FP25	 */
#define REGSPEC_FP253_F1_WIDTH                                                4
#define REGSPEC_FP253_F1_SHIFT                                                4
#define REGSPEC_FP253_F1_MASK                                        0x000000f0
#define REGSPEC_FP253_F1_RD(src)                      (((src) & 0x000000f0)>>4)
#define REGSPEC_FP253_F1_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields FP24	 */
#define REGSPEC_FP243_F1_WIDTH                                                4
#define REGSPEC_FP243_F1_SHIFT                                                0
#define REGSPEC_FP243_F1_MASK                                        0x0000000f
#define REGSPEC_FP243_F1_RD(src)                         (((src) & 0x0000000f))
#define REGSPEC_FP243_F1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiWQPtr0	*/ 
/*	 Fields WQ7	 */
#define REGSPEC_WQ70_WIDTH                                                    4
#define REGSPEC_WQ70_SHIFT                                                   28
#define REGSPEC_WQ70_MASK                                            0xf0000000
#define REGSPEC_WQ70_RD(src)                         (((src) & 0xf0000000)>>28)
#define REGSPEC_WQ70_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields WQ6	 */
#define REGSPEC_WQ60_WIDTH                                                    4
#define REGSPEC_WQ60_SHIFT                                                   24
#define REGSPEC_WQ60_MASK                                            0x0f000000
#define REGSPEC_WQ60_RD(src)                         (((src) & 0x0f000000)>>24)
#define REGSPEC_WQ60_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields WQ5	 */
#define REGSPEC_WQ50_WIDTH                                                    4
#define REGSPEC_WQ50_SHIFT                                                   20
#define REGSPEC_WQ50_MASK                                            0x00f00000
#define REGSPEC_WQ50_RD(src)                         (((src) & 0x00f00000)>>20)
#define REGSPEC_WQ50_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields WQ4	 */
#define REGSPEC_WQ40_WIDTH                                                    4
#define REGSPEC_WQ40_SHIFT                                                   16
#define REGSPEC_WQ40_MASK                                            0x000f0000
#define REGSPEC_WQ40_RD(src)                         (((src) & 0x000f0000)>>16)
#define REGSPEC_WQ40_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields WQ3	 */
#define REGSPEC_WQ30_WIDTH                                                    4
#define REGSPEC_WQ30_SHIFT                                                   12
#define REGSPEC_WQ30_MASK                                            0x0000f000
#define REGSPEC_WQ30_RD(src)                         (((src) & 0x0000f000)>>12)
#define REGSPEC_WQ30_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WQ2	 */
#define REGSPEC_WQ20_WIDTH                                                    4
#define REGSPEC_WQ20_SHIFT                                                    8
#define REGSPEC_WQ20_MASK                                            0x00000f00
#define REGSPEC_WQ20_RD(src)                          (((src) & 0x00000f00)>>8)
#define REGSPEC_WQ20_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields WQ1	 */
#define REGSPEC_WQ10_WIDTH                                                    4
#define REGSPEC_WQ10_SHIFT                                                    4
#define REGSPEC_WQ10_MASK                                            0x000000f0
#define REGSPEC_WQ10_RD(src)                          (((src) & 0x000000f0)>>4)
#define REGSPEC_WQ10_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields WQ0	 */
#define REGSPEC_WQ00_WIDTH                                                    4
#define REGSPEC_WQ00_SHIFT                                                    0
#define REGSPEC_WQ00_MASK                                            0x0000000f
#define REGSPEC_WQ00_RD(src)                             (((src) & 0x0000000f))
#define REGSPEC_WQ00_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiWQPtr1	*/ 
/*	 Fields WQ15	 */
#define REGSPEC_WQ151_WIDTH                                                   4
#define REGSPEC_WQ151_SHIFT                                                  28
#define REGSPEC_WQ151_MASK                                           0xf0000000
#define REGSPEC_WQ151_RD(src)                        (((src) & 0xf0000000)>>28)
#define REGSPEC_WQ151_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields WQ14	 */
#define REGSPEC_WQ141_WIDTH                                                   4
#define REGSPEC_WQ141_SHIFT                                                  24
#define REGSPEC_WQ141_MASK                                           0x0f000000
#define REGSPEC_WQ141_RD(src)                        (((src) & 0x0f000000)>>24)
#define REGSPEC_WQ141_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields WQ13	 */
#define REGSPEC_WQ131_WIDTH                                                   4
#define REGSPEC_WQ131_SHIFT                                                  20
#define REGSPEC_WQ131_MASK                                           0x00f00000
#define REGSPEC_WQ131_RD(src)                        (((src) & 0x00f00000)>>20)
#define REGSPEC_WQ131_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields WQ12	 */
#define REGSPEC_WQ121_WIDTH                                                   4
#define REGSPEC_WQ121_SHIFT                                                  16
#define REGSPEC_WQ121_MASK                                           0x000f0000
#define REGSPEC_WQ121_RD(src)                        (((src) & 0x000f0000)>>16)
#define REGSPEC_WQ121_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields WQ11	 */
#define REGSPEC_WQ111_WIDTH                                                   4
#define REGSPEC_WQ111_SHIFT                                                  12
#define REGSPEC_WQ111_MASK                                           0x0000f000
#define REGSPEC_WQ111_RD(src)                        (((src) & 0x0000f000)>>12)
#define REGSPEC_WQ111_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WQ10	 */
#define REGSPEC_WQ101_WIDTH                                                   4
#define REGSPEC_WQ101_SHIFT                                                   8
#define REGSPEC_WQ101_MASK                                           0x00000f00
#define REGSPEC_WQ101_RD(src)                         (((src) & 0x00000f00)>>8)
#define REGSPEC_WQ101_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields WQ9	 */
#define REGSPEC_WQ91_WIDTH                                                    4
#define REGSPEC_WQ91_SHIFT                                                    4
#define REGSPEC_WQ91_MASK                                            0x000000f0
#define REGSPEC_WQ91_RD(src)                          (((src) & 0x000000f0)>>4)
#define REGSPEC_WQ91_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields WQ8	 */
#define REGSPEC_WQ81_WIDTH                                                    4
#define REGSPEC_WQ81_SHIFT                                                    0
#define REGSPEC_WQ81_MASK                                            0x0000000f
#define REGSPEC_WQ81_RD(src)                             (((src) & 0x0000000f))
#define REGSPEC_WQ81_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiWQPtr2	*/ 
/*	 Fields WQ23	 */
#define REGSPEC_WQ232_WIDTH                                                   4
#define REGSPEC_WQ232_SHIFT                                                  28
#define REGSPEC_WQ232_MASK                                           0xf0000000
#define REGSPEC_WQ232_RD(src)                        (((src) & 0xf0000000)>>28)
#define REGSPEC_WQ232_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields WQ22	 */
#define REGSPEC_WQ222_WIDTH                                                   4
#define REGSPEC_WQ222_SHIFT                                                  24
#define REGSPEC_WQ222_MASK                                           0x0f000000
#define REGSPEC_WQ222_RD(src)                        (((src) & 0x0f000000)>>24)
#define REGSPEC_WQ222_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields WQ21	 */
#define REGSPEC_WQ212_WIDTH                                                   4
#define REGSPEC_WQ212_SHIFT                                                  20
#define REGSPEC_WQ212_MASK                                           0x00f00000
#define REGSPEC_WQ212_RD(src)                        (((src) & 0x00f00000)>>20)
#define REGSPEC_WQ212_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields WQ20	 */
#define REGSPEC_WQ202_WIDTH                                                   4
#define REGSPEC_WQ202_SHIFT                                                  16
#define REGSPEC_WQ202_MASK                                           0x000f0000
#define REGSPEC_WQ202_RD(src)                        (((src) & 0x000f0000)>>16)
#define REGSPEC_WQ202_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields WQ19	 */
#define REGSPEC_WQ192_WIDTH                                                   4
#define REGSPEC_WQ192_SHIFT                                                  12
#define REGSPEC_WQ192_MASK                                           0x0000f000
#define REGSPEC_WQ192_RD(src)                        (((src) & 0x0000f000)>>12)
#define REGSPEC_WQ192_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WQ18	 */
#define REGSPEC_WQ182_WIDTH                                                   4
#define REGSPEC_WQ182_SHIFT                                                   8
#define REGSPEC_WQ182_MASK                                           0x00000f00
#define REGSPEC_WQ182_RD(src)                         (((src) & 0x00000f00)>>8)
#define REGSPEC_WQ182_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields WQ17	 */
#define REGSPEC_WQ172_WIDTH                                                   4
#define REGSPEC_WQ172_SHIFT                                                   4
#define REGSPEC_WQ172_MASK                                           0x000000f0
#define REGSPEC_WQ172_RD(src)                         (((src) & 0x000000f0)>>4)
#define REGSPEC_WQ172_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields WQ16	 */
#define REGSPEC_WQ162_WIDTH                                                   4
#define REGSPEC_WQ162_SHIFT                                                   0
#define REGSPEC_WQ162_MASK                                           0x0000000f
#define REGSPEC_WQ162_RD(src)                            (((src) & 0x0000000f))
#define REGSPEC_WQ162_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiWQPtr3	*/ 
/*	 Fields WQ31	 */
#define REGSPEC_WQ313_WIDTH                                                   4
#define REGSPEC_WQ313_SHIFT                                                  28
#define REGSPEC_WQ313_MASK                                           0xf0000000
#define REGSPEC_WQ313_RD(src)                        (((src) & 0xf0000000)>>28)
#define REGSPEC_WQ313_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields WQ30	 */
#define REGSPEC_WQ303_WIDTH                                                   4
#define REGSPEC_WQ303_SHIFT                                                  24
#define REGSPEC_WQ303_MASK                                           0x0f000000
#define REGSPEC_WQ303_RD(src)                        (((src) & 0x0f000000)>>24)
#define REGSPEC_WQ303_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields WQ29	 */
#define REGSPEC_WQ293_WIDTH                                                   4
#define REGSPEC_WQ293_SHIFT                                                  20
#define REGSPEC_WQ293_MASK                                           0x00f00000
#define REGSPEC_WQ293_RD(src)                        (((src) & 0x00f00000)>>20)
#define REGSPEC_WQ293_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields WQ28	 */
#define REGSPEC_WQ283_WIDTH                                                   4
#define REGSPEC_WQ283_SHIFT                                                  16
#define REGSPEC_WQ283_MASK                                           0x000f0000
#define REGSPEC_WQ283_RD(src)                        (((src) & 0x000f0000)>>16)
#define REGSPEC_WQ283_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields WQ27	 */
#define REGSPEC_WQ273_WIDTH                                                   4
#define REGSPEC_WQ273_SHIFT                                                  12
#define REGSPEC_WQ273_MASK                                           0x0000f000
#define REGSPEC_WQ273_RD(src)                        (((src) & 0x0000f000)>>12)
#define REGSPEC_WQ273_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields WQ26	 */
#define REGSPEC_WQ263_WIDTH                                                   4
#define REGSPEC_WQ263_SHIFT                                                   8
#define REGSPEC_WQ263_MASK                                           0x00000f00
#define REGSPEC_WQ263_RD(src)                         (((src) & 0x00000f00)>>8)
#define REGSPEC_WQ263_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields WQ25	 */
#define REGSPEC_WQ253_WIDTH                                                   4
#define REGSPEC_WQ253_SHIFT                                                   4
#define REGSPEC_WQ253_MASK                                           0x000000f0
#define REGSPEC_WQ253_RD(src)                         (((src) & 0x000000f0)>>4)
#define REGSPEC_WQ253_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields WQ24	 */
#define REGSPEC_WQ243_WIDTH                                                   4
#define REGSPEC_WQ243_SHIFT                                                   0
#define REGSPEC_WQ243_MASK                                           0x0000000f
#define REGSPEC_WQ243_RD(src)                            (((src) & 0x0000000f))
#define REGSPEC_WQ243_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register StsSsQmiWQNumEntries0	*/ 
/*	 Fields WQ3	 */
#define REGSPEC_WQ30_F1_WIDTH                                                 5
#define REGSPEC_WQ30_F1_SHIFT                                                24
#define REGSPEC_WQ30_F1_MASK                                         0x1f000000
#define REGSPEC_WQ30_F1_RD(src)                      (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ30_F1_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ2	 */
#define REGSPEC_WQ20_F1_WIDTH                                                 5
#define REGSPEC_WQ20_F1_SHIFT                                                16
#define REGSPEC_WQ20_F1_MASK                                         0x001f0000
#define REGSPEC_WQ20_F1_RD(src)                      (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ20_F1_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ1	 */
#define REGSPEC_WQ10_F1_WIDTH                                                 5
#define REGSPEC_WQ10_F1_SHIFT                                                 8
#define REGSPEC_WQ10_F1_MASK                                         0x00001f00
#define REGSPEC_WQ10_F1_RD(src)                       (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ10_F1_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ0	 */
#define REGSPEC_WQ00_F1_WIDTH                                                 5
#define REGSPEC_WQ00_F1_SHIFT                                                 0
#define REGSPEC_WQ00_F1_MASK                                         0x0000001f
#define REGSPEC_WQ00_F1_RD(src)                          (((src) & 0x0000001f))
#define REGSPEC_WQ00_F1_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries1	*/ 
/*	 Fields WQ7	 */
#define REGSPEC_WQ71_WIDTH                                                    5
#define REGSPEC_WQ71_SHIFT                                                   24
#define REGSPEC_WQ71_MASK                                            0x1f000000
#define REGSPEC_WQ71_RD(src)                         (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ71_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ6	 */
#define REGSPEC_WQ61_WIDTH                                                    5
#define REGSPEC_WQ61_SHIFT                                                   16
#define REGSPEC_WQ61_MASK                                            0x001f0000
#define REGSPEC_WQ61_RD(src)                         (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ61_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ5	 */
#define REGSPEC_WQ51_WIDTH                                                    5
#define REGSPEC_WQ51_SHIFT                                                    8
#define REGSPEC_WQ51_MASK                                            0x00001f00
#define REGSPEC_WQ51_RD(src)                          (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ51_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ4	 */
#define REGSPEC_WQ41_WIDTH                                                    5
#define REGSPEC_WQ41_SHIFT                                                    0
#define REGSPEC_WQ41_MASK                                            0x0000001f
#define REGSPEC_WQ41_RD(src)                             (((src) & 0x0000001f))
#define REGSPEC_WQ41_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries2	*/ 
/*	 Fields WQ11	 */
#define REGSPEC_WQ112_WIDTH                                                   5
#define REGSPEC_WQ112_SHIFT                                                  24
#define REGSPEC_WQ112_MASK                                           0x1f000000
#define REGSPEC_WQ112_RD(src)                        (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ112_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ10	 */
#define REGSPEC_WQ102_WIDTH                                                   5
#define REGSPEC_WQ102_SHIFT                                                  16
#define REGSPEC_WQ102_MASK                                           0x001f0000
#define REGSPEC_WQ102_RD(src)                        (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ102_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ9	 */
#define REGSPEC_WQ92_WIDTH                                                    5
#define REGSPEC_WQ92_SHIFT                                                    8
#define REGSPEC_WQ92_MASK                                            0x00001f00
#define REGSPEC_WQ92_RD(src)                          (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ92_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ8	 */
#define REGSPEC_WQ82_WIDTH                                                    5
#define REGSPEC_WQ82_SHIFT                                                    0
#define REGSPEC_WQ82_MASK                                            0x0000001f
#define REGSPEC_WQ82_RD(src)                             (((src) & 0x0000001f))
#define REGSPEC_WQ82_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries3	*/ 
/*	 Fields WQ15	 */
#define REGSPEC_WQ153_WIDTH                                                   5
#define REGSPEC_WQ153_SHIFT                                                  24
#define REGSPEC_WQ153_MASK                                           0x1f000000
#define REGSPEC_WQ153_RD(src)                        (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ153_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ14	 */
#define REGSPEC_WQ143_WIDTH                                                   5
#define REGSPEC_WQ143_SHIFT                                                  16
#define REGSPEC_WQ143_MASK                                           0x001f0000
#define REGSPEC_WQ143_RD(src)                        (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ143_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ13	 */
#define REGSPEC_WQ133_WIDTH                                                   5
#define REGSPEC_WQ133_SHIFT                                                   8
#define REGSPEC_WQ133_MASK                                           0x00001f00
#define REGSPEC_WQ133_RD(src)                         (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ133_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ12	 */
#define REGSPEC_WQ123_WIDTH                                                   5
#define REGSPEC_WQ123_SHIFT                                                   0
#define REGSPEC_WQ123_MASK                                           0x0000001f
#define REGSPEC_WQ123_RD(src)                            (((src) & 0x0000001f))
#define REGSPEC_WQ123_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries4	*/ 
/*	 Fields WQ19	 */
#define REGSPEC_WQ194_WIDTH                                                   5
#define REGSPEC_WQ194_SHIFT                                                  24
#define REGSPEC_WQ194_MASK                                           0x1f000000
#define REGSPEC_WQ194_RD(src)                        (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ194_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ18	 */
#define REGSPEC_WQ184_WIDTH                                                   5
#define REGSPEC_WQ184_SHIFT                                                  16
#define REGSPEC_WQ184_MASK                                           0x001f0000
#define REGSPEC_WQ184_RD(src)                        (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ184_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ17	 */
#define REGSPEC_WQ174_WIDTH                                                   5
#define REGSPEC_WQ174_SHIFT                                                   8
#define REGSPEC_WQ174_MASK                                           0x00001f00
#define REGSPEC_WQ174_RD(src)                         (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ174_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ16	 */
#define REGSPEC_WQ164_WIDTH                                                   5
#define REGSPEC_WQ164_SHIFT                                                   0
#define REGSPEC_WQ164_MASK                                           0x0000001f
#define REGSPEC_WQ164_RD(src)                            (((src) & 0x0000001f))
#define REGSPEC_WQ164_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries5	*/ 
/*	 Fields WQ23	 */
#define REGSPEC_WQ235_WIDTH                                                   5
#define REGSPEC_WQ235_SHIFT                                                  24
#define REGSPEC_WQ235_MASK                                           0x1f000000
#define REGSPEC_WQ235_RD(src)                        (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ235_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ22	 */
#define REGSPEC_WQ225_WIDTH                                                   5
#define REGSPEC_WQ225_SHIFT                                                  16
#define REGSPEC_WQ225_MASK                                           0x001f0000
#define REGSPEC_WQ225_RD(src)                        (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ225_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ21	 */
#define REGSPEC_WQ215_WIDTH                                                   5
#define REGSPEC_WQ215_SHIFT                                                   8
#define REGSPEC_WQ215_MASK                                           0x00001f00
#define REGSPEC_WQ215_RD(src)                         (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ215_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ20	 */
#define REGSPEC_WQ205_WIDTH                                                   5
#define REGSPEC_WQ205_SHIFT                                                   0
#define REGSPEC_WQ205_MASK                                           0x0000001f
#define REGSPEC_WQ205_RD(src)                            (((src) & 0x0000001f))
#define REGSPEC_WQ205_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries6	*/ 
/*	 Fields WQ27	 */
#define REGSPEC_WQ276_WIDTH                                                   5
#define REGSPEC_WQ276_SHIFT                                                  24
#define REGSPEC_WQ276_MASK                                           0x1f000000
#define REGSPEC_WQ276_RD(src)                        (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ276_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ26	 */
#define REGSPEC_WQ266_WIDTH                                                   5
#define REGSPEC_WQ266_SHIFT                                                  16
#define REGSPEC_WQ266_MASK                                           0x001f0000
#define REGSPEC_WQ266_RD(src)                        (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ266_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ25	 */
#define REGSPEC_WQ256_WIDTH                                                   5
#define REGSPEC_WQ256_SHIFT                                                   8
#define REGSPEC_WQ256_MASK                                           0x00001f00
#define REGSPEC_WQ256_RD(src)                         (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ256_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ24	 */
#define REGSPEC_WQ246_WIDTH                                                   5
#define REGSPEC_WQ246_SHIFT                                                   0
#define REGSPEC_WQ246_MASK                                           0x0000001f
#define REGSPEC_WQ246_RD(src)                            (((src) & 0x0000001f))
#define REGSPEC_WQ246_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register StsSsQmiWQNumEntries7	*/ 
/*	 Fields WQ31	 */
#define REGSPEC_WQ317_WIDTH                                                   5
#define REGSPEC_WQ317_SHIFT                                                  24
#define REGSPEC_WQ317_MASK                                           0x1f000000
#define REGSPEC_WQ317_RD(src)                        (((src) & 0x1f000000)>>24)
#define REGSPEC_WQ317_SET(dst,src) \
                      (((dst) & ~0x1f000000) | (((u32)(src)<<24) & 0x1f000000))
/*	 Fields WQ30	 */
#define REGSPEC_WQ307_WIDTH                                                   5
#define REGSPEC_WQ307_SHIFT                                                  16
#define REGSPEC_WQ307_MASK                                           0x001f0000
#define REGSPEC_WQ307_RD(src)                        (((src) & 0x001f0000)>>16)
#define REGSPEC_WQ307_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields WQ29	 */
#define REGSPEC_WQ297_WIDTH                                                   5
#define REGSPEC_WQ297_SHIFT                                                   8
#define REGSPEC_WQ297_MASK                                           0x00001f00
#define REGSPEC_WQ297_RD(src)                         (((src) & 0x00001f00)>>8)
#define REGSPEC_WQ297_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields WQ28	 */
#define REGSPEC_WQ287_WIDTH                                                   5
#define REGSPEC_WQ287_SHIFT                                                   0
#define REGSPEC_WQ287_MASK                                           0x0000001f
#define REGSPEC_WQ287_RD(src)                            (((src) & 0x0000001f))
#define REGSPEC_WQ287_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register CfgSsQmiSabEnable	*/ 
/*	 Fields EnableMonitoring	 */
#define REGSPEC_ENABLEMONITORING_WIDTH                                       20
#define REGSPEC_ENABLEMONITORING_SHIFT                                        0
#define REGSPEC_ENABLEMONITORING_MASK                                0x000fffff
#define REGSPEC_ENABLEMONITORING_RD(src)                 (((src) & 0x000fffff))
#define REGSPEC_ENABLEMONITORING_WR(src)            (((u32)(src)) & 0x000fffff)
#define REGSPEC_ENABLEMONITORING_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register CfgSsQmiSab0	*/ 
/*	 Fields QID1	 */
#define REGSPEC_QID10_WIDTH                                                  12
#define REGSPEC_QID10_SHIFT                                                  16
#define REGSPEC_QID10_MASK                                           0x0fff0000
#define REGSPEC_QID10_RD(src)                        (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID10_WR(src)                   (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID10_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID0	 */
#define REGSPEC_QID00_WIDTH                                                  12
#define REGSPEC_QID00_SHIFT                                                   0
#define REGSPEC_QID00_MASK                                           0x00000fff
#define REGSPEC_QID00_RD(src)                            (((src) & 0x00000fff))
#define REGSPEC_QID00_WR(src)                       (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID00_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab1	*/ 
/*	 Fields QID3	 */
#define REGSPEC_QID31_WIDTH                                                  12
#define REGSPEC_QID31_SHIFT                                                  16
#define REGSPEC_QID31_MASK                                           0x0fff0000
#define REGSPEC_QID31_RD(src)                        (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID31_WR(src)                   (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID31_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID2	 */
#define REGSPEC_QID21_WIDTH                                                  12
#define REGSPEC_QID21_SHIFT                                                   0
#define REGSPEC_QID21_MASK                                           0x00000fff
#define REGSPEC_QID21_RD(src)                            (((src) & 0x00000fff))
#define REGSPEC_QID21_WR(src)                       (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID21_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab2	*/ 
/*	 Fields QID5	 */
#define REGSPEC_QID52_WIDTH                                                  12
#define REGSPEC_QID52_SHIFT                                                  16
#define REGSPEC_QID52_MASK                                           0x0fff0000
#define REGSPEC_QID52_RD(src)                        (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID52_WR(src)                   (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID52_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID4	 */
#define REGSPEC_QID42_WIDTH                                                  12
#define REGSPEC_QID42_SHIFT                                                   0
#define REGSPEC_QID42_MASK                                           0x00000fff
#define REGSPEC_QID42_RD(src)                            (((src) & 0x00000fff))
#define REGSPEC_QID42_WR(src)                       (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID42_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab3	*/ 
/*	 Fields QID7	 */
#define REGSPEC_QID73_WIDTH                                                  12
#define REGSPEC_QID73_SHIFT                                                  16
#define REGSPEC_QID73_MASK                                           0x0fff0000
#define REGSPEC_QID73_RD(src)                        (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID73_WR(src)                   (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID73_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID6	 */
#define REGSPEC_QID63_WIDTH                                                  12
#define REGSPEC_QID63_SHIFT                                                   0
#define REGSPEC_QID63_MASK                                           0x00000fff
#define REGSPEC_QID63_RD(src)                            (((src) & 0x00000fff))
#define REGSPEC_QID63_WR(src)                       (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID63_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab4	*/ 
/*	 Fields QID9	 */
#define REGSPEC_QID94_WIDTH                                                  12
#define REGSPEC_QID94_SHIFT                                                  16
#define REGSPEC_QID94_MASK                                           0x0fff0000
#define REGSPEC_QID94_RD(src)                        (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID94_WR(src)                   (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID94_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID8	 */
#define REGSPEC_QID84_WIDTH                                                  12
#define REGSPEC_QID84_SHIFT                                                   0
#define REGSPEC_QID84_MASK                                           0x00000fff
#define REGSPEC_QID84_RD(src)                            (((src) & 0x00000fff))
#define REGSPEC_QID84_WR(src)                       (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID84_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab5	*/ 
/*	 Fields QID11	 */
#define REGSPEC_QID115_WIDTH                                                 12
#define REGSPEC_QID115_SHIFT                                                 16
#define REGSPEC_QID115_MASK                                          0x0fff0000
#define REGSPEC_QID115_RD(src)                       (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID115_WR(src)                  (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID115_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID10	 */
#define REGSPEC_QID105_WIDTH                                                 12
#define REGSPEC_QID105_SHIFT                                                  0
#define REGSPEC_QID105_MASK                                          0x00000fff
#define REGSPEC_QID105_RD(src)                           (((src) & 0x00000fff))
#define REGSPEC_QID105_WR(src)                      (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID105_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab6	*/ 
/*	 Fields QID13	 */
#define REGSPEC_QID136_WIDTH                                                 12
#define REGSPEC_QID136_SHIFT                                                 16
#define REGSPEC_QID136_MASK                                          0x0fff0000
#define REGSPEC_QID136_RD(src)                       (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID136_WR(src)                  (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID136_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID12	 */
#define REGSPEC_QID126_WIDTH                                                 12
#define REGSPEC_QID126_SHIFT                                                  0
#define REGSPEC_QID126_MASK                                          0x00000fff
#define REGSPEC_QID126_RD(src)                           (((src) & 0x00000fff))
#define REGSPEC_QID126_WR(src)                      (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID126_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab7	*/ 
/*	 Fields QID15	 */
#define REGSPEC_QID157_WIDTH                                                 12
#define REGSPEC_QID157_SHIFT                                                 16
#define REGSPEC_QID157_MASK                                          0x0fff0000
#define REGSPEC_QID157_RD(src)                       (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID157_WR(src)                  (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID157_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID14	 */
#define REGSPEC_QID147_WIDTH                                                 12
#define REGSPEC_QID147_SHIFT                                                  0
#define REGSPEC_QID147_MASK                                          0x00000fff
#define REGSPEC_QID147_RD(src)                           (((src) & 0x00000fff))
#define REGSPEC_QID147_WR(src)                      (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID147_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab8	*/ 
/*	 Fields QID17	 */
#define REGSPEC_QID178_WIDTH                                                 12
#define REGSPEC_QID178_SHIFT                                                 16
#define REGSPEC_QID178_MASK                                          0x0fff0000
#define REGSPEC_QID178_RD(src)                       (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID178_WR(src)                  (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID178_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID16	 */
#define REGSPEC_QID168_WIDTH                                                 12
#define REGSPEC_QID168_SHIFT                                                  0
#define REGSPEC_QID168_MASK                                          0x00000fff
#define REGSPEC_QID168_RD(src)                           (((src) & 0x00000fff))
#define REGSPEC_QID168_WR(src)                      (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID168_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register CfgSsQmiSab9	*/ 
/*	 Fields QID19	 */
#define REGSPEC_QID199_WIDTH                                                 12
#define REGSPEC_QID199_SHIFT                                                 16
#define REGSPEC_QID199_MASK                                          0x0fff0000
#define REGSPEC_QID199_RD(src)                       (((src) & 0x0fff0000)>>16)
#define REGSPEC_QID199_WR(src)                  (((u32)(src)<<16) & 0x0fff0000)
#define REGSPEC_QID199_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields QID18	 */
#define REGSPEC_QID189_WIDTH                                                 12
#define REGSPEC_QID189_SHIFT                                                  0
#define REGSPEC_QID189_MASK                                          0x00000fff
#define REGSPEC_QID189_RD(src)                           (((src) & 0x00000fff))
#define REGSPEC_QID189_WR(src)                      (((u32)(src)) & 0x00000fff)
#define REGSPEC_QID189_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register StsSsQmiInt0	*/ 
/*	 Fields FPOverflow	 */
#define REGSPEC_FPOVERFLOW0_WIDTH                                            32
#define REGSPEC_FPOVERFLOW0_SHIFT                                             0
#define REGSPEC_FPOVERFLOW0_MASK                                     0xffffffff
#define REGSPEC_FPOVERFLOW0_RD(src)                      (((src) & 0xffffffff))
#define REGSPEC_FPOVERFLOW0_WR(src)                 (((u32)(src)) & 0xffffffff)
#define REGSPEC_FPOVERFLOW0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt0Mask	*/
/*    Mask Register Fields FPOverflowMask    */
#define REGSPEC_FPOVERFLOWMASK_WIDTH                                         32
#define REGSPEC_FPOVERFLOWMASK_SHIFT                                          0
#define REGSPEC_FPOVERFLOWMASK_MASK                                  0xffffffff
#define REGSPEC_FPOVERFLOWMASK_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_FPOVERFLOWMASK_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_FPOVERFLOWMASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt1	*/ 
/*	 Fields WQOverflow	 */
#define REGSPEC_WQOVERFLOW1_WIDTH                                            32
#define REGSPEC_WQOVERFLOW1_SHIFT                                             0
#define REGSPEC_WQOVERFLOW1_MASK                                     0xffffffff
#define REGSPEC_WQOVERFLOW1_RD(src)                      (((src) & 0xffffffff))
#define REGSPEC_WQOVERFLOW1_WR(src)                 (((u32)(src)) & 0xffffffff)
#define REGSPEC_WQOVERFLOW1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt1Mask	*/
/*    Mask Register Fields WQOverflowMask    */
#define REGSPEC_WQOVERFLOWMASK_WIDTH                                         32
#define REGSPEC_WQOVERFLOWMASK_SHIFT                                          0
#define REGSPEC_WQOVERFLOWMASK_MASK                                  0xffffffff
#define REGSPEC_WQOVERFLOWMASK_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_WQOVERFLOWMASK_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_WQOVERFLOWMASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt2	*/ 
/*	 Fields FPUnderRun	 */
#define REGSPEC_FPUNDERRUN2_WIDTH                                            32
#define REGSPEC_FPUNDERRUN2_SHIFT                                             0
#define REGSPEC_FPUNDERRUN2_MASK                                     0xffffffff
#define REGSPEC_FPUNDERRUN2_RD(src)                      (((src) & 0xffffffff))
#define REGSPEC_FPUNDERRUN2_WR(src)                 (((u32)(src)) & 0xffffffff)
#define REGSPEC_FPUNDERRUN2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt2Mask	*/
/*    Mask Register Fields FPUnderRunMask    */
#define REGSPEC_FPUNDERRUNMASK_WIDTH                                         32
#define REGSPEC_FPUNDERRUNMASK_SHIFT                                          0
#define REGSPEC_FPUNDERRUNMASK_MASK                                  0xffffffff
#define REGSPEC_FPUNDERRUNMASK_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_FPUNDERRUNMASK_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_FPUNDERRUNMASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt3	*/ 
/*	 Fields WQUnderRun	 */
#define REGSPEC_WQUNDERRUN3_WIDTH                                            32
#define REGSPEC_WQUNDERRUN3_SHIFT                                             0
#define REGSPEC_WQUNDERRUN3_MASK                                     0xffffffff
#define REGSPEC_WQUNDERRUN3_RD(src)                      (((src) & 0xffffffff))
#define REGSPEC_WQUNDERRUN3_WR(src)                 (((u32)(src)) & 0xffffffff)
#define REGSPEC_WQUNDERRUN3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt3Mask	*/
/*    Mask Register Fields WQUnderRunMask    */
#define REGSPEC_WQUNDERRUNMASK_WIDTH                                         32
#define REGSPEC_WQUNDERRUNMASK_SHIFT                                          0
#define REGSPEC_WQUNDERRUNMASK_MASK                                  0xffffffff
#define REGSPEC_WQUNDERRUNMASK_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_WQUNDERRUNMASK_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_WQUNDERRUNMASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiInt4	*/ 
/*	 Fields axiwcmr_slverr	 */
#define REGSPEC_AXIWCMR_SLVERR4_WIDTH                                         1
#define REGSPEC_AXIWCMR_SLVERR4_SHIFT                                         1
#define REGSPEC_AXIWCMR_SLVERR4_MASK                                 0x00000002
#define REGSPEC_AXIWCMR_SLVERR4_RD(src)               (((src) & 0x00000002)>>1)
#define REGSPEC_AXIWCMR_SLVERR4_WR(src)          (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_AXIWCMR_SLVERR4_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields axiwcmr_decerr	 */
#define REGSPEC_AXIWCMR_DECERR4_WIDTH                                         1
#define REGSPEC_AXIWCMR_DECERR4_SHIFT                                         0
#define REGSPEC_AXIWCMR_DECERR4_MASK                                 0x00000001
#define REGSPEC_AXIWCMR_DECERR4_RD(src)                  (((src) & 0x00000001))
#define REGSPEC_AXIWCMR_DECERR4_WR(src)             (((u32)(src)) & 0x00000001)
#define REGSPEC_AXIWCMR_DECERR4_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register StsSsQmiInt4Mask	*/
/*    Mask Register Fields axiwcmr_slverrMask    */
#define REGSPEC_AXIWCMR_SLVERRMASK_WIDTH                                      1
#define REGSPEC_AXIWCMR_SLVERRMASK_SHIFT                                      1
#define REGSPEC_AXIWCMR_SLVERRMASK_MASK                              0x00000002
#define REGSPEC_AXIWCMR_SLVERRMASK_RD(src)            (((src) & 0x00000002)>>1)
#define REGSPEC_AXIWCMR_SLVERRMASK_WR(src)       (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_AXIWCMR_SLVERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields axiwcmr_decerrMask    */
#define REGSPEC_AXIWCMR_DECERRMASK_WIDTH                                      1
#define REGSPEC_AXIWCMR_DECERRMASK_SHIFT                                      0
#define REGSPEC_AXIWCMR_DECERRMASK_MASK                              0x00000001
#define REGSPEC_AXIWCMR_DECERRMASK_RD(src)               (((src) & 0x00000001))
#define REGSPEC_AXIWCMR_DECERRMASK_WR(src)          (((u32)(src)) & 0x00000001)
#define REGSPEC_AXIWCMR_DECERRMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CfgSsQmiDbgCtrl	*/ 
/*	 Fields PBID	 */
#define REGSPEC_PBID_WIDTH                                                    6
#define REGSPEC_PBID_SHIFT                                                   12
#define REGSPEC_PBID_MASK                                            0x0003f000
#define REGSPEC_PBID_RD(src)                         (((src) & 0x0003f000)>>12)
#define REGSPEC_PBID_WR(src)                    (((u32)(src)<<12) & 0x0003f000)
#define REGSPEC_PBID_SET(dst,src) \
                      (((dst) & ~0x0003f000) | (((u32)(src)<<12) & 0x0003f000))
/*	 Fields nAck	 */
#define REGSPEC_NACK_WIDTH                                                    1
#define REGSPEC_NACK_SHIFT                                                   11
#define REGSPEC_NACK_MASK                                            0x00000800
#define REGSPEC_NACK_RD(src)                         (((src) & 0x00000800)>>11)
#define REGSPEC_NACK_WR(src)                    (((u32)(src)<<11) & 0x00000800)
#define REGSPEC_NACK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields last	 */
#define REGSPEC_LAST_WIDTH                                                    1
#define REGSPEC_LAST_SHIFT                                                   10
#define REGSPEC_LAST_MASK                                            0x00000400
#define REGSPEC_LAST_RD(src)                         (((src) & 0x00000400)>>10)
#define REGSPEC_LAST_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define REGSPEC_LAST_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields Push	 */
#define REGSPEC_PUSH_WIDTH                                                    1
#define REGSPEC_PUSH_SHIFT                                                    9
#define REGSPEC_PUSH_MASK                                            0x00000200
#define REGSPEC_PUSH_RD(src)                          (((src) & 0x00000200)>>9)
#define REGSPEC_PUSH_WR(src)                     (((u32)(src)<<9) & 0x00000200)
#define REGSPEC_PUSH_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields Write	 */
#define REGSPEC_WRITE_WIDTH                                                   1
#define REGSPEC_WRITE_SHIFT                                                   8
#define REGSPEC_WRITE_MASK                                           0x00000100
#define REGSPEC_WRITE_RD(src)                         (((src) & 0x00000100)>>8)
#define REGSPEC_WRITE_WR(src)                    (((u32)(src)<<8) & 0x00000100)
#define REGSPEC_WRITE_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields Pop	 */
#define REGSPEC_POP_WIDTH                                                     1
#define REGSPEC_POP_SHIFT                                                     7
#define REGSPEC_POP_MASK                                             0x00000080
#define REGSPEC_POP_RD(src)                           (((src) & 0x00000080)>>7)
#define REGSPEC_POP_WR(src)                      (((u32)(src)<<7) & 0x00000080)
#define REGSPEC_POP_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields Read	 */
#define REGSPEC_READ_WIDTH                                                    1
#define REGSPEC_READ_SHIFT                                                    6
#define REGSPEC_READ_MASK                                            0x00000040
#define REGSPEC_READ_RD(src)                          (((src) & 0x00000040)>>6)
#define REGSPEC_READ_WR(src)                     (((u32)(src)<<6) & 0x00000040)
#define REGSPEC_READ_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields BufferAddr	 */
#define REGSPEC_BUFFERADDR_WIDTH                                              6
#define REGSPEC_BUFFERADDR_SHIFT                                              0
#define REGSPEC_BUFFERADDR_MASK                                      0x0000003f
#define REGSPEC_BUFFERADDR_RD(src)                       (((src) & 0x0000003f))
#define REGSPEC_BUFFERADDR_WR(src)                  (((u32)(src)) & 0x0000003f)
#define REGSPEC_BUFFERADDR_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register CfgSsQmiDbgData0	*/ 
/*	 Fields Data	 */
#define REGSPEC_DATA0_WIDTH                                                  32
#define REGSPEC_DATA0_SHIFT                                                   0
#define REGSPEC_DATA0_MASK                                           0xffffffff
#define REGSPEC_DATA0_RD(src)                            (((src) & 0xffffffff))
#define REGSPEC_DATA0_WR(src)                       (((u32)(src)) & 0xffffffff)
#define REGSPEC_DATA0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiDbgData1	*/ 
/*	 Fields Data	 */
#define REGSPEC_DATA1_WIDTH                                                  32
#define REGSPEC_DATA1_SHIFT                                                   0
#define REGSPEC_DATA1_MASK                                           0xffffffff
#define REGSPEC_DATA1_RD(src)                            (((src) & 0xffffffff))
#define REGSPEC_DATA1_WR(src)                       (((u32)(src)) & 0xffffffff)
#define REGSPEC_DATA1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiDbgData2	*/ 
/*	 Fields Data	 */
#define REGSPEC_DATA2_WIDTH                                                  32
#define REGSPEC_DATA2_SHIFT                                                   0
#define REGSPEC_DATA2_MASK                                           0xffffffff
#define REGSPEC_DATA2_RD(src)                            (((src) & 0xffffffff))
#define REGSPEC_DATA2_WR(src)                       (((u32)(src)) & 0xffffffff)
#define REGSPEC_DATA2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiDbgData3	*/ 
/*	 Fields Data	 */
#define REGSPEC_DATA3_WIDTH                                                  32
#define REGSPEC_DATA3_SHIFT                                                   0
#define REGSPEC_DATA3_MASK                                           0xffffffff
#define REGSPEC_DATA3_RD(src)                            (((src) & 0xffffffff))
#define REGSPEC_DATA3_WR(src)                       (((u32)(src)) & 0xffffffff)
#define REGSPEC_DATA3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register StsSsQmiDbgData	*/ 
/*	 Fields Data	 */
#define REGSPEC_DATA_WIDTH                                                   32
#define REGSPEC_DATA_SHIFT                                                    0
#define REGSPEC_DATA_MASK                                            0xffffffff
#define REGSPEC_DATA_RD(src)                             (((src) & 0xffffffff))
#define REGSPEC_DATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiFPQAssoc	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION_WIDTH                                            32
#define REGSPEC_ASSOCIATION_SHIFT                                             0
#define REGSPEC_ASSOCIATION_MASK                                     0xffffffff
#define REGSPEC_ASSOCIATION_RD(src)                      (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION_WR(src)                 (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiWQAssoc	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION_F1_WIDTH                                         32
#define REGSPEC_ASSOCIATION_F1_SHIFT                                          0
#define REGSPEC_ASSOCIATION_F1_MASK                                  0xffffffff
#define REGSPEC_ASSOCIATION_F1_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION_F1_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiMemory	*/ 
/*	 Fields RMA	 */
#define REGSPEC_RMA_WIDTH                                                     2
#define REGSPEC_RMA_SHIFT                                                     4
#define REGSPEC_RMA_MASK                                             0x00000030
#define REGSPEC_RMA_RD(src)                           (((src) & 0x00000030)>>4)
#define REGSPEC_RMA_WR(src)                      (((u32)(src)<<4) & 0x00000030)
#define REGSPEC_RMA_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields RMB	 */
#define REGSPEC_RMB_WIDTH                                                     2
#define REGSPEC_RMB_SHIFT                                                     2
#define REGSPEC_RMB_MASK                                             0x0000000c
#define REGSPEC_RMB_RD(src)                           (((src) & 0x0000000c)>>2)
#define REGSPEC_RMB_WR(src)                      (((u32)(src)<<2) & 0x0000000c)
#define REGSPEC_RMB_SET(dst,src) \
                       (((dst) & ~0x0000000c) | (((u32)(src)<<2) & 0x0000000c))
/*	 Fields RMEA	 */
#define REGSPEC_RMEA_WIDTH                                                    1
#define REGSPEC_RMEA_SHIFT                                                    1
#define REGSPEC_RMEA_MASK                                            0x00000002
#define REGSPEC_RMEA_RD(src)                          (((src) & 0x00000002)>>1)
#define REGSPEC_RMEA_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_RMEA_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields RMEB	 */
#define REGSPEC_RMEB_WIDTH                                                    1
#define REGSPEC_RMEB_SHIFT                                                    0
#define REGSPEC_RMEB_MASK                                            0x00000001
#define REGSPEC_RMEB_RD(src)                             (((src) & 0x00000001))
#define REGSPEC_RMEB_WR(src)                        (((u32)(src)) & 0x00000001)
#define REGSPEC_RMEB_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register StsSsQmiFifo	*/ 
/*	 Fields empty	 */
#define REGSPEC_EMPTY_WIDTH                                                  27
#define REGSPEC_EMPTY_SHIFT                                                   0
#define REGSPEC_EMPTY_MASK                                           0x07ffffff
#define REGSPEC_EMPTY_RD(src)                            (((src) & 0x07ffffff))
#define REGSPEC_EMPTY_SET(dst,src) \
                          (((dst) & ~0x07ffffff) | (((u32)(src)) & 0x07ffffff))

/*	Register CfgSsQmiQMLite	*/ 
/*	 Fields Address	 */
#define REGSPEC_ADDRESS_WIDTH                                                20
#define REGSPEC_ADDRESS_SHIFT                                                 0
#define REGSPEC_ADDRESS_MASK                                         0x000fffff
#define REGSPEC_ADDRESS_RD(src)                          (((src) & 0x000fffff))
#define REGSPEC_ADDRESS_WR(src)                     (((u32)(src)) & 0x000fffff)
#define REGSPEC_ADDRESS_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register CfgSsQmiQMLiteFPQAssoc	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION_F2_WIDTH                                         32
#define REGSPEC_ASSOCIATION_F2_SHIFT                                          0
#define REGSPEC_ASSOCIATION_F2_MASK                                  0xffffffff
#define REGSPEC_ASSOCIATION_F2_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION_F2_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiQMLiteWQAssoc	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION_F3_WIDTH                                         32
#define REGSPEC_ASSOCIATION_F3_SHIFT                                          0
#define REGSPEC_ASSOCIATION_F3_MASK                                  0xffffffff
#define REGSPEC_ASSOCIATION_F3_RD(src)                   (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION_F3_WR(src)              (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiQMHold	*/ 
/*	 Fields QMLite_hold_en	 */
#define REGSPEC_QMLITE_HOLD_EN_WIDTH                                          1
#define REGSPEC_QMLITE_HOLD_EN_SHIFT                                         31
#define REGSPEC_QMLITE_HOLD_EN_MASK                                  0x80000000
#define REGSPEC_QMLITE_HOLD_EN_RD(src)               (((src) & 0x80000000)>>31)
#define REGSPEC_QMLITE_HOLD_EN_WR(src)          (((u32)(src)<<31) & 0x80000000)
#define REGSPEC_QMLITE_HOLD_EN_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields QM2_hold_en	 */
#define REGSPEC_QM2_HOLD_EN_WIDTH                                             1
#define REGSPEC_QM2_HOLD_EN_SHIFT                                             2
#define REGSPEC_QM2_HOLD_EN_MASK                                     0x00000004
#define REGSPEC_QM2_HOLD_EN_RD(src)                   (((src) & 0x00000004)>>2)
#define REGSPEC_QM2_HOLD_EN_WR(src)              (((u32)(src)<<2) & 0x00000004)
#define REGSPEC_QM2_HOLD_EN_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields QM1_hold_en	 */
#define REGSPEC_QM1_HOLD_EN_WIDTH                                             1
#define REGSPEC_QM1_HOLD_EN_SHIFT                                             1
#define REGSPEC_QM1_HOLD_EN_MASK                                     0x00000002
#define REGSPEC_QM1_HOLD_EN_RD(src)                   (((src) & 0x00000002)>>1)
#define REGSPEC_QM1_HOLD_EN_WR(src)              (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_QM1_HOLD_EN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields QM0_hold_en	 */
#define REGSPEC_QM0_HOLD_EN_WIDTH                                             1
#define REGSPEC_QM0_HOLD_EN_SHIFT                                             0
#define REGSPEC_QM0_HOLD_EN_MASK                                     0x00000001
#define REGSPEC_QM0_HOLD_EN_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_QM0_HOLD_EN_WR(src)                 (((u32)(src)) & 0x00000001)
#define REGSPEC_QM0_HOLD_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register StsSsQmiQMHold	*/ 
/*	 Fields QMLite_hold	 */
#define REGSPEC_QMLITE_HOLD_WIDTH                                             1
#define REGSPEC_QMLITE_HOLD_SHIFT                                            31
#define REGSPEC_QMLITE_HOLD_MASK                                     0x80000000
#define REGSPEC_QMLITE_HOLD_RD(src)                  (((src) & 0x80000000)>>31)
#define REGSPEC_QMLITE_HOLD_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields QM2_hold	 */
#define REGSPEC_QM2_HOLD_WIDTH                                                1
#define REGSPEC_QM2_HOLD_SHIFT                                                2
#define REGSPEC_QM2_HOLD_MASK                                        0x00000004
#define REGSPEC_QM2_HOLD_RD(src)                      (((src) & 0x00000004)>>2)
#define REGSPEC_QM2_HOLD_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields QM1_hold	 */
#define REGSPEC_QM1_HOLD_WIDTH                                                1
#define REGSPEC_QM1_HOLD_SHIFT                                                1
#define REGSPEC_QM1_HOLD_MASK                                        0x00000002
#define REGSPEC_QM1_HOLD_RD(src)                      (((src) & 0x00000002)>>1)
#define REGSPEC_QM1_HOLD_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields QM0_hold	 */
#define REGSPEC_QM0_HOLD_WIDTH                                                1
#define REGSPEC_QM0_HOLD_SHIFT                                                0
#define REGSPEC_QM0_HOLD_MASK                                        0x00000001
#define REGSPEC_QM0_HOLD_RD(src)                         (((src) & 0x00000001))
#define REGSPEC_QM0_HOLD_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CfgSsQmiFPQVCAssoc0	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION0_WIDTH                                           32
#define REGSPEC_ASSOCIATION0_SHIFT                                            0
#define REGSPEC_ASSOCIATION0_MASK                                    0xffffffff
#define REGSPEC_ASSOCIATION0_RD(src)                     (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION0_WR(src)                (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiFPQVCAssoc1	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION1_WIDTH                                           32
#define REGSPEC_ASSOCIATION1_SHIFT                                            0
#define REGSPEC_ASSOCIATION1_MASK                                    0xffffffff
#define REGSPEC_ASSOCIATION1_RD(src)                     (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION1_WR(src)                (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiWQVCAssoc0	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION0_F1_WIDTH                                        32
#define REGSPEC_ASSOCIATION0_F1_SHIFT                                         0
#define REGSPEC_ASSOCIATION0_F1_MASK                                 0xffffffff
#define REGSPEC_ASSOCIATION0_F1_RD(src)                  (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION0_F1_WR(src)             (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiWQVCAssoc1	*/ 
/*	 Fields Association	 */
#define REGSPEC_ASSOCIATION1_F1_WIDTH                                        32
#define REGSPEC_ASSOCIATION1_F1_SHIFT                                         0
#define REGSPEC_ASSOCIATION1_F1_MASK                                 0xffffffff
#define REGSPEC_ASSOCIATION1_F1_RD(src)                  (((src) & 0xffffffff))
#define REGSPEC_ASSOCIATION1_F1_WR(src)             (((u32)(src)) & 0xffffffff)
#define REGSPEC_ASSOCIATION1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CfgSsQmiQM2	*/ 
/*	 Fields Address	 */
#define REGSPEC_ADDRESS2_WIDTH                                               20
#define REGSPEC_ADDRESS2_SHIFT                                                0
#define REGSPEC_ADDRESS2_MASK                                        0x000fffff
#define REGSPEC_ADDRESS2_RD(src)                         (((src) & 0x000fffff))
#define REGSPEC_ADDRESS2_WR(src)                    (((u32)(src)) & 0x000fffff)
#define REGSPEC_ADDRESS2_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Global Base Address	*/
#define RTC_I_BASE_ADDR			0x050010000ULL

/*    Address RTC_I  Registers */
#define RTC_CCVR_ADDR                                                0x00000000
#define RTC_CCVR_DEFAULT                                             0x00000000
#define RTC_CMR_ADDR                                                 0x00000004
#define RTC_CMR_DEFAULT                                              0x00000000
#define RTC_CLR_ADDR                                                 0x00000008
#define RTC_CLR_DEFAULT                                              0x00000000
#define RTC_CCR_ADDR                                                 0x0000000c
#define RTC_CCR_DEFAULT                                              0x00000000
#define RTC_STAT_ADDR                                                0x00000010
#define RTC_STAT_DEFAULT                                             0x00000000
#define RTC_RSTAT_ADDR                                               0x00000014
#define RTC_RSTAT_DEFAULT                                            0x00000000
#define RTC_EOI_ADDR                                                 0x00000018
#define RTC_EOI_DEFAULT                                              0x00000000
#define RTC_COMP_VER_ADDR                                            0x0000001c
#define RTC_COMP_VER_DEFAULT                                         0x3230322a

/*	Register RTC_CCVR	*/ 
/*	 Fields CCVR	 */
#define CCVR_WIDTH                                                           32
#define CCVR_SHIFT                                                            0
#define CCVR_MASK                                                    0xffffffff
#define CCVR_RD(src)                                     (((src) & 0xffffffff))
#define CCVR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register RTC_CMR	*/ 
/*	 Fields CMR	 */
#define CMR_WIDTH                                                            32
#define CMR_SHIFT                                                             0
#define CMR_MASK                                                     0xffffffff
#define CMR_RD(src)                                      (((src) & 0xffffffff))
#define CMR_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define CMR_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register RTC_CLR	*/ 
/*	 Fields CLR	 */
#define CLR_WIDTH                                                            32
#define CLR_SHIFT                                                             0
#define CLR_MASK                                                     0xffffffff
#define CLR_RD(src)                                      (((src) & 0xffffffff))
#define CLR_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define CLR_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register RTC_CCR	*/ 
/*	 Fields RTC_WEN	 */
#define RTC_WEN_WIDTH                                                         1
#define RTC_WEN_SHIFT                                                         3
#define RTC_WEN_MASK                                                 0x00000008
#define RTC_WEN_RD(src)                               (((src) & 0x00000008)>>3)
#define RTC_WEN_WR(src)                          (((u32)(src)<<3) & 0x00000008)
#define RTC_WEN_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields RTC_EN	 */
#define RTC_EN_WIDTH                                                          1
#define RTC_EN_SHIFT                                                          2
#define RTC_EN_MASK                                                  0x00000004
#define RTC_EN_RD(src)                                (((src) & 0x00000004)>>2)
#define RTC_EN_WR(src)                           (((u32)(src)<<2) & 0x00000004)
#define RTC_EN_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields RTC_MASK	 */
#define RTC_MASK_WIDTH                                                        1
#define RTC_MASK_SHIFT                                                        1
#define RTC_MASK_MASK                                                0x00000002
#define RTC_MASK_RD(src)                              (((src) & 0x00000002)>>1)
#define RTC_MASK_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define RTC_MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields RTC_IEN	 */
#define RTC_IEN_WIDTH                                                         1
#define RTC_IEN_SHIFT                                                         0
#define RTC_IEN_MASK                                                 0x00000001
#define RTC_IEN_RD(src)                                  (((src) & 0x00000001))
#define RTC_IEN_WR(src)                             (((u32)(src)) & 0x00000001)
#define RTC_IEN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RTC_STAT	*/ 
/*	 Fields STAT	 */
#define STAT_WIDTH                                                            1
#define STAT_SHIFT                                                            0
#define STAT_MASK                                                    0x00000001
#define STAT_RD(src)                                     (((src) & 0x00000001))
#define STAT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RTC_RSTAT	*/ 
/*	 Fields RSTAT	 */
#define RSTAT_WIDTH                                                           1
#define RSTAT_SHIFT                                                           0
#define RSTAT_MASK                                                   0x00000001
#define RSTAT_RD(src)                                    (((src) & 0x00000001))
#define RSTAT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RTC_EOI	*/ 
/*	 Fields EOI	 */
#define EOI_WIDTH                                                             1
#define EOI_SHIFT                                                             0
#define EOI_MASK                                                     0x00000001
#define EOI_RD(src)                                      (((src) & 0x00000001))
#define EOI_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register RTC_COMP_VER	*/ 

/*	Global Base Address	*/
#define MPA_IIC0_I_BASE_ADDR			0x050012000ULL
#define MPA_IIC1_I_BASE_ADDR			0x050011000ULL

/*    Address MPA_IIC1_I  Registers */
#define REGSPEC_I2C_CON_ADDR                                         0x00000000
#define REGSPEC_I2C_CON_DEFAULT                                      0x00000045
#define REGSPEC_I2C_TAR_ADDR                                         0x00000004
#define REGSPEC_I2C_TAR_DEFAULT                                      0x00000056
#define REGSPEC_I2C_SAR_ADDR                                         0x00000008
#define REGSPEC_I2C_SAR_DEFAULT                                      0x00000055
#define REGSPEC_I2C_HS_MADDR_ADDR                                    0x0000000c
#define REGSPEC_I2C_HS_MADDR_DEFAULT                                 0x00000001
#define REGSPEC_I2C_DATA_CMD_ADDR                                    0x00000010
#define REGSPEC_I2C_DATA_CMD_DEFAULT                                 0x00000000
#define REGSPEC_I2C_SS_SCL_HCNT_ADDR                                 0x00000014
#define REGSPEC_I2C_SS_SCL_HCNT_DEFAULT                              0x00000190
#define REGSPEC_I2C_SS_SCL_LCNT_ADDR                                 0x00000018
#define REGSPEC_I2C_SS_SCL_LCNT_DEFAULT                              0x000001d6
#define REGSPEC_I2C_FS_SCL_HCNT_ADDR                                 0x0000001c
#define REGSPEC_I2C_FS_SCL_HCNT_DEFAULT                              0x0000003c
#define REGSPEC_I2C_FS_SCL_LCNT_ADDR                                 0x00000020
#define REGSPEC_I2C_FS_SCL_LCNT_DEFAULT                              0x00000082
#define REGSPEC_I2C_HS_SCL_HCNT_ADDR                                 0x00000024
#define REGSPEC_I2C_HS_SCL_HCNT_DEFAULT                              0x00000006
#define REGSPEC_I2C_HS_SCL_LCNT_ADDR                                 0x00000028
#define REGSPEC_I2C_HS_SCL_LCNT_DEFAULT                              0x00000010
#define REGSPEC_I2C_INTR_STAT_ADDR                                   0x0000002c
#define REGSPEC_I2C_INTR_STAT_DEFAULT                                0x00000000
#define REGSPEC_I2C_INTR_MASK_ADDR                                   0x00000030
#define REGSPEC_I2C_INTR_MASK_DEFAULT                                0x00000000
#define REGSPEC_I2C_RAW_INTR_STAT_ADDR                               0x00000034
#define REGSPEC_I2C_RAW_INTR_STAT_DEFAULT                            0x00000000
#define REGSPEC_I2C_RX_TL_ADDR                                       0x00000038
#define REGSPEC_I2C_RX_TL_DEFAULT                                    0x00000000
#define REGSPEC_I2C_TX_TL_ADDR                                       0x0000003c
#define REGSPEC_I2C_TX_TL_DEFAULT                                    0x00000000
#define REGSPEC_I2C_CLR_INTR_ADDR                                    0x00000040
#define REGSPEC_I2C_CLR_INTR_DEFAULT                                 0x00000000
#define REGSPEC_I2C_CLR_RX_UNDER_ADDR                                0x00000044
#define REGSPEC_I2C_CLR_RX_UNDER_DEFAULT                             0x00000000
#define REGSPEC_I2C_CLR_RX_OVER_ADDR                                 0x00000048
#define REGSPEC_I2C_CLR_RX_OVER_DEFAULT                              0x00000000
#define REGSPEC_I2C_CLR_TX_OVER_ADDR                                 0x0000004c
#define REGSPEC_I2C_CLR_TX_OVER_DEFAULT                              0x00000000
#define REGSPEC_I2C_CLR_RD_REQ_ADDR                                  0x00000050
#define REGSPEC_I2C_CLR_RD_REQ_DEFAULT                               0x00000000
#define REGSPEC_I2C_CLR_TX_ABRT_ADDR                                 0x00000054
#define REGSPEC_I2C_CLR_TX_ABRT_DEFAULT                              0x00000000
#define REGSPEC_I2C_CLR_RX_DONE_ADDR                                 0x00000058
#define REGSPEC_I2C_CLR_RX_DONE_DEFAULT                              0x00000000
#define REGSPEC_I2C_CLR_ACTIVITY_ADDR                                0x0000005c
#define REGSPEC_I2C_CLR_ACTIVITY_DEFAULT                             0x00000000
#define REGSPEC_I2C_CLR_STOP_DET_ADDR                                0x00000060
#define REGSPEC_I2C_CLR_STOP_DET_DEFAULT                             0x00000000
#define REGSPEC_I2C_CLR_START_DET_ADDR                               0x00000064
#define REGSPEC_I2C_CLR_START_DET_DEFAULT                            0x00000000
#define REGSPEC_I2C_CLR_GEN_CALL_ADDR                                0x00000068
#define REGSPEC_I2C_CLR_GEN_CALL_DEFAULT                             0x00000000
#define REGSPEC_I2C_ENABLE_ADDR                                      0x0000006c
#define REGSPEC_I2C_ENABLE_DEFAULT                                   0x00000000
#define REGSPEC_I2C_STATUS_ADDR                                      0x00000070
#define REGSPEC_I2C_STATUS_DEFAULT                                   0x00000006
#define REGSPEC_I2C_TXFLR_ADDR                                       0x00000074
#define REGSPEC_I2C_TXFLR_DEFAULT                                    0x00000000
#define REGSPEC_I2C_RXFLR_ADDR                                       0x00000078
#define REGSPEC_I2C_RXFLR_DEFAULT                                    0x00000000
#define REGSPEC_I2C_TX_ABRT_SOURCE_ADDR                              0x00000080
#define REGSPEC_I2C_TX_ABRT_SOURCE_DEFAULT                           0x00000000
#define REGSPEC_I2C_SLV_DATA_NACK_ONLY_ADDR                          0x00000084
#define REGSPEC_I2C_SLV_DATA_NACK_ONLY_DEFAULT                       0x00000000
#define REGSPEC_I2C_SDA_SETUP_ADDR                                   0x00000094
#define REGSPEC_I2C_SDA_SETUP_DEFAULT                                0x00000064
#define REGSPEC_I2C_ACK_GENERAL_CALL_ADDR                            0x00000098
#define REGSPEC_I2C_ACK_GENERAL_CALL_DEFAULT                         0x00000001
#define REGSPEC_I2C_ENABLE_STATUS_ADDR                               0x0000009c
#define REGSPEC_I2C_ENABLE_STATUS_DEFAULT                            0x00000000
#define REGSPEC_I2C_COMP_PARAM_1_ADDR                                0x000000f4
#define REGSPEC_I2C_COMP_PARAM_1_DEFAULT                             0x000303aa
#define REGSPEC_I2C_COMP_VERSION_ADDR                                0x000000f8
#define REGSPEC_I2C_COMP_VERSION_DEFAULT                             0x00000000
#define REGSPEC_I2C_COMP_TYPE_ADDR                                   0x000000fc
#define REGSPEC_I2C_COMP_TYPE_DEFAULT                                0x44570140

/*	Register I2C_CON	*/ 
/*	 Fields IC_SALVE_DISABLE	 */
#define REGSPEC_IC_SALVE_DISABLE_WIDTH                                        1
#define REGSPEC_IC_SALVE_DISABLE_SHIFT                                        6
#define REGSPEC_IC_SALVE_DISABLE_MASK                                0x00000040
#define REGSPEC_IC_SALVE_DISABLE_RD(src)              (((src) & 0x00000040)>>6)
#define REGSPEC_IC_SALVE_DISABLE_WR(src)         (((u32)(src)<<6) & 0x00000040)
#define REGSPEC_IC_SALVE_DISABLE_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields IC_RESTART_EN	 */
#define REGSPEC_IC_RESTART_EN_WIDTH                                           1
#define REGSPEC_IC_RESTART_EN_SHIFT                                           5
#define REGSPEC_IC_RESTART_EN_MASK                                   0x00000020
#define REGSPEC_IC_RESTART_EN_RD(src)                 (((src) & 0x00000020)>>5)
#define REGSPEC_IC_RESTART_EN_WR(src)            (((u32)(src)<<5) & 0x00000020)
#define REGSPEC_IC_RESTART_EN_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields IC_10BITADDR_MASTER	 */
#define REGSPEC_IC_10BITADDR_MASTER_WIDTH                                     1
#define REGSPEC_IC_10BITADDR_MASTER_SHIFT                                     4
#define REGSPEC_IC_10BITADDR_MASTER_MASK                             0x00000010
#define REGSPEC_IC_10BITADDR_MASTER_RD(src)           (((src) & 0x00000010)>>4)
#define REGSPEC_IC_10BITADDR_MASTER_WR(src)      (((u32)(src)<<4) & 0x00000010)
#define REGSPEC_IC_10BITADDR_MASTER_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields IC_10BITADDR_SLAVE	 */
#define REGSPEC_IC_10BITADDR_SLAVE_WIDTH                                      1
#define REGSPEC_IC_10BITADDR_SLAVE_SHIFT                                      3
#define REGSPEC_IC_10BITADDR_SLAVE_MASK                              0x00000008
#define REGSPEC_IC_10BITADDR_SLAVE_RD(src)            (((src) & 0x00000008)>>3)
#define REGSPEC_IC_10BITADDR_SLAVE_WR(src)       (((u32)(src)<<3) & 0x00000008)
#define REGSPEC_IC_10BITADDR_SLAVE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields IC_MAX_SPEED_MODE	 */
#define REGSPEC_IC_MAX_SPEED_MODE_WIDTH                                       2
#define REGSPEC_IC_MAX_SPEED_MODE_SHIFT                                       1
#define REGSPEC_IC_MAX_SPEED_MODE_MASK                               0x00000006
#define REGSPEC_IC_MAX_SPEED_MODE_RD(src)             (((src) & 0x00000006)>>1)
#define REGSPEC_IC_MAX_SPEED_MODE_WR(src)        (((u32)(src)<<1) & 0x00000006)
#define REGSPEC_IC_MAX_SPEED_MODE_SET(dst,src) \
                       (((dst) & ~0x00000006) | (((u32)(src)<<1) & 0x00000006))
/*	 Fields IC_MASTER_MODE	 */
#define REGSPEC_IC_MASTER_MODE_WIDTH                                          1
#define REGSPEC_IC_MASTER_MODE_SHIFT                                          0
#define REGSPEC_IC_MASTER_MODE_MASK                                  0x00000001
#define REGSPEC_IC_MASTER_MODE_RD(src)                   (((src) & 0x00000001))
#define REGSPEC_IC_MASTER_MODE_WR(src)              (((u32)(src)) & 0x00000001)
#define REGSPEC_IC_MASTER_MODE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_TAR	*/ 
/*	 Fields SPECIAL	 */
#define REGSPEC_SPECIAL_WIDTH                                                 1
#define REGSPEC_SPECIAL_SHIFT                                                11
#define REGSPEC_SPECIAL_MASK                                         0x00000800
#define REGSPEC_SPECIAL_RD(src)                      (((src) & 0x00000800)>>11)
#define REGSPEC_SPECIAL_WR(src)                 (((u32)(src)<<11) & 0x00000800)
#define REGSPEC_SPECIAL_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields GC_OR_START	 */
#define REGSPEC_GC_OR_START_WIDTH                                             1
#define REGSPEC_GC_OR_START_SHIFT                                            10
#define REGSPEC_GC_OR_START_MASK                                     0x00000400
#define REGSPEC_GC_OR_START_RD(src)                  (((src) & 0x00000400)>>10)
#define REGSPEC_GC_OR_START_WR(src)             (((u32)(src)<<10) & 0x00000400)
#define REGSPEC_GC_OR_START_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields IC_TAR	 */
#define REGSPEC_IC_TAR_WIDTH                                                 10
#define REGSPEC_IC_TAR_SHIFT                                                  0
#define REGSPEC_IC_TAR_MASK                                          0x000003ff
#define REGSPEC_IC_TAR_RD(src)                           (((src) & 0x000003ff))
#define REGSPEC_IC_TAR_WR(src)                      (((u32)(src)) & 0x000003ff)
#define REGSPEC_IC_TAR_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register I2C_SAR	*/ 
/*	 Fields I2C_SAR	 */
#define REGSPEC_I2C_SAR_WIDTH                                                10
#define REGSPEC_I2C_SAR_SHIFT                                                 0
#define REGSPEC_I2C_SAR_MASK                                         0x000003ff
#define REGSPEC_I2C_SAR_RD(src)                          (((src) & 0x000003ff))
#define REGSPEC_I2C_SAR_WR(src)                     (((u32)(src)) & 0x000003ff)
#define REGSPEC_I2C_SAR_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register I2C_HS_MADDR	*/ 
/*	 Fields I2C_HS_MADDR	 */
#define REGSPEC_I2C_HS_MADDR_WIDTH                                            3
#define REGSPEC_I2C_HS_MADDR_SHIFT                                            0
#define REGSPEC_I2C_HS_MADDR_MASK                                    0x00000007
#define REGSPEC_I2C_HS_MADDR_RD(src)                     (((src) & 0x00000007))
#define REGSPEC_I2C_HS_MADDR_WR(src)                (((u32)(src)) & 0x00000007)
#define REGSPEC_I2C_HS_MADDR_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register I2C_DATA_CMD	*/ 
/*	 Fields CMD	 */
#define REGSPEC_CMD_WIDTH                                                     1
#define REGSPEC_CMD_SHIFT                                                     8
#define REGSPEC_CMD_MASK                                             0x00000100
#define REGSPEC_CMD_RD(src)                           (((src) & 0x00000100)>>8)
#define REGSPEC_CMD_WR(src)                      (((u32)(src)<<8) & 0x00000100)
#define REGSPEC_CMD_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields DAT	 */
#define REGSPEC_DAT_WIDTH                                                     8
#define REGSPEC_DAT_SHIFT                                                     0
#define REGSPEC_DAT_MASK                                             0x000000ff
#define REGSPEC_DAT_RD(src)                              (((src) & 0x000000ff))
#define REGSPEC_DAT_WR(src)                         (((u32)(src)) & 0x000000ff)
#define REGSPEC_DAT_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register I2C_SS_SCL_HCNT	*/ 
/*	 Fields I2C_SS_SCL_HCNT	 */
#define REGSPEC_I2C_SS_SCL_HCNT_WIDTH                                        16
#define REGSPEC_I2C_SS_SCL_HCNT_SHIFT                                         0
#define REGSPEC_I2C_SS_SCL_HCNT_MASK                                 0x0000ffff
#define REGSPEC_I2C_SS_SCL_HCNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_I2C_SS_SCL_HCNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_I2C_SS_SCL_HCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_SS_SCL_LCNT	*/ 
/*	 Fields I2C_SS_SCL_LCNT	 */
#define REGSPEC_I2C_SS_SCL_LCNT_WIDTH                                        16
#define REGSPEC_I2C_SS_SCL_LCNT_SHIFT                                         0
#define REGSPEC_I2C_SS_SCL_LCNT_MASK                                 0x0000ffff
#define REGSPEC_I2C_SS_SCL_LCNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_I2C_SS_SCL_LCNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_I2C_SS_SCL_LCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_FS_SCL_HCNT	*/ 
/*	 Fields I2C_FS_SCL_HCNT	 */
#define REGSPEC_I2C_FS_SCL_HCNT_WIDTH                                        16
#define REGSPEC_I2C_FS_SCL_HCNT_SHIFT                                         0
#define REGSPEC_I2C_FS_SCL_HCNT_MASK                                 0x0000ffff
#define REGSPEC_I2C_FS_SCL_HCNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_I2C_FS_SCL_HCNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_I2C_FS_SCL_HCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_FS_SCL_LCNT	*/ 
/*	 Fields I2C_FS_SCL_LCNT	 */
#define REGSPEC_I2C_FS_SCL_LCNT_WIDTH                                        16
#define REGSPEC_I2C_FS_SCL_LCNT_SHIFT                                         0
#define REGSPEC_I2C_FS_SCL_LCNT_MASK                                 0x0000ffff
#define REGSPEC_I2C_FS_SCL_LCNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_I2C_FS_SCL_LCNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_I2C_FS_SCL_LCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_HS_SCL_HCNT	*/ 
/*	 Fields I2C_HS_SCL_HCNT	 */
#define REGSPEC_I2C_HS_SCL_HCNT_WIDTH                                        16
#define REGSPEC_I2C_HS_SCL_HCNT_SHIFT                                         0
#define REGSPEC_I2C_HS_SCL_HCNT_MASK                                 0x0000ffff
#define REGSPEC_I2C_HS_SCL_HCNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_I2C_HS_SCL_HCNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_I2C_HS_SCL_HCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_HS_SCL_LCNT	*/ 
/*	 Fields I2C_HS_SCL_LCNT	 */
#define REGSPEC_I2C_HS_SCL_LCNT_WIDTH                                        16
#define REGSPEC_I2C_HS_SCL_LCNT_SHIFT                                         0
#define REGSPEC_I2C_HS_SCL_LCNT_MASK                                 0x0000ffff
#define REGSPEC_I2C_HS_SCL_LCNT_RD(src)                  (((src) & 0x0000ffff))
#define REGSPEC_I2C_HS_SCL_LCNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define REGSPEC_I2C_HS_SCL_LCNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register I2C_INTR_STAT	*/ 
/*	 Fields R_GEN_CALL	 */
#define REGSPEC_R_GEN_CALL_WIDTH                                              1
#define REGSPEC_R_GEN_CALL_SHIFT                                             11
#define REGSPEC_R_GEN_CALL_MASK                                      0x00000800
#define REGSPEC_R_GEN_CALL_RD(src)                   (((src) & 0x00000800)>>11)
#define REGSPEC_R_GEN_CALL_WR(src)              (((u32)(src)<<11) & 0x00000800)
#define REGSPEC_R_GEN_CALL_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields R_START_DET	 */
#define REGSPEC_R_START_DET_WIDTH                                             1
#define REGSPEC_R_START_DET_SHIFT                                            10
#define REGSPEC_R_START_DET_MASK                                     0x00000400
#define REGSPEC_R_START_DET_RD(src)                  (((src) & 0x00000400)>>10)
#define REGSPEC_R_START_DET_WR(src)             (((u32)(src)<<10) & 0x00000400)
#define REGSPEC_R_START_DET_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields R_STOP_DET	 */
#define REGSPEC_R_STOP_DET_WIDTH                                              1
#define REGSPEC_R_STOP_DET_SHIFT                                              9
#define REGSPEC_R_STOP_DET_MASK                                      0x00000200
#define REGSPEC_R_STOP_DET_RD(src)                    (((src) & 0x00000200)>>9)
#define REGSPEC_R_STOP_DET_WR(src)               (((u32)(src)<<9) & 0x00000200)
#define REGSPEC_R_STOP_DET_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields R_ACTIVITY	 */
#define REGSPEC_R_ACTIVITY_WIDTH                                              1
#define REGSPEC_R_ACTIVITY_SHIFT                                              8
#define REGSPEC_R_ACTIVITY_MASK                                      0x00000100
#define REGSPEC_R_ACTIVITY_RD(src)                    (((src) & 0x00000100)>>8)
#define REGSPEC_R_ACTIVITY_WR(src)               (((u32)(src)<<8) & 0x00000100)
#define REGSPEC_R_ACTIVITY_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields R_RX_DONE	 */
#define REGSPEC_R_RX_DONE_WIDTH                                               1
#define REGSPEC_R_RX_DONE_SHIFT                                               7
#define REGSPEC_R_RX_DONE_MASK                                       0x00000080
#define REGSPEC_R_RX_DONE_RD(src)                     (((src) & 0x00000080)>>7)
#define REGSPEC_R_RX_DONE_WR(src)                (((u32)(src)<<7) & 0x00000080)
#define REGSPEC_R_RX_DONE_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields R_TX_ABRT	 */
#define REGSPEC_R_TX_ABRT_WIDTH                                               1
#define REGSPEC_R_TX_ABRT_SHIFT                                               6
#define REGSPEC_R_TX_ABRT_MASK                                       0x00000040
#define REGSPEC_R_TX_ABRT_RD(src)                     (((src) & 0x00000040)>>6)
#define REGSPEC_R_TX_ABRT_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define REGSPEC_R_TX_ABRT_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields R_RD_REQ	 */
#define REGSPEC_R_RD_REQ_WIDTH                                                1
#define REGSPEC_R_RD_REQ_SHIFT                                                5
#define REGSPEC_R_RD_REQ_MASK                                        0x00000020
#define REGSPEC_R_RD_REQ_RD(src)                      (((src) & 0x00000020)>>5)
#define REGSPEC_R_RD_REQ_WR(src)                 (((u32)(src)<<5) & 0x00000020)
#define REGSPEC_R_RD_REQ_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields R_TX_EMPTY	 */
#define REGSPEC_R_TX_EMPTY_WIDTH                                              1
#define REGSPEC_R_TX_EMPTY_SHIFT                                              4
#define REGSPEC_R_TX_EMPTY_MASK                                      0x00000010
#define REGSPEC_R_TX_EMPTY_RD(src)                    (((src) & 0x00000010)>>4)
#define REGSPEC_R_TX_EMPTY_WR(src)               (((u32)(src)<<4) & 0x00000010)
#define REGSPEC_R_TX_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields R_TX_OVER	 */
#define REGSPEC_R_TX_OVER_WIDTH                                               1
#define REGSPEC_R_TX_OVER_SHIFT                                               3
#define REGSPEC_R_TX_OVER_MASK                                       0x00000008
#define REGSPEC_R_TX_OVER_RD(src)                     (((src) & 0x00000008)>>3)
#define REGSPEC_R_TX_OVER_WR(src)                (((u32)(src)<<3) & 0x00000008)
#define REGSPEC_R_TX_OVER_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields R_RX_FULL	 */
#define REGSPEC_R_RX_FULL_WIDTH                                               1
#define REGSPEC_R_RX_FULL_SHIFT                                               2
#define REGSPEC_R_RX_FULL_MASK                                       0x00000004
#define REGSPEC_R_RX_FULL_RD(src)                     (((src) & 0x00000004)>>2)
#define REGSPEC_R_RX_FULL_WR(src)                (((u32)(src)<<2) & 0x00000004)
#define REGSPEC_R_RX_FULL_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields R_RX_OVER	 */
#define REGSPEC_R_RX_OVER_WIDTH                                               1
#define REGSPEC_R_RX_OVER_SHIFT                                               1
#define REGSPEC_R_RX_OVER_MASK                                       0x00000002
#define REGSPEC_R_RX_OVER_RD(src)                     (((src) & 0x00000002)>>1)
#define REGSPEC_R_RX_OVER_WR(src)                (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_R_RX_OVER_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields R_RX_UNDER	 */
#define REGSPEC_R_RX_UNDER_WIDTH                                              1
#define REGSPEC_R_RX_UNDER_SHIFT                                              0
#define REGSPEC_R_RX_UNDER_MASK                                      0x00000001
#define REGSPEC_R_RX_UNDER_RD(src)                       (((src) & 0x00000001))
#define REGSPEC_R_RX_UNDER_WR(src)                  (((u32)(src)) & 0x00000001)
#define REGSPEC_R_RX_UNDER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_INTR_MASK	*/ 
/*	 Fields M_GEN_CALL	 */
#define REGSPEC_M_GEN_CALL_WIDTH                                              1
#define REGSPEC_M_GEN_CALL_SHIFT                                             11
#define REGSPEC_M_GEN_CALL_MASK                                      0x00000800
#define REGSPEC_M_GEN_CALL_RD(src)                   (((src) & 0x00000800)>>11)
#define REGSPEC_M_GEN_CALL_WR(src)              (((u32)(src)<<11) & 0x00000800)
#define REGSPEC_M_GEN_CALL_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields M_START_DET	 */
#define REGSPEC_M_START_DET_WIDTH                                             1
#define REGSPEC_M_START_DET_SHIFT                                            10
#define REGSPEC_M_START_DET_MASK                                     0x00000400
#define REGSPEC_M_START_DET_RD(src)                  (((src) & 0x00000400)>>10)
#define REGSPEC_M_START_DET_WR(src)             (((u32)(src)<<10) & 0x00000400)
#define REGSPEC_M_START_DET_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields M_STOP_DET	 */
#define REGSPEC_M_STOP_DET_WIDTH                                              1
#define REGSPEC_M_STOP_DET_SHIFT                                              9
#define REGSPEC_M_STOP_DET_MASK                                      0x00000200
#define REGSPEC_M_STOP_DET_RD(src)                    (((src) & 0x00000200)>>9)
#define REGSPEC_M_STOP_DET_WR(src)               (((u32)(src)<<9) & 0x00000200)
#define REGSPEC_M_STOP_DET_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields M_ACTIVITY	 */
#define REGSPEC_M_ACTIVITY_WIDTH                                              1
#define REGSPEC_M_ACTIVITY_SHIFT                                              8
#define REGSPEC_M_ACTIVITY_MASK                                      0x00000100
#define REGSPEC_M_ACTIVITY_RD(src)                    (((src) & 0x00000100)>>8)
#define REGSPEC_M_ACTIVITY_WR(src)               (((u32)(src)<<8) & 0x00000100)
#define REGSPEC_M_ACTIVITY_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields M_RX_DONE	 */
#define REGSPEC_M_RX_DONE_WIDTH                                               1
#define REGSPEC_M_RX_DONE_SHIFT                                               7
#define REGSPEC_M_RX_DONE_MASK                                       0x00000080
#define REGSPEC_M_RX_DONE_RD(src)                     (((src) & 0x00000080)>>7)
#define REGSPEC_M_RX_DONE_WR(src)                (((u32)(src)<<7) & 0x00000080)
#define REGSPEC_M_RX_DONE_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields M_TX_ABRT	 */
#define REGSPEC_M_TX_ABRT_WIDTH                                               1
#define REGSPEC_M_TX_ABRT_SHIFT                                               6
#define REGSPEC_M_TX_ABRT_MASK                                       0x00000040
#define REGSPEC_M_TX_ABRT_RD(src)                     (((src) & 0x00000040)>>6)
#define REGSPEC_M_TX_ABRT_WR(src)                (((u32)(src)<<6) & 0x00000040)
#define REGSPEC_M_TX_ABRT_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields M_RD_REQ	 */
#define REGSPEC_M_RD_REQ_WIDTH                                                1
#define REGSPEC_M_RD_REQ_SHIFT                                                5
#define REGSPEC_M_RD_REQ_MASK                                        0x00000020
#define REGSPEC_M_RD_REQ_RD(src)                      (((src) & 0x00000020)>>5)
#define REGSPEC_M_RD_REQ_WR(src)                 (((u32)(src)<<5) & 0x00000020)
#define REGSPEC_M_RD_REQ_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields M_TX_EMPTY	 */
#define REGSPEC_M_TX_EMPTY_WIDTH                                              1
#define REGSPEC_M_TX_EMPTY_SHIFT                                              4
#define REGSPEC_M_TX_EMPTY_MASK                                      0x00000010
#define REGSPEC_M_TX_EMPTY_RD(src)                    (((src) & 0x00000010)>>4)
#define REGSPEC_M_TX_EMPTY_WR(src)               (((u32)(src)<<4) & 0x00000010)
#define REGSPEC_M_TX_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields M_TX_OVER	 */
#define REGSPEC_M_TX_OVER_WIDTH                                               1
#define REGSPEC_M_TX_OVER_SHIFT                                               3
#define REGSPEC_M_TX_OVER_MASK                                       0x00000008
#define REGSPEC_M_TX_OVER_RD(src)                     (((src) & 0x00000008)>>3)
#define REGSPEC_M_TX_OVER_WR(src)                (((u32)(src)<<3) & 0x00000008)
#define REGSPEC_M_TX_OVER_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields M_RX_FULL	 */
#define REGSPEC_M_RX_FULL_WIDTH                                               1
#define REGSPEC_M_RX_FULL_SHIFT                                               2
#define REGSPEC_M_RX_FULL_MASK                                       0x00000004
#define REGSPEC_M_RX_FULL_RD(src)                     (((src) & 0x00000004)>>2)
#define REGSPEC_M_RX_FULL_WR(src)                (((u32)(src)<<2) & 0x00000004)
#define REGSPEC_M_RX_FULL_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields M_RX_OVER	 */
#define REGSPEC_M_RX_OVER_WIDTH                                               1
#define REGSPEC_M_RX_OVER_SHIFT                                               1
#define REGSPEC_M_RX_OVER_MASK                                       0x00000002
#define REGSPEC_M_RX_OVER_RD(src)                     (((src) & 0x00000002)>>1)
#define REGSPEC_M_RX_OVER_WR(src)                (((u32)(src)<<1) & 0x00000002)
#define REGSPEC_M_RX_OVER_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields M_RX_UNDER	 */
#define REGSPEC_M_RX_UNDER_WIDTH                                              1
#define REGSPEC_M_RX_UNDER_SHIFT                                              0
#define REGSPEC_M_RX_UNDER_MASK                                      0x00000001
#define REGSPEC_M_RX_UNDER_RD(src)                       (((src) & 0x00000001))
#define REGSPEC_M_RX_UNDER_WR(src)                  (((u32)(src)) & 0x00000001)
#define REGSPEC_M_RX_UNDER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_RAW_INTR_STAT	*/ 
/*	 Fields GEN_CALL	 */
#define REGSPEC_GEN_CALL_WIDTH                                                1
#define REGSPEC_GEN_CALL_SHIFT                                               11
#define REGSPEC_GEN_CALL_MASK                                        0x00000800
#define REGSPEC_GEN_CALL_RD(src)                     (((src) & 0x00000800)>>11)
#define REGSPEC_GEN_CALL_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields START_DET	 */
#define REGSPEC_START_DET_WIDTH                                               1
#define REGSPEC_START_DET_SHIFT                                              10
#define REGSPEC_START_DET_MASK                                       0x00000400
#define REGSPEC_START_DET_RD(src)                    (((src) & 0x00000400)>>10)
#define REGSPEC_START_DET_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields STOP_DET	 */
#define REGSPEC_STOP_DET_WIDTH                                                1
#define REGSPEC_STOP_DET_SHIFT                                                9
#define REGSPEC_STOP_DET_MASK                                        0x00000200
#define REGSPEC_STOP_DET_RD(src)                      (((src) & 0x00000200)>>9)
#define REGSPEC_STOP_DET_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ACTIVITY	 */
#define REGSPEC_ACTIVITY_WIDTH                                                1
#define REGSPEC_ACTIVITY_SHIFT                                                8
#define REGSPEC_ACTIVITY_MASK                                        0x00000100
#define REGSPEC_ACTIVITY_RD(src)                      (((src) & 0x00000100)>>8)
#define REGSPEC_ACTIVITY_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields RX_DONE	 */
#define REGSPEC_RX_DONE_WIDTH                                                 1
#define REGSPEC_RX_DONE_SHIFT                                                 7
#define REGSPEC_RX_DONE_MASK                                         0x00000080
#define REGSPEC_RX_DONE_RD(src)                       (((src) & 0x00000080)>>7)
#define REGSPEC_RX_DONE_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields TX_ABRT	 */
#define REGSPEC_TX_ABRT_WIDTH                                                 1
#define REGSPEC_TX_ABRT_SHIFT                                                 6
#define REGSPEC_TX_ABRT_MASK                                         0x00000040
#define REGSPEC_TX_ABRT_RD(src)                       (((src) & 0x00000040)>>6)
#define REGSPEC_TX_ABRT_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields RD_REQ	 */
#define REGSPEC_RD_REQ_WIDTH                                                  1
#define REGSPEC_RD_REQ_SHIFT                                                  5
#define REGSPEC_RD_REQ_MASK                                          0x00000020
#define REGSPEC_RD_REQ_RD(src)                        (((src) & 0x00000020)>>5)
#define REGSPEC_RD_REQ_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields TX_EMPTY	 */
#define REGSPEC_TX_EMPTY_WIDTH                                                1
#define REGSPEC_TX_EMPTY_SHIFT                                                4
#define REGSPEC_TX_EMPTY_MASK                                        0x00000010
#define REGSPEC_TX_EMPTY_RD(src)                      (((src) & 0x00000010)>>4)
#define REGSPEC_TX_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields TX_OVER	 */
#define REGSPEC_TX_OVER_WIDTH                                                 1
#define REGSPEC_TX_OVER_SHIFT                                                 3
#define REGSPEC_TX_OVER_MASK                                         0x00000008
#define REGSPEC_TX_OVER_RD(src)                       (((src) & 0x00000008)>>3)
#define REGSPEC_TX_OVER_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields RX_FULL	 */
#define REGSPEC_RX_FULL_WIDTH                                                 1
#define REGSPEC_RX_FULL_SHIFT                                                 2
#define REGSPEC_RX_FULL_MASK                                         0x00000004
#define REGSPEC_RX_FULL_RD(src)                       (((src) & 0x00000004)>>2)
#define REGSPEC_RX_FULL_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields RX_OVER	 */
#define REGSPEC_RX_OVER_WIDTH                                                 1
#define REGSPEC_RX_OVER_SHIFT                                                 1
#define REGSPEC_RX_OVER_MASK                                         0x00000002
#define REGSPEC_RX_OVER_RD(src)                       (((src) & 0x00000002)>>1)
#define REGSPEC_RX_OVER_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields RX_UNDER	 */
#define REGSPEC_RX_UNDER_WIDTH                                                1
#define REGSPEC_RX_UNDER_SHIFT                                                0
#define REGSPEC_RX_UNDER_MASK                                        0x00000001
#define REGSPEC_RX_UNDER_RD(src)                         (((src) & 0x00000001))
#define REGSPEC_RX_UNDER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_RX_TL	*/ 
/*	 Fields I2C_RX_TL	 */
#define REGSPEC_I2C_RX_TL_WIDTH                                               8
#define REGSPEC_I2C_RX_TL_SHIFT                                               0
#define REGSPEC_I2C_RX_TL_MASK                                       0x000000ff
#define REGSPEC_I2C_RX_TL_RD(src)                        (((src) & 0x000000ff))
#define REGSPEC_I2C_RX_TL_WR(src)                   (((u32)(src)) & 0x000000ff)
#define REGSPEC_I2C_RX_TL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register I2C_TX_TL	*/ 
/*	 Fields I2C_TX_TL	 */
#define REGSPEC_I2C_TX_TL_WIDTH                                               8
#define REGSPEC_I2C_TX_TL_SHIFT                                               0
#define REGSPEC_I2C_TX_TL_MASK                                       0x000000ff
#define REGSPEC_I2C_TX_TL_RD(src)                        (((src) & 0x000000ff))
#define REGSPEC_I2C_TX_TL_WR(src)                   (((u32)(src)) & 0x000000ff)
#define REGSPEC_I2C_TX_TL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register I2C_CLR_INTR	*/ 
/*	 Fields CLR_INTR	 */
#define REGSPEC_CLR_INTR_WIDTH                                                1
#define REGSPEC_CLR_INTR_SHIFT                                                0
#define REGSPEC_CLR_INTR_MASK                                        0x00000001
#define REGSPEC_CLR_INTR_RD(src)                         (((src) & 0x00000001))
#define REGSPEC_CLR_INTR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_RX_UNDER	*/ 
/*	 Fields CLR_RX_UNDER	 */
#define REGSPEC_CLR_RX_UNDER_WIDTH                                            1
#define REGSPEC_CLR_RX_UNDER_SHIFT                                            0
#define REGSPEC_CLR_RX_UNDER_MASK                                    0x00000001
#define REGSPEC_CLR_RX_UNDER_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_CLR_RX_UNDER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_RX_OVER	*/ 
/*	 Fields CLR_RX_OVER	 */
#define REGSPEC_CLR_RX_OVER_WIDTH                                             1
#define REGSPEC_CLR_RX_OVER_SHIFT                                             0
#define REGSPEC_CLR_RX_OVER_MASK                                     0x00000001
#define REGSPEC_CLR_RX_OVER_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_CLR_RX_OVER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_TX_OVER	*/ 
/*	 Fields CLR_TX_OVER	 */
#define REGSPEC_CLR_TX_OVER_WIDTH                                             1
#define REGSPEC_CLR_TX_OVER_SHIFT                                             0
#define REGSPEC_CLR_TX_OVER_MASK                                     0x00000001
#define REGSPEC_CLR_TX_OVER_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_CLR_TX_OVER_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_RD_REQ	*/ 
/*	 Fields CLR_RD_REQ	 */
#define REGSPEC_CLR_RD_REQ_WIDTH                                              1
#define REGSPEC_CLR_RD_REQ_SHIFT                                              0
#define REGSPEC_CLR_RD_REQ_MASK                                      0x00000001
#define REGSPEC_CLR_RD_REQ_RD(src)                       (((src) & 0x00000001))
#define REGSPEC_CLR_RD_REQ_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_TX_ABRT	*/ 
/*	 Fields CLR_TX_ABRT	 */
#define REGSPEC_CLR_TX_ABRT_WIDTH                                             1
#define REGSPEC_CLR_TX_ABRT_SHIFT                                             0
#define REGSPEC_CLR_TX_ABRT_MASK                                     0x00000001
#define REGSPEC_CLR_TX_ABRT_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_CLR_TX_ABRT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_RX_DONE	*/ 
/*	 Fields CLR_RX_DONE	 */
#define REGSPEC_CLR_RX_DONE_WIDTH                                             1
#define REGSPEC_CLR_RX_DONE_SHIFT                                             0
#define REGSPEC_CLR_RX_DONE_MASK                                     0x00000001
#define REGSPEC_CLR_RX_DONE_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_CLR_RX_DONE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_ACTIVITY	*/ 
/*	 Fields CLR_ACTIVITY	 */
#define REGSPEC_CLR_ACTIVITY_WIDTH                                            1
#define REGSPEC_CLR_ACTIVITY_SHIFT                                            0
#define REGSPEC_CLR_ACTIVITY_MASK                                    0x00000001
#define REGSPEC_CLR_ACTIVITY_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_CLR_ACTIVITY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_STOP_DET	*/ 
/*	 Fields CLR_STOP_DET	 */
#define REGSPEC_CLR_STOP_DET_WIDTH                                            1
#define REGSPEC_CLR_STOP_DET_SHIFT                                            0
#define REGSPEC_CLR_STOP_DET_MASK                                    0x00000001
#define REGSPEC_CLR_STOP_DET_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_CLR_STOP_DET_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_START_DET	*/ 
/*	 Fields CLR_START_DET	 */
#define REGSPEC_CLR_START_DET_WIDTH                                           1
#define REGSPEC_CLR_START_DET_SHIFT                                           0
#define REGSPEC_CLR_START_DET_MASK                                   0x00000001
#define REGSPEC_CLR_START_DET_RD(src)                    (((src) & 0x00000001))
#define REGSPEC_CLR_START_DET_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_CLR_GEN_CALL	*/ 
/*	 Fields CLR_GEN_CALL	 */
#define REGSPEC_CLR_GEN_CALL_WIDTH                                            1
#define REGSPEC_CLR_GEN_CALL_SHIFT                                            0
#define REGSPEC_CLR_GEN_CALL_MASK                                    0x00000001
#define REGSPEC_CLR_GEN_CALL_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_CLR_GEN_CALL_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_ENABLE	*/ 
/*	 Fields ENABLE	 */
#define REGSPEC_ENABLE_F14_WIDTH                                              1
#define REGSPEC_ENABLE_F14_SHIFT                                              0
#define REGSPEC_ENABLE_F14_MASK                                      0x00000001
#define REGSPEC_ENABLE_F14_RD(src)                       (((src) & 0x00000001))
#define REGSPEC_ENABLE_F14_WR(src)                  (((u32)(src)) & 0x00000001)
#define REGSPEC_ENABLE_F14_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_STATUS	*/ 
/*	 Fields SLV_ACTIVITY	 */
#define REGSPEC_SLV_ACTIVITY_WIDTH                                            1
#define REGSPEC_SLV_ACTIVITY_SHIFT                                            6
#define REGSPEC_SLV_ACTIVITY_MASK                                    0x00000040
#define REGSPEC_SLV_ACTIVITY_RD(src)                  (((src) & 0x00000040)>>6)
#define REGSPEC_SLV_ACTIVITY_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MST_ACTIVITY	 */
#define REGSPEC_MST_ACTIVITY_WIDTH                                            1
#define REGSPEC_MST_ACTIVITY_SHIFT                                            5
#define REGSPEC_MST_ACTIVITY_MASK                                    0x00000020
#define REGSPEC_MST_ACTIVITY_RD(src)                  (((src) & 0x00000020)>>5)
#define REGSPEC_MST_ACTIVITY_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RFF	 */
#define REGSPEC_RFF_WIDTH                                                     1
#define REGSPEC_RFF_SHIFT                                                     4
#define REGSPEC_RFF_MASK                                             0x00000010
#define REGSPEC_RFF_RD(src)                           (((src) & 0x00000010)>>4)
#define REGSPEC_RFF_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields RFNE	 */
#define REGSPEC_RFNE_WIDTH                                                    1
#define REGSPEC_RFNE_SHIFT                                                    3
#define REGSPEC_RFNE_MASK                                            0x00000008
#define REGSPEC_RFNE_RD(src)                          (((src) & 0x00000008)>>3)
#define REGSPEC_RFNE_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields TFE	 */
#define REGSPEC_TFE_WIDTH                                                     1
#define REGSPEC_TFE_SHIFT                                                     2
#define REGSPEC_TFE_MASK                                             0x00000004
#define REGSPEC_TFE_RD(src)                           (((src) & 0x00000004)>>2)
#define REGSPEC_TFE_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TFNF	 */
#define REGSPEC_TFNF_WIDTH                                                    1
#define REGSPEC_TFNF_SHIFT                                                    1
#define REGSPEC_TFNF_MASK                                            0x00000002
#define REGSPEC_TFNF_RD(src)                          (((src) & 0x00000002)>>1)
#define REGSPEC_TFNF_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ACTIVITY	 */
#define REGSPEC_ACTIVITY_F1_WIDTH                                             1
#define REGSPEC_ACTIVITY_F1_SHIFT                                             0
#define REGSPEC_ACTIVITY_F1_MASK                                     0x00000001
#define REGSPEC_ACTIVITY_F1_RD(src)                      (((src) & 0x00000001))
#define REGSPEC_ACTIVITY_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_TXFLR	*/ 
/*	 Fields TXFLR	 */
#define REGSPEC_TXFLR_WIDTH                                                   3
#define REGSPEC_TXFLR_SHIFT                                                   0
#define REGSPEC_TXFLR_MASK                                           0x00000007
#define REGSPEC_TXFLR_RD(src)                            (((src) & 0x00000007))
#define REGSPEC_TXFLR_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register I2C_RXFLR	*/ 
/*	 Fields RXFLR	 */
#define REGSPEC_RXFLR_WIDTH                                                   3
#define REGSPEC_RXFLR_SHIFT                                                   0
#define REGSPEC_RXFLR_MASK                                           0x00000007
#define REGSPEC_RXFLR_RD(src)                            (((src) & 0x00000007))
#define REGSPEC_RXFLR_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register I2C_TX_ABRT_SOURCE	*/ 
/*	 Fields ABRT_SLVRD_INTX	 */
#define REGSPEC_ABRT_SLVRD_INTX_WIDTH                                         1
#define REGSPEC_ABRT_SLVRD_INTX_SHIFT                                        15
#define REGSPEC_ABRT_SLVRD_INTX_MASK                                 0x00008000
#define REGSPEC_ABRT_SLVRD_INTX_RD(src)              (((src) & 0x00008000)>>15)
#define REGSPEC_ABRT_SLVRD_INTX_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields ABRT_SLV_ARBLOST	 */
#define REGSPEC_ABRT_SLV_ARBLOST_WIDTH                                        1
#define REGSPEC_ABRT_SLV_ARBLOST_SHIFT                                       14
#define REGSPEC_ABRT_SLV_ARBLOST_MASK                                0x00004000
#define REGSPEC_ABRT_SLV_ARBLOST_RD(src)             (((src) & 0x00004000)>>14)
#define REGSPEC_ABRT_SLV_ARBLOST_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields ABRT_SLVFLUSH_TXFIFO	 */
#define REGSPEC_ABRT_SLVFLUSH_TXFIFO_WIDTH                                    1
#define REGSPEC_ABRT_SLVFLUSH_TXFIFO_SHIFT                                   13
#define REGSPEC_ABRT_SLVFLUSH_TXFIFO_MASK                            0x00002000
#define REGSPEC_ABRT_SLVFLUSH_TXFIFO_RD(src)         (((src) & 0x00002000)>>13)
#define REGSPEC_ABRT_SLVFLUSH_TXFIFO_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields ARB_LOST	 */
#define REGSPEC_ARB_LOST_WIDTH                                                1
#define REGSPEC_ARB_LOST_SHIFT                                               12
#define REGSPEC_ARB_LOST_MASK                                        0x00001000
#define REGSPEC_ARB_LOST_RD(src)                     (((src) & 0x00001000)>>12)
#define REGSPEC_ARB_LOST_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields ABRT_MASTER_DIS	 */
#define REGSPEC_ABRT_MASTER_DIS_WIDTH                                         1
#define REGSPEC_ABRT_MASTER_DIS_SHIFT                                        11
#define REGSPEC_ABRT_MASTER_DIS_MASK                                 0x00000800
#define REGSPEC_ABRT_MASTER_DIS_RD(src)              (((src) & 0x00000800)>>11)
#define REGSPEC_ABRT_MASTER_DIS_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields ABRT_10B_RD_NORSTRT	 */
#define REGSPEC_ABRT_10B_RD_NORSTRT_WIDTH                                     1
#define REGSPEC_ABRT_10B_RD_NORSTRT_SHIFT                                    10
#define REGSPEC_ABRT_10B_RD_NORSTRT_MASK                             0x00000400
#define REGSPEC_ABRT_10B_RD_NORSTRT_RD(src)          (((src) & 0x00000400)>>10)
#define REGSPEC_ABRT_10B_RD_NORSTRT_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields ABRT_SBYTE_NORSTRT	 */
#define REGSPEC_ABRT_SBYTE_NORSTRT_WIDTH                                      1
#define REGSPEC_ABRT_SBYTE_NORSTRT_SHIFT                                      9
#define REGSPEC_ABRT_SBYTE_NORSTRT_MASK                              0x00000200
#define REGSPEC_ABRT_SBYTE_NORSTRT_RD(src)            (((src) & 0x00000200)>>9)
#define REGSPEC_ABRT_SBYTE_NORSTRT_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields ABRT_HS_NORSTRT	 */
#define REGSPEC_ABRT_HS_NORSTRT_WIDTH                                         1
#define REGSPEC_ABRT_HS_NORSTRT_SHIFT                                         8
#define REGSPEC_ABRT_HS_NORSTRT_MASK                                 0x00000100
#define REGSPEC_ABRT_HS_NORSTRT_RD(src)               (((src) & 0x00000100)>>8)
#define REGSPEC_ABRT_HS_NORSTRT_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields ABRT_SBYTE_ACKDET	 */
#define REGSPEC_ABRT_SBYTE_ACKDET_WIDTH                                       1
#define REGSPEC_ABRT_SBYTE_ACKDET_SHIFT                                       7
#define REGSPEC_ABRT_SBYTE_ACKDET_MASK                               0x00000080
#define REGSPEC_ABRT_SBYTE_ACKDET_RD(src)             (((src) & 0x00000080)>>7)
#define REGSPEC_ABRT_SBYTE_ACKDET_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields ABRT_HS_ACKDET	 */
#define REGSPEC_ABRT_HS_ACKDET_WIDTH                                          1
#define REGSPEC_ABRT_HS_ACKDET_SHIFT                                          6
#define REGSPEC_ABRT_HS_ACKDET_MASK                                  0x00000040
#define REGSPEC_ABRT_HS_ACKDET_RD(src)                (((src) & 0x00000040)>>6)
#define REGSPEC_ABRT_HS_ACKDET_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields ABRT_GCALL_READ	 */
#define REGSPEC_ABRT_GCALL_READ_WIDTH                                         1
#define REGSPEC_ABRT_GCALL_READ_SHIFT                                         5
#define REGSPEC_ABRT_GCALL_READ_MASK                                 0x00000020
#define REGSPEC_ABRT_GCALL_READ_RD(src)               (((src) & 0x00000020)>>5)
#define REGSPEC_ABRT_GCALL_READ_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ABRT_GCALL_NOACK	 */
#define REGSPEC_ABRT_GCALL_NOACK_WIDTH                                        1
#define REGSPEC_ABRT_GCALL_NOACK_SHIFT                                        4
#define REGSPEC_ABRT_GCALL_NOACK_MASK                                0x00000010
#define REGSPEC_ABRT_GCALL_NOACK_RD(src)              (((src) & 0x00000010)>>4)
#define REGSPEC_ABRT_GCALL_NOACK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields ABRT_TXDATA_NOACK	 */
#define REGSPEC_ABRT_TXDATA_NOACK_WIDTH                                       1
#define REGSPEC_ABRT_TXDATA_NOACK_SHIFT                                       3
#define REGSPEC_ABRT_TXDATA_NOACK_MASK                               0x00000008
#define REGSPEC_ABRT_TXDATA_NOACK_RD(src)             (((src) & 0x00000008)>>3)
#define REGSPEC_ABRT_TXDATA_NOACK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ABRT_10ADDR2_NOACK	 */
#define REGSPEC_ABRT_10ADDR2_NOACK_WIDTH                                      1
#define REGSPEC_ABRT_10ADDR2_NOACK_SHIFT                                      2
#define REGSPEC_ABRT_10ADDR2_NOACK_MASK                              0x00000004
#define REGSPEC_ABRT_10ADDR2_NOACK_RD(src)            (((src) & 0x00000004)>>2)
#define REGSPEC_ABRT_10ADDR2_NOACK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields ABRT_10ADDR1_NOACK	 */
#define REGSPEC_ABRT_10ADDR1_NOACK_WIDTH                                      1
#define REGSPEC_ABRT_10ADDR1_NOACK_SHIFT                                      1
#define REGSPEC_ABRT_10ADDR1_NOACK_MASK                              0x00000002
#define REGSPEC_ABRT_10ADDR1_NOACK_RD(src)            (((src) & 0x00000002)>>1)
#define REGSPEC_ABRT_10ADDR1_NOACK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ABRT_7B_ADDR_NOACK	 */
#define REGSPEC_ABRT_7B_ADDR_NOACK_WIDTH                                      1
#define REGSPEC_ABRT_7B_ADDR_NOACK_SHIFT                                      0
#define REGSPEC_ABRT_7B_ADDR_NOACK_MASK                              0x00000001
#define REGSPEC_ABRT_7B_ADDR_NOACK_RD(src)               (((src) & 0x00000001))
#define REGSPEC_ABRT_7B_ADDR_NOACK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_SLV_DATA_NACK_ONLY	*/ 
/*	 Fields NACK	 */
#define REGSPEC_NACK_F2_WIDTH                                                 1
#define REGSPEC_NACK_F2_SHIFT                                                 0
#define REGSPEC_NACK_F2_MASK                                         0x00000001
#define REGSPEC_NACK_F2_RD(src)                          (((src) & 0x00000001))
#define REGSPEC_NACK_F2_WR(src)                     (((u32)(src)) & 0x00000001)
#define REGSPEC_NACK_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_SDA_SETUP	*/ 
/*	 Fields SDA_SETUP	 */
#define REGSPEC_SDA_SETUP_WIDTH                                               8
#define REGSPEC_SDA_SETUP_SHIFT                                               0
#define REGSPEC_SDA_SETUP_MASK                                       0x000000ff
#define REGSPEC_SDA_SETUP_RD(src)                        (((src) & 0x000000ff))
#define REGSPEC_SDA_SETUP_WR(src)                   (((u32)(src)) & 0x000000ff)
#define REGSPEC_SDA_SETUP_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register I2C_ACK_GENERAL_CALL	*/ 
/*	 Fields ACK_GEN_CALL	 */
#define REGSPEC_ACK_GEN_CALL_WIDTH                                            1
#define REGSPEC_ACK_GEN_CALL_SHIFT                                            0
#define REGSPEC_ACK_GEN_CALL_MASK                                    0x00000001
#define REGSPEC_ACK_GEN_CALL_RD(src)                     (((src) & 0x00000001))
#define REGSPEC_ACK_GEN_CALL_WR(src)                (((u32)(src)) & 0x00000001)
#define REGSPEC_ACK_GEN_CALL_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_ENABLE_STATUS	*/ 
/*	 Fields SLV_FIFO_FILLED_AND_FLUSHED	 */
#define REGSPEC_SLV_FIFO_FILLED_AND_FLUSHED_WIDTH                             1
#define REGSPEC_SLV_FIFO_FILLED_AND_FLUSHED_SHIFT                             2
#define REGSPEC_SLV_FIFO_FILLED_AND_FLUSHED_MASK                     0x00000004
#define REGSPEC_SLV_FIFO_FILLED_AND_FLUSHED_RD(src)   (((src) & 0x00000004)>>2)
#define REGSPEC_SLV_FIFO_FILLED_AND_FLUSHED_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SLV_RX_ABORTED	 */
#define REGSPEC_SLV_RX_ABORTED_WIDTH                                          1
#define REGSPEC_SLV_RX_ABORTED_SHIFT                                          1
#define REGSPEC_SLV_RX_ABORTED_MASK                                  0x00000002
#define REGSPEC_SLV_RX_ABORTED_RD(src)                (((src) & 0x00000002)>>1)
#define REGSPEC_SLV_RX_ABORTED_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields IC_EN	 */
#define REGSPEC_IC_EN_WIDTH                                                   1
#define REGSPEC_IC_EN_SHIFT                                                   0
#define REGSPEC_IC_EN_MASK                                           0x00000001
#define REGSPEC_IC_EN_RD(src)                            (((src) & 0x00000001))
#define REGSPEC_IC_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register I2C_COMP_PARAM_1	*/ 
/*	 Fields TX_BUFFER_DEPTH	 */
#define REGSPEC_TX_BUFFER_DEPTH1_WIDTH                                        8
#define REGSPEC_TX_BUFFER_DEPTH1_SHIFT                                       16
#define REGSPEC_TX_BUFFER_DEPTH1_MASK                                0x00ff0000
#define REGSPEC_TX_BUFFER_DEPTH1_RD(src)             (((src) & 0x00ff0000)>>16)
#define REGSPEC_TX_BUFFER_DEPTH1_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields RX_BUFFER_DEPTH	 */
#define REGSPEC_RX_BUFFER_DEPTH1_WIDTH                                        8
#define REGSPEC_RX_BUFFER_DEPTH1_SHIFT                                        8
#define REGSPEC_RX_BUFFER_DEPTH1_MASK                                0x0000ff00
#define REGSPEC_RX_BUFFER_DEPTH1_RD(src)              (((src) & 0x0000ff00)>>8)
#define REGSPEC_RX_BUFFER_DEPTH1_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields ADD_ENCODED_PARAMS	 */
#define REGSPEC_ADD_ENCODED_PARAMS1_WIDTH                                     1
#define REGSPEC_ADD_ENCODED_PARAMS1_SHIFT                                     7
#define REGSPEC_ADD_ENCODED_PARAMS1_MASK                             0x00000080
#define REGSPEC_ADD_ENCODED_PARAMS1_RD(src)           (((src) & 0x00000080)>>7)
#define REGSPEC_ADD_ENCODED_PARAMS1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields HAS_DMA	 */
#define REGSPEC_HAS_DMA1_WIDTH                                                1
#define REGSPEC_HAS_DMA1_SHIFT                                                6
#define REGSPEC_HAS_DMA1_MASK                                        0x00000040
#define REGSPEC_HAS_DMA1_RD(src)                      (((src) & 0x00000040)>>6)
#define REGSPEC_HAS_DMA1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields INTR_IO	 */
#define REGSPEC_INTR_IO1_WIDTH                                                1
#define REGSPEC_INTR_IO1_SHIFT                                                5
#define REGSPEC_INTR_IO1_MASK                                        0x00000020
#define REGSPEC_INTR_IO1_RD(src)                      (((src) & 0x00000020)>>5)
#define REGSPEC_INTR_IO1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields HC_COUNT_VALUES	 */
#define REGSPEC_HC_COUNT_VALUES1_WIDTH                                        1
#define REGSPEC_HC_COUNT_VALUES1_SHIFT                                        4
#define REGSPEC_HC_COUNT_VALUES1_MASK                                0x00000010
#define REGSPEC_HC_COUNT_VALUES1_RD(src)              (((src) & 0x00000010)>>4)
#define REGSPEC_HC_COUNT_VALUES1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MAX_SPEED_MODE	 */
#define REGSPEC_MAX_SPEED_MODE1_WIDTH                                         2
#define REGSPEC_MAX_SPEED_MODE1_SHIFT                                         2
#define REGSPEC_MAX_SPEED_MODE1_MASK                                 0x0000000c
#define REGSPEC_MAX_SPEED_MODE1_RD(src)               (((src) & 0x0000000c)>>2)
#define REGSPEC_MAX_SPEED_MODE1_SET(dst,src) \
                       (((dst) & ~0x0000000c) | (((u32)(src)<<2) & 0x0000000c))
/*	 Fields APB_DATA_WIDTH	 */
#define REGSPEC_APB_DATA_WIDTH1_WIDTH                                         2
#define REGSPEC_APB_DATA_WIDTH1_SHIFT                                         0
#define REGSPEC_APB_DATA_WIDTH1_MASK                                 0x00000003
#define REGSPEC_APB_DATA_WIDTH1_RD(src)                  (((src) & 0x00000003))
#define REGSPEC_APB_DATA_WIDTH1_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register I2C_COMP_VERSION	*/ 
/*	 Fields I2C_COMP_VERSION	 */
#define REGSPEC_I2C_COMP_VERSION_WIDTH                                       32
#define REGSPEC_I2C_COMP_VERSION_SHIFT                                        0
#define REGSPEC_I2C_COMP_VERSION_MASK                                0xffffffff
#define REGSPEC_I2C_COMP_VERSION_RD(src)                 (((src) & 0xffffffff))
#define REGSPEC_I2C_COMP_VERSION_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register I2C_COMP_TYPE	*/ 
/*	 Fields I2C_COMP_TYPE	 */
#define REGSPEC_I2C_COMP_TYPE_WIDTH                                          32
#define REGSPEC_I2C_COMP_TYPE_SHIFT                                           0
#define REGSPEC_I2C_COMP_TYPE_MASK                                   0xffffffff
#define REGSPEC_I2C_COMP_TYPE_RD(src)                    (((src) & 0xffffffff))
#define REGSPEC_I2C_COMP_TYPE_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*    Address MPA_IIC0_I  Registers */

/*	Global Base Address	*/
#define MPA_PKP_TRNG_I_BASE_ADDR			0x050020000ULL

/*    Address MPA_PKP_TRNG_I  Registers */
#define TRNG_INOUT_0_ADDR                                            0x00000000
#define TRNG_INOUT_0_DEFAULT                                         0x00000000
#define TRNG_INOUT_1_ADDR                                            0x00000004
#define TRNG_INOUT_1_DEFAULT                                         0x00000000
#define TRNG_INOUT_2_ADDR                                            0x00000008
#define TRNG_INOUT_2_DEFAULT                                         0x00000000
#define TRNG_INOUT_3_ADDR                                            0x0000000c
#define TRNG_INOUT_3_DEFAULT                                         0x00000000
#define TRNG_INTR_STS_ACK_ADDR                                       0x00000010
#define TRNG_INTR_STS_ACK_DEFAULT                                    0x00000000
#define TRNG_CONTROL_ADDR                                            0x00000014
#define TRNG_CONTROL_DEFAULT                                         0x00000000
#define TRNG_CONFIG_ADDR                                             0x00000018
#define TRNG_CONFIG_DEFAULT                                          0x00000000
#define TRNG_ALARMCNT_ADDR                                           0x0000001c
#define TRNG_ALARMCNT_DEFAULT                                        0xff000000
#define TRNG_FROENABLE_ADDR                                          0x00000020
#define TRNG_FROENABLE_DEFAULT                                       0x00ffffff
#define TRNG_FRODETUNE_ADDR                                          0x00000024
#define TRNG_FRODETUNE_DEFAULT                                       0x00000000
#define TRNG_ALARMMASK_ADDR                                          0x00000028
#define TRNG_ALARMMASK_DEFAULT                                       0x00000000
#define TRNG_ALARMSTOP_ADDR                                          0x0000002c
#define TRNG_ALARMSTOP_DEFAULT                                       0x00000000
#define TRNG_LFSR_L_ADDR                                             0x00000030
#define TRNG_LFSR_L_DEFAULT                                          0x00000000
#define TRNG_LFSR_M_ADDR                                             0x00000034
#define TRNG_LFSR_M_DEFAULT                                          0x00000000
#define TRNG_LFSR_H_ADDR                                             0x00000038
#define TRNG_LFSR_H_DEFAULT                                          0x00000000
#define TRNG_COUNT_ADDR                                              0x0000003c
#define TRNG_COUNT_DEFAULT                                           0x00000000
#define TRNG_KEY_PS_AI_0_ADDR                                        0x00000040
#define TRNG_KEY_PS_AI_0_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_1_ADDR                                        0x00000044
#define TRNG_KEY_PS_AI_1_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_2_ADDR                                        0x00000048
#define TRNG_KEY_PS_AI_2_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_3_ADDR                                        0x0000004c
#define TRNG_KEY_PS_AI_3_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_4_ADDR                                        0x00000050
#define TRNG_KEY_PS_AI_4_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_5_ADDR                                        0x00000054
#define TRNG_KEY_PS_AI_5_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_6_ADDR                                        0x00000058
#define TRNG_KEY_PS_AI_6_DEFAULT                                     0x00000000
#define TRNG_KEY_PS_AI_7_ADDR                                        0x0000005c
#define TRNG_KEY_PS_AI_7_DEFAULT                                     0x08e80000
#define TRNG_V_0_PS_AI_8_ADDR                                        0x00000060
#define TRNG_V_0_PS_AI_8_DEFAULT                                     0xffffffff
#define TRNG_V_1_PS_AI_9_ADDR                                        0x00000064
#define TRNG_V_1_PS_AI_9_DEFAULT                                     0xffffffff
#define TRNG_V_2_PS_AI_10_ADDR                                       0x00000068
#define TRNG_V_2_PS_AI_10_DEFAULT                                    0xffffffff
#define TRNG_V_3_PS_AI_11_ADDR                                       0x0000006c
#define TRNG_V_3_PS_AI_11_DEFAULT                                    0xffffffff
#define TRNG_TEST_ADDR                                               0x00000070
#define TRNG_TEST_DEFAULT                                            0x00000000
#define TRNG_BLOCKCNT_ADDR                                           0x00000074
#define TRNG_BLOCKCNT_DEFAULT                                        0x00000000
#define TRNG_OPTIONS_ADDR                                            0x00000078
#define TRNG_OPTIONS_DEFAULT                                         0xa04e8000
#define TRNG_EIP_REV_ADDR                                            0x0000007c
#define TRNG_EIP_REV_DEFAULT                                         0x32cd0880

/*	Register TRNG_INOUT_0	*/ 
/*	 Fields INOUT_0	 */
#define INOUT_00_WIDTH                                                       32
#define INOUT_00_SHIFT                                                        0
#define INOUT_00_MASK                                                0xffffffff
#define INOUT_00_RD(src)                                 (((src) & 0xffffffff))
#define INOUT_00_WR(src)                            (((u32)(src)) & 0xffffffff)
#define INOUT_00_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_INOUT_1	*/ 
/*	 Fields INOUT_1	 */
#define INOUT_11_WIDTH                                                       32
#define INOUT_11_SHIFT                                                        0
#define INOUT_11_MASK                                                0xffffffff
#define INOUT_11_RD(src)                                 (((src) & 0xffffffff))
#define INOUT_11_WR(src)                            (((u32)(src)) & 0xffffffff)
#define INOUT_11_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_INOUT_2	*/ 
/*	 Fields INOUT_2	 */
#define INOUT_22_WIDTH                                                       32
#define INOUT_22_SHIFT                                                        0
#define INOUT_22_MASK                                                0xffffffff
#define INOUT_22_RD(src)                                 (((src) & 0xffffffff))
#define INOUT_22_WR(src)                            (((u32)(src)) & 0xffffffff)
#define INOUT_22_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_INOUT_3	*/ 
/*	 Fields INOUT_3	 */
#define INOUT_33_WIDTH                                                       32
#define INOUT_33_SHIFT                                                        0
#define INOUT_33_MASK                                                0xffffffff
#define INOUT_33_RD(src)                                 (((src) & 0xffffffff))
#define INOUT_33_WR(src)                            (((u32)(src)) & 0xffffffff)
#define INOUT_33_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_INTR_STS_ACK	*/ 
/*	 Fields NEED_CLOCK	 */
#define NEED_CLOCK_WIDTH                                                      1
#define NEED_CLOCK_SHIFT                                                     31
#define NEED_CLOCK_MASK                                              0x80000000
#define NEED_CLOCK_RD(src)                           (((src) & 0x80000000)>>31)
#define NEED_CLOCK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define NEED_CLOCK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields BLKS_AVAIL	 */
#define BLKS_AVAIL_WIDTH                                                      8
#define BLKS_AVAIL_SHIFT                                                     16
#define BLKS_AVAIL_MASK                                              0x00ff0000
#define BLKS_AVAIL_RD(src)                           (((src) & 0x00ff0000)>>16)
#define BLKS_AVAIL_WR(src)                      (((u32)(src)<<16) & 0x00ff0000)
#define BLKS_AVAIL_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields TEST_READY	 */
#define TEST_READY_WIDTH                                                      1
#define TEST_READY_SHIFT                                                      8
#define TEST_READY_MASK                                              0x00000100
#define TEST_READY_RD(src)                            (((src) & 0x00000100)>>8)
#define TEST_READY_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define TEST_READY_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MONOBIT_FAIL	 */
#define MONOBIT_FAIL_WIDTH                                                    1
#define MONOBIT_FAIL_SHIFT                                                    7
#define MONOBIT_FAIL_MASK                                            0x00000080
#define MONOBIT_FAIL_RD(src)                          (((src) & 0x00000080)>>7)
#define MONOBIT_FAIL_WR(src)                     (((u32)(src)<<7) & 0x00000080)
#define MONOBIT_FAIL_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields POKER_FAIL	 */
#define POKER_FAIL_WIDTH                                                      1
#define POKER_FAIL_SHIFT                                                      6
#define POKER_FAIL_MASK                                              0x00000040
#define POKER_FAIL_RD(src)                            (((src) & 0x00000040)>>6)
#define POKER_FAIL_WR(src)                       (((u32)(src)<<6) & 0x00000040)
#define POKER_FAIL_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields LONG_RUN_FAIL	 */
#define LONG_RUN_FAIL_WIDTH                                                   1
#define LONG_RUN_FAIL_SHIFT                                                   5
#define LONG_RUN_FAIL_MASK                                           0x00000020
#define LONG_RUN_FAIL_RD(src)                         (((src) & 0x00000020)>>5)
#define LONG_RUN_FAIL_WR(src)                    (((u32)(src)<<5) & 0x00000020)
#define LONG_RUN_FAIL_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RUN_FAIL	 */
#define RUN_FAIL_WIDTH                                                        1
#define RUN_FAIL_SHIFT                                                        4
#define RUN_FAIL_MASK                                                0x00000010
#define RUN_FAIL_RD(src)                              (((src) & 0x00000010)>>4)
#define RUN_FAIL_WR(src)                         (((u32)(src)<<4) & 0x00000010)
#define RUN_FAIL_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields NOISE_FAIL	 */
#define NOISE_FAIL_WIDTH                                                      1
#define NOISE_FAIL_SHIFT                                                      3
#define NOISE_FAIL_MASK                                              0x00000008
#define NOISE_FAIL_RD(src)                            (((src) & 0x00000008)>>3)
#define NOISE_FAIL_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define NOISE_FAIL_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields STUCK_OUT	 */
#define STUCK_OUT_WIDTH                                                       1
#define STUCK_OUT_SHIFT                                                       2
#define STUCK_OUT_MASK                                               0x00000004
#define STUCK_OUT_RD(src)                             (((src) & 0x00000004)>>2)
#define STUCK_OUT_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define STUCK_OUT_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SHUTDOWN_OFLO	 */
#define SHUTDOWN_OFLO_WIDTH                                                   1
#define SHUTDOWN_OFLO_SHIFT                                                   1
#define SHUTDOWN_OFLO_MASK                                           0x00000002
#define SHUTDOWN_OFLO_RD(src)                         (((src) & 0x00000002)>>1)
#define SHUTDOWN_OFLO_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define SHUTDOWN_OFLO_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields READY	 */
#define READY_WIDTH                                                           1
#define READY_SHIFT                                                           0
#define READY_MASK                                                   0x00000001
#define READY_RD(src)                                    (((src) & 0x00000001))
#define READY_WR(src)                               (((u32)(src)) & 0x00000001)
#define READY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register TRNG_CONTROL	*/ 
/*	 Fields STARTUP_CYCLES	 */
#define STARTUP_CYCLES_WIDTH                                                 16
#define STARTUP_CYCLES_SHIFT                                                 16
#define STARTUP_CYCLES_MASK                                          0xffff0000
#define STARTUP_CYCLES_RD(src)                       (((src) & 0xffff0000)>>16)
#define STARTUP_CYCLES_WR(src)                  (((u32)(src)<<16) & 0xffff0000)
#define STARTUP_CYCLES_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields RESEED	 */
#define RESEED_WIDTH                                                          1
#define RESEED_SHIFT                                                         15
#define RESEED_MASK                                                  0x00008000
#define RESEED_RD(src)                               (((src) & 0x00008000)>>15)
#define RESEED_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define RESEED_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields POST_PROC_EN	 */
#define POST_PROC_EN_WIDTH                                                    1
#define POST_PROC_EN_SHIFT                                                   12
#define POST_PROC_EN_MASK                                            0x00001000
#define POST_PROC_EN_RD(src)                         (((src) & 0x00001000)>>12)
#define POST_PROC_EN_WR(src)                    (((u32)(src)<<12) & 0x00001000)
#define POST_PROC_EN_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields ENABLE_TRNG	 */
#define ENABLE_TRNG_WIDTH                                                     1
#define ENABLE_TRNG_SHIFT                                                    10
#define ENABLE_TRNG_MASK                                             0x00000400
#define ENABLE_TRNG_RD(src)                          (((src) & 0x00000400)>>10)
#define ENABLE_TRNG_WR(src)                     (((u32)(src)<<10) & 0x00000400)
#define ENABLE_TRNG_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields TEST_MODE	 */
#define REGSPEC_TEST_MODE_WIDTH                                               1
#define REGSPEC_TEST_MODE_SHIFT                                               8
#define REGSPEC_TEST_MODE_MASK                                       0x00000100
#define REGSPEC_TEST_MODE_RD(src)                     (((src) & 0x00000100)>>8)
#define REGSPEC_TEST_MODE_WR(src)                (((u32)(src)<<8) & 0x00000100)
#define REGSPEC_TEST_MODE_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MONOBIT_FAIL_MASK	 */
#define MONOBIT_FAIL_MASK_WIDTH                                               1
#define MONOBIT_FAIL_MASK_SHIFT                                               7
#define MONOBIT_FAIL_MASK_MASK                                       0x00000080
#define MONOBIT_FAIL_MASK_RD(src)                     (((src) & 0x00000080)>>7)
#define MONOBIT_FAIL_MASK_WR(src)                (((u32)(src)<<7) & 0x00000080)
#define MONOBIT_FAIL_MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields POKER_FAIL_MASK	 */
#define POKER_FAIL_MASK_WIDTH                                                 1
#define POKER_FAIL_MASK_SHIFT                                                 6
#define POKER_FAIL_MASK_MASK                                         0x00000040
#define POKER_FAIL_MASK_RD(src)                       (((src) & 0x00000040)>>6)
#define POKER_FAIL_MASK_WR(src)                  (((u32)(src)<<6) & 0x00000040)
#define POKER_FAIL_MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields LONG_RUN_FAIL_MASK	 */
#define LONG_RUN_FAIL_MASK_WIDTH                                              1
#define LONG_RUN_FAIL_MASK_SHIFT                                              5
#define LONG_RUN_FAIL_MASK_MASK                                      0x00000020
#define LONG_RUN_FAIL_MASK_RD(src)                    (((src) & 0x00000020)>>5)
#define LONG_RUN_FAIL_MASK_WR(src)               (((u32)(src)<<5) & 0x00000020)
#define LONG_RUN_FAIL_MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields RUN_FAIL_MASK	 */
#define RUN_FAIL_MASK_WIDTH                                                   1
#define RUN_FAIL_MASK_SHIFT                                                   4
#define RUN_FAIL_MASK_MASK                                           0x00000010
#define RUN_FAIL_MASK_RD(src)                         (((src) & 0x00000010)>>4)
#define RUN_FAIL_MASK_WR(src)                    (((u32)(src)<<4) & 0x00000010)
#define RUN_FAIL_MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields NOISE_FAIL_MASK	 */
#define NOISE_FAIL_MASK_WIDTH                                                 1
#define NOISE_FAIL_MASK_SHIFT                                                 3
#define NOISE_FAIL_MASK_MASK                                         0x00000008
#define NOISE_FAIL_MASK_RD(src)                       (((src) & 0x00000008)>>3)
#define NOISE_FAIL_MASK_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define NOISE_FAIL_MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields STUCK_OUT_MASK	 */
#define STUCK_OUT_MASK_WIDTH                                                  1
#define STUCK_OUT_MASK_SHIFT                                                  2
#define STUCK_OUT_MASK_MASK                                          0x00000004
#define STUCK_OUT_MASK_RD(src)                        (((src) & 0x00000004)>>2)
#define STUCK_OUT_MASK_WR(src)                   (((u32)(src)<<2) & 0x00000004)
#define STUCK_OUT_MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SHUTDOWN_OFLO_MASK	 */
#define SHUTDOWN_OFLO_MASK_WIDTH                                              1
#define SHUTDOWN_OFLO_MASK_SHIFT                                              1
#define SHUTDOWN_OFLO_MASK_MASK                                      0x00000002
#define SHUTDOWN_OFLO_MASK_RD(src)                    (((src) & 0x00000002)>>1)
#define SHUTDOWN_OFLO_MASK_WR(src)               (((u32)(src)<<1) & 0x00000002)
#define SHUTDOWN_OFLO_MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields READY_MASK	 */
#define READY_MASK_WIDTH                                                      1
#define READY_MASK_SHIFT                                                      0
#define READY_MASK_MASK                                              0x00000001
#define READY_MASK_RD(src)                               (((src) & 0x00000001))
#define READY_MASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define READY_MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register TRNG_CONFIG	*/ 
/*	 Fields MAX_REFILL_CYCLES	 */
#define MAX_REFILL_CYCLES_WIDTH                                              16
#define MAX_REFILL_CYCLES_SHIFT                                              16
#define MAX_REFILL_CYCLES_MASK                                       0xffff0000
#define MAX_REFILL_CYCLES_RD(src)                    (((src) & 0xffff0000)>>16)
#define MAX_REFILL_CYCLES_WR(src)               (((u32)(src)<<16) & 0xffff0000)
#define MAX_REFILL_CYCLES_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields READ_TIMEOUT	 */
#define READ_TIMEOUT_WIDTH                                                    4
#define READ_TIMEOUT_SHIFT                                                   12
#define READ_TIMEOUT_MASK                                            0x0000f000
#define READ_TIMEOUT_RD(src)                         (((src) & 0x0000f000)>>12)
#define READ_TIMEOUT_WR(src)                    (((u32)(src)<<12) & 0x0000f000)
#define READ_TIMEOUT_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields SAMPLE_DIV	 */
#define SAMPLE_DIV_WIDTH                                                      4
#define SAMPLE_DIV_SHIFT                                                      8
#define SAMPLE_DIV_MASK                                              0x00000f00
#define SAMPLE_DIV_RD(src)                            (((src) & 0x00000f00)>>8)
#define SAMPLE_DIV_WR(src)                       (((u32)(src)<<8) & 0x00000f00)
#define SAMPLE_DIV_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields MIN_REFILL_CYCLES	 */
#define MIN_REFILL_CYCLES_WIDTH                                               8
#define MIN_REFILL_CYCLES_SHIFT                                               0
#define MIN_REFILL_CYCLES_MASK                                       0x000000ff
#define MIN_REFILL_CYCLES_RD(src)                        (((src) & 0x000000ff))
#define MIN_REFILL_CYCLES_WR(src)                   (((u32)(src)) & 0x000000ff)
#define MIN_REFILL_CYCLES_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register TRNG_ALARMCNT	*/ 
/*	 Fields SHUTDOWN_COUNT	 */
#define SHUTDOWN_COUNT_WIDTH                                                  8
#define SHUTDOWN_COUNT_SHIFT                                                 24
#define SHUTDOWN_COUNT_MASK                                          0xff000000
#define SHUTDOWN_COUNT_RD(src)                       (((src) & 0xff000000)>>24)
#define SHUTDOWN_COUNT_WR(src)                  (((u32)(src)<<24) & 0xff000000)
#define SHUTDOWN_COUNT_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields SHUTDOWN_FATAL	 */
#define SHUTDOWN_FATAL_WIDTH                                                  1
#define SHUTDOWN_FATAL_SHIFT                                                 23
#define SHUTDOWN_FATAL_MASK                                          0x00800000
#define SHUTDOWN_FATAL_RD(src)                       (((src) & 0x00800000)>>23)
#define SHUTDOWN_FATAL_WR(src)                  (((u32)(src)<<23) & 0x00800000)
#define SHUTDOWN_FATAL_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields SHUTDOWN_THRESHOLD	 */
#define SHUTDOWN_THRESHOLD_WIDTH                                              5
#define SHUTDOWN_THRESHOLD_SHIFT                                             16
#define SHUTDOWN_THRESHOLD_MASK                                      0x001f0000
#define SHUTDOWN_THRESHOLD_RD(src)                   (((src) & 0x001f0000)>>16)
#define SHUTDOWN_THRESHOLD_WR(src)              (((u32)(src)<<16) & 0x001f0000)
#define SHUTDOWN_THRESHOLD_SET(dst,src) \
                      (((dst) & ~0x001f0000) | (((u32)(src)<<16) & 0x001f0000))
/*	 Fields STALL_RUN_POKER	 */
#define STALL_RUN_POKER_WIDTH                                                 1
#define STALL_RUN_POKER_SHIFT                                                15
#define STALL_RUN_POKER_MASK                                         0x00008000
#define STALL_RUN_POKER_RD(src)                      (((src) & 0x00008000)>>15)
#define STALL_RUN_POKER_WR(src)                 (((u32)(src)<<15) & 0x00008000)
#define STALL_RUN_POKER_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields ALARM_THRESHOLD	 */
#define ALARM_THRESHOLD_WIDTH                                                 8
#define ALARM_THRESHOLD_SHIFT                                                 0
#define ALARM_THRESHOLD_MASK                                         0x000000ff
#define ALARM_THRESHOLD_RD(src)                          (((src) & 0x000000ff))
#define ALARM_THRESHOLD_WR(src)                     (((u32)(src)) & 0x000000ff)
#define ALARM_THRESHOLD_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register TRNG_FROENABLE	*/ 
/*	 Fields FRO_ENABLES	 */
#define FRO_ENABLES_WIDTH                                                    24
#define FRO_ENABLES_SHIFT                                                     0
#define FRO_ENABLES_MASK                                             0x00ffffff
#define FRO_ENABLES_RD(src)                              (((src) & 0x00ffffff))
#define FRO_ENABLES_WR(src)                         (((u32)(src)) & 0x00ffffff)
#define FRO_ENABLES_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register TRNG_FRODETUNE	*/ 
/*	 Fields FRO_DETUNES	 */
#define FRO_DETUNES_WIDTH                                                    24
#define FRO_DETUNES_SHIFT                                                     0
#define FRO_DETUNES_MASK                                             0x00ffffff
#define FRO_DETUNES_RD(src)                              (((src) & 0x00ffffff))
#define FRO_DETUNES_WR(src)                         (((u32)(src)) & 0x00ffffff)
#define FRO_DETUNES_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register TRNG_ALARMMASK	*/ 
/*	 Fields FRO_ALARMMASKS	 */
#define FRO_ALARMMASKS_WIDTH                                                 24
#define FRO_ALARMMASKS_SHIFT                                                  0
#define FRO_ALARMMASKS_MASK                                          0x00ffffff
#define FRO_ALARMMASKS_RD(src)                           (((src) & 0x00ffffff))
#define FRO_ALARMMASKS_WR(src)                      (((u32)(src)) & 0x00ffffff)
#define FRO_ALARMMASKS_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register TRNG_ALARMSTOP	*/ 
/*	 Fields FRO_ALARMSTOPS	 */
#define FRO_ALARMSTOPS_WIDTH                                                 24
#define FRO_ALARMSTOPS_SHIFT                                                  0
#define FRO_ALARMSTOPS_MASK                                          0x00ffffff
#define FRO_ALARMSTOPS_RD(src)                           (((src) & 0x00ffffff))
#define FRO_ALARMSTOPS_WR(src)                      (((u32)(src)) & 0x00ffffff)
#define FRO_ALARMSTOPS_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register TRNG_LFSR_L	*/ 
/*	 Fields LFSR	 */
#define LFSR_WIDTH                                                           32
#define LFSR_SHIFT                                                            0
#define LFSR_MASK                                                    0xffffffff
#define LFSR_RD(src)                                     (((src) & 0xffffffff))
#define LFSR_WR(src)                                (((u32)(src)) & 0xffffffff)
#define LFSR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_LFSR_M	*/ 
/*	 Fields LFSR	 */
#define LFSR_F1_WIDTH                                                        32
#define LFSR_F1_SHIFT                                                         0
#define LFSR_F1_MASK                                                 0xffffffff
#define LFSR_F1_RD(src)                                  (((src) & 0xffffffff))
#define LFSR_F1_WR(src)                             (((u32)(src)) & 0xffffffff)
#define LFSR_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_LFSR_H	*/ 
/*	 Fields LFSR	 */
#define LFSR_F2_WIDTH                                                        17
#define LFSR_F2_SHIFT                                                         0
#define LFSR_F2_MASK                                                 0x0001ffff
#define LFSR_F2_RD(src)                                  (((src) & 0x0001ffff))
#define LFSR_F2_WR(src)                             (((u32)(src)) & 0x0001ffff)
#define LFSR_F2_SET(dst,src) \
                          (((dst) & ~0x0001ffff) | (((u32)(src)) & 0x0001ffff))

/*	Register TRNG_COUNT	*/ 
/*	 Fields SAMPLE_COUNTERS	 */
#define SAMPLE_COUNTERS_WIDTH                                                24
#define SAMPLE_COUNTERS_SHIFT                                                 0
#define SAMPLE_COUNTERS_MASK                                         0x00ffffff
#define SAMPLE_COUNTERS_RD(src)                          (((src) & 0x00ffffff))
#define SAMPLE_COUNTERS_WR(src)                     (((u32)(src)) & 0x00ffffff)
#define SAMPLE_COUNTERS_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register TRNG_KEY_PS_AI_0	*/ 
/*	 Fields KEY_PS_AI_0_RUN_CNT	 */
#define KEY_PS_AI_0_RUN_CNT0_WIDTH                                           32
#define KEY_PS_AI_0_RUN_CNT0_SHIFT                                            0
#define KEY_PS_AI_0_RUN_CNT0_MASK                                    0xffffffff
#define KEY_PS_AI_0_RUN_CNT0_RD(src)                     (((src) & 0xffffffff))
#define KEY_PS_AI_0_RUN_CNT0_WR(src)                (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_0_RUN_CNT0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_1	*/ 
/*	 Fields KEY_PS_AI_RUN_1	 */
#define KEY_PS_AI_RUN_11_WIDTH                                               32
#define KEY_PS_AI_RUN_11_SHIFT                                                0
#define KEY_PS_AI_RUN_11_MASK                                        0xffffffff
#define KEY_PS_AI_RUN_11_RD(src)                         (((src) & 0xffffffff))
#define KEY_PS_AI_RUN_11_WR(src)                    (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_RUN_11_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_2	*/ 
/*	 Fields KEY_PS_AI_RUN_2	 */
#define KEY_PS_AI_RUN_22_WIDTH                                               32
#define KEY_PS_AI_RUN_22_SHIFT                                                0
#define KEY_PS_AI_RUN_22_MASK                                        0xffffffff
#define KEY_PS_AI_RUN_22_RD(src)                         (((src) & 0xffffffff))
#define KEY_PS_AI_RUN_22_WR(src)                    (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_RUN_22_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_3	*/ 
/*	 Fields KEY_PS_AI_RUN_3	 */
#define KEY_PS_AI_RUN_33_WIDTH                                               32
#define KEY_PS_AI_RUN_33_SHIFT                                                0
#define KEY_PS_AI_RUN_33_MASK                                        0xffffffff
#define KEY_PS_AI_RUN_33_RD(src)                         (((src) & 0xffffffff))
#define KEY_PS_AI_RUN_33_WR(src)                    (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_RUN_33_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_4	*/ 
/*	 Fields KEY_PS_AI_RUN_4	 */
#define KEY_PS_AI_RUN_44_WIDTH                                               32
#define KEY_PS_AI_RUN_44_SHIFT                                                0
#define KEY_PS_AI_RUN_44_MASK                                        0xffffffff
#define KEY_PS_AI_RUN_44_RD(src)                         (((src) & 0xffffffff))
#define KEY_PS_AI_RUN_44_WR(src)                    (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_RUN_44_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_5	*/ 
/*	 Fields KEY_PS_AI_RUN_5	 */
#define KEY_PS_AI_RUN_55_WIDTH                                               32
#define KEY_PS_AI_RUN_55_SHIFT                                                0
#define KEY_PS_AI_RUN_55_MASK                                        0xffffffff
#define KEY_PS_AI_RUN_55_RD(src)                         (((src) & 0xffffffff))
#define KEY_PS_AI_RUN_55_WR(src)                    (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_RUN_55_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_6	*/ 
/*	 Fields KEY_PS_AI_RUN_UP_6	 */
#define KEY_PS_AI_RUN_UP_66_WIDTH                                            32
#define KEY_PS_AI_RUN_UP_66_SHIFT                                             0
#define KEY_PS_AI_RUN_UP_66_MASK                                     0xffffffff
#define KEY_PS_AI_RUN_UP_66_RD(src)                      (((src) & 0xffffffff))
#define KEY_PS_AI_RUN_UP_66_WR(src)                 (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_RUN_UP_66_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_KEY_PS_AI_7	*/ 
/*	 Fields KEY_PS_AI_7_MONOBIT	 */
#define KEY_PS_AI_7_MONOBIT7_WIDTH                                           32
#define KEY_PS_AI_7_MONOBIT7_SHIFT                                            0
#define KEY_PS_AI_7_MONOBIT7_MASK                                    0xffffffff
#define KEY_PS_AI_7_MONOBIT7_RD(src)                     (((src) & 0xffffffff))
#define KEY_PS_AI_7_MONOBIT7_WR(src)                (((u32)(src)) & 0xffffffff)
#define KEY_PS_AI_7_MONOBIT7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_V_0_PS_AI_8	*/ 
/*	 Fields V_0_PS_AI_8_POKER_3_0	 */
#define V_0_PS_AI_8_POKER_3_08_WIDTH                                         32
#define V_0_PS_AI_8_POKER_3_08_SHIFT                                          0
#define V_0_PS_AI_8_POKER_3_08_MASK                                  0xffffffff
#define V_0_PS_AI_8_POKER_3_08_RD(src)                   (((src) & 0xffffffff))
#define V_0_PS_AI_8_POKER_3_08_WR(src)              (((u32)(src)) & 0xffffffff)
#define V_0_PS_AI_8_POKER_3_08_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_V_1_PS_AI_9	*/ 
/*	 Fields V_1_PS_AI_9_POKER_7_4	 */
#define V_1_PS_AI_9_POKER_7_49_WIDTH                                         32
#define V_1_PS_AI_9_POKER_7_49_SHIFT                                          0
#define V_1_PS_AI_9_POKER_7_49_MASK                                  0xffffffff
#define V_1_PS_AI_9_POKER_7_49_RD(src)                   (((src) & 0xffffffff))
#define V_1_PS_AI_9_POKER_7_49_WR(src)              (((u32)(src)) & 0xffffffff)
#define V_1_PS_AI_9_POKER_7_49_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_V_2_PS_AI_10	*/ 
/*	 Fields V_2_PS_AI_10_POKER_B_8	 */
#define V_2_PS_AI_10_POKER_B_80_WIDTH                                        32
#define V_2_PS_AI_10_POKER_B_80_SHIFT                                         0
#define V_2_PS_AI_10_POKER_B_80_MASK                                 0xffffffff
#define V_2_PS_AI_10_POKER_B_80_RD(src)                  (((src) & 0xffffffff))
#define V_2_PS_AI_10_POKER_B_80_WR(src)             (((u32)(src)) & 0xffffffff)
#define V_2_PS_AI_10_POKER_B_80_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_V_3_PS_AI_11	*/ 
/*	 Fields V_3_PS_AI_11_POKER_F_C	 */
#define V_3_PS_AI_11_POKER_F_C1_WIDTH                                        32
#define V_3_PS_AI_11_POKER_F_C1_SHIFT                                         0
#define V_3_PS_AI_11_POKER_F_C1_MASK                                 0xffffffff
#define V_3_PS_AI_11_POKER_F_C1_RD(src)                  (((src) & 0xffffffff))
#define V_3_PS_AI_11_POKER_F_C1_WR(src)             (((u32)(src)) & 0xffffffff)
#define V_3_PS_AI_11_POKER_F_C1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register TRNG_TEST	*/ 
/*	 Fields TEST_IRQ	 */
#define TEST_IRQ_WIDTH                                                        1
#define TEST_IRQ_SHIFT                                                       31
#define TEST_IRQ_MASK                                                0x80000000
#define TEST_IRQ_RD(src)                             (((src) & 0x80000000)>>31)
#define TEST_IRQ_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define TEST_IRQ_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields TEST_PATTERN	 */
#define TEST_PATTERN_WIDTH                                                   12
#define TEST_PATTERN_SHIFT                                                   16
#define TEST_PATTERN_MASK                                            0x0fff0000
#define TEST_PATTERN_RD(src)                         (((src) & 0x0fff0000)>>16)
#define TEST_PATTERN_WR(src)                    (((u32)(src)<<16) & 0x0fff0000)
#define TEST_PATTERN_SET(dst,src) \
                      (((dst) & ~0x0fff0000) | (((u32)(src)<<16) & 0x0fff0000))
/*	 Fields TEST_SELECT	 */
#define TEST_SELECT_WIDTH                                                     5
#define TEST_SELECT_SHIFT                                                     8
#define TEST_SELECT_MASK                                             0x00001f00
#define TEST_SELECT_RD(src)                           (((src) & 0x00001f00)>>8)
#define TEST_SELECT_WR(src)                      (((u32)(src)<<8) & 0x00001f00)
#define TEST_SELECT_SET(dst,src) \
                       (((dst) & ~0x00001f00) | (((u32)(src)<<8) & 0x00001f00))
/*	 Fields TEST_SP_800_90	 */
#define TEST_SP_800_90_WIDTH                                                  1
#define TEST_SP_800_90_SHIFT                                                  7
#define TEST_SP_800_90_MASK                                          0x00000080
#define TEST_SP_800_90_RD(src)                        (((src) & 0x00000080)>>7)
#define TEST_SP_800_90_WR(src)                   (((u32)(src)<<7) & 0x00000080)
#define TEST_SP_800_90_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields TEST_POST_PROC	 */
#define TEST_POST_PROC_WIDTH                                                  1
#define TEST_POST_PROC_SHIFT                                                  6
#define TEST_POST_PROC_MASK                                          0x00000040
#define TEST_POST_PROC_RD(src)                        (((src) & 0x00000040)>>6)
#define TEST_POST_PROC_WR(src)                   (((u32)(src)<<6) & 0x00000040)
#define TEST_POST_PROC_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields TEST_RUN_POKER	 */
#define TEST_RUN_POKER_WIDTH                                                  1
#define TEST_RUN_POKER_SHIFT                                                  5
#define TEST_RUN_POKER_MASK                                          0x00000020
#define TEST_RUN_POKER_RD(src)                        (((src) & 0x00000020)>>5)
#define TEST_RUN_POKER_WR(src)                   (((u32)(src)<<5) & 0x00000020)
#define TEST_RUN_POKER_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields CONT_POKER	 */
#define CONT_POKER_WIDTH                                                      1
#define CONT_POKER_SHIFT                                                      4
#define CONT_POKER_MASK                                              0x00000010
#define CONT_POKER_RD(src)                            (((src) & 0x00000010)>>4)
#define CONT_POKER_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define CONT_POKER_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields NO_LFSR_FB	 */
#define NO_LFSR_FB_WIDTH                                                      1
#define NO_LFSR_FB_SHIFT                                                      3
#define NO_LFSR_FB_MASK                                              0x00000008
#define NO_LFSR_FB_RD(src)                            (((src) & 0x00000008)>>3)
#define NO_LFSR_FB_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define NO_LFSR_FB_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields TEST_PATT_DET	 */
#define TEST_PATT_DET_WIDTH                                                   1
#define TEST_PATT_DET_SHIFT                                                   2
#define TEST_PATT_DET_MASK                                           0x00000004
#define TEST_PATT_DET_RD(src)                         (((src) & 0x00000004)>>2)
#define TEST_PATT_DET_WR(src)                    (((u32)(src)<<2) & 0x00000004)
#define TEST_PATT_DET_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields TEST_PATT_FRO	 */
#define TEST_PATT_FRO_WIDTH                                                   1
#define TEST_PATT_FRO_SHIFT                                                   1
#define TEST_PATT_FRO_MASK                                           0x00000002
#define TEST_PATT_FRO_RD(src)                         (((src) & 0x00000002)>>1)
#define TEST_PATT_FRO_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define TEST_PATT_FRO_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields TEST_EN_OUT	 */
#define TEST_EN_OUT_WIDTH                                                     1
#define TEST_EN_OUT_SHIFT                                                     0
#define TEST_EN_OUT_MASK                                             0x00000001
#define TEST_EN_OUT_RD(src)                              (((src) & 0x00000001))
#define TEST_EN_OUT_WR(src)                         (((u32)(src)) & 0x00000001)
#define TEST_EN_OUT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register TRNG_BLOCKCNT	*/ 
/*	 Fields BLOCK_COUNT	 */
#define REGSPEC_BLOCK_COUNT_WIDTH                                            28
#define REGSPEC_BLOCK_COUNT_SHIFT                                             4
#define REGSPEC_BLOCK_COUNT_MASK                                     0xfffffff0
#define REGSPEC_BLOCK_COUNT_RD(src)                   (((src) & 0xfffffff0)>>4)
#define REGSPEC_BLOCK_COUNT_WR(src)              (((u32)(src)<<4) & 0xfffffff0)
#define REGSPEC_BLOCK_COUNT_SET(dst,src) \
                       (((dst) & ~0xfffffff0) | (((u32)(src)<<4) & 0xfffffff0))

/*	Register TRNG_OPTIONS	*/ 
/*	 Fields PR_TEST	 */
#define PR_TEST_WIDTH                                                         1
#define PR_TEST_SHIFT                                                        16
#define PR_TEST_MASK                                                 0x00010000
#define PR_TEST_RD(src)                              (((src) & 0x00010000)>>16)
#define PR_TEST_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields BUFFER_SIZE	 */
#define BUFFER_SIZE_WIDTH                                                     3
#define BUFFER_SIZE_SHIFT                                                    12
#define BUFFER_SIZE_MASK                                             0x00007000
#define BUFFER_SIZE_RD(src)                          (((src) & 0x00007000)>>12)
#define BUFFER_SIZE_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields NR_OF_FROS	 */
#define NR_OF_FROS_WIDTH                                                      6
#define NR_OF_FROS_SHIFT                                                      6
#define NR_OF_FROS_MASK                                              0x00000fc0
#define NR_OF_FROS_RD(src)                            (((src) & 0x00000fc0)>>6)
#define NR_OF_FROS_SET(dst,src) \
                       (((dst) & ~0x00000fc0) | (((u32)(src)<<6) & 0x00000fc0))
/*	 Fields POST_PROC_OPTION	 */
#define POST_PROC_OPTION_WIDTH                                                3
#define POST_PROC_OPTION_SHIFT                                                0
#define POST_PROC_OPTION_MASK                                        0x00000007
#define POST_PROC_OPTION_RD(src)                         (((src) & 0x00000007))
#define POST_PROC_OPTION_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register TRNG_EIP_REV	*/ 
/*	 Fields MAJOR_HW_REV	 */
#define MAJOR_HW_REV_WIDTH                                                    4
#define MAJOR_HW_REV_SHIFT                                                   24
#define MAJOR_HW_REV_MASK                                            0x0f000000
#define MAJOR_HW_REV_RD(src)                         (((src) & 0x0f000000)>>24)
#define MAJOR_HW_REV_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields MINOR_HW_REV	 */
#define MINOR_HW_REV_WIDTH                                                    4
#define MINOR_HW_REV_SHIFT                                                   20
#define MINOR_HW_REV_MASK                                            0x00f00000
#define MINOR_HW_REV_RD(src)                         (((src) & 0x00f00000)>>20)
#define MINOR_HW_REV_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields HW_PATCH_LEVEL	 */
#define HW_PATCH_LEVEL_WIDTH                                                  4
#define HW_PATCH_LEVEL_SHIFT                                                 16
#define HW_PATCH_LEVEL_MASK                                          0x000f0000
#define HW_PATCH_LEVEL_RD(src)                       (((src) & 0x000f0000)>>16)
#define HW_PATCH_LEVEL_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields BIT_INV_BASIC_EIP	 */
#define BIT_INV_BASIC_EIP_WIDTH                                               8
#define BIT_INV_BASIC_EIP_SHIFT                                               8
#define BIT_INV_BASIC_EIP_MASK                                       0x0000ff00
#define BIT_INV_BASIC_EIP_RD(src)                     (((src) & 0x0000ff00)>>8)
#define BIT_INV_BASIC_EIP_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields BASIC_EIP_NUMBER	 */
#define BASIC_EIP_NUMBER_WIDTH                                                8
#define BASIC_EIP_NUMBER_SHIFT                                                0
#define BASIC_EIP_NUMBER_MASK                                        0x000000ff
#define BASIC_EIP_NUMBER_RD(src)                         (((src) & 0x000000ff))
#define BASIC_EIP_NUMBER_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Global Base Address	*/
#define MPA_PKP_PKA_I_BASE_ADDR			0x050024000ULL

/*    Address MPA_PKP_PKA_I  Registers */
#define PKA_APTR_ADDR                                                0x00000000
#define PKA_APTR_DEFAULT                                             0x00000000
#define PKA_BPTR_ADDR                                                0x00000004
#define PKA_BPTR_DEFAULT                                             0x00000000
#define PKA_CPTR_ADDR                                                0x00000008
#define PKA_CPTR_DEFAULT                                             0x00000000
#define PKA_DPTR_ADDR                                                0x0000000c
#define PKA_DPTR_DEFAULT                                             0x00000000
#define PKA_ALENGTH_ADDR                                             0x00000010
#define PKA_ALENGTH_DEFAULT                                          0x00000000
#define PKA_BLENGTH_ADDR                                             0x00000014
#define PKA_BLENGTH_DEFAULT                                          0x00000000
#define PKA_SHIFT_ADDR                                               0x00000018
#define PKA_SHIFT_DEFAULT                                            0x00000000
#define PKA_FUNCTION_ADDR                                            0x0000001c
#define PKA_FUNCTION_DEFAULT                                         0x00000000
#define PKA_COMPARE_ADDR                                             0x00000020
#define PKA_COMPARE_DEFAULT                                          0x00000001
#define PKA_MSW_ADDR                                                 0x00000024
#define PKA_MSW_DEFAULT                                              0x00008000
#define PKA_DIVMSW_ADDR                                              0x00000028
#define PKA_DIVMSW_DEFAULT                                           0x00008000
#define PKA_SEQ_CTRL_ADDR                                            0x000000c8
#define PKA_SEQ_CTRL_DEFAULT                                         0x00000000
#define PKA_OPTIONS_ADDR                                             0x000000f4
#define PKA_OPTIONS_DEFAULT                                          0x791100a5
#define PKA_SW_REV_ADDR                                              0x000000f8
#define PKA_SW_REV_DEFAULT                                           0x00000000
#define PKA_REVISION_ADDR                                            0x000000fc
#define PKA_REVISION_DEFAULT                                         0x0151e31c

/*	Register PKA_APTR	*/ 
/*	 Fields APTR	 */
#define APTR_WIDTH                                                           11
#define APTR_SHIFT                                                            0
#define APTR_MASK                                                    0x000007ff
#define APTR_RD(src)                                     (((src) & 0x000007ff))
#define APTR_WR(src)                                (((u32)(src)) & 0x000007ff)
#define APTR_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register PKA_BPTR	*/ 
/*	 Fields BPTR	 */
#define BPTR_WIDTH                                                           11
#define BPTR_SHIFT                                                            0
#define BPTR_MASK                                                    0x000007ff
#define BPTR_RD(src)                                     (((src) & 0x000007ff))
#define BPTR_WR(src)                                (((u32)(src)) & 0x000007ff)
#define BPTR_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register PKA_CPTR	*/ 
/*	 Fields CPTR	 */
#define CPTR_WIDTH                                                           11
#define CPTR_SHIFT                                                            0
#define CPTR_MASK                                                    0x000007ff
#define CPTR_RD(src)                                     (((src) & 0x000007ff))
#define CPTR_WR(src)                                (((u32)(src)) & 0x000007ff)
#define CPTR_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register PKA_DPTR	*/ 
/*	 Fields DPTR	 */
#define DPTR_WIDTH                                                           11
#define DPTR_SHIFT                                                            0
#define DPTR_MASK                                                    0x000007ff
#define DPTR_RD(src)                                     (((src) & 0x000007ff))
#define DPTR_WR(src)                                (((u32)(src)) & 0x000007ff)
#define DPTR_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register PKA_ALENGTH	*/ 
/*	 Fields ALENGTH	 */
#define ALENGTH_WIDTH                                                         9
#define ALENGTH_SHIFT                                                         0
#define ALENGTH_MASK                                                 0x000001ff
#define ALENGTH_RD(src)                                  (((src) & 0x000001ff))
#define ALENGTH_WR(src)                             (((u32)(src)) & 0x000001ff)
#define ALENGTH_SET(dst,src) \
                          (((dst) & ~0x000001ff) | (((u32)(src)) & 0x000001ff))

/*	Register PKA_BLENGTH	*/ 
/*	 Fields BLENGTH	 */
#define BLENGTH_WIDTH                                                         9
#define BLENGTH_SHIFT                                                         0
#define BLENGTH_MASK                                                 0x000001ff
#define BLENGTH_RD(src)                                  (((src) & 0x000001ff))
#define BLENGTH_WR(src)                             (((u32)(src)) & 0x000001ff)
#define BLENGTH_SET(dst,src) \
                          (((dst) & ~0x000001ff) | (((u32)(src)) & 0x000001ff))

/*	Register PKA_SHIFT	*/ 
/*	 Fields SHIFT	 */
#define SHIFT_WIDTH                                                           5
#define SHIFT_SHIFT                                                           0
#define SHIFT_MASK                                                   0x0000001f
#define SHIFT_RD(src)                                    (((src) & 0x0000001f))
#define SHIFT_WR(src)                               (((u32)(src)) & 0x0000001f)
#define SHIFT_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register PKA_FUNCTION	*/ 
/*	 Fields STALL_RES	 */
#define STALL_RES_WIDTH                                                       1
#define STALL_RES_SHIFT                                                      24
#define STALL_RES_MASK                                               0x01000000
#define STALL_RES_RD(src)                            (((src) & 0x01000000)>>24)
#define STALL_RES_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define STALL_RES_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields RUN	 */
#define RUN_WIDTH                                                             1
#define RUN_SHIFT                                                            15
#define RUN_MASK                                                     0x00008000
#define RUN_RD(src)                                  (((src) & 0x00008000)>>15)
#define RUN_WR(src)                             (((u32)(src)<<15) & 0x00008000)
#define RUN_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields SEQ_OP	 */
#define SEQ_OP_WIDTH                                                          3
#define SEQ_OP_SHIFT                                                         12
#define SEQ_OP_MASK                                                  0x00007000
#define SEQ_OP_RD(src)                               (((src) & 0x00007000)>>12)
#define SEQ_OP_WR(src)                          (((u32)(src)<<12) & 0x00007000)
#define SEQ_OP_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields COPY	 */
#define COPY_WIDTH                                                            1
#define COPY_SHIFT                                                           11
#define COPY_MASK                                                    0x00000800
#define COPY_RD(src)                                 (((src) & 0x00000800)>>11)
#define COPY_WR(src)                            (((u32)(src)<<11) & 0x00000800)
#define COPY_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields COMPARE	 */
#define COMPARE_WIDTH                                                         1
#define COMPARE_SHIFT                                                        10
#define COMPARE_MASK                                                 0x00000400
#define COMPARE_RD(src)                              (((src) & 0x00000400)>>10)
#define COMPARE_WR(src)                         (((u32)(src)<<10) & 0x00000400)
#define COMPARE_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MODULO	 */
#define MODULO_WIDTH                                                          1
#define MODULO_SHIFT                                                          9
#define MODULO_MASK                                                  0x00000200
#define MODULO_RD(src)                                (((src) & 0x00000200)>>9)
#define MODULO_WR(src)                           (((u32)(src)<<9) & 0x00000200)
#define MODULO_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields DIVIDE	 */
#define DIVIDE_WIDTH                                                          1
#define DIVIDE_SHIFT                                                          8
#define DIVIDE_MASK                                                  0x00000100
#define DIVIDE_RD(src)                                (((src) & 0x00000100)>>8)
#define DIVIDE_WR(src)                           (((u32)(src)<<8) & 0x00000100)
#define DIVIDE_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields LSHIFT	 */
#define LSHIFT_WIDTH                                                          1
#define LSHIFT_SHIFT                                                          7
#define LSHIFT_MASK                                                  0x00000080
#define LSHIFT_RD(src)                                (((src) & 0x00000080)>>7)
#define LSHIFT_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define LSHIFT_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields RSHIFT	 */
#define RSHIFT_WIDTH                                                          1
#define RSHIFT_SHIFT                                                          6
#define RSHIFT_MASK                                                  0x00000040
#define RSHIFT_RD(src)                                (((src) & 0x00000040)>>6)
#define RSHIFT_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define RSHIFT_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields SUBTRACT	 */
#define SUBTRACT_WIDTH                                                        1
#define SUBTRACT_SHIFT                                                        5
#define SUBTRACT_MASK                                                0x00000020
#define SUBTRACT_RD(src)                              (((src) & 0x00000020)>>5)
#define SUBTRACT_WR(src)                         (((u32)(src)<<5) & 0x00000020)
#define SUBTRACT_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields ADD	 */
#define ADD_WIDTH                                                             1
#define ADD_SHIFT                                                             4
#define ADD_MASK                                                     0x00000010
#define ADD_RD(src)                                   (((src) & 0x00000010)>>4)
#define ADD_WR(src)                              (((u32)(src)<<4) & 0x00000010)
#define ADD_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MS1	 */
#define MS1_WIDTH                                                             1
#define MS1_SHIFT                                                             3
#define MS1_MASK                                                     0x00000008
#define MS1_RD(src)                                   (((src) & 0x00000008)>>3)
#define MS1_WR(src)                              (((u32)(src)<<3) & 0x00000008)
#define MS1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields ADDSUB	 */
#define ADDSUB_WIDTH                                                          1
#define ADDSUB_SHIFT                                                          1
#define ADDSUB_MASK                                                  0x00000002
#define ADDSUB_RD(src)                                (((src) & 0x00000002)>>1)
#define ADDSUB_WR(src)                           (((u32)(src)<<1) & 0x00000002)
#define ADDSUB_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MULTIPLY	 */
#define MULTIPLY_WIDTH                                                        1
#define MULTIPLY_SHIFT                                                        0
#define MULTIPLY_MASK                                                0x00000001
#define MULTIPLY_RD(src)                                 (((src) & 0x00000001))
#define MULTIPLY_WR(src)                            (((u32)(src)) & 0x00000001)
#define MULTIPLY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register PKA_COMPARE	*/ 
/*	 Fields A_GT_B	 */
#define A_GT_B_WIDTH                                                          1
#define A_GT_B_SHIFT                                                          2
#define A_GT_B_MASK                                                  0x00000004
#define A_GT_B_RD(src)                                (((src) & 0x00000004)>>2)
#define A_GT_B_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields A_LT_B	 */
#define A_LT_B_WIDTH                                                          1
#define A_LT_B_SHIFT                                                          1
#define A_LT_B_MASK                                                  0x00000002
#define A_LT_B_RD(src)                                (((src) & 0x00000002)>>1)
#define A_LT_B_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields A_EQ_B	 */
#define A_EQ_B_WIDTH                                                          1
#define A_EQ_B_SHIFT                                                          0
#define A_EQ_B_MASK                                                  0x00000001
#define A_EQ_B_RD(src)                                   (((src) & 0x00000001))
#define A_EQ_B_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register PKA_MSW	*/ 
/*	 Fields ZERO	 */
#define ZERO_WIDTH                                                            1
#define ZERO_SHIFT                                                           15
#define ZERO_MASK                                                    0x00008000
#define ZERO_RD(src)                                 (((src) & 0x00008000)>>15)
#define ZERO_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields ADDRESS	 */
#define ADDRESS_WIDTH                                                        11
#define ADDRESS_SHIFT                                                         0
#define ADDRESS_MASK                                                 0x000007ff
#define ADDRESS_RD(src)                                  (((src) & 0x000007ff))
#define ADDRESS_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register PKA_DIVMSW	*/ 
/*	 Fields ZERO	 */
#define ZERO_F1_WIDTH                                                         1
#define ZERO_F1_SHIFT                                                        15
#define ZERO_F1_MASK                                                 0x00008000
#define ZERO_F1_RD(src)                              (((src) & 0x00008000)>>15)
#define ZERO_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields ADDRESS	 */
#define ADDRESS_F1_WIDTH                                                     11
#define ADDRESS_F1_SHIFT                                                      0
#define ADDRESS_F1_MASK                                              0x000007ff
#define ADDRESS_F1_RD(src)                               (((src) & 0x000007ff))
#define ADDRESS_F1_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register PKA_SEQ_CTRL	*/ 
/*	 Fields RESET	 */
#define REGSPEC_RESET_F8_WIDTH                                                1
#define REGSPEC_RESET_F8_SHIFT                                               31
#define REGSPEC_RESET_F8_MASK                                        0x80000000
#define REGSPEC_RESET_F8_RD(src)                     (((src) & 0x80000000)>>31)
#define REGSPEC_RESET_F8_WR(src)                (((u32)(src)<<31) & 0x80000000)
#define REGSPEC_RESET_F8_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SEQ_STAT	 */
#define SEQ_STAT_WIDTH                                                        8
#define SEQ_STAT_SHIFT                                                        8
#define SEQ_STAT_MASK                                                0x0000ff00
#define SEQ_STAT_RD(src)                              (((src) & 0x0000ff00)>>8)
#define SEQ_STAT_WR(src)                         (((u32)(src)<<8) & 0x0000ff00)
#define SEQ_STAT_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields CTRL_TRIG	 */
#define CTRL_TRIG_WIDTH                                                       8
#define CTRL_TRIG_SHIFT                                                       0
#define CTRL_TRIG_MASK                                               0x000000ff
#define CTRL_TRIG_RD(src)                                (((src) & 0x000000ff))
#define CTRL_TRIG_WR(src)                           (((u32)(src)) & 0x000000ff)
#define CTRL_TRIG_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register PKA_OPTIONS	*/ 
/*	 Fields LNME_FIFO_DEPTH	 */
#define LNME_FIFO_DEPTH_WIDTH                                                 8
#define LNME_FIFO_DEPTH_SHIFT                                                24
#define LNME_FIFO_DEPTH_MASK                                         0xff000000
#define LNME_FIFO_DEPTH_RD(src)                      (((src) & 0xff000000)>>24)
#define LNME_FIFO_DEPTH_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields LNME_NUM_PE	 */
#define LNME_NUM_PE_WIDTH                                                     6
#define LNME_NUM_PE_SHIFT                                                    16
#define LNME_NUM_PE_MASK                                             0x003f0000
#define LNME_NUM_PE_RD(src)                          (((src) & 0x003f0000)>>16)
#define LNME_NUM_PE_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields MMM3A	 */
#define MMM3A_WIDTH                                                           1
#define MMM3A_SHIFT                                                          12
#define MMM3A_MASK                                                   0x00001000
#define MMM3A_RD(src)                                (((src) & 0x00001000)>>12)
#define MMM3A_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields INT_MASKING	 */
#define INT_MASKING_WIDTH                                                     1
#define INT_MASKING_SHIFT                                                    11
#define INT_MASKING_MASK                                             0x00000800
#define INT_MASKING_RD(src)                          (((src) & 0x00000800)>>11)
#define INT_MASKING_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields PROT_OPTION	 */
#define PROT_OPTION_WIDTH                                                     3
#define PROT_OPTION_SHIFT                                                     8
#define PROT_OPTION_MASK                                             0x00000700
#define PROT_OPTION_RD(src)                           (((src) & 0x00000700)>>8)
#define PROT_OPTION_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields PROGRAM_RAM	 */
#define PROGRAM_RAM_WIDTH                                                     1
#define PROGRAM_RAM_SHIFT                                                     7
#define PROGRAM_RAM_MASK                                             0x00000080
#define PROGRAM_RAM_RD(src)                           (((src) & 0x00000080)>>7)
#define PROGRAM_RAM_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SEQUENCER_CONFIG	 */
#define SEQUENCER_CONFIG_WIDTH                                                2
#define SEQUENCER_CONFIG_SHIFT                                                5
#define SEQUENCER_CONFIG_MASK                                        0x00000060
#define SEQUENCER_CONFIG_RD(src)                      (((src) & 0x00000060)>>5)
#define SEQUENCER_CONFIG_SET(dst,src) \
                       (((dst) & ~0x00000060) | (((u32)(src)<<5) & 0x00000060))
/*	 Fields LNME_CONFIG	 */
#define LNME_CONFIG_WIDTH                                                     3
#define LNME_CONFIG_SHIFT                                                     2
#define LNME_CONFIG_MASK                                             0x0000001c
#define LNME_CONFIG_RD(src)                           (((src) & 0x0000001c)>>2)
#define LNME_CONFIG_SET(dst,src) \
                       (((dst) & ~0x0000001c) | (((u32)(src)<<2) & 0x0000001c))
/*	 Fields PKCP_CONFIG	 */
#define PKCP_CONFIG_WIDTH                                                     2
#define PKCP_CONFIG_SHIFT                                                     0
#define PKCP_CONFIG_MASK                                             0x00000003
#define PKCP_CONFIG_RD(src)                              (((src) & 0x00000003))
#define PKCP_CONFIG_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register PKA_SW_REV	*/ 
/*	 Fields FIRMWARE	 */
#define FIRMWARE_WIDTH                                                        4
#define FIRMWARE_SHIFT                                                       28
#define FIRMWARE_MASK                                                0xf0000000
#define FIRMWARE_RD(src)                             (((src) & 0xf0000000)>>28)
#define FIRMWARE_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields MAJOR_FW_REV	 */
#define MAJOR_FW_REV_WIDTH                                                    4
#define MAJOR_FW_REV_SHIFT                                                   24
#define MAJOR_FW_REV_MASK                                            0x0f000000
#define MAJOR_FW_REV_RD(src)                         (((src) & 0x0f000000)>>24)
#define MAJOR_FW_REV_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields MINOR_FW_REV	 */
#define MINOR_FW_REV_WIDTH                                                    4
#define MINOR_FW_REV_SHIFT                                                   20
#define MINOR_FW_REV_MASK                                            0x00f00000
#define MINOR_FW_REV_RD(src)                         (((src) & 0x00f00000)>>20)
#define MINOR_FW_REV_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields FW_PATCH_LEVEL	 */
#define FW_PATCH_LEVEL_WIDTH                                                  4
#define FW_PATCH_LEVEL_SHIFT                                                 16
#define FW_PATCH_LEVEL_MASK                                          0x000f0000
#define FW_PATCH_LEVEL_RD(src)                       (((src) & 0x000f0000)>>16)
#define FW_PATCH_LEVEL_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))

/*	Register PKA_REVISION	*/ 
/*	 Fields MAJOR_HW_REV	 */
#define MAJOR_HW_REV_F2_WIDTH                                                 4
#define MAJOR_HW_REV_F2_SHIFT                                                24
#define MAJOR_HW_REV_F2_MASK                                         0x0f000000
#define MAJOR_HW_REV_F2_RD(src)                      (((src) & 0x0f000000)>>24)
#define MAJOR_HW_REV_F2_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields MINOR_HW_REV	 */
#define MINOR_HW_REV_F2_WIDTH                                                 4
#define MINOR_HW_REV_F2_SHIFT                                                20
#define MINOR_HW_REV_F2_MASK                                         0x00f00000
#define MINOR_HW_REV_F2_RD(src)                      (((src) & 0x00f00000)>>20)
#define MINOR_HW_REV_F2_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields HW_PATCH_LEVEL	 */
#define HW_PATCH_LEVEL_F2_WIDTH                                               4
#define HW_PATCH_LEVEL_F2_SHIFT                                              16
#define HW_PATCH_LEVEL_F2_MASK                                       0x000f0000
#define HW_PATCH_LEVEL_F2_RD(src)                    (((src) & 0x000f0000)>>16)
#define HW_PATCH_LEVEL_F2_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields BIT_INV_BASIC_EIP	 */
#define BIT_INV_BASIC_EIP_F2_WIDTH                                            8
#define BIT_INV_BASIC_EIP_F2_SHIFT                                            8
#define BIT_INV_BASIC_EIP_F2_MASK                                    0x0000ff00
#define BIT_INV_BASIC_EIP_F2_RD(src)                  (((src) & 0x0000ff00)>>8)
#define BIT_INV_BASIC_EIP_F2_SET(dst,src) \
                       (((dst) & ~0x0000ff00) | (((u32)(src)<<8) & 0x0000ff00))
/*	 Fields BASIC_EIP_NUMBER	 */
#define BASIC_EIP_NUMBER_F2_WIDTH                                             8
#define BASIC_EIP_NUMBER_F2_SHIFT                                             0
#define BASIC_EIP_NUMBER_F2_MASK                                     0x000000ff
#define BASIC_EIP_NUMBER_F2_RD(src)                      (((src) & 0x000000ff))
#define BASIC_EIP_NUMBER_F2_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Global Base Address	*/
#define MPA_CRDMA_I_BASE_ADDR			0x050040000ULL

/*    Address MPA_CRDMA_I  Registers */
#define CRDMA_VERSION_ADDR                                           0x00000000
#define CRDMA_VERSION_DEFAULT                                        0x00000010
#define CRDMA_CTRL_ADDR                                              0x00000004
#define CRDMA_CTRL_DEFAULT                                           0x00000000
#define CRDMA_CURR_BD_ADDR_ADDR                                      0x00000008
#define CRDMA_CURR_BD_ADDR_DEFAULT                                   0x00000000
#define CRDMA_BDP_ADDR_ADDR                                          0x0000000c
#define CRDMA_BDP_ADDR_DEFAULT                                       0x00000000
#define CRDMA_STATUS_ADDR                                            0x00000010
#define CRDMA_STATUS_DEFAULT                                         0x00000000
#define CRDMA_INT_SRC_ADDR                                           0x00000014
#define CRDMA_INT_SRC_DEFAULT                                        0x00000000
#define CRDMA_INT_EN_ADDR                                            0x00000018
#define CRDMA_INT_EN_DEFAULT                                         0x00000000
#define CRDMA_POLL_CTRL_ADDR                                         0x0000001c
#define CRDMA_POLL_CTRL_DEFAULT                                      0x00000000
#define CRDMA_HEADER_LEN_ADDR                                        0x00000020
#define CRDMA_HEADER_LEN_DEFAULT                                     0x00000000
#define CRDMA_TRAILER_LEN_ADDR                                       0x00000024
#define CRDMA_TRAILER_LEN_DEFAULT                                    0x00000000
#define CRDMA_DTX_STATUS_ADDR_ADDR                                   0x00000028
#define CRDMA_DTX_STATUS_ADDR_DEFAULT                                0x00000000
#define CRDMA_DRX_STATUS_ADDR_ADDR                                   0x0000002c
#define CRDMA_DRX_STATUS_ADDR_DEFAULT                                0x00000000

/*	Register CRDMA_VERSION	*/ 
/*	 Fields crdma_revision	 */
#define CRDMA_REVISION_WIDTH                                                  8
#define CRDMA_REVISION_SHIFT                                                 24
#define CRDMA_REVISION_MASK                                          0xff000000
#define CRDMA_REVISION_RD(src)                       (((src) & 0xff000000)>>24)
#define CRDMA_REVISION_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields crdma_version	 */
#define CRDMA_VERSION_WIDTH                                                   8
#define CRDMA_VERSION_SHIFT                                                  16
#define CRDMA_VERSION_MASK                                           0x00ff0000
#define CRDMA_VERSION_RD(src)                        (((src) & 0x00ff0000)>>16)
#define CRDMA_VERSION_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields crdma_id	 */
#define CRDMA_ID_WIDTH                                                       16
#define CRDMA_ID_SHIFT                                                        0
#define CRDMA_ID_MASK                                                0x0000ffff
#define CRDMA_ID_RD(src)                                 (((src) & 0x0000ffff))
#define CRDMA_ID_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CRDMA_CTRL	*/ 
/*	 Fields csr_swp_en	 */
#define CSR_SWP_EN_WIDTH                                                      1
#define CSR_SWP_EN_SHIFT                                                      5
#define CSR_SWP_EN_MASK                                              0x00000020
#define CSR_SWP_EN_RD(src)                            (((src) & 0x00000020)>>5)
#define CSR_SWP_EN_WR(src)                       (((u32)(src)<<5) & 0x00000020)
#define CSR_SWP_EN_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields csr_config_update	 */
#define CSR_CONFIG_UPDATE_WIDTH                                               1
#define CSR_CONFIG_UPDATE_SHIFT                                               4
#define CSR_CONFIG_UPDATE_MASK                                       0x00000010
#define CSR_CONFIG_UPDATE_RD(src)                     (((src) & 0x00000010)>>4)
#define CSR_CONFIG_UPDATE_WR(src)                (((u32)(src)<<4) & 0x00000010)
#define CSR_CONFIG_UPDATE_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields csr_bdp_ch_start_wstb	 */
#define CSR_BDP_CH_START_WSTB_WIDTH                                           1
#define CSR_BDP_CH_START_WSTB_SHIFT                                           2
#define CSR_BDP_CH_START_WSTB_MASK                                   0x00000004
#define CSR_BDP_CH_START_WSTB_RD(src)                 (((src) & 0x00000004)>>2)
#define CSR_BDP_CH_START_WSTB_WR(src)            (((u32)(src)<<2) & 0x00000004)
#define CSR_BDP_CH_START_WSTB_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields csr_bdp_poll_cntr_en	 */
#define CSR_BDP_POLL_CNTR_EN_WIDTH                                            1
#define CSR_BDP_POLL_CNTR_EN_SHIFT                                            1
#define CSR_BDP_POLL_CNTR_EN_MASK                                    0x00000002
#define CSR_BDP_POLL_CNTR_EN_RD(src)                  (((src) & 0x00000002)>>1)
#define CSR_BDP_POLL_CNTR_EN_WR(src)             (((u32)(src)<<1) & 0x00000002)
#define CSR_BDP_POLL_CNTR_EN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields csr_dma_en	 */
#define CSR_DMA_EN_WIDTH                                                      1
#define CSR_DMA_EN_SHIFT                                                      0
#define CSR_DMA_EN_MASK                                              0x00000001
#define CSR_DMA_EN_RD(src)                               (((src) & 0x00000001))
#define CSR_DMA_EN_WR(src)                          (((u32)(src)) & 0x00000001)
#define CSR_DMA_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CRDMA_CURR_BD_ADDR	*/ 
/*	 Fields tfdma_bdp_curr_bd_addr	 */
#define TFDMA_BDP_CURR_BD_ADDR_WIDTH                                         32
#define TFDMA_BDP_CURR_BD_ADDR_SHIFT                                          0
#define TFDMA_BDP_CURR_BD_ADDR_MASK                                  0xffffffff
#define TFDMA_BDP_CURR_BD_ADDR_RD(src)                   (((src) & 0xffffffff))
#define TFDMA_BDP_CURR_BD_ADDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CRDMA_BDP_ADDR	*/ 
/*	 Fields csr_bdp_bd_addr	 */
#define CSR_BDP_BD_ADDR_WIDTH                                                32
#define CSR_BDP_BD_ADDR_SHIFT                                                 0
#define CSR_BDP_BD_ADDR_MASK                                         0xffffffff
#define CSR_BDP_BD_ADDR_RD(src)                          (((src) & 0xffffffff))
#define CSR_BDP_BD_ADDR_WR(src)                     (((u32)(src)) & 0xffffffff)
#define CSR_BDP_BD_ADDR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CRDMA_STATUS	*/ 
/*	 Fields bdp_csr_state	 */
#define BDP_CSR_STATE_WIDTH                                                   4
#define BDP_CSR_STATE_SHIFT                                                  18
#define BDP_CSR_STATE_MASK                                           0x003c0000
#define BDP_CSR_STATE_RD(src)                        (((src) & 0x003c0000)>>18)
#define BDP_CSR_STATE_SET(dst,src) \
                      (((dst) & ~0x003c0000) | (((u32)(src)<<18) & 0x003c0000))
/*	 Fields bdp_csr_dma_start	 */
#define BDP_CSR_DMA_START_WIDTH                                               1
#define BDP_CSR_DMA_START_SHIFT                                              17
#define BDP_CSR_DMA_START_MASK                                       0x00020000
#define BDP_CSR_DMA_START_RD(src)                    (((src) & 0x00020000)>>17)
#define BDP_CSR_DMA_START_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields bdp_csr_dma_actv	 */
#define BDP_CSR_DMA_ACTV_WIDTH                                                1
#define BDP_CSR_DMA_ACTV_SHIFT                                               16
#define BDP_CSR_DMA_ACTV_MASK                                        0x00010000
#define BDP_CSR_DMA_ACTV_RD(src)                     (((src) & 0x00010000)>>16)
#define BDP_CSR_DMA_ACTV_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields bdp_csr_bdctrl	 */
#define BDP_CSR_BDCTRL_WIDTH                                                 16
#define BDP_CSR_BDCTRL_SHIFT                                                  0
#define BDP_CSR_BDCTRL_MASK                                          0x0000ffff
#define BDP_CSR_BDCTRL_RD(src)                           (((src) & 0x0000ffff))
#define BDP_CSR_BDCTRL_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CRDMA_INT_SRC	*/ 
/*	 Fields bdp_csr_pkt_int	 */
#define BDP_CSR_PKT_INT_WIDTH                                                 1
#define BDP_CSR_PKT_INT_SHIFT                                                 2
#define BDP_CSR_PKT_INT_MASK                                         0x00000004
#define BDP_CSR_PKT_INT_RD(src)                       (((src) & 0x00000004)>>2)
#define BDP_CSR_PKT_INT_WR(src)                  (((u32)(src)<<2) & 0x00000004)
#define BDP_CSR_PKT_INT_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields bdp_csr_cbd_int	 */
#define BDP_CSR_CBD_INT_WIDTH                                                 1
#define BDP_CSR_CBD_INT_SHIFT                                                 1
#define BDP_CSR_CBD_INT_MASK                                         0x00000002
#define BDP_CSR_CBD_INT_RD(src)                       (((src) & 0x00000002)>>1)
#define BDP_CSR_CBD_INT_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define BDP_CSR_CBD_INT_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields crdma_int	 */
#define CRDMA_INT_WIDTH                                                       1
#define CRDMA_INT_SHIFT                                                       0
#define CRDMA_INT_MASK                                               0x00000001
#define CRDMA_INT_RD(src)                                (((src) & 0x00000001))
#define CRDMA_INT_WR(src)                           (((u32)(src)) & 0x00000001)
#define CRDMA_INT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CRDMA_INT_EN	*/ 
/*	 Fields bdp_csr_pkt_int_en	 */
#define BDP_CSR_PKT_INT_EN_WIDTH                                              1
#define BDP_CSR_PKT_INT_EN_SHIFT                                              2
#define BDP_CSR_PKT_INT_EN_MASK                                      0x00000004
#define BDP_CSR_PKT_INT_EN_RD(src)                    (((src) & 0x00000004)>>2)
#define BDP_CSR_PKT_INT_EN_WR(src)               (((u32)(src)<<2) & 0x00000004)
#define BDP_CSR_PKT_INT_EN_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields bdp_csr_cbd_int_en	 */
#define BDP_CSR_CBD_INT_EN_WIDTH                                              1
#define BDP_CSR_CBD_INT_EN_SHIFT                                              1
#define BDP_CSR_CBD_INT_EN_MASK                                      0x00000002
#define BDP_CSR_CBD_INT_EN_RD(src)                    (((src) & 0x00000002)>>1)
#define BDP_CSR_CBD_INT_EN_WR(src)               (((u32)(src)<<1) & 0x00000002)
#define BDP_CSR_CBD_INT_EN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields crdma_int_en	 */
#define CRDMA_INT_EN_WIDTH                                                    1
#define CRDMA_INT_EN_SHIFT                                                    0
#define CRDMA_INT_EN_MASK                                            0x00000001
#define CRDMA_INT_EN_RD(src)                             (((src) & 0x00000001))
#define CRDMA_INT_EN_WR(src)                        (((u32)(src)) & 0x00000001)
#define CRDMA_INT_EN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CRDMA_POLL_CTRL	*/ 
/*	 Fields csr_bdp_poll_cntr	 */
#define CSR_BDP_POLL_CNTR_WIDTH                                              16
#define CSR_BDP_POLL_CNTR_SHIFT                                               0
#define CSR_BDP_POLL_CNTR_MASK                                       0x0000ffff
#define CSR_BDP_POLL_CNTR_RD(src)                        (((src) & 0x0000ffff))
#define CSR_BDP_POLL_CNTR_WR(src)                   (((u32)(src)) & 0x0000ffff)
#define CSR_BDP_POLL_CNTR_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CRDMA_HEADER_LEN	*/ 
/*	 Fields csr_hdr_len	 */
#define CSR_HDR_LEN_WIDTH                                                     8
#define CSR_HDR_LEN_SHIFT                                                     0
#define CSR_HDR_LEN_MASK                                             0x000000ff
#define CSR_HDR_LEN_RD(src)                              (((src) & 0x000000ff))
#define CSR_HDR_LEN_WR(src)                         (((u32)(src)) & 0x000000ff)
#define CSR_HDR_LEN_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register CRDMA_TRAILER_LEN	*/ 
/*	 Fields csr_trlr_len	 */
#define CSR_TRLR_LEN_WIDTH                                                    8
#define CSR_TRLR_LEN_SHIFT                                                    0
#define CSR_TRLR_LEN_MASK                                            0x000000ff
#define CSR_TRLR_LEN_RD(src)                             (((src) & 0x000000ff))
#define CSR_TRLR_LEN_WR(src)                        (((u32)(src)) & 0x000000ff)
#define CSR_TRLR_LEN_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register CRDMA_DTX_STATUS_ADDR	*/ 
/*	 Fields dtx_csr_curr_buf_len	 */
#define DTX_CSR_CURR_BUF_LEN_WIDTH                                           16
#define DTX_CSR_CURR_BUF_LEN_SHIFT                                            4
#define DTX_CSR_CURR_BUF_LEN_MASK                                    0x000ffff0
#define DTX_CSR_CURR_BUF_LEN_RD(src)                  (((src) & 0x000ffff0)>>4)
#define DTX_CSR_CURR_BUF_LEN_SET(dst,src) \
                       (((dst) & ~0x000ffff0) | (((u32)(src)<<4) & 0x000ffff0))
/*	 Fields dtx_csr_state	 */
#define DTX_CSR_STATE_WIDTH                                                   4
#define DTX_CSR_STATE_SHIFT                                                   0
#define DTX_CSR_STATE_MASK                                           0x0000000f
#define DTX_CSR_STATE_RD(src)                            (((src) & 0x0000000f))
#define DTX_CSR_STATE_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register CRDMA_DRX_STATUS_ADDR	*/ 
/*	 Fields drx_csr_curr_buf_len	 */
#define DRX_CSR_CURR_BUF_LEN_WIDTH                                           16
#define DRX_CSR_CURR_BUF_LEN_SHIFT                                            4
#define DRX_CSR_CURR_BUF_LEN_MASK                                    0x000ffff0
#define DRX_CSR_CURR_BUF_LEN_RD(src)                  (((src) & 0x000ffff0)>>4)
#define DRX_CSR_CURR_BUF_LEN_SET(dst,src) \
                       (((dst) & ~0x000ffff0) | (((u32)(src)<<4) & 0x000ffff0))
/*	 Fields drx_csr_state	 */
#define DRX_CSR_STATE_WIDTH                                                   4
#define DRX_CSR_STATE_SHIFT                                                   0
#define DRX_CSR_STATE_MASK                                           0x0000000f
#define DRX_CSR_STATE_RD(src)                            (((src) & 0x0000000f))
#define DRX_CSR_STATE_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Global Base Address	*/
#define MPA_DB9_CSR_I_BASE_ADDR			0x010549000ULL
#define MPA_DB8_CSR_I_BASE_ADDR			0x010548000ULL
#define MPA_DB7_CSR_I_BASE_ADDR			0x010547000ULL
#define MPA_DB6_CSR_I_BASE_ADDR			0x010546000ULL
#define MPA_DB5_CSR_I_BASE_ADDR			0x010545000ULL
#define MPA_DB4_CSR_I_BASE_ADDR			0x010544000ULL
#define MPA_DB3_CSR_I_BASE_ADDR			0x010543000ULL
#define MPA_DB2_CSR_I_BASE_ADDR			0x010542000ULL
#define MPA_DB1_CSR_I_BASE_ADDR			0x010541000ULL
#define MPA_DB0_CSR_I_BASE_ADDR			0x010540000ULL

/*    Address MPA_DB0_CSR_I  Registers */
#define AGENT_DB_IN_ADDR                                             0x00000000
#define AGENT_DB_IN_DEFAULT                                          0x00000000
#define AGENT_DB_DIN0_ADDR                                           0x00000004
#define AGENT_DB_DIN0_DEFAULT                                        0x00000000
#define AGENT_DB_DIN1_ADDR                                           0x00000008
#define AGENT_DB_DIN1_DEFAULT                                        0x00000000
#define AGENT_DB_OUT_ADDR                                            0x00000010
#define AGENT_DB_OUT_DEFAULT                                         0x00000000
#define AGENT_DB_DOUT0_ADDR                                          0x00000014
#define AGENT_DB_DOUT0_DEFAULT                                       0x00000000
#define AGENT_DB_DOUT1_ADDR                                          0x00000018
#define AGENT_DB_DOUT1_DEFAULT                                       0x00000000
#define AGENT_DB_STATUS_ADDR                                         0x00000020
#define AGENT_DB_STATUS_DEFAULT                                      0x00000000
#define AGENT_DB_STATUSMASK_ADDR                                     0x00000024
#define AGENT_DB_RESUME_ADDR                                         0x00000028
#define AGENT_DB_RESUME_DEFAULT                                      0x00000000
#define AGENT_DB_SPMODE_ADDR                                         0x0000002c
#define AGENT_DB_SPMODE_DEFAULT                                      0x00000000

/*	Register AGENT_DB_IN	*/ 
/*	 Fields DB_IN	 */
#define DB_IN_F20_WIDTH                                                      32
#define DB_IN_F20_SHIFT                                                       0
#define DB_IN_F20_MASK                                               0xffffffff
#define DB_IN_F20_RD(src)                                (((src) & 0xffffffff))
#define DB_IN_F20_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_DIN0	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN0_F20_WIDTH                                                    32
#define DB_DIN0_F20_SHIFT                                                     0
#define DB_DIN0_F20_MASK                                             0xffffffff
#define DB_DIN0_F20_RD(src)                              (((src) & 0xffffffff))
#define DB_DIN0_F20_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_DIN1	*/ 
/*	 Fields DB_DIN	 */
#define DB_DIN1_F20_WIDTH                                                    32
#define DB_DIN1_F20_SHIFT                                                     0
#define DB_DIN1_F20_MASK                                             0xffffffff
#define DB_DIN1_F20_RD(src)                              (((src) & 0xffffffff))
#define DB_DIN1_F20_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_OUT	*/ 
/*	 Fields DB_OUT	 */
#define DB_OUT_F20_WIDTH                                                     32
#define DB_OUT_F20_SHIFT                                                      0
#define DB_OUT_F20_MASK                                              0xffffffff
#define DB_OUT_F20_RD(src)                               (((src) & 0xffffffff))
#define DB_OUT_F20_WR(src)                          (((u32)(src)) & 0xffffffff)
#define DB_OUT_F20_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_DOUT0	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT0_F20_WIDTH                                                   32
#define DB_DOUT0_F20_SHIFT                                                    0
#define DB_DOUT0_F20_MASK                                            0xffffffff
#define DB_DOUT0_F20_RD(src)                             (((src) & 0xffffffff))
#define DB_DOUT0_F20_WR(src)                        (((u32)(src)) & 0xffffffff)
#define DB_DOUT0_F20_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_DOUT1	*/ 
/*	 Fields DB_DOUT	 */
#define DB_DOUT1_F20_WIDTH                                                   32
#define DB_DOUT1_F20_SHIFT                                                    0
#define DB_DOUT1_F20_MASK                                            0xffffffff
#define DB_DOUT1_F20_RD(src)                             (((src) & 0xffffffff))
#define DB_DOUT1_F20_WR(src)                        (((u32)(src)) & 0xffffffff)
#define DB_DOUT1_F20_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_STATUS	*/ 
/*	 Fields DB_AVAIL	 */
#define DB_AVAIL_WIDTH                                                        1
#define DB_AVAIL_SHIFT                                                       16
#define DB_AVAIL_MASK                                                0x00010000
#define DB_AVAIL_RD(src)                             (((src) & 0x00010000)>>16)
#define DB_AVAIL_WR(src)                        (((u32)(src)<<16) & 0x00010000)
#define DB_AVAIL_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields DB_ACK	 */
#define DB_ACK_WIDTH                                                          1
#define DB_ACK_SHIFT                                                          0
#define DB_ACK_MASK                                                  0x00000001
#define DB_ACK_RD(src)                                   (((src) & 0x00000001))
#define DB_ACK_WR(src)                              (((u32)(src)) & 0x00000001)
#define DB_ACK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AGENT_DB_STATUSMask	*/
/*    Mask Register Fields DB_AVAILMask    */
#define DB_AVAILMASK_WIDTH                                                    1
#define DB_AVAILMASK_SHIFT                                                   16
#define DB_AVAILMASK_MASK                                            0x00010000
#define DB_AVAILMASK_RD(src)                         (((src) & 0x00010000)>>16)
#define DB_AVAILMASK_WR(src)                    (((u32)(src)<<16) & 0x00010000)
#define DB_AVAILMASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields DB_ACKMask    */
#define DB_ACKMASK_WIDTH                                                      1
#define DB_ACKMASK_SHIFT                                                      0
#define DB_ACKMASK_MASK                                              0x00000001
#define DB_ACKMASK_RD(src)                               (((src) & 0x00000001))
#define DB_ACKMASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define DB_ACKMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register AGENT_DB_RESUME	*/ 
/*	 Fields RESUME	 */
#define RESUME_WIDTH                                                         32
#define RESUME_SHIFT                                                          0
#define RESUME_MASK                                                  0xffffffff
#define RESUME_RD(src)                                   (((src) & 0xffffffff))
#define RESUME_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register AGENT_DB_SPMODE	*/ 
/*	 Fields MODE	 */
#define REGSPEC_MODE_F4_WIDTH                                                32
#define REGSPEC_MODE_F4_SHIFT                                                 0
#define REGSPEC_MODE_F4_MASK                                         0xffffffff
#define REGSPEC_MODE_F4_RD(src)                          (((src) & 0xffffffff))
#define REGSPEC_MODE_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*    Address MPA_DB1_CSR_I  Registers */

/*    Address MPA_DB2_CSR_I  Registers */

/*    Address MPA_DB3_CSR_I  Registers */

/*    Address MPA_DB4_CSR_I  Registers */

/*    Address MPA_DB5_CSR_I  Registers */

/*    Address MPA_DB6_CSR_I  Registers */

/*    Address MPA_DB7_CSR_I  Registers */

/*    Address MPA_DB8_CSR_I  Registers */

/*    Address MPA_DB9_CSR_I  Registers */

/*	Global Base Address	*/
#define MPA_EFUSE_SHADOW_CSR_I_BASE_ADDR			0x01054a000ULL

/*    Address MPA_EFUSE_SHADOW_CSR_I  Registers */
#define SOC_EFUSE0_SHADOW_ADDR                                       0x00000000
#define SOC_EFUSE0_SHADOW_DEFAULT                                    0x00000000
#define SOC_EFUSE1_SHADOW_ADDR                                       0x00000004
#define SOC_EFUSE1_SHADOW_DEFAULT                                    0x00000000
#define SOC_ECID0_SHADOW_ADDR                                        0x00000008
#define SOC_ECID0_SHADOW_DEFAULT                                     0x00000000
#define SOC_ECID1_SHADOW_ADDR                                        0x0000000c
#define SOC_ECID1_SHADOW_DEFAULT                                     0x00000000
#define SOC_ECID2_SHADOW_ADDR                                        0x00000010
#define SOC_ECID2_SHADOW_DEFAULT                                     0x00000000
#define SOC_ECID3_SHADOW_ADDR                                        0x00000014
#define SOC_ECID3_SHADOW_DEFAULT                                     0x00000000
#define SOC_JTAG1_SHADOW_ADDR                                        0x00000018
#define SOC_JTAG1_SHADOW_DEFAULT                                     0x00000000

/*	Register SOC_EFUSE0_SHADOW	*/ 
/*	 Fields SW_VERSION	 */
#define SW_VERSION_F2_WIDTH                                                   8
#define SW_VERSION_F2_SHIFT                                                  24
#define SW_VERSION_F2_MASK                                           0xff000000
#define SW_VERSION_F2_RD(src)                        (((src) & 0xff000000)>>24)
#define SW_VERSION_F2_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields EFUSE23_21	 */
#define EFUSE23_21_F2_WIDTH                                                   2
#define EFUSE23_21_F2_SHIFT                                                  22
#define EFUSE23_21_F2_MASK                                           0x00c00000
#define EFUSE23_21_F2_RD(src)                        (((src) & 0x00c00000)>>22)
#define EFUSE23_21_F2_SET(dst,src) \
                      (((dst) & ~0x00c00000) | (((u32)(src)<<22) & 0x00c00000))
/*	 Fields MPA_SEC_DISABLE	 */
#define MPA_SEC_DISABLE_F2_WIDTH                                              1
#define MPA_SEC_DISABLE_F2_SHIFT                                             21
#define MPA_SEC_DISABLE_F2_MASK                                      0x00200000
#define MPA_SEC_DISABLE_F2_RD(src)                   (((src) & 0x00200000)>>21)
#define MPA_SEC_DISABLE_F2_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields SATA_BYPASS	 */
#define SATA_BYPASS_F2_WIDTH                                                  1
#define SATA_BYPASS_F2_SHIFT                                                 20
#define SATA_BYPASS_F2_MASK                                          0x00100000
#define SATA_BYPASS_F2_RD(src)                       (((src) & 0x00100000)>>20)
#define SATA_BYPASS_F2_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields OTP_DISABLE	 */
#define OTP_DISABLE_F2_WIDTH                                                  1
#define OTP_DISABLE_F2_SHIFT                                                 19
#define OTP_DISABLE_F2_MASK                                          0x00080000
#define OTP_DISABLE_F2_RD(src)                       (((src) & 0x00080000)>>19)
#define OTP_DISABLE_F2_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC_DISABLE	 */
#define SEC_DISABLE_F2_WIDTH                                                  1
#define SEC_DISABLE_F2_SHIFT                                                 18
#define SEC_DISABLE_F2_MASK                                          0x00040000
#define SEC_DISABLE_F2_RD(src)                       (((src) & 0x00040000)>>18)
#define SEC_DISABLE_F2_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields TPM_CFG	 */
#define TPM_CFG_F2_WIDTH                                                      2
#define TPM_CFG_F2_SHIFT                                                     16
#define TPM_CFG_F2_MASK                                              0x00030000
#define TPM_CFG_F2_RD(src)                           (((src) & 0x00030000)>>16)
#define TPM_CFG_F2_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields EFUSE15_4	 */
#define EFUSE15_4_F2_WIDTH                                                   12
#define EFUSE15_4_F2_SHIFT                                                    4
#define EFUSE15_4_F2_MASK                                            0x0000fff0
#define EFUSE15_4_F2_RD(src)                          (((src) & 0x0000fff0)>>4)
#define EFUSE15_4_F2_SET(dst,src) \
                       (((dst) & ~0x0000fff0) | (((u32)(src)<<4) & 0x0000fff0))
/*	 Fields PMD3_DISABLE	 */
#define PMD3_DISABLE_F2_WIDTH                                                 1
#define PMD3_DISABLE_F2_SHIFT                                                 3
#define PMD3_DISABLE_F2_MASK                                         0x00000008
#define PMD3_DISABLE_F2_RD(src)                       (((src) & 0x00000008)>>3)
#define PMD3_DISABLE_F2_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields PMD2_DISABLE	 */
#define PMD2_DISABLE_F2_WIDTH                                                 1
#define PMD2_DISABLE_F2_SHIFT                                                 2
#define PMD2_DISABLE_F2_MASK                                         0x00000004
#define PMD2_DISABLE_F2_RD(src)                       (((src) & 0x00000004)>>2)
#define PMD2_DISABLE_F2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields PMD1_DISABLE	 */
#define PMD1_DISABLE_F2_WIDTH                                                 1
#define PMD1_DISABLE_F2_SHIFT                                                 1
#define PMD1_DISABLE_F2_MASK                                         0x00000002
#define PMD1_DISABLE_F2_RD(src)                       (((src) & 0x00000002)>>1)
#define PMD1_DISABLE_F2_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields PMD0_DISABLE	 */
#define PMD0_DISABLE_F2_WIDTH                                                 1
#define PMD0_DISABLE_F2_SHIFT                                                 0
#define PMD0_DISABLE_F2_MASK                                         0x00000001
#define PMD0_DISABLE_F2_RD(src)                          (((src) & 0x00000001))
#define PMD0_DISABLE_F2_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register SOC_EFUSE1_SHADOW	*/ 
/*	 Fields EFUSE63_32	 */
#define EFUSE63_32_WIDTH                                                      3
#define EFUSE63_32_SHIFT                                                     29
#define EFUSE63_32_MASK                                              0xe0000000
#define EFUSE63_32_RD(src)                           (((src) & 0xe0000000)>>29)
#define EFUSE63_32_SET(dst,src) \
                      (((dst) & ~0xe0000000) | (((u32)(src)<<29) & 0xe0000000))
/*	 Fields SOC_DBG_DIS_PREAUTH	 */
#define SOC_DBG_DIS_PREAUTH_WIDTH                                             1
#define SOC_DBG_DIS_PREAUTH_SHIFT                                            28
#define SOC_DBG_DIS_PREAUTH_MASK                                     0x10000000
#define SOC_DBG_DIS_PREAUTH_RD(src)                  (((src) & 0x10000000)>>28)
#define SOC_DBG_DIS_PREAUTH_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SOC_DBG_DIS_PERM	 */
#define SOC_DBG_DIS_PERM_WIDTH                                                1
#define SOC_DBG_DIS_PERM_SHIFT                                               27
#define SOC_DBG_DIS_PERM_MASK                                        0x08000000
#define SOC_DBG_DIS_PERM_RD(src)                     (((src) & 0x08000000)>>27)
#define SOC_DBG_DIS_PERM_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields TMM_DBG_DIS_PREAUTH	 */
#define TMM_DBG_DIS_PREAUTH_WIDTH                                             1
#define TMM_DBG_DIS_PREAUTH_SHIFT                                            26
#define TMM_DBG_DIS_PREAUTH_MASK                                     0x04000000
#define TMM_DBG_DIS_PREAUTH_RD(src)                  (((src) & 0x04000000)>>26)
#define TMM_DBG_DIS_PREAUTH_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields TMM_DBG_DIS_PERM	 */
#define TMM_DBG_DIS_PERM_WIDTH                                                1
#define TMM_DBG_DIS_PERM_SHIFT                                               25
#define TMM_DBG_DIS_PERM_MASK                                        0x02000000
#define TMM_DBG_DIS_PERM_RD(src)                     (((src) & 0x02000000)>>25)
#define TMM_DBG_DIS_PERM_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SW_TMM	 */
#define SW_TMM_WIDTH                                                         20
#define SW_TMM_SHIFT                                                          5
#define SW_TMM_MASK                                                  0x01ffffe0
#define SW_TMM_RD(src)                                (((src) & 0x01ffffe0)>>5)
#define SW_TMM_SET(dst,src) \
                       (((dst) & ~0x01ffffe0) | (((u32)(src)<<5) & 0x01ffffe0))
/*	 Fields EFUSE36_32	 */
#define EFUSE36_32_WIDTH                                                      5
#define EFUSE36_32_SHIFT                                                      0
#define EFUSE36_32_MASK                                              0x0000001f
#define EFUSE36_32_RD(src)                               (((src) & 0x0000001f))
#define EFUSE36_32_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register SOC_ECID0_SHADOW	*/ 
/*	 Fields ECID	 */
#define ECID_WIDTH                                                           32
#define ECID_SHIFT                                                            0
#define ECID_MASK                                                    0xffffffff
#define ECID_RD(src)                                     (((src) & 0xffffffff))
#define ECID_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SOC_ECID1_SHADOW	*/ 
/*	 Fields ECID	 */
#define ECID_F1_WIDTH                                                        32
#define ECID_F1_SHIFT                                                         0
#define ECID_F1_MASK                                                 0xffffffff
#define ECID_F1_RD(src)                                  (((src) & 0xffffffff))
#define ECID_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SOC_ECID2_SHADOW	*/ 
/*	 Fields ECID	 */
#define ECID_F2_WIDTH                                                        32
#define ECID_F2_SHIFT                                                         0
#define ECID_F2_MASK                                                 0xffffffff
#define ECID_F2_RD(src)                                  (((src) & 0xffffffff))
#define ECID_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SOC_ECID3_SHADOW	*/ 
/*	 Fields ECID	 */
#define ECID_F3_WIDTH                                                        32
#define ECID_F3_SHIFT                                                         0
#define ECID_F3_MASK                                                 0xffffffff
#define ECID_F3_RD(src)                                  (((src) & 0xffffffff))
#define ECID_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register SOC_JTAG1_SHADOW	*/ 
/*	 Fields JTAG1	 */
#define JTAG1_WIDTH                                                          32
#define JTAG1_SHIFT                                                           0
#define JTAG1_MASK                                                   0xffffffff
#define JTAG1_RD(src)                                    (((src) & 0xffffffff))
#define JTAG1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define ACPI7_CSR_I_BASE_ADDR			0x010557000ULL
#define ACPI6_CSR_I_BASE_ADDR			0x010556000ULL
#define ACPI5_CSR_I_BASE_ADDR			0x010555000ULL
#define ACPI4_CSR_I_BASE_ADDR			0x010554000ULL
#define ACPI3_CSR_I_BASE_ADDR			0x010553000ULL
#define ACPI2_CSR_I_BASE_ADDR			0x010552000ULL
#define ACPI1_CSR_I_BASE_ADDR			0x010551000ULL
#define ACPI0_CSR_I_BASE_ADDR			0x010550000ULL

/*    Address ACPI0_CSR_I  Registers */
#define ACPI_PCTL_ADDR                                                0x00000000
#define ACPI_PCTL_DEFAULT                                             0x00000000
#define ACPI_PSTS_ADDR                                                0x00000004
#define ACPI_PSTS_DEFAULT                                             0x00000000
#define ACPI_RO0_ADDR                                                0x00000010
#define ACPI_RO0_DEFAULT                                             0x00000000
#define ACPI_RO1_ADDR                                                0x00000014
#define ACPI_RO1_DEFAULT                                             0x00000000
#define ACPI_RO2_ADDR                                                0x00000018
#define ACPI_RO2_DEFAULT                                             0x00000000
#define ACPI_RO3_ADDR                                                0x0000001c
#define ACPI_RO3_DEFAULT                                             0x00000000
#define ACPI_RO4_ADDR                                                0x00000020
#define ACPI_RO4_DEFAULT                                             0x00000000

/*	Register ACPI_CTL	*/ 
/*	 Fields RW_DATA	 */
#define RW_DATA_WIDTH                                                        32
#define RW_DATA_SHIFT                                                         0
#define RW_DATA_MASK                                                 0xffffffff
#define RW_DATA_RD(src)                                  (((src) & 0xffffffff))
#define RW_DATA_WR(src)                             (((u32)(src)) & 0xffffffff)
#define RW_DATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_STS	*/ 
/*	 Fields RO_DATA	 */
#define RO_DATA_WIDTH                                                        32
#define RO_DATA_SHIFT                                                         0
#define RO_DATA_MASK                                                 0xffffffff
#define RO_DATA_RD(src)                                  (((src) & 0xffffffff))
#define RO_DATA_WR(src)                             (((u32)(src)) & 0xffffffff)
#define RO_DATA_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_RO0	*/ 
/*	 Fields RO_DATA	 */
#define RO_DATA0_WIDTH                                                       32
#define RO_DATA0_SHIFT                                                        0
#define RO_DATA0_MASK                                                0xffffffff
#define RO_DATA0_RD(src)                                 (((src) & 0xffffffff))
#define RO_DATA0_WR(src)                            (((u32)(src)) & 0xffffffff)
#define RO_DATA0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_RO1	*/ 
/*	 Fields RO_DATA	 */
#define RO_DATA1_WIDTH                                                       32
#define RO_DATA1_SHIFT                                                        0
#define RO_DATA1_MASK                                                0xffffffff
#define RO_DATA1_RD(src)                                 (((src) & 0xffffffff))
#define RO_DATA1_WR(src)                            (((u32)(src)) & 0xffffffff)
#define RO_DATA1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_RO2	*/ 
/*	 Fields RO_DATA	 */
#define RO_DATA2_WIDTH                                                       32
#define RO_DATA2_SHIFT                                                        0
#define RO_DATA2_MASK                                                0xffffffff
#define RO_DATA2_RD(src)                                 (((src) & 0xffffffff))
#define RO_DATA2_WR(src)                            (((u32)(src)) & 0xffffffff)
#define RO_DATA2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_RO3	*/ 
/*	 Fields RO_DATA	 */
#define RO_DATA3_WIDTH                                                       32
#define RO_DATA3_SHIFT                                                        0
#define RO_DATA3_MASK                                                0xffffffff
#define RO_DATA3_RD(src)                                 (((src) & 0xffffffff))
#define RO_DATA3_WR(src)                            (((u32)(src)) & 0xffffffff)
#define RO_DATA3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_RO4	*/ 
/*	 Fields RO_DATA	 */
#define RO_DATA4_WIDTH                                                       32
#define RO_DATA4_SHIFT                                                        0
#define RO_DATA4_MASK                                                0xffffffff
#define RO_DATA4_RD(src)                                 (((src) & 0xffffffff))
#define RO_DATA4_WR(src)                            (((u32)(src)) & 0xffffffff)
#define RO_DATA4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*    Address ACPI1_CSR_I  Registers */

/*    Address ACPI2_CSR_I  Registers */

/*    Address ACPI3_CSR_I  Registers */

/*    Address ACPI4_CSR_I  Registers */

/*    Address ACPI5_CSR_I  Registers */

/*    Address ACPI6_CSR_I  Registers */

/*    Address ACPI7_CSR_I  Registers */

/*	Global Base Address	*/
#define ACPI_W1C_CSR_I_BASE_ADDR			0x010558000ULL

/*    Address ACPI_W1C_CSR_I  Registers */
#define ACPI_W1C_ADDR                                                0x00000000
#define ACPI_W1C_DEFAULT                                             0x00000000
#define ACPI_EN_ADDR                                                 0x00000004
#define ACPI_EN_DEFAULT                                              0x00000000
#define ACPI_CNT_ADDR                                                0x00000008
#define ACPI_CNT_DEFAULT                                             0x00000000

/*	Register ACPI_W1C	*/ 
/*	 Fields W1C	 */
#define W1C_WIDTH                                                            16
#define W1C_SHIFT                                                             0
#define W1C_MASK                                                     0x0000ffff
#define W1C_RD(src)                                      (((src) & 0x0000ffff))
#define W1C_WR(src)                                 (((u32)(src)) & 0x0000ffff)
#define W1C_SET(dst,src) (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register ACPI_EN	*/ 
/*	 Fields RW_DATA	 */
#define RW_DATA_F16_WIDTH                                                    32
#define RW_DATA_F16_SHIFT                                                     0
#define RW_DATA_F16_MASK                                             0xffffffff
#define RW_DATA_F16_RD(src)                              (((src) & 0xffffffff))
#define RW_DATA_F16_WR(src)                         (((u32)(src)) & 0xffffffff)
#define RW_DATA_F16_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register ACPI_CNT	*/ 
/*	 Fields RW_DATA	 */
#define RW_DATA_F17_WIDTH                                                    32
#define RW_DATA_F17_SHIFT                                                     0
#define RW_DATA_F17_MASK                                             0xffffffff
#define RW_DATA_F17_RD(src)                              (((src) & 0xffffffff))
#define RW_DATA_F17_WR(src)                         (((u32)(src)) & 0xffffffff)
#define RW_DATA_F17_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define MPA_GC_CTRL_I_BASE_ADDR			0x010580000ULL

/*    Address MPA_GC_CTRL_I  Registers */
#define CNTCR_ADDR                                                   0x00000000
#define CNTCR_DEFAULT                                                0x00000000
#define CNTSR_ADDR                                                   0x00000004
#define CNTSR_DEFAULT                                                0x00000000
#define CNTCVL_ADDR                                                  0x00000008
#define CNTCVL_DEFAULT                                               0x00000000
#define CNTCVH_ADDR                                                  0x0000000c
#define CNTCVH_DEFAULT                                               0x00000000
#define CNTFID0_ADDR                                                 0x00000020
#define CNTFID0_DEFAULT                                              0x0ee6b280
#define CNTFID1_ADDR                                                 0x00000024
#define CNTFID1_DEFAULT                                              0x01dcd650
#define CNTFID2_ADDR                                                 0x00000028
#define CNTFID2_DEFAULT                                              0x003b9aca
#define PIDR4_ADDR                                                   0x00000fd0
#define PIDR4_DEFAULT                                                0x00000000
#define PIDR0_ADDR                                                   0x00000fe0
#define PIDR0_DEFAULT                                                0x00000000
#define PIDR1_ADDR                                                   0x00000fe4
#define PIDR1_DEFAULT                                                0x00000000
#define PIDR2_ADDR                                                   0x00000fe8
#define PIDR2_DEFAULT                                                0x00000000
#define PIDR3_ADDR                                                   0x00000fec
#define PIDR3_DEFAULT                                                0x00000000
#define CIDR0_ADDR                                                   0x00000ff0
#define CIDR0_DEFAULT                                                0x00000000
#define CIDR1_ADDR                                                   0x00000ff4
#define CIDR1_DEFAULT                                                0x00000000
#define CIDR2_ADDR                                                   0x00000ff8
#define CIDR2_DEFAULT                                                0x00000000
#define CIDR3_ADDR                                                   0x00000ffc
#define CIDR3_DEFAULT                                                0x00000000

/*	Register CNTCR	*/ 
/*	 Fields FCREQ	 */
#define FCREQ_WIDTH                                                           3
#define FCREQ_SHIFT                                                           8
#define FCREQ_MASK                                                   0x00000700
#define FCREQ_RD(src)                                 (((src) & 0x00000700)>>8)
#define FCREQ_WR(src)                            (((u32)(src)<<8) & 0x00000700)
#define FCREQ_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields HDBG	 */
#define HDBG_WIDTH                                                            1
#define HDBG_SHIFT                                                            1
#define HDBG_MASK                                                    0x00000002
#define HDBG_RD(src)                                  (((src) & 0x00000002)>>1)
#define HDBG_WR(src)                             (((u32)(src)<<1) & 0x00000002)
#define HDBG_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields EN	 */
#define EN_WIDTH                                                              1
#define EN_SHIFT                                                              0
#define EN_MASK                                                      0x00000001
#define EN_RD(src)                                       (((src) & 0x00000001))
#define EN_WR(src)                                  (((u32)(src)) & 0x00000001)
#define EN_SET(dst,src) (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CNTSR	*/ 
/*	 Fields FCACK	 */
#define FCACK_WIDTH                                                           3
#define FCACK_SHIFT                                                           8
#define FCACK_MASK                                                   0x00000700
#define FCACK_RD(src)                                 (((src) & 0x00000700)>>8)
#define FCACK_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields DBGH	 */
#define DBGH_WIDTH                                                            1
#define DBGH_SHIFT                                                            1
#define DBGH_MASK                                                    0x00000002
#define DBGH_RD(src)                                  (((src) & 0x00000002)>>1)
#define DBGH_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))

/*	Register CNTCVL	*/ 
/*	 Fields CV	 */
#define CV_WIDTH                                                             32
#define CV_SHIFT                                                              0
#define CV_MASK                                                      0xffffffff
#define CV_RD(src)                                       (((src) & 0xffffffff))
#define CV_WR(src)                                  (((u32)(src)) & 0xffffffff)
#define CV_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CNTCVH	*/ 
/*	 Fields CV	 */
#define CV_F1_WIDTH                                                          24
#define CV_F1_SHIFT                                                           0
#define CV_F1_MASK                                                   0x00ffffff
#define CV_F1_RD(src)                                    (((src) & 0x00ffffff))
#define CV_F1_WR(src)                               (((u32)(src)) & 0x00ffffff)
#define CV_F1_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register CNTFID0	*/ 
/*	 Fields FID	 */
#define FID0_WIDTH                                                           32
#define FID0_SHIFT                                                            0
#define FID0_MASK                                                    0xffffffff
#define FID0_RD(src)                                     (((src) & 0xffffffff))
#define FID0_WR(src)                                (((u32)(src)) & 0xffffffff)
#define FID0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CNTFID1	*/ 
/*	 Fields FID	 */
#define FID1_WIDTH                                                           32
#define FID1_SHIFT                                                            0
#define FID1_MASK                                                    0xffffffff
#define FID1_RD(src)                                     (((src) & 0xffffffff))
#define FID1_WR(src)                                (((u32)(src)) & 0xffffffff)
#define FID1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CNTFID2	*/ 
/*	 Fields FID	 */
#define FID2_WIDTH                                                           32
#define FID2_SHIFT                                                            0
#define FID2_MASK                                                    0xffffffff
#define FID2_RD(src)                                     (((src) & 0xffffffff))
#define FID2_WR(src)                                (((u32)(src)) & 0xffffffff)
#define FID2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR4	*/ 
/*	 Fields ID	 */
#define ID4_WIDTH                                                            32
#define ID4_SHIFT                                                             0
#define ID4_MASK                                                     0xffffffff
#define ID4_RD(src)                                      (((src) & 0xffffffff))
#define ID4_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR0	*/ 
/*	 Fields ID	 */
#define ID0_WIDTH                                                            32
#define ID0_SHIFT                                                             0
#define ID0_MASK                                                     0xffffffff
#define ID0_RD(src)                                      (((src) & 0xffffffff))
#define ID0_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR1	*/ 
/*	 Fields ID	 */
#define ID1_WIDTH                                                            32
#define ID1_SHIFT                                                             0
#define ID1_MASK                                                     0xffffffff
#define ID1_RD(src)                                      (((src) & 0xffffffff))
#define ID1_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR2	*/ 
/*	 Fields ID	 */
#define ID2_WIDTH                                                            32
#define ID2_SHIFT                                                             0
#define ID2_MASK                                                     0xffffffff
#define ID2_RD(src)                                      (((src) & 0xffffffff))
#define ID2_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR3	*/ 
/*	 Fields ID	 */
#define ID3_WIDTH                                                            32
#define ID3_SHIFT                                                             0
#define ID3_MASK                                                     0xffffffff
#define ID3_RD(src)                                      (((src) & 0xffffffff))
#define ID3_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR0	*/ 
/*	 Fields ID	 */
#define ID0_F1_WIDTH                                                         32
#define ID0_F1_SHIFT                                                          0
#define ID0_F1_MASK                                                  0xffffffff
#define ID0_F1_RD(src)                                   (((src) & 0xffffffff))
#define ID0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR1	*/ 
/*	 Fields ID	 */
#define ID1_F1_WIDTH                                                         32
#define ID1_F1_SHIFT                                                          0
#define ID1_F1_MASK                                                  0xffffffff
#define ID1_F1_RD(src)                                   (((src) & 0xffffffff))
#define ID1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR2	*/ 
/*	 Fields ID	 */
#define ID2_F1_WIDTH                                                         32
#define ID2_F1_SHIFT                                                          0
#define ID2_F1_MASK                                                  0xffffffff
#define ID2_F1_RD(src)                                   (((src) & 0xffffffff))
#define ID2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR3	*/ 
/*	 Fields ID	 */
#define ID3_F1_WIDTH                                                         32
#define ID3_F1_SHIFT                                                          0
#define ID3_F1_MASK                                                  0xffffffff
#define ID3_F1_RD(src)                                   (((src) & 0xffffffff))
#define ID3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define MPA_GC_READ_I_BASE_ADDR			0x010590000ULL

/*    Address MPA_GC_READ_I  Registers */
#define CNTCVL_STAT_ADDR                                                  0x00000000
#define CNTCVL_STAT_DEFAULT                                               0x00000000
#define CNTCVH_STAT_ADDR                                                  0x00000004
#define CNTCVH_STAT_DEFAULT                                               0x00000000
#define PIDR4_ADDR                                                   0x00000fd0
#define PIDR4_DEFAULT                                                0x00000000
#define PIDR0_ADDR                                                   0x00000fe0
#define PIDR0_DEFAULT                                                0x00000000
#define PIDR1_ADDR                                                   0x00000fe4
#define PIDR1_DEFAULT                                                0x00000000
#define PIDR2_ADDR                                                   0x00000fe8
#define PIDR2_DEFAULT                                                0x00000000
#define PIDR3_ADDR                                                   0x00000fec
#define PIDR3_DEFAULT                                                0x00000000
#define CIDR0_ADDR                                                   0x00000ff0
#define CIDR0_DEFAULT                                                0x00000000
#define CIDR1_ADDR                                                   0x00000ff4
#define CIDR1_DEFAULT                                                0x00000000
#define CIDR2_ADDR                                                   0x00000ff8
#define CIDR2_DEFAULT                                                0x00000000
#define CIDR3_ADDR                                                   0x00000ffc
#define CIDR3_DEFAULT                                                0x00000000

/*	Register CNTCVL	*/ 
/*	 Fields CV	 */
#define CV_F4_WIDTH                                                          32
#define CV_F4_SHIFT                                                           0
#define CV_F4_MASK                                                   0xffffffff
#define CV_F4_RD(src)                                    (((src) & 0xffffffff))
#define CV_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CNTCVH	*/ 
/*	 Fields CV	 */
#define CV_F5_WIDTH                                                          24
#define CV_F5_SHIFT                                                           0
#define CV_F5_MASK                                                   0x00ffffff
#define CV_F5_RD(src)                                    (((src) & 0x00ffffff))
#define CV_F5_SET(dst,src) \
                          (((dst) & ~0x00ffffff) | (((u32)(src)) & 0x00ffffff))

/*	Register PIDR4	*/ 
/*	 Fields ID	 */
#define ID4_F2_WIDTH                                                         32
#define ID4_F2_SHIFT                                                          0
#define ID4_F2_MASK                                                  0xffffffff
#define ID4_F2_RD(src)                                   (((src) & 0xffffffff))
#define ID4_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR0	*/ 
/*	 Fields ID	 */
#define ID0_F4_WIDTH                                                         32
#define ID0_F4_SHIFT                                                          0
#define ID0_F4_MASK                                                  0xffffffff
#define ID0_F4_RD(src)                                   (((src) & 0xffffffff))
#define ID0_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR1	*/ 
/*	 Fields ID	 */
#define ID1_F4_WIDTH                                                         32
#define ID1_F4_SHIFT                                                          0
#define ID1_F4_MASK                                                  0xffffffff
#define ID1_F4_RD(src)                                   (((src) & 0xffffffff))
#define ID1_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR2	*/ 
/*	 Fields ID	 */
#define ID2_F4_WIDTH                                                         32
#define ID2_F4_SHIFT                                                          0
#define ID2_F4_MASK                                                  0xffffffff
#define ID2_F4_RD(src)                                   (((src) & 0xffffffff))
#define ID2_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register PIDR3	*/ 
/*	 Fields ID	 */
#define ID3_F4_WIDTH                                                         32
#define ID3_F4_SHIFT                                                          0
#define ID3_F4_MASK                                                  0xffffffff
#define ID3_F4_RD(src)                                   (((src) & 0xffffffff))
#define ID3_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR0	*/ 
/*	 Fields ID	 */
#define ID0_F5_WIDTH                                                         32
#define ID0_F5_SHIFT                                                          0
#define ID0_F5_MASK                                                  0xffffffff
#define ID0_F5_RD(src)                                   (((src) & 0xffffffff))
#define ID0_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR1	*/ 
/*	 Fields ID	 */
#define ID1_F5_WIDTH                                                         32
#define ID1_F5_SHIFT                                                          0
#define ID1_F5_MASK                                                  0xffffffff
#define ID1_F5_RD(src)                                   (((src) & 0xffffffff))
#define ID1_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR2	*/ 
/*	 Fields ID	 */
#define ID2_F5_WIDTH                                                         32
#define ID2_F5_SHIFT                                                          0
#define ID2_F5_MASK                                                  0xffffffff
#define ID2_F5_RD(src)                                   (((src) & 0xffffffff))
#define ID2_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CIDR3	*/ 
/*	 Fields ID	 */
#define ID3_F5_WIDTH                                                         32
#define ID3_F5_SHIFT                                                          0
#define ID3_F5_MASK                                                  0xffffffff
#define ID3_F5_RD(src)                                   (((src) & 0xffffffff))
#define ID3_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))
	


#endif
