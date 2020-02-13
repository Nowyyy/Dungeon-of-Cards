#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "constantes.h"
#include "fonctions.h"
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

/**
* \fn carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur)
* \brief Crée une carte avec les valeurs passées en paramètres
* \param char* nom Le nom de la carte.
* \param type_carte type Le type de la carte, qui multiplie la valeur par 1 ou -1.
* \param int* cible L'adresse de la statistique sur laquelle la carte influe.
* \param int valeur La puissance de la carte.
* \return i+2
*/

int main(){
  /*Initialisation */
  int i;
  perso_t * perso = creer_perso();
  ennemi_t * ennemi = creer_ennemi("zombie");
  carte_t * deck[TAILLE_DECK];
  deck[0] = creer_carte("soin", DEFENSE, &(perso->pv), 10);
  deck[1] = creer_carte("épée", ATTAQUE, &(ennemi->pv), 10);
  deck[2] = creer_carte("épée", ATTAQUE, &(ennemi->pv), 10);
  deck[3] = creer_carte("épée", ATTAQUE, &(ennemi->pv), 10);
  deck[4] = creer_carte("boule de feu", ATTAQUE, &(ennemi->pv), 20);

  /*Combat*/
  combat(perso, ennemi, deck);


  /*Libération de mémoire */
  for(i=0;i<5;i++){
    detruire_carte(&(deck[i]));
  }
  detruire_perso(&perso);
  detruire_ennemi(&ennemi);
}
