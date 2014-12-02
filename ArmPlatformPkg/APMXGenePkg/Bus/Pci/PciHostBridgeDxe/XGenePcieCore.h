/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
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

#if !defined(__XGENEPCIECORE_H__)
#define __XGENEPCIECORE_H__

#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/Pci.h>
#include <Library/TimerLib.h>
#include <Library/ArmLib.h>

#include <APMXGeneSocCsr.h>
#include <Library/XGenePHY.h>
#include "PciHostBridge.h"

/*FIXME: These typedef just for don't want to modify Serdes code for now */
typedef UINT64 u64;
typedef UINT32 u32;
typedef UINT16 u16;
typedef UINT8  u8;

typedef UINT64 uint64_t;
typedef UINT32 uint32_t;
typedef UINT16 uint16_t;
typedef UINT8  uint8_t;
typedef EFI_PHYSICAL_ADDRESS phys_addr_t;

#define udelay  MicroSecondDelay
#define mdelay(x) MicroSecondDelay(x*1000)

#define PCIECORE_LTSSM      0x4c
#define PCIECORE_CTLANDSTATUS   0x50
#define POWERMANAGEMENTREG    0x54
#define EVENTINTERRUPTSTATUS    0x58
#define EVENTINTERRUPTSTATUSMASK  0x5c
#define ERRORINTERRUPTSTATUS    0x60
#define ERRORINTERRUPTSTATUSMASK  0x64
#define INTXSTATUSMASK      0x6c
#define PCIECORE_CTLANDSTATUS   0x50
#define IBAR2         0x98
#define IBAR3L        0xb4
#define PIM1_1L       0x80
#define PIM2_1L       0xa0
#define PIM3_1L       0xc4
#define PIM4L       0xdc
#define OMR1BARL      0x100
#define CFGBARL       0x154
#define CFGBARH       0x158
#define CFGCTL        0x15c
#define RTDID       0x160
#define CFG_CONSTANTS_31_00   0x2000
#define CFG_CONSTANTS_63_32   0x2004
#define CFG_CONSTANTS_159_128   0x2010
#define CFG_CONSTANTS_351_320   0x2028
#define CFG_CONSTANTS_479_448   0x2038
#define CFG_CONSTANTS_607_576   0x2048
#define CFG_8G_CONSTANTS_31_0   0x2100
#define CFG_CONTROL_31_00   0x2200
#define CFG_CONTROL_63_32   0x2204
#define CFG_CONTROL_191_160   0x2214
#define CFG_CONTROL_447_416   0x2234
#define PCIE_STATUS_31_0    0x2600

#define PCI_PRIMARY_BUS_MASK    0x00ffffff
#define REVISION_ID_MASK    0x000000ff
#define SLOT_IMPLEMENTED_MASK   0x04000000
#define DEVICE_PORT_TYPE_MASK   0x03c00000
#define ADVT_INFINITE_CREDITS   0x00000200
#define PM_FORCE_RP_MODE_MASK   0x00000400
#define SWITCH_PORT_MODE_MASK   0x00000800
#define MSI_CAPABLE_MASK    0x001c0000
#define MSIX_CAP_DISABLE_MASK   0x00020000
#define MSI_CAP_DISABLE_MASK    0x00010000
#define CLASS_CODE_MASK     0xffffff00
#define LINK_UP_MASK      0x00000100
#define AER_OPTIONAL_ERROR_EN   0xffc00000
#define MAX_PAYLD_SZ_SUP_MASK   0x00000007
#define DWNSTRM_EQ_SKP_PHS_2_3    0x00010000
#define DIRECT_TO_5GTS_MASK   0x00020000
#define SUPPORT_5GTS_MASK   0x00010000
#define DIRECT_TO_8GTS_MASK   0x00008000
#define SUPPORT_8GTS_MASK   0x00004000
#define MAX_LNK_WDT_OVRRD_MASK    0x00000007
#define XGENE_PCIE_DEV_CTRL   0x2f09
#define AXI_EP_CFG_ACCESS   0x10000
#define AXI_EP_DMA_ACCESS   0x20000
#define XGENE_PORT_TYPE_RC    0x05000000

#define EN_COHERENCY      0xF0000000
#define EN_REG        0x00000001
#define OB_LO_IO      0x00000002
#define XGENE_PCIE_LINK_WAIT    (500*1000)
#define XGENE_PCIE_MAX_REGIONS    3
#define XGENE_PCIE_VENDORID   0x10E8
#define XGENE_PCIE_BRIDGE_DEVICEID  0xE004
#define XGENE_PCIE_DEVICEID   0xCAFE

