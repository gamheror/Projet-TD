/*#include "../all"
#include "map.h"*/

#include <stdlib.h>
#include <stdio.h>

#define N 4


// utilisation d'une liste pour la création du chemin
void creer_chemin()
{
	int x;
	int y;

	int i;
	int j;
	
	FILE* fichier = NULL;
	fichier = fopen("Chemin/chemin.txt", "r");

	
	
}

int main(){
	
	creer_chemin();
	/*t_mob mob[4];
	t_coord chemin[4];
	t_map map[4][4];
	int temps;
	int i,j;
	
	for(int i = 0; i<NB_MOB; i++)
		creer_mobs(0,0);

	
	/*chemin[0].x = 0;
	chemin[0].y = 1;
	chemin[1].x = 1;
	chemin[1].y = 1;
	chemin[2].x = 1;
	chemin[2].y = 2;
	chemin[3].x = 2;
	chemin[3].y = 2;*/
	
	/*mob[0].pos = chemin[0];	
	mob[0].nom = 'b';
	mob[0].speed = 1;
	mob[0].blbl = 0;
	mob[1].pos = chemin[0];	
	mob[1].nom = 'l';
	mob[1].speed = 2;
	mob[1].blbl = 0;
	mob[2].pos = chemin[0];	
	mob[2].nom = 'b';
	mob[2].speed = 1;
	mob[2].blbl = 0;
	
	for ( i=0; i!=4; i++){
		for ( j=0; j!=4; j++){
			map[i][j].mobs[0] = '.';
			map[i][j].mobs[1] = '.';
			map[i][j].mobs[2] = '.';
			map[i][j].mobs[3] = '.'; 
			map[i][j].mobs[4] = '\0'; 
			
		}
	}	
	
	for (temps = 0;temps !=3; temps++){
		for ( i=0; i!=4; i++){
			if (mob[i].nom == 'b'){
				map[mob[i].pos.x][mob[i].pos.y].mobs[i] = '.';
				mob[i].blbl++;
				mob[i].pos = chemin[mob[i].blbl];
			}
			if (mob[i].nom == 'l' && temps%2 ==0){
				map[mob[i].pos.x][mob[i].pos.y].mobs[i] = '.';
				mob[i].blbl++;
				mob[i].pos = chemin[mob[i].blbl];
			}
			map[mob[i].pos.x][mob[i].pos.y].mobs[i] = mob[i].nom;
		}
		for ( i=1; i!=4; i++){
			printf("\n");
			for ( j=1; j!=4; j++){
				printf("%s ", map[i][j].mobs); 
			}
		}	
		printf("\n");
		printf("\n");
	}*/
}