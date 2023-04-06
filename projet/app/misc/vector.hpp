/**
 * Structure for vectors.
 *
 * USAGE:
 *  Point lower = {3, 0};
 *  Point upper = {3, 4};
 *  Vector vector = {lower, upper};
 *  vector.getPolarAngle();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 24, 2023
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <avr/io.h>

#include <app/misc/point.hpp>

struct Vector {
    Point start;
    Point end;

    int8_t getX() const;
    int8_t getY() const;
    int8_t getDisplacement() const;
    double getPolarAngle() const;

    static int8_t crossProduct(Vector &left, Vector &right);
};

#endif
