/**
 * Control H-bridge using a PWM.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (DDRD) will be set automatically.
 * OUTPUT: Left motor on D5 (enable) and D7 (direction).
 * OUTPUT: Right motor on D4 (enable) D6 (direction).
 *
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#include "pwmMotor.hpp"

#include <avr/io.h>

#include <tp2/components/io.hpp>

void PwmMotor::initialize(const Side &side)
{
    switch (side) {
        case Side::LEFT :
            // (p.129) Clear OCnA/OCnB on Compare Match when upcounting.
            //         Set OCnA/OCnB on Compare Match when downcounting.
            io::clear(&TCCR1A, COM1B0);
            io::setActive(&TCCR1A, COM1B1);

            io::setOutput(&DDRD, DDD4);
            io::setOutput(&DDRD, DDD6);
            break;

        case Side::RIGHT :
            // (p.129) Clear OCnA/OCnB on Compare Match when upcounting.
            //         Set OCnA/OCnB on Compare Match when downcounting.
            io::clear(&TCCR1A, COM1A0);
            io::setActive(&TCCR1A, COM1A1);

            io::setOutput(&DDRD, DDD5);
            io::setOutput(&DDRD, DDD7);
            break;

        case Side::BOTH :
            initialize(Side::LEFT);
            initialize(Side::RIGHT);
            break;
    }

    TCCR1C = 0;

    setDirection(side, Direction::FORWARD);
    setSpeed(side, 0.0);
}

void PwmMotor::setDirection(const Side &side, const Direction &direction)
{
    switch (side) {
        case Side::LEFT :
            setDirectionOfPin(DDD6, direction);
            break;

        case Side::RIGHT :
            setDirectionOfPin(DDD7, direction);
            break;

        case Side::BOTH :
            setDirection(Side::LEFT, direction);
            setDirection(Side::RIGHT, direction);
            break;
    }
}

void PwmMotor::setSpeed(const Side &side, const double speed)
{
    switch (side) {
        case Side::LEFT :
            // (p.132) Output Compare Register 1 B
            OCR1B = speed * TOP_VALUE;
            break;

        case Side::RIGHT :
            // (p.132) Output Compare Register 1 A
            OCR1A = speed * TOP_VALUE;
            break;

        case Side::BOTH :
            setSpeed(Side::LEFT, speed);
            setSpeed(Side::RIGHT, speed);
            break;
    }
}

void PwmMotor::setDirectionOfPin(const uint8_t &pin, const Direction &direction)
{
    switch (direction) {
        case Direction::FORWARD :
            io::clear(&DDRD, pin);
            break;

        case Direction::BACKWARD :
            io::setActive(&DDRD, pin);
            break;
    }
}