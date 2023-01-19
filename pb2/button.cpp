#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "button.hpp"

bool Button::getState()
{
    return PIND & _BV(DDD2);
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
