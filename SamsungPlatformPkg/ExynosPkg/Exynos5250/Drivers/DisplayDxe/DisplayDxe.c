/** @file
  Template for Timer Architecture Protocol driver of the ARM flavor

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DevicePath.h>
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>
#include <Platform/Exynos5250.h>
#include "DisplayDxe.h"


typedef struct {
    VENDOR_DEVICE_PATH DisplayDevicePath;
    EFI_DEVICE_PATH EndDevicePath;
} DISPLAY_DEVICE_PATH;

DISPLAY_DEVICE_PATH gDisplayDevicePath =
{
  {
    HARDWARE_DEVICE_PATH,
    HW_VENDOR_DP,
    (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
    (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
    EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    sizeof (EFI_DEVICE_PATH_PROTOCOL),
    0
  }
};

#define LCD_WIDTH  1280
#define LCD_HEIGHT  800

#define VCLK      62946240

#define SRC_CLK    800000000

/**
  This function configures the MIPI-DSIM channel
**/
INT32 s5p_mipi_dsi_wr_data(UINT32 data_id, UINT32 data0, UINT32 data1)
{
  UINT32 DSIM1BaseAddr = PcdGet32(PcdDSIM1Base);
  UINT32 data_cnt = 0;
  UINT32 payload = 0;
  UINT32 timeout_count = 100000;

  MicroSecondDelay(20000);

  /* in case that data count is more then 4 */
  for (data_cnt=0; data_cnt<data1; data_cnt+=4) {
    /*
   * after sending 4bytes per one time,
   * send remainder data less then 4.
   */
  if ((data1 - data_cnt) < 4) {
    if ((data1 - data_cnt) == 3) {
      payload = *(UINT8 *)(data0 + data_cnt) | (*(UINT8 *)(data0 + (data_cnt + 1))) << 8 | (*(UINT8 *)(data0 + (data_cnt + 2))) << 16;
    } else if ((data1 - data_cnt) == 2) {
      payload = *(UINT8 *)(data0 + data_cnt) | (*(UINT8 *)(data0 + (data_cnt + 1))) << 8;
    } else if ((data1 - data_cnt) == 1) {
      payload = *(UINT8 *)(data0 + data_cnt);
    }

    MmioWrite32(DSIM1BaseAddr + DSIM_PAYLOAD, payload);
    /* send 4bytes per one time. */
  } else {
    payload = *(UINT8 *)(data0 + data_cnt) | (*(UINT8 *)(data0 + (data_cnt + 1))) << 8 | \
          (*(UINT8 *)(data0 + (data_cnt + 2))) << 16 | (*(UINT8 *)(data0 + (data_cnt + 3))) << 24;

    MmioWrite32(DSIM1BaseAddr + DSIM_PAYLOAD, payload);
  }
  }

  MmioWrite32(DSIM1BaseAddr + DSIM_PKTHDR, ((((data1 & 0xFF00) >> 8)<<16) | ((data1 & 0xFF)<<8) | ((data_id & 0x3F)<<0)));

  while(1) {
  if(timeout_count == 0)
    return -1;

    if(MmioRead32(DSIM1BaseAddr + DSIM_INTSRC) & (0x1<<29)) {
    MmioWrite32(DSIM1BaseAddr + DSIM_INTSRC, (0x1<<29));
    return 1;
    }
  else if((MmioRead32(DSIM1BaseAddr + DSIM_FIFOCTRL) & 0xF00000) == 0)
    return -1;
  timeout_count--;
  }
}

