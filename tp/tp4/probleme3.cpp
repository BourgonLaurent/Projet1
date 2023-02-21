
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

void ajustementPwm(uint16_t valeur)
{
    OCR1A = valeur;
    OCR1B = valeur;
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

int main()
{

    // _delay_ms(1000);
    // PORTA |= _BV(PA1);
    // initialisation();
    // _delay_ms(100);
    // PORTA &= ~_BV(PA1);

    DDRD = 0x30;
    for (uint8_t i = 64; i < 257; i += 64)
    {
        ajustementPwm(i);
        _delay_ms(2000);
    }

    // Verifier la réponse

    return 0;
}
