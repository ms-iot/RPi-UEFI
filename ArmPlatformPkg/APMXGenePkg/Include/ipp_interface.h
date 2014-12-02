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
 * @version 1.0
 * @author Prodyut Hazarika (phazarika@amcc.com)
 * @author Anup Patel (apatel@amcc.com)
 * 
 * @endcond
 * 
 * @file apm_ipp_interface.h
 * @brief Interface definition between iPP and PowerPC
 *
 * This module defines the interface between iPP and X-Gene.
 *
 **/

#ifndef __IPP_INTERFACE_H__
#define __IPP_INTERFACE_H__

/** 
 * @name iPP to PPC message structure and message encoding/decoding macros 
 * 
 * @code
 * Bit Definitions in IBM convention
 * 0       4             8          16        24      31  
 * ----------------------------------------------------- 
 * MsgType | Hdlr/SubCmd | CtrlByte | P0/Rsvd | P1/Rsvd |
 * ----------------------------------------------------- 
 * Software Defined message between iPP<->PPC
 * Scratch1 Reg used by PPC1 and Scratch2 Reg by PPC2
 * to send additional 4 bytes to iPP - encoded per cmd  
 * MsgType: Upper Nibble in MSB identifies command type           
 * Hdlr/SubCmd: Lower Nibble in MDB identify subcmd or handler ID 
 * Control Byte: Control Byte - Must not be used for command data 
 * P0: Byte for Command Data - encoded per message type           
 * P1: LSB byte for Command Data - encoded per message type
 * @endcode
 */
/*@{*/
#define IPP_MSG_TYPE_MASK			0xF0000000U
#define IPP_MSG_TYPE_SHIFT			28
#define IPP_MSG_CONTROL_BYTE_MASK		0x00FF0000U
#define IPP_MSG_CONTROL_BYTE_SHIFT		16
#define IPP_DATA_MSG_HNDL_MASK 			0x0F000000U
#define IPP_DATA_MSG_HNDL_SHIFT 		24	
#define IPP_DATA_MSG_CTRL_BYTE_MASK 		0x0000FF00U
#define IPP_DATA_MSG_CTRL_BYTE_SHIFT 		8
#define IPP_DATA_MSG_POS_MASK			0x000000FFU
#define IPP_DATA_MSG_POS_SHIFT			0
#define IPP_ADDR_MSG_HNDL_MASK 			0x0F000000U
#define IPP_ADDR_MSG_HNDL_SHIFT 		24	
#define IPP_ADDR_MSG_PARAM_MASK 		0x0000FF00U
#define IPP_ADDR_MSG_PARAM_SHIFT 		8
#define IPP_ADDR_MSG_CBYTE_MASK 		0x000000F0U
#define IPP_ADDR_MSG_CBYTE_SHIFT 		4	
#define IPP_ADDR_MSG_CBYTE_TX_DIR 		0x00000000U
#define IPP_ADDR_MSG_CBYTE_RX_DIR 		0x00000001U
#define IPP_ADDR_MSG_CBYTE_PPC_ORIGIN 		0x00000000U
#define IPP_ADDR_MSG_CBYTE_IPP_ORIGIN 		0x00000002U
#define IPP_ADDR_MSG_UPPER_ADDR_MASK		0x0000000FU
#define IPP_ADDR_MSG_UPPER_ADDR_SHIFT		0
#define IPP_USER_MSG_HNDL_MASK 			0x0F000000U
#define IPP_USER_MSG_HNDL_SHIFT 		24	
#define IPP_USER_MSG_P0_MASK 			0x0000FF00U
#define IPP_USER_MSG_P0_SHIFT 			8
#define IPP_USER_MSG_P1_MASK 			0x000000FFU
#define IPP_USER_MSG_P1_SHIFT 			0
#define IPP_ERROR_MSG_CODE_MASK			0x0000FFFFU
#define IPP_ERROR_MSG_CODE_SHIFT		0	
#define IPP_FWLOAD_MSG_MODE_MASK		0x0F000000U
#define IPP_FWLOAD_MSG_MODE_SHIFT		24
#define IPP_DBGMSG_TYPE_MASK			0x0F000000U
#define IPP_DBGMSG_TYPE_SHIFT			24
#define IPP_DBGMSG_P0_MASK 			0x0000FF00U
#define IPP_DBGMSG_P0_SHIFT 			8
#define IPP_DBGMSG_P1_MASK 			0x000000FFU
#define IPP_DBGMSG_P1_SHIFT 			0

#define IPP_PWRMGMT_MSG_HNDL_MASK 			0x0F000000U
#define IPP_PWRMGMT_MSG_HNDL_SHIFT 		24

#define IPP_ENCODE_OK_MSG() 			(IPP_OK_MSG << IPP_MSG_TYPE_SHIFT)
#define IPP_ENCODE_PING_MSG() 			(IPP_PING_MSG << IPP_MSG_TYPE_SHIFT)
#define IPP_ENCODE_RESET_MSG() 			(IPP_RESET_MSG << IPP_MSG_TYPE_SHIFT)
#define IPP_ENCODE_DATA_MSG(hndl,cb,dcb,pos)	((IPP_DATA_MSG << IPP_MSG_TYPE_SHIFT) | \
						((hndl << IPP_DATA_MSG_HNDL_SHIFT) & IPP_DATA_MSG_HNDL_MASK) | \
						((cb << IPP_MSG_CONTROL_BYTE_SHIFT) & IPP_MSG_CONTROL_BYTE_MASK) | \
						((dcb << IPP_DATA_MSG_CTRL_BYTE_SHIFT) & IPP_DATA_MSG_CTRL_BYTE_MASK) | \
						((pos << IPP_DATA_MSG_POS_SHIFT) & IPP_DATA_MSG_POS_MASK))
#define IPP_ENCODE_ADDR_MSG(hndl,cb,ua)		((IPP_ADDR_MSG << IPP_MSG_TYPE_SHIFT) | \
						((hndl << IPP_ADDR_MSG_HNDL_SHIFT) & IPP_ADDR_MSG_HNDL_MASK) | \
						((cb << IPP_MSG_CONTROL_BYTE_SHIFT) & IPP_MSG_CONTROL_BYTE_MASK) | \
						((ua << IPP_ADDR_MSG_UPPER_ADDR_SHIFT) & IPP_ADDR_MSG_UPPER_ADDR_MASK))
#define IPP_ENCODE_ADDRN_MSG(hndl,cb,ua,p0,acb) ((IPP_ADDR_MSG << IPP_MSG_TYPE_SHIFT) | \
						((hndl << IPP_ADDR_MSG_HNDL_SHIFT) & IPP_ADDR_MSG_HNDL_MASK) | \
						((cb << IPP_MSG_CONTROL_BYTE_SHIFT) & IPP_MSG_CONTROL_BYTE_MASK) | \
						((p0 << IPP_ADDR_MSG_PARAM_SHIFT) & IPP_ADDR_MSG_PARAM_MASK) | \
						((acb << IPP_ADDR_MSG_CBYTE_SHIFT) & IPP_ADDR_MSG_CBYTE_MASK) | \
						((ua << IPP_ADDR_MSG_UPPER_ADDR_SHIFT) & IPP_ADDR_MSG_UPPER_ADDR_MASK))
#define IPP_ENCODE_USER_MSG(hndl,cb,p0,p1)	((IPP_USER_MSG << IPP_MSG_TYPE_SHIFT) | \
						((hndl << IPP_USER_MSG_HNDL_SHIFT) & IPP_USER_MSG_HNDL_MASK) | \
						((cb << IPP_MSG_CONTROL_BYTE_SHIFT) & IPP_MSG_CONTROL_BYTE_MASK) | \
						((p0 << IPP_USER_MSG_P0_SHIFT) & IPP_USER_MSG_P0_MASK) | \
						(p1 & IPP_USER_MSG_P1_MASK))
#define	IPP_ENCODE_PWRMGMT_MSG(hndl, type)	((IPP_PWRMGMT_MSG << IPP_MSG_TYPE_SHIFT) | \
						((hndl << IPP_PWRMGMT_MSG_HNDL_SHIFT) & IPP_PWRMGMT_MSG_HNDL_MASK) | \
						type)
#define IPP_ENCODE_ERROR_MSG(errcode) 		((IPP_ERROR_MSG << IPP_MSG_TYPE_SHIFT)  | \
						(errcode & IPP_ERROR_MSG_CODE_MASK))
#define IPP_ENCODE_FWLOAD_MSG(fw_mode)		((IPP_FWLOAD_MSG << IPP_MSG_TYPE_SHIFT) | \
						((fw_mode << IPP_FWLOAD_MSG_MODE_SHIFT) & IPP_FWLOAD_MSG_MODE_MASK)) 
#define IPP_ENCODE_DEBUG_MSG(type,cb,p0,p1)	((IPP_DEBUG_MSG << IPP_MSG_TYPE_SHIFT) | \
						((type << IPP_DBGMSG_TYPE_SHIFT) & IPP_DBGMSG_TYPE_MASK) | \
						((cb << IPP_MSG_CONTROL_BYTE_SHIFT) & IPP_MSG_CONTROL_BYTE_MASK) | \
						((p0 << IPP_DBGMSG_P0_SHIFT) & IPP_DBGMSG_P0_MASK) | \
						((p1 << IPP_DBGMSG_P1_SHIFT) & IPP_DBGMSG_P1_MASK))
