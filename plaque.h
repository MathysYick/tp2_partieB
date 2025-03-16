#ifndef PLAQUE_H
#define PLAQUE_H
#define DIM 3 // la largeur de la plaque (3x3 cases en tout)
#define VIDE 0 // la valeur de la case vide
#define NBCOUPS 200 // le nombre de coups à faire pour mélanger la plaque initiale

/* Type énuméré pour les 4 déplacements possibles */
typedef enum { NULLE = -1, HAUT, GAUCHE, BAS, DROITE } t_direction;
/* Type-tableau pour la plaque de jeu */
typedef int t_plaque[DIM][DIM];
/* Constante qui illustre la plaque-solution à trouver */
static const t_plaque SOLUTION = { {1, 2, 3}, {4, 5, 6}, {7, 8, VIDE} };
void trouver_Valeur(const t_plaque pla, int val, int* px_val, int* py_val);
int changer_plaque(t_plaque pla, t_direction dir, int* py_0, int* px_0);
void melanger_plaque(t_plaque pla, int* py_0, int* px_0);
int evaluer_plaque(const t_plaque pla);
void afficher_plaque(const t_plaque pla);

#endif