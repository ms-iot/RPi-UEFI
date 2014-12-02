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

#include "XGenePcie.h"

enum {
        PORT_OK = 0,
        PORT_DISABLED
};

struct xgene_pcie_port *PortList;
UINT32 PcieMaxWidthSupport[XGENE_PCIE_MAX_PORTS] = {0x8, 0x4, 0x1, 0x8, 0x4};
struct xgene_pcie_map_tbl PcieMapTlb[XGENE_PCIE_MAX_PORTS] = {
  {
    /* PCIE 0 SPACE */
    MAKE_U64(PCIE0_CSR_BASE_HI, PCIE0_CSR_BASE_LO),
    PCIE_CSR_SIZE,
    PCIE0_CFGBASE_HI,
    PCIE0_CFGBASE_LO,
    PCIE_CFGSIZE,
    MAKE_U64(PCIE0_CFGBASE_HI,PCIE0_CFGBASE_LO),
    {
      {
        PCIE0_OB_MEMBASE0_HI,
        PCIE0_OB_MEMBASE0_LO,
        PCIE0_OB_MEMSIZE0,
        0,
        PCIE0_OB_MEMBASE0_LO
      },
      {
        PCIE0_OB_MEMBASE1_HI,
        PCIE0_OB_MEMBASE1_LO,
        PCIE0_OB_MEMSIZE1,
        PCIE0_OB_MEMBASE1_HI, /* 1:1 mapping */
        PCIE0_OB_MEMBASE1_LO
      },
      {
        PCIE0_OB_IOBASE_HI,
        PCIE0_OB_IOBASE_LO,
        PCIE0_OB_IOSIZE,
        0,
        PCIE0_OB_IOBASE_LO
      }
    },
    PCIE0_MSGBASE_HI, PCIE0_MSGBASE_LO, PCIE0_MSGSIZE,
    {
      {
        PCIE0_IB_MEMBASE0_PCIE_HI,
        PCIE0_IB_MEMBASE0_PCIE_LO,
        PCIE0_IB_MEMSIZE0,
        PCIE0_IB_MEMBASE0_PIM_1_HI,
        PCIE0_IB_MEMBASE0_PIM_1_LO,
        0,
        0,
        PCIE0_IB_MEMBASE0_PIM_SIZE
      },
      {
        PCIE0_IB_MEMBASE1_PCIE_HI,
        PCIE0_IB_MEMBASE1_PCIE_LO,
        PCIE0_IB_MEMSIZE1,
        0,
        0,
        0,
        0,
        PCIE0_IB_MEMBASE1_PIM_SIZE
      },
      {
        PCIE0_IB_MEMBASE3_PCIE_HI,
        PCIE0_IB_MEMBASE3_PCIE_LO,
        PCIE0_IB_MEMSIZE3,
        PCIE0_IB_MEMBASE3_PIM_1_HI,
        PCIE0_IB_MEMBASE3_PIM_1_LO,
        0,
        0,
        PCIE0_IB_MEMBASE3_PIM_SIZE
      },
    },
    PCIE0_IB_ROMBASE_HI,
    PCIE0_IB_ROMBASE_LO,
    PCIE0_IB_ROMSIZE
  },

