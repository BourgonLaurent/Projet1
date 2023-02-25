/*
 * Name: TP6 problème 2
 * Section #: 02
 * Team #: 46

Authors: Majdoubi Ihsane - Araya Figueroa Catalina Andrea

Description of the program: This program enables the lighting of an LED based
on the amount of light received by a photoresistor: If the light is low , the
LED will emit a green color. If the light level is good, the LED will turn
amber.If the light is too strong, the LED will turn red.

Hardware identification: On the motherboard, one end of a two-position crimped cable (with two female ends) is connected to the LED,
and the other end to pins 1 and 2 (B0 and B1 respectively) of port B (input). Pin 2 (B1) is connected to the positive terminal of the LED.
The pin 1 (A0) of port A is connected to a photresistor in the breadboard.
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <can.h>

const uint8_t LED_GREEN = 1 << PB0;
const uint8_t LED_RED = 1 << PB1;
const uint8_t DELAY_COLOR_AMBRER_MS = 5;
const uint8_t LIMIT_LOW_VALUE = 70;
const uint8_t LIMIT_HIGHT_VALUE = 180;

enum class Color
{
    RED,
    GREEN,
};

void setLed(Color currentColor)
{
    if (currentColor == Color::GREEN)
    {
        PORTB = LED_GREEN;
    }

    if (currentColor == Color::RED)
    {
        PORTB = LED_RED;
    }
}

void ledAmberColor()
{
    setLed(Color::GREEN);
    _delay_ms(DELAY_COLOR_AMBRER_MS);
    setLed(Color::RED);
    _delay_ms(DELAY_COLOR_AMBRER_MS);
    return;
}

int main()
{
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRA &= ~(1 << PA0);

    while (true)
    {
        can myCan;
        uint16_t digitalValue = 0;
        digitalValue = myCan.lecture(PINA0);
        digitalValue = digitalValue >> 2; // The two LSB are not significant

        if (digitalValue < LIMIT_LOW_VALUE)
            setLed(Color::GREEN);
        else if (digitalValue >= LIMIT_HIGHT_VALUE)
            setLed(Color::RED);
        else
            ledAmberColor();
    }

    return 0;
}