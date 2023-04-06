# Ajouts nécessaires pour *append* le `.svg`
Il faut ajouter les éléments dans l'ordre suivant, afin qu'ils s'affichent sur les bons plans. Malheureusement, le `z-index` ne semble pas fonctionner avec SVG, donc pas le choix de procéder ainsi.

Précision aussi, quand je dis « index », je fais référence au numéro de la colonne/ligne, en partant de 0.

Précision *2*, l'axe des ordonnées (y) est différent en SVG. Plus c'est grand, plus c'est vers le bas de l'image. Donc la ligne 3 se trouve être celle du carré rouge.
## 1. Ajout du polygone
Il faut ajouter la ligne suivante, avec les coordonées calculées en `2`.
```svg
<polygon fill="forestgreen" stroke="black" stroke-width="2px" points="305,155 605,155 505,255 405,355"/>
```
## 2. Ajout des poteaux gris
Il faut ajouter cette ligne (pour chaque poteau)
```svg
<circle cx="605" cy="155" r="10" fill="gray" stroke="black" stroke-width="2px"/>
```
La formule pour établir les coordonées `cx` et `cy` est la suivante:
```
cx = ((index de la colonne + 2)) * 100 + largeur du carré/2
cx = ((c + 2) * 100) + 5
cy = ((index de la rangée + 1) * 100) + 50 + largeur du carré/2
cy = ((r + 1) * 100) + 50 + 5
```

## 3. Ajout de l'aire
Il suffit d'ajouter cette ligne
```svg
<text x="96" y="575" fill="blue">AIRE: 420 pouces carrés</text>
``` 
où `420` est bien sûr remplacée par la véritable valeur d'aire.

## 4. Balise fermante `svg`
Une fois tous les éléments ajoutés, il ne faut pas oublier d'inclure la balise fermante `svg`.
```svg
</svg>
```
C'est bien important de le faire parce que sinon le fichier ne sera pas en mesure de s'ouvrir sur la plupart des lecteurs d'images.