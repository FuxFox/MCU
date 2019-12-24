/*******************************************************************************
 *
 * Module: drv_tb660
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/21 14:16          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_tb6600.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/21
  *******************************************************************************/
#ifndef DRV_TB6600_H
#define DRV_TB6600_H

  /*! \defgroup drv_tb660_public Public
  \ingroup drv_tb660
  \brief
          This is a step motor driver base on TB6600 driver chip.
          This driver is implemented base on STM32F103xxx with TIM1
  * @{ */

#include "app_config.h"
#include "app_gpio.h"

  //********************************* Module Config *******************************/

#define DRV_TB6600_SPEED_RPM_MAX    18750            /*!< limit of max speed. unit: rpm */
#define DRV_TB6600_STEP_DIV_MAX        4             /*!< limit of max step clock division*/     
#define DRV_TB6600_TIME_RELOAD_VAL    ((1000000 / (DRV_TB6600_SPEED_RPM_MAX / 60 * (4 * DRV_TB6600_STEP_DIV_MAX))) / 2)    


#define DRV_TB6600_TIMER        TIM1                /*!< STM32 TIM */
#define DRV_TB6600_TIM_IRQ_PRIORITY        7
//********************************* Data Type ***********************************/

/*! clock division */
typedef enum
{
    DRV_TB6600_STEP_DIV_4  = 4,        /*!< 4 clock per step */
    DRV_TB6600_STEP_DIV_8  = 8,        /*!< 8 clock per step */
    DRV_TB6600_STEP_DIV_16 = 16,       /*!< 16 clock per step */
}drv_tb6600_step_div_enum;

/*! direction */
typedef enum
{
    DRV_TB6600_DIR_SAME_AS_LAST,
    DRV_TB6600_DIR_FORWARD,
    DRV_TB6600_DIR_REVERSE,
}drv_tb6600_dir_t;

/*! TB6600 instance structure */
typedef struct tb6600
{
    volatile bool is_enable;
    uint8_t clk_pin;                           /*!< chip pin number of MCU that connected to TB6600 CLK pin. */
    uint8_t cw_ccw_pin;                        /*!< chip pin number of MCU that connected to TB6600 CW/CCW pin. */
    uint8_t enable_pin;                        /*!< chip pin number of MCU that connected to TB6600 EN pin. */
    drv_tb6600_step_div_enum step_division;    
    uint16_t speed_rpm;                        /*!< speed, unit: rpm, Max value: DRV_TB6600_SPEED_RPM_MAX*/

    uint32_t step_num;
    uint32_t step_cnt;
    uint16_t clk_div;
    uint16_t clk_cnt;
    struct tb6600* next;
}drv_tb6600_instance_t;



//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	use this macro to easily define a TB6600 step motor instance

\param[in]	_name           name of instance
\param[in]	_clk_pin        chip pin number of MCU that connected to TB6600 CLK pin.
\param[in]	_cw_ccw_pin     chip pin number of MCU that connected to TB6600 CW/CCW pin.
\param[in]	_enable_pin     chip pin number of MCU that connected to TB6600 EN pin.
\param[in]	_step_div       division for TB6600 clk
*******************************************************************************/
#define DRV_TB6600_INSTANC(_name, _clk_pin, _cw_ccw_pin, _enable_pin, _step_div)    \
    static drv_tb6600_instance_t _name = {                                          \
        .clk_pin = _clk_pin,                                                        \
        .cw_ccw_pin = _cw_ccw_pin,                                                  \
        .enable_pin = _enable_pin,                                                  \
        .step_division = _step_div                                                  \
};


void drv_tb6600_init(drv_tb6600_instance_t* instance, uint16_t speed);

bool drv_tb6600_is_enable(drv_tb6600_instance_t* instance);
void drv_tb6600_move_step(drv_tb6600_instance_t* instance, drv_tb6600_dir_t dir, uint32_t step_num);
void drv_tb6600_move_angle(drv_tb6600_instance_t* instance, drv_tb6600_dir_t dir, uint32_t angle);
void drv_tb6600_stop(drv_tb6600_instance_t* instance);
void drv_tb6600_set_speed(drv_tb6600_instance_t* instance, uint16_t speed);
uint32_t drv_tb6600_get_step_counter(drv_tb6600_instance_t* instance);
void drv_tb6600_set_dir(drv_tb6600_instance_t* instance, drv_tb6600_dir_t dir);
//********************************* Private Interface ***************************/
void drv_tb6600_timer_callback(void);





void drv_tb6600_timer_init(void);
/*! @}*/ //end of group drv_tb660
#endif // DRV_TB6600_H
