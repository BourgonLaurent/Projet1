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

#include <avr/io.h>
#include <util/delay.h>

#include <lib/analogReader.hpp>
#include <lib/io.hpp>
#include <lib/wheels.hpp>

#include <app/detect/border.hpp>
#include <app/detect/constants.hpp>
#include <app/detect/positionManager.hpp>

class ObjectFinder
{
public:
    ObjectFinder(IrSensor &irSensor);

    void run();

    void search(const Wheels::Side &side, double timerLimit,
                uint8_t speed = constants::SPEED_TURN);
    void park(const Wheels::Side &side);
    void find(const Wheels::Side &side,
              double timerLimit = constants::DELAY_FIND_MS);

    bool isObjectFound();
    void sendLastPosition();

    bool isObjectInFront(
        const Wheels::Side &side = Wheels::Side::RIGHT,
        const uint8_t firstDelay = constants::FIRST_DELAY_IS_IN_FRONT_MS,
        const uint8_t secondDelay = constants::SECOND_DELAY_IS_IN_FRONT_MS,
        const uint8_t speed = constants::SPEED_TURN);

    Point getLastPosition();

    static void handleTimer();

private:
    static constexpr uint8_t N_PARK_SOUNDS = 3;
    static constexpr uint8_t PARK_NOTE = 78;
    static constexpr uint16_t PARK_SOUND_PERIOD_MS = 300;
    static constexpr uint16_t END_NOTE = 45;
    static constexpr uint16_t END_SOUND_PERIOD_MS = 2000;

    Border getBorder();

    void turnFind(const Wheels::Side &side);
    void findTurn(const Wheels::Side &side);
    void findLoop(uint8_t max, const Wheels::Side &side);

    static bool timeOut_;

    PositionManager positionManager_;
    IrSensor* const irSensor_;

    bool objectFound_ = false;
};

#endif
