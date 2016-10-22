/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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


#include <PiDxe.h>

#include <BcmMailbox.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DevicePath.h>


typedef struct {
    VENDOR_DEVICE_PATH DisplayDevicePath;
    EFI_DEVICE_PATH EndDevicePath;
} DISPLAY_DEVICE_PATH;

DISPLAY_DEVICE_PATH gDisplayDevicePath =
{
    {
        {
            HARDWARE_DEVICE_PATH,
            HW_VENDOR_DP,
            {
                (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
                (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
            }
        },
        EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
    },
    {
        END_DEVICE_PATH_TYPE,
        END_ENTIRE_DEVICE_PATH_SUBTYPE,
        {
            sizeof(EFI_DEVICE_PATH_PROTOCOL),
            0
        }
    }
};

#define PI2_BITS_PER_PIXEL              (32)
#define PI2_BYTES_PER_PIXEL             (PI2_BITS_PER_PIXEL / 8)

#define PI2_COLOUR_BITS_PER_PIXEL       (24)
#define PI2_COLOUR_BYTES_PER_PIXEL      (PI2_COLOUR_BITS_PER_PIXEL / 8)


// Ensure 16 byte alignment
volatile MAILBOX_FRAMEBUFFER MbFb __attribute__ ((aligned (16)));
volatile MAILBOX_PHYSICAL_SIZE MbFbSize __attribute__((aligned(16)));

//
// Use the mailbox framebuffer channel mechanism to request a frame buffer
// Return non-zero for success
//
UINT32
MailboxTransactFrameBuffer(
    volatile PMAILBOX_FRAMEBUFFER pMbFb
    )
{
    UINT32 MBStatus = 0;
    UINT32 MBData = ((UINT32)pMbFb) | UNCACHED_ADDRESS_MASK;

    DEBUG((EFI_D_INIT, "DisplayDxe writing 0x%8.8X to Mailbox\n", MBData));

    WriteBackInvalidateDataCacheRange((void*)pMbFb, sizeof(*pMbFb));
    if (!BcmMailboxWrite(MAILBOX_CHANNEL_FRAMEBUFFER, MBData))
    {
        DEBUG((DEBUG_ERROR, "Failed to write FB info\n"));
    }

    DEBUG((EFI_D_INIT, "DisplayDxe wrote 0x%8.8X to Mailbox\n", MBData));

    // Wait for the completion on the FB channel
    if (!BcmMailboxRead(MAILBOX_CHANNEL_FRAMEBUFFER, &MBStatus))
    {
        DEBUG((DEBUG_ERROR, "FB info update fail to complete\n"));
    }

    DEBUG((EFI_D_INIT, "DisplayDxe Final MBStatus = 0x%8.8X\n", MBStatus));

    WriteBackInvalidateDataCacheRange((void*)pMbFb, sizeof(*pMbFb));

    DEBUG((EFI_D_INIT, "DisplayDxe FrameBuffer       = 0x%8.8X\n", pMbFb->mbf_framebuf_addr));
    DEBUG((EFI_D_INIT, "DisplayDxe FrameBuffer Size  = %d\n", pMbFb->mbf_framebuf_size));
    DEBUG((EFI_D_INIT, "DisplayDxe FrameBuffer Pitch = %d\n", pMbFb->mbf_pitch));

    if (pMbFb->mbf_framebuf_addr) {
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_phys_width    = %d\n", pMbFb->mbf_phys_width));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_phys_height   = %d\n", pMbFb->mbf_phys_height));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_virt_width    = %d\n", pMbFb->mbf_virt_width));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_virt_height   = %d\n", pMbFb->mbf_virt_height));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_pitch         = %d\n", pMbFb->mbf_pitch));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_depth         = %d\n", pMbFb->mbf_depth));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_x_offset      = %d\n", pMbFb->mbf_x_offset));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_y_offset      = %d\n", pMbFb->mbf_y_offset));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_framebuf_addr = 0x%8.8X\n", pMbFb->mbf_framebuf_addr));
        DEBUG((EFI_D_INIT, "DisplayDxe mbf_framebuf_size = 0x%8.8X\n", pMbFb->mbf_framebuf_size));
    }

    // Strip the GPU's 0xC0000000 from the address returned.
    pMbFb->mbf_framebuf_addr = pMbFb->mbf_framebuf_addr & ~UNCACHED_ADDRESS_MASK;

    return pMbFb->mbf_framebuf_addr;
}

EFI_STATUS
EFIAPI
DisplayQueryMode(
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  IN  UINT32                                ModeNumber,
  OUT UINTN                                 *SizeOfInfo,
  OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
  );

EFI_STATUS
EFIAPI
DisplaySetMode(
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
  IN  UINT32                       ModeNumber
  );

EFI_STATUS
EFIAPI
DisplayBlt(
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,   OPTIONAL
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta         OPTIONAL
  );

