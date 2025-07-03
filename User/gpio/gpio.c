/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpio.c
 * @brief   This file provides code for the configuration
 *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
*/
void MX_GPIO_Init(void) {

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  __HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();  // Enable clock for GPIOD
  __HAL_RCC_GPIOE_CLK_ENABLE();  // Enable clock for GPIOE

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADS1263_DIO_GPIO_Port, ADS1263_DIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADS1263_SCLK_GPIO_Port, ADS1263_SCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADS1263_CS_GPIO_Port, ADS1263_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADS1263_START_GPIO_Port, ADS1263_START_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADS1263_RESET_GPIO_Port, ADS1263_RESET_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_SCLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_DIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_DIO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_DRDY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADS1263_DRDY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_DOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADS1263_DOUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_START_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_START_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADS1263_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_RESET_GPIO_Port, &GPIO_InitStruct);
	
	 /* 配置输出引脚的初始电平 */
  HAL_GPIO_WritePin(ADS1263_2_DIO_GPIO_Port, ADS1263_2_DIO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ADS1263_2_SCLK_GPIO_Port, ADS1263_2_SCLK_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ADS1263_2_CS_GPIO_Port, ADS1263_2_CS_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(ADS1263_2_START_GPIO_Port, ADS1263_2_START_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(ADS1263_2_RESET_GPIO_Port, ADS1263_2_RESET_Pin, GPIO_PIN_SET);

  /* 配置 CS 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_2_CS_GPIO_Port, &GPIO_InitStruct);

  /* 配置 SCLK 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_2_SCLK_GPIO_Port, &GPIO_InitStruct);

  /* 配置 DIO 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_DIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_2_DIO_GPIO_Port, &GPIO_InitStruct);

  /* 配置 DRDY 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_DRDY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADS1263_2_DRDY_GPIO_Port, &GPIO_InitStruct);

  /* 配置 DOUT 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_DOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADS1263_2_DOUT_GPIO_Port, &GPIO_InitStruct);

  /* 配置 START 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_START_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_2_START_GPIO_Port, &GPIO_InitStruct);

  /* 配置 RESET 引脚 */
  GPIO_InitStruct.Pin = ADS1263_2_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADS1263_2_RESET_GPIO_Port, &GPIO_InitStruct);
	
	
	/* Configure output pin levels for ADS1263_3 */
HAL_GPIO_WritePin(ADS1263_3_DIO_GPIO_Port, ADS1263_3_DIO_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(ADS1263_3_SCLK_GPIO_Port, ADS1263_3_SCLK_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(ADS1263_3_CS_GPIO_Port, ADS1263_3_CS_Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(ADS1263_3_START_GPIO_Port, ADS1263_3_START_Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(ADS1263_3_RESET_GPIO_Port, ADS1263_3_RESET_Pin, GPIO_PIN_SET);

/* Configure CS pin */
GPIO_InitStruct.Pin = ADS1263_3_CS_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(ADS1263_3_CS_GPIO_Port, &GPIO_InitStruct);

/* Configure SCLK pin */
GPIO_InitStruct.Pin = ADS1263_3_SCLK_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(ADS1263_3_SCLK_GPIO_Port, &GPIO_InitStruct);

/* Configure DIO pin */
GPIO_InitStruct.Pin = ADS1263_3_DIO_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(ADS1263_3_DIO_GPIO_Port, &GPIO_InitStruct);

/* Configure DRDY pin */
GPIO_InitStruct.Pin = ADS1263_3_DRDY_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(ADS1263_3_DRDY_GPIO_Port, &GPIO_InitStruct);

/* Configure DOUT pin */
GPIO_InitStruct.Pin = ADS1263_3_DOUT_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(ADS1263_3_DOUT_GPIO_Port, &GPIO_InitStruct);

/* Configure START pin */
GPIO_InitStruct.Pin = ADS1263_3_START_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(ADS1263_3_START_GPIO_Port, &GPIO_InitStruct);

/* Configure RESET pin */
GPIO_InitStruct.Pin = ADS1263_3_RESET_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
HAL_GPIO_Init(ADS1263_3_RESET_GPIO_Port, &GPIO_InitStruct);
	
	// 在已有GPIO初始化代码后添加：

/* Configure CD4067 #1 pins */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  // Configure S0-S3 and E pins
  GPIO_InitStruct.Pin = CD4067_1_S0_Pin;
  HAL_GPIO_Init(CD4067_1_S0_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_1_S1_Pin;
  HAL_GPIO_Init(CD4067_1_S1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_1_S2_Pin;
  HAL_GPIO_Init(CD4067_1_S2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_1_S3_Pin;
  HAL_GPIO_Init(CD4067_1_S3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_1_E_Pin;
  HAL_GPIO_Init(CD4067_1_E_GPIO_Port, &GPIO_InitStruct);

  /* Configure CD4067 #2 pins */
  GPIO_InitStruct.Pin = CD4067_2_S0_Pin;
  HAL_GPIO_Init(CD4067_2_S0_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_2_S1_Pin;
  HAL_GPIO_Init(CD4067_2_S1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_2_S2_Pin;
  HAL_GPIO_Init(CD4067_2_S2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_2_S3_Pin;
  HAL_GPIO_Init(CD4067_2_S3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_2_E_Pin;
  HAL_GPIO_Init(CD4067_2_E_GPIO_Port, &GPIO_InitStruct);

  /* Configure CD4067 #3 pins */
  GPIO_InitStruct.Pin = CD4067_3_S0_Pin;
  HAL_GPIO_Init(CD4067_3_S0_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_3_S1_Pin;
  HAL_GPIO_Init(CD4067_3_S1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_3_S2_Pin;
  HAL_GPIO_Init(CD4067_3_S2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_3_S3_Pin;
  HAL_GPIO_Init(CD4067_3_S3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_3_E_Pin;
  HAL_GPIO_Init(CD4067_3_E_GPIO_Port, &GPIO_InitStruct);

  /* Configure CD4067 #4 pins */
  GPIO_InitStruct.Pin = CD4067_4_S0_Pin;
  HAL_GPIO_Init(CD4067_4_S0_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_4_S1_Pin;
  HAL_GPIO_Init(CD4067_4_S1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_4_S2_Pin;
  HAL_GPIO_Init(CD4067_4_S2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_4_S3_Pin;
  HAL_GPIO_Init(CD4067_4_S3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = CD4067_4_E_Pin;
  HAL_GPIO_Init(CD4067_4_E_GPIO_Port, &GPIO_InitStruct);

  /* Initialize CD4067 multiplexers to known state */
  // CD4067 #1
  HAL_GPIO_WritePin(CD4067_1_S0_GPIO_Port, CD4067_1_S0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_1_S1_GPIO_Port, CD4067_1_S1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_1_S2_GPIO_Port, CD4067_1_S2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_1_S3_GPIO_Port, CD4067_1_S3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_1_E_GPIO_Port, CD4067_1_E_Pin, GPIO_PIN_SET); // Disable multiplexer initially

  // CD4067 #2
  HAL_GPIO_WritePin(CD4067_2_S0_GPIO_Port, CD4067_2_S0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_2_S1_GPIO_Port, CD4067_2_S1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_2_S2_GPIO_Port, CD4067_2_S2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_2_S3_GPIO_Port, CD4067_2_S3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_2_E_GPIO_Port, CD4067_2_E_Pin, GPIO_PIN_SET);

  // CD4067 #3
  HAL_GPIO_WritePin(CD4067_3_S0_GPIO_Port, CD4067_3_S0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_3_S1_GPIO_Port, CD4067_3_S1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_3_S2_GPIO_Port, CD4067_3_S2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_3_S3_GPIO_Port, CD4067_3_S3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_3_E_GPIO_Port, CD4067_3_E_Pin, GPIO_PIN_SET);

  // CD4067 #4
  HAL_GPIO_WritePin(CD4067_4_S0_GPIO_Port, CD4067_4_S0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_4_S1_GPIO_Port, CD4067_4_S1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_4_S2_GPIO_Port, CD4067_4_S2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_4_S3_GPIO_Port, CD4067_4_S3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(CD4067_4_E_GPIO_Port, CD4067_4_E_Pin, GPIO_PIN_SET);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
