/**
 * Bit manipulation.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date February 16, 2023
 */

#ifndef IO_H
#define IO_H

#include <avr/io.h>

namespace io {
    using Register = volatile uint8_t*;
    using DataDirectionRegister = Register;
    using Port = Register;
    using Pin = Register;
    using PinPosition = uint8_t;

    static inline bool get(Register pin, const PinPosition bit)
    {
        return *pin & _BV(bit);
    }

    static inline void setActive(Register port, const PinPosition bit)
    {
        *port |= _BV(bit);
    }

    static inline void clear(Register port, const PinPosition bit)
    {
        *port &= ~_BV(bit);
    }

    static inline void setInput(DataDirectionRegister port,
                                const PinPosition bit)
    {
        clear(port, bit);
    }

    static inline void setOutput(DataDirectionRegister port,
                                 const PinPosition bit)
    {
        setActive(port, bit);
    }
} // namespace io

#endif
