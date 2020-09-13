#include "timer.h"

void timer_config(void)
{
	OCR1A = 5000;
	TIMSK1 |= (1 << OCIE1A);
}

void timer_start(void)
{
	TCNT1 = 0;
	
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << CS10);
	TCCR1B &= ~(1 << CS11);
}

void timer_stop(void)
{
	//clear clock select bits
	TCCR1B &= ~(0b111 << 0);
}