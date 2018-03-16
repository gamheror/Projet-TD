#include "Liste.h"

int main()
{
	elem_t * elem;
	liste_t * liste;
	mobs_t * mobs;

	liste= initialisation();
	mobs = creer_mobs(elem);
	afficher_liste(liste);
}
