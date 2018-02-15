#include "../all.h"


static int compteur_mobs = 0;

void afficher_mobs(mobs_t * mobs)
{
	if(mobs != NULL)
		printf("{mob {%d, %d}}\n", mobs->life, mobs->gold);

	else
	{
		printf("{mob NULL}\n");
	}
}

void detruire_mobs(mobs_t ** mobs)
{
	free(*mobs);
	*mobs = NULL;

	compteur_mobs --;

}


void perte_vie (mobs_t ** mobs, int nb_degat)
{
	(*mobs)->life -= nb_degat;

	if ((*mobs)->life <= 0)
		(*mobs)->detruire(mobs);
 
}


mobs_t * creer_mobs()
{
	mobs_t * mobs = malloc(sizeof(mobs_t));

	mobs->life = VIE_MOB;
	mobs->v_deplacement = V_DEP_MOB;
	mobs->gold = rand()%100;
	mobs->attaque = DEGAT_MOB;

	mobs->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs;
}

/*void vague(int multiple)
{
	mobs_t * mobs;

	while(compteur_mobs<NB_MOB)
	{
		creer_mobs;
		afficher_mobs(mobs);
		printf("\n%d \n",compteur_mobs);

	}
}*/