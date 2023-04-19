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

#include "svgBuilder.hpp"

#include <stdio.h>
#include <string.h>

#include <lib/communication.hpp>

#include <app/transmit/tags.hpp>

SvgBuilder::SvgBuilder(const Array<Point> &posts, const Polygon &polygon)
    : poles_(&posts), polygon_(&polygon)
{
}

void SvgBuilder::generateAndSend()
{
    Communication::send(Communication::Control::START_TEXT);
    epilog();

    send(tags::CENTER_GROUP);
    send(tags::TITLE);

    area();

    send(tags::BOX);
    send(tags::MAP);

    polygon();
    dots();
    poles();
    prolog();
    Communication::send(Communication::Control::END_TEXT);

    sendChecksum();
    Communication::send(Communication::Control::END_TRANSMISSION);
}

void SvgBuilder::epilog()
{
    send(tags::OPENING);
    send(tags::STYLE);
}

void SvgBuilder::area()
{
    constexpr uint8_t sizeOfArea = 4;
    constexpr uint8_t maximumResultSize =
        sizeof(tags::templates::AREA) + sizeOfArea;

    char result[maximumResultSize];
    uint16_t area = polygon_->calculateArea();
    sprintf(result, tags::templates::AREA, area);
    send(result);
}

void SvgBuilder::polygon()
{
    constexpr uint8_t maximumPoints = 8;
    constexpr uint8_t sizeOfPoint = 4;
    char points[sizeOfPoint * maximumPoints];

    const Array<Point> &vertices = polygon_->getVertices();

    for (uint8_t i = 0; i < vertices.size(); i++) {
        sprintf(points + (sizeOfPoint * i), tags::templates::POINT,
                vertices[i].x, vertices[i].y);
    }

    constexpr uint8_t maximumResultSize =
        sizeof(tags::templates::POLYGON) + sizeof(points);

    char result[maximumResultSize];
    sprintf(result, tags::templates::POLYGON, points);

    send(result);
}

void SvgBuilder::dots()
{
    send(tags::dots::ROW);
    send(tags::dots::DOT);
    send(tags::dots::ADDITIONAL_DOTS);
    send(tags::dots::ROW_END);
    send(tags::dots::ADDITIONAL_ROWS);
    send(tags::dots::RED);
}

void SvgBuilder::poles()
{
    constexpr uint8_t sizeOfCoordinates = 2;
    constexpr uint8_t maximumResultSize =
        sizeof(tags::templates::POLE) + sizeOfCoordinates;

    for (uint8_t i = 0; i < poles_->size(); i++) {
        char result[maximumResultSize];
        sprintf(result, tags::templates::POLE, (*poles_)[i].x, (*poles_)[i].y);
        send(result);
    }
}

void SvgBuilder::prolog()
{
    send(tags::CLOSING);
}

void SvgBuilder::sendChecksum()
{
    constexpr uint8_t base = 16;
    constexpr uint8_t maximumResultSize = 9;

    char checksum[maximumResultSize];
    ultoa(integrity_.get(), checksum, base);
    Communication::send(checksum);
}

void SvgBuilder::send(const char* data)
{
    integrity_.update(data);
    Communication::send(data);
}
