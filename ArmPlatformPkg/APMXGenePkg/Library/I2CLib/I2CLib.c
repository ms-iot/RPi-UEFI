/**
 *  I2C Host library
 *
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
#include <Uefi/UefiBaseType.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>

#include "I2CLib.h"

//#define I2C_DBG 1
//#define I2C_PRINT 1

#ifdef I2C_DBG
#define DBG(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define DBG(arg...)
#endif

#ifdef I2C_PRINT
#define PRINT(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define PRINT(arg...)
#endif

#ifdef CONFIG_HARD_I2C

#if defined(CONFIG_I2C_MULTI_BUS)
/*
 * Initialize the bus pinter to whatever one the SPD EEPROM is on.
 * Default is bus 0.  This is necessary because the DDR initialization
 * runs from ROM, and we can't switch buses because we can't modify
 * the global variables.
 */
#ifndef CONFIG_SYS_SPD_BUS_NUM
#define CONFIG_SYS_SPD_BUS_NUM  1
#endif
UINTN I2c_Bus_Num  = CONFIG_SYS_SPD_BUS_NUM;
#endif /* CONFIG_I2C_MULTI_BUS */

#define I2c_Sync() { asm volatile ("dmb ish" : : : "memory"); }

UINTN I2c_Hw_Init_Done  = 0;


/* Keeping i2c_poll in micro second, 10 times the signaling period */
DW_I2C_T Dw_I2c[CONFIG_SYS_MAX_I2C_BUS] = {
  {
    .Base = (I2C_BASE + 0x1000),
    .Bus_Endian = DW_LE_BUS,
    .Bus_Speed = CONFIG_SYS_I2C_SPEED,
    .Rx_Buffer = CONFIG_DW_I2C_RX_BUFFER_DEPTH,
    .Tx_Buffer = CONFIG_DW_I2C_TX_BUFFER_DEPTH,
    .Device_Addr = CONFIG_SYS_I2C_EEPROM_ADDR,
    .Device_Addr_Len = CONFIG_SYS_I2C_EEPROM_ADDR_LEN,
    .Page_Write_Size = CONFIG_SYS_I2C_EEPROM_PAGE_WRITE_LEN,
    .Poll_Time = ((10 * 1000000) / CONFIG_SYS_I2C_SPEED),
    .Init_Done = 1,
  },
  {
    .Base = (I2C_BASE),
    .Bus_Endian = DW_LE_BUS,
    .Bus_Speed = CONFIG_SYS_I2C1_SPEED,
    .Rx_Buffer = CONFIG_DW_I2C_RX_BUFFER_DEPTH,
    .Tx_Buffer = CONFIG_DW_I2C_TX_BUFFER_DEPTH,
    .Device_Addr = CONFIG_SYS_I2C1_EEPROM_ADDR,
    .Device_Addr_Len = CONFIG_SYS_I2C1_EEPROM_ADDR_LEN,
    .Page_Write_Size = CONFIG_SYS_I2C1_EEPROM_PAGE_WRITE_LEN,
    .Poll_Time = ((10 * 1000000) / CONFIG_SYS_I2C1_SPEED),
    .Init_Done = 1,
  },
};

UINT32 I2c_Scl_Min[4][3] = {  /* in nano seconds */
  /* High, Low, tf */
  [I2C_SS] =   {4000, 4700, 300},  /* SS (Standard Speed) */
  [I2C_FS] =   { 600, 1300, 300},  /* FS (Fast Speed) */
  [I2C_HS_400PF] = { 160,  320, 300},  /* HS (High Speed) 400pf */
  [I2C_HS_100PF] = {  60,  120, 300},  /* HS (High Speed) 100pf */
};

inline
UINT32 Read32(UINT32 Addr)
{
  return MmioRead32(Addr);
}

inline
VOID Write32(UINT32 Addr, UINT32 Val)
{
  MmioWrite32(Addr, Val);
}

