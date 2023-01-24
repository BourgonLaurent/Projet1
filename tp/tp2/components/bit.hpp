/**
 * Bit manipulation.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#ifndef BIT_H
#define BIT_H

#include <avr/io.h>

namespace Bit
{
    static inline void activate(volatile uint8_t *port, const uint8_t bit)
    {
        *port |= _BV(bit);
    }

    static inline void clear(volatile uint8_t *port, const uint8_t bit)
    {
        *port &= ~_BV(bit);
    }

    static inline uint8_t get(volatile uint8_t *pin, const uint8_t bit)
    {
        return *pin & _BV(bit);
    }
}

#endif
