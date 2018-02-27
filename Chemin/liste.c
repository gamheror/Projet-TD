#include "liste.h"

liste_t * initialisation()
{
	liste_t * liste = malloc(sizeof(liste));
	
	if( liste == NULL )
	{
		printf("Erreur lors de la création de la liste\n");
		return liste;
	}
	
	liste->premier = liste->courant = NULL;
	
	insertion(liste);
	
	return liste;
}

void insertion(liste_t * liste)
{
	FILE * fichier = fopen("chemin.txt", "r");
	
	if(fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier d'initialisation de la liste\n");
		return;
	}
	
	/* Créé le 1er élément sur lequel pointera liste->premier */
	elem_t * elem = malloc(sizeof(elem));
	elem->suivant = NULL;
	fscanf(fichier,"%d %d", &elem->x, &elem->y);
	liste->premier = liste->courant = elem;
	
	/*Création d'un nouvel element*/	
	while(!feof(fichier))
	{
		elem = malloc(sizeof(elem));
		elem->suivant = NULL;
		fscanf(fichier,"%d %d", (&elem->x), (&elem->y));
		liste->courant->suivant = elem;
		liste->courant = elem;
	}
	
	fclose(fichier);
}

int liste_vide(liste_t * liste)
{
	return liste->premier == NULL;
}

int fin_liste(liste_t * liste)
{
	return liste->courant == NULL;
}

void afficher_liste(liste_t * liste)
{
	if(!liste_vide(liste))
	{
		liste_debut(liste);
		
		while( elememt_existe(element_courant(liste)) )
		{
			afficher_element(element_courant(liste));
			printf("\n");
			liste_suivant(liste);
		}
	}
	else
		printf("Liste vide !\n");
}

void liste_debut(liste_t * liste)
{
	liste->courant = liste->premier;
}

void liste_suivant(liste_t * liste)
{
	liste->courant = liste->courant->suivant;
}

elem_t * element_courant(liste_t * liste)
{
	return liste->courant;
}



int elememt_existe(elem_t * elem)
{
	return elem != NULL;
}

void afficher_element(elem_t * elem)
{
	if(elem != NULL)
		printf("{%d %d}", elem->x, elem->y);
}
