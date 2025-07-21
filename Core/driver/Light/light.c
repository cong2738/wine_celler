/*
 * light->c
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */
#include "light.h"

void Light_init(Led_TypeDef* LEDx) {
	HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->pinNum, RESET);
}

void Light_ctrl(Led_TypeDef* LEDx, FlagStatus on)
{
	if(!on) {
		HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->pinNum, RESET);
		return;
	}
	HAL_GPIO_WritePin(LEDx->GPIOx, LEDx->pinNum, SET);
}
