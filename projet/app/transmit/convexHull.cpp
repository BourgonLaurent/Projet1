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

#include "convexHull.hpp"

#include <lib/debug.hpp>

#include <app/misc/vector.hpp>

ConvexHull::ConvexHull(const Array<Point> &points) : points_(points) {}

Point ConvexHull::pivot_ = {0, 0};

Polygon ConvexHull::runGrahamScan()
{
    findPivot();

    // Sort the points using their polar angles towards the pivot
    points_.sort(comparePointsWithPivot);

    // Traverse the sorted points to construct the convex hull
    Array<Point> hullPoints;
    hullPoints.append(points_[0]);
    hullPoints.append(points_[1]);

    const uint8_t nStartingPoints = hullPoints.size();

    for (uint8_t i = nStartingPoints; i < points_.size(); i++) {
        while (hullPoints.size() >= nStartingPoints
               && Point::areCounterClockwise(hullPoints[hullPoints.size() - 2],
                                             hullPoints[hullPoints.size() - 1],
                                             points_[i])) {
            hullPoints.remove();
        }

        hullPoints.append(points_[i]);
    }

    return {hullPoints};
}

void ConvexHull::findPivot()
{
    pivot_ = points_[0];
    for (uint8_t i = 1; i < points_.size(); i++) {
        if (points_[i] < pivot_) {
            pivot_ = points_[i];
        }
    }
}

int ConvexHull::comparePointsWithPivot(const void* left, const void* right)
{
    Vector pivotToLeft = {pivot_, *(Point*)left};
    Vector pivotToRight = {pivot_, *(Point*)right};

    double leftAngle = pivotToLeft.getPolarAngle();
    double rightAngle = pivotToRight.getPolarAngle();

    if (leftAngle < rightAngle) {
        return -1;
    }
    if (leftAngle > rightAngle) {
        return 1;
    }

    // fallback on distance if same polar angle
    double leftDistance = pivotToLeft.getDisplacement();
    double rightDistance = pivotToRight.getDisplacement();

    if (leftDistance < rightDistance) {
        return -1;
    }

    return leftDistance > rightDistance;
}
