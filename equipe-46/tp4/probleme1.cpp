
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_RED = 1 << PA1;
const uint8_t LED_OFF = 0;
const uint8_t MASK_D2 = 1 << PD2;
const uint8_t DELAY_DEBOUNCE = 10;
const uint8_t DELAY_COLOR_AMBRER = 5;

bool isPressed()
{
    return (PIND & MASK_D2);
}
bool debounceButton()
{
    if (isPressed())
    {
        _delay_ms(DELAY_DEBOUNCE);
        return (isPressed());
    }

    return false;
}
enum class States
{
    RED1,
    AMBRER,
    GREEN1,
    RED2,
    OFF,
    GREEN2
};
volatile States state = States::RED1;

void ledAMBRERColor()
{
    PORTA = LED_GREEN;
    _delay_ms(DELAY_COLOR_AMBRER);
    PORTA = LED_RED;
    _delay_ms(DELAY_COLOR_AMBRER);
    return;
}

void setNextState()
{
    switch (state)
    {
    case States::RED1:
        state = States::AMBRER;
        break;

    case States::AMBRER:

        state = States::GREEN1;
        break;

    case States::GREEN1:

        state = States::RED2;
        break;

    case States::RED2:

        state = States::OFF;
        break;

    case States::OFF:

        state = States::GREEN2;
        break;

    case States::GREEN2:

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

    case States::AMBRER:
        ledAMBRERColor();
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

void initialisation(void)
{
    cli();
    DDRA = 0xff;
    DDRD = 0x00;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

ISR(INT0_vect)
{
    _delay_ms(10);
    setNextState();
    EIFR |= (1 << INTF0);
}

int main()
{

    while (true)
    {
        initialisation();
        setColorLed();
    }

    return 0;
}
