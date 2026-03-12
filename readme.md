## FIRE-DRIVE

Code du projet robotique, réalisé dans le cadre de l'unité d'enseignement SDI1201

### Fichiers

code.c : main
code_test.c : test get_to_light 

(extension ".c" pour couleurs sur VSCode, langage réel : NXT)

### Réussite
- get_to_light :
    Renvoie bien de quel coté est la lumière et donc quel coté à suivre
- follow_light :
    Suit bien la lumière en fonction de son intensité. Ajout d'un seuil de tolérance sur la fonction get_to_light pour éviter les secousses
- is_obstacle/get_distance : 
    nous renvoie bien si obstacle il y a à partir d'un certain seuil ( à savoir 30cm, ce seuil est choisi à partir de la taille (longueur) du robot ). Dans la seconde fonction, il nous renvoie aussi la distance à laquelle l'obstacle se situe SI celui-ci est à moins de 30cm !! 
- follow_light_lux:
    Suit la lumière via hystérésis permet de réduire les sécousses tout en suivant l'intensité lumineuse

### Known issues 
- turn() à revoir, soucis lors des essais sur square()
- attention à l'ombre de notre robot qui peut fausser nos mesures de lumières

### A faire
- voire un accélération/décélération ==> moins de glissement, on va de 0 à 100% progressivement. 
- Implémenter l'hystérésis dans le code 
- priorité et échange entre les capteurs US et light
- cas particuliers sans lumière : 
    cas où on est dans l'ombre
    ( autres à réfléchir) 
- manoeuvre d'évitement via capteur ultrason
- attention à ce que les informations ne se chevauchent pas ! ( qu'une manoeuvre déclenchée par le capteur US ne soit pas interrompue par une information du capteur LUM)
- Tester la sensibilité de follow_light_lux pour 2.50m 

## DONE 
- seuil de tolérance lumière. get_to_light() fonctionne en binaire donc risque de tremblements lors des manoeuvres. 
- avancer en fonction de cette information de position lumière ( fonction follow_light)
- tourner en avançant ( pas s'arrêter pour tourner) ==> Pour être précis, on ne s'arrête pas entre deux manoeuvres
- tourner plus lentement que l'on avance 
- tester la détection d'obstacle par capteur à ultrason 