#define IPP_DECODE_MSG_TYPE(data)		((data & IPP_MSG_TYPE_MASK) >> IPP_MSG_TYPE_SHIFT)
#define IPP_DECODE_MSG_CONTROL_BYTE(cb)		((cb & IPP_MSG_CONTROL_BYTE_MASK) >> IPP_MSG_CONTROL_BYTE_SHIFT) 
#define IPP_DECODE_DATA_MSG_HNDL(data) 		((data & IPP_DATA_MSG_HNDL_MASK) >> IPP_DATA_MSG_HNDL_SHIFT)
#define IPP_DECODE_DATA_MSG_CTRL_BYTE(data) 	((data & IPP_DATA_MSG_CTRL_BYTE_MASK) >> IPP_DATA_MSG_CTRL_BYTE_SHIFT)
#define IPP_DECODE_DATA_MSG_POS(data) 		((data & IPP_DATA_MSG_POS_MASK) >> IPP_DATA_MSG_POS_SHIFT)
#define IPP_DECODE_ADDR_MSG_HNDL(data) 		((data & IPP_ADDR_MSG_HNDL_MASK) >> IPP_ADDR_MSG_HNDL_SHIFT)
#define IPP_DECODE_ADDR_MSG_CTRL_BYTE(data)	((data & IPP_ADDR_MSG_CBYTE_MASK) >> IPP_ADDR_MSG_CBYTE_SHIFT)
#define IPP_DECODE_ADDR_MSG_PARAM(data)		((data & IPP_ADDR_MSG_PARAM_MASK) >> IPP_ADDR_MSG_PARAM_SHIFT)
#define IPP_DECODE_ADDR_MSG_UPPER_ADDR(data)	((data & IPP_ADDR_MSG_UPPER_ADDR_MASK) >> IPP_ADDR_MSG_UPPER_ADDR_SHIFT)
#define IPP_DECODE_USER_MSG_HNDL(data) 		((data & IPP_USER_MSG_HNDL_MASK) >> IPP_USER_MSG_HNDL_SHIFT)
#define IPP_DECODE_USER_MSG_P0(data) 		((data & IPP_USER_MSG_P0_MASK) >> IPP_USER_MSG_P0_SHIFT)
#define IPP_DECODE_USER_MSG_P1(data) 		(data & IPP_USER_MSG_P1_MASK)
#define IPP_DECODE_ERROR_MSG_CODE(data)		(data & IPP_ERROR_MSG_CODE_MASK)
#define IPP_DECODE_FWLOAD_MSG_MODE(data)	((data & IPP_FWLOAD_MSG_MODE_MASK) >> IPP_FWLOAD_MSG_MODE_SHIFT)
#define IPP_DECODE_DBGMSG_TYPE(data) 		((data & IPP_DBGMSG_TYPE_MASK) >> IPP_DBGMSG_TYPE_SHIFT)
#define IPP_DECODE_DBGMSG_P0(data) 		((data & IPP_DBGMSG_P0_MASK) >> IPP_DBGMSG_P0_SHIFT)
#define IPP_DECODE_DBGMSG_P1(data) 		(data & IPP_DBGMSG_P1_MASK)
#define IPP_DECODE_PWRMGMT_MSG_HNDL(data) 		((data & IPP_PWRMGMT_MSG_HNDL_MASK) >> IPP_PWRMGMT_MSG_HNDL_SHIFT)
#define IPP_MSG_PARAM_UNUSED			0
/*@}*/

/**
 * @name iPP Message Control Byte Definition
 * @code
 * Bit Definitions in IBM convention          
 * 0   1          7  
 * ---------------- 
 * URG | Reserved | 
 * ---------------- 
 * Bit Definitions (S/W Defined)                                             
 * Bit (0) - URG: Urgent msg: Send ACK after processing msg (in ISR context)
 * Bit (1-7) - Reserved for future and customer use                     
 * @endcode
 */
/*@{*/
#define IPP_MSG_CONTROL_URG_BIT		0x80	
#define CTRL_BYTE_UNSED			0
/*@}*/

/**
 * @name iPP Data Message Control Byte Definition (Only used for Data Message)
 * @code
 * Bit Definitions in IBM convention          
 * 0     1      2          3          4            7  
 * ------------------------------------------------ 
 * Start | Stop | Pos/Data | Reserved | Unused/Pos |
 * ------------------------------------------------ 
 * Bit Definitions (S/W Defined)                                             
 * Bit (0) - Start: Flag for start of Data
 * Bit (1) - Stop: Flag for end of Data
 * Bit (2) - Pos/Data: Flag to indicate bits 24:31 in IPP_DATA_MSG used for 
 *                     passing data message. 0 indicates data is passed using
 *                     SCRATCHx register (used for PPC to iPP Data message), and
 *                     data position pointer is set in bits 24:31
 *                     0 indicates bits 24:31 carries the data for the iPP
 *                     data message (Used for iPP to PPC data message). Byte position
 *                     is implicit in case of iPP to PPC data message
 *                     1 indicates data is passed using
 *                     SCRATCHx register (used for PPC to iPP Data message), and
 *                     data position pointer is set in bits 24:31
 * Bit 3 - Reserved for future use                     
 * Bit 4:7 - Reserved for future use
 * @endcode
 */
/*@{*/
#define DATA_MSG_CTRL_BYTE_UNSED	0
#define IPP_DATA_MSG_CBYTE_START_BIT	0x80	
#define IPP_DATA_MSG_CBYTE_STOP_BIT	0x40	
#define IPP_DATA_MSG_CBYTE_DATA_BIT	0x20	
#define IPP_DATA_MSG_CBYTE_POS_MASK	0x0F
/*@}*/

/** 
 * @name iPP Global Configuration: Common Settings
 * \n
 * Maximum number of variables is 255. \n
 * One byte parameter can be send in message byte - additional 4 byte 
 * sent using SCRATCH1/2 \n
 * Configured using IPP_CONFIG_HDLR from PPC. The maximum value for iPP 
 * Config Var is 1 byte (255) \n 
 * Config parameters can get additional data (4 bytes) using SCRATCH1 and 
 * SCRATCH2 registers \n
 * Protocol: CPU0 always writes to SCRATCH1 and CPU1 uses SCRATCH2 for 
 * sending additional 4 bytes of data \n
 */
/*@{*/
#define IPP_MAX_CONFIG_VAR	(0xFF)
#define IPP_CONFIG_VAL_MASK	(0xFF)
/*@}*/

/** 
 * @name iPP Global Configuration: Deep Sleep Timer Variable (in secs)
 * \n
 * Sleep Timer tells the time after which iPP cuts of 
 * SoC power if both PPC cores are powered down \n       
 * 0: Disable timer 
 */
/*@{*/
#define IPP_DEEPSLEEP_TIMER_VAR		1
#define IPP_DEEPSLEEP_TIMER_DISABLE	0
/*@}*/

/** 
 * @name iPP Global Configuration: CPM Sleep Control Mode
 * \n 
 *  1:Local 
 *  0:Global 
 */
/*@{*/
#define IPP_SLEEP_CTRL_MODE_VAR		2 
#define IPP_LOCAL_SLEEP_MODE		1
#define IPP_GLOBAL_SLEEP_MODE		0
/*@}*/

/** 
 * @name iPP Global Configuration: QMLite_init Variable
 * \n 
 *  1:Start Init 
 */
/*@{*/
#define IPP_QMLITE_INIT_VAR		3
#define IPP_QMLITE_INIT_START		1
/*@}*/

/** 
 * @name iPP Global Configuration: iPP Wakeup EventMap Bitmask Variable 
 *           Warning: Don't change this numberings. EXTEND it if necessary
 *           If you extend wakeup event, please extend ipp_pwrmgmt_stats structure
 */
/*@{*/
#define IPP_WAKEUP_EVENTMAP_VAR		4
#define IPP_WAKEUP_ETHERNET_EVENT_ID	(0)
#define IPP_WAKEUP_ETHERNET_EVENT	(0x1<<IPP_WAKEUP_ETHERNET_EVENT_ID)
#define IPP_WAKEUP_USB_EVENT_ID		(1)
#define IPP_WAKEUP_USB_EVENT		(0x1<<IPP_WAKEUP_USB_EVENT_ID)
#define IPP_WAKEUP_GPIO_EVENT_ID	(2)
#define IPP_WAKEUP_GPIO_EVENT		(0x1<<IPP_WAKEUP_GPIO_EVENT_ID)
#define IPP_WAKEUP_RTC_EVENT_ID		(3)
#define IPP_WAKEUP_RTC_EVENT		(0x1<<IPP_WAKEUP_RTC_EVENT_ID)
#define IPP_WAKEUP_SW_EVENT_ID		(4)
#define IPP_WAKEUP_SW_EVENT		(0x1<<IPP_WAKEUP_SW_EVENT_ID)
#define IPP_MAX_WAKEUP_EVENT		(5)
/*@}*/

/** 
 * @name iPP Global Configuration: OCM offset of ipp_pwr_state_t power state structure 
 */
/*@{*/
#define IPP_PWRSTATE_OCM_OFFSET_VAR	5
/*@}*/

/** 
 * @name iPP Global Configuration: DRAM offset of ipp_pwr_state_t power state structure 
 */
/*@{*/
#define IPP_PWRSTATE_IPPDRAM_OFFSET_VAR	6
/*@}*/

/** 
 * @name iPP Global Configuration: Sleep Timer Variable (in secs) 
* \n 
  * Sleep Timer tells the time after which iPP cuts of
 * SoC clocks if both PPC cores are clock gated
 * 0: Disable timer 
 */
/*@{*/
#define IPP_SLEEP_TIMER_VAR		7
#define IPP_SLEEP_TIMER_DISABLE		0	
/*@}*/

/** 
 * @name iPP Global Configuration: Send IPv4 address
 * \n 
 *  Notify IPv4 Address from PPC to iPP
 */
/*@{*/
#define IPP_SEND_IPv4_ADDR_VAR		8	
/*@}*/

/** 
 * @name iPP Global Configuration: Mask of online PPC cores
 */
/*@{*/
#define IPP_ONLINE_PPC_CORES_MASK_VAR    9
/*@}*/

/** 
 * @name iPP Global Configuration: iPP GPIO Config Variable
 * \n 
 * Configure iPP GPIO as iPP Input (Wakeup), iPP Output,
 * PPC Input or PPC Output,
 * GPIO Mask is passed using SCRATCH1/2 
 */
