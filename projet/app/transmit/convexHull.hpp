/**
 * Find the convex hull of some points.
 *
 * USAGE:
 *  Array<Point> points;
 *  ConvexHull convexHull{points};
 *  Array<Point> polygon = convexHull.runGrahamScan();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 24, 2023
 */

#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <avr/io.h>

#include <app/misc/array.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/point.hpp>
#include <app/transmit/polygon.hpp>

class ConvexHull
{
public:
    ConvexHull(const Array<Point> &points);

    Polygon runGrahamScan();

private:
    void findPivot();

    Array<Point> points_;

    // qsort() compare function needs to be static
    static int comparePointsWithPivot(const void* left, const void* right);
    static Point pivot_;
};

#endif
