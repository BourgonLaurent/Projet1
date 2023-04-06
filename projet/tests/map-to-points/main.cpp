

#include <lib/debug.hpp>

#include <app/misc/array.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>
#include <app/misc/point.hpp>

int main()
{
    debug::initialize();

    Map map;
    map[0][0].set();
    map[1][1].set();
    map[6][2].set();
    map[5][3].set();
    map[7][3].set();

    const Array<Point> points = MapManager::exportToPoints(map);

    for (uint8_t i = 0; i < points.size(); i++) {
        const Point &point = points[i];

        debug::send(point.x);
        debug::send(",");
        debug::send(point.y);
        debug::send("\n");
    }

    debug::send("done", points.size());

    return 0;
}
