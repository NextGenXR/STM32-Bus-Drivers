/*
 * I2CAPI.cpp
 *
 *  Created on: Jun 20, 2023
 *      Author: joconnor
 */

#include <cstdio>
#include <cstdint>
#include <cstdbool>

#include <stm32yyxx_hal_def.h>
#include <stm32yyxx_hal_i2c.h>
#include <stm32yyxx_hal_i2c_ex.h>
#include <stm32yyxx_hal_rcc.h>
#include <I2C_API_def.h>
#include <I2C_Device.h>
#include <tx_api.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Potential STM32 I2C Devices. Not all handles may exist */

	extern I2C_HandleTypeDef hi2c1;
	extern I2C_HandleTypeDef hi2c2;
	extern I2C_HandleTypeDef hi2c3;
	extern I2C_HandleTypeDef hi2c4;
	extern I2C_HandleTypeDef hi2c5;
#ifdef __cplusplus
}
#endif


constexpr unsigned long int I2C_TIMEOUT = 1000;
constexpr unsigned long int I2C_TRIALS = 5;
#define ADDR_BUFFER_SZ 32

HAL_StatusTypeDef I2C_status = HAL_ERROR;

/**
  * @brief Variables related to Master process
  */
/* aCommandCode declaration array    */
/* [CommandCode][RequestSlaveAnswer] */
/* {CODE, YES/NO}                    */
const char* aCommandCode[4][4] = {
  {"CHIP_NAME", "YES"},
  {"CHIP_REVISION", "YES"},
  {"LOW_POWER", "NO"},
  {"WAKE_UP", "NO"}};

#define BUFFER_SIZE 0xF
uint8_t *pMasterTransmitBuffer = (uint8_t*)((&aCommandCode[0]));
uint8_t      ubMasterNbCommandCode     = sizeof(aCommandCode[0][0]);
uint8_t      aMasterReceiveBuffer[BUFFER_SIZE] = {0};
__IO uint8_t ubMasterNbDataToReceive   = sizeof(aMasterReceiveBuffer);
__IO uint8_t ubMasterNbDataToTransmit  = 0;
uint8_t      ubMasterCommandIndex      = 0;
__IO uint8_t ubMasterReceiveIndex      = 0;

/**
  * @brief Variables related to Slave process
  */
const char* aSlaveInfo[]      = {
                  "STM32yyxx",
                  "1.2.3"};

uint8_t       aSlaveReceiveBuffer[BUFFER_SIZE]  = {0};
uint8_t*      pSlaveTransmitBuffer      = 0;
__IO uint8_t  ubSlaveNbDataToTransmit   = 0;
uint8_t       ubSlaveInfoIndex          = 0xFF;
__IO uint8_t  ubSlaveReceiveIndex       = 0;
uint32_t      uwTransferDirection       = 0;
__IO uint32_t uwTransferInitiated       = 0;
__IO uint32_t uwTransferEnded           = 0;


I2C_Device::I2C_Device() {
	aTxBuffer = new uint8_t[TXBUFFERSIZE];
	aRxBuffer = new uint8_t[RXBUFFERSIZE];
}

I2C_Device::~I2C_Device() {
	delete[] aTxBuffer;
	delete[] aRxBuffer;
}



/* Return the address for this device, right-shifted from stored value. */
I2C_AddressTypeDef I2C_Device::address() {

	if(_i2c_device.Address != 0)
		return (_i2c_device.Address>>1);

	return (0);
}

/**
 *  @brief Use when the I2C Interface is initialized in main.h
 *  @retval bool success
 *  */
bool I2C_Device::begin(I2C_HandleTypeDef *Handle) {

	_begun = false;
	if(Handle != nullptr) {
		_i2c_device.Handle = Handle;
		_begun = true;
	}

	return (_begun);
}

/* TODO: Define */
bool I2C_Device::begin(bool addr_detect) {

	// TODO:

	_begun = true;
	return (true);
}

void I2C_Device::end(void)
{
	// TODO: Any memory to recover? Leave it to destructor.

	_begun = false;
}

uint8_t I2C_Device::scan_addresses(I2C_AddressTypeDef* addressbuffer)
{
#define MAX_I2C_ADDRESS 0x7F
#define START_I2C_ADDRESS 0x0E

	for(int x=0; x<ADDR_BUFFER_SZ; x++)
	{
		addressbuffer[x] = 0;
	}

	uint8_t count = 0;
	for(uint16_t addr = START_I2C_ADDRESS; addr< MAX_I2C_ADDRESS; addr++)
	{
		if(HAL_I2C_IsDeviceReady(_i2c_device.Handle, (addr<<1), 1, I2C_TIMEOUT) == HAL_OK)
		{
			addressbuffer[count++] = addr;
		}
	}
	return (count);
}


