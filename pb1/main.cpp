/**
 * Problème 1.
 * \file main.cpp
 * \author Mehdi Benouhoud & Laurent Bourgon
 * \date January 17, 2023
 *
 * Implements the following state table:
 *
 * +---------------+----+------------+-------+
 * | Current state | D2 | Next state |   A   |
 * +---------------+----+------------+-------+
 * |               |  0 |    INIT    |  OFF  |
 * |     INIT      +----+------------+-------+
 * |               |  1 |     S1     |  OFF  |
 * +---------------+----+------------+-------+
 * |               |  0 |     S1     |  OFF  |
 * |      S1       +----+------------+-------+
 * |               |  1 |     S2     |  OFF  |
 * +---------------+----+------------+-------+
 * |               |  0 |     S2     |  OFF  |
 * |      S2       +----+------------+-------+
 * |               |  1 |     S3     |  OFF  |
 * +---------------+----+------------+-------+
 * |      S3       |  X |    INIT    | GREEN |
 * +---------------+----+------------+-------+
 */

#include "../color.cpp"
#include "button.cpp"

#include <avr/io.h>

#define F_CPU 8000000
#include <util/delay.h>

enum class MachineState
{
    INIT,
    S1,
    S2,
    S3
};

int main()
{
    // Output
    DDRA = _BV(DDA0) | _BV(DDA1);

    // Input
    DDRD &= ~_BV(DDD2);

    constexpr int COLOR_DELAY_MS = 2000;

    MachineState currentState = MachineState::INIT;

    while (true)
    {
        switch (currentState)
        {
        case MachineState::INIT:
            while (Button::isPressed())
            {
                currentState = MachineState::S1;
            }
            break;

        case MachineState::S1:
            while (Button::isPressed())
            {
                currentState = MachineState::S2;
            }
            break;

        case MachineState::S2:
            while (Button::isPressed())
            {
                currentState = MachineState::S3;
            }
            break;

        case MachineState::S3:
            PORTA = (uint8_t)Color::GREEN;
            _delay_ms(COLOR_DELAY_MS);
            currentState = MachineState::INIT;
            break;
        }

        PORTA = (uint8_t)Color::OFF;
    }

    return 0;
}
