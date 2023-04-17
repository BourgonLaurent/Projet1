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
 * \date April 17, 2023
 */

#include <lib/detect.hpp>

void detect::initialize()
{
    debug::initialize();
    Wheels::initialize();
    Sound::initialize();
    Communication::initialize();
    InterruptButton::initialize(InterruptButton::Mode::ANY);
    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 2.0);
}
void detect::checkTimerValue()
{
    if (OCR1A < TCNT1)
        detect::timeOut = true;
}

int detect::run()
{
    initialize();
    interrupts::stopCatching();
    while (true) {
        switch (state) {
            case States::SET_DIRECTION :
                led.setAmberForMs(constants::DELAY_LED_AMBER_MS);

                if (!whiteButton.isPressed())
                    state = States::RIGHT;
                else if (interruptButton.isPressed())
                    state = States::UP;

                break;

            case States::RIGHT :
                led.setColor(Led::Color::RED);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                state = States::FROM_RIGH_UP;
                break;

            case States::FROM_RIGH_UP :
                Wheels::turn90(Wheels::Side::LEFT);
                finder.isObjectInFront(timeOut, Wheels::Side::RIGHT);
                state = States::FIND_OBJECT;
                break;

            case States::UP :
                led.setColor(Led::Color::GREEN);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                state = States::FIND_OBJECT;
                break;

            case States::FIND_OBJECT :
                debug::send("Find object from position: \n"); // à enlever
                finder.sendLastPosition();                    // à enlever
                led.setColor(Led::Color::OFF);
                InterruptButton::clear();
                finder.finder(timeOut);
                debug::send("New position: \n"); // à enlever
                finder.sendLastPosition();       // à enlever

                if (finder.isObjectFound()) {
                    state = States::FOUND_OBJECT;
                }
                else {
                    state = States::FOUND_NOTHING;
                }
                break;

            case States::FOUND_OBJECT :
                finder.alertParked();
                state = States::WAIT_NEXT_DETECTION;
                break;

            case States::WAIT_NEXT_DETECTION :
                interrupts::startCatching();
                led.setAmberForMs(250);
                _delay_ms(250);
                break;

            case States::FOUND_NOTHING :
                MapManager::save(map);
                finder.alertFoundNothing();
                while (true) {
                    led.setColor(Led::Color::RED); // fonction pour flash ??
                    _delay_ms(250);
                    led.setColor(Led::Color::OFF);
                    _delay_ms(250);
                }
                return 0;
                break;
        }
    }
}