/**
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

#ifndef _COMMON_H_
#define _COMMON_H_

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/PciIo.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Acpi.h>
#include <Library/ArmLib.h>

#define bool BOOLEAN
#define u8 UINT8
#define u16 UINT16
#define u32 UINT32
#define u64 UINT64

#define __u8  UINT8
#define __u16 UINT16
#define __u32 UINT32
#define __u64 UINT64
#define __bitwise

#define uint8_t  UINT8
#define uint16_t UINT16
#define ushort   UINT16
#define uint32_t UINT32
#define uint64_t UINT64

typedef unsigned long size_t;
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long phys_addr_t;
typedef unsigned long physaddr_t;
typedef unsigned long userptr_t;

#define EPERM            1      /* Operation not permitted */
#define ENOENT           2      /* No such file or directory */
#define ESRCH            3      /* No such process */
#define EINTR            4      /* Interrupted system call */
#define EIO              5      /* I/O error */
#define ENXIO            6      /* No such device or address */
#define E2BIG            7      /* Argument list too long */
#define ENOEXEC          8      /* Exec format error */
#define EBADF            9      /* Bad file number */
#define ECHILD          10      /* No child processes */
#define EAGAIN          11      /* Try again */
#define ENOMEM          12      /* Out of memory */
#define EACCES          13      /* Permission denied */
#define EFAULT          14      /* Bad address */
#define ENOTBLK         15      /* Block device required */
#define EBUSY           16      /* Device or resource busy */
#define EEXIST          17      /* File exists */
#define EXDEV           18      /* Cross-device link */
#define ENODEV          19      /* No such device */
#define ENOTDIR         20      /* Not a directory */
#define EISDIR          21      /* Is a directory */
#define EINVAL          22      /* Invalid argument */
#define ENFILE          23      /* File table overflow */
#define EMFILE          24      /* Too many open files */
#define ENOTTY          25      /* Not a typewriter */
#define ETXTBSY         26      /* Text file busy */
#define EFBIG           27      /* File too large */
#define ENOSPC          28      /* No space left on device */
#define ESPIPE          29      /* Illegal seek */
#define EROFS           30      /* Read-only file system */
#define EMLINK          31      /* Too many links */
#define EPIPE           32      /* Broken pipe */
#define EDOM            33      /* Math argument out of domain of func */
#define ERANGE          34      /* Math result not representable */
#define ENOSYS          38      /* Function not implemented */
#define ENONET          64      /* Machine is not on the network */
#define EOPNOTSUPP      95      /* Operation not supported on transport endpoint */
#define ENETUNREACH 101
#define ENOBUFS   105
#define ENOTSUPP 1
#define true  1
#define false 0

static inline const char *strerror(u8 status)
{
    switch (status) {
    case 0x0:       return "OK";
    case 0x1:       return "internal error";
    case 0x2:       return "bad operation";
    case 0x3:       return "bad parameter";
    case 0x4:       return "bad system state";
    case 0x5:       return "bad resource";
    case 0x6:       return "resource busy";
    case 0x8:       return "limits exceeded";
    case 0x9:       return "bad resource state";
    case 0xa:       return "bad index";
    case 0xf:       return "no resources";
    case 0x50:      return "bad input length";
    case 0x51:      return "bad output length";
    case 0x10:      return "bad QP state";
    case 0x30:      return "bad packet (discarded)";
    case 0x40:      return "bad size too many outstanding CQEs";
    case 0xff:      return "Command Timed Out";
    default:        return "unknown status";
  }
}

//#define MELLANOX_DBG

#ifdef MELLANOX_DBG
#define DBG(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define DBG(arg...)
#endif

#define ERROR(arg...) DEBUG ((EFI_D_ERROR,## arg))

#ifdef MELLANOX_DBG
#define DBGC(ptr, format, arg...) DEBUG((EFI_D_ERROR, format, ##arg));
#define DBGC2(ptr, format, arg...) DEBUG((EFI_D_ERROR, format, ##arg));
#else
#define DBGC(ptr, format, arg...)
#define DBGC2(ptr, format, arg...)
#endif

#define DBGCP(ptr, format, ...)
#define DBGC_HDA(ptr, a, b, c)
#define DBGC2_HDA(ptr, a, b, c)
#define DBGCP_HDA(ptr, a, b, c)

#define __swab16(x) \
        ((__u16)( \
                (((__u16)(x) & (__u16)0x00ffU) << 8) | \
                (((__u16)(x) & (__u16)0xff00U) >> 8) ))
#define __swab32(x) \
        ((__u32)( \
                (((__u32)(x) & (__u32)0x000000ffUL) << 24) | \
                (((__u32)(x) & (__u32)0x0000ff00UL) <<  8) | \
                (((__u32)(x) & (__u32)0x00ff0000UL) >>  8) | \
                (((__u32)(x) & (__u32)0xff000000UL) >> 24) ))
#define __swab64(x) \
        ((__u64)( \
                (__u64)(((__u64)(x) & (__u64)0x00000000000000ffULL) << 56) | \
                (__u64)(((__u64)(x) & (__u64)0x000000000000ff00ULL) << 40) | \
                (__u64)(((__u64)(x) & (__u64)0x0000000000ff0000ULL) << 24) | \
                (__u64)(((__u64)(x) & (__u64)0x00000000ff000000ULL) <<  8) | \
                (__u64)(((__u64)(x) & (__u64)0x000000ff00000000ULL) >>  8) | \
                (__u64)(((__u64)(x) & (__u64)0x0000ff0000000000ULL) >> 24) | \
                (__u64)(((__u64)(x) & (__u64)0x00ff000000000000ULL) >> 40) | \
                (__u64)(((__u64)(x) & (__u64)0xff00000000000000ULL) >> 56) ))