/*@{*/
#define IPP_GPIO_CONFIG_VAR		10
#define GPIO_TYPE_WAKEUP_IPP_INPUT	1
#define GPIO_TYPE_IPP_OUTPUT		2	
#define GPIO_TYPE_PPC_INPUT		3
#define GPIO_TYPE_PPC_OUTPUT		4
#define IPP_MAX_GPI0_WAKEUP_MASK	0xFFFF
#define IPP_MAX_GPI0_LVL_MASK		0xFFFF0000
#define IPP_GPI0_LVL_SHIFT		16
#define GET_GPIO_LVL(val)		((val & IPP_MAX_GPI0_LVL_MASK) >> \
					IPP_GPI0_LVL_SHIFT)
#define GET_GPIO_WAKEUP(val)		(val & IPP_MAX_GPI0_WAKEUP_MASK)
#define ENCODE_GPIO_WAKE_LVL(lvl,wake)	(((lvl << IPP_GPI0_LVL_SHIFT) &	\
					IPP_MAX_GPI0_LVL_MASK) |	\
					(wake & IPP_MAX_GPI0_WAKEUP_MASK))
/*@}*/

/** 
 * @name iPP Global Configuration: iPP Disable GPIO shutdown Variable
 * \n 
 * Disable GPIO and LED shutdown during deep sleep 
 */
/*@{*/
#define IPP_DISABLE_GPIO_SHUTDOWN	11
#define DISABLE_GPIO_SHUTDOWN		1
#define ENABLE_GPIO_SHUTDOWN		0
/*@}*/

/** 
 * @name iPP Global Configuration: Wakeuptime LED Mask Variable
 * \n 
 * LED to light up to measure deep sleep entry/exit times
 */
/*@{*/
#define IPP_LED_MEASURE_MASK		12
/*@}*/

/** 
 * @name iPP Global Configuration: WoL Classifier Start Node Pointer Var
 * \n 
 * Start Node Pointer for WoL Classifier Tree in deep sleep
 */
/*@{*/
#define IPP_ENET0_CLE0_SNPTR0		13
/*@}*/

/** 
 * @name iPP Global Configuration: WoL PortNumber Variable
 * \n 
 * WoL Port in deep sleep variable
 * Upto MAX_IPP_WOL_PORTS wakeup ports can be defined for wakeup
 */
/*@{*/
#define IPP_SEND_WOL_PORT_VAR		14
/* Maximum support WOL Ports on SlimPro */
#define MAX_IPP_WOL_PORTS		4
/*@}*/

/** 
 * @name iPP Global Configuration: QM Coherent Access
 * \n 
 * QM Coherent Access bit C configuration
 */
/*@{*/
#define IPP_QM_COHERENT_ACCESS		15
/*@}*/

/* End of iPP Global Configuration Variables */

/** 
 * @name iPP Scratch PAD Register Definitions 
 * \n 
 * ScratchPAD register is used to notify PPC about iPP capabilities
 * It also stores iPP Software major/minor versions, along with bits
 * indicating whether an IP block has been already initialized (eg. QM/DDR)
 * These bits can be used by PPC boot code to skip that IP initialization
 * Definitions in IBM convention.
 * @code
 * 0  4      6        8     9          10       14        24       28      31 
 * -------------------------------------------------------------------------
 * |ID| Mode | Rsvd   |TPIM |PPCstarted|BootMode| Reserved|MajorVer|MinorVer|
 * -------------------------------------------------------------------------
 * Bit Definitions (S/W Defined)                                          
 * Bit (0-3)   - ID: Magic Identifier                                     
 * Bit (4-5)   - Mode: iPP whether in ROM, Runtime or External code       
 * Bit (6)     - Rsvd: Reserved for future
 * Bit (7-8)   - TPM Mode: Asymmetric/Symmetric secure boot, 0 for normal boot
 * Bit (9)     - PPCStarted: Whether iPP has release PPC reset              
 * Bit (10-13) - Boot Mode: maps to BOOTDEV
 * Bit (14)    - WarmBoot: SlimPro Warm Boot Indicator                                 
 * Bit (15-23) - Reserved: For future use                                 
 * Bit (24-27) - Major Version number                                     
 * Bit (28-31) - Minor Version number                                     
 * @endcode
 */
/*@{*/
/** Scratch ID mask */
#define IPP_SCRATCH_ID_MASK		0xF0000000
/** Scratch ID magic value */
#define IPP_SCRATCH_ID_MAGIC		0xA0000000
/** Scratch ID shift */
#define IPP_SCRATCH_ID_SHIFT		28
/** Mode mask */
#define IPP_MODE_MASK			0x0C000000
/** Mode value ROM Code */
#define IPP_ROM_MODE_MASK		0x04000000
/** Mode value RUNTIME Code */
#define IPP_RUNTIME_MODE_MASK		0x08000000
/** Mode value EXTERNAL Code */
#define IPP_EXTBOOT_MODE_MASK		0x0C000000
/** Mode shift */
#define IPP_MODE_SHIFT			26
/** TPM Mode mask */
#define IPP_TPM_MODE_MASK		0x01800000
#define IPP_TPM_ASYM_BOOT_MODE_MASK	0x01800000
#define IPP_TPM_SYMM_BOOT_MODE_MASK	0x00800000
/** TPM Mode Shift */
#define IPP_TPM_MODE_SHIFT		23
/** PPCStarted mask */
#define IPP_PPC_STARTED_MASK		0x00400000
/** PPCStarted shift */
#define IPP_PPC_STARTED_SHIFT		22
/** BootMode mask */
#define IPP_BOOTMODE_MASK		0x003C0000
/** BootMode shift */
#define IPP_BOOTMODE_SHIFT		18
/** WarmBoot mask */
#define IPP_WARMBOOT_MASK		0x00020000
/** WarmBoot shift */
#define IPP_WARMBOOT_SHIFT		17
/** Major Version mask */
#define IPP_MAJOR_VER_MASK		0x000000f0
/** Major Version shift */
#define IPP_MAJOR_VER_SHIFT		4
/** Minor Version mask */
#define IPP_MINOR_VER_MASK		0x0000000f
/** Minor Version shift */
#define IPP_MINOR_VER_SHIFT		0
/*@}*/

/** 
 * @name Offset of members of ipp_pwr_state_t structure
 * \n 
 * WARNING: If you change order of ipp_pwr_state_t
 * make sure to update the defines for the offsets
 * Assembly code depends on the defines for offsets
 * and bootcode will stop working. BE VERY CAREFUL
 * when changing/adding to ipp_pwr_state_t \n 
 * NOTE: For use in assembly code by PPC bootloader
 */
/*@{*/
/** PowerON flag offset */
#define POWERON_FLAG_OFFSET	0
/** Resume Program Counter offset */
#define RESUME_PC_OFFSET	4
/** TLB Word0 offset */
#define TLB_WORD0_OFFSET	8
/** TLB Word1 offset */
#define TLB_WORD1_OFFSET	12
/** TLB Word2 offset */
#define TLB_WORD2_OFFSET	16
/*@}*/

/** The upper 16 bits of ipp_pwr_state_t.poweron_flag holds magic word if power state structure is valid.
 * The iPP BootCode clears this magic on cold boot. Only iPP writes to poweron_flag, PowerPC only reads it.
 * If structure is invalid, PowerPC resumes normal boot. The Lower 16 bits contain flag to restore state 
 * without doing normal boot
 */
/*@{*/
/** Power State Indentification Magic */
#define IPP_PWR_STATE_MAGIC	(0xA7CC0000)
/** Power State Restore Flag Value */
#define RESTORE_FLAG		(0x1)
/** Power State DDR Magic Values
 *    These magic values are store in DDR at
 *    apm86xxx_resume_deepsleep + 4 + (4*n)
 */
#define IPP_DDR_RESTORE_MAGIC0	(0xA5A5FCFC)
#define IPP_DDR_RESTORE_MAGIC1	(0xAAAA5555)
#define IPP_DDR_RESTORE_MAGIC2	(0xFFFFA5A5)
#define IPP_DDR_RESTORE_MAGIC3	(0x0F0FF0F0)
/*@}*/

/** 
 * Misc Defines
 */
/*@{*/
/** Major Firmware revision for SoC Family
 */
#define IPP_FW_MAJOR_VER_NO	2


#define PPC_CORE0		0 	/**< PPC Core 0 ID */
#define PPC_CORE1		1 	/**< PPC Core 1 ID */
#define PPC_CORE2		2
#define PPC_CORE3		3
#define PPC_CORE4		4
#define PPC_CORE5		5
#define PPC_CORE6		6
#define PPC_CORE7		7
#define MAX_PPC_CORES	8
#define MAX_PPC_CORES_MASK	0xF	/* This is PMD mask */
/*@}*/

/**
 * Minor Firmware revision defination
 */
/*@{*/
/** Minor Firmware revision for various modes
 */
#if defined(IPP_ROM_BOOT)
#define IPP_FW_MINOR_VER_NO	1
#define IPP_BOOT_MODE		ROM
#elif defined(IPP_RUNTIME_BOOT)
#define IPP_FW_MINOR_VER_NO	1
#define IPP_BOOT_MODE		Runtime
#elif defined(IPP_EXTERNAL_BOOT)
#define IPP_FW_MINOR_VER_NO	1
#define IPP_BOOT_MODE		External
#endif
/*@}*/

/**
 * @name IPP_PWRSTATE_IN_xxx
 * @note Location of Shared ipp_pwr_state_t power state structure 
 * 	 ipp_pwr_state_t can be in DSRAM (deep sleep RAM) or in OCM      
 */
/*@{*/
#define IPP_PWRSTATE_IN_OCM		1
#define IPP_PWRSTATE_IN_DSRAM		2
/*@}*/

/** 
 * @name iPP SCU_PPCx_RESUME_DS Register Definition
 * \n 
 * SCU_PPCx_RESUME_DS register used to notify the location for the ipp_pwr_state_t 
 * structure. It can be either in iPP DRAM or OCM. It also has bit to indicate
 * that PPC1 should break out of the spin loop in initial bootup (AMP mode)
 * SCU_PPCx_RESUME_DS is modified by iPP only when iPP gets a message from PPC
 * Some bits in SCU_PPCx_RESUME_DS are set by PPC bootcode (eg. C1Rst bit)
 * Definitions in IBM convention.
 * @code
 * 0      2      3       16             31 
 * --------------------------------------
 * |PSLoc |C1Rst | Rsvd   | OCMPSOffset | 
 * --------------------------------------
 * Bit Definitions (S/W Defined)                                          
 * Bit (0-1)  - PSLoc: Power State Location (OCM or iPP DRAM) - set by iPP
 * Bit (2)  - C1Rst: Release Core1 Reset (used in AMP boot) - set by PPC
 * Bit (3-15) - Rsvd: For future use                                 
 * Bit (16-31) - OCMPSOffset: OCM Power State Offset - set by iPP
 * @endcode
 */
