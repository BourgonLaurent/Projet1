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


int main()
{
    AnalogReader reader;
    io::setOutput(&DDRA, PA6);

}