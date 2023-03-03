/**
 * Interrupt a program with a timer.
 *
 * WARNING: InterruptTimer::whenFinished() must be declared.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#ifndef INTERRUPTTIMER_H
#define INTERRUPTTIMER_H

#define F_CPU 8000000UL

#include <avr/io.h>

class InterruptTimer
{
public:
    enum class Mode
    {
        NORMAL,
        CLEAR_ON_COMPARE
    };
    static void setMode(const Mode &mode);
    static void setSeconds(const double delayS);

    static void initialize(const double delayS, const Mode &mode);

    static void start();
    static void stop();
    static void reset();

    static void whenFinished(); // needs to be declared

private:
    enum class PrescaleMode
    {
        OFF = 0,
        CLK = 1,
        CLK8 = 8,
        CLK64 = 64,
        CLK256 = 256,
        CLK1024 = 1024
    };
    static PrescaleMode prescaleMode_;

    static void setPrescaleMode(const PrescaleMode &prescaleMode);
    static void setBestPrescaleMode(const double delayS);
    static PrescaleMode getFlooredPrescaleMode(const uint16_t idealPrescale);
    static uint16_t getCyclesPerSeconds();
};

#endif
