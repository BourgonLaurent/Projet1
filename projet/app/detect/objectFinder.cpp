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
    isObjectInFront(!side,
                    {constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                     constants::SECOND_DELAY_IN_FRONT_PARK_MS},
                    constants::SPEED_PARK);

    while (!irSensor_->isClose()) {
        Wheels::setSpeed(constants::SPEED_VALUE_TO_PARK);

        while (irSensor_->isTooClose()) {
            Wheels::setDirection(Wheels::Direction::BACKWARD);
        }

        Wheels::setDirection(Wheels::Direction::FORWARD);

        if (!irSensor_->isInFront()) {
            isObjectInFront(Wheels::Side::LEFT,
                            {constants::FIRST_DELAY_IN_FRONT_PARK_MS,
                             constants::SECOND_DELAY_IN_FRONT_PARK_MS},
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

void ObjectFinder::search(const Wheels::Side &side, double timerLimit,
                          uint8_t speed)
{
    InterruptTimer::setSeconds(timerLimit);
    timeOut_ = false;
    InterruptTimer::start();
    interrupts::startCatching();

    Wheels::turn(side, speed);

    while (!irSensor_->isInFront() && !timeOut_) {}
    // _delay_ms(200);
    irSensor_->isInFront();
    Wheels::stopTurn(side);
    InterruptTimer::stop();
    interrupts::stopCatching();
}

void ObjectFinder::turnFind(const Wheels::Side &side)
{
    Wheels::turn90(side);
    positionManager_.updateQuadrant(side);
    if (!isObjectInFront(side))
        find(side);
    _delay_ms(constants::DELAY_AFTER_FIND_MS);
}

void ObjectFinder::findTurn(const Wheels::Side &side)
{
    find(side);
    if (!irSensor_->isObjectDetected()) {
        Wheels::turn90(side);
        positionManager_.updateQuadrant(side);
    }
}

void ObjectFinder::findLoop(uint8_t max, const Wheels::Side &side)
{
    uint8_t loopCount = 0;
    while (!irSensor_->isObjectDetected() && loopCount < max) {
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

    auto finderWithPosition = getBorder();
    positionManager_.resetQuadrant();

    irSensor_->setRange(IrSensor::Range::STRAIGHT);

    switch (finderWithPosition) {
        case Border::TOP :
            debug::send("TOP_BORDER\n");
            Wheels::turn90(Wheels::Side::RIGHT);
            positionManager_.updateQuadrant(Wheels::Side::RIGHT);
            if (!isObjectInFront(Wheels::Side::RIGHT))
                findLoop(2, Wheels::Side::RIGHT);
            break;

        case Border::BOTTOM :
            debug::send("BOTTOM_BORDER\n");
            findTurn(Wheels::Side::RIGHT);
            if (!irSensor_->isObjectDetected()) {
                turnFind(Wheels::Side::RIGHT);
            }
            break;

        case Border::MIDDLE :
            debug::send("MIDDLE\n");
            findLoop(4, Wheels::Side::RIGHT);
            break;

        case Border::TOP_LEFT :
            debug::send("TOP_CORNER_LEFT\n");
            turnFind(Wheels::Side::RIGHT);
            break;

        case Border::TOP_RIGHT :
            debug::send("TOP_CORNER_RIGHT\n");
            turnFind(Wheels::Side::LEFT);
            break;

        case Border::BOTTOM_RIGHT :
            debug::send("BOTTOM_CORNER_RIGHT\n");
            if (!isObjectInFront(Wheels::Side::RIGHT))
                find(Wheels::Side::LEFT);
            break;

        case Border::BOTTOM_LEFT :
            debug::send("BOTTOM_CORNER_LEFT\n");
            find(Wheels::Side::RIGHT);
            break;

        case Border::RIGHT :
            debug::send("RIGHT_BORDER\n");
            findLoop(2, Wheels::Side::LEFT);
            break;

        case Border::LEFT :
            debug::send("LEFT_BORDER\n");
            findLoop(2, Wheels::Side::RIGHT);

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

bool ObjectFinder::isObjectInFront(Wheels::Side side, const Delay &delay,
                                   uint8_t speed)
{
    debug::send("Checking in front\n");

    if (!irSensor_->isInFront())
        search(side, delay.first, speed);

    if (!irSensor_->isInFront())
        search(!side, delay.second, speed);

    return irSensor_->isObjectDetected();
}

Point ObjectFinder::getLastPosition()
{
    return positionManager_.getLastPosition();
}
