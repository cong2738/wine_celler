/*
 * TimeWatch.h
 *
 *  Created on: Jun 23, 2025
 *      Author: kccistc
 */

#ifndef AP_TIMEWATCH_H_
#define AP_TIMEWATCH_H_

#include "FND.h"

typedef struct{
	uint16_t msec;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
}timeWatch_t;

void TimeWatch_IncTimeCallBack();
timeWatch_t get_watch();
int get_watchDotData();

#endif /* AP_TIMEWATCH_H_ */
