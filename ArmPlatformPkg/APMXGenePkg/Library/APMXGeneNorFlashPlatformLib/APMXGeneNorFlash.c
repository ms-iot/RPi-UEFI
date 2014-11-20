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

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/NorFlashPlatformLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Guid/GlobalVariable.h>
#include <Guid/EventGroup.h>

#include <ArmPlatform.h>
#include <APMXGeneGFCCsr.h>
#include <DWSPICsr.h>

#ifdef APM_XGENE_GFC_FLASH
#define NOR_FLASH_DEVICE_COUNT	3

#define _apmGfcWrite(a,d) 	MmioWrite32((a), (d))
#define _apmGfcRead(a) 		MmioRead32((a))


void apmGfcWrite32(UINT64 offset, UINT32 data)
{
  _apmGfcWrite(APM_XGENE_GFC_BASE + offset, data);
}

UINT32 apmGfcRead32(UINT64 offset)
{
  return _apmGfcRead(APM_XGENE_GFC_BASE + offset);
}

/**
 * Disable all default Banks address to prevent multibank error,
 * by using End address smaller than Start address
 */
static void apmGfc_disable_all_banks(void) 
{
  int bank_id;

  for (bank_id = BANK0; bank_id < 6; bank_id++) {
    apmGfcWrite32(GFC_BANK0_START_ADD_ADDR + (bank_id << 12), 1);
    apmGfcWrite32(GFC_BANK0_END_ADD_ADDR + (bank_id << 12), 0);
  }
}

EFI_STATUS apmGfcNorInit(void)
{
  UINT64 norStartAddr, norEndAddr;
  UINT64 norWidth;
  UINT32 reg;
  EFI_STATUS Status;
  UINT64 BaseAddress;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR Descriptor;


  norWidth = 8 * APM_XGENE_SYS_FLASH_CFI_WIDTH; /* norWidth in bits */
  norStartAddr = APM_XGENE_NOR0_BASE;
  norEndAddr =  APM_XGENE_NOR0_BASE + APM_XGENE_SYS_FLASH_LEN;
  if ((norWidth != 8) && (norWidth != 16)) {
    DEBUG((EFI_D_ERROR, "valid values for nor-width: 8, 16\n"));
    return EFI_DEVICE_ERROR;
  }

  if (norStartAddr >= norEndAddr) {
    DEBUG((EFI_D_ERROR, "norStartAddr >= norEndAddr\n"));
    return EFI_DEVICE_ERROR;
  }

  DEBUG((EFI_D_INFO, "NOR: PADDR 0x%p - 0x%p", 
	(VOID *) norStartAddr, (VOID *) norEndAddr));

  BaseAddress = norStartAddr;
  Status = gDS->GetMemorySpaceDescriptor (BaseAddress, &Descriptor);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "GetMemorySpaceDescriptor fail - %r!\n", Status));
    return EFI_DEVICE_ERROR;
  }

  Status = gDS->SetMemorySpaceAttributes (
                  BaseAddress,
                  norEndAddr - norStartAddr,
                  Descriptor.Attributes | EFI_MEMORY_RUNTIME
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "SetMemorySpaceAttributes fail - %r!\n", Status));
    return EFI_DEVICE_ERROR;
  }


  apmGfc_disable_all_banks();

  // Set address for valid Banks Bank0
  apmGfcWrite32(GFC_BANK0_START_ADD_ADDR, 0x0);
  apmGfcWrite32(GFC_BANK0_END_ADD_ADDR, 0x1000);
  apmGfcWrite32(GFC_BANK0_BASE_ADD_ADDR, 0x0);

  // Set up bank information
  reg = apmGfcRead32(GFC_BANK0_CTRL0_ADDR);
  apmGfcWrite32(GFC_BANK0_CTRL0_ADDR, (reg & 0xfffffc00) |
                (BANKVALID | NOR <<1 | READ_WRITE << 4 | BUS_WIDTH_16 << 6) |
                0x1 << 9);

  reg = apmGfcRead32(GFC_BANK0_CTRL0_ADDR + 4);
  apmGfcWrite32(GFC_BANK0_CTRL0_ADDR + 4, (reg | 0x3));

  // Set up timing parameter
  apmGfcWrite32(GFC_BANK0_SRAM_CTRL0_ADDR, 0x0);

