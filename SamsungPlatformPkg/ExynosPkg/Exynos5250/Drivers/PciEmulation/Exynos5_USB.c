/** @file

  Copyright (c) 2008 - 2009, Apple Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Exynos5_USB2Phy.h>
#include <Exynos5_USB3Phy.h>
#include <Exynos5_USB3Drd.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>

#define PHY_ENABLE      (1 << 0)
#define PHY_DISABLE     (0)

enum usb_phy_type {
	USB_PHY         = (0x1 << 0),
	USB_PHY0        = (0x1 << 0),
	USB_PHY1        = (0x1 << 1),
	USB_PHY_HSIC0   = (0x1 << 1),
	USB_PHY_HSIC1   = (0x1 << 2),
};


static void usb_clk_get(enum usb_clk_type clk_type)
{
	if( clk_type == USBOTG_CLK) {
		MmioWrite32(CLK_GATE_IP_FSYS, MmioRead32(CLK_GATE_IP_FSYS) | (1<<7));
	} else if( clk_type == USBHOST_CLK) {
		MmioWrite32(CLK_GATE_IP_FSYS, MmioRead32(CLK_GATE_IP_FSYS) | (1<<18));
	} else if( clk_type == USBDRD30_CLK) {
		MmioWrite32(CLK_GATE_IP_FSYS, MmioRead32(CLK_GATE_IP_FSYS) | (1<<19));
	} else {
		DEBUG ((EFI_D_ERROR, "FAIL! usb_clk_get\n"));
	}

	return;
}

static void usb_clk_put(enum usb_clk_type clk_type)
{
	if( clk_type == USBOTG_CLK) {
		MmioWrite32(CLK_GATE_IP_FSYS, MmioRead32(CLK_GATE_IP_FSYS) & ~ (1<<7));
	} else if( clk_type == USBHOST_CLK) {
		MmioWrite32(CLK_GATE_IP_FSYS, MmioRead32(CLK_GATE_IP_FSYS) & ~ (1<<18));
	} else if( clk_type == USBDRD30_CLK) {
		MmioWrite32(CLK_GATE_IP_FSYS, MmioRead32(CLK_GATE_IP_FSYS) & ~ (1<<19));
	} else {
		DEBUG ((EFI_D_ERROR, "FAIL! usb_clk_get\n"));
	}

	return;
}

//------------------------------------------------------------------------------------

//////////
// Function Name : USBPHY_Ctr48MhzClk
// Function Desctiption : This function sets clk48m_ohci in Suspend Mode.
// Input : NONE
// Output : NONE
// Version :
void USBPHY_Ctr48MhzClk(UINT8 bEnable_48Mhz)
{

	UINT32 uTemp;

	uTemp = MmioRead32(rUPHY_OHCICTRL);
	uTemp &= ~(1<<2);
	uTemp |= bEnable_48Mhz<<2;
	MmioWrite32(rUPHY_OHCICTRL, uTemp);
}

static int exynos5_usb_host_phy20_is_on(void)
{
	return (MmioRead32(EXYNOS5_USB2_PHY_HOST_CTRL0) & HOST_CTRL0_PHYSWRSTALL) ? 0 : 1;
}

static void exynos5_usb_phy_control(enum usb_phy_type phy_type , int on)
{
	if (phy_type & USB_PHY0)
		MmioWrite32(EXYNOS5_USBDEV_PHY_CONTROL, on);
	if (phy_type & USB_PHY1)
		MmioWrite32(EXYNOS5_USBHOST_PHY_CONTROL, on);
}

void exynos5_usb_phy20_init(void)
{
	EFI_STATUS    Status;
	EXYNOS_GPIO *Gpio;
	UINT32 hostphy_ctrl0;
	UINT32 hsic_ctrl;
	UINT32 ehcictrl;

	DEBUG ((EFI_D_ERROR, "exynos5_usb_phy20_init START $$$\n"));

	Status = gBS->LocateProtocol(&gSamsungPlatformGpioProtocolGuid, NULL, (VOID **)&Gpio);
	ASSERT_EFI_ERROR(Status);

	if(PcdGetBool(PcdExynos5250Evt1))
	{
		Gpio->Set(Gpio, USB_2_EVT1, GPIO_MODE_OUTPUT_1);
		Gpio->SetPull(Gpio, USB_2_EVT1, GPIO_PULL_NONE);
	}

	if (exynos5_usb_host_phy20_is_on())
	{
		DEBUG ((EFI_D_ERROR, "Already power on PHY $$$\n"));
		return;
	}

	//  Must be enable usbhost & usbotg clk
	usb_clk_get(USBHOST_CLK);
	usb_clk_get(USBOTG_CLK);

	MmioWrite32(ETC6PUD, (MmioRead32(ETC6PUD) & ~(0x3 << 14)) | (0x3 << 14));

	exynos5_usb_phy_control(USB_PHY1, PHY_ENABLE);

	/* Host and Device should be set at the same time */
	hostphy_ctrl0 = MmioRead32(EXYNOS5_USB2_PHY_HOST_CTRL0);
	hostphy_ctrl0 &= ~(HOST_CTRL0_FSEL_MASK);

	/* 2.0 phy reference clock configuration */
	// default reference clock 24MZ
	hostphy_ctrl0 |= CLKSEL_24M;

	/* COMMON Block configuration during suspend */
	hostphy_ctrl0 &= ~(HOST_CTRL0_COMMONONN);

	/* host phy reset */
	hostphy_ctrl0 &= ~(HOST_CTRL0_PHYSWRST | HOST_CTRL0_PHYSWRSTALL | HOST_CTRL0_SIDDQ);
	hostphy_ctrl0 &= ~(HOST_CTRL0_FORCESUSPEND | HOST_CTRL0_FORCESLEEP);
	hostphy_ctrl0 |= (HOST_CTRL0_LINKSWRST | HOST_CTRL0_UTMISWRST);
	MmioWrite32(EXYNOS5_USB2_PHY_HOST_CTRL0, hostphy_ctrl0);
	MicroSecondDelay(10);
	MicroSecondDelay(10);
	hostphy_ctrl0 &= ~(HOST_CTRL0_LINKSWRST | HOST_CTRL0_UTMISWRST);
	MmioWrite32(EXYNOS5_USB2_PHY_HOST_CTRL0, hostphy_ctrl0);

	DEBUG ((EFI_D_ERROR, "exynos5_usb_phy20_init Clk set $$$\n"));

	/* HSIC phy reset */
	hsic_ctrl = (HSIC_CTRL_REFCLKDIV(0x24) | HSIC_CTRL_REFCLKSEL(0x2) |HSIC_CTRL_PHYSWRST);
	MmioWrite32(PHY_HSIC_CTRL1, hsic_ctrl);
	MmioWrite32(PHY_HSIC_CTRL2, hsic_ctrl);
	MicroSecondDelay(10);
	MicroSecondDelay(10);
	hsic_ctrl = (HSIC_CTRL_REFCLKDIV(0x24) | HSIC_CTRL_REFCLKSEL(0x2));
	MmioWrite32(PHY_HSIC_CTRL1, hsic_ctrl);
	MmioWrite32(PHY_HSIC_CTRL2, hsic_ctrl);

	MicroSecondDelay(80);
	MicroSecondDelay(80);

	/* enable EHCI DMA burst  */
	ehcictrl = MmioRead32(PHY_HOST_EHCICTRL);
	ehcictrl |= (EHCICTRL_ENAINCRXALIGN | EHCICTRL_ENAINCR4 |EHCICTRL_ENAINCR8 | EHCICTRL_ENAINCR16);
	MmioWrite32(PHY_HOST_EHCICTRL, ehcictrl);

	DEBUG ((EFI_D_ERROR, "exynos5_usb_phy20_init END $$$\n"));
}

