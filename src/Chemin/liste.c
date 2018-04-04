#include "liste.h"

/**
 * \fn liste_t * liste_init()
 * \brief Fonction qui va initialiser la liste à NULL dans un premier 
 *	    temps puis insérer des valeurs grâce à la fonction insertion.
 * 
 * \return la liste une fois créée
 */

liste_t * liste_init()
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

/**
 * \fn insertion(liste_t * liste)
 * \brief Fonction d'insertion de valeur pour la liste à partir d'un fichier texte
	    créé au préalable
 *
 * \param pointeur sur la structure liste_t
 */

void insertion(liste_t * liste)
{
	FILE * fichier = fopen("ressources/chemin.txt", "r");
	
	if(fichier == NULL)
	{
		printf("Erreur lors de l'ouverture du fichier d'initialisation de la liste\n");
		return;
	}
	
	elem_t * elem;
	
	int x, y;
	fscanf(fichier,"%d %d", &x, &y); //lit fichier
		
	elem = malloc(sizeof(elem)); //créé element
	elem->suivant = NULL;
	elem->x = x;
	elem->y = y;

	liste->courant = elem; //insere le premier element
	liste->premier = elem; //definie premier element
	/*Création d'un nouvel element */
	while(!feof(fichier))
	{
		
		fscanf(fichier,"%d %d", &x, &y); //lit fichier
		
		elem = malloc(sizeof(elem)); //créé element
		elem->suivant = NULL;
		elem->x = x;
		elem->y = y;
		
		liste->courant->suivant = elem; //insere a la fin de la liste
		liste->courant = liste->courant->suivant; //deplace sur le nouvel element
	}
	
	fclose(fichier);
	
	detruire_dernier_elem(&liste); //bug d'insertion dans la liste : le dernier et avant-dernier element sont les memes
}

/**
 * \fn liste_vide(liste_t * liste)
 * \brief Fonction qui vérifie si la liste est vide
 *
 * \param pointeur sur la structure liste_t
 * \return 0 si la liste est vide.
 */

int liste_vide(liste_t * liste)
{
	return liste->premier == NULL;
}

/**
 * \fn fin_liste (liste_t * liste)
 * \brief Fonction qui vérifie si on est à la fin de la liste
 *
 * \param pointeur sur la structure liste_t
 * \return 0 si la liste est fini
 */

int fin_liste(liste_t * liste)
{
	return liste->courant == NULL;
}

/**
 * \fn afficher_liste(liste_t * liste)
 * \brief Fonction qui affiche les éléments de la liste
 *
 * \param pointeur sur la structure liste_t
 */

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

/**
 * \fn liste_debut(liste_t * liste)
 * \brief Fonction qui place le "curseur" sur l'élément courant de la liste
 *
 * \param pointeur sur la structure liste_t
 * \return l'élément courant de la liste
 */

void liste_debut(liste_t * liste)
{
	liste->courant = liste->premier;
}

/**
 * \fn liste_suivant(liste_t * liste)
 * \brief Fonction qui place le "curseur" sur l'élément suivant de la liste
 *
 * \param pointeur sur la structure liste_t
 */

void liste_suivant(liste_t * liste)
{
	liste->courant = liste->courant->suivant;
}

/**
 * \fn liste_fin(liste_t * liste)
 * \brief Fonction qui place le "curseur" sur le dernier élément de la liste
 *
 * \param pointeur sur la structure liste_t
 */

void liste_fin(liste_t * liste)
{
	liste_debut(liste);
	while(liste->courant->suivant != NULL)
		liste_suivant(liste);
}

/**
 * \fn elem_t * element_courant(liste_t * liste)
 * \brief Fonction retourne l'élément courant
 *
 * \param pointeur sur la structure liste_t
 */

elem_t * element_courant(liste_t * liste)
{
	return liste->courant;
}

/**
 * \fn element_existe(elem_t * elem)
 * \brief Fonction qui vérifie que l'élément en paramètre existe
 *
 * \param pointeur sur la structure elem_t
 * \return 0 si l'élément est différent de NULL
 */

int elememt_existe(elem_t * elem)
{
	return elem != NULL;
}

/**
 * \fn afficher_element(elem_t * elem)
 * \brief Fonction qui affiche l'élément en paramètre
 *
 * \param pointeur sur la structure elem_t
 */

void afficher_element(elem_t * elem)
{
	if(elem != NULL)
		printf("{%d %d}", elem->x, elem->y);
}

/**
 * \fn detruire_liste(liste_t ** liste)
 * \brief Fonction qui supprime des éléments de la liste
 *	    et libère la mémoire une fois la liste vide
 *
 * \param double pointeur sur la structure liste_t
 */

void detruire_liste(liste_t ** liste)
{
	if((*liste) != NULL)
	{	
		liste_debut(*liste);
		elem_t * elem = (*liste)->courant;
		while(elem != NULL)
		{
			liste_suivant(*liste);
			free(elem);
			elem = (*liste)->courant;
		}
		
		free(*liste);
		*liste = NULL;
	}
}

/**
 * \fn detruire_liste(liste_t ** liste)
 * \brief Fonction qui supprime le dernier élément de la liste
 *	   
 * \param double pointeur sur la structure liste_t
 */

void detruire_dernier_elem(liste_t ** liste)
{
	if(*liste != NULL)
	{
		liste_debut(*liste); //va debut de la liste
		elem_t * elem = NULL;
		while((*liste)->courant->suivant != NULL) //parcours liste jusqu'au dernier
		{
			elem = element_courant(*liste);
			liste_suivant(*liste);
		}
		
		free((*liste)->courant); //libere le dernier element
		if(elem != NULL)
		{
			elem->suivant = NULL;
			(*liste)->courant  = elem;
		}
	}
}






