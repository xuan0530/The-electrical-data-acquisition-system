/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
// First ADS1263 pin definitions
#define ADS1263_START_Pin GPIO_PIN_0
#define ADS1263_START_GPIO_Port GPIOC
#define ADS1263_CS_Pin GPIO_PIN_1
#define ADS1263_CS_GPIO_Port GPIOC
#define ADS1263_SCLK_Pin GPIO_PIN_2
#define ADS1263_SCLK_GPIO_Port GPIOC
#define ADS1263_DIO_Pin GPIO_PIN_3
#define ADS1263_DIO_GPIO_Port GPIOC
#define ADS1263_DOUT_Pin GPIO_PIN_4
#define ADS1263_DOUT_GPIO_Port GPIOC
#define ADS1263_DRDY_Pin GPIO_PIN_5
#define ADS1263_DRDY_GPIO_Port GPIOC
#define ADS1263_RESET_Pin GPIO_PIN_6
#define ADS1263_RESET_GPIO_Port GPIOC

// Second ADS1263 pin definitions
#define ADS1263_2_START_Pin GPIO_PIN_8
#define ADS1263_2_START_GPIO_Port GPIOE
#define ADS1263_2_CS_Pin GPIO_PIN_9
#define ADS1263_2_CS_GPIO_Port GPIOE
#define ADS1263_2_SCLK_Pin GPIO_PIN_10
#define ADS1263_2_SCLK_GPIO_Port GPIOE
#define ADS1263_2_DIO_Pin GPIO_PIN_11
#define ADS1263_2_DIO_GPIO_Port GPIOE
#define ADS1263_2_DOUT_Pin GPIO_PIN_12
#define ADS1263_2_DOUT_GPIO_Port GPIOE
#define ADS1263_2_DRDY_Pin GPIO_PIN_13
#define ADS1263_2_DRDY_GPIO_Port GPIOE
#define ADS1263_2_RESET_Pin GPIO_PIN_14
#define ADS1263_2_RESET_GPIO_Port GPIOE

// Third ADS1263 pin definitions
#define ADS1263_3_START_Pin GPIO_PIN_8
#define ADS1263_3_START_GPIO_Port GPIOB
#define ADS1263_3_CS_Pin GPIO_PIN_9
#define ADS1263_3_CS_GPIO_Port GPIOB
#define ADS1263_3_SCLK_Pin GPIO_PIN_10
#define ADS1263_3_SCLK_GPIO_Port GPIOB
#define ADS1263_3_DIO_Pin GPIO_PIN_11
#define ADS1263_3_DIO_GPIO_Port GPIOB
#define ADS1263_3_DOUT_Pin GPIO_PIN_12
#define ADS1263_3_DOUT_GPIO_Port GPIOB
#define ADS1263_3_DRDY_Pin GPIO_PIN_13
#define ADS1263_3_DRDY_GPIO_Port GPIOB
#define ADS1263_3_RESET_Pin GPIO_PIN_14
#define ADS1263_3_RESET_GPIO_Port GPIOB

// CD4067 #1 (1-16) pin definitions
#define CD4067_1_S0_Pin GPIO_PIN_1
#define CD4067_1_S0_GPIO_Port GPIOB
#define CD4067_1_S1_Pin GPIO_PIN_7
#define CD4067_1_S1_GPIO_Port GPIOD
#define CD4067_1_S2_Pin GPIO_PIN_5
#define CD4067_1_S2_GPIO_Port GPIOB
#define CD4067_1_S3_Pin GPIO_PIN_3
#define CD4067_1_S3_GPIO_Port GPIOB
#define CD4067_1_E_Pin GPIO_PIN_7
#define CD4067_1_E_GPIO_Port GPIOB

// CD4067 #2 (17-32) pin definitions
#define CD4067_2_S0_Pin GPIO_PIN_15
#define CD4067_2_S0_GPIO_Port GPIOA
#define CD4067_2_S1_Pin GPIO_PIN_13
#define CD4067_2_S1_GPIO_Port GPIOC
#define CD4067_2_S2_Pin GPIO_PIN_3
#define CD4067_2_S2_GPIO_Port GPIOD
#define CD4067_2_S3_Pin GPIO_PIN_1
#define CD4067_2_S3_GPIO_Port GPIOD
#define CD4067_2_E_Pin GPIO_PIN_5
#define CD4067_2_E_GPIO_Port GPIOD

// CD4067 #3 pin definitions
#define CD4067_3_S0_Pin GPIO_PIN_12
#define CD4067_3_S0_GPIO_Port GPIOD
#define CD4067_3_S1_Pin GPIO_PIN_10
#define CD4067_3_S1_GPIO_Port GPIOD
#define CD4067_3_S2_Pin GPIO_PIN_4
#define CD4067_3_S2_GPIO_Port GPIOA
#define CD4067_3_S3_Pin GPIO_PIN_8
#define CD4067_3_S3_GPIO_Port GPIOD
#define CD4067_3_E_Pin GPIO_PIN_0
#define CD4067_3_E_GPIO_Port GPIOA

// CD4067 #4 pin definitions
#define CD4067_4_S0_Pin GPIO_PIN_7
#define CD4067_4_S0_GPIO_Port GPIOC
#define CD4067_4_S1_Pin GPIO_PIN_1
#define CD4067_4_S1_GPIO_Port GPIOA
#define CD4067_4_S2_Pin GPIO_PIN_9
#define CD4067_4_S2_GPIO_Port GPIOD
#define CD4067_4_S3_Pin GPIO_PIN_11
#define CD4067_4_S3_GPIO_Port GPIOD
#define CD4067_4_E_Pin GPIO_PIN_15
#define CD4067_4_E_GPIO_Port GPIOB

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