VOID I2c_Hw_Init(VOID)
{
  INTN i;
  UINT32 Base, Param;
  DBG("Calling I2c_Hw_Init\n");
  for (i = 0; i < CONFIG_SYS_MAX_I2C_BUS; i++) {
    Base = Dw_I2c[i].Base;
    Dw_I2c[i].Bus_Endian = DW_LE_BUS;
    Param = Read32(Base + DW_IC_COMP_PARAM_1);
    Dw_I2c[i].Rx_Buffer = ((Param >> 8) & 0xff) + 1;
    Dw_I2c[i].Tx_Buffer = ((Param >> 16) & 0xff) + 1;
    DBG("I2c_Hw_Init: Bus:%d Rx_Buffer:%d Tx_Buffer:%d\n", i, Dw_I2c[i].Rx_Buffer, Dw_I2c[i].Tx_Buffer);
  }
  I2c_Hw_Init_Done = 1;
}

/*
 * Check for errors on i2c bus
 */
UINT32 I2c_Dw_Check_Errors(UINT32 Base, INTN Print_Err)
{
  UINT32 I2c_Status_Cnt = DW_STATUS_WAIT_RETRY;
  UINT32 Tx_Abrt = 0;
  UINT32 Status = Read32(Base + DW_IC_RAW_INTR_STAT);

  if (Status & DW_IC_INTR_RX_UNDER)
    Read32(Base + DW_IC_CLR_RX_UNDER);

  if (Status & DW_IC_INTR_RX_OVER)
    Read32(Base + DW_IC_CLR_RX_OVER);

  if (Status & DW_IC_INTR_TX_ABRT) {
    Status = Read32(Base + DW_IC_TX_ABRT_SOURCE);
    Read32(Base + DW_IC_CLR_TX_ABRT);
    if (Print_Err)
      DBG("TX_ABORT ");
  }

  if (Status & DW_IC_ERR_CONDITION) {
    if (Print_Err  && (Status || Tx_Abrt))
      DBG("Errors on i2c bus %08x %08x: ",
        Status, Tx_Abrt);
    /* Disable the adapter */
    Write32(Base + DW_IC_ENABLE, 0);
    do {
      MicroSecondDelay(I2c_Poll_Time);
      I2c_Sync();
      if (I2c_Status_Cnt == 0)
        DBG("I2C disable Timeout: ");
    } while (((Read32(Base + DW_IC_ENABLE_STATUS) & 0x01))
        && I2c_Status_Cnt--);
    I2c_Init_Done = 0;
    /* Unset the target adddress */
    Write32(Base + DW_IC_TAR, 0);
  }

  return (Status & DW_IC_ERR_CONDITION);
}

/*
 * Waiting for bus not busy
 */
BOOLEAN I2c_Dw_Wait_Bus_Not_Busy(UINT32 Base)
{
  INTN Timeout = DW_BUS_WAIT_TIMEOUT;

  while (Read32(Base + DW_IC_STATUS) & 0x20) {
    if (Timeout <= 0) {
      DBG("I2C: Timeout waiting for bus ready\n");
      return TRUE;
    }
    Timeout--;
    MicroSecondDelay(1000);
  }
  return FALSE;
}

/*
 * Check for successful response from slave
 */
UINT32 I2c_Dw_Check_Status(UINT32 Base, INTN Print_Err)
{
  UINT32 Status = Read32(Base + DW_IC_RAW_INTR_STAT);

  if (Status & DW_IC_INTR_ACTIVITY)
    Read32(Base + DW_IC_CLR_ACTIVITY);

  if (Status & DW_IC_INTR_STOP_DET)
    Read32(Base + DW_IC_CLR_STOP_DET);

  if (Status & DW_IC_INTR_START_DET)
    Read32(Base + DW_IC_CLR_START_DET);

  Status = I2c_Dw_Check_Errors(Base, Print_Err);

  if ((Status & DW_IC_ERR_CONDITION) && Print_Err) {
    DBG("device response\n");
  }

  return (Status & DW_IC_ERR_CONDITION);
}

