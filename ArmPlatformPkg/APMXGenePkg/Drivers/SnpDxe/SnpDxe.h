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

#ifndef _SNPDXE_H_
#define _SNPDXE_H_

#include <Uefi.h>

#include <Protocol/SimpleNetwork.h>
#include <Protocol/DevicePath.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/NetLib.h>
#include <Library/MemoryAllocationLib.h>

#define APMNET_DBG

#ifdef APMNET_DBG
#define DBG(arg...) DEBUG ((EFI_D_NET,## arg))
#else
#define DBG(arg...)
#endif

#ifdef APM_XGENE
#include "ethernet/apm_enet_access.h"
extern int apm_eth_initialize(int index, u8* mac_addr);
extern struct eth_device *emac_dev[];
extern int apm_eth_tx(struct eth_device *dev, volatile void *ptr, int len);
extern UINT32 eth_initialized;
extern int putshex(unsigned char *buf, int len);
#endif

typedef struct _SNP_GLOBAL_DATA  SNP_GLOBAL_DATA;
typedef struct _SNP_INSTANCE_DATA SNP_INSTANCE_DATA;

/* FIXME: Do we need pack attribute here ? */
#pragma pack(1)
typedef struct _NET_INTERFACE_INFO {
  UINT32          InterfaceIndex;
  EFI_MAC_ADDRESS MacAddr;
} NET_INTERFACE_INFO;
#pragma pack()

#define NET_ETHER_HEADER_SIZE           14

#define MAX_INTERFACE_INFO_NUMBER       16
#define MAX_FILE_NAME_LENGTH            280

//
//  Functions in Net Library
//
typedef
EFI_STATUS
(*NET_INITIALIZE) (
  IN OUT  UINT32                       *InterfaceCount,
  IN OUT  NET_INTERFACE_INFO           *InterfaceInfoBuffer
  );

typedef
EFI_STATUS
(*NET_FINALIZE) (
  VOID
  );

typedef
EFI_STATUS
(*NET_SET_RECEIVE_FILTER) (
  IN  UINT32                           Index,
  IN  UINT32                           EnableFilter,
  IN  UINT32                           MCastFilterCnt,
  IN  EFI_MAC_ADDRESS                  * MCastFilter
  );

typedef
EFI_STATUS
(*NET_RECEIVE) (
  IN      UINT32                      Index,
//TODO   IN OUT  UINT32                      *BufferSize,
 IN OUT  UINTN                      *BufferSize,
  OUT     VOID                        *Buffer
  );

typedef
EFI_STATUS
(*NET_TRANSMIT) (
  IN  UINT32                          Index,
  IN  UINT32                          HeaderSize,
  IN  UINT32                          BufferSize,
  IN  VOID                            *Buffer,
  IN  EFI_MAC_ADDRESS                 * SrcAddr,
  IN  EFI_MAC_ADDRESS                 * DestAddr,
  IN  UINT16                          *Protocol
  );

typedef struct _NET_UTILITY_TABLE {
  NET_INITIALIZE         Initialize;
  NET_FINALIZE           Finalize;
  NET_SET_RECEIVE_FILTER SetReceiveFilter;
  NET_RECEIVE            Receive;
  NET_TRANSMIT           Transmit;
} NET_UTILITY_TABLE;

//
//  Private functions
//
typedef
EFI_STATUS
(*SNP_INITIALIZE_GLOBAL_DATA) (
  IN SNP_GLOBAL_DATA * This
  );

typedef
EFI_STATUS
(*SNP_INITIALIZE_INSTANCE_DATA) (
  IN SNP_GLOBAL_DATA    * This,
  IN SNP_INSTANCE_DATA  * Instance
  );

typedef
EFI_STATUS
(*SNP_CLOSE_INSTANCE) (
  IN SNP_GLOBAL_DATA    * This,
  IN SNP_INSTANCE_DATA  * Instance
  );

//
//  Global data for this driver
//
#define SNP_DRIVER_SIGNATURE SIGNATURE_32 ('W', 'S', 'N', 'P')
#define TX_QUEUE_DEPTH 16

struct _SNP_GLOBAL_DATA {
  UINT32                            Signature;

  //
  //  List for all the fake SNP instance
  //
  LIST_ENTRY                        InstanceList;


  NET_UTILITY_TABLE                 NtNetUtilityTable;

  EFI_LOCK                          Lock;

  // Keep track of transmitted buffers for GetStatus
  VOID              *TxQueue[TX_QUEUE_DEPTH];
  UINTN             TxQueHead;
  UINTN             TxQueTail;

  //
  //  Private functions
  //
  SNP_INITIALIZE_GLOBAL_DATA        InitializeGlobalData;
  SNP_INITIALIZE_INSTANCE_DATA      InitializeInstanceData;
  SNP_CLOSE_INSTANCE                CloseInstance;
};

//
//  Instance data for each fake SNP instance
//
#define SNP_INSTANCE_SIGNATURE SIGNATURE_32 ('w', 'S', 'N', 'P')

struct _SNP_INSTANCE_DATA {
  UINT32                            Signature;

  //
  //  List entry use for linking with other instance
  //
  LIST_ENTRY                        Entry;

  SNP_GLOBAL_DATA                   *GlobalData;

  EFI_HANDLE                        DeviceHandle;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;

  EFI_SIMPLE_NETWORK_PROTOCOL       Snp;
  EFI_SIMPLE_NETWORK_MODE           Mode;

  NET_INTERFACE_INFO                InterfaceInfo;

  //
  //  Private functions
  //
};

#define SNP_INSTANCE_DATA_FROM_SNP_THIS(a) \
  CR ( \
  a, \
  SNP_INSTANCE_DATA, \
  Snp, \
  SNP_INSTANCE_SIGNATURE \
  )

extern EFI_DRIVER_BINDING_PROTOCOL    gSnpDxeBinding;
extern EFI_COMPONENT_NAME_PROTOCOL    gSnpDxeComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL   gSnpDxeComponentName2;

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
  );

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
  );

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
  );

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
  IN OUT SNP_GLOBAL_DATA *This
  );

/**
  Initialize the SNP driver instance.

  @param  This                  Pointer to the SNP global data.
  @param  Instance              Pointer to the instance context data.

  @retval EFI_SUCCESS           The driver instance is initialized.
  @retval other                 Initialization errors.

**/
EFI_STATUS
SnpDxeInitializeInstanceData (
  IN SNP_GLOBAL_DATA        *This,
  IN OUT SNP_INSTANCE_DATA  *Instance
  );

/**
  Close the SNP driver instance.

  @param  This                  Pointer to the SNP global data.
  @param  Instance              Pointer to the instance context data.

  @retval EFI_SUCCESS           The instance is closed.

**/
EFI_STATUS
SnpDxeCloseInstance (
  IN SNP_GLOBAL_DATA        *This,
  IN OUT SNP_INSTANCE_DATA  *Instance
  );

#endif /* _SNPDXE_H_ */
