#ifndef _TOUR_MONO_H_
#define _TOUR_MONO_H_

#include "tour.h"

typedef struct tour_mono_s
{
	#include "attributs_tour.h"
	void * ennemi;
	
	void (*detruire)( struct tour_mono_s ** );

} tour_mono_t;

tour_mono_t * creer_tour_mono(  );

void afficher_tour_mono( tour_mono_t * );

void detruire_tour_mono( tour_mono_t ** );

#endif