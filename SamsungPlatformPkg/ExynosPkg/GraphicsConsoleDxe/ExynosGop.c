/** @file
  Template for Timer Architecture Protocol driver of the ARM flavor

  Copyright (c) 2011, Samsung Electronics Co. All rights reserved.<BR>

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
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>
#include "ExynosGop.h"
#include "GraphicsConsole.h"


//#define LCD_AMS369FG06
#define LCD_WA101S

#ifdef LCD_AMS369FG06
#define LCD_WIDTH	480
#define LCD_HEIGHT	800
#define VCLK		24360000
#endif

#ifdef LCD_WA101S
#define LCD_WIDTH	1366
#define LCD_HEIGHT	768
#define VCLK		72332000
#endif

#define SRC_CLK		133333333
#define FB_ADDR		0x4E000000

/**
  This function configures the Power Domain of the LCD 0 Module to Normal Mode.
**/
VOID ConfigureLcdPower(VOID)
{
  UINT32 PrevGateState;

  /* Enable LCD0 power domain */
  PrevGateState = MmioRead32((PcdGet32(PcdCmuBase) + CLKGATE_IP_LCD0_OFFSET));

  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLKGATE_IP_LCD0_OFFSET),	\
		~CLK_PPMULCD0_MASK,CLK_PPMULCD0_MASK);
  MmioWrite32((PcdGet32(PcdPmuBase) + PMU_LCD0_CONF_OFFSET),		\
		LCD0_PWR_NRML_MODE);
  while( (MmioRead32((PcdGet32(PcdPmuBase) + PMU_LCD0_STAT_OFFSET))	\
	 & LCD0_PWR_NRML_MODE) != LCD0_PWR_NRML_MODE);

  MmioWrite32((PcdGet32(PcdCmuBase) + CLKGATE_IP_LCD0_OFFSET), PrevGateState);
}

/**
  This function configures Clock Source,Clock gating,Clock Divider and Mask values for the
  FIMD0 in the LCD0 Module

**/
VOID ConfigureLcd0Clk(VOID)
{
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLKGATE_IP_LCD0_OFFSET),	\
			~CLKGATE_FIMD0_MASK,CLKGATE_FIMD0_MASK);
  /* MPLL is the clock source of FIMD0 IP */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLKSRC_LCD0_OFFSET),	\
			~CLKSRC_FIMD0_MASK, CLKSRC_FIMD0_SEL(FIMD0_SCLKMPLL));

  /* Considering MPLL=800000000(800 MHz), SCLK_FIMD0=133333333(133.33 MHz) => DIV => (800/133.33) => 6
  The DIV value to be programmed should be (6 -1) = 5 */
  MmioAndThenOr32((PcdGet32(PcdCmuBase) + CLKDIV_LCD0_OFFSET),		\
			~CLKDIV_FIMD0_MASK, CLKDIV_FIMD0_SEL(FIMD0_CLK_DIV));

  MmioOr32((PcdGet32(PcdCmuBase) + CLKSRC_MASK_LCD0_OFFSET), FIMD0_UNMASK);
}

