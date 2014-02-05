/** @file
*
*  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/


#ifndef _DisplayDxe_H__
#define _DisplayDxe_H__

/*
 * Bit Definitions
*/

/* VIDCON0 */
#define S5P_VIDCON0_DSI_DISABLE			(0 << 30)
#define S5P_VIDCON0_DSI_ENABLE			(1 << 30)
#define S5P_VIDCON0_SCAN_PROGRESSIVE		(0 << 29)
#define S5P_VIDCON0_SCAN_INTERLACE		(1 << 29)
#define S5P_VIDCON0_SCAN_MASK			(1 << 29)
#define S5P_VIDCON0_VIDOUT_RGB			(0 << 26)
#define S5P_VIDCON0_VIDOUT_ITU			(1 << 26)
#define S5P_VIDCON0_VIDOUT_I80LDI0		(2 << 26)
#define S5P_VIDCON0_VIDOUT_I80LDI1		(3 << 26)
#define S5P_VIDCON0_VIDOUT_WB_RGB		(4 << 26)
#define S5P_VIDCON0_VIDOUT_WB_I80LDI0		(6 << 26)
#define S5P_VIDCON0_VIDOUT_WB_I80LDI1		(7 << 26)
#define S5P_VIDCON0_VIDOUT_MASK			(7 << 26)
#define S5P_VIDCON0_PNRMODE_RGB_P		(0 << 17)
#define S5P_VIDCON0_PNRMODE_BGR_P		(1 << 17)
#define S5P_VIDCON0_PNRMODE_RGB_S		(2 << 17)
#define S5P_VIDCON0_PNRMODE_BGR_S		(3 << 17)
#define S5P_VIDCON0_PNRMODE_MASK		(3 << 17)
#define S5P_VIDCON0_PNRMODE_SHIFT		(17)
#define S5P_VIDCON0_CLKVALUP_ALWAYS		(0 << 16)
#define S5P_VIDCON0_CLKVALUP_START_FRAME	(1 << 16)
#define S5P_VIDCON0_CLKVALUP_MASK		(1 << 16)
#define S5P_VIDCON0_CLKVAL_F(x)			(((x) & 0xff) << 6)
#define S5P_VIDCON0_CLKVAL_F_MASK			(0xff << 6)
#define S5P_VIDCON0_VCLKEN_NORMAL		(0 << 5)
#define S5P_VIDCON0_VCLKEN_FREERUN		(1 << 5)
#define S5P_VIDCON0_VCLKEN_MASK			(1 << 5)
#define S5P_VIDCON0_CLKDIR_DIRECTED		(0 << 4)
#define S5P_VIDCON0_CLKDIR_DIVIDED		(1 << 4)
#define S5P_VIDCON0_CLKDIR_MASK			(1 << 4)
#define S5P_VIDCON0_CLKSEL_HCLK			(0 << 2)
#define S5P_VIDCON0_CLKSEL_SCLK			(1 << 2)
#define S5P_VIDCON0_CLKSEL_MASK			(1 << 2)
#define S5P_VIDCON0_ENVID_ENABLE		(1 << 1)
#define S5P_VIDCON0_ENVID_DISABLE		(0 << 1)
#define S5P_VIDCON0_ENVID_F_ENABLE		(1 << 0)
#define S5P_VIDCON0_ENVID_F_DISABLE		(0 << 0)

/* VIDCON1 */
#define S5P_VIDCON1_FIXVCLK_MASK			(3 << 9)
#define S5P_VIDCON1_FIXVCLK_HOLD			(0 << 9)
#define S5P_VIDCON1_FIXVCLK_RUN			(1 << 9)
#define S5P_VIDCON1_IVCLK_FALLING_EDGE	(0 << 7)
#define S5P_VIDCON1_IVCLK_RISING_EDGE		(1 << 7)
#define S5P_VIDCON1_IHSYNC_NORMAL		(0 << 6)
#define S5P_VIDCON1_IHSYNC_INVERT			(1 << 6)
#define S5P_VIDCON1_IVSYNC_NORMAL		(0 << 5)
#define S5P_VIDCON1_IVSYNC_INVERT			(1 << 5)
#define S5P_VIDCON1_IVDEN_NORMAL			(0 << 4)
#define S5P_VIDCON1_IVDEN_INVERT			(1 << 4)

