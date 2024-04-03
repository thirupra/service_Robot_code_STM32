/*
 * rgb.c
 *
 *  Created on: Dec 16, 2022
 *      Author: Anusha
 */

#include "rgb.h"

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness

int datasentflag=0;
uint16_t pwmData[(24*MAX_LED)+50];
uint16_t effStep = 0;
uint8_t rgb_var=0;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&htim4, TIM_CHANNEL_3);
	datasentflag=1;
}

void Set_LED (int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

void Set_RGB_Red()
{
	while(rgb_var < MAX_LED)
	  {
		  Set_LED(rgb_var, 255, 0, 0);
		  rgb_var++;
	  }
	  WS2812_Send();
	  rgb_var = 0;
}

void Set_RGB_Green()
{
	while(rgb_var < MAX_LED)
	  {
		  Set_LED(rgb_var, 0, 255, 0);
		  rgb_var++;
	  }
	  WS2812_Send();
	  rgb_var = 0;
}

void Set_RGB_Yellow(void)
{
	while(rgb_var < MAX_LED)
	  {
		  Set_LED(rgb_var, 255, 255, 0);
		  rgb_var++;
	  }
	  WS2812_Send();
	  rgb_var = 0;
}


void Set_Brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif

}

void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 60;  // 2/3 of 90
			}

			else pwmData[indx] = 30;  // 1/3 of 90

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)pwmData, indx);
	while (!datasentflag){};
	datasentflag = 0;
}

void Reset_LED (void)
{
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Data[i][0] = i;
		LED_Data[i][1] = 0;
		LED_Data[i][2] = 0;
		LED_Data[i][3] = 0;
	}
	WS2812_Send();
}

uint8_t rainbow_effect_left() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 8
    // Steps: 13 - Delay: 54
    // Colors: 3 (255.0.0, 0.255.0, 0.0.255)
    // Options: rainbowlen=8, toLeft=true,
//  if(millis() - strip_0.effStart < 54 * (strip_0.effStep)) return 0x00;

  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<8;j++) {
    ind = effStep + j * 1.625;
    switch((int)((ind % 13) / 4.333333333333333)) {
      case 0: factor1 = 1.0 - ((float)(ind % 13 - 0 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 0) % 13) / 4.333333333333333;
              /************ chnaged here *********/
              Set_LED(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 13 - 1 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 4.333333333333333) % 13) / 4.333333333333333;
              Set_LED(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              WS2812_Send();
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 13 - 2 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 8.666666666666666) % 13) / 4.333333333333333;
              Set_LED(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
    }
  }
  if(effStep >= 13) {effStep=0; return 0x03; }
  else effStep++;
  return 0x01;
}

uint8_t rainbow_effect_right() {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 8
    // Steps: 14 - Delay: 30
    // Colors: 3 (255.0.0, 0.255.0, 0.0.255)
    // Options: rainbowlen=8, toLeft=false,
//  if(millis() - strip_0.effStart < 30 * (strip_0.effStep)) return 0x00;
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<8;j++) {
    ind = 14 - (int16_t)(effStep - j * 1.75) % 14;
    switch((int)((ind % 14) / 4.666666666666667)) {
      case 0: factor1 = 1.0 - ((float)(ind % 14 - 0 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 0) % 14) / 4.666666666666667;
              Set_LED(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 14 - 1 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 4.666666666666667) % 14) / 4.666666666666667;
              Set_LED(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              WS2812_Send();
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 14 - 2 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 9.333333333333334) % 14) / 4.666666666666667;
              Set_LED(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              WS2812_Send();
              break;
    }
  }
  if(effStep >= 14) {effStep = 0; return 0x03; }
  else effStep++;
  return 0x01;
}



