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

static Analog_IO* aio = nullptr;
static Digital_IO* dio = nullptr;
bool begun = false;

#define MAX_PINS 128
PinMode_TypeDef pinStates[MAX_PINS];

void begin()
{
	if(begun == false) {
		aio = Analog_IO::getInstance();
		dio = Digital_IO::getInstance();

		// TODO: Further initialization
		for(auto count = 0; count < MAX_PINS; count++) {
			pinStates[count] = PinMode_TypeDef::NONE;
		}

		begun = true;
	}

}


bool digitalRead(uint8_t pin) {
	if(begun != true) {
		begin();
	}

	// TODO: digitalRead
	return true;

}

bool digitalWrite(uint8_t pin, bool value) {
	if(begun != true) {
		begin();
	}

	// TODO: digitalWrite
	return true;
}

void digital_Write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
	if(begun != true) {
		begin();
	}

	// TODO: digital_Write

}

bool pinMode(uint8_t pin, PinMode_TypeDef mode) {
	if(begun != true) {
		begin();
	}

	// TODO: pinMode
	return true;
}


bool pin_Mode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) {
	if(begun != true) {
		begin();
	}

	// TODO: pin_Mode
	return true;
}


