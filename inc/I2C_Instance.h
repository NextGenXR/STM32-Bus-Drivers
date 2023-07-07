/*
 * I2C_Instance.h
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_

class I2C_Instance {
public:
	I2C_Instance(I2C_TypeDef* instance);
	virtual ~I2C_Instance();

	HAL_StatusTypeDef init_i2c(I2C_HandleTypeDef* I2cHandle);
	uint32_t GetI2CClockFreq(void);



private:
	I2C_TypeDef* _instance;

};

#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_ */
