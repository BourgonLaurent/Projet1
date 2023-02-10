/**
 * Problem 2:
 *  Send with RS232.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 9, 2023
 */

#define F_CPU 8000000UL

#include <string.h>

#include <tp2/components/io.hpp>
#include <tp5/components/usart.hpp>

int main()
{
    Usart::initialize();
    const char* words = "L'equipe de Laurent et Mehdi\n";

    for (uint8_t i = 0; i < 100; i++) {
        Usart::transmit(words);
    }

    return 0;
}
