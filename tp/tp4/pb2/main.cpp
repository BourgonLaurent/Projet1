#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/colors.hpp>
#include <tp2/components/led.hpp>

constexpr uint8_t DEBOUNCE_DELAY_MS = 10;
constexpr uint8_t FLASH_DURATION_MS = 100;

constexpr uint16_t CYCLES_PER_SECOND = F_CPU / 1024;
constexpr uint8_t FLASHING_DELAY_S = 1;
constexpr uint16_t FLASHING_CYCLES = CYCLES_PER_SECOND * FLASHING_DELAY_S;

constexpr uint16_t WAIT_DURATION_MS = 5000;

volatile bool buttonWasPressed = false;
volatile bool waitForUser = false;
volatile bool userFailed = false;

LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

void clearInterrupts()
{
    EIFR |= _BV(INTF0);
}

ISR(TIMER1_COMPA_vect)
{
    if (::waitForUser) {
        ::userFailed = true;
    }
    else {
        ::led.setColor(Color::RED);
        _delay_ms(100);
        ::led.setColor(Color::OFF);
    }

    clearInterrupts();
}

ISR(INT0_vect)
{
    if (::waitForUser) {
        ::buttonWasPressed = true;
    }

    clearInterrupts();
}

void prepareInterrupts()
{
    cli();

    // (p.68) allow interruptions
    EIMSK |= _BV(INT0);

    // (p.67) falling + rising edge
    EICRA |= _BV(ISC00);
    EICRA &= ~_BV(ISC01);

    // mode CTC du timer 1 avec horloge divisée par 1024 (p. 130)
    TCCR1B |= _BV(WGM12);
    TCCR1B &= ~_BV(WGM13);
    TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));

    // prescale at 1024
    TCCR1B |= _BV(CS10) | _BV(CS12);
    TCCR1B &= ~_BV(CS11);

    // interruption après la durée spécifiée
    TCNT1 = 0; // counter
    TCCR1C = 0;
    TIMSK1 |= _BV(OCIE1A);

    OCR1A = FLASHING_CYCLES; // Output Compare Register

    sei();
}

int main()
{
    DDRD &= ~_BV(PD2);

    prepareInterrupts();

    _delay_ms(WAIT_DURATION_MS);
    ::waitForUser = true;
    TCNT1 = 0;

    do {
        ::led.setColor(Color::OFF);
    } while (!::buttonWasPressed && !::userFailed);

    cli();

    if (::userFailed) {
        ::led.setColor(Color::RED);
    }
    else {
        ::led.setColor(Color::GREEN);
    }

    EICRA |= _BV(ISC00) | _BV(ISC01);
    return 0;
}
