/*******************************************************************************
 *
 * Module: drv_IRM
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/13 17:02          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_IRM.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/13
  *******************************************************************************/
#ifndef DRV_IRM_H
#define DRV_IRM_H

/*! \defgroup drv_IRM_public Public
\ingroup drv_IRM
\brief
\details
        Infrared Receiver Module(IRM) Driver 
        This driver implemented base on STM32F103xx with HAL, used as infrared remote control receiver. 
        This driver can be modify to support any IRM and any protocol in theory.

    for example:
        #include "drv_IRM.h"

        DRV_IRM_INSTANCE(m_IRM, PIN_IR_RECEIVER, DRV_IRM_PROTOCOL_TC901, ui_remoter_key_handler2);

        void ui_remoter_init(void)
        {
            drv_IRM_init(&m_IRM);
        }

        static void ui_remoter_key_handler(uint8_t usr_code, uint8_t data)
        {
            //do something, handle the remoter key action.
        }


        //The EXTI line depend on the GPIO pin
        void EXTI15_10_IRQHandler(void)
        {
            HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
        }

        void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
        {
            switch (GPIO_Pin)
            {
            case GPIO_PIN_0:
                    break;
                    .....
            case GPIO_PIN_12:
                    drv_IRM_receive(12);
                    break;
                    .......
            case GPIO_PIN_15:
                    break;
            default:
                    break;
            }
        }


\note    Each instance occupied an EXTI(external interrupt) line
* @{ */

#include "app_config.h"

#include "app_delay.h"
#include "app_gpio.h"

  //********************************* Module Config *******************************/
#define DRV_IRM_INSTANCE_NUM_MAX        16        /*!< The number of max IRM instances that can support. 16 for STM32, depend on EXTI lines number */

//default; priority group for STM32 -> 4bit[0~15] of main priority, 0bit of sub-priority.
#define DRV_IRM_EXTI_IRQ_PRIORITY        7          
#define DRV_IRM_EXTI_IRQ_SUB_PRIORITY    0

#define DRV_IRM_TIMING_OFFSET_US        100        /*!< Allowable timing offset */
//********************************* Data Type ***********************************/

/*! IR protocol structure, the value mean the time(in us) of IR module output level */
typedef struct
{
    uint16_t start_low_us;
    uint16_t start_high_us;
    uint16_t logic_1_low_us;
    uint16_t logic_1_high_us;
    uint16_t logic_0_low_us;
    uint16_t logic_0_high_us;
    uint16_t repeat_low_us;         /*!< if 0, mean not repeat code support */
    uint16_t repeat_high_us;        /*!< if 0, mean not repeat code support */
}drv_IRM_protocol_t;

/*! \defgroup IRM_protocol_enum 
\brief 
    see \ref drv_IRM_protocol_t, you can add protocol here
* @{ */

/*! IR protocol -> NEC with simple repeat code */
#define DRV_IRM_PROTOCOL_NEC_SIMPLE    {9000, 4500, 560, 1690, 560, 560, 9000, 2250}

/*! IR protocol -> NEC with full repeat code */
#define DRV_IRM_PROTOCOL_NEC_FULL      {9000, 4500, 560, 1690, 560, 560, 0, 0}

/*! IR protocol -> NEC with full repeat code */
#define DRV_IRM_PROTOCOL_TC9012        {4500, 4500, 560, 1690, 560, 560, 0, 0}

/*! @}*/ //end of group IRM_protocol_enum

/*! IRM receive status enum */
typedef enum
{
    DRV_IRM_RX_IDLE = 0,    /*!< IRM is idle */
    DRV_IRM_RX_START,       /*!< IRM receiving an start signal */
    DRV_IRM_RX_DATA,        /*!< IRM receiving data bits */
}drv_IRM_rx_status_t;

/*! The data structure of IRM instance */
typedef struct
{
    drv_IRM_rx_status_t rx_status;
    uint8_t rx_buff[4];         /*!< Rx buffer, expect for 2 user code and 2 key code */
    uint8_t rx_bit_cnt;         /*!< A counter of received bits */
    uint32_t old_us_value;      /*!< record the system time in microsecond except for millisecond */
    uint32_t old_ms_value;      /*!< To record the system time in millisecond when rise or fall edge detected, use to calculate the time between two edges*/
}drv_IRM_instance_data_t;

typedef void (*drv_irm_data_handler)(uint8_t usr_code, uint8_t data);

/*! IRM instance structure */
typedef const struct
{
    uint8_t data_pin;               /*!< The pin number of MCU connected to IR module data-output pin */
    drv_IRM_protocol_t protocal;    /*!< The IR protocol, see also \ref drv_IRM_protocol_t and \ref IRM_protocol_enum */
    drv_IRM_instance_data_t* data;  /*!< A pointer to data structure */
    drv_irm_data_handler callback;  /*!< The callback function to handle received data */
}drv_IRM_instance_t;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	Use this macro to quickly define an instance

\param[in]	_name       The name of the instance
\param[in]	_pin        The pin number of MCU connected to IR module data-output pin
\param[in]	_protocol   The protocol, can be one of \ref IRM_protocol_enum
\param[in]	_callback   The callback function to handle received data
*******************************************************************************/
#define DRV_IRM_INSTANCE(_name, _pin, _protocol, _callback)    \
    static drv_IRM_instance_data_t _name##_data = {DRV_IRM_RX_IDLE};\
    static drv_IRM_instance_t _name = {                        \
        .data_pin = _pin,                                      \
        .data = &_name##_data,                                 \
        .callback = _callback,                                 \
        .protocal = _protocol                                  \
    }



void drv_IRM_init(drv_IRM_instance_t* instance);
void drv_IRM_receive(uint8_t gpio_pin);
//********************************* Private Interface ***************************/

static uint16_t drv_IRM_get_duration(drv_IRM_instance_data_t* instance_data);




/*! @}*/ //end of group drv_IRM
#endif // DRV_IRM_H
