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

#ifndef _I2CLIB_H_
#define _I2CLIB_H_

#include <Library/I2C.h>

#define CONFIG_I2C_MULTI_BUS 1

#ifndef CONFIG_SYS_I2C_SLAVE
#define CONFIG_SYS_I2C_SLAVE  0x52
#endif

/*
 * Configuration items.
 */
#define I2C_RXTX_LEN  16  /* maximum tx/rx buffer length */

#if defined(CONFIG_I2C_MULTI_BUS)
#if !defined(CONFIG_SYS_MAX_I2C_BUS)
#define CONFIG_SYS_MAX_I2C_BUS    2
#endif
#define I2C_GET_BUS()    I2c_Get_Bus_Num()
#define I2C_SET_BUS(a)    I2c_Set_Bus_Num(a)
#else
#define CONFIG_SYS_MAX_I2C_BUS    1
#define I2C_GET_BUS()    0
#define I2C_SET_BUS(a)
#endif

/* define the I2C bus number for RTC and DTT if not already done */
#if !defined(CONFIG_SYS_RTC_BUS_NUM)
#define CONFIG_SYS_RTC_BUS_NUM    0
#endif
#if !defined(CONFIG_SYS_DTT_BUS_NUM)
#define CONFIG_SYS_DTT_BUS_NUM    0
#endif
#if !defined(CONFIG_SYS_SPD_BUS_NUM)
#define CONFIG_SYS_SPD_BUS_NUM    1
#endif

#ifndef I2C_SOFT_DECLARATIONS
#  define I2C_SOFT_DECLARATIONS
#endif

#define I2C_BASE       0x10511000


#define CONFIG_HARD_I2C       1
#define CONFIG_I2C_CLK_FREQ		250000000
#define CONFIG_DW_I2C_TX_BUFFER_DEPTH	16
#define CONFIG_DW_I2C_RX_BUFFER_DEPTH	16
#define CONFIG_I2C_MULTI_BUS    1

#define SS_SCL_HCNT  250
#define SS_SCL_LCNT  250
#define FS_SCL_HCNT  62
#define FS_SCL_LCNT  63

#define IC_SAR    0x52

#define MAX_BUF_LEN  16

/*
 * Registers offset
 */
#define DW_IC_CON    0x0
#define DW_IC_TAR    0x4
#define DW_IC_SAR    0x8
#define DW_IC_DATA_CMD    0x10
#define DW_IC_SS_SCL_HCNT  0x14
#define DW_IC_SS_SCL_LCNT  0x18
#define DW_IC_FS_SCL_HCNT  0x1c
#define DW_IC_FS_SCL_LCNT  0x20
#define DW_IC_HS_SCL_HCNT  0x24
#define DW_IC_HS_SCL_LCNT  0x28
#define DW_IC_INTR_STAT    0x2c
#define DW_IC_INTR_MASK    0x30
#define DW_IC_RAW_INTR_STAT  0x34
#define DW_IC_CLR_INTR    0x40
#define DW_IC_CLR_RX_UNDER  0x44
#define DW_IC_CLR_RX_OVER  0x48
#define DW_IC_CLR_TX_ABRT  0x54
#define DW_IC_CLR_ACTIVITY  0x5c
#define DW_IC_CLR_STOP_DET  0x60
#define DW_IC_CLR_START_DET  0x64
#define DW_IC_ENABLE    0x6c
#define DW_IC_STATUS    0x70
#define DW_IC_TXFLR    0x74
#define DW_IC_RXFLR    0x78
#define DW_IC_TX_ABRT_SOURCE  0x80
#define DW_IC_ENABLE_STATUS  0x9c
#define DW_IC_COMP_PARAM_1  0xf4
#define DW_IC_COMP_TYPE    0xfc

#define DW_SIGNATURE    0x44570000  /* 'D' 'W' */
#define DW_LE_BUS    0x1234
#define DW_BE_BUS    0x4321

#define DW_IC_CON_MASTER    0x1
#define DW_IC_CON_SPEED_STD    0x2
#define DW_IC_CON_SPEED_FAST    0x4
#define DW_IC_CON_10BITADDR_MASTER  0x10
#define DW_IC_CON_RESTART_EN    0x20
#define DW_IC_CON_SLAVE_DISABLE    0x40

#define DW_IC_TAR_10BITS    (1 << 12)

