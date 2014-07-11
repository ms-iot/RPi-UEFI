/** @file

  The definition for OHCI register operation routines.

Copyright (c) 2007, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _EFI_OHCI_QUEUE_H_
#define _EFI_OHCI_QUEUE_H_

#if 1
//==================================================================
// data structure
//
// <OHCI>
//

typedef union 
{
	UINT32 data;
	struct {
		// bit[6:0] : function address
		unsigned func_addr : 7;
		// bit[10:7] : endpoint number
		unsigned ep_num : 4;
		// bit[12:11] : direction
		unsigned direction : 2;
		// bit[13] : speed
		unsigned  speed : 1;
		// bit[14] : skip (1->skip this ED)
		unsigned  skip : 1;
		// bit[15] : format (0->gTD, 1->isoTD)
		unsigned  format : 1;		
		// bit[26:16] : maximum packet size
		unsigned mps : 11;
		// bit[31:27] : 
		unsigned reserved31_27 : 5;
	}b;
}ed_info_t;

typedef struct 
{
	ed_info_t ed_info;
	UINT32 tail_td_ptr;
	UINT32 head_td_ptr;
	UINT32 next_ed;
} OHCI_ED_HW;

typedef union 
{
	UINT32 data;
	struct {
		// bit[17:0] : 
		unsigned reserved17_0 : 18;
		// bit[18] : buffer rounding (0->exactly fill the defined buffer, 1->may be smaller than the defined buffer)
		unsigned  buffer_rounding : 1;
		// bit[20:19] : pid (0->setup, 1->out, 2->in, 3->reserved)
		unsigned pid : 2;
		// bit[23:21] : delay interrupt
		unsigned delay_interrupt : 3;
		// bit[25:24] : data toggle
		unsigned data_toggle : 2;
		// bit[27:26] : error count
		unsigned error_count : 2;
		// bit[31:28] : condition code
		unsigned condition_code : 4;
	}b;
}gtd_info_t;

typedef struct 
{
	gtd_info_t gtd_info;
	UINT32 current_buf_ptr;
	UINT32 next_td;
	UINT32 buffer_end;
} OHCI_TD_HW;

typedef struct _OHCI_TD_SW  OHCI_TD_SW;

struct _OHCI_TD_SW{
  OHCI_TD_HW        *TdHw;
  OHCI_TD_SW        *NextTd;
	UINT32						*Data;
	UINT32						DataLen;
};

struct _OHCI_HCCA {
#define NUM_INTS 32
	UINT32	int_table [NUM_INTS];	/* periodic schedule */

	/*
	 * OHCI defines u16 frame_no, followed by u16 zero pad.
	 * Since some processors can't do 16 bit bus accesses,
	 * portable access must be a 32 bits wide.
	 */
	UINT32	frame_no;		/* current frame number */
	UINT32	done_head;		/* info returned for an interrupt */
	UINT8		reserved_for_hc [116];
	UINT8 	what [4];		/* spec only identifies 252 bytes :) */
} __attribute__ ((aligned(256)));

typedef struct _OHCI_HCCA OHCI_HCCA;


















typedef struct {
  UINT32              HorizonLink;
  UINT32              VerticalLink;
} OHCI_QH_HW;

typedef struct _OHCI_QH_SW  OHCI_QH_SW;

struct _OHCI_QH_SW {
  OHCI_QH_HW        QhHw;
  OHCI_QH_SW        *NextQh;
  OHCI_TD_HW        *TDs;
  UINTN             Interval;
};
#else
//
// Macroes used to set various links in OHCI's driver.
// In this OHCI driver, QH's horizontal link always pointers to other QH,
// and its vertical link always pointers to TD. TD's next pointer always
// pointers to other sibling TD. Frame link always pointers to QH because
// ISO transfer isn't supported.
//
// We should use UINT32 to access these pointers to void race conditions
// with hardware.
//
#define QH_HLINK(Pointer, Terminate)  \
        (((UINT32) ((UINTN) (Pointer)) & 0xFFFFFFF0) | 0x02 | ((Terminate) ? 0x01 : 0))

