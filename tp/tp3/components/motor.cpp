/**
 * Basic control a motor.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 26, 2023
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <tp2/components/io.hpp>
#include <util/delay.h>

#include "motor.hpp"

Motor::Motor(volatile uint8_t* dataDirectionRegister, volatile uint8_t* port,
             const uint8_t activationPin, const uint8_t directionPin)
    : port_(port), activationPin_(activationPin), directionPin_(directionPin)
{
    io::setOutput(dataDirectionRegister, activationPin);
    io::setOutput(dataDirectionRegister, directionPin);
}

void Motor::setDirection(const Direction &direction)
{
    switch (direction) {
        case Direction::FORWARD :
            io::clear(port_, directionPin_);
            break;

        case Direction::BACKWARD :
            io::setActive(port_, directionPin_);
            break;
    }
}

void Motor::turnOn()
{
    io::setActive(port_, activationPin_);
}

void Motor::turnOff()
{
    io::clear(port_, activationPin_);
}

void Motor::wait(const double &delay)
{
    if (delay == 0) {
        return;
    }

    for (uint16_t i = 0; i < delay / 30; i++) {
        _delay_us(10);
    }
}

void Motor::forward(const double &periodUs, const double &relativeSpeed)
{
    setDirection(Direction::FORWARD);
    turnOnAtSpeed(periodUs, relativeSpeed);
}

void Motor::backward(const double &periodUs, const double &relativeSpeed)
{
    setDirection(Direction::BACKWARD);
    turnOnAtSpeed(periodUs, relativeSpeed);
}

void Motor::turnOnAtSpeed(const double &periodUs, const double &relativeSpeed)
{
    turnOn();
    wait(periodUs * relativeSpeed);
    turnOff();
    wait(periodUs * (1.0 - relativeSpeed));
}