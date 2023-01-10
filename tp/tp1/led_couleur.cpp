/*
 * Nom: led couleur
 * Description: Affichage séquentiel de la diode
 */

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

// couleurs possibles de la diode bicolore
enum Couleur : uint8_t
{
  Vert = 0x01,
  Rouge = 0x02
};

constexpr uint16_t DELAI_COULEUR_MS = 5000;

void afficherCouleur(Couleur couleur)
{
  PORTA = couleur;
}

void afficherRouge()
{
  afficherCouleur(Couleur::Rouge);
}

void afficherVert()
{
  afficherCouleur(Couleur::Vert);
}

void afficherAmbre()
{
  for (uint16_t i = 0; i < DELAI_COULEUR_MS; i++)
  {
    afficherVert();
    _delay_ms(0.5);
    afficherRouge();
    _delay_ms(0.5);
  }
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
    afficherRouge();

    _delay_ms(DELAI_COULEUR_MS);

    afficherVert();

    _delay_ms(DELAI_COULEUR_MS);

    afficherAmbre();
  }

  return 0;
}
