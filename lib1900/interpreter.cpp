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

#include "interpreter.hpp"

#include <util/delay.h>

#include <lib1900/debug.hpp>
#include <lib1900/led.hpp>
#include <lib1900/sound.hpp>
#include <lib1900/wheels.hpp>

Interpreter::Interpreter(const uint16_t startAddress)
    : currentAddress_(startAddress)
{
    const uint8_t mostSignificativeSizeBits = memory_.read(currentAddress_);

    currentAddress_++;
    const uint8_t leastSignificativeSizeBits = memory_.read(currentAddress_);

    constexpr uint8_t maxBitsForSize = 16;
    constexpr uint8_t nMessagesForSize = 2;
    constexpr uint8_t bitsPerMessage = maxBitsForSize / nMessagesForSize;
    const uint16_t nMessages = ((mostSignificativeSizeBits << bitsPerMessage)
                                | leastSignificativeSizeBits);

    endAddress_ = startAddress + nMessages - 1;
}

void Interpreter::run()
{
    while (currentOpcode_ != Instruction::FIN
           && currentAddress_ < endAddress_) {
        fetch();
        execute();
    }
}

void Interpreter::fetch()
{
    currentAddress_++;
    debug::send("---------\n");
    debug::send("Address", currentAddress_);
    currentOpcode_ = memory_.read(currentAddress_);
    debug::send("Opcode", currentOpcode_);

    currentAddress_++;
    currentOperand_ = memory_.read(currentAddress_);
    debug::send("Operand", currentOperand_);
}

void Interpreter::execute()
{
    if (currentOpcode_ == Instruction::DBT) {
        isRunning_ = true;
    }

    if (!isRunning_) {
        return;
    }

    switch (currentOpcode_) {
        case Instruction::DBT :
            Wheels::initialize();
            Sound::initialize();
            break;

        case Instruction::ATT : {
            constexpr uint8_t waitFactorMs = 25;

            for (uint8_t i = 0; i < currentOperand_; i++) {
                _delay_ms(waitFactorMs);
            }
            break;
        }

        case Instruction::DAL : {
            constexpr uint8_t greenOperand = 1;
            constexpr uint8_t redOperand = 2;

            switch (currentOperand_) {
                case greenOperand :
                    led_.setColor(Led::Color::GREEN);
                    break;

                case redOperand :
                    led_.setColor(Led::Color::RED);
                    break;
            }
            break;
        }

        case Instruction::DET :
            led_.setColor(Led::Color::OFF);
            break;

        case Instruction::SGO :
            Sound::playNote(currentOperand_);
            break;

        case Instruction::SAR :
            Sound::stop();
            break;

        case Instruction::MAR :
        case Instruction::MAR2 :
            Wheels::turnOff();
            break;

        case Instruction::MAV :
            Wheels::setDirection(Wheels::Direction::FORWARD);
            Wheels::setSpeed(currentOperand_ * 100 / 255);
            break;

        case Instruction::MRE :
            Wheels::setDirection(Wheels::Direction::BACKWARD);
            Wheels::setSpeed(currentOperand_ * 100 / 255);
            break;

        case Instruction::TRD :
            Wheels::turn(Wheels::Side::RIGHT);
            break;

        case Instruction::TRG :
            Wheels::turn(Wheels::Side::LEFT);
            break;

        case Instruction::DBC :
            loopStartAddress_ = currentAddress_;
            loopCounter_ = currentOperand_;
            break;

        case Instruction::FBC :
            if (loopCounter_ > 0) {
                loopCounter_--;
                currentAddress_ = loopStartAddress_;
            }
            break;

        case Instruction::FIN :
            Wheels::turnOff();
            Sound::stop();
            break;
    }
}
