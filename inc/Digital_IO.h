/*
 * Digital_IO.h
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_DIGITAL_IO_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_DIGITAL_IO_H_

#include <stdint.h>
#include <stdbool.h>

class Digital_IO {
public:
  static Digital_IO* getInstance() {
    if (instance == nullptr) {
      instance = new Digital_IO();
    }
    return instance;
  }

  void _pinMode(uint8_t pin, PIN_MODE mode);
  bool _digitalWrite(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

  void _pinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_InitTypeDef *GPIO_InitStruct);
  void _pinMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
  		uint32_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed);


private:
  static Digital_IO* instance;  // The single instance of the class
  Digital_IO() {}               // Private constructor to prevent instantiation

  GPIO_PinState     _ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  void              _WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
  void              _WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet);
  void              _TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  void              _EnableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  void              _DisableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  HAL_StatusTypeDef _LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
  void              _IRQHandler(uint16_t GPIO_Pin);
  void              _Rising_Callback(uint16_t GPIO_Pin);
  void              _Falling_Callback(uint16_t GPIO_Pin);

  void _Init(GPIO_TypeDef  *GPIOx, const GPIO_InitTypeDef *pGPIO_Init);
  void _DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);

};

Digital_IO* Digital_IO::instance = nullptr;  // Initialize the instance to nullptr

#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_DIGITAL_IO_H_ */
