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

    struct Calibration {
        const uint8_t tenCm;
        const uint8_t fifteenCm;
        const uint8_t eightyCm;
        const uint8_t farThreshold;
    };

    IrSensor(io::Position pin, const Calibration &constants);

    uint8_t read();

    bool isInFront();
    bool isClose();

    void setDistance(uint8_t distance);
    bool isObjectDetected();

    void setRange(IrSensor::Range range);
    void setObjectDetected(bool objectDetected);
    bool isTooClose();
    Range getRange();
    Distance getDistance();

private:
    static constexpr uint8_t N_MEASURMENTS = 5;
    static constexpr uint8_t DELAY_BETWEEN_READS_MS = 5;

    bool isInRange(uint8_t distance1, uint8_t distance2);

    AnalogReader reader_;
    const io::Position pin_;
    const Calibration calibration_;

    Range range_;
    Distance distance_;

    bool isObjectDetected_ = false;
};

#endif
