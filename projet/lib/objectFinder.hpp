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

    ObjectFinder(Led &led, IrSensor &irSensor, Map &map);

    void finder(volatile bool &timeOut);

    void search(const Wheels::Side &side, volatile bool &timeOut,
                double timerLimit, uint8_t speed = speedTurn);
    void park(volatile bool &timeOut,const Wheels::Side& side);
    void find(const Wheels::Side &side, volatile bool &timeOut,
              double timerLimit = DELAY_FIND_MS);

    void alertParked();
    void alertFoundNothing();
    void initialize();
    bool isObjectFound();
    void sendLastPosition();

    bool isObjectInFront(volatile bool &timeOut,
                         Wheels::Side side = Wheels::Side::RIGHT,
                         double delay1 = FIRST_DELAY_IS_IN_FRONT_MS,
                         double delay2 = SECOND_DELAY_IS_IN_FRONT_MS,
                         uint8_t speed = speedTurn);

private:
    const io::Position SENSOR = PA0;

    static constexpr uint16_t DELAY_FOUND_NOTHING_MS = 2000;
    static constexpr uint16_t DELAY_ALERT_PARKED_MS = 300;
    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    static constexpr uint16_t DELAY_TURNOFF_MS = 125; // changed from 500
    static constexpr double FIRST_DELAY_IS_IN_FRONT_MS = 0.9;
    static constexpr double SECOND_DELAY_IS_IN_FRONT_MS = 0.7; // 1.75
    static constexpr double FIRST_DELAY_IN_FRONT_PARK_MS = 1.0; // 1.5
    static constexpr double SECOND_DELAY_IN_FRONT_PARK_MS = 1.3;
    static constexpr double DELAY_FIND_MS = 2.2;
    static constexpr uint8_t SPEED_VALUE_TO_PARK = 35;
    static constexpr uint8_t speedTurn = 43;
    static constexpr uint8_t speedPark = 45;
    static constexpr uint8_t HIGH_NOTE = 78;
    static constexpr uint8_t LOW_NOTE = 45;

    Led led_;
    PositionManager positionManager_;
    bool objectFound_ = false;

    FinderType determineFinderType();

    void turnFind(const Wheels::Side &side, volatile bool &timeOut);
    void findTurn(const Wheels::Side &side, volatile bool &timeOut);
    void findLoop(uint8_t max, const Wheels::Side &side,
                  volatile bool &timeOut);
};
