/*
	Permet la creation et l'utilisation d'une matrice de tours,
	Lorsqu'une nouvelle tour est posée ou qu'une tour evolue, la sauvegarde est automatiquement modifiée.
	Les fonctions principales et leur utilisation sont les suivantes :
	
	map_tower map = init_mat_tower();	-> creer la matrice en debut de jeu
	
	map_tower map = charger_map();		-> creer la map et place les tours de la partie sauvegardée
	
	poser_tour(map, 1, 1 MONO/AOE);		-> pose une tour MONO/AOE sur la map en (1,1) (coups en GOLDS)
	
	evoluer_tour(map, 1, 1);			-> si il y a une tour en (1,1) sur la map, celle-ci evolue (coups en GOLDS)
	
	attaquer_tour(map);					-> Toutes les tours effectue une attaque
	
	detruire_map_tower(&map);			-> libere la memoire allouée a la map et aux tours qui en faisait partie
*/

#ifndef _MAP_TOWER_H_
#define _MAP_TOWER_H_

#include "../all.h"

/*-------- Macro --------*/
#define COORD(map, x, y) (*(map +y*N +x))


/*-------- Enumération --------*/
typedef enum {AOE, MONO} type_tour;


/*-------- Type --------*/
typedef tour_t ** map_tower;						//Nouveau type : matrice de pointeur sur tour_t			


/*-------- Creation --------*/
map_tower creer_map_tower();						//Création de la map
map_tower init_mat_tower();							//Création et initialise de la map
map_tower charger_map();							//Création de la map et initialisation avec fichier sauvegarde


/*-------- Booléennes --------*/
int map_existe(map_tower);							//Renvoie vrai si map a été initialisée
int case_vide(map_tower, int, int);					//Renvoie vrai si la case passée en param est vide


int poser_tour(map_tower, int, int, type_tour);		//Pose une tour aux coordonnees
int evoluer_tour(map_tower, int, int);				//La tour en x,y evolue

int attaquer_tour(map_tower, mobs_t *(*)[20]);		//Les tours de la map effectue une attaque
void afficher_map_tower(map_tower);					//Affiche la map


/*-------- Destruction --------*/
int detruire_map_tower(map_tower*);					//Supprime la map

#endif
