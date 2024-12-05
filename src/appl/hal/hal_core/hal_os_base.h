

#ifndef _HAL_OS_BASE_H_
#define _HAL_OS_BASE_H_

#ifndef __KERNEL__

#include <endian.h>
#include <asm/byteorder.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

/* data type definition for HAL */
typedef char            CHAR;   /**<  8-bit signed */
typedef short           INT16;  /**< 16-bit signed */
typedef int             INT32;  /**< 32-bit signed */
typedef long long       INT64;  /**< 64-bit signed */

typedef unsigned char   UINT8;  /**<  8-bit unsigned */
typedef unsigned char   UCHAR;  /**<  8-bit unsigned */
typedef unsigned short  UINT16;  /**< 16-bit unsigned */
typedef unsigned short  USHORT;  /**< 16-bit unsigned */
typedef unsigned int    UINT32;  /**< 32-bit unsigned */
typedef unsigned long   ULONG;    /**< 32-bit unsigned */
typedef unsigned long long UINT64;/**< 64-bit unsigned */

/*布尔类型统一使用小写的 bool 类型*/


#define HAL_OS_NTOHL(x) __be32_to_cpu(x) /**< Convert a 32-bit value from network to host order */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h> /* for memset and friend */

#include <errno.h>
#include <time.h>
#include <sys/time.h>

#ifndef _HAL_MAIN_TYPES_H_
/** Sleep for \param nsec nanoseconds */
#define HAL_NSLEEP(nsec)                                \
{                                                       \
    struct timespec ts;                                 \
    ts.tv_sec = 0;                                      \
    ts.tv_nsec = nsec;                                  \
    while(nanosleep(&ts, &ts) == -1 && errno = EINTR){  \
    }                                                   \
}

/** Sleep for \param msec milliseconds */
#define HAL_MSLEEP(msec)                                        \
{                                                               \
    struct timespec ts;                                         \
    ts.tv_sec = msec / 1000;                                    \
    ts.tv_nsec = (msec % 1000) * 1000000;                       \
    while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {        \
    }                                                           \
}

typedef struct {
    struct timeval timeout;  /** time out */
    struct timeval now;      /** time right now */
} hal_mtimer_t;

#define HAL_MTIMER_START(timer,msec) { \
    (void) gettimeofday(&((timer)->timeout),NULL);   \
    (timer)->timeout.tv_usec+=msec*1000; \
    if ((timer)->timeout.tv_usec>=1000000) { (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000; (timer)->timeout.tv_usec%=1000000; } \
} /**< Start timer */

#define HAL_MTIMER_TIMEOUT(timer) (gettimeofday(&((timer)->now),NULL)==0 && timercmp(&((timer)->now),&((timer)->timeout),>)) /**< Timer timeout */

#endif /* _HAL_MAIN_TYPES_H_ */

#define HAL_MTIMER_CANCEL(timer) /** No action in this implementation */

/** Time of day struct */
typedef struct 
{
    time_t sec; /** time of day in seconds */
} hal_timeofday_t;

/** Time of day macro */
#define HAL_TIME_OF_DAY(tod) {         \
    struct timeval tve; \
    (void)gettimeofday(&tve,NULL); \
    tod.sec = tve.tv_sec;          \
}

/**
 * HAL_DIV64 - perform 64/32 bit division yelding 32 bit (at least) output
 */
#define HAL_DIV64(dividend, divisor) ((dividend) / (divisor))
/**
 * HAL_MOD64 - perform 64/32 bit modulus yelding 32 bit (at least) output
 */
#define HAL_MOD64(dividend, divisor) ((dividend) % (divisor))
/**
 * HAL_LABS - perform abs() on long
 */
#define HAL_LABS(arg)                labs(arg)

/**
 * HAL_LLABS - perform abs() on long long
 */
#define HAL_LLABS(arg)               llabs(arg)

#else

/** define __KERNEL__ */

#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/math64.h>

#define HAL_OS_NTOHL(x) __be32_to_cpu(x) /**< Convert a 32-bit value from network to host order */

#define HAL_HAVE_U_TYPES       /* Namespace coexistance - use the ones from the kernel */

typedef struct {
    struct timeval timeout;
    struct timeval now;
} hal_mtimer_t;

#define HAL_NSLEEP(nsec) ndelay(nsec) /**< Sleep for "msec" milliseconds */
#define HAL_MSLEEP(msec) mdelay(msec) /**< Sleep for "nsec" nanoseconds  */

#define HAL_MTIMER_START(timer,msec) {                                 \
        (void) do_gettimeofday(&((timer)->timeout));                     \
        (timer)->timeout.tv_usec+=msec*1000;                            \
        if ((timer)->timeout.tv_usec>=1000000) {                        \
            (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000;  \
            (timer)->timeout.tv_usec%=1000000;                          \
        }                                                               \
    }

static __always_inline int hal_mtimer_timeout(hal_mtimer_t *t)
{
    do_gettimeofday(&t->now);
    if(timeval_compare(&t->now, &t->timeout) > 0)
        return true;
    udelay(1);                  /* Be nice */
    return false;
}