/* VIDCON2 */
#define S5P_VIDCON2_EN601_DISABLE		(0 << 23)
#define S5P_VIDCON2_EN601_ENABLE		(1 << 23)
#define S5P_VIDCON2_EN601_MASK			(1 << 23)
#define S5P_VIDCON2_WB_DISABLE			(0 << 15)
#define S5P_VIDCON2_WB_ENABLE			(1 << 15)
#define S5P_VIDCON2_WB_MASK			(1 << 15)
#define S5P_VIDCON2_TVFORMATSEL_HW		(0 << 14)
#define S5P_VIDCON2_TVFORMATSEL_SW		(1 << 14)
#define S5P_VIDCON2_TVFORMATSEL_MASK		(1 << 14)
#define S5P_VIDCON2_TVFORMATSEL_YUV422		(1 << 12)
#define S5P_VIDCON2_TVFORMATSEL_YUV444		(2 << 12)
#define S5P_VIDCON2_TVFORMATSEL_YUV_MASK	(3 << 12)
#define S5P_VIDCON2_ORGYUV_YCBCR		(0 << 8)
#define S5P_VIDCON2_ORGYUV_CBCRY		(1 << 8)
#define S5P_VIDCON2_ORGYUV_MASK			(1 << 8)
#define S5P_VIDCON2_YUVORD_CBCR			(0 << 7)
#define S5P_VIDCON2_YUVORD_CRCB			(1 << 7)
#define S5P_VIDCON2_YUVORD_MASK			(1 << 7)

/* PRTCON */
#define S5P_PRTCON_UPDATABLE			(0 << 11)
#define S5P_PRTCON_PROTECT			(1 << 11)

/* VIDTCON0 */
#define S5P_VIDTCON0_VBPDE(x)			(((x) & 0xff) << 24)
#define S5P_VIDTCON0_VBPD(x)			(((x) & 0xff) << 16)
#define S5P_VIDTCON0_VFPD(x)			(((x) & 0xff) << 8)
#define S5P_VIDTCON0_VSPW(x)			(((x) & 0xff) << 0)

/* VIDTCON1 */
#define S5P_VIDTCON1_VFPDE(x)			(((x) & 0xff) << 24)
#define S5P_VIDTCON1_HBPD(x)			(((x) & 0xff) << 16)
#define S5P_VIDTCON1_HFPD(x)			(((x) & 0xff) << 8)
#define S5P_VIDTCON1_HSPW(x)			(((x) & 0xff) << 0)

/* VIDTCON2 */
#define S5P_VIDTCON2_LINEVAL(x)			(((x) & 0x7ff) << 11)
#define S5P_VIDTCON2_HOZVAL(x)			(((x) & 0x7ff) << 0)

/* Window 0~4 Control - WINCONx */
#define S5P_WINCON_DATAPATH_DMA			(0 << 22)
#define S5P_WINCON_DATAPATH_LOCAL		(1 << 22)
#define S5P_WINCON_DATAPATH_MASK		(1 << 22)
#define S5P_WINCON_BUFSEL_0			(0 << 20)
#define S5P_WINCON_BUFSEL_1			(1 << 20)
#define S5P_WINCON_BUFSEL_MASK			(1 << 20)
#define S5P_WINCON_BUFSEL_SHIFT			(20)
#define S5P_WINCON_BUFAUTO_DISABLE		(0 << 19)
#define S5P_WINCON_BUFAUTO_ENABLE		(1 << 19)
#define S5P_WINCON_BUFAUTO_MASK			(1 << 19)
#define S5P_WINCON_BITSWP_DISABLE		(0 << 18)
#define S5P_WINCON_BITSWP_ENABLE		(1 << 18)
#define S5P_WINCON_BITSWP_SHIFT			(18)
#define S5P_WINCON_BYTESWP_DISABLE		(0 << 17)
#define S5P_WINCON_BYTESWP_ENABLE		(1 << 17)
#define S5P_WINCON_BYTESWP_SHIFT		(17)
#define S5P_WINCON_HAWSWP_DISABLE		(0 << 16)
#define S5P_WINCON_HAWSWP_ENABLE		(1 << 16)
#define S5P_WINCON_HAWSWP_SHIFT			(16)
#define S5P_WINCON_WSWP_DISABLE			(0 << 15)
#define S5P_WINCON_WSWP_ENABLE			(1 << 15)
#define S5P_WINCON_WSWP_SHIFT			(15)
#define S5P_WINCON_INRGB_RGB			(0 << 13)
#define S5P_WINCON_INRGB_YUV			(1 << 13)
#define S5P_WINCON_INRGB_MASK			(1 << 13)
#define S5P_WINCON_BURSTLEN_16WORD		(0 << 9)
#define S5P_WINCON_BURSTLEN_8WORD		(1 << 9)
#define S5P_WINCON_BURSTLEN_4WORD		(2 << 9)
#define S5P_WINCON_BURSTLEN_MASK		(3 << 9)
#define S5P_WINCON_ALPHA_MULTI_DISABLE		(0 << 7)
#define S5P_WINCON_ALPHA_MULTI_ENABLE		(1 << 7)
#define S5P_WINCON_BLD_PLANE			(0 << 6)
#define S5P_WINCON_BLD_PIXEL			(1 << 6)
#define S5P_WINCON_BLD_MASK			(1 << 6)
#define S5P_WINCON_BPPMODE_1BPP			(0 << 2)
#define S5P_WINCON_BPPMODE_2BPP			(1 << 2)
#define S5P_WINCON_BPPMODE_4BPP			(2 << 2)
#define S5P_WINCON_BPPMODE_8BPP_PAL		(3 << 2)
#define S5P_WINCON_BPPMODE_8BPP				(4 << 2)
#define S5P_WINCON_BPPMODE_16BPP_565		(5 << 2)
#define S5P_WINCON_BPPMODE_16BPP_A555		(6 << 2)
#define S5P_WINCON_BPPMODE_18BPP_666		(8 << 2)
#define S5P_WINCON_BPPMODE_18BPP_A665		(9 << 2)
#define S5P_WINCON_BPPMODE_24BPP_888		(0xb << 2)
#define S5P_WINCON_BPPMODE_24BPP_A887		(0xc << 2)
#define S5P_WINCON_BPPMODE_32BPP				(0xd << 2)
#define S5P_WINCON_BPPMODE_16BPP_A444		(0xe << 2)
#define S5P_WINCON_BPPMODE_15BPP_555		(0xf << 2)
#define S5P_WINCON_BPPMODE_MASK				(0xf << 2)
#define S5P_WINCON_BPPMODE_SHIFT				(2)
#define S5P_WINCON_ALPHA0_SEL					(0 << 1)
#define S5P_WINCON_ALPHA1_SEL					(1 << 1)
#define S5P_WINCON_ALPHA_SEL_MASK			(1 << 1)
#define S5P_WINCON_ENWIN_DISABLE				(0 << 0)
#define S5P_WINCON_ENWIN_ENABLE				(1 << 0)

