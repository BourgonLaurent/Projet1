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
const uint8_t LED_GREEN = 1 << PA0;
const uint8_t LED_OFF = 0;

void delayLED(uint16_t delay)
{
  for (uint16_t i = 0; i < delay / 5; i++)
  {
    _delay_us(5);
  }
}

int main()
{
  DDRA = 0xff;
  DDRD = 0x00;

  enum class Color : uint8_t
  {
    RED = 0x02,
    GREEN = 0x01,
    OFF = 0x00
  };

  while (true)
  {

    for (uint16_t delay = 0; delay <= 1000; delay++)
    {
      for (uint16_t i = 0; i < 2; i++)
      {
        PORTA = LED_GREEN;
        delayLED(1000 - delay);
        PORTA = LED_OFF;
        delayLED(delay);
      }
    }
  }

  return 0;
}
