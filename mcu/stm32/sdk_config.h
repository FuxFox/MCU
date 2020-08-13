/*******************************************************************************
 * LICENSE : Apache 2.0
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/12/07 14:48          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     sdk_config.h
 * \brief    This file implemented for STM32F103xxx
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/12/07
 *******************************************************************************/
#ifndef SDK_CONFIG_H
#define SDK_CONFIG_H

/**************************** CMSIS Configure Wizard *******************/

// <<< Use Configuration Wizard in Context Menu >>>\n

// <h> CLOCK_SYSTEM_CONFIG
//==========================================================

// <h> OSCILLATOR - Adjust the value of oscillator used in your application.
//==========================================================

// <e> HSE_ENABLE - High Speed External oscillator
//==========================================================
#define HSE_ENABLE 1

// <o> HSE_STATE
//==========================================================
// <1=> ON
// <2=> BYPASS
#define HSE_STATE_ 1

#if (HSE_ENABLE == 0)
#define HSE_STATE RCC_HSE_OFF
#elif (HSE_STATE_ == 1)
#define HSE_STATE RCC_HSE_ON
#else
#define HSE_STATE RCC_HSE_BYPASS
#endif

// <o> HSE_VALUE - External High Speed oscillator (HSE) value.
//==========================================================
// <i> This value is used by the RCC HAL module to compute the system frequency (when HSE is used as system clock source, directly or through the PLL).  
// <i> Value of the External oscillator in Hz
#ifndef HSE_VALUE
#define HSE_VALUE    ((uint32_t)8000000) 
#endif 

// <o> HSE_STARTUP_TIMEOUT - Time out for HSE start up, in ms
//==========================================================
//<i> Time out for HSE start up, in ms
#ifndef  HSE_STARTUP_TIMEOUT
#define HSE_STARTUP_TIMEOUT    ((uint32_t)100)   
#endif 


// <o> HSE_PREDIV_VALUE
//==========================================================
// <1=> DIV1
// <2=> DIV2
#define HSE_PREDIV_VALUE_ 1
#define HSE_PREDIV_VALUE CONCAT_2(RCC_HSE_PREDIV_DIV, HSE_PREDIV_VALUE_)

// </e>
//==========================================================


// <e> HSI_ENABLE - High Speed Internal oscillator
//==========================================================
#define HSI_ENABLE 0

#if HSI_ENABLE
#define HSI_STATE RCC_HSI_ON
#else
#define HSI_STATE RCC_HSI_OFF
#endif

// <o> HSI_VALUE - High Speed Internal oscillator (HSI) value.
//==========================================================
// <i> This value is used by the RCC HAL module to compute the system frequency (when HSI is used as system clock source, directly or through the PLL).  
// <i> Value of the Internal oscillator in Hz
#ifndef  HSI_VALUE 
#define HSI_VALUE    ((uint32_t)8000000) 
#endif 

// </e>
//==========================================================


// <e> LSE_ENABLE - Low Speed External oscillator 
//==========================================================
#define LSE_ENABLE    0

// <o> LSE_STATE
//==========================================================
// <1=> ON
// <2=> BYPASS
#define LSE_STATE_ 1

#if (LSE_ENABLE == 0)
#define LSE_STATE RCC_LSE_OFF
#elif (LSE_STATE_ == 1)
#define LSE_STATE RCC_LSE_ON
#else
#define LSE_STATE RCC_LSE_BYPASS
#endif

// <o> LSE_VALUE - Low Speed External oscillator (LSE) value.
//==========================================================
// <i> This value is used by the UART, RTC HAL module to compute the system frequency
// <i> Value of the External oscillator in Hz
#ifndef  LSE_VALUE
#define LSE_VALUE    ((uint32_t)32768)
#endif 

// <o> LSE_STARTUP_TIMEOUT - Time out for LSE start up, in ms
//==========================================================
//<i> Time out for LSE start up, in ms
#ifndef  LSE_STARTUP_TIMEOUT
#define LSE_STARTUP_TIMEOUT    ((uint32_t)5000)   
#endif 



