/*
   2  * ch_types.h
   3  *
   4  * Copyright(c) 2010 Texas Instruments.   All rights reserved.
   5  *
   6  * Texas Instruments, <www.ti.com>
   7  * Bastien Allibert <b-allibert@ti.com>
   8  * Olivier Deprez <o-deprez@ti.com>
   9  *
  10  * Redistribution and use in source and binary forms, with or without
  11  * modification, are permitted provided that the following conditions
  12  * are met:
  13  *
  14  *  * Redistributions of source code must retain the above copyright
  15  *    notice, this list of conditions and the following disclaimer.
  16  *  * Redistributions in binary form must reproduce the above copyright
  17  *    notice, this list of conditions and the following disclaimer in
  18  *    the documentation and/or other materials provided with the
  19  *    distribution.
  20  *  * Neither the name Texas Instruments nor the names of its
  21  *    contributors may be used to endorse or promote products derived
  22  *    from this software without specific prior written permission.
  23  *
  24  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  25  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  26  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  27  * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  28  * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  29  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  30  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  31  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  32  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  33  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  34  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  35  */

#ifndef _CH_TYPES_H
#define _CH_TYPES_H

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed char    int8_t;
typedef signed short   int16_t;
typedef signed int     int32_t;
typedef signed int     bool_t;

typedef struct {
  uint32_t Offset;
  uint32_t Size;
  uint8_t Name[64];
  uint8_t *Description;
  uint32_t Value;
} CH_Field;

typedef struct {
  uint32_t Start;
  uint32_t Size;
  uint32_t Reserved[3];
  uint8_t  Filename[12];
} CH_ItemTOC_t;

typedef struct {
  CH_ItemTOC_t TOC;
  CH_Field *fields;
  uint32_t numberOfFields;
} CH_Item_t;

typedef struct {
  uint8_t Name[16];
  uint32_t ConfigurationHeaderSize;
  CH_Item_t** SupportedItemsList;
  uint32_t NumberOfSupportedItems;
} OMAP_Platform_t;

typedef enum {
	BIN_FILE,
	C_FILE
} outputfile_t;

#endif // _CH_TYPES_H
