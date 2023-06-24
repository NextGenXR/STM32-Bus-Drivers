/*
 * I2C_API_def.h
 *  TypeDefs
 *  Constants
 *  Macros
 *
 *  Created on: Nov 3, 2022
 *      Author: joconnor
 */

#ifndef BSP_BUSAPI_I2C_DEF_H_
#define BSP_BUSAPI_I2C_DEF_H_

#include <cstdint>

typedef uint16_t I2C_AddressTypeDef;
typedef uint8_t* BufferTypeDef;
typedef uint16_t LengthTypeDef;

typedef struct
{
	I2C_AddressTypeDef Address;
	I2C_HandleTypeDef *Handle;
	I2C_TypeDef *Type;
	bool Master = true;
} I2C_DeviceTypeDef;

/* Defaults */
#define I2C_TIMING        0x00D00E28  /* (Rise time = 120ns, Fall time = 25ns) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor I2Cx/I2Cx instance used and associated
   resources */
/* Definition for I2Cx clock resources */
#define I2Cx                            I2C1
#define RCC_PERIPHCLK_I2Cx              RCC_PERIPHCLK_I2C1
#define RCC_I2CxCLKSOURCE_SYSCLK        RCC_I2C1CLKSOURCE_PCLK1
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_DMA_CLK_ENABLE()           __HAL_RCC_DMA1_CLK_ENABLE()

#define I2Cx_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_8
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SCL_SDA_AF                 GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

/* Definition for I2Cx's DMA */
#define I2Cx_DMA                        DMA1
#define I2Cx_DMA_INSTANCE_TX            DMA1_Stream6
#define I2Cx_DMA_INSTANCE_RX            DMA1_Stream0
#define I2Cx_DMA_CHANNEL_TX             DMA_CHANNEL_1
#define I2Cx_DMA_CHANNEL_RX             DMA_CHANNEL_1

/* Definition for I2Cx's DMA NVIC */
#define I2Cx_DMA_TX_IRQn                DMA1_Stream6_IRQn
#define I2Cx_DMA_RX_IRQn                DMA1_Stream0_IRQn
#define I2Cx_DMA_TX_IRQHandler          DMA1_Stream6_IRQHandler
#define I2Cx_DMA_RX_IRQHandler          DMA1_Stream0_IRQHandler

/* Exported macro ------------------------------------------------------------*/
// #define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

#endif /* BSP_BUSAPI_I2C_DEF_H_ */
