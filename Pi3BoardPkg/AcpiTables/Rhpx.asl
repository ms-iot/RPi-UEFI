//
// RHProxy Device Node to enable WinRT API
//
Device(RHPX)
{
    Name(_HID, "MSFT8000")
    Name(_CID, "MSFT8000")
    Name(_UID, 1)

    Name(_CRS, ResourceTemplate()
    {
        // Index 0
        SPISerialBus(              // SCKL - GPIO 11 - Pin 23
                                   // MOSI - GPIO 10 - Pin 19
                                   // MISO - GPIO 9  - Pin 21
                                   // CE0  - GPIO 8  - Pin 24
            0,                     // Device selection (CE0)
            PolarityLow,           // Device selection polarity
            FourWireMode,          // wiremode
            8,                     // databit len
            ControllerInitiated,   // slave mode
            4000000,               // connection speed
            ClockPolarityLow,      // clock polarity
            ClockPhaseFirst,       // clock phase
            "\\_SB.SPI0",          // ResourceSource: SPI bus controller name
            0,                     // ResourceSourceIndex
                                   // Resource usage
                                   // DescriptorName: creates name for offset of resource descriptor
            )                      // Vendor Data

        // Index 1
        SPISerialBus(              // SCKL - GPIO 11 - Pin 23
                                   // MOSI - GPIO 10 - Pin 19
                                   // MISO - GPIO 9  - Pin 21
                                   // CE1  - GPIO 7  - Pin 26
            1,                     // Device selection (CE1)
            PolarityLow,           // Device selection polarity
            FourWireMode,          // wiremode
            8,                     // databit len
            ControllerInitiated,   // slave mode
            4000000,               // connection speed
            ClockPolarityLow,      // clock polarity
            ClockPhaseFirst,       // clock phase
            "\\_SB.SPI0",          // ResourceSource: SPI bus controller name
            0,                     // ResourceSourceIndex
                                   // Resource usage
                                   // DescriptorName: creates name for offset of resource descriptor
            )                      // Vendor Data

        // Index 2
        I2CSerialBus(              // Pin 3 (GPIO2, SDA1), 5 (GPIO3, SCL1)
            0xFFFF,                // SlaveAddress: placeholder
            ,                      // SlaveMode: default to ControllerInitiated
            0,                     // ConnectionSpeed: placeholder
            ,                      // Addressing Mode: default to 7 bit
            "\\_SB.I2C1",          // ResourceSource: I2C bus controller name
            ,
            ,
            ,                      // Descriptor Name: creates name for offset of resource descriptor
            )                      // VendorData
            
        // Index 3
        SPISerialBus(              // SPI1_SCLK - GPIO21
                                   // SPI1_MOSI - GPIO20
                                   // SPI1_MISO - GPIO19
                                   // SPI1_CE2_N - GPIO16
            2,                     // Device selection (CE2)
            PolarityLow,           // Device selection polarity
            FourWireMode,          // wiremode
            8,                     // databit len
            ControllerInitiated,   // slave mode
            4000000,               // connection speed
            ClockPolarityLow,      // clock polarity
            ClockPhaseFirst,       // clock phase
            "\\_SB.SPI1",          // ResourceSource: SPI bus controller name
            0,                     // ResourceSourceIndex
                                   // Resource usage
                                   // DescriptorName: creates name for offset of resource descriptor
            )                      // Vendor Data

        // GPIO 2
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 2 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 2 }
        // GPIO 3
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 3 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 3 }
        // GPIO 4
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 4 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 4 }
        // GPIO 5
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 5 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 5 }
        // GPIO 6
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 6 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 6 }
        // GPIO 7
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 7 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 7 }
        // GPIO 8
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 8 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                            { 8 }
        // GPIO 9
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 9 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 9 }
        // GPIO 10
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 10 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 10 }
        // GPIO 11
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 11 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 11 }
        // GPIO 12
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 12 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 12 }
        // GPIO 13
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 13 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 13 }
        // NTRAID#MSFT-7141401-2016/04/7-jordanrh - disable UART muxing
        // until a proper solution can be created for the dmap conflict
        // GPIO 14 - UART TX
        // GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 14 }
        // GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 14 }
        // GPIO 15 - UART RX
        // GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 15 }
        // GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 15 }
        // GPIO 16
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 16 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 16 }
        // GPIO 17
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 17 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 17 }
        // GPIO 18
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 18 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 18 }
        // GPIO 19
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 19 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 19 }
        // GPIO 20
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 20 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 20 }
        // GPIO 21
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 21 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 21 }
        // GPIO 22
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 22 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 22 }
        // GPIO 23
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 23 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 23 }
        // GPIO 24
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 24 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 24 }
        // GPIO 25
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 25 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 25 }
        // GPIO 26
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 26 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 26 }
        // GPIO 27
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 27 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 27 }
	
