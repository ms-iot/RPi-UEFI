/**
 * Copyright (c) 2013, 2014, AppliedMicro Corp. All rights reserved.
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

EFI_EVENT             EfiExitBootServicesEvent = (EFI_EVENT)NULL;
BOOLEAN               NetUtilityLibInitDone = FALSE;

extern EFI_STATUS
Mellanox_Initialize (
  IN EFI_PCI_IO_PROTOCOL               *PciIo,
  IN OUT  UINT32                       *InterfaceCount,
  IN OUT  NET_INTERFACE_INFO           *InterfaceInfoBuffer,
  OUT     VOID                         **PrivateData
  );

extern EFI_STATUS
Mellanox_Finalize (
  IN VOID *PrivateData
  );

extern EFI_STATUS
Mellanox_Set_Receive_Filter (
  IN  UINT32                           Index,
  IN  UINT32                           EnableFilter,
  IN  UINT32                           MCastFilterCnt,
  IN  EFI_MAC_ADDRESS                  * MCastFilter
  );

extern EFI_STATUS
Mellanox_Receive (
  IN      UINT32                      Index,
  IN OUT  UINTN                      *BufferSize,
  OUT     VOID                        *Buffer,
  IN      VOID                        *PrivateData
  );

extern EFI_STATUS
Mellanox_Transmit (
  IN  UINT32                          Index,
  IN  UINT32                          HeaderSize,
  IN  UINT32                          BufferSize,
  IN  VOID                            *Buffer,
  IN  EFI_MAC_ADDRESS                 * SrcAddr,
  IN  EFI_MAC_ADDRESS                 * DestAddr,
  IN  UINT16                          *Protocol,
  IN  VOID                            *PrivateData
  );

extern VOID
Mellanox_Halt (
  IN  UINT32                          Index,
  IN  VOID                            *PrivateData
  );

EFI_DRIVER_BINDING_PROTOCOL gSnpDxeBinding = {
  SnpDxeBindingSupported,
  SnpDxeBindingStart,
  SnpDxeBindingStop,
  0xa,
  NULL,
  NULL
};

SNP_GLOBAL_DATA         gSnpDxeGlobalData = {
  SNP_DRIVER_SIGNATURE,  //  Signature
  {
    NULL,
    NULL
  },                          //  InstanceList
  {
    0
  },                          //  NtNetUtilityTable
  {
    0,
    0,
    EfiLockUninitialized
  },                          //  Lock
  { 0 }, // TxQueue
  0,     // TxQueHead
  0,     // TxQueTail

  //
  //  Private functions
  //
  SnpDxeInitializeGlobalData,            //  InitializeGlobalData
  SnpDxeInitializeMellanoxPci,
  SnpDxeInitializeInstanceData,          //  InitializeInstanceData
  SnpDxeCloseInstance                    //  CloseInstance
};

INTN TxQueNext (
    IN INTN n
    )
{
  return (((n + 1) >= TX_QUEUE_DEPTH) ? 0 : (n + 1));
}

BOOLEAN
TxQueInsert (
    IN    SNP_GLOBAL_DATA  *GlobalData,
    IN    VOID             *Buffer
    )
{

  if (TxQueNext (GlobalData->TxQueTail) == GlobalData->TxQueHead)
    return FALSE;

  GlobalData->TxQueue[GlobalData->TxQueTail] = Buffer;
  GlobalData->TxQueTail = TxQueNext (GlobalData->TxQueTail);

  return TRUE;
}

VOID
*TxQueRemove (
    IN    SNP_GLOBAL_DATA *GlobalData
    )
{
  VOID *Buffer;

  if (GlobalData->TxQueTail == GlobalData->TxQueHead) {
    return NULL;
  }

  Buffer = GlobalData->TxQueue[GlobalData->TxQueHead];
  GlobalData->TxQueue[GlobalData->TxQueHead] = NULL;
  GlobalData->TxQueHead = TxQueNext (GlobalData->TxQueHead);

  return Buffer;
}

/**
  Changes the state of a network interface from "stopped" to "started".

  @param  This Protocol instance pointer.

  @retval EFI_SUCCESS           Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeStart (
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This)
{
  EFI_SIMPLE_NETWORK_MODE *Mode;

  SNPDBG("Enter SnpDxeStart\n");
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Check state of the driver
  Mode = This->Mode;
  switch (Mode->State) {
  case EfiSimpleNetworkStopped:
    break;
  case EfiSimpleNetworkStarted:
  case EfiSimpleNetworkInitialized:
    DEBUG((EFI_D_WARN, "SnpDxe: Driver already started\n"));
    return EFI_ALREADY_STARTED;
  default:
    DEBUG((EFI_D_ERROR, "SnpDxe: Driver in an invalid state: %u\n",
          (UINTN)Mode->State));
    return EFI_DEVICE_ERROR;
  }
  Mode->State = EfiSimpleNetworkStarted;

  return EFI_SUCCESS;
}

/**
  Changes the state of a network interface from "started" to "stopped".

  @param  This Protocol instance pointer.

  @retval EFI_SUCCESS           Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeStop (
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This)
{
  EFI_SIMPLE_NETWORK_MODE *Mode;

  SNPDBG("Enter SnpDxeStop\n");
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Mode = This->Mode;
  switch (Mode->State) {
  case EfiSimpleNetworkStarted:
  case EfiSimpleNetworkInitialized:
    break;
  case EfiSimpleNetworkStopped:
    DEBUG((EFI_D_WARN, "SnpDxe: Driver not started\n"));
    return EFI_NOT_STARTED;
  default:
    DEBUG((EFI_D_ERROR, "SnpDxe: Driver in an invalid state: %u\n",
          (UINTN)Mode->State));
    return EFI_DEVICE_ERROR;
  }

  Mode->State = EfiSimpleNetworkStopped;
  return EFI_SUCCESS;
}

/**
  Resets a network adapter and allocates the transmit and receive buffers
  required by the network interface; optionally, also requests allocation
  of additional transmit and receive buffers.

  @param  This              Protocol instance pointer.
  @param  ExtraRxBufferSize The size, in bytes, of the extra receive buffer space
                            that the driver should allocate for the network interface.
                            Some network interfaces will not be able to use the extra
                            buffer, and the caller will not know if it is actually
                            being used.
  @param  ExtraTxBufferSize The size, in bytes, of the extra transmit buffer space
                            that the driver should allocate for the network interface.
                            Some network interfaces will not be able to use the extra
                            buffer, and the caller will not know if it is actually
                            being used.

  @retval EFI_SUCCESS           Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeInitialize (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN UINTN                        ExtraRxBufferSize OPTIONAL,
    IN UINTN                        ExtraTxBufferSize OPTIONAL)
{
  EFI_SIMPLE_NETWORK_MODE *Mode;

  SNPDBG("Enter SnpDxeInitialize\n");

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // Check that driver was started but not initialised
  Mode = This->Mode;
  switch (Mode->State) {
  case EfiSimpleNetworkStarted:
    break;
  case EfiSimpleNetworkInitialized:
    DEBUG((EFI_D_WARN, "SnpDxe: Driver already initialized\n"));
    return EFI_SUCCESS;
  case EfiSimpleNetworkStopped:
    DEBUG((EFI_D_WARN, "SnpDxe: Driver not started\n"));
    return EFI_NOT_STARTED;
  default:
    DEBUG((EFI_D_ERROR, "SnpDxe: Driver in an invalid state: %u\n",
          (UINTN)Mode->State));
    return EFI_DEVICE_ERROR;
  }

  Mode->State = EfiSimpleNetworkInitialized;
  return EFI_SUCCESS;
}

/**
  Resets a network adapter and re-initializes it with the parameters that were
  provided in the previous call to Initialize().

  @param  This                 Protocol instance pointer.
  @param  ExtendedVerification Indicates that the driver may perform a more
                               exhaustive verification operation of the device
                               during reset.

  @retval EFI_SUCCESS           Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeReset (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                      ExtendedVerification)
{
  SNPDBG("Enter SnpDxeReset\n");
  return EFI_SUCCESS;
}

/**
  Resets a network adapter and leaves it in a state that is safe for
  another driver to initialize.

  @param  This Protocol instance pointer.

  @retval EFI_SUCCESS           Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeShutdown (
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This)
{
  EFI_SIMPLE_NETWORK_MODE *Mode;

  SNPDBG("Enter SnpDxeShutdown\n");

  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // First check that driver has already been initialized
  Mode = This->Mode;
  switch (Mode->State) {
  case EfiSimpleNetworkInitialized:
    break;
  case EfiSimpleNetworkStarted:
    DEBUG((EFI_D_WARN, "SnpDxe: Driver not yet initialized\n"));
    return EFI_DEVICE_ERROR;
  case EfiSimpleNetworkStopped:
    DEBUG((EFI_D_WARN, "SnpDxe: Driver in stopped state\n"));
    return EFI_NOT_STARTED;
  default:
    DEBUG((EFI_D_ERROR, "SnpDxe: Driver in an invalid state: %u\n",
          (UINTN)Mode->State));
    return EFI_DEVICE_ERROR;
  }

  Mode->State = EfiSimpleNetworkStarted;

  return EFI_SUCCESS;
}

/**
  Manages the multicast receive filters of a network interface.

  @param  This               Protocol instance pointer.
  @param  EnableBits         A bit mask of receive filters to enable on the network interface.
  @param  DisableBits        A bit mask of receive filters to disable on the network interface.
  @param  ResetMcastFilter   Set to TRUE to reset the contents of the multicast receive
                             filters on the network interface to their default values.
  @param  McastFilterCount   Number of multicast HW MAC addresses in the new
                             MCastFilter list. This value must be less than or equal to
                             the MCastFilterCnt field of EFI_SIMPLE_NETWORK_MODE. This
                             field is optional if ResetMCastFilter is TRUE.
  @param  McastFilter        A pointer to a list of new multicast receive filter HW MAC
                             addresses. This list will replace any existing multicast
                             HW MAC address list. This field is optional if
                             ResetMCastFilter is TRUE.

  @retval EFI_SUCCESS           The multicast receive filter list was updated.
  @retval EFI_DEVICE_ERROR      The command could not be sent to the network interface.

**/
EFI_STATUS
EFIAPI
SnpDxeReceiveFilters (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN UINT32                       Enable,
    IN UINT32                       Disable,
    IN BOOLEAN                      ResetMCastFilter,
    IN UINTN                        MCastFilterCnt  OPTIONAL,
    IN EFI_MAC_ADDRESS              *MCastFilter    OPTIONAL)
{
  SNP_INSTANCE_DATA *Instance;
  SNP_GLOBAL_DATA   *GlobalData;
  EFI_STATUS        ReturnValue;

  SNPDBG("Enter SnpDxeReceiveFilters\n");

  Instance    = SNP_INSTANCE_DATA_FROM_SNP_THIS (This);

  GlobalData  = Instance->GlobalData;

  if (EFI_ERROR (EfiAcquireLockOrFail (&GlobalData->Lock))) {
    return EFI_ACCESS_DENIED;
  }

  ReturnValue = GlobalData->NtNetUtilityTable.SetReceiveFilter (
                                                Instance->InterfaceInfo.InterfaceIndex,
                                                Enable,
                                                MCastFilterCnt,
                                                MCastFilter
                                                );

  EfiReleaseLock (&GlobalData->Lock);

  return ReturnValue;
}

