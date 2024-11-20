/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

#ifndef _ICLI_CONFIG_FUNCTIONS_H_
#define _ICLI_CONFIG_FUNCTIONS_H_

#include "icli_api.h"

mrdc_rc icli_multiline_input_start(u32 session_id,
                                   icli_multiline_callback_t cb,
                                   const char *line);

mrdc_rc icli_multiline_process_line(u32 session_id, const char *line);

BOOL icli_multiline_parsing_begin(u32 session_id, const char *line);
BOOL icli_multiline_parsing_complete(u32 session_id, const char *line);

#endif // _ICLI_CONFIG_FUNCTIONS_H_

