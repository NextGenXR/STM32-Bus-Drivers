/*
 * I2C_Instance.h
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_

/**
 * This class takes the I2C1, I2C2, etc, instance macro and initializes the peripheral
 */


void I2C_Init(I2C_HandleTypeDef* hi2c, I2C_InitTypeDef* init);
void I2C_Init(I2C_TypeDef* instance, I2C_InitTypeDef* init);



	HAL_StatusTypeDef init_i2c(I2C_HandleTypeDef* I2cHandle);

	void SetI2CTiming(uint32_t desiredSpeed);
	uint32_t GetI2CClockFreq(void);

	void I2C_MspInit(I2C_HandleTypeDef* i2cHandle);
	void I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle);

};

#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_ */
