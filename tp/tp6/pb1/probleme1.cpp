
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <memoire_24.h>

const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_RED = 1 << PA1;
const uint8_t LED_OFF = 0;
const uint8_t MASK_D2 = 1 << PD2;
const uint8_t DELAY_DEBOUNCE = 10;
const uint8_t DELAY_COLOR_AMBRER = 5;
volatile uint8_t gBoutonPoussoir = 0;
volatile uint8_t change = 0;
volatile uint8_t compteur = 0;

void initialisationUART(void)
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // permettre la réception et la transmission par le UART0
    // (1 << U2X0)
    UCSR0A = (1 << MPCM0) | (1 << UDRE0) | (1 << RXC0);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Format des trames: 8 bits, 1 stop bits, sans parité
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

// Du USART vers le PC

void transmissionUART(uint8_t donnee)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = donnee;
}

bool isPressed()
{
    return (PIND & MASK_D2);
}
bool debounceButton()
{
    if (isPressed())
    {
        _delay_ms(DELAY_DEBOUNCE);
        return (isPressed());
    }

    return false;
}

void starTime()
{
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
    sei();
}

enum class States
{
    READY,
    WAIT,
    GREEN1,
    RED1,
    GREEN2
};
volatile States state = States::READY;

void setNextState()
{
    switch (state)
    {
    case States::READY:
        if (gBoutonPoussoir == 1)
        {
            state = States::WAIT;
            gBoutonPoussoir = 0;
        }
        break;

    case States::WAIT:
        if ((compteur == 120) || (gBoutonPoussoir == 1))
        {
            state = States::GREEN1;
            gBoutonPoussoir = 0;
        }

    case States::GREEN1:
        if (change == 1)
        {
            change = 0;
            state = States::RED1;
        }
        break;

    case States::RED1:
        if (change == 1)
        {
            change = 0;
            state = States::GREEN2;
        }
        break;

    case States::GREEN2:
        if (change == 1)
        {
            change = 0;
            state = States::READY;
        }
        break;
    }
}

void setColorLed()
{

    switch (state)
    {
    case States::RED1:
        for (uint8_t i = 0; i < compteur / 2; i++)
        {
            PORTA = LED_RED;
            _delay_ms(500);
            PORTA = LED_OFF;
            _delay_ms(500);
        }
        change = 1;
        break;

    case States::GREEN1:
        for (uint8_t i = 0; i < 5; i++)
        {
            PORTA = LED_GREEN;
            _delay_ms(50);
            PORTA = LED_OFF;
            _delay_ms(50);
        }
        change = 1;
        break;

    case States::GREEN2:
        PORTA = LED_GREEN;
        _delay_ms(1000);
        change = 1;
        break;

    case States::READY:
    case States::WAIT:
        PORTA = LED_OFF;
        break;
    }
}

ISR(INT0_vect)
{
    _delay_ms(10);
    gBoutonPoussoir = 1;
    EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect)
{
    compteur += 10;
}

int main()
{
    DDRA = 0xff;

    initialisation();

    while (true)
    {
        transmissionUART(compteur);
        setNextState();
        setColorLed();
    }

    return 0;
}
