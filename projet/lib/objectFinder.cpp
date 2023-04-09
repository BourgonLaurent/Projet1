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

#include <lib/debug.hpp>
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/sound.hpp>

bool ObjectFinder::timeOut = false;

ObjectFinder::ObjectFinder(Led &led, IrSensor &irSensor, Map &map)
    : led_(led), positionManager_(PositionManager(irSensor, map))
{
    Sound::initialize();
};

void ObjectFinder::park()
{
    while (!positionManager_.irSensor.isdetected(IrSensor::TEN_CM,
                                                 IrSensor::FIFTEEN_CM)) {
        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(50);
        if (!positionManager_.irSensor.isdetected()) {
            interrupts::startCatching();
            Wheels::turnOff();
            _delay_ms(DELAY_TURNOFF_MS);
            find(Wheels::Side::RIGHT, 1.0);
            debug::send("outRight");
            // if (!positionManager_.irSensor.isdetected()) {
            //     find(Wheels::Side::LEFT, 2.0);
            //     debug::send("outLeft");
            // }
            interrupts::stopCatching();
        }
    }
    Wheels::turnOff();
}

void ObjectFinder::find(const Wheels::Side &side, double timerLimit,
                        bool updateQuadrant)
{
    positionManager_.irSensor.setRange(IrSensor::Range::STRAIGHT);
    InterruptTimer::setSeconds(timerLimit);
    timeOut = false;
    if (side == Wheels::Side::LEFT && updateQuadrant)
        positionManager_.updateQuadrant(side);
    InterruptButton::clear();
    InterruptTimer::start();

    interrupts::startCatching();

    Wheels::turn(side);

    while (!positionManager_.irSensor.isdetected() && !timeOut) {
        ;
    }
    Wheels::stopTurn(side);

    InterruptTimer::stop();

    if (updateQuadrant) {
        if (!positionManager_.irSensor.objectDetected()) {
            positionManager_.updateQuadrant(side);
            debug::send("upgrading\n");
        }
        else {
            positionManager_.irSensor.setRange(IrSensor::Range::DIAGONAL);
            debug::send("\nDIAGONAL\n");
        }
    }
    interrupts::stopCatching();
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
    positionManager_.updateQuadrant(side);
}

void ObjectFinder::findTurn(const Wheels::Side &side)
{
    find(side);
    Wheels::turn90(side);
    positionManager_.updateQuadrant(side);
}

void ObjectFinder::findLoop(uint8_t max, const Wheels::Side &side)
{
    uint8_t loopCount = 0;
    while (!positionManager_.irSensor.objectDetected() && loopCount < max) {
        loopCount++;
        find(side);
    }
}

void ObjectFinder::finder()
{

    objectFound_ = false;

    FinderType finderWithPosition = determineFinderType();
    positionManager_.resetQuadrant();

    positionManager_.irSensor.setRange(IrSensor::Range::STRAIGHT);
    debug::send("\nSTRAIGHT\n");

    if (!positionManager_.irSensor.isdetected()) {

        switch (finderWithPosition) {
            case FinderType::TOP_BORDER :
                // debug::send("TOP_BORDER\n");
                turnFind(Wheels::Side::RIGHT);
                if (!positionManager_.irSensor.objectDetected()) {
                    findTurn(Wheels::Side::RIGHT);
                }
                break;

            case FinderType::BOTTOM_BORDER :
                // debug::send("BOTTOM_BORDER\n");
                findTurn(Wheels::Side::RIGHT);

                if (!positionManager_.irSensor.objectDetected()) {
                    turnFind(Wheels::Side::RIGHT);
                }
                break;

            case FinderType::MIDDLE :
                // debug::send("MIDDLE\n");
                findLoop(4, Wheels::Side::RIGHT);
                break;

            case FinderType::TOP_CORNER_LEFT :
                // debug::send("TOP_CORNER_LEFT\n");
                turnFind(Wheels::Side::RIGHT);
                if (!positionManager_.irSensor.objectDetected()) {
                    debug::send("verify\n");
                    find(Wheels::Side::RIGHT, 1.5, false);
                }
                break;

            case FinderType::TOP_CORNER_RIGHT :
                // debug::send("TOP_CORNER_RIGHT\n");
                turnFind(Wheels::Side::LEFT);
                if (!positionManager_.irSensor.objectDetected()) {
                    find(Wheels::Side::LEFT, 1.5, false);
                }
                break;

            case FinderType::BOTTOM_CORNER_RIGHT :
                // debug::send("BOTTOM_CORNER_RIGHT\n");
                find(Wheels::Side::LEFT);
                if (!positionManager_.irSensor.objectDetected()) {
                    find(Wheels::Side::LEFT, 1.5, false);
                }
                break;

            case FinderType::BOTTOM_CORNER_LEFT :
                // debug::send("BOTTOM_CORNER_LEFT\n");
                find(Wheels::Side::RIGHT);
                if (!positionManager_.irSensor.objectDetected()) {
                    find(Wheels::Side::RIGHT, 1.5, false);
                }
                break;

            case FinderType::RIGHT_BORDER :
                // debug::send("RIGHT_BORDER\n");
                findLoop(2, Wheels::Side::LEFT);
                break;

            case FinderType::LEFT_BORDER :
                // debug::send("LEFT_BORDER\n");
                findLoop(2, Wheels::Side::RIGHT);

                break;
        }
    }
    debug::send("waiting\n");
    _delay_ms(1000);
    if (positionManager_.irSensor.objectDetected()) {
        positionManager_.setNextPositionObject(positionManager_.getQuadrant());
        debug::send("\nquadrant :");
        debug::send(positionManager_.getQuadrant());
        debug::send("   \n");
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
    debug::send(positionManager_.lastPosition().x);
    debug::send(" \n");
    debug::send(positionManager_.lastPosition().y);
    debug::send("       \n");
}