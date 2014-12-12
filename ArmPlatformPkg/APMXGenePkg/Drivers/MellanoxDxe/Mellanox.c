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

#include "SnpDxe.h"

#define MELLANOX_INSTANCE_SIGNATURE SIGNATURE_32 ('w', 'M', 'L', 'X')

//
//  Functions in Net Library
//
typedef struct _MELLANOX_PRIVATE_DATA {
  UINT32        Signature;
  UINT32        MlxNumPorts;
  UINT32        MlxOpenPortMask;
  VOID          *ReceivedBuffer;
  UINT32        BufferMax;
  UINT32        ReceivedPos;
  VOID          *Hermon;
  UINT32        RefCount;
} MELLANOX_PRIVATE_DATA;

#define BUFFER_CHUNK 2048

extern void* hermon_probe (EFI_PCI_IO_PROTOCOL *pci, UINT32 *dev_cnt);
extern int hermon_get_mac_info(void *hermon, unsigned int mport, uint8_t *mac);
extern int hermon_transmit(void *hermon, unsigned int mport, void *packet, unsigned int length);
extern int hermon_close_port(void *hermon, unsigned int mport);
extern int hermon_open_port(void *hermon, unsigned int mport, void *priv_data);
extern int hermon_poll(void *hermon, unsigned int mport);
extern void hermon_free ( void *hermon );

EFI_STATUS
Mellanox_Initialize (
  IN EFI_PCI_IO_PROTOCOL              *PciIo,
  IN OUT UINT32                       *InterfaceCount,
  IN OUT NET_INTERFACE_INFO           *InterfaceInfoBuffer,
  OUT VOID                            **PrivateData
  )
{
  MELLANOX_PRIVATE_DATA *MlxPriv;
  void *Hermon;
  INTN Count;

  SNPDBG("Enter Mellanox_Initialize\n");

  Hermon = hermon_probe(PciIo, InterfaceCount);
  if (NULL == Hermon)
    return EFI_DEVICE_ERROR;

  SNPDBG("Number of interface:%d\n", *InterfaceCount);
  for (Count = 0; Count < *InterfaceCount; Count++) {
    InterfaceInfoBuffer[Count].InterfaceIndex = Count;
    hermon_get_mac_info(Hermon, Count, InterfaceInfoBuffer[Count].MacAddr.Addr);
    SNPDBG("Interface[%d] MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", Count,
        InterfaceInfoBuffer[Count].MacAddr.Addr[0],
        InterfaceInfoBuffer[Count].MacAddr.Addr[1],
        InterfaceInfoBuffer[Count].MacAddr.Addr[2],
        InterfaceInfoBuffer[Count].MacAddr.Addr[3],
        InterfaceInfoBuffer[Count].MacAddr.Addr[4],
        InterfaceInfoBuffer[Count].MacAddr.Addr[5]);
  }
  MlxPriv = AllocateZeroPool(sizeof(MELLANOX_PRIVATE_DATA));
  if (NULL == MlxPriv) {
    hermon_free(Hermon);
    return EFI_OUT_OF_RESOURCES;
  }

  MlxPriv->MlxNumPorts = *InterfaceCount;
  MlxPriv->Hermon = Hermon;
  MlxPriv->RefCount = *InterfaceCount; /* each interface will refer to MlxPriv */
  MlxPriv->Signature = MELLANOX_INSTANCE_SIGNATURE;

  SNPDBG("Mellanox hermon %p num of ports:%d\n", MlxPriv->Hermon, MlxPriv->MlxNumPorts);

  *PrivateData = (VOID *)MlxPriv;

  return EFI_SUCCESS;
}

