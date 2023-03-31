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

#ifndef MAP_H
#define MAP_H

#include <avr/io.h>

#include <app/misc/map/column.hpp>

class Map
{
public:
    Column &operator[](const uint8_t columnIndex);
    const Column &operator[](const uint8_t columnIndex) const;

    void reset();

    static constexpr uint8_t N_COLUMNS = 8;

private:
    Column columns_[N_COLUMNS];
};

#endif
