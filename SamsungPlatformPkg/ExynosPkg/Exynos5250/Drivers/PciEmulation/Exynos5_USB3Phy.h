#ifndef _EFI_EXYNOS5_USB3_PHY_H_
#define _EFI_EXYNOS5_USB3_PHY_H_

#define EXYNOS5_USB3_PHY_HOST_CTRL0 0x12100000

#define EXYNOS_USB3_LINKSYSTEM				(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x04)
#define EXYNOS_USB3_PHYUTMI             		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x08)
#define EXYNOS_USB3_PHYPIPE             		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x0C)
#define EXYNOS_USB3_PHYCLKRST           		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x10)
#define EXYNOS_USB3_PHYREG0             		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x14)
#define EXYNOS_USB3_PHYREG1             		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x18)
#define EXYNOS_USB3_PHYPARAM0           		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x1C)
#define EXYNOS_USB3_PHYPARAM1           		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x20)
#define EXYNOS_USB3_PHYTERM             		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x24)
#define EXYNOS_USB3_PHYTEST             		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x28)
#define EXYNOS_USB3_PHYADP              		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x2C)
#define EXYNOS_USB3_PHYBATCHG           		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x30)
#define EXYNOS_USB3_PHYRESUME           		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x34)
#define EXYNOS_USB3_LINKPORT            		(EXYNOS5_USB3_PHY_HOST_CTRL0 + 0x44)


#define EXYNOS_USB3_PHYUTMI_OTGDISABLE                  (1 << 6)
#define EXYNOS_USB3_PHYUTMI_FORCESUSPEND                (1 << 1)
#define EXYNOS_USB3_PHYUTMI_FORCESLEEP                  (1 << 0)

#define EXYNOS_USB3_PHYCLKRST_SSC_REF_CLK_SEL_MASK      (0xff << 23)
#define EXYNOS_USB3_PHYCLKRST_SSC_REF_CLK_SEL_SHIFT     (23)
#define EXYNOS_USB3_PHYCLKRST_SSC_REF_CLK_SEL_LIMIT     (0xff)
#define EXYNOS_USB3_PHYCLKRST_SSC_REF_CLK_SEL(_x)       ((_x) << 23)

#define EXYNOS_USB3_PHYCLKRST_SSC_RANGE_MASK            (0x03 << 21)
#define EXYNOS_USB3_PHYCLKRST_SSC_RANGE_SHIFT           (21)
#define EXYNOS_USB3_PHYCLKRST_SSC_RANGE_LIMIT           (0x03)
#define EXYNOS_USB3_PHYCLKRST_SSC_RANGE(_x)             ((_x) << 21)

#define EXYNOS_USB3_PHYCLKRST_SSC_EN                    (1 << 20)
#define EXYNOS_USB3_PHYCLKRST_REF_SSP_EN                (1 << 19)
#define EXYNOS_USB3_PHYCLKRST_REF_CLKDIV2               (1 << 18)

#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER_MASK      (0x7f << 11)
#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER_SHIFT     (11)
#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER_LIMIT     (0x7f)
#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER(_x)       ((_x) << 11)

#define EXYNOS_USB3_PHYCLKRST_SSC_EN                    (1 << 20)
#define EXYNOS_USB3_PHYCLKRST_REF_SSP_EN                (1 << 19)
#define EXYNOS_USB3_PHYCLKRST_REF_CLKDIV2               (1 << 18)

#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER_MASK      (0x7f << 11)
#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER_SHIFT     (11)
#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER_LIMIT     (0x7f)
#define EXYNOS_USB3_PHYCLKRST_MPLL_MULTIPLIER(_x)       ((_x) << 11)

#define EXYNOS_USB3_PHYCLKRST_FSEL_MASK                 (0x3f << 5)
#define EXYNOS_USB3_PHYCLKRST_FSEL_SHIFT                (5)
#define EXYNOS_USB3_PHYCLKRST_FSEL_LIMIT                (0x3f)
#define EXYNOS_USB3_PHYCLKRST_FSEL(_x)                  ((_x) << 5)

#define EXYNOS_USB3_PHYCLKRST_RETENABLEN                (1 << 4)

#define EXYNOS_USB3_PHYCLKRST_REFCLKSEL_MASK            (0x03 << 2)
#define EXYNOS_USB3_PHYCLKRST_REFCLKSEL_SHIFT           (2)
#define EXYNOS_USB3_PHYCLKRST_REFCLKSEL_LIMIT           (0x03)
#define EXYNOS_USB3_PHYCLKRST_REFCLKSEL(_x)             ((_x) << 2)

#define EXYNOS_USB3_PHYCLKRST_PORTRESET                 (1 << 1)
#define EXYNOS_USB3_PHYCLKRST_COMMONONN                 (1 << 0)


//-------------------------------------------------------
// Functions
//-------------------------------------------------------

void exynos5_usb_phy30_init(void);
void exynos_xhci_phy_set(void);
UINT32 exynos_xhci_change_mode(void);

#endif


