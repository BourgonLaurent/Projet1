#ifndef TIMER_H
#define TIMER_H

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

    enum class PrescaleMode
    {
        CLK,
        CLK1024
    };
    static void setPrescaleMode(const PrescaleMode &prescaleMode);
};

#endif