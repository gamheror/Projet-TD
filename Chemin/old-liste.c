#include "liste.h"

elem_t * initialisation()
{
	liste_t * liste = malloc(sizeof(liste_t));
	elem_t * elem = malloc(sizeof(elem_t));

	if (elem == NULL || liste == NULL)
	{
		exit(EXIT_FAILURE);
	}

	FILE * fichier = NULL;
	fichier = fopen("chemin.txt", "r");

	while(!feof(fichier))
	{
		liste_t * liste = malloc(sizeof(liste_t));
		fscanf(fichier,"%d %d", (&liste->x), (&liste->y));
		liste->suivant = elem->premier;
		elem->premier = liste;
	}

	fclose(fichier);
	return elem;
}

void insertion(elem_t * elem)
{
	int x;
	int y;

	FILE * fichier = NULL;
	fichier = fopen("chemin.txt", "r");

	/*Création d'un nouvel element*/	
	while(!feof(fichier))
	{
		liste_t * liste = malloc(sizeof(liste_t));
		fscanf(fichier,"%d %d", (&liste->x), (&liste->y));
		liste->suivant = elem->premier;
		elem->premier = liste;
	}
	
	fclose(fichier);
}

void afficher_liste(elem_t * elem)
{
	liste_t * liste = elem->premier;
	
	while(elem != NULL)
	{
		printf("{%d %d}\n", liste->x, liste->y);
		liste = liste->suivant;
	}
	printf("FIN");
}