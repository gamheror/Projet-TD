#ifndef _TOUR_H_
#define _TOUR_H_

#include <stdlib.h>

typedef struct tour_s
{
	#include "attributs_tour.h"
} tour_t;

/* Creer une tour de niveau 1, 
	renvoie son adresse memoire */
tour_t * creer_tour(  );

/* Revoie 0 n'existe pas
	!= 0 si la tour existe */
int existe_tour( void * );

/* Afficher le niveau de la tour et ses degats 
	{niveau degats}*/
void afficher_tour( tour_t * );

/* Le tour gagne un niveau et en degats
	Le niveau max est limité par une constante
	La tour gagne un nombre fixe de degat */
void evoluer_tour( tour_t * );

/* Libere l'espace memoire de la tour */
void detruire_tour( tour_t ** );

#endif
