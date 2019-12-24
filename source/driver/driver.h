/*******************************************************************************
 * Module: driver
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/07/26 14:46          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     driver.h
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/07/26
 *******************************************************************************/
#ifndef DRIVER_H
#define DRIVER_H

/*! \defgroup driver_public Public
\ingroup driver
\brief      driver layer
\details 
* @{ */

#include "app_config.h"
/********************************** Module Config *******************************/
                                




/********************************** Data Type ***********************************/





/********************************** Public Interface ****************************/

void driver_init(void);



#define drv_led_on(led_pin) nrf_gpio_pin_clear(led_pin)
#define drv_led_off(led_pin) nrf_gpio_pin_set(led_pin)

/********************************** Private Interface ***************************/




/*! @}*/ //end of group driver
#endif // DRIVER_H
