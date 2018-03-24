#include "mobs.h"
#include "../Towers/tours.h"

static int compteur_mobs = 0;

int mobs_existe(mobs_t * const mobs)
{
	return mobs != NULL;
}

void afficher_mobs(mobs_t * mobs)
{
	if(mobs_existe(mobs))
		printf("{mob <%d,%d> {%d PV}}\n",mobs->pos->courant->x, mobs->pos->courant->y, mobs->life);

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
		
		printf("mob <%d, %d> meurt \n", (*mobs)->pos->courant->x, (*mobs)->pos->courant->y);
		printf("GOLD +%d : %d\n", mob_g, GOLD);
		
		free(*mobs);
		*mobs = NULL;
	
		
		compteur_mobs --;
	}
	else
		printf("Le mob n'existe pas");

}


void perte_vie(mobs_t ** mobs, int nb_degat)
{
	if (mobs_existe(*mobs))
	{
		(*mobs)->life -= nb_degat;

		if ((*mobs)->life <= 0)
			(*mobs)->detruire(mobs);
	 }
}

mobs_t * creer_mobs_normal()
{
	mobs_t * mobs_normal = malloc(sizeof(mobs_t));
	
	mobs_normal->life = VIE_MOB;
	mobs_normal->v_deplacement = V_DEP_MOB *2;
	mobs_normal->attaque = DEGAT_MOB;
	mobs_normal->caract = 'N';
	
	mobs_normal->pos = NULL;

	mobs_normal->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_normal;
}

mobs_t * creer_mobs_tank()
{
	mobs_t * mobs_tank = malloc(sizeof(mobs_t));
	
	mobs_tank->life = VIE_MOB *3;
	mobs_tank->v_deplacement = V_DEP_MOB *4;
	mobs_tank->attaque = DEGAT_MOB *0,8;
	mobs_tank->caract = 'T';

	mobs_tank->pos = NULL;

	mobs_tank->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_tank;
}

mobs_t * creer_mobs_degat()
{
	
	mobs_t * mobs_degat = malloc(sizeof(mobs_t));
	
	mobs_degat->life = VIE_MOB *0,6;
	mobs_degat->v_deplacement = V_DEP_MOB;
	mobs_degat->attaque = DEGAT_MOB *2;
	mobs_degat->caract = 'D';

	mobs_degat->pos = NULL;

	mobs_degat->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_degat;
}

mobs_t * creer_mobs_boss()
{
	
	mobs_t * mobs_boss = malloc(sizeof(mobs_t));
	
	mobs_boss->life = VIE_MOB *4;
	mobs_boss->v_deplacement = V_DEP_MOB;
	mobs_boss->attaque = DEGAT_MOB *3;
	mobs_boss->caract = 'B';
	
	mobs_boss->pos = NULL;

	mobs_boss->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_boss;
}
void attaque_monum(mobs_t * mobs)
{
	monument_t * monum;
	liste_t * liste = mobs->pos;

/*	if(fin_liste(liste))
	{
		if(degats_monu(&monum, mobs->attaque) != -1);
	}*/
}

/*void creer_vague(char fichier)*/
/*{*/
/*	FILE * fic = fopen("fichier", "r");*/

/*	if(!fic)*/
/*	{*/
/*		printf("\tERREUR, ouverture du fichier de vague impossible !\n");*/
/*	}*/
/*	*/
/*	mobs_t * mobs;*/

/*	char mob;*/
/*	int nb_mobs;*/
/*	int creer = 0;*/

/*	while(!feof(fic))*/
/*	{*/
/*		fscanf(fic, "%c", mob);*/
/*		*/
/*		if(mobs != '\n')*/
/*		{*/
/*			fscanf(fic, "%d", nb_mobs);*/

/*			while(creer < nb_mobs)*/
/*			{*/
/*				switch(mob)*/
/*				{*/
/*					case 'N':*/
/*						mobs = creer_mobs_normal();*/
/*						break;*/
/*					*/
/*					case 'T':*/
/*						mobs = creer_mobs_tank();*/
/*						break;*/

/*					case 'D':*/
/*						mobs = creer_mobs_degat();*/
/*						break;*/

/*					case 'B':*/
/*						mobs = creer_mobs_boss();*/
/*						break;*/
/*			*/
/*					default:*/
/*						printf("Type du mobs inconnu");*/
/*						break;*/
/*				}*/

/*				creer ++;*/
/*			}*/
/*		*/
/*			creer = 0;*/
/*		}*/
/*	}*/
/*}*/
