/**
 * Retrieve information from the push button.
 *
 * Hardware Identification:
 * /!\ The Data Direction Register (`dataDirectionRegister`)
 *     will be set automatically.
 * INPUT: Push button connected to `pin` on `bit`.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

class Button
{
public:
    Button(volatile uint8_t* dataDirectionRegister, volatile uint8_t* pin,
           const uint8_t bit);
    bool isPressed() const;

private:
    static constexpr uint8_t DEBOUNCE_DELAY_MS = 10;

    volatile uint8_t* pin_;
    const uint8_t bit_;

    bool getState() const;
};

#endif
