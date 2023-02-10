/**
 * Problem 1:
 *  Write to memory.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 7, 2023
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/io.hpp>
#include <tp2/components/led.hpp>

#include <tp5/memory/memoire_24.hpp>

constexpr const char* MESSAGE = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
const size_t MESSAGE_SIZE = strlen(MESSAGE) + 1;
constexpr uint16_t START_ADDRESS = 0x0000;

int main()
{
    LED feedbackLed = LED(&DDRA, &PORTA, PORTA0, PORTA1);
    Memoire24CXXX memory = Memoire24CXXX();

    memory.ecriture(START_ADDRESS, (uint8_t*)MESSAGE, MESSAGE_SIZE);
    _delay_ms(5);

    char readString[MESSAGE_SIZE];
    memory.lecture(START_ADDRESS, (uint8_t*)readString, MESSAGE_SIZE);

    if (strcmp(MESSAGE, (const char*)readString) == 0) {
        feedbackLed.setColor(Color::GREEN);
    }
    else {
        feedbackLed.setColor(Color::RED);
    }

    return 0;
}