/**
  This function does the necessary GPIO configuration for the Initialization of the LCD

**/
#ifdef LCD_WA101S
VOID ConfigureLcdGpio(VOID)
{
  EFI_STATUS    Status;
  EXYNOS_GPIO *Gpio;

  Status = gBS->LocateProtocol(&gSamsungPlatformGpioProtocolGuid, NULL, (VOID **)&Gpio);
  ASSERT_EFI_ERROR(Status);

/********************************************************************************
	GPIO Control
	Pull Up/Down
	Driving strenght Setting of GPIO Port F0 for LCD
********************************************************************************/
  Gpio->Set(Gpio,LCD_HSYNC,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VSYNC,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VDEN,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VCLK,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_0,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_1,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_2,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_3,GPIO_MODE_SPECIAL_FUNCTION_2);

  Gpio->SetPull(Gpio,LCD_HSYNC,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VSYNC,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VDEN,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VCLK,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_0,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_1,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_2,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_3,GPIO_PULL_NONE);


  Gpio->SetStrength(Gpio,LCD_HSYNC,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VSYNC,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VDEN,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VCLK,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_0,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_1,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_2,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_3,GPIO_DRV_4X);

/********************************************************************************
	GPIO Control
	Pull Up/Down
	Driving strenght Setting of GPIO Port F1 for LCD
********************************************************************************/
  Gpio->Set(Gpio,LCD_VD_4,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_5,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_6,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_7,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_8,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_9,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_10,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_11,GPIO_MODE_SPECIAL_FUNCTION_2);

  Gpio->SetPull(Gpio,LCD_VD_4,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_5,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_6,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_7,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_8,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_9,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_10,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_11,GPIO_PULL_NONE);


  Gpio->SetStrength(Gpio,LCD_VD_4,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_5,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_6,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_7,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_8,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_9,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_10,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_11,GPIO_DRV_4X);

/********************************************************************************
	GPIO Control
	Pull Up/Down
	Driving strenght Setting of GPIO Port F2 for LCD
********************************************************************************/
  Gpio->Set(Gpio,LCD_VD_12,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_13,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_14,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_15,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_16,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_17,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_18,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_19,GPIO_MODE_SPECIAL_FUNCTION_2);

  Gpio->SetPull(Gpio,LCD_VD_12,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_13,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_14,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_15,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_16,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_17,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_18,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_19,GPIO_PULL_NONE);


  Gpio->SetStrength(Gpio,LCD_VD_12,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_13,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_14,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_15,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_16,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_17,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_18,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_19,GPIO_DRV_4X);

/********************************************************************************
	GPIO Control
	Pull Up/Down
	Driving strenght Setting of GPIO Port F3 for LCD
********************************************************************************/
  Gpio->Set(Gpio,LCD_VD_20,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_21,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_22,GPIO_MODE_SPECIAL_FUNCTION_2);
  Gpio->Set(Gpio,LCD_VD_23,GPIO_MODE_SPECIAL_FUNCTION_2);

  Gpio->SetPull(Gpio,LCD_VD_20,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_21,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_22,GPIO_PULL_NONE);
  Gpio->SetPull(Gpio,LCD_VD_23,GPIO_PULL_NONE);


  Gpio->SetStrength(Gpio,LCD_VD_20,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_21,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_22,GPIO_DRV_4X);
  Gpio->SetStrength(Gpio,LCD_VD_23,GPIO_DRV_4X);

  /* Set FIMD0 bypass */
  MmioOr32((PcdGet32(PcdSysBase) + SYS_DISPLAY_CONTROL_OFFSET), FIMDBYPASS_LBLK0);

}

/**
  This function configures POrt D0 Pin1 as the Output Pin to control the Enable/Disable of
  LCD BackLight

**/
VOID EnableBackLight(VOID)
{
  EFI_STATUS    Status;
  EXYNOS_GPIO *Gpio;

  Status = gBS->LocateProtocol(&gSamsungPlatformGpioProtocolGuid, NULL, (VOID **)&Gpio);
  ASSERT_EFI_ERROR(Status);

  Gpio->Set(Gpio,LCD_BACKLIGHT,GPIO_MODE_OUTPUT_1);
}

VOID lcd_on(VOID)
{
}
#endif


