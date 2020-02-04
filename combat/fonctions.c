#include "structures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur)
{
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

perso_t * creer_perso()
{
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

ennemi_t * creer_ennemi(char * nom)
{
  ennemi_t * ennemi = NULL ;
  static unsigned long int cpt = 0 ;

  ennemi = malloc(sizeof(ennemi_t));

  ennemi->nom = malloc(sizeof(char)*TAILLE);
  strcpy(ennemi->nom , nom);

  ennemi->pv = 20;
  ennemi->vitesse = 10;
  ennemi->attaque = 10;
  ennemi->defense = 10;

  return(ennemi);
}

void detruire_carte(carte_t ** carte)
{
  free((*carte)->nom);
  free(*carte);
}

void detruire_perso(perso_t ** perso)
{
  free(*perso);
}

void detruire_ennemi(ennemi_t ** ennemi)
{
  free((*ennemi)->nom);
  free(*ennemi);
}

int initiative (perso_t * perso,ennemi_t * ennemi)
{
  if(perso->vitesse>ennemi->vitesse){
    return 1;
  }
  else if(ennemi->vitesse>perso->vitesse){
    return 0;
  }
  else if(ennemi->vitesse==perso->vitesse){
    return rand()%2;
  }
}

void tour_ennemi(perso_t * perso,ennemi_t * ennemi)
{
  int i;
  if(ennemi->pv > perso->attaque){
        printf("Le %s attaque \n", ennemi->nom);
        perso->pv += -10;
      }
  else if (ennemi->pv < perso->attaque){
        printf("Le %s se soigne \n", ennemi->nom);
        ennemi->pv += 10;
      }
  else{
    printf("Le %s tacle \n", ennemi->nom);
    perso->vitesse += -1;
  }
}

int tour_perso(int choix,perso_t *perso,ennemi_t * ennemi, carte_t ** deck)
{
  choix--;
  printf("Vous utilisez %s !\n", deck[choix]->nom);
  *(deck[choix]->cible) += deck[choix]->type * deck[choix]->valeur;

}

void combat(perso_t * perso, ennemi_t * ennemi, carte_t ** deck)
{
  while(ennemi->pv > 0 && perso->pv > 0){
    int choix, i;
    printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
    for(i=0 ; i<TAILLE_DECK ; i++){
      printf("[%d] : %s\n", i+1, deck[i]->nom);
    }
    scanf("%d",&choix);
    if (initiative(perso, ennemi)){
      tour_perso(choix, perso, ennemi, deck);
      if(ennemi->pv)
        tour_ennemi(perso, ennemi);
    }
    else{
      tour_ennemi(perso, ennemi);
      if(perso->pv)
        tour_perso(choix, perso, ennemi, deck);
    }
  }
  if(!ennemi->pv){
    printf("Vous avez vaincu le %s\n", ennemi->nom);
  }
  else{
    printf("Vous avez été vaincu par le %s\n", ennemi->nom);
  }

}
