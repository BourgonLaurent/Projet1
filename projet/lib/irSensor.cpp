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

#include "irSensor.hpp"

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
    for (uint8_t i = 0; i < IrSensor::N_MEASURMENTS_; i++) {
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
    sumForAverage = sumForAverage / (IrSensor::N_MEASURMENTS_ - 1);
    // debug::send(sumForAverage);
    // debug::send(" ");
    return sumForAverage;
}

bool IrSensor::isdetected(uint8_t distance1, uint8_t distance2)
{
    uint16_t value = read();
    if (value < distance1 && value > distance2) {
        detectDistance(value);
        objectDetected_ = true;

        return true;
    }
    objectDetected_ =false;
    return false;
}

void IrSensor::detectDistance(uint8_t distance)
{
    debug::send("dans detectDistance\n");
    debug::send(distance);
    if (distance >= 30 && distance < 90) {
        debug::send("\nCLOSE\n");
        distance_ = IrSensor::Distance::CLOSE;
    }
    else if (distance < 30) {
        debug::send("\nFAR\n");
        distance_ = IrSensor::Distance::FAR;
    }
}

bool IrSensor::objectDetected()
{
    return objectDetected_;
}

IrSensor::Range IrSensor::range()
{
    return range_;
}