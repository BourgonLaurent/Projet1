/**
 * Colors of the LED.
 * \file color.cpp
 * \author Mehdi Benouhoud & Laurent Bourgon
 * \date January 17, 2023
 */

#include <avr/io.h>

enum class Color : uint8_t
{
    OFF = 0x00,
    GREEN = 0x01,
    RED = 0x02
};
