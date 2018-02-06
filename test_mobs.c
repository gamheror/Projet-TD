#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mobs.h"

int main()
{
	srand(time(NULL));
	
	mobs_t * mobs;
	
	mobs = mobs_creer();
	afficher_mobs(mobs);
	detruire_mobs(&mobs);
}