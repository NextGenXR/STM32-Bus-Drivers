/*
 * I2C_Instance.h
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#ifndef DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_
#define DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_

#include <stm32yyxx_hal_def.h>

#ifndef I2C_TRIALS
#define I2C_TRIALS 5
#endif

#ifndef I2C_TIMEOUT
#define I2C_TiMEout 1000
#endif

	void init_I2C_Instance(I2C_TypeDef* instance);
	void deinit_2C_Instance(I2C_TypeDef* instance);

	HAL_StatusTypeDef init_i2c(I2C_HandleTypeDef* I2cHandle);

	void SetI2CTiming(uint32_t desiredSpeed);
	uint32_t GetI2CClockFreq(void);

	void I2C_MspInit(I2C_HandleTypeDef* i2cHandle);
	void I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle);


#endif /* DRIVERS_BSP_STM32_BUS_DRIVERS_I2C_INSTANCE_H_ */
