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
 * Implements the following state table
 *
 *
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |     CurrentState    | InterruptButton | WhiteButton |    ObjectFound   |
 * NextState      |           Output          |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |    SET_DIRECTION    |        1        |      0      |         X        | UP
 * |                           |
 * +---------------------+-----------------+-------------+------------------+---------------------+
 * | |    SET_DIRECTION    |        0        |      1      |         X        |
 * RIGHT        |                           |
 * +---------------------+-----------------+-------------+------------------+---------------------+
 * Led AMBER         | |    SET_DIRECTION    |        1        |      1      |
 * X        |    SET_DIRECTION    |                           |
 * +---------------------+-----------------+-------------+------------------+---------------------+
 * | |    SET_DIRECTION    |        0        |      0      |         X        |
 * SET_DIRECTION    |                           |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |         UP          |        X        |      X      |         X        |
 * FIND_OBJECT     |      Led GREEN for 2s     |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |        RIGHT        |        X        |      X      |         X        |
 * FIND_OBJECT     |       Led RED for 2s      |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |     FIND_OBJECT     |        X        |      X      |     SEARCHING    |
 * FIND_OBJECT     |             X             |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |     FIND_OBJECT     |        X        |      X      |   OBJECT_FOUND   |
 * WAIT_NEXT_DETECTION | Three high-pitched sounds |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |     FIND_OBJECT     |        X        |      X      | OBJECT_NOT_FOUND |
 * FOUND_NOTHING    |     Low-pitched sound     |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * | WAIT_NEXT_DETECTION |        0        |      X      |         X        |
 * WAIT_NEXT_DETECTION |                           |
 * +---------------------+-----------------+-------------+------------------+---------------------+
 * Led flashes AMBER     | | WAIT_NEXT_DETECTION |        1        |      X | X
 * |    SET_DIRECTION    |                           |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 * |    FOUND_NOTHING    |        X        |      X      |         X        |
 * FOUND_NOTHING    |      Led flashes RED      |
 * +---------------------+-----------------+-------------+------------------+---------------------+---------------------------+
 *
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
#include <lib/positionManager.hpp>
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
    SET_DIRECTION,
    RIGHT,
    UP,
    FIND_OBJECT,
    WAIT_NEXT_DETECTION,
    FOUND_NOTHING

};
volatile States state = States::SET_DIRECTION;

ISR(InterruptTimer_vect)
{
    Wheels::stopTurn(Wheels::Side::RIGHT);
    return;
}
ISR(InterruptButton_vect)
{
    InterruptButton::waitForDebounce();
    Communication::send("isr ");
    state = States::FIND_OBJECT;
    InterruptButton::clear();
}

int main()
{

    Wheels::initialize();
    Sound::initialize();
    // InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 4.0);
    Communication::initialize();
    Wheels::initialize();
    InterruptButton::initialize(InterruptButton::Mode::ANY);
    IrSensor irSensor(SENSOR);
    ObjectFinder finder(led, irSensor);

    // finder.find(Wheels::Side::RIGHT);
    // finder.park();

    while (true) {
        switch (state) {
            case States::SET_DIRECTION :
                while (button.isPressed() && !interruptButton.isPressed()) {
                    Communication::send("setDirection ");
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
                Communication::send("right  ");
                led.setColor(Led::Color::RED);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                Wheels::turn90(Wheels::Side::LEFT);
                state = States::FIND_OBJECT;
                break;
            case States::UP :
                Communication::send("left ");
                led.setColor(Led::Color::GREEN);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                state = States::FIND_OBJECT;
                break;
            case States::FIND_OBJECT :
                Communication::send("find ");
                finder.find(Wheels::Side::RIGHT);
                if (irSensor.objectFound() == true) {
                    finder.park();
                    state = States::WAIT_NEXT_DETECTION;
                }
                else {
                    state = States::FOUND_NOTHING;
                }
                break;
            case States::WAIT_NEXT_DETECTION :
                Communication::send("wait ");
                finder.alertParked();
                led.setAmberForMs(250);
                _delay_ms(250);
                break;
            case States::FOUND_NOTHING :
                Communication::send("nothing ");
                MapManager::save(finder.map);
                interrupts::startCatching();
                finder.alertParked();
                led.setColor(Led::Color::RED);
                _delay_ms(250);
                led.setColor(Led::Color::OFF);
                _delay_ms(250);
                break;
        }
    }
}