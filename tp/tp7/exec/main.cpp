/**
 * Tests all components of lib1900.
 *
 * Switching between programs takes 5 seconds.
 *  - Green: alternate speed and direction of wheels.
 *  - Red: send value of photoresistance every 5 seconds.
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 *
 * Hardware Identification
 * INPUT:
 *  - Photoresistance connected to A0.
 *  - Push button connected to D2.
 *
 * OUTPUT:
 *  - Led connected plus to B0, and minus to B1.
 *  - H-bridge, connected left  to PD6 (enable) and PD4 (direction).
 *              connected right to PD7 (enable) and PD5 (direction).
 *
 *
 * Implements the following state table:
 *  --------- Note ---------
 *  Button: Released -> 0
 *          Pressed  -> 1
 *  ------------------------
 *
 *  +-----------------+--------+----------------+-------+
 *  | CURRENT PROGRAM | BUTTON |  NEXT PROGRAM  |  LED  |
 *  +=================+========+================+=======+
 *  |                 |    0   |     WHEELS     |       |
 *  |      WHEELS     +--------+----------------+ GREEN +
 *  |                 |    1   |     LIGHTS     |       |
 *  +-----------------+--------+----------------+-------+
 *  |                 |    0   |     LIGHTS     |       |
 *  |      LIGHTS     +--------+----------------+  RED  +
 *  |                 |    1   |     WHEELS     |       |
 *  +-----------------+--------+----------------+-------+
 */

#include <avr/io.h>
#include <util/delay.h>

#include <lib/analogReader.hpp>
#include <lib/communication.hpp>
#include <lib/debug.hpp>
#include <lib/interruptButton.hpp>
#include <lib/interruptTimer.hpp>
#include <lib/interrupts.hpp>
#include <lib/led.hpp>
#include <lib/memory.hpp>
#include <lib/wheels.hpp>

volatile bool isButtonPressed = false;
volatile uint8_t counter = 0;

static Memory memory;

enum class Program
{
    WHEELS,
    LIGHTS
};

namespace constants {
    constexpr uint16_t TIMEOUT_MS = 5000;

    namespace wheels {
        constexpr uint8_t INCREMENT_EACH_MS = 2;
        constexpr uint8_t N_INCRMENTS = 4;
        constexpr uint8_t PERCENT_TO_UINT = 100;
    } // namespace wheels

    namespace lights {
        constexpr io::Position PHOTORESISTANCE_LOCATION = PA0;

        constexpr uint16_t MESSAGE_START_ADDRESS = 0x0000;
        constexpr const char* MESSAGE = "The photoresistance returns %d\n";
        const uint8_t MESSAGE_SIZE = strlen(MESSAGE);

        constexpr uint8_t MEMORY_READ_DELAY_S = 5;
        constexpr uint8_t MAX_VALUE_SIZE = 3;
    } // namespace lights
} // namespace constants

ISR(InterruptButton_vect)
{
    InterruptButton::waitForDebounce();

    ::isButtonPressed = true;
    debug::send("Button is pressed.\n");

    InterruptButton::clear();
}

ISR(InterruptTimer_vect)
{
    ::counter++;
    debug::send("Timer", ::counter);
}

void runWheels()
{

    InterruptTimer::setSeconds(constants::wheels::INCREMENT_EACH_MS);
    InterruptTimer::start();
    ::counter = 0;

    bool isWheelsForward = true;

    while (true) {
        if (::isButtonPressed) {
            Wheels::turnOff();
            InterruptTimer::stop();
            return;
        }

        if (::counter > constants::wheels::N_INCRMENTS) {
            ::counter = 0;
            isWheelsForward = !isWheelsForward;
        }

        Wheels::setDirection(isWheelsForward ? Wheels::Direction::FORWARD
                                             : Wheels::Direction::BACKWARD);

        const uint8_t leftWheelSpeed =
            (::counter * constants::wheels::PERCENT_TO_UINT)
            / constants::wheels::N_INCRMENTS;

        Wheels::setSpeed(leftWheelSpeed, Wheels::Side::LEFT);
        Wheels::setSpeed(constants::wheels::PERCENT_TO_UINT - leftWheelSpeed,
                         Wheels::Side::RIGHT);
    }
}

void runLights()
{
    const uint8_t formattedMessageSize =
        constants::lights::MESSAGE_SIZE + constants::lights::MAX_VALUE_SIZE;
    const char* formatMessage =
        ::memory.readMessage(constants::lights::MESSAGE_START_ADDRESS,
                             constants::lights::MESSAGE_SIZE);

    AnalogReader reader;
    InterruptTimer::setSeconds(constants::lights::MEMORY_READ_DELAY_S);

    InterruptTimer::start();
    ::counter = 0;
    while (true) {
        if (::isButtonPressed) {
            return;
        }

        if (::counter >= 1) {
            const uint8_t readValue =
                reader.read(constants::lights::PHOTORESISTANCE_LOCATION);

            char formattedMessage[formattedMessageSize];
            snprintf(formattedMessage, formattedMessageSize, formatMessage,
                     readValue);
            Communication::send(formattedMessage);

            ::counter = 0;
        }
    }
}

int main()
{
    Communication::initialize();
    debug::initialize();

    io::setInput(&DDRA, constants::lights::PHOTORESISTANCE_LOCATION);

    Led led(&DDRB, &PORTB, PB0, PB1);

    Wheels::initialize();

    InterruptButton::initialize(InterruptButton::Mode::RISING);
    InterruptTimer::initialize(InterruptTimer::Mode::CLEAR_ON_COMPARE, 0);

    ::memory.writeMessage(constants::lights::MESSAGE_START_ADDRESS,
                          constants::lights::MESSAGE);

    Program program = Program::WHEELS;

    while (true) {
        InterruptButton::clear();
        ::isButtonPressed = false;
        interrupts::startCatching();

        debug::send("Program", (uint8_t)program);
        switch (program) {
            case Program::WHEELS :
                led.setColor(Led::Color::GREEN);
                runWheels();
                program = Program::LIGHTS;
                break;

            case Program::LIGHTS :
                led.setColor(Led::Color::RED);
                runLights();
                program = Program::WHEELS;
                break;
        }

        interrupts::stopCatching();
        led.setAmberForMs(constants::TIMEOUT_MS);
    }

    return 0;
}
