
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "memoire_24.h"

const uint16_t adresse = 0x0000;
Memoire24CXXX memoire_24;
const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_RED = 1 << PA1;
const uint8_t LED_OFF = 0;

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

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
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main()
{
    initialisationUART();
    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;

    for (i = 0; i < 100; i++)
    {

        for (j = 0; j < 20; j++)
        {

            transmissionUART(mots[j]);
        }
    }

    return 0;
}
