/**
 * Main program for the detect module.
 *  Find poles and save them in memory.
 *
 * Hardware Identification:
 *  NOTE: The data direction registers are set automatically.
 *
 *  INPUT:
 *    - IR Sensor
 *    - Interrupt Push Button
 *    - White Push Button
 *
 *  OUTPUT:
 *    - Bicolor LED
 *    - Wheels
 *      - Left
 *      - Right
 *    - Buzzer
 *
 *  EEPROM:
 *    - SCL (PC0)
 *    - SDA (PC1)
 *
 *  USART:
 *    - RXD0 (PD0)
 *    - TXD0 (PD1)
 *
 *  TIMERS:
 *    - Timer 0 | Sound
 *    - Timer 1 | InterruptTimer & Flasher
 *    - Timer 2 | Wheels
 *
 * USAGE:
 *  Detect::run(led, white, interrupt, irSensor);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date May 15, 2023
 */

#ifndef DETECT_H
#define DETECT_H

#include <avr/io.h>

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
};

#endif
