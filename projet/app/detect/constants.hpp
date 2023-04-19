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
#include <lib/irSensor.hpp>

namespace constants {
    // Used by detect
    static constexpr double DELAY_TURN_90_MS = 2.0;

    // Constants unique to the robot
    // Used by ObjectFinder
    static constexpr double FIRST_DELAY_IS_IN_FRONT_MS = 1.7;
    static constexpr double SECOND_DELAY_IS_IN_FRONT_MS = 1.0;  // 1.75
    static constexpr double FIRST_DELAY_IN_FRONT_PARK_MS = 1.5; // 1.5
    static constexpr double SECOND_DELAY_IN_FRONT_PARK_MS = 2.0;
    static constexpr double DELAY_FIND_MS = 3.25;
    static constexpr uint8_t SPEED_VALUE_TO_PARK = 45;
    static constexpr uint8_t SPEED_TURN = 40;
    static constexpr uint8_t SPEED_PARK = 40;
    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    static constexpr uint16_t DELAY_TURNOFF_MS = 125;
    static constexpr double DELAY_INCREMENT_FIND_LOOP = 0.5;
    static constexpr uint16_t DELAY_BETWEEN_FINDS_MS = 1500;
    static constexpr uint16_t DELAY_AFTER_FIND_MS = 1000;

    // Used by wheels
    static constexpr uint16_t TURN_DURATION_MS = 2250;
    static constexpr uint8_t TURN_TIMEOUT_MS = 125;
    static constexpr uint8_t SPEED_TURN_90 = 48;
    static constexpr uint8_t SPEED_DIFFERENCE_BETWEEN_WHEELS = 5;

    // Constants for the IrSensor
    static constexpr IrSensor::Calibration CALIBRATION = {
        .tenCm = 120,
        .fifteenCm = 90,
        .eightyCm = 20,
        .farThreshold = 45,
    };
}; // namespace constants

#endif
