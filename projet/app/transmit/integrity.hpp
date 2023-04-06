/**
 * Ensure communication integrity using a
 * 32-bit cyclic redundancy check (CRC32).
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

#ifndef INTEGRITY_H
#define INTEGRITY_H

#include <avr/io.h>

class Integrity
{
public:
    uint32_t get() const;
    void update(const char* data);

private:
    static constexpr uint32_t GENERATOR_POLYNOMIAL = 0xEDB88320;
    static constexpr uint32_t CRC_START_VALUE = 0xFFFFFFFF;

    void updateWithGenerator();

    uint32_t crc_ = CRC_START_VALUE;
};

#endif
