/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
==============================================================================

    Include File

==============================================================================
*/
#include "mrdc_icli.h"

/*
==============================================================================

    Constant

==============================================================================
*/
#define _WAIT_TIME_SLICE    100

/*
==============================================================================

    Constant

==============================================================================
*/
/*
==============================================================================

    Type Definition

==============================================================================
*/

/*
==============================================================================

    Static Variable

==============================================================================
*/

/*
==============================================================================

    Static Function

==============================================================================
*/

/*
==============================================================================

    Public Function

==============================================================================
*/
icli_history_cmd_t *mrdc_icli_sutil_history_cmd_alloc(
    IN  icli_session_handle_t   *handle
)
{
    icli_history_cmd_t  *hcmd;

    if ( handle->runtime_data.history_cmd_free_list == NULL ) {
        return NULL;
    }

    hcmd = handle->runtime_data.history_cmd_free_list;
    handle->runtime_data.history_cmd_free_list = hcmd->next;
    memset( hcmd, 0, sizeof(icli_history_cmd_t) );
    ++( handle->runtime_data.history_cmd_cnt );
    return hcmd;
}

void mrdc_icli_sutil_history_cmd_free(
    IN  icli_session_handle_t   *handle,
    IN  icli_history_cmd_t      *hcmd
)
{
    if ( hcmd == NULL ) {
        T_E("hcmd == NULL\n");
        return;
    }

    hcmd->next = handle->runtime_data.history_cmd_free_list;
    handle->runtime_data.history_cmd_free_list = hcmd;
    --( handle->runtime_data.history_cmd_cnt );
}

void mrdc_icli_sutil_history_cmd_free_n(
    IN  icli_session_handle_t   *handle,
    IN  u32                     n
)
{
    icli_history_cmd_t  *hcmd;
    icli_history_cmd_t  *hnext;
    u32                 cnt;

    if ( n == 0 ) {
        return;
    }

    if ( handle->runtime_data.history_cmd_head == NULL ) {
        return;
    }

    cnt = 0;
    hcmd = handle->runtime_data.history_cmd_head->next;
    while (  hcmd ) {
        ++cnt;
        if ( cnt > n ) {
            break;
        }

        hnext = hcmd->next;
        mrdc_icli_sutil_history_cmd_free( handle, hcmd );
        hcmd = hnext;
    }

    if ( hcmd ) {
        handle->runtime_data.history_cmd_head->next = hcmd;
        hcmd->prev = handle->runtime_data.history_cmd_head;
    } else {
        handle->runtime_data.history_cmd_head = NULL;
    }
}

BOOL mrdc_icli_sutil_history_cmd_full(
    IN  icli_session_handle_t   *handle
)
{
    if ( ICLI_HISTORY_MAX_CNT && (handle->runtime_data.history_cmd_cnt < ICLI_HISTORY_MAX_CNT) ) {
        return FALSE;
    }
    return TRUE;
}

BOOL mrdc_icli_sutil_history_cmd_empty(
    IN  icli_session_handle_t   *handle
)
{
    if ( ICLI_HISTORY_MAX_CNT && handle->runtime_data.history_cmd_cnt ) {
        return FALSE;
    }
    return TRUE;
}

u32 mrdc_icli_sutil_history_cmd_cnt(
    IN  icli_session_handle_t   *handle
)
{
    return handle->runtime_data.history_cmd_cnt;
}

void mrdc_icli_sutil_history_cmd_pos_prev(
    IN  icli_session_handle_t   *handle
)
{
    if ( handle->runtime_data.history_cmd_pos ) {
        ___PREV( handle->runtime_data.history_cmd_pos );
    } else {
        handle->runtime_data.history_cmd_pos = handle->runtime_data.history_cmd_head;
    }
}

void mrdc_icli_sutil_history_cmd_pos_next(
    IN  icli_session_handle_t   *handle
)
{
    if ( handle->runtime_data.history_cmd_pos ) {
        ___NEXT( handle->runtime_data.history_cmd_pos );
    }
}

void mrdc_icli_sutil_cmd_reset(
    IN  icli_session_handle_t   *handle
)
{
    memset(handle->runtime_data.cmd, 0, sizeof(handle->runtime_data.cmd));
    handle->runtime_data.cmd_pos      = 0;
    handle->runtime_data.cmd_len      = 0;
    handle->runtime_data.start_pos    = 0;
    handle->runtime_data.cursor_pos   = 0;
    handle->runtime_data.left_scroll  = 0;
    handle->runtime_data.right_scroll = 0;
#if 0 /* CP, 2012/08/30 09:12, do command by CLI command */
    handle->runtime_data.cmd_do       = NULL;
#endif
}

