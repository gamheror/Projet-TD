#include "../all.h"

static
int rechercher_ennemi( tour_mono_t * mono, mobs_t * mat[][N] )
/* La tour recherche autour d'elle la presence d'un ennemi
	Recherche du plus pres au plus loin possible
	Cible le premier ennemi le plus proche */
{
	//Recupere les coordonnees de la tour
	int x = mono->pos_x, y = mono->pos_y;
	
	//Rayon croissant
	for(int r = 1; r <= RAYON_TOUR; r++)
		//Parcours les cases autour de (x,y) à r cases de rayon
		for(int i = -r; i <= r; i++)
			for(int j = -r; j <= r; j++)
			{
				//verifie que la coordonnees soit dans les limites du tableau et que la case contient pointe sur un ennemi
				if( 0 <= (x+i) < N && 0 <= (y+j) < N && mat[x+i][y+j] != NULL )
				{
					mono->cible = mat[x+i][y+j];
					mono->x_cible = x+i;
					mono->y_cible = y+j;
					return 1;
				}
			}
	return 0;
}


/*-------- Attaque --------*/
static
void tour_mono_attaquer( tour_mono_t * mono, mobs_t * mat[][N] )
/* Fonction d'attaque d'une tour mono cible
	Recherche un ennemi si elle n'a pas en cible */
{
	int rech = 1;
	
	if( mono->cible == NULL || mat[mono->x_cible][mono->y_cible] == NULL )//Si la tour ne possede pas de cible ou qu'elle pointe sur une case NULL
		rech = rechercher_ennemi( mono, mat );
//Si la tour n'a pas trouve d'ennemi, rech = 0
//=> Ne pas attaquer si la tour na trouve pas d'ennemi
	
	if(rech == 1)
	{
		int x_c = mono->x_cible, y_c = mono->y_cible;

		mono->afficher(mono);
		printf(" attaque en <%d,%d> -%d PV\n", x_c, y_c, mono->degat );

		perte_vie( &mat[x_c][y_c], mono->degat );

		//verifier si ennemi mort, alors cible = NULL
		if( mat[x_c][y_c] == NULL )
		{
			mono->cible = NULL;
			mono->afficher(mono);
			printf(" a tuée <%d,%d>\n", x_c, y_c );
		}
	}
}


/*-------- Évolution --------*/
static
int evoluer_tour_mono( tour_mono_t * mono )
{
	if( !tour_existe(mono) )
		return ERR_OBJ_NULL;
	
	int rtn = evolution_tour( (void*) mono );
	
	if(rtn == ERR_OK)
		printf("MONO <%02d,%02d> évolue au niveau %d, %d dégats\n",
			mono->pos_x, mono->pos_y, mono->niveau, mono->degat );
		
	return rtn;
}

static
void afficher_tour_mono( tour_mono_t * mono )
{
	if( tour_existe(mono) )
		printf("M");
	else
		printf("{NULL}");
}


/*-------- Creation --------*/
tour_mono_t * new_mono(int x, int y)
{
	tour_t * temp = NULL;
	tour_mono_t * mono = NULL;
	
	temp = creer_tour(x,y); //Utilise la fonction de creation d'une tour simple
	if(temp == NULL)
		return NULL;
	
	mono = realloc(temp, sizeof(*mono)); //Realloc pour adapter la taille memoire allouee de tour vers tour_aoe
	if( mono == NULL ) //Vérifie que la reallocation a trouvé de la place
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création d'une tour MONO !\n");
		return NULL;
	}
		
	
	mono->degat = DEGATS_TOUR_MONO;
	mono->cible = NULL;

	mono->detruire = (int (*)( void ** )) detruire_tour_mono;
	mono->attaquer = (void (*)(void *, void *(*)[N])) tour_mono_attaquer;
	mono->evoluer = (int (*)(void *)) evoluer_tour_mono;
	mono->afficher = (void (*)(void *)) afficher_tour_mono;
	
	return mono;
}

tour_mono_t * creer_tour_mono( int x, int y )
{
	if(GOLD < PRIX_TOUR)
	{
		printf("\tGOLD insuffisant pour poser une tour MONO !\n");
		return NULL;
	}
	
	tour_mono_t * mono = new_mono(x, y);
	if(mono == NULL)
		return NULL;
	
	GOLD -= PRIX_TOUR;
	
	//Fichier de sauvegarde
	FILE * fic = fopen("fichier_tours.txt", "a");
	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return NULL;
	}
	fprintf(fic, "\nMONO %d %d 1", x, y);
	fclose(fic);
	
	return mono;
}


/*-------- Destruction --------*/
int detruire_tour_mono( tour_mono_t ** mono )
{
	if( !tour_existe(*mono) )
		return ERR_OBJ_NULL;
	
	free(*mono);
	*mono = NULL;
	
	return ERR_OK;
}
