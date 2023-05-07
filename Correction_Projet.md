# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Projet final
+ Section #  : 2
+ Équipe #   : 4546
+ Correcteur : Ghali Chraibi

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1.5/1.5)__ |

- J'apprécie les efforts mis pour avoir des en-têtes claires et bien structurées.

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0.5/0.5)     |
| Noms de variables décrivent l'intention      | (0.35/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.35/1.5)__ |

- Quelques variables pourraient avoir des noms plus explicites (ex: `first_` et `second_` dans `Flasher.cpp`, `white`, `position_` dans `interruptButton`). (-0.15)

- Les noms des fonctions sont très bien choisis.


## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |

- Très bonne pratique de préciser la page du manuel de référence pour les registres utilisés!

## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(1.0/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |  -0.5      |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(0.5/1.0)__ |

- La méthode `run` aurait dû être fragmentée en plusieurs plus petites méthodes pour respecter le principe de responsabilité unique et pour faciliter la compréhension du code. Dans le meilleur des cas, cette fonction exécuterait une machine à états. (-0.5)

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4/4.0)__ |

- Faites attention aux potentielles erreurs de division par zéro, comme dans dans le calcul de `average` de `irSensor.cpp`.

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5/5.0)__ |

# Résultat

__Total des points: 19.35/20__

# Commentaires du correcteur:

- Félicitations pour votre excellent travail sur ce projet ! Vous avez bien réussi à rendre votre code lisible et structuré, avec des identificateurs clairs et une architecture intuitive. Vous avez également bien appliqué les concepts de programmation vus tout au long de la session. J'ai apprécié la lecture de votre code et l'effort consacré à votre README. Je vous souhaite un excellent été et beaucoup de réussite pour vos prochains projets ! :)


# Basé sur le commit suivant
```
commit f0a5758bf4997c5bc965378cd36fc2e563f0aac0
Author: Ihsane Majdoubi <ihsane.majdoubi@polymtl.ca>
Date:   Thu Apr 20 01:23:35 2023 -0400

    halleluia delays are set!
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `projet/lib`
```
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c _memoire_24.cpp -o _memoire_24.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c analogReader.cpp -o analogReader.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c button.cpp -o button.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c communication.cpp -o communication.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c flasher.cpp -o flasher.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c interruptButton.cpp -o interruptButton.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c interruptTimer.cpp -o interruptTimer.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c irSensor.cpp -o irSensor.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c led.cpp -o led.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c memory.cpp -o memory.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c sound.cpp -o sound.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c wheels.cpp -o wheels.o
avr-ar -crs lib1900.a _memoire_24.o analogReader.o button.o communication.o flasher.o interruptButton.o interruptTimer.o irSensor.o led.o memory.o sound.o wheels.o

```

## Sortie de `make` dans `projet/app`
```
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp -o main.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c detect/detect.cpp -o detect/detect.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c detect/objectFinder.cpp -o detect/objectFinder.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c detect/positionManager.cpp -o detect/positionManager.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c misc/point.cpp -o misc/point.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c misc/vector.cpp -o misc/vector.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c transmit/convexHull.cpp -o transmit/convexHull.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c transmit/integrity.cpp -o transmit/integrity.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c transmit/polygon.cpp -o transmit/polygon.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c transmit/svgBuilder.cpp -o transmit/svgBuilder.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c transmit/transmit.cpp -o transmit/transmit.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c misc/map/column.cpp -o misc/map/column.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c misc/map/map.cpp -o misc/map/map.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c misc/map/mapManager.cpp -o misc/map/mapManager.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c misc/map/slot.cpp -o misc/map/slot.o
avr-gcc -Wl,-Map,app.elf.map -mmcu=atmega324pa -o app.elf  main.o detect/detect.o detect/objectFinder.o detect/positionManager.o misc/point.o misc/vector.o transmit/convexHull.o transmit/integrity.o transmit/polygon.o transmit/svgBuilder.o transmit/transmit.o misc/map/column.o misc/map/map.o misc/map/mapManager.o misc/map/slot.o \
	-lm -l1900 -L../lib/
avr-objcopy -j .text -j .data \
		-O ihex app.elf app.hex

```
