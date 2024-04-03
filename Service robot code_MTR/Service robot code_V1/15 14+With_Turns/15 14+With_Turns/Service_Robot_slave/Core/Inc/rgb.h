/*
 * rgb.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Anusha
 */


#ifndef INC_RGB_H_
#define INC_RGB_H_

//#include "stm32f1xx_hal_tim.h"
#include "stdio.h"
#include "tim.h"

//Macros
#define MAX_LED 8
#define USE_BRIGHTNESS 0
#define PI 3.14159265

//Variables


void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_RGB_Red(void);
void Set_RGB_Green(void);
void Set_RGB_Yellow(void);
void Set_Brightness (int brightness);
void WS2812_Send (void);
void Reset_LED (void);
uint8_t rainbow_effect_left();
uint8_t rainbow_effect_right();

#endif /* INC_RGB_H_ */
