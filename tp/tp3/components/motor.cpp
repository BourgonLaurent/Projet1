/**
 * TODO Describe file
 *
 * Hardware Identification:
 * TODO describe hardware identification
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 26, 2023
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <tp2/components/io.hpp>

#include "motor.hpp"

Motor::Motor(
    volatile uint8_t *dataDirectionRegister,
    volatile uint8_t *port,

    const uint8_t pulseWidthModulationPin,
    const uint8_t directionPin) : port_(port),
                                  pulseWidthModulationPin_(pulseWidthModulationPin),
                                  directionPin_(directionPin)
{
    IO::setOutput(dataDirectionRegister, pulseWidthModulationPin);
    IO::setOutput(dataDirectionRegister, directionPin);
}

void Motor::setDirection(const Direction &direction)
{
    switch (direction)
    {
    case Direction::FORWARD:
        IO::clear(port_, directionPin_);
        break;

    case Direction::BACKWARD:
        IO::setActive(port_, directionPin_);
        break;
    }
}

void Motor::turnOn()
{
    IO::setActive(port_, pulseWidthModulationPin_);
}

void Motor::turnOff()
{
    IO::clear(port_, pulseWidthModulationPin_);
}

void Motor::wait(const double &delay)
{
    if (delay == 0)
    {
        return;
    }

    for (uint16_t i = 0; i < delay / 30; i++)
    {
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