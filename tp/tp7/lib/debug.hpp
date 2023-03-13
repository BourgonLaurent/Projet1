/**
 * Send data with RS232 when DEBUG is defined.
 *
 * Hardware Identification
 *  USART: D0 & D1. (from Communication)
 *
 * USAGE:
 *  debug::initialize();
 *  debug::send("lib1900\n");
 *  debug::send(1000);
 *  debug::send("Motor speed", speed);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 10, 2023
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <string.h>

#include <lib/communication.hpp>

namespace debug {
    static inline void send(const char* message)
    {
#ifdef DEBUG
        Communication::send(message);
#endif
    }

    static inline void send(const uint16_t data)
    {
#ifdef DEBUG
        Communication::send(data);
#endif
    }

    static inline void send(const char* label, const uint16_t data)
    {
#ifdef DEBUG
        send(label);
        send(": ");
        send(data);
        send("\n");
#endif
    }

    static inline void initialize()
    {
#ifdef DEBUG
        Communication::initialize();
        send("(DEBUG activated)\n");
#endif
    }
} // namespace debug

#endif
