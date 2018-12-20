#include "sysinc.h"
#include "module.h"
#include "common.h"
#include "log.h"
#include "version.h"
#include "solaris-scf.h"

static int zbx_module_scf_autodiscovery(AGENT_REQUEST *request, AGENT_RESULT *result);
static int zbx_module_scf_status(AGENT_REQUEST *request, AGENT_RESULT *result);

static ZBX_METRIC keys[] =
/*            KEY                    FLAG                   FUNCTION       TEST PARAMETERS */
{
    {"solaris.scf.autodiscovery", CF_HAVEPARAMS, zbx_module_scf_autodiscovery, NULL},
    {"solaris.scf.status",        CF_HAVEPARAMS, zbx_module_scf_status,        NULL},
    {NULL}
};

/******************************************************************************
*                                                                            *
* Function: zbx_module_api_version                                           *
*                                                                            *
* Purpose: returns version number of the module interface                    *
*                                                                            *
* Return value: ZBX_MODULE_API_VERSION - version of module.h module is       *
*               compiled with, in order to load module successfully Zabbix   *
*               MUST be compiled with the same version of this header file   *
*                                                                            *
******************************************************************************/
int zbx_module_api_version(void)	
{
    return ZBX_MODULE_API_VERSION;
}

/******************************************************************************
*                                                                            *
* Function: zbx_module_init                                                  *	
*                                                                            *	
* Purpose: the function is called on agent startup                           *	
*          It should be used to call any initialization routines             *	
*                                                                            *	
* Return value: ZBX_MODULE_OK - success                                      *	
*               ZBX_MODULE_FAIL - module initialization failed               *	
*                                                                            *	
* Comment: the module won't be loaded in case of ZBX_MODULE_FAIL             *
*                                                                            *	
******************************************************************************/
int zbx_module_init(void)
{
    srand(time(NULL));

    zabbix_log(LOG_LEVEL_INFORMATION, 
               "Module: %s - build with agent: %d.%d.%d; OS: %s; Release: %s; Hostname: %s (%s:%d)",
               MODULE_NAME, ZABBIX_VERSION_MAJOR, ZABBIX_VERSION_MINOR, ZABBIX_VERSION_PATCH, 
               "", "", "",
               __FILE__, __LINE__);

    return ZBX_MODULE_OK;
}

/******************************************************************************
*                                                                            *
* Function: zbx_module_uninit                                                *
*                                                                            *
* Purpose: the function is called on agent shutdown                          *
*          It should be used to cleanup used resources if there are any      *
*                                                                            *
* Return value: ZBX_MODULE_OK - success                                      *
*               ZBX_MODULE_FAIL - function failed                            *
*                                                                            *
******************************************************************************/
int zbx_module_uninit(void)
{
    return ZBX_MODULE_OK;
}

/******************************************************************************
*                                                                            *
* Function: zbx_module_item_list                                             *
*                                                                            *
* Purpose: returns list of item keys supported by the module                 *
*                                                                            *
* Return value: list of item keys                                            *
*                                                                            *
******************************************************************************/
ZBX_METRIC *zbx_module_item_list()
{
    return keys;
}

static int zbx_module_scf_autodiscovery(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    const char *__function_name = "zbx_module_scf_autodiscovery";
    char *data;

    data = scf_discovery();

    zabbix_log(LOG_LEVEL_TRACE,
               "Module: %s, function: %s - raw data: %s (%s:%d)",
               MODULE_NAME, __function_name, data, __FILE__, __LINE__);

    SET_STR_RESULT(result, zbx_strdup(NULL, data));
    zbx_free(data);
    return SYSINFO_RET_OK;
}

static int zbx_module_scf_status(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    const char *__function_name = "zbx_module_scf_status";
    int status;

    if (1 != request->nparam)
    {
        SET_MSG_RESULT(result, strdup("Invalid number of parameters"));

        zabbix_log(LOG_LEVEL_DEBUG, "Error in module: %s - invalid number of parameters (%s:%d)",
                   MODULE_NAME, __FILE__, __LINE__);

        return SYSINFO_RET_FAIL;
    }

    char *scf = get_rparam(request, 0);

    zabbix_log(LOG_LEVEL_TRACE,
               "Module: %s, function: %s - service: %s (%s:%d)",
               MODULE_NAME, __function_name, scf, __FILE__, __LINE__);

    status = scf_status_int(scf);

    zabbix_log(LOG_LEVEL_TRACE,
               "Module: %s, function: %s - service: %s, status: %d (%s:%d)",
               MODULE_NAME, __function_name, scf, status, __FILE__, __LINE__);

    SET_UI64_RESULT(result, status);
    return SYSINFO_RET_OK;
}