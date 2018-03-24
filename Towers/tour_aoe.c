#include "tour.h"

/*-------- Sauvegarde --------*/
static
int modif_save(int aoe_x, int aoe_y)
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
		if(x == aoe_x && y == aoe_y)
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
	
	fprintf(fic, "\nAOE %02d %02d 1", x, y);
	fclose(fic);
	
	return ERR_OK;
}


/*-------- Attaque --------*/
static
void tour_aoe_attaquer(tour_aoe_t * aoe, mobs_t * mat[][N])
/* Fonction d'attaque d'une tour d'AOE */
{
	int x = aoe->pos_x, y = aoe->pos_y;
	
	for(int i = -RAYON_TOUR; i <= RAYON_TOUR; i++)
		for(int j = -RAYON_TOUR; j <= RAYON_TOUR; j++)
			if( LIMITES_MAP(x+i) && LIMITES_MAP(y+j) && mat[x+i][y+j] != NULL )
			{
				printf("AOE  <%02d,%02d> attaque en <%02d,%02d> -%d PV\n", 
					aoe->pos_x, aoe->pos_y, x+i, y+j, aoe->degat );
					
				perte_vie( &mat[x+i][y+j], aoe->degat );
				
				if( mat[x+i][y+j] == NULL )
					printf("AOE  <%02d,%02d> a tuée <%02d,%02d>\n",
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
	{
		printf("AOE  <%02d,%02d> évolue au niveau %d, %d dégats\n",
			aoe->pos_x, aoe->pos_y, aoe->niveau, aoe->degat );
		
		if(modif_save(aoe->pos_x, aoe->pos_y) != ERR_OK)
			return ERR_OBJ_NULL;
	}
	
	return rtn;
}

/*static*/
/*void afficher_tour_aoe( tour_aoe_t * aoe )*/
/* Affichage d'une tour d'AOE */
/*{*/
/*	if( tour_existe(aoe) )*/
/*		printf("A");*/
/*	else*/
/*		printf("{NULL}");*/
/*}*/


/*-------- Creation --------*/
tour_aoe_t * new_aoe(int x, int y, int n)
{
	tour_t * temp = NULL;
	tour_aoe_t * aoe = NULL;

	temp = creer_tour(x, y, n);
	if(temp == NULL)
		return NULL;
	
	aoe = realloc(temp, sizeof(*aoe));
	if( aoe == NULL )
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création d'une tour d'AOE !\n");
		return NULL;
	}
	
	
	aoe->degat = DEGATS_TOUR_AOE * pow(MULT_DEGATS_TOUR, n-1);
	aoe->type = AOE;

	aoe->detruire = (int (*)( void ** )) detruire_tour_aoe;
	aoe->attaquer = (void (*)(void *, void *(*)[N])) tour_aoe_attaquer;
	aoe->evoluer = (int (*)(void *)) evoluer_tour_aoe;
/*	aoe->afficher = (void (*)(void *)) afficher_tour_aoe;*/
	
	return aoe;
}

tour_aoe_t * creer_tour_aoe( int x, int y )
{
	if( GOLD < PRIX_TOUR )
	{
		printf("\tGOLD insuffisant pour poser une tour AOE !\n");
		return NULL;
	}
	
	tour_aoe_t * aoe = new_aoe(x, y, 1);
	if(aoe == NULL)
		return NULL;
	
	GOLD -= PRIX_TOUR;	
	
	//Fichier de sauvegarde
	if(ajout_save(x, y) != ERR_OK)
		return NULL;	
	
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
