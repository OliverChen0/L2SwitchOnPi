/************************************************************************/
/*           Copyright 2024 - 2024, Shanghai MRDcom Co.,Ltd.            */
/*                      ALL RIGHTS RESERVED                             */
/************************************************************************/
#ifndef __ICLI_ICFG_H__
#define __ICLI_ICFG_H__

/*
******************************************************************************

    Include files

******************************************************************************
*/

/*
******************************************************************************

    Constant and Macro definition

******************************************************************************
*/

/*
******************************************************************************

    Public Function

******************************************************************************
*/

/**
 * \file icli_icfg.h
 * \brief This file defines the interface to the DHCP snooping module's ICFG commands.
 */

/**
  * \brief Initialization function.
  *
  * Call once, preferably from the INIT_CMD_INIT section of
  * the module's _init() function.
  */
mrdc_rc icli_icfg_init(void);

#endif /* __ICLI_ICFG_H__ */
