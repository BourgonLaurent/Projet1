#include "interruptTimer.hpp"

#include <tp2/components/io.hpp>

#include <tp4/components/interrupts.hpp>

void InterruptTimer::initialize()
{
    interrupts::stopCatching();

    // Force Output Compare for A (p.131)
    io::clear(&TCCR1C, FOC1A);

    setMode(Mode::NORMAL);
    setPrescaleMode(PrescaleMode::CLK);
    setSeconds(0);

    stop();

    interrupts::startCatching();
}

void InterruptTimer::setSeconds(uint8_t delayS)
{
    OCR1A = delayS * CYCLES_PER_SECOND;
}

void InterruptTimer::setMode(const Mode& mode)
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

void InterruptTimer::setPrescaleMode(const PrescaleMode& prescaleMode)
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
