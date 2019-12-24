/*******************************************************************************
 * Module: drv_m26
 *           
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/09/03 19:09          V1.0             build this file
 *
 *******************************************************************************/
/*!
 * \file     drv_m26.c
 * \brief    
 * \author   FuxFox
 * \version  V1.0
 * \date       2019/09/03
 *******************************************************************************/
#ifndef DRV_M26_C
#define DRV_M26_C

#include "drv_m26.h"


NRF_SERIAL_DRV_UART_CONFIG_DEF(m_uart0_drv_config,
        DRV_M26_RX_PIN, DRV_M26_TX_PIN,
        DRV_M26_RTS_PIN, DRV_M26_CTS_PIN,
        DRV_M26_UART_HWFC, NRF_UART_PARITY_EXCLUDED,
        DRV_M26_UART_BAUDRATE,
        UART_DEFAULT_CONFIG_IRQ_PRIORITY);

NRF_SERIAL_QUEUES_DEF(serial_queues, SERIAL_FIFO_TX_SIZE, SERIAL_FIFO_RX_SIZE);

NRF_SERIAL_BUFFERS_DEF(serial_buffs, SERIAL_BUFF_TX_SIZE, SERIAL_BUFF_RX_SIZE);

NRF_SERIAL_CONFIG_DEF(serial_config, NRF_SERIAL_MODE_IRQ,
        &serial_queues, &serial_buffs, drv_m26_serial_event_handler, NULL);


NRF_SERIAL_UART_DEF(serial_uart, 0);

static error_handler m_error_handler = NULL;

/*!*****************************************************************************
\brief      initialize
\details
\param[in]    void
\return     bool : TRUE if success
******************************************************************************/
bool drv_m26_init( error_handler handler )
{
        m_error_handler = handler;

        nrf_gpio_cfg_output(DRV_M26_PWRKEY);
        nrf_gpio_pin_clear(DRV_M26_PWRKEY);

        drv_m26_startup();
        return drv_m26_reinit();
}

/*!*****************************************************************************
\brief      shutdown then reboot
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_m26_reboot(void)
{
        drv_m26_shutdown();
        nrf_delay_ms(12000);
        drv_m26_startup();
}

/*!*****************************************************************************
\brief      re-initialize
\details
\param[in]    void
\return     bool TRUE if success
******************************************************************************/
bool drv_m26_reinit(void)
{
        int8_t i = 3;

        while (!drv_m26_is_ready() && i--)
        {
                NRF_LOG_DEBUG("DRV_M26 NO READY!");
                drv_m26_reboot();
        }

        return (i>0);
}

/*!*****************************************************************************
\brief      re-initialize UART
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_m26_serial_reinit(void)
{
        ret_code_t ret;

        NRF_LOG_INFO("M26: serial reinit.");
        nrf_serial_uninit(&serial_uart);
        ret = nrf_serial_init(&serial_uart, &m_uart0_drv_config, &serial_config);
        APP_ERROR_CHECK(ret);
}
/*!*****************************************************************************
\brief      startup
\details    about 6 second
\param[in]    void
\return     void
******************************************************************************/
void drv_m26_startup(void)
{
        ret_code_t ret;

        nrf_gpio_pin_set(DRV_M26_PWRKEY);
        nrf_delay_ms(1100);
        nrf_gpio_pin_clear(DRV_M26_PWRKEY);
        nrf_delay_ms(6000);

        ret = nrf_serial_init(&serial_uart, &m_uart0_drv_config, &serial_config);//after startup, initialize the UART
        APP_ERROR_CHECK(ret);
        NRF_LOG_INFO("M26: startup.");
}

/*!*****************************************************************************
\brief      shutdown
\details        must wait for 12 second before power off
\param[in]    void
\return     void
******************************************************************************/
void drv_m26_shutdown(void)
{
        nrf_serial_uninit(&serial_uart);
        NRF_LOG_INFO("M26: shutdowning...");

        nrf_gpio_pin_set(DRV_M26_PWRKEY);
        nrf_delay_ms(1000);
        nrf_gpio_pin_clear(DRV_M26_PWRKEY);
}

/*!*****************************************************************************
\brief      send and receive data
\details
\param[in]    const char * tx   data buffer to be send
\param[in]    char * rx         receive buffer, must large than (rx_len + 2), can be NULL if no data to be receive.
\param[in]    size_t rx_len     anticipatory length of received data, can be NULL if no data to be receive
\param[in]    uint32_t timeout_ms   max waiting time, in ms
\return     size_t      actual length of received data, return 0 if no data to be receive.
******************************************************************************/
size_t drv_m26_TxRx(const char *tx, char* rx, size_t rx_len, uint32_t timeout_ms)
{
        size_t len = 0;

        NRF_LOG_INFO("M26: send %s", tx);
        drv_m26_clean_rx_queue();
        nrf_serial_write(&serial_uart, tx, strlen(tx), NULL, NRF_SERIAL_MAX_TIMEOUT);
        if ((rx != NULL) && (rx_len != NULL))
        {
                ret_code_t error;

                error = nrf_serial_read(&serial_uart, rx, rx_len, &len, timeout_ms);
                *(rx + len) =  '\0';
//                NRF_LOG_INFO("M26: recieved %s, len: %d, error:%d", (char *)rx, len, error);
                NRF_LOG_INFO("M26: recieved len: %d, error:%d", len, error);
        }

        return len;
}


/*!*****************************************************************************
\brief      clean rx fifo queue 
\details
\param[in]    void
\return     void
******************************************************************************/
void drv_m26_clean_rx_queue(void)
{
        nrf_serial_rx_drain(&serial_uart);
}

/*!*****************************************************************************
\brief      serial driver event handler
\details
\param[in]    struct nrf_serial_s const * p_serial
\param[in]    nrf_serial_event_t event
\return     void
******************************************************************************/
static void drv_m26_serial_event_handler(struct nrf_serial_s const* p_serial, nrf_serial_event_t event)
{
        switch (event)
        {
        case NRF_SERIAL_EVENT_TX_DONE:
                break;
        case NRF_SERIAL_EVENT_RX_DATA:
//                 if (!m_data_sent)
//                 {
//                         NRF_LOG_DEBUG("M26 UNHANDLER EVENT");
//                 }
                break;
        case NRF_SERIAL_EVENT_DRV_ERR:
                NRF_LOG_DEBUG("UART_DRV_ERR");
                m_error_handler(NRF_SERIAL_EVENT_DRV_ERR);
                break;
        case NRF_SERIAL_EVENT_FIFO_ERR:
                NRF_LOG_DEBUG("UART_FIFO_ERR");
                m_error_handler(NRF_SERIAL_EVENT_FIFO_ERR);
                break;
        default:
                break;
        }
}

/*!*****************************************************************************
\brief      is m26 module ready ?
\details
\param[in]    void
\return     bool
******************************************************************************/
bool drv_m26_is_ready(void)
{
        char buff[8];        
        uint8_t i = 5;

        do
        {
                drv_m26_TxRx("AT\r\n", buff, 7, 300);
                if (strstr(buff, "OK"))
                {
                        return true;
                }
        } while (--i);

        return false;
}

#endif // DRV_M26_C
