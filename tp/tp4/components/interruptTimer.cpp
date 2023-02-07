/**
 * Interrupt a program with a timer.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#include "interruptTimer.hpp"

#include <tp2/components/io.hpp>

#include <tp4/components/interrupts.hpp>
// #include <tp4/components/timer.hpp>

void InterruptTimer::initialize()
{
    // Force Output Compare for A (p.131)
    io::clear(&TCCR1C, FOC1A);

    setMode(Mode::NORMAL);
    setPrescaleMode(PrescaleMode::CLK);
    setSeconds(0);

    stop();
}

void InterruptTimer::setSeconds(uint8_t delayS)
{
    OCR1A = delayS * CYCLES_PER_SECOND;
}

void InterruptTimer::start()
{
    reset();

    // Output Compare Enable Interrupt A (p.134)
    io::setActive(&TIMSK1, OCIE1A);
}

void InterruptTimer::stop()
{
    // Output Compare Enable Interrupt A (p.134)
    io::clear(&TIMSK1, OCIE1A);
}

void InterruptTimer::reset()
{
    TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect)
{
    InterruptTimer::whenFinished();

    interrupts::clear();
}
