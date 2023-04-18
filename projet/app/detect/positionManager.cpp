/**
 * Management of current position and next position.
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
 * \date April 5, 2023
 */

#include <app/detect/positionManager.hpp>
#include <lib/debug.hpp>

PositionManager::PositionManager(IrSensor &irSensor) : irSensor(irSensor){};

Point PositionManager::getLastPosition()
{
    return lastPosition_;
}

void PositionManager::setNextPositionObject(uint8_t quadrant)
{
    // FIXME: violates SRP
    // FIXME: Remove irSensor from the class
    IrSensor::Range range = irSensor.getRange();
    IrSensor::Distance distance = irSensor.getDistance();
    debug::send("Dans SetNextPosition\n");
    switch (range) {
        case IrSensor::Range::DIAGONAL :
            switch (distance) {
                case IrSensor::Distance::CLOSE :
                    setPositionDiagonal(DIFFERENCE_WITH_NEW_POSITION_CLOSE,
                                        quadrant);
                    break;
                case IrSensor::Distance::FAR :
                    setPositionDiagonal(DIFFERENCE_WITH_NEW_POSITION_FAR,
                                        quadrant);
                    break;
            }
            break;
        case IrSensor::Range::STRAIGHT :
            switch (distance) {
                case IrSensor::Distance::CLOSE :
                    setPositionStraight(DIFFERENCE_WITH_NEW_POSITION_CLOSE,
                                        quadrant);
                    break;
                case IrSensor::Distance::FAR :
                    setPositionStraight(DIFFERENCE_WITH_NEW_POSITION_FAR,
                                        quadrant);
                    break;
            }
            break;
    }
}

uint8_t PositionManager::getQuadrant()
{
    return quadrant_;
}

void PositionManager::resetQuadrant()
{
    quadrant_ = 0;
}

void PositionManager::updateQuadrant(const Wheels::Side &side)
{
    quadrant_ += side == Wheels::Side::RIGHT ? 1 : -1;
    quadrant_ %= 4;

    debug::send("le quadrant est maintenant : ");
    debug::send(quadrant_);
    debug::send("\n");
}

void PositionManager::setPositionDiagonal(uint8_t difference, uint8_t quadrant)
{
    switch (quadrant) {
        case Quadrant::TOP_RIGHT :
            lastPosition_.x += difference;
            lastPosition_.y += difference;
            break;
        case Quadrant::BOTTOM_RIGHT :
            if (lastPosition_.y - difference == -1)
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x += difference;
            lastPosition_.y -= difference;
            break;
        case Quadrant::BOTTOM_LEFT :
            if (lastPosition_.y - difference == -1
                || lastPosition_.x - difference == -1)
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x -= difference;
            lastPosition_.y -= difference;
            break;
        case Quadrant::TOP_LEFT :
            if (lastPosition_.x - difference == -1)
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x -= difference;
            lastPosition_.y += difference;
            break;
    }
}
void PositionManager::setPositionStraight(uint8_t difference, uint8_t quadrant)
{
    switch (quadrant) {
        case Quadrant::TOP_RIGHT :
            lastPosition_.y += difference;
            break;
        case Quadrant::BOTTOM_RIGHT :
            lastPosition_.x += difference;
            break;
        case Quadrant::BOTTOM_LEFT :
            if (lastPosition_.y - difference == -1)
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.y -= difference;
            break;
        case Quadrant::TOP_LEFT :
            if (lastPosition_.y - difference == -1)
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x -= difference;
            break;
    }
}

// TODO: remove
void PositionManager::initialize() // à enlever???
{
    lastPosition_.x = 7;
    lastPosition_.y = 2;
}

Point PositionManager::getNexPosition()
{
    return lastPosition_;
}
