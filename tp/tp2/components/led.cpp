/**
 * Control of an LED.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#include <avr/io.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/io.hpp>

#include "led.hpp"

LED::LED(
    volatile uint8_t *dataDirectionRegister,
    volatile uint8_t *port,
    const uint8_t plusBit,
    const uint8_t minusBit) : port_(port),
                              plusBit_(plusBit),
                              minusBit_(minusBit)
{
    IO::setActive(dataDirectionRegister, plusBit);
    IO::setActive(dataDirectionRegister, minusBit);
};

void LED::setColor(const Color &color)
{
    switch (color)
    {
    case Color::OFF:
        IO::setClear(port_, minusBit_);
        IO::setClear(port_, plusBit_);
        break;

    case Color::GREEN:
        IO::setActive(port_, minusBit_);
        IO::setClear(port_, plusBit_);
        break;

    case Color::RED:
        IO::setActive(port_, plusBit_);
        IO::setClear(port_, minusBit_);
        break;
    }
}
