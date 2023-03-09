/**
 * Write and read external EEPROM memory.
 *
 * LIMITATIONS: Memory::readMessage is using a shared buffer.
 *              Copy or use the value read before reading another one.
 *
 * Hardware Identification
 * EEPROM: C0 & C1.
 *
 * INPUT: jumper on MemEN
 * 
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <lib/_memoire_24.hpp>

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
    static constexpr uint8_t READ_WRITE_DELAY_MS = 5;
    static constexpr uint8_t MAXIMUM_MESSAGE_SIZE = 127;

    char readMessageBuffer_[MAXIMUM_MESSAGE_SIZE];
};

#endif
