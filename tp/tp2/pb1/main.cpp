/**
 * Problem 1:
 *  Press three times the push button to turn the LED green.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 17, 2023
 *
 * Hardware Identification
 * INPUT: Push button connected to D2 with a jumper.
 * OUTPUT: Bicolor LED connected plus to A0 and minus to A1.
 *
 * Implements the following state table:
 *  Note: For the Button input:
 *      0: Released
 *      1: Pressed
 * +---------------+--------+--------------+-------+
 * | CURRENT STATE | BUTTON |  NEXT STATE  |  LED  |
 * +===============+========+==============+=======+
 * |               |    0   |     INIT     |       |
 * |      INIT     +--------+--------------+  OFF  +
 * |               |    1   |  FIRST_PRESS |       |
 * +---------------+--------+--------------+-------+
 * |               |    0   |  FIRST_PRESS |       |
 * |  FIRST_PRESS  +--------+--------------+  OFF  +
 * |               |    1   | SECOND_PRESS |       |
 * +---------------+--------+--------------+-------+
 * |               |    0   | SECOND_PRESS |       |
 * |  SECOND_PRESS +--------+--------------+  OFF  +
 * |               |    1   |  THIRD_PRESS |       |
 * +---------------+--------+--------------+-------+
 * |  THIRD_PRESS  |    x   |     INIT     | GREEN |
 * +---------------+--------+--------------+-------+
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/colors.hpp>
#include <tp2/components/led.hpp>

constexpr uint16_t COLOR_DELAY_MS = 2000;

enum class MachineState
{
    INIT,
    FIRST_PRESS,
    SECOND_PRESS,
    THIRD_PRESS
};

int main()
{
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);
    Button button = Button(&DDRD, &PIND, PIND2);

    MachineState currentState = MachineState::INIT;
    while (true) {
        switch (currentState) {
            case MachineState::INIT :
                led.setColor(Color::OFF);

                while (button.isPressed()) {
                    currentState = MachineState::FIRST_PRESS;
                }
                break;

            case MachineState::FIRST_PRESS :
                led.setColor(Color::OFF);

                while (button.isPressed()) {
                    currentState = MachineState::SECOND_PRESS;
                }
                break;

            case MachineState::SECOND_PRESS :
                led.setColor(Color::OFF);

                while (button.isPressed()) {
                    currentState = MachineState::THIRD_PRESS;
                }
                break;

            case MachineState::THIRD_PRESS :
                led.setColor(Color::GREEN);
                _delay_ms(COLOR_DELAY_MS);

                currentState = MachineState::INIT;
                break;
        }
    }

    return 0;
}
