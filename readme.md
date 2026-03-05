## Robot NXT

Code du projet robotique, réalisé dans le cadre de l'unité d'enseignement SDI1201

### Fichiers

code.c : main
code_test.c : test get_to_light 

(extension ".c" pour couleurs sur VSCode, langage réel : NXT)

### Réussite
- get_to_light :
    Renvoie bien de quel coté est la lumière et donc quel coté à suivre

### Known issues 
- turn() à revoir, soucis lors des essais sur square()

### A faire
- seuil de tolérance lumière. get_to_light() fonctionne en binaire donc risque de tremblements lors des manoeuvres. 
- avancer en fonction de cette information de position lumière ( fonction follow_light)

- tourner plus lentement que l'on avance 
- voire un accélération/décélération ==> moins de glissement, on va de 0 à 100% progressivement. 