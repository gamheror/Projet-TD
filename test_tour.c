#include <stdio.h>
#include <stdlib.h>

#include "tours.h"

int main()
{
	tour_aoe_t * aoe = NULL;
	tour_mono_t * mono = NULL;
	
	printf("Tour aoe existe ? %d\n", existe_tour(aoe) );
	printf("Tour mono existe ? %d\n", existe_tour(mono) );
	
	aoe = creer_tour_aoe();
	mono = creer_tour_mono();
	
	printf("Tour aoe existe ? %d\n", existe_tour(aoe) );
	printf("Tour mono existe ? %d\n", existe_tour(mono) );
	
	afficher_tour_aoe(aoe);
	printf("\n");
	afficher_tour_mono(mono);
	printf("\n");
	
	aoe->detruire(&aoe);
	mono->detruire(&mono);
}
