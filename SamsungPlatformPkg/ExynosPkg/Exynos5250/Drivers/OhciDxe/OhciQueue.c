/** @file

  The OHCI register operation routines.

Copyright (c) 2007 - 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "Ohci.h"


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
  )
{
  EFI_STATUS            Status;
  UINTN                 Len;
  EFI_PHYSICAL_ADDRESS  PhyAddr;

#if 1
  Len    = sizeof (EFI_USB_DEVICE_REQUEST);
  Status = Ohc->PciIo->Map (
                         Ohc->PciIo,
                         EfiPciIoOperationBusMasterWrite,
                         Request,
                         &Len,
                         &PhyAddr,
                         Map
                         );

  if (!EFI_ERROR (Status)) {
    *MappedAddr = (UINT8 *) (UINTN) PhyAddr;
  }
#else
  Len    = sizeof (EFI_USB_DEVICE_REQUEST);
  Status = Ohc->PciIo->Map (
                         Ohc->PciIo,
                         EfiPciIoOperationBusMasterRead,
                         Request,
                         &Len,
                         &PhyAddr,
                         Map
                         );

  if (!EFI_ERROR (Status)) {
    *MappedAddr = (UINT8 *) (UINTN) PhyAddr;
  }
#endif
  return Status;
}


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
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  PhyAddr;

  Status = EFI_SUCCESS;
#if 1
	switch (Direction) {
  case EfiUsbDataIn:
    //
    // BusMasterWrite means cpu read
    //
    *PktId = INPUT_PACKET_ID;
    Status = Ohc->PciIo->Map (
                           Ohc->PciIo,
                           EfiPciIoOperationBusMasterRead,
                           Data,
                           Len,
                           &PhyAddr,
                           Map
                           );

    if (EFI_ERROR (Status)) {
      goto EXIT;
    }
		DEBUG((EFI_D_INIT, "Read Mapped : %p\n", *Map));
    *MappedAddr = (UINT8 *) (UINTN) PhyAddr;
    break;

  case EfiUsbDataOut:
    *PktId = OUTPUT_PACKET_ID;
    Status = Ohc->PciIo->Map (
                           Ohc->PciIo,
                           EfiPciIoOperationBusMasterWrite,
                           Data,
                           Len,
                           &PhyAddr,
                           Map
                           );

    if (EFI_ERROR (Status)) {
      goto EXIT;
    }
		DEBUG((EFI_D_INIT, "Write Mapped : %p\n", *Map));
    *MappedAddr = (UINT8 *) (UINTN) PhyAddr;
    break;

  case EfiUsbNoData:
    if ((Len != NULL) && (*Len != 0)) {
      Status    = EFI_INVALID_PARAMETER;
      goto EXIT;
    }
		DEBUG((EFI_D_INIT, "No Mapped : %p\n", *Map));
    *PktId      = OUTPUT_PACKET_ID;
    *MappedAddr = NULL;
    *Map        = NULL;
    break;

  default:
    Status      = EFI_INVALID_PARAMETER;
  }
#else
  switch (Direction) {
  case EfiUsbDataIn:
    //
    // BusMasterWrite means cpu read
    //
    *PktId = INPUT_PACKET_ID;
    Status = Ohc->PciIo->Map (
                           Ohc->PciIo,
                           EfiPciIoOperationBusMasterWrite,
                           Data,
                           Len,
                           &PhyAddr,
                           Map
                           );

    if (EFI_ERROR (Status)) {
      goto EXIT;
    }

    *MappedAddr = (UINT8 *) (UINTN) PhyAddr;
    break;

  case EfiUsbDataOut:
    *PktId = OUTPUT_PACKET_ID;
    Status = Ohc->PciIo->Map (
                           Ohc->PciIo,
                           EfiPciIoOperationBusMasterRead,
                           Data,
                           Len,
                           &PhyAddr,
                           Map
                           );

    if (EFI_ERROR (Status)) {
      goto EXIT;
    }

    *MappedAddr = (UINT8 *) (UINTN) PhyAddr;
    break;

  case EfiUsbNoData:
    if ((Len != NULL) && (*Len != 0)) {
      Status    = EFI_INVALID_PARAMETER;
      goto EXIT;
    }

    *PktId      = OUTPUT_PACKET_ID;
    *MappedAddr = NULL;
    *Map        = NULL;
    break;

  default:
    Status      = EFI_INVALID_PARAMETER;
  }
#endif
EXIT:
  return Status;
}


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
  )
{
#if 1
		UINT32 cmd;

		if(Class == HC_CLASS_CONTROL) //Controll
		{
			/*
			cmd = OhciReadReg(Ohc, HC_CONTROL_OFFSET);
			cmd &= ~(1<<5);
			OhciWriteReg(Ohc, HC_CONTROL_OFFSET, cmd);	*/
			
			cmd = OhciReadReg(Ohc, HC_COM_STATUS_OFFSET);
			cmd |= (1<<1);
			OhciWriteReg(Ohc, HC_COM_STATUS_OFFSET, cmd);

			OhciWriteReg(Ohc, HC_CTRL_HEADED_OFFSET, Ed);
			
			cmd = OhciReadReg(Ohc, HC_CONTROL_OFFSET);
			cmd |= (1<<4);
			OhciWriteReg(Ohc, HC_CONTROL_OFFSET, cmd);	
		}
		else//Interrupt
		{/*
			cmd = OhciReadReg(Ohc, HC_CONTROL_OFFSET);
			cmd &= ~(1<<4);
			OhciWriteReg(Ohc, HC_CONTROL_OFFSET, cmd);	
			*/
			cmd = OhciReadReg(Ohc, HC_COM_STATUS_OFFSET);
			cmd |= (1<<2);
			OhciWriteReg(Ohc, HC_COM_STATUS_OFFSET, cmd);

			OhciWriteReg(Ohc, HC_BULK_HEADED_OFFSET, Ed);
			
			cmd = OhciReadReg(Ohc, HC_CONTROL_OFFSET);
			cmd |= (1<<5);
			OhciWriteReg(Ohc, HC_CONTROL_OFFSET, cmd);	
		}
