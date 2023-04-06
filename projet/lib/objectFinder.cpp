/**
 * Finds object.
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
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/sound.hpp>

ObjectFinder::ObjectFinder(Led &led, IrSensor &irSensor, Map &map)
    : led_(led), positionManager_(PositionManager(irSensor, map))
{
    Sound::initialize();
};

void ObjectFinder::park()
{
    while (!positionManager_.irSensor.detect(IrSensor::TEN_CM,
                                             IrSensor::FIFTEEN_CM)) {
        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(50);

        if (!positionManager_.irSensor.detect()) {
            Wheels::turnOff();
            _delay_ms(DELAY_TURNOFF_MS);
            find(Wheels::Side::RIGHT);
            if (!positionManager_.irSensor.detect()) {
                find(Wheels::Side::LEFT);
            }
        }
    }
    _delay_ms(500);
    Wheels::turnOff();
}

void ObjectFinder::find(const Wheels::Side &side, double timerLimit)
{
    InterruptTimer::setSeconds(timerLimit);

    InterruptTimer::start();
    InterruptButton::clear();
    // interrupts::startCatching();

    Wheels::turn(side);

    while (!positionManager_.irSensor.detect()) {
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
    Sound::stop();
}

void ObjectFinder::turnFind(const Wheels::Side &side)
{
    Wheels::turn90(side);
    find(side);
}

void ObjectFinder::findTurn(const Wheels::Side &side)
{
    find(side);
    Wheels::turn90(side);
}

void ObjectFinder::findLoop(uint8_t &quadrant, uint8_t max,
                            const Wheels::Side &side)
{
    while (quadrant < max && positionManager_.irSensor.objectDetected() == 0) {
        find(side);
        if (side == Wheels::Side::LEFT) {
            quadrant--;
        }
        else {
            quadrant++;
        }
    }
}

void ObjectFinder::finder()
{
    objectFound_ = false;
    FinderType finderWithPosition = determineFinderType();
    uint8_t quadrant = 0;
    switch (finderWithPosition) {
        case FinderType::TOP_BORDER :
            Communication::send("TOP_BORDER");
            turnFind(Wheels::Side::RIGHT);
            quadrant = 1;
            if (positionManager_.irSensor.objectDetected() == false) {
                findTurn(Wheels::Side::RIGHT);
                quadrant = 2;
                if (positionManager_.irSensor.objectDetected() == false) {
                    find(Wheels::Side::RIGHT, 1.5);
                    quadrant = 3;
                }
            }
            break;

        case FinderType::BOTTOM_BORDER :
            Communication::send("BOTTOM_BORDER");
            findTurn(Wheels::Side::RIGHT);
            quadrant = 0;

            if (positionManager_.irSensor.objectDetected() == false) {
                if (positionManager_.irSensor.objectDetected() == false) {
                    find(Wheels::Side::RIGHT, 1.5);
                    quadrant = 1;
                }
                turnFind(Wheels::Side::RIGHT);
                quadrant = 3;
            }
            break;

        case FinderType::MIDDLE :
            Communication::send("MIDDLE");
            findLoop(quadrant, 4, Wheels::Side::RIGHT);
            break;

        case FinderType::TOP_CORNER_LEFT :
            Communication::send("TOP_CORNER_LEFT");
            turnFind(Wheels::Side::RIGHT);
            quadrant = 1;
            if (positionManager_.irSensor.objectDetected() == false) {
                find(Wheels::Side::RIGHT, 1.5);
                quadrant = 2;
            }
            break;

        case FinderType::TOP_CORNER_RIGHT :
            Communication::send("TOP_CORNER_RIGHT");
            turnFind(Wheels::Side::LEFT);
            quadrant = 3;
            if (positionManager_.irSensor.objectDetected() == false) {
                find(Wheels::Side::LEFT, 1.5);
                quadrant = 2;
            }
            break;

        case FinderType::BOTTOM_CORNER_RIGHT :
            Communication::send("BOTTOM_CORNER_RIGHT");
            find(Wheels::Side::LEFT);
            quadrant = 3;
            if (positionManager_.irSensor.objectDetected() == false) {
                find(Wheels::Side::LEFT, 1.5);
                quadrant = 2;
            }
            break;

        case FinderType::BOTTOM_CORNER_LEFT :
            Communication::send("BOTTOM_CORNER_LEFT");
            find(Wheels::Side::RIGHT);
            quadrant = 0;
            if (positionManager_.irSensor.objectDetected() == false) {
                find(Wheels::Side::RIGHT, 1.5);
                quadrant = 1;
            }
            break;

        case FinderType::RIGHT_BORDER :
            Communication::send("RIGHT_BORDER");
            quadrant = 3;
            findLoop(quadrant, 2, Wheels::Side::LEFT);
            if (positionManager_.irSensor.objectDetected() == false) {
                find(Wheels::Side::LEFT, 1.5);
                quadrant = 1;
            }
            break;
        case FinderType::LEFT_BORDER :
            Communication::send("LEFT_BORDER");
            quadrant = 0;
            findLoop(quadrant, 2, Wheels::Side::RIGHT);
            if (positionManager_.irSensor.objectDetected() == false) {
                find(Wheels::Side::RIGHT, 1.5);
                quadrant = 2;
            }
            break;
    }

    if (positionManager_.irSensor.objectDetected() == true) {
        positionManager_.setPositionObject(quadrant);
        Communication::send(quadrant);
        objectFound_ = true;
    }
    else {
        objectFound_ = false;
    }
}

ObjectFinder::FinderType ObjectFinder::determineFinderType()
{
    if (positionManager_.lastPosition().x == 7
        && positionManager_.lastPosition().y == 3) {
        return FinderType::TOP_CORNER_RIGHT;
    }
    if (positionManager_.lastPosition().x == 7
        && positionManager_.lastPosition().y == 0) {
        return FinderType::BOTTOM_CORNER_RIGHT;
    }
    if (positionManager_.lastPosition().x == 0
        && positionManager_.lastPosition().y == 3) {
        return FinderType::TOP_CORNER_LEFT;
    }
    if (positionManager_.lastPosition().x == 0
        && positionManager_.lastPosition().y == 0) {
        return FinderType::BOTTOM_CORNER_LEFT;
    }
    if (positionManager_.lastPosition().x > 0
        && positionManager_.lastPosition().x < 7
        && positionManager_.lastPosition().y == 3) {
        return FinderType::TOP_BORDER;
    }
    if (positionManager_.lastPosition().x > 0
        && positionManager_.lastPosition().x < 7
        && positionManager_.lastPosition().y == 0) {
        return FinderType::BOTTOM_BORDER;
    }
    if (positionManager_.lastPosition().x == 0
        && positionManager_.lastPosition().y > 0
        && positionManager_.lastPosition().y < 3) {
        return FinderType::LEFT_BORDER;
    }
    if (positionManager_.lastPosition().x == 7
        && positionManager_.lastPosition().y > 0
        && positionManager_.lastPosition().y < 3) {
        return FinderType::RIGHT_BORDER;
    }
    return FinderType::MIDDLE;
}

bool ObjectFinder::isObjectFound()
{
    return objectFound_;
}
void ObjectFinder::sendLastPosition()
{
    Communication::send(positionManager_.lastPosition().x);
    Communication::send(" ");
    Communication::send(positionManager_.lastPosition().y);
    Communication::send("       ");
}