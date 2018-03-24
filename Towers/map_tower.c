#include "map_tower.h"

//Format des caracteristique d'une tour
#define FORMAT_NUM(x, y, n) (x >= 0 && x < N && y >= 0 && y < N && n > 0 && n <= NIVEAU_MAX_TOUR)

static int poser_monument(map_tower map)
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	
	int x = rand()%N, y = rand()%N;
	
	while(!case_vide(map, x, y))
	{
		x = rand()%N;
		y = rand()%N;
	}
	COORD(map, x, y) = (tour_t *) creer_monument(x, y);
	
	return ERR_OK;
}


/*-------- Creation --------*/
map_tower creer_map_tower()
/* Alloue un espace mémoire pour la map,
	les valeurs sont initialisées à zéro */
{
	map_tower map = calloc(N*N, sizeof(*map)); //Alloue de la memoire et initialise à zéro
	
	if(map == NULL)
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création de la map de tours !\n");
		return NULL;
	}
	
	return map;
}

map_tower init_mat_tower()
/* Créé la map,
	créé le fichier de sauvegarde des tours (le fichier est écrasé si déjà existant),
	pose le monument */
{
	map_tower map;
	
	if( !(map = creer_map_tower()) )
		return NULL;
	
	//Test l'existance du fichier de sauvegarde des tours, créé un nouveau
	FILE * fic;
	fic = fopen("fichier_tours.txt", "w");
	fclose(fic);
	
	int rtn = poser_monument(map);
	if( rtn != ERR_OK )
		printf("\tERREUR, à la création du monument code erreur %d\n", rtn);
	
	return map;
}

map_tower charger_map()
{
	//Ouverture du fichier + test si existance et non vide
	FILE * fic = fopen("fichier_tours.txt", "r");
	if(fic == 0)
	{
		printf("\tERREUR, le fichier de sauvegarde n'existe pas !\n");
		return NULL;
	}
	fseek(fic, 0, SEEK_END);
	if(ftell(fic) == 0)
	{
		printf("\tERREUR, le fichier de sauvegarde est vide !\n");
		return NULL;
	}
	fseek(fic, 0, SEEK_SET); //Revient au debut de fichier
	
	map_tower map = creer_map_tower();
	if(map == NULL)
		return NULL;
	
	char type[9];
	int x, y, n;
	
	//Parcours le fichier, edit la map en consequence
	while(!feof(fic))
	{
		//li dans le fichier de sauvegarde, le type de tour, la pos x + y et le niveau
		fscanf(fic, "%s %d %d %d", type, &x, &y, &n);
		
		/* Verifie les coordonnees, qui doivent etre dans les bornes de la map,
			le niveau doit etre positif et inferieur a la limite
			et la case visée doit etre vide.
		Verifie que le type existe, si tel est le cas, créé la tour du type adequat au bon endroit */
		if( FORMAT_NUM(x, y, n) && case_vide(map, x, y) )
		{
			if( strcmp(type, "MONUMENT") == 0 )
				COORD(map, x, y) = (tour_t *) new_monument(x, y, n);
			else if( strcmp(type, "MONO") == 0 )
				COORD(map, x, y) = (tour_t *) new_mono(x, y, n);
			else if( strcmp(type, "AOE") == 0 )
				COORD(map, x, y) = (tour_t *) new_aoe(x, y, n);
		}
	}
	fclose(fic);
	
	printf("Les données de sauvegarde ont été chargées !\n");
	
	return map;
}


/*-------- Booléenes --------*/
int map_existe( map_tower map )
{
	return map != NULL;
}

int case_vide(map_tower map, int x, int y)
{
	return COORD(map, x, y) == NULL;
}


int poser_tour(map_tower map, int x, int y, type_tour type)
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	if(!case_vide(map, x, y))
		return ERR_CASE_OCCUPEE;
	
	switch(type)
	{
		case AOE:
			COORD(map, x, y) = (tour_t *) creer_tour_aoe(x, y);
			if( COORD(map, x, y) )
				printf("AOE  posée en <%02d,%02d>\n", x, y);
			break;
		case MONO:
			COORD(map, x, y) = (tour_t *) creer_tour_mono(x, y);
			if( COORD(map, x, y) )
				printf("MONO posée en <%02d,%02d>\n", x, y);
			break;
		default:
			printf("\tERREUR, le type de tour %d n'existe pas !\n", type);
	}
	
	return ERR_OK;
}

int evoluer_tour(map_tower map, int x, int y)
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	if(case_vide(map, x, y))
		return ERR_CASE_VIDE;
	
	return COORD(map, x, y)->evoluer( COORD(map, x, y) );;
}

int attaquer_tour(map_tower map, mobs_t * mat[][N])
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(!case_vide(map, j, i))
				COORD(map, j, i)->attaquer( COORD(map, j, i), (void *)mat );
	
	return ERR_OK;
}

void afficher_map_tower(map_tower map)
{
	if( !map_existe(map) )
	{
		printf("La map n'existe pas !\n");
		return;
	}
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			if(case_vide(map, j, i))
				printf(" ");
			else
				printf("T");
		printf("\n");
	}
}

int attaquer_monument(map_tower map, int degats)
{
	if(!map_existe(map))
	{
		return 1;
	}
	
	int x, y;
	
	get_monu_pos(&x, &y);
	
	degats_monu( (monument_t**) &COORD(map, x, y), degats );
	
	return 0;
}


type_tour get_type_tour(map_tower map, int x, int y)
{
	if(!map_existe(map))
		return -2;
	if(case_vide(map, x, y))
		return -1;
	return get_type(COORD(map, x, y));
}


/*-------- Destruction --------*/
int detruire_map_tower( map_tower * map )
{
	if( !map_existe(*map) )
		return ERR_OBJ_NULL;
	
	//Libere les cases une a une
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if( !case_vide(*map, j, i) )
				COORD(*map, j, i)->detruire( (void**) &COORD(*map, j, i) );
	
	//Libere la matrice
	free(*map);
	*map = NULL;

	return ERR_OK;
}
