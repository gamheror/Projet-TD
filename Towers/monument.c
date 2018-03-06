#include "../all.h"

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
monument_t * creer_monument(int x, int y)
{
	tour_t * temp = NULL;
	monument_t * monu = NULL;

	temp = creer_tour(x,y);
	if(temp == NULL)
		return NULL;
	
	monu = realloc(temp, sizeof(*monu));
	if( monu == NULL )
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création du monument !\n");
		return NULL;
	}
	
	
	monu->degat = DEGATS_MONU;

	monu->detruire = (int (*)(void **)) detruire_monument;
	monu->attaquer = (void (*)(void *, void *(*)[N])) tour_aoe_attaquer;
	monu->evoluer = (int (*)(void *)) evoluer_tour_aoe;
	monu->afficher = (void (*)(void *)) afficher_monument;
	
	//Fichier de sauvegarde
	FILE * fic = fopen("fichier_tours.txt", "a");
	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return NULL;
	}
	fprintf(fic, "MONUMENT\n");
	fprintf(fic, "x=%d y=%d\n", x, y);
	fprintf(fic, "niveau=1\n\n");
	fclose(fic);	
	
	return monu;
}


/*-------- Destruction --------*/
int detruire_monument(monument_t ** monu)
{
	if( !tour_existe( *monu ) )
		return OBJ_NULL;
	
	free(*monu);
	*monu = NULL;
	
	return OK;
}
