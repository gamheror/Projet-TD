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
map_tower init_mat_tower();							//Créé et renvoie la mapx


/*-------- Fonctions booléennes --------*/
int map_existe(map_tower);							//Renvoie vrai si map a été initialisée
int case_vide(map_tower, int, int);					//Renvoie vrai si la case passée en param est vide


/*-------- Modifications --------*/
int poser_tour(map_tower, int, int, type_tour);		//Pose une tour aux coordonnees
int evoluer_tour(map_tower, int, int);				//La tour en x,y evolue
int attaquer_tour(map_tower, mobs_t *(*)[20]);		//Les tours de la map effectue une attaque


/*-------- Affichage --------*/
void afficher_map_tower(map_tower);					//Affiche la map


/*-------- Destruction --------*/
int detruire_map_tower(map_tower*);					//Supprime la map

#endif
