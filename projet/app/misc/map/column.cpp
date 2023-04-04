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

#include "column.hpp"

Slot &Column::operator[](const uint8_t slotIndex)
{
    return slots_[slotIndex];
}

const Slot &Column::operator[](const uint8_t slotIndex) const
{
    return slots_[slotIndex];
}

void Column::operator=(const uint8_t rawRow)
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

uint8_t Column::get() const
{
    uint8_t result = 0;

    for (uint8_t i = 0; i < N_SLOTS; i++) {
        result |= slots_[i].get() << i;
    }

    return result;
}

void Column::clear()
{
    for (uint8_t i = 0; i < N_SLOTS; i++) {
        slots_[i].clear();
    }
}
