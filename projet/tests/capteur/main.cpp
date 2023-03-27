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

ISR(InterruptTimer_vect)
{
    Wheels::stopTurn(Wheels::Side::RIGHT);
    return;
}

int main()
{
    Communication::initialize();

    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 1.65);
    IrSensor irSensor = IrSensor(SENSOR);
    Wheels::initialize();
    Led led = Led(&DDRB, &PORTB, PB0, PB1);
    Wheels::turn(Wheels::Side::RIGHT);
    interrupts::startCatching();
    InterruptTimer::start();
    while (!irSensor.detect()) {
        uint16_t value = irSensor.read();
        Communication::send(value);
        Communication::send(" ");
        led.setColor(Led::Color::GREEN);
    }
    InterruptTimer::stop();
    Wheels::stopTurn(Wheels::Side::RIGHT);
    led.setColor(Led::Color::RED);
    uint16_t value = irSensor.read();
    Communication::send(value);
    Communication::send(" !!!!!");

    while (!irSensor.detectDistanceToPark()) {
        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(50);
    }
    Wheels::turnOff();
}