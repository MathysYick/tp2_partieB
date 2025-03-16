/******************************************************/
/* T_PILE.H :  (*** donné aux élèves ***)             */
/*                                                    */
/* Librairie de gestion d'une pile de coups � jouer.  */
/* Permet d'inverser une liste de coups pour ainsi    */
/* afficher le chemin-solution dans le bon sens.      */
/******************************************************/

#ifndef T_PILE_H
#define T_PILE_H  0

/* Structure de base des éléments (un coup  joueur) */
typedef struct {
	int direction ;		//une des 4 directions d�finies par le type "t_direction"
	int niveau;
} t_coup;

typedef t_coup t_element;	//permet de g�n�raliser le type des éléments-pile

/* Structure de la pile des coups */
typedef struct {
	t_element* items;  //tableau dynamique des coups
	int sommet;			//le "haut" de la pile (== -1 lorsque vide)
	int taille;			//taille totale de la pile (taille du tableau)
} t_pile;


/*********************   PROTOTYPES DES FONCTIONS PUBLIQUES  ***************************/

/* On commence avec les accesseurs et mutateurs d'un "t_coup". */
void set_coup(t_coup* coup, int dir, int niv);
int  get_dir(const t_coup* coup);
int  get_niv(const t_coup* coup);

/* Voici le constructeur */

/* Le constructeur re�oit une capacité maximale d'éléments.
   Retourne une pile vide de cette taille (ou NULL si manque de mémoire) */
t_pile creer_pile(unsigned int taille);


/* Puis voici le destructeur */

/* Fonction qui va lib�rer le tableau dynamique de la pile le pointeur
   de cette pile ne devra plus étre utilisé avant d'être réinitialis�. */
void liberer_pile(t_pile* pile);


/* Puis viennent trois fonctions informatrices de l'état de la pile :*/

/* Obtenir le nombre d'éléments actuellement dans la pile reçue en param�tre. */
unsigned int get_nb_elements(const t_pile* pile);

/* V�rifie si la pile est actuellement pleine.
   Retour de 1 si elle est vide, 0 sinon. */
int pile_pleine(const t_pile* pile);

/* V�rifie si la pile est actuellement vide.
   Retour de 1 si elle est vide, 0 sinon. */
int pile_vide(const t_pile* pile);


/* Puis viennent deux fonctions mutatrices de l'état de la pile : */

/* Extraction de la pile (POP):
   Qui reçoit  le handle d'une pile existante  et la référence ou copier l'objet extrait.
   Retour de 0 si la pile est vide -- seul cas possible -- sinon 1. */
int pop_pile(t_pile* pile, t_element* dest);

/* Insertion dans la pile (PUSH):
   Qui reçoit le handle d'une pile et la valeur à insérer
   Retour de 0 si la pile est pleine -- seul cas possible à sinon 1. */
int push_pile(t_pile* pile, t_element src);

#endif //#ifndef T_PILE_H
