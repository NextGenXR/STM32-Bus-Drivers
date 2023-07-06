/*
 * Analog_IO.h
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_ANALOG_IO_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_ANALOG_IO_H_

#include <stdint.h>
#include <stdbool.h>

class Analog_IO {
            // Private constructor to prevent instantiation

public:
  static Analog_IO* getInstance() {
    if (instance == nullptr) {
      instance = new Analog_IO();
    }
    return instance;
  }


  void analogReference();
  void analogReadResolution();
  void analogWriteResolution();

  uint16_t analogRead(uint8_t pin);
  bool analogWrite(uint8_t pin, uint16_t value);

  bool d2aWrite(uint8_t pin, uint16_t value);

private:
  static Analog_IO* instance;  // The single instance of the class
  Analog_IO() {}

};

Analog_IO* Analog_IO::instance = nullptr;  // Initialize the instance to nullptr


#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_ANALOG_IO_H_ */
