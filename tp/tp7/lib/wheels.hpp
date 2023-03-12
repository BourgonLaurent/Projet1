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
 * \date February 2, 2023
 *
 * USAGE:
 * Wheels::initialize(Side::RIGHT);
 * Wheels::setDirection(Direction::BACKWARD, Side::RIGHT);
 * Wheels::setSpeed(0.6, Side::RIGHT);
 * turnOff(Side::RIGHT)
 */

#ifndef Wheel_H
#define Wheel_H

#include <avr/io.h>

#include <lib/io.hpp>

class Wheels
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

    static void initialize(const Side &side = Side::BOTH);

    static void setDirection(const Direction &direction,
                             const Side &side = Side::BOTH);
    static void setSpeed(const uint8_t speed, const Side &side = Side::BOTH);
    static void turnOff(const Side &side = Side::BOTH);

private:
    static constexpr uint8_t TOP_VALUE = 0xFF; // p. 153

    static io::DataDirectionRegister dataDirectionRegister_;
    static io::Port port_;
    static io::PinPosition leftEnable_;
    static io::PinPosition leftDirection_;
    static io::PinPosition rightEnable_;
    static io::PinPosition rightDirection_;

    static void setDirectionOfPin(const Direction &direction,
                                  const io::PinPosition pin);
    static void configureOutputPins(const Side &side);
};

#endif
