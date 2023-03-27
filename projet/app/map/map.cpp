/**
 * Load, save and modify a map.
 *
 * Hardware Identification
 *  WARNING: Data Direction Register will be set automatically.
 *  Memory: C0 + C1
 *
 * USAGE:
 *  Map map;
 *  Row map[0];
 *  Slot map[0][0];
 *  map.load();
 *  map[0][0].set();
 *  map.save();
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

Row &Map::operator[](const uint8_t rowIndex)
{
    return rows_[rowIndex];
}

void Map::save() const
{
    Memory memory;

    for (uint8_t i = 0; i < N_ROWS; i++) {
        memory.write(START_ADDRESS + i, rows_[i].get());
    }
}

void Map::reset()
{
    for (uint8_t i = 0; i < N_ROWS; i++) {
        rows_[i].clear();
    }
}

void Map::load()
{
    Memory memory;

    for (uint8_t i = 0; i < N_ROWS; i++) {
        rows_[i] = memory.read(START_ADDRESS + i);
    }
}
