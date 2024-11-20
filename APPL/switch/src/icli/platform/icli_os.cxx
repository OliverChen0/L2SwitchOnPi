/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

/*
==============================================================================

    Include File

==============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "icli_def.h"
#include "icli_os.h"
#include "icli_porting_trace.h"
#ifdef ICLI_TARGET
#include "mrdc_os_wrapper.h"
#endif

#ifdef ICLI_TARGET
#include "critd_api.h"
#endif

/*
==============================================================================

    Constant and Macro

==============================================================================
*/
#ifdef ICLI_TARGET
#define ICLI_THREAD_CNT         ICLI_SESSION_CNT
#endif

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
#ifdef ICLI_TARGET

/* thread */
static mrdc_handle_t          g_thread_handle[ICLI_THREAD_CNT];
static mrdc_thread_t          g_thread_block[ICLI_THREAD_CNT];

/* semaphore */
static critd_t      g_critd;

#endif // ICLI_TARGET

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
)
{
    /* create semaphore */
    critd_init(&g_critd, "ICLI", MRDC_MODULE_ID_ICLI, CRITD_TYPE_MUTEX);

    return TRUE;
}
/*
    create thread
*/
BOOL icli_os_thread_create(
    IN  i32                     session_id,
    IN  const char              *name,
    IN  icli_thread_priority_t  priority,
    IN  icli_thread_entry_cb_t  *entry_cb,
    IN  i32                     entry_data
)
{
    mrdc_thread_prio_t thread_prio;

    if ( session_id < 0 || session_id >= ICLI_THREAD_CNT ) {
        return FALSE;
    }

    thread_prio = MRDC_THREAD_PRIO_DEFAULT;
    if (priority == ICLI_THREAD_PRIORITY_HIGH) {
        thread_prio = MRDC_THREAD_PRIO_HIGHER;
    }

    mrdc_thread_create(thread_prio,
                       (mrdc_thread_entry_f *)entry_cb,
                       (mrdc_addrword_t)((u64)entry_data),
                       name,
                       nullptr,
                       0,
                       &(g_thread_handle[session_id]),
                       &(g_thread_block[session_id]));

    return TRUE;
}

/*
    get my thread ID
*/
u32 icli_os_thread_id_get(
    void
)
{
    return (u32)mrdc_thread_self();
}

/*
    sleep in milli-seconds
*/
void icli_os_sleep(
    IN u32  t
)
{
    MRDC_OS_MSLEEP( t );
}

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
void icli_os_sema_take(const char *const file, const int line)
{
    critd_enter(&g_critd, file, line);
}

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
void icli_os_sema_give( const char *const file, const int line)
{
    critd_exit(&g_critd, file, line);
}

#endif // ICLI_TARGET

/*
    get the time elapsed from system start in milli-seconds
*/
u32 icli_os_current_time_get(
    void
)
{
    struct timespec     tp;

    if ( clock_gettime(CLOCK_MONOTONIC, &tp) == -1 ) {
        T_E("failed to get system up time\n");
        return 0;
    }
    return tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
}

