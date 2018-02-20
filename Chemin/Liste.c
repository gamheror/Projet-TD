#include <stdlib.h>
#include <stdio.h>

Liste *initialisation()
{
	Liste *liste = malloc(sizeof(*liste));
	Element *element = malloc(sizeof(*element));

	if (liste == NULL || element == NULL)
	{
		exit(EXIT_FAILURE);
	}


	element->nombre = 0;
	element->suivant = NULL;
	liste->premier = element;


	return liste;
}

void insertion(Liste *liste, int nvNombre)
{
	int x;
	int y;

	FILE* fichier = NULL;
	fichier = fopen("Chemin/chemin.txt", "r");

	/*Création d'un nouvel element*/
	

	while(!feof(fichier))
	{
		liste_t *nouveau = malloc(sizeof(*nouveau));
		fscanf("%d %d", &(nouveau->)x, &(nouveau->)y);
		nouveau->suivant;
	}

	
	
	
}