//
//  RPi2 Platform PEP defines for power management section of ACPI table
//

#ifndef _RPI2PEP_H_INCLUDED_
#define _RPI2PEP_H_INCLUDED_

#include <IndustryStandard/Acpi50.h>

#define PEP_MAX_DEPENDENCIES_PER_STATE 16
#define MAX_PROCESSOR_PATH_LENGTH 16
#define MAX_DEVICE_PATH_LENGTH 32
#define MAX_COMPONENT_COUNT 8

#define P_NUMBER_PROCESSORS 1
#define P_NUMBER_IDLE_STATES 1
#define P_NUMBER_PERF_STATES 0
#define P_NUMBER_DEVICES 1
#define P_NUMBER_COORDINATED_STATS 1

#define P_BUILD_IDLE_STATE(i, c, t, s, w, p, a) ( \
    (a << 9) | (p << 8) | (w << 7) | (s << 3) | (t << 2) | (c << 1) | (i) )


// All processor related data
//

//
// We are crafting our own versions of the pepfx structures
// in order to better control alignment of table fields
//
typedef struct 
{
    UINT32 Ulong;
    UINT32 Latency;
    UINT32 BreakEvenDuration;

} PEP_PROCESSOR_IDLE_STATE_INFO;


typedef struct
{
// Processor idle states
    PEP_PROCESSOR_IDLE_STATE_INFO IdleStates[P_NUMBER_IDLE_STATES];

} PEP_PROCESSOR_IDLE_INFO_PLAT;


typedef struct 
{
    UINT32 ExpectedState;
    UINT32 TargetProcessor;
    UINT32 Ulong;
} COORDINATED_DEPENDENCY_INFO;

// Per coordinated-idle state information
//
typedef struct
{
    COORDINATED_DEPENDENCY_INFO DependencyInfo[PEP_MAX_DEPENDENCIES_PER_STATE];
    UINT32 StateType;
    UINT32 Ulong;
    UINT32 Latency;
    UINT32 BreakEvenDuration;
    UINT32 DependencyCount;
    UINT32 MaximumDependencySize;

} COORDINATED_STATE_INFO;

// Coordinated idle info
// Queried through PCIM
//
typedef struct
{
    UINT32 Version;
    UINT32 CoordinatedStateCount;
    COORDINATED_STATE_INFO CoordinatedStates[P_NUMBER_COORDINATED_STATS];
} PEP_COORDINATED_STATE_TABLE;

// All processor perf related data
//
typedef struct
{
// TODO: Add code here
    UINT32 Unused;
} PEP_PROCESSOR_PERF_INFO;

// Processor info
//

typedef struct 
{
    UINT16 DevicePath[MAX_PROCESSOR_PATH_LENGTH]; // Null-terminated ACPI name
    UINT32 FeedbackCounterCount;

// Bit 0: PerformanceStatesSupported
// Bit 1: ParkingSupported
// 2-31 : Reserved

   UINT32 Ulong;

// We are putting the idle/perf state count here (instead
// of the PEP_PROCESSOR_xxx_INFO structure for the ease of parsing

    UINT32 NumberIdleStates;
    UINT32 NumberPerfStates;

// Processor Data consists of the following (in the specified order):
// 1. Processor idle info (_PEP_PROCESSOR_IDLE_INFO structure)
// 2. Processor p-state info (_PEP_PROCESSOR_PERF_INFO structure)
// *N.B. The exact length of the structures is determined by the NumberIdleStates/NumberPerfStates
// variables

    UINT8  ProcessorData[1];
} PEP_PROCESSOR_INFO;

// Top level processor table
// *N.B. The exact length of the structure is determined by the NumberIdleStates/NumberPerfStates
//  variables
// Queried through PPTM under PEP
//
typedef struct
{
    UINT32 Version;
    UINT32 NumberProcessors;
    PEP_PROCESSOR_INFO ProcessorInfo[P_NUMBER_PROCESSORS];
} PEP_PROCESSOR_TABLE;

typedef struct
{
    UINT32 FState[MAX_COMPONENT_COUNT];
// TODO:Add clock requirement
} COORDINATED_FSTATE_REQUIREMENT;

typedef struct
{
    UINT32 DState;
// TODO: Add clock requirement here
} COORDINATED_DSTATE_REQUIREMENT;

// Top level device table
// *N.B. The exact length of the structure is determined by the NumberIdleStates/NumberPerfStates
//  variables
//

typedef struct
{
    UINT16 DevicePath[MAX_PROCESSOR_PATH_LENGTH]; // Null-terminated ACPI name
    UINT32 FeedbackCounterCount;
    UINT32 Flags;

    //
    // We are putting the idle/perf state count here (instead
    // of the PEP_PROCESSOR_xxx_INFO structure for the ease of parsing
    //
    UINT32 NumberIdleStates;
    UINT32 NumberPerfStates;

    PEP_PROCESSOR_IDLE_INFO_PLAT IdleInfo;
    PEP_PROCESSOR_PERF_INFO PerfInfo;

} PEP_PROCESSOR_INFO_PLAT;

typedef struct
{
    UINT32 Version;
    UINT32 NumberProcessors;
    PEP_PROCESSOR_INFO_PLAT ProcessorInfo[P_NUMBER_PROCESSORS];
} PEP_PROCESSOR_TABLE_PLAT;

typedef struct
{
    UINT32 Version;
    UINT32 CoordinatedStateCount;
    COORDINATED_STATE_INFO CoordinatedStates[P_NUMBER_COORDINATED_STATS];
} PEP_COORDINATED_STATE_TABLE_PLAT;

typedef struct
{
    UINT16 DevicePath[MAX_DEVICE_PATH_LENGTH]; // Null-terminated ACPI name
    UINT32 DStateSupportMask;
    UINT32 NumberComponents;

    COORDINATED_DSTATE_REQUIREMENT DStateRequirement[P_NUMBER_COORDINATED_STATS];
    COORDINATED_FSTATE_REQUIREMENT FStateRequirement[P_NUMBER_COORDINATED_STATS];
} PEP_DEVICE_INFO_PLAT;

typedef struct
{
    UINT32 Version;
    UINT32 NumberDevices;
    PEP_DEVICE_INFO_PLAT DeviceInfo[P_NUMBER_DEVICES];
} PEP_DEVICE_TABLE_PLAT;

#endif