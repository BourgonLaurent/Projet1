/**
 * Control of a infrared sensor.
 *
 * HARDWARE:
 * IR sensor to PA6
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

    static const uint8_t EIGHTY_CM = 11;
    static const uint16_t TEN_CM = 130;
    static const uint8_t FIFTEEN_CM = 85;

    uint16_t read();
    bool isdetected(uint8_t distance1 = TEN_CM, uint8_t distance2 = EIGHTY_CM);
    void detectDistance(uint8_t distance);
    bool objectDetected();
    Range range();
    Distance getDistance() {return distance_;}
    void setRange(IrSensor::Range range) {range_ = range;}

private:
    static const uint8_t N_MEASURMENTS_ = 6;

    const io::Position pin_;
    AnalogReader reader_;
    Range range_;
    Distance distance_;
    bool objectDetected_ = 0;
};
