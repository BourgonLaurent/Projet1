/**
 *
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 7, 2023
 */

#define F_CPU 8000000UL
#include <avr/io.h>

#include <tp2/components/colors.hpp>
#include <tp2/components/io.hpp>
#include <tp2/components/led.hpp>

#include <tp5/memory/memoire_24.hpp>

int main()
{
    uint8_t myString[] = {'y', 'o', 'm', 'a', 'm', 'a'};
    uint8_t lect[6];
    Memoire24CXXX memory = Memoire24CXXX();
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    memory.ecriture(0x0000, myString, sizeof(myString) - 1);

    memory.lecture(0x0000, lect, 6);
    if (myString == lect) {
        led.setColor(Color::GREEN);
    }
    else {
        led.setColor(Color::RED);
    }
    led.setColor(Color::OFF);

    return 0;
}
