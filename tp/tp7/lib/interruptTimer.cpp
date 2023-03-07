/**
 * Interrupt a program with a timer.
 *
 * WARNING: InterruptTimer::whenFinished() must be declared.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 *
 * Hardware Identification
 * TIMER: Timer 1.
 */

#include "interruptTimer.hpp"

#include <lib/interrupts.hpp>
#include <lib/io.hpp>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

ISR(TIMER1_COMPA_vect)
{
    InterruptTimer::whenFinished();
}

void InterruptTimer::initialize(const double delayS, const Mode &mode)
{
    // Force Output Compare for A (p.131)
    io::clear(&TCCR1C, FOC1A);

    setSeconds(delayS);
    setMode(mode);

    stop();
}

void InterruptTimer::reset()
{
    TCNT1 = 0;
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

void InterruptTimer::setSeconds(const double delayS)
{
    setBestPrescaleMode(delayS);
    OCR1A = delayS * getCyclesPerSeconds();
}

void InterruptTimer::setBestPrescaleMode(const double delayS)
{
    const uint16_t idealPrescale = (delayS * F_CPU) / UINT16_MAX;
    const PrescaleMode bestPrescaleMode = getCeiledPrescaleMode(idealPrescale);
    setPrescaleMode(bestPrescaleMode);
}

InterruptTimer::PrescaleMode
InterruptTimer::getCeiledPrescaleMode(const uint16_t idealPrescale)
{
    if (idealPrescale <= (uint16_t)PrescaleMode::OFF) {
        return PrescaleMode::OFF;
    }
    if (idealPrescale <= (uint16_t)PrescaleMode::CLK) {
        return PrescaleMode::CLK;
    }
    if (idealPrescale <= (uint16_t)PrescaleMode::CLK8) {
        return PrescaleMode::CLK8;
    }
    if (idealPrescale <= (uint16_t)PrescaleMode::CLK64) {
        return PrescaleMode::CLK64;
    }
    if (idealPrescale <= (uint16_t)PrescaleMode::CLK256) {
        return PrescaleMode::CLK256;
    }
    if (idealPrescale <= (uint16_t)PrescaleMode::CLK1024) {
        return PrescaleMode::CLK1024;
    }

    return PrescaleMode::OFF;
}

uint16_t InterruptTimer::getCyclesPerSeconds()
{
    PrescaleMode prescaleMode = getPrescaleMode();

    // Prevent dividing by 0
    if (prescaleMode == PrescaleMode::OFF) {
        return 0;
    }

    return F_CPU / static_cast<uint16_t>(prescaleMode);
}

void InterruptTimer::setMode(const Mode &mode)
{
    // Following Table 16-5 (p.130)
    switch (mode) {
        case Mode::NORMAL :
            io::clear(&TCCR1A, WGM10);
            io::clear(&TCCR1A, WGM11);
            io::clear(&TCCR1B, WGM12);
            io::clear(&TCCR1B, WGM13);
            break;

        case Mode::CLEAR_ON_COMPARE :
            io::clear(&TCCR1A, WGM10);
            io::clear(&TCCR1A, WGM11);
            io::setActive(&TCCR1B, WGM12);
            io::clear(&TCCR1B, WGM13);
            break;
    }
}

InterruptTimer::PrescaleMode InterruptTimer::getPrescaleMode()
{
    // Following Table 16-6 (p.131)
    switch (TCCR1B & (_BV(CS12) | _BV(CS11) | _BV(CS10))) {
        case _BV(CS10) :
            return PrescaleMode::CLK;

        case _BV(CS11) :
            return PrescaleMode::CLK8;

        case _BV(CS11) | _BV(CS10) :
            return PrescaleMode::CLK64;

        case _BV(CS12) :
            return PrescaleMode::CLK256;

        case _BV(CS12) | _BV(CS10) :
            return PrescaleMode::CLK1024;

        default :
            return PrescaleMode::OFF;
    }
}

void InterruptTimer::setPrescaleMode(const PrescaleMode &prescaleMode)
{
    // Following Table 16-6 (p.131)
    switch (prescaleMode) {
        case PrescaleMode::OFF :
            io::clear(&TCCR1B, CS12);
            io::clear(&TCCR1B, CS11);
            io::clear(&TCCR1B, CS10);
            break;

        case PrescaleMode::CLK :
            io::clear(&TCCR1B, CS12);
            io::clear(&TCCR1B, CS11);
            io::setActive(&TCCR1B, CS10);
            break;

        case PrescaleMode::CLK8 :
            io::clear(&TCCR1B, CS12);
            io::setActive(&TCCR1B, CS11);
            io::clear(&TCCR1B, CS10);
            break;

        case PrescaleMode::CLK64 :
            io::clear(&TCCR1B, CS12);
            io::setActive(&TCCR1B, CS11);
            io::setActive(&TCCR1B, CS10);
            break;

        case PrescaleMode::CLK256 :
            io::setActive(&TCCR1B, CS12);
            io::clear(&TCCR1B, CS11);
            io::clear(&TCCR1B, CS10);
            break;

        case PrescaleMode::CLK1024 :
            io::setActive(&TCCR1B, CS12);
            io::clear(&TCCR1B, CS11);
            io::setActive(&TCCR1B, CS10);
            break;
    }
}
