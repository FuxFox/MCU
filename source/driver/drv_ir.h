/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/06/23 15:52          V1.0             build this file
 *
 *******************************************************************************/
#ifndef DRV_IR_H
#define DRV_IR_H

/*! \defgroup drv_ir_public Public
\ingroup drv_ir
\brief 
\details 

* @{ */

#include "app_config.h"


//********************************* Module Config *******************************/
#define DRV_IR_BIT_SEQUENCE_MSB_FIRST 0	// default 0 for standard NEC

/*! IR protocol -> NEC with full repeat code */
#define DRV_IR_PROTOCOL_NEC_FULL      {9000, 4500, 560, 1690, 560, 560, 0, 0}

//********************************* Data Type ***********************************/

typedef struct
{
	uint16_t start_high;	//< ir start signal high_duty time, unit:us 
	uint16_t start_low;		//< ir start signal low_duty time, unit:us 
	uint16_t logic_1_high;	//< ir logic 0 high_duty time, unit:us 
	uint16_t logic_1_low;	//< ir logic 0 low_duty time, unit:us 
	uint16_t logic_0_high;	//< ir logic 0 high_duty time, unit:us 
	uint16_t logic_0_low;	//< ir logic 0 low_duty time, unit:us 
	uint16_t repeat_high;	//< ir repeat signal high_duty time, unit:us. if 0, mean no support repeat code.
	uint16_t repeat_low;	//< ir repeat signal low_duty time, unit:us. if 0, mean no support repeat code.
}drv_ir_protocol_t;

typedef struct
{
	void (*pwm_init)(void);		/*!< init pwm channel to 38Khz and 1/3 duty */
	void (*pwm_switch)(bool);	/*!< switch pwm ON or OFF */
}drv_pwm_instance_t;

typedef struct
{
	drv_pwm_instance_t pwm_driver;
	drv_ir_protocol_t protocol;
}drv_ir_instance_t;

//********************************* Public Interface ****************************/

void drv_ir_init(drv_ir_instance_t* instance);



/*!*****************************************************************************
\brief  	send ir data
\param[in]	drv_ir_instance_t * instance
\param[in]	uint8_t * data
\param[in]	uint8_t data_len
\return     void
******************************************************************************/
void drv_ir_send(drv_ir_instance_t* instance, uint8_t* buff, uint8_t buff_len);

//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_ir
#endif // DRV_IR_H
