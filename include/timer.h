#ifndef __TIMER_H_DEFINED
#define __TIMER_H_DEFINED


#include <interrupt.h>

// init timer
void timer_init();

// get number of timer ticks
unsigned int timer_get_time();

#endif