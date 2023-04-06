/**
 * Represents a polygon inside a coordinate system.
 *
 * USAGE:
 *  Array<Point> vertices;
 *  Polygon polygon{vertices};
 *  polygon.getVertices().size();
 *  polygon.calculateArea();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 27, 2023
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <app/misc/array.hpp>
#include <app/misc/point.hpp>

class Polygon
{
public:
    Polygon(const Array<Point> &vertices);

    const Array<Point> &getVertices() const;
    uint16_t calculateArea() const;

private:
    static constexpr uint8_t AREA_UNITS_TO_INCHES = 11 * 11;

    const Array<Point> vertices_;
};

#endif
