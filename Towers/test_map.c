#include <stdlib.h>
#include <stdio.h>

#include "../all.h"
#include "map_tower.h"

int main()
{
	map_tower map = init_mat_tower();
	
	afficher_map_tower(map);
	
//	detruire_map_tower(&map);
}
