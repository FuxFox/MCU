/*******************************************************************************
 * Module: custom_board
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      grx	      2019/08/01 10:30          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     custom_board.h
 * \brief    Customer board pin define for STM32F103xxx
 * \author   grx
 * \version  V1.0
 * \date  	 2019/08/01
 *******************************************************************************/
#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

/*! \defgroup custom_board_public Public
\ingroup custom_board
\details 
* @{ */

#include "stm32f1xxVxx_pinmap.h"

#define PIN_OUTSIDE_GATE_FAULT_DETECT			1
#define PIN_OUTSIDE_GATE_OPEN_DETECT			2
#define PIN_OUTSIDE_GATE_CLOSE_DETECT			3
#define PIN_TEMP_I2C_SCL						4
#define PIN_TEMP_OS								5
#define PIN_TEMP_I2C_SDA						7
#define PIN_RUNNING_INDICATE					8
#define PIN_WATER_ROUTE_CHANGE_CTRL				9

#define PIN_FLASH_I2C_SDA						15
#define PIN_FLASH_I2C_SCL						16
#define PIN_NTC_KATTLE							17
#define PIN_NTC_HEATER							18

#define PIN_BUTTON_CUP_WEIGHT_RESET_OR_DRAIN_WATER		23
#define PIN_CUP_WEIGHT_SCL						24
#define PIN_CUP_WEIGHT_DIN						25
#define PIN_OUTSIDE_GATE_PWM				 	26

#define PIN_OUTSIDE_GATE_EN						29
#define PIN_OUTSIDE_GATE_DIR_CTRL				30
#define PIN_CUP_REACH_DETECT					31
#define PIN_COVER_REACH_DETECT					32
#define PIN_BUTTON_BUCKET_WEIGHT_RESET_2				33
#define PIN_BUTTON_BUCKET_WEIGHT_RESET_1				34
#define PIN_BUTTON_BUCKET_WEIGHT_SET_UNIT_OR_WATER_DETECT_1				35
#define PIN_BUTTON_BUCKET_WEIGHT_SET_UNIT_OR_WATER_DETECT_2				36

#define PIN_BUCKET_WEIGHT_1_DIN					38
#define PIN_BUCKET_WEIGHT_1_SCK					39
#define PIN_BUCKET_WEIGHT_2_DIN					40
#define PIN_BUCKET_WEIGHT_2_SCK					41
#define PIN_HOT_WATER_OUTPUT_VALVE_1			42
#define PIN_WATER_PUMP_CTRL						43
#define PIN_INSIDE_GATE_PWM						44
#define PIN_COOLING_PUMP_220V_CTRL				45
#define PIN_HEATER_CTRL							46
#define PIN_UV_CTRL								47
//#define PIN_FAN_CTRL			48

#define PIN_INSIDE_GATE_EN						51
#define PIN_INSIDE_GATE_DIR_CTRL				52
#define PIN_COOLING_PUMP_24V_CTRL				53
#define PIN_HOT_WATER_OUTPUT_VALVE_2			54
#define PIN_DEBUG_TX							55
#define PIN_DEBUG_RX							56
#define PIN_HOT_WATER_OUTPUT_BUTTON				57
#define PIN_BUTTON_CUP_WEIGHT_SET_UNIT			58
#define PIN_IR_RECEIVER							59
#define PIN_TEA_OUTPUT_CTRL_5					60
#define PIN_TEA_OUTPUT_CTRL_4					61
#define PIN_TEA_OUTPUT_CTRL_3					62
#define PIN_TEA_OUTPUT_CTRL_2					63
#define PIN_BUCKET_OUTPUT_CTRL_1				64
#define PIN_TEA_MOTOR_FAULT_DETECT				65
#define PIN_TEA_OUTPUT_CTRL_1					66
#define PIN_TEA_LOCATION_DETECT_1				67
#define PIN_TEA_MOTOR_PWM_IN1					68
#define PIN_TEA_LOCATION_DETECT_2				69
#define PIN_TEA_MOTOR_PWM_IN2					70
#define PIN_BUCKET_OUTPUT_CTRL_2				71

#define PIN_PUSH_MOTOR_DIR_CTRL					77
#define PIN_HOST_TX								78
#define PIN_HOST_RX								79
#define PIN_CUPMACHINE_CUP_TX					80
#define PIN_TURNTABLE_DIR_CTRL					81
#define PIN_PUSH_MOTOR_EN						82
#define PIN_CUPMACHINE_CUP_RX					83
#define PIN_PUSH_MOTOR_OUT_DETECT				84
#define PIN_PUSH_MOTOR_IN_DETECT				85
#define PIN_TEA_VIBRATION_MOTOR_CTRL			86
#define PIN_TURNTABLE_CUP_DETECT				87
#define PIN_TURNTABLE_COVER_DETECT				88
#define PIN_TURNTABLE_EN						89
#define PIN_PUSH_MOTOR_PWM						90
#define PIN_TURNTABLE_PWM						91
#define PIN_CUPMACHINE_COVER_TX					92
#define PIN_CUPMACHINE_COVER_RX					93

#define PIN_WATER_TEMP_I2C_SCK					95
#define PIN_WATER_TEMP_I2C_SDA					96
#define PIN_INSIDE_GATE_CLOSE_DETECT			97
#define PIN_INSIDE_GATE_OPEN_DETECT				98

/*! @}*/ //end of group custom_board
#endif // CUSTOM_BOARD_H
