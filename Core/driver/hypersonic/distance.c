/*
 * distance.c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#include "distance.h"
#include "usart.h"
#include "tim.h"
#include <stdio.h>
#include <string.h>

// 전역 변수
static volatile uint16_t echo_count = 0;        // Echo HIGH 시간 카운트 (ms 단위)
static volatile uint8_t echo_measuring = 0;     // 측정 중 플래그
static volatile uint8_t echo_done = 0;          // 측정 완료 플래그
static volatile uint8_t prev_echo_state = 0;    // 이전 Echo 상태
static volatile uint16_t current_distance = 0;
static uint32_t measurement_count = 0;

// 마이크로초 지연 함수
static void delay_us(uint32_t us) {
    volatile uint32_t count = us * (SystemCoreClock / 1000000) / 3;
    while(count--);
}

// UART 디버깅 함수
static void Debug_SendMessage(const char* message) {
    HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 1000);
}

void Distance_Init(void)
{
    char msg[100];

    // GPIO 설정
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // PB6 (Trig) - OUTPUT
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

    // PC7 (Echo) - INPUT
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // 타이머 인터럽트 시작 (1ms 주기)
    HAL_TIM_Base_Start_IT(&htim2);

    sprintf(msg, "Distance: HC-SR04 initialized (1ms interrupt, ~17cm resolution)\r\n");
    Debug_SendMessage(msg);
}

// Trig 신호 전송
static void Distance_SendTrigger(void)
{
    // 측정 상태 초기화
    echo_measuring = 0;
    echo_done = 0;
    echo_count = 0;
    current_distance = 0;

    // Trig 신호 전송 (PB6)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
    delay_us(5);  // 5μs 안정화

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    delay_us(12); // 12μs 펄스
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
}

int Distance_Read(void)
{
    char msg[100];
    uint32_t timeout_start;

    measurement_count++;

    // Trig 신호 전송
    Distance_SendTrigger();

    // 측정 완료까지 대기 (최대 30ms)
    timeout_start = HAL_GetTick();
    while (!echo_done && (HAL_GetTick() - timeout_start) < 30) {
        HAL_Delay(1);  // 1ms씩 대기
    }

    if (echo_done) {
        echo_done = 0;  // 플래그 리셋

        sprintf(msg, "Distance[%lu]: %d ms -> %d cm\r\n",
                measurement_count, echo_count, current_distance);
        Debug_SendMessage(msg);

        return DISTANCE_SUCCESS;
    } else {
        sprintf(msg, "Distance[%lu]: Timeout\r\n", measurement_count);
        Debug_SendMessage(msg);

        current_distance = 0;
        return DISTANCE_ERROR;
    }
}

uint16_t Distance_GetValue(void)
{
    return current_distance;
}

// 타이머 인터럽트 콜백 (ap_main.c에서 호출)
void Distance_TimerCallback(void)
{
    // Echo 핀 상태 읽기 (PC7)
    uint8_t echo_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);

    // Echo 신호 상태 변화 감지
    if (echo_state == 1 && prev_echo_state == 0) {
        // LOW -> HIGH: 측정 시작
        echo_measuring = 1;
        echo_count = 0;
        echo_done = 0;
    }
    else if (echo_state == 0 && prev_echo_state == 1) {
        // HIGH -> LOW: 측정 완료
        echo_measuring = 0;
        echo_done = 1;

        // 거리 계산 (직접 ms 단위로 계산)
        // echo_count는 ms 단위
        // 음속 = 343 m/s = 34.3 cm/ms
        // 거리 = (echo_time_ms * 34.3) / 2
        // 정수 연산: distance = (echo_time_ms * 343) / 20
        current_distance = (echo_count * 343) / 20;

        // 유효 범위 제한
        if (current_distance < 2) current_distance = 2;
        if (current_distance > 400) current_distance = 400;

        // 1ms 해상도 제한으로 인한 최소 거리
        // 1ms = 약 17cm이므로 더 정확한 측정은 불가능
        if (current_distance < 17 && echo_count == 1) {
            current_distance = 17;  // 1ms = 약 17cm
        }
    }

    // Echo가 HIGH인 동안 카운트 증가
    if (echo_measuring && echo_state == 1) {
        echo_count++;

        // 타임아웃 방지 (25ms = 약 400cm)
        if (echo_count > 25) {
            echo_measuring = 0;
            echo_done = 1;
            current_distance = 400;  // 최대 거리
        }
    }

    prev_echo_state = echo_state;
}
