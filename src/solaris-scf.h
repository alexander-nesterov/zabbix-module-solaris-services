#define MODULE_NAME    "solaris-scf.so"

/*
#define SCF_STATE_STRING_UNINIT         ((const char *)"uninitialized")
#define SCF_STATE_STRING_MAINT          ((const char *)"maintenance")
#define SCF_STATE_STRING_OFFLINE        ((const char *)"offline")
#define SCF_STATE_STRING_DISABLED       ((const char *)"disabled")
#define SCF_STATE_STRING_ONLINE         ((const char *)"online")
#define SCF_STATE_STRING_DEGRADED       ((const char *)"degraded")

#define  SCF_STATE_UNINIT        0x00000001 = 1
#define  SCF_STATE_MAINT         0x00000002 = 2
#define  SCF_STATE_OFFLINE       0x00000004 = 4
#define  SCF_STATE_DISABLED      0x00000008 = 8
#define  SCF_STATE_ONLINE        0x00000010 = 16
#define  SCF_STATE_DEGRADED      0x00000020 = 32
*/

/*
ZS_ZONE_PROP_NAME
The name of the zone. The string will be up to length ZS_ZONENAME_MAX, including the null terminating character.
 
ZS_ZONE_PROP_ID
The zoneid of the zone.
 
ZS_ZONE_PROP_IPTYPE
The IP networking type of the zone. This property will have a value of ZS_IPTYPE_SHARED or ZS_IPTYPE_EXCLUSIVE.
 
ZS_ZONE_PROP_CPUTYPE
The CPU type of the zone. If the zone has a dedicated CPU resource configured, the CPU type will be ZS_CPUTYPE_DEDICATED.
Otherwise the CPU type will be ZS_CPUTYPE_SHARED.
 
ZS_ZONE_PROP_DEFAULT_SCHED
The default scheduling class of the zone.
 
ZS_ZONE_PROP_SCHEDULERS
A list of scheduling classes that are found running inside the zone. The value is a set of flags defined as ZS_SCHED_*.
If the ZS_SCHED_CONFLICT flag is included, this means the zone has processes in both FSS, as well as TS, IA, or FX, with priority less than 60.
The behavior of the FSS class is undefined in this scenario.
 
ZS_ZONE_PROP_CPU_SHARES
The quantity of CPU shares allocated to zone. If the zone has no processes running in the FSS scheduling class, the value will be ZS_LIMIT_NONE.
If the zone has processes running in FSS, the value will be between 0 and ZS_SHARES_UNLIMITED, inclusive.
 
ZS_ZONE_PROP_POOLNAME
The name of the resource pool to which the zone is bound. If resource pools are not enabled, the value will be pool_default.
 
ZS_ZONE_PROP_PSETNAME
The name of the pool pset to which the zone is bound. If resource pools are disabled, the value will be pset_default.
*/

/*
LOG_LEVEL_EMPTY   0 (none)
LOG_LEVEL_CRIT    1 (critical)
LOG_LEVEL_ERR     2 (error)
LOG_LEVEL_WARNING 3 (warning)
LOG_LEVEL_DEBUG   4 (debug)
LOG_LEVEL_TRACE   5 (trace)
*/

char *scf_discovery();
int scf_status_int(const char *scf);