/*
 * Waiting for TX FIFO buffer available
 */
EFI_STATUS I2c_Dw_Wait_Tx_Data(UINT32 Base)
{
  INTN Timeout = DW_TX_DATA_RETRY;

  while (Read32(Base + DW_IC_TXFLR) == I2c_Tx_Buffer) {
    if (Timeout <= 0) {
      DBG("I2C: Timeout waiting for TX buffer available\n");
      return EFI_TIMEOUT;
    }
    Timeout--;
    MicroSecondDelay(I2c_Poll_Time);
  }
  return EFI_SUCCESS;
}

UINT32
I2c_Dw_Scl_Hcnt(UINT32 Ic_Clk, UINT32 tSYMBOL, UINT32 Tf, INTN Cond, INTN Offset)
{
  /*
   * DesignWare I2C core doesn't seem to have solid strategy to meet
   * the tHD;STA timing spec.  Configuring _HCNT.Based on tHIGH spec
   * will result in violation of the tHD;STA spec.
   */
  if (Cond)
    /*
     * Conditional expression:
     *
     *   IC_[FS]S_SCL_HCNT + (1+4+3) >= IC_CLK * tHIGH
     *
     * This is.Based on the DW manuals, and represents an ideal
     * configuration.  The resulting I2C bus speed will be
     * faster than any of the others.
     *
     * If your hardware is free from tHD;STA issue, try this one.
     */
    return (((Ic_Clk * tSYMBOL + 500000) / 1000000) - 8 + Offset);

  /*
   * Conditional expression:
   *
   *   IC_[FS]S_SCL_HCNT + 3 >= IC_CLK * (tHD;STA + tf)
   *
   * This is just experimental rule; the tHD;STA period turned
   * out to be proportinal to (_HCNT + 3).  With this setting,
   * we could meet both tHIGH and tHD;STA timing specs.
   *
   * If unsure, you'd better to take this alternative.
   *
   * The reason why we need to take INTNo acCount "tf" here,
   * is the same as described in I2c_Dw_Scl_Lcnt().
   */
  return (((Ic_Clk * (tSYMBOL + Tf) + 500000) / 1000000) - 3 + Offset);
}

UINT32 I2c_Dw_Scl_Lcnt(UINT32 Ic_Clk, UINT32 tLOW, UINT32 Tf, INTN Offset)
{
  /*
   * Conditional expression:
   *
   *   IC_[FS]S_SCL_LCNT + 1 >= IC_CLK * (tLOW + tf)
   *
   * DW I2C core starts Counting the SCL CNTs for the LOW period
   * of the SCL clock (tLOW) as soon as it pulls the SCL line.
   * In order to meet the tLOW timing spec, we need to take INTNo
   * acCount the fall time of SCL signal (tf).  Default tf value
   * should be 0.3 us, for safety.
   */
  return (((Ic_Clk * (tLOW + Tf) + 500000) / 1000000) - 1 + Offset);
}

/**
 * I2c_Scl_Init() - initialize the designware i2c scl Counts
 *
 * This functions configures scl clock Count for SS, FS, and HS.
 * This function is called during I2C init function.
 */
