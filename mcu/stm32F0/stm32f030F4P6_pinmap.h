/*!*****************************************************************************
* @file     stm32f030F4P6_pinmap.h
* @brief	Pin number to gpio mapping, used for hal_gpio
* @author   FuxFox
* @version  V1.0
* @date     2019/10/12
*******************************************************************************/
#ifndef STM32F1XXVXX_PINMAP_H
#define STM32F1XXVXX_PINMAP_H

#define NO_GPIO            0xFF
#define NO_GPIO_PORT    ((GPIO_TypeDef *)NO_GPIO)
#define CHIP_PIN_NUM    20

#define PIN_TO_PORT_MAP {                                                                                 \
/*pin 01~05*/        NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT, NO_GPIO_PORT,                \
/*pin 06~13*/        GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,                              \
/*pin 14   */        GPIOB,                                                                               \
/*pin 15~16*/        NO_GPIO_PORT, NO_GPIO_PORT,                \
/*pin 17~20*/        GPIOA, GPIOA, GPIOA, GPIOA                                                          \
}

#define PIN_TO_GPIOPIN_MAP {                                       \
/*pin 01~05*/        NO_GPIO, NO_GPIO, NO_GPIO, NO_GPIO, NO_GPIO, \
/*pin 06~13*/        0, 1, 2, 3, 4, 5, 6, 7,               \
/*pin 14   */        1,                                   \
/*pin 15~16*/        NO_GPIO, NO_GPIO, \
/*pin 17~20*/        9, 10, 13, 14                            \
}


#endif // STM32F1XXVXX_PINMAP_H
