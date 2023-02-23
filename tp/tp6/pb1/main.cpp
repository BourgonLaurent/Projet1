/**
 * Problem 1:
 *  Control external LED with a counter.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 14, 2023
 *
 * Hardware Identification
 * INPUT: Push button connected to D2. Pushed sets at 0.
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
 * ║    RELEASED   ║    x   ║    x    ║      WAIT      ║   X   ║
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

enum class MachineState
{
    READY,
    PRESSED,
    RELEASED,
};

volatile MachineState machineState = MachineState::READY;
volatile uint8_t counter = 0;

constexpr double COUNTER_INCREMENT_S = 0.100;
constexpr uint8_t COUNTER_DIVISOR = 2;
constexpr uint8_t MAX_COUNTER = 120;

namespace delay {
    constexpr uint16_t RELEASED_MS = 500;
    constexpr uint16_t WAIT_MS = 2000;
    constexpr uint16_t END_MS = 500;

    namespace flash {
        constexpr uint8_t N_FLASH = 2;
        constexpr uint8_t DURATION_MS = 20;
        constexpr uint16_t PERIOD_MS = 1000;
        constexpr uint8_t INBETWEEN_MS = 250;

        // Time left in the period after the flash delays
        constexpr uint16_t PERIOD_REMAINDER_MS =
            PERIOD_MS - N_FLASH * DURATION_MS - INBETWEEN_MS;
    } // namespace flash
} // namespace delay

void InterruptButton::whenPressed()
{
    switch (::machineState) {
        case MachineState::READY :
            ::counter = 0;
            InterruptTimer::start();

            ::machineState = MachineState::PRESSED;
            break;

        case MachineState::PRESSED :
            ::machineState = MachineState::RELEASED;
            break;

        default :
            break;
    }
}

void InterruptTimer::whenFinished()
{
    ::counter++;
}

int main()
{
    LED led = LED(&DDRB, &PORTB, PB0, PB1);
    interrupts::stopCatching();

    InterruptButton::initialize();
    InterruptButton::setMode(InterruptButton::Mode::ANY);

    InterruptTimer::initialize();
    InterruptTimer::setMode(InterruptTimer::Mode::CTC);
    InterruptTimer::setPrescaleMode(InterruptTimer::PrescaleMode::CLK1024);
    InterruptTimer::setSeconds(COUNTER_INCREMENT_S);

    while (true) {
        switch (::machineState) {
            case MachineState::READY :
                led.setColor(Color::OFF);

                interrupts::startCatching();
                InterruptButton::start();
                break;

            case MachineState::PRESSED :
                led.setColor(Color::OFF);

                if (::counter == MAX_COUNTER) {
                    ::machineState = MachineState::RELEASED;
                }

                break;

            case MachineState::RELEASED :
                InterruptTimer::stop();
                InterruptButton::stop();
                interrupts::stopCatching();

                led.setColor(Color::GREEN);
                _delay_ms(delay::RELEASED_MS);
                led.setColor(Color::OFF);

                _delay_ms(delay::WAIT_MS);

                bool flashedInsidePeriod = false;
                for (uint8_t i = 0; i < ::counter / COUNTER_DIVISOR; i++) {
                    if (flashedInsidePeriod) {
                        _delay_ms(delay::flash::INBETWEEN_MS);
                    }

                    led.setColor(Color::RED);
                    _delay_ms(delay::flash::DURATION_MS);
                    led.setColor(Color::OFF);

                    if (flashedInsidePeriod) {
                        _delay_ms(delay::flash::PERIOD_REMAINDER_MS);
                        flashedInsidePeriod = false;
                    }
                    else {
                        flashedInsidePeriod = true;
                    }
                }

                _delay_ms(delay::END_MS);
                led.setColor(Color::GREEN);
                _delay_ms(delay::END_MS);

                ::machineState = MachineState::READY;
                break;
        }
    }

    return 0;
}
