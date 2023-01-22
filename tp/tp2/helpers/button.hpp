/**
 * Retrieve information from the push button.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
 */

#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    static bool isPressed();

private:
    static bool getState();
    static constexpr uint8_t DEBOUNCE_DELAY_MS = 10;
};

#endif
