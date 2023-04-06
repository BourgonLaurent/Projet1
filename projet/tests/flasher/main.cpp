
#include <avr/io.h>
#include <util/delay.h>

#include <lib/debug.hpp>
#include <lib/flasher.hpp>
#include <lib/led.hpp>

ISR(Flasher_vect)
{
    Flasher::handleFlash();
}

int main()
{
    debug::initialize();
    Led led(&DDRB, &PORTB, PB0, PB1);

    // Flash the LED on and off at 2Hz.
    {
        Flasher::initialize(led, 2, Led::Color::RED, Led::Color::OFF);
        Flasher::startFlashing();
        _delay_ms(2000);
        Flasher::stopFlashing();
    }

    // Show the LED amber.
    {
        Flasher::initializeAmber(led);
        Flasher::startFlashing();
        _delay_ms(2000);
        Flasher::stopFlashing();
    }

    return 0;
}
