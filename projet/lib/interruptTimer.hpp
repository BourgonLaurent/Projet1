/**
 * Interrupt program with a timer.
 *
 * Hardware Identification
 *  TIMER: Timer 1.
 *
 * USAGE: Use `InterruptTimer_vect` inside the ISR.
 *    ISR(InterruptTimer_vect)
 *    {
 *        ...
 *    }
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date February 2, 2023
 */

#ifndef INTERRUPTTIMER_H
#define INTERRUPTTIMER_H

#include <avr/interrupt.h>
#include <avr/io.h>

#include <lib/interrupts.hpp>

#define InterruptTimer_vect TIMER1_COMPA_vect

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
    static void setMilliseconds(const uint16_t delayMs);

    static void initialize(const Mode &mode, const double delayS);

    static void reset();
    static void start();
    static void stop();

private:
    static constexpr uint16_t MS_TO_S = 1000;

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
