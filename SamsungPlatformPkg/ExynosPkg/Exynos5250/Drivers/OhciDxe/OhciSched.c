/** @file

  The EHCI register operation routines.

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
  Create Frame List Structure.

  @param  Ohc                    OHCI device.

  @retval EFI_OUT_OF_RESOURCES   Can't allocate memory resources.
  @retval EFI_UNSUPPORTED        Map memory fail.
  @retval EFI_SUCCESS            Success.

**/
EFI_STATUS
OhciInitFrameList (
  IN USB_HC_DEV         *Ohc
  )
{
  EFI_PHYSICAL_ADDRESS  MappedAddr;
  EFI_STATUS            Status;
  VOID                  *Buffer;
  VOID                  *Mapping;
  UINTN                 Pages;
  UINTN                 Bytes;
  UINTN                 Index;
  EFI_PHYSICAL_ADDRESS  PhyAddr;

  DEBUG((EFI_D_INIT, "+++OhciInitFrameList()\n"));

  //
  // The Frame List is a common buffer that will be
  // accessed by both the cpu and the usb bus master
  // at the same time. The Frame List ocupies 4K bytes,
  // and must be aligned on 4-Kbyte boundaries.
  //
  Bytes = 4096;
  Pages = EFI_SIZE_TO_PAGES (Bytes);

  Status = Ohc->PciIo->AllocateBuffer (
                         Ohc->PciIo,
                         AllocateAnyPages,
                         EfiBootServicesData,
                         Pages,
                         &Buffer,
                         0
                         );

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "FAIL! AllocateBuffer\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = Ohc->PciIo->Map (
                         Ohc->PciIo,
                         EfiPciIoOperationBusMasterCommonBuffer,
                         Buffer,
                         &Bytes,
                         &MappedAddr,
                         &Mapping
                         );

#if 1
  if (EFI_ERROR (Status) || (Bytes != 4096)) {
    DEBUG((EFI_D_ERROR, "FAIL! Map\n"));
    Status = EFI_UNSUPPORTED;
    return Status;
  }

  Ohc->Hcca           = (UINT32 *) (UINTN) Buffer;
  Ohc->HccaMapping    = Mapping;

  OhciWriteReg(Ohc, HC_HCCA_OFFSET, (UINT32)Buffer);

  return EFI_SUCCESS;

#else
  if (EFI_ERROR (Status) || (Bytes != 4096)) {
    DEBUG((EFI_D_ERROR, "FAIL! Map\n"));
    Status = EFI_UNSUPPORTED;
    goto ON_ERROR;
  }


  Ohc->FrameBase           = (UINT32 *) (UINTN) Buffer;
  Ohc->FrameMapping        = Mapping;

  //
  // Tell the Host Controller where the Frame List lies,
  // by set the Frame List Base Address Register.
  //
  //OhciSetFrameListBaseAddr (Ohc->PciIo, (VOID *) (UINTN) MappedAddr);

  //
  // Allocate the QH used by sync interrupt/control/bulk transfer.
  // FS ctrl/bulk queue head is set to loopback so additional BW
  // can be reclaimed. Notice, LS don't support bulk transfer and
  // also doesn't support BW reclamation.
  //
  Ohc->SyncIntQh  = OhciCreateQh (Ohc, 1);
  Ohc->CtrlQh     = OhciCreateQh (Ohc, 1);
  Ohc->BulkQh     = OhciCreateQh (Ohc, 1);

  if ((Ohc->SyncIntQh == NULL) || (Ohc->CtrlQh == NULL) || (Ohc->BulkQh == NULL)) {
    Ohc->PciIo->Unmap (Ohc->PciIo, Mapping);
    DEBUG((EFI_D_ERROR, "FAIL! NULL1\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_ERROR;
  }

  //
  //                                                +-------------+
  //                                                |             |
  // Link the three together: SyncIntQh->CtrlQh->BulkQh <---------+
  // Each frame entry is linked to this sequence of QH. These QH
  // will remain on the schedul, never got removed
  //
  PhyAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, Ohc->CtrlQh, sizeof (OHCI_QH_HW));
  Ohc->SyncIntQh->QhHw.HorizonLink  = QH_HLINK (PhyAddr, FALSE);
  Ohc->SyncIntQh->NextQh            = Ohc->CtrlQh;

  PhyAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, Ohc->BulkQh, sizeof (OHCI_QH_HW));
  Ohc->CtrlQh->QhHw.HorizonLink     = QH_HLINK (PhyAddr, FALSE);
  Ohc->CtrlQh->NextQh               = Ohc->BulkQh;

  //
  // Some old platform such as Intel's Tiger 4 has a difficult time
  // in supporting the full speed bandwidth reclamation in the previous
  // mentioned form. Most new platforms don't suffer it.
  //
  Ohc->BulkQh->QhHw.HorizonLink     = QH_HLINK (PhyAddr, FALSE);

  Ohc->BulkQh->NextQh               = NULL;

  Ohc->FrameBaseHostAddr = AllocateZeroPool (4096);
  if (Ohc->FrameBaseHostAddr == NULL) {
    DEBUG((EFI_D_ERROR, "FAIL! NULL2\n"));
    Status = EFI_OUT_OF_RESOURCES;
    goto ON_ERROR;
  }

  PhyAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, Ohc->SyncIntQh, sizeof (OHCI_QH_HW));
  for (Index = 0; Index < OHCI_FRAME_NUM; Index++) {
    Ohc->FrameBase[Index] = QH_HLINK (PhyAddr, FALSE);
    Ohc->FrameBaseHostAddr[Index] = (UINT32)(UINTN)Ohc->SyncIntQh;
  }

  DEBUG((EFI_D_INIT, "---OhciInitFrameList()\n"));

  return EFI_SUCCESS;