enum {
  PTYPE_ENDPOINT = 0x0,
  PTYPE_LEGACY_ENDPOINT = 0x1,
  PTYPE_ROOT_PORT = 0x4,

  LNKW_X1 = 0x1,
  LNKW_X2 = 0x2,
  LNKW_X4 = 0x4,
  LNKW_X8 = 0x8,
  LNKW_X16 = 0x10,

  PCIE_GEN1 = 0x0,  /* 2.5G */
  PCIE_GEN2 = 0x1,  /* 5.0G */
  PCIE_GEN3 = 0x2,  /* 8.0G */
};

/* Host to PCIE translation address map */
struct ob_mem_addr {
  u32 hi;
  u32 lo;
  phys_addr_t size;
  u32 pcie_hi;
  u32 pcie_lo;
};

struct ib_mem_addr {
  u32 pcie_hi;
  u32 pcie_lo;
  u64 pcie_size;
  u32 pim1_hi;
  u32 pim1_lo;
  u32 pim2_hi;
  u32 pim2_lo;
  u64 pim_size;
};
/**
 * @struct xgene_pcie_map_tbl
 * @brief Host to PCIE translation address map
 * @note Although, pci_controller structure stores some of these values,
 *       it isn't complete. Therefore, we will keep a complete map here.
 *
 */
struct xgene_pcie_map_tbl {
	u64 csr_addr;    		/* Host bridge CSR address */
	u32 csr_addr_size;

	/* Outbound AXI address for translation to PCIE */
	u32 cfg_addr_hi;    		/* Configuration AXI address for all */
	u32 cfg_addr_lo;		/* PCI devices */
	u32 cfg_addr_size;		/* use 0 for not used */
	u64 cfg_vaddr;			/* Virtual address */
	struct ob_mem_addr ob_mem_addr[XGENE_PCIE_MAX_REGIONS];
	u32 ob_msg_addr_hi;		/* Message region address map */
	u32 ob_msg_addr_lo;
	u64 ob_msg_addr_size;		/* use 0 for not used */

	/* Inbound AXI address for translation from PCIE */
	struct ib_mem_addr ib_mem_addr[XGENE_PCIE_MAX_REGIONS];
	u32 ib_rom_addr_hi;		/* Inbound expansion rom map address */
	u32 ib_rom_addr_lo;
	u32 ib_rom_addr_size;  		/* use 0 for not used */
};

struct xgene_pcie_port {
  void      *host;
	u8			index;
	u8			status;
	u8			type;
	u8			link_up;
	u8			link_width;
	u8			link_speed;
	u8			cur_link_width;
	u8			cur_link_speed;
	u8			reset_core;
	u8			serdes_clk;
	u32			first_busno;
	u32			last_busno;
	struct xgene_pcie_map_tbl *map_tbl;
	void			*csr_base;
	void			*cfg_base;
};

enum {
  XGENE_MEM,
  XGENE_MSI,
  XGENE_IO,
  XGENE_RES /* termination */
};

#define PCI_BASE_ADDRESS_0  0x10  /* 32 bits */
#define PCI_BASE_ADDRESS_1  0x14  /* 32 bits [htype 0,1 only] */
#define PCI_BASE_ADDRESS_2  0x18  /* 32 bits [htype 0 only] */
#define PCI_BASE_ADDRESS_3  0x1c  /* 32 bits */
#define PCI_BASE_ADDRESS_4  0x20  /* 32 bits */
#define PCI_BASE_ADDRESS_5  0x24  /* 32 bits */
#define  PCI_BASE_ADDRESS_SPACE 0x01  /* 0 = memory, 1 = I/O */
#define  PCI_BASE_ADDRESS_SPACE_IO 0x01
#define  PCI_BASE_ADDRESS_SPACE_MEMORY 0x00
#define  PCI_BASE_ADDRESS_MEM_TYPE_MASK 0x06
#define  PCI_BASE_ADDRESS_MEM_TYPE_32 0x00  /* 32 bit address */
#define  PCI_BASE_ADDRESS_MEM_TYPE_1M 0x02  /* Below 1M [obsolete] */
#define  PCI_BASE_ADDRESS_MEM_TYPE_64 0x04  /* 64 bit address */
#define PCI_BASE_ADDRESS_MEM_MASK (~0x0fULL)
#define PCI_BASE_ADDRESS_MEM_PREFETCH 0x08
#define PCI_BASE_ADDRESS_MEM_TYPE_64 0x04

#define PCI_ROM_ADDRESS1  0x38  /* Same as PCI_ROM_ADDRESS, but for htype 1 */
#define PCI_CLASS_BRIDGE_PCI            0x0604

