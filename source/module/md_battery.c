/*******************************************************************************
 *
 * Module: md_battery
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox	      2019/07/26 15:30          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     md_battery.c
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date  	 2019/07/26
  *******************************************************************************/
#ifndef MD_BATTERY_C
#define MD_BATTERY_C

#include "md_battery.h"

APP_TIMER_DEF(m_battery_detect_timer_id);  /**< Polling timer id. */

typedef struct
{
    uint16_t sample_buffer[MD_BATTERY_DETECT_SAMPLE_RATE];
    uint16_t average_voltage;
    uint16_t battery_mah;	/*!< current electric quantity, unit: mah.  */
    uint8_t buffer_index;
    uint8_t battery_percent;
} md_battery_sta_struct;

static md_battery_sta_struct m_battery_sta;
static battery_change_callback m_notice_callback;
static const uint16_t m_voltage_percent_table[11] = {
    //real-0%	 0%,  10%, 20%, 30%, 40%, 50%, 60%, 70%, 80%, 90%, 100%
    /*300*/  MD_BATTERY_LEST_VOLTAGE, 351, 358, 362, 365, 368, 373, 379, 387, 397, MD_BATTERY_FULL_VOLTAGE
};

/*!*****************************************************************************
\brief  	battery voltage level detect init
\details
\param[in]	battery_change_callback		Will be call if battery voltage change greater than 1%. Can be NULL.
\return     void
******************************************************************************/
void md_battery_init(battery_change_callback callback)
{
#if MD_BATTERY_CHARGING_SUPPORT
    nrf_gpio_cfg_input(MD_BATTERY_CHARGE_DETECT_PIN, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(MD_BATTERY_CHARGE_FULL_PIN, NRF_GPIO_PIN_PULLUP);
#endif
    m_notice_callback = callback;

    md_battery_adc_config();
    md_battery_get_first_data();

    app_timer_create(&m_battery_detect_timer_id, APP_TIMER_MODE_REPEATED, md_battery_detect_TimerHandler);
    app_timer_start(m_battery_detect_timer_id, APP_TIMER_TICKS(MD_BATTERY_SAMPLE_INTERVAL_MS), NULL);
}

//saadc callback function
void md_battery_saadc_callback(nrf_drv_saadc_evt_t const* p_event) {/*do nothing*/ }
/*!*****************************************************************************
\brief  	adc init
\details
\param[in]	void
\return     void
******************************************************************************/
void md_battery_adc_config(void)
{
    ret_code_t err_code;

    nrf_saadc_channel_config_t battery_saadc = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(CONCAT_2(NRF_SAADC_INPUT_AIN, MD_BATTERY_DETECT_ADC_CHANNEL));

    err_code = nrf_drv_saadc_init(NULL, md_battery_saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(MD_BATTERY_DETECT_ADC_CHANNEL, &battery_saadc);
    APP_ERROR_CHECK(err_code);
}

/*!*****************************************************************************
\brief  	get first data when power on
\details
\param[in]	void
\return     void
******************************************************************************/
static void md_battery_get_first_data(void)
{
    uint8_t i;
    uint32_t sum;

    memset(&m_battery_sta, 0, sizeof(m_battery_sta));
    for (i = 0, sum = 0; i < MD_BATTERY_DETECT_SAMPLE_RATE; i++)
    {
        nrf_delay_ms(80);
        m_battery_sta.sample_buffer[i] = md_battery_get_sample();
        sum += m_battery_sta.sample_buffer[i];
    }

    m_battery_sta.average_voltage = sum / MD_BATTERY_DETECT_SAMPLE_RATE;
    if (md_battery_is_charging())
    {
        m_battery_sta.average_voltage += MD_BATTERY_CHARGING_VOLTAGE_CALIBRATE;
    }
    m_battery_sta.battery_percent = md_battery_get_percentEx();
    m_battery_sta.battery_mah = MD_BATTERY_CAPABILITY * m_battery_sta.battery_percent / 100;
    NRF_LOG_DEBUG("battery: %dV , %d%%, %dmah\r\n", m_battery_sta.average_voltage, m_battery_sta.battery_percent, m_battery_sta.battery_mah);
}

/*!*****************************************************************************
\brief  	is charging?
\details
\param[in]	void
\return     bool TRUE£ºcharging£¬FALSE£ºno charging
******************************************************************************/
bool md_battery_is_charging(void)
{
#if MD_BATTERY_CHARGING_SUPPORT
    return !nrf_gpio_pin_read(MD_BATTERY_CHARGE_DETECT_PIN);
#else	
    return false;
#endif

}

/*!*****************************************************************************
\brief  	get average voltage
\details
\param[in]	void
\return     int16_t voltage, unit: 10mV
******************************************************************************/
uint16_t md_battery_GetAverageVoltage(void)
{
    uint8_t i = 0;
    uint32_t sum = 0;

    if (md_battery_is_charging())
    {
        m_battery_sta.battery_mah += MD_BATTERY_CHARGING_CURRENT * (MD_BATTERY_SAMPLE_INTERVAL_MS * MD_BATTERY_DETECT_SAMPLE_RATE / 1000) / 3600;
        if (m_battery_sta.battery_mah >= MD_BATTERY_CAPABILITY)
        {
            m_battery_sta.battery_mah = MD_BATTERY_CAPABILITY - 1;
        }
        m_battery_sta.battery_percent = (uint32_t)m_battery_sta.battery_mah * 100 / MD_BATTERY_CAPABILITY;
        i = m_battery_sta.battery_percent / 10;
        m_battery_sta.average_voltage = m_voltage_percent_table[i] + (m_voltage_percent_table[i + 1] - m_voltage_percent_table[i]) * (m_battery_sta.battery_percent % 10) / 10;
// 				for (i = 0; i < MD_BATTERY_DETECT_SAMPLE_RATE; i++)
// 						sum += m_battery_sta.sample_buffer[i];
// 
// 				m_battery_sta.average_voltage = sum / MD_BATTERY_DETECT_SAMPLE_RATE + MD_BATTERY_CHARGING_VOLTAGE_CALIBRATE;

    }
    else
    {
        for (i = 0; i < MD_BATTERY_DETECT_SAMPLE_RATE; i++)
            sum += m_battery_sta.sample_buffer[i];

        m_battery_sta.average_voltage = sum / MD_BATTERY_DETECT_SAMPLE_RATE;
    }

    NRF_LOG_DEBUG("battery: %dV , %d%%, %dmah\r\n", m_battery_sta.average_voltage, m_battery_sta.battery_percent, m_battery_sta.battery_mah);
    return m_battery_sta.average_voltage;
}

/*!*****************************************************************************
\brief  	get average voltage
\details
\param[in]	void
\return     uint16_t	voltage, unit: 10mV
******************************************************************************/
uint16_t md_battery_get_voltage(void)
{
    return m_battery_sta.average_voltage;
}

/*!*****************************************************************************
\brief  	get battery percent
\details
\param[in]	void
\return
******************************************************************************/
uint8_t md_battery_get_percent(void)
{
    return m_battery_sta.battery_percent;
}

/*!*****************************************************************************
\brief  	get battery percent
\details
\return     uint8_t
******************************************************************************/
static uint8_t md_battery_get_percentEx(void)
{
    uint8_t percent = 100;
    uint8_t i;

    if (m_battery_sta.average_voltage <= MD_BATTERY_LEST_VOLTAGE)
    {
        return 0;
    }
#if MD_BATTERY_CHARGING_SUPPORT
    if ((m_battery_sta.average_voltage >= MD_BATTERY_FULL_VOLTAGE) || !nrf_gpio_pin_read(MD_BATTERY_CHARGE_FULL_PIN))
    {
        if (md_battery_is_charging())
        {
            return 99;
        }
        else
#else
    if (m_battery_sta.average_voltage >= MD_BATTERY_FULL_VOLTAGE)
    {
#endif
        {
            return 100;
        }
    }

    for (i = 1; i < ARRAY_SIZE(m_voltage_percent_table); i++)
    {
        if (m_battery_sta.average_voltage <= m_voltage_percent_table[i])
        {
            break;
        }
    }

    percent = (i - 1) * 10;
    percent += (m_battery_sta.average_voltage - m_voltage_percent_table[i - 1]) * 10 / (m_voltage_percent_table[i] - m_voltage_percent_table[i - 1]);

    if (!md_battery_is_charging())
    {
        if ((percent > m_battery_sta.battery_percent) && (m_battery_sta.battery_percent != 0))
        {
            return m_battery_sta.battery_percent;
        }
        else if (percent < m_battery_sta.battery_percent)
        {
            return m_battery_sta.battery_percent--;
        }
    }
    else
    {
        if (percent > m_battery_sta.battery_percent + 1)
        {
            return percent + 1;
        }
    }

    return percent;
}

/*!*****************************************************************************
\brief  	detection timer handler
\details
\param[in]	void * context
\return     void
\author		FuxFox 2019/06/01 11:01
******************************************************************************/
static void md_battery_detect_TimerHandler(void* context)
{
    m_battery_sta.sample_buffer[m_battery_sta.buffer_index++] = md_battery_get_sample();
    uint8_t percent_old;

    if (m_battery_sta.buffer_index >= MD_BATTERY_DETECT_SAMPLE_RATE)
    {
        m_battery_sta.buffer_index = 0;
        percent_old = m_battery_sta.battery_percent;
        m_battery_sta.average_voltage = md_battery_GetAverageVoltage();
        if (!md_battery_is_charging())
        {
            m_battery_sta.battery_percent = md_battery_get_percentEx();
            m_battery_sta.battery_mah = MD_BATTERY_CAPABILITY * m_battery_sta.battery_percent / 100;
        }

        if (m_notice_callback
            && (percent_old != m_battery_sta.battery_percent))
        {
            m_notice_callback(m_battery_sta.battery_percent);
        }
    }
}

/*!*****************************************************************************
\brief  	get battery voltage
\details
\param[in]	void
\return     uint16_t
******************************************************************************/
static uint16_t md_battery_get_sample(void)
{
    nrf_saadc_value_t saadc_val = 0;
    int16_t voltage = MD_BATTERY_FULL_VOLTAGE;  //init battery voltage : 4.2 x 10 = 420

    nrf_drv_saadc_sample_convert(MD_BATTERY_DETECT_ADC_CHANNEL, &saadc_val);
    voltage = (saadc_val * 360) * 2 / 1024;  //3.6 x 100 = 360
//		NRF_LOG_DEBUG("saadc sample saadc_val= %d \r\n", saadc_val);

    return voltage;
}

#endif // MD_BATTERY_C