ON_ERROR:
  if (Ohc->SyncIntQh != NULL) {
    UsbHcFreeMem (Ohc->MemPool, Ohc->SyncIntQh, sizeof (OHCI_QH_SW));
  }

  if (Ohc->CtrlQh != NULL) {
    UsbHcFreeMem (Ohc->MemPool, Ohc->CtrlQh, sizeof (OHCI_QH_SW));
  }

  if (Ohc->BulkQh != NULL) {
    UsbHcFreeMem (Ohc->MemPool, Ohc->BulkQh, sizeof (OHCI_QH_SW));
  }

  Ohc->PciIo->FreeBuffer (Ohc->PciIo, Pages, Buffer);
  return Status;
#endif
}


/**
  Destory FrameList buffer.

  @param  Ohc                    The OHCI device.

**/
VOID
OhciDestoryFrameList (
  IN USB_HC_DEV           *Ohc
  )
{
  //
  // Unmap the common buffer for framelist entry,
  // and free the common buffer.
  // Ohci's frame list occupy 4k memory.
  //
  DEBUG((EFI_D_INIT, "+++OhciDestoryFrameList()\n"));

#if 1
#else
  Ohc->PciIo->Unmap (Ohc->PciIo, Ohc->FrameMapping);

  Ohc->PciIo->FreeBuffer (
                Ohc->PciIo,
                EFI_SIZE_TO_PAGES (4096),
                (VOID *) Ohc->FrameBase
                );

  if (Ohc->FrameBaseHostAddr != NULL) {
    FreePool (Ohc->FrameBaseHostAddr);
  }

  if (Ohc->SyncIntQh != NULL) {
    UsbHcFreeMem (Ohc->MemPool, Ohc->SyncIntQh, sizeof (OHCI_QH_SW));
  }

  if (Ohc->CtrlQh != NULL) {
    UsbHcFreeMem (Ohc->MemPool, Ohc->CtrlQh, sizeof (OHCI_QH_SW));
  }

  if (Ohc->BulkQh != NULL) {
    UsbHcFreeMem (Ohc->MemPool, Ohc->BulkQh, sizeof (OHCI_QH_SW));
  }

  Ohc->FrameBase           = NULL;
  Ohc->FrameBaseHostAddr   = NULL;
  Ohc->SyncIntQh           = NULL;
  Ohc->CtrlQh              = NULL;
  Ohc->BulkQh              = NULL;
#endif
	DEBUG((EFI_D_INIT, "---OhciDestoryFrameList()\n"));
}


/**
  Convert the poll rate to the maxium 2^n that is smaller
  than Interval.

  @param  Interval               The poll rate to convert.

  @return The converted poll rate.

**/
UINTN
OhciConvertPollRate (
  IN  UINTN               Interval
  )
{
  UINTN                   BitCount;

  ASSERT (Interval != 0);

  //
  // Find the index (1 based) of the highest non-zero bit
  //
  BitCount = 0;

  while (Interval != 0) {
    Interval >>= 1;
    BitCount++;
  }

  return (UINTN)1 << (BitCount - 1);
}


