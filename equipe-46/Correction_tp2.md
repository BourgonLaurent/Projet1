# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à état
+ Section #  : 2
+ Équipe #   : 46
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
| Noms de fonctions décrivent l'intention      | (0.2/0.5)     |
| __Résultat partiel__                         | __(1.2/1.5)__ |

- Les noms des fonctions doivent suivre la convention de nommage des fonctions en C++ (camelCase). Par exemple, la fonction `void ledAMBRERColor()` devrait être renommée `void ledAmberColor()`. (-0.2)

- Il faut préciser aussi l'objet manipulé par la fonction après le verbe. (ex: `isPressed()` => `isButtonPressed()`). (-0.1)

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

- Très bonne modularité !

- Pour éviter le plus possible la duplication de code et rendre le code plus modulaire, il est important d’encapsuler les modifications de registre dans des fonctions. Par exemple, `PORTA = GREEN` peut être dans une simple fonction `setLedGreen()` ou encore mieux `setLed(Color::GREEN)`. J’accepte votre façon de faire pour ce TP, mais je demande à ce que vous encapsuliez davantage votre logique dans des fonctions dès le prochain TP.

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |   -0.5     |
| __Résultat partiel__                         | __(3.5/4.0)__ |

- Il est nécessaire d'implémenter un anti-rebond pour les boutons. Le pb2 définit la fonction d'anti-rebond, mais ne l'utilise pas. Je ne retire que la moitié des points par errer car vous avez bien implémenté ce mécanisme dans le pb1. (-0.5)

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (0/1.5)     |
| __Résultat partiel__                         | __(1.5/3.0)__ |

- Plusieurs fichiers inutiles pour la compilation sont présents dans le dépôt. Il est important de les supprimer avant de faire un commit. Je vous recommande d'ajouter un fichier `.gitignore` pour éviter de les ajouter par erreur dans les prochains TPs. Voici ce que je vous recommande d'ajouter dans le fichier:

```
	*.d
	*.o
	*.elf
	*.hex
	*.map
```

- Il faut manipuler dans un registre que les bits pertinents pour votre mise en situation à l’aide des opérations `|=` et `&=`. On utilise le `=` que lorsqu’il est nécessaire d’écraser tout le registre. Je n’ai pas enlevé de points pour ce TP, mais je m’attends à ce que vous suiviez cette pratique dans vos prochains TPs. (Applicable aussi pour le mode - DDRx).

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

__Total des points: 17.7/20__

# Commentaires du correcteur:

- Excellent travail! Je vois que vous avez mis beaucoup d'efforts sur la qualité de votre code. C'est super clean. Les machines à états sont bien structurées, la logique est bien encapsulée dans des fonctions, les nombres magiques sont bien documentés, etc. Continuez comme ça, vous êtes sur la bonne voie! 👏

Si vous avez des questions, n'hésitez pas à me contacter.

# Basé sur le commit suivant
```
commit b7f73fdc75685b165a35546586468f8871a35536
Author: Ihsane Majdoubi <ihsane.majdoubi@polymtl.ca>
Date:   Wed Jan 25 19:08:06 2023 -0500

    modification des descriptions _version finale_
```

# Fichiers indésirables pertinents
```
tp/tp2/pb2/TP2.elf
tp/tp2/pb2/TP2.elf.map
tp/tp2/pb2/TP2.hex
tp/tp2/pb2/probleme2.d
tp/tp2/pb2/probleme2.o
```

# Tous les fichiers indésirables
```
tp/tp2/pb2/TP2.elf
tp/tp2/pb2/TP2.elf.map
tp/tp2/pb2/TP2.hex
tp/tp2/pb2/probleme2.d
tp/tp2/pb2/probleme2.o
```

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp2/pb1`
```
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c probleme1.cpp
avr-gcc -Wl,-Map,TP2.elf.map -mmcu=atmega324pa -o TP2.elf  probleme1.o \
	-lm 
avr-objcopy -j .text -j .data \
		-O ihex TP2.elf TP2.hex

```

## Sortie de `make` dans `tp/tp2/pb2`
```
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c probleme2.cpp
avr-gcc -Wl,-Map,TP2.elf.map -mmcu=atmega324pa -o TP2.elf  probleme2.o \
	-lm 
avr-objcopy -j .text -j .data \
		-O ihex TP2.elf TP2.hex

```