#else
  EFI_PHYSICAL_ADDRESS  PhyAddr;

  PhyAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, Td, sizeof (OHCI_TD_HW));

  ASSERT ((Qh != NULL) && (Td != NULL));

  Qh->QhHw.VerticalLink = QH_VLINK (PhyAddr, FALSE);
  Qh->TDs               = (VOID *) Td;
#endif
}


/**
  Unlink TD from the QH.

  @param  Qh          The queue head to unlink from.
  @param  Td          The TD to unlink.

**/
VOID
OhciUnlinkTdFromQh (
  IN OHCI_QH_SW           *Qh,
  IN OHCI_TD_HW           *Td
  )
{
#if 1
#else
  ASSERT ((Qh != NULL) && (Td != NULL));

  Qh->QhHw.VerticalLink = QH_VLINK (NULL, TRUE);
  Qh->TDs               = NULL;
#endif
}


/**
  Append a new TD To the previous TD.

  @param  Ohc         The OHCI device.
  @param  PrevTd      Previous OHCI_TD_HW to be linked to.
  @param  ThisTd      TD to link.

**/
VOID
OhciAppendTd (
  IN USB_HC_DEV     *Ohc,
  IN OHCI_TD_HW     *PrevTd,
  IN OHCI_TD_HW     *ThisTd
  )
{
  EFI_PHYSICAL_ADDRESS  PhyAddr;

  //PhyAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, ThisTd, sizeof (OHCI_TD_HW));

  ASSERT ((PrevTd != NULL) && (ThisTd != NULL));

#if 1
	PrevTd->next_td       = (VOID *) ThisTd;
#else
  PrevTd->TdHw.NextLink = TD_LINK (PhyAddr, TRUE, FALSE);
  PrevTd->NextTd        = (VOID *) ThisTd;
#endif
}


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
  )
{
  OHCI_TD_SW            *NextTd;
  OHCI_TD_SW            *ThisTd;

	DEBUG((EFI_D_INIT, "+++OhciDestoryTds()\n"));

  NextTd = FirstTd;

  while (NextTd != NULL) {
    ThisTd  = NextTd;
    NextTd  = ThisTd->NextTd;
		if(ThisTd->TdHw)
		{
			DEBUG((EFI_D_INIT, "Destroy TDHW : %p\n", ThisTd->TdHw));
			UsbHcFreeMem (Ohc->MemPool, ThisTd->TdHw, sizeof (OHCI_TD_HW));
		}
		DEBUG((EFI_D_INIT, "Destroy THSW : %p\n", ThisTd));
    UsbHcFreeMem (Ohc->MemPool, ThisTd, sizeof (OHCI_TD_SW));
  }

	DEBUG((EFI_D_INIT, "---OhciDestoryTds()\n"));
}


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
  )
{
  OHCI_QH_SW            *Qh;
#if 1
#else
  Qh = UsbHcAllocateMem (Ohc->MemPool, sizeof (OHCI_QH_SW));

  if (Qh == NULL) {
    return NULL;
  }

  Qh->QhHw.HorizonLink  = QH_HLINK (NULL, TRUE);
  Qh->QhHw.VerticalLink = QH_VLINK (NULL, TRUE);
  Qh->Interval          = OhciConvertPollRate(Interval);
  Qh->TDs               = NULL;
  Qh->NextQh            = NULL;
#endif
  return Qh;
}


