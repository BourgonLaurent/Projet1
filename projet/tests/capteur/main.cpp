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
#include <lib1900/debug.hpp>
#include <lib1900/interruptTimer.hpp>
#include <lib1900/interrupts.hpp>
#include <lib1900/irSensor.hpp>
#include <lib1900/led.hpp>
#include <lib1900/wheels.hpp>
#include <util/delay.h>

constexpr io::Position SENSOR = PA6;
volatile bool gFinishedSearching = 0;

ISR(InterruptTimer_vect)
{
    Wheels::stopTurn(Wheels::Side::RIGHT);
    return;
}

int main()
{
    IrSensor irSensor = IrSensor(SENSOR);
        irSensor.find();
    irSensor.park();
}