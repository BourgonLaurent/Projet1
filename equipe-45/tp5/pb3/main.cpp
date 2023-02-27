/**
 * Problem 3:
 *  Send memory with RS232.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 9, 2023
 */

#define F_CPU 8000000UL

#include <string.h>

#include <tp5/components/usart.hpp>
#include <tp5/memory/memoire_24.hpp>

constexpr uint8_t MESSAGE_LENGTH = 0xFF;

int main()
{
    Memoire24CXXX memory = Memoire24CXXX();
    Usart::initialize();

    for (uint8_t i = 0; i < MESSAGE_LENGTH; i++) {
        uint8_t readValue;
        memory.lecture(i, &readValue);

        Usart::transmit(readValue);
    }

    return 0;
}
