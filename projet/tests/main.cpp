/**
 * Read value from IrSensor
 *
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 28, 2023
 */

#include <avr/io.h>
#include <lib1900/communication.hpp>
#include <lib1900/debug.hpp>
#include <lib1900/interruptTimer.hpp>
#include <lib1900/interrupts.hpp>
#include <lib1900/irSensor.hpp>
#include <lib1900/led.hpp>
#include <lib1900/wheels.hpp>
#include <util/delay.h>

constexpr io::Position SENSOR = PA6;

int main()
{
    IrSensor irSensor = IrSensor(SENSOR);
    Communication::initialize();

    uint8_t value = irSensor.read();
    Communication::send(value);
}