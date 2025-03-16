#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "plaque.h"

#include <time.h>

#include "Algorithme.h"
#include "t_pile.h"


void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}

int main() {
	t_plaque pla = { {1, 2, 3}, {4, 5, 6}, {7, 8, VIDE} };
	t_tab_ptr_niveaux niveaux; // type-tableau pour les niveaux
	t_liste_noeuds liste_noeuds;



	int py = 0;
	int px = 0;
	int* py_val = &py;
	int* px_val = &px;

	int py_vide = 0;
	int px_vide = 0;
	int* py_0 = &py_vide;
	int* px_0 = &px_vide;

	int posf = 0;
	int* posfin = &posf;
	*posfin = 0;
	
	trouver_Valeur(pla, 0, px_0, py_0);
	/*changer_plaque(pla, 0, px_0, py_0);
	changer_plaque(pla, 1, px_0, py_0);
	changer_plaque(pla, 1, px_0, py_0);*/
	melanger_plaque(pla, py_0, px_0);
	afficher_plaque(pla);

	int max_cout = evaluer_plaque(pla);

	printf("Cout Depart = %d\n", max_cout);


	initialiser_arbre(pla, py_vide, px_vide, liste_noeuds, niveaux);


	//while (trouver_solution(liste_noeuds, niveaux, max_cout, liste_noeuds->terminal) != 1) {
	while (trouver_solution(liste_noeuds, niveaux, max_cout, &posfin) != 1) {

		max_cout++;
		//delay(1);
		printf("\n\n\COUT MAX %d -----------------------------------------------------------------------------\n\n\n", max_cout);
		if (max_cout > 1000) {
			break;
		}
		//initialiser_arbre(pla, py_vide, px_vide, liste_noeuds, niveaux);

	}

	printf("position de fin %d\n", posfin);
	posf = posfin;
	printf("parent %d\n", liste_noeuds[posf].parent);
	printf("direction %d\n", liste_noeuds[posf].dir);


	afficher_solution(liste_noeuds, posfin);
}
