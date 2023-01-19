/**
 * Problem 1:
 *  Press three times the switch button to turn the LED green.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
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
 * |               |  0 |     INIT     |       |
 * |      INIT     +----+--------------+  OFF  +
 * |               |  1 |  FIRST_PRESS |       |
 * +---------------+----+--------------+-------+
 * |               |  0 |  FIRST_PRESS |       |
 * |  FIRST_PRESS  +----+--------------+  OFF  +
 * |               |  1 | SECOND_PRESS |       |
 * +---------------+----+--------------+-------+
 * |               |  0 | SECOND_PRESS |       |
 * |  SECOND_PRESS +----+--------------+  OFF  +
 * |               |  1 |  THIRD_PRESS |       |
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
    INIT,
    FIRST_PRESS,
    SECOND_PRESS,
    THIRD_PRESS
};

int main()
{
    // Output
    DDRA |= _BV(DDA0) | _BV(DDA1);

    // Input
    DDRD &= ~_BV(DDD2);

    MachineState currentState = MachineState::INIT;

    while (true)
    {
        switch (currentState)
        {
        case MachineState::INIT:
            while (Button::isPressed())
            {
                currentState = MachineState::FIRST_PRESS;
            }
            break;

        case MachineState::FIRST_PRESS:
            while (Button::isPressed())
            {
                currentState = MachineState::SECOND_PRESS;
            }
            break;

        case MachineState::SECOND_PRESS:
            while (Button::isPressed())
            {
                currentState = MachineState::THIRD_PRESS;
            }
            break;

        case MachineState::THIRD_PRESS:
            PORTA = (uint8_t)Color::GREEN;
            _delay_ms(COLOR_DELAY_MS);
            currentState = MachineState::INIT;
            break;
        }

        PORTA = (uint8_t)Color::OFF;
    }

    return 0;
}
