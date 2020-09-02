/*!*****************************************************************************
* @file     main.c
* @brief    main for STM32
* @author   FuxFox
* @version  V1.0
* @date  	2019/12/20
*******************************************************************************/
#ifndef MAIN_C
#define MAIN_C

#include "main.h"
#include "app_log.h"

/*!*****************************************************************************
* @brief     The application entry point.
* @param[in] void
* @return    int
*******************************************************************************/
int main(void)
{
    main_preinit();

    driver_init();
    module_init();
    ui_init();

    LOG_DEBUG("system start");

    while (1)
    {
        app_timer_process_poll();
        module_baseloop_task();
        ui_baseloop_task();
    }
}

static void main_preinit(void)
{
    app_log_init();

    SystemClock_Config();
    HAL_Init();

    app_delay_init();
    HAL_ERROR_CHECK(app_timer_init());

    app_gpio_init();
}

/*!*****************************************************************************
* @brief     System Clock Configuration
* @param[in] void
* @return    void
*******************************************************************************/
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };
    HAL_StatusTypeDef error_code;

    /** Initializes the Oscillator
    */
#if HSE_ENABLE
    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = HSE_STATE;
    RCC_OscInitStruct.HSEPredivValue = HSE_PREDIV_VALUE;
#endif
#if HSI_ENABLE
    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = HSI_STATE;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
#endif
#if LSE_ENABLE
    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = LSE_STATE;
#endif
#if LSI_ENABLE
    RCC_OscInitStruct.OscillatorType |= RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.LSIState = LSI_STATE;
#endif
#if PLL_ENABLE
    RCC_OscInitStruct.PLL.PLLState = PLL_STATE;
    RCC_OscInitStruct.PLL.PLLSource = PLL_SOURCE;
    RCC_OscInitStruct.PLL.PLLMUL = PLL_MUL;
#endif
    error_code = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    HAL_ERROR_CHECK(error_code);

    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = SYSCLK_SOURCE;
    RCC_ClkInitStruct.AHBCLKDivider = AHB_CLK_DIV;
    RCC_ClkInitStruct.APB1CLKDivider = APB1_CLK_DIV;
    RCC_ClkInitStruct.APB2CLKDivider = APB2_CLK_DIV;

    error_code = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
    HAL_ERROR_CHECK(error_code);

    /** Initializes the Peripheral clocks
    */
#if ADC_CLOCK_ENABLE
    PeriphClkInit.PeriphClockSelection |= RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = ADC_CLOCK_SOURCE;
#endif
#if RTC_CLOCK_ENABLE
    PeriphClkInit.PeriphClockSelection |= RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RTC_CLOCK_SOURCE;
#endif
    error_code = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
    HAL_ERROR_CHECK(error_code);
}


#endif // MAIN_C
