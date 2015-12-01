#include <stdlib.h>
#include <stdio.h>
#include "sys/wait.h"
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
		tNomSommet nom;
		grapheRecupNomSommet(graphe, i, nom);
		printf("%s | %d | %d\n", nom, d[i], pred[i]);
	}
}

void visuNonOriente(tGraphe graphe, FILE *fic) {
  int nbSommet, nbVoisin, i, j;
  tNomSommet origine, destination;
  int grapheMat[MAX_SOMMETS][MAX_SOMMETS] = {0};

  nbSommet = grapheNbSommets(graphe);

  fprintf(fic, "graph{\n");
  for(i = 0; i < nbSommet; i++) {
    nbVoisin = grapheNbVoisinsSommet(graphe, i);
    grapheRecupNomSommet(graphe, i, origine);
    for(j = 0; j < nbVoisin; j++) {
      tNumeroSommet voiNum;
      voiNum = grapheVoisinSommetNumero(graphe, i, j);
      grapheRecupNomSommet(graphe, voiNum, destination);

      grapheMat[voiNum][i] = 1;

      if(grapheMat[i][voiNum] == 0) {
      	fprintf(fic, "%s -- %s[color=blue]\n", origine, destination);
      }
    }
  }
  fprintf(fic, "}");
}

void graphe2visu(tGraphe graphe, char *outfile) {
  FILE *fic;
  char commande[80];
  char dotfile[80];
  int ret;

  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");

  if(fic == NULL)
    halt("Ouverture du fichier %s en ecriture impossible\n", dotfile);
  
  visuNonOriente(graphe, fic);
  
  fclose(fic);

  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if(WEXITSTATUS(ret)) {
    halt("La commande suivante a échoué\n%s\n", commande);
  }
}

/*long nbMicroSecondesDepuisDebutHeure() {
	struct timeval tv;
	long us;
	gettimeofday(&tv, NULL);
	tv.tv_sec = tv.tv_sec % 3600;
	us = (tv.tv_sec * 1000000) + tv.tv_usec;
	return us;
}*/

int main(int argc, char const *argv[])
{
	tGraphe graphe;
	int nbSommets;
	double probaArc;

	if(argc < 3) {
		halt("Usage : ./plusCourteDistance FichierGrapheNonOriente SommetDeDepart");
	}


	graphe = grapheAlloue();

	nbSommets = atoi(argv[1]);
	probaArc = atof(argv[2]);

	grapheAleatoire(graphe, nbSommets, 0, probaArc);

	plusCourteChaine(graphe, 0);
	if(argc == 4) {
		graphe2visu(graphe, argv[3]);
	}
	grapheLibere(graphe);

	
	printf("\n");


	return 0;
}