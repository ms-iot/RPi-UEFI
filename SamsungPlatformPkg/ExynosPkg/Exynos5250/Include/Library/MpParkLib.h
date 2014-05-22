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


#ifndef __MPPARKLIB_H_
#define __MPPARKLIB_H_

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

/*===========================================================================

                        Defines and Structs

===========================================================================*/
extern UINT32 MpParkGPT0CntAddr;
extern UINT32 MpParkGPT0MatchAddr;
extern UINT32 MpParkGPT0EnableAddr;
extern UINT32 MpParkMPMCountAddr;

/*===========================================================================

                        Public Functions

===========================================================================*/
void CPU1_Start(void);


/*===========================================================================

                        Private Functions

===========================================================================*/

#endif // __MPPARKLIB_H_

