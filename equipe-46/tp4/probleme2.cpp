
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_RED = 1 << PA1;
const uint8_t LED_OFF = 0;
const uint8_t MASK_D2 = 1 << PD2;
const uint8_t DELAY_DEBOUNCE = 10;
const uint8_t DELAY_COLOR_AMBRER = 5;
volatile uint8_t gMinuterieExpiree;
volatile uint8_t gBoutonPoussoir;

void starTime()
{
    gMinuterieExpiree = 0;
    cli();
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = (1 << CS10) | (1 << CS12);
    TCCR1C = 0;
    OCR1A = 7812;
    TIMSK1 = (1 << OCIE1A) | (1 << OCIE1B);
    sei();
}

void initialisation(void)
{
    cli();
    DDRA = 0xff;
    DDRD = 0x00;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    starTime();
    sei();
}

ISR(INT0_vect)
{
    gBoutonPoussoir = 1;
    _delay_ms(10);
    EIFR |= (1 << INTF0);
    PORTA |= _BV(PA0);
}

ISR(TIMER1_COMPA_vect)
{

    gMinuterieExpiree = 1;
    PORTA |= _BV(PA1);
}

int main()
{

    _delay_ms(1000);
    PORTA |= _BV(PA1);
    initialisation();
    _delay_ms(100);
    PORTA &= ~_BV(PA1);

    do
    {

    } while (gMinuterieExpiree == 0 && gBoutonPoussoir == 0);

    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli();

    // Verifier la réponse

    return 0;
}
