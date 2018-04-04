#ifndef _ALL_H_
#define _ALL_H_


/*-------- Constante --------*/

/* Matrices */
#define N 20							/*!< Définit la taille des matrices et du tableau de monstres >*/

/* Mobs */
#define VIE_NORM		250				/*!< nombre de points de vie d'un monstre normal >*/
#define VIE_TANK 		750				/*!< nombre de points de vie d'un monstre tank >*/
#define VIE_BOSS		1000			/*!< nombre de points de vie d'un monstre boss >*/
#define VIE_DEGAT		150				/*!< nombre de point de vie d'un monstre rapide  >*/	

/*!< Plus un monstre a une V_DEP_** élevé, plus il est lent >*/

#define V_DEP_NORM		2				/*!< vitesse de déplacement d'un monstre normal en seconde case >*/
#define V_DEP_TANK		2				/*!< vitesse de déplacement d'un monstre tank en seconde case >*/
#define V_DEP_BOSS		3				/*!< vitesse de déplacement d'un monstre boss en seconde case >*/
#define V_DEP_DEGAT		1				/*!< vitesse de déplacement d'un monstre rapide en seconde case >*/

#define DEGAT_NORM		20				/*!< degats qu'infligent les monstres normaux au monument >*/
#define DEGAT_TANK		16				/*!< degats qu'infligent les monstres tank au monument >*/
#define DEGAT_BOSS		60				/*!< degats qu'infligent les monstres boss au monument >*/
#define DEGAT_DEGAT		40				/*!< degats qu'infligent les monstres rapide au monument >*/

#define DROP_MOB_MIN	20				/*!< nombre minimal de gold récuperable sur un monstre >*/
#define DROP_MOB_MAX	80				/*!< nombre maximal de gold récuperable sur un monstre >*/

#define POURCENT_NORM	45				/*!< pourcentage d'apparition des monstres de type normaux >*/
#define POURCENT_DEGA	25				/*!< pourcentage d'apparition des monstres de type degats >*/
#define POURCENT_TANK	25				/*!< pourcentage d'apparition des monstres de type tank >*/
#define POURCENT_BOSS	5				/*!< pourcentage d'apparition des monstres de type rapides >*/

/* Tours */
#define NIVEAU_MAX_TOUR		5			/*!< niveau maximum atteignable pour les tours>*/
#define DEGATS_TOUR_MONO	100			/*!< degats des tours mono sur les monstres >*/
#define DEGATS_TOUR_AOE		20			/*!< degats des tours aoe sur les monstres >*/
#define DEGATS_MONU			12			/*!< degats du monument sur les monstres >*/
#define PV_MONU				2500		/*!< points de vie du monument >*/
#define PRIX_TOUR			500			/*!< coût en gold d'une tour quelconque >*/
#define MULT_DEGATS_TOUR	1.2			/*!< multiplicateur appliqué aux degats d'une tour lors de son évolution >*/
#define MULT_PRIX_TOUR		500			/*!< multiplicateur definissant le coût d'évolution d'une tour du n à n+1 suivant degats(n+1)=n*MULT_PRIX_TOUR >*/
#define RAYON_TOUR			3			/*!< rayon d'attaque des tours >*/

/* SDL */
#define TAILLE_POLICE	 	30			/*!< taille de la police d'ecriture générale>*/
#define TAILLE_TITRE 		45			/*!< taille de la police d'ecriture du titre>*/
#define TAILLE_TXT_FOOTER 	10			/*!< taille de la police d'ecriture du pied de l'ecran d'accueil>*/
#define TAILLE_IMAGE		30			/*!< taille d'un carreau du plateau de jeu>*/
#define TAILLE_TUILE 		80			/*!< taille d'une image dans les menus de jeu>*/

#define LARGEUR_FEN 700					/*!<Largeur de la fenetre>*/
#define HAUTEUR_FEN 700					/*!<Hauteur de la fenetre>*/

#define MARGE_HAUT		100				/*!<Hauteur du menu haut de jeu>*/
#define MARGE_GAUCHE 	100				/*!<Largeur du menu gauche de jeu>*/

#define LARGEUR_MENU_HAUT 	600			/*!<largeur du menu haut de jeu>*/
#define HAUTEUR_MENU_GAUCHE 600			/*!<hauteur du menu gauche de jeu>*/


/*-------- Enumération --------*/
//Codes erreurs
typedef enum
{
	ERR_OK,								/*!<Pas d'erreur>*/
	ERR_OBJ_NULL,						/*!<L'objet est null>*/
	ERR_GOLD,							/*!<Pas assez de GOLD>*/
	ERR_NIVEAU_MAX,						/*!<La tour est deja au niveau maximal>*/
	ERR_CASE_OCCUPEE,					/*!<La case de la matrice possede deja une tour>*/
	ERR_CASE_VIDE,						/*!<La case souhaitée est vide>*/
	ERR_FICHIER_VIDE					/*!<Le fichier de sauvegarde est vide>*/
} code_err;

typedef enum {AOE, MONO, MONU} type_tour; /*!< Enumeration contenant les types de batiments utilisables >*/

/*-------- Variable globale --------*/
int GOLD;								/*!< variable globale contenant le nombres de gold du joueur >*/

#endif