INT32 lcd_display_on(VOID)
{
  UINT8 initcode_013c[6] = {0x3c, 0x01, 0x03, 0x00, 0x02, 0x00};
  UINT8 initcode_0114[6] = {0x14, 0x01, 0x02, 0x00, 0x00, 0x00};
  UINT8 initcode_0164[6] = {0x64, 0x01, 0x05, 0x00, 0x00, 0x00};
  UINT8 initcode_0168[6] = {0x68, 0x01, 0x05, 0x00, 0x00, 0x00};
  UINT8 initcode_016c[6] = {0x6c, 0x01, 0x05, 0x00, 0x00, 0x00};
  UINT8 initcode_0170[6] = {0x70, 0x01, 0x05, 0x00, 0x00, 0x00};
  UINT8 initcode_0134[6] = {0x34, 0x01, 0x1f, 0x00, 0x00, 0x00};
  UINT8 initcode_0210[6] = {0x10, 0x02, 0x1f, 0x00, 0x00, 0x00};
  UINT8 initcode_0104[6] = {0x04, 0x01, 0x01, 0x00, 0x00, 0x00};
  UINT8 initcode_0204[6] = {0x04, 0x02, 0x01, 0x00, 0x00, 0x00};
  UINT8 initcode_0450[6] = {0x50, 0x04, 0x20, 0x01, 0xfa, 0x00};
  UINT8 initcode_0454[6] = {0x54, 0x04, 0x20, 0x00, 0x50, 0x00};
  UINT8 initcode_0458[6] = {0x58, 0x04, 0x00, 0x05, 0x30, 0x00};
  UINT8 initcode_045c[6] = {0x5c, 0x04, 0x05, 0x00, 0x0a, 0x00};
  UINT8 initcode_0460[6] = {0x60, 0x04, 0x20, 0x03, 0x0a, 0x00};
  UINT8 initcode_0464[6] = {0x64, 0x04, 0x01, 0x00, 0x00, 0x00};
  UINT8 initcode_04a0_1[6] = {0xa0, 0x04, 0x06, 0x80, 0x44, 0x00};
  UINT8 initcode_04a0_2[6] = {0xa0, 0x04, 0x06, 0x80, 0x04, 0x00};
  UINT8 initcode_0504[6] = {0x04, 0x05, 0x04, 0x00, 0x00, 0x00};
  UINT8 initcode_049c[6] = {0x9c, 0x04, 0x0d, 0x00, 0x00, 0x00};

  /* Initialize MIPI LCD */
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_013c, sizeof(initcode_013c)) == -1)
  return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0114, sizeof(initcode_0114)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0164, sizeof(initcode_0164)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0168, sizeof(initcode_0168)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_016c, sizeof(initcode_016c)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0170, sizeof(initcode_0170)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0134, sizeof(initcode_0134)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0210, sizeof(initcode_0210)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0104, sizeof(initcode_0104)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0204, sizeof(initcode_0204)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0450, sizeof(initcode_0450)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0454, sizeof(initcode_0454)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0458, sizeof(initcode_0458)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_045c, sizeof(initcode_045c)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0460, sizeof(initcode_0460)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0464, sizeof(initcode_0464)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_04a0_1, sizeof(initcode_04a0_1)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_04a0_2, sizeof(initcode_04a0_2)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_0504, sizeof(initcode_0504)) == -1)
    return 0;
  MicroSecondDelay(6000);
  if(s5p_mipi_dsi_wr_data(0x29, (UINT32)initcode_049c, sizeof(initcode_049c)) == -1)
    return 0;
  MicroSecondDelay(800000);

  return 1;
}

