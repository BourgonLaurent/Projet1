/**
 * Control of a infrared sensor.
 *
 * HARDWARE:
 * IR sensor to PA0
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 28, 2023
 */

#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "analogReader.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <lib/io.hpp>

class IrSensor
{
public:
    enum class Range
    {
        DIAGONAL,
        STRAIGHT,
    };

    enum Distance
    {
        FAR,
        CLOSE,
    };

    IrSensor(io::Position pin);

    uint16_t read();

    bool isInFront(uint8_t distance1 = TEN_CM, uint8_t distance2 = EIGHTY_CM);
    bool isClose();

    void setDistance(uint8_t distance);
    bool isObjectDetected();

    void setRange(IrSensor::Range range);
    void setObjectDetected(bool objectDetected);
    bool isTooClose();
    Range getRange();
    Distance getDistance();

private:
    static const uint8_t N_MEASURMENTS = 6;
    static const uint8_t EIGHTY_CM = 15;
    static const uint16_t TEN_CM = 120;
    static const uint8_t FIFTEEN_CM = 75;

    static const uint8_t EDGE_CLOSE_FAR = 45;

    static const uint8_t LIMIT_OBJECT_CLOSE = 30;

    AnalogReader reader_;
    const io::Position pin_;

    Range range_;
    Distance distance_;

    bool isObjectDetected_ = false;
};

#endif
