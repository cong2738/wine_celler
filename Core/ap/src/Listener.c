/*
 * Listener.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */

#include "Listener.h"
#include <string.h>
#include "Button.h"
#include "usart.h"
#include "DHT11.h"
#include "Controller.h"
#include "distance.h"


Button_Handler_t hBtnMode;
Button_Handler_t hBtnRunStop;
Button_Handler_t hBtnClear;

static uint8_t rxData = 0;
static Que_TypeDef uartRxQue = {0};
static uint16_t stored_distance = 0;  // 거리 정보

static void Listener_CheckButton();
static void Listener_CheckUart();
static void Listener_CheckDHT11();

static DHT11_Dev listener_DHT11Data;

void Listener_CheckButton() { // check button state
	static uint32_t chkBtnTime = 0;
	uint32_t curTick = HAL_GetTick();

	if(curTick - chkBtnTime < 10) return;
	chkBtnTime = curTick;

	if (Button_GetState(&hBtnMode)== ACT_RELEASED) {
		Controller_setEvent(controlId_BTN0);
		return;
	}
	if (Button_GetState(&hBtnRunStop)== ACT_PUSHED) {
		Controller_setEvent(controlId_BTN1);
		return;
	}
	if (Button_GetState(&hBtnClear)== ACT_PUSHED) {
		Controller_setEvent(controlId_BTN2);
		return;
	}
}

char menu[10];
void Listener_CheckUart()
{
	static int strIdx = 0;
	if (isQueEmpty(&uartRxQue)) return;
	int uartRxData = deQue(&uartRxQue);
	if(uartRxData == '!') {
		set_menu(menu);
		strIdx = 0;
		return;
	}
	menu[strIdx] = uartRxData;
	strIdx = (strIdx+ 1) % 10;
}

void Listener_CheckDHT11() { // check UART rxData
	DHT11_read(&listener_DHT11Data);
}

///// public /////
void Listener_UartCallBack() {
	HAL_UART_Receive_IT(&huart2, &rxData, 4);  //interrupt en
	enQue(&uartRxQue, rxData);
}

void Listener_Init()
{
	Button_Init(&hBtnMode, GPIOB, GPIO_PIN_5);
	Button_Init(&hBtnRunStop, GPIOB, GPIO_PIN_3);
	Button_Init(&hBtnClear, GPIOA, GPIO_PIN_10);
	HAL_UART_Receive_IT(&huart2, &rxData, 1); // uart recv interrupt enable(UART IT initializing)
	Que_Init(&uartRxQue);
	DHT11_init(&listener_DHT11Data, GPIOA, GPIO_PIN_9, &htim2);

}

void Listener_Excute()
{
	Listener_CheckButton();
	Listener_CheckUart();
	Listener_CheckDHT11();
	stored_distance = Distance_GetValue();// Distance 모듈을 통해 거리 정보를 가져와서 저장
}

int get_tem() {
	return listener_DHT11Data.temperature;
}

int get_hue() {
	return listener_DHT11Data.humidity;
}

char get_rxChar() {
	return rxData;
}

// 저장된 거리 정보를 반환하는 get 함수
uint16_t Listener_GetStoredDistance(void)
{
    return stored_distance;
}
