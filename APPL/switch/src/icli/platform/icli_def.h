/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/
#ifndef __ICLI_DEF_H__
#define __ICLI_DEF_H__
//****************************************************************************
/*
==============================================================================

    Include File

==============================================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/** \brief IPv4 address/mask */
typedef unsigned int mrdc_ip_t;

#ifdef ICLI_TARGET

#include "main_types.h"
#include "vtss/appl/vlan.h"
#include "main_types.h"
#include "main.h"
#include "mrdc_trace_api.h"
#include "hal_data_api.h"

#else // ICLI_TARGET

/*

    Note:
    The following types are used by ICLI tool that run on LINUX.
    Because when compiling for LINUX, the above include files, ex,
    main_types.h, main_types.h and mrdc_trace_api.h, will introduce errors
    that can not be fixed for LINUX, THEREFORE, they are duplicated here.

*/

typedef signed char         i8;   /*  8-bit signed */
typedef signed short        i16;  /* 16-bit signed */
typedef signed int          i32;  /* 32-bit signed */
typedef signed long long    i64;  /* 64-bit signed */

typedef unsigned char       u8;   /*  8-bit unsigned */
typedef unsigned short      u16;  /* 16-bit unsigned */
typedef unsigned int        u32;  /* 32-bit unsigned */
typedef unsigned long long  u64;  /* 64-bit unsigned */
typedef unsigned char       BOOL; /* Boolean implemented as 8-bit unsigned */

typedef int                 mrdc_rc;

/** \brief IPv4 address/mask */
typedef mrdc_ip_t mrdc_ipv4_t;

/** \brief IPv6 address/mask */
typedef struct {
    u8 addr[16];
} mrdc_ipv6_t;

/* NOTE: This type may be used directly in SNMP
 * InetAddressType types.  */

/** \brief IP address type */
typedef enum {
    MRDC_IP_TYPE_NONE = 0, /**< Matches "InetAddressType_unknown" */
    MRDC_IP_TYPE_IPV4 = 1, /**< Matches "InetAddressType_ipv4"    */
    MRDC_IP_TYPE_IPV6 = 2, /**< Matches "InetAddressType_ipv6"    */
} mrdc_ip_type_t;

/** \brief Either an IPv4 or IPv6 address  */
typedef struct {
    mrdc_ip_type_t  type; /**< Union type */
    union {
        mrdc_ipv4_t ipv4; /**< IPv4 address */
        mrdc_ipv6_t ipv6; /**< IPv6 address */
    } addr;               /**< IP address */
} mrdc_ip_addr_t;

typedef struct {
    mrdc_ipv6_t address;     // Network address
    u32         prefix_size; // Prefix size
} mrdc_ipv6_network_t;

/** \brief MAC Address */
typedef struct {
    u8 addr[6];   /* Network byte order */
} mrdc_mac_t;

#endif // ICLI_TARGET

typedef u64 icli_addrword_t;

/*
==============================================================================

    Constant

==============================================================================
*/
#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef NULL
#define NULL    0
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

/*
==============================================================================

    ICLI spec

==============================================================================
*/
/*
    + 512  : 2013/03/11 10:21
    + 1024 : 2014/11/25 09:45
*/
#ifdef MRDC_PRODUCT_PICASSO
#define ICLI_CMD_CNT                    3600
#else
#define ICLI_CMD_CNT                    3328
#endif

#ifdef MRDC_PRODUCT_RACOON
#define ICLI_SESSION_CNT                5
#define ICLI_SESSION_DEFAULT_CNT        5
#else
#define ICLI_SESSION_CNT                17
#define ICLI_SESSION_DEFAULT_CNT        17
#endif

#define ICLI_SESSION_ID_NONE            0xFFffFFff
#define ICLI_CMD_WORD_CNT               512
#define ICLI_RANGE_LIST_CNT             128
#define ICLI_HISTORY_CMD_CNT            32
#define ICLI_PARAMETER_MEM_CNT          512
#define ICLI_NODE_PROPERTY_CNT          4096
#define ICLI_RUNTIME_CNT                ICLI_SESSION_CNT
#define ICLI_RANDOM_OPTIONAL_DEPTH      3
#define ICLI_RANDOM_OPTIONAL_CNT        ICLI_CMD_WORD_CNT
#define ICLI_BYWORD_MAX_LEN             80
#define ICLI_HELP_MAX_LEN               600
#define ICLI_CWORD_MAX_CNT              256

#define ICLI_USERNAME_MAX_LEN           32
#define ICLI_PASSWORD_MAX_LEN           32
#define ICLI_AUTH_MAX_CNT               5

#define ICLI_DEFAULT_PRIVILEGED_LEVEL   ICLI_PRIVILEGE_2