/**
  Link a queue head (for asynchronous interrupt transfer) to
  the frame list.

  @param  Ohc                    The OHCI device.
  @param  Qh                     The queue head to link into.

**/
VOID
OhciLinkQhToFrameList (
  USB_HC_DEV              *Ohc,
  OHCI_QH_SW              *Qh
  )
{
  UINTN                   Index;
  OHCI_QH_SW              *Prev;
  OHCI_QH_SW              *Next;
  EFI_PHYSICAL_ADDRESS    PhyAddr;
  EFI_PHYSICAL_ADDRESS    QhPciAddr;

#if 1
#else
  ASSERT ((Ohc->FrameBase != NULL) && (Qh != NULL));

  QhPciAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, Qh, sizeof (OHCI_QH_HW));

  for (Index = 0; Index < OHCI_FRAME_NUM; Index += Qh->Interval) {
    //
    // First QH can't be NULL because we always keep static queue
    // heads on the frame list
    //
    ASSERT (!LINK_TERMINATED (Ohc->FrameBase[Index]));
    Next  = (OHCI_QH_SW*)(UINTN)Ohc->FrameBaseHostAddr[Index];
    Prev  = NULL;

    //
    // Now, insert the queue head (Qh) into this frame:
    // 1. Find a queue head with the same poll interval, just insert
    //    Qh after this queue head, then we are done.
    //
    // 2. Find the position to insert the queue head into:
    //      Previous head's interval is bigger than Qh's
    //      Next head's interval is less than Qh's
    //    Then, insert the Qh between then
    //
    // This method is very much the same as that used by EHCI.
    // Because each QH's interval is round down to 2^n, poll
    // rate is correct.
    //
    while (Next->Interval > Qh->Interval) {
      Prev  = Next;
      Next  = Next->NextQh;
      ASSERT (Next != NULL);
    }

    //
    // The entry may have been linked into the frame by early insertation.
    // For example: if insert a Qh with Qh.Interval == 4, and there is a Qh
    // with Qh.Interval == 8 on the frame. If so, we are done with this frame.
    // It isn't necessary to compare all the QH with the same interval to
    // Qh. This is because if there is other QH with the same interval, Qh
    // should has been inserted after that at FrameBase[0] and at FrameBase[0] it is
    // impossible (Next == Qh)
    //
    if (Next == Qh) {
      continue;
    }

    if (Next->Interval == Qh->Interval) {
      //
      // If there is a QH with the same interval, it locates at
      // FrameBase[0], and we can simply insert it after this QH. We
      // are all done.
      //
      ASSERT ((Index == 0) && (Qh->NextQh == NULL));

      Prev                    = Next;
      Next                    = Next->NextQh;

      Qh->NextQh              = Next;
      Prev->NextQh            = Qh;

      Qh->QhHw.HorizonLink    = Prev->QhHw.HorizonLink;

      Prev->QhHw.HorizonLink  = QH_HLINK (QhPciAddr, FALSE);
      break;
    }

    //
    // OK, find the right position, insert it in. If Qh's next
    // link has already been set, it is in position. This is
    // guarranted by 2^n polling interval.
    //
    if (Qh->NextQh == NULL) {
      Qh->NextQh            = Next;
      PhyAddr = UsbHcGetPciAddressForHostMem (Ohc->MemPool, Next, sizeof (OHCI_QH_HW));
      Qh->QhHw.HorizonLink  = QH_HLINK (PhyAddr, FALSE);
    }

    if (Prev == NULL) {
      Ohc->FrameBase[Index]           = QH_HLINK (QhPciAddr, FALSE);
      Ohc->FrameBaseHostAddr[Index]   = (UINT32)(UINTN)Qh;
    } else {
      Prev->NextQh            = Qh;
      Prev->QhHw.HorizonLink  = QH_HLINK (QhPciAddr, FALSE);
    }
  }
#endif
}


/**
  Unlink QH from the frame list is easier: find all
  the precedence node, and pointer there next to QhSw's
  next.

  @param  Ohc                    The OHCI device.
  @param  Qh                     The queue head to unlink.

**/
VOID
OhciUnlinkQhFromFrameList (
  USB_HC_DEV              *Ohc,
  OHCI_QH_SW              *Qh
  )
{
  UINTN                   Index;
  OHCI_QH_SW              *Prev;
  OHCI_QH_SW              *This;
#if 1
#else
  ASSERT ((Ohc->FrameBase != NULL) && (Qh != NULL));

  for (Index = 0; Index < OHCI_FRAME_NUM; Index += Qh->Interval) {
    //
    // Frame link can't be NULL because we always keep static
    // queue heads on the frame list
    //
    ASSERT (!LINK_TERMINATED (Ohc->FrameBase[Index]));
    This  = (OHCI_QH_SW*)(UINTN)Ohc->FrameBaseHostAddr[Index];
    Prev  = NULL;

    //
    // Walk through the frame's QH list to find the
    // queue head to remove
    //
    while ((This != NULL) && (This != Qh)) {
      Prev  = This;
      This  = This->NextQh;
    }

    //
    // Qh may have already been unlinked from this frame
    // by early action.
    //
    if (This == NULL) {
      continue;
    }

    if (Prev == NULL) {
      //
      // Qh is the first entry in the frame
      //
      Ohc->FrameBase[Index]           = Qh->QhHw.HorizonLink;
      Ohc->FrameBaseHostAddr[Index]   = (UINT32)(UINTN)Qh->NextQh;
    } else {
      Prev->NextQh            = Qh->NextQh;
      Prev->QhHw.HorizonLink  = Qh->QhHw.HorizonLink;
    }
  }
#endif
}


