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
 **/

DefinitionBlock("Dsdt.aml", "DSDT", 0x05, "APM   ", "APM88xxxx", 1) {

//Operation Region For Power Control and Power Good
	OperationRegion(\PGUD, SystemMemory, 0x17000078, 4)
	OperationRegion(\PCTL, SystemMemory, 0x1700007C, 4)
	Field(\PGUD, DWordAcc, NoLock, Preserve) {
		SOCG, 1,
		L3CG, 1,
		PD0G, 1,
		PD1G, 1,
		PD2G, 1,
		PD3G, 1
	}
	Field(\PCTL, DWordAcc, NoLock, Preserve) {
		SOCC, 1,
		L3CC, 1,
		PD0C, 1,
		PD1C, 1,
		PD2C, 1,
		PD3C, 1
	}

//SOC VRM resource, power domain for SOC
	PowerResource(SCVR, 2, 0) {
		Method(_STA) {
			Return (NAnd(SOCC, One))
		}
		Method(_ON) {
			Store(One, SOCC)
			Sleep(10)
		}
		Method(_OFF) {
			Store(Zero, SOCC)
			Sleep(10)
		}
	}//SCVR

////////////////////////////////////////////////////////////////////////////////
//System Sleep States

	Name(\_S0, Package(){0x00000000, 0x00000000})
	Name(\_S1, Package(){0x00000001, 0x00000000})
	Name(\_S2, Package(){0x00000002, 0x00000000})

////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU0) {

	Name(_UID, 0)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 0)	//Domain 0

	Method(_PSC) {
		Return (0)
	} //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10550000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10550004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 0, 0xFC, 2}
	}) //Domain 0

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10550014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10550018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055001C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10550020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 1, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	}//CPU0
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU1) {

	Name(_UID, 1)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 0)	//Domain 0

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10551000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10551004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 0, 0xFC, 2}
	}) //Domain 0

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10551014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10551018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055101C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10551020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 1, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU1
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU2) {

	Name(_UID, 0x100)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 1)	//Domain 1

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10552000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10552004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 1, 0xFC, 2}
	}) //Domain 1

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10552014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10552018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055201C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10552020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 2, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU2
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU3) {

	Name(_UID, 0x101)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 1)	//Domain 1

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10553000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10553004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 1, 0xFC, 2}
	}) //Domain 1

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10553014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10553018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055301C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10553020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 2, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU3
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU4) {

	Name(_UID, 0x200)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 2)	//Domain 2

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10554000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10554004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 2, 0xFC, 2}
	}) //Domain 2

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10554014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10554018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055401C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10554020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 3, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU4
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU5) {

	Name(_UID, 0x201)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 2)	//Domain 2

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10555000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10555004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 2, 0xFC, 2}
	}) //Domain 2

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10555014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10555018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055501C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10555020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 3, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU5
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU6) {

	Name(_UID, 0x300)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 3)	//Domain 3

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10556000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10556004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 3, 0xFC, 2}
	}) //Domain 3

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10556014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10556018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055601C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10556020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 4, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU6
////////////////////////////////////////////////////////////////////////////////
//Processor
	Device(\_SB.CPU7) {

	Name(_UID, 0x301)
	Name(_HID, "ACPI0007")
	Method(_STA) {
		Return (One)
	}

//Clock Domain Object
	Name(_CDM, 3)	//Domain 3

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10557000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10557004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 3, 0xFC, 2}
	}) //Domain 3

//C states
	Name(_CST, Package() {
		2,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10557014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
		Package() {	//C2 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			2,
			0,	//latency usec
			0	//power mW
		}, //C2 state
		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10557018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state
		Package() {	//C4 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x1055701C, 3)},
			4,
			500000,	//latency usec
			1000	//power mW
		}, //C4 state
		Package() {	//C5 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x00000000, 3)},
			5,
			0,	//latency usec
			0	//power mW
		}, //C5 state
		Package() {	//C6 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10557020, 3)},
			6,
			10000000,	//latency usec
			0		//power mW
		}, //C6 state

	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 4, 0xFC, 2, 2},
		Package() {6, 0, 5, 0xFC, 8, 3},
		Package() {6, 0, 6, 0xFC, 8, 5},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU7

///////////////////////////////////////////////////////////////////////////////
// Method DTGP
	Method (DTGP, 5, NotSerialized) {
		If (LEqual (Arg0, Buffer (0x10) {
			/* UUID: a706b112-bf0b-48d2-9fa3-95591a3c4c06 */
			/* 0000 */ 0xA7, 0x06, 0xB1, 0x12, 0xBF, 0x0B, 0x48, 0xD2,
			/* 0008 */ 0x9f, 0xA3, 0x95, 0x59, 0x1A, 0x3C, 0x4C, 0x06
		}))

		{
		If (LEqual (Arg1, 0x01)) {
			If (LEqual (Arg2, 0x00)) {
				Store (Buffer (0x01) {
					0x03
				}, Arg4)
				Return (0x01)
			}
			If (LEqual (Arg2, 0x01)) {
				Return (0x01)
			}
		}
		}

		Store (Buffer (0x01) {
			0x00
		}, Arg4)
		Return (0x00)
	}

///////////////////////////////////////////////////////////////////////////////
// PMU
	Device(\_SB.PMU0) {
		Name(_HID, "LNRO0007") // Device Identification Objects
		Name(_DDN, "PMU0")
		Name(_UID, "PMU0")
		Name(_STR, Unicode("PMU"))
		Name(_CID, "LNRO0007")
		Name(_CRS, ResourceTemplate() {
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x1C }
		})
	}

///////////////////////////////////////////////////////////////////////////////
// SLIMpro Device
	Device(\_SB.SLIM) {
		Name(_HID, "APMC0D01") // Device Identification Objects
		Name(_DDN, "SLIM")
		Name(_UID, "SLIM")
		Name(_STR, Unicode("SLIMpro Device"))
		Name(_CID, "APMC0D01")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x10540000, 0xa100, )
			Memory32Fixed(ReadWrite, 0x17000000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x17001000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x20 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x21 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x22 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x23 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x24 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x25 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x26 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x27 }
		})
		Name(DBST, 0x0000) // Doorbell start index
		Name(DBEN, 0x0007) // Doorbell end index
		Name(DBRT, 0x0005) // Doorbell retry count
		Name(DBEV, 0x0007) // Doorbell event
		Name(DBIC, 0x0000) // Doorbell I2C
	} //SLIM

