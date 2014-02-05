/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 *
 * [DSDT] Description of the Arndale board (exynos5250)
 *
 * This source is released under the terms of the GPLv2.
 */

DefinitionBlock (
	"dsdt.aml",             // output filename
	"DSDT",                 // table signature
	2,                      // DSDT compliance revision
	"LINARO",               // OEM ID
	"ARNDALE ",             // table ID
	0x00000003)             // OEM revision
{
	Scope (\_SB)
	{
		Device (GPB3) {
		}

		Device (I2C) {
			Name (_HID, "LINA0001")
			Name (_UID, 0)

			Method (_CRS, 0x0, Serialized) {
				Name (RBUF, ResourceTemplate ()
				{
					Memory32Fixed (ReadWrite, 0x12C60000, 0x00000100)
					Interrupt (ResourceConsumer, Level, ActiveLow, Exclusive, , , ) {0x58}
					GpioIo (Exclusive, PullDefault, , , , "\\_SB.GPB3") {0x2A, 0x2B}
				})
				Return (RBUF)
			}

			Method (DLAY, 0x0, NotSerialized) {
				Return (100)
			}

			Method (SADD, 0x0, NotSerialized) {
				Return (0x66)
			}

			Method (FREQ, 0x0, NotSerialized) {
				Return (20000)
			}
		}

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
				/* 0000 */    0x0B, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, /* type, len, reserved, gic_id */
				/* 0008 */    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, /* uid, flags */
				/* 0010 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* parking_version, performance_interrupt */
				/* 0018 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* parked_address */
				/* 0020 */    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* base_address */
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
		}
	}
}
