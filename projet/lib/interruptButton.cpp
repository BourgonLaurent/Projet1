/**
 * Interrupt the main program with a push button.
 *
 * Hardware Identification:
 *  WARNING: The Data Direction Register (DDRD) will be set automatically.
 *  INPUT: Push button connected to D2.
 *
 * USAGE: Use `InterruptButton_vect` inside the ISR.
 *        For the debounce, call the appropriate functions
 *        at the start and end of the routine.
 *
 *    ISR(InterruptButton_vect)
 *    {
 *        InterruptButton::waitForDebounce();
 *        ...
 *        InterruptButton::clear();
 *    }
 *
 * Team #4546
 *  \author Catalina-Andrea Araya-Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#include "interruptButton.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <lib/interrupts.hpp>
#include <lib/io.hpp>

void InterruptButton::initialize(const Mode &mode)
{
    io::setInput(dataDirection_, position_);

    setMode(mode);
    start();
}

void InterruptButton::start()
{
    // (p.68) External Interrupt Mask: Interrupt 0
    io::setActive(&EIMSK, INT0);
}

void InterruptButton::stop()
{
    // (p.68) External Interrupt Mask: Interrupt 0
    io::clear(&EIMSK, INT0);
}

void InterruptButton::clear()
{
    // (p.68) External Interrupt Flag Register
    io::setActive(&EIFR, INTF0);
}

void InterruptButton::setMode(const Mode &mode)
{
    // (p.68) Following Table 13-1:
    //        Control External Interrupt Control Register A
    switch (mode) {
        case Mode::ANY :
            io::setActive(&EICRA, ISC00);
            io::clear(&EICRA, ISC01);
            break;

        case Mode::FALLING :
            io::clear(&EICRA, ISC00);
            io::setActive(&EICRA, ISC01);
            break;

        case Mode::RISING :
            io::setActive(&EICRA, ISC00);
            io::setActive(&EICRA, ISC01);
            break;
    }
}

void InterruptButton::waitForDebounce()
{
    _delay_ms(DEBOUNCE_DELAY_MS);
}

io::DataDirectionRegister InterruptButton::dataDirection_ = &DDRD;
io::Position InterruptButton::position_ = PD2;
