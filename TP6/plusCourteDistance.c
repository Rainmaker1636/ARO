#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

static int d[MAX_SOMMETS];
static tNumeroSommet pred[MAX_SOMMETS];

typedef enum {ROUGE,BLEU,VERT} tCouleur;
typedef tCouleur tTabCouleur[MAX_SOMMETS];

void plusCourteChaine(tGraphe graphe, tNumeroSommet sommet) {
	int nbSommet, i;
	tFileSommets file;
	tTabCouleur couleur;

	nbSommet = grapheNbSommets(graphe);
	
	for (i = 0; i < nbSommet; ++i) {
		couleur[i] = BLEU;
	}
	
	file = fileSommetsAlloue();

	d[sommet] = 0;
	pred[sommet] = -1;
	
	couleur[sommet] = VERT;
	fileSommetsEnfile(file, sommet);

	while(!fileSommetsEstVide(file)) {
		tNumeroSommet x, y;
		int nbVoisin;

		x = fileSommetsDefile(file);
		nbVoisin = grapheNbVoisinsSommet(graphe, x);
		for(i = 0; i < nbVoisin; i++) {
			y = grapheVoisinSommetNumero(graphe, x, i);
			if(couleur[y] == BLEU) {
				couleur[y] = VERT;
				fileSommetsEnfile(file, y);
				d[y] = d[x] + 1;
				pred[y] = x;
			}
		}
		couleur[x] = ROUGE;
	}

	fileSommetsLibere(file);

	for(i = 0; i < nbSommet; i++) {
		tNomSommet nom, voisin;
		grapheRecupNomSommet(graphe, i, nom);
		printf("%s | %d | %d\n", nom, d[i], pred[i]);
	}
}

long nbMicroSecondesDepuisDebutHeure() {
	struct timeval tv;
	long us;
	gettimeofday(&tv, NULL);
	tv.tv_sec = tv.tv_sec % 3600;
	us = (tv.tv_sec * 1000000) + tv.tv_usec;
	return us;
}

int main(int argc, char const *argv[])
{
	tGraphe graphe;
	tNumeroSommet s;

	if(argc != 3) {
		halt("Usage : ./plusCourteDistance FichierGrapheNonOriente SommetDeDepart");
	}


	graphe = grapheAlloue();
	grapheChargeFichier(graphe, argv[1]);

	s = grapheChercheSommetParNom(graphe, argv[2]);

	plusCourteChaine(graphe, s);
	grapheLibere(graphe);

	printf("\n");

	return 0;
}