#include "plaque.h"
#include <time.h>
#include <stdio.h>


void afficher_plaque(const t_plaque pla) {
	for (int i = 0;i < DIM;i++) {
		for (int j = 0;j < DIM;j++) {
			if (pla[i][j] != 0) {
				printf(" %d ", pla[i][j]);
			}
			else {
				printf("   ");
			}
			//printf(" %d ", pla[i][j]);
		}
		printf("\n");
	}
}

//void trouver_Valeur(const t_plaque pla, int val, int* py_val, int* px_val);
void trouver_Valeur(const t_plaque pla, int val, int* px_val, int* py_val) {
	for (int i = 0;i < DIM;i++) {
		for (int j = 0;j < DIM;j++) {
			if (pla[i][j] == val) {
				*py_val = i;
				*px_val = j;
				return;
			}
		}
	}
}

int changer_plaque(t_plaque pla, t_direction dir, int* px_0, int* py_0) {
	/*printf("\n\nchangement de plaque\n");
	printf("La case vide est à x:%d et y:%d\n", *px_0, *py_0);*/

	int nouveau_y = *py_0;
	int nouveau_x = *px_0;

	switch (dir) {
	case HAUT:
		nouveau_y -= 1;
		break;

	case BAS:
		nouveau_y += 1;
		break;
	case GAUCHE:
		nouveau_x -= 1;
		break;
	case DROITE:
		nouveau_x += 1;
		break;

	default:
		break;
	}

	if (nouveau_y < 0 || nouveau_y >= DIM || nouveau_x < 0 || nouveau_x >= DIM) {
		//printf("Deplacement interdit");
		return 0; // Déplacement hors limites
	}

	pla[*py_0][*px_0] = pla[nouveau_y][nouveau_x];
	pla[nouveau_y][nouveau_x] = VIDE;

	*py_0 = nouveau_y;
	*px_0 = nouveau_x;
	return 1;
}

void melanger_plaque(t_plaque pla, int* py_0, int* px_0) {
	int count = 0;
	for (int i = 0; i < NBCOUPS;i++) {
		t_direction dir = rand() % 4; // Générer un nombre entre 0 et 3 (correspondant à HAUT, BAS, GAUCHE, DROITE)
		if (!changer_plaque(pla, dir, py_0, px_0)) {	//si le mouvement est invalide, ajoute un coup à effectuer pour atteindre la valeur de NBCOUPS
			//i--;
		}
		count++;

	}
	printf("nombre de coup effectue: %d\n", count);
}


int evaluer_plaque(const t_plaque pla) {
	int py = 0, px = 0;
	int* py_val = &py;
	int* px_val = &px;

	int py_val_sol = 0, px_val_sol = 0;
	int* py_sol = &py_val_sol;
	int* px_sol = &px_val_sol;
	int cout = 0;
	for (int i = 1; i <= (DIM * DIM) - 1;i++) {
		trouver_Valeur(pla, i, py_val, px_val);
		trouver_Valeur(SOLUTION, i, py_sol, px_sol);

		//printf("Chiffre %d position en x: %d, position de la solution en x: %d\n", i, px, px_val_sol);
		//printf("Chiffre %d position en y: %d, position de la solution en y: %d\n", i, py, py_val_sol);

		cout += abs(px - px_val_sol) + abs(py - py_val_sol);
	}

	//printf("Le cout estime est de %d", cout);
	return cout;
}