EFI_STATUS
Mellanox_Finalize (
  IN VOID *PrivateData
  )
{
  MELLANOX_PRIVATE_DATA *MlxPriv = (MELLANOX_PRIVATE_DATA *)PrivateData;
  INTN Count;

  SNPDBG("Enter Mellanox_Finalize\n");

  for (Count = 0; Count < MlxPriv->MlxNumPorts; Count++)
    if (MlxPriv->MlxOpenPortMask & (1 << Count)) {
      SNPDBG("Close Mellanox hermon %p port:%d\n", MlxPriv->Hermon, Count);
      hermon_close_port(MlxPriv->Hermon, Count);
      MlxPriv->MlxOpenPortMask &= ~(1 << Count);
    }

  --MlxPriv->RefCount;

  if (MlxPriv->RefCount == 0) {
    SNPDBG("Mellanox_Finalize: Free mellanox instance:%p\n", MlxPriv);
    hermon_free(MlxPriv->Hermon);
    FreePool(MlxPriv);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
Mellanox_Set_Receive_Filter (
  IN  UINT32                           Index,
  IN  UINT32                           EnableFilter,
  IN  UINT32                           MCastFilterCnt,
  IN  EFI_MAC_ADDRESS                  * MCastFilter
  )
{
  SNPDBG("Enter Mellanox_Set_Receive_Filter\n");
  return EFI_SUCCESS;
}

VOID
Mellanox_Callback_GetReceiveData(VOID *PrivateData, VOID *Packet, UINT32 Length)
{

  MELLANOX_PRIVATE_DATA *MlxPriv = (MELLANOX_PRIVATE_DATA *)PrivateData;
  VOID *OldBuffer;

  //SNPDBG("Enter Mellanox_Callback_GetReceiveData\n");
  //SNPDBG("Packet:%p Length:%d\n", Packet, Length);

  if (!MlxPriv->ReceivedBuffer) {
    MlxPriv->ReceivedBuffer = AllocatePool(BUFFER_CHUNK);
    if (!MlxPriv->ReceivedBuffer) {
      ERROR("Out of Memory\n");
      //SNPDBG("Exit Mellanox_Callback_GetReceiveData:%d\n", __LINE__);
      return;
    }
    MlxPriv->ReceivedPos = 0;
    MlxPriv->BufferMax = BUFFER_CHUNK;
  }
  if (MlxPriv->ReceivedPos + Length > MlxPriv->BufferMax) {
    //we are out of buffer
    OldBuffer = MlxPriv->ReceivedBuffer;
    MlxPriv->BufferMax += BUFFER_CHUNK;
    MlxPriv->ReceivedBuffer = AllocatePool(MlxPriv->BufferMax);
    if (!MlxPriv->ReceivedBuffer) {
      ERROR("Out of Memory\n");
      FreePool(OldBuffer);
      //SNPDBG("Exit Mellanox_Callback_GetReceiveData:%d\n", __LINE__);
      return;
    }
    CopyMem(MlxPriv->ReceivedBuffer, OldBuffer, MlxPriv->ReceivedPos);
    FreePool(OldBuffer);
  }
  CopyMem(MlxPriv->ReceivedBuffer + MlxPriv->ReceivedPos, Packet, Length);
  MlxPriv->ReceivedPos += Length;
  //SNPDBG("Exit Mellanox_Callback_GetReceiveData:%d\n", __LINE__);
}

EFI_STATUS
Mellanox_Receive (
  IN      UINT32                      Index,
  IN OUT  UINTN                      *BufferSize,
  OUT     VOID                        *Buffer,
  IN      VOID                        *PrivateData
  )
{
  MELLANOX_PRIVATE_DATA *MlxPriv = (MELLANOX_PRIVATE_DATA *)PrivateData;

//  SNPDBG("Enter Mellanox_Receive hermon %p Buffer=0x%p BufferSize=0x%x\n",
//		MlxPriv->Hermon, Buffer, *BufferSize);

  if (!(MlxPriv->MlxOpenPortMask & (1 << Index))) {
    *BufferSize = 0;
    return EFI_SUCCESS;
  }

	hermon_poll(MlxPriv->Hermon, Index);
	/* We should receive data here */
	if (MlxPriv->ReceivedBuffer) {
	  //SNPDBG("Has data\n");
	  if (*BufferSize < MlxPriv->ReceivedPos) {
	    SNPDBG("Received buffer is larger than buffer size allocated\n");
	    CopyMem(Buffer, MlxPriv->ReceivedBuffer, *BufferSize);
	  } else {
	    CopyMem(Buffer, MlxPriv->ReceivedBuffer, MlxPriv->ReceivedPos);
	    *BufferSize =  MlxPriv->ReceivedPos;
	  }
	  FreePool(MlxPriv->ReceivedBuffer);
	  MlxPriv->ReceivedBuffer = NULL;
	} else {
	  *BufferSize = 0;
	}
	//SNPDBG("Exit Mellanox_Receive:%d\n", __LINE__);
  return EFI_SUCCESS;
}


EFI_STATUS
Mellanox_Transmit (
  IN  UINT32                          Index,
  IN  UINT32                          HeaderSize,
  IN  UINT32                          BufferSize,
  IN  VOID                            *Buffer,
  IN  EFI_MAC_ADDRESS                 * SrcAddr,
  IN  EFI_MAC_ADDRESS                 * DestAddr,
  IN  UINT16                          *Protocol,
  IN  VOID                            *PrivateData
  )
{
  MELLANOX_PRIVATE_DATA *MlxPriv = (MELLANOX_PRIVATE_DATA *)PrivateData;
  UINT16 prot;

  //SNPDBG("Enter Mellanox_Transmit hermon %p\n", MlxPriv->Hermon);
  //SNPDBG("   Index=0x%x, HeaderSize=0x%x, BufferSize=0x%x prot=0x%x\n", Index, HeaderSize, BufferSize, *Protocol);

  if (!(MlxPriv->MlxOpenPortMask & (1 << Index))) {
    SNPDBG("Open Mellanox hermon %p port:%d\n", MlxPriv->Hermon, Index);
    hermon_open_port(MlxPriv->Hermon, Index, (VOID *)MlxPriv);
    MlxPriv->MlxOpenPortMask |= 1 << Index;
  }

  if (HeaderSize) {
    CopyMem (Buffer, DestAddr, 6);
    CopyMem (Buffer + 6, SrcAddr, 6);
    prot = PXE_SWAP_UINT16(*Protocol);
    //SNPDBG("Mellanox_Transmit prot=0x%x\n", prot);
    CopyMem (Buffer + 12, &prot, 2);
  }
  if (hermon_transmit(MlxPriv->Hermon, Index, Buffer, BufferSize) != 0) {
    SNPDBG("Failed to transmit Buffer:%p Size:%x\n", Buffer, BufferSize);
  }
  //SNPDBG("Exit Mellanox_Transmit\n");
  return EFI_SUCCESS;
}

VOID
Mellanox_Halt (
  IN UINT32 Index,
  IN VOID   *PrivateData
  )
{
  MELLANOX_PRIVATE_DATA *MlxPriv = (MELLANOX_PRIVATE_DATA *)PrivateData;

  SNPDBG("Enter Mellanox_Halt\n");
  SNPDBG("   Index=0x%x\n", Index);

  if (MlxPriv->MlxOpenPortMask & (1 << Index)) {
    SNPDBG("Close Mellanox hermon %p port:%d\n", MlxPriv->Hermon, Index);
    hermon_close_port(MlxPriv->Hermon, Index);
    MlxPriv->MlxOpenPortMask &= ~(1 << Index);
  }
}
