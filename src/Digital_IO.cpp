/*
 * Digital_IO.cpp
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#include <stdint.h>
#include <stdbool.h>

#include <stm32yyxx_hal.h>
#include <stm32yyxx_hal_def.h>
#include <IO_Typedefs.h>

#include "Digital_IO.h"


Digital_IO* Digital_IO::instance = nullptr;  // Initialize the instance to nullptr

void Digital_IO::_pinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
		uint32_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed) {

/*!	uint32_t Pin;        < Specifies the GPIO pins to be configured.
	                           This parameter can be a value of @ref GPIO_pins */

/*!	uint32_t Mode;       < Specifies the operating mode for the selected pins.
	                           This parameter can be a value of @ref GPIO_mode */

/*!	  uint32_t Pull;       < Specifies the Pull-up or Pull-Down activation for the selected pins.
	                           This parameter can be a value of @ref GPIO_pull */

/*!	  uint32_t Speed;      < Specifies the speed for the selected pins.
	                           This parameter can be a value of @ref GPIO_speed */

/*!	  uint32_t Alternate; */

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = Mode;
	GPIO_InitStruct.Pull = Pull;
	GPIO_InitStruct.Speed = Speed;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);

	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


void Digital_IO::_pinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_InitTypeDef *GPIO_InitStruct) {

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);

	HAL_GPIO_Init(GPIOx, GPIO_InitStruct);

}

GPIO_PinState     Digital_IO::_ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

	return GPIO_PinState::GPIO_PIN_RESET;

}

void Digital_IO::_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState){

}

void Digital_IO::_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet){

}

void Digital_IO::_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

}

void Digital_IO::_EnableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

}

void Digital_IO::_DisableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

}

HAL_StatusTypeDef Digital_IO::_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){

	return HAL_StatusTypeDef::HAL_OK;
}

void Digital_IO::_IRQHandler(uint16_t GPIO_Pin){

}

void Digital_IO::_Rising_Callback(uint16_t GPIO_Pin){

}

void Digital_IO::_Falling_Callback(uint16_t GPIO_Pin){

}


void Digital_IO::_Init(GPIO_TypeDef  *GPIOx, const GPIO_InitTypeDef *pGPIO_Init){

}

void Digital_IO::_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin){

}

