#include <tp2/components/led.hpp>
#include <tp4/components/interruptButton.hpp>
#include <tp4/components/interrupts.hpp>

#include <util/delay.h>

enum class MachineState
{
    READY,
    PRESSED,
    PRESS_REACTION,
    WAIT,
    FLASH,
    STEADY
};

volatile MachineState currentState = MachineState::READY;

int main()
{
    LED led = LED(&DDRB, &PORTB, DDD1, DDD0);
    interrupts::stopCatching();

    InterruptButton::initialize();
    InterruptButton::setMode(InterruptButton::Mode::FALLING);

    interrupts::startCatching();
    InterruptButton::start();

    return 0;
}