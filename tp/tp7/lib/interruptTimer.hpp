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
 *
 * Hardware Identification
 * TIMER: Timer 1.
 */

#ifndef INTERRUPTTIMER_H
#define INTERRUPTTIMER_H

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

    static void reset();
    static void start();
    static void stop();

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

    static void setBestPrescaleMode(const double delayS);
    static void setPrescaleMode(const PrescaleMode &prescaleMode);
    static PrescaleMode getCeiledPrescaleMode(const uint16_t idealPrescale);
    static PrescaleMode getPrescaleMode();

    static uint16_t getCyclesPerSeconds();
};

#endif