#define MAKE_U64(h, l)    ((((u64) (h)) << 32) | (l))
#define upper_32_bits(x)  ((u32) (((u64)(x)) >> 32))
#define lower_32_bits(x)  ((u32) ((x) & 0xFFFFFFFF))


#define CONFIG_SYS_PCIEX_CFGSIZE        0x01000000 /* 16 MB configuration space */
#define CONFIG_SYS_PCIE_CFGBASE         0xD0000000
#define CONFIG_SYS_PCIE_MEMSIZE         0x10000000
#define CONFIG_SYS_PCIE_INBOUND_BASE    FixedPcdGet64(PcdSystemMemoryBase)

/* Physical Mapping Address */
#define CONFIG_SYS_PCIE0_PHYMEMBASE_HI  (UINT32) ((UINT64)XGENE_PCIE0_IOB_SPACE_BASE >> 32)
#define CONFIG_SYS_PCIE0_PHYMEMBASE_LO  ((UINT32) XGENE_PCIE0_IOB_SPACE_BASE)
#define CONFIG_SYS_PCIE1_PHYMEMBASE_HI  (UINT32) ((UINT64)XGENE_PCIE1_IOB_SPACE_BASE >> 32)
#define CONFIG_SYS_PCIE1_PHYMEMBASE_LO  ((UINT32) XGENE_PCIE1_IOB_SPACE_BASE)
#define CONFIG_SYS_PCIE2_PHYMEMBASE_HI  (UINT32) ((UINT64)XGENE_PCIE2_IOB_SPACE_BASE >> 32)
#define CONFIG_SYS_PCIE2_PHYMEMBASE_LO  ((UINT32) XGENE_PCIE2_IOB_SPACE_BASE)
#define CONFIG_SYS_PCIE3_PHYMEMBASE_HI  (UINT32) ((UINT64)XGENE_PCIE3_IOB_SPACE_BASE >> 32)
#define CONFIG_SYS_PCIE3_PHYMEMBASE_LO  ((UINT32) XGENE_PCIE3_IOB_SPACE_BASE)
#define CONFIG_SYS_PCIE4_PHYMEMBASE_HI  (UINT32) ((UINT64)XGENE_PCIE4_IOB_SPACE_BASE >> 32)
#define CONFIG_SYS_PCIE4_PHYMEMBASE_LO  ((UINT32) XGENE_PCIE4_IOB_SPACE_BASE)


/* PCIE0 - CSR Base Address */
#define PCIE_CSR_SIZE		(8*1024)
#define PCIE0_CSR_BASE_HI	((UINT32) ((UINT64)XGENE_PCIE0_CSR_BASE >> 32))
#define PCIE0_CSR_BASE_LO	((UINT32) XGENE_PCIE0_CSR_BASE)
/* PCIE0 - Configuration Base Address */
#define PCIE0_CFGBASE_HI	CONFIG_SYS_PCIE0_PHYMEMBASE_HI
#define PCIE0_CFGBASE_LO	(CONFIG_SYS_PCIE0_PHYMEMBASE_LO + \
				 CONFIG_SYS_PCIE_CFGBASE)
#define PCIE_CFGSIZE		CONFIG_SYS_PCIEX_CFGSIZE
/* PCIE0 - Message Base Address */
#define PCIE0_MSGBASE_HI	0x00000000
#define PCIE0_MSGBASE_LO	0x00000000
#define PCIE0_MSGSIZE		0	/* 0 for not used */
/* PCIE0 - Outbound I/O Base Address */
#define PCIE0_OB_IOBASE_HI	CONFIG_SYS_PCIE0_PHYMEMBASE_HI
#define PCIE0_OB_IOBASE_LO	(CONFIG_SYS_PCIE0_PHYMEMBASE_LO + 0x10000000)
#define PCIE0_OB_IOSIZE		0x00010000
/* PCIE0 - Outbound Memory 1 Base Address */
#define PCIE0_OB_MEMBASE0_HI	CONFIG_SYS_PCIE0_PHYMEMBASE_HI
#define PCIE0_OB_MEMBASE0_LO	(CONFIG_SYS_PCIE0_PHYMEMBASE_LO + 0x30000000)
#define PCIE0_OB_MEMSIZE0	0x40000000
/* PCIE0 - Outbound Memory 2 Base Address */
#define PCIE0_OB_MEMBASE1_HI	(CONFIG_SYS_PCIE0_PHYMEMBASE_HI + 1)
#define PCIE0_OB_MEMBASE1_LO	CONFIG_SYS_PCIE0_PHYMEMBASE_LO
#define PCIE0_OB_MEMSIZE1	0x40000000
/* * PCIE0 - Inbound Memory 1 Base Address */
#define PCIE0_IB_MEMBASE0_PCIE_HI	0x80
#define PCIE0_IB_MEMBASE0_PCIE_LO	0
#define PCIE0_IB_MEMSIZE0		0x100000000
#define PCIE0_IB_MEMBASE0_PIM_1_HI	0x80
#define PCIE0_IB_MEMBASE0_PIM_1_LO	0
#define PCIE0_IB_MEMBASE0_PIM_2_HI	0
#define PCIE0_IB_MEMBASE0_PIM_2_LO	0
#define PCIE0_IB_MEMBASE0_PIM_SIZE	0xffffffff80000000ULL

