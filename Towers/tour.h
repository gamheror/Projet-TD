#ifndef _TOUR_H_
#define _TOUR_H_

#include "../all.h"
#include "../Mobs/mobs.h"

/*-------- Structures --------*/
typedef struct tour_s
{
	#include "attributs_tour.h"
} tour_t;

typedef struct tour_aoe_s
{
	#include "attributs_tour.h"
} tour_aoe_t;

typedef struct tour_mono_s
{
	#include "attributs_tour.h"
	
	mobs_t * cible;
	int x_cible, y_cible;
	
} tour_mono_t;

typedef struct monument_s
{
	#include "attributs_tour.h"
} monument_t;


/*-------- Creation --------*/
tour_t * creer_tour(int, int);
tour_aoe_t * creer_tour_aoe(int, int);
tour_mono_t * creer_tour_mono(int, int);
monument_t * creer_monument(int, int);


/*-------- Fonction booléenne --------*/
int tour_existe( void * );


/*-------- Attaque --------*/
void tour_aoe_attaquer(tour_aoe_t *, mobs_t *(*)[20]);
void tour_mono_attaquer( tour_mono_t *, mobs_t *(*)[20] );


/*-------- Modifications --------*/
int evolution_tour( tour_t * );
int evoluer_tour_aoe( tour_aoe_t * );
int evoluer_tour_mono( tour_mono_t * );


/*-------- Destruction --------*/
int detruire_tour( tour_t ** );
int detruire_tour_aoe( tour_aoe_t ** );
int detruire_tour_mono( tour_mono_t ** );
int detruire_monument(monument_t **);

#endif
