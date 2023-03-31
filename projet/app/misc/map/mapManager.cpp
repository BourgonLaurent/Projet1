/**
 * Save and load a map.
 *
 * Hardware Identification
 *  WARNING: Data Direction Registers will be set automatically.
 *  Memory: C0 + C1
 *
 * USAGE:
 *  Map map;
 *  MapManager::save(map);
 *  map = MapManager::load();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 31, 2023
 */

#include "mapManager.hpp"

#include <lib/memory.hpp>

void MapManager::save(const Map &map)
{
    Memory memory;

    for (uint8_t i = 0; i < N_BYTES; i++) {
        const uint8_t combinedColumns =
            (map[2 * i + 1].get() << UPPER_COLUMN_SHIFT) | map[2 * i].get();

        memory.write(START_ADDRESS + i, combinedColumns);
    }
}

Map MapManager::load()
{
    Memory memory;
    Map map;

    for (uint8_t i = 0; i < N_BYTES; i++) {
        const uint8_t combinedColumns = memory.read(START_ADDRESS + i);
        map[2 * i] = combinedColumns;
        map[2 * i + 1] = combinedColumns >> UPPER_COLUMN_SHIFT;
    }

    return map;
}
