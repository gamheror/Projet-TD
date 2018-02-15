#include "../all.h"


static int compteur_mobs = 0;

int mobs_existe(mobs_t * const mobs)
{
	return mobs != NULL;
}

void afficher_mobs(mobs_t * mobs)
{
	if(mobs_existe(mobs))
		printf("{mob <%d,%d> {%d PV}}\n",mobs->pos_x, mobs->pos_y, mobs->life);

	else
	{
		printf("{mob NULL}\n");
	}

}

void detruire_mobs(mobs_t ** mobs)
{
	if (mobs_existe(*mobs))
	{
		int mob_g = rand()%DROP_MOB_MAX+DROP_MOB_MIN;
		gold += mob_g;
		
		printf("mob <%d, %d> meurt \n", (*mobs)->pos_x, (*mobs)->pos_y);
		printf("gold +%d : %d\n", mob_g, gold);
		
		free(*mobs);
		*mobs = NULL;
	
		
		compteur_mobs --;
	}

}


void perte_vie (mobs_t ** mobs, int nb_degat)
{
	if (mobs_existe(*mobs))
	{
		(*mobs)->life -= nb_degat;

		if ((*mobs)->life <= 0)
			(*mobs)->detruire(mobs);
	 }
}


mobs_t * creer_mobs(int x, int y)
{
	mobs_t * mobs = malloc(sizeof(mobs_t));

	mobs->life = VIE_MOB;
	mobs->v_deplacement = V_DEP_MOB;
	mobs->attaque = DEGAT_MOB;
	
	mobs->pos_x = x;
	mobs->pos_y = y;

	mobs->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs;
}

/*void degats_mobs(mobs_t * mobs, int monument)
{
	
}
*/

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
