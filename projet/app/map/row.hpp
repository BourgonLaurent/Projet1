/**
 * Represents a row on a map.
 *
 * USAGE:
 *  Row row;
 *  Slot row[0];
 *  uint8_t rawRow = row.get();
 *  row = rawRow;
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#ifndef ROW_H
#define ROW_H

#include <avr/io.h>

#include <app/map/slot.hpp>

class Row
{
public:
    void operator=(const uint8_t rawRow);
    Slot &operator[](const uint8_t slotIndex);

    uint8_t get() const;
    void clear();

private:
    static constexpr uint8_t N_SLOTS = 8;

    Slot slots_[N_SLOTS];
};

#endif
