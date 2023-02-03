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

    io::setInput(&DDRD, PD2);

    setMode(Mode::ANY);
    start();

    interrupts::startCatching();
}

void InterruptButton::start()
{
    // External Interrupt Mask: External Interrupt 0 Enable (p.68)
    io::setActive(&EIMSK, INT0);
}

void InterruptButton::stop()
{
    // External Interrupt Mask: External Interrupt 0 Enable (p.68)
    io::clear(&EIMSK, INT0);
}

void InterruptButton::setMode(const Mode& mode)
{
    // Following Table 13-1 (p.68)
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