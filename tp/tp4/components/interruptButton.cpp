/**
 * Interrupt a program with a push button.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (DDRD) will be set automatically.
 * INPUT: Push button connected to D2.
 *
 * WARNING: InterruptButton::whenPressed() must be declared.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#define F_CPU 8000000UL

#include "interruptButton.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/io.hpp>

#include <tp4/components/interrupts.hpp>

void InterruptButton::initialize()
{
    io::setInput(&DDRD, PD2);

    setMode(Mode::ANY);
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

ISR(INT0_vect)
{
    InterruptButton::waitForDebounce();
    InterruptButton::whenPressed();

    interrupts::clear();
}