/**
  Modifies or resets the current station address, if supported.

  @param  This         Protocol instance pointer.
  @param  Reset        Flag used to reset the station address to the network interfaces
                       permanent address.
  @param  NewMacAddr   New station address to be used for the network interface.

  @retval EFI_UNSUPPORTED       Not supported yet.

**/
EFI_STATUS
EFIAPI
SnpDxeStationAddress (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                      Reset,
    IN EFI_MAC_ADDRESS              *New OPTIONAL)
{
  SNPDBG("Enter SnpDxeStationAddress\n");
  return EFI_UNSUPPORTED;
}

/**
  Resets or collects the statistics on a network interface.

  @param  This            Protocol instance pointer.
  @param  Reset           Set to TRUE to reset the statistics for the network interface.
  @param  StatisticsSize  On input the size, in bytes, of StatisticsTable. On
                          output the size, in bytes, of the resulting table of
                          statistics.
  @param  StatisticsTable A pointer to the EFI_NETWORK_STATISTICS structure that
                          contains the statistics.

  @retval EFI_SUCCESS           The statistics were collected from the network interface.
  @retval EFI_NOT_STARTED       The network interface has not been started.
  @retval EFI_BUFFER_TOO_SMALL  The Statistics buffer was too small. The current buffer
                                size needed to hold the statistics is returned in
                                StatisticsSize.
  @retval EFI_UNSUPPORTED       Not supported yet.

**/
EFI_STATUS
EFIAPI
SnpDxeStatistics (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                      Reset,
    IN OUT UINTN                    *StatisticsSize  OPTIONAL,
    OUT EFI_NETWORK_STATISTICS      *StatisticsTable OPTIONAL)
{
  SNPDBG("Enter SnpDxeStatistics\n");
  return EFI_UNSUPPORTED;
}

