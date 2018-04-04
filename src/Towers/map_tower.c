#include "map_tower.h"

/* Format des caracteristique d'une tour (coordonnées et niveau)*/
/**
 * \def FORMAT_NUM(x, y, n)
 * \brief verifie si les paramètres d'une tour sont valides
 *
 * \param x,y les coordonnées dans la matrice de tour et n le niveau de la tour
 * \return vrai si le paramètres sont valides, faux sinon
*/
#define FORMAT_NUM(x, y, n) (x >= 0 && x < N && y >= 0 && y < N && n > 0 && n <= NIVEAU_MAX_TOUR)

static int poser_monument(map_tower map, int x, int y)
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	
	COORD(map, x, y) = (tour_t *) creer_monument(x, y);
	
	return ERR_OK;
}


/*-------- Creation --------*/
/**
 * \fn creer_map_tower()
 * \brief Alloue un espace mémoire pour la matrice de tours,
	les valeurs de la matrice sont initialisées à zéro 
 *
 * \param void
 *
 * \return retourne la matrice créée
 */
map_tower creer_map_tower()
{
	map_tower map = calloc(N*N, sizeof(*map)); //Alloue de la memoire et initialise à zéro
	
	if(map == NULL)
	{
		printf("\tERREUR, espace mémoire insuffisant pour la création de la map de tours !\n");
		return NULL;
	}
	
	return map;
}

/**
 * \fn init_mat_tower(liste_t * liste)
 * \brief Créé la matrice de tours (appel creer_map_tower()),
	créé le fichier de sauvegarde des tours (le fichier est écrasé si déjà existant),
	se rend a la fin de la liste et pose le monument aux coordonnées indiquées
 *
 * \param liste_t * pour savoir ou poser le monuement
 *
 * \return retourne le matrice de tours initialisée avec le monument
 */
map_tower init_mat_tower(liste_t * liste)
{
	map_tower map;

	if( !(map = creer_map_tower()) )
		return NULL;
	
	//Test l'existance du fichier de sauvegarde des tours, créé un nouveau
	FILE * fic;
	fic = fopen("ressources/fichier_tours.txt", "w");
	fclose(fic);
	
	//liste vide, = pas de chemin = return
	if(liste == NULL)
	{
		printf("Erreur creation map, liste vide !\n");
		return NULL;
	}
	liste_fin(liste);
	
	int rtn = poser_monument(map,liste->courant->x, liste->courant->y);
	if( rtn != ERR_OK )
		printf("\tERREUR, à la création du monument code erreur %d\n", rtn);
	
	return map;
}

/**
 * \fn charger_map()
 * \brief initialise la matrice de tours suivant le fichiers de sauvegarde des tours
 *
 * \param void
 *
 * \return retourne la matrice de tours initialisée avec les tours contenues dans le fichier de sauvegarde
 */
map_tower charger_map()
/*
	
*/
{
	//Ouverture du fichier + test si existance et non vide
	FILE * fic = fopen("ressources/fichier_tours.txt", "r");
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
/**
 * \fn map_existe(map_tower map)
 * \brief fonction booléene verifiant si la matrice de tours a été initialisée
 *
 * \param la matrice de tour map à vérifier
 *
 * \return revoie vrai si la map_tower a été initialisée, faux sinon
 */
int map_existe( map_tower map )
{
	return map != NULL;
}

/**
 * \fn case_vide(map_tower map, int x, int y)
 * \brief verifie si une case de la matrice de tours est case
 *
 * \param la matrice de tour map et les coordonnées x et y de la case à vérifier
 *
 * \return vrai si la case x,y de map est vide (ne possede pas de tours), faux sinon
 */
int case_vide(map_tower map, int x, int y)
{
	return COORD(map, x, y) == NULL;
}

/**
 * \fn poser_tour(map_tower map, int x, int y, type_tour type)
 * \brief ajouter dans la matrice de tours une tour aux coordonnées passées en paramètres
 *
 * \param la matrice dans laquelle ajouter la tour, ses coordonnées x,y et son type
 *
 * \return retourne 0 si tout ses bien passé, code erreur sinon
 */
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

/**
 * \fn evoluer_tour(map_tower map, int x, int y)
 * \brief la tour de la matrice aux coordonnées x,y évolue
 *
 * \param la matrice map et les coordonnées x,y dans la matrice de la tour à évoluer
 *
 * \return retourne 0 si tout s'est bien déroulé, code erreur sinon
 */
int evoluer_tour(map_tower map, int x, int y)
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	if(case_vide(map, x, y))
		return ERR_CASE_VIDE;
	
	return COORD(map, x, y)->evoluer( COORD(map, x, y) );;
}

/**
 * \fn attaquer_tour(map_tower map, mobs_t * mat[N], int temps, int * nb_tues)
 * \brief toutes les tours de la matrice efféctuent une attaque sur les mobs contenus dans mat[N],
 		la répétition des attaques est dépendante de temps (sert d'horloge),
 		quand un mob est tué le pointeur nb_tues est incrémenté
 *
 * \param la matrice de tours, le tableau de mobs à attaquer,
 		une variable temps servant d'horloge et un pointeur sur entier incrémenté lors de la mort d'un mob
 *
 * \return retourne 0 si tout s'est bien passé, code erreur sinon
 */
int attaquer_tour(map_tower map, mobs_t * mat[N], int temps, int * nb_tues)
{
	if(!map_existe(map))
		return ERR_OBJ_NULL;
	
	if(temps%200 == 0) //attaque toute les secondes
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				if(!case_vide(map, j, i))
					*nb_tues += COORD(map, j, i)->attaquer( COORD(map, j, i), (void *)mat );
	
	return ERR_OK;
}

/**
 * \fn afficher_map_tower(map_tower map)
 * \brief affiche dans le terminal la matrice de tour
 *
 * \param la matrice de tours à afficher
 *
 * \return void
 */
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

/**
 * \fn get_type_tour(map_tower map, int x, int y)
 * \brief renvoie le type de la tour aux coordonnées x,y de la matrice
 *
 * \param la matrice de tours, les coordonnées de la tour
 *
 * \return retourne -1 si la case est vide, -2 si map n'existe pas, le type de la tour sinon
 */
type_tour get_type_tour(map_tower map, int x, int y)
{
	if(!map_existe(map))
		return -2;
	if(case_vide(map, x, y))
		return -1;
	return get_type(COORD(map, x, y));
}

/**
 * \fn get_niveau_tour(map_tower map, int x, int y)
 * \brief revoie le niveau de la tour aux coordonnées x,y de la matrice
 *
 * \param la matrice de tours, les coordonnées de la tour
 *
 * \return retourne 0 si la case est vide ou que la matrice n'existe pas, le niveau de la tour sinon
 */
int get_niveau_tour(map_tower map, int x, int y)
{
	if(map_existe(map) && !case_vide(map, x, y))
		return COORD(map, x, y)->niveau;
	return 0;
}


/*-------- Destruction --------*/
/**
 * \fn detruire_map_tower(map_tower * map)
 * \brief detruie la matrice de tour, réinitialise map à NULL
 *
 * \param un pointeur sur matrice de tours
 *
 * \return retourne 0 si tout s'est bien bien passé, code erreur sinon
 */
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
