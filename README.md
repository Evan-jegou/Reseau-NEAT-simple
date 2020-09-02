  
# Réseau NEAT simple :

Il s'agit du tout premier réseau NEAT que j'ai réalisé. Il n'est donc pasz très optimisé. 
Le code a été produit en C à l'aide du logiciel Code-Blocks et nécessite les bibliothèques suivantes pour fonctionner :
	
	- SDL
	- SDL_image
	- stdlib.h
	- stdio
	- string
	- ctype.h
 	- math.h
	- errno.h

Description :

Lors du lancement du logiciel, vous remarquerez de multiple point rouge ansin que des points blanc sur la map. Les point rouge sont de la nouriture et les point blanc des oeufs prêt à éclore. Après un peu de temps, les oeufs éclosent et une première génération de cellule commencent à se mouvoir. Les cellules verte se nourrissent des points rouges et les cellules rouge sont les prédatrices qui se nourrissent des cellules vertes. 
Les cellules poeuvent effectuer 3 actions. Bouger plus ou moins en x, bouger plus ou moins en y et pondre des oeufs. Elles sont aussi capable de percevoir la nouriture, les oeufs et de se percevoir entre elles. 
Lors du lancement, les cellules ne sont pas entrainées et bougeront un peu n'importe comment. Au fur et à mesure des générations, cependant, les meilleurs survivront et se reproduiront plus que la moyenne tandis que les moins bonnes mourront. Leur comportement s'optimisera donc ainsi petit à petit. 
