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
#include <app/detect/detect.hpp>
#include <app/detect/objectFinder.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>

volatile bool Detect::timeOut_ = false;
volatile bool Detect::interruptButtonWasPressed_ = false;

void Detect::handleButtonPress()
{
    interruptButtonWasPressed_ = true;
}

void Detect::handleTimer()
{
    timeOut_ = true;
}

void Detect::initialize()
{
    Wheels::initialize();
    Sound::initialize();
    InterruptButton::initialize(InterruptButton::Mode::RISING);
    InterruptTimer::initialize(InterruptTimer::Mode::CLEAR_ON_COMPARE,
                               constants::DELAY_TURN_90_MS);
}

void Detect::run(Led &led, Button &whiteButton, Button &interruptButton,
                 IrSensor &irSensor)
{
    initialize();
    interrupts::stopCatching();

    Map map;
    ObjectFinder finder(irSensor);

    bool whiteWasPressed = false;
    bool interruptWasPressed = false;

    Flasher::initializeAmber(led);
    Flasher::startFlashing();

    while (interruptWasPressed = interruptButton.isPressed(),
           whiteWasPressed = whiteButton.isPressed(),
           !interruptWasPressed && !whiteWasPressed) {}

    Flasher::stopFlashing();

    led.setColor(whiteWasPressed ? Led::Color::RED : Led::Color::GREEN);
    _delay_ms(INITIALIZATION_DELAY_MS);
    led.setColor(Led::Color::OFF);

    if (whiteWasPressed) {
        Wheels::turn90(Wheels::Side::LEFT);
        finder.isObjectInFront(timeOut_, Wheels::Side::RIGHT);
    }

    while (true) {
        // TODO: remove
        debug::send("Find object from position: \n");
        finder.sendLastPosition();

        led.setColor(Led::Color::OFF);
        finder.finder(timeOut_);

        // TODO: remove
        debug::send("New position: \n");
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

    // TODO: check if it doesn't cause a segfault
    Flasher::initialize(led, END_FLASH_FREQUENCY, Led::Color::RED,
                        Led::Color::OFF);
    Flasher::startFlashing();

    while (true) {}
}
