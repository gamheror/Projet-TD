#include "tour.h"

/*-------- Sauvegarde --------*/

/**
 * \fn 	modif_save(int mono_x, int mono_y)
 * \brief 	Modifie la sauvegarde, le niveau de la tour est incrémenté,
 *		prend en param les coord du monument 
 *	
 * \param 	Les coordonnées x et y de la tour
 */
 
static
int modif_save(int mono_x, int mono_y)
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
		if(x == mono_x && y == mono_y)
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
	
	fprintf(fic, "\nMONO %02d %02d 1", x, y);
	fclose(fic);
	
	return ERR_OK;
}

/**
  * \fn 		recherche_ennemi(tour_mono_t * mono, mobs_t * mobs[])
  * \brief 	La tour recherche autour d'elle la presence d'un ennemi
  *			Recherche du plus pres au plus loin possible
  * 		Cible le premier ennemi le plus proche
  *
  * \param 	Pointeur sur la strucutre tour_mono_t, un tableau de pointeur de mobs sur la structure mobs_t
  *
  */
  
static
int rechercher_ennemi( tour_mono_t * mono, mobs_t * mob[] )
/* La tour recherche autour d'elle  */
{
	//Recupere les coordonnees de la tour
	int mono_x = mono->pos_x, mono_y = mono->pos_y, mob_x, mob_y;
	
	for(int r = 0; r <= RAYON_TOUR; r++)
		for (int i = 0; i < N; i++)
			if(mob[i] != NULL)
			{
				mob_x = mob[i]->pos->x;
				mob_y = mob[i]->pos->y;
				//verifie que la coordonnees soit dans les limites du tableau et que la case contient pointe sur un ennemi
				if(A_PORTE(mono_x, mono_y, mob_x, mob_y, r))
				{
					mono->cible = mob[i];
					mono->pos_mob = i;
					return 1;
				}
			}
	return 0;
}


/*-------- Attaque --------*/

/**
 * \fn tour_mono_attaquer(tour_mono_t * aoe, mobs_t * mob[])
 * \brief Vérifie quels mobs du tableau sont à porté d'attaque de la tour
 *  	  et attaque ceux à porté.
 *
 * \param Un pointeur sur la tour mono et un tableau de pointeur de mobs.
 */
 
static
int tour_mono_attaquer( tour_mono_t * mono, mobs_t * mob[] )
/* Fonction d'attaque d'une tour mono cible
	Recherche un ennemi si elle n'a pas en cible */
{
	int mob_x,
		mob_y,
		mono_y = mono->pos_y,
		mono_x = mono->pos_x,
		pos_mob = mono->pos_mob;
	
	if(pos_mob == -1 || mono->cible == NULL)//Si la tour ne possede pas de cible
		rechercher_ennemi( mono, mob );
	
	if(pos_mob > -1 && mob[pos_mob] != NULL) //si le mob est hors de porté  => recherche ennemi
	{
		mob_x = mob[pos_mob]->pos->x;
		mob_y = mob[pos_mob]->pos->y;
		if(A_PORTE(mono_x, mono_y, mob_x, mob_y, RAYON_TOUR))
			rechercher_ennemi(mono, mob);
	}
	
//=> Ne pas attaquer si la tour na trouve pas d'ennemi, que celui pointé est deja mort ou qu'il soit hors de porté
	if(pos_mob > -1 && mono->cible != NULL && mob[pos_mob] != NULL)
	{
		mob_x = mob[pos_mob]->pos->x;
		mob_y = mob[pos_mob]->pos->y;
		printf("MONO <%02d,%02d> attaque en <%d,%d> -%d PV\n", mono_x, mono_y, mob_x, mob_y, mono->degat );
		
		perte_vie( &mob[pos_mob], mono->degat );
		//verifier si ennemi mort, alors cible = NULL
		if( mob[pos_mob] == NULL )
		{
			mono->cible = NULL;
			mono->pos_mob = -1;
			printf("MONO <%02d,%02d> a tuée <%d,%d>\n", mono_x, mono_y, mob_x, mob_y );
			return 1; //la tour a tué un ennemi
		}
	}
	return 0; //la tour a tué 0 ennemi
}


