# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 2
+ Équipe #   : 4546
+ Correcteur : Paul Petibon

# CODE

| Points importants                                        | Poids       |
| -------------------------------------------------------- | ----------- |
| La qualités et le choix de vos portions de code choisies | (4.5/5.0)      |
| La qualités de vos modifications aux Makefiles           | (5.0/5.0)      |
| __Résultat partiel__                                     | __(9.5/10.0)__ |

- (-0.5) Non gestion des interruptions INT1, ...

# RAPPORT

| Points importants                                                           | Poids      |
| --------------------------------------------------------------------------- | ---------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (2.0/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (2.0/2.0)     |
| Explications claires avec un bon niveau de détails                          | (2.0/2.0)     |
| Bon français                                                                | (1.0/1.0)     |
| __Résultat partiel__                                                        | __(7.0/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé 

| Pénalité par erreur      | -0.5       |
| ------------------------ | ---------- |
| compilation sans erreurs |            |
| etc                      |            |
| __Résultat partiel__     | __(2.0/3.0)__ |

- (-1.0) Manque de commentaires pour les fonctions dans le code


# Résultat

__Total des points: 18.5/20__

# Commentaires du correcteur:

Tres bien !


# Basé sur le commit suivant
```
commit 762c7ff218a5e9e018a8d5f2dc482fef744277de
Author: Laurent Bourgon <laurent.bourgon@polymtl.ca>
Date:   Mon Mar 13 16:42:55 2023 -0400

    [tp7] remise rapport
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make : on entre dans le répertoire « /home/gigl/Bureau/inf1900-grader/correction_tp7/4546/tp/tp7/lib »
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c analogReader.cpp -o analogReader.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c communication.cpp -o communication.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c interruptButton.cpp -o interruptButton.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c interruptTimer.cpp -o interruptTimer.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c led.cpp -o led.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c _memoire_24.cpp -o _memoire_24.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c memory.cpp -o memory.o
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c wheels.cpp -o wheels.o
avr-ar -crs lib1900.a analogReader.o communication.o interruptButton.o interruptTimer.o led.o _memoire_24.o memory.o wheels.o
make : on quitte le répertoire « /home/gigl/Bureau/inf1900-grader/correction_tp7/4546/tp/tp7/lib »

```

## Sortie de `make` dans `tp/tp7/exec`
```
make : on entre dans le répertoire « /home/gigl/Bureau/inf1900-grader/correction_tp7/4546/tp/tp7/exec »
avr-gcc -I. -I/usr/include/simavr -MMD -I../ -g -mmcu=atmega324pa -DF_CPU=8000000UL -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp -o main.o
avr-gcc -Wl,-Map,TP7_exec.elf.map -mmcu=atmega324pa -o TP7_exec.elf  main.o \
-lm -l1900 -L../lib/
avr-objcopy -j .text -j .data \
	-O ihex TP7_exec.elf TP7_exec.hex
make : on quitte le répertoire « /home/gigl/Bureau/inf1900-grader/correction_tp7/4546/tp/tp7/exec »

```
