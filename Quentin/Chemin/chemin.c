#include "../all.h"

int main()
{
	liste_t * liste;
	elem_t * elem;
	mobs_t * mobs;

	liste = initialisation();
	afficher_liste(liste);

	int mat[5][5] = {{0}};

	liste_debut(liste);

	/*for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			elem = element_courant(liste);

			if(i == elem->x && j == elem->y)	
				mat[i][j] == 1;

			printf("%d", mat[i][j]);

			liste_suivant(liste);
			
			
		}

		printf("\n");
	}*/
	
	creer_mobs(elem);
	/*changement_coord(mobs);*/
	afficher_mobs(mobs);
}