VOID I2c_Scl_Init(UINT32 Base, UINT32 I2c_Clk_Freq, UINT32 I2c_Speed)
{
  UINT32 Input_Clock_Khz = I2c_Clk_Freq / 1000;
  UINT32 Hcnt, Lcnt;
  UINT32 Ss_Clock_Khz = Input_Clock_Khz;
  UINT32 Fs_Clock_Khz = Input_Clock_Khz;
  UINT32 Hs_Clock_Khz = Input_Clock_Khz;
  UINT32 I2c_Speed_Khz = I2c_Speed / 1000;

  if (I2c_Speed_Khz <= 100)
    Ss_Clock_Khz = (Ss_Clock_Khz * 100) / I2c_Speed_Khz;
  else if (I2c_Speed_Khz > 100 && I2c_Speed_Khz <= 400)
    Fs_Clock_Khz = (Fs_Clock_Khz * 400) / I2c_Speed_Khz;
  else if (I2c_Speed_Khz > 400 && I2c_Speed_Khz <= 3400)
    Hs_Clock_Khz = (Hs_Clock_Khz * 3400) / I2c_Speed_Khz;

  /* set standard, fast and High speed dividers for high/low periods */

  /* Standard speed mode */
  Hcnt = I2c_Dw_Scl_Hcnt(Ss_Clock_Khz,
    I2c_Scl_Min[I2C_SS][I2C_SCL_HIGH],  /* tHD;STA = tHIGH = 4.0 us */
    I2c_Scl_Min[I2C_SS][I2C_SCL_TF],  /* tf = 0.3 us */
    0,  /* 0: DW default, 1: Ideal */
    0);  /* No Offset */
  Lcnt = I2c_Dw_Scl_Lcnt(Ss_Clock_Khz,
    I2c_Scl_Min[I2C_SS][I2C_SCL_LOW],  /* tLOW = 4.7 us */
    I2c_Scl_Min[I2C_SS][I2C_SCL_TF],  /* tf = 0.3 us */
    0);  /* No Offset */
  Write32(Base + DW_IC_SS_SCL_HCNT, Hcnt);
  Write32(Base + DW_IC_SS_SCL_LCNT, Lcnt);

  /* Fast speed mode */
  Hcnt = I2c_Dw_Scl_Hcnt(Fs_Clock_Khz,
    I2c_Scl_Min[I2C_FS][I2C_SCL_HIGH],  /* tHD;STA = tHIGH = 0.6 us */
    I2c_Scl_Min[I2C_FS][I2C_SCL_TF],  /* tf = 0.3 us */
    0,  /* 0: DW default, 1: Ideal */
    0);  /* No Offset */
  Lcnt = I2c_Dw_Scl_Lcnt(Fs_Clock_Khz,
    I2c_Scl_Min[I2C_FS][I2C_SCL_LOW],  /* tLOW = 1.3 us */
    I2c_Scl_Min[I2C_FS][I2C_SCL_TF],  /* tf = 0.3 us */
    0);  /* No Offset */
  Write32(Base + DW_IC_FS_SCL_HCNT, Hcnt);
  Write32(Base + DW_IC_FS_SCL_LCNT, Lcnt);

  /* High speed mode */
  Hcnt = I2c_Dw_Scl_Hcnt(Hs_Clock_Khz,
    I2c_Scl_Min[I2C_HS][I2C_SCL_HIGH],  /* )
    i2c_hw_init();tHD;STA = tHIGH = 0.06 us for 100pf 0.16 for 400pf */
    I2c_Scl_Min[I2C_HS][I2C_SCL_TF],  /* tf = 0.3 us */
    0,  /* 0: DW default, 1: Ideal */
    0);  /* No Offset */
  Lcnt = I2c_Dw_Scl_Lcnt(Hs_Clock_Khz,
    I2c_Scl_Min[I2C_HS][I2C_SCL_LOW],  /* tLOW = 0.12 us for 100pf 0.32 us for 400pf */
    I2c_Scl_Min[I2C_HS][I2C_SCL_TF],  /* tf = 0.3 us */
    0);  /* No Offset */
  Write32(Base + DW_IC_HS_SCL_HCNT, Hcnt);
  Write32(Base + DW_IC_HS_SCL_LCNT, Lcnt);
}

/**
 * i2c_init() - initialize the designware i2c master hardware
 * This functions configures and enables the I2C master.
 */
