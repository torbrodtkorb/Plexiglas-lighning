#include "button.h"

void button_config(void)
{
	//set pin as input
	BUTTON_DDR &= ~(1 << BUTTON_PIN);
	
	//enable pull-up resistor
	BUTTON_PORT |= (1 << BUTTON_PIN);
	
	//enable interrupt
	//generate interrupt on logical change on INT1
	EICRA &= ~(1 << ISC01);
	EICRA |= (1 << ISC00);
	
	//enable interrupt on INT1
	EIMSK |= (1 << INT0);
	
	//enable global interrupts
	sei();
}

// logical i = true || k == true
// bitwise	i | k

button_press_state_e check_button_press(void)
{
	
}