/**
 * Implementation of the retrieval of information from the switch button.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "button.hpp"

bool Button::getState()
{
    return PIND & _BV(PIND2);
}

bool Button::isPressed()
{
    if (getState())
    {
        _delay_ms(DEBOUNCE_DELAY_MS);
        return getState();
    }
    return false;
}
