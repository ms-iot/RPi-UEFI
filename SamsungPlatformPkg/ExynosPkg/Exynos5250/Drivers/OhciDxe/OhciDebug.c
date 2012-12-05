/** @file

  This file provides the information dump support for Ohci when in debug mode.

Copyright (c) 2007, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "Ohci.h"


#ifdef EFI_D_INIT
#undef EFI_D_INIT
#define EFI_D_INIT EFI_D_INFO
#endif

/**
  Dump the content of QH structure.

  @param  QhSw    Pointer to software QH structure.

**/
#if 0
VOID
OhciDumpQh (
  IN OHCI_QH_SW    *QhSw
  )
{
  DEBUG ((EFI_D_INFO, "&QhSw @ 0x%p\n", QhSw));
  DEBUG ((EFI_D_INFO, "QhSw.NextQh    - 0x%p\n", QhSw->NextQh));
  DEBUG ((EFI_D_INFO, "QhSw.TDs       - 0x%p\n", QhSw->TDs));
  DEBUG ((EFI_D_INFO, "QhSw.QhHw:\n"));
  DEBUG ((EFI_D_INFO, " Horizon  Link - %x\n", QhSw->QhHw.HorizonLink));
  DEBUG ((EFI_D_INFO, " Vertical Link - %x\n\n", QhSw->QhHw.VerticalLink));
}
#endif

/**
  Dump the content of TD structure.

  @param  TdSw    Pointer to software TD structure.

**/
VOID
OhciDumpTdHw (
  IN OHCI_TD_HW           *TdSw
  )
{
  OHCI_TD_HW              *CurTdSw;

	DEBUG ((EFI_D_INIT, "\n+++OhciDumpTds()\n"));

  CurTdSw = TdSw;

  while (CurTdSw != NULL) {
    DEBUG ((EFI_D_INIT, "			TdHw @ 0x%p\n",           CurTdSw));
    DEBUG ((EFI_D_INIT, "TdHw.NextTd   - 0x%p\n",  CurTdSw->next_td));
    DEBUG ((EFI_D_INIT, "TdHw.StartPtr - 0x%p\n",  CurTdSw->current_buf_ptr));
    DEBUG ((EFI_D_INIT, "TdHw.EndPtr   - 0x%p\n",  CurTdSw->buffer_end));
    DEBUG ((EFI_D_INIT, "gtd_info:\n"));
    DEBUG ((EFI_D_INIT, " buffer_rounding - 0x%x\n",  CurTdSw->gtd_info.b.buffer_rounding));
    DEBUG ((EFI_D_INIT, " pid             - 0x%x\n",  CurTdSw->gtd_info.b.pid));
    DEBUG ((EFI_D_INIT, " error_count     - 0x%x\n",  CurTdSw->gtd_info.b.error_count));
    DEBUG ((EFI_D_INIT, " condition_code  - 0x%x\n",  CurTdSw->gtd_info.b.condition_code));
		DEBUG ((EFI_D_INIT, " data_toggle     - 0x%x\n",  CurTdSw->gtd_info.b.data_toggle));

    CurTdSw = CurTdSw->next_td;
  }

	DEBUG ((EFI_D_INIT, "---OhciDumpTds()\n"));
}

VOID
OhciDumpEd (
  IN OHCI_ED_HW           *EdHw
  )
{
	DEBUG ((EFI_D_INIT, "\n+++OhciDumpEd()\n"));

  DEBUG ((EFI_D_INIT, "ed_info:\n"));
  DEBUG ((EFI_D_INIT, " func_addr - 0x%x\n",  EdHw->ed_info.b.func_addr));
  DEBUG ((EFI_D_INIT, " ep_num    - 0x%x\n",  EdHw->ed_info.b.ep_num));
  DEBUG ((EFI_D_INIT, " direction - 0x%x\n",  EdHw->ed_info.b.direction));
  DEBUG ((EFI_D_INIT, " speed     - 0x%x\n",  EdHw->ed_info.b.speed));
	DEBUG ((EFI_D_INIT, " skip      - 0x%x\n",  EdHw->ed_info.b.skip));
	DEBUG ((EFI_D_INIT, " format    - 0x%x\n",  EdHw->ed_info.b.format));
	DEBUG ((EFI_D_INIT, " mps       - 0x%x\n",  EdHw->ed_info.b.mps));

	OhciDumpTdHw(EdHw->head_td_ptr);
	
	DEBUG ((EFI_D_INIT, "---OhciDumpEd()\n\n"));
}

