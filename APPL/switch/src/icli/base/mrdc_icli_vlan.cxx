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

    Constant and Macro

==============================================================================
*/
/* bit array macro's */
#define _VLAN_ENABLE_SIZE               MRDC_BF_SIZE( MRDC_VIDS )
#define _VLAN_ENABLE_GET(vid)           MRDC_BF_GET( g_vlan_enable_bit, vid )
#define _VLAN_ENABLE_SET(vid, val)      MRDC_BF_SET( g_vlan_enable_bit, vid, val )
#define _VLAN_ENABLE_CLR_ALL()          MRDC_BF_CLR( g_vlan_enable_bit, MRDC_VIDS )

#define _VLAN_ENTER_SIZE                MRDC_BF_SIZE( MRDC_VIDS )
#define _VLAN_ENTER_GET(vid)            MRDC_BF_GET( g_vlan_enter_bit, vid )
#define _VLAN_ENTER_SET(vid, val)       MRDC_BF_SET( g_vlan_enter_bit, vid, val )
#define _VLAN_ENTER_CLR_ALL()           MRDC_BF_CLR( g_vlan_enter_bit, MRDC_VIDS )

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
static u8   g_vlan_enable_bit[ _VLAN_ENABLE_SIZE ];
static u8   g_vlan_enter_bit[ _VLAN_ENTER_SIZE ];

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
/*
    initialization

    INPUT
        n/a

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_vlan_init(
    void
)
{
    /* all enabled */
    memset(g_vlan_enable_bit, 0xFF, _VLAN_ENABLE_SIZE);

    /* all not enter */
    _VLAN_ENTER_CLR_ALL();

    return ICLI_RC_OK;
}

/*
    enable/disable a VLAN interface

    INPUT
        vid      : VLAN interface ID to add
        b_enable : TRUE - enable the VLAN interface, FALSE - disable it

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_vlan_enable_set(
    IN u32      vid,
    IN BOOL     b_enable
)
{
    if (vid < MRDC_APPL_VLAN_ID_MIN || vid > MRDC_APPL_VLAN_ID_MAX) {
        T_W("Invalid vid (%u)", vid);
        return ICLI_RC_ERR_PARAMETER;
    }

    _VLAN_ENABLE_SET( vid, b_enable );
    return ICLI_RC_OK;
}

/*
    get if the VLAN interface is enabled or disabled

    INPUT
        vid : VLAN interface ID to get

    OUTPUT
        b_enable : TRUE - enabled, FALSE - disabled

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_vlan_enable_get(
    IN  u32     vid,
    OUT BOOL    *b_enable
)
{
    if (vid < MRDC_APPL_VLAN_ID_MIN || vid > MRDC_APPL_VLAN_ID_MAX) {
        T_W("Invalid VID (%u)", vid);
        return ICLI_RC_ERR_PARAMETER;
    }

    if ( b_enable == NULL ) {
        T_W("b_enable == NULL\n");
        return ICLI_RC_ERR_PARAMETER;
    }

    *b_enable = _VLAN_ENABLE_GET( vid );
    return ICLI_RC_OK;
}

/*
    enter/leave a VLAN interface

    INPUT
        vid     : VLAN interface ID to add
        b_enter : TRUE - enter the VLAN interface, FALSE - leave it

    OUTPUT
        n/a

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_vlan_enter_set(
    IN u32      vid,
    IN BOOL     b_enter
)
{
    if (vid < MRDC_APPL_VLAN_ID_MIN || vid > MRDC_APPL_VLAN_ID_MAX) {
        T_W("Invalid VID (%u)", vid);
        return ICLI_RC_ERR_PARAMETER;
    }

    _VLAN_ENTER_SET( vid, b_enter );
    return ICLI_RC_OK;
}

/*
    get if enter or leave the VLAN interface

    INPUT
        vid : VLAN interface ID to get

    OUTPUT
        b_enter : TRUE - enter, FALSE - leave

    RETURN
        icli_rc_t

    COMMENT
        n/a
*/
i32 mrdc_icli_vlan_enter_get(
    IN  u32     vid,
    OUT BOOL    *b_enter
)
{
    if (vid < MRDC_APPL_VLAN_ID_MIN || vid > MRDC_APPL_VLAN_ID_MAX) {
        T_W("Invalid VID (%u)", vid);
        return ICLI_RC_ERR_PARAMETER;
    }

    if ( b_enter == NULL ) {
        T_W("b_enter == NULL\n");
        return ICLI_RC_ERR_PARAMETER;
    }

    *b_enter = _VLAN_ENTER_GET( vid );
    return ICLI_RC_OK;
}
