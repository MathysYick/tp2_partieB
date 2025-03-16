#include "Algorithme.h"
#include "plaque.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "t_pile.h"


void initialiser_arbre(const t_plaque plaque_depart, int py_0, int px_0, t_liste_noeuds liste_noeuds, t_tab_ptr_niveaux niveaux) {
	printf("initialiser arbre\n");



	t_noeud racine;

	memcpy(racine.plaque, plaque_depart, sizeof(t_plaque));

	//// Initialiser la position du zéro
	trouver_Valeur(racine.plaque, 0, &racine.posx_0, &racine.posy_0);

	racine.cout = evaluer_plaque(plaque_depart); // Fonction qui évalue le coût initial
	racine.profondeur = 0;
	racine.parent = -1; // Pas de parent car c'est la racine
	racine.terminal = 1;  // ehh mon chat // Il ne s'agit pas encore d'un état terminal
	racine.dir = NULLE;


	// Placer la racine dans la liste des nœuds
	liste_noeuds[0] = racine;

	//Initialise les niveaux
	niveaux[0] = 0;
	for (int i = 1;i < MAXNOEUDS;i++) {
		niveaux[i] = -1;
	}

	//// Initialiser les niveaux
	//niveaux[0] = &liste_noeuds[0]; // Pointeur vers le premier nœud
	printf("Premier niveaux: %d\n", niveaux[0]);

}


