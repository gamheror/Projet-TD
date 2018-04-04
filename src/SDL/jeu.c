#include "jeu.h"

/**********************************************************************************************************************
	Une tuile represente les images dans les menus et les bandeaux
**********************************************************************************************************************/


SDL_Surface * ecran; //surface servant a l'affichage

SDL_Rect tuile_select_aoe = {0, MARGE_HAUT/2 +HAUTEUR_MENU_GAUCHE/3, 100, 100},
		 tuile_select_mono = {0, MARGE_HAUT/2 +HAUTEUR_MENU_GAUCHE*2/3, 100, 100};

/**
* \fn print_menu_haut()
* \brief 	Fonction recopiant le bandeau au dessus de l'ecran 
*			montrant le nombre de gold actuel
**/
void print_menu_haut()
{
	SDL_Surface * cadre = SDL_CreateRGBSurface(0, LARGEUR_MENU_HAUT, MARGE_HAUT, 32, 0, 0, 0, 0), //cadre du menu haut
				* tuile_gold = IMG_Load("ressources/Images/gold.png");
	
	SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 64, 64, 64)); //fond gris fonce pour le cadre
	
	SDL_Rect pos_tuile_gold = {LARGEUR_MENU_HAUT/4 -TAILLE_TUILE/2,
							   MARGE_HAUT/2 -TAILLE_TUILE/2,
							   TAILLE_TUILE,
							   TAILLE_TUILE}, //position de la tuile gold dans cadre
			 pos_menu_haut = {MARGE_GAUCHE, 0, LARGEUR_MENU_HAUT, MARGE_HAUT}; //position du cadre dans ecran
	
	SDL_BlitScaled(tuile_gold, NULL, cadre, &pos_tuile_gold); //deplace tuile dans cadre
	
	SDL_BlitScaled(cadre, NULL, ecran, &pos_menu_haut); //copie cadre dans ecran
	
	SDL_FreeSurface(cadre);
	SDL_FreeSurface(tuile_gold);
}