///////////////////////////////////////////////////////////////////////////////
// EDAC MC0 Device
	Device(\_SB.EMC0) {
		Name(_HID, "APMC0D10") // Device Identification Objects
		Name(_DDN, "EMC0")
		Name(_UID, "EMC0")
		Name(_STR, Unicode("EDAC MC0 Device"))
		Name(_ADR, 0x7E800000)
		Name(_CID, "APMC0D10")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E200000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E700000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E720000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E800000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC MC0 Device

// EDAC MC1 Device
	Device(\_SB.EMC1) {
		Name(_HID, "APMC0D10") // Device Identification Objects
		Name(_DDN, "EMC1")
		Name(_UID, "EMC1")
		Name(_STR, Unicode("EDAC MC1 Device"))
		Name(_ADR, 0x7E840000)
		Name(_CID, "APMC0D10")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E200000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E700000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E720000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E840000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC MC1 Device

// EDAC MC2 Device
	Device(\_SB.EMC2) {
		Name(_HID, "APMC0D10") // Device Identification Objects
		Name(_DDN, "EMC2")
		Name(_UID, "EMC2")
		Name(_STR, Unicode("EDAC MC2 Device"))
		Name(_ADR, 0x7E880000)
		Name(_CID, "APMC0D10")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E200000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E700000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E720000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E880000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC MC2 Device

// EDAC MC3 Device
	Device(\_SB.EMC3) {
		Name(_HID, "APMC0D10") // Device Identification Objects
		Name(_DDN, "EMC3")
		Name(_UID, "EMC3")
		Name(_STR, Unicode("EDAC MC3 Device"))
		Name(_ADR, 0x7E8C0000)
		Name(_CID, "APMC0D10")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E200000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E700000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E720000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E8C0000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC MC3 Device

///////////////////////////////////////////////////////////////////////////////
// EDAC L3 Device
	Device(\_SB.EL3) {
		Name(_HID, "APMC0D11") // Device Identification Objects
		Name(_DDN, "EL3")
		Name(_UID, "EL3")
		Name(_STR, Unicode("EDAC L3 Device"))
		Name(_ADR, 0x7E600000)
		Name(_CID, "APMC0D11")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E600000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC L3 Device

///////////////////////////////////////////////////////////////////////////////
// EDAC PMD0 Device
	Device(\_SB.PMD0) {
		Name(_HID, "APMC0D12") // Device Identification Objects
		Name(_DDN, "PMD0")
		Name(_UID, "PMD0")
		Name(_STR, Unicode("EDAC PMD0 Device"))
		Name(_ADR, 0x7C000000)
		Name(_CID, "APMC0D12")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7C000000, 0x200000, )
			Memory32Fixed(ReadWrite, 0x1054A000, 0x10, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC PMD0 Device

// EDAC PMD1 Device
	Device(\_SB.PMD1) {
		Name(_HID, "APMC0D12") // Device Identification Objects
		Name(_DDN, "PMD1")
		Name(_UID, "PMD1")
		Name(_STR, Unicode("EDAC PMD1 Device"))
		Name(_ADR, 0x7C200000)
		Name(_CID, "APMC0D12")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7C200000, 0x200000, )
			Memory32Fixed(ReadWrite, 0x1054A000, 0x10, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC PMD1 Device

// EDAC PMD2 Device
	Device(\_SB.PMD2) {
		Name(_HID, "APMC0D12") // Device Identification Objects
		Name(_DDN, "PMD2")
		Name(_UID, "PMD2")
		Name(_STR, Unicode("EDAC PMD2 Device"))
		Name(_ADR, 0x7C400000)
		Name(_CID, "APMC0D12")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7C400000, 0x200000, )
			Memory32Fixed(ReadWrite, 0x1054A000, 0x10, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC PMD2 Device

// EDAC PMD3 Device
	Device(\_SB.PMD3) {
		Name(_HID, "APMC0D12") // Device Identification Objects
		Name(_DDN, "PMD3")
		Name(_UID, "PMD3")
		Name(_STR, Unicode("EDAC PMD3 Device"))
		Name(_ADR, 0x7C600000)
		Name(_CID, "APMC0D12")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7C600000, 0x200000, )
			Memory32Fixed(ReadWrite, 0x1054A000, 0x10, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
		})
	} //EDAC PMD3 Device

///////////////////////////////////////////////////////////////////////////////
// EDAC SOC Device
	Device(\_SB.ESOC) {
		Name(_HID, "APMC0D13") // Device Identification Objects
		Name(_DDN, "ESOC")
		Name(_UID, "ESOC")
		Name(_STR, Unicode("EDAC SOC Device"))
		Name(_ADR, 0x7E930000)
		Name(_CID, "APMC0D13")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E930000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E000000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x41 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x47 }
		})
	} //EDAC SOC Device

///////////////////////////////////////////////////////////////////////////////
// GPIO
	Device(\_SB.GP00) {
		Name(_HID, "APMC0D07") // Device Identification Objects
		Name(_CID, "APMC0D07")
		Name(_UID, "GPIO0")
		Name(_STR, Unicode("GPIO Device"))
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1C024000, 0x1000)
		})
	} //GP00 Device

///////////////////////////////////////////////////////////////////////////////
// GPIOSB
	Device(\_SB.GPSB) {
		Name(_HID, "APMC0D15") // Device Identification Objects
		Name(_CID, "APMC0D15")
		Name(_UID, "GPIOSB")
		Name(_STR, Unicode("GPIOSB Device"))
		Method(_DSM, 4, NotSerialized) {
			Store (Package (6) {
				"ngpio", "22",
				"nirq", "6",
				"irq_pins", "8 9 10 11 12 13",
			}, Local0)
			 Return (Local0)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x17001000, 0x400)
			Interrupt(ResourceProducer, Edge, ActiveHigh, Exclusive) { 0x48 }
			Interrupt(ResourceProducer, Edge, ActiveHigh, Exclusive) { 0x49 }
			Interrupt(ResourceProducer, Edge, ActiveHigh, Exclusive) { 0x4A }
			Interrupt(ResourceProducer, Edge, ActiveHigh, Exclusive) { 0x4B }
			Interrupt(ResourceProducer, Edge, ActiveHigh, Exclusive) { 0x4C }
			Interrupt(ResourceProducer, Edge, ActiveHigh, Exclusive) { 0x4D }
		})
	} //GPIOSBDevice

