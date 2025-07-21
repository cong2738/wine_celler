/* ap_main.c */

#include "ap_main.h"
#include "Listener.h"
#include "Controller.h"
#include "Presenter.h"
#include "distance.h"

volatile uint8_t dotBlink = 0;
volatile uint16_t blinkTick = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2) {
		FND_DispDataCallBack();
		TimeWatch_IncTimeCallBack();
		Distance_TimerCallback();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2){
		Listener_UartCallBack();
	}
}

int ap_main()
{
	HAL_TIM_Base_Start_IT(&htim2);
	while (1) {
		Listener_Excute();
		Controller_Excute();
		Presenter_Excute();
	}
	return 0;
}
void ap_init(void)
{
	Distance_Init();
	Listener_Init();
	Presenter_Init();
}
