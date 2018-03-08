#ifndef _TOUR_H_
#define _TOUR_H_

#include "../all.h"
#include "../Mobs/mobs.h"

#define LIMITES_MAP(x) (x >= 0 && x < N)

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
tour_t * creer_tour(int, int, int);
tour_aoe_t * new_aoe(int, int, int);
tour_aoe_t * creer_tour_aoe(int, int);
tour_mono_t * new_mono(int, int, int);
tour_mono_t * creer_tour_mono(int, int);
monument_t * new_monument(int, int, int);
monument_t * creer_monument(int, int);


/*-------- Fonction booléenne --------*/
int tour_existe( void * );


/*-------- Evolution --------*/
int evolution_tour( tour_t * );


/*-------- Destruction --------*/
int detruire_tour( tour_t ** );
int detruire_tour_aoe( tour_aoe_t ** );
int detruire_tour_mono( tour_mono_t ** );
int detruire_monument(monument_t **);

#endif
