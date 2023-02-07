/**
 *
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 7, 2023
 */

#define F_CPU 8000000UL
#include <avr/delay.h>
#include <avr/io.h>
#include <string.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/io.hpp>
#include <tp2/components/led.hpp>

#include <tp5/memory/memoire_24.hpp>

constexpr uint8_t STRING_END_CHAR = 0x00;
constexpr uint16_t ADDRESS = 0x0000;

int main()
{
    Memoire24CXXX memory = Memoire24CXXX();
    LED feedbackLed = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    const char* polytechniqueMontreal =
        "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

    uint8_t readString[sizeof(polytechniqueMontreal)];

    memory.ecriture(ADDRESS, (uint8_t*)polytechniqueMontreal,
                    strlen(polytechniqueMontreal));
    // memory.ecriture(ADDRESS + strlen(polytechniqueMontreal),
    // STRING_END_CHAR);

    _delay_ms(5);

    memory.lecture(ADDRESS, &readString[0], strlen(polytechniqueMontreal));

    // feedbackLed.setColor(Color::RED);
    if (strlen((char*)readString) == strlen(polytechniqueMontreal)) {
        feedbackLed.setColor(Color::GREEN);
        _delay_ms(2000);
    }
    else {
        feedbackLed.setColor(Color::RED);
        _delay_ms(2000);
    }
    // feedbackLed.setColor(Color::OFF);

    return 0;
}
