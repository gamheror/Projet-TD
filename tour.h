#ifndef _TOUR_H_
#define _TOUR_H_

#include "../all.h"
#include "../Mobs/mobs.h" //l'objet mobs_t n'est pas reconnu sans cette ligne, alors qu'il est include dans "all.h"...

typedef struct tour_s
{
	#include "attributs_tour.h"
} tour_t;

/* Creer une tour de niveau
	les coordonnees de la tour dans la matrice sont passees en param */
tour_t * creer_tour( int x, int y );

/* Revoie 0 n'existe pas
	!= 0 si existe */
int tour_existe( void * );

/* Afficher le niveau de la tour et ses degats 
	{niveau degats}*/
void afficher_tour( tour_t * );

/* La tour gagne un niveau et des degats
	Le niveau max est limité par une constante
	La tour gagne un nombre fixe de degat */
void evoluer_tour( tour_t * );

/* Libere l'espace memoire de la tour */
void detruire_tour( tour_t ** );

#endif
