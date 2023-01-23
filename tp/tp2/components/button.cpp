/**
 * Implementation of the retrieval of information from the push button.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (`dataDirectionRegister`) will be set automatically.
 * INPUT: Push button connected to `pin` on `bit`.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/bit.hpp>

#include "button.hpp"

Button::Button(
    volatile uint8_t *dataDirectionRegister,
    volatile uint8_t *pin,
    const uint8_t bit) : pin_(pin),
                         bit_(bit)
{
    Bit::clear(dataDirectionRegister, bit);
};

bool Button::getState() const
{
    return *pin_ & _BV(bit_);
}

bool Button::isPressed() const
{
    if (getState())
    {
        _delay_ms(DEBOUNCE_DELAY_MS);
        return getState();
    }
    return false;
}
