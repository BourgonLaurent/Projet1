#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/led.hpp>
#include <tp2/components/colors.hpp>

constexpr uint8_t DEBOUNCE_DELAY_MS = 10;
constexpr uint16_t TIMESPAN_MS = 10'000;
constexpr uint8_t FLASH_DURATION_MS = 100;

volatile uint8_t gExpiredTimespan;
volatile uint8_t gButton;

ISR(TIMER1_COMPA_vect)
{
    gExpiredTimespan = 1;
    _delay_ms(FLASH_DURATION_MS);
    EIFR |= _BV(INTF0);
}

ISR(TIMER1_COMPB_vect)
{
    gButton = 1;
    // Anti-bounce
    // TODO implement anti-bounce
    _delay_ms(DEBOUNCE_DELAY_MS);
    EIFR |= _BV(INTF0);
}

void elapseTimespan(uint16_t duration)
{
    gExpiredTimespan = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024 (p. 130)
    TCCR1B |= _BV(WGM13) | _BV(WGM12);

    TCCR1B |= _BV(CS10) | _BV(CS12);
    TCCR1B &= ~_BV(CS11);
    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duration;

    // page 130
    TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));

    TCCR1C = 0;

    TIMSK1 = _BV(OCIE1A);
}

int main()
{
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    do
    {
        led.setColor(Color::OFF);
        elapseTimespan(TIMESPAN_MS);

        // attendre qu'une des deux variables soit modifiée

        // par une ou l'autre des interruptions.

    } while (gExpiredTimespan == 0 && gButton == 0);

    // Une interruption s'est produite. Arrêter toute

    led.setColor(Color::RED);
    // forme d'interruption. Une seule réponse suffit.

    cli();

    // Verifier la réponse

    // 'modifier ici'

    EICRA |= _BV(ISC00) | _BV(ISC01);
    return 0;
}