/**
  Converts a multicast IP address to a multicast HW MAC address.

  @param  This  Protocol instance pointer.
  @param  Ipv6  Set to TRUE if the multicast IP address is IPv6 [RFC 2460]. Set
                to FALSE if the multicast IP address is IPv4 [RFC 791].
  @param  Ip    The multicast IP address that is to be converted to a multicast
                HW MAC address.
  @param  Mac   The multicast HW MAC address that is to be generated from IP.

  @retval EFI_SUCCESS           The multicast IP address was mapped to the multicast
                                HW MAC address.
  @retval EFI_NOT_STARTED       The network interface has not been started.
  @retval EFI_BUFFER_TOO_SMALL  The Statistics buffer was too small. The current buffer
                                size needed to hold the statistics is returned in
                                StatisticsSize.
  @retval EFI_UNSUPPORTED       Not supported yet.

**/
EFI_STATUS
EFIAPI
SnpDxeMCastIpToMac (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                      IPv6,
    IN EFI_IP_ADDRESS               *IP,
    OUT EFI_MAC_ADDRESS             *MAC)
{
  SNPDBG("Enter SnpDxeMCastIpToMac\n");
  return EFI_UNSUPPORTED;
}

/**
  Performs read and write operations on the NVRAM device attached to a
  network interface.

  @param  This         Protocol instance pointer.
  @param  ReadOrWrite  TRUE for read operations, FALSE for write operations.
  @param  Offset       Byte offset in the NVRAM device at which to start the read or
                       write operation. This must be a multiple of NvRamAccessSize and
                       less than NvRamSize.
  @param  BufferSize   The number of bytes to read or write from the NVRAM device.
                       This must also be a multiple of NvramAccessSize.
  @param  Buffer       A pointer to the data buffer.

  @retval EFI_UNSUPPORTED       Not supported yet.

**/
EFI_STATUS
EFIAPI
SnpDxeNvData (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                      ReadWrite,
    IN UINTN                        Offset,
    IN UINTN                        BufferSize,
    IN OUT VOID                     *Buffer)
{
  SNPDBG("Enter SnpDxeNvData\n");
  return EFI_UNSUPPORTED;
}

