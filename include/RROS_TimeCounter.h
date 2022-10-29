#ifndef RROS_TIMECOUNTER_H
#define RROS_TIMECOUNTER_H
#include <stdint.h>
uint32_t RROS_getCurrentTime(void);
void RROS_timeCounterCallback(void);
void RROS_TimeCounterInit(void);
#endif /*RROS_TIMECOUNTER*/