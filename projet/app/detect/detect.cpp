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
volatile bool Detect::buttonWasPressed_ = false;
Detect::States Detect::state_ = Detect::States::SET_DIRECTION;

void Detect::handleButtonPress()
{
    buttonWasPressed_ = true;
    interrupts::stopCatching();
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

int Detect::run(Led &led, Button &whiteButton, Button &interruptButton,
                IrSensor &irSensor)
{
    initialize();

    Map map;
    ObjectFinder finder(irSensor);

    interrupts::stopCatching();

    while (true) {
        switch (state_) {
            case States::SET_DIRECTION :
                led.setAmberForMs(AMBER_FLASH_PERIOD_MS);

                if (whiteButton.isPressed()) {
                    state_ = States::RIGHT;
                }
                else if (interruptButton.isPressed()) {
                    state_ = States::UP;
                }

                break;

            case States::RIGHT :
                led.setColor(Led::Color::RED);
                _delay_ms(INITIALIZATION_DELAY_MS);
                led.setColor(Led::Color::OFF);

                Wheels::turn90(Wheels::Side::LEFT);
                finder.isObjectInFront(timeOut_, Wheels::Side::RIGHT);

                state_ = States::FIND_OBJECT;
                break;

            case States::UP :
                led.setColor(Led::Color::GREEN);
                _delay_ms(INITIALIZATION_DELAY_MS);
                led.setColor(Led::Color::OFF);

                state_ = States::FIND_OBJECT;
                break;

            case States::FIND_OBJECT :
                debug::send("Find object from position: \n"); // à enlever
                finder.sendLastPosition();                    // à enlever

                led.setColor(Led::Color::OFF);
                InterruptButton::clear();
                finder.finder(timeOut_);

                debug::send("New position: \n"); // à enlever
                finder.sendLastPosition();       // à enlever

                state_ = finder.isObjectFound() ? States::FOUND_OBJECT
                                                : States::FOUND_NOTHING;
                break;

            case States::FOUND_OBJECT :
                alerts::parked::play();

                Point detectedPosition;
                detectedPosition = finder.getLastPosition();

                if (detectedPosition.x <= Map::N_COLUMNS - 1
                    && detectedPosition.y <= Column::N_SLOTS - 1) {
                    map[detectedPosition.x][detectedPosition.y].set();
                }

                state_ = States::WAIT_NEXT_DETECTION;
                break;

            case States::WAIT_NEXT_DETECTION :
                interrupts::startCatching();

                led.setAmberForMs(AMBER_FLASH_PERIOD_MS);
                _delay_ms(AMBER_FLASH_PERIOD_MS);

                if (buttonWasPressed_) {
                    state_ = States::FIND_OBJECT;
                    buttonWasPressed_ = false;
                }

                break;

            case States::FOUND_NOTHING :
                MapManager::save(map);

                alerts::notFound::play();

                // TODO: check if it doesn't cause a segfault
                Flasher::initialize(led, END_FLASH_FREQUENCY, Led::Color::RED,
                                    Led::Color::OFF);
                Flasher::startFlashing();
                while (true) {}

                break;
        }
    }
}
