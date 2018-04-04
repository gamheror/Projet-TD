#include "menu.h"

SDL_Rect new_game = {	70,
						700/2-TAILLE_POLICE/2 -5,
						700-140,
						TAILLE_POLICE +10},
		 load_game = {	70,
						800/2-TAILLE_POLICE/2 -5,
						700-140,
						TAILLE_POLICE +10};

/**
* \fn print_image_fond(SDL_Renderer * renderer)
* \brief	affiche le background 
*
* \param 	le renderer de la fenetre
**/
void print_image_fond(SDL_Renderer * renderer)
{
	SDL_Surface * surface_background = IMG_Load("ressources/Images/old_map.jpeg");
	
	SDL_Texture * texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);
	
	SDL_RenderCopy(renderer, texture_background, NULL, NULL);
	
	SDL_FreeSurface(surface_background);
	SDL_DestroyTexture(texture_background);
}

/**
* \fn print_titre(SDL_Renderer * renderer)
* \brief	affiche le titre
*
* \param 	le renderer de la fenetre
**/
void print_titre(SDL_Renderer * renderer)
{
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	char str[] = "ZOZOR DEFENSE";
	
	SDL_Rect pos_titre = {	LARGEUR_FEN/2 -strlen(str)*TAILLE_TITRE/2,
							HAUTEUR_FEN/6 -TAILLE_TITRE/2,
							strlen(str)*TAILLE_TITRE,
							TAILLE_TITRE},
			 fond_titre = {	LARGEUR_FEN/20,
			 				HAUTEUR_FEN/6 -TAILLE_TITRE/2 -5,
			 				LARGEUR_FEN*9/10,
			 				TAILLE_TITRE +10};
	
	SDL_Surface * surface_titre = TTF_RenderText_Blended(police, str, couleur_blanche);
	
	SDL_Texture * texture_titre = SDL_CreateTextureFromSurface(renderer, surface_titre);
	
	SDL_RenderFillRect(renderer, &fond_titre);
	
	SDL_RenderCopy(renderer, texture_titre, NULL, &pos_titre);
	
	SDL_FreeSurface(surface_titre);
	SDL_DestroyTexture(texture_titre);
	TTF_CloseFont(police);
}

/**
* \fn print_boutton(SDL_Renderer * renderer)
* \brief	copie dans le renderer les buttons de chargement et nouvelle partie
*
* \param 	le renderer de la fenetre
**/
void print_buttons(SDL_Renderer * renderer)
{
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	char str1[] = "Nouvelle partie",
		 str2[] = "Charger une partie";

	SDL_Rect pos_txt_new_g = {	700/2-strlen(str1)*TAILLE_POLICE/2,
								700/2-TAILLE_POLICE/2,
								strlen(str1)*TAILLE_POLICE,
								TAILLE_POLICE},
			 pos_txt_load_g = {	700/2-strlen(str2)*TAILLE_POLICE/2,
								800/2-TAILLE_POLICE/2,
								strlen(str2)*TAILLE_POLICE,
								TAILLE_POLICE},
			 fond_new= {70,
						700/2-TAILLE_POLICE/2 -5,
						700-140,
						TAILLE_POLICE +10},
			 fond_load= {70,
						 800/2-TAILLE_POLICE/2 -5,
						 700-140,
						 TAILLE_POLICE +10};
	
	SDL_Surface * surface_txt_new_game = TTF_RenderText_Blended(police, str1, couleur_blanche),
				* surface_txt_load_game = TTF_RenderText_Blended(police, str2, couleur_blanche);
	
	SDL_Texture * texture_new_g = SDL_CreateTextureFromSurface(renderer, surface_txt_new_game),
				* texture_load_g = SDL_CreateTextureFromSurface(renderer, surface_txt_load_game);
	
	SDL_RenderFillRect(renderer, &fond_load);
	SDL_RenderFillRect(renderer, &fond_new);
	
	SDL_RenderCopy(renderer, texture_new_g, NULL, &pos_txt_new_g);
	SDL_RenderCopy(renderer, texture_load_g, NULL, &pos_txt_load_g);
	
	SDL_FreeSurface(surface_txt_load_game);
	SDL_FreeSurface(surface_txt_new_game);
	SDL_DestroyTexture(texture_load_g);
	SDL_DestroyTexture(texture_new_g);
	TTF_CloseFont(police);
}

