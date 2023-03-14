/**
 * Control left and right wheels using hardware PWM.
 *
 * Hardware Identification
 *  WARNING: The Data Direction Register will be set automatically.
 *  TIMER: Timer 2.
 *  OUTPUT: H-bridge, connected left  to PD6 (enable) and PD4 (direction)
 *                    connected right to PD7 (enable) and PD5 (direction)
 *
 * USAGE:
 *  Wheels::initialize();
 *  Wheels::setDirection(Direction::BACKWARD, Side::RIGHT);
 *  Wheels::setSpeed(0.2, Side::LEFT);
 *  Wheels::setSpeed(0.6, Side::RIGHT);
 *  turnOff(Side::RIGHT)
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#include "wheels.hpp"

#include <lib1900/io.hpp>

io::DataDirectionRegister Wheels::dataDirectionRegister_ = &DDRD;
io::Port Wheels::port_ = &PORTD;
io::Position Wheels::leftEnable_ = PD6;
io::Position Wheels::leftDirection_ = PD4;
io::Position Wheels::rightEnable_ = PD7;
io::Position Wheels::rightDirection_ = PD5;

void Wheels::initialize(const Side &side)
{
    // (p.153) PWM, Phase Correct
    io::setActive(&TCCR2A, WGM20);
    io::clear(&TCCR2A, WGM21);
    io::clear(&TCCR2B, WGM22);

    // (p.154) Prescaler of 1024
    io::setActive(&TCCR2B, CS20);
    io::setActive(&TCCR2B, CS21);
    io::setActive(&TCCR2B, CS22);

    // (p.154) Force Output Compare A/B
    io::clear(&TCCR2B, FOC2B);
    io::clear(&TCCR2B, FOC2A);

    configureOutputPins(side);
    setDirection(Direction::FORWARD, side);
    setSpeed(0, side);
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

void Wheels::setSpeed(const uint8_t speed, const Side &side)
{
    switch (side) {
        case Side::LEFT :
            // (p.155) Output Compare Register 2 B
            OCR2B = (speed * TOP_VALUE) / 100;
            break;

        case Side::RIGHT :
            // (p.155) Output Compare Register 2 A
            OCR2A = (speed * TOP_VALUE) / 100;
            break;

        case Side::BOTH :
            setSpeed(speed, Side::LEFT);
            setSpeed(speed, Side::RIGHT);
    }
}

void Wheels::turnOff(const Side &side)
{
    setSpeed(0, side);
}

void Wheels::setDirectionOfPin(const Direction &direction,
                               const io::Position pin)
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
            // (p.153) Clear OC2B on Compare Match when upcounting.
            //         Set OC2B on Compare Match when downcounting.
            io::clear(&TCCR2A, COM2B0);
            io::setActive(&TCCR2A, COM2B1);

            io::setOutput(dataDirectionRegister_, leftEnable_);
            io::setOutput(dataDirectionRegister_, leftDirection_);
            break;

        case Side::RIGHT :
            // (p.153) Clear OC2A on Compare Match when upcounting.
            //         Set OC2A on Compare Match when downcounting.
            io::clear(&TCCR2A, COM2A0);
            io::setActive(&TCCR2A, COM2A1);

            io::setOutput(dataDirectionRegister_, rightEnable_);
            io::setOutput(dataDirectionRegister_, rightDirection_);
            break;

        case Side::BOTH :
            configureOutputPins(Side::LEFT);
            configureOutputPins(Side::RIGHT);
            break;
    }
}
