
/*
 * Name: TP6 problème 1
 * Section #: 02
 * Team #: 46

Authors: Majdoubi Ihsane - Araya Figueroa Catalina Andrea

Description of the program: when button is pressed for 12 seconds or released
before 12 seconds, the LED flashes green for 0.5 seconds. Then,
the LED is off and after 2 seconds it flashes red (counter/2) timesat a rythmn
of 2 times per seconds. Then, the LED turns green for one second
and the LED finally turns off.

Hardware identification: On the motherboard, one end of a two-position crimped
cable (with two female ends) is connected to the LED,
and the other end to pins 1 and 2 (B0 and B1 respectively) of port B (input).
Pin 2 (B1) is connected to the positive terminal of the LED.
The pin 1 (B0) of port B is connected to the negative terminal of the LED. An
interruptor is connected to pin 3 (D2) of port D, which triggers
an interruption when the button is pressed and released.


State table:
+---------------+---------+---------+--------+------------+-------+-----+
| Current state | gButton | counter | readyToChange | Next state | LED  |
+---------------+---------+---------+--------+------------+------+------+
| READY         | 0       | X       | X             | READY      | Off  |
+---------------+---------+---------+--------+------------+------+------+
| READY         | 1       | X       | X             | WAIT       | Off  |
+---------------+---------+---------+--------+------------+------+------+
| WAIT          | 0       | <120    | X             | WAIT       | Off  |
+---------------+---------+---------+--------+------------+------+------+
| WAIT          | 1       | X       | X             | GREEN_FLASH     | Off  |
+---------------+---------+---------+--------+------------+------+------+
| WAIT          | 0       | 120     | X             | GREEN_FLASH     | Off  |
+---------------+---------+---------+--------+------------+------+------+
| WAIT          | 1       | 120     | X             | GREEN_FLASH     | Off  |
+---------------+---------+---------+--------+------------+------+------+
| GREEN_FLASH        | X       | X       | 0             | GREEN_FLASH     |Green |
+---------------+---------+---------+--------+------------+------+------+
| GREEN_FLASH        | X       | X       | 1             | RED_FLASH       |Green |
+---------------+---------+---------+--------+------------+------+------+
| RED_FLASH          | X       | X       | 0             | RED_FLASH       | Red  |
+---------------+---------+---------+--------+------------+------+------+
| RED_FLASH          | X       | X       | 1             | GREEN     | Red  |
+---------------+---------+---------+--------+------------+------+------+
| GREEN        | X       | X       | 0             | GREEN     |Green |
+---------------+---------+---------+--------+------------+------+------+
| GREEN        | X       | X       | 1             | READY      |Green |
+---------------+---------+---------+--------+------------+------+------+
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t LED_GREEN = 1 << PB0;
const uint8_t LED_RED = 1 << PB1;
const uint8_t LED_OFF = 0;
const uint8_t DELAY_DEBOUNCE_MS = 10;
const uint16_t DELAY_FLASH_RED_MS = 500;
const uint16_t DELAY_FLASH_GREEN_MS = 50;
const uint16_t DELAY_GREEN_HALF_SECOND_MS = 1000;
const uint16_t DELAY_BEFORE_RED_FLASH_MS = 2000;
volatile uint8_t gButton = 0;
volatile uint8_t stateButton = 0;
volatile uint8_t readyToChange = 0;
volatile uint8_t counter = 0;
uint8_t valueCounter = 0;

enum class States
{
    READY,
    WAIT,
    GREEN_FLASH,
    RED_FLASH,
    GREEN_HALF_SECOND
};

volatile States state = States::READY;

enum class Color
{
    OFF,
    RED,
    GREEN,
};

volatile Color currentColor = Color::OFF;

void changeState(States nextState)
{
    if (readyToChange == 1)
    {
        readyToChange = 0;
        state = nextState;
    }
}

void setLed(Color currentColor)
{
    if (currentColor == Color::OFF)
        PORTB = LED_OFF;

    if (currentColor == Color::GREEN)
        PORTB = LED_GREEN;

    if (currentColor == Color::RED)
        PORTB = LED_RED;
}
template <typename T>
void setLedFlash(Color currentColor, T DELAY)
{
    setLed(currentColor);
    _delay_ms(DELAY);
    setLed(Color::OFF);
    _delay_ms(DELAY);
}

void starTime(uint8_t delay)
{
    cli();
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12); // clk/1024 from prescaler and mode CTC
    TCCR1C = 0;
    OCR1A = 781 * delay;    // output compare every 100ms seconds (7812/10)
    TIMSK1 = (1 << OCIE1A); // enable output compare A match interrupt
    TIFR1 = (1 << OCF1A);   // interrupt request when counter value reaches the TOP value
    sei();
}

void initialization(void)
{
    cli();
    EIMSK |= (1 << INT0);  // external interrupt mask for INT0
    EICRA |= (1 << ISC00); // Interrupt request at any edge of INT0 asynchronously
    sei();
}

void setNextState()
{
    switch (state)
    {
    case States::READY:
        if (gButton == 1)
        {
            gButton = 0;
            state = States::WAIT;
        }
        break;

    case States::WAIT:
        if ((counter == 120) || (gButton == 1))
        {
            valueCounter = counter;
            state = States::GREEN_FLASH;
            gButton = 0;
        }

    case States::GREEN_FLASH:
        changeState(States::RED_FLASH);
        break;

    case States::RED_FLASH:
        changeState(States::GREEN_HALF_SECOND);
        break;

    case States::GREEN_HALF_SECOND:
        changeState(States::READY);
        break;
    }
}

void setColorLed()
{
    switch (state)
    {
    case States::READY:
    case States::WAIT:
        setLed(Color::OFF);
        break;

    case States::GREEN_FLASH:
        for (uint8_t i = 0; i < 5; i++)
        {
            setLedFlash(Color::GREEN, DELAY_FLASH_GREEN_MS);
        }
        readyToChange = 1;
        break;

    case States::RED_FLASH:
        _delay_ms(DELAY_BEFORE_RED_FLASH_MS);
        for (uint8_t i = 0; 2 * i < valueCounter; i++)
        {
            setLedFlash(Color::RED, DELAY_FLASH_RED_MS);
        }
        readyToChange = 1;
        break;

    case States::GREEN_HALF_SECOND:
        setLed(Color::GREEN);
        _delay_ms(DELAY_GREEN_HALF_SECOND_MS);
        readyToChange = 1;
        break;
    }
}

ISR(INT0_vect)
{
    _delay_ms(DELAY_DEBOUNCE_MS);
    gButton = 1;
    starTime(1);
    EIFR |= (1 << INTF0); // external interupt flag for INT0
}

ISR(TIMER1_COMPA_vect)
{
    counter += 1;
}

int main()
{
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD &= (1 << PD2);
    initialization();

    while (true)
    {
        setNextState();
        setColorLed();
    }

    return 0;
}
