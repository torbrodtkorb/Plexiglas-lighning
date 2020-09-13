#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_PIN	2
#define BUTTON_PORT	PORTD
#define BUTTON_DDR	DDRD

typedef enum
{
	LONG_PRESS,
	SHORT_PRESS
} button_press_state_e;


void button_config(void);

button_press_state_e check_button_press(void);

#endif