/*
 * GPIO_BSP.h
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_GPIO_BSP_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_GPIO_BSP_H_


#include <stdint.h>
#include <stdbool.h>

#include <IO_Typedefs.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bool digitalRead(uint8_t pin);
bool digitalWrite(uint8_t pin, bool value);

/* Expanded DIO */
void digital_Write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

bool pinMode(uint8_t pin, PIN_MODE mode);


void analogReference();
void analogReadResolution();
void analogWriteResolution();

uint16_t analogRead(uint8_t pin);
bool analogWrite(uint8_t pin, uint8_t value);	// PWM per Arduino standard


#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_GPIO_BSP_H_ */
