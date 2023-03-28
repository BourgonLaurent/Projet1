
#include <util/delay.h>

#include <lib/debug.hpp>
#include <lib/led.hpp>

#include <app/map/map.hpp>

int main()
{
    debug::initialize();

    Map map;
    map.load();

    debug::send(map[0].get());
    debug::send(map[1].get());
    debug::send(map[2].get());
    debug::send(map[3].get());

    map[1] = 34;
    map[0][0].set();

    map.save();
}
