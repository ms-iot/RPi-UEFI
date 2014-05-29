/*******************************************************************
#
#  
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#  
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#  
#**/





#ifndef __std_H
#define __std_H


#ifndef _ASMLANGUAGE

typedef int STATUS;
typedef int INT;
typedef unsigned int size_t;

typedef signed char     S8;
typedef signed short    S16;
typedef signed int      S32;

#ifndef VC_DEBUG_MODE
typedef long long       S64;
#else
typedef __int64         S64;
#endif

#ifndef U8 
typedef unsigned char   U8;
#endif

#ifndef U16
typedef unsigned short  U16;
#endif

#ifndef U32
typedef unsigned int    U32;
#endif

#ifndef VC_DEBUG_MODE
typedef unsigned long long  U64;
#else
typedef unsigned __int64 U64;
#endif

#ifndef LONG
typedef long    LONG;
#endif
#ifndef CHAR
typedef char    CHAR;
#endif

typedef volatile unsigned char  V8;
typedef volatile unsigned short V16;
typedef volatile unsigned int   V32;

#ifndef VC_DEBUG_MODE
typedef volatile unsigned long long  V64;
#else
typedef volatile unsigned __int64 V64;
#endif

#ifndef VC_DEBUG_MODE
typedef  char           BYTE;
#endif

typedef  unsigned char  UBYTE;    
typedef  short          HWORD;    
typedef  unsigned short UHWORD;    

#ifndef VC_DEBUG_MODE
/*typedef  long           WORD;*/    
typedef  unsigned long  UWORD;
#endif




typedef  volatile char           VBYTE;
typedef  volatile unsigned char  VUBYTE;    
typedef  volatile short          VHWORD;    
typedef  volatile unsigned short VUHWORD;    
typedef  volatile long           VWORD;    
typedef  volatile unsigned long  VUWORD;    

#ifndef ERROR
#define ERROR   -1
#endif

#ifndef OK
#define OK      0
#endif
#ifndef BOOL
#define BOOL  int
#endif
#ifndef BYTE_SWAP32
#define BYTE_SWAP32(x)        ((((unsigned)(x) & 0x000000ff) << 24) | \
			                             (((x) & 0x0000ff00) <<  8) | \
			                             (((x) & 0x00ff0000) >>  8) | \
			                             (((x) & 0xff000000) >> 24))
#endif

#ifndef BYTE_SWAP16
#define BYTE_SWAP16(x)     ((((x) & 0x00ff) <<8) | \
                            (((x) & 0xff00) >> 8))
#endif
#define CPU_RAM_HDF_BAK_VERSION_FLAG            (0)
#define CPU_RAM_HDF_MAIN_VERSION_FLAG           (1)
#define REG_WRITE(addr,data)            (*(volatile UINT32 *)(addr) = (data))
#define REG_READ(addr,data)             ((data) = *(volatile UINT32 *)(addr))

#define SYS_CTRL_REG_WRITE(offset,data)  (REG_WRITE((offset), (data)))
#define SYS_CTRL_REG_READ(offset,data)   do \
                                         { \
                                            (REG_READ((offset), (data))); \
                                         }while(0)
#ifndef MEM_MMU_OFFSET
//#define MEM_MMU_OFFSET   0x80000000
#define MEM_MMU_OFFSET   0x00
#endif
#define NELEMENTS(array)	(sizeof (array) / sizeof ((array) [0]))


#define REG64(Addr) (*(volatile unsigned long long *)(Addr))
#define REG32(Addr) (*(volatile unsigned int *)(Addr))
#define REG16(Addr) (*(volatile unsigned short *)(Addr))
#define REG8(Addr)  (*(volatile unsigned char *)(Addr))

U32 vxImmrGet (void);

#endif

#define SIZE_1        1
#define SIZE_4        4
#define SIZE_59      59
#endif /* __std_H */
