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
    volatile uint8_t *dataDirectionRegister,
    volatile uint8_t *port,
    const uint8_t plusBit,
    const uint8_t minusBit) : port_(port),
                              plusBit_(plusBit),
                              minusBit_(minusBit)
{
    Bit::setActive(dataDirectionRegister, plusBit);
    Bit::setActive(dataDirectionRegister, minusBit);
};

void LED::setColor(const Color &color)
{
    switch (color)
    {
    case Color::OFF:
        Bit::setClear(port_, minusBit_);
        Bit::setClear(port_, plusBit_);
        break;

    case Color::GREEN:
        Bit::setActive(port_, minusBit_);
        Bit::setClear(port_, plusBit_);
        break;

    case Color::RED:
        Bit::setActive(port_, plusBit_);
        Bit::setClear(port_, minusBit_);
        break;
    }
}