/*
    get session input by char

    INPUT
        handle    - session handle
        wait_time - in millisecond
                    = 0 - no wait
                    < 0 - forever

    OUTPUT
        c - user input char

    RETURN
        TRUE  - successful
        FALSE - timeout
*/
BOOL mrdc_icli_sutil_usr_char_get(
    IN  icli_session_handle_t   *handle,
    IN  i32                     wait_time,
    OUT i32                     *c
)
{
    icli_session_char_get_t     *char_get_cb;
    i32                         app_id;
    BOOL                        b;
    i32                         n, t = _WAIT_TIME_SLICE;

    if ( handle->open_data.char_get == NULL ) {
        T_E("char_get == NULL\n");
        return FALSE;
    }

    // get milli-seconds for waiting
    if ( wait_time == 0 ) {
        // no wait
        n = 1;
        t = 0;
    } else if ( wait_time < 0 ) {
        // wait forever
        n = -1;
    } else {
        n = wait_time / _WAIT_TIME_SLICE;
        if ( wait_time % _WAIT_TIME_SLICE ) {
            ++n;
        }
    }

    char_get_cb = handle->open_data.char_get;
    app_id = handle->open_data.app_id;

    handle->runtime_data.idle_time = icli_os_current_time_get();

    while ( n ) {

        _ICLI_SEMA_GIVE();

        b = (*char_get_cb)(app_id, t, c);

        _ICLI_SEMA_TAKE();

        if ( handle->runtime_data.alive == FALSE ) {
            return FALSE;
        }

        if ( b ) {
            /* get idle time */
            handle->runtime_data.idle_time = icli_os_current_time_get();
            return TRUE;
        }

        if ( n > 0 ) {
            --n;
        }
    }

    return FALSE;
}

/*
    get user input char according to session wait time

    INPUT
        handle - session handle
            handle->wait_time - in millisecond
                                = 0 - forever

    OUTPUT
        c - user input char

    RETURN
        TRUE  - successful
        FALSE - timeout
*/
BOOL mrdc_icli_sutil_usr_char_get_by_session(
    IN  icli_session_handle_t   *handle,
    OUT i32                     *c
)
{
    icli_session_char_get_t     *char_get_cb;
    i32                         app_id;
    BOOL                        b;
    u32                         idle_time;

    if ( handle->open_data.char_get == NULL ) {
        T_E("char_get == NULL\n");
        return FALSE;
    }

    char_get_cb = handle->open_data.char_get;
    app_id = handle->open_data.app_id;

    handle->runtime_data.idle_time = icli_os_current_time_get();

    for (;;) {

        _ICLI_SEMA_GIVE();

        b = (*char_get_cb)(app_id, _WAIT_TIME_SLICE, c);

        _ICLI_SEMA_TAKE();

        if ( handle->runtime_data.alive == FALSE ) {
            return FALSE;
        }

        if ( b ) {
            /* get idle time */
            handle->runtime_data.idle_time = icli_os_current_time_get();
            return TRUE;
        } else {
            /* timeout, check if expired */
            if ( handle->config_data->wait_time > 0 ) {
                idle_time = icli_os_current_time_get() - handle->runtime_data.idle_time;
                if ( idle_time >= (handle->config_data->wait_time * 1000) ) {
                    break;
                }
            }
        }
    }

    /* expire */
    return FALSE;
}

/*
    output a char on session
*/
BOOL mrdc_icli_sutil_usr_char_put(
    IN  icli_session_handle_t   *handle,
    IN  char                    c
)
#if 1 /* CP, 2013/04/15 10:51, APP to take output */
{
    icli_session_char_put_t     *char_put_cb;
    icli_session_str_put_t      *str_put_cb;
    i32                         app_id;
    BOOL                        b;
    char                        str[2];

    if ( handle->open_data.char_put ) {
        char_put_cb = handle->open_data.char_put;
        app_id = handle->open_data.app_id;

        _ICLI_SEMA_GIVE();

        b = (*char_put_cb)(app_id, c);

        _ICLI_SEMA_TAKE();

        return b;
    }

    if ( handle->open_data.str_put ) {
        str_put_cb = handle->open_data.str_put;
        app_id = handle->open_data.app_id;
        str[0] = c;
        str[1] = 0;

        _ICLI_SEMA_GIVE();

        b = (*str_put_cb)(app_id, str);

        _ICLI_SEMA_TAKE();

        return b;
    }

    return TRUE;
}
#else
{
    icli_session_char_put_t     *char_put_cb;
    i32                         app_id;
    BOOL                        b;

    if ( handle->open_data.char_put == NULL ) {
        return TRUE;
    }

    char_put_cb = handle->open_data.char_put;
    app_id = handle->open_data.app_id;

    _ICLI_SEMA_GIVE();

    b = (*char_put_cb)(app_id, c);

    _ICLI_SEMA_TAKE();

    return b;
}
#endif

