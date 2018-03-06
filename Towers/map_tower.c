#include "map_tower.h"

/*-------- Creation --------*/
map_tower init_mat_tower()
{
	map_tower map = NULL;
	map = calloc(N*N, sizeof(*map)); //Alloue de la memoire et initialise à zéro
	
	if(map == NULL)
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création de la map de tours !\n");
		return NULL;
	}
	
	//Test l'existance du fichier de sauvegarde des tours, créé un nouveau
	FILE * fic;
	fic = fopen("fichier_tours.txt", "w");
	fclose(fic);
	
	//Pose le monument
	srand(time(NULL));
	int x = rand()%N, y = rand()%N;
	COORD(map, x, y) = (tour_t *) creer_monument(x, y);
	
	return map;
}


/*-------- Booléenes --------*/
int map_existe( map_tower map )
{
	return map != NULL;
}

int case_vide(map_tower map, int x, int y)
{
	return COORD(map, x, y) == NULL;
}


/*-------- Modifications --------*/
int poser_tour(map_tower map, int x, int y, type_tour type)
{
	if(!map_existe(map))
		return OBJ_NULL;
	if(!case_vide(map, x, y))
		return CASE_OCCUPEE;
	
	switch(type)
	{
		case AOE:
			COORD(map, x, y) = (tour_t *) creer_tour_aoe(x, y);
			if(COORD(map, x, y))
				printf("AOE posée en <%02d,%02d>\n", x, y);
			break;
		case MONO:
			COORD(map, x, y) = (tour_t *) creer_tour_mono(x, y);
			if(COORD(map, x, y))
				printf("MONO posée en <%02d,%02d>\n", x, y);
			break;
		default:
			printf("\tERREUR, le type de tour %d n'existe pas !\n", type);
	}
	
	return OK;
}

int evoluer_tour(map_tower map, int x, int y)
{
	if(!map_existe(map))
		return OBJ_NULL;
	if(case_vide(map, x, y))
		return CASE_VIDE;
	
	return COORD(map, x, y)->evoluer( COORD(map, x, y) );;
}

int attaquer_tour(map_tower map, mobs_t * mat[][N])
{
	if(!map_existe(map))
		return OBJ_NULL;
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(!case_vide(map, j, i))
				COORD(map, j, i)->attaquer( COORD(map, j, i), (void *)mat );
	
	return OK;
}


/*-------- Affichage --------*/
void afficher_map_tower(map_tower map)
{
	if( !map_existe(map) )
	{
		printf("La map n'existe pas !\n");
		return;
	}
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			if(case_vide(map, j, i))
				printf(" ");
			else
				COORD(map, j, i)->afficher( COORD(map, j, i) );
		printf("\n");
	}
}


/*-------- Destruction --------*/
int detruire_map_tower( map_tower * map )
{
	if( !map_existe(*map) )
		return OBJ_NULL;
	
	//Libere les cases une a une
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if( !case_vide(*map, j, i) )
				COORD(*map, j, i)->detruire( (void**) &COORD(*map, j, i) );
	
	//Libere la matrice
	free(*map);
	*map = NULL;

	return OK;
}
