#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

typedef enum {ROUGE,BLEU,VERT} tCouleur;
typedef tCouleur tTabCouleur[MAX_SOMMETS];

void ParcoursEnProfondeur(tGraphe g, tNumeroSommet s) {
	int nbSommets, i, trouve, index[MAX_SOMMETS];
	tPileSommets pile;
	tTabCouleur couleur;

	nbSommets = grapheNbSommets(g);
	for(i = 0; i < nbSommets; i++) {
		couleur[i] = BLEU;
		index[i] = -1;
	}

	pile = pileSommetsAlloue();

	couleur[s] = VERT;
	pileSommetsEmpile(pile, s);

	while(!pileSommetsEstVide(pile)) {
		tNumeroSommet x, y;

		x = pileSommetsTete(pile);
		index[x] = index[x] + 1;
		trouve = 0;

		while(index[x] < grapheNbVoisinsSommet(g, x) && !trouve) {
			y = grapheVoisinSommetNumero(g, x, index[x]);
			if(couleur[y] == BLEU) {
				trouve = 1;
			} else {
				index[x] = index[x] + 1;
			}
		}

		if(trouve) {
			couleur[y] = VERT;
			pileSommetsEmpile(pile, y);
		} else {
			tNomSommet nom;
			couleur[x] = ROUGE;
			pileSommetsDepile(pile);
			grapheRecupNomSommet(g, x, nom);
			printf("%s\n", nom);
		}
	}

	pileSommetsLibere(pile);
}

int main(int argc, char **argv) {
	tGraphe graphe;
	tNumeroSommet s;

	if(argc != 3) {
		halt("Usage : ./plusCourteDistance FichierGrapheNonOriente SommetDeDepart");
	}

	graphe = grapheAlloue();
	grapheChargeFichier(graphe, argv[1]);

	s = grapheChercheSommetParNom(graphe, argv[2]);

	ParcoursEnProfondeur(graphe, s);
	grapheLibere(graphe);

	printf("\n");

	return 0;
}