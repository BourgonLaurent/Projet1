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
        uint8_t nMaxCharacters = 100;
        char formattedMessage[nMaxCharacters];
        snprintf(formattedMessage, nMaxCharacters, "%s: %u\n", label, data);

        send(formattedMessage);
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
