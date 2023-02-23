/**
 * Control 16-bit Timer 1.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

class Timer
{
public:
    enum class Mode
    {
        NORMAL,
        CTC,
        PWM_PHASE_CORRECT
    };
    static void setMode(const Mode &mode);

    enum class PrescaleMode : uint16_t
    {
        CLK = 1,
        CLK1024 = 1024
    };
    static void setPrescaleMode(const PrescaleMode &prescaleMode);

protected:
    static uint16_t getPrescaleValue();
    static PrescaleMode prescaleMode_;
};

#endif
