/**
 * Control H-bridge using a PWM.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (DDRD) will be set automatically.
 * OUTPUT: Left motor on D5 (enable) and D7 (direction).
 * OUTPUT: Right motor on D4 (enable) D6 (direction).
 *
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

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
