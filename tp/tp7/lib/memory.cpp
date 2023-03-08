/**
 * Write and read external EEPROM memory.
 *
 * LIMITATIONS: Memory::readMessage is using a shared buffer.
 *              Copy or use the value read before reading another one.
 *
 * Hardware Identification
 * EEPROM: C0 & C1.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 */

#include <string.h>
#include <util/delay.h>

#include "memory.hpp"

const uint8_t Memory::read(const uint16_t address) const
{
    uint8_t readCharacter;
    lecture(address, &readCharacter);

    return readCharacter;
}

void Memory::write(const uint16_t address, const uint8_t data)
{
    ecriture(address, data);
    _delay_ms(READ_WRITE_DELAY_MS);
}

const char* Memory::readMessage(const uint16_t startAddress,
                                const uint8_t messageSize) const
{
    lecture(startAddress, (uint8_t*)readMessageBuffer_, messageSize);

    return readMessageBuffer_;
}

void Memory::writeMessage(const uint16_t startAddress, const char* message)
{
    const uint8_t messageSize = strlen(message) + 1;

    ecriture(startAddress, (uint8_t*)message, messageSize);
    _delay_ms(READ_WRITE_DELAY_MS);
}

void Memory::clearBuffer()
{
    memset(readMessageBuffer_, 0, MAXIMUM_MESSAGE_SIZE);
}
