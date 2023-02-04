#ifndef INTERRUPTTIMER_H
#define INTERRUPTTIMER_H

#define F_CPU 8000000UL

#include <avr/io.h>

#include <tp4/components/timer.hpp>

class InterruptTimer : public Timer
{
public:
    static void initialize();

    static void setSeconds(uint8_t delayS);

    static void start();
    static void stop();
    static void reset();

    static void whenFinished();

private:
    static constexpr uint16_t CYCLES_PER_SECOND = F_CPU / 1024;
};

#endif
