/**
 * Management of current position and next position.
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
 * \date April 5, 2023
 */

#include <lib/positionManager.hpp>

PositionManager::PositionManager(IrSensor &irSensor, Map &map)
    : irSensor(irSensor), map_(map){};

void PositionManager::setPositionDiagonal(uint8_t difference, uint8_t quadrant)
{
    switch (quadrant) {
        case Quadrant::TOP_RIGHT :
            lastPosition_.x += difference;
            lastPosition_.y += difference;
            break;
        case Quadrant::BOTTOM_RIGHT :
            lastPosition_.x += difference;
            lastPosition_.y -= difference;
            break;
        case Quadrant::BOTTOM_LEFT :
            lastPosition_.x -= difference;
            lastPosition_.y -= difference;
            break;
        case Quadrant::TOP_LEFT :
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
            lastPosition_.y -= difference;
            break;
        case Quadrant::TOP_LEFT :
            lastPosition_.x -= difference;
            break;
    }
}

void PositionManager::setPositionObject(uint8_t quadrant)
{
    irSensor.detectRange(irSensor.detect());
    IrSensor::Range range = irSensor.range();
    switch (range) {
        case IrSensor::Range::DIAGONAL_CLOSE :
            setPositionDiagonal(1, quadrant);
            break;
        case IrSensor::Range::DIAGONAL_FAR :
            setPositionDiagonal(2, quadrant);
            break;
        case IrSensor::Range::STRAIGHT_ANGLE_CLOSE :
            setPositionStraight(1, quadrant);
            break;
        case IrSensor::Range::STRAIGHT_ANGLE_FAR :
            setPositionStraight(2, quadrant);
            break;
    }
    map_[lastPosition_.x][lastPosition_.y].set();
}
Point PositionManager::lastPosition()
{
    return lastPosition_;
}
