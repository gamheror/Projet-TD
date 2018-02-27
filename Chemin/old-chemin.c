#include "../Mobs/mobs.h"

int main()
{
	elem_t *elem;
	mobs_t * mobs;
	
	
	elem = initialisation();
	/*afficher_liste(elem);*/

	mobs = creer_mobs(elem);
	afficher_mobs(mobs);
}