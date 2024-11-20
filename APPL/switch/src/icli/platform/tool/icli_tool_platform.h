/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
==============================================================================

    Revision history
    > CP.Wang, 05/29/2013 14:18
        - create

==============================================================================
*/
#ifndef __ICLI_TOOL_PLATFORM_H__
#define __ICLI_TOOL_PLATFORM_H__
//****************************************************************************
/*
==============================================================================

    Include File

==============================================================================
*/
#include "mrdc_icli.h"
#include "icli_porting_trace.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
==============================================================================

    Constant

==============================================================================
*/

/*
==============================================================================

    Type

==============================================================================
*/

/*
==============================================================================

    Macro Definition

==============================================================================
*/

/*
==============================================================================

    Public Function

==============================================================================
*/
/*
    get command mode info by string

    INPUT
        mode_str : string of mode

    OUTPUT
        n/a

    RETURN
        icli_cmd_mode_info_t * : successful
        NULL                        : failed

    COMMENT
        n/a
*/
const icli_cmd_mode_info_t *icli_platform_cmd_mode_info_get_by_str(
    IN  char    *mode_str
);

/*
    get command mode info by command mode

    INPUT
        mode : command mode

    OUTPUT
        n/a

    RETURN
        icli_cmd_mode_info_t * : successful
        NULL                        : failed

    COMMENT
        n/a
*/
const icli_cmd_mode_info_t *icli_platform_cmd_mode_info_get_by_mode(
    IN  icli_cmd_mode_t     mode
);

/*
    get privilege by string

    INPUT
        priv_str : string of privilege

    OUTPUT
        n/a

    RETURN
        icli_privilege_t   : successful
        ICLI_PRIVILEGE_MAX : failed

    COMMENT
        n/a
*/
icli_privilege_t icli_platform_privilege_get_by_str(
    IN char     *priv_str
);

#ifdef __cplusplus
}
#endif
//****************************************************************************
#endif //__ICLI_TOOL_PLATFORM_H__

