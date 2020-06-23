/*******************************************************************************
 *
 * Module: stm32f1xxVxx_pinmap
 *
 * History:
 *    <author>         <time>             <version>             <desc>
 *      FuxFox          2019/10/12 14:22          V1.0             build this file
 *
 *******************************************************************************/
 /*!
  * \file     stm32f1xxVxx_pinmap.h
  * \brief
  * \author   FuxFox
  * \version  V1.0
  * \date       2019/10/12
  *******************************************************************************/
#ifndef STM32F1XXVXX_PINMAP_H
#define STM32F1XXVXX_PINMAP_H

#define NO_GPIO            0xFF
#define NO_ADC_CHANNEL    0xFF
#define NO_GPIO_PORT    ((GPIO_TypeDef *)NO_GPIO)
#define CHIP_PIN_NUM    100

#define PIN_TO_PORT_MAP {                                                                   \
/*pin 01~05*/        GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,                                     \
/*pin 06   */        NO_GPIO_PORT,                                                          \
/*pin 07~09*/        GPIOC, GPIOC, GPIOC,                                                   \
/*pin 10~14*/        NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT,  \
/*pin 15~18*/        GPIOC, GPIOC, GPIOC, GPIOC,                                            \
/*pin 19~22*/        NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT,                \
/*pin 23~26*/        GPIOA, GPIOA, GPIOA, GPIOA,                                            \
/*pin 27~28*/        NO_GPIO_PORT, NO_GPIO_PORT,                                            \
/*pin 29~32*/        GPIOA, GPIOA, GPIOA, GPIOA,                                            \
/*pin 33~34*/        GPIOC, GPIOC,                                                          \
/*pin 35~37*/        GPIOB, GPIOB, GPIOB,                                                   \
/*pin 38~46*/        GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,         \
/*pin 47~48*/        GPIOB, GPIOB,                                                          \
/*pin 49~50*/        NO_GPIO_PORT, NO_GPIO_PORT,                                            \
/*pin 51~54*/        GPIOB, GPIOB, GPIOB, GPIOB,                                            \
/*pin 55~62*/        GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,                \
/*pin 63~66*/        GPIOC, GPIOC, GPIOC, GPIOC,                                            \
/*pin 67~72*/        GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,                              \
/*pin 73~75*/        NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT,                              \
/*pin 76~77*/        GPIOA, GPIOA,                                                          \
/*pin 78~80*/        GPIOC, GPIOC, GPIOC,                                                   \
/*pin 81~88*/        GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,                \
/*pin 89~93*/        GPIOB, GPIOB, GPIOB, GPIOB, GPIOB,                                     \
/*pin 94   */        NO_GPIO_PORT,                                                          \
/*pin 95~96*/        GPIOB, GPIOB,                                                          \
/*pin 97~98*/        GPIOE, GPIOE,                                                          \
/*pin 99~100*/        NO_GPIO_PORT, NO_GPIO_PORT,                                           \
}

#define PIN_TO_GPIOPIN_MAP {                                       \
/*pin 01~05*/        2, 3, 4, 5, 6,                                \
/*pin 06   */        NO_GPIO,                                      \
/*pin 07~09*/        13, 14, 15,                                   \
/*pin 10~14*/        NO_GPIO, NO_GPIO, NO_GPIO, NO_GPIO, NO_GPIO,  \
/*pin 15~18*/        0, 1, 2, 3,                                   \
/*pin 19~22*/        NO_GPIO, NO_GPIO, NO_GPIO, NO_GPIO,           \
/*pin 23~26*/        0, 1, 2, 3,                                   \
/*pin 27~28*/        NO_GPIO, NO_GPIO,                             \
/*pin 29~32*/        4, 5, 6, 7,                                   \
/*pin 33~34*/        4, 5,                                         \
/*pin 35~37*/        0, 1, 2,                                      \
/*pin 38~46*/        7, 8, 9, 10, 11, 12, 13, 14, 15,              \
/*pin 47~48*/        10, 11,                                       \
/*pin 49~50*/        NO_GPIO, NO_GPIO,                             \
/*pin 51~54*/        12, 13, 14, 15,                               \
/*pin 55~62*/        8, 9, 10, 11, 12, 13, 14, 15,                 \
/*pin 63~66*/        6, 7, 8, 9,                                   \
/*pin 67~72*/        8, 9, 10, 11, 12, 13,                         \
/*pin 73~75*/        NO_GPIO, NO_GPIO, NO_GPIO,                    \
/*pin 76~77*/        14, 15,                                       \
/*pin 78~80*/        10, 11, 12,                                   \
/*pin 81~88*/        0, 1, 2, 3, 4, 5, 6, 7,                       \
/*pin 89~93*/        3, 4, 5, 6, 7,                                \
/*pin 94   */        NO_GPIO,                                      \
/*pin 95~96*/        8, 9,                                         \
/*pin 97~98*/        0, 1,                                         \
/*pin 99~100*/        NO_GPIO, NO_GPIO,                            \
}

#define PIN_TO_ADC_CHANNEL_MAP {                                                                                         \
/*pin 01~05*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                     \
/*pin 06   */        NO_ADC_CHANNEL,                                                                                     \
/*pin 07~09*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                     \
/*pin 10~14*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                     \
/*pin 15~18*/        ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13,                                     \
/*pin 19~22*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                     \
/*pin 23~26*/        ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3,                                         \
/*pin 27~28*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                     \
/*pin 29~32*/        ADC_CHANNEL_4, ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7,                                         \
/*pin 33~34*/        ADC_CHANNEL_14, ADC_CHANNEL_15,                                                                     \
/*pin 35~37*/        ADC_CHANNEL_8, ADC_CHANNEL_9, NO_ADC_CHANNEL,                                                       \
/*pin 38~46*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,\
/*pin 47~48*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                     \
/*pin 49~50*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                     \
/*pin 51~54*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                     \
/*pin 55~62*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                \
/*pin 63~66*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                     \
/*pin 67~72*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,     \
/*pin 73~75*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                     \
/*pin 76~77*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                     \
/*pin 78~80*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                     \
/*pin 81~88*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                \
/*pin 89~93*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL, NO_ADC_CHANNEL,                     \
/*pin 94   */        NO_ADC_CHANNEL,                                                                                     \
/*pin 95~96*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                     \
/*pin 97~98*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                     \
/*pin 99~100*/        NO_ADC_CHANNEL, NO_ADC_CHANNEL,                                                                    \
}


#endif // STM32F1XXVXX_PINMAP_H