/**
  Reads the current interrupt status and recycled transmit buffer status from
  a network interface.

  @param  This            Protocol instance pointer.
  @param  InterruptStatus A pointer to the bit mask of the currently active interrupts
                          If this is NULL, the interrupt status will not be read from
                          the device. If this is not NULL, the interrupt status will
                          be read from the device. When the  interrupt status is read,
                          it will also be cleared. Clearing the transmit  interrupt
                          does not empty the recycled transmit buffer array.
  @param  TxBuffer        Recycled transmit buffer address. The network interface will
                          not transmit if its internal recycled transmit buffer array
                          is full. Reading the transmit buffer does not clear the
                          transmit interrupt. If this is NULL, then the transmit buffer
                          status will not be read. If there are no transmit buffers to
                          recycle and TxBuf is not NULL, * TxBuf will be set to NULL.

  @retval EFI_SUCCESS           Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeGetStatus (
    IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    OUT UINT32                      *InterruptStatus OPTIONAL,
    OUT VOID                        **TxBuf OPTIONAL)
{
  SNP_INSTANCE_DATA     *Instance;

  Instance    = SNP_INSTANCE_DATA_FROM_SNP_THIS (This);

  if (TxBuf != NULL) {
    *TxBuf = TxQueRemove (Instance->GlobalData);
  }

  if (InterruptStatus != NULL) {
    *InterruptStatus = EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT;
  }

  return EFI_SUCCESS;
}

/**
  Places a packet in the transmit queue of a network interface.

  @param  This       Protocol instance pointer.
  @param  HeaderSize The size, in bytes, of the media header to be filled in by
                     the Transmit() function. If HeaderSize is non-zero, then it
                     must be equal to This->Mode->MediaHeaderSize and the DestAddr
                     and Protocol parameters must not be NULL.
  @param  BufferSize The size, in bytes, of the entire packet (media header and
                     data) to be transmitted through the network interface.
  @param  Buffer     A pointer to the packet (media header followed by data) to be
                     transmitted. This parameter cannot be NULL. If HeaderSize is zero,
                     then the media header in Buffer must already be filled in by the
                     caller. If HeaderSize is non-zero, then the media header will be
                     filled in by the Transmit() function.
  @param  SrcAddr    The source HW MAC address. If HeaderSize is zero, then this parameter
                     is ignored. If HeaderSize is non-zero and SrcAddr is NULL, then
                     This->Mode->CurrentAddress is used for the source HW MAC address.
  @param  DestAddr   The destination HW MAC address. If HeaderSize is zero, then this
                     parameter is ignored.
  @param  Protocol   The type of header to build. If HeaderSize is zero, then this
                     parameter is ignored. See RFC 1700, section "Ether Types", for
                     examples.

  @retval EFI_SUCCESS           The packet was placed on the transmit queue.
  @retval EFI_DEVICE_ERROR      The command could not be sent to the network interface.
  @retval EFI_ACCESS_DENIED     Error acquire global lock for operation.

**/
EFI_STATUS
EFIAPI
SnpDxeTransmit (
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    IN UINTN                        HeaderSize,
    IN UINTN                        BufferSize,
    IN VOID                         *Buffer,
    IN EFI_MAC_ADDRESS              *SrcAddr  OPTIONAL,
    IN EFI_MAC_ADDRESS              *DestAddr OPTIONAL,
    IN UINT16                       *Protocol OPTIONAL)
{
  SNP_INSTANCE_DATA     *Instance;
  SNP_GLOBAL_DATA       *GlobalData;
  EFI_STATUS            ReturnValue;

//  SNPDBG("Enter SnpDxeTransmit\n");

  Instance    = SNP_INSTANCE_DATA_FROM_SNP_THIS (This);

  GlobalData  = Instance->GlobalData;

  if ((HeaderSize != 0) && (SrcAddr == NULL)) {
    SrcAddr = &Instance->Mode.CurrentAddress;
  }

  if (EFI_ERROR (EfiAcquireLockOrFail (&GlobalData->Lock))) {
    return EFI_ACCESS_DENIED;
  }

  if (TxQueNext (GlobalData->TxQueTail) == GlobalData->TxQueHead) {
    EfiReleaseLock (&GlobalData->Lock);
    return EFI_NOT_READY;
  }

  ReturnValue = GlobalData->NtNetUtilityTable.Transmit (
                                                Instance->InterfaceInfo.InterfaceIndex,
                                                HeaderSize,
                                                BufferSize,
                                                Buffer,
                                                SrcAddr,
                                                DestAddr,
                                                Protocol,
                                                Instance->PrivateData
                                                );

  if (ReturnValue == EFI_SUCCESS) {
    TxQueInsert (GlobalData, Buffer);
  }

  EfiReleaseLock (&GlobalData->Lock);

  if (EFI_ERROR(ReturnValue)) {
    return ReturnValue;
  }

  return EFI_SUCCESS;
}

