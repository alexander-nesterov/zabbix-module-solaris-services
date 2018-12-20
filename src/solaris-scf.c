#include "common.h"
#include "log.h"
#include "zbxjson.h"
#include <errno.h>
#include <libscf.h>
#include "sys/systeminfo.h"
#include "solaris-scf.h"

char *scf_discovery(void)
{
    const char *__function_name = "scf_discovery";
    struct zbx_json json;
    int r;

    scf_handle_t *handle = scf_handle_create(SCF_VERSION);
    scf_scope_t *scope = scf_scope_create(handle);
    scf_service_t *svc = scf_service_create(handle);
    scf_instance_t *inst = scf_instance_create(handle);
    scf_iter_t *svc_iter = scf_iter_create(handle);
    scf_iter_t *inst_iter = scf_iter_create(handle);

    size_t sz = scf_limit(SCF_LIMIT_MAX_FMRI_LENGTH) + 1;
    char *fmri = malloc(sz + 1);

    if (handle == NULL || scope == NULL || svc == NULL ||
        inst == NULL || svc_iter == NULL || inst_iter == NULL || fmri == NULL)
    {
        zabbix_log(LOG_LEVEL_DEBUG,
                   "Module: %s, function: %s - handle is NULL (%s:%d)",
                   MODULE_NAME, __function_name, __FILE__, __LINE__);
    }

    if (scf_handle_bind(handle) == -1 ||
        scf_handle_get_scope(handle, SCF_SCOPE_LOCAL, scope) == -1 ||
        scf_iter_scope_services(svc_iter, scope) ==-1)
    {
        zabbix_log(LOG_LEVEL_DEBUG,
                   "Module: %s, function: %s - scf_handle_bind is FAILURE (%s:%d)",
                   MODULE_NAME, __function_name, __FILE__, __LINE__);
    }

    zbx_json_init(&json, ZBX_JSON_STAT_BUF_LEN);
    zbx_json_addarray(&json, ZBX_PROTO_TAG_DATA);

    while ((r = scf_iter_next_service(svc_iter, svc)) > 0)
    {
        if (scf_service_to_fmri(svc, fmri, sz) < 0)
        {
            //failure
        }

        if (scf_iter_service_instances(inst_iter, svc) < 0)
        {
            //failure
        }

        while ((r = scf_iter_next_instance(inst_iter, inst)) > 0)
        {
            if (scf_instance_to_fmri(inst, fmri, sz) < 0)
            {
                //failure
            }
            zbx_json_addobject(&json, NULL);
            zbx_json_addstring(&json, "{#SERVICE}", fmri, ZBX_JSON_TYPE_STRING);
            zbx_json_close(&json);
        }
        if (r < 0) break;
    }

    if (r < 0)
    {
        //failure
    }

    /*
    zabbix_log(LOG_LEVEL_TRACE,
               "Module: %s - raw data: %s (%s:%d)",
               MODULE_NAME, json.buffer, __FILE__, __LINE__);
    */

    //zbx_json_free(&json);

    scf_handle_destroy(handle);
    scf_scope_destroy(scope);
    scf_service_destroy(svc);
    scf_instance_destroy(inst);
    scf_iter_destroy(svc_iter);

    return json.buffer;
}

int scf_status_int(const char *scf)
{
    const char *status_string;
    int status_int;

    status_string = smf_get_state(scf);

    if (status_string != NULL)
    {
        status_int = smf_state_from_string(status_string);
    }
    else
    {
        /* NULL */
        status_int = 0;
    }

    return status_int;
}