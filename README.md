# SNAKE-game 🐍
The famous and classical game Snake in C. 

Un petit projet crée sur la dernière semaine de novembre 2024. 

J'ai utilisé les listes chaînées (qui me paraissaient être le choix le plus logique) pour contrôler le corps de mon serpent (suppression et ajout de noeuds, contrôle des collisions, ...). En effet, toutes les positions doivent être sauvegardées. 
La fonction logique du jeu détecte les touches appuyées par l'utilisateur et rend compte du mouvement du serpent à l'écran. 
La tête du serpent (le premier noeud) est ensuite dessiné à l'écran et sa position est sauvegardée dans des variables prevX et prevY. 

Une boucle while parcourt ensuite le reste de la liste chaînée `current` (le reste des segments, du corps du serpent) 
en sauvegardant chaque segment dans des variables tempX et tempY et en effacant le segment actuel, puis en le redessinant à la position de la tête (`prevX` et `prevY`). Il en va de même pour les autres segments jusqu'à ce que `current`-> NULL. 

![image](https://github.com/user-attachments/assets/e9e8d2b2-31cc-47ac-9408-3a982a1ba262)

![image](https://github.com/user-attachments/assets/a78a975d-9c63-4462-8147-c880de25c243)


# Jouabilité : 
- Les fleches du clavier pour se déplacer.

- Evitez les murs et votre propre corps. 

- Atteignez un score de 1000.

# [Démo]: 

https://youtu.be/O-GwJnR1Qgk
