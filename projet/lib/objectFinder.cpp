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

#include <lib/interruptTimer.hpp>
#include <lib/interruptButton.hpp>
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

        if (!irSensor_.detect()) {
            Wheels::turnOff();
            _delay_ms(DELAY_TURNOFF_MS);
            find(Wheels::Side::RIGHT);
            if (!irSensor_.detect()) {
                find(Wheels::Side::LEFT);
            }
        }
    }
    _delay_ms(500);
    Wheels::turnOff();
}

void ObjectFinder::find(Wheels::Side side)
{

    InterruptTimer::start();
    InterruptButton::clear();
    interrupts::startCatching();

    Wheels::turn(side);

    while (!irSensor_.detect()) {
        led_.setColor(Led::Color::GREEN);
    }

    InterruptTimer::stop();
    interrupts::stopCatching();

    led_.setColor(Led::Color::RED);
    Wheels::stopTurn(side);
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

void ObjectFinder::turnFind(Wheels::Side side)
{
    Wheels::turn90(side);
    find(side);
}

void ObjectFinder::findTurn(Wheels::Side side)
{
    find(side);
    Wheels::turn90(side);
}

void ObjectFinder::findLoop(uint8_t &i, uint8_t max, Wheels::Side side)
{
    while (i < max && irSensor_.objectFound() == 0) {
        find(side);
        i++;
    }
}

void ObjectFinder::finder(const FinderType &finderWithPosition)
{
    uint8_t i = 0;
    switch (finderWithPosition) {
        case FinderType::TOP :
            turnFind(Wheels::Side::RIGHT);
            if (irSensor_.objectFound() == 1) {
                findTurn(Wheels::Side::RIGHT);
            }
            break;

        case FinderType::BOTTOM :
            findTurn(Wheels::Side::RIGHT);
            if (irSensor_.objectFound() == 1) {
                turnFind(Wheels::Side::RIGHT);
            }
            break;

        case FinderType::MIDDLE :
            findLoop(i, 4, Wheels::Side::RIGHT);
            break;

        case FinderType::TOP_CORNER_LEFT :
            turnFind(Wheels::Side::LEFT);
            break;

        case FinderType::TOP_CORNER_RIGHT :
            turnFind(Wheels::Side::RIGHT);
            break;

        case FinderType::BOTTOM_CORMER_RIGHT :
            find(Wheels::Side::RIGHT);
            break;

        case FinderType::BOTTOM_CORNER_LEFT :
            find(Wheels::Side::LEFT);
            break;

        case FinderType::RIGHT :
            i = 0;
            findLoop(i, 2, Wheels::Side::RIGHT);
            break;
        case FinderType::LEFT :
            i = 0;
            findLoop(i, 2, Wheels::Side::LEFT);
            break;
    }
}

bool ObjectFinder::isObjectFound()
{
    return objectFound_;
}