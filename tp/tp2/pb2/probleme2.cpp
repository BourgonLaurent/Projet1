/*
 * Name: TP2 problème 1
 Authors: Catalina Andrea Araya Figueroa and Ihsane
 Date:January 23, 2023
 Hardware indentification:
    INPUT: button connected to D2
    OUTPUT: LED connected to A0 and A1
 *
 * Description: This program turn a LED green, red or ambre depending on the state of the machine.
 *
 *
 *State Table:
 * +---------------+----+------------+-------+
| Current state | D2 | Next state | DEL   |
+---------------+----+------------+-------+
| RED1          | 0  | RED1       | Red   |
+---------------+----+------------+-------+
| RED1          | 1  | AMBRE      | Red   |
+---------------+----+------------+-------+
| AMBRE         | 0  | GREEN1     | Ambre |
+---------------+----+------------+-------+
| AMBRE         | 1  | AMBRE      | Ambre |
+---------------+----+------------+-------+
| GREEN1        | 0  | GREEN1     | Green |
+---------------+----+------------+-------+
| GREEN1        | 1  | RED2       | Green |
+---------------+----+------------+-------+
| RED2          | 0  | OFF        | Red   |
+---------------+----+------------+-------+
| RED2          | 1  | RED2       | Red   |
+---------------+----+------------+-------+
| OFF           | 0  | OFF        | Off   |
+---------------+----+------------+-------+
| OFF           | 1  | GREEN2     | Off   |
+---------------+----+------------+-------+
| GREEN2        | 0  | RED1       | Green |
+---------------+----+------------+-------+
| GREEN2        | 1  | GREEN2     | Green |
+---------------+----+------------+-------+
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_RED = 1 << PA1;
const uint8_t LED_OFF = 0;
const uint8_t MASK_D2 = 1 << PD2;
const uint8_t DELAY_DEBOUNCE = 10;
const uint8_t DELAY_COLOR_AMBRE = 5;

enum class States
{
    RED1,
    AMBRE,
    GREEN1,
    RED2,
    OFF,
    GREEN2
};
States state = States::RED1;

void ledAmbreColor()
{
    PORTA = LED_GREEN;
    _delay_ms(DELAY_COLOR_AMBRE);
    PORTA = LED_RED;
    _delay_ms(DELAY_COLOR_AMBRE);
    return;
}

bool isPressed()
{
    return (PIND & MASK_D2);
}
bool verifyButton()
{
    if (firstPress())
    {
        _delay_ms(DELAY_DEBOUNCE);
        return (firstPress());
    }

    return false;
}

void setNextState()
{

    switch (state)
    {
    case States::RED1:
        if (isPressed())
            state = States::AMBRE;
        break;

    case States::AMBRE:

        if (!isPressed())
            state = States::GREEN1;
        break;

    case States::GREEN1:
        if (isPressed())
            state = States::RED2;
        break;

    case States::RED2:
        if (!isPressed())
            state = States::OFF;
        break;

    case States::OFF:
        if (isPressed())
            state = States::GREEN2;
        break;

    case States::GREEN2:
        if (!isPressed())
            state = States::RED1;
        break;
    }
}

void setColorLed()
{

    switch (state)
    {
    case States::RED1:
    case States::RED2:
        PORTA = LED_RED;
        break;

    case States::AMBRE:
        ledAmbreColor();
        break;

    case States::GREEN1:
    case States::GREEN2:
        PORTA = LED_GREEN;
        break;

    case States::OFF:
        PORTA = LED_OFF;
        break;
    }
}

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    while (true)
    {
        setNextState();
        setColorLed();
    }

    return 0;
}
