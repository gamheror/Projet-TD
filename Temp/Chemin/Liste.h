#ifndef _LISTE_H_
#define _LISTE_H_

#include "../all.h"

typedef struct elem_s
{
	int x;
	int y;

	struct elem_s * suivant;
}elem_t;

typedef struct liste_s
{
	elem_t * premier;
	elem_t * courant;
}liste_t;

liste_t * initialisation();

void insertion(liste_t *);

int liste_vide(liste_t *);
int fin_liste(liste_t *);

void afficher_liste(liste_t *);

void liste_debut(liste_t *);
void liste_suivant(liste_t *);

elem_t * element_courant(liste_t *);

int elememt_existe(elem_t *);

void afficher_element(elem_t *);

#endif
