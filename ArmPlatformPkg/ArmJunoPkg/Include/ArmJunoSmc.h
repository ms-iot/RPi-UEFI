/** @file
*
*  Copyright (c) 2013-2014, ARM Limited. All rights reserved.
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

#ifndef __ARM_JUNO_SMC_H__
#define __ARM_JUNO_SMC_H__

// System Management Trusted Interface
#define ARM_JUNO_ARM_FAST_SMC_SET_SYSTEM_POWER_STATE                  0x81000000

// SMC System Power States
#define ARM_JUNO_ARM_FAST_SMC_SYSTEM_POWER_STATE_REBOOT               0x0
#define ARM_JUNO_ARM_FAST_SMC_SYSTEM_POWER_STATE_SHUTDOWN             0x1

#endif
