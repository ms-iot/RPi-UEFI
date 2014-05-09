/*++
 FVB DXE Driver

Copyright (c) 2012, Samsung Inc. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the
BSD License which accompanies this distribution.  The full text of the
license may be found at http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.


--*/

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Protocol/FirmwareVolumeBlock.h>
#include <Protocol/BlockIo.h>
#include <Library/MemoryAllocationLib.h>


//#undef EFI_D_INFO
//#define EFI_D_INFO 1

EFI_FVB_ATTRIBUTES_2 gAttribute = (EFI_FVB2_READ_STATUS|EFI_FVB2_WRITE_STATUS|EFI_FVB2_ALIGNMENT_32);
EFI_BLOCK_IO_PROTOCOL *BlockIo;
EFI_EVENT mBlockIORegistration = NULL;
EFI_HANDLE mHandle  = NULL;
UINT32 TargetMediaId;

#define EMMC_BLOCK_SIZE 512
#define EMMC_BLOCK_NUMBER 512
#define MSHC_BOOT_NV_OFFSET 0x1000
#define NV_READ_BUFFER_SIZE    0x20000
#define FVB_HEADER_LEN  0x64
#define DMA_BUFFER_NV_OFFSET    0x60000

VOID *BufPtr;
VOID *ReadBufPtr;

#define FVB_TEST 0 
//VOID *TestBufPtr;

/**
  The GetAttributes() function retrieves the attributes and
  current settings of the block.

  @param This       Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL instance.

  @param Attributes Pointer to EFI_FVB_ATTRIBUTES_2 in which the
                    attributes and current settings are
                    returned. Type EFI_FVB_ATTRIBUTES_2 is defined
                    in EFI_FIRMWARE_VOLUME_HEADER.

  @retval EFI_SUCCESS The firmware volume attributes were
                      returned.

**/

EFI_STATUS
EFIAPI
FvbGetAttributes (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  OUT       EFI_FVB_ATTRIBUTES_2                *Attributes
  )
{
    *Attributes = gAttribute;
    DEBUG ((EFI_D_INFO, "FVB:FvbGetAttributes 0x%x\n",  gAttribute));
    return EFI_SUCCESS;
}


/**
  The SetAttributes() function sets configurable firmware volume
  attributes and returns the new settings of the firmware volume.


  @param This        Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL instance.

  @param Attributes   On input, Attributes is a pointer to
                      EFI_FVB_ATTRIBUTES_2 that contains the
                      desired firmware volume settings. On
                      successful return, it contains the new
                      settings of the firmware volume. Type
                      EFI_FVB_ATTRIBUTES_2 is defined in
                      EFI_FIRMWARE_VOLUME_HEADER.

  @retval EFI_SUCCESS           The firmware volume attributes were returned.

  @retval EFI_INVALID_PARAMETER The attributes requested are in
                                conflict with the capabilities
                                as declared in the firmware
                                volume header.

**/
EFI_STATUS
EFIAPI
FvbSetAttributes (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN OUT    EFI_FVB_ATTRIBUTES_2                *Attributes
  )
{
    gAttribute |= *Attributes;
    *Attributes = gAttribute;
    DEBUG ((EFI_D_INFO, "FVB:FvbSetAttributes 0x%x\n",  gAttribute));
    return EFI_SUCCESS;
}


/**
  The GetPhysicalAddress() function retrieves the base address of
  a memory-mapped firmware volume. This function should be called
  only for memory-mapped firmware volumes.

  @param This     Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL instance.

  @param Address  Pointer to a caller-allocated
                  EFI_PHYSICAL_ADDRESS that, on successful
                  return from GetPhysicalAddress(), contains the
                  base address of the firmware volume.

  @retval EFI_SUCCESS       The firmware volume base address was returned.

  @retval EFI_NOT_SUPPORTED The firmware volume is not memory mapped.

**/
EFI_STATUS
EFIAPI
FvbGetPhysicalAddress (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  OUT       EFI_PHYSICAL_ADDRESS                *Address
  )
{
    EFI_PHYSICAL_ADDRESS NVBase = PcdGet32(PcdFlashNvStorageVariableBase);
    //UINT32 NVSize = PcdGet32(PcdFlashNvStorageVariableSize);
    
    *Address = NVBase;
    //DEBUG ((EFI_D_INFO, "FVB:FvbGetPhysicalAddress Addr:0x%x\n", *Address));    
    return EFI_SUCCESS;
}