#define ICLI_STR_MAX_LEN                4096
#define ICLI_PUT_MAX_LEN                (ICLI_STR_MAX_LEN + 512)
#define ICLI_ERR_MAX_LEN                ICLI_PUT_MAX_LEN
#define ICLI_FILE_MAX_LEN               256
#define ICLI_PROMPT_UNINTERPRETED_MAX_LEN 32
#define ICLI_PROMPT_INTERPRETED_MAX_LEN 48 /* Could get longer, but we have to stop it somewhere */
#define ICLI_MODE_PROMPT_MAX_LEN        32
#define ICLI_DIGIT_MAX_LEN              64
#define ICLI_VALUE_STR_MAX_LEN          256
#define ICLI_DEFAULT_WAIT_TIME          (10 * 60)  //in seconds
#define ICLI_MODE_MAX_LEVEL             8
#define ICLI_BANNER_MAX_LEN             255
#define ICLI_MULTILINE_BUFFER_MAX_LEN   256

#define ICLI_HOST_NAME_MAX_LEN          255
#define ICLI_DOMAIN_NAME_MAX_LEN        253
#define ICLI_DEV_NAME_MAX_LEN           ICLI_HOST_NAME_MAX_LEN

#define ICLI_DEFAULT_WIDTH              80

// Set ICLI_MAX_WIDTH to a reasonable value, because deleting a
// whole line is done one character at the time
// (e.g. see mrdc_icli_session_c.c). If the width is e.g.
// set to 0xFFFFFF it is taking forever to delete a whole line
#define ICLI_MAX_WIDTH                  2000
#define ICLI_MIN_WIDTH                  40

#define ICLI_DEFAULT_LINES              24
#define ICLI_MIN_LINES                  3

#ifdef ICLI_TARGET
#define ICLI_MIN_VLAN_ID                MRDC_APPL_VLAN_ID_MIN
#define ICLI_MAX_VLAN_ID                MRDC_APPL_VLAN_ID_MAX
#else
#define ICLI_MIN_VLAN_ID                1
#define ICLI_MAX_VLAN_ID                4095
#endif

#define ICLI_MIN_LOOPBACK_ID            1
#define ICLI_MAX_LOOPBACK_ID            8 // LOOPBACK�ӿ�֧�ֵ�������
/* The valid range of virtual link interface ID */
#define ICLI_MIN_VLINK_ID               1
#define ICLI_MAX_VLINK_ID               (100000000 - 1)

#define ICLI_MIN_SWICTH_ID              1
#define ICLI_MAX_SWICTH_ID              16

#define ICLI_MAX_YEAR                   2037
#define ICLI_MIN_YEAR                   1970
#define ICLI_YEAR_MAX_MONTH             12
#define ICLI_YEAR_MIN_MONTH             1

#define ICLI_LOCATION_MAX_LEN           32

#define ICLI_HMAC_MD5_MAX_LEN           16

#if 0 /* Bugzilla#14129 - remove debug level */
#define ICLI_DEBUG_PRIVI_CMD            "_debug_privilege_"
#endif

/*
    default properties of enable privilege password
*/
#define ICLI_DEFAULT_ENABLE_PASSWORD    "enable"
#define ICLI_ENABLE_PASSWORD_RETRY      3
#define ICLI_ENABLE_PASSWORD_WAIT       (30 * 1000) // milli-second

/* default device name */
#define ICLI_DEFAULT_DEVICE_NAME        ""

/*
    the following syntax symbol is used to customize the command
    reference guide.
*/
#define ICLI_HTM_MANDATORY_BEGIN        '{'
#define ICLI_HTM_MANDATORY_END          '}'
#define ICLI_HTM_LOOP_BEGIN             '('
#define ICLI_HTM_LOOP_END               ')'
#define ICLI_HTM_OPTIONAL_BEGIN         '['
#define ICLI_HTM_OPTIONAL_END           ']'
#define ICLI_HTM_VARIABLE_BEGIN         '<'
#define ICLI_HTM_VARIABLE_END           '>'

/*
    variable input style
*/
#define ICLI_VARIABLE_STYLE             0

/*
    support random optional or not
*/
#define ICLI_RANDOM_OPTIONAL            1

/*
    support random optional must number '}*1'
*/
#define ICLI_RANDOM_MUST_NUMBER         1
#define ICLI_RANDOM_MUST_CNT            32

/*
    wildcard symbol for interface port list
*/
#define ICLI_INTERFACE_WILDCARD         "*"

#define ICLI_MAX_SWITCH_ID              33
#define ICLI_MAX_PORT_ID                65

/*
    support privilege per command
*/
#define ICLI_PRIV_CMD_MAX_LEN           128
#define ICLI_PRIV_CMD_MAX_CNT           64

