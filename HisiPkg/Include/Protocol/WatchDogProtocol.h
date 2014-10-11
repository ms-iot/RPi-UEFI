/***************************************************************
#
#  
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#  
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#  
#**/

#ifndef _WATCH_DOG_PROTOCOL_H_
#define _WATCH_GOG_PROTOCOL_H_

#define OEM_WATCH_DOG_PROTOCOL_GUID \
    {0x707ac059, 0xf335, 0x4643, 0xa6, 0x99, 0x5e, 0x3b, 0x9b, 0x82, 0x60, 0x74}
	

typedef struct _OEM_WATCH_DOG_PROTOCOL   OEM_WATCH_DOG_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI * WATCH_DOG_AUTO_CLEAR_START)(void);

typedef
EFI_STATUS
(EFIAPI * WATCH_DOG_AUTO_CLEAR_STOP)(void);

typedef
EFI_STATUS
(EFIAPI * WATCH_DOG_FEED_TIME_EXTEND)(UINT32 ulMin);

typedef
EFI_STATUS
(EFIAPI * WATCH_DOG_FEED_TIME_RESTORE)(UINT32 ulMin);
typedef
VOID
(EFIAPI * WATCH_DOG_DIAGNOSE_MODE_ENTER)(void);

typedef
VOID
(EFIAPI * WATCH_DOG_DIAGNOSE_MODE_EXIT)(void);


typedef struct _OEM_WATCH_DOG_PROTOCOL
{
    WATCH_DOG_AUTO_CLEAR_START     WtdAutoClearStart;
    WATCH_DOG_AUTO_CLEAR_STOP       WtdAutoClearStop;
    WATCH_DOG_FEED_TIME_EXTEND      WtdFeedTimeExtend;
    WATCH_DOG_FEED_TIME_RESTORE     WtdFeedTimeRestore;
    WATCH_DOG_DIAGNOSE_MODE_ENTER WtdDiagnoseModeEnter;
    WATCH_DOG_DIAGNOSE_MODE_EXIT   WtdDiagnoseModeExit;
    	
} OEM_WATCH_DOG_PROTOCOL;

#define GLOBAL_VARIABLE_WTD_OF_TIME   L"WTDOverFlowTime"

#endif
