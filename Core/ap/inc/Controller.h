/*
 * Controller.h
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */

#ifndef AP_CONTROLLER_H_
#define AP_CONTROLLER_H_

#include "ModeCtrlModel.h"
#include "TimeWatch.h"

void ctrl_UartRxCallBack();
void Controller_setEvent(uint32_t inputData);
void Controller_Excute();
char* get_LcdData0();
char* get_LcdData1();
uint32_t get_FndData();
int get_motorState();
int get_lightState();
void set_menu(char* menuData);

#endif /* AP_CONTROLLER_H_ */
