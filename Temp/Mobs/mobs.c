#include "../all.h"

static int compteur_mobs = 0;

int mobs_existe(mobs_t * const mobs)
{
	return mobs != NULL;
}

void afficher_mobs(mobs_t * mobs)
{
	if(mobs_existe(mobs))
		printf("{mob <%d,%d> {%d PV}}\n",mobs->pos->x, mobs->pos->y, mobs->life);

	else
	{
		printf("{mob NULL}\n");
	}

}

void detruire_mobs(mobs_t ** mobs)
{
	if (mobs_existe(*mobs))
	{
		int mob_g = rand()%( DROP_MOB_MAX -DROP_MOB_MIN +1 ) +DROP_MOB_MIN;
		GOLD += mob_g;
		
		printf("mob <%d, %d> meurt \n", (*mobs)->pos->x, (*mobs)->pos->y);
		printf("GOLD +%d : %d\n", mob_g, GOLD);
		
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


mobs_t * creer_mobs(elem_t * elem)
{

	mobs_t * mobs = malloc(sizeof(mobs_t));
	

	mobs->life = VIE_MOB;
	mobs->v_deplacement = V_DEP_MOB;
	mobs->attaque = DEGAT_MOB;

	mobs->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs;
}

/*void attaque_monum(mobs_t * mobs, monument_t * monum)
{
	liste_t * liste;
	life = monum->life;
	atk = mobs->attaque;

	if(fin_liste(liste))
	{
		while(mobs_existe(mobs) && tou)
		{
			life -= atk;
		}
	}
}*/

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