// </e>
//==========================================================

// <e> LSI_ENABLE - Low Speed Internal oscillator 
//==========================================================
#define LSI_ENABLE 1

#if LSI_ENABLE
#define LSI_STATE RCC_LSI_ON
#else 
#define LSI_STATE RCC_LSI_OFF
#endif


// <o> LSI_VALUE - Internal Low Speed oscillator (LSI) value.
//==========================================================
// <i> Value of the Internal Low Speed oscillator in Hz The real value may vary depending on the variations in voltage and temperature.
// <i> LSI Typical Value in Hz
#ifndef  LSI_VALUE
#define LSI_VALUE    40000U
#endif 


// </e>
//==========================================================


// <e> PLL - Phase Locked Loop
//==========================================================
#define PLL_ENABLE 1

#if PLL_ENABLE
#define PLL_STATE RCC_PLL_ON
#else
#define PLL_STATE RCC_PLL_OFF
#endif

// <o> PLL_SOURCE
//==========================================================
// <0=> HSI_DIV2
// <1=> HSE 
#define PLL_SOURCE_  1
#if PLL_SOURCE_
#define PLL_SOURCE RCC_PLLSOURCE_HSE
#else
#define PLL_SOURCE RCC_PLLSOURCE_HSI_DIV2
#endif

// <o> PLL MUL - Multiplication factor for PLL VCO input clock
//==========================================================
// <i> rang: [2 - 15]
// <i> NOTE: HSE_VALUE * PLL_MUL <= 72(MHz)
// <2-15> 
#define PLL_MUL_ 9
#define PLL_MUL CONCAT_2(RCC_PLL_MUL, PLL_MUL_)

// </e>
//==========================================================



// </h>
//==========================================================

// <h> SYSTEM_CLOCK - CPU, AHB and APB buses clocks
//==========================================================

// <o> SYSCLK_SOURCE - CPU clock source
//==========================================================
// <0x00000000=> HSI
// <0x00000001=> HSE
// <0x00000002=> PLL
#define SYSCLK_SOURCE 0x00000002U

// <o> AHB_CLOCK_DIV - divider factor of SYSCLK to generate AHB clock
//==========================================================
// <1=> DIV1 - not divided
// <2=> DIV2
// <4=> DIV4
// <8=> DIV8
// <16=> DIV16
// <64=> DIV64
// <128=> DIV128
// <256=> DIV256
// <512=> DIV512
#define AHB_CLK_DIV_ 1
#define AHB_CLK_DIV CONCAT_2(RCC_SYSCLK_DIV, AHB_CLK_DIV_)

// <o> APB1_CLOCK_DIV - divider factor of HCLK to generate APB1 clock
//==========================================================
// <1=> DIV1 
// <2=> DIV2
// <4=> DIV4 
// <8=> DIV8 
// <16=> DIV16 
#define APB1_CLK_DIV_ 2
#define APB1_CLK_DIV CONCAT_2(RCC_HCLK_DIV, APB1_CLK_DIV_)

// <o> APB2_CLOCK_DIV - divider factor of HCLK to generate APB2 clock
//==========================================================
// <1=> DIV1 
// <2=> DIV2
// <4=> DIV4 
// <8=> DIV8 
// <16=> DIV16 
#define APB2_CLK_DIV_ 1
#define APB2_CLK_DIV CONCAT_2(RCC_HCLK_DIV, APB2_CLK_DIV_)


// </h>
//==========================================================


// <h> PREPHERAL_CLOCK
//==========================================================

// <e> ADC_CLOCK
//==========================================================
#define ADC_CLOCK_ENABLE 1

// <o> ADC_CLOCK_SOURCE - ADC clock source selection
//==========================================================
// <i> ADC is divided from APB2 clock
// <2=> PCLK_DIV2
// <4=> PCLK_DIV4
// <6=> PCLK_DIV6
// <8=> PCLK_DIV8
#define ADC_CLOCK_SOURCE_ 6
#define ADC_CLOCK_SOURCE CONCAT_2(RCC_ADCPCLK2_DIV, ADC_CLOCK_SOURCE_)

