#ifndef _MOB_H_
#define _MOB_H_

#include "../all.h"
#include "../Chemin/liste.h"

typedef struct mobs_s
{
	int attaque;
	int life;
	int v_deplacement;
	char caract;
	
	//position des mobs
	liste_t *pos;

	//trouver comment insérer la structure attaque;
	//void (*perte_vie)(struct mobs_t *);
	void (*detruire)(struct mobs_s **);
	
}mobs_t;

/* Creation d'un objet mobs_t */
mobs_t * creer_mobs(/*elem_t **/);

/* Affiche la vie et les gold portes par le mob */
void afficher_mobs(mobs_t * );

/* Assaine des degats au mob, si vie <= 0, il est detruit */
void perte_vie (mobs_t ** , int);

/* Libere l'espace memoire alloue a un mob */
void detruire_mobs(mobs_t **);

/*Change les coordonnées du mobs*/
void changement_coord(mobs_t *);

/* création de mobs pour une vague*/
/*void vague(int);*/

#endif