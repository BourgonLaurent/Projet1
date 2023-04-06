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

namespace transmit {
    void run(Led &led)
    {
        led.setColor(Led::Color::GREEN);
        _delay_ms(INITIALIZATION_DELAY_MS);

        Flasher::initialize(led, FLASH_FREQUENCY_HZ, Led::Color::GREEN,
                            Led::Color::OFF);
        Flasher::startFlashing();

        Map map = MapManager::load();

        Array<Point> points = MapManager::exportToPoints(map);

        ConvexHull convexHull(points);
        Polygon polygon = convexHull.runGrahamScan();

        SvgBuilder svgBuilder(points, polygon);
        svgBuilder.generateAndSend();

        Flasher::stopFlashing();
    }
} // namespace transmit
