#include "../all.h"
#include <unistd.h>
#include "SDL2/SDL.h"

char cr; //capte le retour chariot
map_tower map;
mobs_t * mobs[N][N];

void touches()
/*
	commandes temporaires
*/
{
	printf("\nLes commandes sont : \n");
	printf("h - afficher cette aide\n");
	printf("m - poser une tour mono\n");
	printf("a - poser une tour aoe\n");
	printf("e - ameliorer une tour\n");
	printf("double entrée pour passer l'étape\n");
	printf("q - quitter\n\n");
}

void action(char c)
/*
	suivant la commande temporaire envoyée,
	effectue l'action adequat
*/
{
	int x, y;
	
	switch(c)
	{
		case 'h':
			touches();
			break;
		case 'm':
		case 'a':
		case 'e':
			printf("Saisir les coordonnées de la tour [0;%d]\n", N);
			do
			{
				printf(">> x ");
				scanf("%d", &x);
			}while(x < 0 || x >= N);
			do
			{
				printf(">> y ");
				scanf("%d", &y);
			}while(y < 0 || y >= N);
			if(c == 'm')
				poser_tour(map, x, y, MONO);
			else if(c == 'a')
				poser_tour(map, x, y, AOE);
			else
				evoluer_tour(map, x, y);
			break;
	}
	
	scanf("%c", &cr); //capte le retour chariot
}

void spawn()
/*
	plusieurs mobs apparaisse aleatoirement
*/
{
	int x, y, nb = rand()%5;
	
	while(nb > 0)
	{
		do
		{
			x = rand()%N;
			y = rand()%N;
		}while(!case_vide(map, x, y));
		mobs[x][y] = creer_mobs();
		nb--;
	}
}

void affichage()
/*
	affiche les tours et les mobs + mise en forme
*/
{
	printf("\n---- GOLD %5d ----\n   ", GOLD);
	
	for(int i = 0; i < N; i++) printf("_");
	printf("\n");
	for(int i = 0; i < N; i++)
	{
		printf("%02d|", i);
		for(int j = 0; j < N; j++)
		{
			if( COORD(map, j, i) != NULL )
				COORD(map, j, i)->afficher( COORD(map, j, i) );
			else if( mobs[j][i] != NULL )
				printf("x");
			else
				printf(" ");
		}
		printf("|\n");
	}
	printf("   ");
	for(int i = 0; i < N; i++) printf("_");
	printf("\n");
	/* Affichage des coordonnées */
	printf("   ");
	for(int i = 0; i < N; i++)
		printf("%d", i/10);
	printf("\n   ");
	for(int i = 0; i < N; i++)
		printf("%d", i%10);
	printf("\n\n");
	/**/
}

/*
	Interface temporaire.
	
	Charge la sauvegarde ou créé une nouvelle partie suivant le choix de l'utilisateur.
	
	Le jeu se deroule en étape,
	une etape comprend :
		l'attaque des tours,
		le spawn de mobs aleatoirement sur la map,
		l'affichage des tours et des mobs,
		une commande du joueur.
	
	Tant que le jour n'a pas entré la commande 'q', le jeu est en pause
	
	Affichage :
		x	designe un ennemi
		B	designe le monument, c'est le batiment principal, capable de tirer sur plusieurs ennemi en meme temps
		M	designe une tour capable de tirer sur un seul ennemi à la fois
		A	designe une tour capable de tirer sur plusieurs ennemi en meme temps
	
	Le joueur peut poser 2 types de tours :
		'a' pour tour multiple
		'm' pour tour unique
	
	Le joueur peut aussi faire evoluer ses tour (batiment, unique et multiple),
	celles-ci gagne alors en degats, le nombre d'amelioration est limité à 5
*/

int main()
{
	char choix = ' ';
	GOLD = 1000;
	srand(time(NULL));
	
	for(int i = 0; i < N*N; i++)
		mobs[i%N][i/N] = NULL;
	
	
	if( SDL_Init(SDL_INIT_TIMER) != 0)
	{
		printf("Erreur d'initialisation de la SDL !\n");
		return EXIT_FAILURE;
	}
	
	
	printf("----------------------------------------------\n");
	printf("-------- Bienvenue sur Tour Defense ! --------\n");
	printf("----------------------------------------------\n\n");
	
	printf("Voulez-vous continuer la partie (o/n) ?\n");
	do
	{
		do
		{
			scanf("%c", &choix);
		}while(choix != 'o' && choix != 'n');
		scanf("%c", &cr); //capte le retour chariot
		
		switch(choix)
		{
			case 'o':
				printf("\n");
				map = charger_map();
				break;
			case 'n':
				map = init_mat_tower();
				break;
		}
	}while(choix != 'o' && choix != 'n');
	
	printf("\n");
	
	touches();
	
	int running = 1;
	SDL_Event event;
	while(running)
	{
		if(SDL_PollEvent(&event) && event.type == SDL_KEYUP)
			switch(event.key.keysym.sym)
			{
				//Touche echape = quitter le mode plein ecran si plein ecran sinon quitter la fenetre
				case SDLK_ESCAPE:
					running = 0;
					break;
				//F pour basculer le plein ecran
				case SDLK_p:
					sleep(10);
					break;
			}
		
		
		attaquer_tour(map, mobs);
		
		spawn();
		
		affichage();
		
		sleep(1);
	}
	
	detruire_map_tower(&map);
	
	for(int i = 0; i < N*N; i++)
		if(mobs[i%N][i/N] != NULL)
			detruire_mobs(&mobs[i%N][i/N]);
	
	printf("Au revoir !\n");
	
	SDL_Quit();
}
