#include "all.h"

int main()
{
	map_tower map;
	srand(time(NULL));

	GOLD = 100000;
	
//	mobs_t * mobs[N][N];
//	for(int i = 0; i < N; i++)
//		for(int j = 0; j < N; j++)
//			mobs[i][j] = NULL;
	
/*	printf("Initialisation de la map\n");*/
/*	map = init_mat_tower();*/
/*	*/
/*	poser_tour(map, 4, 4, MONO);*/
/*	poser_tour(map, 4, 4, AOE);*/
/*	poser_tour(map, 1, 1, MONO);*/
/*	*/
/*	afficher_map_tower(map);*/
/*	*/
/*	//evoluer_tour(map, 4, 4);*/
/*	*/
/*//	printf("Attaque des tours\n");*/
/*//	attaquer_tour(map, mobs);*/
/*	*/
/*	//afficher_map_tower(map);*/
/*	*/
/*	printf("Destruction\n");*/
/*	detruire_map_tower(&map);*/
/*	*/
/*	afficher_map_tower(map);*/
/*	*/
/*	detruire_map_tower(&map);*/
	printf("Chargement des données\n");
	map = charger_map();
	
	afficher_map_tower(map);
	
	printf("Destruction\n");
	detruire_map_tower(&map);
	
	afficher_map_tower(map);
	
	
}
