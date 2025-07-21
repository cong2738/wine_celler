/*
 * Listener.h
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */

#ifndef AP_LISTENER_H_
#define AP_LISTENER_H_

#include "stm32f4xx_hal.h"
#include "ModeCtrlModel.h"
#include "queue.h"
#include "Controller.h"

void Listener_Excute();
void Listener_Init();
void Listener_UartCallBack();
int get_tem();
int get_hue();
char get_rxChar();
uint16_t Listener_GetStoredDistance(void);

#endif /* AP_LISTENER_H_ */
