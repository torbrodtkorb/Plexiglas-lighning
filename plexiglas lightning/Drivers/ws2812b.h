#ifndef WS2812B_H
#define WS2812B_H

#include <avr/io.h>

typedef struct rgb_color
{
	unsigned char red, green, blue;
} rgb_color;

void __attribute__((noinline)) led_strip_write(rgb_color * colors, uint16_t count);


#endif