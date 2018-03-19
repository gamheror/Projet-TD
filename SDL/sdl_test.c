#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define MARGE 5

void pause( ){
	
	
	int running = 1;
	while (running) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			
			switch(e.type) {
				case SDL_QUIT: running = 0;
				break;

			}
		}
	}
}



int main(int argc ,char ** argv) {
	int m_x, m_y;
	
	int mat[7][5];
	for (int i=0; i<5; i++){
		for (int j=0; j<7; j++){
			if (j%2 == 0)
				mat[j][i] = 1;
			else
				mat[j][i] = 0;
		}
	}
	for (int i=0; i<5; i++){
		for (int j=0; j<7; j++){
			printf("%d ",mat[j][i]);
		}
					printf("\n");

	}
	
			
	
//Le  pointeur  vers  la  fenetre
	SDL_Window* pWindow = NULL;
//Le  pointeur  vers  la  surface  incluse  dans  la  fenetre
	SDL_Surface *image = NULL, *pSurface = NULL, *zozor = NULL;
/*  Initialisation  simple  */
	if(SDL_Init(SDL_INIT_VIDEO) != 0 )   {
		fprintf(stdout ,"echec  de l’initialisation  de la SDL (%s)\n",SDL_GetError ());
		return -1;
	}

/*  Creation  de  la  fenetre  */
	pWindow = SDL_CreateWindow ("Is this gonna be a game?!",
								SDL_WINDOWPOS_UNDEFINED ,
								SDL_WINDOWPOS_UNDEFINED ,
								710,
								510,
								SDL_WINDOW_SHOWN );

	
	SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, 0);
	
	image = SDL_LoadBMP("lac_en_montagne.bmp");
	SDL_Rect pos_image = {5, 5, 700, 500};
	SDL_Texture *fond_t = SDL_CreateTextureFromSurface(renderer, image);
	
	zozor = SDL_LoadBMP("zozor.bmp");
	SDL_Rect rec_zozor = {500, 200, 100, 100};
	SDL_SetColorKey(zozor, SDL_TRUE, SDL_MapRGB(zozor->format, 0, 0, 255));
	SDL_Texture *zozor_t = SDL_CreateTextureFromSurface(renderer, zozor);

	if( pWindow )
	{
		/*int running = 1;
		while (running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				SDL_GetMouseState(&m_x,&m_y);
				rec_zozor.x = m_x;
				rec_zozor.y = m_y;
				pSurface =SDL_GetWindowSurface( pWindow  );
				SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));

				SDL_RenderCopy(renderer, fond_t, NULL, &pos_image);

				SDL_RenderCopy(renderer, zozor_t, NULL, &rec_zozor);

				SDL_RenderPresent(renderer);
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;

					}
				}
			}*/
		
		SDL_Event e;
		int running = 1;
		while (running)
		{
			pSurface =SDL_GetWindowSurface( pWindow  );
			SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));

			SDL_RenderCopy(renderer, fond_t, NULL, &pos_image);
			SDL_GetMouseState(&m_x,&m_y);
/*				if (SDL_MouseButtonEvent(SDL_MOUSEBUTTONUP,*/
/*										 NULL,*/
/*										 pWindow,*/
/*										 SLD_TOUCH_MOUSEID,*/
/*										 SDL_BUTTON_LEFT,*/
/*										 1,*/
/*										 m_x,*/
/*										 m_y))*/
/*				{*/
				rec_zozor.x = m_x;
				rec_zozor.y = m_y;
/*				}*/
			
			SDL_RenderCopy(renderer, zozor_t, NULL, &rec_zozor);

			SDL_RenderPresent(renderer);
			
			
			
			SDL_PollEvent(&e);
			switch(e.type)
			{
				case SDL_QUIT: running = 0;
				break;

			}
		}
		
		
		
		
		
			//On  recupere  la  surface  de la  fenetre
		pSurface = SDL_GetWindowSurface( pWindow  );

		SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));
		SDL_RenderCopy(renderer, fond_t, NULL, &pos_image);

		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 7; j++){
				if (mat[j][i] == 0){
					rec_zozor.x = j*100 + MARGE;
					rec_zozor.y = i*100 + MARGE;
					SDL_RenderCopy(renderer, zozor_t, NULL, &rec_zozor);
				}
			}
		}


		//SDL_RenderCopy(renderer, zozor_t, NULL, &rec_zozor);

		SDL_RenderPresent(renderer);
		pause();	
	}
	else{
		fprintf(stderr ,"Erreur  de  creation  de la  fenetre: %s\n",SDL_GetError ());
	}
// Destruction  de  la  fenetre
	SDL_DestroyTexture(zozor_t);
	SDL_FreeSurface(image);
	SDL_FreeSurface(zozor);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(pWindow );
	SDL_Quit();
	return 0;
}