/*
    output string on session
*/
BOOL mrdc_icli_sutil_usr_str_put(
    IN  icli_session_handle_t   *handle
)
#if 1 /* CP, 2013/04/15 10:51, APP to take output */
{
    icli_session_str_put_t      *str_put_cb;
    icli_session_char_put_t     *char_put_cb;
    i32                         app_id;
    const char                  *str;
    BOOL                        b;
    const char                  *c;

    if ( handle->open_data.str_put ) {
        str = handle->runtime_data.put_str;
        if ( str == NULL ) {
            T_E("handle->runtime_data.put_str == NULL\n");
            return FALSE;
        }

        str_put_cb = handle->open_data.str_put;
        app_id = handle->open_data.app_id;

        _ICLI_SEMA_GIVE();

        b = (*str_put_cb)(app_id, str);

        _ICLI_SEMA_TAKE();

        return b;
    }

    if ( handle->open_data.char_put ) {
        str = handle->runtime_data.put_str;
        if ( str == NULL ) {
            T_E("handle->runtime_data.put_str == NULL\n");
            return FALSE;
        }

        char_put_cb = handle->open_data.char_put;
        app_id = handle->open_data.app_id;

        _ICLI_SEMA_GIVE();

        b = TRUE;
        for ( c = str; ICLI_NOT_(EOS, *c); ++c ) {
            b = (*char_put_cb)(app_id, *c);
            if ( b == FALSE ) {
                break;
            }
        }

        _ICLI_SEMA_TAKE();

        return b;
    }

    return TRUE;
}
#else
{
    icli_session_str_put_t  *str_put_cb;
    i32                     app_id;
    char                    *str;
    BOOL                    b;

    if ( handle->open_data.str_put == NULL ) {
        return TRUE;
    }

    str = handle->runtime_data.put_str;
    if ( str == NULL ) {
        T_E("handle->runtime_data.put_str == NULL\n");
        return FALSE;
    }

    str_put_cb = handle->open_data.str_put;
    app_id = handle->open_data.app_id;

    _ICLI_SEMA_GIVE();

    b = (*str_put_cb)(app_id, str);

    _ICLI_SEMA_TAKE();

    return b;
}
#endif

void mrdc_icli_sutil_tab_reset(
    IN  icli_session_handle_t   *handle
)
{
    handle->runtime_data.tab_cnt = 0;
    handle->runtime_data.tab_port_type = ICLI_PORT_TYPE_NONE;
    mrdc_icli_exec_para_list_free( &(handle->runtime_data.cmd_var) );
    mrdc_icli_exec_para_list_free( &(handle->runtime_data.match_sort_list) );
    handle->runtime_data.grep_var   = NULL;
    handle->runtime_data.grep_begin = 0;
}

void mrdc_icli_sutil_more_prompt_clear(
    IN icli_session_handle_t    *handle
)
{
    i32     len;

    for ( len = mrdc_icli_str_len(handle->runtime_data.put_str); len > 0; --len ) {
        icli_platform_cursor_backward( handle );
        ICLI_PUT_SPACE;
        icli_platform_cursor_backward( handle );
    }
}

/*
    cmd_pos, cmd_len : updated
    cursor_pos       : not updated
*/
BOOL mrdc_icli_sutil_cmd_char_add(
    IN  icli_session_handle_t   *handle,
    IN  i32                     c
)
{
    i32     i;

    /* not supported keys, skip */
    if ( ! ICLI_KEY_VISIBLE(c) ) {
        ICLI_PLAY_BELL;
        return FALSE;
    }

#if 0 /* CP, 2012/08/17 09:38, accept space at beginning */
    /* SPACE at the begin, skip */
    if ( ICLI_IS_(SPACE, c) && handle->runtime_data.cmd_pos == 0 ) {
        return FALSE;
    }
#endif

    /* full in length */
    if ( handle->runtime_data.cmd_len >= ICLI_STR_MAX_LEN ) {
        return FALSE;
    }

    /* cursor at middle, shift command */
    if ( ! _CURSOR_AT_CMD_END ) {
        for ( i = handle->runtime_data.cmd_len; i > handle->runtime_data.cmd_pos; --i ) {
            handle->runtime_data.cmd[i] = handle->runtime_data.cmd[i - 1];
        }
    }

    /* put into cmd */
    handle->runtime_data.cmd[handle->runtime_data.cmd_pos] = (char)c;

    /* update cmd_pos */
    _INC_1( handle->runtime_data.cmd_pos );

    /* increase command length */
    _INC_1( handle->runtime_data.cmd_len );

    return TRUE;
}

void mrdc_icli_sutil_current_xy_get(
    IN  icli_session_handle_t   *handle,
    OUT i32                     *x,
    OUT i32                     *y
)
{
    i32     len;

    len = handle->runtime_data.prompt_len + handle->runtime_data.cursor_pos;
    *x = len % (i32)(handle->runtime_data.width);
    *y = len / (i32)(handle->runtime_data.width);
}

void mrdc_icli_sutil_end_xy_get(
    IN  icli_session_handle_t   *handle,
    OUT i32                     *x,
    OUT i32                     *y
)
{
    i32     len;

    len = handle->runtime_data.prompt_len + handle->runtime_data.cmd_len;
    *x = len % (i32)(handle->runtime_data.width);
    *y = len / (i32)(handle->runtime_data.width);
}
