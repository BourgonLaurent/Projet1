/**
 * TODO Describe file
 *
 * Hardware Identification:
 * TODO describe hardware identification
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 26, 2023
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <tp2/components/io.hpp>

#include "motor.hpp"

Motor::Motor(
    volatile uint8_t *dataDirectionRegister,
    volatile uint8_t *port,

    const uint8_t pulseWidthModulationPin,
    const uint8_t directionPin) : port_(port),
                                  pulseWidthModulationPin_(pulseWidthModulationPin),
                                  directionPin_(directionPin)
{
    IO::setOutput(dataDirectionRegister, pulseWidthModulationPin);
    IO::setOutput(dataDirectionRegister, directionPin);
}