/**
  Check TDs Results.

  @param  Ohc                    This OHCI device.
  @param  Td                     OHCI_TD_HW to check.
  @param  IsLow                  Is Low Speed Device.
  @param  QhResult               Return the result of this TD list.

  @return Whether the TD's result is finialized.

**/
BOOLEAN
OhciCheckTdStatus (
  IN  USB_HC_DEV          *Ohc,
  IN  OHCI_ED_HW          *Ed,
  IN  BOOLEAN             IsLow,
  OUT OHCI_QH_RESULT      *QhResult,
  IN  UINT8               Class
  )
{
  UINTN                   Len;
  UINT8                   State;
  BOOLEAN                 Finished;
  OHCI_TD_SW              *CurTdSw;
  OHCI_TD_HW              *TdHw;

  Finished             = TRUE;

  if(Class == HC_CLASS_CONTROL)
    CurTdSw = Ohc->CtrlQh;
  else // HC_CLASS_INTERRUPT
    CurTdSw = Ohc->IntrQh;

  TdHw = CurTdSw->TdHw;
  //
  // Initialize the data toggle to that of the first
  // TD. The next toggle to use is either:
  // 1. first TD's toggle if no TD is executed OK
  // 2. the next toggle of last executed-OK TD
  //
  QhResult->Result     = EFI_USB_NOERROR;
  QhResult->NextToggle = (UINT8)(TdHw->gtd_info.b.data_toggle & 1);
  QhResult->Complete   = 0;

#if 1
	if(Class == HC_CLASS_CONTROL)
	{
		while(Ohc->Hcca->done_head != Ohc->LastTd)
		{
			DEBUG((EFI_D_ERROR, ".\n"));
			OhciWriteReg(Ohc, HC_INT_STATUS_OFFSET, 0x2);
		}
	}
	else
	{
		OhciWriteReg(Ohc, HC_INT_STATUS_OFFSET, 0x2);
		if(Ohc->Hcca->done_head != Ohc->LastTd)
		{
			Finished = FALSE;
			QhResult->Complete = 0;
			return Finished;
		}
	}

	Ohc->Hcca->done_head = NULL;
	DEBUG((EFI_D_ERROR, ">\n"));

  while (TdHw != NULL) {
    if(TdHw->current_buf_ptr == NULL)
    {
			if(TdHw->gtd_info.b.error_count != 0)
			{
				QhResult->Result |= EFI_USB_ERR_NOTEXECUTE;
				DEBUG((EFI_D_ERROR, "FAIL! EXECUTE ERROR1\n"));
				Finished = TRUE;
				OhciDumpSWTds(Ohc->CtrlQh);
				OhcDumpRegs(Ohc);
				goto ON_EXIT;
			}

			if(TdHw->gtd_info.b.condition_code != 0)
			{
				switch(TdHw->gtd_info.b.condition_code)
				{
					case 4: //stall
						QhResult->Result |= EFI_USB_ERR_STALL;
						DEBUG((EFI_D_ERROR, "FAIL! EFI_USB_ERR_STALL\n"));
						break;
					default :
						QhResult->Result |= EFI_USB_ERR_NOTEXECUTE;
						DEBUG((EFI_D_ERROR, "FAIL! EXECUTE ERROR2\n"));
						break;
				}

				Finished = TRUE;
				OhciDumpSWTds(Ohc->CtrlQh);
				OhcDumpRegs(Ohc);
				goto ON_EXIT;
			}

			QhResult->NextToggle = (TdHw->gtd_info.b.data_toggle & 1) ? 0 : 1;
			//
	    // This TD is finished OK or met short packet read. Update the
	    // transfer length if it isn't a SETUP.
	    //

	    if (TdHw->gtd_info.b.pid != SETUP_PACKET_ID) {
	      QhResult->Complete += CurTdSw->DataLen;
	    }

	    //
	    // Short packet condition for full speed input TD, also
	    // terminate the transfer
	    //
	    /*
	    if (!IsLow && (TdHw->ShortPacket == 1) && (Len < Td->DataLen)) {
	      DEBUG ((EFI_D_INFO, "OhciCheckTdStatus: short packet read occured\n"));

	      Finished = TRUE;
	      goto ON_EXIT;
	    }*/
		} // if(TdHw->current_buf_ptr == NULL)
		/*else
		{
			QhResult->Result |= EFI_USB_ERR_NOTEXECUTE;
			DEBUG((EFI_D_ERROR, "FAIL! EXECUTE ERROR3\n"));
			Finished = TRUE;
			goto ON_EXIT;
		}*/
    CurTdSw = CurTdSw->NextTd;
		TdHw = CurTdSw->TdHw;
  }

	if(!Finished)
	{
		OhciDumpSWTds(Ohc->CtrlQh);
		OhcDumpRegs(Ohc);
	}
#else
  while (Td != NULL) {
    TdHw  = &Td->TdHw;
    State = (UINT8)TdHw->Status;

    //
    // OHCI will set STALLED bit when it abort the execution
    // of TD list. There are several reasons:
    //   1. BABBLE error happened
    //   2. Received a STALL response
    //   3. Error count decreased to zero.
    //
    // It also set CRC/Timeout/NAK/Buffer Error/BitStuff Error
    // bits when corresponding conditions happen. But these
    // conditions are not deadly, that is a TD can successfully
    // completes even these bits are set. But it is likely that
    // upper layer won't distinguish these condtions. So, only
    // set these bits when TD is actually halted.
    //
    if ((State & USBTD_STALLED) != 0) {
      if ((State & USBTD_BABBLE) != 0) {
        QhResult->Result |= EFI_USB_ERR_BABBLE;

      } else if (TdHw->ErrorCount != 0) {
        QhResult->Result |= EFI_USB_ERR_STALL;
      }

      if ((State & USBTD_CRC) != 0) {
        QhResult->Result |= EFI_USB_ERR_CRC;
      }

      if ((State & USBTD_BUFFERR) != 0) {
        QhResult->Result |= EFI_USB_ERR_BUFFER;
      }

      if ((Td->TdHw.Status & USBTD_BITSTUFF) != 0) {
        QhResult->Result |= EFI_USB_ERR_BITSTUFF;
      }

      if (TdHw->ErrorCount == 0) {
        QhResult->Result |= EFI_USB_ERR_TIMEOUT;
      }

      Finished = TRUE;
      goto ON_EXIT;

    } else if ((State & USBTD_ACTIVE) != 0) {
      //
      // The TD is still active, no need to check further.
      //
      QhResult->Result |= EFI_USB_ERR_NOTEXECUTE;

      Finished = FALSE;
      goto ON_EXIT;

    } else {
      //
      // Update the next data toggle, it is always the
      // next to the last known-good TD's data toggle if
      // any TD is executed OK
      //
      QhResult->NextToggle = (UINT8) (1 - (UINT8)TdHw->DataToggle);

      //
      // This TD is finished OK or met short packet read. Update the
      // transfer length if it isn't a SETUP.
      //
      Len = (TdHw->ActualLen + 1) & 0x7FF;

      if (TdHw->PidCode != SETUP_PACKET_ID) {
        QhResult->Complete += Len;
      }

      //
      // Short packet condition for full speed input TD, also
      // terminate the transfer
      //
      if (!IsLow && (TdHw->ShortPacket == 1) && (Len < Td->DataLen)) {
        DEBUG ((EFI_D_INFO, "OhciCheckTdStatus: short packet read occured\n"));

        Finished = TRUE;
        goto ON_EXIT;
      }
    }

    Td = Td->NextTd;
  }
#endif

ON_EXIT:
  //
  // Check whether HC is halted. Don't move this up. It must be
  // called after data toggle is successfully updated.
  //
  if (!OhciIsHcWorking (Ohc->PciIo)) {
    QhResult->Result |= EFI_USB_ERR_SYSTEM;
    Finished  = TRUE;
  }

  if (Finished) {
    Ohc->PciIo->Flush (Ohc->PciIo);
  }

  OhciAckAllInterrupt (Ohc);
  return Finished;
}


