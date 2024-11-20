/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
******************************************************************************

    Include files

******************************************************************************
*/
#include <stdlib.h>
#include "icfg_api.h"
#include "icli_api.h"
#include "icli_porting_trace.h"

#ifdef __cplusplus
#include "enum_macros.hxx"
MRDC_ENUM_INC(icli_privilege_t);
#endif

/*
******************************************************************************

    Constant and Macro definition

******************************************************************************
*/
#define __VISIBLE_MIN_CHAR      33
#define __VISIBLE_MAX_CHAR      126
#define __VISIBLE_SIZE          (__VISIBLE_MAX_CHAR - __VISIBLE_MIN_CHAR + 1)
/*
******************************************************************************

    Data structure type definition

******************************************************************************
*/
static BOOL                 g_banner_deli[__VISIBLE_SIZE];
static char                 g_banner[ICLI_BANNER_MAX_LEN + 1];
static char                 g_password[ICLI_PASSWORD_MAX_LEN + 1];
static char                 g_dev_name[ICLI_DEV_NAME_MAX_LEN + 1];
static icli_session_data_t  g_session_data;
static critd_t              g_mutex;

/*
******************************************************************************

    Static Function

******************************************************************************
*/
struct ICLILockScope {
    ICLILockScope(const char *file, int line)
        : file(file), line(line)
    {
        critd_enter(&g_mutex, file, line);
    }

    ~ICLILockScope(void)
    {
        critd_exit(&g_mutex, file, line);
    }
private:
    const char *file;
    const int  line;
};


static mrdc_rc _banner_print(
    IN mrdc_icfg_query_result_t     *result,
    IN const char                   *type
)
{
    mrdc_rc     rc;
    char        *c;
    char        i;

    if ( g_banner[0] ) {
        /* find delimiter */
        memset(g_banner_deli, 0, sizeof(g_banner_deli));

        // the comment token can not be used for delimiter
        g_banner_deli['!' - __VISIBLE_MIN_CHAR] = TRUE;
        g_banner_deli['#' - __VISIBLE_MIN_CHAR] = TRUE;

        for ( c = g_banner; (*c) != 0; c++ ) {
            if ( (*c) >= __VISIBLE_MIN_CHAR && (*c) <= __VISIBLE_MAX_CHAR ) {
                g_banner_deli[(*c) - __VISIBLE_MIN_CHAR] = TRUE;
            }
        }
        for ( i = 0; i < __VISIBLE_SIZE; i++ ) {
            if ( g_banner_deli[(int)i] == FALSE ) {
                break;
            }
        }
        if ( i < __VISIBLE_SIZE ) {
            i += __VISIBLE_MIN_CHAR;
        } else {
            i = '#';
        }

        /*  */
        rc = mrdc_icfg_printf(result, "banner %s %c%s%c\n", type, i, g_banner, i);
        if ( rc != MRDC_RC_OK ) {
            T_E("fail to print to icfg\n");
            return MRDC_RC_ERROR;
        }
    }
    return MRDC_RC_OK;
}

static mrdc_rc _enable_password_print(
    IN mrdc_icfg_query_result_t     *result,
    IN icli_privilege_t             priv
)
{
    mrdc_rc     rc;

    if ( g_password[0] ) {
        if ( icli_enable_password_if_secret_get(priv) ) {
            rc = mrdc_icfg_printf(result, "enable secret 5 level %d %s\n",
                                  priv, g_password);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        } else {
            rc = mrdc_icfg_printf(result, "enable password level %d %s\n",
                                  priv, g_password);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }
    }
    return MRDC_RC_OK;
}

