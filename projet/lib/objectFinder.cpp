/**
 * Finds object.
 *
 * HARDWARE:
 * IR sensor to PA0
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

ObjectFinder::ObjectFinder(Led &led, IrSensor &irSensor, Map &map)
    : led_(led), positionManager_(PositionManager(irSensor, map))
{
    Sound::initialize();
};

void ObjectFinder::park(volatile bool &timeOut)
{
    while (!positionManager_.irSensor.isClose()) {

        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(SPEED_VALUE_TO_PARK);

        if (!positionManager_.irSensor.isForward()) {
            isObjectForward(timeOut);
        }
    }
    _delay_ms(750);
    Wheels::turnOff();
}

void ObjectFinder::find(const Wheels::Side &side, volatile bool &timeOut,
                        double timerLimit, bool isObjectPresent)
{
    debug::send("In Find\n");
    if (!positionManager_.irSensor.isForward()) {

        if (side == Wheels::Side::LEFT && isObjectPresent == false) {
            positionManager_.updateQuadrant(side);
        }

        search(side, timeOut, timerLimit);

        if (positionManager_.irSensor.isObjectDetected()) {
            positionManager_.irSensor.setRange(IrSensor::Range::DIAGONAL);
            debug::send("\nDIAGONAL\n");
        }
        else if (!isObjectPresent && isObjectForward(timeOut, side)) {
            // positionManager_.updateQuadrant(side);
            positionManager_.irSensor.setRange(IrSensor::Range::STRAIGHT);
            debug::send("STRAIGHT\n");
        }
        // else
        //     debug::send("dans le else de find \n");
        // positionManager_.updateQuadrant(side);

        interrupts::stopCatching();
    }
}

void ObjectFinder::search(const Wheels::Side &side, volatile bool &timeOut,
                          double timerLimit)
{
    InterruptTimer::setSeconds(timerLimit);
    timeOut = false;
    InterruptButton::clear();
    InterruptTimer::start();
    interrupts::startCatching();

    Wheels::turn(side);

    while (!positionManager_.irSensor.isForward() && !timeOut) {
        ;
    }
    _delay_ms(500);
    positionManager_.irSensor.isForward();
    Wheels::stopTurn(side);
    InterruptTimer::stop();
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

void ObjectFinder::turnFind(const Wheels::Side &side, volatile bool &timeOut)
{
    Wheels::turn90(side);
    find(side, timeOut);
    positionManager_.updateQuadrant(side);
}

void ObjectFinder::findTurn(const Wheels::Side &side, volatile bool &timeOut)
{
    find(side, timeOut);
    if (!positionManager_.irSensor.isObjectDetected()) {
        Wheels::turn90(side);
        positionManager_.updateQuadrant(side);
    }
}

void ObjectFinder::findLoop(uint8_t max, const Wheels::Side &side,
                            volatile bool &timeOut)
{
    debug::send("in findloop\n");
    uint8_t loopCount = 0;
    while (!positionManager_.irSensor.isObjectDetected() && loopCount < max) {
        debug::send("no object detected, still in loop\n");
        loopCount++;
        find(side, timeOut);
        _delay_ms(1500);
    }
}

void ObjectFinder::finder(volatile bool &timeOut)
{

    objectFound_ = false;
    positionManager_.irSensor.setObjectDetected(false);

    FinderType finderWithPosition = determineFinderType();
    positionManager_.resetQuadrant();

    positionManager_.irSensor.setRange(IrSensor::Range::STRAIGHT);
    debug::send("\nSTRAIGHT\n");

    switch (finderWithPosition) {
        case FinderType::TOP_BORDER :
            // debug::send("TOP_BORDER\n");
            turnFind(Wheels::Side::RIGHT, timeOut);
            if (!positionManager_.irSensor.isObjectDetected()) {
                findTurn(Wheels::Side::RIGHT, timeOut);
            }
            break;

        case FinderType::BOTTOM_BORDER :
            // debug::send("BOTTOM_BORDER\n");
            findTurn(Wheels::Side::RIGHT, timeOut);
            if (!positionManager_.irSensor.isObjectDetected()) {
                findTurn(Wheels::Side::RIGHT, timeOut);
            }
            break;

        case FinderType::MIDDLE :
            // debug::send("MIDDLE\n");
            findLoop(4, Wheels::Side::RIGHT, timeOut);
            break;

        case FinderType::TOP_CORNER_LEFT :
            // debug::send("TOP_CORNER_LEFT\n");
            turnFind(Wheels::Side::RIGHT, timeOut);
            break;

        case FinderType::TOP_CORNER_RIGHT :
            // debug::send("TOP_CORNER_RIGHT\n");
            turnFind(Wheels::Side::LEFT, timeOut);
            break;

        case FinderType::BOTTOM_CORNER_RIGHT :
            // debug::send("BOTTOM_CORNER_RIGHT\n");
            find(Wheels::Side::LEFT, timeOut);
            break;

        case FinderType::BOTTOM_CORNER_LEFT :
            // debug::send("BOTTOM_CORNER_LEFT\n");
            find(Wheels::Side::RIGHT, timeOut);
            break;

        case FinderType::RIGHT_BORDER :
            debug::send("RIGHT_BORDER\n");
            findLoop(2, Wheels::Side::LEFT, timeOut);
            break;

        case FinderType::LEFT_BORDER :
            // debug::send("LEFT_BORDER\n");
            findLoop(2, Wheels::Side::RIGHT, timeOut);

            break;
    }
    _delay_ms(1000);

    if (positionManager_.irSensor.isObjectDetected()) {
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
    if (positionManager_.getLastPosition().x == 7
        && positionManager_.getLastPosition().y == 3) {
        return FinderType::TOP_CORNER_RIGHT;
    }
    if (positionManager_.getLastPosition().x == 7
        && positionManager_.getLastPosition().y == 0) {
        return FinderType::BOTTOM_CORNER_RIGHT;
    }
    if (positionManager_.getLastPosition().x == 0
        && positionManager_.getLastPosition().y == 3) {
        return FinderType::TOP_CORNER_LEFT;
    }
    if (positionManager_.getLastPosition().x == 0
        && positionManager_.getLastPosition().y == 0) {
        return FinderType::BOTTOM_CORNER_LEFT;
    }
    if (positionManager_.getLastPosition().x > 0
        && positionManager_.getLastPosition().x < 7
        && positionManager_.getLastPosition().y == 3) {
        return FinderType::TOP_BORDER;
    }
    if (positionManager_.getLastPosition().x > 0
        && positionManager_.getLastPosition().x < 7
        && positionManager_.getLastPosition().y == 0) {
        return FinderType::BOTTOM_BORDER;
    }
    if (positionManager_.getLastPosition().x == 0
        && positionManager_.getLastPosition().y > 0
        && positionManager_.getLastPosition().y < 3) {
        return FinderType::LEFT_BORDER;
    }
    if (positionManager_.getLastPosition().x == 7
        && positionManager_.getLastPosition().y > 0
        && positionManager_.getLastPosition().y < 3) {
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
    debug::send(positionManager_.getLastPosition().x);
    debug::send("\n");
    debug::send(positionManager_.getLastPosition().y);
    debug::send("\n");
}

bool ObjectFinder::isObjectForward(volatile bool &timeOut, Wheels::Side side)
{
    debug::send("Mini Find \n");
    if (side == Wheels::Side::RIGHT) {
        if (!positionManager_.irSensor.isForward())
            search(Wheels::Side::RIGHT, timeOut, 2.0);
        if (!positionManager_.irSensor.isForward())
            search(Wheels::Side::LEFT, timeOut, 2.0);
    }

    else if (side == Wheels::Side::LEFT) {
        if (!positionManager_.irSensor.isForward())
            search(Wheels::Side::LEFT, timeOut, 2.0);
        if (!positionManager_.irSensor.isForward())
            search(Wheels::Side::RIGHT, timeOut, 2.0);
    }

    return positionManager_.irSensor.isObjectDetected();
}
void ObjectFinder::initialize()
{
    positionManager_.initialize();
}