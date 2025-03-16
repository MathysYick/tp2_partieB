#include "t_pile.h"

#include <stdio.h>
#include <stdlib.h>

/* On commence avec les accesseurs et mutateurs d'un "t_coup". */
void set_coup(t_coup* coup, int dir, int niv) {
	if (coup != NULL) {
		coup->direction = dir;
		coup->niveau = niv;
	}
}
int  get_dir(const t_coup* coup) {
	return coup->direction;
}
int  get_niv(const t_coup* coup) {
	return coup->niveau;
}

/* Voici le constructeur */

/* Le constructeur reçoit une capacité maximale d'éléments.
   Retourne une pile vide de cette taille (ou NULL si manque de mémoire) */
t_pile creer_pile(unsigned int taille) {
	t_pile pile = { 0 };

	printf("sizeof(t_coup) = %zu\n", sizeof(t_coup));

	pile.items = (t_coup*)malloc(taille * sizeof(t_coup));

	if (!pile.items) {
		printf("Erreur : Allocation mémoire pour la pile échouée !\n");
	}
	else {
		printf("alloc réussi\n");
	}

	printf("Vérification de l'accès à la mémoire\n");
	// Vérifier si la mémoire est accessible
	for (unsigned int i = 0; i < taille; i++) {
		pile.items[i].direction = 0;  // Accéder à un champ de `t_coup`
		pile.items[i].niveau = 0;  // Accéder à un champ de `t_coup`
	}
	//memset(pile.items, 0, taille * sizeof(t_coup)); // Vérifie si on peut écrire sans planter
	//printf("Premier élément items[0]: %p\n", (void*)&pile.items[0]);

	printf("Vérif deux\n");
	if (pile.items) {
		pile.taille = taille;
		pile.sommet = -1;
	}
	
	if (pile.items) {
		//printf("Pile créée - taille: %d, items: direction %d, niveau %d \n", pile.taille, pile.items->direction, pile.items->niveau);
	}

	return pile;
}

/* Puis voici le destructeur */

/* Fonction qui va libérer le tableau dynamique de la pile le pointeur
   de cette pile ne devra plus être utilisé avant d'être réinitialisé. */
void liberer_pile(t_pile* pile) {
	free(pile->items);
}

/* Puis viennent trois fonctions informatrices de l'état de la pile :*/

/* Obtenir le nombre d'éléments actuellement dans la pile reçue en paramètre. */
unsigned int get_nb_elements(const t_pile* pile) {
	return pile->sommet + 1;
}

/* Vérifie si la pile est actuellement pleine.
   Retour de 1 si elle est vide, 0 sinon. */
int pile_pleine(const t_pile* pile) {
	return (pile->sommet == pile->taille);
}

/* Vérifie si la pile est actuellement vide.
   Retour de 1 si elle est vide, 0 sinon. */
int pile_vide(const t_pile* pile) {
	return (pile->sommet == -1);
}

/* Puis viennent deux fonctions mutatrices de l'état de la pile : */

/* Extraction de la pile (POP):
   Qui reçoit le handle d'une pile existante et la référence ou copier l'objet extrait.
   Retour de 0 si la pile est vide -- seul cas possible -- sinon 1. */
int pop_pile(t_pile* pile, t_element* dest) {
	// Vérification que la pile et le pointeur de destination ne sont pas NULL
	if (!pile || !pile->items || !dest) { return 0; }
	// Vérifie si la pile contient au moins un élément avant de dépiler
	if (pile->sommet >= 0) {
		*dest = pile->items[pile->sommet]; // Copie l'élément du sommet dans *dest
		pile->sommet--; // Décrémente l'indice du sommet pour "supprimer" l'élément
		return 1; // Succès du dépilage
	}
	// Retourne 0 si la pile est vide
	return 0;
}

/* Insertion dans la pile (PUSH):
   Qui reçoit le handle d'une pile et la valeur à insérer
   Retour de 0 si la pile est pleine -- seul cas possible à sinon 1. */
int push_pile(t_pile* pile, t_element src) {
	// Vérification que le pointeur vers la pile n'est pas NULL pour éviter un crash
	if (!pile || !pile->items) { return 0; }
	if (!pile->items) {
		printf("erreur dans l'assignation items\n");
	}
	if (!pile->sommet) {
		printf("erreur dans l'assignation sommet\n");
	}
	printf("push_pile() - sommet: %d, taille: %d, items: %p\n", pile->sommet, pile->taille, (void*)pile->items);
	printf("Valeur de src.direction: %d, src.niveau: %d\n", src.direction, src.niveau);

	// Vérifie si la pile n'est pas pleine avant d'ajouter un nouvel élément
	if (pile->sommet < pile->taille - 1) {
		pile->sommet++; // Incrémente l'indice du sommet
		printf("sommet %d\n", pile->sommet);
		pile->items[pile->sommet] = src; // Stocke l'élément au sommet de la pile
		return 1; // Indique que l'ajout a réussi
	}
	// Si la pile est pleine, retourne 0 pour signaler l'échec de l'ajout
	return 0;
}