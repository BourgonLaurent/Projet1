#ifndef PWMMOTOR_H
#define PWMMOTOR_H

#include <avr/io.h>

#include <tp4/components/timer.hpp>

class PwmMotor : public Timer
{
public:
    enum class Side
    {
        LEFT,
        RIGHT,
        BOTH
    };

    enum class Direction
    {
        FORWARD,
        BACKWARD
    };

    static void initialize(const Side &side);
    static void setDirection(const Side &side, const Direction &direction);

    static void setSpeed(const Side &side, const double speed);

private:
    static constexpr uint8_t TOP_VALUE = 0xFF; // p. 130

    static void setDirectionOfPin(const uint8_t pin,
                                  const Direction &direction);
};

#endif