/**
* \fn print_menu_gauche()
* \brief	Fonction recopiant le bandeau de gauche
*			montrant les tuiles des tours et leur couts
*
**/
void print_menu_gauche()
{
	char prix[5];
	sprintf(prix, "%d", PRIX_TOUR);
	
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	SDL_Surface * cadre = SDL_CreateRGBSurface(0, MARGE_GAUCHE, HAUTEUR_MENU_GAUCHE, 32, 0, 0, 0, 0), //cadre du menu gauche
				* tuile_aoe = IMG_Load("ressources/Images/AOE.png"),
				* tuile_mono = IMG_Load("ressources/Images/MONO.png"), 
				* tuile_gold = IMG_Load("ressources/Images/gold.png"),
				* surface_prix_aoe = SDL_CreateRGBSurface(0, MARGE_GAUCHE*9/10, 20, 32, 0, 0, 0, 0),
				* surface_prix_mono = SDL_CreateRGBSurface(0, MARGE_GAUCHE*9/10, 20, 32, 0, 0, 0, 0),
				* surface_prix_tours = TTF_RenderText_Blended(police, prix, couleur_blanche);
	
	SDL_FillRect(cadre, NULL, SDL_MapRGB(cadre->format, 64, 64, 64)); //fond gris fonce pour le cadre
	SDL_FillRect(surface_prix_aoe, NULL, SDL_MapRGB(surface_prix_aoe->format, 64, 64, 64));
	SDL_FillRect(surface_prix_mono, NULL, SDL_MapRGB(surface_prix_mono->format, 64, 64, 64));
	
	SDL_Rect pos_tuile_aoe = {MARGE_GAUCHE/2 -TAILLE_TUILE/2,
							   HAUTEUR_MENU_GAUCHE/3 -TAILLE_TUILE/2,
							   TAILLE_TUILE,
							   TAILLE_TUILE}, //position de la tuile aoe dans cadre*
			 pos_tuile_mono = {MARGE_GAUCHE/2 -TAILLE_TUILE/2,
							   HAUTEUR_MENU_GAUCHE*2/3 -TAILLE_TUILE/2,
							   TAILLE_TUILE,
							   TAILLE_TUILE}, //position de la tuile mono dans cadre
			 pos_menu_gauche = {0, MARGE_HAUT, MARGE_GAUCHE, HAUTEUR_MENU_GAUCHE}, //position du cadre dans ecran
			 pos_prix_aoe = {MARGE_GAUCHE/20,
			 				 HAUTEUR_MENU_GAUCHE/3 -TAILLE_TUILE/2 -30,
			 				 MARGE_GAUCHE*9/10,
			 				 20},
			 pos_prix_mono = {MARGE_GAUCHE/20,
			 				 HAUTEUR_MENU_GAUCHE*2/3 -TAILLE_TUILE/2 -30,
			 				 MARGE_GAUCHE*9/10,
			 				 20},
			 pos_gold_prix = { 10, 0, 20, 20},
			 pos_prix = {30, 0, 60, 20};
	
	//SDL_FillRect(cadre, &pos_prix_aoe, SDL_MapRGB(cadre->format, 255, 255, 255));
	
	SDL_BlitScaled(tuile_aoe, NULL, cadre, &pos_tuile_aoe); //deplace tuile dans cadre
	SDL_BlitScaled(tuile_gold, NULL, surface_prix_aoe, &pos_gold_prix); //dollar prix aoe
	SDL_BlitScaled(surface_prix_tours, NULL, surface_prix_aoe, &pos_prix); //prix aoe
	SDL_BlitScaled(surface_prix_aoe, NULL, cadre, &pos_prix_aoe); //place prix dans cadre
	SDL_BlitScaled(tuile_mono, NULL, cadre, &pos_tuile_mono); //deplace tuile dans cadre
	SDL_BlitScaled(tuile_gold, NULL, surface_prix_mono, &pos_gold_prix); //dollar prix mono
	SDL_BlitScaled(surface_prix_tours, NULL, surface_prix_mono, &pos_prix); //prix mono
	SDL_BlitScaled(surface_prix_mono, NULL, cadre, &pos_prix_mono); //place prix mono dans cadre
	SDL_BlitScaled(cadre, NULL, ecran, &pos_menu_gauche); //copie cadre dans ecran
	
	SDL_FreeSurface(cadre);
	SDL_FreeSurface(tuile_aoe);
	SDL_FreeSurface(tuile_mono);
	SDL_FreeSurface(tuile_gold);
	TTF_CloseFont(police);
}

/**
* \fn print_sol()
* \brief	Fonction recopiant le sol et ajoutant les buissons et les rochers (deco)
* 
**/
void print_sol()
{
	SDL_Surface * pelouse = IMG_Load("ressources/Images/pelouse.png"),
				* deco = NULL;
	
	//Parcours les cases
	for(int i = 0; i < N; i++)
		for(int  j = 0; j < N; j++)
		{
			SDL_Rect pos = {MARGE_GAUCHE +j*TAILLE_IMAGE, MARGE_HAUT +i*TAILLE_IMAGE, TAILLE_IMAGE, TAILLE_IMAGE}; //position de la case
			SDL_BlitScaled(pelouse, NULL, ecran, &pos); //copie pelouse dans ecran
			
			//ajoute la deco
			switch(rand()%100) //deco aleatoire
			{
				case 0:
					deco = IMG_Load("ressources/Images/buisson_1.png");
					break;
				case 1:
					deco = IMG_Load("ressources/Images/buisson_2.png");
					break;
				case 2:
					deco = IMG_Load("ressources/Images/buisson_3.png");
					break;
				case 3:
					deco = IMG_Load("ressources/Images/buisson_4.png");
					break;
				case 4:
					deco = IMG_Load("ressources/Images/rocher_1.png");
					break;
				case 5:
					deco = IMG_Load("ressources/Images/rocher_2.png");
					break;
				case 6:
					deco = IMG_Load("ressources/Images/rocher_3.png");
					break;
			}
			//copie la deco dans ecran
			if(deco != NULL)
			{
				SDL_BlitScaled(deco, NULL, ecran, &pos);
				SDL_FreeSurface(deco);
				deco = NULL;
			}
			
		}
	SDL_FreeSurface(pelouse);
}

