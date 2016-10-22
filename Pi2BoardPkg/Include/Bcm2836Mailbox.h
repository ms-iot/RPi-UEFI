/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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

#ifndef __BCM2836MAILBOX_H__
#define __BCM2836MAILBOX_H__


/* c == Core Number, m == Mailbox number */
#define CORE_MAILBOX_WRITE_SET(c, m) (ARM_PERIPHERAL_BASE_ADDRESS + 0x80 + ((c) * 4 * 4) + ((m) * 4) )
#define CORE_MAILBOX_READ(c, m)      (ARM_PERIPHERAL_BASE_ADDRESS + 0xC0 + ((c) * 4 * 4) + ((m) * 4) )
#define CORE_MAILBOX_CLEAR(c, m)     (ARM_PERIPHERAL_BASE_ADDRESS + 0xC0 + ((c) * 4 * 4) + ((m) * 4) )
#define CORE_MAILBOX_CLEAR_VALUE     (0xFFFFFFFF)

// Timeout
#define MAILBOX_MAX_POLL   0x000F0000

// VC Mailbox register
#define MAILBOX_BASE       0x3F00B880       // Base address of mailbox register set

#define MAILBOX_READ_REG   (MAILBOX_BASE + 0x00)
#define MAILBOX_POLL_REG   (MAILBOX_BASE + 0x10)
#define MAILBOX_SENDER_REG (MAILBOX_BASE + 0x14)
#define MAILBOX_STATUS_REG (MAILBOX_BASE + 0x18)
#define MAILBOX_CONFIG_REG (MAILBOX_BASE + 0x1C)
#define MAILBOX_WRITE_REG  (MAILBOX_BASE + 0x20)

// VC Mailbox Status
#define MAILBOX_STATUS_EMPTY 0x40000000
#define MAILBOX_STATUS_FULL  0x80000000

// VC Mailbox Channel
#define MAILBOX_CHANNEL_POWER_MGMT      0
#define MAILBOX_CHANNEL_FRAMEBUFFER     1
#define MAILBOX_CHANNEL_VIRTUAL_UART    2
#define MAILBOX_CHANNEL_VCHIQ           3
#define MAILBOX_CHANNEL_LED             4
#define MAILBOX_CHANNEL_BUTTON          5
#define MAILBOX_CHANNEL_TOUCH_SCREEN    6
#define MAILBOX_CHANNEL_PROPERTY_ARM_VC 8
#define MAILBOX_CHANNEL_PROPERTY_VC_ARM 9
#define MAILBOX_CHANNEL_MASK            0x0000000F

// VC Mailbox Power management bits
// These needs to be shifted by 4 bits
// as the first 4 bits are used to indicate
// the channel
#define POWER_SD        0x0001
#define POWER_UART      0x0002
#define POWER_MINIUART  0x0004
#define POWER_USB       0x0008
#define POWER_12C0      0x0010
#define POWER_12C1      0x0020
#define POWER_12C2      0x0040
#define POWER_SPI       0x0080
#define POWER_CCP2TX    0x0100
#define POWER_DSI       0x0200

// Mask to access memory in an uncached manner
#define UNCACHED_ADDRESS_MASK 0xC0000000

// Mailbox property structure
#pragma pack(push, 16)
// Structure passed to the mailbox framebuffer interface
typedef struct _MAILBOX_FRAMEBUFFER {
    UINT32 mbf_phys_width;
    UINT32 mbf_phys_height;
    UINT32 mbf_virt_width;
    UINT32 mbf_virt_height;
    UINT32 mbf_pitch;
    UINT32 mbf_depth;
    UINT32 mbf_x_offset;
    UINT32 mbf_y_offset;
    UINT32 mbf_framebuf_addr;
    UINT32 mbf_framebuf_size;
    UINT16 mbf_cmap[256];
} MAILBOX_FRAMEBUFFER, *PMAILBOX_FRAMEBUFFER;

typedef struct _MAILBOX_HEADER
{
    UINT32 BufferSize;
    UINT32 RequestResponse;
    UINT32 TagID;
    UINT32 TagLength;
    UINT32 Request;
}MAILBOX_HEADER, *PMAILBOX_HEADER;

#define TAG_GET_PHYSICAL_SIZE 0x00040003
typedef struct _MAILBOX_PHYSICAL_SIZE
{
    MAILBOX_HEADER Header;
    UINT32 Width;
    UINT32 Height;
    UINT32 EndTag;
}MAILBOX_PHYSICAL_SIZE, *PMAILBOX_PHYSICAL_SIZE;

#define TAG_GET_CLOCK_RATE      0x00030002
#define TAG_GET_MAX_CLOCK_RATE  0x00030004
#define TAG_GET_MIN_CLOCK_RATE  0x00030007
typedef struct _MAILBOX_GET_CLOCK_RATE
{
    MAILBOX_HEADER Header;
    UINT32 ClockId;
    UINT32 Rate;
    UINT32 EndTag;
}MAILBOX_GET_CLOCK_RATE, *PMAILBOX_GET_CLOCK_RATE;

#define TAG_SET_CLOCK_RATE  0x00038002
typedef struct _MAILBOX_SET_CLOCK_RATE {
    MAILBOX_HEADER Header;
    UINT32 ClockId;
    UINT32 Rate;
    UINT32 SkipSettingTurbo;
    UINT32 EndTag;
} MAILBOX_SET_CLOCK_RATE, *PMAILBOX_SET_CLOCK_RATE;

#define TAG_GET_BOARD_SERIAL 0x00010004
typedef struct _MAILBOX_BOARD_SERIAL
{
    MAILBOX_HEADER Header;
    UINT8 BoardSerial[8];
}MAILBOX_BOARD_SERIAL, *PMAILBOX_BOARD_SERIAL;

#define TAG_GET_ARM_MEMORY 0x00010005
#define TAG_GET_VC_MEMORY 0x00010006
typedef struct _MAILBOX_GET_MEMORY
{
    MAILBOX_HEADER Header;
    UINT32 BaseAddress;
    UINT32 Size;
}MAILBOX_GET_MEMORY, *PMAILBOX_GET_MEMORY;

#define TAG_GET_GPIOVIRTBUF 0x00040010
typedef struct _MAILBOX_GET_GPIO_VIRT_ADDR
{
    MAILBOX_HEADER Header;
    UINT32 GpioVirtAddr;
    UINT32 EndTag;
}MAILBOX_GET_GPIO_VIRT_ADDR, *PMAILBOX_GET_GPIO_VIRT_ADDR;

#define TAG_RELEASE_BUFFER 0x00048001

#define CLOCK_ID_RESERVED       0x000000000
#define CLOCK_ID_EMMC           0x000000001
#define CLOCK_ID_UART           0x000000002
#define CLOCK_ID_ARM            0x000000003
#define CLOCK_ID_CORE           0x000000004
#define CLOCK_ID_V3D            0x000000005
#define CLOCK_ID_H264           0x000000006
#define CLOCK_ID_ISP            0x000000007
#define CLOCK_ID_SDRAM          0x000000008
#define CLOCK_ID_PIXEL          0x000000009
#define CLOCK_ID_PWM            0x00000000A

#pragma pack(pop)

#endif // __BCM2836MAILBOX_H__