/* PCIE0 - Inbound Memory 2 Base Address */
#define PCIE0_IB_MEMBASE1_PCIE_HI	0
#define PCIE0_IB_MEMBASE1_PCIE_LO	0
#define PCIE0_IB_MEMSIZE1		0
#define PCIE0_IB_MEMBASE1_PIM_SIZE 0x0

#define PCIE0_IB_MEMBASE3_PCIE_HI 0x0
#define PCIE0_IB_MEMBASE3_PCIE_LO 0x0
#define PCIE0_IB_MEMSIZE3   0x8000000000ULL
#define PCIE0_IB_MEMBASE3_PIM_1_HI  0
#define PCIE0_IB_MEMBASE3_PIM_1_LO  0
#define PCIE0_IB_MEMBASE3_PIM_SIZE  0xFFFFFF8000000000ULL

#define PCIE0_IB_ROMBASE_HI		0
#define PCIE0_IB_ROMBASE_LO		0
#define PCIE0_IB_ROMSIZE		0

/* PCIE1 - CSR Base Address */
#define PCIE1_CSR_BASE_HI	((UINT32)((UINT64)XGENE_PCIE1_CSR_BASE >> 32))
#define PCIE1_CSR_BASE_LO	((UINT32) XGENE_PCIE1_CSR_BASE)
/* PCIE1 - Configuration Base Address */
#define PCIE1_CFGBASE_HI	CONFIG_SYS_PCIE1_PHYMEMBASE_HI
#define PCIE1_CFGBASE_LO	(CONFIG_SYS_PCIE1_PHYMEMBASE_LO + \
				 CONFIG_SYS_PCIE_CFGBASE)
/* PCIE1 - Message Base Address */
#define PCIE1_MSGBASE_HI	0x00000000
#define PCIE1_MSGBASE_LO	0x00000000
#define PCIE1_MSGSIZE		0	/* 0 for not used */
/* PCIE1 - Outbound I/O Base Address */
#define PCIE1_OB_IOBASE_HI	CONFIG_SYS_PCIE1_PHYMEMBASE_HI
#define PCIE1_OB_IOBASE_LO	(CONFIG_SYS_PCIE1_PHYMEMBASE_LO + 0x10000000)
#define PCIE1_OB_IOSIZE		0x00010000	/* 0 for not used */
/* PCIE1 - Outbound Memory 1 Base Address */
#define PCIE1_OB_MEMBASE0_HI	CONFIG_SYS_PCIE1_PHYMEMBASE_HI
#define PCIE1_OB_MEMBASE0_LO	(CONFIG_SYS_PCIE1_PHYMEMBASE_LO + 0x30000000)
#define PCIE1_OB_MEMSIZE0	CONFIG_SYS_PCIE_MEMSIZE
/* PCIE1 - Outbound Memory 2 Base Address */
#define PCIE1_OB_MEMBASE1_HI	CONFIG_SYS_PCIE1_PHYMEMBASE_HI
#define PCIE1_OB_MEMBASE1_LO	(CONFIG_SYS_PCIE1_PHYMEMBASE_LO + 0x80000000)
#define PCIE1_OB_MEMSIZE1	CONFIG_SYS_PCIE_MEMSIZE	/* 0 for not used */
/* * PCIE1 - Inbound Memory 1 Base Address */
#define PCIE1_IB_MEMBASE0_PCIE_HI	0x80
#define PCIE1_IB_MEMBASE0_PCIE_LO	0
#define PCIE1_IB_MEMSIZE0		0x80000000
#define PCIE1_IB_MEMBASE0_PIM_1_HI	0x80
#define PCIE1_IB_MEMBASE0_PIM_1_LO	0
#define PCIE1_IB_MEMBASE0_PIM_2_HI	0
#define PCIE1_IB_MEMBASE0_PIM_2_LO	0
#define PCIE1_IB_MEMBASE0_PIM_SIZE	0xffffffff80000000ULL

