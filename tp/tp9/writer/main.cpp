/**
 * Write a program to memory.
 * debug: verify what was written.
 *
 * LED indicates status
 *  Red: Ready to write
 *  Green: Written
 *
 * USAGE: Use serieViaUSB.
 *  progmem -v -o program.bin program.txt
 *  <make sure LED is red and robot is connected>
 *  serieViaUSB -d -e -f program.bin
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 14, 2023
 */

#include <lib/communication.hpp>
#include <lib/debug.hpp>
#include <lib/led.hpp>
#include <lib/memory.hpp>

constexpr uint16_t START_ADDRESS = 0x00000000;

int main()
{
    Communication::initialize();
    debug::initialize();

    Led led = Led(&DDRB, &PORTB, PB0, PB1);
    Memory memory;

    led.setColor(Led::Color::RED);
    uint16_t writeAddress = START_ADDRESS;

    const uint8_t mostSignificativeSizeBits = Communication::receive();
    memory.write(writeAddress, mostSignificativeSizeBits);
    writeAddress++;

    const uint8_t leastSignificativeSizeBits = Communication::receive();
    memory.write(writeAddress, leastSignificativeSizeBits);
    writeAddress++;

    constexpr uint8_t maxBitsForSize = 16;
    constexpr uint8_t nMessagesForSize = 2;
    constexpr uint8_t bitsPerMessage = maxBitsForSize / nMessagesForSize;
    const uint16_t nMessages = ((mostSignificativeSizeBits << bitsPerMessage)
                                | leastSignificativeSizeBits);

    for (; writeAddress < nMessages; writeAddress++) {
        memory.write(writeAddress, Communication::receive());
    }

    led.setColor(Led::Color::GREEN);

    debug::send("Size", nMessages);

    for (uint16_t address = START_ADDRESS; address < nMessages; address++) {
        debug::send(memory.read(address));
        debug::send(" ");
    }

    return 0;
}