/**
  Check the result of the transfer.

  @param  Ohc                    The OHCI device.
  @param  Qh                     The queue head of the transfer.
  @param  Td                     The first TDs of the transfer.
  @param  TimeOut                TimeOut value in milliseconds.
  @param  IsLow                  Is Low Speed Device.
  @param  QhResult               The variable to return result.

  @retval EFI_SUCCESS            The transfer finished with success.
  @retval EFI_DEVICE_ERROR       Transfer failed.

**/
EFI_STATUS
OhciExecuteTransfer (
  IN  USB_HC_DEV          *Ohc,
  IN  OHCI_ED_HW          *Ed,
  IN  UINTN               TimeOut,
  IN  BOOLEAN             IsLow,
  OUT OHCI_QH_RESULT      *QhResult
  )
{
  UINTN                   Index;
  UINTN                   Delay;
  BOOLEAN                 Finished;
  EFI_STATUS              Status;

  DEBUG((EFI_D_INIT, "+++OhciExecuteTransfer()\n"));

  Finished = FALSE;
  Status   = EFI_SUCCESS;
  Delay    = (TimeOut * OHC_1_MILLISECOND / OHC_SYNC_POLL_INTERVAL) + 1;

  for (Index = 0; Index < Delay; Index++) {
    Finished = OhciCheckTdStatus (Ohc, Ed, IsLow, QhResult, HC_CLASS_CONTROL);

    //
    // Transfer is OK or some error occured (TD inactive)
    //
    if (Finished) {
      DEBUG((EFI_D_INIT, "SUCCESS! OhciExecuteTransfer\n"));
      break;
    }

    gBS->Stall (OHC_SYNC_POLL_INTERVAL);
  }

  if (!Finished) {
    DEBUG ((EFI_D_ERROR, "OhciExecuteTransfer: execution not finished for %dms\n", (UINT32)TimeOut));
    //OhciDumpQh (Qh);
    //OhciDumpTds (Td);

    Status = EFI_TIMEOUT;

  } else if (QhResult->Result != EFI_USB_NOERROR) {
    DEBUG ((EFI_D_ERROR, "OhciExecuteTransfer: execution failed with result %x\n", QhResult->Result));
    //OhciDumpQh (Qh);
    //OhciDumpTds (Td);

    Status = EFI_DEVICE_ERROR;
  }

	DEBUG((EFI_D_INIT, "---OhciExecuteTransfer()\n"));

  return Status;
}


