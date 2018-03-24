#include "all.h"
#include "include_fichiers.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#define LARDEUR_FEN 1280
#define HAUTEUR_FEN 720

#define MARGE_HAUT 100
#define MARGE_BAS 20
#define MARGE_GAUCHE 100

#define TAILLE_POLICE 30

#define TAILLE_IMAGE 30
#define TAILLE_TUILE 80


#define LARGEUR_MENU_HAUT 800
#define HAUTEUR_MENU_GAUCHE 500


void copie_gold(SDL_Renderer * r, TTF_Font * p)
/*
	copie le nombre de GOLDs dans le renderer
*/
{
	char str[16];
	//copie GOLD dans srt
	sprintf(str, "%d", GOLD);
	SDL_Color couleur_gold = {255, 255, 255, 255};
	SDL_Rect pos_gold = {100 +LARGEUR_MENU_HAUT/2 -TAILLE_TUILE/2,
							MARGE_HAUT/2 -TAILLE_POLICE/2,
							strlen(str)*TAILLE_POLICE,
							TAILLE_POLICE};
	SDL_Texture * texture_gold = SDL_CreateTextureFromSurface(r, TTF_RenderText_Blended(p, str, couleur_gold));
	SDL_RenderCopy(r, texture_gold, NULL, &pos_gold);
}


