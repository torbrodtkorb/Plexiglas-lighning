#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <avr/io.h>
#include "../Drivers/ws2812b.h"

#define NUMBER_OF_LEDS 15

extern rgb_color pixels[NUMBER_OF_LEDS];

void set_color(uint8_t r, uint8_t g, uint8_t b);

#endif