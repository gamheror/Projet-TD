#ifndef _ALL_H_
#define _ALL_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Towers/tours.h"
#include "Mobs/mobs.h"

/*-------- Constante --------*/

/* Matrices */
#define N 20

/* Ennemis */
#define VIE_MOB			200
#define V_DEP_MOB		10
#define DEGAT_MOB		15
#define NB_MOB			5
#define DROP_MOB_MIN	20
#define DROP_MOB_MAX	150

/* Tours */
#define NIVEAU_MAX_TOUR		5

#define DEGATS_TOUR_MONO	150
#define DEGATS_TOUR_AOE		50
#define DEGATS_MONU			20

#define PRIX_TOUR			500

#define MULT_DEGATS_TOUR	1.2
#define MULT_PRIX_TOUR		100

#define RAYON_TOUR			5

#define COOLDOWN_TOUR		500


/*-------- Enumération --------*/
//Codes erreurs
typedef enum
{
	ERR_OK,					//Pas d'erreur
	ERR_OBJ_NULL,			//L'objet est null
	ERR_GOLD,				//Pas assez de GOLD
	ERR_NIVEAU_MAX,			//La tour est  deja niveau max
	ERR_CASE_OCCUPEE,		//La case de la matrice possede deja une tour
	ERR_CASE_VIDE,				//La case souhaitée est vide
	ERR_FICHIER_VIDE			//Le fichier de sauvegarde est vide
} code_err;


/*-------- Variable globale --------*/
int GOLD;

#endif
