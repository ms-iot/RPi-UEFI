/** @file
  Timer Architecture Protocol driver of the ARM flavor

  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
  
  This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include "Protocol/LinuxAtagListProtocol.h"
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/NorFlashProtocol.h>

#define  LINUX_ATAG_FLASH_OFFSET        0x1200000 
#define  LINUX_ATAG_FLASH_SIZE          0x1000    

#define  LINUX_ATAG_MAGIC_FLAG          0x01
#define  INITRD_OFFSET                  0x40
#define  INITRD_SIZE_OFFSET             0x0c

typedef struct{
    UINT32              MagicFlag;
    UINT32              Checksum;
    LINUX_ATAG_LIST     LinuxAtagList;
}LINUX_ATAG_FLASH_DATA;


VOID GetDefaultLinuxAtag(
    IN OUT  LINUX_ATAG_LIST        *LinuxAtagList 
)
{
    LinuxAtagList->core_tag.flags = PcdGet32(PcdDefaultCoreTagFlags);
    LinuxAtagList->core_tag.pagesize = PcdGet32(PcdDefaultCoreTagPageSize);
    LinuxAtagList->core_tag.rootdev = PcdGet32(PcdDefaultCoreTagRootdev);

    LinuxAtagList->mem_tag.start = PcdGet32(PcdDefaultMemTagStart);
    LinuxAtagList->mem_tag.size = PcdGet32(PcdDefaultMemTagSize);

    LinuxAtagList->initrd2_tag.start = PcdGet32(PcdtinitrdStart) + INITRD_OFFSET;
    LinuxAtagList->initrd2_tag.size = SwapBytes32(*(volatile UINT32*)(PcdGet32(PcdtinitrdStart) + INITRD_SIZE_OFFSET));

    (VOID)AsciiStrCpy(LinuxAtagList->cmdline_tag.cmdline, (CHAR8*)PcdGetPtr(PcdDefaultCmdlineTagCmdline));

    LinuxAtagList->bootcmd_tag.addr = PcdGet32(PcdBootcmdAddr);
    LinuxAtagList->cpuinfo_tag.invalid = 0xffffffff;
    
#if 0   
    DEBUG((EFI_D_ERROR, "core_tag.flags = 0x%08x \n", LinuxAtagList->core_tag.flags));
    DEBUG((EFI_D_ERROR, "core_tag.pagesize = 0x%08x \n", LinuxAtagList->core_tag.pagesize));
    DEBUG((EFI_D_ERROR, "core_tag.rootdev = 0x%08x \n", LinuxAtagList->core_tag.rootdev));
    
    DEBUG((EFI_D_ERROR, "mem_tag.start = 0x%08x \n", LinuxAtagList->mem_tag.start));
    DEBUG((EFI_D_ERROR, "mem_tag.size = 0x%08x \n", LinuxAtagList->mem_tag.size));
    
    DEBUG((EFI_D_ERROR, "initrd2_tag.start = 0x%08x \n", LinuxAtagList->initrd2_tag.start));
    //DEBUG((EFI_D_ERROR, "initrd2_tag.size = 0x%08x \n", SwapBytes32(LinuxAtagList->initrd2_tag.size)));
    DEBUG((EFI_D_ERROR, "initrd2_tag.size come from initrd file, now can not be gotten \n"));
    
    DEBUG((EFI_D_ERROR, "cmdline_tag.cmdline = %a \n", LinuxAtagList->cmdline_tag.cmdline));
    DEBUG((EFI_D_ERROR, "bootcmd_tag.addr = %a \n", LinuxAtagList->bootcmd_tag.addr));
    DEBUG((EFI_D_ERROR, "cpuinfo_tag.invalid = %a \n", LinuxAtagList->cpuinfo_tag.invalid));
#endif
}

EFI_STATUS
GetLinuxAtag(
    IN LINUX_ATAG_LIST_PROTOCOL   *This,
    IN OUT  LINUX_ATAG_LIST        *LinuxAtagList 
    )
{
    EFI_STATUS  Status;
    UNI_NOR_FLASH_PROTOCOL        *Flash;
    LINUX_ATAG_FLASH_DATA      *FlashData;
    
    //load Flash Protocol
    Status = gBS->LocateProtocol (&gUniNorFlashProtocolGuid, NULL, (VOID **) &Flash);
    if (EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "Locate gOemFlashDriverProtocolGuid Error, Status = %r\n", Status));
        goto ERROR;
    }
    else
    {
        Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  LINUX_ATAG_FLASH_SIZE,
                  (VOID**) &FlashData
                  );
        if (NULL == FlashData)
        {
            DEBUG((EFI_D_ERROR, "AllocatePool  Error, Status = %r\n", Status));
            goto ERROR;
        }
        else
        {
            Status = Flash->Read(Flash, LINUX_ATAG_FLASH_OFFSET, (UINT8 *)FlashData, sizeof(LINUX_ATAG_FLASH_DATA));
            if (EFI_ERROR(Status))
            {
                DEBUG((EFI_D_ERROR, "flashRead Error, Status = %r\n", Status));
                if (NULL != FlashData)
                {
                    (VOID)gBS->FreePool(FlashData);
                }
                goto ERROR;
            }
            else
            {
                #if 0   
                    DEBUG((EFI_D_ERROR, "core_tag.flags = 0x%08x \n", FlashData->LinuxAtagList.core_tag.flags));
                    DEBUG((EFI_D_ERROR, "core_tag.pagesize = 0x%08x \n", FlashData->LinuxAtagList.core_tag.pagesize));
                    DEBUG((EFI_D_ERROR, "core_tag.rootdev = 0x%08x \n", FlashData->LinuxAtagList.core_tag.rootdev));
                    
                    DEBUG((EFI_D_ERROR, "mem_tag.start = 0x%08x \n", FlashData->LinuxAtagList.mem_tag.start));
                    DEBUG((EFI_D_ERROR, "mem_tag.size = 0x%08x \n", FlashData->LinuxAtagList.mem_tag.size));
                    
                    DEBUG((EFI_D_ERROR, "initrd2_tag.start = 0x%08x \n", FlashData->LinuxAtagList.initrd2_tag.start));
                    //DEBUG((EFI_D_ERROR, "initrd2_tag.size = 0x%08x \n", SwapBytes32(LinuxAtagList->initrd2_tag.size)));
                    DEBUG((EFI_D_ERROR, "initrd2_tag.size come from initrd file, now can not be gotten \n"));
                    
                    DEBUG((EFI_D_ERROR, "cmdline_tag.cmdline = %a \n", FlashData->LinuxAtagList.cmdline_tag.cmdline));
                #endif
                if ((LINUX_ATAG_MAGIC_FLAG == FlashData->MagicFlag) && (FlashData->Checksum == CalculateCheckSum32((CONST UINT32*)&(FlashData->LinuxAtagList), sizeof(LINUX_ATAG_LIST))))
                {
                    gBS->CopyMem(LinuxAtagList, &(FlashData->LinuxAtagList), sizeof(LINUX_ATAG_LIST));
                    
                    #if 0   
                        DEBUG((EFI_D_ERROR, "!!!!!!!!!!!!!!!!!!\n"));
                        DEBUG((EFI_D_ERROR, "core_tag.flags = 0x%08x \n", FlashData->LinuxAtagList.core_tag.flags));
                        DEBUG((EFI_D_ERROR, "core_tag.pagesize = 0x%08x \n", FlashData->LinuxAtagList.core_tag.pagesize));
                        DEBUG((EFI_D_ERROR, "core_tag.rootdev = 0x%08x \n", FlashData->LinuxAtagList.core_tag.rootdev));
                        
                        DEBUG((EFI_D_ERROR, "mem_tag.start = 0x%08x \n", FlashData->LinuxAtagList.mem_tag.start));
                        DEBUG((EFI_D_ERROR, "mem_tag.size = 0x%08x \n", FlashData->LinuxAtagList.mem_tag.size));
                        
                        DEBUG((EFI_D_ERROR, "initrd2_tag.start = 0x%08x \n", FlashData->LinuxAtagList.initrd2_tag.start));
                        //DEBUG((EFI_D_ERROR, "initrd2_tag.size = 0x%08x \n", SwapBytes32(LinuxAtagList->initrd2_tag.size)));
                        DEBUG((EFI_D_ERROR, "initrd2_tag.size come from initrd file, now can not be gotten \n"));
                        
                        DEBUG((EFI_D_ERROR, "cmdline_tag.cmdline = %a \n", FlashData->LinuxAtagList.cmdline_tag.cmdline));
                        DEBUG((EFI_D_ERROR, "@@@@@@@@@@@@@@@@@@@@\n"));
                    #endif
                    #if 0   
                        DEBUG((EFI_D_ERROR, "core_tag.flags = 0x%08x \n", LinuxAtagList->core_tag.flags));
                        DEBUG((EFI_D_ERROR, "core_tag.pagesize = 0x%08x \n", LinuxAtagList->core_tag.pagesize));
                        DEBUG((EFI_D_ERROR, "core_tag.rootdev = 0x%08x \n", LinuxAtagList->core_tag.rootdev));
                        
                        DEBUG((EFI_D_ERROR, "mem_tag.start = 0x%08x \n", LinuxAtagList->mem_tag.start));
                        DEBUG((EFI_D_ERROR, "mem_tag.size = 0x%08x \n", LinuxAtagList->mem_tag.size));
                        
                        DEBUG((EFI_D_ERROR, "initrd2_tag.start = 0x%08x \n", LinuxAtagList->initrd2_tag.start));
                        //DEBUG((EFI_D_ERROR, "initrd2_tag.size = 0x%08x \n", SwapBytes32(LinuxAtagList->initrd2_tag.size)));
                        DEBUG((EFI_D_ERROR, "initrd2_tag.size come from initrd file, now can not be gotten \n"));
                        
                        DEBUG((EFI_D_ERROR, "cmdline_tag.cmdline = %a \n", LinuxAtagList->cmdline_tag.cmdline));
                        //DEBUG((EFI_D_ERROR, "#########################\n"));
                    #endif
                    if (NULL != FlashData)
                    {
                        (VOID)gBS->FreePool(FlashData);
                    }
                    return EFI_SUCCESS;
                }
                else
                {
                    if (NULL != FlashData)
                    {
                        (VOID)gBS->FreePool(FlashData);
                    }
                    goto ERROR;
                }
            }
        }
    }

ERROR:
    DEBUG((EFI_D_ERROR, "Get default linux atag list\n"));
    GetDefaultLinuxAtag(LinuxAtagList);
    DEBUG((EFI_D_ERROR, "Get default linux atag list ok!\n"));
    return EFI_SUCCESS;
}

EFI_STATUS
SetLinuxAtag(
    IN LINUX_ATAG_LIST_PROTOCOL   *This,
    IN LINUX_ATAG_LIST             *LinuxAtagList 
    )
{
    EFI_STATUS  Status;
    UNI_NOR_FLASH_PROTOCOL  *Flash;
    LINUX_ATAG_FLASH_DATA      *FlashData;
    
    //load Flash Protocol
    Status = gBS->LocateProtocol (&gUniNorFlashProtocolGuid, NULL, (VOID **) &Flash);
    if (EFI_ERROR(Status))
    {
        DEBUG((EFI_D_ERROR, "Locate gUniNorFlashProtocolGuid Error, Status = %r\n", Status));
        return Status;
    }
    else
    {
        
        Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  LINUX_ATAG_FLASH_SIZE,
                  (VOID**) &FlashData
                  );
        if (NULL == FlashData)
        {
            DEBUG((EFI_D_ERROR, "AllocatePool  Error, Status = %r\n", Status));
            return Status;
        }
        else
        {
            (VOID)ZeroMem(FlashData, LINUX_ATAG_FLASH_SIZE);
            
            FlashData->MagicFlag = LINUX_ATAG_MAGIC_FLAG;
            FlashData->Checksum = CalculateCheckSum32((CONST UINT32*)LinuxAtagList, sizeof(LINUX_ATAG_LIST));
            gBS->CopyMem(&(FlashData->LinuxAtagList), LinuxAtagList, sizeof(LINUX_ATAG_LIST));
            
            #if 0   
                DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));
                DEBUG((EFI_D_ERROR, "core_tag.flags = 0x%08x \n", LinuxAtagList->core_tag.flags));
                DEBUG((EFI_D_ERROR, "core_tag.pagesize = 0x%08x \n", LinuxAtagList->core_tag.pagesize));
                DEBUG((EFI_D_ERROR, "core_tag.rootdev = 0x%08x \n", LinuxAtagList->core_tag.rootdev));
                
                DEBUG((EFI_D_ERROR, "mem_tag.start = 0x%08x \n", LinuxAtagList->mem_tag.start));
                DEBUG((EFI_D_ERROR, "mem_tag.size = 0x%08x \n", LinuxAtagList->mem_tag.size));
                
                DEBUG((EFI_D_ERROR, "initrd2_tag.start = 0x%08x \n", LinuxAtagList->initrd2_tag.start));
                //DEBUG((EFI_D_ERROR, "initrd2_tag.size = 0x%08x \n", SwapBytes32(LinuxAtagList->initrd2_tag.size)));
                DEBUG((EFI_D_ERROR, "initrd2_tag.size come from initrd file, now can not be gotten \n"));
                
                DEBUG((EFI_D_ERROR, "cmdline_tag.cmdline = %a \n", LinuxAtagList->cmdline_tag.cmdline));
            #endif
            Status = Flash->Write(Flash, LINUX_ATAG_FLASH_OFFSET, (UINT8 *)FlashData, sizeof(LINUX_ATAG_FLASH_DATA));
            if (EFI_ERROR(Status))
            {
                DEBUG((EFI_D_ERROR, "flashWrite LINUX_ATAG_LIST Error, Status = %r\n", Status));
            }
            
            #if 0   
                DEBUG((EFI_D_ERROR, "[DJ]: %a : %d\n", __FUNCTION__, __LINE__));
                DEBUG((EFI_D_ERROR, "core_tag.flags = 0x%08x \n", FlashData->LinuxAtagList.core_tag.flags));
                DEBUG((EFI_D_ERROR, "core_tag.pagesize = 0x%08x \n", FlashData->LinuxAtagList.core_tag.pagesize));
                DEBUG((EFI_D_ERROR, "core_tag.rootdev = 0x%08x \n", FlashData->LinuxAtagList.core_tag.rootdev));
                
                DEBUG((EFI_D_ERROR, "mem_tag.start = 0x%08x \n", FlashData->LinuxAtagList.mem_tag.start));
                DEBUG((EFI_D_ERROR, "mem_tag.size = 0x%08x \n", FlashData->LinuxAtagList.mem_tag.size));
                
                DEBUG((EFI_D_ERROR, "initrd2_tag.start = 0x%08x \n", FlashData->LinuxAtagList.initrd2_tag.start));
                //DEBUG((EFI_D_ERROR, "initrd2_tag.size = 0x%08x \n", SwapBytes32(LinuxAtagList->initrd2_tag.size)));
                DEBUG((EFI_D_ERROR, "initrd2_tag.size come from initrd file, now can not be gotten \n"));
                
                DEBUG((EFI_D_ERROR, "cmdline_tag.cmdline = %a \n", FlashData->LinuxAtagList.cmdline_tag.cmdline));
            #endif
            
            if (NULL != FlashData)
            {
                (VOID)gBS->FreePool(FlashData);
            }
            return Status;
        }
    }
}


LINUX_ATAG_LIST_PROTOCOL mLinuxAtagListProtocol = 
{
    GetLinuxAtag,
    SetLinuxAtag
};



EFI_STATUS
EFIAPI
LinuxAtagListInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
    EFI_STATUS  Status;


    Status = gBS->InstallProtocolInterface(
                  &ImageHandle,
                  &gLinuxAtagListProtocolGuid,      
                  EFI_NATIVE_INTERFACE,
                  &mLinuxAtagListProtocol
                  );
    if (EFI_ERROR (Status))
    {
        DEBUG((EFI_D_ERROR, "Install gLinuxAtagListProtocolGuid %r \n", Status));
    }

  return Status;
}

