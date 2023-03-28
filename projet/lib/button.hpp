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

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

#include <lib/io.hpp>

class Button
{
public:
    enum class ActiveMode
    {
        PRESSED,
        RELEASED
    };

    Button(io::DataDirectionRegister dataDirection, io::Pin pin,
           const io::Position position,
           const ActiveMode &mode = ActiveMode::PRESSED);
    bool isPressed() const;

private:
    static constexpr uint8_t DEBOUNCE_DELAY_MS = 10;

    io::Pin pin_;
    const io::Position position_;
    const ActiveMode mode_;

    bool getState() const;
};

#endif
