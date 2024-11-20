/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/

#ifndef __ICLI_PORTING_UTIL_H__
#define __ICLI_PORTING_UTIL_H__

#include "port_iter.hxx"
#include "mrdc_icli_type.h"
#include <vtss/appl/types.h>


//****************************************************************************

/*
******************************************************************************

    Type

******************************************************************************
*/

/*
******************************************************************************

    Constant

******************************************************************************
*/
#define ICLI_PORTING_STR_BUF_SIZE   80
#define ICLI_VLAN_USER_STR_BUF_SIZE  30
/*
******************************************************************************

    Macro Definition

******************************************************************************
*/

/*
******************************************************************************

    Public Function

******************************************************************************
*/
/* Get enabled/disabled text */
const char *icli_bool_txt(BOOL enabled);

/* Get port information text */
char *icli_port_info_txt(mrdc_usid_t usid, mrdc_port_no_t uport, char *str_buf_p);
char *icli_port_info_txt_short(mrdc_usid_t usid, mrdc_port_no_t uport, char *str_buf_p);

/* Display port header text with optional new line before and after */
void icli_port_header(i32 session_id, mrdc_isid_t usid, mrdc_port_no_t uport, const char *txt, BOOL pre, BOOL post);

/* Display underlined header with new line before and after */
void icli_header(i32 session_id, const char *txt, BOOL post);

/* Display header text with under line (including underlining of spaces) */
void icli_table_header(i32 session_id, const char *txt);

/* Display header text with under line */
void icli_parm_header(i32 session_id, const char *txt);

/* Display two counters in one row */
void icli_stats(i32 session_id, const char *counter_str_1_p, const char *counter_str_2_p, u32 counter_1, u32 counter_2);

void icli_print_port_info_txt(i32 session_id, mrdc_isid_t usid, mrdc_port_no_t uport);

/* Port list string */
// TODO_DATA: mesa_port_list_t适配完成删掉
#if !defined(INCLUDE_VTSS_LIB)
char *icli_iport_list_txt(mesa_port_list_t &port_list, char *buf);
int icli_rangelist2iportlist(icli_unsigned_range_t *icli_range_list_p, mesa_port_list_t &port_list);
int icli_porttypelist2iportlist(mrdc_usid_t usid, icli_stack_port_range_t *port_type_list_p, mesa_port_list_t &port_list);
char *icli_port_list_info_txt(mrdc_isid_t isid, mesa_port_list_t &port_list, char *str_buf_p, BOOL short_form);
#endif
char *icli_iport_list_txt(mrdc_port_list_t &port_list, char *buf);

const char *icli_time_txt(time_t time_val);


/* Returns a MAC address in a ICLI style */
char *icli_mac_txt(const uchar *mac, char *buf);
//****************************************************************************

