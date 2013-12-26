#include <stdlib.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

#include "led.h"
#include "usb.h"
#include "bl.h"

static void __init(void)
{
    led_gpio_init();
    usb_gpio_init();
    /* Pwr control clock */
    rcc_peripheral_enable_clock(&RCC_APB1ENR, RCC_APB1ENR_PWREN);
}

int main(void)
{
    usbd_device *usbd;

    __init();

    /* Show that hardware is set up */
    led_on(BOARD_LED_ACTIVITY);
    usbd = usbd_create();
    if (!usbd) {
        led_on(BOARD_LED_ERROR);
        for (;;);
    }

    while (1) {
        /* Check if usb is connected */
        if (usb_connect()) {
            led_on(BOARD_LED_USB);
            usbd_poll(usbd);
        } else
            led_off(BOARD_LED_USB);
    }

    return 0;
}
