#include "tour.h"

/*-------- Sauvegarde --------*/
static
int modif_save(int mono_x, int mono_y)
/* Modifie la sauvegarde,
	le niveau du monument est incrémenté,
	prend en param les coord du monument */
{
	FILE * fic = fopen("fichier_tours.txt", "r+");
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

static
int ajout_save(int x, int y)
{
	FILE * fic = fopen("fichier_tours.txt", "a");

	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return ERR_OBJ_NULL;
	}
	
	fprintf(fic, "\nMONO %02d %02d 1", x, y);
	fclose(fic);
	
	return ERR_OK;
}


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
				if( LIMITES_MAP(x+i) && LIMITES_MAP(y+j) && mat[x+i][y+j] != NULL )
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
	
	if( mono->cible == NULL /*|| mat[mono->x_cible][mono->y_cible] == NULL*/ )//Si la tour ne possede pas de cible
		rech = rechercher_ennemi( mono, mat );
//Si la tour n'a pas trouve d'ennemi, rech = 0
//=> Ne pas attaquer si la tour na trouve pas d'ennemi
	
	if(rech == 1)
	{
		int x_c = mono->x_cible, y_c = mono->y_cible;

		printf("MONO <%02d,%02d> attaque en <%d,%d> -%d PV\n", 
			mono->pos_x, mono->pos_y, x_c, y_c, mono->degat );

		perte_vie( &mat[x_c][y_c], mono->degat );

		//verifier si ennemi mort, alors cible = NULL
		if( mat[x_c][y_c] == NULL )
		{
			mono->cible = NULL;
			printf("MONO <%02d,%02d> a tuée <%d,%d>\n",
				mono->pos_x, mono->pos_y, x_c, y_c );
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
	{
		printf("MONO <%02d,%02d> évolue au niveau %d, %d dégats\n",
			mono->pos_x, mono->pos_y, mono->niveau, mono->degat );
		
		if(modif_save(mono->pos_x, mono->pos_y) != ERR_OK)
			return ERR_OBJ_NULL;
	}
		
	return rtn;
}

/*static*/
/*void afficher_tour_mono( tour_mono_t * mono )*/
/*{*/
/*	if( tour_existe(mono) )*/
/*		printf("M");*/
/*	else*/
/*		printf("{NULL}");*/
/*}*/


/*-------- Creation --------*/
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

	mono->detruire = (int (*)( void ** )) detruire_tour_mono;
	mono->attaquer = (void (*)(void *, void *(*)[N])) tour_mono_attaquer;
	mono->evoluer = (int (*)(void *)) evoluer_tour_mono;
/*	mono->afficher = (void (*)(void *)) afficher_tour_mono;*/
	
	return mono;
}

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
int detruire_tour_mono( tour_mono_t ** mono )
{
	if( !tour_existe(*mono) )
		return ERR_OBJ_NULL;
	
	free(*mono);
	*mono = NULL;
	
	return ERR_OK;
}