// </e> 
//==========================================================

// <e> RTC_CLOCK
//==========================================================
#define RTC_CLOCK_ENABLE 1

// <o> RTC_CLOCK_SOURCE
//==========================================================
// <1=> LSE
// <2=> LSI
// <3=> HSE_DIV128
#define RTC_CLOCK_SOURCE_ 3

#if !RTC_CLOCK_ENABLE
#define RTC_CLOCK_SOURCE RCC_RTCCLKSOURCE_NO_CLK
#elif (RTC_CLOCK_SOURCE_ == 1)
#define RTC_CLOCK_SOURCE RCC_RTCCLKSOURCE_LSE
#elif (RTC_CLOCK_SOURCE_ == 2)
#define RTC_CLOCK_SOURCE RCC_RTCCLKSOURCE_LSI
#elif (RTC_CLOCK_SOURCE_ == 3)
#define RTC_CLOCK_SOURCE RCC_RTCCLKSOURCE_HSE_DIV128
#endif

// </e> 
//==========================================================


// </h>
//==========================================================

// </h>
//==========================================================


// <e> HAL_ENABLE
//==========================================================
#define HAL_ENABLED 1
#if HAL_ENABLED
#define HAL_MODULE_ENABLED
#endif

// <h> HAL_SYSTEM_CONFIG
//==========================================================

// <o> VDD_VALUE - Value of VDD in mv
//==========================================================
#ifndef VDD_VALUE                   
#define VDD_VALUE 3300
#endif
// <o> TICK_INT_PRIORITY - tick interrupt priority
//==========================================================
#ifndef TICK_INT_PRIORITY                
#define TICK_INT_PRIORITY 0
#endif

// <q> USE_RTOS
//==========================================================
#ifndef USE_RTOS                     
#define USE_RTOS 0
#endif

// <q> PREFETCH_ENABLE
//==========================================================
#ifndef PREFETCH_ENABLE              
#define PREFETCH_ENABLE 0
#endif

//<q> USE_SPI_CRC - Use to activate CRC feature inside HAL SPI Driver 
//==========================================================
//<i> Activated: CRC code is present inside driver
//<i> Deactivated: CRC code cleaned from driver
#ifndef USE_SPI_CRC
#define USE_SPI_CRC 0
#endif



// </h>
//==========================================================


// <h> HAL_DRIVER_ENABLE
//==========================================================

// <e> HAL_ADC
//==========================================================
#define HAL_ADC_ENABLE 1
#if HAL_ADC_ENABLE 
#define HAL_ADC_MODULE_ENABLED
#endif

// <q> USE_HAL_ADC_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_ADC_REGISTER_CALLBACKS
#define USE_HAL_ADC_REGISTER_CALLBACKS 0
#endif



// </e> 
//========================================================== 
// <e> HAL_CAN
//==========================================================
#define HAL_CAN_ENABLE 0
#if HAL_CAN_ENABLE 
#define HAL_CAN_MODULE_ENABLED
#endif

// <q> USE_HAL_CAN_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_CAN_REGISTER_CALLBACKS
#define USE_HAL_CAN_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_CAN_LEGACY
//==========================================================
#define HAL_CAN_LEGACY_ENABLE 0
#if HAL_CAN_LEGACY_ENABLE 
#define HAL_CAN_LEGACY_MODULE_ENABLED
#endif
//
// </e> 
//========================================================== 
// <e> HAL_CEC
//==========================================================
#define HAL_CEC_ENABLE 0
#if HAL_CEC_ENABLE 
#define HAL_CEC_MODULE_ENABLED
#endif

// <q> USE_HAL_CEC_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_CEC_REGISTER_CALLBACKS
#define USE_HAL_CEC_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_CORTEX
//==========================================================
#define HAL_CORTEX_ENABLE 1
#if HAL_CORTEX_ENABLE 
#define HAL_CORTEX_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_CRC
//==========================================================
#define HAL_CRC_ENABLE 0
#if HAL_CRC_ENABLE 
#define HAL_CRC_MODULE_ENABLED
#endif
//
// </e> 
//========================================================== 
// <e> HAL_DAC
//==========================================================
#define HAL_DAC_ENABLE 0
#if HAL_DAC_ENABLE 
#define HAL_DAC_MODULE_ENABLED
#endif

