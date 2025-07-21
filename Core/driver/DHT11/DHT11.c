/*
 * DHT11.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */


#include "dht11.h"

// DWT 기반 마이크로초 지연 함수
static void delay_us(uint32_t us) {
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT - start) < cycles);
}

// DWT 초기화 함수
static void DWT_Init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

int DHT11_init(struct DHT11_Dev* dev, GPIO_TypeDef* port, uint16_t pin, TIM_HandleTypeDef* htim) {
    dev->port = port;
    dev->pin = pin;
    dev->htim = htim;

    // DWT 초기화 (마이크로초 지연용)
    DWT_Init();

    // GPIO를 OUTPUT으로 초기 설정
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = dev->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(dev->port, &GPIO_InitStruct);

    // 초기 상태는 HIGH
    HAL_GPIO_WritePin(dev->port, dev->pin, GPIO_PIN_SET);

    return 0;
}

int DHT11_read(struct DHT11_Dev* dev) {
    uint8_t i, j, temp;
    uint8_t data[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Step 1: GPIO를 OUTPUT 모드로 설정
    GPIO_InitStruct.Pin = dev->pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(dev->port, &GPIO_InitStruct);

    // Step 2: START 신호 생성
    // MCU가 LOW 신호를 최소 18ms 전송
    HAL_GPIO_WritePin(dev->port, dev->pin, GPIO_PIN_RESET);
    HAL_Delay(20);  // 18ms 이상

    // MCU가 HIGH 신호를 20-40us 전송
    HAL_GPIO_WritePin(dev->port, dev->pin, GPIO_PIN_SET);
    delay_us(30);   // 30us

    // Step 3: GPIO를 INPUT 모드로 변경 (센서가 응답할 수 있도록)
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // 풀업 활성화
    HAL_GPIO_Init(dev->port, &GPIO_InitStruct);

    // Step 4: DHT11 응답 신호 확인
    // DHT11이 LOW 신호를 80us 전송 (응답 시작)
    uint32_t timeout_start = HAL_GetTick();
    while (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_SET) {
        if (HAL_GetTick() - timeout_start > 1) {
            return DHT11_ERROR_TIMEOUT;
        }
    }

    // DHT11이 HIGH 신호를 80us 전송 (데이터 전송 준비)
    timeout_start = HAL_GetTick();
    while (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_RESET) {
        if (HAL_GetTick() - timeout_start > 1) {
            return DHT11_ERROR_TIMEOUT;
        }
    }

    timeout_start = HAL_GetTick();
    while (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_SET) {
        if (HAL_GetTick() - timeout_start > 1) {
            return DHT11_ERROR_TIMEOUT;
        }
    }

    // Step 5: 40비트 데이터 읽기 (5바이트 * 8비트)
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 8; i++) {
            // 각 비트는 LOW 50us로 시작
            timeout_start = HAL_GetTick();
            while (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_RESET) {
                if (HAL_GetTick() - timeout_start > 1) {
                    return DHT11_ERROR_TIMEOUT;
                }
            }

            // HIGH 신호 지속시간으로 0 또는 1 판별
            // 26-28us = 0, 70us = 1
            delay_us(30);  // 30us 후 상태 확인

            data[j] <<= 1;  // 비트 시프트

            if (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_SET) {
                data[j] |= 1;  // 1 비트

                // HIGH 신호가 끝날 때까지 대기
                timeout_start = HAL_GetTick();
                while (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_SET) {
                    if (HAL_GetTick() - timeout_start > 1) {
                        return DHT11_ERROR_TIMEOUT;
                    }
                }
            }
            // else: 이미 0 비트로 처리됨
        }
    }

    // Step 6: 체크섬 검증
    if (data[4] != (data[0] + data[1] + data[2] + data[3])) {
        return DHT11_ERROR_CHECKSUM;
    }

    // Step 7: 데이터 저장
    dev->humidity = data[0];     // 습도 정수 부분
    dev->temperature = data[2];  // 온도 정수 부분

    return DHT11_SUCCESS;
}
