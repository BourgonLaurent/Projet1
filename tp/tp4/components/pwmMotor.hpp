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

    static void setDirectionOfPin(const uint8_t &pin,
                                  const Direction &direction);
};

#endif