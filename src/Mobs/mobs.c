#include "mobs.h"
#include "../Towers/tours.h"

static int compteur_mobs = 0;

/**
 * \fn mobs_existe(mobs_t * const mobs)
 * \brief Fonction qui vérifie que le mobs en paramètre existe
 *
 * \param pointeur sur la structure mobs_t
 * \return 0 si mobs différent de NULL
 */

int mobs_existe(mobs_t * const mobs)
{
	return mobs != NULL;
}

/**
 * \fn afficher_mobs(mobs_t * const mobs)
 * \brief Fonction qui affiche le mobs en paramètre.
 *
 * \param pointeur sur la structure mobs_t
 */

void afficher_mobs(mobs_t * mobs)
{
	if(mobs_existe(mobs))
		printf("{mob <%d,%d> {%d PV}}\n",mobs->pos->x, mobs->pos->y, mobs->life);

	else
	{
		printf("{mob NULL}\n");
	}

}

/**
 * \fn detruire(mobs_t ** mobs)
 * \brief Fonction qui détruie le mobs en paramètre en libérent l'espace
 * 	    et en mettant le pointeur à NULL
 *
 * \param double pointeur sur la structure mobs_t
 */

void detruire_mobs(mobs_t ** mobs)
{
	if (mobs_existe(*mobs))
	{
		int mob_g = rand()%( DROP_MOB_MAX -DROP_MOB_MIN +1 ) +DROP_MOB_MIN;
		GOLD += mob_g;
		
		printf("GOLD +%d : %d\n", mob_g, GOLD);
		
		free(*mobs);
		*mobs = NULL;
	
		
		compteur_mobs --;
	}

}

/**
 * \fn perte_vie(mobs_t ** mobs, int nb_degat
 * \brief Fonction qui va modifier la variable "life" de la structure mobs_t
 *	    en fonction de la valeur de la variavle nb_degat et va utiliser la
 *	    fonction detruire_mobs lorsque "life" est inférieur à 0. 
 *        Cette fonction est utilisée par les fonctions des tours.
 *
 * \param double pointeur sur la structure mobs_t et une variable nb_degat
 */

void perte_vie(mobs_t ** mobs, int nb_degat)
{
	if (mobs_existe(*mobs))
	{
		(*mobs)->life -= nb_degat;

		if ((*mobs)->life <= 0)
			(*mobs)->detruire(mobs);
	 }
}

/**
 * \fn get_mob_pos(mobs_t * mob, int * x, int * y)
 * \brief Fonction qui permet d'avoir la position des mobs
 * 	    en x et en y.
 *
 * \param pointeur sur la sructure mob, sur une variable x et une variable y.
 */

void get_mob_pos(mobs_t * mob, int * x, int * y)
{
	if(mobs_existe(mob))
	{
		*x = mob->pos->x;
		*y = mob->pos->y;
	}
}

/**
 * \fn mobs_t * creer_mobs_normal()
 * \brief Fonction va creer un mobs de type normal en initialisant les variables
 *	    de la structure mobs_t avec des valeurs étant propre au type "normal"
 *	    contenu dans le fichier all.h.
 *	    Les autres fonctions creer_mobs sont identique à celle-ci mais avec des 
 *	    valeurs différentes.
 *
 * \return le pointeur sur la strunsture mobs_t
 */

mobs_t * creer_mobs_normal()
{
	mobs_t * mobs_normal = malloc(sizeof(mobs_t));
	
	mobs_normal->life = VIE_NORM;
	mobs_normal->v_deplacement = V_DEP_NORM;
	mobs_normal->attaque = DEGAT_NORM;
	mobs_normal->caract = 'N';
	
	//liste_debut(liste);
	mobs_normal->pos = NULL;

	mobs_normal->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_normal;
}

mobs_t * creer_mobs_tank()
{
	mobs_t * mobs_tank = malloc(sizeof(mobs_t));
	
	mobs_tank->life = VIE_TANK;
	mobs_tank->v_deplacement = V_DEP_TANK;
	mobs_tank->attaque = DEGAT_TANK;
	mobs_tank->caract = 'T';

	mobs_tank->pos = NULL;

	mobs_tank->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_tank;
}

mobs_t * creer_mobs_degat()
{
	
	mobs_t * mobs_degat = malloc(sizeof(mobs_t));
	
	mobs_degat->life = VIE_DEGAT;
	mobs_degat->v_deplacement = V_DEP_DEGAT;
	mobs_degat->attaque = DEGAT_DEGAT;
	mobs_degat->caract = 'D';

	mobs_degat->pos = NULL;

	mobs_degat->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_degat;
}

mobs_t * creer_mobs_boss()
{
	
	mobs_t * mobs_boss = malloc(sizeof(mobs_t));
	
	mobs_boss->life = VIE_BOSS;
	mobs_boss->v_deplacement = V_DEP_BOSS;
	mobs_boss->attaque = DEGAT_BOSS;
	mobs_boss->caract = 'B';
	
	mobs_boss->pos = NULL;

	mobs_boss->detruire = detruire_mobs;
	
	compteur_mobs ++;

	return mobs_boss;
}

/**
 * \fn attaque_monum(mobs_t * const mobs)
 * \brief Fonction qui modifie la vie du monument en 
 *	    en faisant appaelle à la fonction degats_monu 
 *	    du fichier monument.c.
 *
 * \param pointeur sur la structure mobs_t
 */

void attaque_monum(mobs_t * mobs)
{
	if(mobs != NULL)
	{
		degats_monu(mobs->attaque);
	}
}

/**
 * \fn deplacer_mob(mob_t * mob[], int temps)
 * \brief 
 *
 * \param 
 */ 

void deplacer_mob(mobs_t * mob[], int temps)
{
	for(int i =0; i < N; i++)
	{
		if(mob[i] != NULL && temps%(150*mob[i]->v_deplacement) == 0)
		{
			if(mob[i]->pos->suivant == NULL) //fin de la liste
				attaque_monum(mob[i]);
			else
				mob[i]->pos = mob[i]->pos->suivant;
		}
		
	}
}

/**
 * \fn apparaitre(mobs_t * mobs[], liste_t * chemin, int temps, int * nb_arrives)
 * \brief Fonction qui va permettre de faire apparaître les différents type de mobs
 *   	    en utilisant l'aléatoire pour ne pas avoir un schéma prédéfini. Les mobs
 *	    apparaissent à l'aide d'un timer représenté par le varible temps.
 *
 * \param tableau représentant les mobs pointant sur la structure mobs_t,
 *	    un pointeur sur la structure liste_t,
 * 	    une variable temps
 *	    une variable nb_arrives pointant sur un int
 */

void apparaitre(mobs_t * mob[], liste_t * chemin, int temps, int * nb_arrives, int num_vague)
{
	if(chemin != NULL)
	{
		int i = 0;
		while(mob[i] != NULL && i < N)
			i++;
		if(mob[i] == NULL && temps%(501-50*(num_vague-1)) == 0) //1 mob apparait toute les 1m30 a la vague 1
		{
			int random = rand()%100;
			if (random < POURCENT_NORM)
				mob[i] = creer_mobs_normal();
			else if (random < POURCENT_NORM+POURCENT_DEGA)
				mob[i] = creer_mobs_degat();
			else if (random < 100-POURCENT_BOSS)
				mob[i] = creer_mobs_tank();
			else
				mob[i] = creer_mobs_boss();
			mob[i]->pos = chemin->premier;
			(*nb_arrives)++;
		}
	}
}
