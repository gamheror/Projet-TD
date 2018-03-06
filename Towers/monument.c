#include "../all.h"

static int nb_monument = 0;

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
monument_t * new_monument(int x, int y)
{
	if(nb_monument >= 1)
	{
		printf("\tERREUR, un monument est deja construit, impossible d'en créer un nouveau !\n");
		return NULL;
	}
	
	monument_t * monu = (monument_t *) new_aoe(x, y);
	if( monu == NULL )
		return NULL;
	
	monu->degat = DEGATS_MONU;

	monu->detruire = (int (*)(void **)) detruire_monument;
	monu->afficher = (void (*)(void *)) afficher_monument;
	
	nb_monument++;
	
	return monu;
}

monument_t * creer_monument(int x, int y)
{
	monument_t * monu = new_monument(x, y);
	if(monu == NULL)
		return NULL;
	
	//Fichier de sauvegarde
	FILE * fic = fopen("fichier_tours.txt", "a");
	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return NULL;
	}
	fprintf(fic, "MONUMENT %d %d 1", x, y);
	fclose(fic);	
	
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
