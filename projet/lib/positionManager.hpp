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

#include <app/misc/map/map.hpp>
#include <app/misc/point.hpp>

#include <lib/irSensor.hpp>

class PositionManager
{
public:
    PositionManager(IrSensor &irSensor, Map &map);

    enum Quadrant
    {
        TOP_RIGHT = 0,
        BOTTOM_RIGHT = 1,
        BOTTOM_LEFT = 2,
        TOP_LEFT = 4

    };
    Point lastPosition();
    void setPositionObject(uint8_t quadrant);
    IrSensor irSensor;

private:
    Point lastPosition_;
    Map map_;

    void setPositionDiagonal(uint8_t difference, uint8_t quadrant);
    void setPositionStraight(uint8_t difference, uint8_t quadrant);
};