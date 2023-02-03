/**
 * Control of an LED.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (`dataDirectionRegister`)
 *     will be set automatically.
 * OUTPUT: Bicolor LED connected plus to `plusBit` and minus to `minusBit`.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#include <avr/io.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/io.hpp>

#include "led.hpp"

LED::LED(volatile uint8_t* dataDirectionRegister, volatile uint8_t* port,
         const uint8_t plusBit, const uint8_t minusBit)
    : port_(port), plusBit_(plusBit), minusBit_(minusBit)
{
    io::setOutput(dataDirectionRegister, plusBit);
    io::setOutput(dataDirectionRegister, minusBit);
};

void LED::setColor(const Color& color)
{
    switch (color) {
        case Color::OFF :
            io::clear(port_, minusBit_);
            io::clear(port_, plusBit_);
            break;

        case Color::GREEN :
            io::setActive(port_, minusBit_);
            io::clear(port_, plusBit_);
            break;

        case Color::RED :
            io::setActive(port_, plusBit_);
            io::clear(port_, minusBit_);
            break;
    }
}
