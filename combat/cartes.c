#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*!
* \file cartes.c
* \brief Ce programme contient les fonctions liées aux cartes
* \author Timothée Marin
* \version 0.1
* \date 30 janvier 2020
*
*
*
*
*/
#define TAILLE 20
#define TAILLE_DECK 5

/**
* \fn carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur)
* \brief Crée une carte avec les valeurs passées en paramètres
* \param char* nom Le nom de la carte.
* \param type_carte type Le type de la carte, qui multiplie la valeur par 1 ou -1.
* \param int* cible L'adresse de la statistique sur laquelle la carte influe.
* \param int valeur La puissance de la carte.
* \return i+2
*/

typedef enum {ATTAQUE = -1, DEFENSE = 1} type_carte ;

typedef struct carte_s {
  char * nom ;
  type_carte type;
  int * cible;
  int valeur;
} carte_t ;

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


int main(){
  int pv_joueur = 20;
  int pv_ennemi = 20;
  carte_t * deck[TAILLE_DECK];
  deck[0] = creer_carte("soin", DEFENSE, &pv_joueur, 10);
  deck[1] = creer_carte("épée", ATTAQUE, &pv_ennemi, 10);
  deck[2] = creer_carte("épée", ATTAQUE, &pv_ennemi, 10);
  deck[3] = creer_carte("épée", ATTAQUE, &pv_ennemi, 10);
  deck[4] = creer_carte("boule de feu", ATTAQUE, &pv_ennemi, 20);
  int i;
  for(i=0;i<5;i++){
    *(deck[i]->cible) += deck[i]->type * deck[i]->valeur;
    printf("Tour %d : \n", i+1);
    printf("Carte utilisée : %s\n", deck[i]->nom);
    printf("%d\n", deck[i]->type * deck[i]->valeur);
    printf("pv joueur : %d\n", pv_joueur);
    printf("pv ennemi : %d\n\n", pv_ennemi);
  }
}
