#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdlib.h>
#include <stdio.h>

/**
 * \enum elem_t
 * \brief Strucutre sur le contenu des éléments de la liste.
 */

typedef struct elem_s
{
	int x; /*!< Position en x */
	int y; /*!< Position en y */

	struct elem_s * suivant; /*!< Permet de passer à l'élément suivant de la liste */
}elem_t;


/**
 * \enum liste_t
 * \brief Structure de pointeur sur elem_t.
	    Cette structure est utilisée pour les fonctions de liste
 */

typedef struct liste_s
{
	elem_t * premier; /*!< Pointeur sur le premier élément de le liste */
	elem_t * courant; /*!< Pointeur sur l'élément courant de la liste */
}liste_t;


liste_t * liste_init();

void insertion(liste_t *);

int liste_vide(liste_t *);
int fin_liste(liste_t *);

void afficher_liste(liste_t *);

void liste_debut(liste_t *);
void liste_suivant(liste_t *);
void liste_fin(liste_t * liste);

elem_t * element_courant(liste_t *);

int elememt_existe(elem_t *);

void afficher_element(elem_t *);

void detruire_liste(liste_t **);
void detruire_dernier_elem(liste_t **);
#endif
