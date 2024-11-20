/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

#ifndef __MRDC_ICLI_SESSION_Z_H__
#define __MRDC_ICLI_SESSION_Z_H__
//****************************************************************************

/*
==============================================================================

    Include File

==============================================================================
*/

/*
==============================================================================

    Constant and Macro

==============================================================================
*/

/*
==============================================================================

    Type Definition

==============================================================================
*/

/*
==============================================================================

    Public Function

==============================================================================
*/
/*
    get command from usr input
    1. function key will be provided
    2. the command will be stored in handle->runtime_data.cmd

    INPUT
        handle : session handle

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_z_usr_cmd_get(
    IN  icli_session_handle_t   *handle
);

/*
    More page

    INPUT
        handle : session handle

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_z_line_mode(
    IN icli_session_handle_t    *handle
);

void mrdc_icli_z_cmd_display(
    IN  icli_session_handle_t   *handle
);

void mrdc_icli_z_line_clear(
    IN  icli_session_handle_t   *handle
);

//****************************************************************************
#endif //__MRDC_ICLI_SESSION_Z_H__

