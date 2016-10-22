#define P_NUMBER_PROCESSORS 1
#define P_NUMBER_IDLE_STATES 1
#define P_NUMBER_PERF_STATES 0
#define P_NUMBER_DEVICES 1
#define P_NUMBER_COORDINATED_STATS 1

typedef struct _PEP_PROCESSOR_IDLE_INFO_PLAT
{
    //
    // Processor idle states
    //
    PEP_PROCESSOR_IDLE_STATE_INFO IdleStates[P_NUMBER_IDLE_STATES];

} PEP_PROCESSOR_IDLE_INFO_PLAT, *PPEP_PROCESSOR_IDLE_INFO_PLAT;

typedef struct _PEP_PROCESSOR_INFO_PLAT
{
    WCHAR DevicePath[MAX_PROCESSOR_PATH_LENGTH]; // Null-terminated ACPI name
    ULONG FeedbackCounterCount;
    ULONG Flags;

    //
    // We are putting the idle/perf state count here (instead
    // of the PEP_PROCESSOR_xxx_INFO structure for the ease of parsing
    //
    ULONG NumberIdleStates;
    ULONG NumberPerfStates;

    PEP_PROCESSOR_IDLE_INFO_PLAT IdleInfo;
    PEP_PROCESSOR_PERF_INFO PerfInfo;

} PEP_PROCESSOR_INFO_PLAT, *PPEP_PROCESSOR_INFO_PLAT;

typedef struct _PEP_PROCESSOR_TABLE_PLAT
{
    ULONG Version;
    ULONG NumberProcessors;
    PEP_PROCESSOR_INFO_PLAT ProcessorInfo[P_NUMBER_PROCESSORS];
} PEP_PROCESSOR_TABLE_PLAT, *PPEP_PROCESSOR_TABLE_PLAT;

typedef struct _PEP_COORDINATED_STATE_TABLE_PLAT
{
    ULONG Version;
    ULONG CoordinatedStateCount;
    COORDINATED_STATE_INFO CoordinatedStates[P_NUMBER_COORDINATED_STATS];
} PEP_COORDINATED_STATE_TABLE_PLAT, *PPEP_COORDINATED_STATE_TABLE_PLAT;

typedef struct _PEP_DEVICE_INFO_PLAT
{
    WCHAR DevicePath[MAX_DEVICE_PATH_LENGTH]; // Null-terminated ACPI name
    ULONG DStateSupportMask;
    ULONG NumberComponents;

    COORDINATED_DSTATE_REQUIREMENT DStateRequirement[P_NUMBER_COORDINATED_STATS];
    COORDINATED_FSTATE_REQUIREMENT FStateRequirement[P_NUMBER_COORDINATED_STATS];
} PEP_DEVICE_INFO_PLAT, *PPEP_DEVICE_INFO_PLAT;

typedef struct _PEP_DEVICE_TABLE_PLAT
{
    ULONG Version;
    ULONG NumberDevices;
    PEP_DEVICE_INFO_PLAT DeviceInfo[P_NUMBER_DEVICES];
} PEP_DEVICE_TABLE_PLAT, *PPEP_DEVICE_TABLE_PLAT;

PEP_PROCESSOR_TABLE_PLAT RPI2Processors =
{
	1, //Version
	1, //NumberProcessors
	{ //ProcessorInfo
		{ //[0]
			L"\\_SB.CPU0", //DevicePath , wchar_t[16]
			0, //FeedbackCounterCount
			0x00000000, //Flags
			0, //NumberIdleStates
			0, //NumberPerfStates
			{ //IdleInfo
			},
			{ // perfinfo
			}
		}
	}
};

PEP_COORDINATED_STATE_TABLE_PLAT RPI2CoordinatedStates =
{
	1, //Version
	1, //CoordinatedStateCount
	{ //CordinatedStates[]
		{ //[0]
			{ // DependencyInfo
				{ //[0]
					1, //ExpectedState
					0, //TargetProcessor
					0x0 | 0x2 | 0x4, //LooseDependency = FALSE, InitialState = TRUE, DependentState = TRUE
				}
			},
			SOC_STATE_TYPE, //StateType
			0x1, //Flags
			0, //Latency
			0, //BreakEvenDuration
			1, //DependencyCount
			1, //MaximumDependencySize
		}
	}
};

PEP_DEVICE_TABLE_PLAT RPI2Devices =
{
	1, //Version
	1, //NumberDevices
	{ //DeviceInfo
		{ //[1]
			L"\\_SB.I2C0", //DevicePath , wchar_t[16]
			0x1 | (1 << 3), //DStateSupportMask (D0 and D3)
			1, //NumberCompoenents
			{ //DStateRequirement
				{ //[0]
					PowerDeviceD3 //DState
				}
			},
			{ // FStateRequirement
				{ //[0]
					{ //FState
						{ //[0]
							0
						}
					}
				}
			}
		}
	}
};