EFI_GRAPHICS_OUTPUT_PROTOCOL gDisplay = {
  DisplayQueryMode,
  DisplaySetMode,
  DisplayBlt,
  NULL
};


EFI_STATUS
EFIAPI
DisplayQueryMode(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
    IN  UINT32                                ModeNumber,
    OUT UINTN                                 *SizeOfInfo,
    OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
    )
{
    EFI_STATUS Status;

    Status = gBS->AllocatePool(
                    EfiBootServicesData,
                    sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION),
                    (VOID **)Info
                    );
    ASSERT_EFI_ERROR(Status);

    *SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);

    (*Info)->Version = This->Mode->Info->Version;
    (*Info)->HorizontalResolution = This->Mode->Info->HorizontalResolution;
    (*Info)->VerticalResolution = This->Mode->Info->VerticalResolution;
    (*Info)->PixelFormat = This->Mode->Info->PixelFormat;
    (*Info)->PixelsPerScanLine = This->Mode->Info->PixelsPerScanLine;

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DisplaySetMode(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN  UINT32                       ModeNumber
    )
{
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DisplayBlt(
    IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
    IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,   OPTIONAL
    IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
    IN  UINTN                                   SourceX,
    IN  UINTN                                   SourceY,
    IN  UINTN                                   DestinationX,
    IN  UINTN                                   DestinationY,
    IN  UINTN                                   Width,
    IN  UINTN                                   Height,
    IN  UINTN                                   Delta         OPTIONAL
    )
{
    UINT8 *VidBuf, *BltBuf, *VidBuf1;
    UINTN i, j;

    switch(BltOperation) {
    case EfiBltVideoFill:
        BltBuf = (UINT8 *)BltBuffer;

        for (i=0;i<Height;i++) {
            VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
                     (DestinationY + i)*This->Mode->Info->PixelsPerScanLine*PI2_BYTES_PER_PIXEL + \
                     DestinationX*PI2_BYTES_PER_PIXEL);

            for(j=0;j<Width;j++) {
                gBS->CopyMem((VOID *)VidBuf, (VOID *)BltBuf, PI2_COLOUR_BYTES_PER_PIXEL);
                VidBuf += PI2_BYTES_PER_PIXEL;
            }
        }
        break;

    case EfiBltVideoToBltBuffer:
        if (Delta == 0) {
          Delta = Width * PI2_BYTES_PER_PIXEL;
        }

        for (i=0;i<Height;i++) {
            VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
                     (SourceY + i)*This->Mode->Info->PixelsPerScanLine*PI2_BYTES_PER_PIXEL + \
                     SourceX*PI2_BYTES_PER_PIXEL);
            BltBuf = (UINT8 *)((UINT32)BltBuffer + (DestinationY + i)*Delta + DestinationX*PI2_BYTES_PER_PIXEL);

            for (j=0;j<Width;j++) {
                gBS->CopyMem((VOID *)BltBuf, (VOID *)VidBuf, PI2_COLOUR_BYTES_PER_PIXEL);
                VidBuf += PI2_BYTES_PER_PIXEL;
                BltBuf += PI2_BYTES_PER_PIXEL;
            }
        }
        break;

    case EfiBltBufferToVideo:
        if (Delta == 0) {
            Delta = Width * PI2_BYTES_PER_PIXEL;
        }

        for (i=0;i<Height;i++) {
            VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
                     (DestinationY + i)*This->Mode->Info->PixelsPerScanLine*PI2_BYTES_PER_PIXEL + \
                     DestinationX*PI2_BYTES_PER_PIXEL);
            BltBuf = (UINT8 *)((UINT32)BltBuffer + (SourceY + i)*Delta + SourceX*PI2_BYTES_PER_PIXEL);

            for (j=0;j<Width;j++) {
                gBS->CopyMem((VOID *)VidBuf, (VOID *)BltBuf, PI2_COLOUR_BYTES_PER_PIXEL);
                VidBuf += PI2_BYTES_PER_PIXEL;
                BltBuf += PI2_BYTES_PER_PIXEL;
            }
        }
        break;

    case EfiBltVideoToVideo:
        for (i=0;i<Height;i++) {
            VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
                     (SourceY + i)*This->Mode->Info->PixelsPerScanLine*PI2_BYTES_PER_PIXEL + \
                     SourceX*PI2_BYTES_PER_PIXEL);

            VidBuf1 = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
                      (DestinationY + i)*This->Mode->Info->PixelsPerScanLine*PI2_BYTES_PER_PIXEL + \
                      DestinationX*PI2_BYTES_PER_PIXEL);

            for (j=0;j<Width;j++) {
                gBS->CopyMem((VOID *)VidBuf1, (VOID *)VidBuf, PI2_COLOUR_BYTES_PER_PIXEL);
                VidBuf += PI2_BYTES_PER_PIXEL;
                VidBuf1 += PI2_BYTES_PER_PIXEL;
            }
        }
        break;

    default:
        ASSERT_EFI_ERROR(EFI_SUCCESS);
        break;
    }

    return EFI_SUCCESS;
}


