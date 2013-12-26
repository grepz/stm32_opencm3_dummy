#ifndef __BL_LED_H
#define __BL_LED_H

#define BOARD_PIN_LED1		        GPIO12
#define BOARD_PIN_LED2	                GPIO13
#define BOARD_PIN_LED3	                GPIO14
#define BOARD_PIN_LED4	                GPIO15
#define BOARD_PORT_LEDS		        GPIOD
#define BOARD_CLOCK_LEDS		RCC_AHB1ENR_IOPDEN
#define BOARD_LED_ON			gpio_set
#define BOARD_LED_OFF			gpio_clear

#define BOARD_LED_ON			gpio_set
#define BOARD_LED_OFF			gpio_clear

enum {
    BOARD_LED_ACTIVITY = 0,
    BOARD_LED_ERROR,
    BOARD_LED_APP,
    BOARD_LED_USB
};

void led_on(unsigned led);
void led_off(unsigned led);
void led_toggle(unsigned led);
void led_gpio_init(void);

#endif /* __BL_LED_H */
