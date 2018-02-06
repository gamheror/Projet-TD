#include <stdio.h>
#include <stdlib.h>

#include "tour.h"

#define NIVEAU_MAX_TOUR		5
#define DEGATS_TOUR_N_1		150
#define DEGATS_TOUR_PAR_N	75
#define RAYON_TOUR			5
#define COOLDOWN_TOUR		500
#define PRIX				200

tour_t * creer_tour(  )
{
	tour_t * tour = malloc(sizeof(tour_t));
	
	tour->niveau = 1;
	tour->degat = DEGATS_TOUR_N_1;
	tour->rayon = RAYON_TOUR;
	tour->cooldown = COOLDOWN_TOUR;
	tour->prix = PRIX;
	
	return tour;
}

int existe_tour( void * tour )
{
	return tour != NULL ;
}

void afficher_tour( tour_t * tour )
{
	existe_tour(tour) ? printf("{%d %d}", tour->niveau, tour->degat) : printf("{NULL}");
}

void evoluer_tour( tour_t * tour )
{
	if( existe_tour( tour) )
	{
		if( tour->niveau < NIVEAU_MAX_TOUR )
		{
			tour->niveau++;
			tour->degat += DEGATS_TOUR_PAR_N;
		}
	}
}

void detruire_tour( tour_t ** tour )
{
	if( existe_tour(*tour) )
	{
		free(*tour);
		*tour = NULL;
	}
}
