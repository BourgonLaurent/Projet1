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

#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "analogReader.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <lib/io.hpp>
#include <lib/led.hpp>
#include <lib/wheels.hpp>

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

    IrSensor(io::Position pin);

    uint16_t read();

    bool detect();
    void detectRange(uint8_t distance);
    bool detectDistanceToPark(uint8_t distance1, uint8_t distance2);

    void park();
    void find();

    bool objectFound();

private:
    Led led = Led(&DDRB, &PORTB, PB0, PB1); // should be removed
    static const uint8_t N_MEASURMENTS_ = 6;

    const io::Position pin_;
    AnalogReader reader_;
    Side side_;
    Range range_;
    bool objectFound_ = 0;
};

#endif
