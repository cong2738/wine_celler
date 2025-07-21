/*
 * light.h
 *
 *  Created on: Jun 27, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_LIGHT_LIGHT_H_
#define DRIVER_LIGHT_LIGHT_H_

#include "stm32f4xx_hal.h"

typedef struct {
	GPIO_TypeDef *GPIOx;
	uint32_t pinNum;
}Led_TypeDef;

void Light_init(Led_TypeDef* LEDx);
void Light_ctrl(Led_TypeDef* LEDx, FlagStatus on);

#endif /* DRIVER_LIGHT_LIGHT_H_ */
