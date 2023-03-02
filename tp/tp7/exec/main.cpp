/**
 * Tests lib1900.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 *
 * Hardware Identification
 * INPUT: .
 * OUTPUT: .
 */

#include <avr/io.h>
#include <util/delay.h>

#include <lib/led.hpp>

int main()
{
    Led led(&DDRB, &PORTB, PB0, PB1);
    while (true) {
        led.setAmberForMs(1000);
        _delay_ms(1000);
    }
    return 0;
}
