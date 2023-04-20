/**
 * Finds object.
 *
 * Hardware Identification:
 *  NOTE: The data direction registers are set automatically.
 *
 *  INPUT:
 *    - IR Sensor
 *
 *  OUTPUT:
 *    - Wheels
 *      - Left  | PD6 (enable) and PD4 (direction)
 *      - Right | PD7 (enable) and PD5 (direction)
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

#include <app/detect/constants.hpp>
#include <app/misc/map/map.hpp>

#include <lib/debug.hpp>
#include <lib/interruptTimer.hpp>

volatile bool ObjectFinder::timeOut_ = false;
bool ObjectFinder::timerActive_ = false;

void ObjectFinder::handleTimer()
{
    if (timerActive_) {
        timeOut_ = true;
        // debug::send("handled");
    }
}

ObjectFinder::ObjectFinder(IrSensor &irSensor) : irSensor_(&irSensor){};

void ObjectFinder::run()
{
    objectFound_ = false;
    irSensor_->setObjectDetected(false);

    positionManager_.resetQuadrant();
    irSensor_->setRange(IrSensor::Range::STRAIGHT);

    auto border = getBorder();
    switch (border) {
        case Border::TOP :
            Wheels::turn(Wheels::Side::RIGHT);
            positionManager_.updateQuadrant(Wheels::Side::RIGHT);

            if (!isObjectInFront(Wheels::Side::RIGHT)) {
                findLoop(N_FINDS_ON_BORDER, Wheels::Side::RIGHT);
            }

            break;

        case Border::BOTTOM :
            findTurn(Wheels::Side::RIGHT);

            if (!irSensor_->isObjectDetected()) {
                turnFind(Wheels::Side::RIGHT);
            }

            break;

        case Border::LEFT :
        case Border::RIGHT :
            findLoop(N_FINDS_IN_MIDDLE, border == Border::LEFT
                                            ? Wheels::Side::RIGHT
                                            : Wheels::Side::LEFT);
            break;

        case Border::TOP_LEFT :
        case Border::TOP_RIGHT :
            turnFind(border == Border::TOP_LEFT ? Wheels::Side::RIGHT
                                                : Wheels::Side::LEFT);
            break;

        case Border::BOTTOM_LEFT :
        case Border::BOTTOM_RIGHT :
            find(border == Border::BOTTOM_LEFT ? Wheels::Side::RIGHT
                                               : Wheels::Side::LEFT);
            break;

        case Border::MIDDLE :
            findLoop(N_FINDS_IN_MIDDLE, Wheels::Side::RIGHT);
            break;
    }

    _delay_ms(constants::DELAY_AFTER_FIND_MS);

    objectFound_ = irSensor_->isObjectDetected();

    if (objectFound_) {
        IrSensor::Range range = irSensor_->getRange();

        positionManager_.setNextPositionObject(range);
    }
}

void ObjectFinder::find(const Wheels::Side &side, const uint16_t timerLimit)
{
    if (!irSensor_->isInFront()) {
        if (side == Wheels::Side::LEFT) {
            positionManager_.updateQuadrant(side);
        }

        search(side, timerLimit);

        if (irSensor_->isObjectDetected()) {
            debug::send("\nDIAGONAL\n");
            irSensor_->setRange(IrSensor::Range::DIAGONAL);
        }
        else if (isObjectInFront(side)) {
            if (side != Wheels::Side::LEFT) {
                positionManager_.updateQuadrant(side);
            }

            debug::send("STRAIGHT\n");
            irSensor_->setRange(IrSensor::Range::STRAIGHT);
        }
        else if (side != Wheels::Side::LEFT) {
            positionManager_.updateQuadrant(side);
        }

        interrupts::stopCatching();
    }

    if (irSensor_->isObjectDetected()) {
        park(side);
    }
}

void ObjectFinder::search(const Wheels::Side &side, const uint16_t timerLimit,
                          const uint8_t speed)
{
    InterruptTimer::setMilliseconds(timerLimit);
    InterruptTimer::start();
    interrupts::startCatching();

    debug::send("Searching\n");
    debug::send("Timer", timerLimit);

    Wheels::rotate(side, speed);

    timeOut_ = false;
    timerActive_ = true;

    while (!timeOut_ && !irSensor_->isInFront()) {}

    timerActive_ = false;

    irSensor_->isInFront();

    Wheels::stopRotating(side);
    InterruptTimer::stop();
    interrupts::stopCatching();
}

void ObjectFinder::park(const Wheels::Side &side)
{
    isObjectInFront(!side, constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                    constants::SECOND_DELAY_IN_FRONT_PARK_MS,
                    constants::SPEED_PARK);

    uint8_t counter = 0;
    positionManager_.setDistance(PositionManager::Distance::CLOSE);
    while (!irSensor_->isClose()) {
        counter++;
        if (counter == constants::CLOSE_FAR_THRESHOLD) {
            positionManager_.setDistance(PositionManager::Distance::FAR);
        }

        debug::send("Counter", counter);

        Wheels::setSpeed(constants::SPEED_VALUE_TO_PARK);

        while (irSensor_->isTooClose()) {
            Wheels::setDirection(Wheels::Direction::BACKWARD);
        }

        Wheels::setDirection(Wheels::Direction::FORWARD);

        if (!irSensor_->isInFront()) {
            isObjectInFront(Wheels::Side::LEFT,
                            constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                            constants::SECOND_DELAY_IN_FRONT_PARK_MS,
                            constants::SPEED_PARK);
        }
    }

    Wheels::turnOff();
}

bool ObjectFinder::isObjectFound()
{
    return objectFound_;
}

bool ObjectFinder::isObjectInFront(const Wheels::Side &side,
                                   const uint16_t firstDelay,
                                   const uint16_t secondDelay,
                                   const uint8_t speed)
{
    debug::send("Checking in front\n");
    debug::send("first", firstDelay);
    debug::send("second", secondDelay);

    if (!irSensor_->isInFront())
        search(side, firstDelay, speed);

    if (!irSensor_->isInFront())
        search(!side, secondDelay, speed);

    return irSensor_->isObjectDetected();
}

Point ObjectFinder::getLastPosition()
{
    return positionManager_.getLastPosition();
}

void ObjectFinder::sendLastPosition()
{
    debug::send("x", positionManager_.getLastPosition().x);
    debug::send("y", positionManager_.getLastPosition().y);
}

Border ObjectFinder::getBorder()
{
    Point position = positionManager_.getLastPosition();
    Border border = Border::MIDDLE;

    switch (position.x) {
        case 0 :
            border |= Border::LEFT;
            break;

        case Map::N_COLUMNS - 1 :
            border |= Border::RIGHT;
            break;
    }

    switch (position.y) {
        case 0 :
            border |= Border::BOTTOM;
            break;

        case Column::N_SLOTS - 1 :
            border |= Border::TOP;
            break;
    }

    return border;
}

void ObjectFinder::turnFind(const Wheels::Side &side)
{
    Wheels::turn(side);
    positionManager_.updateQuadrant(side);

    if (!isObjectInFront(side)) {
        find(side);
    }

    _delay_ms(constants::DELAY_AFTER_FIND_MS);
}

void ObjectFinder::findTurn(const Wheels::Side &side)
{
    find(side);

    if (!irSensor_->isObjectDetected()) {
        Wheels::turn(side);
        positionManager_.updateQuadrant(side);
    }
}

void ObjectFinder::findLoop(const uint8_t nTurns, const Wheels::Side &side)
{
    for (uint8_t i = 0; i < nTurns; i++) {
        if (irSensor_->isObjectDetected()) {
            break;
        }

        find(side, constants::DELAY_FIND_MS
                       + (i * constants::DELAY_INCREMENT_FIND_LOOP_MS));
        _delay_ms(constants::DELAY_BETWEEN_FINDS_MS);
    }
}
