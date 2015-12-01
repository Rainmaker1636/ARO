#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"

void sommetSansVoisin(tGraphe graphe) {
  int nbSommet;
  int i;
  tNomSommet nom;
  
  nbSommet = grapheNbSommets(graphe);

  for(i = 0; i < nbSommet; i++) {
    if(grapheNbVoisinsSommet(graphe, i) == 0) {
      grapheRecupNomSommet(graphe, i, nom);
      printf("Le sommet %s n'a pas de voisin\n", nom);
    }
  }
}

void plusDeVoisin(tGraphe graphe) {
  int nbSommet;
  int i;
  int maxVoisin;
  tNomSommet nom;

  maxVoisin = 0;
  nbSommet = grapheNbSommets(graphe);
  
  for(i = 0; i < nbSommet; i++) {
    int nbVoisin;
    nbVoisin = grapheNbVoisinsSommet(graphe, i);
    if(maxVoisin < nbVoisin) {
      maxVoisin = nbVoisin;
    }
  }

  for(i = 0; i < nbSommet; i++) {
    if(grapheNbVoisinsSommet(graphe, i) == maxVoisin) {
      grapheRecupNomSommet(graphe, i, nom);
      printf("Le sommet %s a le plus de voisin (%d)\n", nom, maxVoisin);
    }
  }
}

int main(int argc, char *argv[]) {
  tGraphe graphe;

  if(argc < 2) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }

  graphe = grapheAlloue();

  grapheChargeFichier(graphe, argv[1]);
  sommetSansVoisin(graphe);
  printf("-------\n");
  plusDeVoisin(graphe);
  
  grapheLibere(graphe);
  
  exit(EXIT_SUCCESS);
}