/*@{*/
/** Power State mask */
#define IPP_PWR_STATE_MASK		0xC0000000
/** Power State shift */
#define IPP_PWR_STATE_SHIFT		30
/** Mode value OCM Power State Code */
#define IPP_PWR_STATE_OCM_MODE_MASK	(IPP_PWRSTATE_IN_OCM<<IPP_PWR_STATE_SHIFT)
/** Mode value iPP DRAM Power State Code */
#define IPP_PWR_STATE_DSRAM_MODE_MASK	(IPP_PWRSTATE_IN_DSRAM<<IPP_PWR_STATE_SHIFT)
/** PPC1 Reset release mask - set by PPC bootcode */
#define PPC1_RELEASE_RESET_MASK		0x20000000
/** PPC1 Reset release shift - set by PPC bootcode */
#define PPC1_RELEASE_RESET_SHIFT	29
/*@}*/

/** 
 * @name SLIMpro Firmware Features Definition 
 * \n 
 * SLIMpro Firmware Features are used to notify PPC cores of the
 * available SLIMpro firmware features compiled into the binary
 * Bit Definitions in IBM convention.
 * 0            1                          31 
 * --------------------------------------------
 * |ExpansionBit| ReservedBits | Features Bits |
 * --------------------------------------------
 * Bit Definitions (S/W Defined)                                          
 * Bit (0)  - ExpansionBit: If set, firmware features extends to next 32 bits
 * Bit (1-15)  - Reserved: Reserved for new features in SlimPro firmware
 * Bit (16-23) - NETOffload: Various NET offload support in firmware
 * Bit (21) - IPv4 NAT Offload support in firmware
 * Bit (22) - IPv4 Forward Offload support in firmware
 * Bit (23) - Bridge Offload support in firmware
 * Bit (24) - CodeSwap: CodeSwap support in firmware
 * Bit (25) - LLMNR: LLMNR support in firmware
 * Bit (26) - SNMP: SNMP support in firmware
 * Bit (27) - NetBIOS: NetBIOS support in firmware
 * Bit (28) - LRO: LRO support in firmware
 * Bit (29) - IPv6: IPv6 support in firmware
 * Bit (30) - IPv4: IPv4 support in firmware
 * Bit (31) - PWRMGMT: PowerManagement Feature in firmware
 * @endcode
 */
/*@{*/
/** Features Expansion Bit mask */
#define IPP_FEATURES_EXPANSION_MASK	0x80000000
/** Features Expansion Bit shift */
#define IPP_FEATURES_EXPANSION_SHIFT	31
/** NET Offload Features Bits mask */
#define IPP_NETOFFLOAD_FW_MASK		0x0000FF00
/** IPv4 NAT Offload Feature Bit mask */
#define IPP_IPV4NAT_OFFLOAD_FW_MASK	0x00000400
/** IPv4 NAT Offload Feature Bit shift */
#define IPP_IPV4NAT_OFFLOAD_FW_SHIFT	10
/** IPv4 Forward Offload Feature Bit mask */
#define IPP_IPV4FWD_OFFLOAD_FW_MASK	0x00000200
/** IPv4 Forward Offload Feature Bit shift */
#define IPP_IPV4FWD_OFFLOAD_FW_SHIFT	9
/** Bridge Offload Feature Bit mask */
#define IPP_BRIDGE_OFFLOAD_FW_MASK	0x00000100
/** Bridge Offload Feature Bit shift */
#define IPP_BRIDGE_OFFLOAD_FW_SHIFT	8
/** Code Swap Feature Bit mask */
#define IPP_CODESWAP_FW_MASK		0x00000080
/** Code Swap Feature Bit shift */
#define IPP_CODESWAP_FW_SHIFT		7
/** Code Swap Feature Bit mask */
#define IPP_LLMNR_FW_MASK		0x00000040
/** Code Swap Feature Bit shift */
#define IPP_LLMNR_FW_SHIFT		6
/** SNMP Feature Bit mask */
#define IPP_SNMP_FW_MASK		0x00000020
/** SNMP Feature Bit shift */
#define IPP_SNMP_FW_SHIFT		5
/** NetBios Feature Bit mask */
#define IPP_NETBIOS_FW_MASK		0x00000010
/** NetBios Feature Bit shift */
#define IPP_NETBIOS_FW_SHIFT		4
/** LRO Feature Bit mask */
#define IPP_LRO_FW_MASK			0x00000008
/** LRO Feature Bit shift */
#define IPP_LRO_FW_SHIFT		3
/** IPv6 Feature Bit mask */
#define IPP_IPV6_FW_MASK		0x00000004
/** IPv6 Feature Bit shift */
#define IPP_IPV6_FW_SHIFT		2	
/** IPv4 Feature Bit mask */
#define IPP_IPV4_FW_MASK		0x00000002
/** IPv4 Feature Bit shift */
#define IPP_IPV4_FW_SHIFT		1
/** Power Management Feature Bit mask */
#define IPP_PWRMGMT_FW_MASK		0x00000001
/** Power Management Feature Bit shift */
#define IPP_PWRMGMT_FW_SHIFT		0
/*@}*/

/** 
 * @name iPP bootaccess helper defines and macros
 */
/*@{*/
#define IPP_BOOTACCESS_WORD0_DEVICE_MASK	 0xF0000000
#define IPP_BOOTACCESS_WORD0_DEVICE_SHIFT	 28
#define IPP_BOOTACCESS_WORD0_OPERATION_MASK	 0x0F000000
#define IPP_BOOTACCESS_WORD0_OPERATION_SHIFT	 24
#define IPP_BOOTACCESS_WORD0_RESERVED_MASK	 0x000FFFFF
#define IPP_BOOTACCESS_WORD0_RESERVED_SHIFT	 0
#define IPP_ENCODE_BOOTACCESS_WORD0(dev,op)	 (((dev << IPP_BOOTACCESS_WORD0_DEVICE_SHIFT) & IPP_BOOTACCESS_WORD0_DEVICE_MASK) | \
						 ((op << IPP_BOOTACCESS_WORD0_OPERATION_SHIFT) & IPP_BOOTACCESS_WORD0_OPERATION_MASK))
#define IPP_ENCODE_BOOTACCESS_ADDRESS(erpn,addr) (((erpn << 28) & 0xF0000000) | \
						 ((addr >> 4) & 0x0FFFFFFF))
#define IPP_DECODE_BOOTACCESS_DEVICE(word0)	 ((word0 & IPP_BOOTACCESS_WORD0_DEVICE_MASK) >> IPP_BOOTACCESS_WORD0_DEVICE_SHIFT)
#define IPP_DECODE_BOOTACCESS_OPERATION(word0)	 ((word0 & IPP_BOOTACCESS_WORD0_OPERATION_MASK) >> IPP_BOOTACCESS_WORD0_OPERATION_SHIFT)
#define IPP_DECODE_BOOTACCESS_ERPN(data)	 ((data & 0xF0000000) >> 28)
#define IPP_DECODE_BOOTACCESS_ADDRESS(data)	 ((data & 0x0FFFFFFF) << 4)
/** Maximum size of filename to be used by boot access */
#define IPP_BOOTACCESS_MAX_FILENAME_SIZE	 16
/*@}*/

/** 
 * @name iPP NET_DATA helper defines and macros
 */
/*@{*/
#define IPP_NETDATA_CTRL_BYTE0_MASK			0xFF000000
#define IPP_NETDATA_CTRL_BYTE0_SHIFT			24
#define IPP_NETDATA_CTRL_BYTE1_MASK			0x00FF0000
#define IPP_NETDATA_CTRL_BYTE1_SHIFT			16
#define IPP_NETDATA_CTRL_BYTE2_MASK			0x0000FF00
#define IPP_NETDATA_CTRL_BYTE2_SHIFT			8		
#define IPP_NETDATA_CTRL_BYTE3_MASK			0x000000FF
#define IPP_ENCODE_NETDATA_CTRL_WORD(b0,b1,b2,b3)	(((b0 << IPP_NETDATA_CTRL_BYTE0_SHIFT) & IPP_NETDATA_CTRL_BYTE0_MASK) | \
							((b1 << IPP_NETDATA_CTRL_BYTE1_SHIFT) & IPP_NETDATA_CTRL_BYTE1_MASK) | \
							((b2 << IPP_NETDATA_CTRL_BYTE2_SHIFT) & IPP_NETDATA_CTRL_BYTE2_MASK) | \
							(b3 & IPP_NETDATA_CTRL_BYTE3_MASK))
#define IPP_DECODE_NETDATA_CTRL_BYTE0(word)		((word & IPP_NETDATA_CTRL_BYTE0_MASK) >> IPP_NETDATA_CTRL_BYTE0_SHIFT)
#define IPP_DECODE_NETDATA_CTRL_BYTE1(word)		((word & IPP_NETDATA_CTRL_BYTE1_MASK) >> IPP_NETDATA_CTRL_BYTE1_SHIFT)
#define IPP_DECODE_NETDATA_CTRL_BYTE2(word)		((word & IPP_NETDATA_CTRL_BYTE2_MASK) >> IPP_NETDATA_CTRL_BYTE2_SHIFT)
#define IPP_DECODE_NETDATA_CTRL_BYTE3(word)		((word & IPP_NETDATA_CTRL_BYTE3_MASK) >> IPP_NETDATA_CTRL_BYTE3_SHIFT)

#define IPP_NETDATA_CTRL_UNUSED				0

