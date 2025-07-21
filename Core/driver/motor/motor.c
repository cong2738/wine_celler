/*
 * motor.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */
#include "motor.h"

static TIM_HandleTypeDef *hMotorTim;
static uint32_t MotorTimChannel;

void Motor_Init(TIM_HandleTypeDef* htim, uint32_t channel)
{
	hMotorTim = htim;
	MotorTimChannel = channel;
}

void Motor_SetDuty(uint32_t duty)
{
    Motor_Start();

    if (duty == 0) {
        Motor_Stop();
        return;
    }

    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(hMotorTim);
    uint32_t ccr = (arr + 1) * duty / 100 - 1;
    __HAL_TIM_SET_COMPARE(hMotorTim, MotorTimChannel, ccr);
}

void Motor_Start()
{
	HAL_TIM_PWM_Start(hMotorTim, MotorTimChannel);
}

void Motor_Stop()
{
	HAL_TIM_PWM_Stop(hMotorTim, MotorTimChannel);
}
