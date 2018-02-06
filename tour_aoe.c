#include <stdio.h>
#include <stdlib.h>

#include "tour_aoe.h"

#define DEGATS_TOUR_N_1		150
#define RAYON_TOUR			5
#define COOLDOWN_TOUR		500

tour_aoe_t * creer_tour_aoe(  )
{
	tour_aoe_t * aoe = (tour_aoe_t*)creer_tour();
	aoe = realloc(aoe, sizeof(tour_aoe_t));
	
	aoe->detruire = detruire_tour_aoe;
	
	return aoe;
}

void afficher_tour_aoe( tour_aoe_t * aoe )
{
	if( existe_tour( aoe) )
	{
		printf("{AOE ");
		afficher_tour( (tour_t*)aoe );
		printf(" }");
	}
	else
		printf("{NULL}");
}

void detruire_tour_aoe( tour_aoe_t ** aoe )
{
	if( existe_tour( (*aoe) ) )
	{
		free(*aoe);
		*aoe = NULL;
	}
}
