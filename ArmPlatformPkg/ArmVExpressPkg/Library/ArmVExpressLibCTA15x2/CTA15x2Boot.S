//
//  Copyright (c) 2011, ARM Limited. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//

#include <AsmMacroIoLib.h>
#include <Base.h>
#include <Library/ArmPlatformLib.h>
#include <Drivers/PL35xSmc.h>
#include <Drivers/PL341Dmc.h>
#include <ArmPlatform.h>
#include <AutoGen.h>

.text
.align 3

GCC_ASM_EXPORT(ArmPlatformSecBootAction)
GCC_ASM_EXPORT(ArmPlatformInitializeBootMemory)
GCC_ASM_EXPORT(ArmPlatformSecBootMemoryInit)

/**
  Call at the beginning of the platform boot up

  This function allows the firmware platform to do extra actions at the early
  stage of the platform power up.

  Note: This function must be implemented in assembler as there is no stack set up yet

**/
ASM_PFX(ArmPlatformSecBootAction):
  bx    lr

/**
  Initialize the memory where the initial stacks will reside

  This memory can contain the initial stacks (Secure and Secure Monitor stacks).
  In some platform, this region is already initialized and the implementation of this function can
  do nothing. This memory can also represent the Secure RAM.
  This function is called before the satck has been set up. Its implementation must ensure the stack
  pointer is not used (probably required to use assembly language)

**/
ASM_PFX(ArmPlatformInitializeBootMemory):
        bx    lr


/**
  Initialize the memory where the initial stacks will reside

  This memory can contain the initial stacks (Secure and Secure Monitor stacks).
  In some platform, this region is already initialized and the implementation of this function can
  do nothing. This memory can also represent the Secure RAM.
  This function is called before the satck has been set up. Its implementation must ensure the stack
  pointer is not used (probably required to use assembly language)

**/
ASM_PFX(ArmPlatformSecBootMemoryInit):
  mov  r8, lr
  bl   smc_init
  bl   dmc_init
  bx   r8


/**
  Initialise the Static Memory Controller
**/
smc_init:

	//
	// Disable loop buffer for A15
	//
	MRC     p15, 0, r2, c0, c0, 0
	MOV     r1, r2, lsr #4
	LDR     r0, =0xFFF
	AND     r1, r1, r0
	LDR     r0, =0xC0F                      // See if A15
	CMP     r1, r0
	BNE     smc_init2                       // Go if not

	MRC     p15, 0, r1, c1, c0, 1           // Read Aux Ctrl Reg
	ORR     r1, r1, #(1 << 1)               // Set Bit 1
	MCR     p15, 0, r1, c1, c0, 1           // and write it back

