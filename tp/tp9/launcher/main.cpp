/**
 * Run a program in memory.
 *
 * Hardware Identification
 * OUTPUT:
 *  - LED, connected plus to B0, and minus to B1.
 *  - Buzzer, connected plus to B3 and minus to B2.
 *  - H-bridge, connected left  to PD6 (enable) and PD4 (direction).
 *              connected right to PD7 (enable) and PD5 (direction).
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 16, 2023
 */

#include <lib/debug.hpp>
#include <lib/interpreter.hpp>

constexpr uint16_t START_ADDRESS = 0x00000000;

int main()
{
    debug::initialize();

    Interpreter interpreter(START_ADDRESS);
    interpreter.run();

    return 0;
}
