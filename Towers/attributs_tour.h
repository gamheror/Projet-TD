void (*detruire)( void ** );
void (*attaquer)( void *, void *(*)[20] );
void (*evoluer)(void *);
void (*afficher)(void*);

int niveau;
int degat;
int rayon;
int cooldown;
int pos_x, pos_y;