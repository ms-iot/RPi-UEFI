//  Copyright (c), Microsoft Corporation. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//

//
// SSDT definition for a discrete TPM2 device on SPI0
//

DefinitionBlock ("TPM2Dev.dat", "SSDT", 1, "MSFT", "SPITPM", 1)
{
    Scope (\_SB)
    {
        Device(TPM1)
        {
            Name(_HID, "MSFT0101")
            Name(_UID, 1)
            Name(_DDN, "SPI TPM 2.0 Device")            // _DDN: DOS Device Name
            Name(_STR, Unicode ("SPI TPM 2.0 Device"))  // _STR: Description String
            Name (RBUF, ResourceTemplate ()
            {
                // RaspberryPi 4MHz, SPI0/CS0
                // SpiSerialBus (0x0000, PolarityLow, FourWireMode, 0x08, ControllerInitiated, 0x003D0900, ClockPolarityLow, ClockPhaseFirst, "\\_SB.SPI0", 0x00, ResourceConsumer, ,)
                // RaspberryPi 4MHz, SPI0/CS1
                SpiSerialBus (0x0001, PolarityLow, FourWireMode, 0x08, ControllerInitiated, 0x003D0900, ClockPolarityLow, ClockPhaseFirst, "\\_SB.SPI0", 0x00, ResourceConsumer, ,)
                // RaspberryPi 4MHz, SPI1/CS0  (DeviceSelection on SPI1/CS0 is mapped to 0x0001 not 0x0000!)
                // SpiSerialBus (0x0001, PolarityLow, FourWireMode, 0x08, ControllerInitiated, 0x003D0900, ClockPolarityLow, ClockPhaseFirst, "\\_SB.SPI1", 0x00, ResourceConsumer, ,)
            })
            Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
            {
                Return (RBUF) /* \_SB_.FSIM.RBUF */
            }
            Method (_STA, 0, NotSerialized)  // _STA: Status
            {
                Return (0x0F)
            }
        }
    }
}