/**
  The GetBlockSize() function retrieves the size of the requested
  block. It also returns the number of additional blocks with
  the identical size. The GetBlockSize() function is used to
  retrieve the block map (see EFI_FIRMWARE_VOLUME_HEADER).


  @param This        Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL instance.

  @param Lba         Indicates the block for which to return the size.

  @param BlockSize   Pointer to a caller-allocated UINTN in which
                     the size of the block is returned.

  @param NumberOfBlocks Pointer to a caller-allocated UINTN in
                        which the number of consecutive blocks,
                        starting with Lba, is returned. All
                        blocks in this range have a size of
                        BlockSize.


  @retval EFI_SUCCESS             The firmware volume base address was returned.

  @retval EFI_INVALID_PARAMETER   The requested LBA is out of range.

**/
EFI_STATUS
EFIAPI
FvbGetBlockSize (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  OUT       UINTN                               *BlockSize,
  OUT       UINTN                               *NumberOfBlocks
  )
{
    EFI_STATUS status = EFI_SUCCESS;
    *BlockSize = EMMC_BLOCK_SIZE;
    *NumberOfBlocks = EMMC_BLOCK_NUMBER;
    DEBUG ((EFI_D_INFO, "FVB:FvbGetBlockSize numblocks:%d\n",  *NumberOfBlocks));
    return status;
}



/**
  Reads the specified number of bytes into a buffer from the specified block.

  The Read() function reads the requested number of bytes from the
  requested block and stores them in the provided buffer.
  Implementations should be mindful that the firmware volume
  might be in the ReadDisabled state. If it is in this state,
  the Read() function must return the status code
  EFI_ACCESS_DENIED without modifying the contents of the
  buffer. The Read() function must also prevent spanning block
  boundaries. If a read is requested that would span a block
  boundary, the read must read up to the boundary but not
  beyond. The output parameter NumBytes must be set to correctly
  indicate the number of bytes actually read. The caller must be
  aware that a read may be partially completed.

  @param This     Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL instance.

  @param Lba      The starting logical block index
                  from which to read.

  @param Offset   Offset into the block at which to begin reading.

  @param NumBytes Pointer to a UINTN. At entry, *NumBytes
                  contains the total size of the buffer. At
                  exit, *NumBytes contains the total number of
                  bytes read.

  @param Buffer   Pointer to a caller-allocated buffer that will
                  be used to hold the data that is read.

  @retval EFI_SUCCESS         The firmware volume was read successfully,
                              and contents are in Buffer.

  @retval EFI_BAD_BUFFER_SIZE Read attempted across an LBA
                              boundary. On output, NumBytes
                              contains the total number of bytes
                              returned in Buffer.

  @retval EFI_ACCESS_DENIED   The firmware volume is in the
                              ReadDisabled state.

  @retval EFI_DEVICE_ERROR    The block device is not
                              functioning correctly and could
                              not be read.

**/
UINT8 FVB_Header[100]={0xff,};

