/**
 * Main program for the transmit module.
 *  Fetches the positions of poles in memory,
 *  calculates the best fitting polygon,
 *  and sends a SVG file via RS232.
 *
 * Hardware Identification:
 *  NOTE: The data direction registers are set automatically.
 *
 *  OUTPUT:
 *    - Bicolor LED.
 *
 *  EEPROM:
 *    - SCL (PC0)
 *    - SDA (PC1)
 *
 *  USART:
 *    - RXD0 (PD0)
 *    - TXD0 (PD1)
 *
 *  TIMERS:
 *    - Timer 1 | Flasher
 *
 * USAGE:
 *  Transmit::run(led, Transmit::Mode::NORMAL);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <lib/led.hpp>

class Transmit
{
public:
    enum class Mode
    {
        NORMAL,
        DEMO,
    };

    static void run(Led &led, const Mode &mode = Mode::NORMAL);

private:
    static constexpr uint16_t INITIALIZATION_DELAY_MS = 2000;
    static constexpr uint8_t FLASH_FREQUENCY_HZ = 10;
};

#endif
