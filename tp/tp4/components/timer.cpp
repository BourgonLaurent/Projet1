/**
 * Control 16-bit Timer 1.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#include "timer.hpp"

#include <tp2/components/io.hpp>

void Timer::setMode(const Mode &mode)
{
    // Following Table 16-5 (p.130)
    switch (mode) {
        case Mode::NORMAL :
            io::clear(&TCCR1A, WGM10);
            io::clear(&TCCR1A, WGM11);
            io::clear(&TCCR1B, WGM12);
            io::clear(&TCCR1B, WGM13);
            break;

        case Mode::CTC :
            io::clear(&TCCR1A, WGM10);
            io::clear(&TCCR1A, WGM11);
            io::setActive(&TCCR1B, WGM12);
            io::clear(&TCCR1B, WGM13);
            break;

        case Mode::PWM_PHASE_CORRECT :
            io::setActive(&TCCR1A, WGM10);
            io::clear(&TCCR1A, WGM11);
            io::clear(&TCCR1B, WGM12);
            io::clear(&TCCR1B, WGM13);
    }
}

void Timer::setPrescaleMode(const PrescaleMode &prescaleMode)
{
    // Following Table 16-6 (p.131)
    switch (prescaleMode) {
        case PrescaleMode::CLK :
            io::setActive(&TCCR1B, CS10);
            io::clear(&TCCR1B, CS11);
            io::clear(&TCCR1B, CS12);
            break;

        case PrescaleMode::CLK1024 :
            io::setActive(&TCCR1B, CS10);
            io::clear(&TCCR1B, CS11);
            io::setActive(&TCCR1B, CS12);
            break;
    }

    prescaleMode_ = prescaleMode;
}

Timer::PrescaleMode Timer::prescaleMode_ = PrescaleMode::CLK;

uint16_t Timer::getPrescale()
{
    return static_cast<uint16_t>(prescaleMode_);
}
