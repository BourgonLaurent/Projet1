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

#include <app/detect/constants.hpp>
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

    bool isInFront(uint8_t distance1 = constants::TEN_CM,
                   uint8_t distance2 = constants::EIGHTY_CM);
    bool isClose();

    void setDistance(uint8_t distance);
    bool isObjectDetected();

    void setRange(IrSensor::Range range);
    void setObjectDetected(bool objectDetected);
    bool isTooClose();
    Range getRange();
    Distance getDistance();

private:
    static constexpr uint8_t N_MEASURMENTS = 6;

    AnalogReader reader_;
    const io::Position pin_;

    Range range_;
    Distance distance_;

    bool isObjectDetected_ = false;
};

#endif
