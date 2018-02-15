#include "all.h"

void detruire_tours( tour_t * t[N][N] )
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			t[i][j]->detruire((void**)&t[i][j]);
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

void init_mat(void * mat[N][N])
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			mat[i][j] = NULL;
}

int main()
{
	srand(time(NULL));
	gold = 10000;
	
	tour_t * tower[N][N];
	mobs_t * mob[N][N];
	init_mat( (void *)tower);
	init_mat( (void *)mob);
	
	tower[1][1] = (void*) creer_tour_mono(1, 1);
	tower[2][1] = (void*) creer_tour_aoe(2, 1);
	mob[3][3] = creer_mobs(3,3);
	mob[3][4] = creer_mobs(3,4);
		
	printf("\nMAP :\n");
	afficher_tower(tower, mob);
	
	while(mob[3][4] != NULL || mob[3][3] != NULL)
	{
		tower[1][1]->attaquer( tower[1][1], (void *(*)[N])(&mob) );
		tower[2][1]->attaquer( tower[2][1], (void *(*)[N])(&mob) );
		
		tower[1][1]->evoluer( tower[1][1] );
		tower[2][1]->evoluer( tower[2][1] );
		
		printf("\n");
	}
	
	printf("\nEnnemis tués :\n");
	afficher_tower(tower, mob);

	printf("Gold : %d\n", gold);
	
	detruire_tours(tower);
}







