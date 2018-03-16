#include "all.h"

mobs_t * mobs[N][N];
/*
void afficher(map_tower map)
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			if(!case_vide(map, j, i))
				COORD(map, j, i)->afficher( COORD(map, j, i) );
			else if(mobs[j][i] != NULL)
				printf("x");
			else
				printf(" ");
		printf("\n");
	}
}
*/
int main()
{
	
	map_tower map;
	srand(time(NULL));

	GOLD = 100000;
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			mobs[i][j] = NULL;
	mobs[2][2] = creer_mobs();
	mobs[2][3] = creer_mobs();
	mobs[3][2] = creer_mobs();
	
	printf("\n\tInitialisation de la map\n");
	map = init_mat_tower();
	
	poser_tour(map, 4, 4, MONO);
	poser_tour(map, 4, 3, AOE);
	poser_tour(map, 1, 1, MONO);
	afficher_map_tower(map);

	printf("Attaque des tours\n");
	attaquer_tour(map, mobs);
	
	evoluer_tour(map, 4, 4);
	afficher_map_tower(map);
	
	printf("Destruction\n");
	detruire_map_tower(&map);
	afficher_map_tower(map);

	printf("\n\tChargement des données\n");
	map = charger_map();
	afficher_map_tower(map);
	
	
	printf("Attaque sur le monument :\n");
	attaquer_monument(map, 120);
	printf("\n");	

	
		
	evoluer_tour(map, 4, 4);
	evoluer_tour(map, 1, 1);
	evoluer_tour(map, 4, 3);
	afficher_map_tower(map);
	
	printf("Destruction\n");
	detruire_map_tower(&map);
	afficher_map_tower(map);
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if( mobs[i][j] != NULL)
				detruire_mobs(&mobs[i][j]);
}
