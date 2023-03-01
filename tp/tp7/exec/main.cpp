/**
 * Tests lib1900.
 *
 * Team #4546
 * \author Catalina-Andrea Araya-Figueroa
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

#include <tp7/lib/io.hpp>
#include <tp7/lib/led.hpp>

int main()
{
    LED led(&DDRB, &PORTB, PB0, PB1);
    led.setColor(Color::GREEN);
    return 0;
}
