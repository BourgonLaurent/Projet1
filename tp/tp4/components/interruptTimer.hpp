/**
 * Interrupt a program with a timer.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 2, 2023
 */

#ifndef INTERRUPTTIMER_H
#define INTERRUPTTIMER_H

#define F_CPU 8000000UL

#include <avr/io.h>

#include <tp4/components/timer.hpp>

class InterruptTimer : public Timer
{
public:
    static void initialize();

    static void setSeconds(const double delayS);

    static void start();
    static void stop();
    static void reset();

    static void whenFinished();

private:
    static uint16_t getCyclesPerSeconds();
};

#endif
