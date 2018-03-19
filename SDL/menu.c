#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define LARGEUR_TITRE 750
#define HAUTEUR_TITRE 100

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
	
	
	int largeur_fenetre = 1280,
		hauteur_fenetre = 720;
	
	
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Surface * image_aigle = NULL;
	TTF_Font * police = NULL;
	SDL_Color couleur_titre = {32, 32, 32};
	
	
	//Initialisation de la fenetre
	if( NULL == (window = SDL_CreateWindow ("ZOZOR DEFENSE",
											SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
											largeur_fenetre,
											hauteur_fenetre,
											SDL_WINDOW_SHOWN ) ) )
	{
		printf("Erreur a la création de la fenetre : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Initialisation des images
	if( NULL == (image_aigle = IMG_Load("old_map.jpeg")) )
	{
		printf("Erreur chargement d'une image : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Initialisation du renderer sur la fenetre
	if( NULL == (renderer = SDL_CreateRenderer(window, -1, 0)) )
	{
		printf("Erreur a la creation du renderer : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	if( NULL == (police = TTF_OpenFont("Ordinary.ttf", HAUTEUR_TITRE)) )
	{
		printf("Erreur de chargement de la police : %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}
	
	
	
	//creer la texture de l'aigle
	SDL_Texture * texture_aigle = SDL_CreateTextureFromSurface(renderer, image_aigle);
	//copie la texture dans le renderer
	SDL_Rect pos_aigle = {0, 0, largeur_fenetre, hauteur_fenetre};
	SDL_RenderCopy(renderer, texture_aigle, NULL, &pos_aigle);
	SDL_DestroyTexture(texture_aigle);
	
	
	//Titre
	SDL_Surface * surface_titre = TTF_RenderText_Blended(police, "ZOZOR DEFENSE", couleur_titre);
	SDL_Rect pos_titre = {largeur_fenetre/2 -LARGEUR_TITRE/2,
						  100, 
						  LARGEUR_TITRE, 
						  HAUTEUR_TITRE };
	SDL_Texture * texture_titre = SDL_CreateTextureFromSurface(renderer, surface_titre);
	SDL_RenderCopy(renderer, texture_titre, NULL, &pos_titre);
	SDL_DestroyTexture(texture_titre);
	SDL_FreeSurface(surface_titre);
	
	
	
	
	
	//Refresh la fenetre avec le render present
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
	
	
	SDL_FreeSurface(image_aigle);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	TTF_CloseFont(police);
	TTF_Quit();
}
