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

#include <lib/communication.hpp>
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
    Communication::send(sumForAverage);
    Communication::send(" ");
    return sumForAverage;
}

bool IrSensor::detect(uint8_t distance1, uint8_t distance2)
{
    uint16_t value = read();

    if (value < distance1 && value > distance2) {
        return true;
    }
    return false;
}

void IrSensor::detectRange(uint8_t distance)
{
    if (distance < 15 && distance > 12) {
        IrSensor::range_ = IrSensor::Range::DIAGONAL_FAR;
    }

    if (distance < 50 && distance > 44) {
        IrSensor::range_ = IrSensor::Range::DIAGONAL_CLOSE;
    }
}

bool IrSensor::objectFound()
{
    return objectFound_;
}