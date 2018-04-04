#include "tour.h"

static int nb_monument = 0;

static monument_t * monument = NULL;


/*-------- Sauvegarde --------*/

/**
 * \fn 	modif_save(int monu_x, int monu_y)
 * \brief 	Modifie la sauvegarde, le niveau de la tour est incrémenté,
 *	    	prend en param les coord du monument 
 *	
 * \param 	Les coordonnées x et y de la tour
 */

static
int modif_save(int monu_x, int monu_y)
{
	FILE * fic = fopen("ressources/fichier_tours.txt", "r+");
	if(fic == NULL)
		return ERR_OBJ_NULL;
	
	char type[9];
	int x, y, n;
	int trouve = 0;
	//Cherche la tour, elle est identifiée par ses coordonnées
	while( !trouve && !feof(fic) )
	{
		fscanf(fic, "%s %d %d %d", type, &x, &y, &n);
		if(x == monu_x && y == monu_y)
			trouve = 1;
	}
	//elle a été trouvée
	if(trouve == 1)
	{
		fseek(fic, -1, SEEK_CUR); //Place la tete de lecture sur le caractere niveau
		fprintf(fic, "%d", n+1); //Incremente le niveau
	}
	fclose(fic);
	
	return ERR_OK;
}

/**
 * \fn 	ajout_save(int x, int y)
 * \brief 	Ajoute dans le fichier de sauvegarde le monument, sa position
 * 	  	et son niveau.
 *
 * \param	Les coordonnées x et y du monument
 */

static
int ajout_save(int x, int y)
{
	FILE * fic = fopen("ressources/fichier_tours.txt", "a");
	
	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return ERR_OBJ_NULL;
	}
	fprintf(fic, "MONUMENT %02d %02d 1", x, y);
	fclose(fic);
	
	return ERR_OK;
}


/*-------- Attaque --------*/

/**
 * \fn 	monument_attaquer(tour_aoe_t * monu, mobs_t * mob[])
 * \brief 	Vérifie quels mobs du tableau sont à porté d'attaque du monument
 *  	  	et attaque ceux à porté. Le monument attque comme une tour de type
 *		aoe
 *
 * \param 	Un pointeur sur la tour AOE et un tableau de pointeur de mobs.
 */

static
int monument_attaquer(tour_aoe_t * monu, mobs_t * mob[N])
{
	int monu_x = monu->pos_x,
		monu_y = monu->pos_y,
		mob_x,
		mob_y,
		nb_tues = 0;
	
	for (int i = 0; i < N; i++)
		if(mob[i] != NULL)
		{
			mob_x = mob[i]->pos->x;
			mob_y = mob[i]->pos->y;
			if(A_PORTE(monu_x, monu_y, mob_x, mob_y, RAYON_TOUR))
			{
				printf("MONU <%02d,%02d> attaque en <%02d,%02d> -%d PV\n", monu_x, monu_y, mob_x, mob_y, monu->degat);
				perte_vie(&mob[i], DEGATS_MONU);
			
				if( mob[i] == NULL )
				{
					printf("MONU <%02d,%02d> a tuée <%02d,%02d>\n", monu->pos_x, monu->pos_y, mob_x, mob_y );
					nb_tues++;
				}
			}
		}
	return nb_tues; //retourne le nombre d'ennemis qu'a tué la tour
}


/*-------- Évolution --------*/

/**
 * \fn 	evoluer_tour_aoe( monument_t * monument )
 * \brief 	Fait appelle à la fonction evolution_tour et modifie son
 * 	    	niveau dans la sauvegarde.
 *
 * \param 	Un pointeur sur la structure monument_t
 */

static
int evoluer_monument( monument_t * monu )
{
	if( !tour_existe(monu) )
		return ERR_OBJ_NULL;
	
	int rtn = evolution_tour( (void*)monu ); //fait evoluer le monument
	
	//si tout s'est bien passé
	if(rtn == ERR_OK)
	{
		printf("MONUMENT évolue au niveau %d, %d dégats\n", monu->niveau, monu->degat );
		
		//change le niveau du monument dans la sauvegarde
		if(modif_save(monu->pos_x, monu->pos_y) != ERR_OK)
			return ERR_OBJ_NULL;
	}
	
	return rtn;
}