VOID ConfigureMIPI(VOID)
{
  UINT32 DSIM1BaseAddr = PcdGet32(PcdDSIM1Base);
  UINT32 DSIM_status;
  BOOLEAN config_done = FALSE;

  /* Enable MIPI-DSIM clock */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_DISP1_OFFSET), ~CLK_GATE_DSIM1_MASK,CLK_GATE_DSIM1_MASK);

  while(!config_done) {
    /* Enable MIPI PHY1 */
  MmioAndThenOr32((PcdGet32(PcdPmuBase) +PMU_MIPI_PHY1_CONTROL_OFFSET),  ~(1<<0), (1<<0));
  /* Reset DSIM part of MIPI PHY1 */
  MmioAndThenOr32((PcdGet32(PcdPmuBase) +PMU_MIPI_PHY1_CONTROL_OFFSET),  ~(1<<2), (1<<2));

  /* DSIM SW Reset */
  MmioOr32(DSIM1BaseAddr + DSIM_SWRST, (1<<0));

  /* Disable swap of Dp/Dn channel of data and clock lanes */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PHYACCHR1, ~(0x3<<0), ((0 & 0x3)<<0));

  /* DSIM SW Reset */
  MmioOr32(DSIM1BaseAddr + DSIM_SWRST, (1<<0));

  /* Initialize FIFO pointer */
  MmioAnd32(DSIM1BaseAddr + DSIM_FIFOCTRL, ~(0x1F<<0));
  MicroSecondDelay(10000);
  MmioOr32(DSIM1BaseAddr + DSIM_FIFOCTRL, (0x1F<<0));

  /* DSI configuration */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CONFIG, ~((0x1<<28) | (0x1F<<20) | (0x3<<5)), (0x3<<5));
  MmioOr32(DSIM1BaseAddr + DSIM_CONFIG, ((0x1<<0)|(0x1<<1)|(0x1<<2)|(0x1<<3)|(0x1<<4)));

  /* clock configuration */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CLKCTRL, ~(0x3<<25), (0x0<<25));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PHYACCHR, ~(0x7<<5), ((0x1<<14)|(0x3<<5)));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PLLCTRL, ~(0x7FFFF<<1),  ((3<<13)|(115<<4)|(1<<1)));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PLLCTRL, ~(0xF<<28), (0x0<<28));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PLLCTRL, ~(0x7<<20), (0x0<<20));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PLLCTRL, ~(0xF<<24), (0x8<<24));
  MmioWrite32(DSIM1BaseAddr + DSIM_PLLTMR, 500);
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CLKCTRL, ~(0x1<<27), (0x0<<27));

  /* Enable PLL */
  MmioWrite32(DSIM1BaseAddr + DSIM_INTSRC, (0x1<<31));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_PLLCTRL, ~(0x1<<23), (0x1<<23));
  while(1) {
    if(MmioRead32(DSIM1BaseAddr + DSIM_STATUS) & (0x1<<31))
      break;
  }

  /* Enable byte clock */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CLKCTRL, ~(0x1<<24), (0x1<<24));
  /* Enable escape clock */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CLKCTRL, ~((0x1<<28) | (0xFFFF<<0)), ((0x1<<28) | (144<<0)));
  /* Enable escape clock data and clock lanes */
  MmioOr32(DSIM1BaseAddr + DSIM_CLKCTRL, (0x1F<<19));

  MicroSecondDelay(100000);

  while(1) {
    DSIM_status = MmioRead32(DSIM1BaseAddr + DSIM_STATUS);
    if((DSIM_status & (0xF<<0)) && ((DSIM_status & (0x1<<8)) || (DSIM_status & (0x1<<10))))
      break;
  }

  /* BTA sequence counters */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_ESCMODE, ~(0x7FF<<21), ((0xF &0x7FF) << 21));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_TIMEOUT, ~(0xFF<<16), (0xFF<<16));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_TIMEOUT, ~(0xFFFF<<0), (0xFFFF<<0));

    /* Enable HS clock */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CLKCTRL, ~(0x1<<31), (0x1<<31));

  /* Set CPU transfer mode */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_ESCMODE, ~(0x1<<7), (0x1<<7));

  /* Set display mode */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_MVPORCH, ~((0xF<<28)|(0x7FF<<16)|(0x7FF<<0)), ((0xF<<28)|(0x4<<16)|(0x4<<0)));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_MHPORCH, ~((0xFFFF<<16)|(0xFFFF<<0)), ((0x4<<16)|(0x4<<0)));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_MSYNC, ~((0x3FF<<22)|(0xFFFF<<0)), ((0x4<<22)|(0x4<<0)));

  MmioAnd32(DSIM1BaseAddr + DSIM_MDRESOL, ~(0x1<<31));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_MDRESOL, ~((0x7FF<<16)|(0x7FF<<0)), ((0x1<<31)|(LCD_HEIGHT<<16)|(LCD_WIDTH<<0)));
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_CONFIG, ~((0x3<<26)|(0x1<<25)|(0x3<<18)|(0x7<<12)|(0x3<<16)|(0x7<<8)),  \
                              ((0x1<<26)|(0x1<<25)|(0x7<<12)));

  /* Clear interrupt status */
  MmioWrite32(DSIM1BaseAddr + DSIM_INTSRC, (0x1<<29));

  if(lcd_display_on() == 1)
    config_done = TRUE;

  /* Reset CPU transfer mode */
  MmioAndThenOr32(DSIM1BaseAddr + DSIM_ESCMODE, ~(0x1<<7), (0x0<<7));

  if(!config_done)
    MmioOr32(DSIM1BaseAddr + DSIM_SWRST, (1<<0));  /* DSIM SW Reset */    
  }
}