/*-------- Évolution --------*/

/**
 * \fn evoluer_tour_mono( tour_mono_t * aoe )
 * \brief Fait appelle à la fonction evolution_tour et modifie son
 * 	    niveau dans la sauvegarde.
 *
 * \param Un pointeur sur la tour mono.
 */
 
static
int evoluer_tour_mono( tour_mono_t * mono )
{
	if( !tour_existe(mono) )
		return ERR_OBJ_NULL;
	
	int rtn = evolution_tour( (void*) mono );
	
	if(rtn == ERR_OK)
	{
		printf("MONO <%02d,%02d> évolue au niveau %d, %d dégats\n",
			mono->pos_x, mono->pos_y, mono->niveau, mono->degat );
		
		if(modif_save(mono->pos_x, mono->pos_y) != ERR_OK)
			return ERR_OBJ_NULL;
	}
		
	return rtn;
}


/*-------- Creation --------*/

/**
  * \fn tour_mono_t * new_mono(int x, int y, int n)
  * \brief Intialise la strucure tour_mono_t et va permettre
  *	     d'effectuer la fonction creer_tour_mono.
  *
  * \param Variable x et y définissant la position
  * 	     variable n défini le niveau de la tour
  *
  * \return Le pointeur sur la structure tour_mono_t ou retourne NULL si
  * 	      erreur.
  */
  
tour_mono_t * new_mono(int x, int y, int n)
{
	tour_t * temp = NULL;
	tour_mono_t * mono = NULL;
	
	temp = creer_tour(x, y, n); //Utilise la fonction de creation d'une tour simple
	if(temp == NULL)
		return NULL;
	
	mono = realloc(temp, sizeof(*mono)); //Realloc pour adapter la taille memoire allouee de tour vers tour_aoe
	if( mono == NULL ) //Vérifie que la reallocation a trouvé de la place
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création d'une tour MONO !\n");
		return NULL;
	}
		
	
	mono->degat = DEGATS_TOUR_MONO * pow(MULT_DEGATS_TOUR, n-1);
	mono->cible = NULL;
	mono->type = MONO;
	mono->pos_mob = -1;

	mono->detruire = (int (*)( void ** )) detruire_tour_mono;
	mono->attaquer = (int (*)(void *, void *[])) tour_mono_attaquer;
	mono->evoluer = (int (*)(void *)) evoluer_tour_mono;
	
	return mono;
}

/**
  * \fn 	tour_mono_t * creer_tour_mono (int x, int y)
  * \brief 	Cette fonction permet de creer et d'ajouter à la sauvegarde
  *		une tour de type mono de niveau 1 
  *	  	en utilisant la fonction new_aoe si le nombre de gold est suffisant. 
  *	     	Elle va aussi modifier le nombre de GOLD que possède le joueur.
  *
  * \param 	variable x et y définissant la position
  *
  * \return Retourne le pointeur sur la structure tour_mono_t
  * 	      retourne NULL si GOLD insuffisant
  */
  
tour_mono_t * creer_tour_mono( int x, int y )
{
	if(GOLD < PRIX_TOUR)
	{
		printf("\tGOLD insuffisant pour poser une tour MONO !\n");
		return NULL;
	}
	
	tour_mono_t * mono = new_mono(x, y, 1);
	if(mono == NULL)
		return NULL;
	
	GOLD -= PRIX_TOUR;
	
	//Fichier de sauvegarde
	if(ajout_save(x, y) != ERR_OK)
		return NULL;
	
	return mono;
}


/*-------- Destruction --------*/

/**
  * \fn detruire _tour_mono(tour_aoe_t ** mono)
  * \brief Cette fonction libère l'espace mémoire du pointeur sur la 
  *		structure tour_mono_t
  *
  * \param double pointeur sur la structure tour_mono_t
  *
  * \return retourne ERR_OK -> pas d'erreur
  */
  
int detruire_tour_mono( tour_mono_t ** mono )
{
	if( !tour_existe(*mono) )
		return ERR_OBJ_NULL;
	
	free(*mono);
	*mono = NULL;
	
	return ERR_OK;
}
