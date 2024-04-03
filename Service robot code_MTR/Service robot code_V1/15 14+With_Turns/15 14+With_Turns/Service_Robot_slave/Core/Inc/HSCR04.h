/*
 * HSCR04.h
 *
 *  Created on: Dec 8, 2022
 *      Author: Naveen
 */

#ifndef INC_HSCR04_H_
#define INC_HSCR04_H_

#include "main.h"
#include "tim.h"

#define ULTRA_RIGHT_TRIG_Pin GPIO_PIN_12
#define ULTRA_RIGHT_TRIG_GPIO_Port GPIOB
#define ULTRA_LEFT_TRIG_Pin GPIO_PIN_13
#define ULTRA_LEFT_TRIG_GPIO_Port GPIOB
#define ULTRA_LEFT_ECHO_Pin GPIO_PIN_14
#define ULTRA_LEFT_ECHO_GPIO_Port GPIOB
#define ULTRA_RIGHT_ECHO_Pin GPIO_PIN_15
#define ULTRA_RIGHT_ECHO_GPIO_Port GPIOB

#define ULTRA_CENTER_TRIG_Pin GPIO_PIN_11
#define ULTRA_CENTER_TRIG_GPIO_Port GPIOA
#define ULTRA_CENTER_ECHO_Pin GPIO_PIN_12
#define ULTRA_CENTER_ECHO_GPIO_Port GPIOA

#define TRIG_PIN GPIO_PIN_11
#define TRIG_PORT GPIOA
#define ECHO_PIN GPIO_PIN_12
#define ECHO_PORT GPIOA



//char string[15];

void send_pulse();
uint16_t center_ultra();
uint16_t right_ultra();
uint16_t Left_ultra();




#endif /* INC_HSCR04_H_ */
