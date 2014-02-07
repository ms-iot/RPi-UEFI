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
[0001]                           Revision : 01
[0001]                           Checksum : F1
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110623

[0008]                      Timer Address : 0000000000000000
[0004]              Flags (decoded below) : 00000001
                           Memory Present : 1

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
[0004]               Secure PL1 Interrupt : 0000001d
[0004]         SPL1 Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0

[0004]           Non-Secure PL1 Interrupt : 0000001e
[0004]        NSPL1 Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0

[0004]            Virtual Timer Interrupt : 0000001b
[0004]           VT Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0

[0004]           Non-Secure PL2 Interrupt : 0000001a
[0004]        NSPL2 Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
