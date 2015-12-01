#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graphe.h"

typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

static tTabCouleurs sommets_couleur;

void parcours_largeur(tGraphe graphe, tNumeroSommet s) {
  int nbSommet, i, file_vide;
  tFileSommets file;
  
  nbSommet = grapheNbSommets(graphe);
  for(i = 0; i < nbSommet; i++) {
    if(i != s)
      sommets_couleur[i] = BLEU;
  }
  sommets_couleur[s] = VERT;

  file = fileSommetsAlloue();

  fileSommetsEnfile(file, s);
  file_vide = fileSommetsEstVide(file);
  while(!file_vide) {
    tNumeroSommet x;
    tNomSommet nom;
    int nbVoisin;
    
    x = fileSommetsDefile(file);
    grapheRecupNomSommet(graphe, x, nom);
    
    printf("%s ", nom);
    
    nbVoisin = grapheNbVoisinsSommet(graphe, x);
    for(i = 0; i < nbVoisin; i++) {
      tNumeroSommet y;

      y = grapheVoisinSommetNumero(graphe, x, i);
      if(sommets_couleur[y] == BLEU) {
	sommets_couleur[y] = VERT;
	fileSommetsEnfile(file, y);
      }
    }
    sommets_couleur[x] = ROUGE;
  }
  
  fileSommetsLibere(file);
}

int main(int argc, char *argv[]) {
  tGraphe graphe;
  tNumeroSommet s;
  
  if(argc != 3)
    halt("Usage : parcours_largeur FichierGraphe SommetDeDepart");

  graphe = grapheAlloue();
  grapheChargeFichier(graphe, argv[1]);

  s = grapheChercheSommetParNom(graphe, argv[2]);

  parcours_largeur(graphe, s);
  grapheLibere(graphe);

  printf("\n");
  
  return 0;
}
