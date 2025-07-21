/*
 * hypersonic.h
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_HYPERSONIC_HYPERSONIC_H_
#define DRIVER_HYPERSONIC_HYPERSONIC_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

// HCSR04 상태 코드
#define HCSR04_SUCCESS         1
#define HCSR04_ERROR_TIMEOUT   2
#define HCSR04_ERROR_NO_ECHO   3

// HCSR04 디바이스 구조체
typedef struct HCSR04_Dev {
    GPIO_TypeDef* trig_port;
    uint16_t trig_pin;
    GPIO_TypeDef* echo_port;
    uint16_t echo_pin;
    TIM_HandleTypeDef* htim;
    uint16_t distance_cm;
} HCSR04_Dev;

// 함수 프로토타입
int HCSR04_init(struct HCSR04_Dev* dev,
               GPIO_TypeDef* trig_port, uint16_t trig_pin,
               GPIO_TypeDef* echo_port, uint16_t echo_pin,
               TIM_HandleTypeDef* htim);
int HCSR04_read(struct HCSR04_Dev* dev);

#endif /* DRIVER_HYPERSONIC_HYPERSONIC_H_ */
