/**
 * Process user inputs with the push button.
 * \file button.cpp
 * \author Mehdi Benouhoud & Laurent Bourgon
 * \date January 18, 2023
 */

#include <avr/io.h>

#define F_CPU 8000000
#include <util/delay.h>

namespace Button
{
    constexpr int DEBOUNCE_DELAY_MS = 10;

    bool getState()
    {
        return PIND & _BV(DDD2);
    }

    bool isPressed()
    {
        if (getState())
        {
            _delay_ms(DEBOUNCE_DELAY_MS);
            return getState();
        }
        return false;
    }
}
