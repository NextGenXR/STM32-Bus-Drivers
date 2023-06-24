/*
 * I2CAPI.cpp
 *
 *  Created on: Jun 20, 2023
 *      Author: joconnor
 */


#include <stm32yyxx_hal_def.h>
#include <stm32yyxx_hal_i2c.h>
#include <stm32f7xx_hal_i2c_ex.h>
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

HAL_StatusTypeDef I2c_status = HAL_ERROR;

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
                  "STM32F767xx",
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
	// TODO Auto-generated constructor stub

	aTxBuffer = new uint8_t[TXBUFFERSIZE];
	aRxBuffer = new uint8_t[RXBUFFERSIZE];
}

I2C_Device::~I2C_Device() {
	// TODO Auto-generated destructor stub
	delete[] aTxBuffer;
	delete[] aRxBuffer;
}


/*
 * @brief Initialize I2C peripheral in the STM32 chip
 * Pass in a HandleTypeDef pointe to store I2C states
 * */
void I2C_Device::I2C_Init(I2C_HandleTypeDef* hi2c, I2C_TypeDef* i2cx, I2C_InitTypeDef* init)
{

	/* Copy input params to handle's Init params */
	hi2c->Instance             = i2cx; // Your I2C peripheral instance
	hi2c->Init.AddressingMode  = init->AddressingMode;
	hi2c->Init.Timing			= init->Timing;

	hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	// TODO: Missing Param
	// hi2c->Init.DutyCycle       = I2C_DUTYCYCLE_2;

	hi2c->Init.GeneralCallMode = init->GeneralCallMode; 	// I2C_GENERALCALL_DISABLE;
	hi2c->Init.NoStretchMode   = init->NoStretchMode;		// I2C_NOSTRETCH_DISABLE;
	hi2c->Init.OwnAddress1     = init->OwnAddress1;
	hi2c->Init.OwnAddress2     = init->OwnAddress2;
	hi2c->Init.OwnAddress2Masks = init->OwnAddress2Masks;

	HAL_I2C_Init(hi2c);

	/* Enable the Analog I2C Filter */
	HAL_I2CEx_ConfigAnalogFilter(hi2c,I2C_ANALOGFILTER_ENABLE);

	/* Additional Configuration */
	hi2c->Mode = HAL_I2C_ModeTypeDef::HAL_I2C_MODE_MASTER;
}

/* Return the address for this device, right-shifted from stored value. */
I2C_AddressTypeDef I2C_Device::address() {
	if(addr == 0)
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

// Function to get I2C clock frequency
uint32_t I2C_Device::GetI2CClockFreq(void) {
	RCC_PeriphCLKInitTypeDef PeriphClkInit;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	// Get the current peripheral clock configuration
	HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInit);

	if (PeriphClkInit.PeriphClockSelection == RCC_PERIPHCLK_I2Cx) {
		// I2C clock source is based on PLL
		uint32_t pllSource;
		uint32_t pllM;
		uint32_t pllN;
		uint32_t pllR;
		uint32_t pllP;
		uint32_t systemClock;

		// Get PLL settings
		HAL_RCC_GetOscConfig(&RCC_OscInitStruct);
		pllSource = RCC_OscInitStruct.PLL.PLLSource;
		pllM = RCC_OscInitStruct.PLL.PLLM;
		pllN = RCC_OscInitStruct.PLL.PLLN;
		pllR = RCC_OscInitStruct.PLL.PLLR;
		pllP = RCC_OscInitStruct.PLL.PLLP;

		// Get system clock
		if (pllSource == RCC_PLLSOURCE_HSI) {
		  systemClock = HSI_VALUE;
		} else
			if (pllSource == RCC_PLLSOURCE_HSE) {
		  systemClock = HSE_VALUE;
		} else {
		  // Other PLL sources (e.g., PLL source from HSI48)
		  // TODO: Adjust accordingly or add additional cases if needed
		  return (0);
		}

		// Calculate the I2C clock frequency
		return ((systemClock * pllN) / (pllM * pllP * pllR));
	}

  return (0);
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

/*
 * Initialize the I2C Interface if necessary
 *
 *
 * */
HAL_StatusTypeDef I2C_Device::init_i2c(I2C_HandleTypeDef* I2cHandle) //, I2C_TypeDef* _I2Cx )
{
	HAL_StatusTypeDef result = HAL_OK;

	if(HAL_I2C_IsDeviceReady(_i2c_device.Handle, _i2c_device.Address, I2C_TRIALS, I2C_TIMEOUT) == HAL_OK)
		return (result);

	// TODO: This overrides the settings from the CubeMX
	/*##-1- Configure the I2C peripheral ######################################*/
	I2cHandle->Instance             = I2Cx;
	I2cHandle->Init.Timing          = I2C_TIMING;
	I2cHandle->Init.OwnAddress1     = I2C_ADDRESS;
	I2cHandle->Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	I2cHandle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2cHandle->Init.OwnAddress2     = I2C_OWN_ADDRESS;
	I2cHandle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2cHandle->Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

	result = HAL_I2C_Init(I2cHandle);
	if(result != HAL_OK) {
	/* Initialization Error */
	Error_Handler();
	}

	return (result);
}


