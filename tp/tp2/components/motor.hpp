/**
 * TODO Describe header file
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 26, 2023
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

class Motor
{
public:
    Motor(
        volatile uint8_t *dataDirectionRegister,
        volatile uint8_t *port,

        const uint8_t pulseWidthModulationPin,
        const uint8_t directionPin

    );

private:
    volatile uint8_t *port_;

    const uint8_t pulseWidthModulationPin_;
    const uint8_t directionPin_;
};

#endif
