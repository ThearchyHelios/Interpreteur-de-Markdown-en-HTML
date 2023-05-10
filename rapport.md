---
title: Compte rendu du projet final
author: JIANG Yilun
---

<div style="float:right; margin: 0px 0px 10px 10px;">
  <img src="https://thearchyhelios.com/images/%E6%9D%82%E9%A1%B9/UGA.png" width="200">
</div>
# Interpréteur de Markdown en HTML

## Introduction

Le but de ce projet est de créer un programme qui compile les fichiers markdown en fichiers HTML et les affiche dans un navigateur web.
La raison pour laquelle j'ai choisi ce projet est que je utilise beaucoup de Markdown dans mon travail, et j'ai toujours voulu savoir comment les fichiers markdown sont compilés en fichiers HTML, et j'ai toujours voulu créer un programme qui peut compiler les fichiers markdown en fichiers HTML.

## Caractéristiques du programme

- Analyse lexicale : Le programme utilise un analyseur lexical pour décomposer le texte d'entrée en éléments syntaxiques (ou "tokens"). Cette étape permet de simplifier le processus de conversion en identifiant les éléments clés du texte, tels que les titres, les listes, les liens ou autres.
- Arbre syntaxique abstrait (AST) : L'AST est une structure de données qui représente le texte d'entrée sous une forme hiérarchique. Il est utilisé pour faciliter la conversion du texte d'entrée en HTML en permettant de naviguer et de manipuler facilement la structure du document.
- Conversion en HTML (Parser) : Une fois l'AST créé, le programme parcourt cette structure pour générer le code HTML correspondant. Cette étape assure que le formatage et la mise en page du texte d'entrée sont préservés dans la sortie HTML.

## Documents supportés

Tous les fichiers terminés par `.md` qui respectent la spécification markdown

## Exemple

Ficher `test/font_style.md` -> `output.html`

<img src="https://thearchyhelios.com/images/INF404/rapport%20image%201.png" alt="image1" style="zoom:33%;" /><img src="https://thearchyhelios.com/images/INF404/rapport%20image%203.png" alt="image3" style="zoom:33%;" />

<img src="https://thearchyhelios.com/images/INF404/rapport%20image%202.png" alt="image2" style="zoom: 33%;" />
