/**
 * Finds object.
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
 * \date March 28, 2023
 */

#include "lib/analogReader.hpp"
#include <lib/positionManager.hpp>

#include <avr/io.h>
#include <util/delay.h>

#include <lib/io.hpp>

#include <lib/led.hpp>
#include <lib/wheels.hpp>

class ObjectFinder
{
public:
    ObjectFinder(Led &led, IrSensor &irSensor, Map &map);

    enum class FinderType
    {
        TOP_BORDER,
        MIDDLE,
        BOTTOM_BORDER,
        RIGHT_BORDER,
        LEFT_BORDER,
        TOP_CORNER_RIGHT,
        TOP_CORNER_LEFT,
        BOTTOM_CORNER_RIGHT,
        BOTTOM_CORNER_LEFT
    };

    void park();
    void find(const Wheels::Side &side, double timerLimit = 3.0);
    void alertParked();
    void alertFoundNothing();
    void finder();
    bool isObjectFound();
    void sendLastPosition();

private:
    const io::Position SENSOR = PA6;
    static constexpr uint16_t DELAY_FOUND_NOTHING_MS = 2000;
    static constexpr uint16_t DELAY_ALERT_PARKED_MS = 300;
    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    static constexpr uint8_t HIGH_NOTE = 78;
    static constexpr uint8_t LOW_NOTE = 45;
    static constexpr uint16_t DELAY_TURNOFF_MS = 500;
    void turnFind(const Wheels::Side &side);
    void findTurn(const Wheels::Side &side);
    void findLoop(uint8_t &quadrant, uint8_t max, const Wheels::Side &side);
    FinderType determineFinderType();
    Led led_;
    PositionManager positionManager_;
    bool objectFound_ = false;
};
