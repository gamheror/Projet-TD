#ifndef _TOUR_H_
#define _TOUR_H_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../all.h"
#include "../Mobs/mobs.h"

#define A_PORTE(x1, y1, x2, y2, r) (abs(x1-x2) + abs(y1-y2) <= r)

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
	
	mobs_t * cible; 	/*!< pointeur sur la structure mob pour avoir accès à ce qu'elle contient */
	int pos_mob;	/*!< variable qui va prendre comme valeur la position du mob */
} tour_mono_t;

typedef struct monument_s
{
	#include "attributs_tour.h"
	
	int pv;		/*!< variable qui va prendre comme valeur les pv du monument*/
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


monument_t * get_monu();
int degats_monu(int);
int monu_est_detruit();

type_tour get_type(tour_t *);


/*-------- Destruction --------*/
int detruire_tour( tour_t ** );
int detruire_tour_aoe( tour_aoe_t ** );
int detruire_tour_mono( tour_mono_t ** );
int detruire_monument(monument_t **);

#endif