#define DW_IC_INTR_RX_UNDER  0x01
#define DW_IC_INTR_RX_OVER  0x02
#define DW_IC_INTR_TX_EMPTY  0x10
#define DW_IC_INTR_TX_ABRT  0x40
#define DW_IC_INTR_ACTIVITY  0x100
#define DW_IC_INTR_STOP_DET  0x200
#define DW_IC_INTR_START_DET  0x400
#define DW_IC_ERR_CONDITION  (DW_IC_INTR_RX_UNDER | \
         DW_IC_INTR_RX_OVER | \
         DW_IC_INTR_TX_ABRT)

#define DW_IC_STATUS_ACTIVITY  0x1

#define DW_IC_ERR_TX_ABRT  0x1

/*
 * status codes
 */
#define STATUS_IDLE      0x0
#define STATUS_WRITE_IN_PROGRESS  0x1
#define STATUS_READ_IN_PROGRESS    0x2

/* timeout and retry values */
#define DW_BUS_WAIT_TIMEOUT  20 /* ms */
#define DW_RX_DATA_RETRY  5
#define DW_TX_DATA_RETRY  5
#define DW_STATUS_WAIT_RETRY  5
#define DW_BUS_WAIT_INACTIVE  10

/*
 * hardware abort codes from the DW_IC_TX_ABRT_SOURCE register
 *
 * only expected abort codes are listed here
 * refer to the datasheet for the full list
 */
#define ABRT_7B_ADDR_NOACK  0
#define ABRT_10ADDR1_NOACK  1
#define ABRT_10ADDR2_NOACK  2
#define ABRT_TXDATA_NOACK  3
#define ABRT_GCALL_NOACK  4
#define ABRT_GCALL_READ    5
#define ABRT_SBYTE_ACKDET  7
#define ABRT_SBYTE_NORSTRT  9
#define ABRT_10B_RD_NORSTRT  10
#define ARB_MASTER_DIS    11
#define ARB_LOST    12
#define ARB_OK      0xFF

/* I2C SCL counter macros */
enum {
  I2C_SS = 0,
  I2C_FS,
  I2C_HS_400PF,
  I2C_HS_100PF,
};

#define I2C_HS I2C_HS_400PF

enum {
  I2C_SCL_HIGH = 0,
  I2C_SCL_LOW,
  I2C_SCL_TF,
};

#define Byte_Swap32(UINT32b) \
  ((UINT32b & 0xFF000000) >> 24 | \
   (UINT32b & 0x00FF0000) >>  8 | \
   (UINT32b & 0x0000FF00) <<  8 | \
   (UINT32b & 0x000000FF) << 24)

/* Bus specific values */
typedef struct DW_I2C_S {
  UINT32 Base;
  UINT32 Bus_Endian;
  UINT32 Bus_Speed;
  UINT32 Rx_Buffer;
  UINT32 Tx_Buffer;
  UINT32 Device_Addr;
  UINT32 Device_Addr_Len;
  UINT32 Page_Write_Size;
  UINT32 Poll_Time;
  UINT32 Clk_Base;
  UINT32 Init_Done;
} DW_I2C_T;

#if defined(CONFIG_I2C_MULTI_BUS)
#define GET_BUS_NUM  I2c_Bus_Num
#else
#define GET_BUS_NUM  0
#endif /* CONFIG_I2C_MULTI_BUS */

#define Sys_I2c_Base  (Dw_I2c[GET_BUS_NUM].Base)
#define I2c_Bus_Endian  (Dw_I2c[GET_BUS_NUM].Bus_Endian)
#define I2c_Bus_Speed  (Dw_I2c[GET_BUS_NUM].Bus_Speed)
#define I2c_Rx_Buffer  Dw_I2c[GET_BUS_NUM].Rx_Buffer
#define I2c_Tx_Buffer  Dw_I2c[GET_BUS_NUM].Tx_Buffer
#define I2c_Device_Addr  Dw_I2c[GET_BUS_NUM].Device_Addr
#define I2c_Device_Addr_Len  Dw_I2c[GET_BUS_NUM].Device_Addr_Len
#define I2c_Page_Write_Size  Dw_I2c[GET_BUS_NUM].Page_Write_Size
#define I2c_Poll_Time  Dw_I2c[GET_BUS_NUM].Poll_Time
#define I2c_Clk_Base  Dw_I2c[GET_BUS_NUM].Clk_Base
#define I2c_Init_Done  Dw_I2c[GET_BUS_NUM].Init_Done


#endif /* _I2CLIB_H_*/