/* PCIE1 - Inbound Memory 2 Base Address */
#define PCIE1_IB_MEMBASE1_PCIE_HI	0
#define PCIE1_IB_MEMBASE1_PCIE_LO	0
#define PCIE1_IB_MEMSIZE1		0
#define PCIE1_IB_MEMBASE1_PIM_SIZE 0x0

#define PCIE1_IB_MEMBASE3_PCIE_HI 0x0
#define PCIE1_IB_MEMBASE3_PCIE_LO 0x0
#define PCIE1_IB_MEMSIZE3   0x8000000000ULL
#define PCIE1_IB_MEMBASE3_PIM_1_HI  0
#define PCIE1_IB_MEMBASE3_PIM_1_LO  0
#define PCIE1_IB_MEMBASE3_PIM_SIZE  0xFFFFFF8000000000ULL

#define PCIE1_IB_ROMBASE_HI		0
#define PCIE1_IB_ROMBASE_LO		0
#define PCIE1_IB_ROMSIZE		0

/* PCIE2 - CSR Base Address */
#define PCIE2_CSR_BASE_HI	((UINT32) ((UINT64)XGENE_PCIE2_CSR_BASE >> 32))
#define PCIE2_CSR_BASE_LO	((UINT32) XGENE_PCIE2_CSR_BASE)
/* PCIE2 - Configuration Base Address */
#define PCIE2_CFGBASE_HI	CONFIG_SYS_PCIE2_PHYMEMBASE_HI
#define PCIE2_CFGBASE_LO	(CONFIG_SYS_PCIE2_PHYMEMBASE_LO + \
				 CONFIG_SYS_PCIE_CFGBASE)
/* PCIE2 - Message Base Address */
#define PCIE2_MSGBASE_HI	0x00000000
#define PCIE2_MSGBASE_LO	0x00000000
#define PCIE2_MSGSIZE		0
/* PCIE2 - Outbound I/O Base Address */
#define PCIE2_OB_IOBASE_HI	CONFIG_SYS_PCIE2_PHYMEMBASE_HI
#define PCIE2_OB_IOBASE_LO	(CONFIG_SYS_PCIE2_PHYMEMBASE_LO + 0x10000000)
#define PCIE2_OB_IOSIZE		0x00010000	/* 0 for not used */
/* PCIE2 - Outbound Memory 1 Base Address */
#define PCIE2_OB_MEMBASE0_HI	CONFIG_SYS_PCIE2_PHYMEMBASE_HI
#define PCIE2_OB_MEMBASE0_LO	(CONFIG_SYS_PCIE2_PHYMEMBASE_LO + 0x30000000)
#define PCIE2_OB_MEMSIZE0	CONFIG_SYS_PCIE_MEMSIZE
/* PCIE2 - Outbound Memory 2 Base Address */
#define PCIE2_OB_MEMBASE1_HI	CONFIG_SYS_PCIE2_PHYMEMBASE_HI
#define PCIE2_OB_MEMBASE1_LO	(CONFIG_SYS_PCIE2_PHYMEMBASE_LO + 0x80000000)
#define PCIE2_OB_MEMSIZE1	CONFIG_SYS_PCIE_MEMSIZE	/* 0 for not used */
/* * PCIE2 - Inbound Memory 1 Base Address */
#define PCIE2_IB_MEMBASE0_PCIE_HI	0x80
#define PCIE2_IB_MEMBASE0_PCIE_LO	0
#define PCIE2_IB_MEMSIZE0		0x80000000
#define PCIE2_IB_MEMBASE0_PIM_1_HI	0x80
#define PCIE2_IB_MEMBASE0_PIM_1_LO	0
#define PCIE2_IB_MEMBASE0_PIM_2_HI	0
#define PCIE2_IB_MEMBASE0_PIM_2_LO	0
#define PCIE2_IB_MEMBASE0_PIM_SIZE	0xffffffff80000000ULL

/* PCIE0 - Inbound Memory 2 Base Address */
#define PCIE2_IB_MEMBASE1_PCIE_HI	0
#define PCIE2_IB_MEMBASE1_PCIE_LO	0
#define PCIE2_IB_MEMSIZE1		0
#define PCIE2_IB_MEMBASE1_PIM_SIZE 0x0

