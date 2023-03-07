/**
 * Control left and right wheels using hardware PWM.
 *
 * Hardware Identification
 * WARNING: The Data Direction Register will be set automatically.
 * TIMER: Timer 0.
 * OUTPUT: H-bridge, connected left  to PB4 (enable) and PB5 (direction)
 *                   connected right to PB3 (enable) and PB2 (direction)
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#define F_CPU 8000000UL

#include "wheels.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <lib/io.hpp>

io::DataDirectionRegister Wheels::dataDirectionRegister_ = &DDRB;
io::Port Wheels::port_ = &PORTB;
io::PinPosition Wheels::leftEnable_ = PB4;
io::PinPosition Wheels::leftDirection_ = PB5;
io::PinPosition Wheels::rightEnable_ = PB3;
io::PinPosition Wheels::rightDirection_ = PB2;

void Wheels::initialize(const Side &side)
{
    // (p.103) PWM, Phase Correct
    io::setActive(&TCCR0A, WGM00);
    io::clear(&TCCR0A, WGM01);
    io::clear(&TCCR0B, WGM02);

    // (p.105) Prescaler of 1024
    io::setActive(&TCCR0B, CS00);
    io::clear(&TCCR0B, CS01);
    io::setActive(&TCCR0B, CS02);

    // (p.104) Force Output Compare A/B
    io::clear(&TCCR0B, FOC0B);
    io::clear(&TCCR0B, FOC0A);

    configureOutputPins(side);
    setDirection(Direction::FORWARD, side);
    setSpeed(0.0, side);
}

void Wheels::setDirection(const Direction &direction, const Side &side)
{
    switch (side) {
        case Side::LEFT :
            setDirectionOfPin(direction, leftDirection_);
            break;

        case Side::RIGHT :
            setDirectionOfPin(direction, rightDirection_);
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
            // (p.132) Output Compare Register 1 B
            OCR0B = speed * TOP_VALUE;
            break;

        case Side::RIGHT :
            // (p.132) Output Compare Register 1 A
            OCR0A = speed * TOP_VALUE;
            break;

        case Side::BOTH :
            setSpeed(speed, Side::LEFT);
            setSpeed(speed, Side::RIGHT);
    }
}

void Wheels::turnOff(const Side &side)
{
    setSpeed(0.0, side);
}

void Wheels::setDirectionOfPin(const Direction &direction,
                               const io::PinPosition pin)
{
    switch (direction) {
        case Direction::FORWARD :
            io::clear(port_, pin);
            break;

        case Direction::BACKWARD :
            io::setActive(port_, pin);
            break;
    }
}

void Wheels::configureOutputPins(const Side &side)
{
    switch (side) {
        case Side::LEFT :
            // (p.103) Clear OC0B on Compare Match when upcounting.
            //         Set OC0B on Compare Match when downcounting.
            io::clear(&TCCR0A, COM0B0);
            io::setActive(&TCCR0A, COM0B1);

            io::setOutput(&DDRB, leftEnable_);
            io::setOutput(&DDRB, leftDirection_);
            break;

        case Side::RIGHT :
            // (p.103) Clear OC0A on Compare Match when upcounting.
            //         Set OC0A on Compare Match when downcounting.
            io::clear(&TCCR0A, COM0A0);
            io::setActive(&TCCR0A, COM0A1);

            io::setOutput(&DDRB, rightEnable_);
            io::setOutput(&DDRB, rightDirection_);
            break;

        case Side::BOTH :
            configureOutputPins(Side::LEFT);
            configureOutputPins(Side::RIGHT);
            break;
    }
}
