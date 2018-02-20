#ifndef _MONUMENT_H_
#define _MONUMENT_H_

#include "../all.h"
#include "../Mobs/mobs.h"

typedef struct monument_s
{
	#include "attributs_tour.h"
} monument_t;

monument_t * creer_monument(int, int);

void detruire_monument(monument_t **);

#endif
