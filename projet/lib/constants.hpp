/**
 * Constants for the project
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date April 17, 2023
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <avr/io.h>
#include <util/delay.h>

#include <lib/io.hpp>

namespace constants {
    // Constants unique to the robot
    // Used by ObjectFinder
    static constexpr double FIRST_DELAY_IS_IN_FRONT_MS = 0.9;
    static constexpr double SECOND_DELAY_IS_IN_FRONT_MS = 0.7;  // 1.75
    static constexpr double FIRST_DELAY_IN_FRONT_PARK_MS = 1.0; // 1.5
    static constexpr double SECOND_DELAY_IN_FRONT_PARK_MS = 1.3;
    static constexpr double DELAY_FIND_MS = 3.0;
    static constexpr uint8_t SPEED_VALUE_TO_PARK = 45;
    static constexpr uint8_t SPEED_TURN = 35;
    static constexpr uint8_t SPEED_PARK = 35;
    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    static constexpr uint16_t DELAY_TURNOFF_MS = 125;

    // Used by wheels
    static constexpr uint16_t TURN_DURATION_MS = 2500;
    static constexpr uint8_t TURN_TIMEOUT_MS = 125;

    // Constants for the project
    static constexpr uint8_t HIGH_NOTE = 78;
    static constexpr uint8_t LOW_NOTE = 45;
    const io::Position SENSOR = PA0;

    // Used by detect
    static constexpr uint16_t DELAY_FOUND_NOTHING_MS = 2000;
    static constexpr uint16_t DELAY_ALERT_PARKED_MS = 300;
    const uint8_t DELAY_LED_AMBER_MS = 20;

    // Constants for the IrSensor
    static const uint8_t EIGHTY_CM = 15;
    static const uint16_t TEN_CM = 120;
    static const uint8_t FIFTEEN_CM = 80;
    static const uint8_t EDGE_CLOSE_FAR = 45;
    static const uint8_t LIMIT_OBJECT_CLOSE = 30;
}; // namespace constants
#endif