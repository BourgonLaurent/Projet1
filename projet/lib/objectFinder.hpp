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

#ifndef OBJECT_FINDER_H
#define OBJECT_FINDER_H

#include "lib/analogReader.hpp"
#include <lib/positionManager.hpp>

#include <avr/io.h>
#include <util/delay.h>

#include <lib/constants.hpp>
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

    ObjectFinder(Led &led, IrSensor &irSensor);

    void finder(volatile bool &timeOut);

    void search(const Wheels::Side &side, volatile bool &timeOut,
                double timerLimit, uint8_t speed = constants::SPEED_TURN);
    void park(volatile bool &timeOut, const Wheels::Side &side);
    void find(const Wheels::Side &side, volatile bool &timeOut,
              double timerLimit = constants::DELAY_FIND_MS);

    void alertParked();
    void alertFoundNothing();
    void initialize();
    bool isObjectFound();
    void sendLastPosition();

    bool isObjectInFront(volatile bool &timeOut,
                         Wheels::Side side = Wheels::Side::RIGHT,
                         double delay1 = constants::FIRST_DELAY_IS_IN_FRONT_MS,
                         double delay2 = constants::SECOND_DELAY_IS_IN_FRONT_MS,
                         uint8_t speed = constants::SPEED_TURN);

    Point getLastPosition();

private:
    Led led_;
    PositionManager positionManager_;

    bool objectFound_ = false;

    FinderType determineFinderType();

    void turnFind(const Wheels::Side &side, volatile bool &timeOut);
    void findTurn(const Wheels::Side &side, volatile bool &timeOut);
    void findLoop(uint8_t max, const Wheels::Side &side,
                  volatile bool &timeOut);
};

#endif