//symbol CM_IO_BOARD is used to add extended GPIO pins for Compute Module IO Board, you can define at here or from -D command line option
//#define CM_IO_BOARD 
#ifdef CM_IO_BOARD
		
		// GPIO 28
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 28 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 28 }
		
		// GPIO 29
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 29 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 29 }
		
		// GPIO 30
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 30 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 30 }
		
		// GPIO 31
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 31 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 31 }
		
		// GPIO 32
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 32 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 32 }
		
		// GPIO 33
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 33 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 33 }
		
		// GPIO 34
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 34 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 34 }
		
		// GPIO 35
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 35 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 35 }
		
		// GPIO 36
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 36 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 36 }
		
		// GPIO 37
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 37 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 37 }
		
		// GPIO 38
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 38 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 38 }
		
		// GPIO 39
        GpioIO(Shared, PullDown, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , ) { 39 }
        GpioInt(Edge, ActiveBoth, Shared, PullDown, 0, "\\_SB.GPI0",)                            { 39 }
		
		// GPIO 40
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 40 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 40 }
		
		// GPIO 41
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 41 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 41 }
		
		// GPIO 42
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 42 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 42 }
		
		// GPIO 43
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 43 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 43 }
		
		// GPIO 44
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 44 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 44 }
		
        // GPIO 45
        GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPI0", 0, ResourceConsumer, , )   { 45 }
        GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPI0",)                              { 45 }
#endif
    })

    Name(_DSD, Package()
    {
        ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
        Package()
        {
            // Reference http://www.raspberrypi.org/documentation/hardware/raspberrypi/spi/README.md
            // SPI 0
            Package(2) { "bus-SPI-SPI0", Package() { 0, 1 }},                       // Index 0 & 1
            Package(2) { "SPI0-MinClockInHz", 7629 },                               // 7629 Hz
            Package(2) { "SPI0-MaxClockInHz", 125000000 },                          // 125 MHz
            Package(2) { "SPI0-SupportedDataBitLengths", Package() { 8 }},          // Data Bit Length
            // I2C1
            Package(2) { "bus-I2C-I2C1", Package() { 2 }},
            // GPIO Pin Count and supported drive modes
            Package (2) { "GPIO-PinCount", 54 },
            Package (2) { "GPIO-UseDescriptorPinNumbers", 1 },
            Package (2) { "GPIO-SupportedDriveModes", 0xf },                        // InputHighImpedance, InputPullUp, InputPullDown, OutputCmos
            // SPI 1
            Package(2) { "bus-SPI-SPI1", Package() { 3 }},                          // Index 3
            Package(2) { "SPI1-MinClockInHz", 30511 },                              // 30.5 kHz
            Package(2) { "SPI1-MaxClockInHz", 20000000 },                           // 20 MHz
            Package(2) { "SPI1-SupportedDataBitLengths", Package() { 8 }},          // Data Bit Length
        }
    })
}
