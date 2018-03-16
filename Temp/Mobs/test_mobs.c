#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../all.h"

int main()
{
	srand(time(NULL));

	elem_t * elem;
	liste_t * liste = initialisation();
	mobs_t * mobs;
	
	afficher_liste(liste);
	mobs = creer_mobs(elem);
	afficher_mobs(mobs);
}
