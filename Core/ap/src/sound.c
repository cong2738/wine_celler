/*
 * sound.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#include "sound.h"

void Sound_BeepDelay(uint32_t freq, uint32_t length);
void Sound_BeepTiming(uint32_t freq, uint32_t time, uint32_t start, uint32_t end);

void Sound_BeepDelay(uint32_t freq, uint32_t length){
	Buzzer_SetFreq(freq);
	Buzzer_Start();
	HAL_Delay(length);
	Buzzer_Stop();
}

void Sound_BeepTiming(uint32_t freq, uint32_t time, uint32_t start, uint32_t end) {
	if(time < start || time > end) return;
	Buzzer_SetFreq(freq);
	Buzzer_Start();
}

void Sound_Init()
{
	Buzzer_Init(&htim3, TIM_CHANNEL_1);
}

void Sound_Power_On()
{
	Sound_BeepDelay(1047, 50);
	Sound_BeepDelay(1319, 50);
	Sound_BeepDelay(1568, 50);
	Sound_BeepDelay(2039, 50);
}
void Sound_Power_Off()
{

}
void Sound_ChangeMode()
{

}
void Sound_Alarm()
{

}