/* IPP_NETDATA Control Byte 1 Types */
#define IPP_NETDATA_IPv6_TYPE				1
#define IPP_NETDATA_SNMP_TYPE				2
#define IPP_NETDATA_NETBIOS_TYPE			3
#define IPP_NETDATA_LLMNR_TYPE				4
#define IPP_NETDATA_NET_OFFLOAD_TYPE			5
#define IPP_NETDATA_LRO_TYPE				6

/* IPP_NETDATA Control Byte 2 Types */

/* for IPv6_TYPE */
#define IPP_IPv6_UCAST					1
#define IPP_IPv6_MCAST					2

/* for SNMP_TYPE */
#define IPP_SNMP_COMMUNITY				1
#define IPP_SNMP_MIB_DEVICE_STATUS			2
#define IPP_SNMP_MIB_PRINTER_ERROR_DETECT  		3
#define IPP_SNMP_MIB_MEM_SIZE				4
#define IPP_SNMP_MIB_STORAGE_TYPE			5
#define IPP_SNMP_MIB_MIB_MEDIA_PATH_TYPE		6
#define IPP_SNMP_MIB_PRINTER_STATUS			7

/* for NETBIOS_TYPE */
#define IPP_NETBIOS_TTL  				1
#define IPP_NETBIOS_NAME 				2
#define IPP_NETBIOS_NODE_TYPE 				3
#define IPP_NETBIOS_NODE_STATUS 			3

/* For LLMNR_TYPE */
#define IPP_LLMNR_TTL					1
#define IPP_LLMNR_NAME					2

/* For NET Offload */
#define IPP_NET_OFFLOAD_MAC				1
#define IPP_NET_OFFLOAD_BUFDATALEN			2
#define IPP_NET_OFFLOAD_QM				3

/* For NAT Offload */
#define IPP_NATOFFLOAD_ENABLE				1
#define IPP_NATOFFLOAD_DISABLE				2
#define IPP_NATOFFLOAD_IP4ADDR				3
#define IPP_NATOFFLOAD_IP4MAC				4
#define IPP_NATOFFLOAD_INGRESS_WQPB			5
#define IPP_NATOFFLOAD_INGRESS_WQ			6
#define IPP_NATOFFLOAD_EGRESS_WQ			7

/* LRO Command Type */
#define IPP_LRO_TIMEOUT			1
#define IPP_LRO_BYTECNT			2
#define IPP_LRO_QM_SYS_WQ		3
#define IPP_LRO_QM_SRC_FP		4
#define IPP_LRO_QM_DST_FP		5

/* LRO PKTDMA operation mode */
#define LRO_DMA_SINGLE_SRC_BUF_TO_SINGLE_DST_MEM

/* All of the below type uses ADDR MSG and share the types
 * from DATA MSG. 
 * IPP_NETDATA Control Byte 3 Types Carries Length for 
 * IPP_SNMP_COMMUNITY,
 * IPP_SNMP_MIB_STORAGE_TYPE,
 * IPP_NETBIOS_NAME
 * IPP_NETBIOS_NODE_STATUS
 * IPP_LLMNR_NAME
*/

/* Default WOL Port on SlimPro */
#define UDP_DEFAULT_WOL_PORT		55555


/* BMC */
#define DECODE_BMC_REG_OFFSET(msg_val) ((msg_val >> 8) & 0xff)
#define DECODE_BMC_ACCESS_INFO(msg_val) ((msg_val) & 0xff)
#define DECODE_BMC_ACCESS_INFO_IS_READ(access_info) (((access_info) & 0x08) == 0x08)
#define DECODE_BMC_ACCESS_INFO_IS_WRITE(access_info) (((access_info) & 0x08) == 0)
#define DECODE_BMC_ACCESS_INFO_LEN(access_info) (((access_info) & 0xf0) >> 4)
#define DECODE_BMC_ACCESS_INFO_MORE_DATA(access_info) (((access_info) & 0x04) >> 2)

#define ENCODE_BMC_ACCESS_INFO(len, is_read, more_data) \
                (((len & 0xf) << 4) | ((is_read & 0x1)<< 3) | ((more_data & 0x1) << 2))
#define ENCODE_BMC_ACCESS_INFO_CMD(info, sub_type) \
                ((info & 0xfc) | (sub_type & 0x03))
#define DECODE_BMC_CMD_REQ(access_info)         (access_info & 0x03)
#define BMC_STOP_REQ_CMD        0x2
#define BMC_START_REQ_CMD       0x1

/*@}*/

#ifndef __ASSEMBLY__
/** 
 * Domain Protection Interface 
 */
struct ipp_dp_cmd  
{
	/* As this is spec from SlimPRO, the format is in little endian */
#if defined(__PPC__)
	unsigned int resv2 : 8;
	unsigned int rd : 1;			
	unsigned int wr : 1;
	unsigned int rsvd1 : 2;
	unsigned int domain : 4;		/* Filled by SlimPRO */
	unsigned int res_type : 8;		/* IPP_DP_RES_XXX */
	unsigned int cmd : 8;			/* IPP_DP_CMD_XXX */

	unsigned int phy_end_hi : 8;
	unsigned int phy_start_hi : 8;
	unsigned int resv3 : 16;

	unsigned int phy_start_lo;
	unsigned int phy_end_lo;
#else
	unsigned int cmd : 8;			/* IPP_DP_CMD_XXX */
	unsigned int res_type : 8;		/* IPP_DP_RES_XXX */
	unsigned int rd : 1;			
	unsigned int wr : 1;
	unsigned int rsvd1 : 2;
	unsigned int domain : 4;		/* Filled by SlimPRO */
	unsigned int resv2 : 8;

	unsigned int resv3 : 16;
	unsigned int phy_start_hi : 8;
	unsigned int phy_end_hi : 8;

	unsigned int phy_start_lo;
	unsigned int phy_end_lo;
#endif
};

#define IPP_DP_CMD_EXCLUSIVE		0x01 /* Exclusive */
#define IPP_DP_CMD_EXCLUSIVE_SHARED	0x02 /* Exclusive temporary than shared \
					        must enters PROTECTIVE after \
                                                TBD seconds. Or issue command \
                                                again to reset timer */
#define IPP_DP_CMD_PROTECTIVE 		0x03 /* SlimPRO only */
#define IPP_DP_CMD_SHARED	 	0x04 /* Shared between PPC0/PPC1/SlimPRO */

#define IPP_DP_RES_NONE			0x00
#define IPP_DP_RES_SLIMPRO		0x01
#define IPP_DP_RES_MEMC			0x02
#define IPP_DP_RES_AHBC			0x03
#define IPP_DP_RES_DDR			0x04	/* Make sure last */
#define IPP_DP_RES_TOTAL		0x05

#define IPP_DP_ERR_OK			0
#define IPP_DP_ERR_RES_TYPE_INVALID	1
#define IPP_DP_ERR_RES_PROTECTIVE	2
#define IPP_DP_ERR_RES_EXCLUSIVE	3
#define IPP_DP_ERR_RES_SHARED		4
#define IPP_DP_ERR_RES_OUTOFENTRY	5
#define IPP_DP_ERR_NORESOURCE		6
#define IPP_DP_ERR_UNSUPPORTED		6

/** 
 * Power State Structure uses for passing power-save/restore information 
 * between PPC and iPP. SCU_PPCx_RESUME_DS reg points to Power state location
 * Don't use enums in this structure since the compiler doesn't assign 
 * word by default and it messes up. \n
 * WARNING: When you CHANGE any FIELD or order please UPDATE macros used by 
 * PPC bootloader above.             
 */
struct ipp_pwr_state {
	unsigned int poweron_flag; /**< PowerON flag */
	unsigned int resume_pc; /**< Resume Program Counter */
	unsigned int tlb_word0; /**< TLB Word0 for PowerPC */
	unsigned int tlb_word1; /**< TLB Word1 for PowerPC */
	unsigned int tlb_word2; /**< TLB Word2 for PowerPC */
};

typedef struct ipp_pwr_state ipp_pwr_state_t;

/*
** iPP Common Interface
*/

/** iPP error codes */
enum ipp_error_codes {
	IPP_OK=0, 		/**< OK (=No Error) */
	IPP_ERR_INVALID_OP, 	/**< Invalid Operation */
	IPP_ERR_INVALID_PARAM,  /**< Invalid parameter */
	IPP_ERR_NOTAVAIL, 	/**< Not Available */
	IPP_ERR_NOSPACE, 	/**< No Space */
	IPP_ERR_DEV_INIT, 	/**< Error in Device Init */
	IPP_ERR_BOOT_INVALIMG, 	/**< Invalid Boot Image */
	IPP_ERR_NO_IMGAUTHKEY, 	/**< Image Authentication key missing */
	IPP_ERR_NO_IMGSIG, 	/**< Image signature missing */
	IPP_ERR_NO_KEYSIGN,     /**< Key Signature missing */
	IPP_ERR_KEYAUTHFAIL,	/**< Key Authentication Failure */
	IPP_ERR_IMGAUTHFAIL,	/**< Image Authentication Failure */
	IPP_ERR_CRCFAIL,	/**< CRC Failure */
	IPP_ERR_FILE_OPEN,	/**< Error opening file */
	IPP_ERR_INVALID_FILE,	/**< Invalid File */
	IPP_ERR_FILE_NOTFOUND,	/**< Specified file not found */
	IPP_ERR_FILE_READ_FAIL,	/**< Error opening file */
	IPP_ERR_UNSUPPORTED_MSG, /**< Unsupported message */
	IPP_ERR_UNSUPPORTED_CMD, /**< Unsupported command */
	IPP_ERR_UNSUPPORTED_CFG, /**< Unsupported configuration */
	IPP_ERR_TIMEOUT,	/**< Generic Timeout */
	IPP_ERR_SECHW_TIMEOUT,  /**< Security Hardware Engine Timeout */
	IPP_ERR_BUSY, 		/**< Busy */
	IPP_ERR_SD_UNPLUGGED, 	/**< SDIO card Unplugged */
	IPP_ERR_SDHW, 		/**< SDIO hardware error */
	IPP_ERR_NO_I2C_DEV, 	/**< No I2C device found */
	IPP_ERR_I2C_TIMEOUT, 	/**< I2C timedout */
	IPP_ERR_NO_SPI_DEV, 	/**< No SPI device found */
	IPP_ERR_OCM_MEM_NOT_RDY, /**< OCM not ready */
	IPP_ERR_HW_INIT_DONE, 	 /**< Hardware init already done */
	IPP_ERR_INVALID_AXI_ADDR,	/**< Invalid AXI Address */
	IPP_ERR_CSR_MEM_NOT_RDY,	/**< CSR Memory Not ready */
	IPP_SELF_REFRESH_FAIL,	 /**< Self refresh mode fail */
	IPP_CPM_READ_FAIL,	 /**< Reading CPM register failed */
	IPP_CPM_WRITE_FAIL,	 /**< Writing to CPM reigster failed */
	IPP_ERR_AHCI_RESET_FAIL, /**< Failed to reset AHCI */
	IPP_ERR_AHCI_NO_ACTIVE_PORT, /**< No active port for AHCI */
	IPP_ERR_AHCI_PORT_NO_LINK, /**< Link not Up on AHCI Port */
	IPP_ERR_AHCI_NO_MEM, /**< Insufficient memory for AHCI */
	IPP_ERR_AHCI_CMD_TIMEOUT, /**< Command timeout for AHCI */
	IPP_ERR_SATA_PHY_READ_FAIL,	 /**< Reading SATA PHY register failed */
	IPP_ERR_SATA_PHY_WRITE_FAIL,	 /**< Writing to SATA PHY reigster failed */
	IPP_ERR_PLL_LOCK_FAIL,		 /**< PLL Lock Failure */
	IPP_ERROR,					/**< Generic error condition */
};

