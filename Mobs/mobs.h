#ifndef _MOB_H_
#define _MOB_H_

#include <stdlib.h>
#include <stdio.h>

#include "../all.h"
#include "mobs.h"
#include "../Chemin/liste.h"

typedef struct mobs_s
{
	int attaque;
	int life;
	int v_deplacement;
	char caract;
	
	//position des mobs
	liste_t * pos;

	//trouver comment insérer la structure attaque;
	//void (*perte_vie)(struct mobs_t *);
	void (*detruire)(struct mobs_s **);
	
} mobs_t;


/* Creation d'un objet mobs_t */
mobs_t * creer_mobs_normal();
mobs_t * creer_mobs_tank();
mobs_t * creer_mobs_degat();

/* Affiche la vie et les gold portes par le mob */
void afficher_mobs(mobs_t * );

/* Assaine des degats au mob, si vie <= 0, il est detruit */
void perte_vie (mobs_t ** , int);

/* Libere l'espace memoire alloue a un mob */
void detruire_mobs(mobs_t **);

/* Assaine des dégats au monument */
void attaque_monum(mobs_t *);

/* Creation de la vague */
void creer_vague(char);

#endif
