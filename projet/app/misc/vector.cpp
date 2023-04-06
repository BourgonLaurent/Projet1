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

#include "vector.hpp"

#include <math.h>

int8_t Vector::getX() const
{
    return end.x - start.x;
}

int8_t Vector::getY() const
{
    return end.y - start.y;
}

int8_t Vector::getDisplacement() const
{
    return sqrt(pow(getX(), 2) + pow(getY(), 2));
}

double Vector::getPolarAngle() const
{
    return atan2(getY(), getX());
}

int8_t Vector::crossProduct(Vector &left, Vector &right)
{
    return left.getX() * right.getY() - left.getY() * right.getX();
}