VOID s5p_mipi_dsi_func_reset(VOID)
{
  UINT32 DSIM1BaseAddr = PcdGet32(PcdDSIM1Base);

  MmioOr32(DSIM1BaseAddr + DSIM_SWRST, (1<<16));
}

/**
  This function configures the Power Domain of the LCD 0 Module to Normal Mode.
**/
VOID ConfigurePower(VOID)
{
  UINT32 PrevGateState;

  /* Enable FIMD1 power domain */
  PrevGateState = MmioRead32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_DISP1_OFFSET));
  MmioWrite32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_DISP1_OFFSET), 0xFFFFFFFF);

  MmioWrite32((PcdGet32(PcdPmuBase) + PMU_DISP1_CONFIGURATION_OFFSET),  LOCAL_PWR_ENABLE);
  while( (MmioRead32((PcdGet32(PcdPmuBase) + PMU_DISP1_STATUS_OFFSET))  & LOCAL_PWR_ENABLE) != \
               LOCAL_PWR_ENABLE);

  MmioWrite32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_DISP1_OFFSET), PrevGateState);
}

/**
  This function configures Clock Source,Clock gating,Clock Divider and Mask values for the
  FIMD0 in the LCD0 Module

**/
VOID ConfigureClk(VOID)
{
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLK_GATE_IP_DISP1_OFFSET),  \
      ~CLK_GATE_FIMD1_MASK,CLK_GATE_FIMD1_MASK);

  /* MPLL is the clock source of FIMD1 IP */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLK_SRC_DISP1_0_OFFSET),  \
      ~CLK_SRC_FIMD1_MASK, CLK_SRC_FIMD1_SEL(FIMD1_SCLKMPLL));

  /* Considering MPLL=800000000(800 MHz), SCLK_FIMD0=800000000(800 MHz) => DIV => (800/800) => 1
  The DIV value to be programmed should be (1 -1) = 0 */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLK_DIV_DISP1_0_OFFSET),    \
      ~CLK_DIV_FIMD1_MASK, CLK_DIV_FIMD1_SEL(FIMD1_CLK_DIV));
  
  MmioOr32((PcdGet32(PcdCmuBase) + CLK_SRC_MASK_DISP1_0_OFFSET), CLK_SRC_DISP1_0_UNMASK);
}

VOID lcd_power_on(VOID)
{
  EFI_STATUS    Status;
  EXYNOS_GPIO *Gpio;

  Status = gBS->LocateProtocol(&gSamsungPlatformGpioProtocolGuid, NULL, (VOID **)&Gpio);
  ASSERT_EFI_ERROR(Status);

  /* reset */
  Gpio->Set(Gpio,LCD_RESET,GPIO_MODE_OUTPUT_1);
  MicroSecondDelay(20000);
  Gpio->Set(Gpio,LCD_RESET,GPIO_MODE_OUTPUT_0);
  MicroSecondDelay(20000);
  Gpio->Set(Gpio,LCD_RESET,GPIO_MODE_OUTPUT_1);
  MicroSecondDelay(20000);

  /* power */
  Gpio->Set(Gpio,LCD_POWER,GPIO_MODE_OUTPUT_0);
  MicroSecondDelay(20000);
  Gpio->Set(Gpio,LCD_POWER,GPIO_MODE_OUTPUT_1);
  MicroSecondDelay(20000);
  
  /*backlight */
  Gpio->Set(Gpio,LCD_BACKLIGHT,GPIO_MODE_OUTPUT_0);
  MicroSecondDelay(20000);
  Gpio->Set(Gpio,LCD_BACKLIGHT,GPIO_MODE_OUTPUT_1);
  MicroSecondDelay(20000);
}