void exynos5_usb_phy20_off(void)
{
	UINT32 uTemp;

	uTemp = MmioRead32(rUPHY_USBCTRL0);
	uTemp |= (0x1<<9);
	MmioWrite32(rUPHY_USBCTRL0, uTemp);

	usb_clk_put(USBOTG_CLK);
	usb_clk_put(USBHOST_CLK);
}


void exynos5_usb_phy30_init(void)
{
	UINT32 reg;
	DEBUG ((EFI_D_ERROR, "exynos5_usb_phy30_init START $$$\n"));

	MmioWrite32(0x10020548, 0x0BF00000);
	usb_clk_get(USBDRD30_CLK);

	exynos5_usb_phy_control(USB_PHY0, PHY_ENABLE);

	/* Reset USB 3.0 PHY */
	MmioWrite32(EXYNOS_USB3_PHYREG0,   0x00000000);
	MmioWrite32(EXYNOS_USB3_PHYPARAM0, 0x24d4e6e4);
	MmioWrite32(EXYNOS_USB3_PHYRESUME, 0x00000000);

  if(PcdGetBool(PcdExynos5250Evt1))
  {
		MmioWrite32(EXYNOS_USB3_LINKSYSTEM, 0x08000000);
		MmioWrite32(EXYNOS_USB3_PHYPARAM1, 0x03fff81C);
		MmioWrite32(EXYNOS_USB3_PHYBATCHG,  0x00000004);
	}	else {
		MmioWrite32(EXYNOS_USB3_LINKSYSTEM, 0x087FFFC0);
		MmioWrite32(EXYNOS_USB3_PHYPARAM1, 0x03fff820);
		MmioWrite32(EXYNOS_USB3_PHYBATCHG,  0x00000000);
		MmioWrite32(EXYNOS_USB3_LINKPORT, (MmioRead32(EXYNOS_USB3_LINKPORT) & ~(0x3<<4)) |(0x3<<2));
	}

	/* UTMI Power Control */
	MmioWrite32(EXYNOS_USB3_PHYUTMI, EXYNOS_USB3_PHYUTMI_OTGDISABLE);

  if(PcdGetBool(PcdExynos5250Evt1))
  {
		/* Set 100MHz external clock */
		reg = EXYNOS_USB3_PHYCLKRST_PORTRESET |
			/* HS PLL uses ref_pad_clk{p,m} or ref_alt_clk_{p,m}
			* as reference */
			EXYNOS_USB3_PHYCLKRST_REFCLKSEL(3) |
			/* Digital power supply in normal operating mode */
			EXYNOS_USB3_PHYCLKRST_RETENABLEN |
			/* 0x27-100MHz, 0x2a-24MHz, 0x31-20MHz, 0x38-19.2MHz */
			EXYNOS_USB3_PHYCLKRST_FSEL(0x5) |
			/* 0x19-100MHz, 0x68-24MHz, 0x7d-20Mhz */
			EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER(0x68) |
			EXYNOS_USB3_PHYCLKRST_SSC_REF_CLK_SEL(0x88) |
			/* Enable ref clock for SS function */
			EXYNOS_USB3_PHYCLKRST_REF_SSP_EN |
			/* Enable spread spectrum */
			EXYNOS_USB3_PHYCLKRST_SSC_EN;
	} else {
		/* Set 100MHz external clock */
		reg = EXYNOS_USB3_PHYCLKRST_PORTRESET |
			/* HS PLL uses ref_pad_clk{p,m} or ref_alt_clk_{p,m}
			* as reference */
			EXYNOS_USB3_PHYCLKRST_REFCLKSEL(2) |
			/* Digital power supply in normal operating mode */
			EXYNOS_USB3_PHYCLKRST_RETENABLEN |
			/* 0x27-100MHz, 0x2a-24MHz, 0x31-20MHz, 0x38-19.2MHz */
			EXYNOS_USB3_PHYCLKRST_FSEL(0x27) |
			/* 0x19-100MHz, 0x68-24MHz, 0x7d-20Mhz */
			EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER(0x19) |
			EXYNOS_USB3_PHYCLKRST_SSC_REF_CLK_SEL(0x00) |
			/* Enable ref clock for SS function */
			EXYNOS_USB3_PHYCLKRST_REF_SSP_EN |
			/* Enable spread spectrum */
			EXYNOS_USB3_PHYCLKRST_SSC_EN |
			EXYNOS_USB3_PHYCLKRST_COMMONONN;
	}
	MmioWrite32(EXYNOS_USB3_PHYCLKRST, reg);

	MicroSecondDelay(10);
	MicroSecondDelay(10);

	reg &= ~(EXYNOS_USB3_PHYCLKRST_PORTRESET);

	MmioWrite32(EXYNOS_USB3_PHYCLKRST, reg);
	DEBUG ((EFI_D_ERROR, "exynos5_usb_phy30_init END $$$\n"));

}