/* ICFG callback functions */
static mrdc_rc _icli_icfg(
    IN const mrdc_icfg_query_request_t  *req,
    IN mrdc_icfg_query_result_t         *result
)
{
    mrdc_rc              rc;
    BOOL                 b_print, is_default;
    icli_privilege_t     priv;
    i32                  sec;
    icli_priv_cmd_conf_t cmd_conf;
    const char           *prompt;

    if ( req == NULL ) {
        T_E("req == NULL\n");
        return MRDC_RC_ERROR;
    }

    if ( result == NULL ) {
        T_E("result == NULL\n");
        return MRDC_RC_ERROR;
    }
    ICLILockScope lock(__FILE__, __LINE__);

    switch ( req->cmd_mode ) {
    case ICLI_CMD_MODE_GLOBAL_CONFIG:
        /* banner motd */
        if ( icli_banner_motd_get(g_banner) != ICLI_RC_OK ) {
            T_E("fail to get motd banner\n");
            return MRDC_RC_ERROR;
        }
        if ( _banner_print(result, "motd") != MRDC_RC_OK ) {
            return MRDC_RC_ERROR;
        }

        /* banner exec */
        if ( icli_banner_exec_get(g_banner) != ICLI_RC_OK ) {
            T_E("fail to get exec banner\n");
            return MRDC_RC_ERROR;
        }
        if ( _banner_print(result, "exec") != MRDC_RC_OK ) {
            return MRDC_RC_ERROR;
        }

        /* banner login */
        if ( icli_banner_login_get(g_banner) != ICLI_RC_OK ) {
            T_E("fail to get login banner\n");
            return MRDC_RC_ERROR;
        }
        if ( _banner_print(result, "login") != MRDC_RC_OK ) {
            return MRDC_RC_ERROR;
        }

        /* enable password */
        for (priv = (icli_privilege_t)0; priv < (icli_privilege_t)(ICLI_PRIVILEGE_MAX - 1); ++priv) {
            if ( icli_enable_password_get(priv, g_password) == FALSE ) {
                T_E("fail to get enable password at priv %d\n", priv);
                return MRDC_RC_ERROR;
            }
            if ( _enable_password_print(result, priv) != MRDC_RC_OK ) {
                return MRDC_RC_ERROR;
            }
        }
        // highest privilege has default value, so process individually
        if ( icli_enable_password_get(priv, g_password) == FALSE ) {
            T_E("fail to get enable password at priv %d\n", priv);
            return MRDC_RC_ERROR;
        }
        // check if print
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( icli_str_cmp(g_password, ICLI_DEFAULT_ENABLE_PASSWORD) != 0 ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            if ( _enable_password_print(result, priv) != MRDC_RC_OK ) {
                return MRDC_RC_ERROR;
            }
        }

        /* hostname */
        if ( icli_dev_name_get(g_dev_name) != ICLI_RC_OK ) {
            T_E("fail to get device name\n");
            return MRDC_RC_ERROR;
        }
        // check if print
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( icli_str_cmp(g_dev_name, ICLI_DEFAULT_DEVICE_NAME) != 0 ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            if ( g_dev_name[0] ) {
                rc = mrdc_icfg_printf(result, "hostname %s\n", g_dev_name);
            } else {
                rc = mrdc_icfg_printf(result, "no hostname\n");
            }
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        // Prompt
        // This is a little special, because we need to call a function to figure out
        // whether the current prompt is default or not (ssssh, between us: it has two defaults).
        prompt = icli_prompt_get();
        if ((is_default = icli_prompt_is_default(prompt))) {
            // The default prompt to show in all-defaults need not be the same
            // as held in #prompt.
            prompt = icli_prompt_default_get();
        }

        if (req->all_defaults || !is_default) {
            // Cater for the case where someone changes the default prompt to an empty string
            if (strlen(prompt)) {
                (void)mrdc_icfg_printf(result, "prompt %s\n", prompt);
            } else {
                (void)mrdc_icfg_printf(result, "no prompt\n");
            }
        }

        /* command privilege */
        if ( icli_priv_get_first(&cmd_conf) == ICLI_RC_OK ) {
            rc = mrdc_icfg_printf(result, "privilege %s level %u %s\n", icli_mode_name_get(cmd_conf.mode), cmd_conf.privilege, cmd_conf.cmd);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
            while ( icli_priv_get_next(&cmd_conf) == ICLI_RC_OK ) {
                rc = mrdc_icfg_printf(result, "privilege %s level %u %s\n", icli_mode_name_get(cmd_conf.mode), cmd_conf.privilege, cmd_conf.cmd);
                if ( rc != MRDC_RC_OK ) {
                    T_E("fail to print to icfg\n");
                    return MRDC_RC_ERROR;
                }
            }
        }

        break;

    case ICLI_CMD_MODE_CONFIG_LINE:
        /* get session data */
        g_session_data.session_id = req->instance_id.line;
        if ( icli_session_data_get(&g_session_data) != ICLI_RC_OK ) {
            T_E("fail to get session data of session %d.\n", g_session_data.session_id);
            return MRDC_RC_ERROR;
        }

        /* editing */
        // check if print
        if ( req->all_defaults ) {
            if ( g_session_data.input_style == ICLI_INPUT_STYLE_SINGLE_LINE ) {
                rc = mrdc_icfg_printf(result, " editing\n");
                if ( rc != MRDC_RC_OK ) {
                    T_E("fail to print to icfg\n");
                    return MRDC_RC_ERROR;
                }
            } else {
                rc = mrdc_icfg_printf(result, " no editing\n");
                if ( rc != MRDC_RC_OK ) {
                    T_E("fail to print to icfg\n");
                    return MRDC_RC_ERROR;
                }
            }
        } else if ( g_session_data.input_style != ICLI_INPUT_STYLE_SINGLE_LINE ) {
            // different with default
            rc = mrdc_icfg_printf(result, " no editing\n");
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* exec-banner */
        b_print = FALSE;
        if ( req->all_defaults ) {
            if ( g_session_data.b_exec_banner ) {
                rc = mrdc_icfg_printf(result, " exec-banner\n");
                if ( rc != MRDC_RC_OK ) {
                    T_E("fail to print to icfg\n");
                    return MRDC_RC_ERROR;
                }
            } else {
                b_print = TRUE;
            }
        } else if ( g_session_data.b_exec_banner != TRUE ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " no exec-banner\n");
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* exec-timeout */
        sec = (g_session_data.wait_time <= 0) ? 0 : g_session_data.wait_time;
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( sec != ICLI_DEFAULT_WAIT_TIME ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " exec-timeout %d %d\n", sec / 60, sec % 60);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* history size */
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( g_session_data.history_size != ICLI_HISTORY_CMD_CNT ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " history size %u\n", g_session_data.history_size);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* length */
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( g_session_data.lines != ICLI_DEFAULT_LINES ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " length %u\n", g_session_data.lines);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* location */
        if ( g_session_data.location[0] ) {
            rc = mrdc_icfg_printf(result, " location %s\n", g_session_data.location);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* motd-banner */
        b_print = FALSE;
        if ( req->all_defaults ) {
            if ( g_session_data.b_motd_banner ) {
                rc = mrdc_icfg_printf(result, " motd-banner\n");
                if ( rc != MRDC_RC_OK ) {
                    T_E("fail to print to icfg\n");
                    return MRDC_RC_ERROR;
                }
            } else {
                b_print = TRUE;
            }
        } else if ( g_session_data.b_motd_banner != TRUE ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " no motd-banner\n");
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }


        /* privilege level */
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( g_session_data.privileged_level != ICLI_DEFAULT_PRIVILEGED_LEVEL ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " privilege level %d\n", g_session_data.privileged_level);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }

        /* width */
        b_print = FALSE;
        if ( req->all_defaults ) {
            b_print = TRUE;
        } else if ( g_session_data.width != ICLI_DEFAULT_WIDTH ) {
            // different with default
            b_print = TRUE;
        }
        if ( b_print ) {
            rc = mrdc_icfg_printf(result, " width %u\n", g_session_data.width);
            if ( rc != MRDC_RC_OK ) {
                T_E("fail to print to icfg\n");
                return MRDC_RC_ERROR;
            }
        }
        break;

    default:
        /* no config in other modes */
        break;
    }
    return MRDC_RC_OK;
}

/*
******************************************************************************

    Public functions

******************************************************************************
*/

/* Initialization function */
mrdc_rc icli_icfg_init(void)
{
    mrdc_rc rc;

    /*
        Register Global config callback functions to ICFG module.
    */
    rc = mrdc_icfg_query_register(MRDC_ICFG_GLOBAL_ICLI, "icli", _icli_icfg);
    if ( rc != MRDC_RC_OK ) {
        return rc;
    }

    /*
        Register Line config callback functions to ICFG module.
    */
    rc = mrdc_icfg_query_register(MRDC_ICFG_LINE_ICLI, "icli", _icli_icfg);
    if ( rc != MRDC_RC_OK ) {
        return rc;
    }

    /* init mutex */
    critd_init(&g_mutex, "icli_icfg", MRDC_MODULE_ID_ICLI, CRITD_TYPE_MUTEX);

    return MRDC_RC_OK;
}
