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

#include "row.hpp"

void Row::operator=(const uint8_t rawRow)
{
    for (uint8_t i = 0; i < N_SLOTS; i++) {
        if ((rawRow & (1 << i)) != 0) {
            slots_[i].set();
        }
        else {
            slots_[i].clear();
        }
    }
}

Slot &Row::operator[](const uint8_t slotIndex)
{
    return slots_[slotIndex];
}

uint8_t Row::get() const
{
    uint8_t result = 0;

    for (uint8_t i = 0; i < N_SLOTS; i++) {
        result |= slots_[i].get() << i;
    }

    return result;
}

void Row::clear()
{
    for (uint8_t i = 0; i < N_SLOTS; i++) {
        slots_[i].clear();
    }
}
