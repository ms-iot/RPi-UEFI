/** @file

  Copyright (c) 2012 - 2013, Texas Instruments Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __OMAP4430ROM_H__
#define __OMAP4430ROM_H__

#define PUBLIC_API_BASE                                 (0x28400)

#define PUBLIC_API_IRQ_REGISTER                         (0x44)
#define PUBLIC_API_IRQ_UNREGISTER                       (0x48)
#define PUBLIC_API_CM_ENABLEMODULECLOCKS                (0xA0)
#define PUBLIC_API_WDTIMER_DISABLE                      (0x54)
#define PUBLIC_API_CTRL_CONFIGUREPADS                   (0xA8)

//PUBLIC_API_IRQ_REGISTER
typedef UINT32 (** const IRQ_Register_pt)( UINT32,
                                           UINT32,
                                           UINT32 );
#define RomIrqRegister(a, b, c) \
   (*(IRQ_Register_pt) ((PUBLIC_API_BASE+PUBLIC_API_IRQ_REGISTER)&0xFFFFFFFE))(a, b, c);

//PUBLIC_API_IRQ_UNREGISTER
typedef UINT32 (** const IRQ_UnRegister_pt)( UINT32 );
#define RomIrqUnRegister(a) \
   (*(IRQ_UnRegister_pt) (PUBLIC_API_BASE+PUBLIC_API_IRQ_UNREGISTER))(a);

// PUBLIC_API_WDTIMER_DISABLE
typedef void (** const HAL_WDTIMER_Disable_pt)( void );
#define RomWdtimerDisable() \
  (*(HAL_WDTIMER_Disable_pt) ((PUBLIC_API_BASE+PUBLIC_API_WDTIMER_DISABLE)&0xFFFFFFFE))();

//PUBLIC_API_CM_ENABLEMODULECLOCKS
typedef UINT32 (** const HAL_CM_EnableModuleClocks_pt)( UINT32, UINT32 );
#define RomEnableClocks(a, b) \
  (*(HAL_CM_EnableModuleClocks_pt) ((PUBLIC_API_BASE+PUBLIC_API_CM_ENABLEMODULECLOCKS)&0xFFFFFFFE))(a, b);

//PUBLIC_API_CTRL_CONFIGUREPADS
typedef UINT32 (** const HAL_CTRL_ConfigurePads_pt)( UINT32, UINT32 );
#define RomCtrlConfigurePads(a, b) \
  (*(HAL_CTRL_ConfigurePads_pt) ((PUBLIC_API_BASE+PUBLIC_API_CTRL_CONFIGUREPADS)&0xFFFFFFFE))(a, b);

#endif // __OMAP4430ROM_H__
