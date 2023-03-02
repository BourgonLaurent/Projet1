/**
 * Implementation of the control of an LED.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (`dataDirectionRegister`)
 *     will be set automatically.
 * OUTPUT: Bicolor LED connected plus to `plusBit` and minus to `minusBit`.
 *
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#ifndef LED_H
#define LED_H

#include <lib/colors.hpp>
#include <lib/io.hpp>

class Led
{
public:
    Led(io::DataDirectionRegister dataDirectionRegister, io::Port port,
        const io::PinPosition plus, const io::PinPosition minus);

    void setColor(const Color &color);
    void setAmberForMs(const uint16_t durationMs);

private:
    io::Port port_;
    const io::PinPosition plus_;
    const io::PinPosition minus_;

    constexpr static uint16_t AMBER_DELAY_US = 500;
};

#endif
