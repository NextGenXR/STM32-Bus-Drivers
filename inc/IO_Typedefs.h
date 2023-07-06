#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_GPIO_BSP_TYPEDEFS_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_GPIO_BSP_TYPEDEFS_H_

#include <stm32yyxx_hal.h>

#include <stm32yyxx_hal_def.h>
#include <stm32yyxx_hal_gpio.h>
#include <stm32yyxx_hal_adc.h>
#include <stm32yyxx_hal_dac.h>




#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

enum PIN_MODE {
	INPUT,
	OUTPUT,
	INPUT_PULLUP,
	ANALOG_IN,
	ANALOG_OUT
};




#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_GPIO_BSP_TYPEDEFS_H_ */
