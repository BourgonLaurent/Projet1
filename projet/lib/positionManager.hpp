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
#include <lib/irSensor.hpp>

struct Point {
    uint8_t x = 0;
    uint8_t y = 0;
};

class PositionManager
{
public:
    PositionManager(IrSensor &irSensor);

    enum Quadrant
    {
        TOP_RIGHT = 0,
        BOTTOM_RIGHT = 1,
        BOTTOM_LEFT = 2,
        TOP_LEFT = 4

    };
    Map map;
    Point lastPosition();
    void setPositionObject(uint8_t quadrant);
    IrSensor irSensor;

private:
    Point lastPosition_;

    void setPositionDiagonal(uint8_t difference, uint8_t quadrant);
    void setPositionStraight(uint8_t difference, uint8_t quadrant);
};