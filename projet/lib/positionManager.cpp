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

#include <lib/debug.hpp>
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

void PositionManager::setNextPositionObject(uint8_t quadrant)
// La prochaine position dépend du quadrant et du Range qui est déterminé à
// chaque read de irSensor
{
    IrSensor::Range range = irSensor.range();
    IrSensor::Distance distance = irSensor.getDistance();
    
    switch(range){
        case IrSensor::Range::DIAGONAL:
            switch (distance)
            {
                case IrSensor::Distance::CLOSE:
                    debug::send("range/DIAGONAL_CLOSE");
                    setPositionDiagonal(1, quadrant);
                    break;
                case IrSensor::Distance::FAR:
                    setPositionDiagonal(2, quadrant);
                    break;
            }
            break;
        case IrSensor::Range::STRAIGHT :
            switch (distance)
            {
                case IrSensor::Distance::CLOSE:
                    setPositionStraight(1, quadrant);
                    break;
                case IrSensor::Distance::FAR:
                    setPositionStraight(2, quadrant);
                    break;
            }
            break;
    }
    map_[lastPosition_.x][lastPosition_.y].set();
}

Point PositionManager::lastPosition()
{
    return lastPosition_;
}

void PositionManager::updateQuadrant(const Wheels::Side &side)
{
    if (side == Wheels::Side::RIGHT) {
        if (quadrant_ == 3)
            quadrant_ = 0;
        else
            quadrant_++;
    }
    else {
        if (quadrant_ == 0)
            quadrant_ = 3;
        else
            quadrant_--;
    }
}

void PositionManager::resetQuadrant()
{
    quadrant_ = 0;
}