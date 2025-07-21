/*
 * distance.h
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#ifndef AP_INC_DISTANCE_H_
#define AP_INC_DISTANCE_H_

#include "stm32f4xx_hal.h"

// 상태 코드
#define DISTANCE_SUCCESS    1
#define DISTANCE_ERROR      0

// 함수 프로토타입
void Distance_Init(void);
int Distance_Read(void);
uint16_t Distance_GetValue(void);
void Distance_TimerCallback(void);  // 타이머 인터럽트 콜백

#endif /* AP_INC_DISTANCE_H_ */
