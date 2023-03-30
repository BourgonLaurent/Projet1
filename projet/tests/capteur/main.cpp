/**
 * Read infra red sensor values.
 *
 * Hardware Identification
 * OUTPUT:
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 16, 2023
 */

#include <avr/io.h>
#include <util/delay.h>

#include <lib/button.hpp>
#include <lib/communication.hpp>
#include <lib/debug.hpp>
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/led.hpp>
#include <lib/objectFinder.hpp>
#include <lib/sound.hpp>
#include <lib/wheels.hpp>

volatile bool gFinishedSearching = 0;
Led led = Led(&DDRB, &PORTB, PB0, PB1);

// Global variables to remove
Button button(&DDRA, &PINA, PA1);
Button interruptButton(&DDRD, &PIND, PD2);
const io::Position SENSOR = PA6;

enum class States
{
    SET_MODE,
    SET_DIRECTION,
    RIGHT,
    UP,
    FIND_OBJECT,
    WAIT_NEXT_DETECTION,
    FOUND_NOTHING

};
volatile States state = States::SET_MODE;

ISR(InterruptTimer_vect)
{
    Wheels::stopTurn(Wheels::Side::RIGHT);
    return;
}
ISR(InterruptButton_vect)
{
    InterruptButton::waitForDebounce();
    // if (state == States::SET_DIRECTION) {
    //     led.setColor(Led::Color::OFF);
    //     state = States::UP;
    // }
    // else {
    state = States::FIND_OBJECT;
    // }

    InterruptButton::clear();
}

int main()
{

    Wheels::initialize();
    Sound::initialize();
    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 4.0);
    Communication::initialize();
    Wheels::initialize();
    InterruptButton::initialize(InterruptButton::Mode::ANY);
    IrSensor irSensor(SENSOR);
    ObjectFinder finder(led, irSensor);

    while (true) {
        switch (state) {
            case States::SET_MODE :
                led.setColor(Led::Color::OFF);
                state = States::SET_DIRECTION;
                break;
            case States::SET_DIRECTION :
                while (button.isPressed() && !interruptButton.isPressed()) {
                    led.setAmberForMs(100);
                    if (!button.isPressed()) {
                        state = States::RIGHT;
                    }
                    else if (interruptButton.isPressed()) {
                        state = States::UP;
                    }
                }

                break;
            case States::RIGHT :
                led.setColor(Led::Color::RED);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                Wheels::turn90(Wheels::Side::LEFT);
                state = States::FIND_OBJECT;
                break;
            case States::UP :
                led.setColor(Led::Color::GREEN);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                state = States::FIND_OBJECT;
                break;
            case States::FIND_OBJECT :
                finder.find();
                finder.park();
                state = States::WAIT_NEXT_DETECTION;
                break;
            case States::WAIT_NEXT_DETECTION :
                finder.alertParked();
                led.setAmberForMs(250);
                _delay_ms(250);
                break;
            case States::FOUND_NOTHING :
                interrupts::startCatching();
                finder.alertParked();
                led.setColor(Led::Color::RED);
                _delay_ms(250);
                led.setColor(Led::Color::OFF);
                _delay_ms(250);
                state = States::SET_MODE;
                break;
        }
    }
}