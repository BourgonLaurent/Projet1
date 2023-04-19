/**
 * Send by RS232 a SVG file with poles and its respective polygon.
 * Every time a component of the SVG is generated, it is sent directly.
 *
 * Data is sent in the following format:
 *  ╔════════════════════════════════════╗
 *  ║            START OF TEXT           ║
 *  ║                0x02                ║
 *  ╠════════════════════════════════════╣
 *  ║                 SVG                ║
 *  ╠════════════════════════════════════╣
 *  ║             END OF TEXT            ║
 *  ║                0x03                ║
 *  ╠════════════════════════════════════╣
 *  ║                CRC32               ║
 *  ║ 8 lowercase hexadecimal characters ║
 *  ║       polynomial: 0xEDB88320       ║
 *  ╠════════════════════════════════════╣
 *  ║         END OF TRANSMISSION        ║
 *  ║                0x04                ║
 *  ╚════════════════════════════════════╝
 *
 * Hardware Identification
 *  USART: D0 & D1.
 *
 * USAGE:
 *  SvgBuilder builder(poles, polygon);
 *  builder.generateAndSend();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 28, 2023
 */

#ifndef SVGBUILDER_H
#define SVGBUILDER_H

#include <app/misc/array.hpp>
#include <app/misc/point.hpp>
#include <app/transmit/integrity.hpp>
#include <app/transmit/polygon.hpp>

class SvgBuilder
{
public:
    SvgBuilder(const Array<Point> &poles, const Polygon &polygon);
    void generateAndSend();

private:
    void epilog();
    void area();
    void polygon();
    void dots();
    void poles();
    void prolog();

    void sendChecksum();

    void send(const char* data);

    const Array<Point>* poles_;
    const Polygon* polygon_;

    Integrity integrity_;
};

#endif
