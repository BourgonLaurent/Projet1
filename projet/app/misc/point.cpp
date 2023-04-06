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

#include "point.hpp"

#include <avr/io.h>
#include <math.h>

#include <app/misc/vector.hpp>

bool Point::operator<(const Point &other) const
{
    if (y != other.y) {
        return y < other.y;
    }

    return x < other.x;
}

bool Point::areCounterClockwise(const Point &previous, const Point &current,
                                const Point &next)
{
    Vector incoming = {previous, current};
    Vector outgoing = {current, next};

    return Vector::crossProduct(incoming, outgoing) <= 0;
}
