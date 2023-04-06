
#include <avr/io.h>

#include <lib/debug.hpp>

#include <app/misc/array.hpp>
#include <app/misc/point.hpp>
#include <app/transmit/convexHull.hpp>

int main()
{
    debug::initialize();

    Point points[] = {
        {1, 1}, {1, 2}, {1, 3}, {2, 2}, {3, 3}, {4, 2}, // énoncé
        // {1, 0}, {0, 0}, {0, 3}, {7, 3}, {2, 1},
        // {0, 3}, {7, 3}, {5, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 2},
    };
    constexpr uint8_t nPoints = sizeof(points) / sizeof(points[0]);

    Array<Point> pointArray(points, nPoints);

    ConvexHull convexHull(pointArray);
    Polygon polygon = convexHull.runGrahamScan();

    debug::send("size", polygon.getVertices().size());
    for (uint8_t i = 0; i < polygon.getVertices().size(); i++) {
        Point point = polygon.getVertices()[i];

        debug::send(point.x);
        debug::send(",");
        debug::send(point.y);
        debug::send("\n");
    }

    debug::send("area", polygon.calculateArea());

    return 0;
}