/**
* \fn print_chemin()
* \brief 	Fonction recopiant le chemin sur l'ecran en le remplissant
*			de maniere aleatoire avec 3 types de cases differentes
**/
void print_chemin(liste_t * chemin)
{
	liste_debut(chemin);
	
	SDL_Surface * parcours = IMG_Load("ressources/Images/chemin.png"),
				* deco = NULL;
	
	//Parcours les cases
	while(!fin_liste(chemin))
	{
		SDL_Rect pos = {MARGE_GAUCHE + chemin->courant->x*TAILLE_IMAGE,
						MARGE_GAUCHE + chemin->courant->y*TAILLE_IMAGE,
						TAILLE_IMAGE,
						TAILLE_IMAGE}; //position de la case
		SDL_BlitScaled(parcours, NULL, ecran, &pos); //copie la pelouse dans ecran
		
		//ajoute la deco
		switch(rand()%10) //deco aleatoire
		{
			case 0:
				deco = IMG_Load("ressources/Images/relief_chemin_1.png");
				break;
			case 1:
				deco = IMG_Load("ressources/Images/relief_chemin_2.png");
				break;
			case 2:
				deco = IMG_Load("ressources/Images/relief_chemin_3.png");
				break;
		}
		//copie la deco dans ecran
		if(deco != NULL)
		{
			SDL_BlitScaled(deco, NULL, ecran, &pos);
			SDL_FreeSurface(deco);
			deco = NULL;
		}
		liste_suivant(chemin);
	}
	SDL_FreeSurface(parcours);
} 

/**
* \fn print_tours(map_tower map, listes_t * chemin)
* \brief 	Fonction recopiant les tours sur l'ecran en fonction de la 
*			matrice des tours. En fin de fonction la derniere case de la
*			liste est à supprimer pour empecher le monument d'etre sur le chemin.
*
* \param 	matrice de pointeur map, la liste_t du chemin
**/
void print_tours(map_tower map, liste_t * chemin)
{
	SDL_Surface * tour, 
				* pelouse = IMG_Load("ressources/Images/pelouse.png");
	
	//parcours matrice tours
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(!case_vide(map, j, i))					//il y a quelque chose dans la case
			{
				int niveau = get_niveau_tour(map, j, i);
				switch(get_type_tour(map, j ,i))		//recupere sont type et charge l'image adequat
				{
					case AOE :
						if(niveau > 2)
							tour = IMG_Load("ressources/Images/AOE_2.png");
						else
							tour = IMG_Load("ressources/Images/AOE.png");
						break;
					case MONO :
						if(niveau > 2)
							tour = IMG_Load("ressources/Images/MONO_2.png");
						else
							tour = IMG_Load("ressources/Images/MONO.png");
						break;
					case MONU :
						tour = IMG_Load("ressources/Images/monument.png");
						break;
				}
				SDL_Rect pos = {MARGE_GAUCHE +j*TAILLE_IMAGE,
								MARGE_HAUT +i*TAILLE_IMAGE,
								TAILLE_IMAGE, 
								TAILLE_IMAGE}; 					//position de l'image
				SDL_BlitScaled(pelouse, NULL, ecran, &pos); 	//carre de pelouse
				SDL_BlitScaled(tour, NULL, ecran, &pos);		//pose tour dans ecran
				SDL_FreeSurface(tour);
			}
	SDL_FreeSurface(pelouse);
	detruire_dernier_elem(&chemin); //supprime le dernier element de la liste sinon le monument est sur le chemin
}

