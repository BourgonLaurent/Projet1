/**
 * Control left and right wheels using hardware PWM.
 *
 * Hardware Identification
 * WARNING: The Data Direction Register will be set automatically.
 * TIMER: Timer 0.
 * OUTPUT: H-bridge, connected left  to PD6 (enable) and PD4 (direction)
 *                   connected right to PD7 (enable) and PD5 (direction)
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 14, 2023
 */

#define F_CPU 8000000UL

#include "wheels.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <lib/io.hpp>

void Wheels::setOutput(const Side &side)
{
    switch (side) {
        case Side::LEFT :
            // (p.152) Clear OC2B on Compare Match when upcounting.
            //         Set OC2B on Compare Match when downcounting.
            io::clear(&TCCR2A, COM2B0);
            io::setActive(&TCCR2A, COM2B1);

            io::setOutput(&DDRD, PD6); // OC2B
            io::setOutput(&DDRD, PD4); // Direction
            break;

        case Side::RIGHT :
            // (p.152) Clear OC2A on Compare Match when upcounting.
            //         Set OC2A on Compare Match when downcounting.
            io::clear(&TCCR2A, COM2A0);
            io::setActive(&TCCR2A, COM2A1);

            io::setOutput(&DDRD, PD7); // OC2A
            io::setOutput(&DDRD, PD5); // Direction
            break;

        case Side::BOTH :
            setOutput(Side::LEFT);
            setOutput(Side::RIGHT);
            break;
    }
}

void Wheels::initialize(const Side &side)
{
    // PWM PHASE CORRECT timer 2 p. 153
    io::setActive(&TCCR2A, WGM20);
    io::clear(&TCCR2A, WGM21);
    io::setActive(&TCCR2B, WGM22);

    // prescaler 1024 timer 0 p. 154
    io::setActive(&TCCR2B, CS20);
    io::clear(&TCCR2B, CS21);
    io::setActive(&TCCR2B, CS22);

    setOutput(side);
    // setDirection(Direction::FORWARD, side);
    setSpeed(0.0, side);

    // io::clear(&TCCR2B, FOC2B);
    // io::clear(&TCCR2B, FOC2A);
    // TCNT2 = 0;
}

void Wheels::setDirection(const Direction &direction, const Side &side)
{
    switch (side) {
        case Side::LEFT :
            setDirectionOfPin(direction, PD6);
            break;

        case Side::RIGHT :
            setDirectionOfPin(direction, PD7);
            break;
        case Side::BOTH :
            setDirection(direction, Side::LEFT);
            setDirection(direction, Side::RIGHT);
    }
}

void Wheels::setSpeed(const double speed, const Side &side)
{
    switch (side) {
        case Side::LEFT :
            // (p.152) Output Compare Register 1 B
            OCR2B = speed * TOP_VALUE;
            break;

        case Side::RIGHT :
            // (p.152) Output Compare Register 1 A
            OCR2A = speed * TOP_VALUE;
            break;

        case Side::BOTH :
            setSpeed(speed, Side::LEFT);
            setSpeed(speed, Side::RIGHT);
    }
}

void Wheels::setDirectionOfPin(const Direction &direction, const uint8_t pin)
{
    switch (direction) {
        case Direction::FORWARD :
            io::clear(&PORTD, pin);
            break;

        case Direction::BACKWARD :
            io::setActive(&PORTD, pin);
            break;
    }
}

void Wheels::turnOff(const Side &side)
{
    setSpeed(0.0, side);
}
