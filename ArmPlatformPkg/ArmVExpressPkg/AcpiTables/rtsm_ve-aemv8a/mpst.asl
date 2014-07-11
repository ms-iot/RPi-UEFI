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
 * [MPST] Memory Power State Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 */

[0004]                          Signature : "MPST"
[0004]                       Table Length : 000000B6
[0001]                           Revision : 01
[0001]                           Checksum : 77
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "RTSMVEV8"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20120913

[0001]                         Channel ID : 00
[0003]                           Reserved : 000000
[0002]                   Power Node Count : 0002
[0002]                           Reserved : 0000

[0001]              Flags (decoded below) : 00
                             Node Enabled : 0
                            Power Managed : 0
                         Hot Plug Capable : 0
[0001]                           Reserved : 00
[0002]                            Node ID : 0000
[0004]                             Length : 00000000
[0008]                      Range Address : 0000000000000000
[0008]                       Range Length : 0000000000000000
[0004]                   Num Power States : 00000002
[0004]            Num Physical Components : 00000003

[0001]                        Power State : 00
[0001]                          InfoIndex : 00

[0001]                        Power State : 00
[0001]                          InfoIndex : 00

[0002]                       Component Id : 0000
[0002]                       Component Id : 0001
[0002]                       Component Id : 0002

[0001]              Flags (decoded below) : 00
                             Node Enabled : 0
                            Power Managed : 0
                         Hot Plug Capable : 0
[0001]                           Reserved : 00
[0002]                            Node ID : 0000
[0004]                             Length : 00000000
[0008]                      Range Address : 0000000000000000
[0008]                       Range Length : 0000000000000000
[0004]                   Num Power States : 00000001
[0004]            Num Physical Components : 00000001

[0001]                        Power State : 00
[0001]                          InfoIndex : 00

[0002]                       Component Id : 0000

[0002]              Characteristics Count : 0002
[0002]                           Reserved : 0000

[0001]                       Structure ID : 01
[0001]              Flags (decoded below) : 00
                         Memory Preserved : 0
                               Auto Entry : 0
                                Auto Exit : 0
[0002]                           Reserved : 0000
[0004]                      Average Power : 00000000
[0004]                       Power Saving : 00000000
[0008]                       Exit Latency : 0000000000000000
[0008]                           Reserved : 0000000000000000

[0001]                       Structure ID : 01
[0001]              Flags (decoded below) : 00
                         Memory Preserved : 0
                               Auto Entry : 0
                                Auto Exit : 0
[0002]                           Reserved : 0000
[0004]                      Average Power : 00000000
[0004]                       Power Saving : 00000000
[0008]                       Exit Latency : 0000000000000000
[0008]                           Reserved : 0000000000000000
