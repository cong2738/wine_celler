#include "timeWatch.h"

void TimeWatchDotBlink();


uint32_t timeWatchDotData = 0b0000;

timeWatch_t timeWatch = {0,0,0,12}; //all 0

void TimeWatch_IncTimeCallBack()
{
	if(timeWatch.msec < 1000 - 1){
		timeWatch.msec++;
		return;
	}
	timeWatch.msec = 0;

	if(timeWatch.sec < 60 - 1){
		timeWatch.sec++;
		return;
	}
	timeWatch.sec = 0;

	if(timeWatch.min < 60 - 1){
		timeWatch.min++;
		return;
	}
	timeWatch.min = 0;

	if(timeWatch.hour < 24 - 1){
		timeWatch.hour++;
		return;
	}
	timeWatch.hour = 0;
}

void TimeWatchDotBlink(){
	timeWatchDotData = 0b0000;
	if(timeWatch.sec%2 < 1) timeWatchDotData |= (1U << 2);
}

timeWatch_t get_watch() {
	return timeWatch;
}

int get_watchDotData() {
	return timeWatchDotData;
}
