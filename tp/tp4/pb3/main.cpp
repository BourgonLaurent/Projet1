#define F_CPU 8000000UL
#include <util/delay.h>

#include <tp2/components/io.hpp>

#include <tp3/components/motor.hpp>

#include <tp4/components/interruptTimer.hpp>
#include <tp4/components/interrupts.hpp>

void InterruptTimer::whenFinished() {}

void ajustementPwm(const double& relativeSpeed)
{
    io::setActive(&TCCR1A, COM1A1);
    io::setActive(&TCCR1A, COM1B1);

    OCR1A = relativeSpeed * 0x00FF;
    OCR1B = relativeSpeed * 0x00FF;

    TCCR1C = 0;
}

int main()
{
    io::setOutput(&DDRD, DDD4);
    io::setOutput(&DDRD, DDD5);
    io::setOutput(&DDRD, DDD6);
    io::setOutput(&DDRD, DDD7);

    io::clear(&PORTD, PORTD6);
    io::clear(&PORTD, PORTD7);

    InterruptTimer::initialize();
    InterruptTimer::setMode(InterruptTimer::Mode::PWM_PHASE_CORRECT);
    InterruptTimer::setPrescaleMode(InterruptTimer::PrescaleMode::CLK1024);
    interrupts::startCatching();

    for (double i = 0; i <= 1; i += 0.25) {
        ajustementPwm(i);

        _delay_ms(2000);
    }

    ajustementPwm(0);

    return 0;
}
