/**
 * Bit manipulation.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date January 19, 2023
 */

#ifndef IO_H
#define IO_H

#include <avr/io.h>

namespace io {
    using Register = volatile uint8_t*;
    using DataDirectionRegister = Register;
    using Port = Register;
    using Pin = Register;
    using Position = uint8_t;

    static inline bool get(Register pin, const Position position)
    {
        return *pin & _BV(position);
    }

    static inline void setActive(Register port, const Position position)
    {
        *port |= _BV(position);
    }

    static inline void clear(Register port, const Position position)
    {
        *port &= ~_BV(position);
    }

    static inline void setInput(DataDirectionRegister port,
                                const Position position)
    {
        clear(port, position);
    }

    static inline void setOutput(DataDirectionRegister port,
                                 const Position position)
    {
        setActive(port, position);
    }
} // namespace io

#endif
