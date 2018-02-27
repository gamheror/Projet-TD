#ifndef _MAP_TOWER_H_
#define _MAP_TOWER_H_

#include "../all.h"
#include "tours.h"

/* Créé un nouveau type, tableau de pointeur sur tour_t */
typedef tour_t ** map_tower;

map_tower init_mat_tower();

int map_existe(map_tower);
int case_vide(map_tower, int, int);

int detruire_case(map_tower, int, int);

void afficher_map_tower(map_tower);

int detruire_map_tower(map_tower*);

#endif
