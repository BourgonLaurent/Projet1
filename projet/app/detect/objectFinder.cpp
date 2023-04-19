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

#include <app/detect/constants.hpp>
#include <app/detect/objectFinder.hpp>
#include <app/misc/map/map.hpp>

#include <lib/debug.hpp>
#include <lib/interruptTimer.hpp>

bool ObjectFinder::timeOut_ = false;

void ObjectFinder::handleTimer()
{
    timeOut_ = true;
}

ObjectFinder::ObjectFinder(IrSensor &irSensor) : irSensor_(&irSensor){};

void ObjectFinder::park(const Wheels::Side &side)
{
    isObjectInFront(!side, constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                    constants::SECOND_DELAY_IN_FRONT_PARK_MS,
                    constants::SPEED_PARK);

    while (!irSensor_->isClose()) {
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

void ObjectFinder::find(const Wheels::Side &side, double timerLimit)
{
    if (!irSensor_->isInFront()) {

        if (side == Wheels::Side::LEFT) {
            positionManager_.updateQuadrant(side);
        }

        search(side, timerLimit);

        if (irSensor_->isObjectDetected()) {
            irSensor_->setRange(IrSensor::Range::DIAGONAL);
            debug::send("\nDIAGONAL\n");
        }
        else if (isObjectInFront(side)) {
            if (side != Wheels::Side::LEFT) {
                positionManager_.updateQuadrant(side);
            }
            irSensor_->setRange(IrSensor::Range::STRAIGHT);
            debug::send("STRAIGHT\n");
        }
        else if (side != Wheels::Side::LEFT) { // FIXME: why left?
            positionManager_.updateQuadrant(side);
        }

        interrupts::stopCatching();
    }
    if (irSensor_->isObjectDetected())
        park(side);
}

void ObjectFinder::search(const Wheels::Side &side, const double timerLimit,
                          const uint8_t speed)
{
    timeOut_ = false;
    InterruptTimer::setSeconds(timerLimit);
    InterruptTimer::start();
    interrupts::startCatching();

    Wheels::rotate(side, speed);

    while (!irSensor_->isInFront() && !timeOut_) {}

    irSensor_->isInFront();

    Wheels::stopRotating(side);
    InterruptTimer::stop();
    interrupts::stopCatching();
}

void ObjectFinder::turnFind(const Wheels::Side &side)
{
    Wheels::turn(side);
    positionManager_.updateQuadrant(side);
    if (!isObjectInFront(side))
        find(side);
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

void ObjectFinder::findLoop(const uint8_t maximum, const Wheels::Side &side)
{
    uint8_t loopCount = 0;
    while (!irSensor_->isObjectDetected() && loopCount < maximum) {
        loopCount++;
        find(side,
             constants::DELAY_FIND_MS
                 + (loopCount
                    * constants::DELAY_INCREMENT_FIND_LOOP)); // à tester
        _delay_ms(constants::DELAY_BETWEEN_FINDS_MS);
    }
}

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
            turnFind(border == Border::LEFT ? Wheels::Side::RIGHT
                                            : Wheels::Side::LEFT);
            break;

        case Border::BOTTOM_RIGHT :
        case Border::BOTTOM_LEFT :
            find(border == Border::LEFT ? Wheels::Side::RIGHT
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
        IrSensor::Distance distance = irSensor_->getDistance();

        positionManager_.setNextPositionObject(range, distance);
    }
}

Border ObjectFinder::getBorder()
{
    auto position = positionManager_.getLastPosition();
    auto cardinal = Border::MIDDLE;

    switch (position.x) {
        case 0 :
            cardinal |= Border::LEFT;
            break;
        case Map::N_COLUMNS - 1 :
            cardinal |= Border::RIGHT;
            break;
    }

    switch (position.y) {
        case 0 :
            cardinal |= Border::BOTTOM;
            break;
        case Column::N_SLOTS - 1 :
            cardinal |= Border::TOP;
            break;
    }

    return cardinal;
}

bool ObjectFinder::isObjectFound()
{
    return objectFound_;
}

// FIXME: to remove
void ObjectFinder::sendLastPosition()
{
    debug::send("\n");
    debug::send(positionManager_.getLastPosition().x);
    debug::send("\n");
    debug::send(positionManager_.getLastPosition().y);
    debug::send("\n");
}

bool ObjectFinder::isObjectInFront(const Wheels::Side &side,
                                   const uint8_t firstDelay,
                                   const uint8_t secondDelay,
                                   const uint8_t speed)
{
    debug::send("Checking in front\n");

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
