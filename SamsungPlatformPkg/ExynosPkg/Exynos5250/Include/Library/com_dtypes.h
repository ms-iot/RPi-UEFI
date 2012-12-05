#ifndef COM_DTYPES_H
#define COM_DTYPES_H
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


/*===========================================================================

                            Data Declarations

===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* For NT apps we want to use the Win32 definitions and/or those
** supplied by the Win32 compiler for things like NULL, MAX, MIN
** abs, labs, etc.
*/
#ifdef T_WINNT
   #ifndef WIN32
      #define WIN32
   #endif
   #include <stdlib.h>
#endif

/* ------------------------------------------------------------------------
** Constants
** ------------------------------------------------------------------------ */

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */

#define  ON   1    /* On value. */
#define  OFF  0    /* Off value. */

#ifndef NULL
  #define NULL  0
#endif

/* -----------------------------------------------------------------------
** Standard Types
** ----------------------------------------------------------------------- */

/* The following definitions are the same accross platforms.  This first
** group are the sanctioned types.
*/
#ifndef _ARM_ASM_
#ifndef _BOOLEAN_DEFINED
typedef  unsigned char      boolean;     /* Boolean value type. */
#define _BOOLEAN_DEFINED
#endif


#if defined(DALSTDDEF_H) /* guards against a known re-definer */
#define _BOOLEAN_DEFINED
#define _UINT32_DEFINED
#define _UINT16_DEFINED
#define _UINT8_DEFINED
#define _INT32_DEFINED
#define _INT16_DEFINED
#define _INT8_DEFINED
#define _UINT64_DEFINED
#define _INT64_DEFINED
#define _BYTE_DEFINED
#endif /* #if !defined(DALSTDDEF_H) */

#ifndef _UINT32_DEFINED
typedef  unsigned long int  uint32;      /* Unsigned 32 bit value */
#define _UINT32_DEFINED
#endif

#ifndef _UINT16_DEFINED
typedef  unsigned short     uint16;      /* Unsigned 16 bit value */
#define _UINT16_DEFINED
#endif

#ifndef _UINT8_DEFINED
typedef  unsigned char      uint8;       /* Unsigned 8  bit value */
#define _UINT8_DEFINED
#endif

#ifndef _INT32_DEFINED
typedef  signed long int    int32;       /* Signed 32 bit value */
#define _INT32_DEFINED
#endif

#ifndef _INT16_DEFINED
typedef  signed short       int16;       /* Signed 16 bit value */
#define _INT16_DEFINED
#endif

#ifndef _INT8_DEFINED
typedef  signed char        int8;        /* Signed 8  bit value */
#define _INT8_DEFINED
#endif

/* This group are the deprecated types.  Their use should be
** discontinued and new code should use the types above
*/
#ifndef _BYTE_DEFINED
typedef  unsigned char      byte;         /* Unsigned 8  bit value type. */
#define  _BYTE_DEFINED
#endif

typedef  unsigned short     word;         /* Unsinged 16 bit value type. */
typedef  unsigned long      dword;        /* Unsigned 32 bit value type. */

typedef  unsigned char      uint1;        /* Unsigned 8  bit value type. */
typedef  unsigned short     uint2;        /* Unsigned 16 bit value type. */
typedef  unsigned long      uint4;        /* Unsigned 32 bit value type. */

typedef  signed char        int1;         /* Signed 8  bit value type. */
typedef  signed short       int2;         /* Signed 16 bit value type. */
typedef  long int           int4;         /* Signed 32 bit value type. */

typedef  signed long        sint31;       /* Signed 32 bit value */
typedef  signed short       sint15;       /* Signed 16 bit value */
typedef  signed char        sint7;        /* Signed 8  bit value */

typedef uint16 UWord16 ;
typedef uint32 UWord32 ;
typedef int32  Word32 ;
typedef int16  Word16 ;
typedef uint8  UWord8 ;
typedef int8   Word8 ;
typedef int32  Vect32 ;

#if (! defined T_WINNT) && (! defined __GNUC__)
  /* Non WinNT Targets */
  #ifndef _INT64_DEFINED
    typedef long long     int64;       /* Signed 64 bit value */
    #define _INT64_DEFINED
  #endif
  #ifndef _UINT64_DEFINED
    typedef  unsigned long long  uint64;      /* Unsigned 64 bit value */
    #define _UINT64_DEFINED
  #endif
#else /* T_WINNT || TARGET_OS_SOLARIS || __GNUC__ */
  /* WINNT or SOLARIS based targets */
  #if (defined __GNUC__) 
    #ifndef _INT64_DEFINED
      typedef long long           int64;
      #define _INT64_DEFINED
    #endif
    #ifndef _UINT64_DEFINED
      typedef unsigned long long  uint64;
      #define _UINT64_DEFINED
    #endif
  #else
    typedef  __int64              int64;       /* Signed 64 bit value */
    #ifndef _UINT64_DEFINED
      typedef  unsigned __int64   uint64;      /* Unsigned 64 bit value */
      #define _UINT64_DEFINED
    #endif
  #endif
#endif /* T_WINNT */

#endif /* _ARM_ASM_ */

#ifdef __cplusplus
}
#endif

#endif  /* COM_DTYPES_H */
