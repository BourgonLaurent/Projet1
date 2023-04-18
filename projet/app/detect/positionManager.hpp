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

#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include <app/misc/map/map.hpp>
#include <app/misc/point.hpp>
#include <lib/wheels.hpp>

#include <lib/irSensor.hpp>

class PositionManager
{
public:
    enum Quadrant
    {
        TOP_RIGHT = 0,
        BOTTOM_RIGHT = 1,
        BOTTOM_LEFT = 2,
        TOP_LEFT = 3
    };

    PositionManager(IrSensor &irSensor);

    Point getLastPosition();

    void setNextPositionObject(uint8_t quadrant);
    void initialize();
    uint8_t getQuadrant();

    void resetQuadrant();
    void updateQuadrant(const Wheels::Side &side);

    Point getNexPosition();

    IrSensor irSensor;

private:
    Point lastPosition_;
    uint8_t quadrant_;

    void setPositionDiagonal(uint8_t difference, uint8_t quadrant);
    void setPositionStraight(uint8_t difference, uint8_t quadrant);
};

#endif
