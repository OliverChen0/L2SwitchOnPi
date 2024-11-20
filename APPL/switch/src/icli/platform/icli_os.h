/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/
#ifndef __MRDC_ICLI_OS_H__
#define __MRDC_ICLI_OS_H__
//****************************************************************************
/*lint --e{429,454,455,456,459} */
/*lint -sem(icli_os_sema_take, thread_lock)   */
/*lint -sem(icli_os_sema_give, thread_unlock) */
/*
==============================================================================

    Include File

==============================================================================
*/
#include "icli_os_misc.h"

/*
==============================================================================

    Constant

==============================================================================
*/


/*
==============================================================================

    Macro

==============================================================================
*/
#define _ICLI_SEMA_TAKE()     icli_os_sema_take(__FILE__, __LINE__)
#define _ICLI_SEMA_GIVE()     icli_os_sema_give(__FILE__, __LINE__)

/*
==============================================================================

    Type

==============================================================================
*/
typedef i32 icli_thread_entry_cb_t(
    IN i32  data
);

typedef enum {
    ICLI_THREAD_PRIORITY_NORMAL,
    ICLI_THREAD_PRIORITY_HIGH,
} icli_thread_priority_t;

/*
==============================================================================

    Macro Definition

==============================================================================
*/

/*
==============================================================================

    Public Function

==============================================================================
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ICLI_TARGET

/**
 * \brief
 *      initialization
 *
 * \param
 *      n/a
 *
 * \return
 *      TRUE  - successful
 *      FALSE - failed
 */
BOOL icli_os_init(
    void
);

/*
    create thread
*/
BOOL icli_os_thread_create(
    IN  i32                     session_id,
    IN  const char              *name,
    IN  icli_thread_priority_t  priority,
    IN  icli_thread_entry_cb_t  *entry_cb,
    IN  i32                     entry_data
);

/*
    get my thread ID
*/
u32 icli_os_thread_id_get(
    void
);

/*
    sleep in milli-seconds
*/
void icli_os_sleep(
    IN u32  t
);

/**
 * \brief
 *      take semaphore
 *
 * \param
 *      file [IN]: file name
 *      line [IN]: line number
 *
 * \return
 *      n/a.
 */
void icli_os_sema_take(
    const char *const   file,
    const int           line
);

/**
 * \brief
 *      give semaphore
 *
 * \param
 *      file [IN]: file name
 *      line [IN]: line number
 *
 * \return
 *      n/a.
 */
void icli_os_sema_give(
    const char *const   file,
    const int           line
);

#endif // ICLI_TARGET

/*
    get the time elapsed from system start in milli-seconds
*/
u32 icli_os_current_time_get(
    void
);

#ifdef __cplusplus
}
#endif

//****************************************************************************
#endif //__MRDC_ICLI_OS_H__

