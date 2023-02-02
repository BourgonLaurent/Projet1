#ifndef INTERRUPTBUTTON_H
#define INTERRUPTBUTTON_H

#include <avr/io.h>

class InterruptButton
{
public:
    enum class Mode
    {
        ANY,
        FALLING,
        RISING,
    };

    static void initialize();

    static void start();
    static void stop();

    static void waitForDebounce();

    static void setMode(const Mode& mode);

    static void whenPressed();

private:
    static constexpr uint8_t DEBOUNCE_DELAY_MS = 30;
};

#endif