/**
* \fn print_gold(SDL_Renderer * renderer)
* \brief 	Fonction recopiant les golds sur l'ecran
*			
* \param 	le renderer contenant les images
**/
void print_gold(SDL_Renderer * renderer)
{
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	char str[16];
	//copie GOLD dans srt
	sprintf(str, "%d", GOLD);
	
	SDL_Rect pos_gold = {100 +LARGEUR_MENU_HAUT/2 -TAILLE_TUILE/2,
							MARGE_HAUT/2 -TAILLE_POLICE/2,
							strlen(str)*TAILLE_POLICE,
							TAILLE_POLICE};
	
	SDL_Surface * surface_texte = TTF_RenderText_Blended(police, str, couleur_blanche);
	
	SDL_Texture * texture_gold = SDL_CreateTextureFromSurface(renderer, surface_texte);
	
	SDL_RenderCopy(renderer, texture_gold, NULL, &pos_gold);
	
	SDL_DestroyTexture(texture_gold);
	SDL_FreeSurface(surface_texte);
	TTF_CloseFont(police);
}

/**
* \fn print_mob(SDL_Renderer * renderer, mobs_t * mob[N])
* \brief 	Fonction affichant les monstres sur le chemin.
*			
* \param 	le renderer de la fenetre, un tableau de structure mobs_t
**/
void print_mob(SDL_Renderer * renderer, mobs_t * mob[N])
{
	SDL_Surface * m_boss = IMG_Load("ressources/Images/monstre_boss.png"),
				* m_degat = IMG_Load("ressources/Images/monstre_degat.png"),
				* m_tank = IMG_Load("ressources/Images/monstre_tank.png"),
				* m_norm = IMG_Load("ressources/Images/monstre_normal.png");
	
	for(int i = 0; i < N; i++)
	{
		if(mob[i] != NULL)
		{
			SDL_Texture * texture_image;
			switch(mob[i]->caract)
			{
				case 'B' :
					texture_image = SDL_CreateTextureFromSurface(renderer, m_boss);
					break;
				case 'D' :
					texture_image = SDL_CreateTextureFromSurface(renderer, m_degat);
					break;
				case 'T' :
					texture_image = SDL_CreateTextureFromSurface(renderer, m_tank);
					break;
				case 'N' :
					texture_image = SDL_CreateTextureFromSurface(renderer, m_norm);
					break;
			}
			SDL_Rect pos = {MARGE_GAUCHE +mob[i]->pos->x*TAILLE_IMAGE,
						MARGE_HAUT +mob[i]->pos->y*TAILLE_IMAGE,
						TAILLE_IMAGE,
						TAILLE_IMAGE};
			SDL_RenderCopy(renderer, texture_image, NULL, &pos);
			SDL_DestroyTexture(texture_image);
		}
	}
	SDL_FreeSurface(m_boss);
	SDL_FreeSurface(m_degat);
	SDL_FreeSurface(m_norm);
	SDL_FreeSurface(m_tank);
}

/**
* \fn print_avancement_vague(SDL_Renderer * renderer, int nb_tues, int nb_vague)
* \brief 	Fonction recopiant le nombres de monstres restant dans la vague.
*			
* \param 	le renderer de la fenetre, le nombre de monstres abbatus, la vague actuelle
**/
void print_avancement_vague(SDL_Renderer * renderer, int nb_tues, int nb_vague)
{
	char avancement[16];
	sprintf(avancement, "%d sur %d", nb_tues, nb_vague);
	
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	SDL_Rect pos_avancement = {	MARGE_GAUCHE/2 -strlen(avancement)*TAILLE_TXT_FOOTER/2,
								MARGE_HAUT +20,
								strlen(avancement)*TAILLE_TXT_FOOTER,
								TAILLE_TXT_FOOTER};
	
	SDL_Surface * surface_avancement = TTF_RenderText_Blended(police, avancement, couleur_blanche);
	
	SDL_Texture * texture_avancement = SDL_CreateTextureFromSurface(renderer, surface_avancement);
	
	SDL_RenderCopy(renderer, texture_avancement, NULL, &pos_avancement);
	
	SDL_DestroyTexture(texture_avancement);
	SDL_FreeSurface(surface_avancement);
	TTF_CloseFont(police);
}