// <q> USE_HAL_DAC_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_DAC_REGISTER_CALLBACKS
#define USE_HAL_DAC_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_DMA
//==========================================================
#define HAL_DMA_ENABLE 1
#if HAL_DMA_ENABLE 
#define HAL_DMA_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_ETH
//==========================================================
#define HAL_ETH_ENABLE 0
#if HAL_ETH_ENABLE 
#define HAL_ETH_MODULE_ENABLED
#endif

// <q> USE_HAL_ETH_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_ETH_REGISTER_CALLBACKS
#define USE_HAL_ETH_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_EXTI
//==========================================================
#define HAL_EXTI_ENABLE 1
#if HAL_EXTI_ENABLE 
#define HAL_EXTI_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_FLASH
//==========================================================
#define HAL_FLASH_ENABLE 1
#if HAL_FLASH_ENABLE 
#define HAL_FLASH_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_GPIO
//==========================================================
#define HAL_GPIO_ENABLE 1
#if HAL_GPIO_ENABLE 
#define HAL_GPIO_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_HCD
//==========================================================
#define HAL_HCD_ENABLE 0
#if HAL_HCD_ENABLE 
#define HAL_HCD_MODULE_ENABLED
#endif

// <q> USE_HAL_HCD_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_HCD_REGISTER_CALLBACKS
#define USE_HAL_HCD_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_I2C
//==========================================================
#define HAL_I2C_ENABLE 0
#if HAL_I2C_ENABLE 
#define HAL_I2C_MODULE_ENABLED
#endif

// <q> USE_HAL_I2C_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_I2C_REGISTER_CALLBACKS
#define USE_HAL_I2C_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_I2S
//==========================================================
#define HAL_I2S_ENABLE 0
#if HAL_I2S_ENABLE 
#define HAL_I2S_MODULE_ENABLED
#endif

// <q> USE_HAL_I2S_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_I2S_REGISTER_CALLBACKS
#define USE_HAL_I2S_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_IRDA
//==========================================================
#define HAL_IRDA_ENABLE 0
#if HAL_IRDA_ENABLE 
#define HAL_IRDA_MODULE_ENABLED
#endif

// <q> USE_HAL_IRDA_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_IRDA_REGISTER_CALLBACKS
#define USE_HAL_IRDA_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_IWDG
//==========================================================
#define HAL_IWDG_ENABLE 1
#if HAL_IWDG_ENABLE 
#define HAL_IWDG_MODULE_ENABLED
#endif
//
// </e> 
//========================================================== 
// <e> HAL_MMC
//==========================================================
#define HAL_MMC_ENABLE 0
#if HAL_MMC_ENABLE 
#define HAL_MMC_MODULE_ENABLED
#endif

// <q> USE_HAL_MMC_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_MMC_REGISTER_CALLBACKS
#define USE_HAL_MMC_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//==========================================================
// <e> HAL_NAND
//==========================================================
#define HAL_NAND_ENABLE 0
#if HAL_NAND_ENABLE 
#define HAL_NAND_MODULE_ENABLED
#endif

// <q> USE_HAL_NAND_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_NAND_REGISTER_CALLBACKS
#define USE_HAL_NAND_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_NOR
//==========================================================
#define HAL_NOR_ENABLE 0
#if HAL_NOR_ENABLE 
#define HAL_NOR_MODULE_ENABLED
#endif

// <q> USE_HAL_NOR_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_NOR_REGISTER_CALLBACKS
#define USE_HAL_NOR_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_PCCARD
//==========================================================
#define HAL_PCCARD_ENABLE 0
#if HAL_PCCARD_ENABLE 
#define HAL_PCCARD_MODULE_ENABLED
#endif

