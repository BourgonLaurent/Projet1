/*
 * Nom: interrupteur
 * Description: Affichage séquentiel de la diode
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

// couleurs possibles de la diode bicolore
enum Color : uint8_t
{
    Off = 0x00,
    Green = 0x01,
    Red = 0x02
};

void showColor(Color color)
{
    PORTA = color;
}

void showOff()
{
    showColor(Color::Off);
}

void showRed()
{
    showColor(Color::Red);
}

bool isButtonPressed()
{
    return PIND & 0b0000'0100;
}

bool isPressingButton()
{
    if (isButtonPressed())
    {
        _delay_ms(10);
        return isButtonPressed();
    }

    return false;
}

int main()
{
    // ne met en sortie que les broches A1 et A2
    DDRA = 0b00000011;

    // séquence de la diode:
    //  - rouge
    //  - vert
    //  - ambré (rouge + vert varie rapidement)
    while (true)
    {
        if (isPressingButton())
        {
            showRed();
        }
        else
        {

            showOff();
        }
    }

    return 0;
}