  /* PCIE 1 SPACE */
  {
    MAKE_U64(PCIE1_CSR_BASE_HI, PCIE1_CSR_BASE_LO),
    PCIE_CSR_SIZE,
    PCIE1_CFGBASE_HI,
    PCIE1_CFGBASE_LO,
    PCIE_CFGSIZE,
    MAKE_U64(PCIE1_CFGBASE_HI,PCIE1_CFGBASE_LO),
    {
      {
        PCIE1_OB_MEMBASE0_HI,
        PCIE1_OB_MEMBASE0_LO,
        PCIE1_OB_MEMSIZE0,
        0,
        PCIE1_OB_MEMBASE0_LO
      },
      {
        PCIE1_OB_MEMBASE1_HI,
        PCIE1_OB_MEMBASE1_LO,
        PCIE1_OB_MEMSIZE1,
        0,
        PCIE1_OB_MEMBASE1_LO
      },
      {
        PCIE1_OB_IOBASE_HI,
        PCIE1_OB_IOBASE_LO,
        PCIE1_OB_IOSIZE,
        0,
        PCIE1_OB_IOBASE_LO
      }
    },
    PCIE1_MSGBASE_HI,
    PCIE1_MSGBASE_LO,
    PCIE1_MSGSIZE,
    {
      {
        PCIE1_IB_MEMBASE0_PCIE_HI,
        PCIE1_IB_MEMBASE0_PCIE_LO,
        PCIE1_IB_MEMSIZE0,
        PCIE1_IB_MEMBASE0_PIM_1_HI,
        PCIE1_IB_MEMBASE0_PIM_1_LO,
        0,
        0,
        PCIE1_IB_MEMBASE0_PIM_SIZE
      },
      {
        PCIE1_IB_MEMBASE1_PCIE_HI,
        PCIE1_IB_MEMBASE1_PCIE_LO,
        PCIE1_IB_MEMSIZE1,
        0,
        0,
        0,
        0,
        PCIE1_IB_MEMBASE1_PIM_SIZE
      },
      {
        PCIE1_IB_MEMBASE3_PCIE_HI,
        PCIE1_IB_MEMBASE3_PCIE_LO,
        PCIE1_IB_MEMSIZE3,
        PCIE1_IB_MEMBASE3_PIM_1_HI,
        PCIE1_IB_MEMBASE3_PIM_1_LO,
        0,
        0,
        PCIE1_IB_MEMBASE3_PIM_SIZE
      },
    },
    PCIE1_IB_ROMBASE_HI,
    PCIE1_IB_ROMBASE_LO,
    PCIE1_IB_ROMSIZE
  },

  /* PCIE 2 SPACE */
  {
    MAKE_U64(PCIE2_CSR_BASE_HI, PCIE2_CSR_BASE_LO),
    PCIE_CSR_SIZE,
    PCIE2_CFGBASE_HI,
    PCIE2_CFGBASE_LO,
    PCIE_CFGSIZE,
    MAKE_U64(PCIE2_CFGBASE_HI,PCIE2_CFGBASE_LO),
    {
      {
        PCIE2_OB_MEMBASE0_HI,
        PCIE2_OB_MEMBASE0_LO,
        PCIE2_OB_MEMSIZE0,
        0,
        PCIE2_OB_MEMBASE0_LO
      },
      {
        PCIE2_OB_MEMBASE1_HI,
        PCIE2_OB_MEMBASE1_LO,
        PCIE2_OB_MEMSIZE1,
        0,
        PCIE2_OB_MEMBASE1_LO
      },
      {
        PCIE2_OB_IOBASE_HI,
        PCIE2_OB_IOBASE_LO,
        PCIE2_OB_IOSIZE,
        0,
        PCIE2_OB_IOBASE_LO
      }
    },
    PCIE2_MSGBASE_HI,
    PCIE2_MSGBASE_LO,
    PCIE2_MSGSIZE,
    {
      {
        PCIE2_IB_MEMBASE0_PCIE_HI,
        PCIE2_IB_MEMBASE0_PCIE_LO,
        PCIE2_IB_MEMSIZE0,
        PCIE2_IB_MEMBASE0_PIM_1_HI,
        PCIE2_IB_MEMBASE0_PIM_1_LO,
        0,
        0,
        PCIE2_IB_MEMBASE0_PIM_SIZE
      },
      {
        PCIE2_IB_MEMBASE1_PCIE_HI,
        PCIE2_IB_MEMBASE1_PCIE_LO,
        PCIE2_IB_MEMSIZE1,
        0,
        0,
        0,
        0,
        PCIE2_IB_MEMBASE1_PIM_SIZE
      },
      {
        PCIE2_IB_MEMBASE3_PCIE_HI,
        PCIE2_IB_MEMBASE3_PCIE_LO,
        PCIE2_IB_MEMSIZE3,
        PCIE2_IB_MEMBASE3_PIM_1_HI,
        PCIE2_IB_MEMBASE3_PIM_1_LO,
        0,
        0,
        PCIE2_IB_MEMBASE3_PIM_SIZE
      },
    },
    PCIE2_IB_ROMBASE_HI,
    PCIE2_IB_ROMBASE_LO,
    PCIE2_IB_ROMSIZE
  },

