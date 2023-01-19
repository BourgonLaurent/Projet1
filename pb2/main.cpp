/**
 * Problem 2:
 *  Cycles through LED colors based on a state table.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 *
 * Hardware Identification
 * INPUT: Switch button connected to D2 with a jumper.
 * OUTPUT: Bicolor LED to A0 + A1.
 *
 * Implements the following state table:
 *
 * +-----------------+----+----------------+-------+
 * |  Current State  | D2 |Next State      |   A   |
 * +=================+====+================+=======+
 * |                 |  0 |      INIT      |       |
 * |       INIT      +----+----------------+  RED  +
 * |                 |  1 |   FIRST_PRESS  |       |
 * +-----------------+----+----------------+-------+
 * |                 |  0 |  FIRST_RELEASE |       |
 * |   FIRST_PRESS   +----+----------------+ AMBER +
 * |                 |  1 |   FIRST_PRESS  |       |
 * +-----------------+----+----------------+-------+
 * |                 |  0 |  FIRST_RELEASE |       |
 * |  FIRST_RELEASE  +----+----------------+ GREEN +
 * |                 |  1 |  SECOND_PRESS  |       |
 * +-----------------+----+----------------+-------+
 * |                 |  0 | SECOND_RELEASE |       |
 * |   SECOND_PRESS  +----+----------------+  RED  +
 * |                 |  1 |  SECOND_PRESS  |       |
 * +-----------------+----+----------------+-------+
 * |                 |  0 | SECOND_RELEASE |       |
 * |  SECOND_RELEASE +----+----------------+  OFF  +
 * |                 |  1 |   THIRD_PRESS  |       |
 * +-----------------+----+----------------+-------+
 * |                 |  0 |      INIT      |       |
 * |   THIRD_PRESS   +----+----------------+ GREEN +
 * |                 |  1 |  SECOND_PRESS  |       |
 * +-----------------+----+----------------+-------+
 */

#define F_CPU 8000000 // CPU clock frequency, used by <util/delay.h>
#include <avr/io.h>
#include <util/delay.h>

#include "colors.hpp"
#include "button.hpp"

constexpr int AMBER_DELAY_MS = 10;

enum class MachineState
{
    INIT,
    FIRST_PRESS,
    FIRST_RELEASE,
    SECOND_PRESS,
    SECOND_RELEASE,
    THIRD_PRESS
};

int main()
{
    DDRA |= _BV(DDA0) | _BV(DDA1);
    DDRD &= ~_BV(DDD2);

    MachineState currentState = MachineState::INIT;

    while (true)
    {
        switch (currentState)
        {
        case MachineState::INIT:
            PORTA = (uint8_t)Color::RED;

            if (Button::isPressed())
            {
                currentState = MachineState::FIRST_PRESS;
            }
            break;

        case MachineState::FIRST_PRESS:
            PORTA = (uint8_t)Color::RED;
            _delay_ms(AMBER_DELAY_MS);
            PORTA = (uint8_t)Color::GREEN;

            if (!Button::isPressed())
            {
                currentState = MachineState::FIRST_RELEASE;
            }
            break;

        case MachineState::FIRST_RELEASE:
            PORTA = (uint8_t)Color::GREEN;
            if (Button::isPressed())
            {
                currentState = MachineState::SECOND_PRESS;
            }
            break;

        case MachineState::SECOND_PRESS:
            PORTA = (uint8_t)Color::RED;
            if (!Button::isPressed())
            {
                currentState = MachineState::SECOND_RELEASE;
            }
            break;

        case MachineState::SECOND_RELEASE:
            PORTA = (uint8_t)Color::OFF;
            if (Button::isPressed())
            {
                currentState = MachineState::THIRD_PRESS;
            }
            break;

        case MachineState::THIRD_PRESS:
            PORTA = (uint8_t)Color::GREEN;
            if (!Button::isPressed())
            {
                currentState = MachineState::INIT;
            }
            break;
        }
    }

    return 0;
}
