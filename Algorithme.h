#ifndef ALGO_H
#define ALGO_H
#include "plaque.h"
#define MAXNOEUDS 1000 // le nombre maximal de noeuds dans la liste
// type structuré qui représente un « noeud » de la liste (vous pouvez y ajouter d’autres champs!)

typedef struct {
	t_plaque plaque; // la plaque de jeu
	int posx_0, posy_0; // la position de la case vide
	int cout; // le « coût » de ce noeud, Cout(N) = P(N) + E(N)
	int profondeur; // la profondeur (ou niveau) dans l’arbre de jeu
	int parent; // position du noeud-parent de ce noeud
	int terminal; // soit 0 (non-Terminal) ou 1 (Terminal)
	t_direction dir; // la direction qui à été utilisée pour générer cette plaque
} t_noeud;
typedef t_noeud t_liste_noeuds[MAXNOEUDS]; // type-tableau pour la liste des noeuds
typedef int t_tab_ptr_niveaux[MAXNOEUDS]; // type-tableau pour les niveaux


void initialiser_arbre(const t_plaque plaque_depart, int py_0, int px_0, t_liste_noeuds liste_noeuds, t_tab_ptr_niveaux niveaux);

int trouver_solution(t_liste_noeuds liste_noeuds, t_tab_ptr_niveaux niveaux, int max_cout, int* posfin);

void afficher_solution(const t_liste_noeuds liste_noeuds, int posfin);
#endif