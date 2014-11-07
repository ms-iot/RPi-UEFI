/**
 * Copyright (c) 2013, AppliedMicro  Corp. All rights reserved.
 * All rights reserved. Tuan Phan <tphan@apm.com>.
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

#ifndef _GPIO_H_
#define _GPIO_H_

#if 0
#define GPIO_DBG
#define GPIO_DBG_IO
#endif

#define ERROR(arg...) DEBUG((EFI_D_ERROR,## arg))


#ifdef GPIO_DBG
#define DBG(arg...) DEBUG((EFI_D_VERBOSE,## arg))
#else
#define DBG(arg...)
#endif

#ifdef GPIO_DBG_IO
#define DBG_IO(arg...) DEBUG((EFI_D_VERBOSE,## arg))
#else
#define DBG_IO(arg...)
#endif

#define GPIO_MUX_MAX 32
#define GPIO_MUX_ALT_CLEAR(Val, Gpio) ( Val & ~(0x3 << (Gpio * 2)))
#define GPIO_MUX_ALT_MASK_VAL(Func, Gpio) (Func << (Gpio * 2))
#define GPIO_MUX_VAL(Gpio) (0x00000001 << Gpio)
#define GPIO_ALT3 0x3
#define GPIO_IN 0
#define GPIO_OUT 1
#define GPIO_OUT_CLR 1

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

#endif /* _GPIO_H_ */
