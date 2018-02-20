#include "../all.h"

tour_t * creer_tour( int x, int y )
{
	tour_t * tour = NULL;
	
	tour = malloc(sizeof(tour_t));

	if( tour == NULL )
		printf("Erreur de creation d'une tour\n");
	else
	{
		tour->niveau = 1;
		tour->rayon = RAYON_TOUR;
		tour->cooldown = COOLDOWN_TOUR;
		tour->pos_x = x;
		tour->pos_y = y;
	}
	
	return tour;
}

int tour_existe( void * tour )
{
	return tour != NULL ;
}

void afficher_tour( tour_t * tour )
{
	tour_existe(tour) ? printf("{%d %d}", tour->niveau, tour->degat) : printf("{NULL}");
}

void evoluer_tour( tour_t * tour )
/* 1 -> 2 100 gold
	2 -> 3 200 gold
	3 -> 4 300 gold
	4 -> 5 400 gold */
{
	if( tour_existe(tour) )
	{
		int n = tour->niveau;
		if( n < NIVEAU_MAX_TOUR && GOLD >= 100*n )
		{
			GOLD -= 100*n;
			
			tour->niveau++;
			tour->degat *= MULT_DEGATS_TOUR;
		}
	}
	else
		printf("Evolution d'une tour inexistante !\n");
}

void detruire_tour( tour_t ** tour )
{
	if( tour_existe(*tour) )
	{
		free(*tour);
		*tour = NULL;
	}
}
