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

Point PositionManager::getLastPosition()
{
    return lastPosition_;
}

void PositionManager::setNextPositionObject(const IrSensor::Range &range,
                                            const IrSensor::Distance &distance)
{
    switch (range) {
        case IrSensor::Range::DIAGONAL :
            switch (distance) {
                case IrSensor::Distance::CLOSE :
                    setPositionDiagonal(DIFFERENCE_WITH_NEW_POSITION_CLOSE,
                                        quadrant_);
                    break;
                case IrSensor::Distance::FAR :
                    setPositionDiagonal(DIFFERENCE_WITH_NEW_POSITION_FAR,
                                        quadrant_);
                    break;
            }
            break;

        case IrSensor::Range::STRAIGHT :
            switch (distance) {
                case IrSensor::Distance::CLOSE :
                    setPositionStraight(DIFFERENCE_WITH_NEW_POSITION_CLOSE,
                                        quadrant_);
                    break;
                case IrSensor::Distance::FAR :
                    setPositionStraight(DIFFERENCE_WITH_NEW_POSITION_FAR,
                                        quadrant_);
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

    debug::send("Quadrant", quadrant_);
}

void PositionManager::setPositionDiagonal(uint8_t difference, uint8_t quadrant)
{
    switch (quadrant) {
        case Quadrant::TOP_RIGHT :
            lastPosition_.x += difference;
            lastPosition_.y += difference;
            break;

        case Quadrant::BOTTOM_RIGHT :
            if (lastPosition_.y - difference == -1) {
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            }

            lastPosition_.x += difference;
            lastPosition_.y -= difference;
            break;

        case Quadrant::BOTTOM_LEFT :
            if (lastPosition_.y - difference == -1
                || lastPosition_.x - difference == -1) {
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            }

            lastPosition_.x -= difference;
            lastPosition_.y -= difference;
            break;

        case Quadrant::TOP_LEFT :
            if (lastPosition_.x - difference == -1) {
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            }

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
            if (lastPosition_.y - difference == -1) {
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            }

            lastPosition_.y -= difference;
            break;

        case Quadrant::TOP_LEFT :
            if (lastPosition_.y - difference == -1) {
                difference = DIFFERENCE_WITH_NEW_POSITION_CLOSE;
            }

            lastPosition_.x -= difference;
            break;
    }
}