smc_init2:

	LDR     r0, = ARM_VE_SMC_CTRL_BASE
	LDR     r2, = ARM_VE_SMB_PERIPH_BASE

	// CS0 - NOR0
	LDR     r1, = 0x0002393A
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000AAA
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x00400000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS1 - PSRAM
	LDR     r1, = 0x00027158
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000802
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x00C00000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS2 - usb, ethernet and vram
	LDR     r1, = 0x000CD2AA
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000046
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x01400000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS3 - IOFPGA peripherals
	LDR     r1, = 0x00025156
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000046
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x01C00000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS4 - NOR1
	LDR     r1, = 0x0002393A
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000AAA
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x02400000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS5 - unused
	LDR     r1, = 0x0002393A
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000AAA
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x02C00000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS6 - unused
	LDR     r1, = 0x0002393A
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000AAA
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x03400000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// CS7 - unused
	LDR     r1, = 0x0002393A
	STR     r1, [r0, #PL350_SMC_SET_CYCLES_OFFSET]
	LDR     r1, = 0x00000AAA
	STR     r1, [r0, #PL350_SMC_SET_OPMODE_OFFSET]
	LDR     r1, = 0x03C00000
	STR     r1, [r0, #PL350_SMC_DIRECT_CMD_OFFSET]

	// Set refresh period
        LDR     r1, = 0x1
        STR     r1, [r0, #0x20]

        LDR     r1, = 0x1
        STR     r1, [r0, #0x24]

	// page mode setup for VRAM
	LDR     r0, = 0x00FFFFFC
	ADD     r0, r0, r2

	// read current state
	LDR     r1, [r0, #0]
	LDR     r1, [r0, #0]
	LDR     r1, = 0x00000000
	STR     r1, [r0, #0]
	LDR     r1, [r0, #0]

	// enable page mode
	LDR     r1, [r0, #0]
	LDR     r1, [r0, #0]
	LDR     r1, = 0x00000000
	STR     r1, [r0, #0]
	LDR     r1, = 0x00900090
	STR     r1, [r0, #0]

	// confirm page mode enabled
	LDR     r1, [r0, #0]
	LDR     r1, [r0, #0]
	LDR     r1, = 0x00000000
	STR     r1, [r0, #0]
	LDR     r1, [r0, #0]

	BX      lr
	// end of smc_init


/**
  Initialise the PL341 Dynamic Memory Controller (DMC)

  On A15, the PHY needs to be locked before configuring the DMC.
  After DMC config, the PHY needs to be trained
**/
#define SCC_PHY_RESET_REG_OFFSET                     0x04

dmc_init:

	LDR     r0, = ARM_VE_DMC_BASE
	LDR     r1, = 0x00000400 // SCC reset bit for DDR PHY
	LDR     r2, = 0x7FEF0000 // PHY addr

	LDR     r3, =0x3
	STR     r3, [r2, #PHY_PTM_DFI_CLK_RANGE]
	LDR     r3, =0x0
	STR     r3, [r2, #PHY_PTM_PLL_RANGE]
	LDR     r3, =0x0
	STR     r3, [r2, #PHY_PTM_FEEBACK_DIV]
	LDR     r3, =0x0
	STR     r3, [r2, #PHY_PTM_RCLK_DIV]
	LDR     r3, =0x1
	STR     r3, [r2, #PHY_PTM_PLL_EN]

	// Wait for PHY to lock
waitloop_01:
	LDR     r3, [r2, #PHY_PTM_LOCK_STATUS]
	AND     r3, #0xff
	CMP     r3, #0x1
	BNE     waitloop_01

	LDR     r3, =0x5
	STR     r3, [r2, #PHY_PTM_IOTERM]
	LDR     r0, =ARM_VE_SCC_BASE
	LDR     r3, [r0, #SCC_PHY_RESET_REG_OFFSET]
	ORR     r3, r3, r1
	STR     r3, [r0, #SCC_PHY_RESET_REG_OFFSET]

	// wait for PHY ready
waitloop_03:
	LDR     r3, [r2, #PHY_PTM_INIT_DONE]
	AND     r3, #0x1
	TST     r3, #0x1
	BEQ     waitloop_03

	// Init PL341
	LDR     r0, = ARM_VE_DMC_BASE

	LDR     r1, =0x4 // enter config mode
	STR     r1, [r0, #DMC_COMMAND_REG]
	LDR     r1, =0xc30
	STR     r1, [r0, #DMC_REFRESH_PRD_REG]
	LDR     r1, =0xc
	STR     r1, [r0, #DMC_CAS_LATENCY_REG]
	LDR     r1, =0x5
	STR     r1, [r0, #DMC_WRITE_LATENCY_REG]
	LDR     r1, =0x2
	STR     r1, [r0, #DMC_T_MRD_REG]
	LDR     r1, =0x12
	STR     r1, [r0, #DMC_T_RAS_REG]
	LDR     r1, =0x18
	STR     r1, [r0, #DMC_T_RC_REG]
	LDR     r1, =0x0306
	STR     r1, [r0,#DMC_T_RCD_REG]
	LDR     r1, =0x00004c4f
	STR     r1, [r0, #DMC_T_RFC_REG]
	LDR     r1, =0x00000306
	STR     r1, [r0, #DMC_T_RP_REG]
	LDR     r1, =0x4
	STR     r1, [r0, #DMC_T_RRD_REG]
	LDR     r1, =0x6
	STR     r1, [r0, #DMC_T_WR_REG]
	LDR     r1, =0x3
	STR     r1, [r0, #DMC_T_WTR_REG]
	LDR     r1, =0x2
	STR     r1, [r0, #DMC_T_XP_REG]
	LDR     r1, =0x52
	STR     r1, [r0, #DMC_T_XSR_REG]
	LDR     r1, =0xc8
	STR     r1, [r0, #DMC_T_ESR_REG]
	LDR     r1, =0x0b0e
	STR     r1, [r0, #DMC_T_FAW_REG]
	LDR     r1, =0x3
	STR     r1, [r0, #DMC_T_RDATA_EN]
	LDR     r1, =0x1
	STR     r1, [r0, #DMC_T_WRLAT_DIFF]
	LDR     r1, =0x00210022
	STR     r1, [r0, #DMC_MEMORY_CONFIG_REG]
	LDR     r1, =0x0000007C
	STR     r1, [r0, #DMC_MEMORY_CFG2_REG]
	LDR     r1, =0x00000001
	STR     r1, [r0, #DMC_MEMORY_CFG3_REG]
	LDR     r1, =0x000000c0
	STR     r1, [r0, #DMC_CHIP_0_CFG_REG]
	LDR     r1, =0x00040c0
	STR     r1, [r0, #DMC_CHIP_1_CFG_REG]

	// Configure DDR2 Devices on Chip Select 0
	// nop
	LDR     r1, =0x000C0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// pre-charge all
	LDR     r1, =0x0
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_04:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_04

	// extended mode register 2 (EMR2)
	LDR     r1, =0x000A0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// extended mode register 3 (EMR3)
	LDR     r1, =0x000B0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// extended mode register (EMR), OCD default state
	LDR     r1, =0x00090000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set mode register (MR) with DLL reset
	LDR     r1,=0x00080B62
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// pre-charge all
	LDR     r1, =0x0
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// auto-refresh
	LDR     r1, =0x00040000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// auto-refresh
	LDR     r1, =0x00040000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set mode register (MR) without DLL reset
	LDR     r1,=0x00080A62
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_05:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_05

	// extended mode register (EMR) enable OCD defaults
	LDR     r1, =0x00094384
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_06:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_06

	// extended mode register (EMR) OCD Exit
	LDR     r1, =0x00094004
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_07:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_07

	// Configure DDR2 Devices on Chip Select 1
	// send nop
	// nop
	LDR     r1, =0x001C0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// pre-charge all
	LDR     r1, =0x00100000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_08:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_08

	// set extended mode register 2
	LDR     r1, =0x001A0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set extended mode register 3
	LDR     r1, =0x001B0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	//  extended mode register (EMR) OCD default state
	LDR     r1, =0x00190000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// mode register (MR) with DLL reset
	LDR     r1,=0x00180B62
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// pre-charge all
	LDR     r1, =0x00100000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// auto-refresh
	LDR     r1, =0x00140000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// auto-refresh
	LDR     r1, =0x00140000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]


	// mode register (MR) without DLL reset
	LDR     r1,=0x00180A62
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_09:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_09

	// extended mode register (EMR) enable OCD defaults
	LDR     r1, =0x00194384
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_10:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_10

	// extended mode register (EMR) OCD Exit
	LDR     r1, =0x00194004
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// wait loop
	LDR     r1, =0x0
waitloop_11:
	LDR     r3, [r0, #DMC_STATUS_REG]
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     waitloop_11

	// go command
	LDR     r1, =DMC_COMMAND_GO
	STR     r1, [r0, #DMC_COMMAND_REG]

	// wait for ready
waitloop_12:
	LDR     r1, [r0,#DMC_STATUS_REG]
	AND     r1, #0x3                // Mask of all but memc_status bits
	TST     r1,#1
	BEQ     waitloop_12

	// PHY Squelch Training
	LDR     r3, =0x1
	STR     r3, [r2, #PHY_PTM_SQU_TRAINING]

	LDR     r5, =0x80000000
waitloop_13:
	LDR     r4, =0
waitloop_14:
	LDR     r3, [r5, #0]
	ADD     r4, #1
	CMP     r4, #200
	BNE     waitloop_14

	// wait for ready
	LDR     r3, [r2,#PHY_PTM_SQU_STAT]
	TST     r3,#1
	BEQ     waitloop_13

	LDR     r3, =0
	STR     r3, [r2, #PHY_PTM_SQU_TRAINING]

	// For Test Chip Change Program architected timer frequency
	MRC     p15, 0, r0, c0, c1, 1           // CPUID_EXT_PFR1
	LSR     r0, r0, #16
	ANDS    r0, r0, #1                      // Check generic timer support
	BEQ     exit
	LDR     r0, = 600000000                 // 600MHz timer frequency
	MCR     p15, 0, r0, c14, c0, 0          // CNTFRQ

exit:
	bx      lr
	// end of dmc_init