#define PCIE2_IB_MEMBASE3_PCIE_HI 0x0
#define PCIE2_IB_MEMBASE3_PCIE_LO 0x0
#define PCIE2_IB_MEMSIZE3   0x8000000000ULL
#define PCIE2_IB_MEMBASE3_PIM_1_HI  0
#define PCIE2_IB_MEMBASE3_PIM_1_LO  0
#define PCIE2_IB_MEMBASE3_PIM_SIZE  0xFFFFFF8000000000ULL

#define PCIE2_IB_ROMBASE_HI		0
#define PCIE2_IB_ROMBASE_LO		0
#define PCIE2_IB_ROMSIZE		0


/* PCIE3 - CSR Base Address */
#define PCIE3_CSR_BASE_HI	((UINT32) ((UINT64)XGENE_PCIE3_CSR_BASE >> 32))
#define PCIE3_CSR_BASE_LO	((UINT32) XGENE_PCIE3_CSR_BASE)
/* PCIE3 - Configuration Base Address */
#define PCIE3_CFGBASE_HI	CONFIG_SYS_PCIE3_PHYMEMBASE_HI
#define PCIE3_CFGBASE_LO	(CONFIG_SYS_PCIE3_PHYMEMBASE_LO + \
				 CONFIG_SYS_PCIE_CFGBASE)
/* PCIE3 - Message Base Address */
#define PCIE3_MSGBASE_HI	0x00000000
#define PCIE3_MSGBASE_LO	0x00000000
#define PCIE3_MSGSIZE		0
/* PCIE3 - Outbound I/O Base Address */
#define PCIE3_OB_IOBASE_HI	CONFIG_SYS_PCIE3_PHYMEMBASE_HI
#define PCIE3_OB_IOBASE_LO	(CONFIG_SYS_PCIE3_PHYMEMBASE_LO + 0x10000000)
#define PCIE3_OB_IOSIZE		0x10000	/* 0 for not used */
/* PCIE3 - Outbound Memory 1 Base Address */
#define PCIE3_OB_MEMBASE0_HI	CONFIG_SYS_PCIE3_PHYMEMBASE_HI
#define PCIE3_OB_MEMBASE0_LO	(CONFIG_SYS_PCIE3_PHYMEMBASE_LO + 0x30000000)
#define PCIE3_OB_MEMSIZE0	CONFIG_SYS_PCIE_MEMSIZE
/* PCIE3 - Outbound Memory 2 Base Address */
#define PCIE3_OB_MEMBASE1_HI	CONFIG_SYS_PCIE3_PHYMEMBASE_HI
#define PCIE3_OB_MEMBASE1_LO	(CONFIG_SYS_PCIE3_PHYMEMBASE_LO + 0x80000000)
#define PCIE3_OB_MEMSIZE1	CONFIG_SYS_PCIE_MEMSIZE	/* 0 for not used */
/* * PCIE3 - Inbound Memory 1 Base Address */
#define PCIE3_IB_MEMBASE0_PCIE_HI	0x80
#define PCIE3_IB_MEMBASE0_PCIE_LO	0
#define PCIE3_IB_MEMSIZE0		0x80000000
#define PCIE3_IB_MEMBASE0_PIM_1_HI	0x80
#define PCIE3_IB_MEMBASE0_PIM_1_LO	0
#define PCIE3_IB_MEMBASE0_PIM_2_HI	0
#define PCIE3_IB_MEMBASE0_PIM_2_LO	0
#define PCIE3_IB_MEMBASE0_PIM_SIZE	0xffffffff80000000ULL

/* PCIE0 - Inbound Memory 2 Base Address */
#define PCIE3_IB_MEMBASE1_PCIE_HI	0
#define PCIE3_IB_MEMBASE1_PCIE_LO	0
#define PCIE3_IB_MEMSIZE1		0
#define PCIE3_IB_MEMBASE1_PIM_SIZE 0x0

#define PCIE3_IB_MEMBASE3_PCIE_HI 0x0
#define PCIE3_IB_MEMBASE3_PCIE_LO 0x0
#define PCIE3_IB_MEMSIZE3   0x8000000000ULL
#define PCIE3_IB_MEMBASE3_PIM_1_HI  0
#define PCIE3_IB_MEMBASE3_PIM_1_LO  0
#define PCIE3_IB_MEMBASE3_PIM_SIZE  0xFFFFFF8000000000ULL

#define PCIE3_IB_ROMBASE_HI		0
#define PCIE3_IB_ROMBASE_LO		0
#define PCIE3_IB_ROMSIZE		0


