# TP2 - Bourgon & Benouhoud

Travail pratique #2 du cours INF1900.

* Mehdi Benouhoud
* Laurent Bourgon

## Problèmes à résoudre

Vous devez faire allumer la DEL bicolore d'une manière précise, en utilisant uniquement la carte mère.

### Problème 1

Les compteurs sont une forme de machines à états. On veut ici simplement que la DEL soit éteinte au départ. On doit appuyer et relâcher 3 fois le bouton-poussoir avant que la DEL tourne au vert pendant exactement 2 secondes. Par la suite, on revient au départ pour pouvoir recommencer.

### Problème 2

Quand la carte mère démarre, la DEL libre doit s'allumer en rouge. Si le bouton-poussoir libre pour usage général est pesé, la DEL affiche la couleur ambre. Quand le bouton-poussoir est relâché, la DEL devient verte. Si le bouton est de nouveau pesé, la DEL prend la couleur rouge encore. Quand il est relâché, la DEL s'éteint. Si le bouton est de nouveau pesé, la DEL affiche la couleur verte. Quand il est relâché, la DEL tourne au rouge ce qui fait que la carte mère est de retour à son état initial et tout peut recommencer.