EFI_STATUS
EFIAPI
FvbRead (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  IN        UINTN                               Offset,
  IN OUT    UINTN                               *NumBytes,
  IN OUT    UINT8                               *Buffer
  )
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 NumBlock;
    UINT32 AllocSize = 0;
    EFI_LBA NV_Lba = Lba + MSHC_BOOT_NV_OFFSET;
    UINT32 NVBase = PcdGet32(PcdFlashNvStorageVariableBase);  
    
    DEBUG ((EFI_D_INFO, "FVB:FvbRead O:%d ",Offset));
    DEBUG ((EFI_D_INFO, "Lba:%d \n",Lba));    
    DEBUG ((EFI_D_INFO, "N:%d \n",*NumBytes));    

    // check invalid input parameter
    if(*NumBytes<=0){
      goto Exit;
    }
    if((*NumBytes-1)>=(MAX_ADDRESS-(UINTN)Buffer)){
      goto Exit;
    }

    // 1. Copy FVB header 
    CopyMem(&FVB_Header[0], (UINT8 *)NVBase, 100);

    // 2. calculate block number and allocate memory
    // 3. ReadBlock 
    if (0 == ((Offset + *NumBytes)%EMMC_BLOCK_SIZE)) 
    {
        NumBlock = ((Offset + *NumBytes)/EMMC_BLOCK_SIZE);
     } 
    else 
    {
    	NumBlock = ((Offset + *NumBytes)/EMMC_BLOCK_SIZE)+1;
     } 
    AllocSize = NumBlock*EMMC_BLOCK_SIZE;
    Status = BlockIo->ReadBlocks(BlockIo, BlockIo->Media->MediaId, NV_Lba, AllocSize, (UINT8 *)NVBase);

    if (((EFI_FIRMWARE_VOLUME_HEADER *)(UINTN)(NVBase))->Signature != EFI_FVH_SIGNATURE)
    {
        DEBUG ((EFI_D_ERROR, "FVB:FvbRead invalid header\n"));
        CopyMem((UINT8 *)NVBase, &FVB_Header[0], 100);
        goto Exit;
    }
    // 4. Copy read buffer to dest
    CopyMem(Buffer, (UINT8 *)(NVBase +Offset), *NumBytes);

    if(Status!=EFI_SUCCESS)
    {
        DEBUG ((EFI_D_ERROR, "FVB:FvbRead Failed %r\n",  Status));
        Status = EFI_ACCESS_DENIED;
    }
    
Exit:
    return Status;
}


/**
  Writes the specified number of bytes from the input buffer to the block.

  The Write() function writes the specified number of bytes from
  the provided buffer to the specified block and offset. If the
  firmware volume is sticky write, the caller must ensure that
  all the bits of the specified range to write are in the
  EFI_FVB_ERASE_POLARITY state before calling the Write()
  function, or else the result will be unpredictable. This
  unpredictability arises because, for a sticky-write firmware
  volume, a write may negate a bit in the EFI_FVB_ERASE_POLARITY
  state but cannot flip it back again.  Before calling the
  Write() function,  it is recommended for the caller to first call
  the EraseBlocks() function to erase the specified block to
  write. A block erase cycle will transition bits from the
  (NOT)EFI_FVB_ERASE_POLARITY state back to the
  EFI_FVB_ERASE_POLARITY state. Implementations should be
  mindful that the firmware volume might be in the WriteDisabled
  state. If it is in this state, the Write() function must
  return the status code EFI_ACCESS_DENIED without modifying the
  contents of the firmware volume. The Write() function must
  also prevent spanning block boundaries. If a write is
  requested that spans a block boundary, the write must store up
  to the boundary but not beyond. The output parameter NumBytes
  must be set to correctly indicate the number of bytes actually
  written. The caller must be aware that a write may be
  partially completed. All writes, partial or otherwise, must be
  fully flushed to the hardware before the Write() service
  returns.

  @param This     Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL instance.

  @param Lba      The starting logical block index to write to.

  @param Offset   Offset into the block at which to begin writing.

  @param NumBytes The pointer to a UINTN. At entry, *NumBytes
                  contains the total size of the buffer. At
                  exit, *NumBytes contains the total number of
                  bytes actually written.

  @param Buffer   The pointer to a caller-allocated buffer that
                  contains the source for the write.

  @retval EFI_SUCCESS         The firmware volume was written successfully.

  @retval EFI_BAD_BUFFER_SIZE The write was attempted across an
                              LBA boundary. On output, NumBytes
                              contains the total number of bytes
                              actually written.

  @retval EFI_ACCESS_DENIED   The firmware volume is in the
                              WriteDisabled state.

  @retval EFI_DEVICE_ERROR    The block device is malfunctioning
                              and could not be written.


**/
EFI_STATUS
EFIAPI
FvbWrite (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  IN        EFI_LBA                             Lba,
  IN        UINTN                               Offset,
  IN OUT    UINTN                               *NumBytes,
  IN        UINT8                               *Buffer
  )
{  
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 NumBlock;
    UINT32 AllocSize = 0;
    EFI_LBA NV_Lba = Lba + MSHC_BOOT_NV_OFFSET;
    UINT32 NVBase = PcdGet32(PcdFlashNvStorageVariableBase);        

    DEBUG ((EFI_D_INFO, "FvbWrite O:%d\n ", Offset));
    DEBUG ((EFI_D_INFO, "FVB:FvbWrite O:%d ", Offset)); 
    DEBUG ((EFI_D_INFO, "N:%d ", *NumBytes));

    // 1. Calculate block count number
    if (0 == ((Offset+*NumBytes)%EMMC_BLOCK_SIZE)) 
    {
        NumBlock = ((Offset+*NumBytes)/EMMC_BLOCK_SIZE);
     } 
    else 
    {
    	NumBlock = ((Offset+*NumBytes)/EMMC_BLOCK_SIZE) + 1;
     } 
    AllocSize = (NumBlock * EMMC_BLOCK_SIZE);
    
    CopyMem((UINT8 *)(NVBase + Offset), Buffer, *NumBytes);
    
    // 4. Apply the offset and WriteBlock
   Status = BlockIo->WriteBlocks(BlockIo, TargetMediaId, NV_Lba, AllocSize, (VOID *)(NVBase));
    if(Status!=EFI_SUCCESS)
    {
        DEBUG ((EFI_D_ERROR, "FVB:FvbWrite Failed %r\n",  Status));
        Status = EFI_ACCESS_DENIED;
    }    

    return Status;
}