/**
* \fn init_plateau(map_tower map, liste_t * chemin)
* \brief 	Fonction definissant la taille de l'ecran et applique les 
*			differentes fonctions print existante pour initialiser la map
*			
* \param 	un map_tower pour la matrice de tour et la liste_t du chemin
**/
void init_plateau(map_tower map, liste_t * chemin)
{
	ecran = SDL_CreateRGBSurface(0, LARGEUR_FEN, HAUTEUR_FEN, 32, 0, 0, 0, 0); //definie taille image
	
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //fond blanc
	
	//copie different element de l'ecran
	print_nb_vague(1);
	print_menu_haut();
	print_menu_gauche();
	print_sol();
	print_tours(map, chemin);
	print_chemin(chemin);
}

/**
* \fn update_plateau(SDL_Renderer * renderer, mobs_t * mob[N], int nb_tues, int nb_vague)
* \brief 	Fonction appliquant les differentes fonctions print existante pour mettre a jour la map
*
* \param 	le renderer de la fenetre, un tableau de monstre, le nombre de monstres abbatuent, la vague actuelle
**/
void update_plateau(SDL_Renderer * renderer, mobs_t * mob[N], int nb_tues, int nb_vague)
{
	SDL_Rect pos = {0, 0, LARGEUR_FEN, HAUTEUR_FEN};
	
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, ecran);
	
	SDL_RenderCopy(renderer, texture, NULL, &pos);
	
	print_gold(renderer);
	print_mob(renderer, mob);
	print_avancement_vague(renderer, nb_tues, nb_vague);
	
	SDL_RenderPresent(renderer);
	
	SDL_DestroyTexture(texture);
}

/**
* \fn		ajouter_tour_plateau(map_tower map, liste_t * chemin, type_tour type, int x, int y)
* \brief 	Fonction ajoutant une tour sur l'ecran et dans la matrice des tours.
*			
* \param 	matrice de pointeur map, liste_t contenant le chemin, le type de tour, sa coordonnée en x, sa coordonnée en y
**/
void ajouter_tour_plateau(map_tower map, liste_t * chemin, type_tour type, int x, int y)
{
	if(x < 0 || x >= N || y < 0 || y >= N)
		return;
	
	//verifie que la case de la matrice de tour est vide
	if(!case_vide(map, x, y))
	{
		if(get_type_tour(map, x, y) == type)
			evoluer_tour_plateau(map, x, y);
		return;
	}
	
	//parcours chemin pour verifier si on ne pose pas la tour sur celui-ci
	liste_debut(chemin);
	while(!fin_liste(chemin))
	{
		if(chemin->courant->x == x && chemin->courant->y == y)
			return;
		liste_suivant(chemin);
	}
	
	if(GOLD >= PRIX_TOUR)
	{
		//ajoute la tour dans la matrice
		poser_tour(map, x, y, type);
		//pose la bonne tour
		SDL_Surface * tour, 
					* pelouse = IMG_Load("ressources/Images/pelouse.png");
	
		switch(type) //recupere sont type et charge l'image adequat
		{
			case AOE :
				tour = IMG_Load("ressources/Images/AOE.png");
				printf("%s", TTF_GetError());
				break;
			case MONO :
				tour = IMG_Load("ressources/Images/MONO.png");
				printf("%s", TTF_GetError());
				break;
			case MONU: break;
		}
		SDL_Rect pos = {MARGE_GAUCHE +x*TAILLE_IMAGE,
						MARGE_HAUT +y*TAILLE_IMAGE,
						TAILLE_IMAGE, 
						TAILLE_IMAGE}; //position de l'image
	
		SDL_BlitScaled(pelouse, NULL, ecran, &pos); //carre de pelouse
		SDL_BlitScaled(tour, NULL, ecran, &pos); //pose tour dans ecran
	
		SDL_FreeSurface(tour);
		SDL_FreeSurface(pelouse);
	}
}

