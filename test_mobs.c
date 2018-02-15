#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mobs.h"

int main()
{
	srand(time(NULL));
	
	mobs_t * mobs;
	
	mobs = creer_mobs();
	afficher_mobs(mobs);
	perte_vie(&mobs,rand()%400);
	afficher_mobs(mobs);

}
