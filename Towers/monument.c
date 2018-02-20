#include "../all.h"

static void afficher_monument(monument_t * monu)
{
	if( tour_existe(monu) )
	{
		printf("{MONU  <%d,%d> ", monu->pos_x, monu->pos_y);
		afficher_tour( (tour_t*)monu );
		printf(" }");
	}
	else
		printf("{NULL}");
}

monument_t * creer_monument(int x, int y)
{
	monument_t * monu = (monument_t*)creer_tour_aoe(x, y);
	
	if( !monu )
		printf("Erreur a la creation du monument !\n");
	else
	{
		monu->afficher = (void (*)(void *)) afficher_monument;
		
		monu->degat = DEGATS_MONU;
	}
}

void detruire_monument(monument_t ** monu)
{
	if( tour_existe( *monu ) )
	{
		detruire_tour((tour_t**)monu);
	}
}