VOID LCD_Initialize(VOID)
{
  UINTN div;
  UINT32 Fimd0BaseAddr;
  gBS->SetMem((VOID *)FB_ADDR, (LCD_WIDTH*LCD_HEIGHT*4), 0x0);

  Fimd0BaseAddr = PcdGet32(PcdFIMD0Base);
  ConfigureLcdPower();
  ConfigureLcdGpio();
  ConfigureLcd0Clk();

  /* Configure FIMD */
  MmioAndThenOr32(Fimd0BaseAddr + VIDCON0_OFFSET, ~S5P_VIDCON0_VIDOUT_MASK, S5P_VIDCON0_VIDOUT_RGB);

  MmioAndThenOr32(Fimd0BaseAddr + VIDCON2_OFFSET, ~(S5P_VIDCON2_WB_MASK | S5P_VIDCON2_TVFORMATSEL_MASK | \
		  S5P_VIDCON2_TVFORMATSEL_YUV_MASK), S5P_VIDCON2_WB_DISABLE);

  MmioAndThenOr32(Fimd0BaseAddr + VIDCON0_OFFSET, ~S5P_VIDCON0_PNRMODE_MASK, S5P_VIDCON0_PNRMODE_RGB_P);

#ifdef LCD_WA101S
  MmioOr32(Fimd0BaseAddr + VIDCON1_OFFSET, (S5P_VIDCON1_IVCLK_RISING_EDGE | S5P_VIDCON1_IHSYNC_INVERT | \
	   S5P_VIDCON1_IVSYNC_INVERT | S5P_VIDCON1_IVDEN_NORMAL));

  MmioOr32(Fimd0BaseAddr + VIDTCON0_OFFSET, (S5P_VIDTCON0_VBPDE(-1) | S5P_VIDTCON0_VBPD(13) | \
	   S5P_VIDTCON0_VFPD(2) | S5P_VIDTCON0_VSPW(4)));

  MmioOr32(Fimd0BaseAddr + VIDTCON1_OFFSET, (S5P_VIDTCON1_VFPDE(-1) | S5P_VIDTCON1_HBPD(79) | \
	   S5P_VIDTCON1_HFPD(47) | S5P_VIDTCON1_HSPW(31)));

#endif

  MmioOr32(Fimd0BaseAddr + VIDTCON2_OFFSET, (S5P_VIDTCON2_HOZVAL(LCD_WIDTH - 1) | S5P_VIDTCON2_LINEVAL(LCD_HEIGHT - 1)));

  MmioAndThenOr32(Fimd0BaseAddr + WINCON_OFFSET(0), ~(S5P_WINCON_BITSWP_ENABLE | S5P_WINCON_BYTESWP_ENABLE | \
		  S5P_WINCON_HAWSWP_ENABLE | S5P_WINCON_WSWP_ENABLE | S5P_WINCON_BURSTLEN_MASK | \
		  S5P_WINCON_BPPMODE_MASK | S5P_WINCON_INRGB_MASK | S5P_WINCON_DATAPATH_MASK), \
		  (S5P_WINCON_WSWP_ENABLE | S5P_WINCON_BURSTLEN_16WORD | \
		  S5P_WINCON_BPPMODE_24BPP_888));

  MmioOr32(Fimd0BaseAddr + WINSHMAP_OFFSET, S5P_WINSHMAP_PROTECT(0));
  MmioWrite32(Fimd0BaseAddr + VIDOSD_A_OFFSET(0), (S5P_VIDOSD_LEFT_X(0) | S5P_VIDOSD_TOP_Y(0)));
  MmioWrite32(Fimd0BaseAddr + VIDOSD_B_OFFSET(0), (S5P_VIDOSD_RIGHT_X(LCD_WIDTH - 1) | \
	      S5P_VIDOSD_BOTTOM_Y(LCD_HEIGHT - 1)));
  MmioAnd32(Fimd0BaseAddr + WINSHMAP_OFFSET, ~(S5P_WINSHMAP_PROTECT(0)));

  MmioWrite32(Fimd0BaseAddr + VIDOSD_C_OFFSET(0), S5P_VIDOSD_SIZE(LCD_WIDTH * LCD_HEIGHT));

  MmioOr32(Fimd0BaseAddr + WINSHMAP_OFFSET, S5P_WINSHMAP_PROTECT(0));
  MmioWrite32(Fimd0BaseAddr + VIDADDR_START0_OFFSET(0), FB_ADDR);
  MmioWrite32(Fimd0BaseAddr + VIDADDR_END0_OFFSET(0), (FB_ADDR + (LCD_WIDTH * LCD_HEIGHT * 4)));
  MmioAnd32(Fimd0BaseAddr + WINSHMAP_OFFSET, ~(S5P_WINSHMAP_PROTECT(0)));

  MmioWrite32(Fimd0BaseAddr + VIDADDR_SIZE_OFFSET(0), (S5P_VIDADDR_PAGEWIDTH(LCD_WIDTH * 4) | S5P_VIDADDR_OFFSIZE(0)));

  div = SRC_CLK / VCLK;
  if(SRC_CLK % VCLK)
    div++;

  MmioAndThenOr32(Fimd0BaseAddr + VIDCON0_OFFSET, ~(S5P_VIDCON0_CLKVALUP_MASK | S5P_VIDCON0_VCLKEN_MASK), \
		  (S5P_VIDCON0_CLKVALUP_ALWAYS | S5P_VIDCON0_VCLKEN_NORMAL | \
		  S5P_VIDCON0_CLKVAL_F(div - 1)));

  MmioOr32(Fimd0BaseAddr + WINCON_OFFSET(0), S5P_WINCON_ENWIN_ENABLE);
  MmioOr32(Fimd0BaseAddr + WINSHMAP_OFFSET, S5P_WINSHMAP_CH_ENABLE(0));

  MmioOr32(Fimd0BaseAddr + VIDCON0_OFFSET, (S5P_VIDCON0_ENVID_ENABLE | S5P_VIDCON0_ENVID_F_ENABLE));

  EnableBackLight();

  lcd_on();
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
      ASSERT_EFI_ERROR(Status);
  }

  return EFI_SUCCESS;
}




