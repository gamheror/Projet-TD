#include "../all.h"

/*-------- Creation --------*/
tour_t * creer_tour( int x, int y, int n )
{
	tour_t * tour = NULL;
	
	tour = malloc(sizeof(*tour));

	if( tour == NULL )
		printf("\tERREUR, espace mémoire insuffisant pour la création d'une tour !\n");
	else
	{
		tour->niveau = n;
		tour->rayon = RAYON_TOUR;
		tour->cooldown = COOLDOWN_TOUR;
		tour->pos_x = x;
		tour->pos_y = y;
	}
	
	return tour;
}


/*-------- Fonction booléenne --------*/
int tour_existe( void * tour )
{
	return tour != NULL ;
}


/*-------- Modifications --------*/
int evolution_tour( tour_t * tour )
/* Fonction d'évolution d'une tour de base
	cout_évolution = niveau_tour * 100 */
{
	if( !tour_existe(tour) )
		return ERR_OBJ_NULL;
	
	int n = tour->niveau;
	
	if(GOLD < 100*n)
		return ERR_GOLD;
	if(n >= NIVEAU_MAX_TOUR)
		return ERR_NIVEAU_MAX;
	
	GOLD -= 100*n;
		
	tour->niveau++;
	tour->degat *= MULT_DEGATS_TOUR;
	
	return ERR_OK;
}


/*-------- Destruction --------*/
int detruire_tour( tour_t ** tour )
{
	if( !tour_existe(*tour) )
		return ERR_OBJ_NULL;
	
	free(*tour);
	*tour = NULL;
	
	return ERR_OK;
}
