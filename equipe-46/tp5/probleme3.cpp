
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
uint8_t message[17] = {'P', 'O', 'L', 'Y', 'T', 'E', 'C', 'H', 'N', 'I', 'Q', 'U', 'E', ' ', 'M', 'T', 'L'};

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

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;
    initialisationUART();

    memoire_24.ecriture(adresse, message, 17);
    _delay_ms(15);
    uint8_t valeurLecture[17];
    memoire_24.lecture(adresse, valeurLecture, 17);

    for (uint8_t j = 0; j < 17; j++)
    {
        transmissionUART(valeurLecture[j]);
    }

    return 0;
}
// char mots[21] = "Le robot en INF1900\n";