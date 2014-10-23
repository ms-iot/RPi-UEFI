/** @file
*
*  Copyright (c) 2014, ARM Limited. All rights reserved.
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

#ifndef __HOSTNAME_GUID_H__
#define __HOSTNAME_GUID_H__

/*
  This Variable guid is used for the UEFI variable named "Hostname".
  A use case for this is Ip4ConfigDxe sending a hostname during the DHCP DORA
  process. A future version of the UEFI spec might include this variable in
  the list of globally defined variables. In this case this GUID would become
  redundant and gEfiGlobalVariableGuid could be used instead.
*/
extern EFI_GUID gEfiHostnameVariableGuid;

#endif
