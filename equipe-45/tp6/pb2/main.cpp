/**
 * Problem 2:
 *  Set color of LED based on light intensity:
 *      Poor: Green
 *      Ambient: Amber
 *      Flashlight: Red
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 16, 2023
 *
 * Hardware Identification
 * INPUT: Photoresistor connected to A0.
 * OUTPUT: Bicolor LED connected plus to B0 and minus to B1.
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include <tp6/components/can.h>
#include <tp6/components/led.hpp>

constexpr uint8_t THRESHOLD_LOW_LIGHT = 170;
constexpr uint8_t THRESHOLD_HIGH_LIGHT = 240;
constexpr uint8_t AMBER_DELAY_MS = 10;

int main()
{
    LED led = LED(&DDRB, &PORTB, PB0, PB1);
    can analogDigitalConverter = can();

    while (true) {
        uint8_t lightIntensity = analogDigitalConverter.lecture(PA0) >> 2;

        if (lightIntensity <= THRESHOLD_LOW_LIGHT) {
            led.setColor(Color::GREEN);
        }
        else if (lightIntensity >= THRESHOLD_HIGH_LIGHT) {
            led.setColor(Color::RED);
        }
        else {
            led.setColor(Color::GREEN);
            _delay_ms(AMBER_DELAY_MS);
            led.setColor(Color::RED);
            _delay_ms(AMBER_DELAY_MS);
        }
    }

    return 0;
};
