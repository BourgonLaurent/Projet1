/**
 *
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 7, 2023
 */

#define F_CPU 8000000UL

#include <string.h>
#include <tp2/components/io.hpp>
#include <tp5/components/usart.hpp>
#include <tp5/memory/memoire_24.hpp>

int main()
{
    Memoire24CXXX mem = Memoire24CXXX();
    Usart::initialize();

    for (uint8_t i = 0; i < 0xFF; i++) {
        uint8_t* readValuePtr;
        mem.lecture(i, readValuePtr);

        Usart::transmit(*readValuePtr);
    }

    return 0;
}
