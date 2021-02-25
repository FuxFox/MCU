/*******************************************************************************
* LICENSE : Apache 2.0
*           
* History:
*    <author>         <time>             <version>             <desc>
*      FuxFox	      2020/05/22 09:07          V1.0             build this file
*
*******************************************************************************/
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

/** 
* @defgroup hal_gpio
* @ingroup HAL
* @brief	K210 HAL GPIO interface
* @details ��װ�ײ�io���ã�Ϊ�ϲ�Ӧ���ṩͳһ�Ľӿ�
*	K210 ���� 32 + 8 ��gpio������32������gpiohs��8����ͨgpio��
*	����gpio������ӳ�䵽FPIOA��48��IO�ܽ��ϡ�
* 
* @attention
*	1�����к����У����� gpio_pin ��Ӧ����K210��48��IO�ı�ţ���Χ[0 ~ 47]��
*	2��HAL_GPIO_MODE_INPUT �� HAL_GPIO_MODE_OUTPUT Ĭ�ϴ�gpio��ʼ���䣬8��gpio�����ŷ���gpiohs��
*	3���� HAL_GPIO_MODE_INPUT / HAL_GPIO_MODE_OUTPUT �Ĺ���ֻ�ܷ���gpiohs��
* @{ */

#include "app_config.h"

/*================================= Module Config ============================*/

/*================================= Data Type ================================*/

/** GPIO pin level */
typedef enum
{
	HAL_GPIO_LOW,
	HAL_GPIO_HIGH,
}hal_gpio_state_t;

/** gpio pin pull state */
typedef enum
{
	HAL_GPIO_NOPULL,
	HAL_GPIO_PULLDOWN,
	HAL_GPIO_PULLUP,
}hal_gpio_pull_t;

typedef enum
{
	HAL_GPIO_MODE_INPUT,             
	HAL_GPIO_MODE_OUTPUT,				 /*!< PUSH PULL mode */

// 	HAL_GPIO_MODE_EXTI_LOW,             /*!< External Interrupt Mode with LOW level detection */
// 	HAL_GPIO_MODE_EXTI_HIGH,            /*!< External Interrupt Mode with HIGH level detection */
// 	HAL_GPIO_MODE_EXTI_FALLING,         /*!< External Interrupt Mode with Falling edge trigger detection */
// 	HAL_GPIO_MODE_EXTI_RISING,          /*!< External Interrupt Mode with Rising  edge trigger detection */
// 	HAL_GPIO_MODE_EXTI_RISING_FALLING,  /*!< External  Interrupt Mode  with  Rising/Falling edge trigger detection */
}hal_gpio_mode_enum;

/*================================= Public Interface =========================*/

/*!*****************************************************************************
* @brief  	initialize hal_gpio module
* @param[in]	void
* @return     void
*******************************************************************************/
void hal_gpio_init(void);

/*!*****************************************************************************
* @brief  	configure pin as gpio
* @param[in]	uint8_t gpio_pin	:	gpio pin number
* @param[in]	hal_gpio_mode_enum mode		
* @param[in]	hal_gpio_pull_t pin_pull
* @return     void
*******************************************************************************/
void hal_gpio_cfg(uint8_t gpio_pin, hal_gpio_mode_enum mode, hal_gpio_pull_t pin_pull);

/*!*****************************************************************************
* @brief  	read pin state
* @param[in]	uint8_t gpio_pin	:	gpio pin number
* @return     bool	: true if high, false if low
*******************************************************************************/
bool hal_gpio_pin_read(uint8_t gpio_pin);

/*!*****************************************************************************
* @brief  	set pin state
* @param[in]	uint8_t gpio_pin	:	gpio pin number
* @param[in]	hal_gpio_state_t pin_state
* @return     void
*******************************************************************************/
void hal_gpio_pin_write(uint8_t gpio_pin, hal_gpio_state_t pin_state);

/*!*****************************************************************************
* @brief      configure gpio as output
* @param[in]    uint8_t gpio_pin
* @return     void
*******************************************************************************/
#define hal_gpio_cfg_output(gpio_pin)            hal_gpio_cfg(gpio_pin, HAL_GPIO_MODE_OUTPUT, HAL_GPIO_NOPULL)

/*!*****************************************************************************
* @brief      configure gpio as input
* @param[in]    uint8_t gpio_pin
* @param[in]    hal_gpio_pull_t pin_pull
* @return     void
*******************************************************************************/
#define hal_gpio_cfg_input(gpio_pin, pin_pull)        hal_gpio_cfg(gpio_pin, HAL_GPIO_MODE_INPUT, pin_pull)

/*******************************************************************************
* @brief  	
* @param[in]	uint8_t gpio_pin
* @return     void
*******************************************************************************/
void hal_gpio_pin_toggle(uint8_t gpio_pin);


/** @} */ //end of group hal_gpio
#endif // HAL_GPIO_H
