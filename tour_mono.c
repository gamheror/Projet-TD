#include <stdio.h>
#include <stdlib.h>

#include "tour_mono.h"

tour_mono_t * creer_tour_mono(  )
{
	tour_mono_t * mono = (tour_mono_t*)creer_tour(); //Utilise la fonction de creation d'une tour simple
	mono = realloc(mono, sizeof(tour_mono_t)); //Realloc pour adapter la taille memoire allouee de tour vers tour_aoe
	
	mono->ennemi = NULL;
	
	mono->detruire = detruire_tour_mono;
	
	return mono;
}

void afficher_tour_mono( tour_mono_t * mono )
{
	if( existe_tour(mono) )
	{
		printf("{MONO ");
		afficher_tour( (tour_t *)mono );
		printf(" }");
	}
	else
		printf("NULL");
}

void detruire_tour_mono( tour_mono_t ** mono )
{
	if( existe_tour(*mono) )
	{
		free(*mono);
		*mono = NULL;
	}
}