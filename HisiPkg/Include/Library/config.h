/* config.h - Mistral OMAP35xx configuration header */

/*
 * Copyright (c) 2008-2009 Wind River Systems, Inc.
 * Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,25mar09,m_h  add support for copyback cache & RTP
01e,19mar09,m_h  Cache is writethrough not copyback
01d,19feb09,m_h  cleanup
01c,22jan09,m_h  OneNand Flash Support
01b,24nov08,m_h  Configure to add networking
01a,16jun08,m_h  created.
*/

/*
DESCRIPTION
This module contains the configuration parameters for the Mistral OMAP35xx BSP.
*/

#ifndef __INCconfigh
#define __INCconfigh

#ifdef __cplusplus
extern "C" {
#endif

/* BSP version/revision identification, before configAll.h */

#define BSP_VER_1_1     1       /* 1.2 is backwards compatible with 1.1 */
#define BSP_VER_1_2     1
#define BSP_VERSION     "2.0"
#define BSP_REV         "/0"   /* 0 for first revision */

//#include <configAll.h>
/*
 * vxbus support
 */
#ifdef _BSP_BUILD_VXWORKS
#define INCLUDE_VXBUS
#else
#undef INCLUDE_VXBUS
#endif
#ifdef INCLUDE_VXBUS
#define INCLUDE_HWMEM_ALLOC
#define INCLUDE_VXB_CMDLINE

#define HWMEM_POOL_SIZE 50000

#endif /* INCLUDE_VXBUS */

/*
 * SYS_MODEL define
 *
 */

#define SYS_MODEL "HISILICON - CortexA9 (ARM)"


/* Support network devices */
#define INCLUDE_NET_DAEMON
#undef INCLUDE_APPL_LOG_UTIL
#undef INCLUDE_END2_LINKBUFPOOL

#define DEFAULT_BOOT_LINE \
      "HiFE(0,0)OMC:vxWorks.bin h=192.168.0.200 e=192.168.0.100 u=aa pw=123"



#ifndef HDF_MASTER_CORE_FLAG
#define HDF_MASTER_CORE_FLAG    0
#define HDF_SLAVE_CORE_FLAG     1
#define HDF_BOOTROM_COMPILE_FLAG    0
#define HDF_VXWORKS_COMPILE_FLAG    1
#endif





/* Memory configuration */
#undef  LOCAL_MEM_AUTOSIZE                    /* run-time memory sizing */

#ifndef _BSP_BUILD_VXWORKS
#ifdef _CONTROL_SLAVE_CORE_IMG
#define USER_RESERVED_MEM       HDF_GetMemPoolResSizeConfig(HDF_SLAVE_CORE_FLAG,HDF_BOOTROM_COMPILE_FLAG)
#else
#define USER_RESERVED_MEM       HDF_GetMemPoolResSizeConfig(HDF_MASTER_CORE_FLAG,HDF_BOOTROM_COMPILE_FLAG)
#endif
#else
#ifdef _CONTROL_SLAVE_CORE_IMG
#define USER_RESERVED_MEM       HDF_GetMemPoolResSizeConfig(HDF_SLAVE_CORE_FLAG,HDF_VXWORKS_COMPILE_FLAG)
#else
#define USER_RESERVED_MEM       HDF_GetMemPoolResSizeConfig(HDF_MASTER_CORE_FLAG,HDF_VXWORKS_COMPILE_FLAG)
#endif
#endif

#define LOCAL_MEM_LOCAL_ADRS    (0x0)



#ifndef _BSP_BUILD_VXWORKS
#ifdef _CONTROL_SLAVE_CORE_IMG
#define LOCAL_MEM_SIZE          HDF_GetMemPoolPhyMemTopConfig(HDF_SLAVE_CORE_FLAG,HDF_BOOTROM_COMPILE_FLAG)
#else
#define LOCAL_MEM_SIZE          HDF_GetMemPoolPhyMemTopConfig(HDF_MASTER_CORE_FLAG,HDF_BOOTROM_COMPILE_FLAG)
#endif
#else
#ifdef _CONTROL_SLAVE_CORE_IMG
#define LOCAL_MEM_SIZE          HDF_GetMemPoolPhyMemTopConfig(HDF_SLAVE_CORE_FLAG,HDF_VXWORKS_COMPILE_FLAG)
#else
#define LOCAL_MEM_SIZE          HDF_GetMemPoolPhyMemTopConfig(HDF_MASTER_CORE_FLAG,HDF_VXWORKS_COMPILE_FLAG)
#endif

#endif
#define LOCAL_MEM_END_ADRS      (LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE)


/*
 * Boot ROM is an image written into Flash. Part of the Flash can be
 * reserved for boot parameters etc. (see the Flash section below).
 *
 * The following parameters are defined here and in the Makefile.
 * They must be kept synchronized; effectively config.h depends on Makefile.
 * Any changes made here must be made in the Makefile and vice versa.
 *
 * ROM_BASE_ADRS is the base of the Flash ROM/EPROM.
 * ROM_TEXT_ADRS is the entry point of the VxWorks image
 * ROM_SIZE is the size of the part of the Flash ROM/EPROM allocated to
 *      the VxWorks image (block size - size of headers)
 *
 * Two other constants are used:
 * ROM_COPY_SIZE is the size of the part of the ROM to be copied into RAM
 *       (e.g. in uncompressed boot ROM)
 * ROM_SIZE_TOTAL is the size of the entire Flash ROM (used in sysPhysMemDesc)
 *
 * The values are given as literals here to make it easier to ensure
 * that they are the same as those in the Makefile.
 */

#undef  RAM_LOW_ADRS
#undef  RAM_HIGH_ADRS

#define IMAGE_LOW_ADRS   0x00a00000

/* VxWorks entry link address */
#define VXWORKS_ENTRY    IMAGE_LOW_ADRS

#ifdef _CONTROL_SLAVE_CORE_IMG
#define RAM_LOW_ADRS     0x00200000  /* VxWorks image entry point */
#define RAM_HIGH_ADRS    0x03000000  /* RAM address for ROM boot */

#else

#ifndef _BSP_BUILD_VXWORKS
#define ROM_BASE_ADRS    (HDFINF_GetTextBase())
#define ROM_TEXT_ADRS    (HDFINF_GetTextBase())
#define RAM_LOW_ADRS     0x05000000  /* VxWorks image entry point */
#define RAM_HIGH_ADRS    0x06000000  /* RAM address for ROM boot */
#else
#define ROM_BASE_ADRS    0x40200000     /* base of Flash/EPROM */
#define ROM_TEXT_ADRS    0x40200000     /* code start addr in ROM */
#define RAM_LOW_ADRS     IMAGE_LOW_ADRS  /* VxWorks image entry point */
#define RAM_HIGH_ADRS    0x05000000  /* RAM address for ROM boot */
#endif

#endif

#undef  ROM_SIZE
#define ROM_SIZE          0x00200000     /* size of ROM holding VxWorks*/


/*
 * Flash/NVRAM memory configuration
 *
 * A block of the Flash memory (FLASH_SIZE bytes at FLASH_ADRS) is
 * reserved for non-volatile storage of data.
 *
 */

#undef INCLUDE_FLASH

/* Serial port configuration */

#define N_SIO_CHANNELS    3

#undef  NUM_TTY
#define NUM_TTY             N_SIO_CHANNELS

#define DEFAULT_BAUD        (HDF_GetUartBaudRate())

/* Console baud rate reconfiguration. */
#undef  CONSOLE_BAUD_RATE
#define CONSOLE_BAUD_RATE DEFAULT_BAUD     /* Reconfigure default baud rate */

/*
 * Define SERIAL_DEBUG to enable debugging
 * via the serial ports
 */

#undef SERIAL_DEBUG
#undef INCLUDE_BOOT_WDB

#undef INCLUDE_WDB



#if defined(INCLUDE_WDB) || defined (INCLUDE_BOOT_WDB)
#   undef WDB_COMM_TYPE
#   undef WDB_TTY_BAUD
#   undef WDB_TTY_CHANNEL
#   undef WDB_TTY_DEV_NAME
#   ifdef SERIAL_DEBUG
#       define WDB_NO_BAUD_AUTO_CONFIG
#       define WDB_COMM_TYPE       WDB_COMM_SERIAL /* WDB in Serial mode */
#       define WDB_TTY_BAUD        38400       /* Baud rate for WDB Connctn */
#       define WDB_TTY_CHANNEL     1            /* COM PORT #2 */
#       define WDB_TTY_DEV_NAME    "/tyCo/1"    /* deflt TYCODRV_5_2 dev name */
#   else /* SERIAL_DEBUG */
#       define WDB_COMM_TYPE       WDB_COMM_END
#       define WDB_TTY_BAUD        DEFAULT_BAUD /* Baud rate for WDB Connctn */
#       define WDB_TTY_CHANNEL     0            /* COM PORT #1 */
#       define WDB_TTY_DEV_NAME    "/tyCo/0"    /* deflt TYCODRV_5_2 dev name */
#   endif /* SERIAL_DEBUG */
#endif /* INCLUDE_WDB || INCLUDE_BOOT_WDB */


/*
 * We use the generic architecture libraries, with caches/MMUs present. A
 * call to sysHwInit0() is needed from within usrInit before
 * cacheLibInit() is called.
 */

/*
 * Cache/MMU configuration
 *
 * Note that when MMU is enabled, cache modes are controlled by
 * the MMU table entries in sysPhysMemDesc[], not the cache mode
 * macros defined here.
 */
#define SYS_CACHE_UNCACHED_ADRS  0xffffffff/*OMAP35XX_L4_MPU_INTC*/

#   undef  USER_I_CACHE_MODE
#   define USER_I_CACHE_MODE       CACHE_COPYBACK

#   undef  USER_D_CACHE_MODE
#   define USER_D_CACHE_MODE       CACHE_COPYBACK


/* Include MMU BASIC and CACHE support for command line and project builds */

#   define INCLUDE_MMU_BASIC
#   define INCLUDE_BOOT_MMU_BASIC
#   define INCLUDE_CACHE_SUPPORT

#if defined(INCLUDE_MMU_BASIC) || defined(INCLUDE_MMU_FULL)
#   define INCLUDE_MMU
#endif /* INCLUDE_MMU_BASIC || INCLUDE_MMU_FULL */

/* Include MMU BASIC and CACHE support for command line and project builds */

#   define INCLUDE_MMU_BASIC
#   define INCLUDE_BOOT_MMU_BASIC
#   define INCLUDE_CACHE_SUPPORT

#if defined(INCLUDE_MMU_BASIC) || defined(INCLUDE_MMU_FULL)
#   define INCLUDE_MMU
#endif /* INCLUDE_MMU_BASIC || INCLUDE_MMU_FULL */

#ifndef MEM_MMU_OFFSET
#define MEM_MMU_OFFSET   0x00
#endif

/*
 * Network driver configuration.
 *
 * De-select unused (default) network drivers selected in configAll.h.
 */

#undef  INCLUDE_ENP     /* include CMC Ethernet interface*/
#undef  INCLUDE_EX      /* include Excelan Ethernet interface */
#undef  INCLUDE_SM_NET      /* include backplane net interface */
#undef  INCLUDE_SM_SEQ_ADDR /* shared memory network auto address setup */

#define INCLUDE_IPCOM_USE_AUTH_RADIUS


/* Enhanced Network Driver (END) Support */

#define INCLUDE_END

#ifdef  INCLUDE_END
#   ifndef SERIAL_DEBUG
#       define WBD_AGENT_END
#   else
#       undef WBD_AGENT_END
#   endif /* SERIAL_DEBUG */

#endif  /* INCLUDE_END */

#ifdef _BSP_BUILD_VXWORKS
#ifndef _CONTROL_SLAVE_CORE_IMG
#if 1
#define INCLUDE_USB
#define INCLUDE_USB_INIT

/*ehci*/
#define INCLUDE_EHCI
#define INCLUDE_EHCI_INIT
#define INCLUDE_EHCI_BUS

/*ohci*/
#define INCLUDE_OHCI
#define INCLUDE_OHCI_INIT
#define INCLUDE_OHCI_BUS

/*MASS STORGY device*/
#define INCLUDE_USB_MS_BULKONLY
#define INCLUDE_USB_MS_BULKONLY_INIT
#define INCLUDE_USB_MS_CBI
#define INCLUDE_USB_MS_CBI_INIT
#define INCLUDE_NOR_FILESYS
#endif
#endif
#endif

#define INCLUDE_BSP_WATCHDOG

#ifdef _CONTROL_SLAVE_CORE_IMG
#undef  _INCLUDE_FILESYS
#else
#define  _INCLUDE_FILESYS
#endif

#undef INCLUDE_TFFS

#ifdef _CONTROL_SLAVE_CORE_IMG
#undef INCLUDE_DOSFS
#else
/*define for FS*/
#define INCLUDE_DOSFS
#endif

#define INCLUDE_XBD_RAMDRV /*ramDisk*/

#ifdef INCLUDE_DOSFS
#define INCLUDE_ERF
#define INCLUDE_DEVICE_MANAGER
#define INCLUDE_FS_EVENT_UTIL
#define INCLUDE_FS_MONITOR
#define INCLUDE_XBD
#define INCLUDE_XBD_BLK_DEV
#define INCLUDE_XBD_TRANS
#define INCLUDE_DOSFS_DIR_FIXED
#define INCLUDE_DOSFS_DIR_VFAT
#define INCLUDE_DOSFS_FAT
#define INCLUDE_DOSFS_FMT
#define INCLUDE_DOSFS_CHKDSK
#define INCLUDE_DOSFS_MAIN
#endif /* INCLUDE_DOSFS*/

/* I2C not supported */
#undef INCLUDE_I2C

/* touch screen not supported */
#undef INCLUDE_TOUCHSCREEN

/*
 * Interrupt mode.  Preemptive interrupts are not supported by the interrupt
 * driver so INT_MODE must be set to INT_NON_PREEMPT_MODEL.
 */

#define INT_MODE    INT_NON_PREEMPT_MODEL

/*
 * miscellaneous definitions
 * Note: ISR_STACK_SIZE is defined here rather than in ../all/configAll.h
 * (as is more usual) because the stack size depends on the interrupt
 * structure of the BSP.
 */

#define ISR_STACK_SIZE  0x2000  /* size of ISR stack, in bytes */

/* Optional timestamp support */

#undef  INCLUDE_TIMESTAMP   /* define to include timestamp driver */
#define INCLUDE_TIMESTAMP

#ifndef INCLUDE_LOADER
#define INCLUDE_LOADER
#endif
#ifndef INCLUDE_LOADER_HOOKS
#define INCLUDE_LOADER_HOOKS
#endif
#ifndef INCLUDE_PTYDRV
#define INCLUDE_PTYDRV          /* pseudo terminal driver */
#endif
/*script*/
#ifndef INCLUDE_STARTUP_SCRIPT
#define INCLUDE_STARTUP_SCRIPT
#endif


#define INCLUDE_SHELL_INTERP_C  /* C interpreter */
#define INCLUDE_SHELL_INTERP_CMD /* shell command interpreter */

#undef SHELL_COMPATIBLE
#define SHELL_COMPATIBLE        TRUE

#ifndef BSP_BUILD_BASIC_BTRM
#define INCLUDE_RAWFS
#define INCLUDE_XBD_RAMDRV
#endif
#ifndef _CONTROL_SLAVE_CORE_IMG
#ifdef _BSP_BUILD_VXWORKS
#define INCLUDE_SECURITY
#endif
#endif
#ifdef INCLUDE_SECURITY
#define LOGIN_USER_NAME      "target"
#endif

#include "BrdCommon.h"
//#include "configExtend.h"

#ifdef __cplusplus
}
#endif
#endif  /* __INCconfigh */
