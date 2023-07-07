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
  // Private constructor to prevent instantiation
  Analog_IO() {}

};




#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_ANALOG_IO_H_ */
