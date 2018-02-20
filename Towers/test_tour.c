#include <stdio.h>
#include <stdlib.h>

#include "tours.h"

int main()
{
	tour_aoe_t * aoe = NULL;
	tour_mono_t * mono = NULL;
	
	printf("Tour aoe existe ? %d\n", tour_existe(aoe) );
	printf("Tour mono existe ? %d\n", tour_existe(mono) );
	
	aoe = creer_tour_aoe(0,0);
	mono = creer_tour_mono(0,0);
	
	printf("Tour aoe existe ? %d\n", tour_existe(aoe) );
	printf("Tour mono existe ? %d\n", tour_existe(mono) );
	
	afficher_tour_aoe(aoe);
	printf("\n");
	afficher_tour_mono(mono);
	printf("\n");
	
	aoe->detruire(&aoe);
	mono->detruire(&mono);
}