#if 0
  reg = apmGfcRead32(GFC_BANK0_SRAM_NOR_CTRL1_ADDR);
  apmGfcWrite32(GFC_BANK0_SRAM_NOR_CTRL1_ADDR, (reg & 0x60080c00) | 
                (twt | fwt << 12 | bwt << 20 | alh << 25 | burst_en << 31));
		
  reg = apmGfcRead32(GFC_BANK0_SRAM_NOR_CTRL2_ADDR);
  apmGfcWrite32(GFC_BANK0_SRAM_NOR_CTRL2_ADDR, (reg & 0xfe00000) | 
                (csn | oen << 4 | wbn << 8 | wbf << 12 | th << 16 | aln << 28));
#endif

  return EFI_SUCCESS;
}

NOR_FLASH_DESCRIPTION mNorFlashDevices[NOR_FLASH_DEVICE_COUNT] = {
  { 
    APM_XGENE_NOR0_BASE,
    APM_XGENE_NOR0_BASE,
    SIZE_32KB * 4,
    SIZE_32KB,
    {0x6C9CEEF0, 0xA406, 0x11E3, {0xA5, 0xE2, 0x08, 0x00, 0x20, 0x0C, 0x9A, 0x66}}
  },
  { 
    APM_XGENE_NOR0_BASE,
    APM_XGENE_NOR0_BASE + SIZE_32KB * 4,
    SIZE_128KB * 254,
    SIZE_128KB,
    {0x02118005, 0x9DA7, 0x443A, {0x92, 0xD5, 0x78, 0x1F, 0x02, 0x2A, 0xED, 0xBB}}
  },
  { 
    APM_XGENE_NOR0_BASE,
    APM_XGENE_NOR0_BASE + SIZE_32KB * 4 + SIZE_128KB * 254,
    SIZE_32KB * 4,
    SIZE_32KB,
    {0xF40A3869, 0x92C4, 0x4275, {0x85, 0x01, 0x44, 0x91, 0xA1, 0xA2, 0x0C, 0x19}}
  },
};

EFI_STATUS
NorFlashPlatformInitialization (
  VOID
  )
{
  return apmGfcNorInit();
}

