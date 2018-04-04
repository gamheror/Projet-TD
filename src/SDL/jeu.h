#ifndef _jeu_h_
#define _jeu_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../all.h"
#include "../Towers/map_tower.h"
#include "../Chemin/liste.h"

/* print dans ecran */
void print_menu_haut();
void print_menu_gauche();
void print_sol();
void print_chemin(liste_t *);
void print_tours(map_tower, liste_t *);

/* print dans le renderer */
void print_gold(SDL_Renderer *);
void print_mob(SDL_Renderer *, mobs_t *[]);
void print_avancement_vague(SDL_Renderer *, int, int);

void init_plateau(map_tower, liste_t *); //remplie la surface ecran avec nb_vague, menus, sol, tours et chemin
void update_plateau(SDL_Renderer *, mobs_t *[], int, int); //rafranchi renderer avec la surface ecran

/* modifs de ecran */
void ajouter_tour_plateau(map_tower, liste_t *, type_tour type, int x, int y);
void evoluer_tour_plateau(map_tower, int x, int y);
void print_nb_vague(int);

/* positions de tuiles pour poser des tours */
SDL_Rect * get_tuile_aoe();
SDL_Rect * get_tuile_mono();

#endif
