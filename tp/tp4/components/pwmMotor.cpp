#include "pwmMotor.hpp"

#include <avr/io.h>

#include <tp2/components/io.hpp>

void PwmMotor::initialize(const Side &side)
{
    switch (side) {
        case Side::LEFT :
            io::setActive(&TCCR1A, COM1A1);

            io::setOutput(&OC1A_DDR, OC1A_BIT);
            io::setOutput(&DDRD, DDD7);
            break;

        case Side::RIGHT :
            io::setActive(&TCCR1A, COM1B1);

            io::setOutput(&OC1B_DDR, OC1B_BIT);
            io::setOutput(&DDRD, DDD6);
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
            setDirectionOfPin(DDD7, direction);
            break;

        case Side::RIGHT :
            setDirectionOfPin(DDD6, direction);
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
            OCR1A = speed * TOP_VALUE;
            break;

        case Side::RIGHT :
            OCR1B = speed * TOP_VALUE;
            break;

        case Side::BOTH :
            setSpeed(Side::LEFT, speed);
            setSpeed(Side::RIGHT, speed);
            break;
    }
}

void PwmMotor::setDirectionOfPin(const uint8_t pin, const Direction &direction)
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