EFI_STATUS
NorFlashPlatformGetDevices (
  OUT NOR_FLASH_DESCRIPTION   **NorFlashDevices,
  OUT UINT32                  *Count
  )
{
  if ((NorFlashDevices == NULL) || (Count == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *NorFlashDevices = mNorFlashDevices;
  *Count = NOR_FLASH_DEVICE_COUNT;
  
  return EFI_SUCCESS;
}
#else /* APM_XGENE_SPI_FLASH */

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SPIFlash.h>

#define NOR_FLASH_DEVICE_COUNT 3

struct SPI_FLASH *Spi_Flash;
EFI_EVENT  mSpiNorVirtualAddressChangeEvent = NULL;

NOR_FLASH_DESCRIPTION mNorFlashDevices[NOR_FLASH_DEVICE_COUNT] = {
  {
    0,
    0x0,
    SIZE_128KB * 64,
    SIZE_128KB,
    {0x6C9CEEF0, 0xA406, 0x11E3, {0xA5, 0xE2, 0x08, 0x00, 0x20, 0x0C, 0x9A, 0x66}}
  },
  {
    0,
    0x800000,
    SIZE_128KB * 8,
    SIZE_128KB,
    {0x02118005, 0x9DA7, 0x443A, {0x92, 0xD5, 0x78, 0x1F, 0x02, 0x2A, 0xED, 0xBB}}
  },
  {
    0,
    0x900000,
    SIZE_128KB * 184,
    SIZE_128KB,
    {0xF40A3869, 0x92C4, 0x4275, {0x85, 0x01, 0x44, 0x91, 0xA1, 0xA2, 0x0C, 0x19}}
  },
};

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It convers pointer to new virtual address.

  @param  Event        Event whose notification function is being invoked.
  @param  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
SpiNorVariableClassAddressChangeEvent (
  IN EFI_EVENT                            Event,
  IN VOID                                 *Context
  )
{
  EfiConvertPointer (0x0, (VOID **) &Spi_Flash->Read);
  EfiConvertPointer (0x0, (VOID **) &Spi_Flash->Write);
  EfiConvertPointer (0x0, (VOID **) &Spi_Flash->Erase);
  EfiConvertPointer (0x0, (VOID **) &Spi_Flash->Name);
  EfiConvertPointer (0x0, (VOID **) &Spi_Flash->Params);
  EfiConvertPointer (0x0, (VOID **) &Spi_Flash);
}

EFI_STATUS
NorFlashPlatformInitialization (
  VOID
  )
{
  EFI_STATUS Status;
  UINT64     BaseAddress;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR Descriptor;
  Spi_Flash = AllocateRuntimeZeroPool(sizeof(struct SPI_FLASH));
  if (Spi_Flash == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  DEBUG((EFI_D_BLKIO, "Spi_Flash: 0x%p\n", Spi_Flash));

  /* Allocate page that need for runtime service */
  BaseAddress = PcdGet64(PcdDWSpiBaseAddress);

  Status = gDS->GetMemorySpaceDescriptor (BaseAddress, &Descriptor);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "GetMemorySpaceDescriptor fail - %r!\n", Status));
    return EFI_DEVICE_ERROR;
  }

  Status = gDS->SetMemorySpaceAttributes (
                  BaseAddress,
                  DWSPI_CSR_SIZE,
                  Descriptor.Attributes | EFI_MEMORY_RUNTIME
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "SetMemorySpaceAttributes fail - %r!\n", Status));
    return EFI_DEVICE_ERROR;
  }

  Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    SpiNorVariableClassAddressChangeEvent,
                    NULL,
                    &gEfiEventVirtualAddressChangeGuid,
                    &mSpiNorVirtualAddressChangeEvent
                    );
  ASSERT_EFI_ERROR (Status);

  //SetMem((VOID*)&Spi_Flash, sizeof(struct SPI_FLASH), 0);
  if (Spi_Flash_Probe(Spi_Flash, PcdGet32(PcdSPIFlashBus),
          PcdGet32(PcdSPIFlashCS), PcdGet32(PcdSPIFlashMaxHz), SPI_MODE_3)) {
    return EFI_SUCCESS;
  }


  DEBUG((EFI_D_BLKIO, "Spi_Flash_Probe error\n"));
  FreePool((VOID *)Spi_Flash);
  return EFI_DEVICE_ERROR;
}

EFI_STATUS
NorFlashPlatformGetDevices (
  OUT NOR_FLASH_DESCRIPTION   **NorFlashDevices,
  OUT UINT32                  *Count
  )
{
  if ((NorFlashDevices == NULL) || (Count == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *NorFlashDevices = mNorFlashDevices;
  *Count = NOR_FLASH_DEVICE_COUNT;

  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashPlatformRead (
  IN  UINT32 Offset,
  IN  VOID *Buffer,
  IN  UINT32 Len
  )
{
  ASSERT (Spi_Flash);
  DEBUG((EFI_D_BLKIO, "NorFlashPlatformRead:Buffer:0x%p Offset: 0x%x Len:0x%x\n", Buffer, Offset, Len));
  DEBUG((EFI_D_BLKIO, "Spi_Flash: 0x%p\n", Spi_Flash));
  return Spi_Flash->Read(Spi_Flash, Offset,
      Len, (VOID *)Buffer);
}

EFI_STATUS
NorFlashPlatformWrite (
  IN  UINT32 Offset,
  IN  VOID *Buffer,
  IN  UINT32 Len
  )
{
  ASSERT (Spi_Flash);
  DEBUG((EFI_D_BLKIO, "NorFlashPlatformWrite:Offset: 0x%x Len:0x%x\n", Offset, Len));
  return Spi_Flash->Write(Spi_Flash, Offset,
      Len, (CONST VOID *)Buffer);
}

EFI_STATUS
NorFlashPlatformErase (
  IN  UINT32 Offset,
  IN  UINT32 Len
  )
{
  ASSERT (Spi_Flash);
  DEBUG((EFI_D_BLKIO, "NorFlashPlatformErase:Offset: 0x%x Len:0x%x\n", Offset, Len));
  return Spi_Flash->Erase(Spi_Flash, Offset,
        Len);
}

#endif
