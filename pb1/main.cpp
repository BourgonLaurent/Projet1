/**
 * Problème 1.
 * \file main.cpp
 * \author Mehdi Benouhoud & Laurent Bourgon
 * \date January 17, 2023
 *
 *
 * +--------------+----+--------------+-------+
 * | État présent | D2 | État suivant |   A   |
 * +--------------+----+--------------+-------+
 * |              |  0 |     INIT     |  OFF  |
 * |     INIT     +----+--------------+-------+
 * |              |  1 |      S1      |  OFF  |
 * +--------------+----+--------------+-------+
 * |              |  0 |      S1      |  OFF  |
 * |      S1      +----+--------------+-------+
 * |              |  1 |      S2      |  OFF  |
 * +--------------+----+--------------+-------+
 * |              |  0 |      S2      |  OFF  |
 * |      S2      +----+--------------+-------+
 * |              |  1 |      S3      |  OFF  |
 * +--------------+----+--------------+-------+
 * |      S3      |  X |     INIT     | GREEN |
 * +--------------+----+--------------+-------+
 */

#define F_CPU 8000000

#include "../color.cpp"

#include <avr/io.h>
#include <util/delay.h>

enum MachineState
{
    INIT,
    S1,
    S2,
    S3
};

bool getButtonState()
{
    return PIND & _BV(DDD2);
}

bool isUserPressingButton()
{
    if (getButtonState())
    {
        _delay_ms(10);
        return getButtonState();
    }
    return false;
}

bool didUserPressAndRelease()
{
    return false;
}

int main()
{
    // Output
    DDRA = _BV(DDA0) | _BV(DDA1);

    // Input
    DDRD &= ~_BV(DDD2);

    MachineState currentState = MachineState::INIT;
    MachineState nextState = MachineState::INIT;

    while (true)
    {
        while (isUserPressingButton())
        {
            switch (currentState)
            {
            case MachineState::INIT:
                nextState = MachineState::S1;
                break;

            case MachineState::S1:
                nextState = MachineState::S2;
                break;

            case MachineState::S2:
                nextState = MachineState::S3;
                break;

            default:
                break;
            }
        }

        currentState = nextState;

        if (currentState == MachineState::S3)
        {
            PORTA = (uint8_t)Color::GREEN;
            _delay_ms(2000);
            currentState = MachineState::INIT;
        }

        PORTA = (uint8_t)Color::OFF;
    }

    return 0;
}
