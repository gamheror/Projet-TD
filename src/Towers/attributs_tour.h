int (*evoluer)(void *);
int (*attaquer)( void *, void *[] );
int (*detruire)( void ** );

int niveau;			/*!< variable pour le niveau de la tour */
int degat;			/*!< variable pour les dégats que la tour va infliger */
int rayon;			/*!< variable pour le rayon d'action de la tour, va servir pour savoir quand attaquer les mobs */
int cooldown;		/*!< variable concernant le temps entre chaque attaque de la tour */
int pos_x, pos_y; 	/*!< variable pour la position en x et en y de la tour */
type_tour type;
