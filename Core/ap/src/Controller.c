/*
 * Controller.c
 *
 *  Created on: Jun 24, 2025
 *      Author: kccistc
 */

#include "Controller.h"
#include "ModeCtrlModel.h"
#include "Listener.h"
#include "string.h"

uint32_t controlE;
char inputStr[50];

typedef enum {FND_HT, FND_TIME}FND_SHOWDATA; // fnd mode enum
#define LCD_DATA_NUM 4
#define FND_dataIndex_NUM 2
#define RXSTR_NUM 4

static uint32_t motOff_Tem = 30;
static uint32_t ledOff_Dis = 100;
uint32_t hue = 10;
uint32_t tem = 10;
uint32_t dis = 99;
timeWatch_t watchData;

static char LCD_DATA0[4][18] = {"soda","beer","cola","wine"};
static char LCD_DATA1[4][18] = {"TEST0","TEST1","TEST2","TEST3"};
static uint32_t FND_DATA[2] = {1234, 0000};
static int LCD_dataIndex = 0;
static int FND_dataIndex = 0;

void ctrl_LCD_DataSel();
void ctrl_FND_DataMode();


void ctrl_LCD_DataSel() { // LCD show Data sel ctrl
	if (controlE == controlId_BTN0) {
		controlE = controlId_IDLE;
		LCD_dataIndex = (LCD_dataIndex + 1) % LCD_DATA_NUM;
		return;
	}
	if (controlE == controlId_BTN1) {
		controlE = controlId_IDLE;
		LCD_dataIndex = (LCD_dataIndex - 1);
		if(LCD_dataIndex < 0) LCD_dataIndex = LCD_DATA_NUM - 1;
		return;
	}
}

void ctrl_FND_DataMode() { // fnd show Data sel ctrl
	if (controlE == controlId_BTN2) {
		controlE = controlId_IDLE;
		FND_dataIndex = (FND_dataIndex + 1) % FND_dataIndex_NUM;
		return;
	}
	if (controlE == controlId_BTN3) {
		controlE = controlId_IDLE;
		FND_dataIndex = (FND_dataIndex - 1);
		if(FND_dataIndex < 0) FND_dataIndex = FND_dataIndex_NUM - 1;
		return;
	}
}

///// public /////

void Controller_setEvent(uint32_t inputData)
{
	controlE = inputData;
}

void Controller_Excute()
{
	watchData = get_watch();
	tem = get_tem();
	hue = get_hue();
	dis = Listener_GetStoredDistance();
	FND_DATA[0] = dis;
//	FND_DATA[0] = tem*100 + hue;
	FND_DATA[1] = watchData.hour*100+watchData.min;
	ctrl_LCD_DataSel();
	ctrl_FND_DataMode();
}

char* get_LcdData0()
{
	return LCD_DATA0[LCD_dataIndex];
}

char* get_LcdData1()
{
	return LCD_DATA1[LCD_dataIndex];
}

uint32_t get_FndData()
{
	return FND_DATA[FND_dataIndex];
}

int get_motorState() {
	return (tem > motOff_Tem) ? 1 : 0;
}

int get_lightState() {
	return (dis < ledOff_Dis) ? 1 : 0;
}

void set_menu(char* menuData){
	strcpy(LCD_DATA0[0],menuData);
}
