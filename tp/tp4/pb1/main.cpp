/**
 * Problem 2:
 *  Cycles through LED colors based on a state table.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 *
 * Hardware Identification
 * INPUT: Push button connected to D2 with a jumper.
 * OUTPUT: Bicolor LED connected plus to A0 and minus to A1.
 *
 * Implements the following state table:
 *  Note: For the Button input:
 *      0: Released
 *      1: Pressed
 * +-----------------+--------+----------------+-------+
 * |  CURRENT STATE  | BUTTON |   NEXT STATE   |  LED  |
 * +=================+========+================+=======+
 * |                 |    0   |      INIT      |       |
 * |       INIT      +--------+----------------+  RED  +
 * |                 |    1   |   FIRST_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   |  FIRST_RELEASE |       |
 * |   FIRST_PRESS   +--------+----------------+ AMBER +
 * |                 |    1   |   FIRST_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   |  FIRST_RELEASE |       |
 * |  FIRST_RELEASE  +--------+----------------+ GREEN +
 * |                 |    1   |  SECOND_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   | SECOND_RELEASE |       |
 * |   SECOND_PRESS  +--------+----------------+  RED  +
 * |                 |    1   |  SECOND_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   | SECOND_RELEASE |       |
 * |  SECOND_RELEASE +--------+----------------+  OFF  +
 * |                 |    1   |   THIRD_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   |      INIT      |       |
 * |   THIRD_PRESS   +--------+----------------+ GREEN +
 * |                 |    1   |   THIRD_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 */

#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/colors.hpp>
#include <tp2/components/led.hpp>

#include <tp4/components/interruptButton.hpp>
#include <tp4/components/interrupts.hpp>

constexpr uint8_t AMBER_DELAY_MS = 10;
constexpr uint8_t DEBOUNCE_DELAY_MS = 10;

enum class MachineState
{
    INIT,
    FIRST_PRESS,
    FIRST_RELEASE,
    SECOND_PRESS,
    SECOND_RELEASE,
    THIRD_PRESS
};

volatile MachineState currentState = MachineState::INIT;

void InterruptButton::whenPressed()
{
    switch (::currentState) {
        case MachineState::INIT :
            ::currentState = MachineState::FIRST_PRESS;
            break;

        case MachineState::FIRST_PRESS :
            ::currentState = MachineState::FIRST_RELEASE;
            break;

        case MachineState::FIRST_RELEASE :
            ::currentState = MachineState::SECOND_PRESS;
            break;

        case MachineState::SECOND_PRESS :
            ::currentState = MachineState::SECOND_RELEASE;
            break;

        case MachineState::SECOND_RELEASE :
            ::currentState = MachineState::THIRD_PRESS;
            break;

        case MachineState::THIRD_PRESS :
            ::currentState = MachineState::INIT;
            break;
    }
}

int main()
{
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    InterruptButton::initialize();
    InterruptButton::setMode(InterruptButton::Mode::ANY);

    InterruptButton::start();
    while (true) {
        switch (::currentState) {
            case MachineState::INIT :
                led.setColor(Color::RED);
                break;

            case MachineState::FIRST_PRESS :
                led.setColor(Color::RED);
                _delay_ms(AMBER_DELAY_MS);
                led.setColor(Color::GREEN);
                _delay_ms(AMBER_DELAY_MS);
                break;

            case MachineState::FIRST_RELEASE :
                led.setColor(Color::GREEN);
                break;

            case MachineState::SECOND_PRESS :
                led.setColor(Color::RED);
                break;

            case MachineState::SECOND_RELEASE :
                led.setColor(Color::OFF);
                break;

            case MachineState::THIRD_PRESS :
                led.setColor(Color::GREEN);
                break;
        }
    }

    return 0;
}