/* PCIE4 - CSR Base Address */
#define PCIE4_CSR_BASE_HI	((UINT32) ((UINT64)XGENE_PCIE4_CSR_BASE >> 32))
#define PCIE4_CSR_BASE_LO	((UINT32) XGENE_PCIE4_CSR_BASE)
/* PCIE4 - Configuration Base Address */
#define PCIE4_CFGBASE_HI	CONFIG_SYS_PCIE4_PHYMEMBASE_HI
#define PCIE4_CFGBASE_LO	(CONFIG_SYS_PCIE4_PHYMEMBASE_LO + \
				 CONFIG_SYS_PCIE_CFGBASE)
/* PCIE4 - Message Base Address */
#define PCIE4_MSGBASE_HI	0x00000000
#define PCIE4_MSGBASE_LO	0x00000000
#define PCIE4_MSGSIZE		0
/* PCIE4 - Outbound I/O Base Address */
#define PCIE4_OB_IOBASE_HI	CONFIG_SYS_PCIE4_PHYMEMBASE_HI
#define PCIE4_OB_IOBASE_LO	(CONFIG_SYS_PCIE4_PHYMEMBASE_LO + 0x10000000)
#define PCIE4_OB_IOSIZE		0x10000	/* 0 for not used */
/* PCIE4 - Outbound Memory 1 Base Address */
#define PCIE4_OB_MEMBASE0_HI	CONFIG_SYS_PCIE4_PHYMEMBASE_HI
#define PCIE4_OB_MEMBASE0_LO	(CONFIG_SYS_PCIE4_PHYMEMBASE_LO + 0x30000000)
#define PCIE4_OB_MEMSIZE0	CONFIG_SYS_PCIE_MEMSIZE
/* PCIE4 - Outbound Memory 2 Base Address */
#define PCIE4_OB_MEMBASE1_HI	CONFIG_SYS_PCIE4_PHYMEMBASE_HI
#define PCIE4_OB_MEMBASE1_LO	(CONFIG_SYS_PCIE4_PHYMEMBASE_LO + 0x80000000)
#define PCIE4_OB_MEMSIZE1	CONFIG_SYS_PCIE_MEMSIZE	/* 0 for not used */
/* * PCIE4 - Inbound Memory 1 Base Address */
#define PCIE4_IB_MEMBASE0_PCIE_HI	0x80
#define PCIE4_IB_MEMBASE0_PCIE_LO	0
#define PCIE4_IB_MEMSIZE0		0x80000000
#define PCIE4_IB_MEMBASE0_PIM_1_HI	0x80
#define PCIE4_IB_MEMBASE0_PIM_1_LO	0
#define PCIE4_IB_MEMBASE0_PIM_2_HI	0
#define PCIE4_IB_MEMBASE0_PIM_2_LO	0
#define PCIE4_IB_MEMBASE0_PIM_SIZE	0xffffffff80000000ULL

/* PCIE0 - Inbound Memory 2 Base Address */
#define PCIE4_IB_MEMBASE1_PCIE_HI	0
#define PCIE4_IB_MEMBASE1_PCIE_LO	0
#define PCIE4_IB_MEMSIZE1		0
#define PCIE4_IB_MEMBASE1_PIM_SIZE 0x0

#define PCIE4_IB_MEMBASE3_PCIE_HI 0x0
#define PCIE4_IB_MEMBASE3_PCIE_LO 0x0
#define PCIE4_IB_MEMSIZE3   0x8000000000ULL
#define PCIE4_IB_MEMBASE3_PIM_1_HI  0
#define PCIE4_IB_MEMBASE3_PIM_1_LO  0
#define PCIE4_IB_MEMBASE3_PIM_SIZE  0xFFFFFF8000000000ULL

#define PCIE4_IB_ROMBASE_HI		0
#define PCIE4_IB_ROMBASE_LO		0
#define PCIE4_IB_ROMSIZE		0

#define XGENE_PCIE_MAX_PORTS      5

#define APMXGeneRevA1 1
#define APMXGeneRevA2 2
#define APMXGeneRevA3 3

/* clock */
#define PCIE_SRST     0xc000
#define PCIE_CLKEN      0xc008
#define CORE_CLKEN_MASK     0x00000002
#define CORE_RESET_MASK     0x00000002
#define PCIE_RESET_ALL_MASK 0x1f

#define CFG_8G_CONSTANTS_287_256  0x2120
#define CFG_8G_CONSTANTS_319_288  0x2124
#define CFG_8G_CONSTANTS_351_320  0x2128
#define CFG_8G_CONSTANTS_383_352  0x212c
#define CFG_8G_CONSTANTS_159_128  0x2110
#define CFG_CONTROL_95_64     0x2208
#define CFG_CONSTANTS_415_384   0x2030

