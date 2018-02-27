#include "all.h"

/* Detruire les tours presentent sur la map */
void detruire_tours( tour_t * t[N][N] )
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if( t[i][j] != NULL )
				t[i][j]->detruire( (void**)&t[i][j] );
}

void afficher_tower(tour_t * t[N][N], mobs_t * m[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("%c", t[i][j] == NULL ? ' ' : 'T' );
			printf("%c", m[i][j] == NULL ? ' ' : 'M' );
		}
		printf("\n");
	}
}

void attaque_tours(tour_t * t[N][N], mobs_t * m[N][N])
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			if( tour_existe(t[i][j]) )
				t[i][j]->attaquer( t[i][j], (void*(*)[N])m );
		}
}

void init_mat(void * mat[N][N])
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			mat[i][j] = NULL;
}

int main()
{
	srand(time(NULL));
	GOLD = 10000;
	
	tour_t * tower[N][N];
	mobs_t * mob[N][N];
	init_mat( (void *)tower);
	init_mat( (void *)mob);
	
	tower[1][1] = (void*) creer_tour_mono(1, 1);
	tower[2][1] = (void*) creer_tour_aoe(2, 1);
	tower[4][4] = (void*) creer_monument(4, 4);
//	mob[3][3] = creer_mobs(3,3);
//	mob[3][4] = creer_mobs(3,4);
		
	printf("\nMAP :\n");
	afficher_tower(tower, mob);
	
	while(mob[3][4] != NULL || mob[3][3] != NULL)
	{
		attaque_tours(tower, mob);
		
		tower[1][1]->evoluer( tower[1][1] );
		tower[2][1]->evoluer( tower[2][1] );
		
		printf("\n");
	}
	
	printf("\nEnnemis tués :\n");
	afficher_tower(tower, mob);

	printf("GOLD : %d\n", GOLD);
	
	detruire_tours(tower);
}







