/**
 * Main program for the transmit module.
 *  Fetches the positions of poles in memory,
 *  calculates the best fitting polygon,
 *  and sends a SVG file via RS232.
 *
 * Hardware Identification:
 *  NOTE: The data direction registers are set automatically.
 *
 *  OUTPUT:
 *    - Bicolor LED.
 *
 *  EEPROM:
 *    - SCL (PC0)
 *    - SDA (PC1)
 *
 *  USART:
 *    - RXD0 (PD0)
 *    - TXD0 (PD1)
 *
 *  TIMERS:
 *    - Timer 1 | Flasher
 *
 * USAGE:
 *  Transmit::run(led, Transmit::Mode::NORMAL);
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 23, 2023
 */

#include "transmit.hpp"

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
    Flasher::start();

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

    Flasher::stop();
}