/**
  Create and intialize a TD.

  @param  Ohc         The OHCI device.

  @return The newly allocated and initialized TD.

**/
OHCI_TD_HW *
OhciCreateTd (
  IN  USB_HC_DEV          *Ohc
  )
{
  OHCI_TD_HW              *Td;

  Td     = UsbHcAllocateMem (Ohc->MemPool, sizeof (OHCI_TD_HW));
  if (Td == NULL) {
    return NULL;
  }

  Td->current_buf_ptr  = NULL;
  Td->next_td          = NULL;
  Td->buffer_end       = NULL;

  return Td;
}


/**
  Create and initialize a TD for Setup Stage of a control transfer.

  @param  Ohc         The OHCI device.
  @param  DevAddr     Device address.
  @param  Request     A pointer to cpu memory address of Device request.
  @param  RequestPhy  A pointer to pci memory address of Device request.
  @param  IsLow       Full speed or low speed.

  @return The created setup Td Pointer.

**/
OHCI_TD_HW *
OhciCreateSetupTd (
  IN  USB_HC_DEV          *Ohc,
  IN  UINT8               DevAddr,
  IN  UINT8               *Request,
  IN  UINT8               *RequestPhy,
  IN  BOOLEAN             IsLow
  )
{
  OHCI_TD_HW              *Td;

  Td = OhciCreateTd (Ohc);

  if (Td == NULL) {
    return NULL;
  }
#if 1
	OhcDumpRequest(RequestPhy);
	DEBUG((EFI_D_INIT, "LowSpeed : %d\n", IsLow));

	Td->gtd_info.data = 0;
	Td->gtd_info.b.buffer_rounding = 0;
	Td->gtd_info.b.pid = SETUP_PACKET_ID;
	Td->gtd_info.b.data_toggle = 2;	// DATA0
	Td->current_buf_ptr = (UINT32)RequestPhy;
	Td->next_td = NULL;
	Td->buffer_end = (UINT32)RequestPhy + sizeof (EFI_USB_DEVICE_REQUEST)-1;
#else
  Td->TdHw.NextLink     = TD_LINK (NULL, TRUE, TRUE);
  Td->TdHw.ShortPacket  = FALSE;
  Td->TdHw.IsIsoch      = FALSE;
  Td->TdHw.IntOnCpl     = FALSE;
  Td->TdHw.ErrorCount   = 0x03;
  Td->TdHw.Status      |= USBTD_ACTIVE;
  Td->TdHw.DataToggle   = 0;
  Td->TdHw.EndPoint     = 0;
  Td->TdHw.LowSpeed     = IsLow ? 1 : 0;
  Td->TdHw.DeviceAddr   = DevAddr & 0x7F;
  Td->TdHw.MaxPacketLen = (UINT32) (sizeof (EFI_USB_DEVICE_REQUEST) - 1);
  Td->TdHw.PidCode      = SETUP_PACKET_ID;
  Td->TdHw.DataBuffer   = (UINT32) (UINTN) RequestPhy;

  Td->Data              = Request;
  Td->DataLen           = (UINT16) sizeof (EFI_USB_DEVICE_REQUEST);
#endif
  return Td;
}


