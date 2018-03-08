#include "../all.h"

static int nb_monument = 0;


/*-------- Sauvegarde --------*/
static
int modif_save(int monu_x, int monu_y)
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

static
int ajout_save(int x, int y)
{
	FILE * fic = fopen("fichier_tours.txt", "a");
	
	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return ERR_OBJ_NULL;
	}
	fprintf(fic, "MONUMENT %02d %02d 1", x, y);
	fclose(fic);
	
	return ERR_OK;
}


/*-------- Évolution --------*/
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


static
void afficher_monument(monument_t * monu)
/* Affichage du monument */
{
	if( tour_existe(monu) )
		printf("B");
	else
		printf("{NULL}");
}


/*-------- Creation --------*/
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
	
	monu->degat = DEGATS_MONU * pow(MULT_DEGATS_TOUR, n-1);

	monu->detruire = (int (*)(void **)) detruire_monument;
	monu->evoluer = (int (*)(void *)) evoluer_monument;
	monu->afficher = (void (*)(void *)) afficher_monument;
	
	nb_monument++;
	
	return monu;
}

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


/*-------- Destruction --------*/
int detruire_monument(monument_t ** monu)
{
	if( !tour_existe( *monu ) )
		return ERR_OBJ_NULL;
	
	free(*monu);
	*monu = NULL;
	
	nb_monument--;
	
	return ERR_OK;
}
