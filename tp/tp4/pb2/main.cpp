#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/colors.hpp>
#include <tp2/components/led.hpp>

constexpr uint16_t CYCLES_PER_SECOND = F_CPU / 1024;
constexpr uint8_t TIMER_DURATION_S = 1;
constexpr uint16_t TIMER_CYCLES = CYCLES_PER_SECOND * TIMER_DURATION_S;

constexpr uint16_t WAIT_DURATION_MS = 10000;
constexpr uint8_t FLASH_DURATION_MS = 100;

volatile bool waitForUser = false;
volatile bool userWon = false;

void clearInterrupts()
{
    EIFR |= _BV(INTF0);
}

ISR(TIMER1_COMPA_vect)
{
    if (::waitForUser) {
        ::userWon = false;
        ::waitForUser = false;
    }

    clearInterrupts();
}

ISR(INT0_vect)
{
    if (::waitForUser) {
        ::userWon = true;
    }

    clearInterrupts();
}

void prepareInterrupts()
{
    cli();

    // (p.68) allow interruptions
    EIMSK |= _BV(INT0);

    // (p.67) rising edge
    EICRA |= _BV(ISC00) | _BV(ISC01);

    sei();
}

void startTimer()
{
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

    OCR1A = TIMER_CYCLES; // Output Compare Register

    sei();
}

int main()
{
    DDRD &= ~_BV(PD2);
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    prepareInterrupts();

    _delay_ms(WAIT_DURATION_MS);

    led.setColor(Color::RED);
    _delay_ms(FLASH_DURATION_MS);
    led.setColor(Color::OFF);

    startTimer();
    ::waitForUser = true;

    while (::waitForUser && !::userWon) {
    }

    cli();

    led.setColor(::userWon ? Color::GREEN : Color::RED);

    EICRA |= _BV(ISC00) | _BV(ISC01);
    return 0;
}
