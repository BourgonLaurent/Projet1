/**
 * Problem 2:
 *  Cycles through LED colors based on a state table.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date January 19, 2023
 *
 * Hardware Identification
 * INPUT: Push button connected to D2 with a jumper.
 * OUTPUT: Bicolor LED connected plus to A0 and minus to A1.
 *
 * Implements the following state table:
 *  Note: For the Button input:
 *      0: Released
 *      1: Pressed
 * +-----------------+--------+----------------+-------+
 * |  CURRENT STATE  | BUTTON |   NEXT STATE   |  LED  |
 * +=================+========+================+=======+
 * |                 |    0   |      INIT      |       |
 * |       INIT      +--------+----------------+  RED  +
 * |                 |    1   |   FIRST_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   |  FIRST_RELEASE |       |
 * |   FIRST_PRESS   +--------+----------------+ AMBER +
 * |                 |    1   |   FIRST_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   |  FIRST_RELEASE |       |
 * |  FIRST_RELEASE  +--------+----------------+ GREEN +
 * |                 |    1   |  SECOND_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   | SECOND_RELEASE |       |
 * |   SECOND_PRESS  +--------+----------------+  RED  +
 * |                 |    1   |  SECOND_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   | SECOND_RELEASE |       |
 * |  SECOND_RELEASE +--------+----------------+  OFF  +
 * |                 |    1   |   THIRD_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 * |                 |    0   |      INIT      |       |
 * |   THIRD_PRESS   +--------+----------------+ GREEN +
 * |                 |    1   |   THIRD_PRESS  |       |
 * +-----------------+--------+----------------+-------+
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <tp2/components/button.hpp>
#include <tp2/components/led.hpp>
#include <tp2/components/colors.hpp>

constexpr uint8_t AMBER_DELAY_MS = 10;

enum class MachineState
{
    INIT,
    FIRST_PRESS,
    FIRST_RELEASE,
    SECOND_PRESS,
    SECOND_RELEASE,
    THIRD_PRESS
};

volatile MachineState currentState = MachineState::INIT;

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR(INT0_vect)
{
    _delay_ms(30);

    switch (::currentState)
    {
    case MachineState::INIT:
        ::currentState = MachineState::FIRST_PRESS;
        break;

    case MachineState::FIRST_PRESS:
        ::currentState = MachineState::FIRST_RELEASE;
        break;

    case MachineState::FIRST_RELEASE:
        ::currentState = MachineState::SECOND_PRESS;
        break;

    case MachineState::SECOND_PRESS:
        ::currentState = MachineState::SECOND_RELEASE;
        break;

    case MachineState::SECOND_RELEASE:
        ::currentState = MachineState::THIRD_PRESS;
        break;

    case MachineState::THIRD_PRESS:
        ::currentState = MachineState::INIT;
        break;
    }

    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0);
}

int main()
{
    cli();

    // DDRA |= _BV(PORTA0) | _BV(PORTA1);
    DDRD &= ~_BV(PIND2);

    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli();

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= _BV(INT0);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= _BV(ISC00);
    EICRA &= ~_BV(ISC01);

    // sei permet de recevoir à nouveau des interruptions.
    sei();

    // Button button = Button(&DDRD, &PIND, PIND2);
    LED led = LED(&DDRA, &PORTA, PORTA0, PORTA1);

    while (true)
    {
        switch (::currentState)
        {
        case MachineState::INIT:
            led.setColor(Color::RED);
            break;

        case MachineState::FIRST_PRESS:
            led.setColor(Color::RED);
            _delay_ms(AMBER_DELAY_MS);
            led.setColor(Color::GREEN);
            break;

        case MachineState::FIRST_RELEASE:
            led.setColor(Color::GREEN);
            break;

        case MachineState::SECOND_PRESS:
            led.setColor(Color::RED);
            break;

        case MachineState::SECOND_RELEASE:
            led.setColor(Color::OFF);
            break;

        case MachineState::THIRD_PRESS:
            led.setColor(Color::GREEN);
            break;
        }
    }

    return 0;
}