/* WINCON1 special */
#define S5P_WINCON1_VP_DISABLE			(0 << 24)
#define S5P_WINCON1_VP_ENABLE				(1 << 24)
#define S5P_WINCON1_LOCALSEL_FIMC1		(0 << 23)
#define S5P_WINCON1_LOCALSEL_VP			(1 << 23)
#define S5P_WINCON1_LOCALSEL_MASK		(1 << 23)

/* WINSHMAP */
#define S5P_SHADOWCON_PROTECT(x)			(1 << (10 + x))
#define S5P_SHADOWCON_CH_ENABLE(x)		(1 << (x))
#define S5P_SHADOWCON_CH_DISABLE(x)		(1 << (x))


/* VIDOSDxA, VIDOSDxB */
#define S5P_VIDOSD_LEFT_X(x)			(((x) & 0x7ff) << 11)
#define S5P_VIDOSD_TOP_Y(x)			(((x) & 0x7ff) << 0)
#define S5P_VIDOSD_RIGHT_X(x)			(((x) & 0x7ff) << 11)
#define S5P_VIDOSD_BOTTOM_Y(x)			(((x) & 0x7ff) << 0)

/* VIDOSD0C, VIDOSDxD */
#define S5P_VIDOSD_SIZE(x)			(((x) & 0xffffff) << 0)

/* VIDOSDxC (1~4) */
#define S5P_VIDOSD_ALPHA0_R(x)			(((x) & 0xf) << 20)
#define S5P_VIDOSD_ALPHA0_G(x)			(((x) & 0xf) << 16)
#define S5P_VIDOSD_ALPHA0_B(x)			(((x) & 0xf) << 12)
#define S5P_VIDOSD_ALPHA1_R(x)			(((x) & 0xf) << 8)
#define S5P_VIDOSD_ALPHA1_G(x)			(((x) & 0xf) << 4)
#define S5P_VIDOSD_ALPHA1_B(x)			(((x) & 0xf) << 0)
#define S5P_VIDOSD_ALPHA0_SHIFT			(12)
#define S5P_VIDOSD_ALPHA1_SHIFT			(0)

/* Start Address */
#define S5P_VIDADDR_START_VBANK(x)		(((x) & 0xff) << 24)
#define S5P_VIDADDR_START_VBASEU(x)		(((x) & 0xffffff) << 0)

/* End Address */
#define S5P_VIDADDR_END_VBASEL(x)		(((x) & 0xffffff) << 0)

/* Buffer Size */
#define S5P_VIDADDR_OFFSIZE(x)			(((x) & 0x1fff) << 13)
#define S5P_VIDADDR_PAGEWIDTH(x)		(((x) & 0x1fff) << 0)

