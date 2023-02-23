/**
 * Interrupt a program with a timer.
 *
 * WARNING: InterruptTimer::whenFinished() must be declared.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#include "interruptTimer.hpp"

#include <tp6/components/interrupts.hpp>
#include <tp6/components/io.hpp>

void InterruptTimer::initialize()
{
    // Force Output Compare for A (p.131)
    io::clear(&TCCR1C, FOC1A);

    setMode(Mode::NORMAL);
    setPrescaleMode(PrescaleMode::CLK);
    setSeconds(0);

    stop();
}

void InterruptTimer::setSeconds(const double delayS)
{
    OCR1A = delayS * getCyclesPerSeconds();
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

uint16_t InterruptTimer::getCyclesPerSeconds()
{
    return F_CPU / getPrescaleValue();
}
