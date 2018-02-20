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
				aoe->afficher(aoe);
				printf(" attaque en <%d,%d> -%d PV\n", x+i, y+j, aoe->degat );
					
				perte_vie( &mat[x+i][y+j], aoe->degat );
				
				if( mat[x+i][y+j] == NULL )
				{
					aoe->afficher(aoe);
					printf(" a tuée <%d,%d>\n", x+i, y+j );
				}
			}
}

static void afficher_tour_aoe( tour_aoe_t * aoe )
{
	if( tour_existe(aoe) )
	{
		printf("{AOE  <%d,%d> ", aoe->pos_x, aoe->pos_y);
		afficher_tour( (tour_t*)aoe );
		printf(" }");
	}
	else
		printf("{NULL}");
}

tour_aoe_t * creer_tour_aoe( int x, int y )
{
	tour_t * temp = NULL;
	tour_aoe_t * aoe = NULL;

	if( GOLD >= PRIX_TOUR )
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
			aoe->afficher = (void (*)(void *)) afficher_tour_aoe;
			
			GOLD -= PRIX_TOUR;
			
			aoe->afficher(aoe);
			printf(" posée en <%d,%d>\n", x, y);
			printf("GOLD -%d : %d\n", PRIX_TOUR, GOLD);
		}
	}
	
	return aoe;
}

void evoluer_tour_aoe( tour_aoe_t * aoe )
{
	if( tour_existe(aoe) )
	{
		evoluer_tour( (void*)aoe );
		
		aoe->afficher(aoe);
		printf(" a évolué au niveau %d, %d degats\n", aoe->niveau, aoe->degat );
		printf("GOLD -%d : %d\n", MULT_PRIX_TOUR*(aoe->niveau-1), GOLD);
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
