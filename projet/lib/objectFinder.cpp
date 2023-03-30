/**
 * Control of a infrared sensor.
 *
 * HARDWARE:
 * IR sensor to PA6
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 28, 2023
 */

#include "objectFinder.hpp"

#include <lib/communication.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/sound.hpp>

ObjectFinder::ObjectFinder(Led &led, IrSensor &irSensor)
    : led_(led), irSensor_(irSensor)
{
    Sound::initialize();
};

void ObjectFinder::park()
{
    while (!irSensor_.detect(IrSensor::TEN_CM, IrSensor::FIFTEEN_CM)) {
        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(50);
        _delay_ms(DELAY_TURNOFF_MS);
        Wheels::turnOff();
        if (!irSensor_.detect()) {
            find();
            if (!irSensor_.detect()) {
                find(Wheels::Side::LEFT);
            }
        }
    }
    Wheels::turnOff();
}

void ObjectFinder::find(Wheels::Side side)
{

    Wheels::turn(side);
    interrupts::startCatching();
    InterruptTimer::start();

    while (!irSensor_.detect()) {
        led_.setColor(Led::Color::GREEN);
    }
    InterruptTimer::stop();
    _delay_ms(DELAY_TURN_MIDDLE_OBJECT_MS);
    Wheels::stopTurn(side);
    led_.setColor(Led::Color::RED);
}

void ObjectFinder::alertParked()
{

    for (uint8_t i = 0; i < 3; i++) {
        Sound::playNote(HIGH_NOTE);
        _delay_ms(DELAY_ALERT_PARKED_MS);
        Sound::stop();
        _delay_ms(DELAY_ALERT_PARKED_MS);
    }
}

void ObjectFinder::alertFoundNothing()
{
    Sound::playNote(LOW_NOTE);
    _delay_ms(DELAY_FOUND_NOTHING_MS);
}