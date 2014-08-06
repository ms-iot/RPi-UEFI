/*******************************************************************
#
#  
#  Copyright (c) Huawei Technologies Co., Ltd. 2013. All rights reserved.
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#  
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#  
#**/


#ifndef __BRDCOMMON_H
#define __BRDCOMMON_H

#ifdef __cplusplus
    extern "C" {
#endif


#define HDF_FIRST_BOOTROM_FLAG                  0x0
#define HDF_SECOND_BOOTROM_FLAG                 0x1

#define DEFAULT_FIRST_BOOTROM_SPACE_SIZE        (0x200000)
#define DEFAULT_SECOND_BOOTROM_SPACE_SIZE       (0x700000)
#define DEFAULT_BSP_PARA_SPACE_SIZE             (0x300000)


#define DEFAULT_FIRST_BOOTROM_BINDFILE_SIZE     (0x200000)
#define DEFAULT_SECOND_BOOTROM_BINDFILE_SIZE    (0x200000)

#define DEFAULT_BOOTLINE_OFFSET_IN_PARA         (0x20000+0x2000)

#define FLASH_BASE_ADDR                         0xf0000000

#define FLASH_FIRST_HDF_ADDR                    (0)  
#define FLASH_FIRST_HDF_SIZE                    (0x20000)         
#define FLASH_FIRST_HDF_RSV_SIZE                (0x60000)            

#define FLASH_SECOND_HDF_ADDR                   (FLASH_FIRST_HDF_ADDR + FLASH_FIRST_HDF_SIZE + FLASH_FIRST_HDF_RSV_SIZE)  
#define FLASH_SECOND_HDF_SIZE                   (FLASH_FIRST_HDF_SIZE)      
#define FLASH_SECOND_HDF_RSV_SIZE               (FLASH_FIRST_HDF_RSV_SIZE)  

#define FIRST_BOOTROM_ADRS                      (0x100000)//(FLASH_SECOND_HDF_ADDR + FLASH_SECOND_HDF_SIZE + FLASH_SECOND_HDF_RSV_SIZE) 

#define FIRST_BOOTROM_SIZE                      0x200000

#define FLASH_PROTECT_BLOCK0                    (0x0)
#define FLASH_PROTECT_BLOCK8                    (0x8)
#define FLASH_PROTECT_BLOCK9                    (0x9)
#define FLASH_PROTECT_BLOCK10                   (0xa)
#define FLASH_PROTECT_BLOCK11                   (0xb)

#define RESERVE_AFTER_FIRST_BOOTROM_SIZE        (0x200000)
#define DDR_DIAGNOSE_START_ADRS                 ((FIRST_BOOTROM_ADRS) + (FIRST_BOOTROM_SIZE) + RESERVE_AFTER_FIRST_BOOTROM_SIZE)
#define DDR_DIAGNOSE_LENGTH_ADRS                   (DDR_DIAGNOSE_START_ADRS + (0x4))

#define SECOND_BOOTROM_ADRS                     ((FIRST_BOOTROM_ADRS) + (FIRST_BOOTROM_SIZE))  
#define SECOND_BOOTROM_SIZE                     0x700000   //size of L2 BIOS
#define BOARD_WORK_INFO_ADRS                    ((SECOND_BOOTROM_ADRS) + (SECOND_BOOTROM_SIZE)) 
#define BOARD_WORK_INFO_SIZE                    (0x20000)        /* 128K byte*/

#define BOARD_HARD_INFO_ADRS                    ((BOARD_WORK_INFO_ADRS)+(BOARD_WORK_INFO_SIZE))
#define BOARD_HARD_INFO_SIZE                    (0x20000)        /* 128K byte*/

#define BOARD_AGING_INFO_ADRS                   ((BOARD_HARD_INFO_ADRS)+(BOARD_HARD_INFO_SIZE))  
#define BOARD_AGING_INFO_SIZE                   (0x18000)        /*   96K byte    */

#define BOARD_AGING_LOG_ADRS                    ((BOARD_AGING_INFO_ADRS)+(BOARD_AGING_INFO_SIZE))   
#define BOARD_AGING_LOG_SIZE                    (0x8000)        /*   32K byte    */
#define BOARD_AGING_CHIP_LOG_SIZE               (0x800) 

#define APPLICATION_INFO_ADRS                   ((BOARD_AGING_LOG_ADRS)+(BOARD_AGING_LOG_SIZE))  
#define APPLICATION_INFO_SIZE                   (0x60000)          /* 128*3K byte    */

#define FLASH_BLOCK_RSV_ADDRS                   (APPLICATION_INFO_ADRS + APPLICATION_INFO_SIZE)
#define FLASH_BLOCK_RSV_SIZE                    (0xc0000)          /*128*6K byte*/

#define BOARD_DRV_MEND_INFO_ADDRS               (FLASH_BLOCK_RSV_ADDRS + FLASH_BLOCK_RSV_SIZE)
#define BOARD_DRV_MEND_INFO_SIZE                (0x80000)      /*128*4K byte*/

#define SECOND_BOOTROM_VALID_FLAG_ADDR          (BOARD_WORK_INFO_ADRS + 0)  
#define SECOND_BOOTROM_VALID_FLAG_SIZE          (0x04)
#define SECOND_BOOTROM_VALID_FLAG_VALUE         (0x5A5A5A5A)           

#define FLASH_BSP_PARA_START                    ((BOARD_WORK_INFO_ADRS) + 0x2000)  //a00000+0xe0000 
#define FLASH_BSP_PARA_SIZE                     (0x2000)

#define FAST_STARTUP_VALID_FLAG_ADDR            (FLASH_BSP_PARA_START + FLASH_BSP_PARA_SIZE)
#define FAST_STARTUP_VALID_FLAG_SIZE            (0x04)
#define FAST_STARTUP_VALID_FLAG_VALUE           (0x5A5A5A5A)            
#define FAST_STARTUP_FILE_START_BLOCK_ADDR      (FAST_STARTUP_VALID_FLAG_ADDR + FAST_STARTUP_VALID_FLAG_SIZE)
#define FAST_STARTUP_FILE_START_BLOCK_SIZE      (0x04)
#define FAST_STARTUP_FILE_LENGTH_ADDR           (FAST_STARTUP_FILE_START_BLOCK_ADDR + FAST_STARTUP_FILE_START_BLOCK_SIZE)
#define FAST_STARTUP_FILE_LENGTH_SIZE           (0x04)

#define FLASH_UET_PARA_START                    (BOARD_HARD_INFO_ADRS)      /*BOARD_HARD_INFO_ADRS*/

#define FLASH_UET_PARA_SIZE                     0x2000   

#define SIZE_4KB                                0x00001000
#define SIZE_2KB                                0x00000800
#define FLASH_TELNET_USER                       (FLASH_UET_PARA_START + FLASH_UET_PARA_SIZE -SIZE_4KB)
#define FLASH_TELNET_USER_SIZE                  SIZE_2KB
#define FLASH_TELNET_USER_SET_FLAG              (FLASH_TELNET_USER +FLASH_TELNET_USER_SIZE)
#define FLASH_TELNET_USER_SIZE                  SIZE_2KB
#define FLASH_TELNET_FLAG                       0x5a5aa6a6

#define FLASH_CLOCK_PARA_START                  (APPLICATION_INFO_ADRS + 0x0)
#define FLASH_CLOCK_PARA_SIZE                   0x1000

#define FLASH_NET_PARA_START                    (APPLICATION_INFO_ADRS + 0x20000)
#define FLASH_NET_PARA_SIZE                     0x1000

#define FLASH_BSPLOG_PARA_START                 (FLASH_NET_PARA_START + 0x20000)
#define FLASH_BSPLOG_PARA_SIZE                  0x1000

#define FLASH_UPPER_PARA_START                  (BOARD_DRV_MEND_INFO_ADDRS + BOARD_DRV_MEND_INFO_SIZE)
#define FLASH_UPPER_PARA_SIZE                   0x200000

#define SECOND_BTRM_TEXT_START                  (FIRST_BOOTROM_ADRS + FIRST_BOOTROM_SIZE)

#define STA_SRAM_MEM_BASE                       0xe0000000//HDFINF_CpuBaseAddrAutoMatch(4)    /*4=SRAM*/ /* 0x2ff00000 */
#define STA_SRAM_MEM_SIZE                       (0x40000)     /* 256K */

#define CPU_RAM_USED_TOTAL_SIZE                 (0x200)                  
#define CPU_RAM_USED_START_ADRS                 (STA_SRAM_MEM_BASE)                       

#define CPU_RAM_START_TYPE_ADRS                 (CPU_RAM_USED_START_ADRS)  /*addr : 0x2ff00000*/
#define CPU_RAM_START_TYPE_SIZE                 (0x04)
#define BOOTROM_LEVEL1_START_VALUE              (1)                   
#define BOOTROM_LEVEL2_START_VALUE              (2)                  
#define SAFE_VERSION_START_VALUE                (0)                   
#define FAST_VERSION_START_VALUE                (3)                    

#define CPU_RAM_RESET_FLAG_ADRS                 (CPU_RAM_START_TYPE_ADRS + CPU_RAM_START_TYPE_SIZE)/*addr : 0x2ff00004*/
#define CPU_RAM_RESET_FLAG_SIZE                 (0x04)
#define CPU_RAM_RESET_FLAG_VALUE                (0x5A5A5A5A)
#define CPU_PWR_RESET_FLAG_VALUE                (0x4B4B)

#define CPU_RAM_LOAD_IMAGE_ADRS                 (CPU_RAM_RESET_FLAG_ADRS + CPU_RAM_RESET_FLAG_SIZE) /*addr : 0x2ff00008*/
#define CPU_RAM_LOAD_IMAGE_SIZE                 (0x04)

#define CPU_RAM_EXAM_RESULT_ADRS                (CPU_RAM_LOAD_IMAGE_ADRS + CPU_RAM_LOAD_IMAGE_SIZE)/*addr : 0x2ff0000c*/
#define CPU_RAM_EXAM_RESULT_SIZE                (40)                   

#define CPU_RAM_SEC_BTRM_FAIL_FLAG_ADRS         (CPU_RAM_EXAM_RESULT_ADRS + CPU_RAM_EXAM_RESULT_SIZE)
#define CPU_RAM_SEC_BTRM_FAIL_FLAG_SIZE         (0x04)                
#define CPU_RAM_SEC_BTRM_FAIL_FLAG_VALUE        (0x5A5A5A5A)        
#define CPU_RAM_SEC_BTRM_FIRST_RUN_VALUE        (0xb0aec7e9)        

#define CPU_RAM_SEC_BTRM_FAIL_COUNTER_ADRS      ((CPU_RAM_SEC_BTRM_FAIL_FLAG_ADRS)+(CPU_RAM_SEC_BTRM_FAIL_FLAG_SIZE))
#define CPU_RAM_SEC_BTRM_FAIL_COUNTER_SIZE      (0x04)    

#define CPU_RAM_AGING_INFO_ADRS            ((CPU_RAM_SEC_BTRM_FAIL_COUNTER_ADRS)+(CPU_RAM_SEC_BTRM_FAIL_COUNTER_SIZE))
#define CPU_RAM_AGING_INFO_SIZE            (0x48)            

#define CPU_AGING_STAT_ADRS                ((CPU_RAM_AGING_INFO_ADRS)+(CPU_RAM_AGING_INFO_SIZE))/*addr : 0x2ff00084*/
#define CPU_AGING_STAT_SIZE                (0x4)
#define CPU_AGING_STAT_VAL                 (0x5a5a5a5a)
#define CPU_AGING_STAT_NO_VAL              (0x00000000)

#define CPU_HDF_VER_SELECT_ADRS            ((CPU_AGING_STAT_ADRS)+(CPU_AGING_STAT_SIZE))/*addr : 0x2ff00088*/
#define CPU_HDF_VER_SELECT_SIZE            (0x4)

#define CPU_RAM_DEC_WDT_TIME_ADDR          ((CPU_HDF_VER_SELECT_ADRS) + CPU_HDF_VER_SELECT_SIZE)/*addr : 0x2ff0008c*/
#define CPU_RAM_DEC_WDT_TIME_SIZE          (0x4)

#define CPU_RAM_UART_ADDR                  (CPU_RAM_DEC_WDT_TIME_ADDR + CPU_RAM_DEC_WDT_TIME_SIZE)/*addr : 0x2ff00090*/
#define CPU_RAM_UART_SIZE                  (0x4)

#define CPU_MBIST_AGING_INFO_ADRS          (CPU_RAM_UART_ADDR + CPU_RAM_UART_SIZE) /*addr : 0xaff00094*/
#define CPU_MBIST_AGING_INFO_SIZE          (64)
#define MEM_MANAGE_ADDR   				   (CPU_RAM_UART_ADDR + CPU_RAM_UART_SIZE)/*addr : 0xaff00094*/
#define MEM_MANAGE_SIZE 				   (4*8)

#define CPU_RAM_TEST_FAIL_COUNT_ADDR (MEM_MANAGE_ADDR+MEM_MANAGE_SIZE)/*0x2ff000b4*/
#define CPU_RAM_TEST_FAIL_COUNT_SIZE (4)

#define FAST_STARTUP_PROCESS_FLAG_ADDR      (CPU_RAM_TEST_FAIL_COUNT_ADDR + CPU_RAM_TEST_FAIL_COUNT_SIZE)/*0x2ff000b8*/
#define FAST_STARTUP_PROCESS_FLAG_SIZE      (0x4)
#define FAST_STARTUP_SUCCESS_FLAG       (0x5a5a5a5a)
#define FAST_STARTUP_FAIL_FLAG          (0x4b4b4b4b)

#define CPU_RAM_HDF_CURRENT_VERSION_ADDR        (FAST_STARTUP_PROCESS_FLAG_ADDR + FAST_STARTUP_PROCESS_FLAG_SIZE) /*0x2ff000bc*/
#define CPU_RAM_HDF_CURRENT_VERSION_SIZE        (4)
#define CPU_RAM_HDF_BAK_VERSION_MAGIC_FLAG      (0xb5a4b5a4)

#define CPU_RAM_HDF_RESOLVE_FAIL_COUNT_ADDR     (CPU_RAM_HDF_CURRENT_VERSION_ADDR + CPU_RAM_HDF_CURRENT_VERSION_SIZE) /*0x2ff000c0*/
#define CPU_RAM_HDF_RESOLVE_FAIL_COUNT_SIZE     (4)





#define MCLOAD_INFO_ADDR  0xaff000c4    /*addr : 0xaff000c4*/ 
#define MClOAD_INFO_SIZE (12*8) 


#define CONTROL_SLAVE_STATUS_INFO 0xaff00124   /*addr : 0xaff00124*/ 
#define CONTROL_SLAVE_STATUS_INFO_SIZE (4*8)

#define CPU_RAM_WFI_STATUS_ADDR                 (CONTROL_SLAVE_STATUS_INFO + CONTROL_SLAVE_STATUS_INFO_SIZE)/*addr : 0xaff00144*/ 
#define CPU_RAM_WFI_STATUS_SIZE                 (4*8)

#define CPU_RAM_CONTROL_SLAVE_HART_BEAT_ADDR    (CPU_RAM_WFI_STATUS_ADDR + CPU_RAM_WFI_STATUS_SIZE) /*addr : 0xaff00164*/ 
#define CPU_RAM_CONTROL_SLAVE_HART_BEAT_SIZE    (4*8)

#define CPU_RAM_SLAVE_CORE_TYPE_ADDR            (CPU_RAM_CONTROL_SLAVE_HART_BEAT_ADDR + CPU_RAM_CONTROL_SLAVE_HART_BEAT_SIZE)/*addr : 0xaff00184*/ 
#define CPU_RAM_SLAVE_CORE_TYPE_SIZE            (4)

#define CPU_RAM_CLUSTER0_SCU_EN_FLAG_ADDR       (CPU_RAM_SLAVE_CORE_TYPE_ADDR + CPU_RAM_SLAVE_CORE_TYPE_SIZE)/*0xaff00188*/
#define CPU_RAM_CLUSTER0_SCU_EN_FLAG_SIZE       (4)
#define CPU_RAM_CLUSTER1_SCU_EN_FLAG_ADDR       (CPU_RAM_CLUSTER0_SCU_EN_FLAG_ADDR + CPU_RAM_CLUSTER0_SCU_EN_FLAG_SIZE)/*0xaff0018c*/
#define CPU_RAM_CLUSTER1_SCU_EN_FLAG_SIZE       (4)

#define CPU_RAM_SCU_EN_FLAG                     (0xaaaaaaaa)
#define CPU_RAM_SCU_UNEN_FLAG                   (0xbbbbbbbb)

#define CPU_RAM_SLAVE_CORE_RUN_COUNT_ADDR       (CPU_RAM_CLUSTER1_SCU_EN_FLAG_ADDR+CPU_RAM_CLUSTER1_SCU_EN_FLAG_SIZE)/*0xaff00190*/
#define CPU_RAM_SLAVE_CORE_RUN_COUNT_SIZE       (4)

#define CPU_RAM_CPU1_RST_SRC_ADDR               (CPU_RAM_SLAVE_CORE_RUN_COUNT_ADDR+CPU_RAM_SLAVE_CORE_RUN_COUNT_SIZE)/*0xaff00194*/
#define CPU_RAM_CPU1_RST_SRC_SIZE               (4)

#define CPU_RAM_SAVE_HIMEM_FLAG                 ((CPU_RAM_CPU1_RST_SRC_ADDR)+(CPU_RAM_CPU1_RST_SRC_SIZE))  /*0xaff00198*/
#define CPU_RAM_SAVE_HIMEM_FLAG_SIZE            (4)            

#define CPU_RAM_DDR_WRITE_LEVELING_FLAG         ((CPU_RAM_SAVE_HIMEM_FLAG) + (CPU_RAM_SAVE_HIMEM_FLAG_SIZE)) /*0xaff0019c*/
#define CPU_RAM_DDR_WRITE_LEVELING_SIZE         4

#define CPU_RAM_IPI_BASE_ADDR                   (CPU_RAM_DDR_WRITE_LEVELING_FLAG + CPU_RAM_DDR_WRITE_LEVELING_SIZE) /* 0xAFF001A0 */
#define CPU_RAM_IPI_SIZE                        (4* 8 * 8)

#define CPU_RAM_STACK_ADRS                      (STA_SRAM_MEM_BASE + STA_SRAM_MEM_SIZE-0x100)

#define FLASH_CPU_CHIP_INDEX                    0  
#define FLASH_MAX_CHIP_INDEX                    FLASH_CPU_CHIP_INDEX 



/******************************************************************************
Memory configuration 
*******************************************************************************/ 
#define HDF_COPY_TO_DRAM_ADRS                   (0x900000)  

/*** RAM Information ***/
#define BSP_LOG_SIZE                            (0x00080000)   

#define BSP_REPORT_MAX_SIZE                     (0x00010000)

#define BSP_REALTIME_REPORT_ADDR                (0x00020000) 
#define BSP_LASTWORD_REPORT_ADDR                (0x00040000)

#define BSP_FILESYS_RESERVED_ADDR               (0x00030000)

#define TASK_SWITCH_TRACE_BASEADDR              (0x00050000+0x10)/*Addr=0x50000*/


#define BSP_WARM_RESET_TABLE_ADRS               (IMAGE_LOW_ADRS - 0x200)
#define BSP_WARM_RESET_TABLE_SIZE               0X04
#define BSP_WARM_RESET_TABLE_VALUE              0x3C5AA5C3  

#define BSP_SOFT_RESET_TABLE_ADRS               (BSP_WARM_RESET_TABLE_ADRS + BSP_WARM_RESET_TABLE_SIZE)
#define BSP_SOFT_RESET_TABLE_SIZE               0x04
#define BSP_SOFT_RESET_TABLE_VALUE0             0xa5a5a5a5 
#define BSP_SOFT_RESET_TABLE_VALUE1             0x4b4b4b4b
#define BSP_SOFT_RESET_TABLE_VALUE2             0         

#define BSP_1588_RESERVED_BEGIN                 (0x5ff800)
#define BSP_1588_RESERVED_SIZE                  (2048)
#define BSP_1588_RESERVED_END                   (0x600000)

#define BSP_VECTOR_SAVE_BASEADDR                (0)
#define BSP_VECTOR_SAVE_SIZE                    (0)
#define BSP_MEM_RECORD_BASEADDR                 (0x600000)
#define BSP_MEM_RECORD_MAX_LEN                  (0x300000)
#define BSP_MEM_RECORD_BAK_BASEADDR             (0)
#define BSP_MEM_RECORD_BAK_MAX_LEN              (0)
#define DEDICATED_TASKTCB_INFO_BASEADDR         (0)
#define DEDICATED_TASKTCB_INFO_MAX_LEN          (0)
#define ISR_STACK_INFO_BASEADDR                 (0)
#define ISR_STACK_INFO_MAX_LEN                  (0)
#define BOARD_REALTIME_RECORD_BASEADDR          (0)
#define BOARD_REALTIME_RECORD_MAX_LEN           (0)

#define HDF_RAM_MAPAREA_ADDR                    (0x900000)
#define HDF_RAM_MAPAREA_SIZE                    (0x20000)    /* 128K */

#define FIQ_TASK_INFO_ADDR                      (0x920000)                      
#define FIQ_STACK_ADDR                          (FIQ_TASK_INFO_ADDR + 0x4000) 
#define BOARD_NAME   "MPTXb"
#define SYS_CLK_FREQ                            (13000000)

#define PENDING                                 (0x0)       
#define RST_HANDLE                              (0x1)     
#define SYS_INIT                                (0x2)       
#define USR_INIT                                (0x3)       
#define USR_ROOT                                (0x4)      
#define RUNNING                                 (0x5)    
#define INIT_START                              (0x1)
#define RUN_NORMAL                              (0x2)
#define INIT_FAIL                               (0x3)
#define RUN_ABNORMAL                            (0x4)
#define RUN_LOOP                                (0x5)
#define STATUS_NULL                             (0x0)

#define FE_ELE_NET_ID                           0                        
#define FE_DDI_NET_ID                           1                     
#define CBUS_NET_ID                             2                     
#define BACK_NET_ID                             3
#define MAX_NET_ID                              4    

#define GE_IPADDR_ID                            0                 
#define TARGET_IPADDR_ID                        1                     
#define HOST_IPADDR_ID                          2                       

#define PORT_TYPE_DEBUG                         0
#define PORT_TYPE_CAN                           1
#define PORT_TYPE_TRAFFIC                       2 
#define PORT_TYPE_BACK                          3
#define PORT_TYPE_MAX_NUM                       3

#define PORT_DEBUG_ID                           0
#define PORT_CAN_ID                             0
#define PORT_TRAFFIC_ID_0                       0
#define PORT_TRAFFIC_ID_1                       1
#define PORT_CAN_DEBUG_ID                       0

#define SC_SYSSTAT15                            (HDFINF_CpuBaseAddrAutoMatch(CPU_SYSCTRL) + 0x444)
#define SC_MSCPU_BIT                            (20)
#define SC_MSCPU_MASK                           (0x1)
#define PORT_INTERLINK_ID                       0
#define BSP_SLAVE_CPU_START_FLAG_ADDR           0x91b00000
#define BSP_SLAVE_CPU_START_FLAG                0x5A6A7A8A
#define BSP_MS_CPU_SHARE_ADDR                   0x91b00004
#define BSP_CPU1_FILELOAD_MEM_ADDR              (0x92A00000)
#define BSP_CPU1_FILELOAD_MEM_LEN               (0x2400000)
#define BSP_MAX_FILE_LENS_FOR_ONE_FILE          (BSP_CPU1_FILELOAD_MEM_ADDR - BSP_MS_CPU_SHARE_ADDR)

#define BSP_CPU1_FILELOAD_OK_FLAG               0x5A576767
#define  HDF_DDR_Addr (0x900000)
#define L1_CACHE_MBIST_End 0xA5A5A5A5
#define L1_CACHE_MBIST_FLAG 0x12345678
#define L1_CACHE_MBIST_FLAG_B 0x87654321
#define MBIST_CTRL_ADDR     0x2FF3FCC0
#define MBIST_STRL_ADDR     0x2FF3FD00
#define SRAM_HDF_WDT_FLAG1 0x2ff3fc00
#define SRAM_HDF_WDT_FLAG2 0x2ff3fc04
#define SRAM_HDF_WDT_FLAG3 0x2ff3fc08
#ifdef __cplusplus
}
#endif
#endif  /* __BRDCOMMON_H */

