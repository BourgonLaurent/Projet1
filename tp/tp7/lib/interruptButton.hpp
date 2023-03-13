/**
 * Interrupt the main program with a push button.
 *
 * Hardware Identification:
 *  WARNING: The Data Direction Register (DDRD) will be set automatically.
 *  INPUT: Push button connected to D2.
 *
 * USAGE: Use `InterruptButton_vect` inside the ISR.
 *        For the debounce, call the appropriate functions
 *        at the start and end of the routine.
 *
 *    ISR(InterruptButton_vect)
 *    {
 *        InterruptButton::waitForDebounce();
 *        ...
 *        InterruptButton::clear();
 *    }
 *
 * Team #4546
 *  \author Catalina-Andrea Araya-Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#ifndef INTERRUPTBUTTON_H
#define INTERRUPTBUTTON_H

#include <avr/interrupt.h>
#include <avr/io.h>

#include <lib/io.hpp>

#define InterruptButton_vect INT0_vect

class InterruptButton
{
public:
    enum class Mode
    {
        ANY,
        FALLING,
        RISING,
    };

    static void initialize(const Mode &mode = Mode::ANY);
    static void setMode(const Mode &mode);

    static void start();
    static void stop();
    static void clear();

    static void waitForDebounce();

private:
    static constexpr uint8_t DEBOUNCE_DELAY_MS = 30;
    static io::DataDirectionRegister dataDirection_;
    static io::Position position_;
};

#endif
