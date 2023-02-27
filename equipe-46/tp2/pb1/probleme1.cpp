/*
 * Name: TP2 problème 1
 * Section #: 02
 * Team #: 46

Authors: Majdoubi Ihsane - Araya Figueroa Catalina Andrea

Description of the program: This program turns a two-color LED green during 2 seconds after pressing 3 times the button interrupt.

Hardware identification: On the motherboard, one end of a two-position crimped cable (with two female ends) is connected to the LED,
and the other end to pins 1 and 2 (A0 and A1 respectively) of port A (input). Pin 2 (A1) is connected to the positive terminal of the LED.
Also with the help of a jumper, the switch is linked to pin D2 of port D (output).

Status table:
+----------------+-------+------------+-----------+
| Current State  | Input | Next State | Led Color |
+----------------+-------+------------+-----------+
|      INIT      |  D2=0 |    INIT    |    OFF    |
+----------------+-------+------------+-----------+
|      INIT      |  D2=1 |   CLIC_1   |    OFF    |
+----------------+-------+------------+-----------+
|     CLIC_1     |  D2=0 |   CLIC_1   |    OFF    |
+----------------+-------+------------+-----------+
|     CLIC_1     |  D2=1 |   CLIC_2   |    OFF    |
+----------------+-------+------------+-----------+
|     CLIC_2     |  D2=0 |   CLIC_2   |    OFF    |
+----------------+-------+------------+-----------+
|     CLIC_2     |  D2=1 |   CLIC_3   |    OFF    |
+----------------+-------+------------+-----------+
|     CLIC_3     |  D2=0 |   CLIC_3   |   GREEN   |
+----------------+-------+------------+-----------+
|     CLIC_3     |  D2=1 |    INIT    |   GREEN   |
+----------------+-------+------------+-----------+
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_OFF = 0;
const uint8_t MASK_D2 = 1 << PD2;
const uint8_t DELAY_DEBOUNCE = 10;
const uint16_t TIME_LED_ON = 2000;
bool buttonIsPressed = false;
enum class States
{
    INIT,
    CLIC_1,
    CLIC_2,
    CLIC_3
};
States state = States::INIT;

bool isPressed()
{
    return (PIND & MASK_D2);
}
bool debounceButton()
{
    if (isPressed())
    {
        _delay_ms(DELAY_DEBOUNCE);
        if (isPressed())
        {
            buttonIsPressed = true;
            return true;
        }
    }

    return false;
}

bool isButtonPressedAndReleased()
{
    if (!debounceButton() && buttonIsPressed)
    {
        buttonIsPressed = false;
        return true;
    }

    return false;
}

void setNextState()
{
    switch (state)
    {
    case States::INIT:
        if (isButtonPressedAndReleased())
            state = States::CLIC_1;
        break;
    case States::CLIC_1:
        if (isButtonPressedAndReleased())
            state = States::CLIC_2;
        break;
    case States::CLIC_2:
        if (isButtonPressedAndReleased())
            state = States::CLIC_3;
        break;
    case States::CLIC_3:
        state = States::INIT;
        break;
    }
    return;
}

void setColorLed()
{
    switch (state)
    {
    case States::CLIC_3:
        PORTA = LED_GREEN;
        _delay_ms(TIME_LED_ON);
        break;
    default:
        PORTA = LED_OFF;
        break;
    }
    return;
}

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    while (true)
    {
        setColorLed();
        setNextState();
    }
    return 0;
}
