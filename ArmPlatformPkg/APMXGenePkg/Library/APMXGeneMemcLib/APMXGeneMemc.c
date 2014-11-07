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

#include <Base.h>
#include <Library/I2C.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/ArmLib.h>


#define RANK0_OFFSET 0x300
#define MCU0_BASE 0x7E800000ULL
#define PCPRB_BASE  0x7C000000ULL
#define PCP_RB_CSW_CSWCR_DUALMCB_RD(src)    (((src) & 0x00000001U)>>0)

#define TTB_BASE_ADDR PcdGet64(PcdTTBBaseAddr)

#define PAGESIZE    4096

#define MEM_ATTR_DEVICE_SO  0
#define MEM_ATTR_NORMAL_CACHE  1  //WB
//#define MEM_ATTR_NORMAL_CACHE  3  //Write through

enum TBLTYPE {
  TBL_TYPE_L0 = 0,
  TBL_TYPE_L1_0,
  TBL_TYPE_L1_1,
  TBL_TYPE_L2
};

UINT64 GetTTBAddr(enum TBLTYPE Tbl)
{
  if (Tbl < TBL_TYPE_L0 || Tbl > TBL_TYPE_L2)
    return 0;

  return (TTB_BASE_ADDR + (PAGESIZE * Tbl));
}

VOID InitPageTBL(UINT64 Ttb)
{
  UINT64 *Pte = (UINT64 *)Ttb;
  UINTN i;

  if (NULL == Pte)
    return;

  for (i=0; i<PAGESIZE; i+=8) {
    *(Pte++) = 0;
  }
}

VOID AddL1BlockEntry(UINT64 Addr, UINT32 MemAttr)
{
  UINT64 Ttb;
  UINT64 Pte = 0;
  UINT64 Index;

  if ((Addr >> 39) > 1)
    return;

  if (Addr >> 39)
    Ttb = GetTTBAddr(TBL_TYPE_L1_1);
  else
    Ttb = GetTTBAddr(TBL_TYPE_L1_0);

  Pte |= Addr & 0xFFFFC0000000ULL;// o/p addr bits[47:30]
  Pte |= (0x1 << 10);    // AF bit[10]
  Pte |= (0x2 << 8);    // SH bits[9:8]
  Pte |= (0x1 << 5);    // NS bit[5]
  Pte |= ((MemAttr & 0x7) << 2);  // AttrIndx bits[4:2]
  Pte |= 0x1;      // block entry bits[1:0]

  Index = (Addr >> 30) & 0x1FF;
  *((UINT64 *)(Ttb + (Index * 8))) = Pte;
}

VOID AddL2BlockEntry(UINT64 Addr, UINT32 MemAttr)
{
  UINT64 Ttb;
  UINT64 Pte = 0;
  UINT64 Index;

  if ((Addr >> 30) > 0)
    return;

  Ttb = GetTTBAddr(TBL_TYPE_L2);

  Pte |= Addr & 0xFFFFFFE00000ULL;// o/p addr bits[47:21]
  Pte |= (0x1 << 10);    // AF bit[10]
  Pte |= (0x2 << 8);    // SH bits[9:8]
  Pte |= (0x1 << 5);    // NS bit[5]
  Pte |= ((MemAttr & 0x7) << 2);  // AttrIndx bits[4:2]
  Pte |= 0x1;      // block entry bits[1:0]

  Index = (Addr >> 21) & 0x1FF;

  *((UINT64 *)(Ttb + (Index * 8))) = Pte;
}

VOID SetupL0Entries(VOID)
{
  UINT64 L0TTBAddr   = GetTTBAddr(TBL_TYPE_L0);
  UINT64 L1TTBAddr0 = GetTTBAddr(TBL_TYPE_L1_0);
  UINT64 L1TTBAddr1 = GetTTBAddr(TBL_TYPE_L1_1);

  InitPageTBL(L0TTBAddr);

  /* Set L0 'Table' entries
   *  L0[0]   --> L1-0 TTB
   *  L0[1]   --> L1-1 TTB
   */

  *((UINT64 *)L0TTBAddr) = (L1TTBAddr0 | 0x3);
  *((UINT64 *)(L0TTBAddr + 8)) = (L1TTBAddr1 | 0x3);
}

