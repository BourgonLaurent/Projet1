/**
 * Bit manipulation.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 */

#ifndef IO_H
#define IO_H

#include <avr/io.h>

namespace IO {
    static inline void setActive(volatile uint8_t* port, const uint8_t bit)
    {
        *port |= _BV(bit);
    }

    static inline void clear(volatile uint8_t* port, const uint8_t bit)
    {
        *port &= ~_BV(bit);
    }

    static inline bool get(volatile uint8_t* pin, const uint8_t bit)
    {
        return *pin & _BV(bit);
    }

    static inline void setInput(volatile uint8_t* port, const uint8_t bit)
    {
        clear(port, bit);
    }

    static inline void setOutput(volatile uint8_t* port, const uint8_t bit)
    {
        setActive(port, bit);
    }
} // namespace IO

#endif
