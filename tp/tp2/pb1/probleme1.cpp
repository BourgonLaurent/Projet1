/*
 * Nom: TP2 problème 1
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 *
 * +--------------+----+--------------+------------+
| État présent | D2 | État suivant | Sortie DEL |
+--------------+----+--------------+------------+
| INIT         | 0  | INIT         | éteint     |
+--------------+----+--------------+------------+
| INIT         | 1  | CLIC1        | éteint     |
+--------------+----+--------------+------------+
| CLIC1        | 0  | CLIC1        | éteint     |
+--------------+----+--------------+------------+
| CLIC1        | 1  | CLIC2        | éteint     |
+--------------+----+--------------+------------+
| CLIC2        | 0  | CLIC2        | éteint     |
+--------------+----+--------------+------------+
| CLIC2        | 1  | CLIC3        | éteint     |
+--------------+----+--------------+------------+
| CLIC3        | 0  | CLIC3        | vert       |
+--------------+----+--------------+------------+
| CLIC3        | 1  | INIT         | vert       |
+--------------+----+--------------+------------+
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

bool buttonPress()
{
  if (PIND & 0x04)
  {
    _delay_ms(10);
    return !(PIND & 0x04);
  }

  return false;
}

int main()
{
  DDRA = 0xff;
  DDRD = 0x00;

  enum class States
  {
    INIT,
    CLIC1,
    CLIC2,
    CLIC3
  };

  States presentState = States::INIT;

  while (true)
  {

    switch (presentState)
    {
    case States::INIT:
      PORTA = 0x0;
      if (buttonPress())
      {
        presentState = States::CLIC1;
      }
      break;

    case States::CLIC1:
      if (buttonPress())
      {
        presentState = States::CLIC2;
      }
      break;

    case States::CLIC2:
      if (buttonPress())
      {
        presentState = States::CLIC3;
      }
      break;

    case States::CLIC3:
      PORTA = 0x02;
      _delay_ms(2000);
      presentState = States::INIT;

      break;
    }
  }
  return 0;
}
