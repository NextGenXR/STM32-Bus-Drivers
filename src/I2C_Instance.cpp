/*
 * I2C_Instance.cpp
 *
 *  Created on: Jul 6, 2023
 *      Author: joconnor
 */

#include "I2C_Instance.h"

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


I2C_Instance::I2C_Instance() {
	// TODO Auto-generated constructor stub

}

I2C_Instance::~I2C_Instance() {
	// TODO Auto-generated destructor stub
}


/*
 * Takes the I2C_TypeDef of the controller to use macro: I2C1, I2C2, etc.
 *
 *
 * */
HAL_StatusTypeDef I2C_Instance::I2C_Init(I2C_ControllerTypeDef controller, I2C_InitTypeDef* init) {

	// TODO: Verify that this MCU has that controller available
	// TODO: User

	HAL_StatusTypeDef retval = HAL_ERROR;

	_i2c_device.Controller = controller;

	switch(controller) {
	case I2C_1:
		_i2c_device.Handle = &hi2c1;			// Global Handle
		_i2c_device.Handle->Instance = I2C1; 	// Your I2C peripheral instance
		break;
	case I2C_2:
		_i2c_device.Handle = &hi2c2;			// Global Handle
		_i2c_device.Handle->Instance = I2C2; 	// Your I2C peripheral instance
		break;
	case I2C_3:
		_i2c_device.Handle = &hi2c3;			// Global Handle
		_i2c_device.Handle->Instance = I2C3; 	// Your I2C peripheral instance
		break;
	case I2C_4:
		_i2c_device.Handle = &hi2c4;			// Global Handle
		_i2c_device.Handle->Instance = I2C4; 	// Your I2C peripheral instance
		break;
	case I2C_5:
		_i2c_device.Handle = &hi2c5;			// Global Handle
		_i2c_device.Handle->Instance = I2C5; 	// Your I2C peripheral instance
		break;
	default:
		break;
	}

	// No CASE triggered, or no controller for that I2C
	if(_i2c_device.Handle == nullptr) {
		// TODO: If port exists, perhaps init with new params?
		return retval;
	}

	/* Copy input params to handle's Init params */
	_i2c_device.Handle->Init.AddressingMode  = init->AddressingMode;
	_i2c_device.Handle->Init.Timing			= init->Timing;

	_i2c_device.Handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	_i2c_device.Handle->Init.GeneralCallMode = init->GeneralCallMode; 	// I2C_GENERALCALL_DISABLE;
	_i2c_device.Handle->Init.NoStretchMode   = init->NoStretchMode;		// I2C_NOSTRETCH_DISABLE;
	_i2c_device.Handle->Init.OwnAddress1     = init->OwnAddress1;
	_i2c_device.Handle->Init.OwnAddress2     = init->OwnAddress2;
	_i2c_device.Handle->Init.OwnAddress2Masks = init->OwnAddress2Masks;

	if (retval = HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
	  return retval;
	  //Error_Handler();
	}

	/** Configure Analog filter
	*/
	if (retval = HAL_I2CEx_ConfigAnalogFilter(_i2c_device.Handle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
	  return retval;
	  // Error_Handler();
	}

	/** Configure Digital filter
	*/
	if (retval = HAL_I2CEx_ConfigDigitalFilter(_i2c_device.Handle, 0) != HAL_OK)
	{
	  return retval;
	  // Error_Handler();
	}

	/* Additional Configuration */
	_i2c_device.Handle->Mode = HAL_I2C_ModeTypeDef::HAL_I2C_MODE_MASTER;

	return retval;
}


/*
 * @brief Initialize I2C peripheral in the STM32 chip
 * Pass in a HandleTypeDef pointer to store I2C states
 * I2C_TypeDef is one of I2C1, I2C2, etc.
 * */
void I2C_Instance::I2C_Init(I2C_HandleTypeDef* hi2c, I2C_TypeDef* i2cx, I2C_InitTypeDef* init)
{
	// Has this port been initialized?
	if(_i2c_device.Handle != nullptr) return;

	// I2C_DeviceTypeDef == internal structure

	_i2c_device.Handle = hi2c;

	/* Copy input params to handle's Init params */
	_i2c_device.Handle->Instance             = i2cx; // Your I2C peripheral instance
	_i2c_device.Handle->Init.AddressingMode  = init->AddressingMode;
	_i2c_device.Handle->Init.Timing			= init->Timing;

	_i2c_device.Handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	// TODO: Missing Param
	// hi2c->Init.DutyCycle       = I2C_DUTYCYCLE_2;

	_i2c_device.Handle->Init.GeneralCallMode = init->GeneralCallMode; 	// I2C_GENERALCALL_DISABLE;
	_i2c_device.Handle->Init.NoStretchMode   = init->NoStretchMode;		// I2C_NOSTRETCH_DISABLE;
	_i2c_device.Handle->Init.OwnAddress1     = init->OwnAddress1;
	_i2c_device.Handle->Init.OwnAddress2     = init->OwnAddress2;
	_i2c_device.Handle->Init.OwnAddress2Masks = init->OwnAddress2Masks;

	HAL_I2C_Init(_i2c_device.Handle);

	/* Enable the Analog I2C Filter */
	HAL_I2CEx_ConfigAnalogFilter(_i2c_device.Handle, I2C_ANALOGFILTER_ENABLE);

	/* Additional Configuration */
	_i2c_device.Handle->Mode = HAL_I2C_ModeTypeDef::HAL_I2C_MODE_MASTER;
}



void I2C_Instance::I2C_MspInit(I2C_TypeDef* instance)
{
	// TODO: Conditionals to process each of


	_i2c_device.Handle->Instance = instance;

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  if(_i2c_device.Handle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PG13     ------> I2C1_SDA
    PG14     ------> I2C1_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();

    /* I2C1 interrupt Init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }


}

void I2C_Instance::I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PG13     ------> I2C1_SDA
    PG14     ------> I2C1_SCL
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_14);

    /* I2C1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}


// Function to get I2C clock frequency
uint32_t I2C_Instance::GetI2CClockFreq(void) {
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

/*
 * Initialize the I2C Interface if necessary
 *
 *
 * */
HAL_StatusTypeDef I2C_Instance::init_i2c(I2C_HandleTypeDef* I2cHandle) //, I2C_TypeDef* _I2Cx )
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

