/*
 * motor.h
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_MOTOR_MOTOR_H_
#define DRIVER_MOTOR_MOTOR_H_

#include "tim.h"
#include "stm32f4xx_hal.h"

void Motor_Init(TIM_HandleTypeDef* htim, uint32_t channel);
void Motor_SetDuty(uint32_t duty);
void Motor_Start();
void Motor_Stop();

#endif /* DRIVER_MOTOR_MOTOR_H_ */
