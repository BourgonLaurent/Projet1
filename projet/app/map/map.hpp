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

#ifndef MAP_H
#define MAP_H

#include <avr/io.h>

#include <app/map/row.hpp>

class Map
{
public:
    Row &operator[](const uint8_t rowIndex);

    void save() const;
    void reset();
    void load();

private:
    static constexpr uint8_t N_ROWS = 4;
    static constexpr uint16_t START_ADDRESS = 0x0000;

    Row rows_[N_ROWS];
};

#endif
