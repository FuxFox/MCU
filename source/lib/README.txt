* The files in this folder provide generic interface for other module.

* You can modify the code to support other MCU.

*list:
- app_button	  -	This module is used for keyboard scanning and provides callback.Support long-press detection.
- app_delay		-	A blocking delay module. Implemented base on STM32F103 with HAL.
- app_error		-	Implement assert macro and error handler.
- app_gpio		-	You can use pin number of chip to control the GPIO
- app_log		-	simple LOG module , used SEGGER RTT.
- app_timer		-	A software timer module implemented base on STM32f103xxx with HAL.
- app_usart		-	This module is the encapsulation of HAL Library for STM32f103xxx

- stm32f1xxVxx_pinmap	-	pin map use by app_gpio