/* 
 * iPP Messaging Interface 
 */

/** iPP message types */
enum ipp_message_type {
	IPP_DEBUG_MSG=0x0, 	/**< Debug Message */
	IPP_OK_MSG=0x1, 	/**< OK Message */
	IPP_PING_MSG=0x2, 	/**< Ping Message */
	IPP_RESET_MSG=0x3, 	/**< Reset Message */
	IPP_DATA_MSG=0x4, 	/**< Data Message */
	IPP_ADDR_MSG=0x5, 	/**< Address Message */
	IPP_USER_MSG=0x6, 	/**< User Message */
	IPP_ERROR_MSG=0x7, 	/**< Error Message */
	IPP_FWLOAD_MSG=0x8, 	/**< Firmware Load Message */
	IPP_PWRMGMT_MSG=0x9,
	IPP_MAX_MSG_NUM=0xF
};

/** iPP firmware load modes */
enum ipp_firmware_modes {
	IPP_FWLOAD_FROM_PPC=0x1, /**< iPP firmware loaded by PPC */
	IPP_FWLOAD_FROM_I2C=0x2  /**< iPP firmware loaded from I2C */
};

/** iPP user message handlers */
enum ipp_user_message_handlers {
	IPP_USER_MSG_HDLR_UNUSED=0, /**< User Msg Handler Unused */
	IPP_PWRMGMT_HDLR=1, /**< Power Mode Handler */
	IPP_CONFIG_SET_HDLR=2, /**< iPP Configuration Set Handler */
	IPP_MAX_USER_MSG_HANDLERS=0xf
};

/** iPP data message handlers */
enum ipp_data_message_handlers {
	IPP_DATA_MSG_HDLR_UNUSED=0, /**< Data Msg Handler Unused */
	IPP_BOOTACCESS_HDLR=1, /**< Data Msg handler Boot RAW interface */
	IPP_NETDATA_HDLR=2, /**< Data Msg handler for NETDATA msg */
	IPP_DP_HDLR=3, /**< AMP domain protection handler */
	IPP_MAX_DATA_MSG_HANDLERS=0xf
};

/** iPP address message handlers */
enum ipp_addr_message_handlers {
	IPP_ADDR_MSG_HDLR_UNUSED=0, /**< Addr Msg Handler Unused */
	IPP_GENERIC_TX_RX_ADDR_MSG_HDLR=1, /**< Addr Msg hdlr to get/send data to SLIMPro */
	IPP_NETDATA_ADDR_MSG_HDLR=2, /**< NetData Addr Msg handler for NETDATA msg */
	IPP_SECUREBOOT_ADDR_MSG_HDLR=3, /**< Secure Boot Data Msg handler */
	IPP_MAX_ADDR_MSG_HANDLERS=0xf
};

/** iPP power mgmt message handlers */
enum ipp_pwrmgmt_message_handlers {
	IPP_PWRMGMT_MSG_HDLR_UNUSED=0, /**< User Msg Handler Unused */
	IPP_TPC_HDLR=1, 	/**< Thermal Protection Circuit Handler */
	IPP_ACPI_HDLR=2, 	/**< ACPI Message Handler */
	IPP_MAX_PWRMGMT_MSG_HANDLERS=0xf
};

/** Must be word aligned */
/** Header for ipp_secureboot_msg_type */
struct ipp_secboot_msg_hdr {
	unsigned int len;  /* ADDR mesg len */
	unsigned int cmd;
	unsigned int status;
};

/** SECUREBOOT_ADDR_MSG Subtypes */
/* MSByte in ipp_secboot_msg_hdr.cmd */
enum ipp_secureboot_msg_type {
	IPP_SECBOOT_MSG_UNUSED=0, /**< Secure Boot Msg subtype Unused */
	IPP_SECBOOT_MSG_READREG_OFFSET=1, /**< Secure Boot Msg Read Register offset */
	IPP_SECBOOT_MSG_WRITEREG_OFFSET=2, /**< Secure Boot Msg Write Register offset */
	IPP_SECBOOT_MSG_READREG_ABSOLUTE=3, /**< Secure Boot Msg ReadReg phy addr */
	IPP_SECBOOT_MSG_WRITEREG_ABSOLUTE=4, /**< Secure Boot Msg ReadReg phy addr */
	IPP_SECBOOT_MSG_AUTH_IMAGE=5, /**< Secure Boot Msg Authenticate image */
	IPP_SECBOOT_MSG_MAX           /**< Secure Boot Msg Maximum supported */
};

/** ipp_secboot_msg_hdr.cmd word is encoded using IPP_ENC_SECBOOTMSG_CMD */
/** | MsgType | MsgCmd | Param0 | Param1 |       */
#define IPP_SECBOOT_MSGTYPE_SHIFT		(24)
#define IPP_SECBOOT_MSGTYPE_MASK		(0xFF000000)
#define IPP_SECBOOT_MSGCMD_SHIFT		(16)
#define IPP_SECBOOT_MSGCMD_MASK			(0x00FF0000)
#define IPP_SECBOOT_MSGP0_SHIFT			(8)
#define IPP_SECBOOT_MSGP0_MASK			(0x0000FF00)
#define IPP_SECBOOT_MSGP1_SHIFT			(0)
#define IPP_SECBOOT_MSGP1_MASK			(0x000000FF)
#define IPP_ENC_SECBOOTMSG_CMD(type,cmd,p0,p1)	(((type << IPP_SECBOOT_MSGTYPE_SHIFT) & IPP_SECBOOT_MSGTYPE_MASK) | \
						((cmd << IPP_SECBOOT_MSGCMD_SHIFT) & IPP_SECBOOT_MSGCMD_MASK) | \
						((p0 << IPP_SECBOOT_MSGP0_SHIFT) & IPP_SECBOOT_MSGP0_MASK) | \
						((p1 << IPP_SECBOOT_MSGP1_SHIFT) & IPP_SECBOOT_MSGP1_MASK))
#define IPP_DECODE_SECBOOTMSG_TYPE(data)	((data & IPP_SECBOOT_MSGTYPE_MASK) >> IPP_SECBOOT_MSGTYPE_SHIFT)
#define IPP_DECODE_SECBOOTMSG_SUBTYPE(data)	((data & IPP_SECBOOT_MSGCMD_MASK) >> IPP_SECBOOT_MSGCMD_SHIFT)
#define IPP_DECODE_SECBOOTMSG_P0(data)		((data & IPP_SECBOOT_MSGP0_MASK) >> IPP_SECBOOT_MSGP0_SHIFT)
#define IPP_DECODE_SECBOOTMSG_P1(data)		((data & IPP_SECBOOT_MSGP1_MASK) >> IPP_SECBOOT_MSGP1_SHIFT)
#define IPP_ENCODE_SECBOOTMSG_ADDRESS(erpn,addr) ((((erpn) << 28) & 0xF0000000) | \
						 (((addr) >> 4) & 0x0FFFFFFF))
#define IPP_DECODE_SECBOOTMSG_ERPN(data)	 (((data) & 0xF0000000) >> 28)
#define IPP_DECODE_SECBOOTMSG_ADDRESS(data)	 (((data) & 0x0FFFFFFF) << 4)

/** Must be word aligned */
/** Data for Register offset read write */
struct ipp_regoff {
	unsigned int offset;
	unsigned int mask;
	unsigned int val;
};

/** Must be word aligned */
/** Data for image authentication */
struct ipp_secure_file_metadata {
	unsigned int binary_addr;
	unsigned int binary_size;
	unsigned int sig_addr;
	unsigned int key_addr;
	unsigned int ksg_addr;
};

/** Must be word aligned */
/** Addr Buffer format for IPP_SECBOOT_MSG_READREG_OFFSET  */
/** or IPP_SECBOOT_MSG_WRITEREG_OFFSET address messages    */
/* For IPP_SECBOOT_MSG_READREG_OFFSET, ipp_regoff.val is  */
/* filled by SlimPro. For IPP_SECBOOT_MSG_WRITEREG_OFFSET, */
/* Slimpro writes ipp_regoff.val to ipp_regoff.offset    */
struct ipp_secboot_regoff_addrmsg {
	struct ipp_secboot_msg_hdr hdr;
	struct ipp_regoff *regp;
};