/**
  Receives a packet from a network interface.

  @param  This             Protocol instance pointer.
  @param  HeaderSize       The size, in bytes, of the media header received on the network
                           interface. If this parameter is NULL, then the media header size
                           will not be returned.
  @param  BuffSize         On entry, the size, in bytes, of Buffer. On exit, the size, in
                           bytes, of the packet that was received on the network interface.
  @param  Buffer           A pointer to the data buffer to receive both the media header and
                           the data.
  @param  SourceAddr       The source HW MAC address. If this parameter is NULL, the
                           HW MAC source address will not be extracted from the media
                           header.
  @param  DestinationAddr  The destination HW MAC address. If this parameter is NULL,
                           the HW MAC destination address will not be extracted from the
                           media header.
  @param  Protocol         The media header type. If this parameter is NULL, then the
                           protocol will not be extracted from the media header. See
                           RFC 1700 section "Ether Types" for examples.

  @retval  EFI_SUCCESS           The received data was stored in Buffer, and BufferSize has
                                 been updated to the number of bytes received.
  @retval  EFI_NOT_READY         The network interface is too busy to accept this transmit
                                 request.
  @retval  EFI_BUFFER_TOO_SMALL  The BufferSize parameter is too small.
  @retval  EFI_DEVICE_ERROR      The command could not be sent to the network interface.
  @retval  EFI_ACCESS_DENIED     Error acquire global lock for operation.

**/
EFI_STATUS
EFIAPI
SnpDxeReceive (
    IN EFI_SIMPLE_NETWORK_PROTOCOL *This,
    OUT UINTN                       *HeaderSize   OPTIONAL,
    IN OUT UINTN                    *BufferSize,
    OUT VOID                        *Buffer,
    OUT EFI_MAC_ADDRESS             *SrcAddr      OPTIONAL,
    OUT EFI_MAC_ADDRESS             *DestAddr     OPTIONAL,
    OUT UINT16                      *Protocol     OPTIONAL)
{
  SNP_INSTANCE_DATA     *Instance;
  SNP_GLOBAL_DATA       *GlobalData;
  EFI_STATUS            ReturnValue;
  UINTN                 BufSize;

  BufSize     = *BufferSize;

  Instance    = SNP_INSTANCE_DATA_FROM_SNP_THIS (This);

  GlobalData  = Instance->GlobalData;

  ASSERT (GlobalData->NtNetUtilityTable.Receive != NULL);
  if (EFI_ERROR (EfiAcquireLockOrFail (&GlobalData->Lock))) {
    return EFI_ACCESS_DENIED;
  }
  ReturnValue = GlobalData->NtNetUtilityTable.Receive (
                                                Instance->InterfaceInfo.InterfaceIndex,
                                                BufferSize,
                                                Buffer,
                                                Instance->PrivateData
                                                );
//  SNPDBG("Enter SnpDxeReceive index:%d BufSize=0x%x BufferSize=0x%x ReturnValue=0x%x\n",
//      Instance->InterfaceInfo.InterfaceIndex, BufSize, *BufferSize, ReturnValue);

  EfiReleaseLock (&GlobalData->Lock);

  if (EFI_ERROR(ReturnValue)) {
    return ReturnValue;
  }

  if (*BufferSize == 0)
    return EFI_NOT_READY;

  if (*BufferSize > BufSize)
    return EFI_BUFFER_TOO_SMALL;

  if (HeaderSize != NULL)
    *HeaderSize = 14;

  if (SrcAddr != NULL) {
    ZeroMem (SrcAddr, sizeof (EFI_MAC_ADDRESS));
    CopyMem (SrcAddr, ((UINT8 *) Buffer) + 6, 6);
  }

  if (DestAddr != NULL) {
    ZeroMem (DestAddr, sizeof (EFI_MAC_ADDRESS));
    CopyMem (DestAddr, ((UINT8 *) Buffer), 6);
  }

  if (Protocol != NULL)
    *Protocol = NTOHS (*((UINT16 *) (((UINT8 *) Buffer) + 12)));

  return EFI_SUCCESS;
}

/**
  Test to see if this driver supports ControllerHandle. This service
  is called by the EFI boot service ConnectController(). In
  order to make drivers as small as possible, there are a few calling
  restrictions for this service. ConnectController() must
  follow these calling restrictions. If any other agent wishes to call
  Supported() it must also follow these calling restrictions.

  @param  This                Protocol instance pointer.
  @param  ControllerHandle    Handle of device to test
  @param  RemainingDevicePath Optional parameter use to pick a specific child
                              device to start.

  @retval EFI_SUCCESS         This driver supports this device
  @retval EFI_UNSUPPORTED     This driver does not support this device

**/
EFI_STATUS
EFIAPI
SnpDxeBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  * This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     * RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS            Status;
  EFI_PCI_IO_PROTOCOL   *PciIo;
  PCI_TYPE00            PciData;

  //
  // Attempt to open PCI I/O Protocol
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = PciIo->Pci.Read (
                        PciIo,
                        EfiPciIoWidthUint8,
                        0,
                        sizeof (PciData),
                        &PciData
                        );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }
  SNPDBG("Read VendorId == %x!!!\n", PciData.Hdr.VendorId);
  if (PciData.Hdr.VendorId == PCI_VENDOR_ID_MELLANOX &&
      PciData.Hdr.DeviceId == PCI_DEVICE_ID_MELLANOX)
    return EFI_SUCCESS;

  return EFI_UNSUPPORTED;
}