#define HAL_MTIMER_TIMEOUT(timer) hal_mtimer_timeout(timer)

#define HAL_MTIMER_CANCEL(timer) /* No action in this implementation. */

#define HAL_DIV64 div64_u64

static inline u32 hal_mod64(u64 div, u32 base)
{
    return do_div(div, base);   /* Remainder *returned* by do_div */
}

#define HAL_MOD64 vtss_mod64

#define HAL_LABS(arg)                __builtin_labs(arg)

static __always_inline long long
hal_llabs(long long j)
{
    return (j < 0 ? -j : j);
}

#define HAL_LLABS(arg)               hal_llabs(arg)

/******************************************************************************/
// PLATFORM SECTION
/******************************************************************************/

#include <asm/io.h>

/******************************************************************************/
// TASK SWITCH/INTERRUPT SECTION
/******************************************************************************/

#include <linux/interrupt.h>

/*
 * HAL_OS_SCHEDULER_FLAGS
 * HAL_OS_SCHEDULER_LOCK(flags)
 * HAL_OS_SCHEDULER_UNLOCK(flags)
 *   These functions are called by API code that consists of a user-level part
 *   and a deferred interrupt handler part.
 *   Only the user-level part will call the HAL_OS_SCHEDULER_LOCK()/UNLOCK()
 *   functions, since it is assumed that the deferred interrupt handler will
 *   have atomic access throughout its execution.
 *   Each module within the API that contains such functionality will have
 *   an option to call either the HAL_OS_SCHEDULER_(UN)LOCK() functions
 *   or the HAL_OS_INTERRUPT_DISABLE()/RESTORE() functions.
 */
#define HAL_OS_SCHEDULER_FLAGS         unsigned long
#define HAL_OS_SCHEDULER_LOCK(flags)   local_irq_save(flags)
#define HAL_OS_SCHEDULER_UNLOCK(flags) local_irq_restore(flags)

/*
 * HAL_OS_INTERRUPT_FLAGS
 * HAL_OS_INTERRUPT_DISABLE(flags)
 * HAL_OS_INTERRUPT_RESTORE(flags)
 *   These functions are called by API code that consists of a user-level part
 *   and an interrupt handler part executing directly in interrupt context.
 *   Only the user-level part will call the HAL_OS_INTERRUPT_DISABLE()/RESTORE()
 *   functions, since it is assumed that the interrupt handler will
 *   have atomic access throughout its execution.
 *   Each module within the API that contains such functionality will have
 *   an option to call either the HAL_OS_SCHEDULER_(UN)LOCK() functions
 *   or the HAL_OS_INTERRUPT_DISABLE()/RESTORE() functions.
 */
#define HAL_OS_INTERRUPT_FLAGS          NOT_NEEDED
#define HAL_OS_INTERRUPT_DISABLE(flags) NOT_NEEDED
#define HAL_OS_INTERRUPT_RESTORE(flags) NOT_NEEDED

#endif /** __KERNEL__ */


/**
 * Request OS to allocate size bytes of memory.
 *
 * The first argument is the number of bytes that must
 * be allocated. Type is size_t.
 *
 * The second argument is a mask of flags that the
 * implementation must obey. Type is vtss_mem_flags_t.
 *
 * The returned pointer should be at least 8-byte aligned,
 * to make it suitable for a struct.
 */
#ifdef __KERNEL__
#define HAL_OS_MALLOC(size, flags) vmalloc(size)


#else
#define HAL_OS_MALLOC(size, flags) malloc(size)
#endif

/**
 * Request OS to free memory previously allocated with
 * HAL_OS_MALLOC().
 *
 * The first argument is the pointer previously
 * obtained with a call to HAL_OS_MALLOC(). Type is
 * void *.
 *
 * The second argument is a mask of flags identical to
 * those passed to HAL_OS_MALLOC() when the memory
 * was requested.
 */
#ifdef __KERNEL__
#define HAL_OS_FREE(ptr, flags) vfree(ptr)
#else
#define HAL_OS_FREE(ptr, flags) free(ptr)
#endif

/**
 * Wrap of call to rand() defined in stdlib.h
 */
#define HAL_OS_RAND() rand()

#define HAL_MEMSET(s, c, n) memset(s, c, n)
#define HAL_MEMCMP(s, c, n) memcmp(s, c, n)
#define HAL_MEMCPY(s, c, n) memcpy(s, c, n)

#define HAL_STRLEN(s) strlen(s)
#define HAL_STRCPY(sd, ss) strcpy(sd, ss)
#define HAL_SPRINTF(...) sprintf(__VA_ARGS__)
#define HAL_SNPRINTF(...) snprintf(__VA_ARGS__)

#define HAL_TOUPPER(arg) (toupper(arg))
#define HAL_TOLOWER(arg) (toupper(arg))

#define Assert(Cond) if (!(Cond)) abort()

#define HAL_ASSERT(arg) {\
    Assert(arg);\
}


#endif /* _HAL_OS_BASE_H_ */
