/**
 * Control the activation of interrupt routines (ISR).
 *
 * USAGE:
 *  interrupts::startCatching();
 *  InterruptTimer::start();
 *  ...
 *  interrupts::stopCatching();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <avr/interrupt.h>

namespace interrupts {
    static inline void startCatching()
    {
        sei();
    }

    static inline void stopCatching()
    {
        cli();
    }
} // namespace interrupts

#endif
