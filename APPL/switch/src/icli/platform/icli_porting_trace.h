/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

#ifndef __ICLI_PORTING_TRACE_H__
#define __ICLI_PORTING_TRACE_H__

#ifdef ICLI_TARGET

#include "mrdc_trace_api.h"
#include "mrdc_module_id.h"
#include "mrdc_trace_lvl_api.h"

#ifdef MRDC_TRACE_MODULE_ID
#undef MRDC_TRACE_MODULE_ID
#endif

#define MRDC_TRACE_MODULE_ID MRDC_MODULE_ID_ICLI
#include <mrdc_trace_api.h>

#else // ICLI_TARGET

#ifndef T_E
#define T_E(...) \
    printf("\nError: %s::%s()#%d: ", __FILE__, __FUNCTION__, __LINE__); \
    printf(__VA_ARGS__);
#endif

#ifndef T_W
#define T_W(...) \
    printf("Warning: %s::%s()#%d: ", __FILE__, __FUNCTION__, __LINE__); \
    printf(__VA_ARGS__);
#endif

#endif // ICLI_TARGET

#endif  /* __ICLI_PORTING_TRACE_H__ */

