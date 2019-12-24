/*******************************************************************************
 *
 * Module: drv_pins
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/16 15:59          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_pins.h
  * \brief    
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/16
  *******************************************************************************/
#ifndef DRV_PINS_H
#define DRV_PINS_H

/*! \defgroup drv_pins_public Public
\ingroup drv_pins
\brief       Batch pins configure and readability macro define.
\details
* @{ */

#include "app_config.h"
#include "app_gpio.h"

//********************************* Module Config *******************************/
#define PIN_INPUT_LIST {        \
        PIN_OUTSIDE_GATE_FAULT_DETECT,\
        PIN_OUTSIDE_GATE_OPEN_DETECT,\
        PIN_OUTSIDE_GATE_CLOSE_DETECT,\
        PIN_INSIDE_GATE_OPEN_DETECT,\
        PIN_INSIDE_GATE_CLOSE_DETECT,\
        PIN_PUSH_MOTOR_IN_DETECT,\
        PIN_PUSH_MOTOR_OUT_DETECT,\
        PIN_BUTTON_BUCKET_WEIGHT_SET_UNIT_OR_WATER_DETECT_2,\
        PIN_CUP_REACH_DETECT,\
        PIN_COVER_REACH_DETECT,\
        PIN_TURNTABLE_CUP_DETECT,\
        PIN_TURNTABLE_COVER_DETECT,\
        PIN_TEA_LOCATION_DETECT_1,\
        /*PIN_TEA_LOCATION_DETECT_2,*/\
}

#define PIN_OUTPUT_LIST_INIT_LOW {        \
        PIN_WATER_PUMP_CTRL,\
        PIN_BUCKET_OUTPUT_CTRL_1,\
        PIN_BUCKET_OUTPUT_CTRL_2,\
        PIN_HOT_WATER_OUTPUT_VALVE_1,\
        PIN_TEA_VIBRATION_MOTOR_CTRL,\
        PIN_COOLING_PUMP_220V_CTRL,\
        PIN_HEATER_CTRL,\
        PIN_UV_CTRL,\
        PIN_TEA_MOTOR_PWM_IN1,\
        PIN_TEA_MOTOR_PWM_IN2,\
        PIN_TEA_OUTPUT_CTRL_1,\
        PIN_TEA_OUTPUT_CTRL_2,\
        PIN_TEA_OUTPUT_CTRL_3,\
        PIN_TEA_OUTPUT_CTRL_4,\
        PIN_TEA_OUTPUT_CTRL_5,\
        PIN_BUTTON_CUP_WEIGHT_RESET_OR_DRAIN_WATER,\
/*delete    */    PIN_TEA_LOCATION_DETECT_2\
}

#define PIN_OUTPUT_LIST_INIT_HIGHT {        \
        PIN_RUNNING_INDICATE\
}

//********************************* Data Type ***********************************/





//********************************* Public Interface ****************************/
void drv_pins_init(void);

#define drv_sensor_is_outside_gate_stuck()    (!app_gpio_pin_read(PIN_OUTSIDE_GATE_FAULT_DETECT))
#define drv_sensor_is_outside_gate_open()    (!app_gpio_pin_read(PIN_OUTSIDE_GATE_OPEN_DETECT))
#define drv_sensor_is_outside_gate_close()    (!app_gpio_pin_read(PIN_OUTSIDE_GATE_CLOSE_DETECT))
#define drv_sensor_is_inside_gate_open()    (!app_gpio_pin_read(/*PIN_INSIDE_GATE_OPEN_DETECT*/PIN_PUSH_MOTOR_IN_DETECT))
#define drv_sensor_is_inside_gate_close()    (!app_gpio_pin_read(PIN_INSIDE_GATE_CLOSE_DETECT))
#define drv_sensor_is_table_push_in()        (!app_gpio_pin_read(PIN_PUSH_MOTOR_IN_DETECT))
#define drv_sensor_is_table_push_out()        (!app_gpio_pin_read(PIN_PUSH_MOTOR_OUT_DETECT))
#define drv_sensor_is_water_out_ready()        (app_gpio_pin_read(PIN_BUTTON_BUCKET_WEIGHT_SET_UNIT_OR_WATER_DETECT_1))
#define drv_sensor_is_heater_water_ready()    (app_gpio_pin_read(PIN_BUTTON_BUCKET_WEIGHT_SET_UNIT_OR_WATER_DETECT_2))
#define drv_sensor_is_cup_ready()            (app_gpio_pin_read(PIN_CUP_REACH_DETECT))
#define drv_sensor_is_cover_ready()            (app_gpio_pin_read(PIN_COVER_REACH_DETECT))
#define drv_sensor_is_turntable_at_cup()    (app_gpio_pin_read(PIN_TURNTABLE_CUP_DETECT))
#define drv_sensor_is_turntable_at_cover()    (app_gpio_pin_read(PIN_TURNTABLE_COVER_DETECT))
#define drv_sensor_is_tea_arrive()            (!app_gpio_pin_read(PIN_TEA_LOCATION_DETECT_1))
#define drv_sensor_is_tea_ready()            (!app_gpio_pin_read(PIN_TEA_LOCATION_DETECT_2))
#define drv_sensor_is_water_button_press()    (!app_gpio_pin_read(/*PIN_HOT_WATER_OUTPUT_BUTTON*/PIN_INSIDE_GATE_OPEN_DETECT))


