#ifndef _ALL_H_
#define _ALL_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Towers/tours.h"
#include "Mobs/mobs.h"

/* Main */
#define N 20

/* Ennemis */
#define VIE_MOB		200
#define V_DEP_MOB		10
#define DEGAT_MOB		15
#define NB_MOB		5

/* Tours */
#define NIVEAU_MAX_TOUR		5
#define DEGATS_TOUR_MONO	150
#define DEGATS_TOUR_AOE		50
#define MULT_DEGATS_TOUR	1.2
#define RAYON_TOUR			5
#define COOLDOWN_TOUR		500
#define MULT_PRIX_TOUR		100

#define PRIX_TOUR	500

int gold;

#endif