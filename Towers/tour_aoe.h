#ifndef _TOUR_AOE_H_
#define _TOUR_AOE_H_

#include "../all.h"

typedef struct tour_aoe_s
{
	#include "attributs_tour.h"
} tour_aoe_t;

tour_aoe_t * creer_tour_aoe( int x, int y );

//void afficher_tour_aoe( tour_aoe_t * );

void evoluer_tour_aoe( tour_aoe_t * );

void detruire_tour_aoe( tour_aoe_t ** );

#endif
