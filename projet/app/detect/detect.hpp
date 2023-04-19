/**
 * Detect program of the project
 *
 * HARDWARE:
 * IR sensor to PA0
 * Led to PB0(+) and PB1(-) // à vérifier
 * InterruptButton to PD2
 * White Button to PC2
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date May 17, 2023
 */

#ifndef DETECT_H
#define DETECT_H

#include <avr/io.h>

#include <app/misc/map/map.hpp>
#include <lib/button.hpp>
#include <lib/interruptButton.hpp>
#include <lib/irSensor.hpp>
#include <lib/led.hpp>

class Detect
{
public:
    static void handleButtonPress();
    static void run(Led &led, Button &whiteButton, Button &interruptButton,
                    IrSensor &irSensor);

private:
    static constexpr uint16_t INITIALIZATION_DELAY_MS = 2000;
    static constexpr uint8_t AMBER_FLASH_PERIOD_MS = 250;
    static constexpr uint8_t END_FLASH_FREQUENCY = 2;

    static void initialize();

    static volatile bool interruptButtonWasPressed_;
    static volatile bool timeOut_;
};

#endif
