/**
 * Basic control a motor.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 26, 2023
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

class Motor
{
public:
    Motor(volatile uint8_t* dataDirectionRegister, volatile uint8_t* port,
          const uint8_t activationPin, const uint8_t directionPin);

    void forward(const double &periodUs, const double &speed);
    void backward(const double &periodUs, const double &speed);

private:
    volatile uint8_t* port_;

    const uint8_t activationPin_;
    const uint8_t directionPin_;

    enum class Direction
    {
        FORWARD,
        BACKWARD
    };

    void setDirection(const Direction &direction);

    void turnOn();
    void turnOff();
    void wait(const double &delay);
    void turnOnAtSpeed(const double &periodUs, const double &relativeSpeed);
};

#endif