#define VTSS_ICLI_RANGE_FOREACH(LIST, VAR_TYPE, VAR_NAME)               \
{                                                                       \
    u32 MACRO_VARIABLE_outer ## LIST;                                   \
    VAR_TYPE VAR_NAME;                                                  \
    for (MACRO_VARIABLE_outer ## LIST = 0;                              \
         MACRO_VARIABLE_outer ## LIST < LIST->cnt;                      \
         ++MACRO_VARIABLE_outer ## LIST) {                              \
        for (VAR_NAME = LIST->range[MACRO_VARIABLE_outer ## LIST].min;  \
             VAR_NAME <= LIST->range[MACRO_VARIABLE_outer ## LIST].max; \
             ++VAR_NAME)
#define VTSS_ICLI_RANGE_FOREACH_END() }}

/* Convert to iport_list from icli_range_list.
   Return value -
    0 : success
    -1: fail - invalid parameter
    -2: fail - iport_list array size overflow */
int icli_rangelist2iportlist(icli_unsigned_range_t *icli_range_list_p, mrdc_port_list_t &port_list);

/* Convert to iport_list from icli_port_type_list.
   Return value -
    0 : success
    -1: fail - invalid parameter
    -2: fail - iport_list array size overflow
    1 : fail - different switch ID existing in port type list */
int icli_porttypelist2iportlist(mrdc_usid_t usid, icli_stack_port_range_t *port_type_list_p, mrdc_port_list_t &port_list);

/** \brief Convert a boolean array of port members to a textual representation.
 *  \param short_form [IN] When TRUE, prints e.g. "Gi 3" rather than "GigabitEthernet 3"
 */
char *icli_port_list_info_txt(mrdc_isid_t isid, mrdc_port_list_t &port_list, char *str_buf_p, BOOL short_form);

/* Is uport member of plist? */
BOOL icli_uport_is_included(mrdc_usid_t usid, mrdc_port_no_t uport, icli_stack_port_range_t *plist);

/* Is usid member of plist? */
BOOL icli_usid_is_included(mrdc_usid_t usid, icli_stack_port_range_t *plist);

/*
 * Initialize iCLI switch iterator to iterate over all switches in USID order.
 * Use icli_switch_iter_getnext() to filter out non-selected, non-existing switches.
 */
mrdc_rc icli_switch_iter_init(switch_iter_t *sit);

/*
 * iCLI switch iterator. Returns selected switches.
 * If list == NULL, all existing switches are returned.
 * Updates sit->first to match first selected switch.
 * NOTE: sit->last is not updated and therefore unreliable.
 */
BOOL icli_switch_iter_getnext(switch_iter_t *sit, icli_stack_port_range_t *list);

/*
 * Initialize iCLI port iterator to iterate over all ports in uport order.
 * Use icli_port_iter_getnext() to filter out non-selected ports.
 */
mrdc_rc icli_port_iter_init(port_iter_t *pit, mrdc_isid_t isid, u32 flags);

/*
 * iCLI port iterator. Returns selected ports.
 * If list == NULL, all existing ports are returned.
 * Updates pit->first to match first selected port.
 * NOTE: pit->last is not updated and therefore unreliable.
 */
BOOL icli_port_iter_getnext(port_iter_t *pit, icli_stack_port_range_t *list);


void icli_port_iter_add_port(u32 type, mrdc_isid_t isid, mrdc_port_no_t iport,
                             mrdc_port_no_t uport);


/**
 * \brief Function for at runtime getting information about stacking
 *
 * \param session_id [IN] The session id use by iCLI print.
 * \param ask [IN]  Asking
 * \param runtime [IN]  Pointer to where to put the "answer"
 * \return TRUE is runtime contains valid information.
 **/
BOOL icli_runtime_stacking(u32                session_id,
                           icli_runtime_ask_t ask,
                           icli_runtime_t     *runtime);


// Determine run-time presence based on capability
BOOL icli_present_cap(icli_runtime_ask_t ask,
                      icli_runtime_t     *runtime,
                      int                cap);

// Determine run-time presence based on PHY capability
BOOL icli_present_phy_cap(icli_runtime_ask_t ask, icli_runtime_t *runtime, mepa_phy_cap_t cap);

/* Print two counters (RX and TX) in columns  */
// IN - Session_Id - For iCLI printing
//      rx_name    - RX counter name - Set to NULL if there is no RX counter
//      tx_name    - TX counter name - Set to NULL if there is no TX counter
//      rx_val     - RX counter value
//      tx_val     - TX counter value
void icli_cmd_stati(i32 session_id, const char *rx_name, const char *tx_name, u64 rx_val, u64 tx_val);

/**
 * \brief Check configurable switches if existing.
 *
 * \param session_id                          [IN]     - The ICLI session ID.
 * \param port_list_p                         [IN&OUT] - Pointer to structure that contains the port range information.
 * \param omit_non_exist                      [IN]     - If it is needed to ommit non-existing switches in the port range information.
 * \parm                                                 The parameter of 'port_list_p' will be updaetd if this value is TRUE.
 * \param alert_configurable_but_non_existing [IN]     - If it is needed to display the alert message alert message(configurable but non-existing) on ICLI session.
 *
 * \return TRUE  - All switches are configurable and existing in the port range information.
 * \return FALSE - Found at least one non-existing switch or it isn't configurable switch in the port range information.
 **/
BOOL icli_cmd_port_range_exist(u32 session_id, icli_stack_port_range_t *port_list_p, BOOL omit_non_exist, BOOL alert_configurable_but_non_existing);

/**
 * \brief Check configurable switche if existing.
 *
 * \param session_id                          [IN] - The ICLI session ID.
 * \param usid                                [IN] - User switch ID.
 * \param alert_not_configurable              [IN] - If it is needed to display the alert message(not configurable switch) on ICLI session.
 * \param alert_configurable_but_non_existing [IN] - If it is needed to display the alert message(configurable but non-existing switch) on ICLI session.
 *
 * \return TRUE  - The switch is configurable and existing.
 * \return FALSE - The switch isn't configurable or it is non-existing.
 **/
BOOL icli_cmd_switch_exist(u32 session_id, mrdc_usid_t usid, BOOL alert_not_configurable, BOOL alert_configurable_but_non_existing);

/**
 * \brief Check configurable switches if existing.
 *
 * \param session_id                          [IN]     - The ICLI session ID.
 * \param switch_list_p                       [IN&OUT] - Pointer to structure that contains the switch range information.
 * \param omit_non_exist                      [IN]     - If it is needed to ommit non-existing switches in the switch range information.
 * \parm                                                 The parameter of 'switch_list_p' will be updaetd if this value is TRUE.
 * \param alert_configurable_but_non_existing [IN]     - If it is needed to display the alert message alert message(configurable but non-existing) on ICLI session.
 *
 * \return TRUE  - All switches are configurable and existing in the port range information.
 * \return FALSE - Found at least one non-existing switch or it isn't configurable switch in the port range information.
 **/
BOOL icli_cmd_switch_range_exist(u32 session_id, icli_unsigned_range_t *switch_list_p, BOOL omit_non_exist, BOOL alert_configurable_but_non_existing);

/**
 * \brief Check if selected ports are switch ports
 *
 * \param session_id [IN] The session id use by iCLI print.
 * \param ask [IN]  Asking
 * \param runtime [IN]  Pointer to where to put the "answer"
 * \return TRUE is runtime contains valid information.
 **/
BOOL icli_is_switchport_runtime(u32                session_id,
                                icli_runtime_ask_t ask,
                                icli_runtime_t     *runtime);

/**
 * \brief Check if selected ports are cpu ports
 *
 * \param session_id [IN] The session id use by iCLI print.
 * \param ask [IN]  Asking
 * \param runtime [IN]  Pointer to where to put the "answer"
 * \return TRUE is runtime contains valid information.
 **/
BOOL icli_is_cpuport_runtime(u32                session_id,
                             icli_runtime_ask_t ask,
                             icli_runtime_t     *runtime);

#endif //__ICLI_PORTING_UTIL_H__