VOID SetupL1Entries(VOID)
{
  UINT64 L1TTBAddr0 = GetTTBAddr(TBL_TYPE_L1_0);
  UINT64 L1TTBAddr1 = GetTTBAddr(TBL_TYPE_L1_1);
  UINT64 L2TTBAddr  = GetTTBAddr(TBL_TYPE_L2);
  UINT64 i;

  InitPageTBL(L1TTBAddr0);
  InitPageTBL(L1TTBAddr1);

  /* Set L1-0 'Table' entry
   *  L1-0[0] --> L2 TTB
   */

  *((UINT64 *)L1TTBAddr0) = (L2TTBAddr | 0x3);

  /* add 1GB 'Block' entries */

  /* For Address space 0x4000_0000 to 0x7FFF_FFFF
   *  - Device memory
   */
  AddL1BlockEntry(0x40000000ULL, MEM_ATTR_DEVICE_SO);

  /* For Address space 0x8000_0000 to 0x7F_FFFF_FFFF
   *  - Normal cacheable memory
   */
  for (i=0; i<510; i++) {
    AddL1BlockEntry(0x80000000ULL + (i<<30), MEM_ATTR_NORMAL_CACHE);
  }

  /* For Address space 0x80_0000_0000 to 0x80_7FFF_FFFF
   *  - Normal cacheable memory
   */
  for (i=0; i<2; i++) {
    AddL1BlockEntry(0x8000000000ULL + (i<<30), MEM_ATTR_NORMAL_CACHE);
  }

  AddL1BlockEntry(0x8100000000ULL, MEM_ATTR_NORMAL_CACHE);

  /* For Address space 0x90_0000_0000 to 0xFF_FFFF_FFFF
   *  - Device memory
   */
  for (i=0; i<448; i++) {
    AddL1BlockEntry(0x9000000000ULL + (i<<30), MEM_ATTR_DEVICE_SO);
  }

}

VOID SetupL2Entries(VOID)
{
  UINT64 L2TTBAddr   = GetTTBAddr(TBL_TYPE_L2);
  UINT64 i;

  InitPageTBL(L2TTBAddr);

  /* add 2MB 'Block' entries */

  /* For Address space 0x0000_0000 to 0x3FFF_FFFF
   *  - Boot region: Normal memory cacheable
   *   - OCM region: Normal memory cacheable
   *  - Rest of the region: Device memory
   */

  for (i=0; i<128; i++) {
    AddL2BlockEntry(0ULL + (i<<21), MEM_ATTR_NORMAL_CACHE);
  }

  for (i=128; i<232; i++) {
    AddL2BlockEntry(0ULL + (i<<21), MEM_ATTR_DEVICE_SO);
  }

  AddL2BlockEntry(0x1D000000ULL, MEM_ATTR_NORMAL_CACHE);
  
  for (i=233; i<512; i++) {
    AddL2BlockEntry(0ULL + (i<<21), MEM_ATTR_DEVICE_SO);
  }
}

VOID MMUDisable(VOID)
{
  ArmCleanInvalidateDataCache ();
  ArmInvalidateInstructionCache ();

  ArmInvalidateTlb ();

  ArmDisableDataCache ();
  ArmDisableInstructionCache();
  ArmDisableMmu ();
}

