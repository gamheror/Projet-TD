#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct liste_s
{
	int x;
	int y;

	struct liste_s * suivant;
}liste_t;

typedef struct elem_s
{
	liste_t * premier;
}elem_t;

elem_t * initialisation();
void insertion(elem_t *);
void afficher_liste(elem_t *);

#endif