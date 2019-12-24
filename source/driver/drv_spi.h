/*******************************************************************************
 *
 * Module: drv_spi
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/17 09:59          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     drv_spi.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/17
  *******************************************************************************/
#ifndef DRV_SPI_H
#define DRV_SPI_H

  /*! \defgroup drv_spi_public Public
  \ingroup drv_spi
  \brief      software SPI driver
  \details
  * @{ */

#include "app_config.h"

#include "app_gpio.h"
  //********************************* Module Config *******************************/

#define DRV_SPI_MAX_SPEED_MODE      1       /*!< if 1 use max speed(no delay), if 0 use specified speed(has delay) */



//********************************* Data Type ***********************************/

#define DRV_SPI_CPHA_MASK 0x01      /*!< Phase mask */
#define DRV_SPI_CPOL_MASK 0x02      /*!< Polarity mask */

typedef enum
{
    DRV_SPI_MODE_0,            /*!< Bus idle level low(0), sample at first(0) edge(rise) */
    DRV_SPI_MODE_1,            /*!< Bus idle level low(0), sample at second(1) edge(fall) */
    DRV_SPI_MODE_2,            /*!< Bus idle level high(1), sample at first(0) edge(fall) */
    DRV_SPI_MODE_3,            /*!< Bus idle level high(1), sample at second(1) edge(rise) */
}drv_spi_mode_enum;

typedef enum
{
    DRV_SPI_CS_LEVEL_LOW,
    DRV_SPI_CS_LEVEL_HEIGHT,
}drv_spi_cs_level_t;

typedef struct
{
    uint8_t mosi_pin;          /*!< chip pin number of MCU that connected to MOSI pin of target. Can be NULL if not use */
    uint8_t miso_pin;          /*!< chip pin number of MCU that connected to MISO pin of target. Can be NULL if not use */
    uint8_t sck_pin;           /*!< chip pin number of MCU that connected to SCK pin of target. */
    uint8_t cs_pin;            /*!< chip pin number of MCU that connected to CS pin of target. Can be NULL if not use */
    uint8_t cs_level;          /*!< CS pin active level, \ref drv_spi_cs_level_t */
    drv_spi_mode_enum mode;
    uint32_t speed_kHz;        /*!< SPI speed, unit:kHz, range[1 - 500] */
    uint32_t delay_time;
}drv_spi_instance_struct;


//********************************* Public Interface ****************************/

/*!*****************************************************************************
\brief  	use this macro to quickly define a SPI instance

\param[in]	_name       name of instance
\param[in]	_mosi_pin   chip pin number of MCU that connected to MOSI pin of target 
\param[in]	_miso_pin   chip pin number of MCU that connected to MISO pin of target 
\param[in]	_sck_pin    chip pin number of MCU that connected to SCK pin of target 
\param[in]	_cs_pin     chip pin number of MCU that connected to CS pin of target 
\param[in]	_cs_level   CS pin active level \ref drv_spi_cs_level_t
\param[in]	_mode       bus mode, \ref drv_spi_mode_enum

\param[in]	_speed      SPI speed, unit:kHz, range[1 - 500]. 
*******************************************************************************/
#if DRV_SPI_MAX_SPEED_MODE
#define DRV_SPI_INSTANCE(_name, _mosi_pin, _miso_pin, _sck_pin, _cs_pin, _cs_level, _mode)        \
    static drv_spi_instance_struct _name = {                                                      \
        .mosi_pin = _mosi_pin,                                                                    \
        .miso_pin = _miso_pin,                                                                    \
        .sck_pin = _sck_pin,                                                                      \
        .cs_pin = _cs_pin,                                                                        \
        .cs_level = _cs_level,                                                                    \
        .mode = _mode,                                                                            \
}
#else    
#define DRV_SPI_INSTANCE(_name, _mosi_pin, _miso_pin, _sck_pin, _cs_pin, _cs_level, _mode, _speed)\
    static drv_spi_instance_struct _name = {                                                      \
        .mosi_pin = _mosi_pin,                                                                    \
        .miso_pin = _miso_pin,                                                                    \
        .sck_pin = _sck_pin,                                                                      \
        .cs_pin = _cs_pin,                                                                        \
        .cs_level = _cs_level,                                                                    \
        .mode = _mode,                                                                            \
        .speed_kHz = _speed,                                                                      \
}
#endif

void drv_spi_init(drv_spi_instance_struct* instance);

void drv_spi_TxRx(drv_spi_instance_struct* spi_instance, const uint8_t* tx_buff, uint32_t tx_len, uint8_t* rx_buff, uint32_t rx_len);

#define drv_spi_Tx(instance, data, len)    drv_spi_TxRx(instance,data, len, NULL, NULL)
#define drv_spi_Rx(instance, buff, len)    drv_spi_TxRx(instance,NULL, NULL, buff, len)

//********************************* Private Interface ***************************/





/*! @}*/ //end of group drv_spi
#endif // DRV_SPI_H