/**
* \fn		evoluer_tour_plateau(map_tower map, int x, int y)
* \brief 	Fonction faisant évoluer une tour d'un niveau. 
*			Une fois qu'elle passe le niveau 3 elle change d'apparence
*
* \param 	matrice de pointeur map, la coordonnée en x de la tour, la coordonnée en y de la tour
**/
void evoluer_tour_plateau(map_tower map, int x, int y)
{
	if(!case_vide(map, x, y))
	{
		evoluer_tour(map, x, y);
		SDL_Surface * tour, 
					* pelouse = IMG_Load("ressources/Images/pelouse.png");
		
		int niveau = get_niveau_tour(map, x, y);
		if(niveau < NIVEAU_MAX_TOUR)
		{
			switch(get_type_tour(map, x, y)) 			//recupere sont type et charge l'image adequat
			{
				case AOE :
					if(niveau > 2)
						tour = IMG_Load("ressources/Images/AOE_2.png");
					else
						tour = IMG_Load("ressources/Images/AOE.png");
					break;
				case MONO :
					if(niveau > 2)
						tour = IMG_Load("ressources/Images/MONO_2.png");
					else
						tour = IMG_Load("ressources/Images/MONO.png");
					break;
				case MONU:
					tour = IMG_Load("ressources/Images/monument");
					break;
			}
			SDL_Rect pos = {MARGE_GAUCHE +x*TAILLE_IMAGE,
							MARGE_HAUT +y*TAILLE_IMAGE,
							TAILLE_IMAGE, 
							TAILLE_IMAGE}; 				//position de l'image
			SDL_BlitScaled(pelouse, NULL, ecran, &pos); //carre de pelouse
			SDL_BlitScaled(tour, NULL, ecran, &pos); 	//pose tour dans ecran
		
			SDL_FreeSurface(tour);
		}
		SDL_FreeSurface(pelouse);
	}
}

/**
* \fn		print_nb_vague(int num_vague)
* \brief 	Fonction faisant apparaitre le numéro de la vague dans le coin supérieur gauche
*
* \param 	le numéro de la vague
**/
void print_nb_vague(int num_vague)
{
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	char str[2];
	sprintf(str, "%d", num_vague);
	
	SDL_Surface * cadre = SDL_CreateRGBSurface(0, MARGE_GAUCHE, MARGE_HAUT, 32, 0, 0, 0, 0),
				* surface_num_vague = TTF_RenderText_Blended(police, str, couleur_blanche);
	
	SDL_Rect pos = {0, 0, MARGE_GAUCHE, MARGE_HAUT},
			 pos_num = {20, 20, MARGE_GAUCHE-40, MARGE_HAUT-40};
	
	SDL_FillRect(cadre, NULL, SDL_MapRGB(ecran->format, 64, 64, 64));
	
	SDL_BlitScaled(surface_num_vague, NULL, cadre, &pos_num);
	SDL_BlitScaled(cadre, NULL, ecran, &pos);
	
	SDL_FreeSurface(surface_num_vague);
	SDL_FreeSurface(cadre);
	TTF_CloseFont(police);
}

/* Permet de récuperer l'adresse des tuiles des tours */
SDL_Rect * get_tuile_aoe()
{
	return &tuile_select_aoe;
}

SDL_Rect * get_tuile_mono()
{
	return &tuile_select_mono;
}
