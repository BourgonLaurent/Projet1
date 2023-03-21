/**
 * Run a program in memory.
 *
 * Hardware Identification
 * OUTPUT:
 *  - LED, connected plus to B0, and minus to B1.
 *  - Buzzer, connected plus to B3 and minus to B2.
 *  - H-bridge, connected left  to PD6 (enable) and PD4 (direction).
 *              connected right to PD7 (enable) and PD5 (direction).
 *
 * USAGE:
 *  Interpreter interpreter(0x00000000);
 *  interpreter.run();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 16, 2023
 */

#include <avr/io.h>

#include <lib1900/led.hpp>
#include <lib1900/memory.hpp>

class Interpreter
{
public:
    Interpreter(const uint16_t startAddress);
    void run();

private:
    void fetch();
    void execute();

    static constexpr uint8_t WAIT_FACTOR_MS = 25;

    bool isStarted_ = false;

    uint16_t currentAddress_;
    uint16_t endAddress_;

    uint8_t currentOpcode_ = 0x00;
    uint8_t currentOperand_ = 0x00;

    uint8_t loopStartAddress_ = 0x00;
    uint8_t loopCounter_ = 0;

    Led led_ = Led(&DDRB, &PORTB, PB0, PB1);
    Memory memory_;

    enum Instruction : uint8_t
    {
        DBT = 0x01,
        ATT = 0x02,
        DAL = 0x44,
        DET = 0x45,
        SGO = 0x48,
        SAR = 0x09,
        MAR = 0x60,
        MAR2 = 0x61,
        MAV = 0x62,
        MRE = 0x63,
        TRD = 0x64,
        TRG = 0x65,
        DBC = 0xc0,
        FBC = 0xc1,
        FIN = 0xff
    };

    enum LedOperand : uint8_t
    {
        GREEN = 1,
        RED = 2
    };
};
