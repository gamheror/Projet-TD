#ifndef _MOB_H_
#define _MOB_H_

typedef struct mobs_s
{
	int attaque;
	int life;
	int gold;
	int v_deplacement;
	char caract;

	//trouver comment insérer la structure attaque;
	//void (*perte_vie)(struct mobs_t *);
	void (*detruire)(struct mobs_s **);
	
}mobs_t;


/* Creation d'un objet mobs_t */
mobs_t * creer_mobs();

/* Affiche la vie et les gold portes par le mob */
void afficher_mobs(mobs_t * );

/* Assaine des degats au mob, si vie <= 0, il est detruit */
void perte_vie (mobs_t ** , int);

/* Libere l'espace memoire alloue a un mob */
void detruire_mobs(mobs_t **);

/* création de mobs pour une vague*/
/*void vague(int);*/

#endif