#define __be16_to_cpu(x) ((__u16)(    \
  (((__u16)(x) & (__u16)0x00ff) << 8) | \
  (((__u16)(x) & (__u16)0xff00) >> 8) ))
#define cpu_to_be32(x) (__swab32((x)))
#define __cpu_to_be32(x) cpu_to_be32(x)
#define be32_to_cpu(x) (__swab32((x)))
#define __be32_to_cpu(x) be32_to_cpu(x)
#define __cpu_to_be16(x) (__swab16((x)))

/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
static inline int fls(int x)
{
        int r = 32;

        if (!x)
                return 0;
        if (!(x & 0xffff0000u)) {
                x <<= 16;
                r -= 16;
        }
        if (!(x & 0xff000000u)) {
                x <<= 8;
                r -= 8;
        }
        if (!(x & 0xf0000000u)) {
                x <<= 4;
                r -= 4;
        }
        if (!(x & 0xc0000000u)) {
                x <<= 2;
                r -= 2;
        }
        if (!(x & 0x80000000u)) {
                x <<= 1;
                r -= 1;
        }
        return r;
}

/*
 * Handle ntohl and suches. These have various compatibility
 * issues - like we want to give the prototype even though we
 * also have a macro for them in case some strange program
 * wants to take the address of the thing or something..
 *
 * Note that these used to return a "long" in libc5, even though
 * long is often 64-bit these days.. Thus the casts.
 *
 * They have to be macros in order to do the constant folding
 * correctly - if the argument passed into a inline function
 * it is no longer constant according to gcc..
 */

#undef ntohl
#undef ntohs
#undef htonl
#undef htons

/*
 * Do the prototypes. Somebody might want to take the
 * address or some such sick thing..
 */
#if defined(__KERNEL__) || (defined (__GLIBC__) && __GLIBC__ >= 2)
extern __u32      ntohl(__u32);
extern __u32      htonl(__u32);
#else
extern unsigned long int  ntohl(unsigned long int);
extern unsigned long int  htonl(unsigned long int);
#endif
extern unsigned short int ntohs(unsigned short int);
extern unsigned short int htons(unsigned short int);


#if defined(__GNUC__) && (__GNUC__ >= 2)

#define ___htonl(x) __cpu_to_be32(x)
#define ___htons(x) __cpu_to_be16(x)
#define ___ntohl(x) __be32_to_cpu(x)
#define ___ntohs(x) __be16_to_cpu(x)

#if defined(__KERNEL__) || (defined (__GLIBC__) && __GLIBC__ >= 2)
#define htonl(x) ___htonl(x)
#define ntohl(x) ___ntohl(x)
#else
#define htonl(x) ((unsigned long)___htonl(x))
#define ntohl(x) ((unsigned long)___ntohl(x))
#endif
#define htons(x) ___htons(x)
#define ntohs(x) ___ntohs(x)

#endif /* OPTIMIZE */

#define assert ASSERT

#define wmb()           ArmDataSyncronizationBarrier
#define barrier() ArmDataMemoryBarrier()

#define max(a,b)  (((a)>(b))?(a):(b))
#define strcmp          AsciiStrCmp

#define offsetof(TYPE, MEMBER) ((u64) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define virt_to_phys(x)         ((u64) (unsigned long) (x))
#define phys_to_virt(x)         ((void *) (unsigned long) (x))

#define virt_to_bus(v) (u64)(v)
#define bus_to_phys(a) (a)
#define user_to_phys(a,b) (a)

/** Declare a variable or data structure as unused. */
#define __unused __attribute__ (( unused ))
#define ENOTSUP         252     /* Function not implemented (POSIX.4 / HPUX)  - lxr */
#define ECANCELED 125 /* Operation Canceled */

#define UNULL 0
#define PERMANENT_PROCESS(...)
#define REQUIRE_OBJECT(...)


//#define TAG(format, ...)  DBG("\t<~>%s:%d "format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define TAG(format, ...)

#define __iomem
#define __always_inline
#define unlikely
#define zalloc(x)   AllocateZeroPool(x)
#define malloc(x)   AllocateZeroPool(x)
#define free(x)     FreePool(x)

#define malloc_dma(bytes, align)    AllocatePages(EFI_SIZE_TO_PAGES(bytes)) //BootservicePages
#define free_dma(buf, bytes)      FreePages(buf, EFI_SIZE_TO_PAGES(bytes))
#define umalloc(bytes)    AllocatePages(EFI_SIZE_TO_PAGES(bytes))
#define ufree(x)      FreePool((void *)(x))

#define writel(v, x)           *((volatile u32 *) (x)) = (v)
#define readl(x)               *((volatile u32 *) (x))

#define udelay(a) MicroSecondDelay(a)
#define mdelay(a) MicroSecondDelay((a) * 1000)
#define sleep(a) mdelay((a) * 1000)

#define memcpy CopyMem
#define memset(a,b,c) SetMem(a,c,b)
#define memcmp CompareMem

static inline uint32_t random(void)
{
  static uint32_t r;
  return (r++ << 12);
}

#endif /* _COMMON_H_ */