/**
* \fn print_boutton(SDL_Renderer * renderer)
* \brief	copie dans le renderer le footer
*
* \param 	le renderer de la fenetre
**/
void print_footer(SDL_Renderer * renderer)
{
	TTF_Font * police = TTF_OpenFont("ressources/Polices/Ordinary.ttf", TAILLE_POLICE);
	SDL_Color couleur_blanche = {255, 255, 255, 255};
	
	char str[] = "Un jeu de",
		 a[] = "Dorso-Martin Antoine",
		 p[] = "Durand Pierre",
		 t[] = "Edel Thomas",
		 q[] = "Goncalves Quentin";
	
	SDL_Surface * surface_footer = SDL_CreateRGBSurface(0, LARGEUR_FEN*9/10, TAILLE_TXT_FOOTER*5 +30, 32, 0, 0, 0, 0),
				* surface_str = TTF_RenderText_Blended(police, str, couleur_blanche),
				* surface_a = TTF_RenderText_Blended(police, a, couleur_blanche),
				* surface_p = TTF_RenderText_Blended(police, p, couleur_blanche),
				* surface_t = TTF_RenderText_Blended(police, t, couleur_blanche),
				* surface_q = TTF_RenderText_Blended(police, q, couleur_blanche);
	
	SDL_Rect pos_footer = {	LARGEUR_FEN/20,
							HAUTEUR_FEN*9/10 -(TAILLE_TXT_FOOTER*5+30)/2,
							LARGEUR_FEN*9/10,
							TAILLE_TXT_FOOTER*5+30},
			 pos_str = {LARGEUR_FEN*9/10/2 -strlen(str)*TAILLE_TXT_FOOTER/2,
			 			5,
			 			strlen(str)*TAILLE_TXT_FOOTER,
			 			TAILLE_TXT_FOOTER},
			 pos_a = {	LARGEUR_FEN*9/10/2 -strlen(a)*TAILLE_TXT_FOOTER/2,
			 			TAILLE_TXT_FOOTER +10,
			 			strlen(a)*TAILLE_TXT_FOOTER,
			 			TAILLE_TXT_FOOTER},
			 pos_p = {	LARGEUR_FEN*9/10/2 -strlen(p)*TAILLE_TXT_FOOTER/2,
			 			TAILLE_TXT_FOOTER*2 +15,
			 			strlen(p)*TAILLE_TXT_FOOTER,
			 			TAILLE_TXT_FOOTER},
			 pos_t = {	LARGEUR_FEN*9/10/2 -strlen(t)*TAILLE_TXT_FOOTER/2,
			 			TAILLE_TXT_FOOTER*3 +20,
			 			strlen(t)*TAILLE_TXT_FOOTER,
			 			TAILLE_TXT_FOOTER},
			 pos_q = {	LARGEUR_FEN*9/10/2 -strlen(q)*TAILLE_TXT_FOOTER/2,
			 			TAILLE_TXT_FOOTER*4 +25,
			 			strlen(q)*TAILLE_TXT_FOOTER,
			 			TAILLE_TXT_FOOTER};
	
	SDL_BlitScaled(surface_str, NULL, surface_footer, &pos_str);
	SDL_BlitScaled(surface_a, NULL, surface_footer, &pos_a);
	SDL_BlitScaled(surface_p, NULL, surface_footer, &pos_p);
	SDL_BlitScaled(surface_t, NULL, surface_footer, &pos_t);
	SDL_BlitScaled(surface_q, NULL, surface_footer, &pos_q);
	
	SDL_Texture * texture_footer = SDL_CreateTextureFromSurface(renderer, surface_footer);
	
	SDL_RenderCopy(renderer, texture_footer, NULL, &pos_footer);
	
	SDL_FreeSurface(surface_footer);
	SDL_FreeSurface(surface_str);
	SDL_FreeSurface(surface_a);
	SDL_FreeSurface(surface_p);
	SDL_FreeSurface(surface_t);
	SDL_FreeSurface(surface_q);
	TTF_CloseFont(police);
}

/* Permet de récuperer l'adresse des buttons pour une nouvelle partie ou pour charger la sauvegarde*/
SDL_Rect * get_rect_new_game()
{
	return &new_game;
}

SDL_Rect * get_rect_load_game()
{
	return &load_game;
}
