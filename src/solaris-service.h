#define MODULE_NAME    "solaris-services.so"

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
LOG_LEVEL_EMPTY   0 (none)
LOG_LEVEL_CRIT    1 (critical)
LOG_LEVEL_ERR     2 (error)
LOG_LEVEL_WARNING 3 (warning)
LOG_LEVEL_DEBUG   4 (debug)
LOG_LEVEL_TRACE   5 (trace)
*/

char *scf_discovery();
int scf_status_int(const char *scf);