/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * GTDT Table for X-Gene Processor
 *
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 **/

[0004]                          Signature : "GTDT"    [Generic Timer Description Table]
[0004]                       Table Length : 000000E0
[0001]                           Revision : 02
[0001]                           Checksum : B0
[0006]                             Oem ID : "APM   "
[0008]                       Oem Table ID : "XGENE   "
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20140424

[0008]              Counter Block Address : 0000000000000000
[0004]                           Reserved : 00000000

[0004]               Secure EL1 Interrupt : 00000010
[0004]          EL1 Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0
                                Always On : 0

[0004]           Non-Secure EL1 Interrupt : 0000001D
[0004]         NEL1 Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0
                                Always On : 0

[0004]            Virtual Timer Interrupt : 0000001E
[0004]           VT Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0
                                Always On : 0

[0004]           Non-Secure EL2 Interrupt : 0000001F
[0004]         NEL2 Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0
                                Always On : 0
[0008]         Counter Read Block Address : 0000000000000000

[0004]               Platform Timer Count : 00000002
[0004]              Platform Timer Offset : 00000060

[0001]                      Subtable Type : 00 [GT Block]
[0001]                             Length : 64
[0002]                           Reserved : 0000
[0008]                   GT Block Address : 0000000000000000
[0004]                     GT Block Count : 00000002
[0004]                    GT Block Offset : 00000014

[0001]                    GT Frame Number : 00
[0003]                           Reserved : 000000
[0008]                        GTx Address : 0000000000000000
[0008]                    GTx EL0 Address : 0000000000000000
[0004]                GTx Timer Interrupt : 00000000
[0004]    GTx Timer Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
[0004]        GTx Virtual Timer Interrupt : 00000000
[0004] GTx Virtual Timer Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
[0004]   GTx Common Flags (decoded below) : 00000000
                                   Secure : 0
                                Always On : 0

[0001]                    GT Frame Number : 01
[0003]                           Reserved : 000000
[0008]                        GTx Address : 0000000000000000
[0008]                    GTx EL0 Address : 0000000000000000
[0004]                GTx Timer Interrupt : 00000000
[0004]    GTx Timer Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
[0004]        GTx Virtual Timer Interrupt : 00000000
[0004] GTx Virtual Timer Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
[0004]   GTx Common Flags (decoded below) : 00000000
                                   Secure : 0
                                Always On : 0

[0001]                      Subtable Type : 01 [SBSA Generic Watchdog]
[0001]                             Length : 1C
[0002]                           Reserved : 0000
[0008]              Refresh Frame Address : 0000000000000000
[0008]              Control Frame Address : 0000000000000000
[0004]                    Timer Interrupt : 00000000
[0004]        Timer Flags (decoded below) : 00000001
                             Trigger Mode : 1
                                 Polarity : 0
                                   Secure : 0
