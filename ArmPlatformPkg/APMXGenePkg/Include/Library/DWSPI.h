/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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
 
#ifndef _DWSPILib_H_
#define _DWSPILib_H_

#include <Library/SPI.h>

struct SPI_SLAVE *DwSpiHostSetupSlave(OUT struct SPI_SLAVE *, 
                                  IN UINTN , IN UINTN ,
                                  IN UINTN , IN UINTN );

BOOLEAN DwSpiHostIsEnabled(IN UINT64);
VOID DwSpiHostEnable(IN UINT64);
VOID DwSpiHostDisable(IN UINT64);
                                  
EFI_STATUS DwSpiHostXfer(IN struct SPI_SLAVE *, IN UINTN , IN const VOID *,
       IN VOID *, IN UINT32 );
       
EFI_STATUS DwSpiHostEepromRead(IN UINT64 , IN UINT8 * , IN UINT32 , IN UINT8 * , IN UINT32 );

EFI_STATUS DwSpiHostTxDual(IN UINT64 , IN UINT8 * , IN UINT32 , IN UINT8 * , IN UINT32 );

EFI_STATUS DwSpiHostRxDual(IN UINT64 , IN UINT8 * , IN UINT32 , IN UINT8 * , IN UINT32 );

#endif /* _DWSPILib_H_ */
