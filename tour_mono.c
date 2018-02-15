#include "../all.h"

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
				if( 0 <= (x+i) < N && 0 <= (y+j) < N && mat[x+i][y+j] != NULL )
				{
					mono->cible = mat[x+i][y+j];
					mono->x_cible = x+i;
					mono->y_cible = y+j;
					return 1;
				}
			}
	return 0;
}

static
void tour_mono_attaquer( tour_mono_t * mono, mobs_t * mat[][N] )
/* Fonction d'attaque d'une tour mono cible
	Recherche un ennemi si elle n'a pas en cible */
{
	int rech = 1;
	
	if( mono->cible == NULL || mat[mono->x_cible][mono->y_cible] == NULL )//Si la tour ne possede pas de cible ou qu'elle pointe sur une case NULL
		rech = rechercher_ennemi( mono, mat );
//Si la tour n'a pas trouve d'ennemi, rech = 0
//=> Ne pas attaquer si la tour na trouve pas d'ennemi
	
	if(rech == 1)
	{
		int x_c = mono->x_cible, y_c = mono->y_cible;

		afficher_tour_mono(mono);
		printf(" attaque en <%d,%d> -%d PV\n", x_c, y_c, mono->degat );

		perte_vie( &mat[x_c][y_c], mono->degat );

		//verifier si ennemi mort, alors cible = NULL
		if( mat[x_c][y_c] == NULL )
		{
			mono->cible = NULL;
			afficher_tour_mono(mono);
			printf(" a tuée <%d,%d>\n", x_c, y_c );
		}
	}
}

tour_mono_t * creer_tour_mono( int x, int y )
{
	tour_t * temp = NULL;
	tour_mono_t * mono = NULL;
	
	if( gold >= PRIX_TOUR )
	{
		temp = creer_tour(x,y); //Utilise la fonction de creation d'une tour simple
		mono = realloc(temp, sizeof(tour_mono_t)); //Realloc pour adapter la taille memoire allouee de tour vers tour_aoe
		//Verifie si realloc a trouve de la place pour une tour_mono
		if( mono == NULL )
			printf("Erreur creation d'une tour mono\n");
		else
		{
			mono->degat = DEGATS_TOUR_MONO;
			mono->cible = NULL;
	
			mono->detruire = (void (*)( void ** )) detruire_tour_mono;
			mono->attaquer = (void (*)(void *, void *(*)[N])) tour_mono_attaquer;
			mono->evoluer = (void (*)(void *)) evoluer_tour_mono;
			
			gold -= PRIX_TOUR;
			
			printf("Mono posée en <%d,%d>\n", x, y);
			printf("gold -%d : %d\n", PRIX_TOUR, gold);
		}
	}
	
	return mono;
}

void afficher_tour_mono( tour_mono_t * mono )
{
	if( tour_existe(mono) )
	{
		printf("{MONO <%d,%d> ", mono->pos_x, mono->pos_y);
		afficher_tour( (tour_t *)mono );
		printf(" }");
	}
	else
		printf("NULL");
}

void evoluer_tour_mono( tour_mono_t * mono )
{
	if( tour_existe(mono) )
	{
		evoluer_tour( (void*)mono );
		afficher_tour_mono(mono);
		printf(" a évolué au niveau %d, %d degats\n", mono->niveau, mono->degat );
		printf("gold -%d : %d\n", MULT_PRIX_TOUR*(mono->niveau-1), gold);
	}
}

void detruire_tour_mono( tour_mono_t ** mono )
{
	if( tour_existe(*mono) )
	{
		free(*mono);
		*mono = NULL;
	}
}
