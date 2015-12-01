#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"
#include "sys/wait.h"

void visuOriente(tGraphe graphe, FILE *fic) {
  int nbSuccesseur, nbSommet, i, j;
  tNomSommet origine, destination;
  nbSommet = grapheNbSommets(graphe);

  fprintf(fic, "digraph{\n");
  for(i = 0; i < nbSommet; i++) {
    nbSuccesseur = grapheNbSuccesseursSommet(graphe, i);
    grapheRecupNomSommet(graphe, i, origine);
    for(j = 0; j < nbSuccesseur; j++) {
      tNumeroSommet sucNum;
      sucNum = grapheSuccesseurSommetNumero(graphe, i, j);
      grapheRecupNomSommet(graphe, sucNum, destination);

      fprintf(fic, "%s -> %s\n", origine, destination);
    }
  }
  fprintf(fic, "}");
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

      if(grapheMat[i][voiNum] == 0) fprintf(fic, "%s -- %s\n", origine, destination);
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
  
  if(grapheEstOriente(graphe)) visuOriente(graphe, fic);
  else visuNonOriente(graphe, fic);
  
  fclose(fic);

  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if(WEXITSTATUS(ret)) {
    halt("La commande suivante a échoué\n%s\n", commande);
  }
}

int main(int argc, char *argv[]) {
  tGraphe graphe;
  
  if(argc != 2) {
    halt("Usage : %s FichierGraphe");
  }

  graphe = grapheAlloue();
  grapheChargeFichier(graphe, argv[1]);
  graphe2visu(graphe, "visu");
  grapheLibere(graphe);
  
  return 0;
}
