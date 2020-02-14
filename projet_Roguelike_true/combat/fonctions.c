/**
*\file fonctions.c
*\brief fichier qui permet de référencé tous les fonctions du système de combat.
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 13/02/2020
*/


#include "constantes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Mise en oeuvre dynamique d'une liste de cartes


// Primitives de manipulation de la liste

void init_liste(){
	drapeau = malloc(sizeof(element_t));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}

int liste_vide(){
	return drapeau->pred==drapeau;
}

int hors_liste(){
	return ec==drapeau;
}

void en_tete(){
	if (!liste_vide())
		ec = drapeau->succ;
}

void en_queue(){
	if (!liste_vide())
		ec = drapeau->pred;
}

void precedent(){
	if (!hors_liste())
		ec = ec->pred;
}

void suivant(){
	if (!hors_liste())
		ec = ec->succ;
}

void valeur_elt(carte_t * t){
	if (!hors_liste())
		*t = *ec->carte;
}

void modif_elt(carte_t t){
	if (!hors_liste())
		*ec->carte = t;
}

void oter_elt(carte_t t){
	element_t * temp;

	if (!hors_liste()){
		(ec->succ)->pred = ec->pred;
		(ec->pred)->succ = ec->succ;
		temp = ec;
		ec = ec->pred;
		free(temp);
		}
}

void ajout_droit(carte_t * t){
	element_t* nouv;

	if (liste_vide() || !hors_liste()){
		nouv = malloc(sizeof(element_t));
		nouv->carte = t;
		nouv->pred = ec;
		nouv->succ = ec->succ;
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		ec = nouv;
	}
}

void ajout_gauche(carte_t * t){
	element_t* nouv;

	if (liste_vide() || !hors_liste()){
		nouv = malloc(sizeof(element_t));
		nouv->carte = t;
		nouv->succ = ec;
		nouv->pred = ec->pred;
		(ec->pred)->succ = nouv;
		ec->pred = nouv;
		ec = nouv;
	}
}

/**
*\fn carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur)
*\brief permet de créer une carte selon différentes caractéristiques donnés
*\param nom pour le nom de la carte
*\param type pour le type de la carte
*\param cible pour la cible de la carte
*\param valeur pour la valeur de la force de la carte
*\return un pointeur sur une variable structure carte_t
*/
carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur, int consommable)
{
  carte_t * carte = NULL ;
  static unsigned long int cpt = 0 ;

  carte = malloc(sizeof(carte_t));

  carte->nom = malloc(sizeof(char)*TAILLE);
  strcpy(carte->nom , nom);
  carte->valeur = valeur;
  carte->cible = cible;
  carte->type = type;
  carte->consommable = consommable;
  return(carte);
}
/**
*\fn perso_t * creer_perso()
*\brief permet de créer un personnage selon différentes caractéristiques
*\return un pointeur sur une variable structure perso_t
*/
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
/**
*\fn ennemi_t * creer_ennemi(char * nom)
*\brief permet de créer un ennemi selon plusieurs caractéristiques
*\param nom pour le nom d'un ennemi
*\return un pointeur sur une variable structure ennemi_t
*/
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
/**
*\fn void detruire_carte(carte_t ** carte)
*\brief Fonction qui permet de détruire une carte
*\param carte Un pointeur de pointeur de carte qui permet de détruire le pointeur qui pointe sur la structure carte
*/
void detruire_carte(carte_t ** carte)
{
  free((*carte)->nom);
  free(*carte);
}

/**
*\fn void detruire_perso(perso_t ** perso)
*\brief Fonction qui permet de détruire un personnage
*\param perso Un pointeur de pointeur de perso qui permet de détruire le pointeur qui pointe sur la structure perso
*/
void detruire_perso(perso_t ** perso)
{
  free(*perso);
}
/**
*\fn void detruire_ennemi(ennemi_t ** ennemi)
*\brief Fonction qui permet de détruire un ennemi
*\param perso Un pointeur de pointeur de ennemi qui permet de détruire le pointeur qui pointe sur la structure ennemi
*/
void detruire_ennemi(ennemi_t ** ennemi)
{
  free((*ennemi)->nom);
  free(*ennemi);
}

/**
*\fn int initiative (perso_t * perso,ennemi_t * ennemi)
*\brief Fonction qui permet savoir si c'est l'ennemi ou le personnage qui combat en premier
*\param perso Un pointeur sur la structure perso_t qui permet de prendre la vitesse pour la comparé à l'ennemi
*\param perso Un pointeur sur la structure ennemi_t qui permet de prendre la vitesse pour la comparé au personnage
*/
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

/**
*\fn void tour_ennemi(perso_t * perso,ennemi_t * ennemi)
*\brief Fonction qui permet à l'ennemi d'effectuer une action
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action de l'ennemi
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action de l'ennemi
*/
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

/**
*\fn int tour_perso(int choix,perso_t *perso,ennemi_t * ennemi, carte_t ** deck)
*\brief Fonction qui permet au personnage d'effectuer une action
*\param choix Entier qui va permettre au personnage un choix selon les instructions de l'utilisateur
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
int tour_perso(int choix,perso_t * perso,ennemi_t * ennemi)
{
  int i;
  for(i = 0, choix--, en_tete();i < choix || !hors_liste();i++, suivant());
  printf("%s\n", ec->carte->)

}

/**
*\fn void combat(perso_t * perso, ennemi_t * ennemi, carte_t ** deck)
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
void combat(perso_t * perso, ennemi_t * ennemi)
{
  while(ennemi->pv > 0 && perso->pv > 0){
    int choix, i;
    printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
    for(i=0, en_tete() ; !hors_liste() ; i++, suivant()){
      printf("[%d] : %s\n", i+1, ec->carte->nom);
    }
    scanf("%d",&choix);
    if (initiative(perso, ennemi)){
      tour_perso(choix, perso, ennemi);
      if(ennemi->pv)
        tour_ennemi(perso, ennemi);
    }
    else{
      tour_ennemi(perso, ennemi);
      if(perso->pv)
        tour_perso(choix, perso, ennemi);
    }
  }
  if(!ennemi->pv){
    printf("Vous avez vaincu le %s\n", ennemi->nom);
  }
  else{
    printf("Vous avez été vaincu par le %s\n", ennemi->nom);
  }

}