int trouver_solution(t_liste_noeuds liste_noeuds, t_tab_ptr_niveaux niveaux, int max_cout, int* posfin) {
	bool terminal_exist = true;
	bool new_child = true;
	int nd_terminal = 0;
	int niveau = 0; // Dernier niveau (Losrque le niveau n'est plus égale à -1
	int ind_parent = 0;

	t_noeud child;

	child = liste_noeuds[0];
	child.terminal = 1;
	liste_noeuds[0] = child;
	printf("Début de la recherche de solution\n");

	////Ré-initialise les niveaux ?
	//niveaux[0] = 0;
	//for (int i = 1;i < MAXNOEUDS;i++) {
	//	niveaux[i] = -1;
	//}

	printf("Child - Position vide: (%d, %d)\n", child.posx_0, child.posy_0);
	printf("Child - Cout: %d\n", child.cout);
	printf("child - Terminal: %d\n", child.terminal);
	printf("Child - Parent: %d\n", child.parent);
	printf("Child - Profondeur: %d\n", child.profondeur);
	printf("Child - Direction: %d\n", child.dir);

	while (terminal_exist || new_child) {

		printf("terminal_exist %d\n", terminal_exist);
		printf("new_child %d\n", new_child);
		new_child = false;
		terminal_exist = false;

		for (int i = MAXNOEUDS - 1; i > 0; i--) {
			if (niveaux[i] != -1) {
				niveau = i;
				break;
			}
		}

		for (int i = MAXNOEUDS - 1; i >= 0; i--) {
			child = liste_noeuds[i];

			if (child.terminal == 1) {
				printf("sjkdjbs***********************************************\n");
				printf("dernier noeud de type terminal est à %d. Son parent est %d\n\n", i, child.parent);
				break;
			}
		}
		printf("Cout MAX %d #################################################\n\n\n", max_cout);
		printf("dernier noeuds est à %d tab niveau %d\n", niveau, niveaux[niveau]);

		printf("La plaque du dernier noeud avec un type %d\n", child.terminal);
		afficher_plaque(child.plaque);


		//Étape 2-4
		printf("Etape 2 """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""\n");
		for (int i = MAXNOEUDS - 1; i >= 0; i--) {
			child = liste_noeuds[i];

			if (child.terminal == 1) {
				nd_terminal = i;
				terminal_exist = true;
				printf("dernier noeud de type terminal est à %d. Son parent est %d\n\n", i, child.parent);
				ind_parent = child.parent;
				child.terminal = 0;
				liste_noeuds[i] = child;
				break;
			}

		}
		/*printf("Noeud %d: \n", nd_terminal);
		printf("Child - Position vide: (%d, %d)\n", child.posx_0, child.posy_0);
		printf("Child - Cout: %d\n", child.cout);
		printf("child - Terminal: %d\n", child.terminal);
		printf("Child - Parent: %d\n", child.parent);
		printf("Child - Profondeur: %d\n", child.profondeur);
		printf("Child - Direction: %d\n", child.dir);*/

		t_noeud parent;
		if (child.parent == -1) {
			parent = child;
			//parent.parent = -1;
			//child.parent = -1;
			printf("copie de l'enfant dans le parent puisque c'est le noeud originale\n");
		}
		else {
			parent = liste_noeuds[child.parent];
			printf("copie du parent avec le noeud child.parent %d\n", child.parent);
		}

		//Étape 3
		printf("Etape 3 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		if (!terminal_exist) {
			printf("Aucun noeud terminal trouvé, reset des noeuds\n");
			for (int i = MAXNOEUDS - 1; i > 0; i--) {
				niveaux[i] = -1;
			}
			return 0;
		}

		child.terminal = 0; //Noeud devient un noeud exploré  // EHHH
		printf("child - Terminal: %d\n", child.terminal);


		//Étape 5
		if (evaluer_plaque(child.plaque) == 0) { // Étape 6
			printf("plaque est la solution, noeud terminal %d\n", nd_terminal);

			*posfin = nd_terminal;

			printf("Noeud %d: \n", nd_terminal);
			printf("Child - Position vide: (%d, %d)\n", child.posx_0, child.posy_0);
			printf("Child - Cout: %d\n", child.cout);
			printf("child - Terminal: %d\n", child.terminal);
			printf("Child - Parent: %d\n", child.parent);
			printf("Child - Profondeur: %d\n", child.profondeur);
			printf("Child - Direction: %d\n", child.dir);
			return 1;
		}
		else {
			printf("plaque n'est pas la solution\n");
		}

		//Étape 7
		printf("Génération des enfants $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
		child = liste_noeuds[nd_terminal]; // Copie l'enfant du parent

		//ind_parent = child.parent;  //Copie du parent
		for (int i = 0; i < 4;i++) {

			child = liste_noeuds[nd_terminal]; // Copie l'enfant du parent
			//ind_parent = child.parent;  //Copie du parent
			//child.parent = ind_parent;

			printf("\nEnfant %d du parent %d\n", i, child.parent);

			if (changer_plaque(child.plaque, i, &child.posx_0, &child.posy_0)) {// Modifie la plaque selon la direction
				if ((child.posx_0 != parent.posx_0) || (child.posy_0 != parent.posy_0)) { //Prévient en retour en arrière en comparant la position de la case vide
					child.dir = i;
					child.terminal = 1;	//Noeud n'est pas encore exploré

					printf("Le noeud qu'on explore est le %d\n", nd_terminal);
					/*if (child.parent == -1) {
						child.parent = nd_terminal;

					}
					else {
						child.parent = -1;
					}*/

					//ICITEE
					//child.parent = ind_parent;
					child.parent = nd_terminal;
					//ind_parent = child.parent;
					child.profondeur++;

					child.cout = evaluer_plaque(child.plaque) + child.profondeur;

					if (child.cout < max_cout) {

						if (child.parent == nd_terminal) {
							printf(" parent %d est egale au noeud terminal %d (Qu'on explore)\n", child.parent, nd_terminal);
							//child.parent = ind_parent;
							if (child.parent == 16) {
								//exit(59);
							}
						}
						child.terminal = 1;

						/*niveau++;
						niveaux[niveau] = child.parent;*/
						printf("dernier noeuds est à %d tab niveau %d\n", niveau, niveaux[niveau]);

						printf("indice au niveau %d est %d\n", niveau, niveaux[niveau]);
						niveaux[niveau + i] = nd_terminal + i;
						//printf("indice au niveau %d est %d\n", (niveau + i), niveaux[niveau]);
						memcpy(&liste_noeuds[nd_terminal + i], &child, sizeof(t_noeud));

						if (child.profondeur >10) {
							//delay(1);
							afficher_plaque(child.plaque);

						}
						
						printf("Enfant %d ajouter au niveau %d\n", i, niveau+i);

						new_child = true;

						if (nd_terminal != 0) {
							if (child.parent == nd_terminal) {
								printf(" parent %d est egale au noeud terminal %d (Qu'on explore)\n", child.parent, nd_terminal);
								//exit(69);
							}
						}
						
					}
					else {
						printf("Cout trop elever (%d> %d)\n", child.cout, max_cout);
						printf("ENFANT %d NON AJOUTÉ\n", i);
					}
				}
				else {
					printf("RETOUR AU PARENT\n");
					printf("ENFANT %d NON AJOUTÉ\n", i);
				}
			}
			else {
				printf("MOUVEMENT IMPOSSIBLE\n");
				printf("ENFANT %d NON AJOUTÉ\n", i);
			}

		}
		for (int i = MAXNOEUDS - 1; i >= 0; i--) {
			child = liste_noeuds[i];
			if (child.terminal == 1) {
				nd_terminal = i;
				terminal_exist = true;
				printf("dernier noeud de type terminal est à %d. Son parent est %d\n\n", i, child.parent);
				break;
			}
		}
	}
	if (!new_child) {
		printf("Aucun enfant généré\n");
	}
	if (!terminal_exist) {
		printf("Aucun noeud terminal trouvé\n");
	}

	for (int i = MAXNOEUDS - 1; i > 0; i--) {
		liste_noeuds[niveaux[i]].terminal = 0;
	}
	return 0;
}

void afficher_solution(const t_liste_noeuds liste_noeuds, int posfin) {
	//int pos = posfin;
	printf("afficher solution\n");
	printf("dernier noeud %d\n", posfin);
	t_pile arbre = creer_pile(MAXNOEUDS);
	printf("ele %d\n", get_nb_elements(&arbre));

	//// Remonter les parents jusqu'à l'état initial
	t_element coup_act = { 0 };

	while (posfin != -1) {
		//delay(1);
		coup_act.direction = liste_noeuds[posfin].dir;
		coup_act.niveau = liste_noeuds[posfin].profondeur;
		printf("Direction %d\n", liste_noeuds[posfin].dir);
		printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
		printf("parent %d\n", liste_noeuds[posfin].parent);


		push_pile(&arbre, coup_act); // Stocker le mouvement
		posfin = liste_noeuds[posfin].parent;
		printf("ele %d\n", get_nb_elements(&arbre));
		afficher_plaque(liste_noeuds[posfin].plaque);
		if (arbre.sommet == 10) {
			break;
		}
	}
	{

	//while (posfin != -1) {
	//	posfin = liste_noeuds[posfin].parent;

	//	coup_act.direction = liste_noeuds[posfin].dir;
	//	coup_act.niveau = liste_noeuds[posfin].profondeur;
	//	//push_pile(&arbre, coup_act) // Stocker le mouvement
	//	printf("Direction %d\n", liste_noeuds[posfin].dir);
	//	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	//	printf("parent %d\n", liste_noeuds[posfin].parent);
	//}

	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);

	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);

	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);

	printf("Child - Position vide: (%d, %d)\n", liste_noeuds[posfin].posx_0, liste_noeuds[posfin].posy_0);
	printf("Child - Cout: %d\n", liste_noeuds[posfin].cout);
	printf("child - Terminal: %d\n", liste_noeuds[posfin].terminal);
	printf("Child - Parent: %d\n", liste_noeuds[posfin].parent);
	printf("Child - Profondeur: %d\n", liste_noeuds[posfin].profondeur);
	printf("Child - Direction: %d\n", liste_noeuds[posfin].dir);


	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);

	printf("Child - Position vide: (%d, %d)\n", liste_noeuds[posfin].posx_0, liste_noeuds[posfin].posy_0);
	printf("Child - Cout: %d\n", liste_noeuds[posfin].cout);
	printf("child - Terminal: %d\n", liste_noeuds[posfin].terminal);
	printf("Child - Parent: %d\n", liste_noeuds[posfin].parent);
	printf("Child - Profondeur: %d\n", liste_noeuds[posfin].profondeur);
	printf("Child - Direction: %d\n", liste_noeuds[posfin].dir);


	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);
	printf("ele %d\n", get_nb_elements(&arbre));

	printf("Child - Position vide: (%d, %d)\n", liste_noeuds[posfin].posx_0, liste_noeuds[posfin].posy_0);
	printf("Child - Cout: %d\n", liste_noeuds[posfin].cout);
	printf("child - Terminal: %d\n", liste_noeuds[posfin].terminal);
	printf("Child - Parent: %d\n", liste_noeuds[posfin].parent);
	printf("Child - Profondeur: %d\n", liste_noeuds[posfin].profondeur);
	printf("Child - Direction: %d\n", liste_noeuds[posfin].dir);


	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);
	printf("ele %d\n", get_nb_elements(&arbre));

	printf("Child - Position vide: (%d, %d)\n", liste_noeuds[posfin].posx_0, liste_noeuds[posfin].posy_0);
	printf("Child - Cout: %d\n", liste_noeuds[posfin].cout);
	printf("child - Terminal: %d\n", liste_noeuds[posfin].terminal);
	printf("Child - Parent: %d\n", liste_noeuds[posfin].parent);
	printf("Child - Profondeur: %d\n", liste_noeuds[posfin].profondeur);
	printf("Child - Direction: %d\n", liste_noeuds[posfin].dir);

	coup_act.direction = liste_noeuds[posfin].dir;
	coup_act.niveau = liste_noeuds[posfin].profondeur;
	push_pile(&arbre, coup_act); // Stocker le mouvement
	posfin = liste_noeuds[posfin].parent;
	printf("Direction %d\n", liste_noeuds[posfin].dir);
	printf("Profondeur %d\n", liste_noeuds[posfin].profondeur);
	printf("parent %d\n", liste_noeuds[posfin].parent);
	printf("ele %d\n", get_nb_elements(&arbre));

	printf("Child - Position vide: (%d, %d)\n", liste_noeuds[posfin].posx_0, liste_noeuds[posfin].posy_0);
	printf("Child - Cout: %d\n", liste_noeuds[posfin].cout);
	printf("child - Terminal: %d\n", liste_noeuds[posfin].terminal);
	printf("Child - Parent: %d\n", liste_noeuds[posfin].parent);
	printf("Child - Profondeur: %d\n", liste_noeuds[posfin].profondeur);
	printf("Child - Direction: %d\n", liste_noeuds[posfin].dir);
}


	int test = 0;

	while(liste_noeuds[test].profondeur != 16) {
		printf("Noeud %d: \n", test);

		printf("Child - Position vide: (%d, %d)\n", liste_noeuds[test].posx_0, liste_noeuds[test].posy_0);
		printf("Child - Cout: %d\n", liste_noeuds[test].cout);
		printf("child - Terminal: %d\n", liste_noeuds[test].terminal);
		printf("Child - Parent: %d\n", liste_noeuds[test].parent);
		printf("Child - Profondeur: %d\n", liste_noeuds[test].profondeur);
		printf("Child - Direction: %d\n\n\n", liste_noeuds[test].dir);

		test++;
	}


	//}

	//// Affichage des mouvements dans l'ordre correct
	//printf("Solution trouvée !\nDéplacements : ");
	//while (!pile_vide(&arbre)) {
	//	//printf("%d ", depiler(&arbre)); // Dépiler pour afficher dans l'ordre correct
	//}
	//printf("\n");

}