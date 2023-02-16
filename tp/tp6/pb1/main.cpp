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
 *  -----------Note-----------
 *   For the Button input:
 *      0: Pressed
 *      1: Released
 *  --------------------------
 * ╔═══════════════╦════════╦═════════╦════════════════╦═══════╗
 * ║ CURRENT STATE ║ BUTTON ║ COUNTER ║   NEXT STATE   ║  LED  ║
 * ╠═══════════════╬════════╬═════════╬════════════════╬═══════╣
 * ║               ║    0   ║    x    ║     PRESSED    ║       ║
 * ║     READY     ╠════════╬═════════╬════════════════╣  OFF  ║
 * ║               ║    1   ║    x    ║      READY     ║       ║
 * ╠═══════════════╬════════╬═════════╬════════════════╬═══════╣
 * ║               ║    0   ║    x    ║     PRESSED    ║       ║
 * ║               ╠════════╬═════════╬════════════════╣       ║
 * ║    PRESSED    ║    1   ║    x    ║    RELEASED    ║  OFF  ║
 * ║               ╠════════╬═════════╬════════════════╣       ║
 * ║               ║    x   ║   120   ║    RELEASED    ║       ║
 * ╠═══════════════╬════════╬═════════╬════════════════╬═══════╣
 * ║    RELEASED   ║    x   ║    x    ║      WAIT      ║ GREEN ║
 * ╚═══════════════╩════════╩═════════╩════════════════╩═══════╝
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/io.hpp>
#include <tp2/components/led.hpp>
#include <tp4/components/interruptButton.hpp>
#include <tp4/components/interruptTimer.hpp>
#include <tp4/components/interrupts.hpp>
#include <tp5/components/usart.hpp>

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
            interrupts::stopCatching();
            InterruptTimer::stop();
            break;
        default :
            break;
    }
}

void InterruptTimer::whenFinished()
{
    ::counter += 10;
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
                led.setColor(Color::OFF);

                if (::counter == 120) {
                    Usart::transmit(0xFF);
                    InterruptTimer::stop();
                    interrupts::stopCatching();
                    ::currentState = MachineState::RELEASED;
                }
                break;

            case MachineState::RELEASED :
                Usart::transmit(::counter);

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

    return 0;
}