VOID I2c_Init(INTN Speed, INTN Slaveadd)
{
  UINT32 I2c_Status_Cnt;
  UINT32 Base;
  UINT16 Ic_Con;
  UINT32 I2c_Clk_Freq = CONFIG_I2C_CLK_FREQ;

  DBG("Calling I2c_Init\n");
  if (!I2c_Hw_Init_Done)
   I2c_Hw_Init();

  Base = Sys_I2c_Base;
  if (I2c_Bus_Speed != Speed) {
    I2c_Bus_Speed = Speed;
  }

  if (I2c_Bus_Num)
      I2c_Poll_Time = (10 * 1000000) / Speed;
  else
    I2c_Poll_Time = ((10 * 1000000) / Speed) * (I2c_Clk_Freq / 50000000);

  DBG("I2c_Init: Polling time:%d\n", I2c_Poll_Time);
  DBG("I2c_Init: I2c_Bus_Speed:%x\n", I2c_Bus_Speed);
  DBG("I2c_Init: Slaveadd:%d\n", Slaveadd);
  I2c_Status_Cnt = DW_STATUS_WAIT_RETRY;
  /* Disable the adapter and INTNerrupt */
  Write32(Base + DW_IC_ENABLE, 0);
  do {
    MicroSecondDelay(I2c_Poll_Time);
    I2c_Sync();
    if (I2c_Status_Cnt == 0) {
      DBG("I2C disable Timeout\n");
      I2c_Init_Done = 0;
      /* Unset the target adddress */
      Write32(Base + DW_IC_TAR, 0);
      return;
    }
  } while (((Read32(Base + DW_IC_ENABLE_STATUS) & 0x01)) && I2c_Status_Cnt--);
  Write32(Base + DW_IC_INTR_MASK, 0);
  /* set standard and fast speed deviders for high/low periods */
  I2c_Scl_Init(Base, I2c_Clk_Freq, Speed);
  /* Write target Address */
  Write32(Base + DW_IC_TAR, Slaveadd);
  /* Write slave Address */
  Write32(Base + DW_IC_SAR, IC_SAR); /* Address */
  Ic_Con = DW_IC_CON_MASTER | DW_IC_CON_SLAVE_DISABLE | DW_IC_CON_RESTART_EN;

  if (Speed > 400000 && Speed <= 3400000)
    Ic_Con |= (DW_IC_CON_SPEED_STD | DW_IC_CON_SPEED_FAST);
  else if (Speed > 100000 && Speed <= 400000)
    Ic_Con |= DW_IC_CON_SPEED_FAST;
  else
    Ic_Con |= DW_IC_CON_SPEED_STD;

  Write32(Base + DW_IC_CON, Ic_Con);

  I2c_Status_Cnt = DW_STATUS_WAIT_RETRY;
  /* Enable the adapter */
  Write32(Base + DW_IC_ENABLE, 1);
  do {
    MicroSecondDelay(I2c_Poll_Time);
    I2c_Sync();
    if (I2c_Status_Cnt == 0) {
      DBG("I2C enable Timeout\n");
      I2c_Init_Done = 0;
      /* Unset the target adddress */
      Write32(Base + DW_IC_TAR, 0);
      return;
    }
  } while ((!(Read32(Base + DW_IC_ENABLE_STATUS) & 0x01)) && I2c_Status_Cnt--);
  I2c_Init_Done = 1;

  I2c_Set_Bus_Num(I2c_Bus_Num);

}

EFI_STATUS I2c_Set_Target(CHAR8 Chip)
{
  UINT32 Base = Sys_I2c_Base;
  EFI_STATUS Rc = EFI_SUCCESS;

  if (!I2c_Init_Done || Read32(Base + DW_IC_TAR) != Chip) {
    I2c_Init(I2c_Bus_Speed, Chip);

    /* Check if TAR is set */
    if (Read32(Base + DW_IC_TAR) != Chip) {
      DBG("Cannot set the target on I2c bus to %x\n", Chip);
      Rc = EFI_INVALID_PARAMETER;
    }
  }
  return Rc;
}