// <q> USE_HAL_PCCARD_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_PCCARD_REGISTER_CALLBACKS
#define USE_HAL_PCCARD_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_PCD
//==========================================================
#define HAL_PCD_ENABLE 0
#if HAL_PCD_ENABLE 
#define HAL_PCD_MODULE_ENABLED
#endif

// <q> USE_HAL_PCD_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_PCD_REGISTER_CALLBACKS
#define USE_HAL_PCD_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_PWR
//==========================================================
#define HAL_PWR_ENABLE 1
#if HAL_PWR_ENABLE 
#define HAL_PWR_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_RCC
//==========================================================
#define HAL_RCC_ENABLE 1
#if HAL_RCC_ENABLE 
#define HAL_RCC_MODULE_ENABLED
#endif

// </e> 
//========================================================== 
// <e> HAL_RTC
//==========================================================
#define HAL_RTC_ENABLE 0
#if HAL_RTC_ENABLE 
#define HAL_RTC_MODULE_ENABLED
#endif

// <q> USE_HAL_RTC_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_RTC_REGISTER_CALLBACKS
#define USE_HAL_RTC_REGISTER_CALLBACKS 0
#endif



// </e> 
//========================================================== 
// <e> HAL_SD
//==========================================================
#define HAL_SD_ENABLE 0
#if HAL_SD_ENABLE 
#define HAL_SD_MODULE_ENABLED
#endif

// <q> USE_HAL_SD_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_SD_REGISTER_CALLBACKS
#define USE_HAL_SD_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_SMARTCARD
//==========================================================
#define HAL_SMARTCARD_ENABLE 0
#if HAL_SMARTCARD_ENABLE 
#define HAL_SMARTCARD_MODULE_ENABLED
#endif

// <q> USE_HAL_SMARTCARD_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_SMARTCARD_REGISTER_CALLBACKS
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_SPI
//==========================================================
#define HAL_SPI_ENABLE 0
#if HAL_SPI_ENABLE 
#define HAL_SPI_MODULE_ENABLED
#endif

// <q> USE_HAL_SPI_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_SPI_REGISTER_CALLBACKS
#define USE_HAL_SPI_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_SRAM
//==========================================================
#define HAL_SRAM_ENABLE 0
#if HAL_SRAM_ENABLE 
#define HAL_SRAM_MODULE_ENABLED
#endif

// <q> USE_HAL_SRAM_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_SRAM_REGISTER_CALLBACKS
#define USE_HAL_SRAM_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_TIM
//==========================================================
#define HAL_TIM_ENABLE 1
#if HAL_TIM_ENABLE 
#define HAL_TIM_MODULE_ENABLED
#endif

// <q> USE_HAL_TIM_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_TIM_REGISTER_CALLBACKS
#define USE_HAL_TIM_REGISTER_CALLBACKS 0
#endif



// </e> 
//========================================================== 
// <e> HAL_TIMER - hal timebase
//==========================================================
#define HAL_TIMER_ENABLE 1

// <o> HAL_TIMER_TIMEBASE - the time base use for app_timer
//==========================================================
//<0=> RTC
//<1=> TIM
#define CFG_HAL_TIMER_TIMEBASE 1

//<o> HAL_TIMER_TIMEBASE_IRQ_PRIORITY - the irq priority of hardware timer used by app_timer
//<0-15> 
#define CFG_HAL_TIMEBASE_IRQ_PRIORITY    6    

//<o> HAL_TIMER_TIM_ID - the hardware timer used by app_timer
//<i> The hardware timer used by app_timer, can be [2-7]. e.g if use TIM6, this value will be 6
//<i> Recommend use basic timer TIM6 or TIM7
//<6=> TIM6
//<7=> TIM7
#define CFG_HAL_TIMER_TIM_ID    6   


// </e> 
//========================================================== 
// <e> HAL_UART
//==========================================================
#define HAL_UART_ENABLE 1
#if HAL_UART_ENABLE 
#define HAL_UART_MODULE_ENABLED
#endif

// <q> USE_HAL_UART_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_UART_REGISTER_CALLBACKS
#define USE_HAL_UART_REGISTER_CALLBACKS 0
#endif