  /* PCIE 3 SPACE */
  {
    MAKE_U64(PCIE3_CSR_BASE_HI, PCIE3_CSR_BASE_LO),
    PCIE_CSR_SIZE,
    PCIE3_CFGBASE_HI,
    PCIE3_CFGBASE_LO,
    PCIE_CFGSIZE,
    MAKE_U64(PCIE3_CFGBASE_HI,PCIE3_CFGBASE_LO),
    {
      {
        PCIE3_OB_MEMBASE0_HI,
        PCIE3_OB_MEMBASE0_LO,
        PCIE3_OB_MEMSIZE0,
        0,
        PCIE3_OB_MEMBASE0_LO
      },
      {
        PCIE3_OB_MEMBASE1_HI,
        PCIE3_OB_MEMBASE1_LO,
        PCIE3_OB_MEMSIZE1,
        0,
        PCIE3_OB_MEMBASE1_LO
      },
      {
        PCIE3_OB_IOBASE_HI,
        PCIE3_OB_IOBASE_LO,
        PCIE3_OB_IOSIZE,
        0,
        PCIE3_OB_IOBASE_LO
      }
    },
    PCIE3_MSGBASE_HI,
    PCIE3_MSGBASE_LO,
    PCIE3_MSGSIZE,
    {
      {
        PCIE3_IB_MEMBASE0_PCIE_HI,
        PCIE3_IB_MEMBASE0_PCIE_LO,
        PCIE3_IB_MEMSIZE0,
        PCIE3_IB_MEMBASE0_PIM_1_HI,
        PCIE3_IB_MEMBASE0_PIM_1_LO,
        0,
        0,
        PCIE3_IB_MEMBASE0_PIM_SIZE
      },
      {
        PCIE3_IB_MEMBASE1_PCIE_HI,
        PCIE3_IB_MEMBASE1_PCIE_LO,
        PCIE3_IB_MEMSIZE1,
        0,
        0,
        0,
        0,
        PCIE3_IB_MEMBASE1_PIM_SIZE
      },
      {
        PCIE3_IB_MEMBASE3_PCIE_HI,
        PCIE3_IB_MEMBASE3_PCIE_LO,
        PCIE3_IB_MEMSIZE3,
        PCIE3_IB_MEMBASE3_PIM_1_HI,
        PCIE3_IB_MEMBASE3_PIM_1_LO,
        0,
        0,
        PCIE3_IB_MEMBASE3_PIM_SIZE
      },
    },
    PCIE3_IB_ROMBASE_HI,
    PCIE3_IB_ROMBASE_LO,
    PCIE3_IB_ROMSIZE
  },

  /* PCIE 4 SPACE */
  {
    MAKE_U64(PCIE4_CSR_BASE_HI, PCIE4_CSR_BASE_LO),
    PCIE_CSR_SIZE,
    PCIE4_CFGBASE_HI,
    PCIE4_CFGBASE_LO,
    PCIE_CFGSIZE,
    MAKE_U64(PCIE4_CFGBASE_HI,PCIE4_CFGBASE_LO),
    {
      {
        PCIE4_OB_MEMBASE0_HI,
        PCIE4_OB_MEMBASE0_LO,
        PCIE4_OB_MEMSIZE0,
        0,
        PCIE4_OB_MEMBASE0_LO
      },
      {
        PCIE4_OB_MEMBASE1_HI,
        PCIE4_OB_MEMBASE1_LO,
        PCIE4_OB_MEMSIZE1,
        0,
        PCIE4_OB_MEMBASE1_LO
      },
      {
        PCIE4_OB_IOBASE_HI,
        PCIE4_OB_IOBASE_LO,
        PCIE4_OB_IOSIZE,
        0,
        PCIE4_OB_IOBASE_LO
      }
    },
    PCIE4_MSGBASE_HI,
    PCIE4_MSGBASE_LO,
    PCIE4_MSGSIZE,
    {
      {
        PCIE4_IB_MEMBASE0_PCIE_HI,
        PCIE4_IB_MEMBASE0_PCIE_LO,
        PCIE4_IB_MEMSIZE0,
        PCIE4_IB_MEMBASE0_PIM_1_HI,
        PCIE4_IB_MEMBASE0_PIM_1_LO,
        PCIE4_IB_MEMBASE0_PIM_2_HI,
        PCIE4_IB_MEMBASE0_PIM_2_LO,
        PCIE4_IB_MEMBASE0_PIM_SIZE
      },
      {
        PCIE4_IB_MEMBASE1_PCIE_HI,
        PCIE4_IB_MEMBASE1_PCIE_LO,
        PCIE4_IB_MEMSIZE1,
        0,
        0,
        0,
        0,
        PCIE4_IB_MEMBASE1_PIM_SIZE
      },
      {
        PCIE4_IB_MEMBASE3_PCIE_HI,
        PCIE4_IB_MEMBASE3_PCIE_LO,
        PCIE4_IB_MEMSIZE3,
        PCIE4_IB_MEMBASE3_PIM_1_HI,
        PCIE4_IB_MEMBASE3_PIM_1_LO,
        0,
        0,
        PCIE4_IB_MEMBASE3_PIM_SIZE
      },
    },
    PCIE4_IB_ROMBASE_HI,
    PCIE4_IB_ROMBASE_LO,
    PCIE4_IB_ROMSIZE
  }
};

