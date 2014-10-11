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
* [DSDT] Description of the armv8 VE Model
*
*/

DefinitionBlock (
  "dsdt.aml",    // output filename
  "DSDT",      // table signature
  2,      // DSDT compliance revision
  "LINARO",    // OEM ID
  "RTSMVEV8",    // table ID
  0x00000004)    // OEM revision
{
  Scope (\_SB)
  {
    Method (_OSC, 4, NotSerialized)
    {
      /* Platform-Wide OSPM Capabilities */
      If(LEqual(Arg0,ToUUID("0811B06E-4A27-44F9-8D60-3CBBC22E7B48")))
      {
        /* APEI support unconditionally */
        Return (Arg3)
      } Else {
        CreateDWordField (Arg3, Zero, CDW1)
        /* Set invalid UUID error bit */
        Or (CDW1, 0x04, CDW1)
        Return (Arg3)
      }
    }

    //
    // Two Emulated aarch64 CPUs each with 4 cores
    //
    Device(CPU0) { // Cluster 0, Cpu 0
      Name(_HID, "ACPI0007")
      Name(_UID, 0)
    }
    Device(CPU1) { // Cluster 0, Cpu 1
      Name(_HID, "ACPI0007")
      Name(_UID, 1)
    }
    Device(CPU2) { // Cluster 0, Cpu 2
      Name(_HID, "ACPI0007")
      Name(_UID, 2)
    }
    Device(CPU3) { // Cluster 0, Cpu 3
      Name(_HID, "ACPI0007")
      Name(_UID, 3)
    }
    Device(CPU4) { // Cluster 1, Cpu 0
      Name(_HID, "ACPI0007")
      Name(_UID, 4)
    }
    Device(CPU5) { // Cluster 1, Cpu 1
      Name(_HID, "ACPI0007")
      Name(_UID, 5)
    }
    Device(CPU6) { // Cluster 1, Cpu 2
      Name(_HID, "ACPI0007")
      Name(_UID, 6)
    }
    Device(CPU7) { // Cluster 1, Cpu 3
      Name(_HID, "ACPI0007")
      Name(_UID, 7)
    }

    // SMC91X
    Device (NET0) {
      Name (_HID, "LNRO0003")
      Name (_UID, 0)

      Name (_CRS, ResourceTemplate () {
        Memory32Fixed (ReadWrite, 0x1a000000, 0x00010000)
        Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {0x2F}
      })
    }

    // SYSREG
    Device (SREG) {
      Name (_HID, "LNRO0009")
      Name (_UID, 0)

      Method (_CRS, 0x0, Serialized) {
        Name (RBUF, ResourceTemplate() {
          Memory32Fixed (ReadWrite, 0x1c010000, 0x1000)
        })
        Return (RBUF)
      }
    }

    // VIRTIO
    Device (VIRT) {
      Name (_HID, "LNRO0005")
      Name (_UID, 0)

      Name (_CRS, ResourceTemplate() {
        Memory32Fixed (ReadWrite, 0x1c130000, 0x1000)
        Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x4A}
      })
    }

    // UART PL011
    Device(COM0) {
      Name(_HID, "ARMH0011")
      Name(_CID, "PL011")
      Name(_UID, Zero)

      Name(_CRS, ResourceTemplate() {
        Memory32Fixed(ReadWrite, 0x1c090000, 0x1000)
        Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 0x25 }
      })
    }
  }
}