// </e> 
//========================================================== 
// <e> HAL_USART
//==========================================================
#define HAL_USART_ENABLE 0
#if HAL_USART_ENABLE 
#define HAL_USART_MODULE_ENABLED
#endif

// <q> USE_HAL_USART_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_USART_REGISTER_CALLBACKS
#define USE_HAL_USART_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 
// <e> HAL_WWDG
//==========================================================
#define HAL_WWDG_ENABLE 0
#if HAL_WWDG_ENABLE 
#define HAL_WWDG_MODULE_ENABLED
#endif

// <q> USE_HAL_WWDG_REGISTER_CALLBACKS
//==========================================================
#ifndef USE_HAL_WWDG_REGISTER_CALLBACKS
#define USE_HAL_WWDG_REGISTER_CALLBACKS 0
#endif


//
// </e> 
//========================================================== 

// </h>
//==========================================================


// </e>
//==========================================================




// <h> DEBUG
//==========================================================

//<q> TEST_CODE_ENABLE 
#ifndef TEST_CODE_ENABLE
#define TEST_CODE_ENABLE 1
#endif

//<q> USE_FULL_ASSERT - param check and assert
#ifndef USE_FULL_ASSERT
#define USE_FULL_ASSERT 1
#endif





// </h>
//==========================================================


// <h> SEGGER_RTT
//==========================================================

// <e> segger_rtt - SEGGER RTT ENALE
//==========================================================
#ifndef SEGGER_RTT_ENABLE
#define SEGGER_RTT_ENABLE 1
#endif

// <o> SEGGER_RTT_CONFIG_BUFFER_SIZE_UP - Size of upstream buffer.
// <i> default: 1024SEGGER_RTT_CONFIG_BUFFER_SIZE_UP
#ifndef SEGGER_RTT_CONFIG_BUFFER_SIZE_UP
#define SEGGER_RTT_CONFIG_BUFFER_SIZE_UP 512
#endif

// <o> SEGGER_RTT_CONFIG_MAX_NUM_UP_BUFFERS - Size of upstream buffer. 
// <i> default: 3
#ifndef SEGGER_RTT_CONFIG_MAX_NUM_UP_BUFFERS
#define SEGGER_RTT_CONFIG_MAX_NUM_UP_BUFFERS 2
#endif

// <o> SEGGER_RTT_CONFIG_BUFFER_SIZE_DOWN - Size of upstream buffer. 
// <i> default: 16
#ifndef SEGGER_RTT_CONFIG_BUFFER_SIZE_DOWN
#define SEGGER_RTT_CONFIG_BUFFER_SIZE_DOWN 16
#endif

// <o> SEGGER_RTT_CONFIG_MAX_NUM_DOWN_BUFFERS - Size of upstream buffer. 
// <i> default: 3
#ifndef SEGGER_RTT_CONFIG_MAX_NUM_DOWN_BUFFERS
#define SEGGER_RTT_CONFIG_MAX_NUM_DOWN_BUFFERS 2
#endif

// <o> SEGGER_RTT_CONFIG_MAX_NUM_DOWN_BUFFERS - Size of upstream buffer. 
// <i> default: 64
#ifndef SEGGER_RTT_CONFIG_PRINTF_BUFFER_SIZE
#define SEGGER_RTT_CONFIG_PRINTF_BUFFER_SIZE    64
#endif

// <o> SEGGER_RTT_CONFIG_DEFAULT_MODE  - RTT behavior if the buffer is full.

// <i> The following modes are supported:
// <i> - SKIP  - Do not block, output nothing.
// <i> - TRIM  - Do not block, output as much as fits.
// <i> - BLOCK - Wait until there is space in the buffer.
// <0=> SKIP (default)
// <1=> TRIM 
// <2=> BLOCK_IF_FIFO_FULL 

#ifndef SEGGER_RTT_CONFIG_DEFAULT_MODE
#define SEGGER_RTT_CONFIG_DEFAULT_MODE 0
#endif

// </e> 
//==========================================================
// </h>
//==========================================================

// <<< end of configuration section >>>





#endif //SDK_CONFIG_H

