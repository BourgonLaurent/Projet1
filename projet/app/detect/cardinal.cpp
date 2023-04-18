#include "cardinal.hpp"

Cardinal operator|(Cardinal lhs, Cardinal rhs)
{
    return static_cast<Cardinal>(static_cast<uint8_t>(lhs)
                                 | static_cast<uint8_t>(rhs));
}

Cardinal operator|=(Cardinal &lhs, Cardinal rhs)
{
    return lhs = lhs | rhs;
}
