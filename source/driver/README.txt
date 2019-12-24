* The files in this folder are all the driver of peripheral component for MCU

* Some drivers are implemented base on STM32F103xxx with HAL, others are implemented base on NRF52832,
	as well as some generic drivers that can use for any MCU.
	
* Some drivers are developed based on the object-oriented idea. 
	You only need to remap the GPIO configure interface (see ../app_interface_remap.h and ../lib/app_gpio.h) 
	and create an instance using the macro like "DRV_XXX_INSTANCE(...)" provided by the header file, 
	and then you can use all the driver interfaces for the instance.

* Here is a list of drivers base on STM32, you can also replace STM32 related code for other MCU.
- drv_cv0629	-	KEWEINIDI CV0629 driver.(a cup distribute device)
- drv_IRM		-	Infrared Receiver Module(IRM) Driver 
- drv_NTC		-	NTC resistor driver
- drv_tb6600	-	This is a step motor driver base on TB6600 driver chip

* Here is a list of drivers base on NRF52832, you can also replace NRF related code for other MCU.
- drv_buzzer	-	Just a passive buzzer driver
- drv_m26		-	QUECTEL M26 IOT module driver
- drv_st7789v	-	AML280V15002-A TFT-LCD driver, base on ST7789V driver chip

* Here is a list of generic driver.
- drv_at24cxx	-	AT24Cxx serial EEPROM
- drv_cs1237	-	CHIPSEA CS1237 24-bit Sigma-Delta ADC
- drv_iic		-	Software IIC driver
- drv_mlx90614	-	MLX90614 Infrared temperature sensor driver
- drv_pct2075gv -	PCT2075GV temperature sensor driver
- drv_pins		-	Batch pins configure and readability macro define.
- drv_rgb_led	-	RGB LED driver
- drv_spi		-	Software SPI driver

* You may also need to refer the files app_config.h and custom_board.h under the ../../mcu/nrf52/ or ../../mcu/stm32/