INTN IsPciRoot(INTN Port)
{
  return PortList[Port].type == PTYPE_ENDPOINT ? 0 : 1;
}


INTN IsPortAvailable(INTN Port)
{
  return PortList[Port].status == PORT_DISABLED ? 0 : 1;
}

VOID DisablePort (INTN Port)
{
  PortList[Port].status = PORT_DISABLED;
}

VOID EnablePort (INTN Port)
{
  PortList[Port].status = PORT_OK;
}

INTN SetupPortType(VOID)
{
  UINT32   PcieGen = PcdGet32(PcdPcieRootBridgeGen);
  UINT32   PcieWidth = PcdGet32(PcdPcieRootBridgeWidth);
  INTN i = 0;
  INTN Speed, Width;

  for(i = 0; i < XGENE_PCIE_MAX_PORTS; i++) {
    Speed = ((PcieGen >> (i*4)) & 0xF) - 1;
    if (Speed < PCIE_GEN1 || Speed > PCIE_GEN3) {
      continue;
    }
    PortList[i].link_speed = Speed;
    PCIE_VDEBUG("PORT%d GEN %d\n", i, Speed + 1);

  }

  for(i = 0; i < XGENE_PCIE_MAX_PORTS; i++) {
    Width = (PcieWidth >> (i*4)) & 0xF;

    if ((Width != LNKW_X8) && (Width != LNKW_X4) &&
        (Width != LNKW_X1)) {
      continue;
    }
    /* setting Width higher than max supported */
    if (Width > PcieMaxWidthSupport[i]) {
      PCIE_VDEBUG("PORT%d WIDTH %d is not supported\n", i, Width);
      PCIE_DEBUG ("PCIE port %d disabled\n",i);
      PortList[i].status = PORT_DISABLED;
      continue;
    }

    PCIE_VDEBUG("PORT%d WIDTH %d\n", i, Width);
    PortList[i].link_width = Width;

    if (i == 1 || i == 4) {
      if (PortList[i-1].link_width == LNKW_X8) {
        PCIE_DEBUG ("Link Width setting for port %d and port %d are incompatible.\n",
            i, i-1);
        PCIE_DEBUG ("PCIE port %d disabled\n",i);
        PortList[i].status = PORT_DISABLED;
      }
    }
  }

  for(i = 0; i < XGENE_PCIE_MAX_PORTS; i++) {
    PortList[i].index = i;
    PortList[i].type = PTYPE_ROOT_PORT;
    PortList[i].last_busno = 1;
   }

  return 0;
}

VOID CheckPortStatus(VOID)
{
  INTN i;
  for (i = 0; i < XGENE_PCIE_MAX_PORTS; i++) {
    DisablePort(i);
    if ((PcdGet32(PcdPcieRootBridgeMask) >> i) & 0x1) {
      EnablePort(i);
    } else {
      PCIE_DEBUG("PORT%d is disabled\n", i);
    }
  }
}


