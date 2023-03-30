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
#include <util/delay.h>

#include <lib/communication.hpp>
#include <lib/debug.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/irSensor.hpp>
#include <lib/led.hpp>
#include <lib/wheels.hpp>

constexpr io::Position SENSOR = PA6;

int main()
{
    IrSensor irSensor = IrSensor(SENSOR);
    Communication::initialize();

    uint8_t value = irSensor.read();
    Communication::send(value);
}