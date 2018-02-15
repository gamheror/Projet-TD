#include <stdio.h>
#include "../all.h"

static
void tour_aoe_attaquer(tour_aoe_t * aoe, mobs_t * mat[][N])
{
	int x = aoe->pos_x, y = aoe->pos_y;
	
	for(int i = -RAYON_TOUR; i <= RAYON_TOUR; i++)
		for(int j = -RAYON_TOUR; j <= RAYON_TOUR; j++)
			if( 0 <= (x+i) < N && 0 <= (y+j) < N && mat[x+i][y+j] != NULL )
			{
				perte_vie( &mat[x+i][y+j], aoe->degat );
				printf("AOE <%d,%d> attaque en <%d,%d> -%d PV\n",
					x, y,
					x+i, y+j,
					aoe->degat );
				
				if( mat[x+i][y+j] == NULL )
					printf("AOE <%d,%d> a tuée <%d,%d>\n", x, y, x+i, y+j );
			}
}

tour_aoe_t * creer_tour_aoe( int x, int y )
{
	tour_t * temp = NULL;
	tour_aoe_t * aoe = NULL;

	if( gold >= PRIX_TOUR )
	{
		temp = creer_tour(x,y);
		aoe = realloc(temp, sizeof(tour_aoe_t));
		
		if( aoe == NULL )
			printf("Erreur creation d'une tour aoe\n");
		else
		{
			aoe->degat = DEGATS_TOUR_AOE;
	
			aoe->detruire = (void (*)( void ** )) detruire_tour_aoe;
			aoe->attaquer = (void (*)(void *, void *(*)[N])) tour_aoe_attaquer;
			aoe->evoluer = (void (*)(void *)) evoluer_tour_aoe;
			
			gold -= PRIX_TOUR;
			
			printf("AOE posée en <%d,%d>\n", x, y);
			printf("gold -%d : %d\n", PRIX_TOUR, gold);
		}
	}
	
	return aoe;
}

void afficher_tour_aoe( tour_aoe_t * aoe )
{
	if( tour_existe(aoe) )
	{
		printf("{AOE ");
		afficher_tour( (tour_t*)aoe );
		printf(" }");
	}
	else
		printf("{NULL}");
}

void evoluer_tour_aoe( tour_aoe_t * aoe )
{
	if( tour_existe(aoe) )
	{
		evoluer_tour( (void*)aoe );
		printf("AOE <%d,%d> évolue au niveau %d, %d degats\n",
			aoe->pos_x, aoe->pos_y,
			aoe->niveau,
			aoe->degat );
		printf("gold -%d : %d\n", MULT_PRIX_TOUR*(aoe->niveau-1), gold);
	}
}

void detruire_tour_aoe( tour_aoe_t ** aoe )
{
	if( tour_existe( (*aoe) ) )
	{
		free(*aoe);
		*aoe = NULL;
	}
}
