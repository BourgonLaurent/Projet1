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
#include <lib/wheels.hpp>

volatile bool isGreen = false;

ISR(InterruptTimer_vect)
{
    ::isGreen = !::isGreen;
}

int main()
{
    Led led(&DDRB, &PORTB, PB0, PB1);

    Communication::initialize();

    InterruptTimer::initialize(InterruptTimer::Mode::CLEAR_ON_COMPARE, 1);
    InterruptTimer::start();

    interrupts::startCatching();

    Wheels::initialize();

    while (true) {
        led.setColor(::isGreen ? Led::Color::GREEN : Led::Color::RED);

        Wheels::setDirection(::isGreen ? Wheels::Direction::FORWARD
                                       : Wheels::Direction::BACKWARD);

        for (double i = 0; i <= 1; i += 0.25) {
            Wheels::setSpeed(i, Wheels::Side::LEFT);
            Wheels::setSpeed(1 - i, Wheels::Side::RIGHT);
            Communication::send(i * 100);
            _delay_ms(250);
        }

        Wheels::turnOff();
    }
    return 0;
}
