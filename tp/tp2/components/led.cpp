/**
 * Control of an LED.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#include <avr/io.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/bit.hpp>

#include "led.hpp"

LED::LED(
    volatile uint8_t &dataDirectionRegister,
    volatile uint8_t &port,
    const uint8_t plusBit,
    const uint8_t minusBit) : port(port),
                              plusBit(plusBit),
                              minusBit(minusBit)
{
    Bit::activate(dataDirectionRegister, plusBit);
    Bit::activate(dataDirectionRegister, minusBit);
};

void LED::setColor(const Color &color)
{
    switch (color)
    {
    case Color::OFF:
        Bit::clear(port, minusBit);
        Bit::clear(port, plusBit);
        break;

    case Color::GREEN:
        Bit::activate(port, minusBit);
        Bit::clear(port, plusBit);
        break;

    case Color::RED:
        Bit::activate(port, plusBit);
        Bit::clear(port, minusBit);
        break;
    }
}
