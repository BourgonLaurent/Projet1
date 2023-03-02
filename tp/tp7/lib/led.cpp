/**
 * Control of an LED.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (`dataDirectionRegister`)
 *     will be set automatically.
 * OUTPUT: Bicolor LED connected plus to `plusBit` and minus to `minusBit`.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#include "led.hpp"

#include <util/delay.h>

#include <lib/colors.hpp>
#include <lib/io.hpp>

Led::Led(io::DataDirectionRegister dataDirectionRegister, io::Port port,
         const io::PinPosition plus, const io::PinPosition minus)
    : port_(port), plus_(plus), minus_(minus)
{
    io::setOutput(dataDirectionRegister, plus_);
    io::setOutput(dataDirectionRegister, minus_);
};

void Led::setColor(const Color &color)
{
    switch (color) {
        case Color::OFF :
            io::clear(port_, minus_);
            io::clear(port_, plus_);
            break;

        case Color::GREEN :
            io::setActive(port_, minus_);
            io::clear(port_, plus_);
            break;

        case Color::RED :
            io::clear(port_, minus_);
            io::setActive(port_, plus_);
            break;
    }
}

void Led::setAmberForMs(const uint16_t durationMs)
{
    for (uint16_t i = 0; i < durationMs; i++) {
        setColor(Color::GREEN);
        _delay_us(AMBER_DELAY_US);
        setColor(Color::RED);
        _delay_us(AMBER_DELAY_US);
    }
    setColor(Color::OFF);
}
