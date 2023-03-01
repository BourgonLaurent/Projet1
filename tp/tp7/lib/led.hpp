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

#include <avr/io.h>

#include <lib/colors.hpp>
#include <lib/io.hpp>

class LED
{
public:
    LED(io::DataDirectionRegister dataDirectionRegister, io::Port port,
        const io::PinPosition plus, const io::PinPosition minus);

    void setColor(const Color &color);

private:
    io::Port port_;
    const io::PinPosition plus_;
    const io::PinPosition minus_;
};

#endif
