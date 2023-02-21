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
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
const uint8_t PWMSignal = 1 << PB0;
const uint8_t PWM_OFF = 0;

void delayMoteur(uint16_t delay)
{
  for (uint16_t i = 0; i < delay / 5; i++)
  {
    _delay_us(5);
  }
}

int main()
{
  DDRB = 0xff;
  DDRD = 0x00;

  while (true)
  {

    for (uint16_t delay = 0; delay <= 60; delay = delay + 15)
    {
      for (uint16_t i = 0; i < 2000; i++)
      {
        PORTB = PWMSignal;
        delayMoteur(delay);
        PORTB = PWM_OFF;
        delayMoteur(60 - delay);
      }
    }
  }
  return 0;
}
