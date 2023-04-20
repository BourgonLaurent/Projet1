/**
 * Constants used for the detection.
 * They change with the robot.
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date April 15, 2023
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <avr/io.h>

#include <lib/io.hpp>
#include <lib/irSensor.hpp>

namespace constants {
    static constexpr uint16_t REPOSITION_DELAY_MS = 1900;


    static constexpr uint16_t FIRST_DELAY_IS_IN_FRONT_MS = 800;
    static constexpr uint16_t SECOND_DELAY_IS_IN_FRONT_MS = 850;

    static constexpr uint16_t FIRST_DELAY_IN_FRONT_PARK_MS = 1500;
    static constexpr uint16_t SECOND_DELAY_IN_FRONT_PARK_MS = 3000;

    static constexpr uint16_t DELAY_FIND_MS = 1750;

    static constexpr uint8_t SPEED_VALUE_TO_PARK = 45;
    static constexpr uint8_t CLOSE_FAR_THRESHOLD = 45;

    static constexpr uint8_t SPEED_TURN = 50;
    static constexpr uint8_t SPEED_PARK = 40;

    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    
    static constexpr uint16_t DELAY_TURNOFF_MS = 125;
    static constexpr uint16_t DELAY_INCREMENT_FIND_LOOP_MS = 160;

    static constexpr uint16_t DELAY_BETWEEN_FINDS_MS = 1500;
    static constexpr uint16_t DELAY_AFTER_FIND_MS = 1000;

    static constexpr IrSensor::Calibration CALIBRATION = {
        .tenCm = 120,
        .fifteenCm = 90,
        .eightyCm = 17,
    };
}; // namespace constants

#endif
