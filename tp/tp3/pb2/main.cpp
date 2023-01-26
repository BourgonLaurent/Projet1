/**
 * Problem 2:
 *  Motor control
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 26, 2023
 *
 * Hardware Identification
 * TODO Set hardware identification
 *
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include <tp3/components/motor.hpp>

constexpr uint32_t DURATION = 2000000;

void forwardIncrement(Motor &motor, const double &frequencyUs)
{
    const double periodUs = 1.0 / frequencyUs;
    const double numberOfCycles = DURATION / periodUs;

    for (double i = 0; i <= 1; i += 0.25)
    {
        for (uint16_t j = 0; j < numberOfCycles; j++)
        {
            motor.backward(periodUs, i);
        }
    }
}

int main()
{
    Motor motor = Motor(&DDRB, &PORTB, PORTB0, PORTB1);

    forwardIncrement(motor, 60e-6);
    forwardIncrement(motor, 400e-6);
    return 0;
}
