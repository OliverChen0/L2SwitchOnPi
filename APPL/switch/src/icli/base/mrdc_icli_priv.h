/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

#ifndef __MRDC_ICLI_PRIV_H__
#define __MRDC_ICLI_PRIV_H__
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
#define ICLI_PRIV_MATCH_NODE_CNT        16

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
    initialization

    INPUT
        n/a

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_priv_init(
    void
);

/*
    set privilege per command

    INPUT
        conf   : privilege command configuration

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_priv_set(
    IN  icli_priv_cmd_conf_t    *conf
);

/*
    delete privilege per command

    INPUT
        conf : privilege command configuration, index - mode, cmd

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_priv_delete(
    IN icli_priv_cmd_conf_t    *conf
);

/*
    get first privilege per command

    INPUT
        n/a

    OUTPUT
        conf : first privilege command configuration, index - mode, cmd

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_priv_get_first(
    OUT icli_priv_cmd_conf_t    *conf
);

/*
    get privilege per command

    INPUT
        conf : privilege command configuration, index - mode, cmd

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_priv_get(
    INOUT icli_priv_cmd_conf_t    *conf
);

/*
    get next privilege per command
    use index - mode, cmd to find the current one and then get the next one
    of the current one. So, if the current one is not found, then this fails.

    INPUT
        conf : privilege command configuration, sorted by time

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_priv_get_next(
    INOUT icli_priv_cmd_conf_t    *conf
);

//****************************************************************************
#endif //__MRDC_ICLI_PRIV_H__