/**
  Start this driver on ControllerHandle. This service is called by the
  EFI boot service ConnectController(). In order to make
  drivers as small as possible, there are a few calling restrictions for
  this service. ConnectController() must follow these
  calling restrictions. If any other agent wishes to call Start() it
  must also follow these calling restrictions.

  @param  This                 Protocol instance pointer.
  @param  ControllerHandle     Handle of device to bind driver to
  @param  RemainingDevicePath  Optional parameter use to pick a specific child
                               device to start.

  @retval EFI_SUCCESS          Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  * This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     * RemainingDevicePath OPTIONAL
  )
{
  EFI_STATUS                        Status;
  EFI_PCI_IO_PROTOCOL               *PciIo;
  PCI_TYPE00                        PciData;
  UINT64                            Supports;
  UINT64                            OriginalPciAttributes;
  BOOLEAN                           PciAttributesSaved;

  SNPDBG("Enter SnpDxeBindingStart\n");
  //
  // Now test and open PCI I/O Protocol
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "SnpDxeBindingStart error return status = %r\n", Status));
    return Status;
  }

  PciAttributesSaved = FALSE;
  //
  // Save original PCI attributes
  //
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationGet,
                    0,
                    &OriginalPciAttributes
                    );

  if (EFI_ERROR (Status)) {
    goto Done;
  }

  PciAttributesSaved = TRUE;

  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSupported,
                    0,
                    &Supports
                    );
  if (!EFI_ERROR (Status)) {
    Supports &= EFI_PCI_DEVICE_ENABLE;
    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationEnable,
                      Supports,
                      NULL
                      );
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "SnpDxeBindingStart: failed to enable controller\n"));
    goto Done;
  }

  Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          0,
                          sizeof (PciData),
                          &PciData
                          );
  if (EFI_ERROR (Status))
    goto Done;

  if (PciData.Hdr.VendorId != PCI_VENDOR_ID_MELLANOX) {
    SNPDBG("Not mallanox card\n");
    goto Done;
  }

  SNPDBG("Latency Timer:%d\n", PciData.Hdr.LatencyTimer);
  if (PciData.Hdr.LatencyTimer == 0) {
    SNPDBG("Latency timer is too slow, set it to 32\n");
    PciData.Hdr.LatencyTimer = 32;
    Status = PciIo->Pci.Write (
                            PciIo,
                            EfiPciIoWidthUint8,
                            0,
                            sizeof (PciData),
                            &PciData
                            );
    if (EFI_ERROR (Status))
      goto Done;
  }

  if (!NetUtilityLibInitDone) {
    //
    //  Initialize the global data
    //
    Status = SnpDxeInitializeGlobalData (PciIo, &gSnpDxeGlobalData);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "SnpDxeBindingStart: failed to initialize controller\n"));
    }
  }

  Status = SnpDxeInitializeMellanoxPci(PciIo, &gSnpDxeGlobalData);

Done:
  if (EFI_ERROR (Status)) {
    if (PciAttributesSaved) {
      //
      // Restore original PCI attributes
      //
      PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationSet,
                      OriginalPciAttributes,
                      NULL
                      );
    }
    gBS->CloseProtocol (
         ControllerHandle,
          &gEfiPciIoProtocolGuid,
          This->DriverBindingHandle,
          ControllerHandle
          );
  }

  DEBUG ((EFI_D_INFO, "SnpDxeBindingStart END status = %r\n", Status));

  return Status;
}

/**
  Stop this driver on ControllerHandle. This service is called by the
  EFI boot service DisconnectController(). In order to
  make drivers as small as possible, there are a few calling
  restrictions for this service. DisconnectController()
  must follow these calling restrictions. If any other agent wishes
  to call Stop() it must also follow these calling restrictions.

  @param  This              Protocol instance pointer.
  @param  ControllerHandle  Handle of device to stop driver on
  @param  NumberOfChildren  Number of Handles in ChildHandleBuffer. If number of
                            children is zero stop the entire bus driver.
  @param  ChildHandleBuffer List of Child Handles to Stop.

  @retval EFI_SUCCESS       Always succeeds.

**/
EFI_STATUS
EFIAPI
SnpDxeBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   ControllerHandle,
  IN  UINTN                        NumberOfChildren,
  IN  EFI_HANDLE                   *ChildHandleBuffer
  )
{
  //
  // Close PCI protocols
  //
  return gBS->CloseProtocol (
                ControllerHandle,
                &gEfiPciIoProtocolGuid,
                This->DriverBindingHandle,
                ControllerHandle
                );
}

SNP_INSTANCE_DATA gSnpDxeInstanceTemplate = {
  SNP_INSTANCE_SIGNATURE,            //  Signature
  {
    NULL,
    NULL
  },                                      //  Entry
  NULL,                                   //  GlobalData
  NULL,                                   //  DeviceHandle
  NULL,                                   //  DevicePath
  {                                       //  Snp
    EFI_SIMPLE_NETWORK_PROTOCOL_REVISION, //  Revision
    SnpDxeStart,                          //  Start
    SnpDxeStop,                           //  Stop
    SnpDxeInitialize,                     //  Initialize
    SnpDxeReset,                          //  Reset
    SnpDxeShutdown,                       //  Shutdown
    SnpDxeReceiveFilters,                 //  ReceiveFilters
    SnpDxeStationAddress,                 //  StationAddress
    SnpDxeStatistics,                     //  Statistics
    SnpDxeMCastIpToMac,                   //  MCastIpToMac
    SnpDxeNvData,                         //  NvData
    SnpDxeGetStatus,                      //  GetStatus
    SnpDxeTransmit,                       //  Transmit
    SnpDxeReceive,                        //  Receive
    NULL,                                 //  WaitForPacket
    NULL                                  //  Mode
  },
  {                                       //  Mode
    EfiSimpleNetworkStopped,              //  State
    NET_ETHER_ADDR_LEN,                   //  HwAddressSize
    NET_ETHER_HEADER_SIZE,                //  MediaHeaderSize
    1500,                                 //  MaxPacketSize
    0,                                    //  NvRamSize
    0,                                    //  NvRamAccessSize
    0,                                    //  ReceiveFilterMask
    0,                                    //  ReceiveFilterSetting
    MAX_MCAST_FILTER_CNT,                 //  MaxMCastFilterCount
    0,                                    //  MCastFilterCount
    {
      { { 0 } }
    },                                    //  MCastFilter
    {
      { 0 }
    },                                    //  CurrentAddress
    {
      { 0 }
    },                                    //  BroadcastAddress
    {
      { 0 }
    },                                    //  PermanentAddress
    NET_IFTYPE_ETHERNET,                  //  IfType
    FALSE,                                //  MacAddressChangeable
    FALSE,                                //  MultipleTxSupported
    TRUE,                                 //  MediaPresentSupported
    TRUE                                  //  MediaPresent
  },
  {
    0
  }                                       //  InterfaceInfo
};

/**
  Disable the ethnet
**/
VOID
EFIAPI
ExitBootServicesEvent (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  SNP_GLOBAL_DATA   *This = Context;
  SNP_INSTANCE_DATA *Instance;
  LIST_ENTRY        *Entry = NULL;

  Entry = GetFirstNode(&This->InstanceList);
  while (!IsNull(&This->InstanceList, Entry)) {
    Instance  = NET_LIST_USER_STRUCT_S (Entry, SNP_INSTANCE_DATA, Entry, SNP_INSTANCE_SIGNATURE);
    SNPDBG("Closing interfaceIndex:%d\n", Instance->InterfaceInfo.InterfaceIndex);
    Mellanox_Halt (Instance->InterfaceInfo.InterfaceIndex, Instance->PrivateData);
    Entry = GetNextNode(&This->InstanceList, Entry);
  }
}

