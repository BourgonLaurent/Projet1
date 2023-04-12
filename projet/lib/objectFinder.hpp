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
                double timerLimit);
    void park(volatile bool &timeOut);
    void find(const Wheels::Side &side, volatile bool &timeOut,
              double timerLimit = 3.5, bool isObjectPresent = false);

    void alertParked();
    void alertFoundNothing();
    void initialize();
    bool isObjectFound();
    void sendLastPosition();

    bool isObjectForward(volatile bool &timeOut,
                         Wheels::Side side = Wheels::Side::RIGHT);

private:
    const io::Position SENSOR = PA0;

    static constexpr uint16_t DELAY_FOUND_NOTHING_MS = 2000;
    static constexpr uint16_t DELAY_ALERT_PARKED_MS = 300;
    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    static constexpr uint16_t DELAY_TURNOFF_MS = 125; // changed from 500

    static constexpr uint8_t SPEED_VALUE_TO_PARK = 40;

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
