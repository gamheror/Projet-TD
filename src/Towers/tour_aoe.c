#include "tour.h"

/*-------- Sauvegarde --------*/

/**
  * \fn 	modif_save(int aoe_x, int aoe_y)
  * \brief 	Modifie la sauvegarde, le niveau de la tour est incrémenté,
  *		prend en param les coord du monument 
  *	
  * \param 	Les coordonnées x et y de la tour
  */

static
int modif_save(int aoe_x, int aoe_y)
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
		if(x == aoe_x && y == aoe_y)
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
 * \fn ajout_save(int x, int y)
 * \brief Ajoute dans le fichier de sauvegarde le type de tour, sa position
 * 	  et son niveau.
 *
 * \param Les coordonnées x et y de la tour
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
	
	fprintf(fic, "\nAOE %02d %02d 1", x, y);
	fclose(fic);
	
	return ERR_OK;
}


/*-------- Attaque --------*/

/**
 * \fn tour_aoe_attaquer(tour_aoe_t * aoe, mobs_t * mob[])
 * \brief Vérifie quels mobs du tableau sont à porté d'attaque de la tour
 *  	  et attaque ceux à porté.
 *
 * \param Un pointeur sur la tour AOE et un tableau de pointeur de mobs.
 */

static
int tour_aoe_attaquer(tour_aoe_t * aoe, mobs_t * mob[])
{
	int aoe_x = aoe->pos_x,
		aoe_y = aoe->pos_y,
		mob_x,
		mob_y,
		nb_tues = 0;
	
	for (int i = 0;i < N; i++)
		if(mob[i] != NULL)
		{
			mob_x = mob[i]->pos->x;
			mob_y = mob[i]->pos->y;
			if(A_PORTE(aoe_x, aoe_y, mob_x, mob_y, RAYON_TOUR))
			{
				printf("AOE <%02d,%02d> attaque en <%02d,%02d> -%d PV\n", aoe_x, aoe_y, mob_x, mob_y, aoe->degat);
				perte_vie(&mob[i], DEGATS_MONU);
			
				if( mob[i] == NULL )
				{
					printf("AOE  <%02d,%02d> a tuée <%02d,%02d>\n", aoe->pos_x, aoe->pos_y, mob_x, mob_y );
					nb_tues++;
				}
			}
		}
	return nb_tues; //retourne le nombre de mobs tués
}


/*-------- Évolution --------*/
/**
 * \fn evoluer_tour_aoe( tour_aoe_t * aoe )
 * \brief Fait appelle à la fonction evolution_tour et modifie son
 * 	    niveau dans la sauvegarde.
 *
 * \param Un pointeur sur la tour AOE.
 */

static
int evoluer_tour_aoe( tour_aoe_t * aoe )
{
	if( !tour_existe(aoe) )
		return ERR_OBJ_NULL;
	
	int rtn = evolution_tour( (void*)aoe );
	
	if(rtn == ERR_OK)
	{
		printf("AOE  <%02d,%02d> évolue au niveau %d, %d dégats\n",
			aoe->pos_x, aoe->pos_y, aoe->niveau, aoe->degat );
		
		if(modif_save(aoe->pos_x, aoe->pos_y) != ERR_OK)
			return ERR_OBJ_NULL;
	}
	
	return rtn;
}


/*-------- Creation --------*/

/**
  * \fn tour_aoe_t * new_aoe(int x, int y, int n)
  * \brief Cette fonction intialise la strucure tour_aoe_t et va permettre
  *	     d'effectuer la fonction creer_tour_aoe.
  *
  * \param variable x et y définissant la position
  * 	     variable n défini le niveau de la tour
  *
  * \return retourne le pointeur sur la structure tour_aoe_t ou retourne NULL si
  * 	      erreur.
  */

tour_aoe_t * new_aoe(int x, int y, int n)
{
	tour_t * temp = NULL;
	tour_aoe_t * aoe = NULL;

	temp = creer_tour(x, y, n);
	if(temp == NULL)
		return NULL;
	
	aoe = realloc(temp, sizeof(*aoe));
	if( aoe == NULL )
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création d'une tour d'AOE !\n");
		return NULL;
	}
	
	
	aoe->degat = DEGATS_TOUR_AOE * pow(MULT_DEGATS_TOUR, n-1);
	aoe->type = AOE;

	aoe->detruire = (int (*)( void ** )) detruire_tour_aoe;
	aoe->attaquer = (int (*)(void *, void *[])) tour_aoe_attaquer;
	aoe->evoluer = (int (*)(void *)) evoluer_tour_aoe;
/*	aoe->afficher = (void (*)(void *)) afficher_tour_aoe;*/
	
	return aoe;
}

/**
  * \fn 	tour_aoe_t * creer_tour_aoe (int x, int y)
  * \brief 	Cette fonction permet de creer et d'ajouter à la sauvegarde
  *		une tour de type aoe de niveau 1 
  *	  	en utilisant la fonction new_aoe si le nombre de gold est suffisant. 
  *	     	Elle va aussi modifier le nombre de GOLD que possède le joueur.
  *
  * \param 	variable x et y définissant la position
  *
  * \return retourne le pointeur sur la structure tour_aoe_t
  * 	      retourne NULL si GOLD insuffisant
  */

tour_aoe_t * creer_tour_aoe( int x, int y )
{
	if( GOLD < PRIX_TOUR )
	{
		printf("\tGOLD insuffisant pour poser une tour AOE !\n");
		return NULL;
	}
	
	tour_aoe_t * aoe = new_aoe(x, y, 1);
	if(aoe == NULL)
		return NULL;
	
	GOLD -= PRIX_TOUR;	
	
	//Fichier de sauvegarde
	if(ajout_save(x, y) != ERR_OK)
		return NULL;	
	
	return aoe;
}


/*-------- Destruction --------*/

/**
  * \fn detruire _tour_aoe(tour_aoe_t ** aoe)
  * \brief Cette fonction libère l'espace mémoire du pointeur sur la 
  *		structure tour_aoe_t
  *
  * \param double pointeur sur la structure tour_aoe_t
  *
  * \return retourne ERR_OK -> pas d'erreur
  */

int detruire_tour_aoe( tour_aoe_t ** aoe )
{
	if( !tour_existe( (*aoe) ) )
		return ERR_OBJ_NULL;
	
	free(*aoe);
	*aoe = NULL;
	
	return ERR_OK;
}
