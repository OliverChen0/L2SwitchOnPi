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
#define Z_MORE_PROMPT  "-- more --, next page: Space, continue: c, quit: ^C"

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
static BOOL _fkey_backspace(
    IN  icli_session_handle_t   *handle
)
{
    /* already at the begin */
    if ( handle->runtime_data.cmd_pos == 0 ) {
        ICLI_PLAY_BELL;
        return TRUE;
    }

    icli_platform_cursor_backspace( handle );

    --( handle->runtime_data.cmd_pos );
    --( handle->runtime_data.cmd_len );
    handle->runtime_data.cmd[handle->runtime_data.cmd_len] = 0;
    return TRUE;
}

static void _fkey_line_end(
    IN  icli_session_handle_t   *handle
)
{
    /* already at the end */
    if ( handle->runtime_data.cmd_pos == handle->runtime_data.cmd_len ) {
        return;
    }
    mrdc_icli_session_str_put(handle, &(handle->runtime_data.cmd[handle->runtime_data.cmd_pos]));
    handle->runtime_data.cmd_pos = handle->runtime_data.cmd_len;
}

static BOOL _fkey_del_line(
    IN  icli_session_handle_t   *handle
)
{
    i32     i,
            len;

    //go to the end first
    _fkey_line_end( handle );

    //clear and back to the begin
    for ( i = 0, len = handle->runtime_data.cmd_len; i < len; ++i ) {
        if ( _fkey_backspace(handle) == FALSE ) {
            return FALSE;
        }
    }

    //reset cmd
    mrdc_icli_sutil_cmd_reset( handle );
    return TRUE;
}

static void _fkey_prev_cmd(
    IN  icli_session_handle_t   *handle
)
{
    /* empty */
    if ( mrdc_icli_sutil_history_cmd_empty(handle) ) {
        ICLI_PLAY_BELL;
        return;
    }

    /* alread at tail */
    if ( handle->runtime_data.history_cmd_pos == handle->runtime_data.history_cmd_head->next ) {
        ICLI_PLAY_BELL;
        return;
    }

    /* delete line */
    if ( _fkey_del_line(handle) == FALSE ) {
        return;
    }

    /* update history pos */
    mrdc_icli_sutil_history_cmd_pos_prev( handle );

    /* get history command */
    (void)mrdc_icli_str_cpy( handle->runtime_data.cmd, handle->runtime_data.history_cmd_pos->cmd);
    mrdc_icli_session_str_put(handle, handle->runtime_data.cmd);
    handle->runtime_data.cmd_len = mrdc_icli_str_len(handle->runtime_data.cmd);
    handle->runtime_data.cmd_pos = handle->runtime_data.cmd_len;
}

static void _fkey_next_cmd(
    IN  icli_session_handle_t   *handle
)
{
    /* delete line */
    if ( _fkey_del_line(handle) == FALSE ) {
        return;
    }

    /* empty */
    if ( mrdc_icli_sutil_history_cmd_empty(handle) ) {
        ICLI_PLAY_BELL;
        return;
    }

    /* no next */
    if ( handle->runtime_data.history_cmd_pos == NULL ) {
        ICLI_PLAY_BELL;
        return;
    }

    /* at head */
    if ( handle->runtime_data.history_cmd_pos == handle->runtime_data.history_cmd_head ) {
        handle->runtime_data.history_cmd_pos = NULL;
        ICLI_PLAY_BELL;
        return;
    }

    /* update history pos */
    mrdc_icli_sutil_history_cmd_pos_next( handle );

    /* get history command */
    (void)mrdc_icli_str_cpy( handle->runtime_data.cmd, handle->runtime_data.history_cmd_pos->cmd);
    mrdc_icli_session_str_put(handle, handle->runtime_data.cmd);
    handle->runtime_data.cmd_len = mrdc_icli_str_len(handle->runtime_data.cmd);
    handle->runtime_data.cmd_pos = handle->runtime_data.cmd_len;
}

static void _fkey_tab(
    IN  icli_session_handle_t   *handle
)
{
    handle->runtime_data.exec_type = ICLI_EXEC_TYPE_TAB;
}