/**
  Initialize the driver's global data.

  @param  This                  Pointer to the global context data.

  @retval EFI_SUCCESS           The global data is initialized.
  @retval EFI_NOT_FOUND         The required DLL is not found.
  @retval EFI_DEVICE_ERROR      Error initialize network utility library.
  @retval EFI_OUT_OF_RESOURCES  Out of resource.
  @retval other                 Other errors.

**/
EFI_STATUS
SnpDxeInitializeGlobalData (
  IN EFI_PCI_IO_PROTOCOL    *PciIo,
  IN OUT SNP_GLOBAL_DATA    *This
  )
{
  EFI_STATUS            Status;

  SNPDBG("Enter SnpDxeInitializeGlobalData\n");

  ASSERT (This != NULL);

  InitializeListHead (&This->InstanceList);
  EfiInitializeLock (&This->Lock, TPL_CALLBACK);

  /* Pointer to Mellanox network utility */
  This->NtNetUtilityTable.Initialize = Mellanox_Initialize;

  if (NULL == This->NtNetUtilityTable.Initialize) {
    Status = EFI_NOT_FOUND;
    goto ErrorReturn;
  }

  This->NtNetUtilityTable.Finalize = Mellanox_Finalize;

  if (NULL == This->NtNetUtilityTable.Finalize) {
    Status = EFI_NOT_FOUND;
    goto ErrorReturn;
  }

  This->NtNetUtilityTable.SetReceiveFilter = Mellanox_Set_Receive_Filter;

  if (NULL == This->NtNetUtilityTable.SetReceiveFilter) {
    Status = EFI_NOT_FOUND;
    goto ErrorReturn;
  }

  This->NtNetUtilityTable.Receive = Mellanox_Receive;

  if (NULL == This->NtNetUtilityTable.Receive) {
    Status = EFI_NOT_FOUND;
    goto ErrorReturn;
  }

  This->NtNetUtilityTable.Transmit = Mellanox_Transmit;

  if (NULL == This->NtNetUtilityTable.Transmit) {
    Status = EFI_NOT_FOUND;
    goto ErrorReturn;
  }

  NetUtilityLibInitDone = TRUE;

  // Register for an ExitBootServicesEvent
  Status = gBS->CreateEvent (EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_NOTIFY,
			     ExitBootServicesEvent, This, &EfiExitBootServicesEvent);
  ASSERT_EFI_ERROR (Status);

  SNPDBG("Exit SnpDxeInitializeGlobalData\n");
  return EFI_SUCCESS;

ErrorReturn:
  SNPDBG("SnpDxeInitializeGlobalData Err Status = 0x%x\n", Status);

  return Status;
}

EFI_STATUS
SnpDxeInitializeMellanoxPci (
  IN EFI_PCI_IO_PROTOCOL    *PciIo,
  IN SNP_GLOBAL_DATA        *This
  )
{
  EFI_STATUS            Status;
  UINT32                Index;
  EFI_STATUS            ReturnValue;
  NET_INTERFACE_INFO    NetInterfaceInfoBuffer[MAX_INTERFACE_INFO_NUMBER];
  SNP_INSTANCE_DATA     *Instance;
  UINT32                InterfaceCount;
  VOID                  *PrivateData;

  //
  //  Initialize the network utility library
  //  And enumerate the interfaces in NT32 host
  //
  InterfaceCount = MAX_INTERFACE_INFO_NUMBER;
  ReturnValue = This->NtNetUtilityTable.Initialize (PciIo, &InterfaceCount, &NetInterfaceInfoBuffer[0], &PrivateData);
  if (EFI_ERROR(ReturnValue)) {
    Status = EFI_DEVICE_ERROR;
    goto ErrorReturn;
  }

  if (InterfaceCount == 0) {
    Status = EFI_NOT_FOUND;
    goto ErrorReturn;
  }
  //
  //  Create SNP instances
  //
  for (Index = 0; Index < InterfaceCount; Index++) {

    Instance = AllocatePool (sizeof (SNP_INSTANCE_DATA));

    if (NULL == Instance) {
     Status = EFI_OUT_OF_RESOURCES;
     goto ErrorReturn;
    }
    //
    //  Copy the content from a template
    //
    CopyMem (Instance, &gSnpDxeInstanceTemplate, sizeof (SNP_INSTANCE_DATA));

    Instance->Snp.Mode = &Instance->Mode;

    //
    //  Set the interface information.
    //
    CopyMem ((void *)&(Instance->InterfaceInfo), &NetInterfaceInfoBuffer[Index],
             sizeof(NetInterfaceInfoBuffer[Index]));
    //
    //  Initialize this instance
    //
    Status = This->InitializeInstanceData (This, Instance);
    if (EFI_ERROR (Status)) {
      gBS->FreePool (Instance);
      goto ErrorReturn;
    }
    Instance->PrivateData = PrivateData;
    //
    //  Insert this instance into the instance list
    //
    InsertTailList (&This->InstanceList, &Instance->Entry);
  }

  return EFI_SUCCESS;

ErrorReturn:
  SNPDBG("SnpDxeInitializeMellanoxPci Err Status = 0x%x\n", Status);

  return Status;
}

