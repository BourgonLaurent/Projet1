#define F_CPU 8000000UL

#include "interruptButton.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/io.hpp>

#include <tp4/components/interrupts.hpp>

void InterruptButton::initialize()
{
    interrupts::stopCatching();

    IO::setInput(&DDRD, PD2);

    setMode(Mode::ANY);
    start();

    interrupts::startCatching();
}

void InterruptButton::start()
{
    // External Interrupt Mask: External Interrupt 0 Enable (p.68)
    IO::setActive(&EIMSK, INT0);
}

void InterruptButton::stop()
{
    // External Interrupt Mask: External Interrupt 0 Enable (p.68)
    IO::clear(&EIMSK, INT0);
}

void InterruptButton::setMode(const Mode& mode)
{
    // Following Table 13-1 (p.68)
    switch (mode) {
        case Mode::ANY :
            IO::setActive(&EICRA, ISC00);
            IO::clear(&EICRA, ISC01);
            break;

        case Mode::FALLING :
            IO::clear(&EICRA, ISC00);
            IO::setActive(&EICRA, ISC01);
            break;

        case Mode::RISING :
            IO::setActive(&EICRA, ISC00);
            IO::setActive(&EICRA, ISC01);
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