///////////////////////////////////////////////////////////////////////////////
//AHBC Bus
	// AHBC Device
	Device(\_SB.AHBC) {
		OperationRegion(SRST, SystemMemory, 0x1F2AC000, 4)
		OperationRegion(CLKE, SystemMemory, 0x1F2AC004, 4)
		OperationRegion(SRRM, SystemMemory, 0x1F2AD070, 4)
		OperationRegion(RD2F, SystemMemory, 0x1F2AE014, 4)
		Field(SRST, DWordAcc, NoLock, Preserve) {
			ACSR, 1,
			SDRS, 1,
			IORS, 1,
			U0RS, 1,
			U1RS, 1,
			U2RS, 1,
			U3RS, 1,
			S0RS, 1,
			S1RS, 1,
			APRS, 1
		}
		Field(CLKE, DWordAcc, NoLock, Preserve) {
			ACCE, 1,
			SDCE, 1,
			IOCE, 1,
			U0CE, 1,
			U1CE, 1,
			U2CE, 1,
			U3CE, 1,
			S0CE, 1,
			S1CE, 1,
			APCE, 1
		}
		Field(SRRM, DWordAcc, NoLock, Preserve) {
			RMSH, 32
		}
		Field(RD2F, DWordAcc, NoLock, Preserve) {
			RSV9, 1,
			RDFL, 1,
			RSVA, 30
		}

		// Device Identification Objects
		Name(_HID, "APMC0D06")
		Name(_DDN, "AHBC")
		Name(_UID, "AHBC")
		Name(_CID, "APMC0D06")
		Name(_STR, Unicode("AHBC Peripheral Bus"))

		// Device Configuration Objects
		// Device Status
		Method(_STA) {
			if (LOr(LOr(NAnd(ACSR, One), NAnd(APRS, One)),
			LOr(LEqual(ACCE, Zero), LEqual(APCE, Zero)))) {
				Return (1)
			}
			Return (3)
		} //_STA

		// Device current resources, two registers
		Name(_CRS, ResourceTemplate() {
     			Memory32Fixed(ReadWrite, 0x1f2a0000, 0x80000, )
     			Memory32Fixed(ReadWrite, 0x1c000200, 0x100, )
		})

//==============================================================================

		//UART0 Device Controller
		Device(URT0) {
			//Device Identification Objects
			Name(_HID, "APMC0D08")
			Name(_DDN, "URT0")
			Name(_UID, "URT0")
			Name(_STR, Unicode("APM X-Gene UART0 Controller"))

			Name(_ADR, 0x1C020000)
			Name(_CID, "NS16550")

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, U0CE)
				Store(One, U0RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(U0RS, One), LEqual(U0CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, U0CE)
				Store(Zero, U0RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, U0CE)
				Store(One, U0RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(U0RS, One), LEqual(U0CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)
			//Lowest D-State supported in S1 to support wakeup
			Name(_S1W, 0)
			//Inform OSPM to use _S1W instead of _S1D when used for wake up
			Name(_PRW, Package() { 0x0, 0x3 })

			//Device Current Resource Settings
			//UART0 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Memory32Fixed(ReadWrite, 0x1C020000, 0x100)
				UARTSerialBus(
					115200,			//Baud Rate
					DataBitsEight, 		//Bits-per-byte
					StopBitsOne, 		//StopBits
					0x00,			//Lines in use
					LittleEndian,
					ParityTypeNone,
					FlowControlNone,
					16,			//Rx Buffer size
					16, 			//Tx Buffer size
					"URT0",			//This resource for UART0
					0,
					ResourceConsumer,
					U0DT
				)
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {108}
				})
		} //URT0

		//UART1 Device Controller
		Device(URT1) {
			//Device Identification Objects
			Name(_HID, "APMC0D08")
			Name(_DDN, "URT1")
			Name(_UID, "URT1")
			Name(_STR, Unicode("APM88xxxx UART1 Controller"))

			Name(_ADR, 0x1C021000)
			Name(_CID, "NS16550")

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, U1CE)
				Store(One, U1RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(U1RS, One), LEqual(U1CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, U1CE)
				Store(Zero, U1RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, U1CE)
				Store(One, U1RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(U1RS, One), LEqual(U1CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)
			//Lowest D-State supported in S1 to support wakeup
			Name(_S1W, 0)
			//Inform OSPM to use _S1W instead of _S1D when used for wake up
			Name(_PRW, Package() { 0x0, 0x3 })

			//Device Current Resource Settings
			//UART1 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Memory32Fixed(ReadWrite, 0x1C021000, 0x100)
				UARTSerialBus(
					115200,			//Baud Rate
					DataBitsEight, 		//Bits-per-byte
					StopBitsOne, 		//StopBits
					0x00,			//Lines in use
					LittleEndian,
					ParityTypeNone,
					FlowControlNone,
					16,			//Rx Buffer size
					16, 			//Tx Buffer size
					"URT1",			//This resource for UART0
					0,
					ResourceConsumer,
					U1DT
				)
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {109}
				})
		} //URT1
