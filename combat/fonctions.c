#include "structures.h"
#include <string.h>

carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur){
  carte_t * carte = NULL ;
  static unsigned long int cpt = 0 ;

  carte = malloc(sizeof(carte_t));

  carte->nom = malloc(sizeof(char)*TAILLE);
  strcpy(carte->nom , nom);
  carte->valeur = valeur;
  carte->cible = cible;
  carte->type = type;

  return(carte);
}

perso_t * creer_perso(){
  perso_t * perso = NULL ;
  static unsigned long int cpt = 0 ;

  perso = malloc(sizeof(perso_t));

  perso->pv = 20;
  perso->vitesse = 10;
  perso->attaque = 10;
  perso->defense = 10;
  perso->x = 0;
  perso->y = 0;
  return(perso);
}

void detruire_perso(perso_t ** perso){
  free(*perso);
}
