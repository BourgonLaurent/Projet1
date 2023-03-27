/**
 * Run two programs:
 *  - Detect   : Find and log poles on a map.
 *  - Transmit : Calculate the convex hull from the poles
 *               and send a SVG through RS232.
 *
 * Hardware Identification:
 *  INPUT:
 *    - Interrupt Push Button: D2
 *    - White Push Button: C2
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#include <avr/io.h>

#include <lib/button.hpp>
#include <lib/debug.hpp>

int main()
{
    debug::initialize();

    Button white(&DDRC, &PINC, PC2, Button::ActiveMode::RELEASED);
    Button interrupt(&DDRD, &PIND, PD2);

    while (!white.isPressed() && !interrupt.isPressed()) {}

    if (interrupt.isPressed()) {
        debug::send("Mode: detect\n");
        // call detect main function
    }
    else if (white.isPressed()) {
        debug::send("Mode: transmit\n");
        // call transmit main function
    }
}