//==============================================================================
		//SPI0 Device Controller
		Device(SPI0) {

			//Device Identification Objects
			Name(_HID, "SPI00000")
			Name(_DDN, "SPI0")
			Name(_UID, "SPI0")
			Name(_STR, Unicode("APM88xxxx SPI0 Controller"))

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, S0CE)
				Store(One, S0RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(S0RS, One), LEqual(S0CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, S0CE)
				Store(Zero, S0RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, S0CE)
				Store(One, S0RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(S0RS, One), LEqual(S0CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)

			//Device Current Resource Settings
			//SPI0 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {106}
			})
		}//SPI0

		//SPI0 CS0 connection resource
		Name(SP00, ResourceTemplate() {
			SPISerialBus(
			1,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI0",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP00

		//SPI0 CS1 connection resource
		Name(SP01, ResourceTemplate() {
			SPISerialBus(
			2,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI0",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP01

		//SPI0 CS2 connection resource
		Name(SP02, ResourceTemplate() {
			SPISerialBus(
			4,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI0",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP02

//==============================================================================
		//SPI1 Device Controller
		Device(SPI1) {

			//Device Identification Objects
			Name(_HID, "SPI10000")
			Name(_DDN, "SPI1")
			Name(_UID, "SPI1")
			Name(_STR, Unicode("APM88xxxx SPI1 Controller"))

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, S1CE)
				Store(One, S1RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(S1RS, One), LEqual(S1CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, S1CE)
				Store(Zero, S1RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, S1CE)
				Store(One, S1RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(S1RS, One), LEqual(S1CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)

			//Device Current Resource Settings
			//SPI0 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {107}
			})
		}//SPI1

		//SPI1 CS0 connection resource
		Name(SP10, ResourceTemplate() {
			SPISerialBus(
			1,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI1",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP10

		//SPI1 CS1 connection resource
		Name(SP11, ResourceTemplate() {
			SPISerialBus(
			2,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI1",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP11

		//SPI1 CS2 connection resource
		Name(SP12, ResourceTemplate() {
			SPISerialBus(
			4,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI1",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP12

		// SDIO0
		Device(SDM0) {
			Name(_HID, "APMC0D0C") // Device Identification Objects
			Name(_CID, "APMC0D0C")
			Name(_STR, Unicode("APM X-Gene SDHCI Controller"))

			Method(_STA) {
				Return (One)
			}

			Name(_CRS, ResourceTemplate () {
				Memory32Fixed (ReadWrite, 0x1C000000, 0x100)
				Memory32Fixed (ReadWrite, 0x1f2a0000, 0x1000)
				Interrupt (ResourceConsumer, Level, ActiveHigh, ExclusiveAndWake) { 0x69 }
			})

			OperationRegion(CPL0, SystemMemory, 0x1F2A0024, 4)
			OperationRegion(CPH0, SystemMemory, 0x1F2A0028, 4)
			OperationRegion(CFG0, SystemMemory, 0x1F2A0000, 4)
			Field(CPL0, DWordAcc, NoLock, Preserve) {
				TOCF, 6,
				TOCU, 1,
				BACF, 8,
				MXBL, 2,
				EMBS, 1,
				ADM2, 1,
				RSV1, 1,
				HSST, 1,
				SDMA, 1,
				SURS, 1,
				VS33, 1,
				VS30, 1,
				VS18, 1,
				BS64, 1,
				ASIS, 1,
				SLTY, 2,
				RSV2, 2
			}
			Field(CPH0, DWordAcc, NoLock, Preserve) {
				DTAS, 1,
				DTCS, 1,
				DTDS, 1,
				TCRT, 4,
				TU50, 1,
				MODE, 2,
				CLMU, 8,
				SPIM, 1,
				SPIB, 1,
				RSV3, 12
			}
			Field(CFG0, DWordAcc, NoLock, Preserve) {
				RXWG, 4,
				TXWG, 4,
				PWMO, 4,
				RSV4, 3,
				WBRD, 1,
				RSV5, 1,
				RDPR, 2,
				RDCH, 1,
				RSV6, 1,
				WRPR, 2,
				WRCH, 1,
				RSV7, 8
			}

			// Device Power Management Methods
			// D0 State, ON
			Method(_PS0) {
				// Configure the capability of the core
				Store(0x30, TOCF)	// Time out 48MHz
				Store(One, TOCU)	// Clock unit MHz
				Store(50, BACF)		// 50MHz clock
				Store(Zero, MXBL)	// 512B block size
				Store(Zero, EMBS)	// No extend media support
				Store(Zero, ADM2)	// No ADMA2 support
				Store(Zero, RSV1)
				Store(One, HSST)	// High speed support
				Store(One, SDMA)	// SDMA support
				Store(One, SURS)	// Suspend/resume support
				Store(One, VS33)	// 3.3 voltage support
				Store(One, VS30)	// 3.0 voltage support
				Store(Zero, VS18)	// No 1.8 voltage support
				Store(Zero, BS64)	// No 64-bit
				Store(Zero, ASIS)	// Async Int
				Store(Zero, SLTY)	// Removable media
				Store(0, RSV2)

				Store(One, DTAS)	// Type A support
				Store(One, DTCS)	// Type C support
				Store(One, DTDS)	// Type D support
				Store(One, TCRT)	// 1 seconds timer counter
				Store(One, TU50)	// SDR50 tuning
				Store(Zero, MODE)	// Return mode 1
				Store(Zero, CLMU)	// Clock multipler
				Store(Zero, SPIM)	// No SPI mode
				Store(Zero, SPIB)	// No SPI block mode
				Store(Zero, RSV3)	// Reserved

				// Configure coherency
				Store(0xf, RXWG)	// Tx weight
				Store(0xf, TXWG)	// Tx weight
				Store(0x1, PWMO)	// PW Max outstanding
				Store(0x0, RSV4)	// Reserved
				Store(0x1, WBRD)	// Write block Read
				Store(0x0, RSV5)	// Reserved
				Store(0x2, RDPR)	// Read AXI sideband prio
				Store(0x1, RDCH)	// Read Coherent
				Store(0x0, RSV6)	// Reserved
				Store(0x2, WRPR)	// Write AXI sideband prio
				Store(0x1, WRCH)	// Write Coherent
				Store(0x0, RSV7)	// Reserved

				// Configure PIN Mux
				// NOTE: Default for GPIO is SD function

				// Enable clock and CSR
				Store(One, SDCE)	// Enable the clock
				Store(Zero, SDRS)	// Enable the CSR

				// Enable AHBC read to flush
				Store(1, RDFL)		// Enable read to flush

				// Remove RAM from shutdown
				Store(Zero, RMSH)	// Release from shutdown
				Sleep(1)		// Sleep 1 ms
			}

			// D3 State, OFF
			// NOTE: This is only possible if you only enable 1
			//       slot as both slot share the same clock and
			//       etc.
			Method(_PS3) {
				Store(One, SDRS)
				Store(Zero, SDCE)
			}

			// Current Power State
			Method(_PSC) {
				if (LOr(NAnd(U0RS, One), LEqual(U0CE, Zero))) {
					Return (3)
				}
				Return (0)
			}
		}
		Device(\_SB.GP01) {
			Name(_HID, "APMC0D14")
			Name(_DDN, "GP01")
			Name(_UID, "GP01")
			Name(_STR, Unicode("GFC GPIO Device Port"))
			Name(_CID, "GP01")
			Name(_CRS, ResourceTemplate() {
				Memory32Fixed(ReadWrite, 0x1701C000, 0x1000)
			})
		} //GP01 Device
	} //AHBC
////////////////////////////////////////////////////////////////////////////////
// DesignWare I2C
	Device (I2C0) {
		// Serial IO I2C0 Controller
		Name (_HID, "APMC0D0F")
		Name (_CID, "APMC0D0F")
		Name (_UID, 1)
		Name (_ADR, 0x00150001)
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x10512000, 0x10000,)
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x64 }
		})
		OperationRegion(\SMEM, SystemMemory, 0x1051E008, 4)
		Field(\SMEM, DWordAcc, NoLock, Preserve) {
			CLK0, 2,
		}
		Method(SPD, 0, NotSerialized) {
			// initial clock value
			Store(0xf4240, CLK0)
		}
		Method(_STA, 0, NotSerialized) {
			Return (0x0)
		}
	} //I2C0 -- DesignWare
////////////////////////////////////////////////////////////////////////////////
// I2C1 VRM Bus

	Device(\_SB.I2CS) {
		//Device Identification Objects
		Name(_HID, "I2CS0001")
		Name(_DDN, "I2CS")
		Name(_UID, "I2CS")
		Name(_STR, Unicode("SLIMpro IIC1 Serial Bus"))

//==============================================================================
		//PMD+L3C VRM connection resource
		Name(PCCG, ResourceTemplate() {
			I2CSerialBus(
			0x10,	//Slave Address(_ADR)
			ControllerInitiated,	//Slave Mode (_SLV)
			1000,	//Connection speed in Hz (_SPE)
			AddressingMode7Bit,	//(_MOD)
			"I2CS",	//Controller
			0,
			ResourceConsumer,
			PCVR
			)
		}) //PCCG

		//VRM Info Common to PMD+L3C
		Device(PCPV) {
			//Device Identification Objects
			Name(_HID, "PCPV0000")
			Name(_DDN, "PCCG")
			Name(_UID, "PCCG")
			Name(_STR, Unicode("APM88xxxx PMD+L3C VRM"))

			//Resources used
			Method(_CRS) {
				Return (PCCG)
			}
			Method(_PRS) {
				Return (PCCG)
			}

			//VRM Device Register Locations
			Name(POWR, 0x36)
			Name(CURR, 0x38)
			Name(VOLT, 0x40)

		} //PCPV

//==============================================================================
		//SOC VRM Connection resource
		Name(SCCG, ResourceTemplate() {
			I2CSerialBus(
			0x10,	//Slave Address(_ADR)
			ControllerInitiated,	//Slave Mode (_SLV)
			1000,	//Connection speed in Hz (_SPE)
			AddressingMode7Bit,	//(_MOD)
			"I2CS",	//Controller
			0,
			ResourceConsumer,
			SCVR
			)
		}) //SCCG

		//VRM Info for SOC domain
		Device(SOCV) {
			//Device Identification Objects
			Name(_HID, "SOCV0000")
			Name(_DDN, "SCCG")
			Name(_UID, "SCCG")
			Name(_STR, Unicode("APM88xxxx SOC VRM"))

			//Resources used
			Method(_CRS) {
				Return (SCCG)
			}
			Method(_PRS) {
				Return (SCCG)
			}

			//VRM Device Register Locations
			Name(POWR, 0x36)
			Name(CURR, 0x38)
			Name(VOLT, 0x40)
		} //SOCV


	} //I2C1

///////////////////////////////////////////////////////////////////////////////
// SATA Devices
	Device(\_SB.SAT0) {
		Name(_HID, "APMC0D00") // Device Identification Objects
		Name(_UID, 1)
		Name(_STR, Unicode("X-Gene SATA"))
		Method(_STA, 0, NotSerialized)
		{
			Return (0x0)
		}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1A000000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F210000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F21D000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F21E000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1f217000, 0x1000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0xA6}
		})
	} //SAT0
	Device(\_SB.SAT1) {
		Name(_HID, "APMC0D0D") // Device Identification Objects
		Name(_UID, 2)
		Name(_STR, Unicode("X-Gene SATA"))
		Method(_STA, 0, NotSerialized)
		{
			Return (0x1)
		}
		Name (_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1A400000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F220000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F22D000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F22E000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1f227000, 0x1000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0xA7}
		})
	} //SAT1
	Device(\_SB.SAT2) {
		Name(_HID, "APMC0D09") // Device Identification Objects
		Name(_UID, 3)
		Name(_STR, Unicode("X-Gene SATA"))
		Method(_STA, 0, NotSerialized)
		{
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1A800000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F230000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F23D000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F23E000, 0x1000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0xA8}
		})
	} //SAT2

///////////////////////////////////////////////////////////////////////////////
// USB Devices
	Device(\_SB.USB0) {
		Name(_HID, "APMC0D03")
		Name(_DDN, "USB0")
		Name(_UID, "USB0")
		Name(_STR, Unicode("X-Gene USB"))
		Method(_STA, 0, NotSerialized)
		{
			Return (0x1)
		}
		Name(_CID, "PNP0D10")
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x19000000, 0x100000)
			Memory32Fixed (ReadWrite, 0x1F280000,  0x10000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0xA9}
		})
	} //USB0
	Device(\_SB.USB1) {
		Name(_HID, "APMC0D03")
		Name(_DDN, "USB1")
		Name(_UID, "USB1")
		Name(_STR, Unicode("X-Gene USB"))
		Method(_STA, 0, NotSerialized)
		{
			Return (0x1)
		}
		Name(_CID, "PNP0D10")
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x19800000, 0x100000)
			Memory32Fixed (ReadWrite, 0x1F290000,  0x10000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0xAA}
		})
	} //USB1