EFI_STATUS __i2c_write(CHAR8 Chip, UINT32 Addr, INTN alen, CHAR8 *Data, INTN Length)
{
  INTN i;
  INTN Offset = 0;
  UINT32 Page_Size = I2c_Page_Write_Size;
  UINT32 Base = Sys_I2c_Base;
  UINT32 Temp;

  DBG("i2c_write: chip:%d addr:%x alen:%d len:%d\n", Chip, Addr, alen, Length);
  DBG("i2c_write: page_size:%d\n", Page_Size);
  if (I2c_Dw_Wait_Bus_Not_Busy(Base))
    return EFI_NOT_READY;

  /* If addr isn't write page aligned, write the unaligned first bytes */
  if ((Addr % Page_Size) != 0) {
    Temp = (Length < (Page_Size - (Addr % Page_Size)))? Length : Page_Size - (Addr % Page_Size);
    for (i = 0; i < Temp; i++) {
      if (alen == 2)
        Write32(Base + DW_IC_DATA_CMD, (((Addr + i) >> 8) & 0xFF)); /* Write Addr */
      Write32(Base + DW_IC_DATA_CMD, ((Addr + i) & 0xFF)); /* Write Addr */
      Write32(Base + DW_IC_DATA_CMD, Data[Offset + i] & 0xFF);
      I2c_Sync();

      I2c_Dw_Wait_Bus_Not_Busy(Base);
      MicroSecondDelay(3000);
    }
    Length -= i;
    Addr += i;
    Offset += i;
  }


  while (Length > (Page_Size - 1)) {
    if (alen == 2)
      Write32(Base + DW_IC_DATA_CMD, (((Addr) >> 8) & 0xFF)); /* Write Addr */
    Write32(Base + DW_IC_DATA_CMD, ((Addr) & 0xFF)); /* Write Addr */

    for (i = 0; i < Page_Size; i++) {
      Write32(Base + DW_IC_DATA_CMD, Data[Offset + i] & 0xFF);
      I2c_Sync();
      if (EFI_ERROR(I2c_Dw_Wait_Tx_Data(Base)))
        return EFI_NOT_READY;
    }

    I2c_Dw_Wait_Bus_Not_Busy(Base);
    MicroSecondDelay(3100);

    Length -= Page_Size;
    Addr += Page_Size;
    Offset += Page_Size;
  }

  for (i = 0; i < Length; i++) {
    if (alen == 2)
      Write32(Base + DW_IC_DATA_CMD, (((Addr + i) >> 8) & 0xFF)); /*  Write Addr */
    Write32(Base + DW_IC_DATA_CMD, ((Addr + i) & 0xFF)); /* Write Addr */
    Write32(Base + DW_IC_DATA_CMD, Data[Offset + i] & 0xFF);
    I2c_Sync();

    I2c_Dw_Wait_Bus_Not_Busy(Base);
    MicroSecondDelay(3100);
  }

  return EFI_SUCCESS;
}

