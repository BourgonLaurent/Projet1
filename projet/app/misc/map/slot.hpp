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

#ifndef SLOT_H
#define SLOT_H

class Slot
{
public:
    const bool get() const;
    void set();
    void clear();

private:
    bool status_ = false;
};

#endif
