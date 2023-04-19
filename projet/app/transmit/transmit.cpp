#include "run.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <lib/debug.hpp>
#include <lib/flasher.hpp>
#include <lib/led.hpp>

#include <app/misc/array.hpp>
#include <app/misc/map/map.hpp>
#include <app/misc/map/mapManager.hpp>
#include <app/misc/point.hpp>
#include <app/transmit/convexHull.hpp>
#include <app/transmit/polygon.hpp>
#include <app/transmit/svgBuilder.hpp>

void Transmit::run(Led &led, const Mode &mode)
{
    led.setColor(Led::Color::GREEN);
    _delay_ms(INITIALIZATION_DELAY_MS);

    Flasher::initialize(led, FLASH_FREQUENCY_HZ, Led::Color::GREEN,
                        Led::Color::OFF);
    Flasher::startFlashing();

    Array<Point> points;
    switch (mode) {
        case Mode::NORMAL : {
            Map map = MapManager::load();
            points = MapManager::exportToPoints(map);
            break;
        }
        case Mode::DEMO : {
            points.append({0, 2});
            points.append({1, 1});
            points.append({1, 2});
            points.append({1, 3});
            points.append({3, 1});
            points.append({4, 2});
            points.append({6, 2});
            points.append({7, 3});
            break;
        }
    }

    ConvexHull convexHull(points);
    Polygon polygon = convexHull.runGrahamScan();

    SvgBuilder svgBuilder(points, polygon);
    svgBuilder.generateAndSend();

    Flasher::stopFlashing();
}