/** Must be word aligned */
/** Data for Register Absolute read write */
struct ipp_regabs {
	unsigned int u_phyaddr;
	unsigned int l_phyaddr;
	unsigned int mask;
	unsigned int val;
};
/** Must be word aligned */
/** Addr Buffer format for IPP_SECBOOT_MSG_READREG_ABSOLUTE  */
/** or IPP_SECBOOT_MSG_WRITEREG_ABSOLUTE address messages    */
/* For IPP_SECBOOT_MSG_READREG_ABSOLUTE, ipp_regabs.val is   */
/* filled by SlimPro. For IPP_SECBOOT_MSG_WRITEREG_ABSOLUTE, */
/* Slimpro writes ipp_regabs.val to mapped physical addr    */
struct ipp_secboot_regabs_addrmsg {
	struct ipp_secboot_msg_hdr hdr;
	struct ipp_regabs *regp;
};

/** Register Bank Identifier */
/** Register bank can be extended if needed */
enum ipp_regbank_id {
	IPP_REGBANK_UNUSED=0, /**< Unused Register Bank*/
	IPP_REGBANK_SCU=1, /**< SCU Register Bank */
	IPP_REGBANK_MPA=2, /**< SCU Register Bank */
	IPP_REGBANK_PKA=3, /**< PKA Register Bank */
	IPP_REGBANK_TRNG=4, /**< TRNG Register Bank */
	IPP_REGBANK_MAX /**< Add New Bank before this macro */
};

/** Parameter definitions for each ipp_secureboot_msg_type */
/* Command IPP_SECBOOT_MSG_READREG_OFFSET */
/* Param0: Register Bank ID: ipp_regbank_id */
/* Param1: Number of struct ipp_regoff records */

/* Command IPP_SECBOOT_MSG_WRITEREG_OFFSET */
/* Param0: Register Bank ID: ipp_regbank_id */
/* Param1: Number of struct ipp_regoff records */

/* Command IPP_SECBOOT_MSG_READREG_ABSOLUTE */
/* Param0: Number of struct ipp_regabs records */

/* Command IPP_SECBOOT_MSG_WRITEREG_ABSOLUTE */
/* Param0: Number of struct ipp_regabs records */

/** iPP debug message subtype */
enum ipp_debug_msg_type {
	IPP_DBG_SUBTYPE_UNUSED=0, /**< Debug subtype Unused */
	IPP_DBG_SUBTYPE_CPMREAD=1, /**< CPM Reg read */
	IPP_DBG_SUBTYPE_CPMWRITE=2, /**< CPM Reg write */
	IPP_DBG_SUBTYPE_CPMREAD_RESP=3, /**< CPM Reg read response */
	IPP_DBG_SUBTYPE_I2C1READ=4,	/**< I2C1 read command */
	IPP_DBG_SUBTYPE_I2C1WRITE=5, /**< I2C1 write command */
	IPP_DBG_SUBTYPE_I2C1READ_RESP=6,  /**< I2C1 read response */
	IPP_DBG_SUBTYPE_SCUREAD=7, /**< SCU read command */
	IPP_DBG_SUBTYPE_SCUWRITE=8, /**< SCU write command */
	IPP_DBG_SUBTYPE_SCUREAD_RESP=9,  /**< SCU read response */
	IPP_DBG_SUBTYPE_DPCMD_RESP=0xA,  /**< DP command response */
	IPP_DBG_SUBTYPE_ACPI=0xB,
	IPP_DBG_SUBTYPE_THERMAL=0xC,
	IPP_DBG_SUBTYPE_BMC_MSG=0xE,  /**< BMC message */
	IPP_DBG_SUBTYPE_MAX=0xf
};

/* 
** iPP Boot Access Interface 
*/

/** iPP bootaccess devices */
enum ipp_bootaccess_devices {
	IPP_BOOTACCESS_DEVICE_UNUSED=0, /**< Unused bootaccess device */
	IPP_BOOTACCESS_DEVICE_DEFAULT=1, /**< Default bootaccess device */
	IPP_BOOTACCESS_DEVICE_SDIO=2, /** SDIO bootaccess device */
	IPP_BOOTACCESS_DEVICE_USB=3, /** USB bootaccess device */
	IPP_BOOTACCESS_DEVICE_SPI=4, /** SPI bootaccess device */
	IPP_BOOTACCESS_DEVICE_SATA=5, /** SATA bootaccess device */
	IPP_MAX_BOOTACCESS_DEVICE=0xf
};

/** iPP bootacess operations */
enum ipp_bootaccess_operations {
	IPP_BOOTACCESS_OP_UNUSED=0, /**< Unused bootraw read operation */
	IPP_BOOTACCESS_OP_READ=1, /**< Bootaccess read operation */
	IPP_BOOTACCESS_OP_READFULL=2, /**< Bootaccess read full operation */
	IPP_BOOTACCESS_OP_WRITE=3, /**< Bootaccess write operation */
	IPP_BOOTACCESS_OP_AUTHENTICATE=4, /**< Bootaccess authenticate operation */
	IPP_MAX_BOOTACCESS_OP=0xf
};

/* 
** iPP Power Management Interface 
*/

/** iPP POWER Management Commands */
enum ipp_pwrmgmt_cmd {
	IPP_PWRMGMT_CMD_CPU_SET_NORMAL=0, /**< Restore CPU clock */
	IPP_PWRMGMT_CMD_CPU_CLKGATE, 	/**< Clock Gate CPU */
	IPP_PWRMGMT_CMD_CPU_POWEROFF, 	/**< Power off CPU */
	IPP_PWRMGMT_CMD_CPU_FREQ_SCALE, /**< Scale up/down CPU freq */
	IPP_PWRMGMT_CMD_PLB_FREQ_SCALE, /**< Scale up/down PLB freq */
	IPP_PWRMGMT_CMD_VOLTAGE_SCALE, 	/**< Scale up/down Voltage */
	IPP_PWRMGMT_CMD_ISCALE, 	/**< Scale internal voltage */
	IPP_PWRMGMT_CMD_CPU_DBGPWROFF, 	/**< Debug power off CPU */
	IPP_PWRMGMT_CMD_SWITCH_SBUF, 	/**< Switch to Streak SBUF */
	IPP_PWRMGMT_CMD_FORCE_CPU1_PWROFF, /**<Force CPU1 off */ 
	IPP_PWRMGMT_CMD_MAX
};

enum ipp_gpio {
	IPP_GPIO_0=0, 	/**< iPP GPIO 0 */
	IPP_GPIO_1, 	/**< iPP GPIO 1 */
	IPP_GPIO_2, 	/**< iPP GPIO 2 */
	IPP_GPIO_3, 	/**< iPP GPIO 3 */
	IPP_GPIO_4, 	/**< iPP GPIO 4 */
	IPP_GPIO_5, 	/**< iPP GPIO 5 */
	IPP_GPIO_6, 	/**< iPP GPIO 6 */
	IPP_GPIO_7, 	/**< iPP GPIO 7 */
	IPP_GPIO_8, 	/**< iPP GPIO 8 */
	IPP_GPIO_9, 	/**< iPP GPIO 9 */
	IPP_GPIO_10, 	/**< iPP GPIO 10 */
	IPP_GPIO_11, 	/**< iPP GPIO 11 */
	IPP_GPIO_12, 	/**< iPP GPIO 12 */
	IPP_GPIO_13, 	/**< iPP GPIO 13 */
	IPP_GPIO_14, 	/**< iPP GPIO 14 */
	IPP_GPIO_15, 	/**< iPP GPIO 15 */
	IPP_MAX_GPI0
};

/** Possible Potenza boot devices */
enum ipp_ppcboot_devices {
	IPP_PPCBOOTDEV_NOR8=0, /**< PPC boot device NOR 8-bit*/
	IPP_PPCBOOTDEV_NOR16=1, /**< PPC boot device NOR 16-bit*/
	IPP_PPCBOOTDEV_NOR8_MUX=2, /**< PPC boot device NOR 8-bit mux*/
	IPP_PPCBOOTDEV_NOR16_MUX=3, /**< PPC boot device NOR 16-bit mux*/
	IPP_PPCBOOTDEV_SPI_NOR=4, /**< PPC boot device SPI NOR*/
	IPP_PPCBOOTDEV_EMMC=5, /**< PPC boot device eMMC */
	IPP_PPCBOOTDEV_SDIO=6, /**< PPC boot device SDIO */
	IPP_PPCBOOTDEV_USB=7,	/**< PPC boot device USB */
	IPP_PPCBOOTDEV_SATA=8, /**< PPC boot device SATA */
	IPP_PPCBOOTDEV_PCIE=9, /**< PPC boot device PCIe */
	IPP_PPCBOOTDEV_NAND=0xA, /**< PPC boot device NAND */
	IPP_PPCBOOTDEV_NAND_ECC=0xB, /**< PPC boot device NAND-ECC */
	IPP_PPCBOOTDEV_SPI_NAND=0xC, /**< PPC boot device SPI NOR*/
	IPP_PPCBOOTDEV_NULL=0xE, /**< Dummy null device to abstract memory */
	IPP_PPCBOOTDEV_MAX=0xF /**< Maximum number of PPC boot devices */
};

/* IPP Net Offload Command for setting MAC Address */
struct ipp_net_offload_mac {
	unsigned int cmd;
	unsigned char addr[8];
};

/* IPP Net Offload Command for setting Free Pool BufDataLen */
struct ipp_net_offload_bufdatalen {
	unsigned int cmd;
	unsigned int val;
};

/* IPP Net Offload Command for setting QM info */
struct ipp_net_offload_qm {
	unsigned int cmd;
#if defined(__PPC__)
	unsigned int rsvd00 : 8;
	unsigned int offloader_rx_qid : 8;
	unsigned int offloader_rx_mbid : 8;
	unsigned int offloader_rx_pbn : 8;

	unsigned int rsvd04 : 8;
	unsigned int eth_tx_qid : 8;
	unsigned int eth_tx_mbid : 8;
	unsigned int eth_tx_pbn : 8;
#else
	unsigned int offloader_rx_pbn : 8;
	unsigned int offloader_rx_mbid : 8;
	unsigned int offloader_rx_qid : 8;
	unsigned int rsvd00 : 8;

