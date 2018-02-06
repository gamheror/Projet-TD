#ifndef _TOUR_AOE_H_
#define _TOUR_AOE_H_

#include "tour.h"

typedef struct tour_aoe_s
{
	#include "attributs_tour.h"
	
	void (*detruire)( struct tour_aoe_s ** );
} tour_aoe_t;

tour_aoe_t * creer_tour_aoe(  );

void afficher_tour_aoe( tour_aoe_t * );

void detruire_tour_aoe( tour_aoe_t ** );

#endif
