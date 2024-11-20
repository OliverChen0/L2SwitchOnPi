/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

#ifndef __MRDC_ICLI_PARSING_H__
#define __MRDC_ICLI_PARSING_H__
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
    initialization

    input -
        n/a
    output -
        n/a
    return -
        icli_rc_t
    comment -
        n/a
*/
i32 mrdc_icli_parsing_init(
    void
);

/*
    build parsing tree

    input -
        cmd_register : command data, string with word ID
    output -
        n/a
    return -
        icli_rc_t
    comment -
        n/a
*/
i32 mrdc_icli_parsing_build(
    IN  icli_cmd_register_t     *cmd_register
);

/*
    get parsing tree according to the mode

    input -
        mode : command mode
    output -
        n/a
    return -
        not NULL : successful, tree
        NULL     : failed
    comment -
        n/a
*/
icli_parsing_node_t *mrdc_icli_parsing_tree_get(
    IN  icli_cmd_mode_t         mode
);

/*
    check if head is the random optiona head of node

    INPUT
        head : random optional head
        node : the node to be checked

    OUTPUT
        n/a

    RETURN
        TRUE  - yes, it is
        FALSE - no

    COMMENT
        n/a
*/
BOOL mrdc_icli_parsing_random_head(
    IN  icli_parsing_node_t     *head,
    IN  icli_parsing_node_t     *node,
    OUT u32                     *optional_level
);

//****************************************************************************
#endif //__MRDC_ICLI_PARSING_H__