/**
  Initialize the state information for the Display Dxe

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
DisplayDxeInitialize (
    IN EFI_HANDLE         ImageHandle,
    IN EFI_SYSTEM_TABLE   *SystemTable
    )
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GUID GraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_GUID DevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;

    if (gDisplay.Mode == NULL){
        Status = gBS->AllocatePool(
                        EfiBootServicesData,
                        sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE),
                        (VOID **)&gDisplay.Mode
                        );
        ASSERT_EFI_ERROR(Status);

        if (EFI_ERROR (Status)) {
          return Status;
        }

        ZeroMem(gDisplay.Mode,sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE));
    }

    if(gDisplay.Mode->Info==NULL){
        Status = gBS->AllocatePool(
                        EfiBootServicesData,
                        sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION),
                        (VOID **)&gDisplay.Mode->Info
                        );
        ASSERT_EFI_ERROR(Status);

        if (EFI_ERROR (Status)) {
          return Status;
        }

        ZeroMem(gDisplay.Mode->Info,sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
    }
        
    ZeroMem((void*)&MbFbSize, sizeof(MbFbSize));
    MbFbSize.Header.BufferSize = sizeof(MbFbSize);
    MbFbSize.Header.TagID = TAG_GET_PHYSICAL_SIZE;
    MbFbSize.Header.TagLength = 8;

    // Query the current display resolution from mailbox
    Status = MailboxProperty(MAILBOX_CHANNEL_PROPERTY_ARM_VC, (MAILBOX_HEADER*)&MbFbSize);
    if(EFI_ERROR(Status)) {
        return Status;
    }
    DEBUG((EFI_D_INIT, "Mailbox Display Size  %d x %d\n", MbFbSize.Width, MbFbSize.Height));

    ZeroMem((void*)&MbFb, sizeof(MAILBOX_FRAMEBUFFER));
    MbFb.mbf_phys_width = MbFb.mbf_virt_width = MbFbSize.Width;
    MbFb.mbf_phys_height = MbFb.mbf_virt_height = MbFbSize.Height;
    MbFb.mbf_depth = PI2_BITS_PER_PIXEL;

    // Request a frame buffer allocation so we can retrive
    // frame buffer address
    MailboxTransactFrameBuffer((PMAILBOX_FRAMEBUFFER)&MbFb);

    if ((MbFb.mbf_framebuf_addr != 0) && (MbFb.mbf_framebuf_size != 0))
    {
        //Applying alpha value to the frame buffer
        SetMem32((void*)MbFb.mbf_framebuf_addr, MbFb.mbf_framebuf_size, 0xFF000000);

        // Fill out mode information
        gDisplay.Mode->MaxMode = 1;
        gDisplay.Mode->Mode = 0;
        gDisplay.Mode->Info->Version = 0;
        // There is no way to communicate pitch back to OS. OS and even UEFI
        // expects a fully linear frame buffer. So the width should
        // be based on the frame buffer's pitch value. In some casses VC
        // firmware would allocate a frame buffer with some padding
        // presumeably to be 8 byte align.
        gDisplay.Mode->Info->HorizontalResolution = MbFb.mbf_pitch / PI2_BYTES_PER_PIXEL;
        gDisplay.Mode->Info->VerticalResolution = MbFb.mbf_virt_height;

        // NOTE: Windows REQUIRES BGR in 32 or 24 bit format.
        // TODO: Figure out a way in GOP driver to set the display controller
        //       to the appropriate pixel format instead of relying on 
        //       framebuffer_ignore_alpha and framebuffer_swap
        gDisplay.Mode->Info->PixelFormat = PixelBlueGreenRedReserved8BitPerColor;
        gDisplay.Mode->Info->PixelsPerScanLine = MbFb.mbf_pitch / PI2_BYTES_PER_PIXEL;;
        gDisplay.Mode->SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
        gDisplay.Mode->FrameBufferBase = MbFb.mbf_framebuf_addr;
        gDisplay.Mode->FrameBufferSize = MbFb.mbf_framebuf_size;

        {
            EFI_HANDLE gUEFIDisplayHandle = NULL;
            Status = gBS->InstallMultipleProtocolInterfaces (
                              &gUEFIDisplayHandle,
                              &DevicePathProtocolGuid,
                              &gDisplayDevicePath,
                              &GraphicsOutputProtocolGuid,
                              &gDisplay,
                              NULL);

        }
    }
    else
    {
        Status = EFI_DEVICE_ERROR;
    }

    return Status;
}
