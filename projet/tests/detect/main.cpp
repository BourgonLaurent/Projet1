#include <avr/io.h>
#include <util/delay.h>

#include <lib/constants.hpp>
#include <lib/debug.hpp>
#include <lib/detect.hpp>

#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>

ISR(InterruptTimer_vect)
{
    detect::checkTimerValue();
}

ISR(InterruptButton_vect)
{
    InterruptButton::waitForDebounce();
    detect::state = detect::States::FIND_OBJECT;
    InterruptButton::clear();
}

int main()
{
    detect::run();
}
