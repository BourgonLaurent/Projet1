/**
 * Save and load a map.
 *
 * Hardware Identification
 *  WARNING: Data Direction Registers will be set automatically.
 *
 *  EEPROM:
 *    - SCL (PC0)
 *    - SDA (PC1)
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

#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <app/misc/array.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/point.hpp>

class MapManager
{
public:
    static void save(const Map &map);
    static Map load();

    static Array<Point> exportToPoints(const Map &map);

private:
    static constexpr uint16_t START_ADDRESS = 0x0000;

    static constexpr uint8_t N_COLUMNS_PER_BYTE = 2;
    static constexpr uint8_t N_BYTES = Map::N_COLUMNS / N_COLUMNS_PER_BYTE;

    static constexpr uint8_t UPPER_COLUMN_SHIFT = 4;
};

#endif
