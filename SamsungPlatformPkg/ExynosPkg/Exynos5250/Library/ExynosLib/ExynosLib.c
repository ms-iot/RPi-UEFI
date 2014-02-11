/** @file

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Platform/ArmPlatform.h>

UINT32
GpioBase (
  IN  UINTN Port
  )
{

  ASSERT( ((Port >= GPA0) && (Port <= GPY6))
	   || ((Port >= GPX0) && (Port <= GPX3))
	   || ((Port >= GPE0) && (Port <= GPH1))
	   || ((Port >= GPV0) && (Port <= GPV4))
	   || (Port == GPZ));

  /*decide which part of gpio is being requested. give the corresponding base address*/
  if(Port >= 0x90) {
	/* 0x0386_0000 */
	Port -= 0x90; 
	return (PcdGet32(PcdGpioPart4Base) + (Port*DISTANCE_BTWN_PORTS));
  }else if(Port >= 0x80) {
	/* 0x10D1_0000 */
	Port -= 0x80; 
	return (PcdGet32(PcdGpioPart3Base) + (Port*DISTANCE_BTWN_PORTS));
  }else if(Port >= 0x70) {
	/* 0x1340_0000 */
	Port -= 0x70; 
	return (PcdGet32(PcdGpioPart2Base) + (Port*DISTANCE_BTWN_PORTS));
  }else {
	/* 0x1140_0000 */
	return (PcdGet32(PcdGpioPart1Base) + (Port*DISTANCE_BTWN_PORTS));
   }

 ASSERT(FALSE); return 0;
}