int main()
{
	//Initialisation de la SDL
	if( SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	if( TTF_Init() != 0 )
	{
		printf("Erreur d'initialisation des polices : %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}
	if( IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0 )
	{
		printf("Erreur initialisation des images : %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}
	
	GOLD = 1000;
	liste_t * chemin = NULL;
	map_tower tower = NULL;
	
	
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Surface * image = NULL;
	TTF_Font * police = NULL;
	SDL_Texture * texture_image = NULL;
	
	
	
	//Initialisation de la fenetre
	if( NULL == (window = SDL_CreateWindow ("ZOZOR DEFENSE",
											SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
											LARDEUR_FEN,
											HAUTEUR_FEN,
											SDL_WINDOW_SHOWN ) ) )
	{
		printf("Erreur a la création de la fenetre : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Initialisation du renderer sur la fenetre
	if( NULL == (renderer = SDL_CreateRenderer(window, -1, 0)) )
	{
		printf("Erreur a la creation du renderer : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Initialisation de la police
	if( NULL == (police = TTF_OpenFont("Polices/Ordinary.ttf", TAILLE_POLICE)) )
	{
		printf("Erreur de chargement de la police : %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}
	
	
	
/*	//creer la texture de l'aigle*/
/*	SDL_Texture * texture_aigle = SDL_CreateTextureFromSurface(renderer, image_aigle);*/
/*	//copie la texture dans le renderer*/
/*	SDL_Rect pos_aigle = {0, 0, largeur_fenetre, hauteur_fenetre};*/
/*	SDL_RenderCopy(renderer, texture_aigle, NULL, &pos_aigle);*/
/*	SDL_DestroyTexture(texture_aigle);*/
/*	*/
/*	*/
/*	//Titre*/
/*	SDL_Surface * surface_titre = TTF_RenderText_Blended(police, "ZOZOR DEFENSE", couleur_titre);*/
/*	SDL_Rect pos_titre = {largeur_fenetre/2 -LARGEUR_TITRE/2,*/
/*						  100, */
/*						  LARGEUR_TITRE, */
/*						  HAUTEUR_TITRE };*/
/*	SDL_Texture * texture_titre = SDL_CreateTextureFromSurface(renderer, surface_titre);*/
/*	SDL_RenderCopy(renderer, texture_titre, NULL, &pos_titre);*/
/*	SDL_DestroyTexture(texture_titre);*/
/*	SDL_FreeSurface(surface_titre);*/
/*	*/
/*	*/
/*	*/
/*	*/
/*	*/
/*	//Refresh la fenetre avec le render present*/
/*	SDL_RenderPresent(renderer);*/
	
	
	
	
	//Arriere plan blanc
	SDL_Rect arriere_plan = {0, 0, LARDEUR_FEN, HAUTEUR_FEN};
	SDL_RenderFillRect(renderer, &arriere_plan);
	
	
	//Numero de vague
	texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/vague_0.png"));
	SDL_Rect vague = {0, 0, MARGE_GAUCHE, MARGE_HAUT};
	SDL_RenderCopy(renderer, texture_image, NULL, &vague);
	
	
	//Menu haut
	SDL_Rect menu_haut = {100, 0, LARGEUR_MENU_HAUT, MARGE_HAUT};
	SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
	SDL_RenderFillRect(renderer, &menu_haut);
	//Tuile gold
	texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/gold.png"));
	SDL_Rect pos_tuile_gold = {100 +LARGEUR_MENU_HAUT/4 -TAILLE_TUILE/2,
								MARGE_HAUT/2 -TAILLE_TUILE/2,
								TAILLE_TUILE,
								TAILLE_TUILE};
	SDL_RenderCopy(renderer, texture_image, NULL, &pos_tuile_gold);
	//GOLD
	copie_gold(renderer, police);
	
	
	//Menu gauche
	SDL_Rect menu_gauche = {0, MARGE_HAUT, MARGE_GAUCHE, HAUTEUR_MENU_GAUCHE};
	SDL_SetRenderDrawColor(renderer, 64, 64,  64, 255);
	SDL_RenderFillRect(renderer, &menu_gauche);
	//Tuile tour aoe
	texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/AOE.png"));
	SDL_Rect pos_tuile_aoe = {MARGE_GAUCHE/2 - TAILLE_TUILE/2,
								100 +HAUTEUR_MENU_GAUCHE/3 - TAILLE_TUILE/2,
								TAILLE_TUILE,
								TAILLE_TUILE};
	SDL_RenderCopy(renderer, texture_image, NULL, &pos_tuile_aoe);
	//Tuile tour mono
	texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/MONO.png"));
	SDL_Rect pos_tuile_mono = {MARGE_GAUCHE/2 - TAILLE_TUILE/2,
								100 +HAUTEUR_MENU_GAUCHE*2/3 - TAILLE_TUILE/2,
								TAILLE_TUILE,
								TAILLE_TUILE};
	SDL_RenderCopy(renderer, texture_image, NULL, &pos_tuile_mono);
	
	
	//Affiche le sol
	texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/pelouse.png"));
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			SDL_Rect pos = {MARGE_GAUCHE +j*TAILLE_IMAGE,
							MARGE_HAUT +i*TAILLE_IMAGE,
							TAILLE_IMAGE,
							TAILLE_IMAGE};
			SDL_RenderCopy(renderer, texture_image, NULL, &pos);
		}
	SDL_DestroyTexture(texture_image);
	
	
	//Créé le chemin
	chemin = initialisation();
	if(!chemin)
	{
		printf("Erreur initialisation de la liste !\n");
		return EXIT_FAILURE;
	}
	liste_debut(chemin);
	
	
	//Affiche le chemin
	texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/chemin.png"));
	while(!fin_liste(chemin))
	{
		SDL_Rect pos = {MARGE_GAUCHE +chemin->courant->x*TAILLE_IMAGE,
							MARGE_HAUT +chemin->courant->y*TAILLE_IMAGE,
							TAILLE_IMAGE,
							TAILLE_IMAGE};
		SDL_RenderCopy(renderer, texture_image, NULL, &pos);
		liste_suivant(chemin);
	}
	SDL_DestroyTexture(texture_image);
	
	
	//Tours
	tower = charger_map();
	if(tower == NULL)
	{
		printf("Erreur chargement tours !\n");
		return EXIT_FAILURE;
	}
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			if(!case_vide(tower, j, i))
			{
				switch(get_type_tour(tower, j ,i))
				{
					case AOE :
						texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/AOE.png"));
						break;
					case MONO :
						texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/MONO.png"));
						break;
					case MONU :
						texture_image = SDL_CreateTextureFromSurface(renderer, IMG_Load("Images/monument.png"));
						break;
				}
				SDL_Rect pos_tour = {MARGE_GAUCHE +j*TAILLE_IMAGE,
										MARGE_HAUT +i*TAILLE_IMAGE,
										TAILLE_IMAGE, 
										TAILLE_IMAGE};
				SDL_RenderCopy(renderer, texture_image, NULL, &pos_tour);
				
				SDL_DestroyTexture(texture_image);
			}
	
	
	SDL_RenderPresent(renderer);
	
	
	int running = 1;
	int x, y;
	SDL_Event event;
	while(running)
	{
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
				break;
		}
	}
	
	
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	TTF_CloseFont(police);
	TTF_Quit();
	
	detruire_map_tower(&tower);
	detruire_liste(&chemin);
}
