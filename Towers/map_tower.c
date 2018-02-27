#include "monument.h"
#include "map_tower.h"

map_tower init_mat_tower()
{
	map_tower map = NULL;
	map = malloc(N*N*sizeof(*map));
	
	/* Initialise les pointeurs de la matrice à NULL */
	if( map != NULL )
	{
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				*(map +i*N +j) = NULL;

		*(map +5*N +5) = creer_monument(5, 5);
	}
	
	/* Ouvre le fichier des tours, s'il n'existe pas, il est créé */
	FILE * fic = fopen("fichier_tours.txt", "r");
	if( fic == NULL )
		fic = fopen("fichier_tours.txt", "w");
	
	return map;
}

int map_existe( map_tower map )
{
	return map != NULL;
}

int case_vide(map_tower map, int x, int y)
{
	return *(map +y*N +x) == NULL;
}

int detruire_case(map_tower map, int x, int y)
{
	if( !map_existe(map) )
		return 0;
	
	(*(map +y*N +x))->detruire( (void**)(map +y*N +x) );
	return 1;
}

void afficher_map_tower(map_tower map)
{
	if( map_existe(map) )
	{
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
				case_vide(map, j, i) ? printf(" ") : printf("T");
			printf("\n");
		}
			
				
	}
}

int detruire_map_tower( map_tower * map )
{
	if( !map_existe(*map) )
		return 0;
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if( !case_vide(*map, i, j) )
				detruire_case(*map, i, j);
	
	free(*map);
	*map = NULL;
	
	return 1;
}

