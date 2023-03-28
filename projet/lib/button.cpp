/**
 * Retrieve information from a button.
 *
 * Hardware Identification:
 *  WARNING: The Data Direction Register will be set automatically.
 *  INPUT: Push button connected to `pin` on `bit`.
 *
 * USAGE:
 *  Button button(&PORTD, &PIND, PD2);
 *  button.isPressed();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#include "button.hpp"

#include <util/delay.h>

#include <lib/io.hpp>

Button::Button(io::DataDirectionRegister dataDirection, io::Pin pin,
               const io::Position position, const ActiveMode &mode)
    : pin_(pin), position_(position), mode_(mode)
{
    io::setInput(dataDirection, position);
};

bool Button::getState() const
{
    bool state = io::get(pin_, position_);
    if (mode_ == ActiveMode::RELEASED) {
        state = !state;
    }

    return state;
}

bool Button::isPressed() const
{
    if (getState()) {
        _delay_ms(DEBOUNCE_DELAY_MS);
        return getState();
    }

    return false;
}
