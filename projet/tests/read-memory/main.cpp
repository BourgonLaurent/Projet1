

#include <lib/debug.hpp>
#include <lib/irSensor.hpp>
#include <lib/led.hpp>
#include <lib/objectFinder.hpp>
#include <lib/positionManager.hpp>

#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>

int main()
{
    debug::initialize();

    // Led led = Led(&DDRB, &PORTB, PB0, PB1);

    // Map map;
    // IrSensor irSensor(PA0);
    // ObjectFinder objectFinder(led, irSensor, &map);
    // objectFinder.initialize();
    Map map = MapManager::load();

    debug::send(map[0][0].get());
    debug::send(map[0][1].get());

    debug::send(map[0].get());
    debug::send(map[1].get());
    debug::send(map[2].get());
    debug::send(map[3].get());
    debug::send(map[4].get());
    debug::send(map[5].get());
    debug::send(map[6].get());
    debug::send(map[7].get());
}
