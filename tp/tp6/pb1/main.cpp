/**
 * Problem 1:
 *  Control external LED with a counter.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 14, 2023
 *
 * Hardware Identification
 * INPUT: Push button connected to D2 through the breadboard. Pushed returns 0.
 * OUTPUT: Bicolor LED connected plus to B0 and minus to B1.
 *
 * Implements the following state table:
 *  Note: For the Button input:
 *      0: Pressed
 *      1: Released
 * ╔═══════════════╦════════╦═════════╦═════════════╦════════════════╦═══════╗
 * ║ CURRENT STATE ║ BUTTON ║ COUNTER ║    TIMER    ║   NEXT STATE   ║  LED  ║
 * ╠═══════════════╬════════╬═════════╬═════════════╬════════════════╬═══════╣
 * ║               ║    1   ║    x    ║      x      ║      READY     ║       ║
 * ║     READY     ╠════════╬═════════╬═════════════╬════════════════╣  OFF  ║
 * ║               ║    0   ║    x    ║      x      ║     PRESSED    ║       ║
 * ╠═══════════════╬════════╬═════════╬═════════════╬════════════════╬═══════╣
 * ║               ║    1   ║    x    ║      x      ║ PRESS_REACTION ║       ║
 * ║               ╠════════╬═════════╬═════════════╬════════════════╣       ║
 * ║    PRESSED    ║    0   ║    x    ║      x      ║     PRESSED    ║  OFF  ║
 * ║               ╠════════╬═════════╬═════════════╬════════════════╣       ║
 * ║               ║    x   ║   120   ║      x      ║     PRESSED    ║       ║
 * ╠═══════════════╬════════╬═════════╬═════════════╬════════════════╬═══════╣
 * ║    RELEASED   ║    x   ║    x    ║     0.5s    ║      WAIT      ║ GREEN ║
 * ╠═══════════════╬════════╬═════════╬═════════════╬════════════════╬═══════╣
 * ║      WAIT     ║    x   ║    x    ║      2s     ║      FLASH     ║  OFF  ║
 * ╠═══════════════╬════════╬═════════╬═════════════╬════════════════╬═══════╣
 * ║     FLASH     ║    x   ║    x    ║ COUNTER/2 s ║     STEADY     ║  RED  ║
 * ╠═══════════════╬════════╬═════════╬═════════════╬════════════════╬═══════╣
 * ║     STEADY    ║    x   ║    x    ║      1s     ║      READY     ║ GREEN ║
 * ╚═══════════════╩════════╩═════════╩═════════════╩════════════════╩═══════╝
 */

#include <tp2/components/led.hpp>
#include <tp4/components/interruptButton.hpp>
#include <tp4/components/interruptTimer.hpp>
#include <tp4/components/interrupts.hpp>
#define F_CPU 8000000UL
#include <util/delay.h>

enum class MachineState
{
    READY,
    PRESSED,
    RELEASED,
    WAIT,
    FLASH,
    STEADY
};

volatile MachineState currentState = MachineState::READY;

void InterruptButton::whenPressed()
{
    switch (::currentState) {
        case MachineState::READY :
            currentState = MachineState::PRESSED;
            break;
        case MachineState::PRESSED :
            currentState = MachineState::RELEASED;
            break;
        default :
            break;
    }
}

void InterruptTimer::whenFinished()
{
    switch (::currentState) {
        case MachineState::PRESSED :
            currentState = MachineState::FLASH;
            break;
    }
}

constexpr uint8_t DURATION_S = 1;
volatile bool flashIsDone = false;

int main()
{
    LED led = LED(&DDRB, &PORTB, DDD1, DDD0);
    interrupts::stopCatching();

    InterruptButton::initialize();
    InterruptButton::setMode(InterruptButton::Mode::ANY);

    InterruptTimer::initialize();
    InterruptTimer::setMode(InterruptTimer::Mode::CTC);
    InterruptTimer::setPrescaleMode(InterruptTimer::PrescaleMode::CLK1024);
    InterruptTimer::setSeconds(DURATION_S);

    interrupts::startCatching();
    InterruptButton::start();

    while (true) {
        switch (::currentState) {
            case MachineState::READY :
                led.setColor(Color::OFF);
                break;
            case MachineState::PRESSED :
                led.setColor(Color::OFF);
                break;
            case MachineState::RELEASED :
                led.setColor(Color::GREEN);
                break;
            case MachineState::WAIT :
                led.setColor(Color::OFF);
                break;
            case MachineState::FLASH :
                InterruptTimer::start();
                led.setColor(Color::GREEN);
                led.setColor(Color::OFF);
                break;
            case MachineState::STEADY :
                led.setColor(Color::GREEN);
                break;
        }
    }

    return 0;
}