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
 **/

#ifndef _SLIMPROLIB_H_
#define _SLIMPROLIB_H_

EFI_STATUS
EFIAPI
XGeneBMCStart(BOOLEAN Start);

EFI_STATUS
EFIAPI
XGeneReadIppMsg(UINT32 *data);

EFI_STATUS
EFIAPI
XGeneWriteIppMsg(UINT32 data, UINT32 param);

EFI_STATUS
EFIAPI
XGeneIppLoadFile(CHAR8* f_name, UINT64 addr,
        UINTN offset, UINTN size);

EFI_STATUS
EFIAPI
XGeneIppGetFWRevision(CHAR16* Str, UINT32 Len);

#endif /* _SLIMPROLIB_H_*/
