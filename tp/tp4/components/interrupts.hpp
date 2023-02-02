#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <avr/interrupt.h>
#include <avr/io.h>

namespace interrupts {
    static inline void clear()
    {
        EIFR |= _BV(INTF0);
    }

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