	unsigned int eth_tx_pbn : 8;
	unsigned int eth_tx_mbid : 8;
	unsigned int eth_tx_qid : 8;
	unsigned int rsvd04 : 8;
#endif
};


/* IPP LRO Message Command for setting timeout, byte count */
struct ipp_lro_message {
	unsigned int cmd;
	unsigned int val;
};

/* IPP LRO Command for setting System WQ info */
struct ipp_lro_qm_sys_wq {
	unsigned int cmd;
#if defined(__PPC__)
	unsigned int rsvd00 : 8;
	unsigned int seg_rx_qid : 8;
	unsigned int seg_rx_mbid : 8;
	unsigned int seg_rx_pbn : 8;

	unsigned int rsvd04 : 8;
	unsigned int dma_asm_qid : 8;
	unsigned int dma_asm_mbid : 8;
	unsigned int dma_asm_pbn : 8;

	unsigned int rsvd08 : 8;
	unsigned int lro_rx_qid : 8;
	unsigned int lro_rx_mbid : 8;
	unsigned int lro_rx_pbn : 8;
#else
	unsigned int seg_rx_pbn : 8;
	unsigned int seg_rx_mbid : 8;
	unsigned int seg_rx_qid : 8;
	unsigned int rsvd00 : 8;

	unsigned int dma_asm_pbn : 8;
	unsigned int dma_asm_mbid : 8;
	unsigned int dma_asm_qid : 8;
	unsigned int rsvd04 : 8;

	unsigned int lro_rx_pbn : 8;
	unsigned int lro_rx_mbid : 8;
	unsigned int lro_rx_qid : 8;
	unsigned int rsvd08 : 8;
#endif
};

/* IPP LRO Command for setting Source FP info */
struct ipp_lro_qm_src_fp {
	unsigned int cmd;
#if defined(__PPC__)
	unsigned int rsvd00 : 8;
	unsigned int seg_fp_qid : 8;
	unsigned int seg_fp_mbid : 8;
	unsigned int seg_fp_pbn : 8;

	unsigned int seg_BufDataLen;
#else
	unsigned int seg_fp_pbn : 8;
	unsigned int seg_fp_mbid : 8;
	unsigned int seg_fp_qid : 8;
	unsigned int rsvd00 : 8;

	unsigned int seg_BufDataLen;
#endif
};

/* IPP LRO Command for setting Destination FP info */
struct ipp_lro_qm_dst_fp {
	unsigned int cmd;
#if defined(__PPC__)
	unsigned int rsvd00 : 8;
	unsigned int one_fp_qid : 8;
	unsigned int one_fp_mbid : 8;
	unsigned int one_fp_pbn : 8;

	unsigned int one_BufDataLen;

	unsigned int rsvd08 : 8;
	unsigned int lro_fp_qid : 8;
	unsigned int lro_fp_mbid : 8;
	unsigned int lro_fp_pbn : 8;

	unsigned int lro_BufDataLen;
#else
	unsigned int one_fp_pbn : 8;
	unsigned int one_fp_mbid : 8;
	unsigned int one_fp_qid : 8;
	unsigned int rsvd00 : 8;

	unsigned int one_BufDataLen;

	unsigned int lro_fp_pbn : 8;
	unsigned int lro_fp_mbid : 8;
	unsigned int lro_fp_qid : 8;
	unsigned int rsvd08 : 8;

	unsigned int lro_BufDataLen;
#endif
};

#define IPP_MAX_LOG_WORDS		9
#define IPP_LOG_SIGNATURE		0x474F4C41  /* ALOG */
#define IPP_LOG_VERSION			1
/** Auth Flags BitMask */
#define IPP_LOG_COLDBOOT		(0x1)
#define IPP_LOG_FLAG_INITED		(0x1<<1)
#define IPP_LOG_FLAG_SS_VALID		(0x1<<2)

/* Keep it 32 bit aligned because registers are used   */
/* ipp_log error_code value defined in ipp_error_codes */
struct ipp_log {
	union {
		struct {
			unsigned int signature;		/* Log Signature */
			unsigned int version;		/* Log Version   */
			unsigned int flags;		/* Log Flags     */
			unsigned int warmboot_cnt;	/* WarmBoot count*/
			unsigned int error_code;	/* Error code	 */
			unsigned int auth_fail_cnt;	/* AuthFail count*/
			unsigned int auth_ok_cnt;	/* AuthOK count  */
			unsigned int psecret;		/* Pointer to Shared secret */
			unsigned int reserved;		/* Expansion pointer	*/
		} log;
		unsigned int word[IPP_MAX_LOG_WORDS];
	} data;
};


/** iPP Generic Data Buffer Index: for generic Rxdata */
/* Subtypes of IPP_GENERIC_TX_RX_ADDR_MSG_HDLR        */
/* Please add new member before IPP_MAX_DATABUF_INDEX */
enum ipp_generic_databuf_index {
	IPP_DATABUF_UNUSED=0, /**< Unused DataBuf index */
	IPP_DATABUF_SECURELOG=1, /**< Secure Log DataBuffer index */
	IPP_DATABUF_PWRMGMT=2, /**< Power Management DataBuffer index */
	IPP_DATABUF_NET=3, /**< SlimPro Network DataBuffer index */
	IPP_DATABUF_FW_FEATURES=4, /**< SlimPro FW Features DataBuffer index */
	IPP_DATABUF_LRO=5, /**< SlimPro LRO DataBuffer index */
	IPP_DATABUF_CODESWAP=6, /**< SlimPro LRO DataBuffer index */
	IPP_MAX_DATABUF_INDEX
};

/** Structure Definitions for each Generic RxData Index */
/*  in ipp_generic_databuf_index. Each index maps to a  */
/*  structure that PPC can request to get iPP data      */
/*  Add only int because swap happens at word level     */
/* ipp_pwrmgmt_stats maps to IPP_DATABUF_PWRMGMT index  */
struct ipp_pwrmgmt_stats {
	unsigned int last_wakeup_mask;		/* IPP_WAKEUP_xxx_EVENT */
	unsigned int gpio_wakeup_mask;		/* IPP_WAKEUP_GPIO_EVENT */
	unsigned int ddr_selfref_cnt;
	union {
		/* Wakeup counts - Maintain order as in IPP_MAX_xxx define */
		struct {
			unsigned int eth_wake;		/* ETH wakecnt */
			unsigned int usb_wake;		/* USB wakecnt */
			unsigned int gpio_wake;		/* GPIO wakecnt*/
			unsigned int rtc_wake;		/* RTC wakecnt */
			unsigned int sw_wake;		/* SW event wakecnt*/
		} count;
		unsigned int word[IPP_MAX_WAKEUP_EVENT];
	} wakecnt;
};

/**
 * ipp_net_stats maps to IPP_DATABUF_NET index
 * SlimPro network statistics 
 *
 * This structure represents SlimPro network statistic information
 */
typedef struct ipp_net_stats {
        unsigned int hw_mtu;		/**< Ethernet HW MTU */
        unsigned int rx_pkt_cnt;	/**< Number of packet received */
        unsigned int tx_pkt_cnt;	/**< Number of packet transmitted */
	unsigned int ipv6_rx_pkt_cnt;	/**< Number of IPv6 packet received */
        unsigned int drop_pkt_cnt;	/**< Number of packet dropped */
	unsigned int ipv6_drop_pkt_cnt;	/**< Number of packet dropped */
        unsigned int icmp_drop_pkt_cnt; /**< Number of ICMP packet dropped */
	unsigned int icmpv6_drop_pkt_cnt;
			    		/**< Number of ICMPv6 packet dropped */
        unsigned int arp_drop_pkt_cnt;  /**< Number of ARP packet dropped */
        unsigned int wol_pkt_cnt;	/**< Number of WOL packet received */
        unsigned int len_err_pkt_cnt;	/**< Number of error length packet received */
        unsigned int mac_err_pkt_cnt;	/**< Number of MAC error packet received */
        unsigned int ip_err_pkt_cnt;	/**< Number of IP error packet received */
	unsigned int ip_nbios_pkt_cnt;
	unsigned int ip_llmnr_pkt_cnt;
	unsigned int ip_snmp_pkt_cnt;
	unsigned int other_udp_pkt_cnt; 
	unsigned int comp_msg_cnt;      /**< Number of comp message received */
	unsigned int fp_dealloc_cnt;
	unsigned int rx_Lerr_cnt;      /**< Number of message with Lerr received */
} ipp_net_stats_t;

#endif /* __ASSEMBLY__ */

typedef union ipp_bd_pwr_info {
        struct {
                unsigned int adv_mode : 1;
                unsigned int tpc_en : 1;
                unsigned int avs_en : 1;
                unsigned int reset_cap : 1;
                unsigned int rsvd1 : 12;
                unsigned int pmd_vltg : 4;
                unsigned int soc_vltg : 4;
                unsigned int rsvd2 : 8;
        } inf;
        unsigned int data;
} ipp_bd_pwr_info_t;
typedef union ipp_build_info {
        struct {
                unsigned int dd : 8;
                unsigned int mm : 8;
                unsigned int yyyy : 16;
        } inf;
        unsigned int date;
} ipp_build_info_t;
typedef struct ipp_info {
        ipp_bd_pwr_info_t bd_pwr_info;
        ipp_build_info_t build_info;
} ipp_info_t;

/** 
 * Voltage Scaling Sub commands
 * Voltage Scaling can be done using DEFAULT_SUBCMD or I2C_SUBCMD
 * For DEFAULT_SUBCMD, iPP just drives SCU_PS_CTL[2] output pin 
 * For I2C_SUBCMD, PPC uses SCRATCH1/2 register to pass additional params
 */
/*@{*/
#define IPP_VOLTAGE_SCALE_DEFAULT_SUBCMD	1
#define IPP_VOLTAGE_SCALE_I2C_SUBCMD		2

/** 
 * Internal Scaling Sub commands
 */
/*@{*/
#define IPP_ISCALE_DISABLE		0	
#define IPP_ISCALE_ENABLE		1
/*@}*/

#endif /* __IPP_IFACE_H__ */