///////////////////////////////////////////////////////////////////////////////
// QM Device
	Device(\_SB.QM03) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM03")
		Name(_UID, "QM03")
		Name(_STR, Unicode("QM Lite Device"))
		Name(_CID, "APMC0D04")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x17030000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x10000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x60 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x5C }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1703c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (8) {
				"max_queues", "1024",
				"devid", "3",
				"slave_name", "CPU_QMTM3",
				"slave_info", "3 0 1 32 1",
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	} // QM03

	Device(\_SB.QM01) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM01")
		Name(_UID, "QM01")
		Name(_STR, Unicode("QM 1 Device"))
		Name(_CID, "APMC0D04")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f200000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x1b000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xe0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc2 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc3 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc4 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc5 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc6 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc7 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc8 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc9 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xca }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xcb }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xcc }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xcd }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xce }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xcf }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd2 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd3 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd4 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd5 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd6 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd7 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd8 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xd9 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xda }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xdb }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xdc }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xdd }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xde }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xdf }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f20c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (8) {
				"max_queues", "1024",
				"devid", "1",
				"slave_name", "CPU_QMTM1",
				"slave_info", "1 0 32 32 32",
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	} // QM01

	Device(\_SB.QM00) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM00")
		Name(_UID, "QM00")
		Name(_STR, Unicode("QM 0 Device"))
		Name(_CID, "APMC0D04")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f600000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x18000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xA0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x80 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x81 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x82 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x83 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x84 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x85 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x86 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x87 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x88 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x89 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8a }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8b }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8c }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8d }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8e }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8f }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f60c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (8) {
				"max_queues", "1024",
				"devid", "0",
				"slave_name", "CPU_QMTM0",
				"slave_info", "0 0 16 32 16",
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	} // QM00

	Device(\_SB.QM02) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM02")
		Name(_UID, "QM02")
		Name(_STR, Unicode("QM 2 Device"))
		Name(_CID, "APMC0D04")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f700000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x1e000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xE1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x90 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x91 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x92 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x93 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x94 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x95 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x96 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x97 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x98 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x99 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9a }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9b }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9c }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9d }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9e }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9f }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f70c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (8) {
				"max_queues", "1024",
				"devid", "2",
				"slave_name", "CPU_QMTM2",
				"slave_info", "2 16 16 48 16",
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	} //QM02
///////////////////////////////////////////////////////////////////////////////
//SOC PLL and ETH Divider Fields
//Operation Region For Eth Speed Control
	OperationRegion(\SOCP, SystemMemory, 0x17000120, 4)
	Field(\SOCP, DWordAcc, NoLock, Preserve) {
		CLKF, 9,
		RSV1, 11,
		CLOD, 2,
		RSV2, 2,
		CLKR, 3,
		RSV3, 5
	}
