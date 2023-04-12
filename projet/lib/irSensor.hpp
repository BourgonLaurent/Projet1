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

    bool isForward(uint8_t distance1 = TEN_CM, uint8_t distance2 = EIGHTY_CM);
    bool isClose();

    void setDistance(uint8_t distance);
    bool isObjectDetected();

    void setRange(IrSensor::Range range);
    void setObjectDetected(bool objectDetected);
    Range getRange();
    Distance getDistance();

private:
    static const uint8_t N_MEASURMENTS = 6;
    static const uint8_t EIGHTY_CM = 20;
    static const uint16_t TEN_CM = 130;
    static const uint8_t FIFTEEN_CM = 85;

    static const uint8_t MIN_DIAGONAL_FAR = 85;
    static const uint8_t EDGE_CLOSE_FAR = 85;

    static const uint8_t LIMIT_OBJECT_CLOSE = 30;

    AnalogReader reader_;
    const io::Position pin_;

    Range range_;
    Distance distance_;

    bool isObjectDetected_ = false;
};
