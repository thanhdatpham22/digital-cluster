/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define CCMRAM_BSS  __attribute__((section(".ccmram"), used))
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define L3GD20_SCK_Pin GPIO_PIN_7
#define L3GD20_SCK_GPIO_Port GPIOF
#define L3GD20_MISO_Pin GPIO_PIN_8
#define L3GD20_MISO_GPIO_Port GPIOF
#define L3GD20_MOSI_Pin GPIO_PIN_9
#define L3GD20_MOSI_GPIO_Port GPIOF
#define L3DG20_CS_Pin GPIO_PIN_1
#define L3DG20_CS_GPIO_Port GPIOC
#define DC_Pin GPIO_PIN_0
#define DC_GPIO_Port GPIOB
#define RESET_Pin GPIO_PIN_1
#define RESET_GPIO_Port GPIOB
#define CS_Pin GPIO_PIN_10
#define CS_GPIO_Port GPIOB
#define T_IRQ_Pin GPIO_PIN_2
#define T_IRQ_GPIO_Port GPIOG
#define T_CS_Pin GPIO_PIN_15
#define T_CS_GPIO_Port GPIOA
#define T_SCK_Pin GPIO_PIN_10
#define T_SCK_GPIO_Port GPIOC
#define T_DIN_Pin GPIO_PIN_11
#define T_DIN_GPIO_Port GPIOC
#define T_DO_Pin GPIO_PIN_12
#define T_DO_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_13
#define LED_GREEN_GPIO_Port GPIOG
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