VOID
OhciDumpSWTds (
  IN OHCI_TD_SW           *TdSw
  )
{
  OHCI_TD_SW              *CurTdSw;
	OHCI_TD_HW              *TdHw;

	DEBUG ((EFI_D_INIT, "\n+++OhciDumpSWTds()\n"));

  CurTdSw = TdSw;
	TdHw = CurTdSw->TdHw;
	
  while (TdHw != NULL) {
    DEBUG ((EFI_D_INIT, "			TdHw @ 0x%p\n",      TdHw));
    DEBUG ((EFI_D_INIT, "TdHw.NextTd   - 0x%p\n",  TdHw->next_td));
    DEBUG ((EFI_D_INIT, "TdHw.StartPtr - 0x%p\n",  TdHw->current_buf_ptr));
    DEBUG ((EFI_D_INIT, "TdHw.EndPtr   - 0x%p\n",  TdHw->buffer_end));
		DEBUG ((EFI_D_INIT, "TdSw.DataLen  - 0x%p\n",  CurTdSw->DataLen));
    DEBUG ((EFI_D_INIT, "gtd_info:\n"));
    DEBUG ((EFI_D_INIT, " buffer_rounding - 0x%x\n",  TdHw->gtd_info.b.buffer_rounding));
    DEBUG ((EFI_D_INIT, " pid             - 0x%x\n",  TdHw->gtd_info.b.pid));
    DEBUG ((EFI_D_INIT, " error_count     - 0x%x\n",  TdHw->gtd_info.b.error_count));
    DEBUG ((EFI_D_INIT, " condition_code  - 0x%x\n",  TdHw->gtd_info.b.condition_code));
		DEBUG ((EFI_D_INIT, " data_toggle     - 0x%x\n",  TdHw->gtd_info.b.data_toggle));

    CurTdSw = CurTdSw->NextTd;
		TdHw = CurTdSw->TdHw;
  }

	DEBUG ((EFI_D_INIT, "---OhciDumpSWTds()\n\n"));
}

VOID
OhcDumpRegs (
  IN  USB_HC_DEV         *Ohc
  )
{
  UINT8   Index;
	
  DEBUG ((EFI_D_INIT, "  HC_REVISION_OFFSET         = 0x%08x\n", OhciReadReg (Ohc, HC_REVISION_OFFSET)));
  DEBUG ((EFI_D_INIT, "  HC_CONTROL_OFFSET          = 0x%08x\n", OhciReadReg (Ohc, HC_CONTROL_OFFSET)));
  DEBUG ((EFI_D_INIT, "  HC_COM_STATUS_OFFSET       = 0x%08x\n", OhciReadReg (Ohc, HC_COM_STATUS_OFFSET)));
  DEBUG ((EFI_D_INIT, "  HC_HCCA_OFFSET             = 0x%08x\n", OhciReadReg (Ohc, HC_HCCA_OFFSET)));
  DEBUG ((EFI_D_INIT, "  HC_FMINTERVAL_OFFSET       = 0x%08x\n", OhciReadReg (Ohc, HC_FMINTERVAL_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_INT_DISABLE_OFFSET      = 0x%08x\n", OhciReadReg (Ohc, HC_INT_DISABLE_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_INT_STATUS_OFFSET       = 0x%08x\n", OhciReadReg (Ohc, HC_INT_STATUS_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_CTRL_HEADED_OFFSET      = 0x%08x\n", OhciReadReg (Ohc, HC_CTRL_HEADED_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_CTRL_CURRED_OFFSET      = 0x%08x\n", OhciReadReg (Ohc, HC_CTRL_CURRED_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_BULK_HEADED_OFFSET      = 0x%08x\n", OhciReadReg (Ohc, HC_BULK_HEADED_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_BULK_CURRED_OFFSET      = 0x%08x\n", OhciReadReg (Ohc, HC_BULK_CURRED_OFFSET)));
  DEBUG ((EFI_D_INIT, "  HC_RH_STATUS_OFFSET        = 0x%08x\n", OhciReadReg (Ohc, HC_RH_STATUS_OFFSET)));
  DEBUG ((EFI_D_INIT, "  HC_RH_DESCRIPTORA_OFFSET   = 0x%08x\n", OhciReadReg (Ohc, HC_RH_DESCRIPTORA_OFFSET)));
	DEBUG ((EFI_D_INIT, "  HC_RH_DESCRIPTORB_OFFSET   = 0x%08x\n", OhciReadReg (Ohc, HC_RH_DESCRIPTORB_OFFSET)));

  for (Index = 0; Index <3; Index++) {
  DEBUG ((EFI_D_INIT, "  HC_PORT_STATUS_OFFSET(%d)  = 0x%08x\n", Index, OhciReadReg (Ohc, HC_PORT_STATUS_OFFSET + (4 * Index))));
  }
}

VOID
OhcDumpRequest (
  IN  EFI_USB_DEVICE_REQUEST              *Request
  )
{
  DEBUG ((EFI_D_INIT, "RequestType = 0x%X\n", Request->RequestType));
	DEBUG ((EFI_D_INIT, "Request     = 0x%X\n", Request->Request));
	DEBUG ((EFI_D_INIT, "Value       = 0x%X\n", Request->Value));
	DEBUG ((EFI_D_INIT, "Index       = 0x%X\n", Request->Index));
	DEBUG ((EFI_D_INIT, "Length      = 0x%X\n", Request->Length));
}

VOID
OhcDumpResult (
  IN  OHCI_QH_RESULT              *Result
  )
{
  DEBUG ((EFI_D_INIT, "Result 		= 0x%X\n", Result->Result));
	DEBUG ((EFI_D_INIT, "Complete   = 0x%X\n", Result->Complete));
	DEBUG ((EFI_D_INIT, "NextToggle = 0x%X\n", Result->NextToggle));
}