/**
  Initialize the state information for the GOP Architectural Protocol

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
ExynosGopConstructor (
  IN   GRAPHICS_CONSOLE_DEV                 *Private
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  /* Initialize Display */
  LCD_Initialize();
  if(Private->GraphicsOutput->Mode == NULL){
    Status = gBS->AllocatePool(
		    EfiBootServicesData,
		    sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE),
		    (VOID **)&Private->GraphicsOutput->Mode
		    );
    ASSERT_EFI_ERROR(Status);
    ZeroMem(Private->GraphicsOutput->Mode,sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE));
  }
  if(Private->GraphicsOutput->Mode->Info==NULL){
    Status = gBS->AllocatePool(
		    EfiBootServicesData,
		    sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION),
		    (VOID **)&Private->GraphicsOutput->Mode->Info
		    );
   ASSERT_EFI_ERROR(Status);
    ZeroMem(Private->GraphicsOutput->Mode->Info,sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
  }
  /* Fill out mode information */
  Private->GraphicsOutput->Mode->MaxMode = 1;
  Private->GraphicsOutput->Mode->Mode = 0;
  Private->GraphicsOutput->Mode->Info->Version = 0;
  Private->GraphicsOutput->Mode->Info->HorizontalResolution = LCD_WIDTH;
  Private->GraphicsOutput->Mode->Info->VerticalResolution = LCD_HEIGHT;
  Private->GraphicsOutput->Mode->Info->PixelFormat = PixelBlueGreenRedReserved8BitPerColor;
  Private->GraphicsOutput->Mode->Info->PixelsPerScanLine = LCD_WIDTH;
  Private->GraphicsOutput->Mode->SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
  Private->GraphicsOutput->Mode->FrameBufferBase = FB_ADDR;
  Private->GraphicsOutput->Mode->FrameBufferSize = (LCD_WIDTH * LCD_HEIGHT * 4);
  return Status;
}

EFI_STATUS
ExynosGopDestructor (
	GRAPHICS_CONSOLE_DEV *Private
  )
{
  //
  // Free graphics output protocol occupied resource
  //
  if(Private != NULL){
    if(Private->GraphicsOutput != NULL){
      if (Private->GraphicsOutput->Mode != NULL) {
        if (Private->GraphicsOutput->Mode->Info != NULL) {
          gBS->FreePool (Private->GraphicsOutput->Mode->Info);
	  Private->GraphicsOutput->Mode->Info =NULL;
        }
        gBS->FreePool (Private->GraphicsOutput->Mode);
	Private->GraphicsOutput->Mode=NULL;
      }
    }
  }
  return EFI_SUCCESS;
}
