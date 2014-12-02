/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials are licensed and made
 * available under the terms and conditions of the BSD License which
 * accompanies this distribution.  The full text of the license may be
 * found at * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * APIC Table for X-Gene Processor
 * 
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 **/

[0004]                         Signature : "APIC"    [Multiple APIC Description Table (MADT)]
[0004]                      Table Length : 0000028C
[0001]                          Revision : 03
[0001]                          Checksum : 00
[0006]                            Oem ID : "APM   "
[0008]                      Oem Table ID : "XGENE   "
[0004]                      Oem Revision : 00000003
[0004]                   Asl Compiler ID : "INTL"
[0004]             Asl Compiler Revision : 20140724

[0004]                Local Apic Address : 00000000
[0004]             Flags (decoded below) : 00000000
                     PC-AT Compatibility : 0

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000000
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 0x00004000008000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000000

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000001
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 0000004000009000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000001

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000100
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 000000400000a000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000100

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000101
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 000000400000b000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000101

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000200
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 000000400000c000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000200

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000201
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 000000400000d000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000201

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000300
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 000000400000e000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000300

[0001]                     Subtable Type : 0B [Generic Interrupt Controller]
[0001]                            Length : 4C
[0002]                          Reserved : 0000
[0004]              CPU Interface Number : 00000000
[0004]                     Processor UID : 00000301
[0004]             Flags (decoded below) : 00000001
                       Processor Enabled : 1
      Performance Interrupt Trigger Mode : 0
      Virtual GIC Interrupt Trigger Mode : 0
[0004]          Parking Protocol Version : 00000001
[0004]             Performance Interrupt : 0000001A
[0008]                    Parked Address : 000000400000f000
[0008]                      Base Address : 00000000780A0000
[0008]          Virtual GIC Base Address : 00000000780E0000
[0008]       Hypervisor GIC Base Address : 00000000780C0000
[0004]             Virtual GIC Interrupt : 00000009
[0008]        Redistributor Base Address : 0000000078090000
[0008]                         ARM MPIDR : 0000000000000301

[0001]                     Subtable Type : 0C [Generic Interrupt Distributor]
[0001]                            Length : 18
[0002]                          Reserved : 0000
[0004]             Local GIC Hardware ID : 00000000
[0008]                      Base Address : 0000000078090000
[0004]                    Interrupt Base : 00000000
[0004]                          Reserved : 00000000