#define drv_ctrl_water_pump(onoff)                app_gpio_pin_write(PIN_WATER_PUMP_CTRL, (GPIO_PinState)onoff)
#define drv_ctrl_bucket_1_output(onoff)            app_gpio_pin_write(PIN_BUCKET_OUTPUT_CTRL_1, (GPIO_PinState)onoff)
#define drv_ctrl_bucket_2_output(onoff)            app_gpio_pin_write(PIN_BUCKET_OUTPUT_CTRL_2, (GPIO_PinState)onoff)
#define drv_ctrl_main_water_valve(onoff)        app_gpio_pin_write(PIN_HOT_WATER_OUTPUT_VALVE_1, (GPIO_PinState)onoff)
#define drv_ctrl_cooling_system(onoff)            app_gpio_pin_write(PIN_COOLING_PUMP_220V_CTRL, (GPIO_PinState)(onoff))
#define drv_ctrl_water_heater(onoff)            app_gpio_pin_write(PIN_HEATER_CTRL, (GPIO_PinState)(onoff))
#define drv_ctrl_uv_led(onoff)                    app_gpio_pin_write(PIN_UV_CTRL, (GPIO_PinState)(onoff))
#define drv_ctrl_tea_output_1(onoff)            app_gpio_pin_write(PIN_TEA_OUTPUT_CTRL_1, (GPIO_PinState)(onoff))
#define drv_ctrl_tea_output_2(onoff)            app_gpio_pin_write(PIN_TEA_OUTPUT_CTRL_2, (GPIO_PinState)(onoff))
#define drv_ctrl_tea_output_3(onoff)            app_gpio_pin_write(PIN_TEA_OUTPUT_CTRL_3, (GPIO_PinState)(onoff))
#define drv_ctrl_tea_output_4(onoff)            app_gpio_pin_write(PIN_TEA_OUTPUT_CTRL_4, (GPIO_PinState)(onoff))
#define drv_ctrl_tea_output_5(onoff)            app_gpio_pin_write(PIN_TEA_OUTPUT_CTRL_5, (GPIO_PinState)(onoff))
#define drv_ctrl_running_led(onoff)                app_gpio_pin_write(PIN_RUNNING_INDICATE, (GPIO_PinState)(!onoff))
#define drv_ctrl_running_led_toggle()            app_gpio_pin_toggle(PIN_RUNNING_INDICATE)
#define drv_ctrl_tea_motor_forward()            app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN1, GPIO_PIN_SET);app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN2, GPIO_PIN_RESET)
#define drv_ctrl_tea_motor_reverse()            app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN1, GPIO_PIN_RESET);app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN2, GPIO_PIN_SET)
#define drv_ctrl_tea_motor_stop()                app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN1, GPIO_PIN_RESET);app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN2, GPIO_PIN_RESET)
#define drv_ctrl_tea_vibration_motor(onoff)        app_gpio_pin_write(PIN_TEA_VIBRATION_MOTOR_CTRL, (GPIO_PinState)onoff)
#define drv_ctrl_drain_water_valve(onoff)        app_gpio_pin_write(PIN_BUTTON_CUP_WEIGHT_RESET_OR_DRAIN_WATER, (GPIO_PinState)onoff)

#if 1//old_board

#define drv_ctrl_tea_motor_1(onoff)                app_gpio_pin_write(PIN_TEA_LOCATION_DETECT_2, (GPIO_PinState)onoff);app_gpio_pin_write(PIN_TEA_MOTOR_PWM_IN2, GPIO_PIN_RESET)//delete
#define drv_sensor_is_tea_1_ready()            (app_gpio_pin_read(PIN_OUTSIDE_GATE_OPEN_DETECT))//delete

#endif
//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_sensor
#endif // DRV_PINS_H
