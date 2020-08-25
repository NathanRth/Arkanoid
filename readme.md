#Arkanoïd
Nathan ROTH - Maxime SCHNEBERGER

## Compilation

Pour compiler le programme, entrez l'une des commande suivante
- `make` : compile avec les paramètre `release`
- `make release` : compile avec le flag `-o3`
- `make debug`  : compile avec les flags `-g -Wall`

Chacune des trois commandes va créer un dossier `build/<method>/` dans lequel va se placer l'executable. Un lien symbolique de la dernière compilation est aussi créé à côté du makefile.

Pour lancer le programme : `./Arkanoid`

Afin de passer au niveau suivant artificellement (pour raison de debug pour nous), vous pouvez appuyer sur la touche "n" (next).