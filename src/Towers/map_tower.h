#ifndef _MAP_TOWER_H_
#define _MAP_TOWER_H_

#include "tour.h"
#include "../Chemin/liste.h"

/*-------- Macro --------*/
/**
 * \def COORD(map, x, y)
 * \brief simplifie l'acces a la matrice de tours qui est implémenté en tant que tableau de pointeur sur tour_t
 * 
 * \param la map_tower, les coordonnées x,y
 * \return retourne le pointeur sur tour_t dans le tableau de tour_t
*/
#define COORD(map, x, y) (*(map +y*N +x))


/*-------- Type --------*/
typedef tour_t ** map_tower;						//Nouveau type : matrice de pointeur sur tour_t			


/*-------- Creation --------*/
map_tower creer_map_tower();						//Création de la map
map_tower init_mat_tower(liste_t *);							//Création et initialise de la map
map_tower charger_map();							//Création de la map et initialisation avec fichier sauvegarde


/*-------- Booléennes --------*/
int map_existe(map_tower);							//Renvoie vrai si map a été initialisée
int case_vide(map_tower, int, int);					//Renvoie vrai si la case passée en param est vide


int poser_tour(map_tower, int, int, type_tour);		//Pose une tour aux coordonnees
int evoluer_tour(map_tower, int, int);				//La tour en x,y evolue

int attaquer_tour(map_tower, mobs_t *[], int, int *);		//Les tours de la map effectue une attaque
void afficher_map_tower(map_tower);					//Affiche la map

type_tour get_type_tour(map_tower, int, int);		//Renvoie le tyoe de la tour aux coord, -1 si case vide, -2 si map NULL
int get_niveau_tour(map_tower, int, int);			//renvoiele niveau de la tour aux coord

/*-------- Destruction --------*/
int detruire_map_tower(map_tower*);					//Supprime la map

#endif
