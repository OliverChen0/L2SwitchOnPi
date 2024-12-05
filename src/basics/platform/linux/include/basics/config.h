#ifndef _INCLUDE_MRDC_BASICS_CONFIG_H
#define _INCLUDE_MRDC_BASICS_CONFIG_H

// Use mrdc unified API header files to get API types
#define VTSS_USE_API_HEADERS

// #define VTSS_SIZEOF_VOID_P 8

/* #if ((ULONG_MAX) == (UINT_MAX)) */
/* #define VTSS_SIZEOF_VOID_P 4 */
/* #else */
/* #define VTSS_SIZEOF_VOID_P 8 */
/* #endif */

#if __GNUC__
#if __x86_64__ || __ppc64__ || __aarch64__
#define VTSS_SIZEOF_VOID_P 8
#else
#define VTSS_SIZEOF_VOID_P 4
#endif
#endif


#endif  // _INCLUDE_MRDC_BASICS_CONFIG_H
