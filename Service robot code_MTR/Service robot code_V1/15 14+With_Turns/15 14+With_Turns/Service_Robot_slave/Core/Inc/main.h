/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef enum
{

  Invalid_frame  = 0x00U,
  Invalid_Packet_Type = 0x01U,
  Invalid_Sensor_Type = 0x02U,
  Invalid_Sensor_ID = 0x03U,
  Invalid_Function_ID = 0x04U,
  Invalid_Data = 0x05U,
  Frame_Success  = 0x0FU,
} Frame_Status;

typedef enum
{
	CMD = 0xF0U,
	RESP = 0xF1U,
	ACK = 0xF2U,
    NACK = 0xF3U,
}Packet_Type;


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
extern uint8_t tx_frame[22];

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR_DIR_R_Pin GPIO_PIN_14
#define MOTOR_DIR_R_GPIO_Port GPIOC
#define MOTOR_DIR_L_Pin GPIO_PIN_15
#define MOTOR_DIR_L_GPIO_Port GPIOC
#define MOTO_PWM_R_Pin GPIO_PIN_0
#define MOTO_PWM_R_GPIO_Port GPIOA
#define MOTOR_PWM_L_Pin GPIO_PIN_1
#define MOTOR_PWM_L_GPIO_Port GPIOA
#define Left_WE_Pin_A_Pin GPIO_PIN_4
#define Left_WE_Pin_A_GPIO_Port GPIOA
#define Left_WE_Pin_A_EXTI_IRQn EXTI4_IRQn
#define Left_WE_Pin_B_Pin GPIO_PIN_5
#define Left_WE_Pin_B_GPIO_Port GPIOA
#define Left_WE_Pin_B_EXTI_IRQn EXTI9_5_IRQn
#define MODE_SELECTION_Pin GPIO_PIN_6
#define MODE_SELECTION_GPIO_Port GPIOA
#define BATTERY_RELAY_Pin GPIO_PIN_7
#define BATTERY_RELAY_GPIO_Port GPIOA
#define BATTERY_ADC_Pin GPIO_PIN_0
#define BATTERY_ADC_GPIO_Port GPIOB
#define LED_RING_Pin GPIO_PIN_1
#define LED_RING_GPIO_Port GPIOB
#define FAN_Pin GPIO_PIN_2
#define FAN_GPIO_Port GPIOB
#define ULTRA_RIGHT_TRIG_Pin GPIO_PIN_12
#define ULTRA_RIGHT_TRIG_GPIO_Port GPIOB
#define ULTRA_LEFT_TRIG_Pin GPIO_PIN_13
#define ULTRA_LEFT_TRIG_GPIO_Port GPIOB
#define ULTRA_LEFT_ECHO_Pin GPIO_PIN_14
#define ULTRA_LEFT_ECHO_GPIO_Port GPIOB
#define ULTRA_RIGHT_ECHO_Pin GPIO_PIN_15
#define ULTRA_RIGHT_ECHO_GPIO_Port GPIOB
#define Right_WE_Pin_B_Pin GPIO_PIN_8
#define Right_WE_Pin_B_GPIO_Port GPIOA
#define Right_WE_Pin_B_EXTI_IRQn EXTI9_5_IRQn
#define Right_WE_Pin_A_Pin GPIO_PIN_9
#define Right_WE_Pin_A_GPIO_Port GPIOA
#define Right_WE_Pin_A_EXTI_IRQn EXTI9_5_IRQn
#define ULTRA_CENTER_TRIG_Pin GPIO_PIN_11
#define ULTRA_CENTER_TRIG_GPIO_Port GPIOA
#define ULTRA_CENTER_ECHO_Pin GPIO_PIN_12
#define ULTRA_CENTER_ECHO_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_5
#define BUZZER_GPIO_Port GPIOB
#define UART_PI_TX_Pin GPIO_PIN_6
#define UART_PI_TX_GPIO_Port GPIOB
#define UART_PI_RX_Pin GPIO_PIN_7
#define UART_PI_RX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