///////////////////////////////////////////////////////////////////////////////
// Ethernet Device
// APMC0D05: For Open Source
// APMC0D19: For APM's driver. When APM driver sync up with open source then
// this ID will be changed to APMC0D05
	Device(\_SB.ET08) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET08")
		Name(_UID, "ET08")
		Name(_STR, Unicode("Ethernet RGMII Device Node Open Source"))
		Name(_CID, "APMC0D05")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x17020000, 0xd100, )
			Memory32Fixed(ReadWrite, 0x17030000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x10000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x5c }
		})

		OperationRegion(ETHD, SystemMemory, 0x17000238, 4)
		Field(ETHD, DWordAcc, NoLock, Preserve) {
			NDIV, 9,
		}
		Method(S10, 0, NotSerialized) {
			// 10Mbps requires 2.5MHz clock
			// SOC DIV 2 = REF * (CLKF/((CLKR+1) * (CLKD+1)))
			// NDIV = (SOC DIV 2)/2500000
			Store(Divide(Divide(Multiply(100000000, Divide(CLKF, Multiply(Add(CLKR, One), Add(CLOD, One)))), 2), 2500000), NDIV)
		}
		Method(S100, 0, NotSerialized) {
			// 100Mbps requires 25MHz clock
			// SOC DIV 2 = REF * (CLKF/((CLKR+1) * (CLKD+1)))
			// 100Mbps = (SOC DIV 2)/25000000
			Store(Divide(Divide(Multiply(100000000, Divide(CLKF, Multiply(Add(CLKR, One), Add(CLOD, One)))), 2), 25000000), NDIV)
		}
		Method(S1G, 0, NotSerialized) {
			// 1Gbps requires 125MHz clock
			// SOC DIV 2 = REF * (CLKF/((CLKR+1) * (CLKD+1)))
			// NDIV = (SOC DIV 2)/125000000
			Store(Divide(Divide(Multiply(100000000, Divide(CLKF, Multiply(Add(CLKR, One), Add(CLOD, One)))), 2), 125000000), NDIV)
		}
		OperationRegion(CLKQ, SystemMemory, 0x1702c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Name (_DSD, Package () {
			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
			Package () {
				Package (2) {"mac-address", Package (6) {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},
				Package (2) {"phy-channel", 3},
				Package (2) {"phy-mode", "rgmii"},
				Package (2) {"max-transfer-unit", 0x5dc},   // MTU of 1500
				Package (2) {"max-speed", 0x3e8},           // 1000 Mbps
			}
		})
	}


	Device(\_SB.ET8) {
		Name(_HID, "APMC0D19") // Device Identification Objects
		Name(_DDN, "ET08")
		Name(_UID, "ET08")
		Name(_STR, Unicode("Ethernet RGMII Device for APM kernel"))
		Name(_CID, "APMC0D19")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x17020000, 0xd100, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x58 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x59 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x5a }
		})

		OperationRegion(ETHD, SystemMemory, 0x17000238, 4)
		Field(ETHD, DWordAcc, NoLock, Preserve) {
			NDIV, 9,
		}
		Method(S10, 0, NotSerialized) {
			// 10Mbps requires 2.5MHz clock
			// SOC DIV 2 = REF * (CLKF/((CLKR+1) * (CLKD+1)))
			// NDIV = (SOC DIV 2)/2500000
			Store(Divide(Divide(Multiply(100000000, Divide(CLKF, Multiply(Add(CLKR, One), Add(CLOD, One)))), 2), 2500000), NDIV)
		}
		Method(S100, 0, NotSerialized) {
			// 100Mbps requires 25MHz clock
			// SOC DIV 2 = REF * (CLKF/((CLKR+1) * (CLKD+1)))
			// 100Mbps = (SOC DIV 2)/25000000
			Store(Divide(Divide(Multiply(100000000, Divide(CLKF, Multiply(Add(CLKR, One), Add(CLOD, One)))), 2), 25000000), NDIV)
		}
		Method(S1G, 0, NotSerialized) {
			// 1Gbps requires 125MHz clock
			// SOC DIV 2 = REF * (CLKF/((CLKR+1) * (CLKD+1)))
			// NDIV = (SOC DIV 2)/125000000
			Store(Divide(Divide(Multiply(100000000, Divide(CLKF, Multiply(Add(CLKR, One), Add(CLOD, One)))), 2), 125000000), NDIV)
		}
		OperationRegion(CLKQ, SystemMemory, 0x1702c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (14) {
				"devid", "8",
				"slave_name", "RGMII",
				"slave_info", "3 0 4 32 4",
				"max-frame-size", "9018",
				"phyid", "3",
				"phy-mode", "rgmii",
				"local-mac-address", "00:00:00:00:00:00"
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	}

	Device(\_SB.ET00) {
		Name(_HID, "APMC0D19") // Device Identification Objects
		Name(_DDN, "ET00")
		Name(_UID, "ET00")
		Name(_STR, Unicode("Ethernet SATA-SGMII Device"))
		Name(_CID, "APMC0D19")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f210000, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f210000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xac }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xad }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb0 }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f21c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 4,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0xf, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (14) {
				"devid", "0",
				"slave_name", "SGMII0",
				"slave_info", "1 0 8 32 8",
				"max-frame-size", "9018",
				"phyid", "30",
				"phy-mode", "sgmii",
				"local-mac-address", "00:00:00:00:00:00"
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	}

	Device(\_SB.ET01) {
		Name(_HID, "APMC0D19") // Device Identification Objects
		Name(_DDN, "ET01")
		Name(_UID, "ET01")
		Name(_STR, Unicode("Ethernet SATA-SGMII Device"))
		Name(_CID, "APMC0D19")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f210030, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f210000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xac }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xad }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb0 }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f21c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 4,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0xf, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (14) {
				"devid", "1",
				"slave_name", "SGMII1",
				"slave_info", "1 8 8 40 8",
				"max-frame-size", "9018",
				"phyid", "30",
				"phy-mode", "sgmii",
				"local-mac-address", "00:00:00:00:00:00"
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	}

	Device(\_SB.ET04) {
		Name(_HID, "APMC0D19") // Device Identification Objects
		Name(_DDN, "ET04")
		Name(_UID, "ET04")
		Name(_STR, Unicode("Ethernet 10Gb Device"))
		Name(_CID, "APMC0D19")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f610000, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f610000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x70 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x71 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x72 }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f61c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (14) {
				"devid", "4",
				"slave_name", "SXGMII0",
				"slave_info", "0 0 8 32 8",
				"max-frame-size", "9018",
				"phyid", "1",
				"phy-mode", "xgmii",
				"local-mac-address", "00:00:00:00:00:00"
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	}

	Device(\_SB.ET05) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET05")
		Name(_UID, "ET05")
		Name(_STR, Unicode("Ethernet 10Gb Device"))
		Name(_CID, "APMC0D05")
		Method(_STA, 0, NotSerialized) {
			Return (0x0)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f620000, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f620000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x73 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x74 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x75 }
		})
		OperationRegion(CLKQ, SystemMemory, 0x1f61c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, CLKE)
			Stall(100)
		}
		Method(_DSM, 4, NotSerialized) {
			Store (Package (14) {
				"devid", "5",
				"slave_name", "SXGMII1",
				"slave_info", "0 0 8 32 8",
				"max-frame-size", "9018",
				"phyid", "1",
				"phy-mode", "xgmii",
				"local-mac-address", "00:00:00:00:00:00"
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	}
///////////////////////////////////////////////////////////////////////////////
//PCIe0
	Device(\_SB.PCI0) {
            //
            // Hardware ID must be PNP0A08, which maps to a PCIe root complex.
            // Section 6.1.5
            //

            Name(_HID,"PNP0A08")

            //
            // Optionally, include a compatible ID of PNP0A03, which maps to a PCI
            // root complex for use with pre-PCIe operating systems.
            // Section 6.1.2
            //

            Name(_CID,"PNP0A03")

            //
            // Declare the segment number of this root complex. Most systems only
            // have one segment, which is numbered 0.
            // Section 6.5.6
            //

            Name(_SEG, 0)

            //
            // Declare the base bus number, which is the bus number of the root
            // bus in this root complex. This is usually 0, but need not be.
            // For root complexes supporting multiple root busses, this should
            // be the lowest numbered root bus.
            // Section 6.5.5
            //

            Name(_BBN, 0)

            //
            // The _UID value provides a way of uniquely identifying a device
            // in the case where more than one instance of a specific device
            // is implemented with the same _HID/_CID. For systems with a
            // single root complex, this is usually just 0. For systems with
            // multiple root complexes, this should be different for each
            // root complex.
            // Section 6.1.12
            //

            Name(_UID, "PCI0")
			Name(_STR, Unicode("PCIe 0 Device"))

            //
            // Declare the PCI Routing Table.
            // This defines SPI mappings of the four line-based interrupts
            // associated with the root complex and hierarchy below it.
            // Section 6.2.12
            //

            Name(_PRT, Package() {

                //
                // Routing for device 0, all functions.
                // Note: ARM doesn't support LNK nodes, so the third param
                // is 0 and the fourth param is the SPI number of the interrupt
                // line. In this example, the A/B/C/D interrupts are wired to
                // SPI lines 100/101/102/103 respectively.
                //

                Package() {0x0000FFFF, 0, 0, 226},
                Package() {0x0000FFFF, 1, 0, 227},
                Package() {0x0000FFFF, 2, 0, 228},
                Package() {0x0000FFFF, 3, 0, 229},
            })

            //
            // Declare the resources assigned to this root complex.
            // Section 6.2.2
            //
			Method (_CBA, 0, Serialized) {
				Return (0xE0D0000000)
			}
            Method (_CRS, 0, Serialized) {

                //
                // Declare a ResourceTemplate buffer to return the resource
                // requirements from _CRS.
                // Section 19.5.109
                //

                Name (RBUF, ResourceTemplate () {

                    //
                    // Declare the range of bus numbers assigned to this root
                    // complex. In this example, the minimum bus number will be
                    // 0, the maximum bus number will be 0xFF, supporting
                    // 256 busses total.
                    // Section 19.5.141
                    //

                    WordBusNumber (
                        ResourceProducer,
                        MinFixed,   // IsMinFixed
                        MaxFixed,   // IsMaxFixed
                        PosDecode,  // Decode
                        0,          // AddressGranularity
                        0,          // AddressMinimum - Minimum Bus Number
                        255,        // AddressMaximum - Maximum Bus Number
                        0,          // AddressTranslation - Set to 0
                        256)        // RangeLength - Number of Busses

                    //
                    // Declare the memory range to be used for BAR memory
                    // windows. This declares a 4GB region starting at
                    // 0x4000000000.
                    // Section 19.5.80
                    //
					Memory32Fixed(ReadWrite, 0x1F2B0000, 0x10000, )

					QWordIO(
						ResourceConsumer,
						MinFixed,
						MaxFixed,
						PosDecode,
						EntireRange,
						0x0000000000000000,
						0x0000000010000000,
						0x000000001000FFFF,
						0x000000E000000000,
						0x0000000000010000
					)
					QWordMemory(
						ResourceConsumer,
						PosDecode,
						MinFixed,
						MaxFixed,
						Cacheable,
						ReadWrite,
						0x0000000000000000,
						0x0000000030000000,
						0x0000000030FFFFFF,
						0x000000E000000000,
						0x0000000001000000
					)
					QWordMemory(
						ResourceConsumer,
						PosDecode,
						MinFixed,
						MaxFixed,
						Cacheable,
						ReadWrite,
						0x0000000000000000,
						0x000000e100000000,
						0x000000e13FFFFFFF,
						0x0000000000000000,
						0x0000000040000000
					)
				})

                Return (RBUF)
            }

            //
            // Declare an _OSC (OS Control Handoff) method which takes 4 arguments.
            //
            // Argments:
            //   Arg0  A Buffer containing a UUID
            //   Arg1  An Integer containing a Revision ID of the buffer format
            //   Arg2  An Integer containing a count of entries in Arg3
            //   Arg3  A Buffer containing a list of DWORD capabilities
            // Return Value:
            //   A Buffer containing a list of capabilities
            // See the APCI spec, Section 6.2.10,
            // and the PCI FW spec, Section 4.5.
            //
            // The following is an example, and may need modification for
            // specific implementations.
            //

            Name(SUPP,0) // PCI _OSC Support Field value
            Name(CTRL,0) // PCI _OSC Control Field value
            Method(_OSC, 4) {

                //
                // Look for the PCI Host Bridge Interface UUID.
                // Section 6.2.10.3
                //

                //
                // Create DWord-adressable fields from the Capabilities Buffer
                // Create CDW1 outside the test as it's used in the else clause.
                //

                CreateDWordField(Arg3,0,CDW1)
                If(LEqual(Arg0,ToUUID("33DB4D5B-1FF7-401C-9657-7441C03DD766"))) {

                    CreateDWordField(Arg3,4,CDW2)
                    CreateDWordField(Arg3,8,CDW3)

                    //
                    // Save Capabilities DWord 2 & 3
                    //

                    Store(CDW2,SUPP)
                    Store(CDW3,CTRL)

                    //
                    // Only allow native hot plug control if OS supports:
                    //  ASPM
                    //  Clock PM
                    //  MSI/MSI-X
                    //

					// Storm, no hotplug, but still return bit 0 set
					// because win won't be happy.
					And(CTRL,0x1D,CTRL)

                    //If(LNotEqual(And(SUPP, 0x16), 0x16)) {

                        //
                        // Mask bit 0 (and undefined bits)
                        //

                      //  And(CTRL,0x1E,CTRL)
                    //}

                    //
                    // Always allow native PME, AER (no dependencies).
                    // Never allow SHPC (no SHPC controller in this system).
                    //

                    And(CTRL,0x1D,CTRL)

                    //
                    // Check for unknown revision.
                    //

                    If(LNotEqual(Arg1,One)) {
                        Or(CDW1,0x08,CDW1)
                    }

                    //
                    // Check if capabilities bits were masked.
                    //

                    If(LNotEqual(CDW3,CTRL)) {
                        Or(CDW1,0x10,CDW1)
                    }

                    //
                    // Update DWORD3 in the buffer.
                    //

                    Store(CTRL,CDW3)
                    Return(Arg3)

                } Else {

                    //
                    // Unrecognized UUID
                    //

                    Or(CDW1,4,CDW1)
                    Return(Arg3)
                }
            } // End _OSC

            //
            // Declare a _DSM method for various functions called by the OS.
            // See the APCI spec, Section 9.14.1,
            // and the PCI FW spec, Section 4.6.
            // See also:
            // http://download.microsoft.com/download/9/c/5/9c5b2167-8017-4bae-9fde-d599bac8184a/PCI-rsc.doc
            //

            Method(_DSM, 0x4, Serialized) {

                //
                // Match against the _DSM PCI GUID.
                //

                If(LEqual(Arg0,ToUUID("E5C937D0-3553-4d7a-9117-EA4D19C3434D"))) {

                    switch(ToInteger(Arg2))
                    {
                        //
                        // Function 0: Return supported functions as a bitfield
                        // with one bit for each supported function.
                        // Bit 0 must always be set, as that represents
                        // function 0 (which is what is being called here).
                        // Support for different functions may depend on
                        // the revision ID of the interface, passed as Arg1.
                        //

                        case(0) {

                            //
                            // Functions 0-7 are supported.
                            //

                            return (Buffer() {0x01})
                        }


                    }
                }

                //
                // If not one of the function identifiers we recognize, then return a buffer
                // with bit 0 set to 0 indicating no functions supported.
                //

                return(Buffer(){0})
            }

             //
            // Root Port 0 Device within the Root Complex.
            //

            Device(RP0) {

                //
                // Device 0, Function 0.
                //

                Name(_ADR, 0x00000000)

                //
                // Power resources required for D0.
                //

                Name(_PR0, Package() {SCVR})

                //
                // Power resources required for D3Hot.
                //

                Name(_PR3, Package(){SCVR})
            }
	} // PCI0

///////////////////////////////////////////////////////////////////////////////
// MSI
	Device(\_SB.MSIX) {
		Name(_HID, "APMC0D0E") // Device Identification Objects
		Name(_UID, 0)
		Name(_STR, Unicode("X-Gene MSI/MSIX"))
		Method(_STA, 0, NotSerialized)
		{
			Return (One)
		}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x79000000, 0x900000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x30}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x31}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x32}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x33}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x34}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x35}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x36}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x37}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x38}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x39}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x3A}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x3B}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x3C}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x3D}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x3E}
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x3F}
		})
		Method(_DSM, 4, NotSerialized) {
			Store (Package (2) {
				"msi-available-ranges", "0x0 0x1000",
			}, Local0)
			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))
			Return (Local0)
		}
	}

