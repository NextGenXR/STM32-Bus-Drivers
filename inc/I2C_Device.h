/*
 * I2CAPI.h
 *
 *  Created on: Jun 20, 2023
 *      Author: joconnor
 *
 *  Based on Adafruit BusIO Library
 *  with STM32 HAL Support
 *
 */

#ifndef DRIVERS_BSP_BUS_API_I2C_DEVICE_H_
#define DRIVERS_BSP_BUS_API_I2C_DEVICE_H_

#include <stm32yyxx_hal_def.h>
#include <stm32yyxx_hal_i2c.h>

#ifdef __cplusplus
#include <I2C_API_def.h>
#include <cstdbool>

#define MASTER_BOARD
#define I2C_ADDRESS        0x47	// 71
#define LED_STATUS_TIMEOUT  100 /* 1 Second in ThreadX */
#define I2C_OWN_ADDRESS 0xFE
#define MAX_BUFFER_SIZE 32
#define MAX_I2C_DEVICES 128


/* Exported macro ------------------------------------------------------------*/
// #define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

/**
 * @brief Defines related to I2C clock speed
 */

#define I2C_TIMING        0x00D00E28  /* (Rise time = 120ns, Fall time = 25ns) */
// #define I2C_TIMING 0x20404768;	// From CubeMX


class I2C_Device {
public:
	I2C_Device();
	virtual ~I2C_Device();

	I2C_AddressTypeDef address(void);	// Get (non-shifted) address.
	bool begin(I2C_AddressTypeDef addr, I2C_HandleTypeDef *hi2c = nullptr, bool Master = true);
	bool begin();	// Default to hi2c1 and address I2C_OWN_ADDRESS
	bool begin(bool addr_detect = true);
	bool begin(I2C_InitTypeDef* init_typedef, I2C_HandleTypeDef *Handle);

	/* When the I2C Interface is initialized in main.c, and pointer is valid */
	bool begin(I2C_HandleTypeDef *Handle);

	void end(void);
	bool detected(void);

	uint8_t scan_addresses(I2C_AddressTypeDef* validAddresses);
	bool check_address(uint8_t address);

	bool read(BufferTypeDef buffer, LengthTypeDef len = 1, bool stop = true);
	bool write(BufferTypeDef buffer, LengthTypeDef len = 1, bool stop = true, BufferTypeDef prefix_buffer = NULL,
			LengthTypeDef prefix_len = 0);
	bool write_then_read(BufferTypeDef write_buffer, LengthTypeDef write_len, BufferTypeDef read_buffer,
			LengthTypeDef read_len, bool stop = false);
	bool set_speed(uint32_t desiredclk);


private:
	bool _begun;
	size_t _maxBufferSize;

	/* Buffer used for transmission */
	uint8_t* aTxBuffer; //[] = " ****I2C_TwoBoards communication based on IT****  ****I2C_TwoBoards communication based on IT****  ****I2C_TwoBoards communication based on IT**** ";

	/* Size of Transmission buffer */
	#define TXBUFFERSIZE  147 //                    (COUNTOF(aTxBuffer) - 1)
	/* Size of Reception buffer */
	#define RXBUFFERSIZE                      TXBUFFERSIZE

	/* Buffer used for reception */
	uint8_t* aRxBuffer;

	bool _read(BufferTypeDef *buffer, LengthTypeDef len, bool stop);
	void wait_transfer(uint32_t timeout);

	I2C_DeviceTypeDef _i2c_device;
	HAL_StatusTypeDef transmit_hal_i2c(BufferTypeDef pData, LengthTypeDef Size);
	HAL_StatusTypeDef receive_hal_i2c(BufferTypeDef pData, LengthTypeDef Size);
	HAL_StatusTypeDef init_i2c(I2C_HandleTypeDef *_I2cHandle);

};

#endif /* cpp */

#endif /* DRIVERS_BSP_BUS_API_I2C_DEVICE_H_ */


