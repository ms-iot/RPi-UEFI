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
	"dsdt.aml",		// output filename
	"DSDT",			// table signature
	2,			// DSDT compliance revision
	"LINARO",		// OEM ID
	"RTSMVEV8",		// table ID
	0x00000004)		// OEM revision
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

		Device (HED)
		{
			Name (_HID, EisaId ("PNP0C33"))
			Name (_UID, 0x00)
		}

		Device (SCK0)
		{
			Name (_HID, "ACPI0004")
			Name (_UID, 0x00)
			Method (_STA, 0, NotSerialized)
			{
				Return (0x0F)
			}

			Device (PRC0)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x00)

				/* CPU0 will be always present */
				Method (_STA, 0, NotSerialized)
				{
					Return (0x0F)
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* type, len, reserved, gic_id */
				/* 0008 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* uid, flags */
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* parking_version, performance_interrupt */
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* parked_address */
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* base_address */
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0008 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}

			Device (PRC1)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x01)

				Name (STA1, 0x0F)
				Method (_STA, 0, NotSerialized)
				{
					Return (STA1)
				}

				Method (_EJ0, 1, NotSerialized)
				{
					If (LEqual (STA1, 0x0F))
					{
						Store (0x00, STA1)
					}
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				/* 0008 */    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				/* 0008 */    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}

			Device (PRC2)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x02)

				Name (STA2, 0x0F)
				Method (_STA, 0, NotSerialized)
				{
					Return (STA2)
				}

				Method (_EJ0, 1, NotSerialized)
				{
					If (LEqual (STA2, 0x0F))
					{
						Store (0x00, STA2)
					}
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
				/* 0008 */    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
				/* 0008 */    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}

			Device (PRC3)
			{
				Name (_HID, "ACPI0007")
				Name (_UID, 0x03)

				Name (STA3, 0x0F)
				Method (_STA, 0, NotSerialized)
				{
					Return (STA3)
				}

				Method (_EJ0, 1, NotSerialized)
				{
					If (LEqual (STA3, 0x0F))
					{
						Store (0x00, STA3)
					}
				}

				Name (MAT0, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
				/* 0008 */    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Name (MAT1, Buffer (0x28)
				{
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
				/* 0008 */    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
				})

				Method (_MAT, 0, NotSerialized)
				{
					If (_STA())
					{
						Return (MAT0)
					}
					Else
					{
						Return (MAT1)
					}
				}
			}
		}

		Device (PMU0) {
			Name (_HID, "LNRO0007")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {92, 93, 94, 95}
				})
				Return (RBUF)
			}
		}

                Device (SMB) {
                        Name (_HID, "ACPI0004")
                        Name (_UID, 0)

                        Name (_CRS, ResourceTemplate () {

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x08000000,         // Address Range Minimum   (base address in FDT)
                        0x0BFFFFFF,         // Address Range Maximum   (base + (len-1))
                        0x00000000,         // Address Translation Offset
                        0x04000000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x14000000,         // Address Range Minimum   (base address in FDT)
                        0x17FFFFFF,         // Address Range Maximum   (base + (len-1))
                        0x00000000,         // Address Translation Offset
                        0x04000000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x18000000,         // Address Range Minimum   (base address in FDT)
                        0x1BFFFFFF,         // Address Range Maximum   (base + (len-1))
                        0x00000000,         // Address Translation Offset
                        0x04000000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x1C000000,         // Address Range Minimum   (base address in FDT)
                        0x1FFFFFFF,         // Address Range Maximum   (base + (len -1))
                        0x00000000,         // Address Translation Offset
                        0x04000000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x0C000000,         // Address Range Minimum   (base address in FDT)
                        0x0FFFFFFF,         // Address Range Maximum   (base + (len-1))
                        0x00000000,         // Address Translation Offset
                        0x04000000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x10000000,         // Address Range Minimum   (base address in FDT)
                        0x13FFFFFF,         // Address Range Maximum   (base + (len-1))
                        0x00000000,         // Address Translation Offset
                        0x04000000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)

                        })

		Device (NET0) {
			Name (_HID, "LNRO0003")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1a000000, 0x00010000)
					Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {0x2F}
				})
				Return (RBUF)
			}
		}

                Device (CLK0) {
                        Name (_HID, "LNRO0008")
                        Name (_UID, 0)

                        Method (FREQ, 0x0, NotSerialized) {
                                Return (24000000)
                        }
                }

                Device (CLK1) {
                        Name (_HID, "LNRO0008")
                        Name (_UID, 1)

                        Method (FREQ, 0x0, NotSerialized) {
                                Return (1000000)
                        }
                }

                Device (CLK2) {
                        Name (_HID, "LNRO0008")
                        Name (_UID, 2)

                        Method (FREQ, 0x0, NotSerialized) {
                                Return (32768)
                        }
                }

                Device (FPGA) {
                        Name (_HID, "ACPI0004")
                        Name (_UID, 0)

                        Name (_CRS, ResourceTemplate () {

                        DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
                        0x00000000,         // Address Space Granularity
                        0x1C000000,         // Address Range Minimum   (base address in FDT)
                        0x1C1FFFFF,         // Address Range Maximum   (base + (len-1))
                        0x00000000,         // Address Translation Offset
                        0x00200000,         // Address Length           (len in FDT)
                        ,, , AddressRangeMemory, TypeStatic)
                        })

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

                Device (VIRT) {
                        Name (_HID, "LNRO0005")
                        Name (_UID, 0)

                        Method (_CRS, 0x0, Serialized) {
                                Name (RBUF, ResourceTemplate() {
                                        Memory32Fixed (ReadWrite, 0x1c130000, 0x1000)
                                        Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {0x4A}
                                })
                                Return (RBUF)
                        }
                }
        } // End of FPGA
        } // End SMB

        Method (DTGP, 5, NotSerialized)
        {
                If (LEqual (Arg0, Buffer (0x10)
                {
                /* UUID:        a706b112-bf0b-48d2-9fa3-95591a3c4c06 */
                /* 0000 */    0xa7, 0x06, 0xb1, 0x12, 0xbf, 0x0b, 0x48, 0xd2,
                /* 0008 */    0x9f, 0xa3, 0x95, 0x59, 0x1a, 0x3c, 0x4c, 0x06
                }))
                {
                If (LEqual (Arg1, 0x01)) {
                        If (LEqual (Arg2, 0x00)) {
                                Store (Buffer (0x01)
                                {
                                0x03
                                }, Arg4)
                                Return (0x01)
                        }

                        If (LEqual (Arg2, 0x01)) {
                                Return (0x01)
                        }
                }
                }

                Store (Buffer (0x01)
                {
                        0x00
                }, Arg4)

                Return (0x00)
        }

	Device (REG0) {
		Name (_HID, "LNRO0019")
		Name (_UID, 0)

		Method(_DSM, 4, NotSerialized) {
			Store (Package (8)
			{
                        "regulator-name", "3V3",
                        "regulator-min-microvolt", "3300000",
                        "regulator-max-microvolt", "3300000",
                        "regulator-always-on", "1",
			}, Local0)

			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

			Return (Local0)
		}
	}

	Device (FLH0) {
		Name (_HID, "LNRO0015")
		Name (_UID, 0)
		Method (_CRS, 0x0, Serialized) {
			Name (RBUF, ResourceTemplate () {
				Memory32Fixed (ReadWrite, 0x08000000, 0x04000000)
				Memory32Fixed (ReadWrite, 0x0C000000, 0x04000000)
			})
			Return (RBUF)
		}

		Method(_DSM, 4, NotSerialized) {
			Store (Package ()
			{
				"bank-width", "4",
			}, Local0)

			DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

			Return (Local0)
		}
	}

        Device (AMBA) {
                Name (_HID, "AMBA0000")
                Name (_UID, 0)

                /* Define 'apb_pclk' as a default clock source since it is
                        common with devices below */

                Method(_DSM, 4, NotSerialized) {
                        Store (Package (2)
                        {
                                "clock-name", "apb_pclk \\_SB.SMB.CLK0",
                                }, Local0)

                                DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

                                Return (Local0)
                }

		Device (SCT0) {
                        Name (_HID, "LNRO000C")
                        Name (_UID, 0)
			Name (_ADR, 0x1c020000)						/* SYSCTL */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c020000, 0x00001000)
				})
				Return (RBUF)
			}
			Method(_DSM, 4, Serialized) {
				Store (Package (4)
				{
					"clock-name", "refclk \\_SB.SMB.CLK2",
					"clock-name", "timclk \\_SB.SMB.CLK1",
				}, Local0)

				DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

				Return (Local0)
			}
		}

		Device (AAC0) {
                        Name (_HID, "LNRO000D")
                        Name (_UID, 0)
			Name (_ADR, 0x1c040000)						/* AACI */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c040000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {43}
				})
				Return (RBUF)
			}
		}

		Device (MMC0) {
			Name (_HID, "LNRO000E")
			Name (_UID, 0)
			Name (_ADR, 0x1c050000)						/* MMCI */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c050000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {41, 42}
				})
				Return (RBUF)
			}
			Method(_DSM, 4, Serialized) {
				Store (Package (2)
				{
					"clock-name", "MCLK \\_SB.SMB.CLK0",
				}, Local0)

				DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

				Return (Local0)
			}
		}

		Device (KMI0) {
                        Name (_HID, "LNRO000F")
                        Name (_UID, 0)
			Name (_ADR, 0x1c060000)
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c060000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {44}
				})
				Return (RBUF)
			}
			Method(_DSM, 4, Serialized) {
				Store (Package (2)
				{
					"clock-name", "KMIREFCLK \\_SB.SMB.CLK0",
				}, Local0)

				DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

				Return (Local0)
			}
		}

		Device (KMI1) {
                        Name (_HID, "LNRO000F")
                        Name (_UID, 1)
			Name (_ADR, 0x1c070000)
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c070000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {45}
				})
				Return (RBUF)
			}
			Method(_DSM, 4, NotSerialized) {
				Store (Package (2)
				{
					"clock-name", "KMIREFCLK \\_SB.SMB.CLK0",
				}, Local0)

				DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

				Return (Local0)
			}
		}

                Device (SER0) {
                        Name (_HID, "LNRO000A")
                        Name (_ADR, 0x1c090000)
                        Name (_UID, 0)

                        Method (_CRS, 0x0, Serialized) {
                                Name (RBUF, ResourceTemplate() {
                                        Memory32Fixed (ReadWrite, 0x1c090000, 0x1000)
                                        Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x25}
                                })
                        Return (RBUF)
                        }
                }

                Device (SER1) {
                        Name (_HID, "LNRO000A")
                        Name (_ADR, 0x1c0a0000)
                        Name (_UID, 1)

                        Method (_CRS, 0x0, Serialized) {
                                Name (RBUF, ResourceTemplate() {
                                        Memory32Fixed (ReadWrite, 0x1c0a0000, 0x1000)
                                        Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x26}
                                })
                        Return (RBUF)
                        }
                }

                Device (SER2) {
                        Name (_HID, "LNRO000A")
                        Name (_ADR, 0x1c0b0000)
                        Name (_UID, 2)

                        Method (_CRS, 0x0, Serialized) {
                                Name (RBUF, ResourceTemplate() {
                                        Memory32Fixed (ReadWrite, 0x1c0b0000, 0x1000)
                                        Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x27}
                                })
                        Return (RBUF)
                        }
                }

                Device (SER3) {
                        Name (_HID, "LNRO000A")
                        Name (_ADR, 0x1c0c0000)
                        Name (_UID, 3)

                        Method (_CRS, 0x0, Serialized) {
                                Name (RBUF, ResourceTemplate() {
                                        Memory32Fixed (ReadWrite, 0x1c0c0000, 0x1000)
                                        Interrupt (ResourceConsumer, Edge, ActiveBoth, Exclusive, , , ) {0x28}
                        })
                        Return (RBUF)
                        }
                }

		Device (WDT0) {
                        Name (_HID, "LNRO0011")
                        Name (_UID, 0)
			Name (_ADR, 0x1c0f0000)						/* WDT */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c0f0000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {32}
				})
				Return (RBUF)
			}
		}

		Device (TIM0) {
                        Name (_HID, "LNRO0012")
                        Name (_UID, 0)
			Name (_ADR, 0x1c110000)						/* TIMER01 */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c110000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {34}
				})
				Return (RBUF)
			}
		}

		Device (TIM2) {
                        Name (_HID, "LNRO0012")
                        Name (_UID, 1)
			Name (_ADR, 0x1c120000)						/* TIMER23 */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c120000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {35}
				})
				Return (RBUF)
			}
		}

		Device (RTC0) {
                        Name (_HID, "LNRO0013")
                        Name (_UID, 0)
			Name (_ADR, 0x1c170000)						/* RTC */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c170000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {36}
				})
				Return (RBUF)
			}
		}

		Device (CLCD) {
                        Name (_HID, "LNRO0014")
                        Name (_UID, 0)
			Name (_ADR, 0x1c1f0000)						/* CLCD */
			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate () {
					Memory32Fixed (ReadWrite, 0x1c1f0000, 0x00001000)
					Interrupt (ResourceConsumer, Edge, ActiveBoth,
							Exclusive, , , ) {46}
				})
				Return (RBUF)
			}
			Method(_DSM, 4, Serialized) {
				Store (Package (2)
				{
					"clock-name", "CCLDCLK \\_SB.SMB.CLK0",
				}, Local0)

				DTGP (Arg0, Arg1, Arg2, Arg3, RefOf (Local0))

				Return (Local0)
			}
		}

        } // End of AMBA
	}
}
