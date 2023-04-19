/**
 * Ensure communication integrity using a
 * 32-bit cyclic redundancy check (CRC).
 *
 * USAGE:
 *  Integrity integrity;
 *  integrity.update(data);
 *  integrity.update(data2);
 *  const uint32_t crc32 = integrity.get();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 28, 2023
 */

#include "integrity.hpp"

#include <string.h>

uint32_t Integrity::get() const
{
    return ~crc_;
}

void Integrity::update(const char* data)
{
    for (uint32_t i = 0; i < strlen(data); i++) {
        crc_ ^= data[i];

        updateWithGenerator();
    }
}

void Integrity::updateWithGenerator()
{
    static constexpr uint8_t nBitsPerCharacter = 8;

    for (uint8_t i = 0; i < nBitsPerCharacter; i++) {
        if (crc_ & 1) {
            crc_ = (crc_ >> 1) ^ GENERATOR_POLYNOMIAL;
        }
        else {
            crc_ >>= 1;
        }
    }
}
