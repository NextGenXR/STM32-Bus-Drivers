/*
 * Analog_IO.cpp
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#include "Analog_IO.h"

Analog_IO* Analog_IO::instance = nullptr;  // Initialize the instance to nullptr


  void Analog_IO::analogReference() {

  }

  void Analog_IO::analogReadResolution() {

  }

  void Analog_IO::analogWriteResolution() {

  }

  uint16_t Analog_IO::analogRead(uint8_t pin) {

	  return 0;

  }

  bool Analog_IO::analogWrite(uint8_t pin, uint16_t value) {
	  return false;
  }

  bool Analog_IO::d2aWrite(uint8_t pin, uint16_t value) {
	  return false;
  }
