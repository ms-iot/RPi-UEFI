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
	LDR     r1, = ARM_VE_BOARD_PERIPH_BASE

	// On entry:-
	// r0 = base address of ssmc controller
	// r1 = address of system registers

	// Initializes V2P_CA5 dynamic memory controller

	MOV     r2, r1

	// set config mode
	MOV     r1, #0x4
	STR     r1, [r0, #DMC_COMMAND_REG]

	// initialise memory controlller

	// refresh period
	LDR     r1, =0x3D0
	STR     r1, [r0, #DMC_REFRESH_PRD_REG]

	// cas latency
	MOV     r1, #0xA
	STR     r1, [r0, #DMC_CAS_LATENCY_REG]

	// write latency
	MOV     r1, #0x3
	STR     r1, [r0, #DMC_WRITE_LATENCY_REG]

	// t_mrd
	MOV     r1, #0x2
	STR     r1, [r0, #DMC_T_MRD_REG]

	// t_ras
	MOV     r1, #0x0C
	STR     r1, [r0, #DMC_T_RAS_REG]

	// t_rc
	MOV     r1, #0x0F
	STR     r1, [r0, #DMC_T_RC_REG]

	// t_rcd
	LDR     r1, =0x00000104
	STR     r1, [r0,#DMC_T_RCD_REG]

	// t_rfc
	LDR     r1, =0x00001022
	STR     r1, [r0, #DMC_T_RFC_REG]

	// t_rp
	LDR     r1, =0x00000104
	STR     r1, [r0, #DMC_T_RP_REG]

	// t_rrd
	MOV     r1, #0x2
	STR     r1, [r0, #DMC_T_RRD_REG]

	// t_wr
	MOV     r1, #0x4
	STR     r1, [r0, #DMC_T_WR_REG]

	// t_wtr
	MOV     r1, #0x2
	STR     r1, [r0, #DMC_T_WTR_REG]

	// t_xp
	MOV     r1, #0x2
	STR     r1, [r0, #DMC_T_XP_REG]

	// t_xsr
	MOV     r1, #0xC8
	STR     r1, [r0, #DMC_T_XSR_REG]

	// t_esr
	MOV     r1, #0x04
	STR     r1, [r0, #DMC_T_ESR_REG]

	// t_faw
	LDR     r1, =0x00000407
	STR     r1, [r0, #DMC_T_FAW_REG]
	
	// set memory config
	LDR     r1, =0x0001001A
	STR     r1, [r0, #DMC_MEMORY_CONFIG_REG]

	// set memory config 2
	LDR     r1, =0x000000B0
	STR     r1, [r0, #DMC_MEMORY_CFG2_REG]

	// initialise external memory chips
	// set chip select for chip configuration
	LDR     r1, =0x000180C0
	STR     r1, [r0, #DMC_CHIP_0_CFG_REG]

	// config memories
	
	// send nop
	LDR     r1, =0x000C0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// delay
	MOV     r1, #0
B1: LDR     r3, [r0, #DMC_STATUS_REG]    	// read status register
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     B1		

	// pre-charge all
	MOV     r1, #0x0
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// delay
	MOV     r1, #0
B2:       LDR     r3, [r0, #DMC_STATUS_REG]    	// read status register
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     B2		

	// set extended mode register 2
	LDR     r1, =0x000A8000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set extended mode register 3
	MOV     r1, #0x000B0000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set extended mode register
	LDR     r1, =0x00094005
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set mode register -DLL reset
	LDR     r1, =0x00080552
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]
	
	// delay
	MOV     r1, #0		
B3:	LDR     r3, [r0, #DMC_STATUS_REG]    	// read status register
	ADD     r1, r1, #1
	CMP     r1, #10
	BLT     B3

	// pre-charge all
	MOV     r1, #0x0
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]
	
	// auto-refresh
	MOV     r1, #0x00040000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]
	
	// auto-refresh
	MOV     r1, #0x00040000
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]
	
	// set mode register
	LDR     r1, =0x00080452
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	// set extended mode register - Enable OCD defaults
	LDR     r1, =0x000943C5
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]
	
	// set extended mode register - OCD Exit
	LDR     r1, =0x00094047
	STR     r1, [r0, #DMC_DIRECT_CMD_REG]

	//----------------------------------------
	// go command
	MOV     r1, #0x0
	STR     r1, [r0, #DMC_COMMAND_REG]

	// wait for ready
B4:       LDR     r1, [r0,#DMC_STATUS_REG]
	TST     r1,#1
	BEQ     B4
	
exit:
	bx      lr
	// end of dmc_init

