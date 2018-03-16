void (*afficher)(void*);
int (*evoluer)(void *);
void (*attaquer)( void *, void *(*)[20] );
int (*detruire)( void ** );

int niveau;
int degat;
int rayon;
int cooldown;
int pos_x, pos_y;
