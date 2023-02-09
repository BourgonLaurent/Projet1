#include "usart.hpp"

void Usart::initialize()
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    io::setActive(&UCSR0A, UDRE0);

    io::setActive(&UCSR0B, RXEN0);
    io::setActive(&UCSR0B, TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    // 8 bits
    io::clear(&UCSR0C, UCSZ02);
    io::setActive(&UCSR0C, UCSZ01);
    io::setActive(&UCSR0C, UCSZ00);

    // 1 stop bit
    io::clear(&UCSR0C, USBS0);

    // sans parite
    io::clear(&UCSR0C, UPM01);
    io::clear(&UCSR0C, UPM00);
}

void Usart::transmit(uint8_t data)
{
    while (!(UCSR0A & _BV(UDRE0))) {}

    UDR0 = data;
}

void Usart::transmit(char data[], uint8_t dataLength)
{
    for (uint8_t i = 0; i < dataLength; i++) {

        Usart::transmit(data[i]);
    }
}