/**
  Update Async Request, QH and TDs.

  @param  Ohc                    The OHCI device.
  @param  AsyncReq               The OHCI asynchronous transfer to update.
  @param  Result                 Transfer reslut.
  @param  NextToggle             The toggle of next data.

**/
VOID
OhciUpdateAsyncReq (
  IN USB_HC_DEV          *Ohc,
  IN OHCI_ASYNC_REQUEST  *AsyncReq,
  IN UINT32              Result,
  IN UINT32              NextToggle
  )
{
  OHCI_ED_HW              *EdHw;
  OHCI_TD_SW              *FirstTd;
  OHCI_TD_SW              *Td;
	OHCI_TD_HW              *TdHw;

	UINT8 *DataPtr, *DataPhy;

	//DEBUG((EFI_D_INIT, "+++OhciUpdateAsyncReq()\n"));

  EdHw        = AsyncReq->EdHw;
  FirstTd     = AsyncReq->TdSw;

  if (Result == EFI_USB_NOERROR) {
    //
    // The last transfer succeeds. Then we need to update
    // the Qh and Td for next round of transfer.
    // 1. Update the TD's data toggle
    // 2. Activate all the TDs
    // 3. Link the TD to the queue head again since during
    //    execution, queue head's TD pointer is changed by
    //    hardware.
    //

    for (Td = FirstTd; Td != NULL; Td = Td->NextTd) {
			TdHw = Td->TdHw;
			if(TdHw != NULL)
			{
			  //
			  // Allocate and map source data buffer for bus master access.
			  //
			  DataPtr = UsbHcAllocateMem (Ohc->MemPool, Td->DataLen);

			  if (DataPtr == NULL) {
					DEBUG((EFI_D_ERROR, "FAIL! UsbHcAllocateMem\n"));
			    return;
			  }

			  DataPhy = (UINT8 *) (UINTN) UsbHcGetPciAddressForHostMem (Ohc->MemPool, DataPtr, Td->DataLen);

				Ohc->Destory = Td->Data;
				Ohc->DestroySize = Td->DataLen;
				TdHw->current_buf_ptr = DataPhy;
				TdHw->buffer_end = DataPhy + Td->DataLen - 1;
      	TdHw->gtd_info.b.data_toggle = NextToggle + 2;

				if(Td->NextTd)
				{
					TdHw->next_td = Td->NextTd->TdHw;
				}

	      NextToggle = NextToggle ? 0 : 1;
			}
    }

		EdHw->head_td_ptr = FirstTd->TdHw;

		//OhciDumpEd(EdHw);

    OhciLinkTdToQh (Ohc, EdHw, HC_CLASS_INTERRUPT);

		//DEBUG((EFI_D_INIT, "---OhciUpdateAsyncReq()\n"));

    return ;
  }
}


