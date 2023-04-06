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

const uint16_t DELAY_BEFORE_SEARCHING_MS = 2000;
const uint8_t DELAY_LED_AMBER_MS = 20;
const io::Position SENSOR = PA0;

enum class States
{
    SET_MODE,
    TRANSMISSION,
    SET_DIRECTION,
    RIGHT,
    FROM_RIGH_UP,
    UP,
    FIND_OBJECT,
    FOUND_NOTHING,
    FOUND_OBJECT,
    WAIT_NEXT_DETECTION

};
volatile States state = States::SET_MODE;

ISR(InterruptTimer_vect)
{
    debug::send("timerIsr\n");
    InterruptTimer::stop();
    interrupts::stopCatching();
    Wheels::stopTurn(Wheels::Side::RIGHT);
    //ISR too long ?
    return;
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

    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 4.0);
    InterruptButton::initialize(InterruptButton::Mode::ANY);


    Led led = Led(&DDRB, &PORTB, PB0, PB1);
    Button whiteButton(&DDRC, &PINC, PC2);
    Button interruptButton(&DDRD, &PIND, PD2);

    IrSensor irSensor(SENSOR);
    ObjectFinder finder(led, irSensor);

    while (true) {
        switch (state) {
            case States::SET_MODE :
                debug::send("setMode\n");
                led.setColor(Led::Color::OFF);

                if (!whiteButton.isPressed())
                    state = States::TRANSMISSION;
                if (interruptButton.isPressed())
                    state = States::SET_DIRECTION;

                while (!whiteButton.isPressed() || interruptButton.isPressed())
                    ;

                break;

            case States::TRANSMISSION :
                led.setColor(Led::Color::OFF);
                debug::send("transmission\n");
                break;

            case States::SET_DIRECTION :
                debug::send("setDirection\n");
                led.setAmberForMs(DELAY_LED_AMBER_MS);
                // setAmberForMs bloquantte

                if (!whiteButton.isPressed())
                    state = States::RIGHT;
                else if (interruptButton.isPressed())
                    state = States::UP;

                break;

            case States::RIGHT :
                debug::send("right\n");
                led.setColor(Led::Color::RED);
                _delay_ms(DELAY_BEFORE_SEARCHING_MS);
                state = States::FROM_RIGH_UP;
                break;

            case States::UP :
                debug::send("up\n");
                led.setColor(Led::Color::GREEN);
                _delay_ms(DELAY_BEFORE_SEARCHING_MS);
                state = States::FIND_OBJECT;
                break;

            case States::FROM_RIGH_UP :
                debug::send("fromRightUp\n");
                led.setColor(Led::Color::OFF);
                Wheels::turn90(
                    Wheels::Side::LEFT); // replace turn90 with rotate?
                state = States::FIND_OBJECT;
                break;

            case States::FIND_OBJECT :
                debug::send("findObject\n");
                interrupts::stopCatching();

                led.setColor(Led::Color::OFF);

                finder.find(Wheels::Side::RIGHT);
                debug::send("back");

                InterruptTimer::stop();
                interrupts::stopCatching();
                Wheels::stopTurn(Wheels::Side::RIGHT);

                if (finder.isObjectFound()) 
                {
                    finder.park();
                    state = States::FOUND_OBJECT;
                }
                else
                {
                    state = States::FOUND_NOTHING;
                }

                break;

            case States::FOUND_OBJECT :
                debug::send("parked");
                finder.alertParked();
                state = States::WAIT_NEXT_DETECTION;
                break;

            case States::FOUND_NOTHING :
                finder.alertFoundNothing();
                break;

            case States::WAIT_NEXT_DETECTION :
                debug::send("Done\n");
                interrupts::startCatching();
                led.setAmberForMs(250);
                _delay_ms(250);
                break;
        }
    }
}