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

#include "detect.hpp"

#include <util/delay.h>

#include <lib/debug.hpp>
#include <lib/flasher.hpp>
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/irSensor.hpp>
#include <lib/sound.hpp>
#include <lib/wheels.hpp>

#include <app/detect/alerts.hpp>
#include <app/detect/objectFinder.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>

volatile bool Detect::interruptButtonWasPressed_ = false;

void Detect::handleButtonPress()
{
    interruptButtonWasPressed_ = true;
}

void Detect::initialize()
{
    Wheels::initialize();
    Sound::initialize();
    InterruptButton::initialize(InterruptButton::Mode::RISING);
    InterruptTimer::initialize(InterruptTimer::Mode::CLEAR_ON_COMPARE,
                               constants::REPOSITION_DELAY_MS);
    interrupts::stopCatching();
}

void Detect::run(Led &led, Button &whiteButton, Button &interruptButton,
                 IrSensor &irSensor)
{
    initialize();

    Map map;
    ObjectFinder finder(irSensor);

    Flasher::initializeAmber(led);
    Flasher::start();

    bool pointingUp = false;
    bool pointingRight = false;

    while (pointingUp = interruptButton.isPressed(),
           pointingRight = whiteButton.isPressed(),
           !pointingUp && !pointingRight) {}

    Flasher::stop();

    led.setColor(pointingRight ? Led::Color::RED : Led::Color::GREEN);
    _delay_ms(INITIALIZATION_DELAY_MS);
    led.setColor(Led::Color::OFF);

    if (pointingRight) {
        Wheels::turn(Wheels::Side::LEFT);
        finder.isObjectInFront(Wheels::Side::RIGHT);
    }

    while (true) {
        debug::send("Find object from position:\n");
        finder.sendLastPosition();

        led.setColor(Led::Color::OFF);
        finder.run();

        debug::send("New position:\n");
        finder.sendLastPosition();

        if (!finder.isObjectFound()) {
            break;
        }

        alerts::parked::play();

        Point detectedPosition = finder.getLastPosition();

        if (detectedPosition.x <= Map::N_COLUMNS - 1
            && detectedPosition.y <= Column::N_SLOTS - 1) {
            map[detectedPosition.x][detectedPosition.y].set();
        }

        interruptButtonWasPressed_ = false;
        InterruptButton::clear();
        interrupts::startCatching();
        while (!interruptButtonWasPressed_) {
            led.setAmberForMs(AMBER_FLASH_PERIOD_MS);
            _delay_ms(AMBER_FLASH_PERIOD_MS);
        }
        interrupts::stopCatching();
    }

    MapManager::save(map);
    alerts::notFound::play();

    Flasher::initialize(led, END_FLASH_FREQUENCY, Led::Color::RED,
                        Led::Color::OFF);
    Flasher::start();

    while (true) {}
}
