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
#include "stm32l4xx_hal.h"

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

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define SPI_CS_Pin GPIO_PIN_0
#define SPI_CS_GPIO_Port GPIOC
#define MAGNETO_STATUS_Pin GPIO_PIN_1
#define MAGNETO_STATUS_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define STEPPER_DIR_Pin GPIO_PIN_7
#define STEPPER_DIR_GPIO_Port GPIOA
#define GPS_PPS_Pin GPIO_PIN_4
#define GPS_PPS_GPIO_Port GPIOC
#define BTN_CENTER_Pin GPIO_PIN_5
#define BTN_CENTER_GPIO_Port GPIOC
#define MAGNETO_INT_Pin GPIO_PIN_0
#define MAGNETO_INT_GPIO_Port GPIOB
#define LED_3_Pin GPIO_PIN_1
#define LED_3_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_2
#define LED_1_GPIO_Port GPIOB
#define BTN_BOTTOM_Pin GPIO_PIN_11
#define BTN_BOTTOM_GPIO_Port GPIOB
#define BTN_BOTTOM_EXTI_IRQn EXTI15_10_IRQn
#define GPS_ENN_Pin GPIO_PIN_13
#define GPS_ENN_GPIO_Port GPIOB
#define LED_6_Pin GPIO_PIN_14
#define LED_6_GPIO_Port GPIOB
#define LED_4_Pin GPIO_PIN_15
#define LED_4_GPIO_Port GPIOB
#define BTN_LEFT_Pin GPIO_PIN_6
#define BTN_LEFT_GPIO_Port GPIOC
#define LED_0_Pin GPIO_PIN_7
#define LED_0_GPIO_Port GPIOC
#define BTN_TOP_Pin GPIO_PIN_8
#define BTN_TOP_GPIO_Port GPIOC
#define BTN_RIGHT_Pin GPIO_PIN_9
#define BTN_RIGHT_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_8
#define LED_2_GPIO_Port GPIOA
#define STEPPER_MS1_Pin GPIO_PIN_11
#define STEPPER_MS1_GPIO_Port GPIOA
#define STEPPER_ENN_Pin GPIO_PIN_12
#define STEPPER_ENN_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ENC_BTN_Pin GPIO_PIN_15
#define ENC_BTN_GPIO_Port GPIOA
#define ENC_BTN_EXTI_IRQn EXTI15_10_IRQn
#define LED_5_Pin GPIO_PIN_4
#define LED_5_GPIO_Port GPIOB
#define LED_7_Pin GPIO_PIN_5
#define LED_7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
