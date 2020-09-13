#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Application/animations.h"
#include "Drivers/button.h"
#include "Drivers/timer.h"

volatile uint8_t short_press = 0;
volatile uint8_t long_press = 0;
volatile uint8_t long_press_signal = 0;

uint8_t power = 0;

uint8_t program = 0;

void lamp_on(uint8_t r, uint8_t g, uint8_t b) {
	uint8_t start_number = 0;
	for (uint8_t i = start_number; i < start_number + NUMBER_OF_LEDS; i++) {
		pixels[i] = (rgb_color){r, g, b};
	}
}

void layer_on(uint8_t layer, uint8_t r, uint8_t g, uint8_t b) {
	uint8_t start_number = (layer - 1) * 9;
	for (uint8_t i = start_number; i < start_number + 9; i++) {
		pixels[i] = (rgb_color){r, g, b};
	}
}

void layer_off(uint8_t layer) {
	uint8_t start_number = (layer - 1) * 9;
	for (uint8_t i = start_number; i < start_number + 9; i++) {
		pixels[i] = (rgb_color){0, 0, 0};
	}
}

void initialize_led(void) {
	led_strip_write(pixels, NUMBER_OF_LEDS);
}

void show(void) {
	led_strip_write(pixels, NUMBER_OF_LEDS);
	
}

float hue2rgb(float p, float q, float t) {
	if(t < 0) t += 1;
	if(t > 1) t -= 1;
	if(t < 1/6.0) return p + (q - p) * 6 * t;
	if(t < 1/2.0) return q;
	if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
	return p;
}

void hslToRgb(float h, float s, float l, char rgb[]) {
	float r, g, b;

	if (s == 0) {
		r = g = b = l; // achromatic
		} else {
		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = hue2rgb(p, q, h + 1/3.0);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1/3.0);
	}

	rgb[0] = r * 255;
	rgb[1] = g * 255;
	rgb[2] = b * 255;
}


void rainbow(){
	char color1 [3];
	char color2 [3];
	char color3 [3];
	char color4 [3];
	char color5 [3];
	char color6 [3];
	char color7 [3];
	
	float hue = 0;
	while (1) {
		hue = hue+0.01f;
		hue -= (int)hue;
		
		hslToRgb(hue, 1, 0.2f, color1);
		hslToRgb(hue + 0.1429, 1, 0.2f, color2);
		hslToRgb(hue + 0.2857, 1, 0.2f, color3);
		hslToRgb(hue + 0.4286, 1, 0.2f, color4);
		hslToRgb(hue + 0.5714, 1, 0.2f, color5);
		hslToRgb(hue + 0.4173, 1, 0.2f, color6);
		hslToRgb(hue + 0.8571, 1, 0.2f, color7);
		
		layer_on(1,color1[0], color1[1], color1[2]);
		layer_on(2,color2[0], color2[1], color2[2]);
		layer_on(3,color3[0], color3[1], color3[2]);
		layer_on(4,color4[0], color4[1], color4[2]);
		layer_on(5,color5[0], color5[1], color5[2]);
		layer_on(6,color6[0], color6[1], color6[2]);
		layer_on(7,color7[0], color7[1], color7[2]);
		show();
		_delay_ms(40);
		
		if (short_press)
		{
			return;
		}
		if (long_press)
		{
			return;
		}
	}
}
int main(void)
{
	button_config();
	timer_config();
	set_color(0, 0, 0);
		
	
    while (1) 
    {
		if (short_press)
		{
			short_press = 0;
			if (power == 1)
			{
				program++;
				if (program == 7)
				{
					program = 1;
				}
			}
		}
		else if (long_press)
		{
			long_press = 0;
			if (power == 0)
			{
				power = 1;
			}
			else
			{
				power = 0;
				program = 0;
				set_color(0, 0, 0);
			}
		}
		
		if (power == 1)
		{
			switch (program)
			{
				case 0:
					set_color(1,1,1);
					break;
				case 1:
					set_color(200, 50, 180);
					break;
				case 2:
					set_color(0, 255,255);
					break;
				case 3:
					set_color(255, 0, 0);
					break;
				case 4:
					set_color(0, 255, 0);
					break;
				case 5:
					set_color(0, 0, 255);
					break;
				case 6:
					rainbow();
					break;
			}
		}
		
    }
}

ISR (INT0_vect)
{
	if (!(PIND & (1 << 2)))
	{
		//you have pushed the button
		timer_start();
	}
	else if (PIND & (1 << 2))
	{
		if (long_press_signal == 1)
		{
			long_press = 1;
			long_press_signal = 0;
		}
		else
		{
			short_press = 1;
			timer_stop();
		}
	}

}

ISR (TIMER1_COMPA_vect)
{
	if (!(PIND & (1 << 2)))
	{
		long_press_signal = 1;
	}
	timer_stop();
}