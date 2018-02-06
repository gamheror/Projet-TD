#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mobs.h"

#define LIFE 200
#define V_DEP 10

mobs_t * mobs_creer()
{
	mobs_t * mobs = malloc(sizeof(mobs_t));
	
	mobs->life = LIFE;
	mobs->v_deplacement = V_DEP;
	mobs->gold = rand()%1000;
	
	return mobs;
}

void afficher_mobs(mobs_t * mobs)
{
	printf("{mob {%d, %d}}", mobs->life, mobs->gold);
	
}

void detruire_mobs(mobs_t ** mobs)
{
	free(*mobs);
	*mobs = NULL;
}

/*
void perte_vie (mobs_t * mobs, tower_t * tower, void(*focus)(int *)
{
	boucle avec la range de la tour
		utilisation de la fonction focus
		boucle vie du mob > 0
			-> dégâts continue
			-> mise à jour de la vie à chaque coups 
			-> utilisation de la structure attaque(tower)
		fin  
}
*/

