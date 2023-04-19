#ifndef BORDER_H
#define BORDER_H

#include <stdint.h>

enum class Border : uint8_t
{
    MIDDLE = 0,
    TOP = 0b0001,
    BOTTOM = 0b0010,
    LEFT = 0b0100,
    RIGHT = 0b1000,
    TOP_LEFT = TOP | LEFT,
    TOP_RIGHT = TOP | RIGHT,
    BOTTOM_LEFT = BOTTOM | LEFT,
    BOTTOM_RIGHT = BOTTOM | RIGHT,
};

constexpr Border operator|(Border lhs, Border rhs)
{
    return static_cast<Border>(static_cast<uint8_t>(lhs)
                               | static_cast<uint8_t>(rhs));
}

constexpr Border operator|=(Border &lhs, Border rhs)
{
    return lhs = lhs | rhs;
}

#endif