EFI_STATUS __i2c_read(CHAR8 Chip, UINT32 Addr, INTN alen, CHAR8 *Data, INTN Length)
{
  INTN i;
  INTN Offset = 0;
  INTN Count = 0;
  UINTN Rx_Fifo = I2c_Rx_Buffer;
  UINT32 I2c_Poll = I2c_Poll_Time;
  UINT32 Base = Sys_I2c_Base;
  DBG("i2c_read: chip:%d addr:%x alen:%d len:%d\n", Chip, Addr, alen, Length);

  /* Added delay since it was giving "TX_ABORT" error everytime */
  MicroSecondDelay(3000);
  if (I2c_Dw_Wait_Bus_Not_Busy(Base))
    return EFI_NOT_READY;

  DBG("Write: %d @ %x\n", Addr, Base + DW_IC_DATA_CMD);

  if (alen == 2)
    Write32(Base + DW_IC_DATA_CMD, ((Addr >> 8) & 0xFF)); /* Write Addr */
  Write32(Base + DW_IC_DATA_CMD, (Addr & 0xFF)); /*Write Addr */

  I2c_Sync();
  while (Offset < Length) {
    if (I2c_Dw_Wait_Bus_Not_Busy(Base))
      return EFI_NOT_READY;

    if (I2c_Dw_Check_Errors(Base, alen)) {
      if (alen)
        DBG("writing Chip %02x register Offset %04x\n", Chip, Addr);
      return EFI_CRC_ERROR;
    }

    Count = (((Length - Offset) < Rx_Fifo) ? (Length - Offset) : Rx_Fifo);
    for (i = 0; i < Count; i++) {
      Write32(Base + DW_IC_DATA_CMD, 0x100); /*Read Command */
      I2c_Sync();
      if (I2c_Dw_Check_Errors(Base, alen)) {
        if (alen)
          DBG("reading Chip %02x register "
            "Offset %04x start %04x Length %d\n",
            Chip, Offset + i, Addr, Length);
        return EFI_CRC_ERROR;
      }

      MicroSecondDelay(I2c_Poll / 10);
    }

    /* Extra delay required to read the 1st byte */
    if (Offset == 0)
      MicroSecondDelay(I2c_Poll * 6);
    /* Extra delay required when a byte is received in 1st FIFO buffer */
    MicroSecondDelay((I2c_Poll * 15) / 10);

    for (i = 0; i < Count; i++) {
      if (I2c_Dw_Check_Errors(Base, alen)) {
        if (alen)
          DBG("reading Chip %02x data "
            "Offset %04x start %04x Length %d\n",
            Chip, Offset + i, Addr, Length);
        return EFI_CRC_ERROR;
      }
      MicroSecondDelay((I2c_Poll * 25) / 10);
      Data[Offset + i] = Read32(Base + DW_IC_DATA_CMD);
      I2c_Sync();
    }

    Offset += Count;
  }

  return EFI_SUCCESS;
}

EFI_STATUS I2c_Write(CHAR8 Chip, UINT32 Addr, INTN alen, UINT8 * Buf, INTN Len)
{
  EFI_STATUS Rc = EFI_DEVICE_ERROR; /* signal error */

  if (I2c_Set_Target(Chip) == 0)
    Rc = __i2c_write(Chip, Addr, alen, (CHAR8 *) Buf, Len);

  return Rc;
}

EFI_STATUS I2c_Read(CHAR8 Chip, UINT32 Addr, INTN alen, UINT8 * Buf, INTN Len)
{
  EFI_STATUS Rc = EFI_DEVICE_ERROR; /* signal error */

  if (I2c_Set_Target(Chip) == 0)
    Rc = __i2c_read(Chip, Addr, alen, (CHAR8 *) Buf, Len);

  return Rc;
}

EFI_STATUS I2c_Probe(CHAR8 Chip)
{
  CHAR8 Buf[1];

  I2c_Init(I2c_Bus_Speed, Chip);
  return I2c_Read(Chip, 0, 0, (UINT8 *) Buf, 1);
}

#if defined(CONFIG_I2C_MULTI_BUS)
/*
 * Functions for multiple I2C bus handling
 */
UINTN I2c_Get_Bus_Num(VOID)
{
  return I2c_Bus_Num;
}

EFI_STATUS I2c_Set_Bus_Num(UINTN Bus)
{
  if (Bus >= CONFIG_SYS_MAX_I2C_BUS)
    return EFI_INVALID_PARAMETER;

  I2c_Bus_Num = Bus;

  return EFI_SUCCESS;

}
#endif  /* CONFIG_I2C_MULTI_BUS */

UINTN I2c_Get_Bus_Speed(VOID)
{
  return I2c_Bus_Speed;
}

EFI_STATUS I2c_Set_Bus_Speed(UINTN Speed)
{
  if (Speed > 0 && Speed <= 3400000) {
    if (I2c_Bus_Speed != Speed)
      I2c_Init(Speed, I2c_Device_Addr);
    return EFI_SUCCESS;
  }

  return EFI_INVALID_PARAMETER;
}
#endif  /* CONFIG_HARD_I2C */
