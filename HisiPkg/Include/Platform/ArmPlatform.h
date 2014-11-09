/** @file
*  Header defining Versatile Express constants (Base addresses, sizes, flags)
*
*  Copyright (c) 2011, ARM Limited. All rights reserved.
*  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
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

#ifndef __ARM_D01_H__
#define __ARM_D01_H__

#define IS_PRIMARY_CORE(MpId) (((MpId) & PcdGet32(PcdArmPrimaryCoreMask)) == PcdGet32(PcdArmPrimaryCore))


/***********************************************************************************
// Motherboard memory-mapped peripherals
************************************************************************************/

// Define MotherBoard SYS flags offsets (from ARM_VE_BOARD_PERIPH_BASE)
#define ARM_VE_SYS_ID_REG                         (ARM_VE_BOARD_PERIPH_BASE + 0x00000)
#define ARM_VE_SYS_SW_REG                         (ARM_VE_BOARD_PERIPH_BASE + 0x00004)
#define ARM_VE_SYS_LED_REG                        (ARM_VE_BOARD_PERIPH_BASE + 0x00008)
#define ARM_VE_SYS_FLAGS_REG                      (ARM_VE_BOARD_PERIPH_BASE + 0x00030)
#define ARM_VE_SYS_FLAGS_SET_REG                  (ARM_VE_BOARD_PERIPH_BASE + 0x00030)
#define ARM_VE_SYS_FLAGS_CLR_REG                  (ARM_VE_BOARD_PERIPH_BASE + 0x00034)
#define ARM_VE_SYS_FLAGS_NV_REG                   (ARM_VE_BOARD_PERIPH_BASE + 0x00038)
#define ARM_VE_SYS_FLAGS_NV_SET_REG               (ARM_VE_BOARD_PERIPH_BASE + 0x00038)
#define ARM_VE_SYS_FLAGS_NV_CLR_REG               (ARM_VE_BOARD_PERIPH_BASE + 0x0003C)
#define ARM_VE_SYS_FLASH                          (ARM_VE_BOARD_PERIPH_BASE + 0x0004C)
#define ARM_VE_SYS_CFGSWR_REG                     (ARM_VE_BOARD_PERIPH_BASE + 0x00058)
#define ARM_VE_SYS_MISC                           (ARM_VE_BOARD_PERIPH_BASE + 0x00060)
#define ARM_VE_SYS_PROCID0_REG                    (ARM_VE_BOARD_PERIPH_BASE + 0x00084)
#define ARM_VE_SYS_PROCID1_REG                    (ARM_VE_BOARD_PERIPH_BASE + 0x00088)
#define ARM_VE_SYS_CFGDATA_REG                    (ARM_VE_BOARD_PERIPH_BASE + 0x000A0)
#define ARM_VE_SYS_CFGCTRL_REG                    (ARM_VE_BOARD_PERIPH_BASE + 0x000A4)
#define ARM_VE_SYS_CFGSTAT_REG                    (ARM_VE_BOARD_PERIPH_BASE + 0x000A8)

// SP810 Controller
#ifndef SP810_CTRL_BASE
#define SP810_CTRL_BASE                           (ARM_VE_BOARD_PERIPH_BASE + 0x01000)
#endif

// PL111 Colour LCD Controller - motherboard
#define PL111_CLCD_MOTHERBOARD_BASE               (ARM_VE_BOARD_PERIPH_BASE + 0x1F000)
#define PL111_CLCD_MOTHERBOARD_VIDEO_MODE_OSC_ID  1

// VRAM offset for the PL111 Colour LCD Controller on the motherboard
#define VRAM_MOTHERBOARD_BASE                     (ARM_VE_SMB_PERIPH_BASE   + 0x00000)

#define ARM_VE_SYS_PROC_ID_HBI                    0xFFF
#define ARM_VE_SYS_PROC_ID_MASK                   (UINT32)(0xFFU << 24)
#define ARM_VE_SYS_PROC_ID_UNSUPPORTED            (UINT32)(0xFFU << 24)
#define ARM_VE_SYS_PROC_ID_CORTEX_A9              (UINT32)(0x0CU << 24)
#define ARM_VE_SYS_PROC_ID_CORTEX_A5              (UINT32)(0x12U << 24)
#define ARM_VE_SYS_PROC_ID_CORTEX_A15             (UINT32)(0x14U << 24)

// Boot Master Select:
// 0 = Site 1 boot master
// 1 = Site 2 boot master
#define ARM_VE_SYS_MISC_MASTERSITE                (1 << 14)
//
// Sites where the peripheral is fitted
//
#define ARM_VE_UNSUPPORTED                        ~0
#define ARM_VE_MOTHERBOARD_SITE                   0
#define ARM_VE_DAUGHTERBOARD_1_SITE               1
#define ARM_VE_DAUGHTERBOARD_2_SITE               2

#define VIRTUAL_SYS_CFG(site,func)                (((site) << 24) | (func))

