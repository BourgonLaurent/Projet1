/**
 * Represents a slot on a map.
 *
 * USAGE:
 *  Slot slot;
 *  slot.clear();
 *  slot.set();
 *  uint8_t slot.get();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#include "slot.hpp"

const bool Slot::get() const
{
    return status_;
}
void Slot::set()
{
    status_ = true;
}

void Slot::clear()
{
    status_ = false;
}
