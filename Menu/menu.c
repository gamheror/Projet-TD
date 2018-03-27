#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../all.h"
#include "../Towers/map_tower.h"
#include "../Mobs/mobs.h"
#include "../Chemin/liste.h" 

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


map_tower map;

int main(int argc ,char ** argv) {

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Surface * image = NULL;
	SDL_Surface * pSurface;
	TTF_Font * police = NULL;
	SDL_Texture * texture_image = NULL;
	
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
		//Initialisation de la police
	if( NULL == (police = TTF_OpenFont("../Polices/Ordinary.ttf", TAILLE_POLICE)) )
	{
		printf("Erreur de chargement de la police : %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}
	
	
	window = SDL_CreateWindow ("Is this gonna be a game?!",
								SDL_WINDOWPOS_UNDEFINED ,
								SDL_WINDOWPOS_UNDEFINED ,
								700,
								700,
								SDL_WINDOW_SHOWN );
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	image = IMG_Load("../Images/background.jpeg");
	SDL_Rect pos_image = {0, 0, 700, 700};
	SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, image);
	
	
	SDL_Color black = {255,255,255,255};
	SDL_Rect new_game = {70, 280, 560, 70};
	char str[16] = "Nouvelle partie";
	SDL_Rect pos_new_g = {	700/2-strlen(str)*TAILLE_POLICE/2,
							700/2-TAILLE_POLICE/2,
							strlen(str)*TAILLE_POLICE,
							TAILLE_POLICE};
	SDL_Rect fond_choix= {	70,
							700/2-TAILLE_POLICE/2 -5,
						  	700-140,
						  	TAILLE_POLICE +10};
	
	SDL_Texture * texture_new_g = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(police, str, black));
	SDL_RenderCopy(renderer, texture_new_g, NULL, &pos_new_g);
	
	
	pSurface =SDL_GetWindowSurface( window  );
	SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));
	SDL_RenderCopy(renderer, background, NULL, &pos_image);

	SDL_RenderFillRect(renderer, &fond_choix);

	SDL_RenderCopy(renderer, texture_new_g, NULL, &pos_new_g);

	
	int running = 1;
	int x, y;
	SDL_Event event;
	SDL_RenderPresent(renderer);

	while(running)
	{
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					{
						map = charger_map();
					}
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
				break;
				

		}
	}
	
	
/**********************************************************************************/
	/******	free et destruction	******/
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	TTF_CloseFont(police);
	TTF_Quit();
	
	//detruire_map_tower(&tower);
	//detruire_liste(&chemin);
}