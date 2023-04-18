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
    static constexpr double DELAY_INCREMENT_FIND_LOOP = 0.2;
    static constexpr uint16_t DELAY_BETWEEN_FINDS_MS = 1500;
    static constexpr uint16_t DELAY_AFTER_FIND_MS = 1000;

    // Used by wheels
    static constexpr uint16_t TURN_DURATION_MS = 2500;
    static constexpr uint8_t TURN_TIMEOUT_MS = 125;
    static constexpr uint8_t SPEED_TURN_90 = 48;
    static constexpr uint8_t SPEED_DIFFERENCE_BETWEEN_WHEELS = 5;

    // Constants for the project
    static constexpr uint8_t HIGH_NOTE = 78;
    static constexpr uint8_t LOW_NOTE = 45;
    static constexpr io::Position SENSOR = PA0;

    // Used by detect
    static constexpr uint16_t DELAY_FOUND_NOTHING_MS = 2000;
    static constexpr uint16_t DELAY_ALERT_PARKED_MS = 300;
    static constexpr uint8_t DELAY_LED_AMBER_MS = 20;
    static constexpr double DELAY_TURN_90_MS = 2.0;
    static constexpr uint8_t DELAY_LED_AMBER_2HZ_MS = 250;

    // Constants for the IrSensor
    static constexpr uint8_t EIGHTY_CM = 15;
    static constexpr uint16_t TEN_CM = 120;
    static constexpr uint8_t FIFTEEN_CM = 80;
    static constexpr uint8_t EDGE_CLOSE_FAR = 45;
    static constexpr uint8_t LIMIT_OBJECT_CLOSE = 30;
    static constexpr uint8_t DELAY_READ_VALUE_SENSOR_MS = 5;

    // Constants PositionManager
    static constexpr uint8_t DIFFERENCE_WITH_NEW_POSITION_FAR = 2;
    static constexpr uint8_t DIFFERENCE_WITH_NEW_POSITION_CLOSE = 1;
}; // namespace constants

#endif