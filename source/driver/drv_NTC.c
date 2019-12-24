/*******************************************************************************
 * Module: drv_NTC
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/11/20 13:58          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_NTC.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/11/20
  *******************************************************************************/
#ifndef DRV_NTC_C
#define DRV_NTC_C

#include "drv_NTC.h"
#include "math.h"

ADC_HandleTypeDef m_hadc;


static bool m_is_adc_init = false;

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_NTC_init(drv_NTC_instance_t* instance)
{
    HAL_StatusTypeDef err_code;

    app_gpio_cfg_analog(instance->input_pin);

    if (!m_is_adc_init)
    {
        m_is_adc_init = true;

        CONCAT_3(__HAL_RCC_ADC, DRV_NTC_ADC_ID, _CLK_ENABLE(););

        m_hadc.Instance = CONCAT_2(ADC, DRV_NTC_ADC_ID);
        m_hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
        m_hadc.Init.ContinuousConvMode = DISABLE;
        m_hadc.Init.DiscontinuousConvMode = DISABLE;
        m_hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        m_hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        m_hadc.Init.NbrOfConversion = 1;

        err_code = HAL_ADC_Init(&m_hadc);
        HAL_ERROR_CHECK(err_code);
    }
}

/*!*****************************************************************************
\brief      get current temperature

\param[in]    void
\return     float
******************************************************************************/
float drv_NTC_get_temperature(drv_NTC_instance_t* instance)
{
    float Rt;
    float temp;
    HAL_StatusTypeDef err_code;
    ADC_ChannelConfTypeDef sConfig = {
            .Channel = instance->adc_channel,
            .Rank = ADC_REGULAR_RANK_1,
            .SamplingTime = ADC_SAMPLETIME_239CYCLES_5//about 21 us per conversion
    };

    err_code = HAL_ADC_ConfigChannel(&m_hadc, &sConfig);
    HAL_ERROR_CHECK(err_code);

    Rt = drv_NTC_get_resistance();
    //like this R0=5000, T0=273.15+25,B=3470, RT=5000*EXP(3470*(1/T1-1/(273.15+25)),  
    // T1 = 1 / (ln(Rt/R0)/B + (1/T0))
    temp = log(Rt / DRV_NTC_R0) / DRV_NTC_B;//ln(Rt/R0)/B
    temp += (1 / DRV_NTC_T0);
    temp = 1 / (temp);
    temp -= DRV_NTC_K0;

    return temp;
}

/*!*****************************************************************************
\brief      calculate current NTC resistance

\param[in]    void
\return     uint32_t    NTC resistance in Ohm
******************************************************************************/
static uint32_t drv_NTC_get_resistance(void)
{
    uint32_t result = 0;

    for (uint8_t i = 0; i < DRV_NTC_AVERAGE_TIMES; i++)
    {
        HAL_ADC_Start(&m_hadc);
        HAL_ADC_PollForConversion(&m_hadc, 5);
        result += HAL_ADC_GetValue(&m_hadc);
    }
    //calculate voltage Ut
    result /= DRV_NTC_AVERAGE_TIMES;
    result *= VDD_VALUE;//3.3v
    result /= 4096;//2^12

    //Ut/Rt = (Vcc - Ut)/Rd = I
    //Rt = Ut * Rd / (Vcc - Ut)
    result = result * DRV_NTC_DIVIDER_RESISTOR / (VDD_VALUE - result);

    return result;
}


#endif // DRV_NTC_C
