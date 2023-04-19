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

#include "irSensor.hpp"

#include <lib/debug.hpp>

#include <lib/interruptTimer.hpp>

io::DataDirectionRegister IrSensor::dataDirection_ = &DDRA;

IrSensor::IrSensor(const io::Position pin, const Calibration &calibration)
    : pin_(pin), calibration_(calibration)
{
    io::setInput(dataDirection_, pin_);
};

uint16_t IrSensor::read()
{
    uint16_t sum = 0;
    uint8_t maximum = 0;

    for (uint8_t i = 0; i < N_MEASURMENTS; i++) {
        const uint8_t distance = reader_.read(pin_);

        if (distance > maximum) {
            maximum = distance;
        }

        sum += distance;

        _delay_ms(DELAY_BETWEEN_READS_MS);
    }

    const uint16_t average = (sum - maximum) / (N_MEASURMENTS - 1);

    debug::send(average);
    debug::send("\n");
    return average;
}

bool IrSensor::isInFront()
{
    return isInRange(calibration_.tenCm, calibration_.eightyCm);
}

bool IrSensor::isClose()
{
    return isInRange(calibration_.tenCm, calibration_.fifteenCm);
}

void IrSensor::setDistance(uint8_t distance)
{
    debug::send("setDistance:\n");
    debug::send(distance);
    if (distance >= calibration_.farThreshold
        && distance <= calibration_.tenCm) {
        distance_ = IrSensor::Distance::CLOSE;
    }
    else if (distance < calibration_.farThreshold
             && distance > calibration_.eightyCm) {
        distance_ = IrSensor::Distance::FAR;
    }
}

bool IrSensor::isObjectDetected()
{
    return isObjectDetected_;
}

void IrSensor::setObjectDetected(bool objectDetected)
{
    isObjectDetected_ = objectDetected;
}

void IrSensor::setRange(IrSensor::Range range)
{
    range_ = range;
}

IrSensor::Range IrSensor::getRange()
{
    return range_;
}

IrSensor::Distance IrSensor::getDistance()
{
    return distance_;
}

bool IrSensor::isTooClose()
{
    uint16_t distance = read();

    return distance >= calibration_.tenCm;
}

bool IrSensor::isInRange(uint8_t minimum, uint8_t maximum)
{
    uint16_t distance = read();

    isObjectDetected_ = distance < minimum && distance > maximum;

    if (isObjectDetected_) {
        setDistance(distance);
    }

    return isObjectDetected_;
}