//
// System Configuration Control Functions
//
#define SYS_CFG_OSC                               1
#define SYS_CFG_VOLT                              2
#define SYS_CFG_AMP                               3
#define SYS_CFG_TEMP                              4
#define SYS_CFG_RESET                             5
#define SYS_CFG_SCC                               6
#define SYS_CFG_MUXFPGA                           7
#define SYS_CFG_SHUTDOWN                          8
#define SYS_CFG_REBOOT                            9
#define SYS_CFG_DVIMODE                           11
#define SYS_CFG_POWER                             12
// Oscillator for Site 1
#define SYS_CFG_OSC_SITE1                         VIRTUAL_SYS_CFG(ARM_VE_DAUGHTERBOARD_1_SITE,SYS_CFG_OSC)
// Oscillator for Site 2
#define SYS_CFG_OSC_SITE2                         VIRTUAL_SYS_CFG(ARM_VE_DAUGHTERBOARD_2_SITE,SYS_CFG_OSC)
// Can not access the battery backed-up hardware clock on the Versatile Express motherboard
#define SYS_CFG_RTC                               VIRTUAL_SYS_CFG(ARM_VE_UNSUPPORTED,1)

//
// System ID
//
// All RTSM VE models have the same System ID : 0x225F500
//
// FVP models have a different System ID.
// Default Base model System ID : 0x00201100
// [31:28] Rev     - Board revision:          0x0     = Rev A
// [27:16] HBI     - HBI board number in BCD: 0x020   = v8 Base Platform
// [15:12] Variant - Build variant of board:  0x1     = Variant B. (GIC 64k map)
// [11:8]  Plat    - Platform type:           0x1     = Model
// [7:0]   FPGA    - FPGA build, BCD coded:   0x00
//
//HBI = 010 = Foundation Model
//HBI = 020 = Base Platform
//
// And specifically, the GIC register banks start at the following
// addresses:
//              Variant = 0             Variant = 1
//GICD          0x2c001000              0x2f000000
//GICC          0x2c002000              0x2c000000
//GICH          0x2c004000              0x2c010000
//GICV          0x2c006000              0x2c020000

// The default SYS_IDs. These can be changed when starting the model.
#define ARM_RTSM_SYS_ID                (0x225F500)
#define ARM_FVP_BASE_SYS_ID            (0x00201100)
#define ARM_FVP_FOUNDATION_SYS_ID      (0x00101100)

#define ARM_FVP_SYS_ID_VARIANT_MASK    (UINT32)(0xFUL << 12)



/***********************************************************************************
// Platform Memory Map
************************************************************************************/

// Can be NOR0, NOR1, DRAM
#define ARM_VE_REMAP_BASE                       0x00000000
#define ARM_VE_REMAP_SZ                         SIZE_64MB

// Motherboard Peripheral and On-chip peripheral
#define ARM_VE_BOARD_PERIPH_BASE                0x1C010000

// NOR Flash 1
// There is typo in the reference manual for the Base address of NOR Flash 1
#define ARM_VE_SMB_NOR0_BASE                    0x08000000
#define ARM_VE_SMB_NOR0_SZ                      SIZE_64MB
// NOR Flash 2
#define ARM_VE_SMB_NOR1_BASE                    0x0C000000
#define ARM_VE_SMB_NOR1_SZ                      SIZE_64MB
// SRAM
#define ARM_VE_SMB_SRAM_BASE                    0x2E000000
#define ARM_VE_SMB_SRAM_SZ                      SIZE_64KB
// USB, Ethernet, VRAM
#define ARM_VE_SMB_PERIPH_BASE                  0x18000000
#define PL111_CLCD_VRAM_MOTHERBOARD_BASE        ARM_VE_SMB_PERIPH_BASE
#define ARM_VE_SMB_PERIPH_SZ                    SIZE_64MB

// DRAM
#define ARM_VE_DRAM_BASE                        PcdGet32 (PcdSystemMemoryBase)
#define ARM_VE_DRAM_SZ                          PcdGet32 (PcdSystemMemorySize)

// This can be any value since we only support motherboard PL111
#define LCD_VRAM_CORE_TILE_BASE                 0x00000000

// On-chip peripherals (Snoop Control Unit etc...)
#define ARM_VE_ON_CHIP_PERIPH_BASE              0x2C000000
// Note: The TRM says not all the peripherals are implemented
#define ARM_VE_ON_CHIP_PERIPH_SZ                SIZE_256MB


// External AXI between daughterboards (Logic Tile)
#define ARM_VE_EXT_AXI_BASE                     0x2E010000 // Not modelled
#define ARM_VE_EXT_AXI_SZ                       0x20000000  /* 512 MB */

/***********************************************************************************
// Memory-mapped peripherals
************************************************************************************/

// SP810 Controller
#undef SP810_CTRL_BASE
#define SP810_CTRL_BASE                         0x1C020000

// PL111 Colour LCD Controller
#define PL111_CLCD_SITE                         ARM_VE_MOTHERBOARD_SITE
#define PL111_CLCD_MOTHERBOARD_VIDEO_MODE_OSC_ID  1
#define PL111_CLCD_CORE_TILE_VIDEO_MODE_OSC_ID  1

// VRAM offset for the PL111 Colour LCD Controller on the motherboard
#define VRAM_MOTHERBOARD_BASE                     (ARM_VE_SMB_PERIPH_BASE   + 0x00000)

#endif
