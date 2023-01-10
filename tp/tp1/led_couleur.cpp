/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 */

#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>

#define F_CPU 8000000

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie

  unsigned long compteur = 0;

  uint8_t ETEINT = 0x00;
  uint8_t VERT = 0x01;
  uint8_t ROUGE = 0x02;

  for (;;) // boucle sans fin
  {
    PORTA = ROUGE;

    _delay_ms(5000);

    PORTA = VERT;

    _delay_ms(5000);

    for (int i = 0; i < 2500; i++)
    {
      PORTA = VERT;
      _delay_ms(1);
      PORTA = ROUGE;
      _delay_ms(1);
    }
  }
  return 0;
}