/**
  Initialize the snpdxe driver instance.

  @param  This                  Pointer to the SnpNt32 global data.
  @param  Instance              Pointer to the instance context data.

  @retval EFI_SUCCESS           The driver instance is initialized.
  @retval other                 Initialization errors.

**/
EFI_STATUS
SnpDxeInitializeInstanceData (
  IN SNP_GLOBAL_DATA        *This,
  IN OUT SNP_INSTANCE_DATA  *Instance
  )
{
  EFI_STATUS    Status;
  EFI_DEV_PATH  EndNode;
  EFI_DEV_PATH  Node;

  SNPDBG("Enter SnpDxeInitializeInstanceData\n");

  Instance->GlobalData  = This;
  Instance->Snp.Mode    = &Instance->Mode;
  //
  //  Set broadcast address
  //
  SetMem (&Instance->Mode.BroadcastAddress, sizeof (EFI_MAC_ADDRESS), 0xFF);

  //
  //  Copy Current/PermanentAddress MAC address
  //
  SNPDBG(" SnpDxeInitializeInstanceData PrivateData:%p interface=%d\n", Instance->PrivateData, Instance->InterfaceInfo.InterfaceIndex);

  CopyMem (
    &Instance->Mode.CurrentAddress,
    &Instance->InterfaceInfo.MacAddr,
    NET_ETHER_ADDR_LEN
    );
  CopyMem (
    &Instance->Mode.PermanentAddress,
    &Instance->InterfaceInfo.MacAddr,
    NET_ETHER_ADDR_LEN
    );

  //
  //  Create a device path for the instance
  //
  ZeroMem (&Node, sizeof (Node));

  Node.DevPath.Type     = MESSAGING_DEVICE_PATH;
  Node.DevPath.SubType  = MSG_MAC_ADDR_DP;
  SetDevicePathNodeLength (&Node.DevPath, sizeof (MAC_ADDR_DEVICE_PATH));

  CopyMem (
    &Node.MacAddr.MacAddress,
    &Instance->Mode.CurrentAddress,
    NET_ETHER_ADDR_LEN
    );

  Node.MacAddr.IfType = Instance->Mode.IfType;

  SetDevicePathEndNode (&EndNode.DevPath);

  Instance->DevicePath = AppendDevicePathNode (
                           &EndNode.DevPath,
                           &Node.DevPath
                           );

  //
  //  Create a device handle for the SNP
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Instance->DeviceHandle,
                  &gEfiSimpleNetworkProtocolGuid,
                  &Instance->Snp,
                  &gEfiDevicePathProtocolGuid,
                  Instance->DevicePath,
                  NULL
                  );
  return Status;
}

/**
  Close the SnpDxe driver instance.

  @param  This                  Pointer to the SnpNt32 global data.
  @param  Instance              Pointer to the instance context data.

  @retval EFI_SUCCESS           The instance is closed.

**/
EFI_STATUS
SnpDxeCloseInstance (
  IN SNP_GLOBAL_DATA        *This,
  IN OUT SNP_INSTANCE_DATA  *Instance
  )
{
  SNPDBG("Enter SnpDxeCloseInstance\n");

  ASSERT (This != NULL);
  ASSERT (Instance != NULL);

  gBS->UninstallMultipleProtocolInterfaces (
         Instance->DeviceHandle,
         &gEfiSimpleNetworkProtocolGuid,
         &Instance->Snp,
         &gEfiDevicePathProtocolGuid,
         Instance->DevicePath,
         NULL
         );

  if (Instance->DevicePath != NULL) {
    gBS->FreePool (Instance->DevicePath);
  }

  return EFI_SUCCESS;
}

/**
  Unloads an image.

  @param  ImageHandle           Handle that identifies the image to be unloaded.

  @retval EFI_SUCCESS           The image has been unloaded.
  @return Exit code from the image's unload handler

**/
EFI_STATUS
EFIAPI
SnpDxeUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS            Status;
  SNP_GLOBAL_DATA   *This;
  LIST_ENTRY            *Entry;
  SNP_INSTANCE_DATA *Instance;

  SNPDBG("Enter SnpDxeUnload\n");

  This    = &gSnpDxeGlobalData;

  Status  = NetLibDefaultUnload (ImageHandle);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  while (!IsListEmpty (&This->InstanceList)) {
    //
    //  Walkthrough the interfaces and remove all the SNP instance
    //
    Entry     = This->InstanceList.ForwardLink;

    Instance  = NET_LIST_USER_STRUCT_S (Entry, SNP_INSTANCE_DATA, Entry, SNP_INSTANCE_SIGNATURE);

    RemoveEntryList (Entry);

    if (This->NtNetUtilityTable.Finalize != NULL) {
      This->NtNetUtilityTable.Finalize (Instance->PrivateData);
    }

    This->CloseInstance (This, Instance);
    gBS->FreePool (Instance);
  }


  return EFI_SUCCESS;
}

/**
  This is the declaration of an EFI image entry point. This entry pointer is
  the same for UEFI Applications, UEFI OS Loaders, and UEFI Drivers including
  both device drivers and bus drivers.

  @param  ImageHandle           The firmware allocated handle for the UEFI image.
  @param  SystemTable           A pointer to the EFI System Table.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack of resources.

**/
EFI_STATUS
InitializeSnpDxeDriver (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;

  SNPDBG("Enter InitializeSnpDxeDriver\n");

  //
  // Install the Driver Protocols
  //

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gSnpDxeBinding,
             ImageHandle,
             &gSnpDxeComponentName,
             &gSnpDxeComponentName2
             );

  return Status;
}
