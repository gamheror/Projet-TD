#ifndef _MOB_H_
#define _MOB_H_

#include <stdlib.h>
#include <stdio.h>

#include "../all.h"
#include "mobs.h"
#include "../Chemin/liste.h"

/**
 * \enum mobs_t
 * \brief Strucutre contenant les caractéristiques des mobs.
 */

typedef struct mobs_s
{
	int attaque; /*!< Variable pour l'attaque */
	int life; /*!< variable pour la vie du mob */
	int v_deplacement; /*!< Varible pour la vitesse de déplacement des mobs : utilisé pour le déplacement*/
	char caract; /*!< Variable pour le caractère du mobs : Utilisé pour l'affichage des mobs afin de les reconnaitre */
	
	elem_t * pos;  /*!< Pointeur sur la structure elem_t du fichier liste.h permetant d'obtenir le contenu de l'élément*/

	void (*detruire)(struct mobs_s **);  /*!< Pointeur sur la fonction detruire pour pouvoir être utilisée par d'autre fonction d'autre fichier */
	
} mobs_t;

mobs_t * creer_mobs_normal();
mobs_t * creer_mobs_tank();
mobs_t * creer_mobs_degat();
mobs_t * creer_mobs_boss();

void afficher_mobs(mobs_t * );

void get_mob_pos(mobs_t *, int *, int *);

void deplacer_mob(mobs_t *[], int);
void apparaitre(mobs_t *[], liste_t *, int, int *, int); 


void perte_vie (mobs_t ** , int);

void detruire_mobs(mobs_t **);

void attaque_monum(mobs_t *);

void creer_vague();

#endif
