///*
// * HCSR04.c
// *
// *  Created on: Dec 8, 2022
// *      Author: Naveen
// */
//
//
#include "HSCR04.h"
#include "usart.h"
#include "stdio.h"

uint32_t pMillis;
uint32_t val1 = 0;
uint32_t val2 = 0;
uint16_t distance  = 0;





char Buffer[50];

void send_pulse()
{
	HAL_GPIO_WritePin(ULTRA_CENTER_TRIG_GPIO_Port, ULTRA_CENTER_TRIG_Pin, GPIO_PIN_SET);
	//HAL_Delay(300);
	HAL_GPIO_WritePin(ULTRA_CENTER_TRIG_GPIO_Port, ULTRA_CENTER_TRIG_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Start(&htim1);
	HAL_GPIO_WritePin(ULTRA_CENTER_TRIG_GPIO_Port, ULTRA_CENTER_TRIG_Pin, GPIO_PIN_RESET);
}

uint16_t center_ultra()
{
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);
		  	  __HAL_TIM_SET_COUNTER(&htim1, 0);
		  	   while (__HAL_TIM_GET_COUNTER (&htim1) < 10);  // wait for 10 us
		  	//  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);

		  	   pMillis = HAL_GetTick();
		  	   while (!(HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 10 >  HAL_GetTick());
		  	   val1 = __HAL_TIM_GET_COUNTER (&htim1);
		  	//  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   pMillis = HAL_GetTick();
		  	   while ((HAL_GPIO_ReadPin (ECHO_PORT, ECHO_PIN)) && pMillis + 50 > HAL_GetTick());
		  	   val2 = __HAL_TIM_GET_COUNTER (&htim1);
		  //	  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   distance = (val2-val1)* 0.034/2;
		  	   return distance;
}

uint16_t right_ultra()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
		  	  __HAL_TIM_SET_COUNTER(&htim1, 0);
		  	   while (__HAL_TIM_GET_COUNTER (&htim1) < 10);  // wait for 10 us
		  	//  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

		  	   pMillis = HAL_GetTick();
		  	   while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)) && pMillis + 10 >  HAL_GetTick());
		  	   val1 = __HAL_TIM_GET_COUNTER (&htim1);
		  	//  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   pMillis = HAL_GetTick();
		  	   while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_15)) && pMillis + 50 > HAL_GetTick());
		  	   val2 = __HAL_TIM_GET_COUNTER (&htim1);
		  //	  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   distance = (val2-val1)* 0.034/2;
		  	   return distance;
}

uint16_t Left_ultra()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		  	  __HAL_TIM_SET_COUNTER(&htim1, 0);
		  	   while (__HAL_TIM_GET_COUNTER (&htim1) < 10);  // wait for 10 us
		  	//  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

		  	   pMillis = HAL_GetTick();
		  	   while (!(HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)) && pMillis + 10 >  HAL_GetTick());
		  	   val1 = __HAL_TIM_GET_COUNTER (&htim1);
		  	//  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   pMillis = HAL_GetTick();
		  	   while ((HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_14)) && pMillis + 50 > HAL_GetTick());
		  	   val2 = __HAL_TIM_GET_COUNTER (&htim1);
		  //	  HAL_UART_Transmit(&huart2, "HELLO ANUSHA", 13, 100);

		  	   distance = (val2-val1)* 0.034/2;
		  	   return distance;
}
