
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
uint8_t message2[17] = {'P', 'O', 'L', 'Y', 'T', 'E', 'C', 'H', 'N', 'I', 'Q', 'U', 'E', ' ', 'M', 'T', 'L'};

void allumeLed()
{
    uint8_t valeurLecture[17];
    memoire_24.lecture(adresse, valeurLecture, 17);
    for (uint8_t i = 0; i < 17; i++)
    {
        if (valeurLecture[i] == message2[i])
        {
            if (i = 16)
                PORTA = LED_GREEN;
            else
                continue;
        }
        if (valeurLecture[i] != message2[i])
        {
            PORTA = LED_RED;
            break;
        }
    }
}

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;
    PORTA = LED_OFF;
    memoire_24.ecriture(adresse, message, 17);
    _delay_ms(15);
    allumeLed();

    return 0;
}
