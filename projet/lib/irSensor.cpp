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

#include <lib/constants.hpp>
#include <lib/debug.hpp>

#include <lib/interruptTimer.hpp>

IrSensor::IrSensor(const io::Position pin) : pin_(pin)
{
    io::setInput(&DDRA, IrSensor::pin_);
};

uint16_t IrSensor::read()
{
    uint16_t sumForAverage = 0;
    uint8_t temporaryMaximum = 0;
    for (uint8_t i = 0; i < IrSensor::N_MEASURMENTS; i++) {
        const uint8_t value = IrSensor::reader_.read(IrSensor::pin_);

        if (value > temporaryMaximum) {
            sumForAverage = sumForAverage + temporaryMaximum;
            temporaryMaximum = value;
        }
        else {
            sumForAverage = sumForAverage + value;
        }
        _delay_ms(5);
    }
    sumForAverage = sumForAverage / (IrSensor::N_MEASURMENTS - 1);
    debug::send(sumForAverage);
    debug::send("\n");
    return sumForAverage;
}

bool IrSensor::isInFront(uint8_t distance1, uint8_t distance2)
{

    uint16_t value = read();

    if (value < distance1 && value > distance2) {
        setDistance(value);
        isObjectDetected_ = true;

        return true;
    }
    isObjectDetected_ = false;
    return false;
}

bool IrSensor::isClose()
{
    return isInFront(constants::TEN_CM, constants::FIFTEEN_CM);
}

void IrSensor::setDistance(uint8_t distance)
{
    debug::send("setDistance:\n");
    debug::send(distance);
    if (distance >= constants::EDGE_CLOSE_FAR
        && distance <= constants::TEN_CM) {

        distance_ = IrSensor::Distance::CLOSE;
    }
    else if (distance < constants::EDGE_CLOSE_FAR
             && distance > constants::EIGHTY_CM) {

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
    uint16_t value = read();
    if (value >= constants::TEN_CM)
        return true;
    return false;
}