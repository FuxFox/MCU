
#define CFG_LOG_LEVEL APP_LOG_LEVEL_ERROR
#include "app_config.h"
#include "app_timer.h"
#include "app_log.h"
#include "hal_delay.h"
#include "hal_gpio.h"
#include "printf.h"

#define PIN_LED_R 13
#define PIN_LED_G 12
#define PIN_LED_B 14

static app_timer_id_t sec_timer;
static void sec_timer_task(void* param) {
	static uint8_t rgb = 0b111;

	hal_gpio_pin_write(PIN_LED_R, (~rgb & 0x01));
	hal_gpio_pin_write(PIN_LED_G, (~rgb & 0x02) >> 1);
	hal_gpio_pin_write(PIN_LED_B, (~rgb & 0x04) >> 2);
	rgb++;
}

int main(void) {
	hal_gpio_init();
	hal_gpio_cfg_output(PIN_LED_R);
	hal_gpio_cfg_output(PIN_LED_G);
	hal_gpio_cfg_output(PIN_LED_B);
	hal_gpio_pin_write(PIN_LED_R, HAL_GPIO_HIGH);
	hal_gpio_pin_write(PIN_LED_G, HAL_GPIO_HIGH);
	hal_gpio_pin_write(PIN_LED_B, HAL_GPIO_HIGH);

	app_timer_init();
	sec_timer = app_timer_create(APP_TIMER_MODE_REPEATED, sec_timer_task, false);
	app_timer_start(sec_timer, 1000, NULL);
	uint64_t i = 0;
	while (1) {
		app_timer_process_poll();
		hal_delay_ms(500);
		APP_LOG_DEBUG("debug");
		APP_LOG_ERROR("err");
		APP_LOG_WARNING("warning");
		APP_LOG_INFO("hello word: %d", i++);
	}
}
