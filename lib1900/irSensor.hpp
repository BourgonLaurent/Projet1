#include "analogReader.hpp"
#include <avr/io.h>
#include <util/delay.h>

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <lib1900/io.hpp>
#include <lib1900/wheels.hpp>

class IrSensor
{
public:
    enum class Range
    {
        DIAGONAL_FAR,
        DIAGONAL_CLOSE,
        STRAIGHT_ANGLE_CLOSE,
        STARIGHT_ANGLE_FAR
    };
    enum class Side
    {
        RIGHT,
        LEFT
    };
    static Side side_;
    Range range_;
    IrSensor(io::Position pin);
    bool detect();
    bool detectDistanceToPark(uint8_t distance1, uint8_t distance2);
    uint16_t read();
    void goToObject(uint8_t distanceObject);
    void park();
    void detectRange(uint8_t distance);
    void find();
    bool objectFound() {return objectFound_ ;};

private:
    static const uint8_t N_MEASURMENTS_ = 6;
    const io::Position pin_;
    AnalogReader reader_;
    bool objectFound_ = 0;
};

#endif