VOID LCD_Initialize(VOID)
{
  UINTN div;
  UINT32 Fimd1BaseAddr = PcdGet32(PcdFIMD1Base);
  UINT32 FBAddr = PcdGet32(PcdFrameBufferBase);
  
  gBS->SetMem((VOID *)FBAddr, (LCD_WIDTH*LCD_HEIGHT*4), 0x0);

  ConfigurePower();

  /* Power up the LCD */
  lcd_power_on();

  /* Initialize MIPI-DSIM */
  ConfigureMIPI();

  ConfigureClk();

  /* Set FIMD1 bypass */
  MmioOr32((PcdGet32(PcdSysBase) + SYS_DISP1BLK_CFG_OFFSET), FIMDBYPASS_DISP1);

  /* Configure FIMD */
  MmioAndThenOr32(Fimd1BaseAddr + VIDCON1_OFFSET, ~S5P_VIDCON1_FIXVCLK_MASK, (S5P_VIDCON1_IVCLK_RISING_EDGE | \
            S5P_VIDCON1_FIXVCLK_RUN));

  MmioOr32(Fimd1BaseAddr + SHADOWCON_OFFSET, S5P_SHADOWCON_PROTECT(0));
  
  div = SRC_CLK / VCLK;

  MmioAndThenOr32(Fimd1BaseAddr + VIDCON0_OFFSET, ~S5P_VIDCON0_CLKVAL_F_MASK, (S5P_VIDCON0_CLKDIR_DIVIDED | \
              S5P_VIDCON0_CLKVAL_F(div - 1) | S5P_VIDCON0_ENVID_ENABLE | S5P_VIDCON0_ENVID_F_ENABLE));
  MmioOr32(Fimd1BaseAddr + VIDTCON0_OFFSET, (S5P_VIDTCON0_VBPD(3) | S5P_VIDTCON0_VFPD(3) | S5P_VIDTCON0_VSPW(3)));
  MmioOr32(Fimd1BaseAddr + VIDTCON1_OFFSET, (S5P_VIDTCON1_HBPD(3) | S5P_VIDTCON1_HFPD(3) | S5P_VIDTCON1_HSPW(3)));

  MmioOr32(Fimd1BaseAddr + VIDTCON2_OFFSET, (S5P_VIDTCON2_HOZVAL(LCD_WIDTH - 1) | S5P_VIDTCON2_LINEVAL(LCD_HEIGHT - 1)));

  MmioWrite32(Fimd1BaseAddr + VIDADDR_START0_OFFSET(0), FBAddr);
  MmioWrite32(Fimd1BaseAddr + VIDADDR_END0_OFFSET(0), (FBAddr + (LCD_WIDTH * LCD_HEIGHT * 4)));
  MmioWrite32(Fimd1BaseAddr + VIDADDR_SIZE_OFFSET(0), (S5P_VIDADDR_PAGEWIDTH(LCD_WIDTH * 4) | S5P_VIDADDR_OFFSIZE(0)));

  MmioWrite32(Fimd1BaseAddr + VIDOSD_A_OFFSET(0), (S5P_VIDOSD_LEFT_X(0) | S5P_VIDOSD_TOP_Y(0)));
  MmioWrite32(Fimd1BaseAddr + VIDOSD_B_OFFSET(0), (S5P_VIDOSD_RIGHT_X(LCD_WIDTH - 1) | S5P_VIDOSD_BOTTOM_Y(LCD_HEIGHT - 1)));
  MmioWrite32(Fimd1BaseAddr + VIDOSD_C_OFFSET(0), S5P_VIDOSD_SIZE(LCD_WIDTH * LCD_HEIGHT));

  MmioOr32(Fimd1BaseAddr + SHADOWCON_OFFSET, S5P_SHADOWCON_CH_ENABLE(0));

  MmioAndThenOr32(Fimd1BaseAddr + WINCON_OFFSET(0), ~(S5P_WINCON_BURSTLEN_MASK | S5P_WINCON_BPPMODE_MASK), \
            (S5P_WINCON_WSWP_ENABLE | S5P_WINCON_BURSTLEN_16WORD | S5P_WINCON_BPPMODE_24BPP_888 | S5P_WINCON_ENWIN_ENABLE));
  
  MmioAnd32(Fimd1BaseAddr + SHADOWCON_OFFSET, ~(S5P_SHADOWCON_PROTECT(0)));

#if defined(LCD_MIPI_TC358764)
  s5p_mipi_dsi_func_reset();
#endif
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

      for(i=0;i<Height;i++) {
  VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
       (DestinationY + i)*This->Mode->Info->PixelsPerScanLine*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + \
       DestinationX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

        for(j=0;j<Width;j++) {
    gBS->CopyMem((VOID *)VidBuf, (VOID *)BltBuf, sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    VidBuf += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  }
      }
      break;

    case EfiBltVideoToBltBuffer:
      if(Delta == 0)
        Delta = Width * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

      for(i=0;i<Height;i++) {
  VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
       (SourceY + i)*This->Mode->Info->PixelsPerScanLine*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + \
       SourceX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  BltBuf = (UINT8 *)((UINT32)BltBuffer + (DestinationY + i)*Delta + DestinationX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

        for(j=0;j<Width;j++) {
    gBS->CopyMem((VOID *)BltBuf, (VOID *)VidBuf, sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    VidBuf += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    BltBuf += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  }
      }
      break;

    case EfiBltBufferToVideo:
      if(Delta == 0)
        Delta = Width * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

      for(i=0;i<Height;i++) {
  VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
       (DestinationY + i)*This->Mode->Info->PixelsPerScanLine*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + \
       DestinationX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  BltBuf = (UINT8 *)((UINT32)BltBuffer + (SourceY + i)*Delta + SourceX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

        for(j=0;j<Width;j++) {
    gBS->CopyMem((VOID *)VidBuf, (VOID *)BltBuf, sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    VidBuf += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    BltBuf += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  }
      }
      break;

    case EfiBltVideoToVideo:
      for(i=0;i<Height;i++) {
  VidBuf = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
       (SourceY + i)*This->Mode->Info->PixelsPerScanLine*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + \
       SourceX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  VidBuf1 = (UINT8 *)((UINT32)This->Mode->FrameBufferBase + \
       (DestinationY + i)*This->Mode->Info->PixelsPerScanLine*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + \
       DestinationX*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

        for(j=0;j<Width;j++) {
    gBS->CopyMem((VOID *)VidBuf1, (VOID *)VidBuf, sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
    VidBuf += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    VidBuf1 += sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  }
      }
      break;

    default:
      ASSERT_EFI_ERROR(EFI_SUCCESS);
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
  UINT32 FBAddr = PcdGet32(PcdFrameBufferBase);

  /* Initialize Display */
  LCD_Initialize();
  if(gDisplay.Mode == NULL){
    Status = gBS->AllocatePool(
        EfiBootServicesData,
        sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE),
        (VOID **)&gDisplay.Mode
        );
    ASSERT_EFI_ERROR(Status);
    ZeroMem(gDisplay.Mode,sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE));
  }
  if(gDisplay.Mode->Info==NULL){
    Status = gBS->AllocatePool(
        EfiBootServicesData,
        sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION),
        (VOID **)&gDisplay.Mode->Info
        );
    ASSERT_EFI_ERROR(Status);
    ZeroMem(gDisplay.Mode->Info,sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
  }
  /* Fill out mode information */
  gDisplay.Mode->MaxMode = 1;
  gDisplay.Mode->Mode = 0;
  gDisplay.Mode->Info->Version = 0;
  gDisplay.Mode->Info->HorizontalResolution = LCD_WIDTH;
  gDisplay.Mode->Info->VerticalResolution = LCD_HEIGHT;
  gDisplay.Mode->Info->PixelFormat = PixelBlueGreenRedReserved8BitPerColor;
  gDisplay.Mode->Info->PixelsPerScanLine = LCD_WIDTH;
  gDisplay.Mode->SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
  gDisplay.Mode->FrameBufferBase = FBAddr;
  gDisplay.Mode->FrameBufferSize = (LCD_WIDTH * LCD_HEIGHT * 4);
 
#if 0
  Status = gBS->InstallMultipleProtocolInterfaces (
                   &ImageHandle,
                   &DevicePathProtocolGuid,
                   &gDisplayDevicePath,
                   &GraphicsOutputProtocolGuid,
                   &gDisplay,
                   NULL);
#else
  {
    EFI_HANDLE      gUEFIDisplayHandle = NULL;
     Status = gBS->InstallMultipleProtocolInterfaces (
                   &gUEFIDisplayHandle,
                   &DevicePathProtocolGuid,
                   &gDisplayDevicePath,
                   &GraphicsOutputProtocolGuid,
                   &gDisplay,
                   NULL);

  }
#endif

  return Status;
}
