/*++

Copyright (c) 2006 - 2009, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name: 

  PlatformData.c

Abstract:
  
  Defined the platform specific device path which will be used by
  platform Bbd to perform the platform policy connect.

--*/

#include "BdsPlatform.h"
#include <Protocol/SerialIo.h>
#include <Protocol/GraphicsOutput.h>


//
// Predefined platform default time out value
//
UINT16                      gPlatformBootTimeOutDefault = 10;

//
// Platform specific keyboard device path
//
EXYNOS_GOP_DEVICE_PATH gGopDevicePath = {
  {	// ExynosBus
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      },
      EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
  },
  gEndEntire
};

EXYNOS_CONSOLE_DEVICE_PATH gConsoleDevicePath = {
  {	// ExynosBus
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      },
		  EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID
  },
  gEndEntire
};

//
// Predefined platform default console device path
//
BDS_CONSOLE_CONNECT_ENTRY   gPlatformConsole[] = {
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &gConsoleDevicePath,
    (CONSOLE_OUT | CONSOLE_IN)
  },
  {
    (EFI_DEVICE_PATH_PROTOCOL *) &gGopDevicePath,
    (CONSOLE_OUT | CONSOLE_IN)
  },
  {
    NULL,
    0
  }
};

//
// Predefined platform specific driver option
//
EFI_DEVICE_PATH_PROTOCOL    *gPlatformDriverOption[] = { NULL };

//
// Predefined platform connect sequence
//
EFI_DEVICE_PATH_PROTOCOL    *gPlatformConnectSequence[] = { NULL };