/**
  Create Async Request node, and Link to List.

  @param  Ohc                    The OHCI device.
  @param  Qh                     The queue head of the transfer.
  @param  FirstTd                First TD of the transfer.
  @param  DevAddr                Device Address.
  @param  EndPoint               EndPoint Address.
  @param  DataLen                Data length.
  @param  Interval               Polling Interval when inserted to frame list.
  @param  Data                   Data buffer, unmapped.
  @param  Callback               Callback after interrupt transfeer.
  @param  Context                Callback Context passed as function parameter.
  @param  IsLow                  Is Low Speed.

  @retval EFI_SUCCESS            An asynchronous transfer is created.
  @retval EFI_INVALID_PARAMETER  Paremeter is error.
  @retval EFI_OUT_OF_RESOURCES   Failed because of resource shortage.

**/
EFI_STATUS
OhciCreateAsyncReq (
  IN USB_HC_DEV                       *Ohc,
  IN OHCI_ED_HW                       *EdHw,
  IN OHCI_TD_SW                       *TdSw,
  IN UINT8                            DevAddr,
  IN UINT8                            EndPoint,
  IN UINTN                            DataLen,
  IN UINTN                            Interval,
  IN UINT8                            *Data,
  IN EFI_ASYNC_USB_TRANSFER_CALLBACK  Callback,
  IN VOID                             *Context,
  IN BOOLEAN                          IsLow
  )
{
  OHCI_ASYNC_REQUEST      *AsyncReq;

	DEBUG((EFI_D_INIT, "+++OhciCreateAsyncReq()\n"));

  AsyncReq = AllocatePool (sizeof (OHCI_ASYNC_REQUEST));

  if (AsyncReq == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Fill Request field. Data is allocated host memory, not mapped
  //
  AsyncReq->Signature   = OHCI_ASYNC_INT_SIGNATURE;
  AsyncReq->DevAddr     = DevAddr;
  AsyncReq->EndPoint    = EndPoint;
  AsyncReq->DataLen     = DataLen;
  AsyncReq->Interval    = OhciConvertPollRate(Interval);
  AsyncReq->Data        = Data;
  AsyncReq->Callback    = Callback;
  AsyncReq->Context     = Context;
  AsyncReq->EdHw        = EdHw;
  AsyncReq->TdSw				= TdSw;
  AsyncReq->IsLow       = IsLow;

  //
  // Insert the new interrupt transfer to the head of the list.
  // The interrupt transfer's monitor function scans the whole
  // list from head to tail. The new interrupt transfer MUST be
  // added to the head of the list.
  //
  InsertHeadList (&(Ohc->AsyncIntList), &(AsyncReq->Link));

	DEBUG((EFI_D_INIT, "---OhciCreateAsyncReq()\n"));

  return EFI_SUCCESS;
}


/**
  Free an asynchronous request's resource such as memory.

  @param  Ohc                    The OHCI device.
  @param  AsyncReq               The asynchronous request to free.

**/
VOID
OhciFreeAsyncReq (
  IN USB_HC_DEV           *Ohc,
  IN OHCI_ASYNC_REQUEST   *AsyncReq
  )
{
  ASSERT ((Ohc != NULL) && (AsyncReq != NULL));

	DEBUG((EFI_D_ERROR, "+++OhciFreeAsyncReq()\n"));

  OhciDestoryTds (Ohc, AsyncReq->TdSw);

  if (AsyncReq->Data != NULL) {
    UsbHcFreeMem (Ohc->MemPool, AsyncReq->Data, AsyncReq->DataLen);
  }

  gBS->FreePool (AsyncReq);

	DEBUG((EFI_D_ERROR, "+++OhciFreeAsyncReq()\n"));
}


/**
  Unlink an asynchronous request's from OHC's asynchronus list.
  also remove the queue head from the frame list. If FreeNow,
  release its resource also. Otherwise, add the request to the
  OHC's recycle list to wait for a while before release the memory.
  Until then, hardware won't hold point to the request.

  @param  Ohc                    The OHCI device.
  @param  AsyncReq               The asynchronous request to free.
  @param  FreeNow                If TRUE, free the resource immediately, otherwise
                                 add the request to recycle wait list.

**/
VOID
OhciUnlinkAsyncReq (
  IN USB_HC_DEV           *Ohc,
  IN OHCI_ASYNC_REQUEST   *AsyncReq,
  IN BOOLEAN              FreeNow
  )
{
  ASSERT ((Ohc != NULL) && (AsyncReq != NULL));

	DEBUG((EFI_D_INIT, "+++OhciUnlinkAsyncReq()\n"));
#if 1
#else
  RemoveEntryList (&(AsyncReq->Link));
  OhciUnlinkQhFromFrameList (Ohc, AsyncReq->QhSw);

  if (FreeNow) {
    OhciFreeAsyncReq (Ohc, AsyncReq);
  } else {
    //
    // To sychronize with hardware, mark the queue head as inactive
    // then add AsyncReq to OHC's recycle list
    //
    AsyncReq->QhSw->QhHw.VerticalLink = QH_VLINK (NULL, TRUE);
    AsyncReq->Recycle = Ohc->RecycleWait;
    Ohc->RecycleWait  = AsyncReq;
  }
#endif
	DEBUG((EFI_D_INIT, "---OhciUnlinkAsyncReq()\n"));
}


/**
  Delete Async Interrupt QH and TDs.

  @param  Ohc                    The OHCI device.
  @param  DevAddr                Device Address.
  @param  EndPoint               EndPoint Address.
  @param  Toggle                 The next data toggle to use.

  @retval EFI_SUCCESS            The request is deleted.
  @retval EFI_INVALID_PARAMETER  Paremeter is error.
  @retval EFI_NOT_FOUND          The asynchronous isn't found.

**/
EFI_STATUS
OhciRemoveAsyncReq (
  IN  USB_HC_DEV          *Ohc,
  IN  UINT8               DevAddr,
  IN  UINT8               EndPoint,
  OUT UINT8               *Toggle
  )
{
  EFI_STATUS          Status;
  OHCI_ASYNC_REQUEST  *AsyncReq;
  OHCI_QH_RESULT      QhResult;
  LIST_ENTRY          *Link;
  BOOLEAN             Found;

  Status = EFI_SUCCESS;

  //
  // If no asynchronous interrupt transaction exists
  //
  if (IsListEmpty (&(Ohc->AsyncIntList))) {
    return EFI_SUCCESS;
  }

  //
  // Find the asynchronous transfer to this device/endpoint pair
  //
  Found = FALSE;
  Link  = Ohc->AsyncIntList.ForwardLink;

  do {
    AsyncReq  = OHCI_ASYNC_INT_FROM_LINK (Link);
    Link      = Link->ForwardLink;

    if ((AsyncReq->DevAddr == DevAddr) && (AsyncReq->EndPoint == EndPoint)) {
      Found = TRUE;
      break;
    }

  } while (Link != &(Ohc->AsyncIntList));

  if (!Found) {
    return EFI_NOT_FOUND;
  }

  //
  // Check the result of the async transfer then update it
  // to get the next data toggle to use.
  //
  OhciCheckTdStatus (Ohc, AsyncReq->EdHw, AsyncReq->IsLow, &QhResult, HC_CLASS_INTERRUPT);
  *Toggle = QhResult.NextToggle;

  //
  // Don't release the request now, keep it to synchronize with hardware.
  //
  OhciUnlinkAsyncReq (Ohc, AsyncReq, FALSE);
  return Status;
}


/**
  Recycle the asynchronouse request. When a queue head
  is unlinked from frame list, host controller hardware
  may still hold a cached pointer to it. To synchronize
  with hardware, the request is released in two steps:
  first it is linked to the OHC's RecycleWait list. At
  the next time OhciMonitorAsyncReqList is fired, it is
  moved to OHC's Recylelist. Then, at another timer
  activation, all the requests on Recycle list is freed.
  This guarrantes that each unlink queue head keeps
  existing for at least 50ms, far enough for the hardware
  to clear its cache.

  @param  Ohc                    The OHCI device.

**/
VOID
OhciRecycleAsyncReq (
  IN USB_HC_DEV           *Ohc
  )
{
  OHCI_ASYNC_REQUEST      *Req;
  OHCI_ASYNC_REQUEST      *Next;

  Req = Ohc->Recycle;

  while (Req != NULL) {
    Next = Req->Recycle;
    OhciFreeAsyncReq (Ohc, Req);
    Req  = Next;
  }

  Ohc->Recycle     = Ohc->RecycleWait;
  Ohc->RecycleWait = NULL;
}



/**
  Release all the asynchronous transfers on the lsit.

  @param  Ohc                    The OHCI device.

**/
VOID
OhciFreeAllAsyncReq (
  IN USB_HC_DEV           *Ohc
  )
{
  LIST_ENTRY              *Head;
  OHCI_ASYNC_REQUEST      *AsyncReq;

	DEBUG((EFI_D_INIT, "+++OhciFreeAllAsyncReq()\n"));

  //
  // Call OhciRecycleAsyncReq twice. The requests on Recycle
  // will be released at the first call; The requests on
  // RecycleWait will be released at the second call.
  //
  OhciRecycleAsyncReq (Ohc);
  OhciRecycleAsyncReq (Ohc);

  Head = &(Ohc->AsyncIntList);

  if (IsListEmpty (Head)) {
    return;
  }

  while (!IsListEmpty (Head)) {
    AsyncReq  = OHCI_ASYNC_INT_FROM_LINK (Head->ForwardLink);
    OhciUnlinkAsyncReq (Ohc, AsyncReq, TRUE);
  }

	DEBUG((EFI_D_INIT, "---OhciFreeAllAsyncReq()\n"));
}


/**
  Interrupt transfer periodic check handler.

  @param  Event                  The event of the time.
  @param  Context                Context of the event, pointer to USB_HC_DEV.

**/
VOID
EFIAPI
OhciMonitorAsyncReqList (
  IN EFI_EVENT            Event,
  IN VOID                 *Context
  )
{
  OHCI_ASYNC_REQUEST      *AsyncReq;
  LIST_ENTRY              *Link;
  USB_HC_DEV              *Ohc;
  VOID                    *Data;
  BOOLEAN                 Finished;
  OHCI_QH_RESULT          QhResult;
	UINT32									Inputs;

	DEBUG((EFI_D_INFO, "++%a : %d\n", __FUNCTION__, __LINE__));

  Ohc = (USB_HC_DEV *) Context;

  //
  // Recycle the asynchronous requests expired, and promote
  // requests waiting to be recycled the next time when this
  // timer expires
  //

	if(Ohc->Destory)
	{
	  DEBUG((EFI_D_ERROR, "%a (Destoryed) : %d\n", __FUNCTION__, __LINE__));
		UsbHcFreeMem (Ohc->MemPool, Ohc->Destory, Ohc->DestroySize);
		Ohc->Destory = NULL;
		Ohc->DestroySize = 0;
	}
	//OhciRecycleAsyncReq (Ohc);

  if (IsListEmpty (&(Ohc->AsyncIntList))) {
	  DEBUG((EFI_D_ERROR, "%a (IsListEmpty) : %d\n", __FUNCTION__, __LINE__));
    return ;
  }

  //
  // This loop must be delete safe
  //
  Link = Ohc->AsyncIntList.ForwardLink;

  do {
    AsyncReq  = OHCI_ASYNC_INT_FROM_LINK (Link);
    Link      = Link->ForwardLink;

    Finished = OhciCheckTdStatus (Ohc, AsyncReq->EdHw, AsyncReq->IsLow, &QhResult, HC_CLASS_INTERRUPT);

    if (!Finished) {
      continue;
    }

    //
    // Copy the data to temporary buffer if there are some
    // data transferred. We may have zero-length packet
    //
    Data = NULL;

    if (QhResult.Complete != 0) {
      Data = AllocatePool (QhResult.Complete);

      if (Data == NULL) {
        return ;
      }

      CopyMem (Data, AsyncReq->TdSw->Data, QhResult.Complete);

      Inputs = QhResult.Complete;
      DEBUG((EFI_D_INIT, "INPUT : "));
      while(Inputs--)
      {
        DEBUG((EFI_D_INIT, "0x%02X ", ((UINT8*)Data)[QhResult.Complete - Inputs -1]));
      }
      DEBUG((EFI_D_INIT, "\n"));
    }

    OhciUpdateAsyncReq (Ohc, AsyncReq, QhResult.Result, QhResult.NextToggle);

    //
    // Now, either transfer is SUCCESS or met errors since
    // we have skipped to next transfer earlier if current
    // transfer is still active.
    //
    if (QhResult.Result == EFI_USB_NOERROR) {
      AsyncReq->Callback (Data, QhResult.Complete, AsyncReq->Context, QhResult.Result);
    } else {
      //
      // Leave error recovery to its related device driver.
      // A common case of the error recovery is to re-submit
      // the interrupt transfer. When an interrupt transfer
      // is re-submitted, its position in the linked list is
      // changed. It is inserted to the head of the linked
      // list, while this function scans the whole list from
      // head to tail. Thus, the re-submitted interrupt transfer's
      // callback function will not be called again in this round.
      //
      AsyncReq->Callback (NULL, 0, AsyncReq->Context, QhResult.Result);
    }

    if (Data != NULL) {
      gBS->FreePool (Data);
    }
  } while (Link != &(Ohc->AsyncIntList));

	DEBUG((EFI_D_INFO, "--%a : %d\n", __FUNCTION__, __LINE__));
}
