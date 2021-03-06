/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2019/12/20 18:49          V1.0             build this file
*
*******************************************************************************/
#ifndef MAIN_H
#define MAIN_H

/**
* @defgroup main
* @ingroup main
* @brief
* @details
* @{ */

#ifdef __cplusplus
extern "C" {
#endif

#include "app_config.h"

#include "driver.h"
#include "module.h"
#include "ui.h"

    static void main_preinit(void);
    static void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif


/** @}*/ //end of group main
#endif // MAIN_H
