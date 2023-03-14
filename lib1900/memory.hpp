/**
 * Write and read external EEPROM memory.
 *
 * LIMITATIONS: Memory::readMessage is using a shared buffer.
 *              Copy or use the value read before reading another one.
 *
 * Hardware Identification
 *  EEPROM: C0 & C1.
 *
 * USAGE: example of writing a message and reading it.
 *
 *  const char* message = "C'est quoi le STEP ?\n";
 *  const uint8_t messageSize = strlen(message);
 *  Memory::writeMessage(0x0000, message);
 *  const char* messageRead = Memory::readMessage(0x0000, messageSize);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <lib1900/_memoire_24.hpp>

class Memory : private Memoire24CXXX
{
public:
    void write(const uint16_t address, const uint8_t data);
    const uint8_t read(const uint16_t address) const;

    void writeMessage(const uint16_t startAddress, const char* message);
    const char* readMessage(const uint16_t startAddress,
                            const uint8_t messageSize) const;

    void clearBuffer();

private:
    static constexpr uint8_t WRITE_DELAY_MS = 5;
    static constexpr uint8_t N_MAX_CHARACTERS = 127;

    char readMessageBuffer_[N_MAX_CHARACTERS];
};

#endif
