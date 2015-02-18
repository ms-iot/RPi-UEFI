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

#include "mustang.h"
#include "SnpDxe.h"
#include <Library/PrintLib.h>
#include <Library/SerialPortLib.h>
#include <Library/UefiLib.h>

UINT32 eth_initialized; 
/*
  Functions in Net Library
*/
#define PREFIX_VARIABLE_NAME            L"MAC"
static UINT8 apm_mac_addr[][6] = {{0x00, 0x11, 0x22, 0x33, 0x44, 0x55},
			{0x00, 0x11, 0x22, 0x33, 0x44, 0x56},
			{0x00, 0x11, 0x22, 0x33, 0x44, 0x57},
			{0x00, 0x11, 0x22, 0x33, 0x44, 0x58}
	};
static UINT8 invalid_mac[6] = {0xde, 0xad, 0xbe, 0xef, 0xde, 0xad};
extern EFI_GUID gShellVariableGuid;

static void AsciiStrToEthAddr(CHAR16 *MacBuf, UINT8 *MAC)
{
#define A_D(x) ( ((x >= L'a')&&(x <= L'f'))?(x-L'a'+0xa):(((x >= L'A')&&(x <= L'F'))?(x-L'A'+0xa):(x-L'0')) )

  *MAC++ = (A_D(*MacBuf)<<4) + A_D(*(MacBuf+1));
  *MAC++ = (A_D(*(MacBuf+3))<<4) + A_D(*(MacBuf+4));
  *MAC++ = (A_D(*(MacBuf+6))<<4) + A_D(*(MacBuf+7));
  *MAC++ = (A_D(*(MacBuf+9))<<4) + A_D(*(MacBuf+10));
  *MAC++ = (A_D(*(MacBuf+12))<<4) + A_D(*(MacBuf+13));
  *MAC++ = (A_D(*(MacBuf+15))<<4) + A_D(*(MacBuf+16));
}

static void GetEnvMacAddr(int index, UINT8* MacBuf)
{
  EFI_STATUS  Status;
  UINTN       Size;
  CHAR16      Buf[20];
  CHAR16      MACEnv[30];

  if (index > sizeof(apm_mac_addr)/sizeof(apm_mac_addr[0])) {
    memcpy(MacBuf, invalid_mac, sizeof(invalid_mac));
    return;
  }
  UnicodeSPrint(MACEnv, sizeof(MACEnv), L"%s%d", PREFIX_VARIABLE_NAME, index);
  Size = sizeof(Buf);
  Status = gRT->GetVariable(MACEnv,
                            &gShellVariableGuid,
                            0,
                            &Size,
                            (void *)Buf);

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "GetVariable %s ERROR !!!", MACEnv));
    *((UINT8*)MacBuf+0) = apm_mac_addr[index][0];
    *((UINT8*)MacBuf+1) = apm_mac_addr[index][1];
    *((UINT8*)MacBuf+2) = apm_mac_addr[index][2];
    *((UINT8*)MacBuf+3) = apm_mac_addr[index][3];
    *((UINT8*)MacBuf+4) = apm_mac_addr[index][4];
    *((UINT8*)MacBuf+5) = apm_mac_addr[index][5];
  } else {
    UINT8       MAC[20];

    AsciiStrToEthAddr (Buf, MAC);
    DEBUG((EFI_D_ERROR, "GetVariable  MAC: %2x:%2x:%2x:%2x:%2x:%x !!!", 
          MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]));

    apm_mac_addr[index][0] = *((UINT8*)MacBuf) = MAC[0];
    apm_mac_addr[index][1] = *((UINT8*)MacBuf+1) = MAC[1];
    apm_mac_addr[index][2] = *((UINT8*)MacBuf+2) = MAC[2];
    apm_mac_addr[index][3] = *((UINT8*)MacBuf+3) = MAC[3];
    apm_mac_addr[index][4] = *((UINT8*)MacBuf+4) = MAC[4];
    apm_mac_addr[index][5] = *((UINT8*)MacBuf+5) = MAC[5];
  }
}

EFI_STATUS
APMXGeneNet_Initialize (
  IN OUT  UINT32                       *InterfaceCount,
  IN OUT  NET_INTERFACE_INFO           *InterfaceInfoBuffer
  )
{
  DBG("Enter APMXGeneNet_Initialize\n");
  int index;

  *InterfaceCount = CONFIG_INTERFACE_COUNT;
  for (index = 0; index < *InterfaceCount; index++) {
      InterfaceInfoBuffer[index].InterfaceIndex = index;
      GetEnvMacAddr(index, InterfaceInfoBuffer[index].MacAddr.Addr);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
APMXGeneNet_Finalize (
  VOID
  )
{
  DBG("Enter APMXGeneNet_Finalize\n");
  return EFI_SUCCESS;
}

EFI_STATUS
APMXGeneNet_Set_Receive_Filter (
  IN  UINT32                           Index,
  IN  UINT32                           EnableFilter,
  IN  UINT32                           MCastFilterCnt,
  IN  EFI_MAC_ADDRESS                  * MCastFilter
  )
{
  DBG("Enter APMXGeneNet_Set_Receive_Filter\n");
  return EFI_SUCCESS;
}

EFI_STATUS
APMXGeneNet_Receive (
  IN      UINT32                      Index,
  IN OUT  UINTN                      *BufferSize,
  OUT     VOID                        *Buffer
  )
{
  DBG("Enter APMXGeneNet_Receive\n");
  if (eth_initialized) {
    int rc;
    rc = (emac_dev[Index])->recv(emac_dev[Index], Buffer, BufferSize);
    return rc;
  }
  return EFI_SUCCESS;
}


EFI_STATUS
APMXGeneNet_Transmit (
  IN  UINT32                          Index,
  IN  UINT32                          HeaderSize,
  IN  UINT32                          BufferSize,
  IN  VOID                            *Buffer,
  IN  EFI_MAC_ADDRESS                 * SrcAddr,
  IN  EFI_MAC_ADDRESS                 * DestAddr,
  IN  UINT16                          *Protocol
  )
{

	UINT16 prot;
  DBG("APMXGeneNet_Transmit emac_dev[%d]=0x%p\n",  Index, emac_dev[Index]);

   if (!eth_initialized) {
#ifdef CONFIG_STORM
	if (Index == 0)
		emac_dev[Index]->index = MENET;
	else if (Index == 1) 
		emac_dev[Index]->index = ENET_0;
	else if (Index == 2) 
		emac_dev[Index]->index = ENET_1;
	else if (Index == 3) 
		emac_dev[Index]->index = XGENET_0;
	else
		return EFI_SUCCESS;
#else
	if (Index == 0)
		emac_dev[Index]->index = XGENET_0;
	else if (Index == 1)
		emac_dev[Index]->index = XGENET_1;
	else
		return EFI_SUCCESS;
#endif
   	(emac_dev[Index])->init(emac_dev[Index]);
	eth_initialized = 1;
   }

   if (HeaderSize) {
	CopyMem (Buffer, DestAddr, 6);
	CopyMem (Buffer + 6, SrcAddr, 6);
	prot = PXE_SWAP_UINT16(*Protocol);
	DBG("APMXGeneNet_Transmit prot=0x%x\n", prot);
	CopyMem (Buffer + 12, &prot, 2);
   }
   apm_eth_tx( emac_dev[Index], Buffer, BufferSize);

  return EFI_SUCCESS;
}

VOID
APMXGeneNet_Halt (
  IN UINT32 Index
  )
{
  if (eth_initialized) {
     /* stop rx and tx */
     (emac_dev[Index])->halt(emac_dev[Index]);
  }
}
