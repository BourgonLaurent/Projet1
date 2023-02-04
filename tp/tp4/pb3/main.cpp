#define F_CPU 8000000UL
#include <util/delay.h>

#include <tp2/components/io.hpp>

#include <tp3/components/motor.hpp>

#include <tp4/components/interrupts.hpp>
#include <tp4/components/pwmMotor.hpp>
#include <tp4/components/timer.hpp>

int main()
{
    PwmMotor::initialize(PwmMotor::Side::BOTH);
    PwmMotor::setMode(PwmMotor::Mode::PWM_PHASE_CORRECT);
    PwmMotor::setPrescaleMode(PwmMotor::PrescaleMode::CLK1024);

    for (double i = 0; i <= 1; i += 0.25) {
        PwmMotor::setSpeed(PwmMotor::Side::BOTH, i);
        _delay_ms(2000);
    }

    PwmMotor::setSpeed(PwmMotor::Side::BOTH, 0);

    return 0;
}
