#include <avr/io.h>
#include <util/delay.h>

#include <lib/button.hpp>
#include <lib/debug.hpp>
#include <lib/communication.hpp>
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

ISR(InterruptTimer_vect)
{
    debug::send("timerIsr\n");
    debug::send(TCNT1);
    debug::send("\n");
    ObjectFinder::timeOut = true;
    // Wheels::stopTurn(Wheels::Side::RIGHT);
    // ISR too long ?
    return;
}

int main()
{
    interrupts::stopCatching();

    Communication::initialize();
    Wheels::initialize();
    Sound::initialize();
    debug::initialize();

    InterruptTimer::initialize(InterruptTimer::Mode::NORMAL, 3.0);
    
    debug::send(TCNT1);
    debug::send("\n");  


    Led led = Led(&DDRB, &PORTB, PB0, PB1);

    Map map;
    IrSensor irSensor(SENSOR);
    ObjectFinder finder(led, irSensor, map);

    debug::send(TCNT1);
    debug::send("\n");

    finder.park();
}