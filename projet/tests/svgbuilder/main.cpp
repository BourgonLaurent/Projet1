#include <lib/communication.hpp>

#include <app/misc/array.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>
#include <app/misc/point.hpp>
#include <app/transmit/convexHull.hpp>
#include <app/transmit/polygon.hpp>
#include <app/transmit/svgBuilder.hpp>

int main()
{
    Communication::initialize();
    Map map;
    map[0][0].set();
    map[1][1].set();
    map[6][2].set();
    map[5][3].set();
    map[7][3].set();

    Array<Point> points = MapManager::exportToPoints(map);

    ConvexHull convexHull(points);
    Polygon polygon = convexHull.runGrahamScan();

    SvgBuilder svgBuilder(points, polygon);
    svgBuilder.generateAndSend();

    return 0;
}
