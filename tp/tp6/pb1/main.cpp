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
#include <tp5/components/usart.hpp>
#define F_CPU 8000000UL
#include <util/delay.h>

enum class MachineState
{
    READY,
    PRESSED,
    RELEASED,
};

volatile MachineState currentState = MachineState::READY;
volatile uint8_t counter = 0;

constexpr uint8_t DURATION_S = 1;
constexpr uint8_t RELEAED_DURATION_NS = 50;

constexpr uint8_t WAIT_DURATION_S = 2;

constexpr uint8_t FLASH_DURATION_MS = 20;
constexpr uint8_t FLASH_PERIOD_S = 1;
constexpr uint8_t N_FLASH = 2;
constexpr uint8_t N_END_FLASH = 1;
constexpr uint16_t FLASH_DELAY_MS =
    (FLASH_PERIOD_S * 1000 - N_FLASH * FLASH_DURATION_MS)
    / (N_FLASH + N_END_FLASH);

void InterruptButton::whenPressed()
{
    switch (::currentState) {
        case MachineState::READY :
            ::currentState = MachineState::PRESSED;
            ::counter = 0;
            InterruptTimer::start();
            break;

        case MachineState::PRESSED :
            ::currentState = MachineState::RELEASED;
            break;
        default :
            break;
    }
}

void InterruptTimer::whenFinished()
{
    ::counter += 10;
    Usart::transmit(counter);
}

int main()
{
    Usart::initialize();

    LED led = LED(&DDRB, &PORTB, DDD1, DDD0);
    interrupts::stopCatching();

    InterruptButton::initialize();
    InterruptButton::setMode(InterruptButton::Mode::ANY);

    InterruptTimer::initialize();
    InterruptTimer::setMode(InterruptTimer::Mode::CTC);
    InterruptTimer::setPrescaleMode(InterruptTimer::PrescaleMode::CLK1024);
    InterruptTimer::setSeconds(DURATION_S);

    while (true) {
        switch (::currentState) {
            case MachineState::READY :
                led.setColor(Color::OFF);
                interrupts::startCatching();
                InterruptButton::start();
                break;

            case MachineState::PRESSED :
                Usart::transmit(::counter);
                led.setColor(Color::OFF);

                if (::counter == 120) {
                    Usart::transmit(0xFF);
                    InterruptTimer::stop();
                    interrupts::stopCatching();
                    ::currentState = MachineState::RELEASED;
                }
                break;

            case MachineState::RELEASED :
                interrupts::stopCatching();
                InterruptTimer::stop();

                led.setColor(Color::GREEN);
                _delay_ms(RELEAED_DURATION_NS * 10);
                led.setColor(Color::OFF);

                led.setColor(Color::OFF);
                _delay_ms(WAIT_DURATION_S * 1000);

                for (uint8_t i = 0; i < (counter / 4); i++) {
                    for (uint8_t j = 0; j < N_FLASH; j++) {
                        _delay_ms(FLASH_DELAY_MS);
                        led.setColor(Color::RED);
                        _delay_ms(FLASH_DURATION_MS);
                        led.setColor(Color::OFF);
                    }

                    _delay_ms(FLASH_DELAY_MS);
                }

                led.setColor(Color::GREEN);
                _delay_ms(1000);
                ::currentState = MachineState::READY;
                break;
        }
    }

    interrupts::stopCatching();

    return 0;
}