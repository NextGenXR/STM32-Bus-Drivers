/*
 * GPIO_BSP.cpp
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#include <stdint.h>
#include <stdbool.h>

#include "GPIO_BSP.h"
#include <IO_Typedefs.h>

#include <Analog_IO.h>
#include <Digital_IO.h>

Analog_IO* aio;
Digital_IO* dio;

void begin()
{
	aio = Analog_IO::getInstance();
	dio = Digital_IO::getInstance();


}


bool digitalRead(uint8_t pin) {
	return true;
}

bool digitalWrite(uint8_t pin, bool value) {
	return true;
}

void digital_Write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {

}

bool pinMode(uint8_t pin, PIN_MODE mode) {
	return true;
}


bool pin_Mode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
	return true;
}