/**
  Create a TD for data.

  @param  Ohc         The OHCI device.
  @param  DevAddr     Device address.
  @param  Endpoint    Endpoint number.
  @param  DataPtr     A pointer to cpu memory address of Data buffer.
  @param  DataPhyPtr  A pointer to pci memory address of Data buffer.
  @param  Len         Data length.
  @param  PktId       Packet ID.
  @param  Toggle      Data toggle value.
  @param  IsLow       Full speed or low speed.

  @return Data Td pointer if success, otherwise NULL.

**/
OHCI_TD_HW *
OhciCreateDataTd (
  IN  USB_HC_DEV          *Ohc,
  IN  UINT8               DevAddr,
  IN  UINT8               Endpoint,
  IN  UINT8               *DataPtr,
  IN  UINT8               *DataPhyPtr,
  IN  UINTN               Len,
  IN  UINT8               PktId,
  IN  UINT8               Toggle,
  IN  BOOLEAN             IsLow
  )
{
  OHCI_TD_HW  *Td;

	//DEBUG((EFI_D_INIT, "+++OhciCreateDataTd(Len : %d)\n", Len));
	
  //
  // Code as length - 1, and the max valid length is 0x500
  //
  ASSERT (Len <= 0x500);

  Td  = OhciCreateTd (Ohc);

  if (Td == NULL) {
    return NULL;
  }

#if 1
	Td->gtd_info.data = 0;
	Td->gtd_info.b.buffer_rounding = 1;	// may be smaller than the defined buffer
	Td->gtd_info.b.pid = PktId;
	Td->gtd_info.b.data_toggle = Toggle;	// DATA1
	Td->current_buf_ptr = (UINT32) (UINTN) DataPhyPtr;
	Td->next_td = NULL;
	Td->buffer_end = (UINT32) (UINTN) DataPhyPtr + Len-1;
#else
  Td->TdHw.NextLink     = TD_LINK (NULL, TRUE, TRUE);
  Td->TdHw.ShortPacket  = FALSE;
  Td->TdHw.IsIsoch      = FALSE;
  Td->TdHw.IntOnCpl     = FALSE;
  Td->TdHw.ErrorCount   = 0x03;
  Td->TdHw.Status       = USBTD_ACTIVE;
  Td->TdHw.LowSpeed     = IsLow ? 1 : 0;
  Td->TdHw.DataToggle   = Toggle & 0x01;
  Td->TdHw.EndPoint     = Endpoint & 0x0F;
  Td->TdHw.DeviceAddr   = DevAddr & 0x7F;
  Td->TdHw.MaxPacketLen = (UINT32) (Len - 1);
  Td->TdHw.PidCode      = (UINT8) PktId;
  Td->TdHw.DataBuffer   = (UINT32) (UINTN) DataPhyPtr;

  Td->Data              = DataPtr;
  Td->DataLen           = (UINT16) Len;
#endif

	//DEBUG((EFI_D_INIT, "---OhciCreateDataTd()\n"));

  return Td;
}


/**
  Create TD for the Status Stage of control transfer.

  @param  Ohc         The OHCI device.
  @param  DevAddr     Device address.
  @param  PktId       Packet ID.
  @param  IsLow       Full speed or low speed.

  @return Status Td Pointer.

**/
OHCI_TD_HW *
OhciCreateStatusTd (
  IN  USB_HC_DEV          *Ohc,
  IN  UINT8               DevAddr,
  IN  UINT8               PktId,
  IN  BOOLEAN             IsLow
  )
{
  OHCI_TD_HW              *Td;

  Td = OhciCreateTd (Ohc);

  if (Td == NULL) {
    return NULL;
  }

#if 1
	Td->gtd_info.data = 0;
	Td->gtd_info.b.buffer_rounding = 1;	// may be smaller than the defined buffer
	Td->gtd_info.b.pid = PktId;
	Td->gtd_info.b.data_toggle = 3;	// DATA1
	Td->current_buf_ptr = 0;
	Td->next_td = 0;
	Td->buffer_end = 0;
#else
  Td->TdHw.NextLink     = TD_LINK (NULL, TRUE, TRUE);
  Td->TdHw.ShortPacket  = FALSE;
  Td->TdHw.IsIsoch      = FALSE;
  Td->TdHw.IntOnCpl     = FALSE;
  Td->TdHw.ErrorCount   = 0x03;
  Td->TdHw.Status      |= USBTD_ACTIVE;
  Td->TdHw.MaxPacketLen = 0x7FF;      //0x7FF: there is no data (refer to OHCI spec)
  Td->TdHw.DataToggle   = 1;
  Td->TdHw.EndPoint     = 0;
  Td->TdHw.LowSpeed     = IsLow ? 1 : 0;
  Td->TdHw.DeviceAddr   = DevAddr & 0x7F;
  Td->TdHw.PidCode      = (UINT8) PktId;
  Td->TdHw.DataBuffer   = (UINT32) (UINTN) NULL;

  Td->Data              = NULL;
  Td->DataLen           = 0;
#endif
  return Td;
}