/*-------- Creation --------*/

/**
  * \fn 	monument_t * new_monument(int x, int y, int n)
  * \brief 	Cette fonction intialise la strucure monument_t et va permettre
  *	     	d'effectuer la fonction creer_monument.
  *
  * \param 	variable x et y définissant la position
  * 	     	variable n défini le niveau du monument
  *
  * \return retourne le pointeur sur la structure tour_aoe_t ou retourne NULL si
  * 	      erreur.
  */

monument_t * new_monument(int x, int y, int n)
{
	if(nb_monument >= 1)
	{
		printf("\tERREUR, un monument est deja construit, impossible d'en créer un nouveau !\n");
		return NULL;
	}
	
	monument_t * monu = (monument_t *) new_aoe(x, y, n);
	if( monu == NULL )
		return NULL;
	monu = realloc(monu, sizeof(*monu));
	
	monu->degat = DEGATS_MONU * pow(MULT_DEGATS_TOUR, n-1);
	monu->pv = PV_MONU;
	monu->type = MONU;

	monu->detruire = (int (*)(void **)) detruire_monument;
	monu->evoluer = (int (*)(void *)) evoluer_monument;
	monu->attaquer = (int (*)(void *, void *[])) monument_attaquer;
	
	monument = monu;
	
	nb_monument++;
	
	return monu;
}

/**
  * \fn	monument_t * creer_monument (int x, int y)
  * \brief 	Cette fonction permet de creer un monument au début du jeu de niveau 1 
  *	    	en utilisant la fonction new_monument. 
  *
  * \param variable x et y définissant la position
  *
  * \return retourne le pointeur sur la structure monument_t
  */

monument_t * creer_monument(int x, int y)
{
	monument_t * monu = new_monument(x, y, 1);
	if(monu == NULL)
		return NULL;
	
	//Fichier de sauvegarde
	if(ajout_save(x, y) != ERR_OK)
		return NULL;
	
	return monu;
}


monument_t * get_monu()
{
	return monument;
}

/**
  * \fn 	degats_monu(int qtt)
  * \brief 	Fonction qui va modifier les PV du monuments.
  *		Cette fonction est utilisée par la fonction attaque_monum
  *		du fichier mobs.c
  *
  * \param 	variable qtt qui va prendre comme valeur le nombre de dégat infligé
  *		au monument par le(s) mob(s)
  *
  * \return 1 si le monument est détruit, c-à-d qu'il n'a plus de pv ou 0 si ses
  *		PV sont suppérieur à 0.
  */

int degats_monu(int qtt)
{
	monument_t * monu = get_monu();
	if(tour_existe(monu))
	{
		monu->pv -= qtt;
		printf("Monument rencoie %d degats %d pv\n", qtt, monu->pv);
	}
	else
		return 1;
	return 0;
}

/**
  * \fn	monum_est_detruit()
  * \brief	Cette fonction permet de savoir si le monument est détruit ou non
  *
  * \return	1 si les pv du monoment sont inférieurs ou égaux à 0 ou s'il n'existe pas.
  * 		Sinon retourne 0. 
  */

int monu_est_detruit()
{
	monument_t * monu = get_monu();
	if(tour_existe(monu) && monu->pv <= 0)
		return 1;
	return 0;
}


/*-------- Destruction --------*/

/**
  * \fn 	detruire_monument(monument_t ** monu)
  * \brief 	Cette fonction libère l'espace mémoire du pointeur sur la 
  *		structure tour_aoe_t
  *
  * \param 	double pointeur sur la structure monument_t
  *
  * \return retourne ERR_OK -> pas d'erreur
  */

int detruire_monument(monument_t ** monu)
{
	if( !tour_existe( *monu ) )
		return ERR_OBJ_NULL;
	
	free(*monu);
	*monu = NULL;
	
	monument = NULL;
	
	nb_monument--;
	
	return ERR_OK;
}