/**
  Erases and initializes a firmware volume block.

  The EraseBlocks() function erases one or more blocks as denoted
  by the variable argument list. The entire parameter list of
  blocks must be verified before erasing any blocks. If a block is
  requested that does not exist within the associated firmware
  volume (it has a larger index than the last block of the
  firmware volume), the EraseBlocks() function must return the
  status code EFI_INVALID_PARAMETER without modifying the contents
  of the firmware volume. Implementations should be mindful that
  the firmware volume might be in the WriteDisabled state. If it
  is in this state, the EraseBlocks() function must return the
  status code EFI_ACCESS_DENIED without modifying the contents of
  the firmware volume. All calls to EraseBlocks() must be fully
  flushed to the hardware before the EraseBlocks() service
  returns.

  @param This   Indicates the EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL
                instance.

  @param ...    The variable argument list is a list of tuples.
                Each tuple describes a range of LBAs to erase
                and consists of the following:
                - An EFI_LBA that indicates the starting LBA
                - A UINTN that indicates the number of blocks to
                  erase.

                The list is terminated with an
                EFI_LBA_LIST_TERMINATOR. For example, the
                following indicates that two ranges of blocks
                (5-7 and 10-11) are to be erased: EraseBlocks
                (This, 5, 3, 10, 2, EFI_LBA_LIST_TERMINATOR);

  @retval EFI_SUCCESS The erase request successfully
                      completed.

  @retval EFI_ACCESS_DENIED   The firmware volume is in the
                              WriteDisabled state.
  @retval EFI_DEVICE_ERROR  The block device is not functioning
                            correctly and could not be written.
                            The firmware device may have been
                            partially erased.
  @retval EFI_INVALID_PARAMETER One or more of the LBAs listed
                                in the variable argument list do
                                not exist in the firmware volume.

**/
EFI_STATUS
EFIAPI
FvbEraseBlocks (
  IN CONST  EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL *This,
  ...
  )
{
    DEBUG ((EFI_D_INFO, "FvbEraseBlocks\n"));
    return EFI_SUCCESS;
}


//
// Making this global saves a few bytes in image size
//
EFI_HANDLE  gFvbHandle = NULL;


