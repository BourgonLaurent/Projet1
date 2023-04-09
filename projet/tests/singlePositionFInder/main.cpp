#include <avr/io.h>
#include <util/delay.h>

#include <lib/button.hpp>
#include <lib/debug.hpp>
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/led.hpp>
#include <lib/objectFinder.hpp>
#include <lib/sound.hpp>
#include <lib/wheels.hpp>

#include <app/misc/map/mapManager.hpp>

const uint16_t DELAY_BEFORE_SEARCHING_MS = 2000;
const uint8_t DELAY_LED_AMBER_MS = 20;
const io::Position SENSOR = PA0;

enum class States
{
    SET_DIRECTION,
    RIGHT,
    FROM_RIGH_UP,
    UP,
    FIND_OBJECT,
    FOUND_NOTHING,
    FOUND_OBJECT,
    WAIT_NEXT_DETECTION

};
volatile States state = States::SET_DIRECTION;
volatile bool first = true;

ISR(InterruptTimer_vect)
{
    if (first)
        first = !first;
    else
        ObjectFinder::timeOut = true;
    debug::send("timerIsr\n");
}

ISR(InterruptButton_vect)
{
    debug::send("intIsr\n");
    InterruptButton::waitForDebounce();
    state = States::FIND_OBJECT;
    InterruptButton::clear();
}

int main()
{
    interrupts::stopCatching();

    debug::initialize();
    Wheels::initialize();
    Sound::initialize();
    Communication::initialize();

    InterruptButton::initialize(InterruptButton::Mode::ANY);

    Led led = Led(&DDRB, &PORTB, PB0, PB1);
    Button whiteButton(&DDRC, &PINC, PC2);
    Button interruptButton(&DDRD, &PIND, PD2);
    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 3.0);

    Map map;
    IrSensor irSensor(SENSOR);
    ObjectFinder finder(led, irSensor, map);

    finder.setLastPosition();

    while (true) {
        switch (state) {
            case States::SET_DIRECTION :
                led.setAmberForMs(DELAY_LED_AMBER_MS);
                // setAmberForMs bloquantte

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
                Wheels::turn90(Wheels::Side::LEFT); // replace turn90 with rotate?
                state = States::FIND_OBJECT;
                break;

            case States::UP :
                led.setColor(Led::Color::GREEN);
                _delay_ms(2000);
                led.setColor(Led::Color::OFF);
                state = States::FIND_OBJECT;
                break;

            case States::FIND_OBJECT :
                debug::send("Find object from position: \n");
                finder.sendLastPosition();
                led.setColor(Led::Color::OFF);
                InterruptButton::clear();
                // interrupts::startCatching();
                // InterruptTimer::reset();
                finder.finder();
                debug::send("New position: \n");
                finder.sendLastPosition();
                debug::send("back\n");
                // InterruptTimer::stop();
                // interrupts::stopCatching();

                if (finder.isObjectFound()) {
                    debug::send("ObjectFound-Parking\n");
                    finder.park();
                    state = States::FOUND_OBJECT;
                }
                else {
                    state = States::FOUND_NOTHING;
                }
                break;

            case States::FOUND_OBJECT :
                debug::send("parked, in FOUND_OBJECT");
                finder.alertParked();
                state = States::WAIT_NEXT_DETECTION;
                break;

            case States::WAIT_NEXT_DETECTION :
                debug::send("Done\n");
                interrupts::startCatching();
                led.setAmberForMs(250);
                _delay_ms(250);
                break;

            case States::FOUND_NOTHING :
                Communication::send("nothing ");
                MapManager::save(map);
                // InterruptButton::clear();
                finder.alertFoundNothing();
                while (true) {
                    led.setColor(Led::Color::RED);
                    _delay_ms(250);
                    led.setColor(Led::Color::OFF);
                    _delay_ms(250);
                }
                return 0;
                break;
        }
    }
}