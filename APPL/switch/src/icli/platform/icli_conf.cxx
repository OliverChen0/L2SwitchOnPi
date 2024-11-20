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
#include "icli_porting_trace.h"
#include "misc_api.h"

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
/*
    save ICLI config data into file

    INPUT
        n/a

    OUTPUT
        n/a

    RETURN
        TRUE  - successful
        FALSE - failed

    COMMENT
        n/a
*/
BOOL icli_conf_file_write(
    void
)
{
    // successful
    return TRUE;
}

/*
    load and apply ICLI config data from file

    INPUT
        b_default : create default config or not

    OUTPUT
        n/a

    RETURN
        TRUE  - successful
        FALSE - failed

    COMMENT
        n/a
*/
BOOL icli_conf_file_load(
    IN BOOL     b_default
)
{
    if (b_default) {}

    // load defaults
    if ( icli_conf_default() != ICLI_RC_OK ) {
        T_E("fail to reset conf to default\n");
        return FALSE;
    }

    // successful
    return TRUE;
}
