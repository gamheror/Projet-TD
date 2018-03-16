#include "../all.h"

int main(){
	typedef struct {char n_mobs[10];}t_map;
	
	mobs_t *mob[4];
	t_map map[4][4];
	int temps;
	int i,j;

	mob[0] = creer_mobs();
	mob[0]->pos = NULL;	
	mob[0]->caract = 'b';
	mob[0]->v_deplacement = 1;

	mob[1] = creer_mobs()  ;
	mob[1]->pos = NULL;	
	mob[1]->caract = 'l';
	mob[1]->v_deplacement = 2;

	mob[2] = creer_mobs();
	mob[2]->pos = NULL;	
	mob[2]->caract = 'b';
	mob[2]->v_deplacement = 1;
	
	mob[3] = creer_mobs();
	mob[3]->pos = NULL;	
	mob[3]->caract = 'l';
	mob[3]->v_deplacement = 2;

	
	for ( i=0; i!=4; i++){
		for ( j=0; j!=4; j++){
			map[i][j].n_mobs[0] = '0';
			map[i][j].n_mobs[1] = '0';
			map[i][j].n_mobs[2] = '0';
			map[i][j].n_mobs[3] = '0';
			map[i][j].n_mobs[4] = '\0'; 
			
		}
	}	
	
	for (temps = 0;temps !=15; temps++){
		for ( i=0; i!=4; i++){
			if (temps % mob[i]->v_deplacement == 0){
				if(mob[i]->pos == NULL){
					mob[i]->pos = initialisation();
					mob[i]->pos->courant = mob[i]->pos->premier;
				}
				if (fin_liste(mob[i]->pos)){
				} 
				else{
					map[mob[i]->pos->courant->x][mob[i]->pos->courant->y].n_mobs[i] = '0';
					mob[i]->pos->courant = mob[i]->pos->courant->suivant;
				}
			}
		map[mob[i]->pos->courant->x][mob[i]->pos->courant->y].n_mobs[i] = mob[i]->caract;
		}

		for ( i=0; i!=4; i++){
			printf("\n");
			for ( j=0; j!=4; j++){
				printf("%s ", map[i][j].n_mobs); 
			}
		}	
		printf("\n");
		printf("\n");
	}
	
	return(0);	
}
