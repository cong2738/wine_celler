/*
 * Presenter.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */
#include "Presenter.h"

#include <string.h>
#include <stdio.h>
#include "Controller.h"
#include "usart.h"
#include "motor.h"
#include "DHT11.h"
#include "sound.h"
#include "light.h"

Led_TypeDef Light_led = {GPIOC, GPIO_PIN_9};

int motor = 0;
int light = 0;

void Presenter_DisTimeWatchFnd();

void Presenter_DisTimeWatchFnd(){
	FND_WriteData(get_FndData());
//	FND_WriteData(motor*10 + light);
	FND_WriteDp(0b1111, FND_DP_OFF);
}

///// public /////
void Presenter_Excute()
{
	motor = get_motorState();
	light = get_lightState();
	Presenter_DisTimeWatchFnd();
	LCD_writeStringXY(0,0,get_LcdData0());
//	LCD_writeStringXY(1,0,get_LcdData1());
	int temp = (get_motorState()) ? 100 : 30;
	Motor_SetDuty(temp);
	Light_ctrl(&Light_led, (get_lightState())?SET:RESET);
}

void Presenter_Init() {
	LCD_Init(&hi2c1);
	Sound_Init();
	Sound_Power_On();
	Buzzer_Init(&htim3, TIM_CHANNEL_1);
	Motor_Init(&htim1, TIM_CHANNEL_1);
	Motor_Start();
	Light_init(&Light_led);
	Light_ctrl(&Light_led, SET);
}
