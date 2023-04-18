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

#include "app/detect/objectFinder.hpp"

#include <app/detect/constants.hpp>
#include <lib/debug.hpp>

#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/sound.hpp>

ObjectFinder::ObjectFinder(IrSensor &irSensor) : irSensor_(&irSensor)
{
    Sound::initialize();
};

void ObjectFinder::park(volatile bool &timeOut, const Wheels::Side &side)
{
    isObjectInFront(timeOut, Wheels::getOtherSide(side),
                    constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                    constants::SECOND_DELAY_IN_FRONT_PARK_MS,
                    constants::SPEED_PARK);

    while (!irSensor_->isClose()) {

        while (irSensor_->isTooClose()) {
            Wheels::setDirection(Wheels::Direction::BACKWARD);
            Wheels::setSpeed(constants::SPEED_VALUE_TO_PARK);
        }
        Wheels::setDirection(Wheels::Direction::FORWARD);
        Wheels::setSpeed(constants::SPEED_VALUE_TO_PARK);

        if (!irSensor_->isInFront()) {
            isObjectInFront(timeOut, Wheels::Side::LEFT,
                            constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                            constants::SECOND_DELAY_IN_FRONT_PARK_MS,
                            constants::SPEED_PARK);
        }
    }
    Wheels::turnOff();
}

void ObjectFinder::find(const Wheels::Side &side, volatile bool &timeOut,
                        double timerLimit)
{
    if (!irSensor_->isInFront()) {

        if (side == Wheels::Side::LEFT) {
            positionManager_.updateQuadrant(side);
        }

        search(side, timeOut, timerLimit);

        if (irSensor_->isObjectDetected()) {
            irSensor_->setRange(IrSensor::Range::DIAGONAL);
            debug::send("\nDIAGONAL\n");
        }
        else if (isObjectInFront(timeOut, side)) {
            if (side != Wheels::Side::LEFT) {
                positionManager_.updateQuadrant(side);
            }
            irSensor_->setRange(IrSensor::Range::STRAIGHT);
            debug::send("STRAIGHT\n");
        }
        else if (side != Wheels::Side::LEFT) {
            positionManager_.updateQuadrant(side);
        }

        interrupts::stopCatching();
    }
    if (irSensor_->isObjectDetected())
        park(timeOut, side);
}

void ObjectFinder::search(const Wheels::Side &side, volatile bool &timeOut,
                          double timerLimit, uint8_t speed)
{
    InterruptTimer::setSeconds(timerLimit);
    timeOut = false;
    InterruptButton::clear();
    InterruptTimer::start();
    interrupts::startCatching();

    Wheels::turn(side, speed);

    while (!irSensor_->isInFront() && !timeOut) {}
    // _delay_ms(200);
    irSensor_->isInFront();
    Wheels::stopTurn(side);
    InterruptTimer::stop();
    interrupts::stopCatching();
}

void ObjectFinder::alertParked()
{

    for (uint8_t i = 0; i < 3; i++) {
        Sound::playNote(constants::HIGH_NOTE);
        _delay_ms(constants::DELAY_ALERT_PARKED_MS);
        Sound::stop();
        _delay_ms(constants::DELAY_ALERT_PARKED_MS);
    }
}

void ObjectFinder::alertFoundNothing()
{
    Sound::playNote(constants::LOW_NOTE);
    _delay_ms(constants::DELAY_FOUND_NOTHING_MS);
    Sound::stop();
}

void ObjectFinder::turnFind(const Wheels::Side &side, volatile bool &timeOut)
{
    Wheels::turn90(side);
    positionManager_.updateQuadrant(side);
    if (!isObjectInFront(timeOut, side))
        find(side, timeOut, 3.0); // pourquoi 3.0 secondes?????
    _delay_ms(constants::DELAY_AFTER_FIND_MS);
}

void ObjectFinder::findTurn(const Wheels::Side &side, volatile bool &timeOut)
{
    find(side, timeOut);
    if (!irSensor_->isObjectDetected()) {
        Wheels::turn90(side);
        positionManager_.updateQuadrant(side);
    }
}

void ObjectFinder::findLoop(uint8_t max, const Wheels::Side &side,
                            volatile bool &timeOut)
{
    uint8_t loopCount = 0;
    while (!irSensor_->isObjectDetected() && loopCount < max) {
        loopCount++;
        find(side, timeOut,
             constants::DELAY_FIND_MS
                 + (loopCount
                    * constants::DELAY_INCREMENT_FIND_LOOP)); // à tester
        _delay_ms(constants::DELAY_BETWEEN_FINDS_MS);
    }
}