void exynos_xhci_phy_set(void)
{
	/* The reset values:
	*      GUSB2PHYCFG(0)  = 0x00002400
	*      GUSB3PIPECTL(0) = 0x00260002
	*/
	// orr32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GCTL,
                   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GCTL) | EXYNOS_USB3_GCTL_CoreSoftReset));
	// orr32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0)) | EXYNOS_USB3_GUSB2PHYCFGx_PHYSoftRst));
	// orr32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0)) | EXYNOS_USB3_GUSB3PIPECTLx_PHYSoftRst));

	exynos5_usb_phy30_init();

	// bic32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0)) & ~EXYNOS_USB3_GUSB2PHYCFGx_PHYSoftRst));
	// bic32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0)) & ~EXYNOS_USB3_GUSB3PIPECTLx_PHYSoftRst));
	// bic32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GCTL,
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GCTL) & ~EXYNOS_USB3_GCTL_CoreSoftReset));
	// bic32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0)) & ~(EXYNOS_USB3_GUSB2PHYCFGx_SusPHY |
		   EXYNOS_USB3_GUSB2PHYCFGx_EnblSlpM |
		   EXYNOS_USB3_GUSB2PHYCFGx_USBTrdTim_MASK)));

	// orr32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0)) | EXYNOS_USB3_GUSB2PHYCFGx_USBTrdTim(9)));

	// bic32
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0),
		   (MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0)) & ~EXYNOS_USB3_GUSB3PIPECTLx_SuspSSPhy));


	DEBUG ((EFI_D_ERROR, "GUSB2PHYCFG(0)=0x%08x, GUSB3PIPECTL(0)=0x%08x\n",
		MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB2PHYCFG(0)),
		MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GUSB3PIPECTL(0))));

	/* Global core init */
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GSBUSCFG0,
		    EXYNOS_USB3_GSBUSCFG0_INCR16BrstEna |
		    EXYNOS_USB3_GSBUSCFG0_INCR8BrstEna |
		    EXYNOS_USB3_GSBUSCFG0_INCR4BrstEna);

	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GSBUSCFG1,
		    EXYNOS_USB3_GSBUSCFG1_BREQLIMIT(0x3));

	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GTXTHRCFG, 0x0);
	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GRXTHRCFG, 0x0);
}

UINT32 exynos_xhci_change_mode(void)
{
	UINT32 gctl;

	gctl = MmioRead32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GCTL);
	gctl &= ~(EXYNOS_USB3_GCTL_PrtCapDir_MASK |
		EXYNOS_USB3_GCTL_FRMSCLDWN_MASK |
		EXYNOS_USB3_GCTL_RAMClkSel_MASK);

	gctl |= (EXYNOS_USB3_GCTL_FRMSCLDWN(0x1e85) | /* Power Down Scale */
		EXYNOS_USB3_GCTL_RAMClkSel(0x2) | /* Ram Clock Select */
		EXYNOS_USB3_GCTL_DisScramble);

	gctl |= EXYNOS_USB3_GCTL_PrtCapDir(0x1);/* 0x1 : Host */

	MmioWrite32(EXYNOS5_USB3_DRD_BASEADDR + EXYNOS_USB3_GCTL, gctl);

	DEBUG ((EFI_D_ERROR, "Change xHCI host mode %x\n", gctl));
	return gctl;
}