/* ues tag BYWORD or not */
#define ICLI_CMD_BYWORD_USE             0

#define ICLI_STUB_SERVER_PORT           41907

/* DPL value range */
#define ICLI_DPL_MIN                    0
#ifdef ICLI_TARGET
#define ICLI_DPL_MAX                    (fast_cap(HAL_CAP_QOS_DPL_CNT) - 1)
#else
#define ICLI_DPL_MAX                    3
#endif

#if 1 /* CP, 2014-09-24 15:44, Bugzilla#16386 - ICLI new feature, Loop */
#define ICLI_LOOP_SYNTAX                1
#endif

#define ICLI_URL_MAX_LEN                512
#define ICLI_FILE_NAME_MAX_LEN          63

#define ICLI_URL_PROTOCOL_MAX_LEN       31
#define ICLI_URL_USERNAME_MAX_LEN       63
#define ICLI_URL_PASSWORD_MAX_LEN       63
#define ICLI_URL_HOST_MAX_LEN           63
#define ICLI_URL_PORT_MAX_LEN           31
#define ICLI_URL_PATH_MAX_LEN           255

#if 1 /* 2014-12-24 13:30, Bugzilla#17511 - generic URL syntax */
#define ICLI_URL_GENERIC_SYNTAX         0
#endif

/*
    Command mode
*/
typedef enum {
    ICLI_CMD_MODE_EXEC,
    ICLI_CMD_MODE_GLOBAL_CONFIG,
    ICLI_CMD_MODE_CONFIG_VLAN,
    ICLI_CMD_MODE_INTERFACE_PORT_LIST,
    ICLI_CMD_MODE_INTERFACE_VLAN,
    ICLI_CMD_MODE_INTERFACE_LOOPBACK,
    ICLI_CMD_MODE_CONFIG_LINE,
    ICLI_CMD_MODE_IPMC_PROFILE,
    ICLI_CMD_MODE_SNMPS_HOST,
    ICLI_CMD_MODE_STP_AGGR,
    ICLI_CMD_MODE_DHCP_POOL,
    ICLI_CMD_MODE_JSON_NOTI_HOST,
    ICLI_CMD_MODE_LLAG,
    ICLI_CMD_MODE_QOS_INGRESS_MAP,
    ICLI_CMD_MODE_QOS_EGRESS_MAP,
    ICLI_CMD_MODE_CFM_MD,
    ICLI_CMD_MODE_CFM_MA,
    ICLI_CMD_MODE_CFM_MEP,
    ICLI_CMD_MODE_APS,
    ICLI_CMD_MODE_ERPS,
    ICLI_CMD_MODE_IEC_MRP,
    ICLI_CMD_MODE_REDBOX,
    ICLI_CMD_MODE_MULTILINE,
    ICLI_CMD_MODE_CONFIG_CPU_PORT,
    ICLI_CMD_MODE_CONFIG_ROUTER_OSPF,
    ICLI_CMD_MODE_CONFIG_ROUTER_OSPF6,
    ICLI_CMD_MODE_CONFIG_ROUTER_RIP,
    ICLI_CMD_MODE_CONFIG_ROUTER_KEYCHAIN,
    ICLI_CMD_MODE_STREAM,
    ICLI_CMD_MODE_TSN_PSFP_FLOW_METER,
    ICLI_CMD_MODE_TSN_PSFP_STREAM_FILTER,
    ICLI_CMD_MODE_TSN_PSFP_STREAM_GATE,
    ICLI_CMD_MODE_TSN_FRER,

    //------- add above
    ICLI_CMD_MODE_MAX
} icli_cmd_mode_t;

/*
    Privilege
*/
typedef enum {
    ICLI_PRIVILEGE_0,
    ICLI_PRIVILEGE_1,
    ICLI_PRIVILEGE_2,
    ICLI_PRIVILEGE_3,
    ICLI_PRIVILEGE_4,
    ICLI_PRIVILEGE_5,
    ICLI_PRIVILEGE_6,
    ICLI_PRIVILEGE_7,
    ICLI_PRIVILEGE_8,
    ICLI_PRIVILEGE_9,
    ICLI_PRIVILEGE_10,
    ICLI_PRIVILEGE_11,
    ICLI_PRIVILEGE_12,
    ICLI_PRIVILEGE_13,
    ICLI_PRIVILEGE_14,
    ICLI_PRIVILEGE_15,
    //------- add above
#if 0 /* Bugzilla#14129 - remove debug level */
    ICLI_PRIVILEGE_DEBUG,
#endif
    ICLI_PRIVILEGE_MAX,
} icli_privilege_t;

/*
==============================================================================

    Macro Definition

==============================================================================
*/

/*
==============================================================================

    Type

==============================================================================
*/

//****************************************************************************
#endif //__ICLI_DEF_H__
