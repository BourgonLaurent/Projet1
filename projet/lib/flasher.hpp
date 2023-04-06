/**
 * Flash a LED at a given frequency.
 *
 * LIMITATIONS:
 *  Since Flasher modifies the configuration
 *  of InterruptTimer, they cannot be used at
 *  the same time.
 *
 * Hardware Identification
 *  TIMER: Uses InterruptTimer (Timer 1).
 *
 * USAGE: Use `Flasher_vect` (or `InterruptTimer_vect`) for the ISR.
 *    ISR(Flasher_vect)
 *    {
 *        Flasher::handleFlash();
 *        ...
 *    }
 *
 *   Led led(&PORTB, &DDRB, PB0, PB1);
 *
 *   // Flash the LED on and off at 2Hz.
 *   Flasher::initialize(led, 2, Led::Color::RED, Led::Color::OFF);
 *   Flasher::startFlashing();
 *   Flasher::stopFlashing();
 *
 *   // Show the LED amber.
 *   Flasher::initializeAmber(led);
 *   Flasher::startFlashing();
 *   Flasher::stopFlashing();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date April 5, 2023
 */

#ifndef FLASHER_H
#define FLASHER_H

#include <lib/interruptTimer.hpp>
#include <lib/io.hpp>
#include <lib/led.hpp>

#define Flasher_vect InterruptTimer_vect

class Flasher
{
public:
    static void initialize(Led &led, const uint16_t frequencyHz,
                           const Led::Color &first, const Led::Color &second);

    static void initializeAmber(Led &led);

    static void startFlashing();
    static void stopFlashing();

    static void handleFlash();

private:
    static constexpr uint8_t AMBER_FREQUENCY_HZ = 15;

    static Led* led_;
    static Led::Color first_;
    static Led::Color second_;
    static bool isActive_;
};

#endif