#define QH_VLINK(Pointer, Terminate)  \
        (((UINT32) ((UINTN) (Pointer)) & 0xFFFFFFF0) | ((Terminate) ? 0x01 : 0))

#define TD_LINK(Pointer, VertFirst, Terminate) \
        (((UINT32) ((UINTN) (Pointer)) & 0xFFFFFFF0) | \
         ((VertFirst) ? 0x04 : 0) | ((Terminate) ? 0x01 : 0))

#define LINK_TERMINATED(Link) (((Link) & 0x01) != 0)

#define OHCI_ADDR(QhOrTd)     ((VOID *) (UINTN) ((QhOrTd) & 0xFFFFFFF0))

#pragma pack(1)
//
// Both links in QH has this internal structure:
//   Next pointer: 28, Reserved: 2, NextIsQh: 1, Terminate: 1
// This is the same as frame list entry.
//
typedef struct {
  UINT32              HorizonLink;
  UINT32              VerticalLink;
} OHCI_QH_HW;

//
// Next link in TD has this internal structure:
//   Next pointer: 28, Reserved: 1, Vertical First: 1, NextIsQh: 1, Terminate: 1
//
typedef struct {
  UINT32              NextLink;
  UINT32              ActualLen   : 11;
  UINT32              Reserved1   : 5;
  UINT32              Status      : 8;
  UINT32              IntOnCpl    : 1;
  UINT32              IsIsoch     : 1;
  UINT32              LowSpeed    : 1;
  UINT32              ErrorCount  : 2;
  UINT32              ShortPacket : 1;
  UINT32              Reserved2   : 2;
  UINT32              PidCode     : 8;
  UINT32              DeviceAddr  : 7;
  UINT32              EndPoint    : 4;
  UINT32              DataToggle  : 1;
  UINT32              Reserved3   : 1;
  UINT32              MaxPacketLen: 11;
  UINT32              DataBuffer;
} OHCI_TD_HW;
#pragma pack()

typedef struct _OHCI_TD_SW  OHCI_TD_SW;
typedef struct _OHCI_QH_SW  OHCI_QH_SW;

struct _OHCI_QH_SW {
  OHCI_QH_HW        QhHw;
  OHCI_QH_SW        *NextQh;
  OHCI_TD_SW        *TDs;
  UINTN             Interval;
};

struct _OHCI_TD_SW {
  OHCI_TD_HW        TdHw;
  OHCI_TD_SW        *NextTd;
  UINT8             *Data;
  UINT16            DataLen;
};
#endif

/**
  Link the TD To QH.

  @param  Ohc         The OHCI device.
  @param  Qh          The queue head for the TD to link to.
  @param  Td          The TD to link.

**/
VOID
OhciLinkTdToQh (
  IN USB_HC_DEV           *Ohc,
  IN OHCI_ED_HW           *Ed,
  IN UINT8								Class
  );


/**
  Unlink TD from the QH.

  @param  Qh          The queue head to unlink from.
  @param  Td          The TD to unlink.

  @return None.

**/
VOID
OhciUnlinkTdFromQh (
  IN OHCI_QH_SW           *Qh,
  IN OHCI_TD_HW           *Td
  );

/**
  Map address of request structure buffer.

  @param  Ohc                The OHCI device.
  @param  Request            The user request buffer.
  @param  MappedAddr         Mapped address of request.
  @param  Map                Identificaion of this mapping to return.

  @return EFI_SUCCESS        Success.
  @return EFI_DEVICE_ERROR   Fail to map the user request.

**/
EFI_STATUS
OhciMapUserRequest (
  IN  USB_HC_DEV          *Ohc,
  IN  OUT VOID            *Request,
  OUT UINT8               **MappedAddr,
  OUT VOID                **Map
  );