///
/// The Firmware Volume Block Protocol is the low-level interface
/// to a firmware volume. File-level access to a firmware volume
/// should not be done using the Firmware Volume Block Protocol.
/// Normal access to a firmware volume must use the Firmware
/// Volume Protocol. Typically, only the file system driver that
/// produces the Firmware Volume Protocol will bind to the
/// Firmware Volume Block Protocol.
///
EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL gFvbProtocol = {
  FvbGetAttributes,
  FvbSetAttributes,
  FvbGetPhysicalAddress,
  FvbGetBlockSize,
  FvbRead,
  FvbWrite,
  FvbEraseBlocks,
  ///
  /// The handle of the parent firmware volume.
  ///
  NULL
};



/**
  Initialize the FVB to use block IO 


  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
VOID
EFIAPI
BlockIONotificationEvent (
  IN  EFI_EVENT                           Event,
  IN  VOID                                *Context
  )
{
    EFI_HANDLE *HandleBuffer = NULL;
    EFI_STATUS Status;
    UINTN NumHandles;
    UINT32 i;
    DEBUG((EFI_D_INFO, "FVB:BlockIONotificationEvent Start \n"));
    
    TargetMediaId = SIGNATURE_32('e','m','m','c');
    //TargetMediaId ++;
    DEBUG((EFI_D_INFO, "FVB:Target Device ID = 0x%x\n", TargetMediaId));
    
    if(mHandle!=NULL)
        return;

    Status = gBS->LocateHandleBuffer(ByProtocol, &gEfiBlockIoProtocolGuid, NULL, &NumHandles, &HandleBuffer);   
    
    for(i=0;i<NumHandles;i++) {
      Status = gBS->HandleProtocol(HandleBuffer[i], &gEfiBlockIoProtocolGuid, (VOID **)&BlockIo);

      DEBUG((EFI_D_INFO, "FVB:Device %d Media ID=0x%x\n", i, BlockIo->Media->MediaId));
  
      if((BlockIo->Media->MediaId == TargetMediaId)||(BlockIo->Media->MediaId == (TargetMediaId+1)))
      {
        DEBUG((EFI_D_INFO, "FVB:InstallFVBProtocol 0x%x \n", BlockIo));
        Status =  gBS->InstallMultipleProtocolInterfaces (
                      &mHandle,
                      &gEfiFirmwareVolumeBlockProtocolGuid,   &gFvbProtocol,
                      NULL
                      );

        if(Status!=EFI_SUCCESS)
        {
            DEBUG((EFI_D_ERROR, "FVB:BlockIO handle is not valid %r\n", Status));
        }

        break;
      }

    if(i == NumHandles) {
    DEBUG((EFI_D_ERROR, "Cannot find Block IO protocol handle! \n"));
  }
    }

}



/**
  Initialize the state information for the CPU Architectural Protocol

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
FvbDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS  Status=EFI_SUCCESS;
  
  //
  // Register FvbNotificationEvent () notify function.
  // 

    BlockIo = AllocatePool(sizeof(EFI_BLOCK_IO_PROTOCOL)+sizeof(EFI_BLOCK_IO_MEDIA));
    BufPtr = AllocatePool(EMMC_BLOCK_SIZE*2);
    if(BufPtr==NULL)
    {
        DEBUG ((EFI_D_ERROR, "FVB:Temp buffer allocate failed!!!\n"));
    }
    ReadBufPtr = AllocatePool(NV_READ_BUFFER_SIZE);
    if(ReadBufPtr==NULL)
    {
        DEBUG ((EFI_D_ERROR, "FVB:NV Read buffer allocate failed!!!\n"));
    }
#if FVB_TEST    
    TestBufPtr = AllocatePool(EMMC_BLOCK_SIZE*2);
    DEBUG ((EFI_D_ERROR, "FVB:TestBufPtr:0x%x ", TestBufPtr));
#endif     
    DEBUG ((EFI_D_ERROR, "BufPtr:0x%x\n", BufPtr));    
  
  EfiCreateProtocolNotifyEvent (
    &gEfiBlockIoProtocolGuid,
    TPL_CALLBACK,
    BlockIONotificationEvent,
    (VOID *)SystemTable,
    &mBlockIORegistration
    );
  
  DEBUG ((EFI_D_INFO, "\nFVB:FvbDxeInitialize\n"));

  // SetVertAddressEvent ()

  // GCD Map NAND as RT

  return Status;
}

