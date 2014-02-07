/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
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
 * [EINJ] Error Injection Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 */

[0004]                          Signature : "EINJ"
[0004]                       Table Length : 00000130
[0001]                           Revision : 01
[0001]                           Checksum : 09
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000003
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0004]            Injection Header Length : 00000030
[0001]                              Flags : 00
[0003]                           Reserved : 000000
[0004]              Injection Entry Count : 00000008

[0001]                             Action : 00 [Begin Operation]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0200

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 01 [Get Trigger Table]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0208

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 02 [Set Error Type]
[0001]                        Instruction : 02 [Write Register]
[0001]              Flags (decoded below) : 01
                   Preserve Register Bits : 1
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0210

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 03 [Get Error Type]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0218

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 04 [End Operation]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 01
                   Preserve Register Bits : 1
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0220

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 05 [Execute Operation]
[0001]                        Instruction : 03 [Write Register Value]
[0001]              Flags (decoded below) : 01
                   Preserve Register Bits : 1
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 10
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 02 [Word Access:16]
[0008]                            Address : 0xFFFF0228

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 06 [Check Busy Status]
[0001]                        Instruction : 01 [Read Register Value]
[0001]              Flags (decoded below) : 00
                   Preserve Register Bits : 0
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0230

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF

[0001]                             Action : 07 [Get Command Status]
[0001]                        Instruction : 00 [Read Register]
[0001]              Flags (decoded below) : 01
                   Preserve Register Bits : 1
[0001]                           Reserved : 00

[0012]                    Register Region : [Generic Address Structure]
[0001]                           Space ID : 00 [SystemMemory]
[0001]                          Bit Width : 40
[0001]                         Bit Offset : 00
[0001]               Encoded Access Width : 04 [QWord Access:64]
[0008]                            Address : 0xFFFF0238

[0008]                              Value : 0000000000000000
[0008]                               Mask : FFFFFFFFFFFFFFFF
