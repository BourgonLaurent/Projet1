/**
 * Problem 2:
 *  Press three times the switch button to turn the LED green.
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
 * +---------------+----+--------------+-------+
 * | Current State | D2 |  Next State  |   A   |
 * +===============+====+==============+=======+
 * |               |  0 |     INIT     |  OFF  |
 * |      INIT     +----+--------------+-------+
 * |               |  1 |  FIRST_PRESS |  OFF  |
 * +---------------+----+--------------+-------+
 * |               |  0 |  FIRST_PRESS |  OFF  |
 * |  FIRST_PRESS  +----+--------------+-------+
 * |               |  1 | SECOND_PRESS |  OFF  |
 * +---------------+----+--------------+-------+
 * |               |  0 | SECOND_PRESS |  OFF  |
 * |  SECOND_PRESS +----+--------------+-------+
 * |               |  1 |  THIRD_PRESS |  OFF  |
 * +---------------+----+--------------+-------+
 * |  THIRD_PRESS  |  x |     INIT     | GREEN |
 * +---------------+----+--------------+-------+
 */

#define F_CPU 8000000 // CPU clock frequency, used by <util/delay.h>
#include <avr/io.h>
#include <util/delay.h>

#include "colors.hpp"
#include "button.hpp"

constexpr int COLOR_DELAY_MS = 2000;

enum class MachineState
{
    INIT_RED,
    AMBER,
    FIRST_GREEN,
    SECOND_RED,
    FIRST_OFF,
    SECOND_GREEN
};

int main()
{
    DDRA |= _BV(DDA0) | _BV(DDA1);
    DDRD &= ~_BV(DDD2);

    MachineState currentState = MachineState::INIT_RED;

    while (true)
    {
        switch (currentState)
        {
        case MachineState::INIT_RED:
            PORTA = (uint8_t)Color::RED;

            if (Button::isPressed())
            {
                currentState = MachineState::AMBER;
            }
            break;

        case MachineState::AMBER:
            PORTA = (uint8_t)Color::RED;
            _delay_ms(10);
            PORTA = (uint8_t)Color::GREEN;

            if (!Button::isPressed())
            {
                currentState = MachineState::FIRST_GREEN;
            }
            break;

        case MachineState::FIRST_GREEN:
            PORTA = (uint8_t)Color::GREEN;
            if (Button::isPressed())
            {
                currentState = MachineState::SECOND_RED;
            }
            break;

        case MachineState::SECOND_RED:
            PORTA = (uint8_t)Color::RED;
            if (!Button::isPressed())
            {
                currentState = MachineState::FIRST_OFF;
            }
            break;

        case MachineState::FIRST_OFF:
            PORTA = (uint8_t)Color::OFF;
            if (Button::isPressed())
            {
                currentState = MachineState::SECOND_GREEN;
            }
            break;

        case MachineState::SECOND_GREEN:
            PORTA = (uint8_t)Color::GREEN;
            if (!Button::isPressed())
            {
                currentState = MachineState::INIT_RED;
            }
            break;
        }

        // PORTA = (uint8_t)Color::OFF;
    }

    return 0;
}
