#include <stdio.h>
#include "../all.h"


/*-------- Attaque --------*/
static
void tour_aoe_attaquer(tour_aoe_t * aoe, mobs_t * mat[][N])
/* Fonction d'attaque d'une tour d'AOE */
{
	int x = aoe->pos_x, y = aoe->pos_y;
	
	for(int i = -RAYON_TOUR; i <= RAYON_TOUR; i++)
		for(int j = -RAYON_TOUR; j <= RAYON_TOUR; j++)
			if( 0 <= (x+i) < N && 0 <= (y+j) < N && mat[x+i][y+j] != NULL )
			{
				printf("AOE  %02d %02d attaque en <%02d,%02d> -%d PV\n", 
					aoe->pos_x, aoe->pos_y, x+i, y+j, aoe->degat );
					
				perte_vie( &mat[x+i][y+j], aoe->degat );
				
				if( mat[x+i][y+j] == NULL )
					printf("AOE  %02d %02d a tuée <%02d,%02d>\n",
						aoe->pos_x, aoe->pos_y, x+i, y+j );
			}
}


/*-------- Évolution --------*/
static
int evoluer_tour_aoe( tour_aoe_t * aoe )
{
	if( !tour_existe(aoe) )
		return ERR_OBJ_NULL;
	
	int rtn = evolution_tour( (void*)aoe );
	
	if(rtn == ERR_OK)
		printf("AOE  <%02d,%02d> évolue au niveau %d, %d dégats\n",
			aoe->pos_x, aoe->pos_y, aoe->niveau, aoe->degat );
	
	return rtn;
}

static
void afficher_tour_aoe( tour_aoe_t * aoe )
/* Affichage d'une tour d'AOE */
{
	if( tour_existe(aoe) )
		printf("A");
	else
		printf("{NULL}");
}


/*-------- Creation --------*/
tour_aoe_t * new_aoe(int x, int y)
{
	tour_t * temp = NULL;
	tour_aoe_t * aoe = NULL;

	temp = creer_tour(x,y);
	if(temp == NULL)
		return NULL;
	
	aoe = realloc(temp, sizeof(*aoe));
	if( aoe == NULL )
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création d'une tour d'AOE !\n");
		return NULL;
	}
	
	
	aoe->degat = DEGATS_TOUR_AOE;

	aoe->detruire = (int (*)( void ** )) detruire_tour_aoe;
	aoe->attaquer = (void (*)(void *, void *(*)[N])) tour_aoe_attaquer;
	aoe->evoluer = (int (*)(void *)) evoluer_tour_aoe;
	aoe->afficher = (void (*)(void *)) afficher_tour_aoe;
	
	return aoe;
}

tour_aoe_t * creer_tour_aoe( int x, int y )
{
	if( GOLD < PRIX_TOUR )
	{
		printf("\tGOLD insuffisant pour poser une tour AOE !\n");
		return NULL;
	}
	
	tour_aoe_t * aoe = new_aoe(x, y);
	if(aoe == NULL)
		return NULL;
	
	GOLD -= PRIX_TOUR;	
	
	//Fichier de sauvegarde
	FILE * fic = fopen("fichier_tours.txt", "a");
	if(!fic)
	{
		printf("\tERREUR, ouverture du fichier de sauvgarde impossible !\n");
		return NULL;
	}
	fprintf(fic, "\nAOE %d %d 1", x, y);
	fclose(fic);	
	
	return aoe;
}


/*-------- Destruction --------*/
int detruire_tour_aoe( tour_aoe_t ** aoe )
{
	if( !tour_existe( (*aoe) ) )
		return ERR_OBJ_NULL;
	
	free(*aoe);
	*aoe = NULL;
	
	return ERR_OK;
}