bool I2C_Device::detected(void)
{
	return (HAL_I2C_IsDeviceReady(_i2c_device.Handle, _i2c_device.Address, I2C_TRIALS, I2C_TIMEOUT) == HAL_OK);
}


bool I2C_Device::read(BufferTypeDef buffer, LengthTypeDef len, bool stop)
{
	return (receive_hal_i2c(buffer, len) == HAL_OK);
}

bool I2C_Device::write(BufferTypeDef buffer, LengthTypeDef len, bool stop,
		BufferTypeDef prefix_buffer, LengthTypeDef prefix_len)
{
	if(prefix_len != 0)
	{
		transmit_hal_i2c(prefix_buffer, prefix_len);
	}

	return (transmit_hal_i2c(buffer, len) == HAL_OK);
}

bool I2C_Device::write_then_read(BufferTypeDef write_buffer, LengthTypeDef write_len,
		BufferTypeDef read_buffer, LengthTypeDef read_len, bool stop)
{
	/* TODO: Any Data Validation needed? */

	auto result1 = write(write_buffer, write_len);
	auto result2 = read(read_buffer, read_len);

	return (result1 == true && result2 == true);
}

bool I2C_Device::set_speed(uint32_t newSpeed)
{
	/* TODO Required? */

	// Disable the I2C peripheral
	HAL_I2C_DeInit(_i2c_device.Handle);

	// Update the I2C speed configuration
	SetI2CTiming(newSpeed);

	// Reinitialize the I2C peripheral with the updated configuration
	HAL_I2C_Init(_i2c_device.Handle);

	return (true);
}

void I2C_Device::wait_transfer(uint32_t timeout) {
	  /*##-5- Wait for the end of the transfer ###################################*/
	  /*  Before starting a new communication transfer, you need to check the current
	      state of the peripheral; if it�s busy you need to wait for the end of current
	      transfer before starting a new one.
	      For simplicity reasons, this example is just waiting till the end of the
	      transfer, but application may perform other tasks while transfer operation
	      is ongoing. */
	  while (HAL_I2C_GetState(_i2c_device.Handle) != HAL_I2C_STATE_READY)
	  {
		  /* Thread sleep for .1s */
		      tx_thread_sleep(10);
	  }
}



HAL_StatusTypeDef I2C_Device::transmit_hal_i2c(BufferTypeDef pData, LengthTypeDef Size)
{
	/* TODO: Slave doesn't need address, needs a default */
	/* Address is already left-shifted for HAL driver */

	if(_i2c_device.Master)
		return(HAL_I2C_Master_Transmit(_i2c_device.Handle, _i2c_device.Address, pData, Size, I2C_TIMEOUT));

	return (HAL_I2C_Slave_Transmit(_i2c_device.Handle, pData, Size, I2C_TIMEOUT));
}

HAL_StatusTypeDef I2C_Device::receive_hal_i2c(BufferTypeDef pData, LengthTypeDef Size)
{
	/* Address is already left-shifted for HAL driver */

	if(_i2c_device.Master)
		return (HAL_I2C_Master_Receive(_i2c_device.Handle, _i2c_device.Address, pData, Size, I2C_TIMEOUT));
	else
		return (HAL_I2C_Slave_Receive(_i2c_device.Handle, pData, Size, I2C_TIMEOUT));
}


/* Check I2C Address on this I2C Device */
bool I2C_Device::check_address(uint8_t address)
{
	bool state = false;

	if(_i2c_device.Handle == nullptr)
		return false;

	// Send a start condition on the I2C bus
	HAL_I2C_Master_Transmit(_i2c_device.Handle, 0, 0, 0, I2C_TIMEOUT);

	// Iterate through all possible I2C device addresses
	for (uint8_t address = 0; address < 128; address++)
	{
		// Try to communicate with the device at the current address
		if (HAL_I2C_IsDeviceReady(_i2c_device.Handle, address, 1, 100) == HAL_OK)
		{
			// Device is present on the I2C bus
			printf("Device found at address 0x%02X\n", address);
			state = true;
		}
	}

	// Send a stop condition on the I2C bus
	HAL_I2C_Master_Transmit(_i2c_device.Handle, 0, 0, 0, I2C_TIMEOUT);

	return state;
}


