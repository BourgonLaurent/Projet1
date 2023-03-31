

#include <lib/debug.hpp>
#include <lib/led.hpp>

#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>

int main()
{
    debug::initialize();

    // Map map;
    Map map = MapManager::load();

    debug::send(map[0].get());
    debug::send(map[1].get());
    debug::send(map[2].get());
    debug::send(map[3].get());
    debug::send(map[4].get());
    debug::send(map[5].get());
    debug::send(map[6].get());
    debug::send(map[7].get());

    map[0][0].set();   // should save as 1
    map[1] = 0b0011;   // should save as 3
    map[2][0].clear(); // should save as 0
    map[6] = 0b10000;  // should save as 0
    map[7] = 0b1001;   // should save as 9

    // expected result in debug: 13000009

    MapManager::save(map);
}
