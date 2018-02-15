#ifndef _TOUR_MONO_H_
#define _TOUR_MONO_H_

#include "../all.h"
#include "../Mobs/mobs.h"

typedef struct tour_mono_s
{
	#include "attributs_tour.h"
	
	mobs_t * cible;
	int x_cible, y_cible;
	
} tour_mono_t;

tour_mono_t * creer_tour_mono( int x, int y );

void afficher_tour_mono( tour_mono_t * );

void evoluer_tour_mono( tour_mono_t * );

void detruire_tour_mono( tour_mono_t ** );

#endif
