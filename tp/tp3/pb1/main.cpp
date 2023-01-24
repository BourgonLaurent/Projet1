/**
 * Problem 1:
 *  LED attenuation
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
 *
 * Hardware Identification
 * OUTPUT: Bicolor LED connected plus to A0 and minus to A1.
 *
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include <tp2/components/led.hpp>
#include <tp2/components/colors.hpp>

void wait(uint16_t delay)
{
    for (uint16_t i = 0; i < delay; i++)
    {
        _delay_us(10);
    }
}

constexpr __uint24 TOTAL_SHUTDOWN_US = 3000000;
constexpr uint16_t PERIOD_US = 1000;

int main()
{
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    for (uint16_t i = 0; i < PERIOD_US / 2; i += TOTAL_SHUTDOWN_US / PERIOD_US / PERIOD_US)
    {
        led.setColor(Color::GREEN);
        wait(PERIOD_US - i);
        led.setColor(Color::OFF);
        wait(i);
    }

    return 0;
}