/**
  Map address of user data buffer.

  @param  Ohc                The OHCI device.
  @param  Direction          Direction of the data transfer.
  @param  Data               The user data buffer.
  @param  Len                Length of the user data.
  @param  PktId              Packet identificaion.
  @param  MappedAddr         Mapped address to return.
  @param  Map                Identificaion of this mapping to return.

  @return EFI_SUCCESS        Success.
  @return EFI_DEVICE_ERROR   Fail to map the user data.

**/
EFI_STATUS
OhciMapUserData (
  IN  USB_HC_DEV              *Ohc,
  IN  EFI_USB_DATA_DIRECTION  Direction,
  IN  VOID                    *Data,
  IN  OUT UINTN               *Len,
  OUT UINT8                   *PktId,
  OUT UINT8                   **MappedAddr,
  OUT VOID                    **Map
  );


/**
  Delete a list of TDs.

  @param  Ohc         The OHCI device.
  @param  FirstTd     TD link list head.

  @return None.

**/
VOID
OhciDestoryTds (
  IN USB_HC_DEV           *Ohc,
  IN OHCI_TD_SW           *FirstTd
  );


/**
  Create an initialize a new queue head.

  @param  Ohc         The OHCI device.
  @param  Interval    The polling interval for the queue.

  @return The newly created queue header.

**/
OHCI_QH_SW *
OhciCreateQh (
  IN  USB_HC_DEV        *Ohc,
  IN  UINTN             Interval
  );


/**
  Create Tds list for Control Transfer.

  @param  Ohc         The OHCI device.
  @param  DeviceAddr  The device address.
  @param  DataPktId   Packet Identification of Data Tds.
  @param  Request     A pointer to cpu memory address of request structure buffer to transfer.
  @param  RequestPhy  A pointer to pci memory address of request structure buffer to transfer.
  @param  Data        A pointer to cpu memory address of user data buffer to transfer.
  @param  DataPhy     A pointer to pci memory address of user data buffer to transfer.
  @param  DataLen     Length of user data to transfer.
  @param  MaxPacket   Maximum packet size for control transfer.
  @param  IsLow       Full speed or low speed.

  @return The Td list head for the control transfer.

**/
OHCI_ED_HW *
OhciCreateCtrlTds (
  IN USB_HC_DEV           *Ohc,
  IN UINT8                DeviceAddr,
  IN UINT8                DataPktId,
  IN UINT8                *Request,
  IN UINT8                *RequestPhy,
  IN UINT8                *Data,
  IN UINT8                *DataPhy,
  IN UINTN                DataLen,
  IN UINT8                MaxPacket,
  IN BOOLEAN              IsLow
  );


/**
  Create Tds list for Bulk/Interrupt Transfer.

  @param  Ohc         USB_HC_DEV.
  @param  DevAddr     Address of Device.
  @param  EndPoint    Endpoint Number.
  @param  PktId       Packet Identification of Data Tds.
  @param  Data        A pointer to cpu memory address of user data buffer to transfer.
  @param  DataPhy     A pointer to pci memory address of user data buffer to transfer.
  @param  DataLen     Length of user data to transfer.
  @param  DataToggle  Data Toggle Pointer.
  @param  MaxPacket   Maximum packet size for Bulk/Interrupt transfer.
  @param  IsLow       Is Low Speed Device.

  @return The Tds list head for the bulk transfer.

**/
OHCI_TD_HW *
OhciCreateBulkOrIntTds (
  IN USB_HC_DEV           *Ohc,
  IN UINT8                DevAddr,
  IN UINT8                EndPoint,
  IN UINT8                PktId,
  IN UINT8                *Data,
  IN UINT8                *DataPhy,
  IN UINTN                DataLen,
  IN OUT UINT8            *DataToggle,
  IN UINT8                MaxPacket,
  IN BOOLEAN              IsLow
  );

#endif