/* WIN Color Map */
#define S5P_WINMAP_COLOR(x)			((x) & 0xffffff)

/* VIDINTCON0 */
#define S5P_VIDINTCON0_SYSMAINCON_DISABLE	(0 << 19)
#define S5P_VIDINTCON0_SYSMAINCON_ENABLE	(1 << 19)
#define S5P_VIDINTCON0_SYSSUBCON_DISABLE	(0 << 18)
#define S5P_VIDINTCON0_SYSSUBCON_ENABLE		(1 << 18)
#define S5P_VIDINTCON0_SYSIFDONE_DISABLE	(0 << 17)
#define S5P_VIDINTCON0_SYSIFDONE_ENABLE		(1 << 17)
#define S5P_VIDINTCON0_FRAMESEL0_BACK		(0 << 15)
#define S5P_VIDINTCON0_FRAMESEL0_VSYNC		(1 << 15)
#define S5P_VIDINTCON0_FRAMESEL0_ACTIVE		(2 << 15)
#define S5P_VIDINTCON0_FRAMESEL0_FRONT		(3 << 15)
#define S5P_VIDINTCON0_FRAMESEL0_MASK		(3 << 15)
#define S5P_VIDINTCON0_FRAMESEL1_NONE		(0 << 13)
#define S5P_VIDINTCON0_FRAMESEL1_BACK		(1 << 13)
#define S5P_VIDINTCON0_FRAMESEL1_VSYNC		(2 << 13)
#define S5P_VIDINTCON0_FRAMESEL1_FRONT		(3 << 13)
#define S5P_VIDINTCON0_INTFRMEN_DISABLE		(0 << 12)
#define S5P_VIDINTCON0_INTFRMEN_ENABLE		(1 << 12)
#define S5P_VIDINTCON0_FIFOSEL_WIN4		(1 << 11)
#define S5P_VIDINTCON0_FIFOSEL_WIN3		(1 << 10)
#define S5P_VIDINTCON0_FIFOSEL_WIN2		(1 << 9)
#define S5P_VIDINTCON0_FIFOSEL_WIN1		(1 << 6)
#define S5P_VIDINTCON0_FIFOSEL_WIN0		(1 << 5)
#define S5P_VIDINTCON0_FIFOSEL_ALL		(0x73 << 5)
#define S5P_VIDINTCON0_FIFOSEL_MASK		(0x73 << 5)
#define S5P_VIDINTCON0_FIFOLEVEL_25		(0 << 2)
#define S5P_VIDINTCON0_FIFOLEVEL_50		(1 << 2)
#define S5P_VIDINTCON0_FIFOLEVEL_75		(2 << 2)
#define S5P_VIDINTCON0_FIFOLEVEL_EMPTY		(3 << 2)
#define S5P_VIDINTCON0_FIFOLEVEL_FULL		(4 << 2)
#define S5P_VIDINTCON0_FIFOLEVEL_MASK		(7 << 2)
#define S5P_VIDINTCON0_INTFIFO_DISABLE		(0 << 1)
#define S5P_VIDINTCON0_INTFIFO_ENABLE		(1 << 1)
#define S5P_VIDINTCON0_INT_DISABLE		(0 << 0)
#define S5P_VIDINTCON0_INT_ENABLE		(1 << 0)
#define S5P_VIDINTCON0_INT_MASK			(1 << 0)

/* VIDINTCON1 */
#define S5P_VIDINTCON1_INTVPPEND		(1 << 5)
#define S5P_VIDINTCON1_INTI80PEND		(1 << 2)
#define S5P_VIDINTCON1_INTFRMPEND		(1 << 1)
#define S5P_VIDINTCON1_INTFIFOPEND		(1 << 0)

/* WINMAP */
#define S5P_WINMAP_ENABLE			(1 << 24)

/* WxKEYCON0 (1~4) */
#define S5P_KEYCON0_KEYBLEN_DISABLE		(0 << 26)
#define S5P_KEYCON0_KEYBLEN_ENABLE		(1 << 26)
#define S5P_KEYCON0_KEY_DISABLE			(0 << 25)
#define S5P_KEYCON0_KEY_ENABLE			(1 << 25)
#define S5P_KEYCON0_DIRCON_MATCH_FG		(0 << 24)
#define S5P_KEYCON0_DIRCON_MATCH_BG		(1 << 24)
#define S5P_KEYCON0_COMPKEY(x)			(((x) & 0xffffff) << 0)

/* WxKEYCON1 (1~4) */
#define S5P_KEYCON1_COLVAL(x)			(((x) & 0xffffff) << 0)


#endif // _Display_Dxe_H__
