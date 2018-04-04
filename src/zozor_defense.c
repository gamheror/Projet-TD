#include <time.h>
 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
 
#include "all.h"
#include "include_fichiers.h"
 
 
int main()
{
    SDL_Window * window;
    SDL_Renderer * renderer;
 
    map_tower map;
    liste_t * chemin;
     
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
    if( NULL == (window = SDL_CreateWindow ("ZOZOR DEFENSE",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            LARGEUR_FEN,
                                            HAUTEUR_FEN,
                                            SDL_WINDOW_SHOWN ) ) )
    {
        printf("Erreur a la création de la fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if( NULL == (renderer = SDL_CreateRenderer(window, -1, 0)) )
    {
        printf("Erreur a la creation du renderer : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
	/* Affichage du menu */
    print_image_fond(renderer);
    print_titre(renderer);
    print_buttons(renderer);
    print_footer(renderer);
 
	SDL_RenderPresent(renderer);
     
     
    SDL_Event event;
    int running = 1,
        clique = 0;
    while(running && !clique) //boucle menu
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
			case SDL_QUIT:								// Dans le cas où on appuie sur la croix
                running = 0;							// Fermeture de la SDL
                break;
            case SDL_KEYDOWN:							// Dans le cas où on appuie sur une touche
                if(event.key.keysym.sym == SDLK_ESCAPE) // Si c'est la touche echap
                    running = 0;						// Fermeture de la SDL
                break;
            case SDL_MOUSEBUTTONUP:						// Dans le cas où on relache un clique souris
                if (event.button.button == SDL_BUTTON_LEFT && !clique)	// Si c'est un clique gauche et qu'on ne clique plus
                {
                    SDL_Point pointeur;									// Structure de coordonnée de souris
                    SDL_GetMouseState(&pointeur.x, &pointeur.y);		// On attribut les coordonnées de la souris à pointeur
                    if( SDL_PointInRect(&pointeur, get_rect_new_game()) ) // Si il est sur le carré "Nouvelle partie"
                    {
						/*On initialise le chemin et la matrice, on passe la variable clique à un et on fait une vérification visuel avec un message dans le terminal*/
                        chemin = liste_init();
                        map = init_mat_tower(chemin);					
                        clique = 1;
                        printf("initialisation du jeu !\n");
                    }
                    if( SDL_PointInRect(&pointeur, get_rect_load_game()) )
                    {
						/*On charge la matrice, on initialise le chemin et on passe la variable clique à un et on fait une vérification visuel avec un message dans le terminal*/
                        chemin = liste_init();
                        map = charger_map();
                        clique = 1;
                        printf("chargement de la sauvegarde !\n");
                    }
                }
        }
         
         
         
        if(clique) // Si on a cliqué sur l'une des cases
        {
            printf("Le jeu est pret à démarrer !\n");
			
			/* Initialisation des parametres pour une partie */
			GOLD = 1000; 
            srand(time(NULL));
            mobs_t * mob[N];
            int temps = 0, num_vague = 1, nb_mobs = 20, nb_arrives = 0, nb_tues = 0;
     
            for(int i = 0;  i < N; i++)
                mob[i] = NULL;
            if(!chemin)
            {
                printf("Erreur initialisation de la liste !\n");
                return EXIT_FAILURE;
            }
            if(map == NULL)
            {
                printf("Erreur chargement tours !\n");
                return EXIT_FAILURE;
            }
     		
			/* Initialisation de l'affichage */
			
            init_plateau(map, chemin);  
             
            SDL_Surface * tuile_aoe = IMG_Load("ressources/Images/AOE.png"),
                        * tuile_mono = IMG_Load("ressources/Images/MONO.png");
            SDL_Texture * texture_aoe = SDL_CreateTextureFromSurface(renderer, tuile_aoe),
                        * texture_mono = SDL_CreateTextureFromSurface(renderer, tuile_mono);
            SDL_Rect pos_drag_n_drop = {0, 0, TAILLE_IMAGE, TAILLE_IMAGE};
            SDL_FreeSurface(tuile_aoe);
            SDL_FreeSurface(tuile_mono);
             
            int drag_n_drop = 0;
            type_tour type_tour_select = -1;
            
			while(clique) //Boucle tant que clique ne repasse pas a 0
            {
         
                SDL_PollEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:			// Dans le cas où on appuie sur la croix
                        clique = 0;			// Affichage du menu 
                        break;
                    case SDL_KEYDOWN:								// Dans le cas où on appuie sur une touche
                        if(event.key.keysym.sym == SDLK_ESCAPE)		// Si c'est la touche echap
                            clique = 0;								// Affichage du menu 
                        break;
                    case SDL_MOUSEBUTTONDOWN:										// Dans le cas où on appuie sur un clique souris
                        if (event.button.button == SDL_BUTTON_LEFT && !drag_n_drop) // Si c'est le clique gauche et que l'on fait l'action de glisser
                        {
                            drag_n_drop = 1;
                            SDL_Point pointeur;
                            SDL_GetMouseState(&pointeur.x, &pointeur.y);
							/* Ici on fait affiché au niveau de la souris l'image de la tuile choisie */
                            if(SDL_PointInRect(&pointeur, get_tuile_aoe()))			
                                type_tour_select = AOE;
                            else if(SDL_PointInRect(&pointeur, get_tuile_mono()))
                                type_tour_select = MONO;
							
                        }
                        SDL_Delay(50); // anti-rebond
                        break;
                    case SDL_MOUSEBUTTONUP:											// Dans le cas où on relache un clique souris
                        if (event.button.button == SDL_BUTTON_LEFT && drag_n_drop)	// Si c'est le clique gauche et que l'on ne fait pas l'action de glisser
                        {
                            drag_n_drop = 0;
                            SDL_Point pointeur;
                            SDL_GetMouseState(&pointeur.x, &pointeur.y);
							/*l'endroit ou l'on va poser la tour sera déterminé par les coordonnées de la souris à ce moment là*/
                            pointeur.x = (pointeur.x -MARGE_GAUCHE)/TAILLE_IMAGE;
                            pointeur.y = (pointeur.y -MARGE_HAUT)/TAILLE_IMAGE;
                            ajouter_tour_plateau(map, chemin, type_tour_select, pointeur.x, pointeur.y);
                            type_tour_select = -1;
                        }
                        SDL_Delay(50); // anti-rebond
                        break;
                }
         		
				/*Ici on résout les actions d'un tour normal. Les tours attaquent les monstres*/
                attaquer_tour(map, mob, temps, &nb_tues);
                deplacer_mob(mob, temps);
                if(nb_arrives < nb_mobs)
                    apparaitre(mob, chemin, temps, &nb_arrives, num_vague);
         
                update_plateau(renderer, mob, nb_tues, nb_mobs);
                 
                if(drag_n_drop)
                {
                    SDL_GetMouseState(&pos_drag_n_drop.x, &pos_drag_n_drop.y);
                    if(type_tour_select == AOE)
                        SDL_RenderCopy(renderer, texture_aoe, NULL, &pos_drag_n_drop);
                    else if(type_tour_select == MONO)
                        SDL_RenderCopy(renderer, texture_mono, NULL, &pos_drag_n_drop);
                    SDL_RenderPresent(renderer);
                }
                 
         
                if(nb_tues == nb_mobs) 			// A la fin d'une vague
                {
                    nb_mobs += 10; 				// Augmentation de 10 du nombres de monstres pour la prochaine vague
                    nb_tues = nb_arrives = 0;	// Remise du nombre de monstres abattus à 0
                    num_vague++;				// Augmentation du numéro de la vague de 1
                    print_nb_vague(num_vague);	// Actualisation du numéro de la vague sur l'ecran
                }
         
                if(monu_est_detruit() || num_vague > 9) // Si le monument est detruit ou que l'on dépasse le nombre de vague maximale
                    clique = 0;							// On repasse sur l'ecran du menu
     
     
     
                SDL_Delay(1);
                temps++;
            }
            //affiche le menu
            print_image_fond(renderer);
            print_titre(renderer);
            print_buttons(renderer);
            print_footer(renderer);
            SDL_RenderPresent(renderer);
            printf("retour menu\n");
             
            detruire_map_tower(&map);
            detruire_liste(&chemin);
        }
         
    }
     
     
     
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
}
