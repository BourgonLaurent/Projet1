/**
 * Tests lib1900.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 *
 * Hardware Identification
 * INPUT: .
 * OUTPUT: .
 */

#include <avr/io.h>
#include <util/delay.h>

#include <lib/communication.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/led.hpp>

volatile bool isGreen = false;

void InterruptTimer::whenFinished()
{
    ::isGreen = !::isGreen;
    Communication::send("Status: ");
    Communication::send(::isGreen);
    Communication::send("\n");
}

int main()
{
    Led led(&DDRB, &PORTB, PB0, PB1);

    Communication::initialize();

    InterruptTimer::initialize(1, InterruptTimer::Mode::CLEAR_ON_COMPARE);
    InterruptTimer::start();

    interrupts::startCatching();

    while (true) {
        led.setColor(::isGreen ? Led::Color::GREEN : Led::Color::RED);
    }

    return 0;
}