EFI_STATUS
EFIAPI
XGenePcieSetupPrimaryBus(UINT32 Index, UINT32 FirstBus, UINT32 LastBus)
{
  UINT32 Val;
  struct xgene_pcie_port *Port = &PortList[Index];
  VOID *CfgAddr = Port->cfg_base;

  Port->first_busno = FirstBus;
  Port->last_busno = LastBus;

  xgene_pcie_in32(CfgAddr + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, &Val);
  Val &= 0xFF000000;
  Val |= (FirstBus << 8) | (LastBus << 16);
  xgene_pcie_out32(CfgAddr + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, Val);
  xgene_pcie_in32(CfgAddr + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET, &Val);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
XGenePcieSetupHostPre()
{

  PortList = (struct xgene_pcie_port *)
             AllocateZeroPool(sizeof(struct xgene_pcie_port) * XGENE_PCIE_MAX_PORTS);
  if (PortList == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CheckPortStatus();
  SetupPortType();

  return EFI_SUCCESS;
}

//VOID XgenePcieAdjustRanges(struct xgene_pcie_port *port)
//{
//  struct xgene_pcie_map_tbl *hb = port->map_tbl;
//  EFI_PHYSICAL_ADDRESS ram_addr = CONFIG_SYS_PCIE_INBOUND_BASE;
//  UINT64 ram_size = *(UINT64*)(UINT64)PcdGet64(PcdMemSizeAddr);
//  UINT64 pim = (ram_addr & ~(ram_size - 1));
//
//  hb->ib_mem_addr[0].pcie_hi = upper_32_bits(ram_addr);
//  hb->ib_mem_addr[0].pcie_lo = lower_32_bits(ram_addr);
//  hb->ib_mem_addr[0].pcie_size = ram_size;
//  hb->ib_mem_addr[0].pim1_hi = upper_32_bits(pim);
//  hb->ib_mem_addr[0].pim1_lo = lower_32_bits(pim);
//  hb->ib_mem_addr[0].pim2_hi = 0;
//  hb->ib_mem_addr[0].pim2_lo = 0;
//  hb->ib_mem_addr[0].pim_size = (u64) ~(hb->ib_mem_addr[0].pcie_size - 1);
//
//}

EFI_STATUS
EFIAPI
XGenePcieReset(VOID)
{
  struct xgene_pcie_port *Port = NULL;
  INTN Count;

  CheckPortStatus();
  SetupPortType();

  for (Count = 0; Count < XGENE_PCIE_MAX_PORTS; Count++) {
    Port = &PortList[Count];
    if (Port->status != PORT_OK)
      continue;
    PCIE_DEBUG("Resetting PCIe%d\n", Count);
    xgene_pcie_reset_port(Port);
    PCIE_DEBUG("Resetted PCIe%d\n", Count);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
XGenePcieSetupHostPost(UINT32 Index, PCI_HOST_BRIDGE_INSTANCE *HostInstance)
{
  struct xgene_pcie_port *Port = &PortList[Index];
  PCIE_DEBUG("\nSetting up PCIe%d as ROOT COMPLEX\n", Index);

  Port->type = PTYPE_ROOT_PORT;
  Port->map_tbl = &PcieMapTlb[Index];
  Port->csr_base = (VOID *)PcieMapTlb[Index].csr_addr;
  Port->cfg_base = (VOID *)PcieMapTlb[Index].cfg_vaddr;
  Port->host = (VOID *)HostInstance;

  //XgenePcieAdjustRanges(Port);
  xgene_pcie_setup_core(Port);

  if (Port->link_up) {
    PCIE_INFO("PCIE%d: (RC) X%d GEN-%d link up\n", Index,
        Port->cur_link_width, Port->cur_link_speed + 1);
    XGenePcieSetupPrimaryBus(Index, XGENE_PCIE_FIRST_BUS, XGENE_PCIE_LAST_BUS);
  } else {
    PCIE_INFO("PCIE%d: (RC) link down\n", Index);
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

/**
  Reads/Writes an PCI configuration register.

  Reads/Writes from/to register specified by Address.
  This function must guarantee that all PCI read and write operations are
  serialized.

  If Address > 0x0FFFFFFF, then ASSERT().
**/

#define PCIE_OP(rw,size,type,op,mask)                                 \
EFI_STATUS                                                                \
EFIAPI                                                                    \
XGenePcie##rw##Config##size(                                           \
  IN      PCI_ROOT_BRIDGE_INSTANCE *RootInstance,                         \
  IN      UINTN                     Address,                              \
  IN      type                      Val                                  \
  )                                                                       \
{                                                                         \
  struct xgene_pcie_port *Port = NULL;                                      \
  VOID    *CsrBase = NULL;                                                \
  VOID    *CfgBase = NULL;                                                \
  PCI_HOST_BRIDGE_INSTANCE *HostInstance = NULL;                          \
  LIST_ENTRY                            *List;                            \
  UINTN Index;                                                            \
  UINT32 Bus, Dev, Func, Reg;                                             \
  UINT32 Port_ID = XGENE_PCIE_MAX_PORTS;                                    \
  UINT32 TmpVal;                                                          \
  ASSERT(Address <= 0x0FFFFFFF);                                          \
                                                                          \
  for (Index = 0; Index < XGENE_PCIE_MAX_PORTS; Index++) {                  \
    Port = &PortList[Index];                                              \
    HostInstance = (PCI_HOST_BRIDGE_INSTANCE *)Port->host;                \
    if (HostInstance == NULL)                                             \
      continue;                                                           \
    List = HostInstance->Head.ForwardLink;                                \
                                                                          \
    while (List != &HostInstance->Head) {                                 \
      PCI_ROOT_BRIDGE_INSTANCE *TmpRootInstance;                          \
      TmpRootInstance = DRIVER_INSTANCE_FROM_LIST_ENTRY (List);           \
      if (TmpRootInstance == RootInstance) {                              \
        Port_ID = Index;                                                  \
        Index = XGENE_PCIE_MAX_PORTS;                                       \
        break;                                                            \
      }                                                                   \
                                                                          \
      List = List->ForwardLink;                                           \
    }                                                                     \
  }                                                                       \
                                                                          \
  if (Port_ID == XGENE_PCIE_MAX_PORTS || Port == NULL) {                    \
    PCIE_ERR("Can't find port id for Root Instance:%p\n", RootInstance);  \
    return EFI_INVALID_PARAMETER;                                         \
  }                                                                       \
                                                                          \
  Bus = (Address >> 20) & 0xFF;                                           \
  Dev = (Address >> 15) & 0x1F;                                           \
  Func = (Address >> 12) & 0x07;                                          \
  Reg = (Address) & 0xFFF;                                                \
                                                                          \
  CsrBase = (VOID *) Port->csr_base;                \
  if (Bus > Port->first_busno)                                            \
    CfgBase = (VOID *)((UINT64)Port->cfg_base | 0x10000);  \
  else                                                                    \
    CfgBase = (VOID *)(Port->cfg_base);            \
                                                                          \
  xgene_pcie_out32(CsrBase + RTDID,                  \
      (Bus << 8) | (Dev << 3) | (Func << 0));                             \
  xgene_pcie_in32(CsrBase + RTDID, &TmpVal);         \
  (op)((VOID *)(CfgBase + (Reg & (~mask))), Val);                         \
  xgene_pcie_out32(CsrBase + RTDID, 0);              \
  xgene_pcie_in32(CsrBase + RTDID, &TmpVal);         \
  return EFI_SUCCESS;                                                     \
}

PCIE_OP(Read,8,UINT8 *,xgene_pcie_cfg_in8,0)
PCIE_OP(Read,16,UINT16 *,xgene_pcie_cfg_in16,1)
PCIE_OP(Read,32,UINT32 *,xgene_pcie_cfg_in32,3)
PCIE_OP(Write,8,UINT8,xgene_pcie_cfg_out8,0)
PCIE_OP(Write,16,UINT16,xgene_pcie_cfg_out16,1)
PCIE_OP(Write,32,UINT32,xgene_pcie_cfg_out32,3)

