/**
 * Read and modify a map.
 *
 * USAGE:
 *  Map map;
 *  Column map[0];
 *  Slot map[7][3];
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#include "map.hpp"

#include <lib/memory.hpp>

Column &Map::operator[](const uint8_t columnIndex)
{
    return columns_[columnIndex];
}

const Column &Map::operator[](const uint8_t columnIndex) const
{
    return columns_[columnIndex];
}

void Map::reset()
{
    for (uint8_t i = 0; i < N_COLUMNS; i++) {
        columns_[i].clear();
    }
}
