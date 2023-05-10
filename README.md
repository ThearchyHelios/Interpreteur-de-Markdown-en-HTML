# Interpréteur de Markdown en HTML
Un projet qui compile les fichiers markdown en fichiers HTML et les affiche dans un navigateur web.
![Markdown to HTML](https://thearchyhelios.com/images/INF404/Markdown%20to%20HTML.png)
## Requirements
Vous devez disposer des logiciels suivants pour utiliser le projet:
- gcc
- make

## Utilisation
1. Ouvez un terminal et placez vous dans le dossier du projet
2. Fonctionner le Makefile avec la commande ` make `.
3. Lancer le programme avec la commande ` ./markdown + fichier_markdown `:

Ex: `./markdown test/test.md`

Cette commande génère un fichier ` output.html ` et l'affiche à l'aide du navigateur par défaut.

## Fonctionnalités
- [ ] Génération de fichiers HTML à partir de fichiers markdown
  - [x] Gestion des titres
  - [x] Gestion des font styles
    - [x] Gestion du gras
    - [x] Gestion de l'italique
    - [x] Gestion du gras et de l'italique
    - [x] Gestion du barré
  - [x] Gestion des liens
  - [ ] Gestion des listes
    - [x] Gestion des listes non ordonnées
    - [ ] Gestion des listes ordonnées (BUG: les listes ordonnées ne sont pas affichées correctement)
  - [ ] Gestion des codes
    - [x] Gestion des codes en ligne
    - [ ] Gestions des blocs de codes (BUG)
  - [x] Gestion des images
  - [x] Gestion des Checkbox
  - [ ] CSS support
  - [x] Affichage des fichiers HTML dans un navigateur web

## Références
- [Markdown: Syntax](https://daringfireball.net/projects/markdown/syntax)
- [Markdown cheat sheet](https://www.markdownguide.org/cheat-sheet/)

## Auteurs
- [JIANG Yilun](https://thearchyhelios.com)