OHCI_ED_HW *
OhciCreateEd (
  IN USB_HC_DEV           *Ohc,
  IN UINT8                DeviceAddr,
  IN UINT32               *QH,
  IN UINT8                MaxPacket,
  IN BOOLEAN              IsLow
  )
{
	OHCI_ED_HW              *Ed;

  Ed = UsbHcAllocateMem (Ohc->MemPool, sizeof (OHCI_ED_HW));
  if (Ed == NULL) {
    return NULL;
  }

	Ed->ed_info.data = 0;
	Ed->ed_info.b.func_addr = DeviceAddr;
	Ed->ed_info.b.ep_num = 0;
	Ed->ed_info.b.direction = 0;
	Ed->ed_info.b.speed = IsLow?1:0;	// speed
	Ed->ed_info.b.format = 0;	// gTD
	Ed->ed_info.b.mps = MaxPacket;
	Ed->tail_td_ptr = 0;
	Ed->head_td_ptr = QH;
	Ed->next_ed = 0;

	return Ed;
}

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
  )
{
	OHCI_ED_HW								*Ed;
  OHCI_TD_HW                *SetupTd;
  OHCI_TD_HW                *FirstDataTd;
  OHCI_TD_HW                *DataTd;
  OHCI_TD_HW                *PrevDataTd;
  OHCI_TD_HW                *StatusTd;
  UINT8                     DataToggle;
  UINT8                     StatusPktId;
  UINTN                     ThisTdLen;


  DataTd      = NULL;
  SetupTd     = NULL;
  FirstDataTd = NULL;
  PrevDataTd  = NULL;
  StatusTd    = NULL;

  //
  // Create setup packets for the transfer
  //
  SetupTd = OhciCreateSetupTd (Ohc, DeviceAddr, Request, RequestPhy, IsLow);

  if (SetupTd == NULL) {
    return NULL;
  }

  //
  // Create data packets for the transfer
  //
  DataToggle = 1;
	DEBUG((EFI_D_INIT, "Max Len %d, Dat Len ; %d\n", MaxPacket, DataLen));
  while (DataLen > 0) {
    //
    // PktSize is the data load size in each Td.
    //
    ThisTdLen = (DataLen > MaxPacket ? MaxPacket : DataLen);

    DataTd = OhciCreateDataTd (
               Ohc,
               DeviceAddr,
               0,
               Data,  //cpu memory address
               DataPhy, //Pci memory address
               ThisTdLen,
               DataPktId,
               (DataToggle + 2),
               IsLow
               );

    if (DataTd == NULL) {
      goto FREE_TD;
    }

    if (FirstDataTd == NULL) {
      FirstDataTd          = DataTd;
      FirstDataTd->next_td = NULL;
    } else {
      OhciAppendTd (Ohc, PrevDataTd, DataTd);
    }

    DataToggle ^= 1;
    PrevDataTd = DataTd;
    Data += ThisTdLen;
    DataPhy += ThisTdLen;
    DataLen -= ThisTdLen;
  }

  //
  // Status packet is on the opposite direction to data packets
  //
  if (OUTPUT_PACKET_ID == DataPktId) {
    StatusPktId = INPUT_PACKET_ID;
  } else {
    StatusPktId = OUTPUT_PACKET_ID;
  }

  StatusTd = OhciCreateStatusTd (Ohc, DeviceAddr, StatusPktId, IsLow);

  if (StatusTd == NULL) {
		DEBUG((EFI_D_ERROR, "FAIL! OhciCreateStatusTd\n"));
    goto FREE_TD;
  }

  //
  // Link setup Td -> data Tds -> status Td together
  //
  if (FirstDataTd != NULL) {
    OhciAppendTd (Ohc, SetupTd, FirstDataTd);
    OhciAppendTd (Ohc, PrevDataTd, StatusTd);
  } else {
    OhciAppendTd (Ohc, SetupTd, StatusTd);
  }

	//iky

	Ed = Ohc->EdHw[0];
	Ed->ed_info.data = 0;
	Ed->ed_info.b.func_addr = DeviceAddr;
	Ed->ed_info.b.ep_num = 0;
	Ed->ed_info.b.direction = 0;
	Ed->ed_info.b.speed = IsLow?1:0;	// speed
	Ed->ed_info.b.format = 0;	// gTD
	Ed->ed_info.b.mps = MaxPacket;
	Ed->tail_td_ptr = 0;
	Ed->head_td_ptr = SetupTd;
	Ed->next_ed = 0;
	
	Ohc->LastTd = StatusTd;

  return Ed;

FREE_TD:
  if (SetupTd != NULL) {
    OhciDestoryTds (Ohc, SetupTd);
  }

  if (FirstDataTd != NULL) {
    OhciDestoryTds (Ohc, FirstDataTd);
  }

  return NULL;
}


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
  )
{
	OHCI_ED_HW							*Ed;
  OHCI_TD_HW              *DataTd;
  OHCI_TD_HW              *FirstDataTd;
  OHCI_TD_HW              *PrevDataTd;
  UINTN                   ThisTdLen;
	UINT8										EP;
#if 1
	EP = EndPoint >> 7;
	DEBUG((EFI_D_INIT, "+++OhciCreateBulkOrIntTds(EP%d : %p)\n", EP, Ohc->EdHw[EP]));

	DataTd      = NULL;
  FirstDataTd = NULL;
  PrevDataTd  = NULL;
  //
  // Create data packets for the transfer
  //
  while (DataLen > 0) {
    //
    // PktSize is the data load size that each Td.
    //
    ThisTdLen = DataLen;

    if (DataLen > MaxPacket) {
      ThisTdLen = MaxPacket;
    }

    DataTd = OhciCreateDataTd (
               Ohc,
               DevAddr,
               EndPoint,
               Data,
               DataPhy,
               ThisTdLen,
               PktId,
               (*DataToggle + 2),
               IsLow
               );

    if (DataTd == NULL) {
			DEBUG((EFI_D_ERROR, "FAIL! OhciCreateDataTd\n"));
      goto FREE_TD;
    }
/*
    if (PktId == INPUT_PACKET_ID) {
      DataTd->gtd_info.b.buffer_rounding = 1;
    }
*/
    if (FirstDataTd == NULL) {
      FirstDataTd          = DataTd;
      FirstDataTd->next_td = NULL;
    } else {
      OhciAppendTd (Ohc, PrevDataTd, DataTd);
    }

    *DataToggle ^= 1;
    PrevDataTd   = DataTd;
    Data        += ThisTdLen;
    DataPhy     += ThisTdLen;
    DataLen     -= ThisTdLen;
  }

	Ed = Ohc->EdHw[EP];
	Ed->ed_info.data = 0;
	Ed->ed_info.b.func_addr = DevAddr;
	Ed->ed_info.b.ep_num = EP;
	Ed->ed_info.b.direction = 0; //IN DIRECTION
	Ed->ed_info.b.speed = IsLow?1:0;	// speed
	Ed->ed_info.b.format = 0;	// gTD
	Ed->ed_info.b.mps = MaxPacket;
	Ed->tail_td_ptr = 0;
	Ed->head_td_ptr = FirstDataTd;
	Ed->next_ed = 0;

	Ohc->LastTd = PrevDataTd;

	DEBUG((EFI_D_INIT, "---OhciCreateBulkOrIntTds()\n"));

  return Ed;

FREE_TD:
  if (FirstDataTd != NULL) {
    OhciDestoryTds (Ohc, FirstDataTd);
  }

	return NULL;
#else
  DataTd      = NULL;
  FirstDataTd = NULL;
  PrevDataTd  = NULL;

  //
  // Create data packets for the transfer
  //
  while (DataLen > 0) {
    //
    // PktSize is the data load size that each Td.
    //
    ThisTdLen = DataLen;

    if (DataLen > MaxPacket) {
      ThisTdLen = MaxPacket;
    }

    DataTd = OhciCreateDataTd (
               Ohc,
               DevAddr,
               EndPoint,
               Data,
               DataPhy,
               ThisTdLen,
               PktId,
               *DataToggle,
               IsLow
               );

    if (DataTd == NULL) {
      goto FREE_TD;
    }

    if (PktId == INPUT_PACKET_ID) {
      DataTd->TdHw.ShortPacket = TRUE;
    }

    if (FirstDataTd == NULL) {
      FirstDataTd         = DataTd;
      FirstDataTd->NextTd = NULL;
    } else {
      OhciAppendTd (Ohc, PrevDataTd, DataTd);
    }

    *DataToggle ^= 1;
    PrevDataTd   = DataTd;
    Data        += ThisTdLen;
    DataPhy     += ThisTdLen;
    DataLen     -= ThisTdLen;
  }

  return FirstDataTd;

FREE_TD:
  if (FirstDataTd != NULL) {
    OhciDestoryTds (Ohc, FirstDataTd);
  }
#endif
}
