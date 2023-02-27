# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à état
+ Section #  : 2
+ Équipe #   : 45
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

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (/0.5)     |
| Noms de variables décrivent l'intention      | (/0.5)     |
| Noms de fonctions décrivent l'intention      | (/0.5)     |
| __Résultat partiel__                         | __(1.5/1.5)__ |

- Aucun nombre magique et les noms de variables et fonctions sont significatifs. Bravo !

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(1/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1/1.0)__ |


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

__Total des points: 20.0/20__

# Commentaires du correcteur:

Je n'ai vraiment rien à rajouter, votre remise est parfaite! Vous avez déjà une très bonne longueur d'avance et vous dépassez de très loin les attentes. Je vous dirais qu'une bonne partie de votre TP7 (où l'on vous demandera de construire une librairie) est déjà terminée, à la semaine 3. Bravo !

J'aime beaucoup votre implémentation de la classe IO, c'est super clean.

Continuez sur votre lancée, j'ai hâte de voir ce que vous allez faire pour le TP7! 🙌


# Basé sur le commit suivant
```
commit acc7338ca95fa42a437cfd9f51303b5a0768efc3
Author: Laurent Bourgon <laurent.bourgon@polymtl.ca>
Date:   Fri Jan 27 18:06:07 2023 -0500

    [tp3] [pb2] [fix] call forward method for motor
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
avr-gcc -I. -I/usr/include/simavr  -MMD -I../../ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp -o main.o
avr-gcc -I. -I/usr/include/simavr  -MMD -I../../ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c ../components/button.cpp -o ../components/button.o
avr-gcc -I. -I/usr/include/simavr  -MMD -I../../ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c ../components/led.cpp -o ../components/led.o
avr-gcc -Wl,-Map,TP2_pb1.elf.map -mmcu=atmega324pa -o TP2_pb1.elf  main.o ../components/button.o ../components/led.o \
	-lm 
avr-objcopy -j .text -j .data \
		-O ihex TP2_pb1.elf TP2_pb1.hex

```

## Sortie de `make` dans `tp/tp2/pb2`
```
avr-gcc -I. -I/usr/include/simavr  -MMD -I../../ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp -o main.o
avr-gcc -I. -I/usr/include/simavr  -MMD -I../../ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c ../components/button.cpp -o ../components/button.o
avr-gcc -I. -I/usr/include/simavr  -MMD -I../../ -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c ../components/led.cpp -o ../components/led.o
avr-gcc -Wl,-Map,TP2_pb2.elf.map -mmcu=atmega324pa -o TP2_pb2.elf  main.o ../components/button.o ../components/led.o \
	-lm 
avr-objcopy -j .text -j .data \
		-O ihex TP2_pb2.elf TP2_pb2.hex

```
