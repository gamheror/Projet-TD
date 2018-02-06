typedef struct mobs_s
{
	int life;
	int gold;
	int v_deplacement;
	char caract;

	//trouver comment insérer la structure attaque;
	//void (*perte_vie)(struct mobs_t *);
	
}mobs_t;

mobs_t * mobs_creer();
void afficher_mobs(mobs_t * );
void detruire_mobs(mobs_t **);