#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void timer_config(void);

void timer_start(void);

void timer_stop(void);

#endif