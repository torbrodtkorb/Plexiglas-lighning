#include "animations.h"

rgb_color pixels[NUMBER_OF_LEDS];

void set_color(uint8_t r, uint8_t g, uint8_t b)
{
	for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
	{
		pixels[i] = (rgb_color){ r, g, b };
	}

	led_strip_write(pixels, NUMBER_OF_LEDS);
}