#ifndef CARDINAL_H
#define CARDINAL_H

#include <stdint.h>

enum class Cardinal : uint8_t
{
    MIDDLE = 0,
    NORTH = 0b0001,
    SOUTH = 0b0010,
    EAST = 0b0100,
    WEST = 0b1000,
    NORTH_WEST = NORTH | WEST,
    NORTH_EAST = NORTH | EAST,
    SOUTH_WEST = SOUTH | WEST,
    SOUTH_EAST = SOUTH | EAST,
};

Cardinal operator|(Cardinal lhs, Cardinal rhs);
Cardinal operator|=(Cardinal &lhs, Cardinal rhs);

#endif
