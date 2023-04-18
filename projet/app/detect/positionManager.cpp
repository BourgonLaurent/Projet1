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
    IrSensor::Range range = irSensor.getRange();
    IrSensor::Distance distance = irSensor.getDistance();
    debug::send("Dans SetNextPosition\n");
    switch (range) {
        case IrSensor::Range::DIAGONAL :
            switch (distance) {
                case IrSensor::Distance::CLOSE :
                    setPositionDiagonal(
                        constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE,
                        quadrant);
                    break;
                case IrSensor::Distance::FAR :
                    setPositionDiagonal(
                        constants::DIFFERENCE_WITH_NEW_POSITION_FAR, quadrant);
                    break;
            }
            break;
        case IrSensor::Range::STRAIGHT :
            switch (distance) {
                case IrSensor::Distance::CLOSE :
                    setPositionStraight(
                        constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE,
                        quadrant);
                    break;
                case IrSensor::Distance::FAR :
                    setPositionStraight(
                        constants::DIFFERENCE_WITH_NEW_POSITION_FAR, quadrant);
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
    if (side == Wheels::Side::RIGHT)
        quadrant_ = (quadrant_ == 3) ? 0 : quadrant_ + 1;

    else
        quadrant_ = (quadrant_ == 0) ? 3 : quadrant_ - 1;

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
                difference = constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x += difference;
            lastPosition_.y -= difference;
            break;
        case Quadrant::BOTTOM_LEFT :
            if (lastPosition_.y - difference == -1
                || lastPosition_.x - difference == -1)
                difference = constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x -= difference;
            lastPosition_.y -= difference;
            break;
        case Quadrant::TOP_LEFT :
            if (lastPosition_.x - difference == -1)
                difference = constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE;
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
                difference = constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.y -= difference;
            break;
        case Quadrant::TOP_LEFT :
            if (lastPosition_.y - difference == -1)
                difference = constants::DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            lastPosition_.x -= difference;
            break;
    }
}

void PositionManager::initialize() // à enlever???
{
    lastPosition_.x = 7;
    lastPosition_.y = 2;
}

Point PositionManager::getNexPosition()
{
    return lastPosition_;
}
