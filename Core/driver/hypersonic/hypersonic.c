/*
 * hypersonic.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#include "hypersonic.h"

// 간단한 마이크로초 지연 함수
static void delay_us(uint32_t us) {
    volatile uint32_t count = us * (SystemCoreClock / 1000000) / 4;
    while(count--);
}

int HCSR04_init(struct HCSR04_Dev* dev,
               GPIO_TypeDef* trig_port, uint16_t trig_pin,
               GPIO_TypeDef* echo_port, uint16_t echo_pin,
               TIM_HandleTypeDef* htim) {

    dev->trig_port = trig_port;
    dev->trig_pin = trig_pin;
    dev->echo_port = echo_port;
    dev->echo_pin = echo_pin;
    dev->htim = htim;
    dev->distance_cm = 0;

    // Trig 핀을 OUTPUT으로 설정
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = dev->trig_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(dev->trig_port, &GPIO_InitStruct);

    // Echo 핀을 INPUT으로 설정
    GPIO_InitStruct.Pin = dev->echo_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(dev->echo_port, &GPIO_InitStruct);

    // 초기 상태는 LOW
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);
    HAL_Delay(100);

    return HCSR04_SUCCESS;
}

int HCSR04_read(struct HCSR04_Dev* dev) {
    uint32_t echo_time = 0;
    uint32_t timeout_start = 0;

    // Step 1: Trig 핀 초기화 및 펄스 전송
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);
    delay_us(5);

    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_SET);
    delay_us(15);
    HAL_GPIO_WritePin(dev->trig_port, dev->trig_pin, GPIO_PIN_RESET);

    // Step 2: Echo 핀이 HIGH가 될 때까지 대기
    timeout_start = HAL_GetTick();
    while (HAL_GPIO_ReadPin(dev->echo_port, dev->echo_pin) == GPIO_PIN_RESET) {
        if (HAL_GetTick() - timeout_start > 50) {
            dev->distance_cm = 999;
            return HCSR04_ERROR_TIMEOUT;
        }
    }

    // Step 3: Echo 핀이 HIGH인 시간 측정 시작
    __HAL_TIM_SET_COUNTER(dev->htim, 0);

    // Step 4: Echo 핀이 LOW로 떨어질 때까지 대기
    timeout_start = HAL_GetTick();
    while (HAL_GPIO_ReadPin(dev->echo_port, dev->echo_pin) == GPIO_PIN_SET) {
        if (HAL_GetTick() - timeout_start > 50) {
            dev->distance_cm = 998;
            return HCSR04_ERROR_TIMEOUT;
        }
    }

    echo_time = __HAL_TIM_GET_COUNTER(dev->htim);

    // Step 5: 거리 계산
    if (echo_time > 0) {
        // 타이머가 1MHz(1μs)로 설정된 경우:
        // 거리(cm) = (echo_time * 0.034) / 2
        // 음속 = 340m/s = 0.034cm/μs

        dev->distance_cm = (echo_time * 34) / 2000;  // 정수 연산으로 변경

        // 유효 범위 확인 (2cm ~ 400cm)
        if (dev->distance_cm < 2) {
            dev->distance_cm = 2;
        } else if (dev->distance_cm > 400) {
            dev->distance_cm = 400;
        }
    } else {
        dev->distance_cm = 997;
        return HCSR04_ERROR_NO_ECHO;
    }

    return HCSR04_SUCCESS;
}
