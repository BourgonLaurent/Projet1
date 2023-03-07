/**
 * Implementation of the control of a bicolor LED.
 *
 * Hardware Identification:
 * WARNING: The Data Direction Register will be set automatically.
 * OUTPUT: Bicolor LED connected plus to `plus` and minus to `minus`.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date January 19, 2023
 */

#ifndef LED_H
#define LED_H

#include <lib/io.hpp>

class Led
{
public:
    Led(io::DataDirectionRegister dataDirectionRegister, io::Port port,
        const io::PinPosition plus, const io::PinPosition minus);

    enum class Color
    {
        OFF,
        GREEN,
        RED
    };

    void setColor(const Color &color);
    void setAmberForMs(const uint16_t durationMs);

private:
    constexpr static uint16_t AMBER_DELAY_US = 500;

    io::Port port_;
    const io::PinPosition plus_;
    const io::PinPosition minus_;
};

#endif
