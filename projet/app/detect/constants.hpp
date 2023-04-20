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
    static constexpr uint16_t DELAY_TURN_90_MS = 2500;

    // Constants unique to the robot
    // Used by ObjectFinder
    // le robot vérifie si le poteau est devant lui après avoir tourné
    static constexpr uint16_t FIRST_DELAY_IS_IN_FRONT_MS = 800;
    static constexpr uint16_t SECOND_DELAY_IS_IN_FRONT_MS = 1000; // 1.75

    // le robot cherche le poteau après l'avoir perdu de vue
    static constexpr uint16_t FIRST_DELAY_IN_FRONT_PARK_MS = 1500; // 1.5
    static constexpr uint16_t SECOND_DELAY_IN_FRONT_PARK_MS = 3000;

    // le robot cherche en le poteau en tourant
    static constexpr uint16_t DELAY_FIND_MS = 2000;

    // vitesse du robot quand il se dirige vers le poteau
    static constexpr uint8_t SPEED_VALUE_TO_PARK = 45;

    // vitesse du robot quand il tourne en charchant le poteau
    static constexpr uint8_t SPEED_TURN = 50;

    // vitesse du  robot quand il cherche le poteau après l'avoir perdu de vue
    static constexpr uint8_t SPEED_PARK = 40;

    static constexpr uint8_t DELAY_TURN_MIDDLE_OBJECT_MS = 100;
    static constexpr uint16_t DELAY_TURNOFF_MS = 125;
    static constexpr uint16_t DELAY_INCREMENT_FIND_LOOP_MS = 100;
    static constexpr uint16_t DELAY_BETWEEN_FINDS_MS = 1500;
    static constexpr uint16_t DELAY_AFTER_FIND_MS = 1000;

    // Constants for the IrSensor
    static constexpr IrSensor::Calibration CALIBRATION = {
        .tenCm = 120,
        .fifteenCm = 90,
        .eightyCm = 20,
        .farThreshold = 45,
    };
}; // namespace constants

#endif
