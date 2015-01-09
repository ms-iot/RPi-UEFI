/** @file
*
*  Copyright (c) 2011-2013, ARM Limited. All rights reserved.
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
#include <Library/BaseMemoryLib.h>
#include <Library/BdsLib.h>
#include <Library/BdsUnixLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Library/ArmSmcLib.h>
#include <Library/ArmLib.h>

#include <Guid/GlobalVariable.h>
#include <Guid/ArmMpCoreInfo.h>
#include <Guid/ShellVariableGuid.h>

#include <libfdt.h>

#include <IndustryStandard/ArmSmc.h>

extern unsigned long get_AHB_CLK(void);

#define A_D(x) ( ((x >= L'a')&&(x <= L'f'))?(x-L'a'+0xa):(((x >= L'A')&&(x <= L'F'))?(x-L'A'+0xa):(x-L'0')) )

#ifdef AARCH64_MP_PROTOCOL
#define CPU_OFFSET	8
#else
#define CPU_OFFSET	0
#endif

STATIC VOID
UpdateFdt(
  IN OUT UINT8 *fdt
  )
{
  EFI_STATUS            Status;
  INTN                  err;
  INTN                  node;
  INTN                  soc;
  INTN                  cpu_node;
  UINTN                 Index;
  ARM_PROCESSOR_TABLE   *ArmProcessorTable;
  ARM_CORE_INFO         *ArmCoreInfoTable;
  UINT32                Freq;
  UINT64                CpuReleaseAddr;
  UINTN                 CoreMpId;
  unsigned long         ahb, tmp;
  CHAR16                Buf[20];
  UINT8                 MacAddr[6];
  UINTN                 Size;

  //
  // Validate Device Tree blob
  //
  err = fdt_check_header (fdt);
  if (err != 0) {
    Print (L"ERROR: Device Tree header not valid (err:%d)\n", err);
    return;
  }

  //
  // Set up cpu-release-addr
  //
  // For 'cpus' and 'cpu' device tree nodes bindings, refer to this file
  // in the kernel documentation:
  // Documentation/devicetree/bindings/arm/cpus.txt
  //
  for (Index=0; Index < gST->NumberOfTableEntries; Index++) {
    // Check for correct GUID type
    if (CompareGuid (&gArmMpCoreInfoGuid, &(gST->ConfigurationTable[Index].VendorGuid))) {
      node = fdt_subnode_offset(fdt, 0, "cpus");
      if (node < 0) {
	Print (L"ERROR: Device Tree 'cpus' node not found\n");
	break;
      }

      ArmProcessorTable = (ARM_PROCESSOR_TABLE *)gST->ConfigurationTable[Index].VendorTable;
      ArmCoreInfoTable = ArmProcessorTable->ArmCpus;

      for (Index = 0; Index < ArmProcessorTable->NumberOfEntries; Index++) {
	CHAR8 Name[10];
        CoreMpId = (UINTN) GET_MPID (ArmCoreInfoTable[Index].ClusterId,
                             ArmCoreInfoTable[Index].CoreId);
        AsciiSPrint (Name, 10, "cpu@%03x", CoreMpId);

        cpu_node = fdt_subnode_offset(fdt, node, Name);

        if (cpu_node >= 0) {
	  CONST VOID *Method;
	  INT32       lenp;
          Method = fdt_getprop(fdt, cpu_node, "enable-method", &lenp);
          if (Method && !AsciiStrCmp((CHAR8 *)Method, "spin-table")) {
            CpuReleaseAddr = cpu_to_fdt64(ArmCoreInfoTable[Index].MailboxSetAddress + CPU_OFFSET);
            fdt_setprop(fdt, cpu_node, "cpu-release-addr", &CpuReleaseAddr, sizeof(CpuReleaseAddr));
          }
        }
      }
      break;
    }
  }

  //
  // Find soc node
  //
  soc = fdt_subnode_offset(fdt, 0, "soc");
  if (soc < 0) {
      Print (L"ERROR: Device Tree 'soc' node not found\n");
      return;
  }

  //
  // Set MAC addr
  //
  Size = sizeof(Buf);
  Status = gRT->GetVariable(L"MAC0",
			    &gShellVariableGuid,
			    NULL, &Size,(void *)Buf);

  if (!EFI_ERROR (Status)) {
    MacAddr[0] = (A_D(Buf[0])<<4) + A_D(Buf[1]);
    MacAddr[1] = (A_D(Buf[3])<<4) + A_D(Buf[4]);
    MacAddr[2] = (A_D(Buf[6])<<4) + A_D(Buf[7]);
    MacAddr[3] = (A_D(Buf[9])<<4) + A_D(Buf[10]);
    MacAddr[4] = (A_D(Buf[12])<<4) + A_D(Buf[13]);
    MacAddr[5] = (A_D(Buf[15])<<4) + A_D(Buf[16]);

    node = fdt_subnode_offset(fdt, soc, "ethernet");
    if (node >= 0)
      fdt_setprop(fdt, node, "local-mac-address", MacAddr, sizeof(MacAddr));

    node = fdt_subnode_offset(fdt, soc, "ethernet_old");
    if (node >= 0)
      fdt_setprop(fdt, node, "local-mac-address", MacAddr, sizeof(MacAddr));
  }

  //
  // Set uart clock-frequency (there may be more than one serial port)
  // UART clock is as close as we can get to 50MHz (max) by
  // dividing AHB clock.
  //
  ahb = get_AHB_CLK();
  tmp = ahb / 50000000;
  Freq = cpu_to_fdt32(ahb / tmp);

  node = fdt_subnode_offset(fdt, soc, "serial");
  while (node > 0) {
    if (fdt_node_check_compatible(fdt, node, "ns16550a") == 0)
      fdt_setprop(fdt, node, "clock-frequency", &Freq, sizeof(Freq));

    node = fdt_next_node(fdt, node, NULL);
  }
}

extern UINT8 DeviceTreeBuff[];

VOID
SetupDeviceTree(
  )
{
  EFI_STATUS          Status;
  UINT8               *DeviceTreeVar;
  UINTN               DeviceTreeVarSize;
  UINTN               Count = 0;
  CHAR16              DeviceTreeName[14];
  UINT8               *Traveller = DeviceTreeBuff;
  EFI_GUID            RedhatGuid = {0x0abba7dc, 0xe516, 0x4167,
                                    {0xbb,0xf5,0x4d,0x9d,0x1c,0x73,0x94,0x16}};

  /* DeviceTree is encoded in ~1K blocks and the DeviceTreeBuff is 16K */
  do {
    UnicodeSPrint(DeviceTreeName, 13 * sizeof(CHAR16), L"DeviceTree%02d", Count);
    DeviceTreeVarSize = sizeof(UINT16);
    Status = GetEnvironmentVariable (DeviceTreeName, &RedhatGuid, NULL,
                                    &DeviceTreeVarSize, (VOID**)&DeviceTreeVar);
    if (EFI_ERROR(Status)) {
      break;
    } else {
      /* DeviceTree found. Copy it into DeviceTreeBuff */
      CopyMem(Traveller, DeviceTreeVar, DeviceTreeVarSize);

      FreePool(DeviceTreeVar);
      Traveller += DeviceTreeVarSize;
    }
    Count += 1;
  } while (Count < 16);

  if ((DeviceTreeBuff[0] == 0xd0) &&
      (DeviceTreeBuff[1] == 0x0d) &&
      (DeviceTreeBuff[2] == 0xfe) &&
      (DeviceTreeBuff[3] == 0xed)) {
    EFI_GUID DeviceTreeGuid = { 0xB1B621D5, 0xF19C, 0x41A5,
                               { 0x83, 0x0B, 0xD9, 0x15,
                                 0x2C, 0x69, 0xAA, 0xE0 }};

    UpdateFdt(DeviceTreeBuff);

    Status = gBS->InstallConfigurationTable(&DeviceTreeGuid, (void *) DeviceTreeBuff);
  }
}
