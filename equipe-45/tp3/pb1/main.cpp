/**
 * Problem 1:
 *  LED attenuation.
 *
 * Team #45
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

#include <tp2/components/colors.hpp>
#include <tp2/components/led.hpp>

void wait(double delay)
{
    if (delay == 0) {
        return;
    }

    for (uint16_t i = 0; i < delay / 40; i++) {
        _delay_us(10);
    }
}

constexpr uint32_t DURATION = 3000000;
constexpr uint16_t PERIOD_US = 1000;
constexpr uint16_t NUMBER_OF_CYCLES = DURATION / PERIOD_US;
constexpr double INCREMENT_RATIO = 1.0 / NUMBER_OF_CYCLES;

int main()
{
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    double onRatio = 1;
    double offRatio = 0;
    for (uint16_t i = 0; i < NUMBER_OF_CYCLES; i++) {
        led.setColor(Color::GREEN);
        wait(PERIOD_US * onRatio);
        led.setColor(Color::OFF);
        wait(PERIOD_US * offRatio);

        onRatio -= INCREMENT_RATIO;
        offRatio += INCREMENT_RATIO;
    }

    return 0;
}