void ObjectFinder::finder(volatile bool &timeOut)
{
    objectFound_ = false;
    irSensor_->setObjectDetected(false);

    auto finderWithPosition = getCardinal();
    positionManager_.resetQuadrant();

    irSensor_->setRange(IrSensor::Range::STRAIGHT);

    switch (finderWithPosition) {
        case Border::TOP :
            // debug::send("TOP_BORDER\n");
            Wheels::turn90(Wheels::Side::RIGHT);
            positionManager_.updateQuadrant(Wheels::Side::RIGHT);
            if (!isObjectInFront(timeOut, Wheels::Side::RIGHT))
                findLoop(2, Wheels::Side::RIGHT, timeOut);
            break;

        case Border::BOTTOM :
            // debug::send("BOTTOM_BORDER\n");
            findTurn(Wheels::Side::RIGHT, timeOut);
            if (!irSensor_->isObjectDetected()) {
                turnFind(Wheels::Side::RIGHT, timeOut);
            }
            break;

        case Border::MIDDLE :
            // debug::send("MIDDLE\n");
            findLoop(4, Wheels::Side::RIGHT, timeOut);
            break;

        case Border::TOP_LEFT :
            // debug::send("TOP_CORNER_LEFT\n");
            turnFind(Wheels::Side::RIGHT, timeOut);
            break;

        case Border::TOP_RIGHT :
            // debug::send("TOP_CORNER_RIGHT\n");
            turnFind(Wheels::Side::LEFT, timeOut);
            break;

        case Border::BOTTOM_RIGHT :
            // debug::send("BOTTOM_CORNER_RIGHT\n");
            if (!isObjectInFront(timeOut, Wheels::Side::RIGHT))
                find(Wheels::Side::LEFT, timeOut);
            break;

        case Border::BOTTOM_LEFT :
            // debug::send("BOTTOM_CORNER_LEFT\n");
            find(Wheels::Side::RIGHT, timeOut);
            break;

        case Border::RIGHT :
            // debug::send("RIGHT_BORDER\n");
            findLoop(2, Wheels::Side::LEFT, timeOut);
            break;

        case Border::LEFT :
            // debug::send("LEFT_BORDER\n");
            findLoop(2, Wheels::Side::RIGHT, timeOut);

            break;
    }
    _delay_ms(constants::DELAY_AFTER_FIND_MS);

    objectFound_ = irSensor_->isObjectDetected();

    if (objectFound_) {
        IrSensor::Range range = irSensor_->getRange();
        IrSensor::Distance distance = irSensor_->getDistance();

        positionManager_.setNextPositionObject(range, distance);
    }
}

Border ObjectFinder::getCardinal()
{
    auto position = positionManager_.getLastPosition();
    auto cardinal = Border::MIDDLE;

    switch (position.x) {
        case 0 :
            cardinal |= Border::LEFT;
            break;
        case 7 :
            cardinal |= Border::RIGHT;
            break;
    }

    switch (position.y) {
        case 0 :
            cardinal |= Border::BOTTOM;
            break;
        case 3 :
            cardinal |= Border::TOP;
            break;
    }

    return cardinal;
}

bool ObjectFinder::isObjectFound()
{
    return objectFound_;
}

void ObjectFinder::sendLastPosition()
{
    debug::send("\n");
    debug::send(positionManager_.getLastPosition().x);
    debug::send("\n");
    debug::send(positionManager_.getLastPosition().y);
    debug::send("\n");
}

bool ObjectFinder::isObjectInFront(volatile bool &timeOut, Wheels::Side side,
                                   double delay1, double delay2, uint8_t speed)
{
    debug::send("Mini Find \n");
    if (side == Wheels::Side::RIGHT) {
        if (!irSensor_->isInFront())
            search(Wheels::Side::RIGHT, timeOut, delay1, speed);
        if (!irSensor_->isInFront())
            search(Wheels::Side::LEFT, timeOut, delay2, speed);
    }

    else if (side == Wheels::Side::LEFT) {
        if (!irSensor_->isInFront())
            search(Wheels::Side::LEFT, timeOut, delay1, speed);
        if (!irSensor_->isInFront())
            search(Wheels::Side::RIGHT, timeOut, delay2, speed);
    }

    return irSensor_->isObjectDetected();
}

Point ObjectFinder::getLastPosition()
{
    return positionManager_.getLastPosition();
}
