/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
******************************************************************************

    Revision history
    > CP.Wang, 2012/09/27 12:19
        - create

******************************************************************************
*/
#ifndef __ICLI_CMD_FUNC_H__
#define __ICLI_CMD_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
******************************************************************************

    Public Function

******************************************************************************
*/
BOOL icli_config_go_to_exec_mode(
    IN u32 session_id
);

void icli_config_help_print(u32 session_id);
i32 icli_config_exec_do(u32 session_id, char *command);

BOOL icli_config_user_str_get(
    IN  u32     session_id,
    IN  i32     max_len,
    OUT char    *user_str

);

//****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //__ICLI_CMD_FUNC_H__
