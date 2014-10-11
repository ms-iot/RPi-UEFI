/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *                     Hanjun Guo <hanjun.guo@linaro.org>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright 
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 * NB: This License is also known as the "BSD 2-Clause License".
 * 
 *
 * [GTDT] Generic Timer Description Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 */

[0004]                          Signature : "GTDT"
[0004]                       Table Length : 00000050
[0001]                           Revision : 02
[0001]                           Checksum : F1
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110623

[0008]              Counter Block Address : 0000000000000000
[0004]                           Reserved : 00000000

/* In RTSM model's dts file, the last cell of interrupts
 * is 0xff01, it means its cpu mask is FF, and trigger type
 * and flag is 1 = low-to-high edge triggered.
 * 
 * so in ACPI the Trigger Mode is 1 - Edge triggered, and 
 * Polarity is 0 - Active high as ACPI spec describled.
 *
 * using direct mapping for hwirqs, it means that we using
 * ID [16, 31] for PPI, not [0, 15] used in FDT.
 */
[0004]               Secure EL1 Interrupt : 0000001d
[0004]         SEL1 Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
                                Always-on : 0

[0004]           Non-Secure EL1 Interrupt : 0000001e
[0004]        NSEL1 Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
                                Always-on : 0

[0004]            Virtual Timer Interrupt : 0000001b
[0004]           VT Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
                                Always-on : 0

[0004]           Non-Secure EL2 Interrupt : 0000001a
[0004]        NSEL2 Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
				Always-on : 0

/* The 64-bit physical address at which the Counter Read block is located */
[0008]	     CntReadBase Physical address : 0000000000000000

[0004]               Platform Timer Count : 00000001
[0004]              Platform Timer Offset : 0000005C

/* Memory-mapped GT (Generic Timer) structures */
[0001]                      Subtable Type : 00
[0002]                             Length : 0064
[0001]                           Reserved : 000000
[0008]                      Block Address : 000000002a810000
[0004]                        Timer Count : 00000001
[0004]                       Timer Offset : 00000010

/* One frame is available */
[0001]                       Frame Number : 00
[0003]                           Reserved : 000000
[0008]                       Base Address : 000000002a820000
[0008]                   EL0 Base Address : FFFFFFFFFFFFFFFF
[0004]                    Timer Interrupt : 00000029 /* 25+16 */
[0004]        Timer Flags (decoded below) : 00000000 /* Active high level-sensitive */
                             Trigger Mode : 0
                                 Polarity : 0
/* No virtual timer */
[0004]            Virtual Timer Interrupt : 00000000
[0004] Virtual Timer Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0
[0004]       Common Flags (decoded below) : 00000000
                                   Secure : 0
                                Always On : 0

