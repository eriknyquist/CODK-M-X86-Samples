#include "wiring_digital.h"
#include "arduino.h"

#include <zephyr.h>

#include <misc/printk.h>

#include <device.h>
#include <gpio.h>
#include <misc/util.h>

#include <pinmux.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

//#define GPIO_DRV_NAME CONFIG_GPIO_QMSI_0_NAME
#if defined(CONFIG_GPIO_DW_0)
#define GPIO_DRV_NAME CONFIG_GPIO_DW_0_NAME
#elif defined(CONFIG_GPIO_QMSI_0)
#define GPIO_DRV_NAME CONFIG_GPIO_QMSI_0_NAME
#elif defined(CONFIG_GPIO_ATMEL_SAM3)
#define GPIO_DRV_NAME CONFIG_GPIO_ATMEL_SAM3_PORTB_DEV_NAME
#else
#error "Unsupported GPIO driver"
#endif

#define PULL_UP 1

struct device *gpio_dev;

void digitalInit()
{
	gpio_dev= device_get_binding(GPIO_DRV_NAME);
}

void pinMode(uint8_t pin, uint8_t mode)
{
	struct device *p_mux = device_get_binding((char*)"PINMUX_DEV");
	pinmux_pin_set(p_mux, zephyrDescription[pin].pinMux, zephyrDescription[pin].muxMode); //set to default gpio mux mode

	if(zephyrDescription[pin].zephyrPin2 != INVALID) 
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin2, (GPIO_DIR_IN)); //HIGH-Z
	}

	if(mode == OUTPUT)
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin1, (GPIO_DIR_OUT));
	}
	else if(mode == INPUT)
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin1, (GPIO_DIR_IN));
	}
	else if(mode == INPUT_PULLUP)
	{
		gpio_pin_configure(gpio_dev, zephyrDescription[pin].zephyrPin1, (GPIO_DIR_IN | PULL_UP));
	}
}

void digitalWrite(uint8_t pin, uint8_t level)
{
	gpio_pin_write(gpio_dev, zephyrDescription[pin].zephyrPin1, level);
}

int digitalRead(uint8_t pin)
{
	int ret = 0;
	gpio_pin_read(gpio_dev, zephyrDescription[pin].zephyrPin1, &ret);
	return ret;
}