/* generated macros to access bitfields */
#define PIPE_PHY_RATE_RD(src)     ((0xc000 & (u32)(src)) >> 0xe)
#define MGMT_US_PORT_TX_PRESET_SET(dst, src)  (((dst) & ~0xf00)| \
            (((u32)(src) << 0x8) & 0xf00))
#define MGMT_DS_PORT_TX_PRESET_SET(dst, src)  (((dst) & ~0xf) | \
            (((u32)(src)) & 0xf))

#define ENABLE_L1S_POWER_MGMT_MASK    0x02000000
#define ENABLE_L1S_POWER_MGMT_SHIFT_MASK    0x19
#define ENABLE_L1S_POWER_MGMT_SET(dst, src) (((dst) & ~ENABLE_L1S_POWER_MGMT_MASK) | \
            (((uint32_t)(src) << ENABLE_L1S_POWER_MGMT_SHIFT_MASK) & \
            ENABLE_L1S_POWER_MGMT_MASK))

#define EQ_UPDN_POST_STEP_MASK      0x00000030
#define EQ_UPDN_POST_STEP_SHIFT_MASK    0x4
#define EQ_UPDN_POST_STEP_SET(dst, src) (((dst) & ~EQ_UPDN_POST_STEP_MASK) | \
            (((uint32_t)(src) << EQ_UPDN_POST_STEP_SHIFT_MASK) & \
            EQ_UPDN_POST_STEP_MASK))

#define EQ_PRE_CURSOR_LANE0_MASK    0x000000ff
#define EQ_PRE_CURSOR_LANE0_SHIFT_MASK    0x0
#define EQ_PRE_CURSOR_LANE0_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE0_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE0_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE0_MASK))

#define EQ_PRE_CURSOR_LANE1_MASK    0x00ff0000
#define EQ_PRE_CURSOR_LANE1_SHIFT_MASK    0x10
#define EQ_PRE_CURSOR_LANE1_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE1_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE1_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE1_MASK))

#define EQ_PRE_CURSOR_LANE2_MASK    0x000000ff
#define EQ_PRE_CURSOR_LANE2_SHIFT_MASK    0x0
#define EQ_PRE_CURSOR_LANE2_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE2_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE2_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE2_MASK))

#define EQ_PRE_CURSOR_LANE3_MASK    0x00ff0000
#define EQ_PRE_CURSOR_LANE3_SHIFT_MASK    0x10
#define EQ_PRE_CURSOR_LANE3_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE3_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE3_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE3_MASK))

#define EQ_PRE_CURSOR_LANE4_MASK    0x000000ff
#define EQ_PRE_CURSOR_LANE4_SHIFT_MASK    0x0
#define EQ_PRE_CURSOR_LANE4_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE4_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE4_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE4_MASK))

#define EQ_PRE_CURSOR_LANE5_MASK    0x00ff0000
#define EQ_PRE_CURSOR_LANE5_SHIFT_MASK    0x10
#define EQ_PRE_CURSOR_LANE5_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE5_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE5_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE5_MASK))

#define EQ_PRE_CURSOR_LANE6_MASK    0x000000ff
#define EQ_PRE_CURSOR_LANE6_SHIFT_MASK    0x0
#define EQ_PRE_CURSOR_LANE6_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE6_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE6_SHIFT_MASK) & \
            EQ_PRE_CURSOR_LANE6_MASK))

#define EQ_PRE_CURSOR_LANE7_MASK    0x00ff0000
#define EQ_PRE_CURSOR_LANE7_SHIFT_MASK    0x10
#define EQ_PRE_CURSOR_LANE7_SET(dst, src) (((dst) & ~EQ_PRE_CURSOR_LANE7_MASK) | \
            (((uint32_t)(src) << EQ_PRE_CURSOR_LANE7_SHIFT_MASK) & \
             EQ_PRE_CURSOR_LANE7_MASK))


//int apm88xxx_chip_revision(void);

int
xgene_pcie_out32(void *addr, u32 val);

int
xgene_pcie_in32(void *addr, u32 *val);

int
xgene_pcie_cfg_out32(void *addr, u32 val);

int
xgene_pcie_cfg_out16(void *addr, u16 val);

int
xgene_pcie_cfg_out8(void *addr, u8 val);

int
xgene_pcie_cfg_in32(void *addr, u32 *val);

int
xgene_pcie_cfg_in16(void *addr, u16 *val);

int
xgene_pcie_cfg_in8(void *addr, u8 *val);

int
xgene_pcie_setup_core(struct xgene_pcie_port *port);

void
xgene_pcie_reset_port(struct xgene_pcie_port *port);

#endif /* __XGENEPCIECORE_H__ */

