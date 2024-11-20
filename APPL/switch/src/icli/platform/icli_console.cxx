/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
******************************************************************************

    Include File

******************************************************************************
*/
#include "icli_api.h"

#ifndef MRDC_SW_OPTION_CLI
#ifdef MRDC_SW_OPTION_CONSOLE
#include <string.h>
#include "console_api.h"
#endif
#endif /* MRDC_SW_OPTION_CLI */

/*
******************************************************************************

    Constant and Macro

******************************************************************************
*/

/*
******************************************************************************

    Type Definition

******************************************************************************
*/

/*
******************************************************************************

    Static Variable

******************************************************************************
*/

/*
******************************************************************************

    Static Function

******************************************************************************
*/

/*
******************************************************************************

    Public Function

******************************************************************************
*/
BOOL icli_console_start(void)
{
#ifndef MRDC_SW_OPTION_CLI
#ifdef MRDC_SW_OPTION_CONSOLE
    i32                         rc;
    u32                         session_id;
    icli_session_open_data_t    open_data;

    /* open a Console session */
    if ( console_session_open("ICLI", &session_id) == FALSE ) {
        T_E("fail to open a Console session\n");
        return FALSE;
    }

    /* Open ICLI session */
    memset(&open_data, 0, sizeof(open_data));

    open_data.name      = "CONSOLE";
    open_data.way       = ICLI_SESSION_WAY_CONSOLE;
    open_data.app_id    = session_id;

    /* I/O callback */
    open_data.char_get  = &console_getc;
    open_data.char_put  = &console_putc;
    open_data.str_put   = &console_puts;

    /* APP session callback */
    open_data.app_init  = NULL;
    open_data.app_close = NULL;

    rc = icli_session_open(&open_data, &session_id);
    if ( rc != ICLI_RC_OK ) {
        T_E("fail to open a session for console\n");
        return FALSE;
    }
#endif
#endif /* MRDC_SW_OPTION_CLI */
    return TRUE;
}

