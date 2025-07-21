/*
 * DHT11.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_DHT11_DHT11_H_
#define DRIVER_DHT11_DHT11_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

// DHT11 상태 코드
#define DHT11_SUCCESS         1
#define DHT11_ERROR_CHECKSUM  2
#define DHT11_ERROR_TIMEOUT   3

// DHT11 디바이스 구조체
typedef struct DHT11_Dev {
    GPIO_TypeDef* port;
    uint16_t pin;
    TIM_HandleTypeDef* htim;
    uint8_t temperature;
    uint8_t humidity;
} DHT11_Dev;

// 함수 프로토타입
int DHT11_init(struct DHT11_Dev* dev, GPIO_TypeDef* port, uint16_t pin, TIM_HandleTypeDef* htim);
int DHT11_read(struct DHT11_Dev* dev);

#endif /* DRIVER_DHT11_DHT11_H_ */