VOID MMUSetup(VOID)
{
  UINT64  Reg;

  ArmCleanInvalidateDataCache ();
  ArmInvalidateInstructionCache ();

  ArmDisableDataCache ();
  ArmDisableInstructionCache();
  ArmDisableMmu ();

  ArmCleanInvalidateDataCache ();
  ArmInvalidateInstructionCache ();
  ArmInvalidateTlb ();

  /* setup pte */
  SetupL0Entries();
  SetupL1Entries();
  SetupL2Entries();

  /* setup TTBR_EL2 */
  Reg = GetTTBAddr(TBL_TYPE_L0);
  ArmSetTTBR0((VOID *)Reg);
  
  /* setup TCR_EL2 */
  Reg = 0x3ULL << 16;  // 42bit PA
  ArmSetTCR(Reg);

  /* setup MAIR_EL2
   *  0 : 0x00 : Device Strongly ordered
   *  1 : 0xFF : Normal,WB-WA
   *  2 : 0x44 : Normal,no-cache
   *  3 : 0xAA : Normal,Write-through
   */
  Reg = 0xAA44FF00;
  ArmSetMAIR(Reg);

  ArmDisableAlignmentCheck();
  ArmEnableInstructionCache();
  ArmEnableDataCache();

  /* Enable MMU */
  ArmEnableMmu();
}

UINT64 GetDDRSize(VOID)
{
  UINT32 McuActiveFlag;
  UINT64 Result = 0;
  INTN i, j;
  volatile UINT64 Reg;
  volatile UINT32 Value;
  Reg = (PCPRB_BASE + 0x02200000);
  Value = *(UINT32 *)Reg;
  if (PCP_RB_CSW_CSWCR_DUALMCB_RD(Value)) {
    Reg = (PCPRB_BASE + 0x02720000);
    Value = *(UINT32 *)Reg;
    McuActiveFlag = (Value & 0x00000004)? 0xF: 0x5;
  } else {
    Reg = (PCPRB_BASE + 0x02700000);
    Value = *(UINT32 *)Reg;
    McuActiveFlag = (Value & 0x00000004)? 0x3: 0x1;
  }

  for (i = 0; i < 4; i++) {
    Reg = (MCU0_BASE+ 0x40000*i + RANK0_OFFSET);
    if (!(McuActiveFlag & (1 << i)))
      continue;
    for (j = 0; j < 8; j++) {
      Reg += 0x40*j;
      Value = *(UINT32 *)Reg;
      if (Value > 5)
        continue;
      switch (Value) {
      case 0:
        Result += 512 * 1024 * 1024ULL;
        break;
      case 1:
        Result += 1024 * 1024 * 1024ULL;
        break;
      case 2:
        Result += 2 * 1024 * 1024 * 1024ULL;
        break;
      case 3:
        Result += 4 * 1024 * 1024 * 1024ULL;
        break;
      case 4:
        Result += 8 * 1024 * 1024 * 1024ULL;
        break;
      case 5:
        Result += 16 * 1024 * 1024 * 1024ULL;
        break;
      default:
        ASSERT(0);
        break;
      }
    }
  }
  return Result;
}


extern int dram_hw_init(void);

RETURN_STATUS APMXGeneMemcInit(VOID)
{
  UINT64 *MemSizeAddr;
#if defined(APM_XGENE_VHP) || defined(APM_XGENE_UHP)
  /* test environment so set mem to fix 4GB*/
  MemSizeAddr = (UINT64*)(UINT64)PcdGet64(PcdMemSizeAddr);
  *MemSizeAddr = GetDDRSize();
  DEBUG ((EFI_D_VERBOSE, "Memsize:0x%llx\n", *MemSizeAddr));
#else
 
  MMUSetup();
  
  DEBUG ((EFI_D_VERBOSE, "I2C Init\n"));
  I2c_Init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
  DEBUG ((EFI_D_VERBOSE, "DDR Init\n"));

  dram_hw_init();

  MMUDisable();

  MemSizeAddr = (UINT64 *)PcdGet64(PcdMemSizeAddr);
  *MemSizeAddr =  GetDDRSize();
  DEBUG ((EFI_D_VERBOSE, "DDR SIZE:%lX\n", *MemSizeAddr));
#endif
  return RETURN_SUCCESS;
}

