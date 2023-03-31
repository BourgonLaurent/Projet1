/**
 * Represents a column on a map.
 *
 * USAGE:
 *  Column column;
 *  Slot column[0];
 *  uint8_t rawColumn = column.get();
 *  column = rawColumn;
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#ifndef COLUMN_H
#define COLUMN_H

#include <avr/io.h>

#include <app/misc/map/slot.hpp>

class Column
{
public:
    Slot &operator[](const uint8_t slotIndex);
    const Slot &operator[](const uint8_t slotIndex) const;

    void operator=(const uint8_t rawRow);

    uint8_t get() const;
    void clear();

    static constexpr uint8_t N_SLOTS = 4;

private:
    Slot slots_[N_SLOTS];
};

#endif
