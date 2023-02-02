#ifndef INTERRUPTTIMER_H
#define INTERRUPTTIMER_H

#define F_CPU 8000000UL

#include <avr/io.h>

class InterruptTimer
{
public:
    static void initialize();

    enum class Mode
    {
        NORMAL,
        CTC,
    };
    static void setMode(const Mode& mode);

    enum class PrescaleMode
    {
        CLK,
        CLK1024
    };
    static void setPrescaleMode(const PrescaleMode& prescaleMode);

    static void whenFinished();

    static void setSecondsDelay(uint8_t delayS);

    static void start();
    static void stop();
    static void reset();

private:
    static constexpr uint16_t CYCLES_PER_SECOND = F_CPU / 1024;
};

#endif