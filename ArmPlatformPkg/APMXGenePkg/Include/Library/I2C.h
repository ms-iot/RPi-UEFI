/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *  
 *  This program and the accompanying materials
 *  are licensed and made available under the terms and conditions of the BSD License
 *  which accompanies this distribution.  The full text of the license may be found at
 *  http://opensource.org/licenses/bsd-license.php
 *  
 *  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *  
 **/

#ifndef _I2C_H_
#define _I2C_H_

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>

/*
 * Many boards/controllers/drivers don't support an I2C slave INTNerface so
 * provide a default slave address for them for use in common code.  A real
 * value for CONFIG_SYS_I2C_SLAVE should be defined for any board which does
 * support a slave INTNerface.
 */
#ifndef  CONFIG_SYS_I2C_SLAVE
#define  CONFIG_SYS_I2C_SLAVE  0x52
#endif

#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS 8
#define CONFIG_SYS_I2C_SPEED      100000  /* I2C speed */
#define CONFIG_SYS_I2C_EEPROM_ADDR  0x51
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN  1 /* Bytes of address */
#define CONFIG_SYS_I2C_EEPROM_PAGE_WRITE_LEN  8

#define CONFIG_SYS_I2C1_SPEED 100000  /* I2C speed */
#define CONFIG_SYS_I2C1_EEPROM_ADDR 0x52
#define CONFIG_SYS_I2C1_EEPROM_ADDR_LEN  2  /* Bytes of address */
#define CONFIG_SYS_I2C1_EEPROM_PAGE_WRITE_LEN 256
#define IIC0_BOOTPROM_ADDR  0x50
#define IIC0_ALT_BOOTPROM_ADDR  0x54


/*
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 * The implementation MUST NOT use static or global variables if the
 * I2C routines are used to read SDRAM configuration information
 * because this is done before the memories are initialized. Limited
 * use of stack-based variables are OK (the initial stack size is
 * limited).
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 */

/*
 * Initialization, must be called once on start up, may be called
 * repeatedly to change the speed and slave addresses.
 */
VOID I2c_Init(INTN, INTN);

#ifdef CONFIG_SYS_I2C_INIT_BOARD
extern VOID I2c_Init_Board(VOID);
#endif

/*
 * Probe the given I2C chip address.  Returns 0 if a chip responded,
 * not 0 on failure.
 */
EFI_STATUS I2c_Probe(CHAR8);

/*
 * Read/Write INTNerface:
 *   chip:    I2C chip address, range 0..127
 *   addr:    Memory (register) address within the chip
 *   alen:    Number of bytes to use for addr (typically 1, 2 for larger
 *              memories, 0 for register type devices with only one
 *              register)
 *   buffer:  Where to read/write the data
 *   len:     How many bytes to read/write
 *
 *   Returns: 0 on success, not 0 on failure
 */
EFI_STATUS I2c_Read(CHAR8 , UINT32 , INTN , UINT8 *, INTN );
EFI_STATUS I2c_Write(CHAR8 , UINT32 , INTN , UINT8 *, INTN );

/*
 * Functions for setting the current I2C bus and its speed
 */

/*
 * i2c_set_bus_num:
 *
 *  Change the active I2C bus.  Subsequent read/write calls will
 *  go to this one.
 *
 *  bus - bus index, zero based
 *
 *  Returns: 0 on success, not 0 on failure
 *
 */
EFI_STATUS I2c_Set_Bus_Num(UINTN);

/*
 * i2c_get_bus_num:
 *
 *  Returns index of currently active I2C bus.  Zero-based.
 */

UINTN I2c_Get_Bus_Num(VOID);

/*
 * i2c_set_bus_speed:
 *
 *  Change the speed of the active I2C bus
 *
 *  speed - bus speed in Hz
 *
 *  Returns: 0 on success, not 0 on failure
 *
 */
EFI_STATUS I2c_Set_Bus_Speed(UINTN);

/*
 * i2c_get_bus_speed:
 *
 *  Returns speed of currently active I2C bus in Hz
 */

UINTN I2c_Get_Bus_Speed(VOID);

#endif  /* _I2C_H_ */
