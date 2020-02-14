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
char communes[][TAILLE] = {{"soin"},{"poing"},{"épée"}};
char peu_communes[][TAILLE] = {{"potion"},{"barrière"}};
char rares[][TAILLE] = {{"boule de feu"},{"poison"}};
carte_t * generer_carte(int niveau){
  int r = rand()%101;
  printf("%d%%\n", r);
  if (r < 70){
    /*Communes*/

  }
  else if (r >70 && r < 95){
    /*Peu communes*/
  }
  else if (r > 95){
    /*Rares*/
  }
}

int main(){
  /*Initialisation */
  srand(time(NULL));
  int i;
  perso_t * perso = creer_perso();
  ennemi_t * ennemi = creer_ennemi("zombie");
  init_liste();
  ajout_droit(creer_carte("soin", DEFENSE, &(perso->pv), 5, 0));
  ajout_droit(creer_carte("potion", DEFENSE, &(perso->pv), 20, 1));
  ajout_droit(creer_carte("épée", ATTAQUE, &(ennemi->pv), 10, 0));
  ajout_droit(creer_carte("épée", ATTAQUE, &(ennemi->pv), 10, 0));
  ajout_droit(creer_carte("boule de feu", ATTAQUE, &(ennemi->pv), 20, 0));


  /*deck[1] = creer_carte("potion", DEFENSE, &(perso->pv), 20, 1);
  deck[2] = creer_carte("épée", ATTAQUE, &(ennemi->pv), 10, 0);
  deck[3] = creer_carte("épée", ATTAQUE, &(ennemi->pv), 10, 0);
  deck[4] = creer_carte("boule de feu", ATTAQUE, &(ennemi->pv), 20, 0);*/

  /*Combat*/
  generer_carte(1);
  combat(perso,ennemi);

  /*Libération de mémoire */
  /*for(i=0;i<5;i++){
    detruire_carte(&(deck[i]));
  }*/
  detruire_perso(&perso);
  detruire_ennemi(&ennemi);
}
