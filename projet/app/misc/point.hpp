/**
 * Structure for coordinates.
 *
 * USAGE:
 *  Point lower = {3, 0};
 *  Point upper = {3, 4};
 *  lower < upper // true
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 24, 2023
 */

#ifndef POINT_H
#define POINT_H

#include <avr/io.h>

struct Point {
    uint8_t x = 0;
    uint8_t y = 0;

    bool operator<(const Point &other) const;

    static bool areCounterClockwise(const Point &previous, const Point &current,
                                    const Point &next);
};

#endif
