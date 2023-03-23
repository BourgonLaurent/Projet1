/**
 * Read infra red sensor values.
 *
 * Hardware Identification
 * OUTPUT:
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 16, 2023
 */

#include <avr/io.h>
#include <lib1900/analogReader.hpp>
#include <lib1900/communication.hpp>

constexpr io::Position SENSOR = PA6;
int main()
{
    Communication::initialize();
    io::setInput(&DDRA, SENSOR);

    AnalogReader reader;
    const uint8_t value = reader.read(SENSOR);
    Communication::send(value);
}