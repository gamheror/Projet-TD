#ifndef _menu_h_
#define _menu_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../all.h"

/* print dans renderer */
void print_image_fond(SDL_Renderer *);
void print_titre(SDL_Renderer *);
void print_buttons(SDL_Renderer *);
void print_footer(SDL_Renderer *);

/* retournent les rects des 2 bouttons */
SDL_Rect * get_rect_new_game();
SDL_Rect * get_rect_load_game();

#endif
