/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/
#ifndef __MRDC_ICLI_VARIABLE_H__
#define __MRDC_ICLI_VARIABLE_H__
//****************************************************************************

/*
==============================================================================

    Include File

==============================================================================
*/
#include "mrdc_icli_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
==============================================================================

    Constant and Macro

==============================================================================
*/
#if 1 /* CP, 2012/09/25 10:47, <dscp> */
#define ICLI_DSCP_MAX_CNT   22
#endif

/*
==============================================================================

    Type Definition

==============================================================================
*/
#if 1 /* CP, 2012/09/25 10:47, <dscp> */
typedef struct {
    const char    *word;
    u32           value;
    const char    *help;
} icli_dscp_wvh_t;
#endif

/*
==============================================================================

    Public Function

==============================================================================
*/
/*
    parse string to get signed/unsigned range

    input -
        range_str : string of range
        delimiter : the delimiter for range

    output -
        range : range

    return -
        icli_rc_t

    comment -
        n/a
*/
i32 mrdc_icli_variable_range_get(
    IN  char            *range_str,
    IN  char            delimiter,
    OUT icli_range_t    *range
);

/*
    get variable type for the name

    INPUT
        name : variable name

    OUTPUT
        type  : variable type
        range : value range

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_variable_type_get(
    IN  char                    *name,
    OUT icli_variable_type_t    *type,
    OUT icli_range_t            *range
);

/*
    get value from the word for the type

    input -
        type  : variable type
        word  : user input word
        range : range checking

    output -
        value   : corresponding value of the type if successful
        err_pos : error position if failed

    return -
        icli_rc_t

    comment -
        n/a
*/
i32 mrdc_icli_variable_get(
    IN  icli_variable_type_t    type,
    IN  char                    *word,
    IN  icli_range_t            *range,
    OUT icli_variable_value_t   *value,
    OUT u32                     *err_pos
);

/*
    get name string for the port type

    INPUT
        type : port type

    OUTPUT
        n/a

    RETURN
        name string of the type
            if the type is invalid. then "Unknown" is return

    COMMENT
        n/a
*/
char *mrdc_icli_variable_port_type_get_name(
    IN  icli_port_type_t    type
);

/*
    get short name string for the port type

    INPUT
        type : port type

    OUTPUT
        n/a

    RETURN
        short name string of the type
            if the type is invalid. then "Unkn" is return

    COMMENT
        n/a
*/
const char *mrdc_icli_variable_port_type_get_short_name(
    IN  icli_port_type_t    type
);

/*
    get help string for the port type

    INPUT
        type : port type

    OUTPUT
        n/a

    RETURN
        help string of the type
            if the type is invalid. then "Unknown" is return

    COMMENT
        n/a
*/
const char *mrdc_icli_variable_port_type_get_help(
    IN  icli_port_type_t    type
);

#if 1 /* CP, 2012/09/25 10:47, <dscp> */
/*
    get database pointer for DSCP word, value, help

    INPUT
        n/a

    OUTPUT
        n/a

    RETURN
        icli_dscp_wvh_t *

    COMMENT
        n/a
*/
icli_dscp_wvh_t *mrdc_icli_variable_dscp_wvh_get(
    void
);
#endif

#if ICLI_RANDOM_MUST_NUMBER
/*
    get 32-bit unsigned decimal

    INPUT
        word : user input word

    OUTPUT
        val  : unsigned 32-bit decimal value

    RETURN
        TRUE  - get successfully
        FALSE - fail to get
*/
BOOL mrdc_icli_variable_decimal_get(
    IN  char    *word,
    OUT u32     *val
);
#endif

const char *mrdc_icli_variable_data_name_get(
    IN  icli_variable_type_t    type
);

const char *mrdc_icli_variable_data_variable_get(
    IN  icli_variable_type_t    type
);

const char *mrdc_icli_variable_data_decl_type_get(
    IN  icli_variable_type_t    type
);

const char *mrdc_icli_variable_data_init_val_get(
    IN  icli_variable_type_t    type
);

BOOL mrdc_icli_variable_data_pointer_type_get(
    IN  icli_variable_type_t    type
);

BOOL mrdc_icli_variable_data_string_type_get(
    IN  icli_variable_type_t    type
);

BOOL mrdc_icli_variable_data_has_range_get(
    IN  icli_variable_type_t    type
);

icli_url_proto_t mrdc_icli_variable_url_protocol_get(
    IN  char     *w
);

#ifdef __cplusplus
}
#endif

//****************************************************************************
#endif //__MRDC_ICLI_VARIABLE_H__