///////////////////////////////////////////////////////////////////////////////
// PktDMA
	Device(\_SB.PDMA) {
		Name(_HID, "APMC0D16") // Device Identification Objects
		Name(_UID, 0)
		Name(_STR, Unicode("X-Gene PktDMA"))
		Method(_STA, 0, NotSerialized) {
			Return (One)
		}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1f270000, 0x10000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0xA3}
		})
		OperationRegion(RSTQ, SystemMemory, 0x1f27c000, 4)
		Field(RSTQ, DWordAcc, NoLock, Preserve) {
			RSTE, 2,
		}
		OperationRegion(CLKQ, SystemMemory, 0x1f27c008, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			CLKE, 2,
		}
		Method(_INI, 0, NotSerialized) {
			Store(0x3, RSTE)
			Stall(100)
			Store(0x0, RSTE)
			Stall(100)
			Store(0x3, CLKE)
			Stall(100)
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Pkt
	Device(\_SB.PKA) {
		Name(_HID, "APMC0D17") // Device Identification Objects
		Name(_UID, 0)
		Name(_STR, Unicode("X-Gene Pka"))
		Method(_STA, 0, NotSerialized) {
			Return (One)
		}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x10524000, 0x4000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x63}
		})
		OperationRegion(RSTQ, SystemMemory, 0x1700000c, 4)
		Field(RSTQ, DWordAcc, NoLock, Preserve) {
			RSV1, 4,
			RSTE, 1,
		}
		OperationRegion(CLKQ, SystemMemory, 0x17000010, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			RSV2, 4,
			CLKE, 1,
		}
		Method(_INI, 0, NotSerialized) {
			If (LNot(CLKE)) {
				Store(0x1, RSTE)
				Stall(100)
				Store(0x0, RSTE)
				Stall(100)
				Store(0x1, CLKE)
				Stall(100)
			}
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Trng
	Device(\_SB.TRNG) {
		Name(_HID, "APMC0D18") // Device Identification Objects
		Name(_UID, 0)
		Name(_STR, Unicode("X-Gene TRNG"))
		Method(_STA, 0, NotSerialized) {
			Return (One)
		}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x10520000, 0x4000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x61}
		})
		OperationRegion(RSTQ, SystemMemory, 0x1700000c, 4)
		Field(RSTQ, DWordAcc, NoLock, Preserve) {
			RSV1, 4,
			RSTE, 1,
		}
		OperationRegion(CLKQ, SystemMemory, 0x17000010, 4)
		Field(CLKQ, DWordAcc, NoLock, Preserve) {
			RSV2, 4,
			CLKE, 1,
		}
		Method(_INI, 0, NotSerialized) {
			If (LNot(CLKE)) {
				Store(0x1, RSTE)
				Stall(100)
				Store(0x0, RSTE)
				Stall(100)
				Store(0x1, CLKE)
				Stall(100)
			}
		}
	}

///////////////////////////////////////////////////////////////////////////////
}//DSDT
