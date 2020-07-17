/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2020/06/23 15:52          V1.0             build this file
 *
 *******************************************************************************/
#ifndef DRV_IR_C
#define DRV_IR_C

#include "drv_ir.h"
#include "app_log.h"
#include "hal_gpio.h"
#include "hal_delay.h"

/*!*****************************************************************************
\brief  	initialize
\details
\param[in]	void
\return     void
******************************************************************************/
void drv_ir_init(drv_ir_instance_t* instance)
{
	instance->pwm_driver.pwm_init();
	instance->pwm_driver.pwm_switch(OFF);
}


static void drv_ir_send_byte(drv_ir_instance_t* instance, uint8_t byte)
{
	uint8_t i;

	for (i = 0x80; i ; i >>= 1)
	{
		instance->pwm_driver.pwm_switch(ON);
		hal_delay_us((byte & i)? instance->protocol.logic_1_high 
			: instance->protocol.logic_0_high);
		instance->pwm_driver.pwm_switch(OFF);
		hal_delay_us((byte & i) ? instance->protocol.logic_1_low
			: instance->protocol.logic_0_low);		
	}
}

void drv_ir_send(drv_ir_instance_t* instance, uint8_t* buff, uint8_t buff_len)
{
	//start signal
	instance->pwm_driver.pwm_switch(ON);
	hal_delay_us(instance->protocol.start_high);
	instance->pwm_driver.pwm_switch(OFF);
	hal_delay_us(instance->protocol.start_low);

	while (buff_len--)
	{
		drv_ir_send_byte(instance, *buff++);
	}
}

#endif // DRV_IR_C
