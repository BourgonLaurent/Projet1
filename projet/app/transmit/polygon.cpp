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

#include "polygon.hpp"

Polygon::Polygon(const Array<Point> &vertices) : vertices_(vertices) {}

const Array<Point> &Polygon::getVertices() const
{
    return vertices_;
}

uint16_t Polygon::calculateArea() const
{
    // Implementation of the shoelace formula
    // calculating each side of the determinant separetly
    // https://en.wikipedia.org/wiki/Shoelace_formula

    double positiveSum = 0.0;
    double negativeSum = 0.0;

    for (uint8_t i = 0; i < vertices_.size(); i++) {
        uint8_t j = (i + 1) % vertices_.size();

        positiveSum += vertices_[i].x * vertices_[j].y;
        negativeSum += vertices_[i].y * vertices_[j].x;
    }

    double area = abs(positiveSum - negativeSum) / 2.0;

    return area * AREA_UNITS_TO_INCHES;
}