static void _fkey_question(
    IN  icli_session_handle_t   *handle
)
{
    handle->runtime_data.exec_type = ICLI_EXEC_TYPE_QUESTION;
}

static void _cmd_put(
    IN  icli_session_handle_t   *handle,
    IN  i32                     c
)
{
    /* not supported keys, skip */
    if ( ! ICLI_KEY_VISIBLE(c) ) {
        ICLI_PLAY_BELL;
        return;
    }

    /* SPACE at the begin, skip */
    if ( ICLI_IS_(SPACE, c) && handle->runtime_data.cmd_pos == 0 ) {
        ICLI_PLAY_BELL;
        return;
    }

    /* full in length */
    if ( handle->runtime_data.cmd_len >= ICLI_STR_MAX_LEN ) {
        ICLI_PLAY_BELL;
        return;
    }

    handle->runtime_data.cmd[ (handle->runtime_data.cmd_pos)++ ] = (char)c;
    ++( handle->runtime_data.cmd_len );
    (void)mrdc_icli_sutil_usr_char_put(handle, (char)c);
}

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
i32 mrdc_icli_z_usr_cmd_get(IN  icli_session_handle_t   *handle)
{
    i32 c = 0;

    while (1) {
        /* get char */
        if ( mrdc_icli_sutil_usr_char_get_by_session(handle, &c) == FALSE ) {
            ICLI_PLAY_BELL;
            return ICLI_RC_ERR_EXPIRED;
        }

        /*
            avoid the cases of CR+LF or LF+CR
        */
        switch (c) {
        case ICLI_KEY_ENTER:
            if ( handle->runtime_data.prev_char == ICLI_NEWLINE ) {
                // reset previous input char
                handle->runtime_data.prev_char = 0;
                continue;
            }
            break;

        case ICLI_NEWLINE:
            if ( handle->runtime_data.prev_char == ICLI_KEY_ENTER ) {
                // reset previous input char
                handle->runtime_data.prev_char = 0;
                continue;
            }
            break;
        }

        /* get previous input char */
        handle->runtime_data.prev_char = c;

        /* reset TAB */
        if ( ICLI_NOT_(KEY_TAB, c) ) {
            mrdc_icli_sutil_tab_reset( handle );
        }

        /* process input char */
        switch (c) {
        case ICLI_KEY_FUNCTION0:
            /*
                function key is not supported
                consume next char
            */
            (void)mrdc_icli_sutil_usr_char_get(handle, _FKEY_WAIT_TIME, &c);
            ICLI_PLAY_BELL;
            continue;

        case ICLI_KEY_FUNCTION1:
            if ( mrdc_icli_sutil_usr_char_get(handle, _FKEY_WAIT_TIME, &c) == FALSE ) {
                /* invalid function key, skip it */
                continue;
            }
            switch ( c ) {
            case ICLI_FKEY1_UP:
                _fkey_prev_cmd( handle );
                break;

            case ICLI_FKEY1_DOWN:
                _fkey_next_cmd( handle );
                break;

            case ICLI_FKEY1_LEFT:
                (void)_fkey_backspace( handle );
                break;

            default:
                ICLI_PLAY_BELL;
                break;
            }
            continue;

        case ICLI_HYPER_TERMINAL:
            /* case ICLI_KEY_ESC: */

            /* get HT_BEGIN */
            if ( mrdc_icli_sutil_usr_char_get(handle, _FKEY_WAIT_TIME, &c) == FALSE ) {
                /* ICLI_KEY_ESC */
                (void)_fkey_del_line( handle );
                continue;
            }

            if ( ICLI_NOT_(HT_BEGIN, c) ) {
                continue;
            }

            /* get VT100 keys */
            if ( mrdc_icli_sutil_usr_char_get(handle, _FKEY_WAIT_TIME, &c) == FALSE ) {
                continue;
            }

            switch ( c ) {
            case ICLI_VKEY_UP:
                _fkey_prev_cmd( handle );
                break;

            case ICLI_VKEY_DOWN:
                _fkey_next_cmd( handle );
                break;

            case ICLI_VKEY_LEFT:
                (void)_fkey_backspace( handle );
                break;

            default:
                ICLI_PLAY_BELL;
                break;
            }
            continue;

        case ICLI_KEY_CTRL_('U'):
            (void)_fkey_del_line( handle );
            continue;

        case ICLI_KEY_BACKSPACE:
            /* case ICLI_KEY_CTRL_H: the same */
            (void)_fkey_backspace( handle );
            continue;

        case ICLI_KEY_TAB:
            _fkey_tab( handle );
            return ICLI_RC_OK;

        case ICLI_KEY_QUESTION:
            (void)mrdc_icli_sutil_usr_char_put(handle, '?');
            ICLI_PUT_NEWLINE;
            _fkey_question( handle );
            return ICLI_RC_OK;

        case ICLI_KEY_CTRL_('Z'):
            handle->runtime_data.after_cmd_act = ICLI_AFTER_CMD_ACT_GOTO_PREVIOUS_MODE;
            (void)mrdc_icli_sutil_usr_char_put(handle, '^');
            (void)mrdc_icli_sutil_usr_char_put(handle, 'Z');

        //fall through

        case ICLI_KEY_ENTER:
        case ICLI_NEWLINE:
            ICLI_PUT_NEWLINE;
            if ( handle->runtime_data.cmd_len ) {
                handle->runtime_data.exec_type = ICLI_EXEC_TYPE_CMD;
                handle->runtime_data.cmd[handle->runtime_data.cmd_len] = 0;
                return ICLI_RC_OK;
            } else {
                return ICLI_RC_ERR_EMPTY;
            }

        default :
            break;
        }

        /* put into cmd */
        _cmd_put(handle, c);
    }
}

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
)
{
    i32     c;

    if ( handle == NULL ) {
        T_E("handle == NULL\n");
        return ICLI_RC_ERR_PARAMETER;
    }

    /* print prompt */
    handle->runtime_data.put_str = Z_MORE_PROMPT;
    (void)mrdc_icli_sutil_usr_str_put( handle );

    /* get usr input */
    if ( mrdc_icli_sutil_usr_char_get_by_session(handle, &c) == FALSE ) {
        handle->runtime_data.alive = FALSE;
        handle->runtime_data.line_mode = ICLI_LINE_MODE_BYPASS;
        return ICLI_RC_ERR_EXPIRED;
    }

    /* put here to avoid ICLI_LINE_MODE_BYPASS */
    mrdc_icli_sutil_more_prompt_clear( handle );

    switch ( c ) {
    /* flooding */
    case 'c':
        handle->runtime_data.line_mode = ICLI_LINE_MODE_FLOOD;
        break;

        /* bypass */
#if 0
    case ICLI_KEY_ESC:
        /* flood all function keys */
        while ( mrdc_icli_sutil_usr_char_get(handle, _FKEY_WAIT_TIME, &c) ) {
            ;
        }

        //fall through
#endif
    case 'q':
    case ICLI_KEY_CTRL_('C'):
        handle->runtime_data.line_mode = ICLI_LINE_MODE_BYPASS;
        break;

    /* next page */
    case ICLI_KEY_SPACE:
    case ICLI_KEY_ENTER:
    case ICLI_NEWLINE:
    default:
        handle->runtime_data.line_mode = ICLI_LINE_MODE_PAGE;
        handle->runtime_data.line_cnt  = 0;
        break;
    }
    return ICLI_RC_OK;
}

void mrdc_icli_z_cmd_display(
    IN  icli_session_handle_t   *handle
)
{
    mrdc_icli_session_str_put(handle, handle->runtime_data.cmd);
    handle->runtime_data.cmd_len = mrdc_icli_str_len( handle->runtime_data.cmd );
    handle->runtime_data.cmd_pos = handle->runtime_data.cmd_len;
}

void mrdc_icli_z_line_clear(
    IN  icli_session_handle_t   *handle
)
{
    i32     i,
            j = handle->runtime_data.cmd_len;

    for ( i = 0; i < j; ++i ) {
        icli_platform_cursor_backspace( handle );
        --( handle->runtime_data.cmd_pos );
    }
}
